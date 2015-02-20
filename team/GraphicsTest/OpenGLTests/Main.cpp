
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include "GL/glew.h"
#include "QWindow.h"
#include "ErrorTracingDefinitions.h"

void InitializeMainWindow(HINSTANCE hInstance, QWindow** ppWindow);
void InitializeRenderingContext(QDeviceContext &dc);
void InitializeGlew();
void SetupCoreProfileRenderingContext(QDeviceContext &dc);
int MainLoop();
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void Cleanup();
void SetupShaders();
void SetupGeometry();

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
    SetupShaders();
    SetupGeometry();

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

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, NULL, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

        glClearColor(0.4f, 0.6f, 0.9f, 0.0f);
        glViewport(0, 0, 800, 600); // Set the viewport size to fill the window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // Clear required buffers

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

void SetupShaders()
{
    // Reads the vertex shader from text file
    string_q strFileContent;
    EQFileSystemError eErrorInfo = EQFileSystemError::E_Unknown;
    QFileStream fs(QPath("./Resources/VertexShader.txt"), EQFileOpenMode::E_Open, 500, eErrorInfo);
    QTextStreamReader<QFileStream> ts(fs, EQTextEncoding::E_ASCII);
    ts.ReadToEnd(strFileContent);
    fs.Close();
    
    // Adapts the content
    QArrayResult<i8_q> arFileContent = strFileContent.ToBytes(EQTextEncoding::E_ASCII);
    const char* szFileContent = arFileContent.Get();

    // Compiles the vertex shader
    QE_LOG("LOG: Compiling vertex shader...\n");
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID, 1, &szFileContent, null_q);
    glCompileShader(vertexShaderID);

    // Checks result
    GLint nSucceed;
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &nSucceed);

    if(!nSucceed)
    {
        GLsizei nActualLength = 0;
        GLchar szErrorMessage[512];
        glGetShaderInfoLog(vertexShaderID, 512, &nActualLength, szErrorMessage);

        QE_ASSERT_ERROR(false, szErrorMessage);
    }

    QE_LOG("LOG: Vertex shader compiled successfully.\n");

    // Reads the fragment shader from text file
    QFileStream fs2(QPath("./Resources/FragmentShader.txt"), EQFileOpenMode::E_Open, 500, eErrorInfo);
    QTextStreamReader<QFileStream> ts2(fs2, EQTextEncoding::E_ASCII);
    strFileContent = string_q::GetEmpty();
    ts2.ReadToEnd(strFileContent);
    fs2.Close();

    // Adapts the content
    QArrayResult<i8_q> arFileContent2 = strFileContent.ToBytes(EQTextEncoding::E_ASCII);
    szFileContent = arFileContent2.Get();

    // Compiles the fragment shader
    QE_LOG("LOG: Compiling fragment shader...\n");
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID, 1, &szFileContent, null_q);
    glCompileShader(fragmentShaderID);

    // Checks result
    nSucceed = 0;
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &nSucceed);

    if(!nSucceed)
    {
        GLsizei nActualLength = 0;
        GLchar szErrorMessage[512];
        glGetShaderInfoLog(fragmentShaderID, 512, &nActualLength, szErrorMessage);

        QE_ASSERT_ERROR(false, szErrorMessage);
    }

    QE_LOG("LOG: Fragment shader compiled successfully.\n");

    // Links the program
    QE_LOG("LOG: Linking shader program...\n");
    GLuint shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertexShaderID);
    glAttachShader(shaderProgramID, fragmentShaderID);
    glLinkProgram(shaderProgramID);

    // Checks result
    nSucceed = 0;
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &nSucceed);

    if(!nSucceed)
    {
        GLsizei nActualLength = 0;
        GLchar szErrorMessage[512];
        glGetProgramInfoLog(shaderProgramID, 512, &nActualLength, szErrorMessage);

        QE_ASSERT_ERROR(false, szErrorMessage);
    }

    QE_LOG("LOG: Shader program linked successfully.\n");

    // Deletes useless shaders
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    // Makes the program the current
    glUseProgram(shaderProgramID);

    QE_LOG("LOG: Using shader program.\n");
}

void SetupGeometry()
{
    // Vertices
    GLfloat arVertices[] = { 
      0.5f,  0.5f, 0.0f,  // Top Right
     0.5f, -0.5f, 0.0f,  // Bottom Right
    -0.5f, -0.5f, 0.0f,  // Bottom Left
    -0.5f,  0.5f, 0.0f   // Top Left 
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(arVertices), arVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // create EBO
    GLuint eboTriangleID = 0;
    glGenBuffers(1, &eboTriangleID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboTriangleID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(arIndices), arIndices, GL_STATIC_DRAW);

}