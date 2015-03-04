
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include "GL/glew.h"
#include "QWindow.h"
#include "ErrorTracingDefinitions.h"
#include "QResourceManager.h"
#include "QGraphicsEngine.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

// [TODO]: Get opengl debugging log
// [TODO]: Be able to save binary compilation of shaders
// [TODO]: Bindless textures
// [TODO]: Use Direct State Access commands

QResourceManager* QE_RESOURCE_MANAGER = null_q;
QGraphicsEngine* QE_GRAPHICS_ENGINE = null_q;

void InitializeMainWindow(HINSTANCE hInstance, QWindow** ppWindow);
void InitializeRenderingContext(QDeviceContext &dc);
void InitializeGlew();
void SetupCoreProfileRenderingContext(QDeviceContext &dc);
int MainLoop();
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void Cleanup();
void SetupEngine();
void SetupShaders();
void SetupGeometry();
void SetupTextures(QFragmentShader* pFragmentShader);

QWindow* pMainWindow;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    InitializeMainWindow(hInstance, &pMainWindow);
    InitializeRenderingContext(pMainWindow->GetDeviceContext());
    InitializeGlew();
    SetupCoreProfileRenderingContext(pMainWindow->GetDeviceContext());
    InitializeGlew(); // Every time glew is initialized, functions are associated to the current rendering context, so it should be initialized every time the context changes
    SetupEngine();
    SetupShaders();
    SetupGeometry();
    SetupTextures(QE_RESOURCE_MANAGER->GetFragmentShader("FS1"));

    int uResult = MainLoop();

    std::exit(uResult);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

int MainLoop()
{
    QE_LOG("LOG: Entering de main loop...\n");

    MSG msg;
    QStopwatch mainTimer;
    mainTimer.Set();

    glClearColor(0.4f, 0.6f, 0.9f, 0.0f);
    glViewport(0, 0, 800, 600); // Set the viewport size to fill the window

	// Main message loop:
	while (true)
	{
        while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // Translate the message and dispatch it to WindowProc()
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if(msg.message == WM_QUIT)
            break;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // Clear required buffers

        QE_GRAPHICS_ENGINE->UpdateVertexShaderData("VS1", "uColor", SQFloat::Clamp(sin(mainTimer.GetElapsedTimeAsFloat() / 50000.0f), 0.0f, 1.0f), sin(mainTimer.GetElapsedTimeAsFloat() / 30000.0f), sin(mainTimer.GetElapsedTimeAsFloat() / 40000.0f), 1.0f);
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, null_q);

        if(pMainWindow->GetDeviceContext().GetCurrentRenderingContext() != null_q)
            pMainWindow->GetDeviceContext().SwapBuffers();
	}

    QE_LOG("LOG: Exiting de main loop...\n");

	return (int) msg.wParam;
}

void InitializeMainWindow(HINSTANCE hInstance, QWindow** ppWindow)
{
    *ppWindow = new QWindow(hInstance);
    (*ppWindow)->SetMessageDispatcher(&WndProc);
    (*ppWindow)->SetHeight(600);
    (*ppWindow)->SetWidth(800);
    (*ppWindow)->SetTitle("OpenGL test application");

    QE_LOG("LOG: Window initialized.\n");

    (*ppWindow)->Show();

    QE_LOG("LOG: Window shown.\n");
}

void InitializeRenderingContext(QDeviceContext &dc)
{
    dc.SetPixelFormat(QDeviceContext::E_R8G8B8A8D24S8);
    QDeviceContext::NativeRenderingContext renderingContext = dc.CreateRenderingContext();
    dc.MakeRenderingContextCurrent();

    QE_LOG("LOG: Pixel format set.\n");
}

