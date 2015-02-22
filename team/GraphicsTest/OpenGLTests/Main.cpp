
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include "GL/glew.h"
#include "QWindow.h"
#include "ErrorTracingDefinitions.h"
#include "QResourceManager.h"
#include "QGraphicsEngine.h"

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
    SetupEngine();
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

        QE_GRAPHICS_ENGINE->UpdateVertexShaderData("VS1", "uColor", SQFloat::Clamp(sin(mainTimer.GetElapsedTimeAsFloat() / 20000.0f), 0.0f, 1.0f), sin(mainTimer.GetElapsedTimeAsFloat() / 10000.0f), sin(mainTimer.GetElapsedTimeAsFloat() / 30000.0f), 1.0f);

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
    QE_RESOURCE_MANAGER->CreateVertexShader("VS1", QPath("./Resources/VertexShader.txt"));
    QE_RESOURCE_MANAGER->CreateFragmentShader("FS1", QPath("./Resources/FragmentShader.txt"));
    QE_GRAPHICS_ENGINE->SetVertexShader("VS1");
    QE_GRAPHICS_ENGINE->SetFragmentShader("FS1");
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