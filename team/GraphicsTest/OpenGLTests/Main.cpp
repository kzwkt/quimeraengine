
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include "GL/glew.h"
#include "QWindow.h"
#include "ErrorTracingDefinitions.h"
#include "QResourceManager.h"
#include "QGraphicsEngine.h"


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
void SetupTextures();
void SetTexture(GLuint programId, GLuint textureId, const char* samplerName, int textureIndex);

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
    SetupTextures();
    QE_GRAPHICS_ENGINE->SetAspect("Aspect1");

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

    QTransformationMatrix<QMatrix4x4> transformation(0.2, 0.2, 0, 0, 0, 0, 1, 0.5, 0.5, 0.5);
    QRotationMatrix3x3 rotation(0, 0, 0.01);

    glClearColor(0.4f, 0.6f, 0.9f, 0.0f);
    glViewport(0, 0, 800, 600); // Set the viewport size to fill the window

	// Main message loop:
	while (true)
	{
        transformation = transformation * rotation;

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
        QE_GRAPHICS_ENGINE->UpdateVertexShaderData("VS1", "transformationMatrix", transformation);
        
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

void SetupTextures()
{
    QMaterial* pMaterial = QE_RESOURCE_MANAGER->CreateMaterial("DEFAULT");
    pMaterial->Ambient = QColor(0, 0, 0, 1);
    pMaterial->Diffuse = QColor(0.5, 0.5, 0.5, 1);

    QE_RESOURCE_MANAGER->CreateImage("Image1", QPath("./Resources/qe.png"), QImage::E_RGBA);
    QE_RESOURCE_MANAGER->CreateImage("Image2", QPath("./Resources/wall.jpg"), QImage::E_RGB);
    QTexture2D* pTex1 = QE_RESOURCE_MANAGER->CreateTexture2D("Texture1", "Image1", QImage::E_RGBA);

    pTex1->GenerateMipmaps();
    pTex1->SetWrapModeS(QTexture2D::E_Repeat);
    pTex1->SetWrapModeT(QTexture2D::E_Repeat);
    pTex1->SetMinificationFilter(QTexture2D::E_LinearMipmaps);
    pTex1->SetMagnificationFilter(QTexture2D::E_MagLinear);

    QTexture2D* pTex2 = QE_RESOURCE_MANAGER->CreateTexture2D("Texture2", "Image2", QImage::E_RGB);

    pTex2->GenerateMipmaps();
    pTex2->SetWrapModeS(QTexture2D::E_Repeat);
    pTex2->SetWrapModeT(QTexture2D::E_Repeat);
    pTex2->SetMinificationFilter(QTexture2D::E_LinearMipmaps);
    pTex2->SetMagnificationFilter(QTexture2D::E_MagLinear);

    QAspect* pAspect = QE_RESOURCE_MANAGER->CreateAspect("Aspect1");
    pAspect->AddTexture("Texture2", "DEFAULT", "sampler2");
    pAspect->AddTexture("Texture1", "DEFAULT", "sampler1");
    pAspect->SetVertexShader("VS1");
    pAspect->SetFragmentShader("FS1");

}