void InitializeGlew()
{
    glewExperimental = GL_TRUE;
    GLenum eInitResult = glewInit();
    
    QE_ASSERT_ERROR(eInitResult == GLEW_OK, string_q("An error occurred when attempting to initialize GLEW. ") + rcast_q(glewGetErrorString(eInitResult), const i8_q*));
    const GLubyte* u = glewGetErrorString(eInitResult);
    QE_LOG(string_q("LOG: GLEW Initialized (") + rcast_q(glewGetString(GLEW_VERSION), const i8_q*) + ")\n");
    QE_LOG(string_q("LOG: Open GL Version ") + rcast_q(glGetString(GL_VERSION), const i8_q*) + "\n");
}

void SetupCoreProfileRenderingContext(QDeviceContext &dc)
{
    QDeviceContext::NativeRenderingContext rc = dc.GetCurrentRenderingContext();
    dc.CreateAdvancedRenderingContext(QDeviceContext::E_R8G8B8A8D24S8, true);
    dc.MakeRenderingContextCurrent();
    dc.DeleteRenderingContext(rc);
}

void Cleanup()
{
    QDeviceContext::NativeRenderingContext rc = pMainWindow->GetDeviceContext().GetCurrentRenderingContext();
    pMainWindow->GetDeviceContext().ResetCurrentRenderingContext();
    pMainWindow->GetDeviceContext().DeleteRenderingContext(rc);
    delete pMainWindow;

    QE_LOG("LOG: Clean up performed.\n");
}

void SetupEngine()
{
    QE_RESOURCE_MANAGER = new QResourceManager(new QShaderCompositor());
    QE_GRAPHICS_ENGINE = new QGraphicsEngine(QE_RESOURCE_MANAGER);
}

void SetupShaders()
{
    QE_RESOURCE_MANAGER->CreateVertexShader("VS1", QPath("./Resources/VertexShader.glsl"));
    QE_RESOURCE_MANAGER->CreateFragmentShader("FS1", QPath("./Resources/FragmentShader.glsl"));
    QE_GRAPHICS_ENGINE->SetVertexShader("VS1");
    QE_GRAPHICS_ENGINE->SetFragmentShader("FS1");
}

void SetupGeometry()
{
    struct QVertex
    {
        QVector3 Position;
        QVector4 Color;
        QVector2 TexCoords0;
        QVector2 TexCoords1;
    };

    QVertex arVertices[] = {
        
        { QVector3(0.5f, 0.5f, 0.0f),
          QVector4(1.0f, 0.0f, 0.0f, 1.0f),
          QVector2(1.0f, 0.0f),// Images are flipped vertically, texture coordinates had to be reverted for Y axis
          QVector2(1.0f, 1.0f)
        },
        
        { QVector3(0.5f, -0.5f, 0.0f),
          QVector4(0.0f, 1.0f, 0.0f, 1.0f),
          QVector2(1.0f, 1.0f),
          QVector2(1.0f, 0.0f)
        },
        
        { QVector3(-0.5f, -0.5f, 0.0f),
          QVector4(0.0f, 0.0f, 1.0f, 1.0f),
          QVector2(0.0f, 1.0f),
          QVector2(0.0f, 0.0f)
        },
        
        { QVector3(-0.5f, 0.5f, 0.0f),
          QVector4(1.0f, 1.0f, 1.0f, 1.0f),
          QVector2(0.0f, 0.0f),
          QVector2(0.0f, 1.0f)
        }
    };

    // Indices
    GLuint arIndices[] = { 
        0, 1, 3,   // First Triangle
        1, 2, 3    // Second Triangle
    };

    // create attribs
    // create VAO
    GLuint vaoTriangleID = 0;
    glGenVertexArrays(1, &vaoTriangleID);
    glBindVertexArray(vaoTriangleID);

    // Set up VAO

    // create VBO
    GLuint vboTriangleID = 0;
    glGenBuffers(1, &vboTriangleID);
    glBindBuffer(GL_ARRAY_BUFFER, vboTriangleID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(arVertices), &arVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(QVertex), (GLvoid*)0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(QVertex), (GLvoid*)(sizeof(QVector3)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(QVertex), (GLvoid*)(sizeof(QVector3) + sizeof(QVector4)));
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(QVertex), (GLvoid*)(sizeof(QVector3) + sizeof(QVector4) + sizeof(QVector2)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    // create EBO
    GLuint eboTriangleID = 0;
    glGenBuffers(1, &eboTriangleID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboTriangleID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(arIndices), arIndices, GL_STATIC_DRAW);
    
}

void SetTexture(GLuint programId, const char* path, const char* samplerName, int textureIndex)
{
    EQFileSystemError eErrorInfo = EQFileSystemError::E_Unknown;
    QFileStream fs(QPath(path), EQFileOpenMode::E_Open, 256000, eErrorInfo);
    QBinaryStreamReader<QFileStream> bs(fs);
    stbi_uc* pImageFile = new stbi_uc[fs.GetLength()];
    bs.ReadBytes(pImageFile, fs.GetLength());

    int x, y, components;
    stbi_uc* pTexture = null_q;
    pTexture = stbi_load_from_memory(pImageFile, fs.GetLength(), &x, &y, &components, STBI_rgb);
    GLuint textureID = 0;
    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0 + textureIndex);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, pTexture);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(pTexture);

    GLint samplerLocation = glGetUniformLocation(programId, samplerName);

    if (samplerLocation == -1)
    {
        QE_ASSERT_WINDOWS_ERROR("An error occurred while getting the location of a uniform (SetupTextures).");
    }

    glProgramUniform1i(programId, samplerLocation, textureIndex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // Mipmap levels
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


void SetupTextures(QFragmentShader* pFragmentShader)
{
   /* SetTexture(pFragmentShader->GetProgramID(), "./Resources/awesomeface.png", "sampler1", 0);
    SetTexture(pFragmentShader->GetProgramID(), "./Resources/wall.jpg", "sampler2", 1);
    */
    EQFileSystemError eErrorInfo = EQFileSystemError::E_Unknown;
    QFileStream fs(QPath("./Resources/qe.png"), EQFileOpenMode::E_Open, 256000, eErrorInfo);
    QBinaryStreamReader<QFileStream> bs(fs);
    stbi_uc* pImageFile = new stbi_uc[fs.GetLength()];
    bs.ReadBytes(pImageFile, fs.GetLength());

    QFileStream fs2(QPath("./Resources/wall.jpg"), EQFileOpenMode::E_Open, 256000, eErrorInfo);
    QBinaryStreamReader<QFileStream> bs2(fs2);
    stbi_uc* pImageFile2 = new stbi_uc[fs2.GetLength()];
    bs2.ReadBytes(pImageFile2, fs2.GetLength());

    int x, y, components;
    stbi_uc* pTexture = null_q;
    pTexture = stbi_load_from_memory(pImageFile, fs.GetLength(), &x, &y, &components, STBI_rgb_alpha);
    GLuint textureID = 0;
    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, pTexture);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(pTexture);

    GLint samplerLocation = glGetUniformLocation(pFragmentShader->GetProgramID(), "sampler1");

    if (samplerLocation == -1)
    {
        QE_ASSERT_WINDOWS_ERROR("An error occurred while getting the location of a uniform (SetupTextures).");
    }

    glProgramUniform1i(pFragmentShader->GetProgramID(), samplerLocation, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // Mipmap levels
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_uc* pTexture2 = null_q;
    x = 0;
    y = 0;
    components = 0;
    pTexture2 = stbi_load_from_memory(pImageFile2, fs2.GetLength(), &x, &y, &components, STBI_rgb);
    GLuint textureID2 = 0;
    glGenTextures(1, &textureID2);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureID2);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, pTexture2);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(pTexture2);

    GLint samplerLocation2 = glGetUniformLocation(pFragmentShader->GetProgramID(), "sampler2");

    if (samplerLocation2 == -1)
    {
        QE_ASSERT_WINDOWS_ERROR("An error occurred while getting the location of a uniform (SetupTextures).");
    }

    glProgramUniform1i(pFragmentShader->GetProgramID(), samplerLocation2, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // Mipmap levels
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}