
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include "GL/glew.h"
#include "QWindow.h"
#include "ErrorTracingDefinitions.h"
#include "QKeyboard.h"
#include "QCamera.h"
#include "QuimeraEngine.h"

/*#include "glm/glm.hpp"
#include "glm/gtc/matrix_projection.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_operation.hpp"
#include "glm/gtx/transform2.hpp"
*/
// [TODO]: Get opengl debugging log
// [TODO]: Be able to save binary compilation of shaders
// [TODO]: Bindless textures, vertex arrays and uniforms
// [TODO]: Use Direct State Access commands
// [TODO]: #includes in shaders, semantics like HLSL with glBindAttribLocationARB http://www.g-truc.net/post-0267.html
// [TODO]: Buffer objects in shaders (i/o data)
// [TODO]: Subroutines, seem to be slower
// [TODO]: Path rendering
// [TODO]: Pixel Buffer Objects and Pixel Transfers

// Since it will not be possible to add precise documentation for every implementation (DX or OGL), main documentation will contain the common behavior and the rest
// of restrictions will be explained through assertions

QKeyboard* QE_KEYBOARD = null_q;
QCamera* QE_CAMERA = null_q;
QStopwatchEnclosed MAIN_TIMER(QTimeSpan(0, 0, 0, 1, 0, 0, 0), EQStopwatchEnclosedBehavior::E_Proportional);
QStopwatchEnclosed ANIMATION_TIMER(QTimeSpan(0, 0, 0, 1, 0, 0, 0), EQStopwatchEnclosedBehavior::E_Proportional);

void SetupInputDevices();
int MainLoop();
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
QWindow* SetupWindowAndEngine(HINSTANCE hInstance);
void SetupEngine(QWindow* pWindow);
void SetupShaders();
void SetupModel();
void SetupScene();
QWindow* pMainWindow;
void CheckInputs();
void OnKeyPressed(const QKeyboard* pKeyboard, const QKeyboard::KeyInfo &info);
void OnKeyKept(const QKeyboard* pKeyboard, const QKeyboard::KeyInfo &info);
void OnKeyReleased(const QKeyboard* pKeyboard, const QKeyboard::KeyInfo &info);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR    lpCmdLine,
                     int       nCmdShow)
{
    MAIN_TIMER.Set();
    ANIMATION_TIMER.Set();

    SetupInputDevices();
    pMainWindow = SetupWindowAndEngine(hInstance);
    SetupEngine(pMainWindow);
    SetupShaders();
    SetupModel();
    SetupScene();

    int uResult = MainLoop();

    std::exit(uResult);
}

LRESULT WndProc(QWindow* pSender, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
    wchar_t msg[32];

    QE_KEYBOARD->Update(message, wParam, lParam);

	switch (message)
	{
    /*case WM_SYSKEYDOWN:
        swprintf_s(msg, L"WM_SYSKEYDOWN: 0x%x\n", wParam);
        OutputDebugString(msg);
        break;

    case WM_SYSCHAR:
        swprintf_s(msg, L"WM_SYSCHAR: %c\n", (wchar_t)wParam);
        OutputDebugString(msg);
        break;

    case WM_SYSKEYUP:
        swprintf_s(msg, L"WM_SYSKEYUP: 0x%x\n", wParam);
        OutputDebugString(msg);
        break;

    case WM_KEYDOWN:
        swprintf_s(msg, L"WM_KEYDOWN: 0x%x\n", wParam);
        OutputDebugString(msg);
        break;

    case WM_KEYUP:
        swprintf_s(msg, L"WM_KEYUP: 0x%x\n", wParam);
        OutputDebugString(msg);
        break;

    case WM_CHAR:
        swprintf_s(msg, L"WM_CHAR: %c\n", (wchar_t)wParam);
        OutputDebugString(msg);
        break;*/
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return 0;
}

void OnWindowSizeChanged(QWindow* pWindows, const QWindow::QSizeChangedEventData eventArgs)
{
    // [TODO]: Add an option so all this is updated automatically
    // [TODO]: Implement SetFullscreen, when windowing set the previous configuration
    // [TODO]: Receive the window status (minimized, maximized, restored)
    // [TODO]: Add option to minimize when window is not active and it's fullscreen (clicking outside the window)

    if (eventArgs.WindowStatus != QWindow::E_Minimized)
    {
        QE->Graphics->SetCanvas(eventArgs.NewClientAreaWidth, eventArgs.NewClientAreaHeight);

        QViewport viewport;
        viewport.Top = 0;
        viewport.Left = 0;
        viewport.Width = eventArgs.NewClientAreaWidth;
        viewport.Height = eventArgs.NewClientAreaHeight;
        QE->Graphics->SetViewport(viewport);

        if (QE_CAMERA)
            QE_CAMERA->Frustum.AspectRatio = (float_q)eventArgs.NewClientAreaWidth / (float_q)eventArgs.NewClientAreaHeight;
    }
}

int MainLoop()
{
    QE_LOG("LOG: Entering de main loop...\n");

    MSG msg;

    QTransformationMatrix<QMatrix4x4> transformation;

    float_q fTranslation = 0;
    float_q fRotation = 0;

	// Main message loop:
    QAspect* pAspect = QE->Resources->GetAspect("64124be4_dds");
    QTexture2D* pTexture = QE->Resources->GetTexture2D("64124be4.jpg");
    QFramebuffer* pFramebuffer = QE->Graphics->CreateFramebuffer("FBO");
    QFramebuffer* pFramebuffer2 = QE->Graphics->CreateFramebuffer("FBO2");
    
    QKeyValuePair<QHashedString, QTexture2D*> texture = QE->Resources->CreateTexture2D("MyTexture", EQTextureFormat::E_RGB8UI_Normalized, 512, 512, 1, 0);
    pAspect->SetTexture(QAspect::E_Diffuse, 0, "MyTexture");
    GETFULLCONTENT AND GETSUBTEXTURE should return the number of bytes reserved for the buffer
    void* pSubtexture = null_q;
    pTexture->GetFullContent(0, 0, &pSubtexture);
    texture.GetValue()->SetFullContent(0, pSubtexture);
    
    QKeyValuePair<QHashedString, QTexture2D*> texture2 = QE->Resources->CreateTexture2D("MyTexture2", EQTextureFormat::E_RGBA8UI_Normalized, 320, 240, 1, 0);
    pFramebuffer->SetColorBuffer(0, "MyTexture", QFramebuffer::E_Texture2D);
    pFramebuffer2->SetColorBuffer(0, "MyTexture2", QFramebuffer::E_Texture2D);

    QE->Graphics->CreateRenderbuffer("RC1", EQPixelFormat::E_RGBA8UI_Normalized, QE->Graphics->GetCanvasWidth(), QE->Graphics->GetCanvasHeight(), 0);
    pFramebuffer->SetColorBuffer(0, "RC1", QFramebuffer::E_Renderbuffer);

    QColor cubeColor = QColor::GetVectorOfOnes();
    /*
    GLuint textureID = 0;
    glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, 1, &textureID);
    glTextureStorage2DMultisample(textureID, 4, GL_RGBA8, 512, 512, 0);

    GLuint textureID2 = 0;
    glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, 1, &textureID2);
    glTextureStorage2DMultisample(textureID2, 4, GL_RGBA8, 256, 256, 0);

    GLuint framebufferID = 0;
    glCreateFramebuffers(1, &framebufferID);
    glNamedFramebufferTexture2DEXT(framebufferID, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, textureID, 0);

    GLuint framebufferID2 = 0;
    glCreateFramebuffers(1, &framebufferID2);
    glNamedFramebufferTexture2DEXT(framebufferID2, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, textureID2, 0);

    glBlitNamedFramebuffer(framebufferID, framebufferID2, 0, 0, 512, 512, 0, 0, 256, 256, GL_COLOR_BUFFER_BIT, GL_SCALED_RESOLVE_FASTEST_EXT);

    QE_ASSERT_OPENGL_ERROR("YEAH");
    */
    while (true)
	{
        CheckInputs();
        ANIMATION_TIMER.Set();

        QSpaceConversionMatrix worldMatrix, viewMatrix, projectionMatrix;

        viewMatrix = QE_CAMERA->GetViewSpaceMatrix();
        projectionMatrix = QE_CAMERA->Frustum.GetProjectionSpaceMatrix();

        QVector3 vTranslation(0, 0, 0);
        QQuaternion qRotation(0, 0, SQAngle::_HalfPi * MAIN_TIMER.GetProgression());
        QVector3 vScale(1, 1, 1);

        //worldMatrix.SetWorldSpaceMatrix(vTranslation, qRotation, vScale);
        
        transformation = worldMatrix * viewMatrix * projectionMatrix;

        QE->Graphics->ClearAllRenderTargets();
        /*
        QE->Graphics->SetDestinationFramebuffer("FBO");*/
        QViewport textureViewport;
        textureViewport.Height = 512;
        textureViewport.Width = 512;
        textureViewport.Top = 0;
        textureViewport.Left = 0;
        QViewport originalViewport = QE->Graphics->GetViewport();
        
        QE->Graphics->UpdateVertexShaderData("VS1", "uColor", cubeColor.x, cubeColor.y, cubeColor.z, cubeColor.w);
        QE->Graphics->UpdateVertexShaderData("VS1", "transformationMatrix", transformation.Transpose());

        QStaticModel* pModel = QE->Resources->GetStaticModel("Model1");
         
        // [TODO]: Create array of matrices and update hierarchically
        
        QE->Graphics->SetStaticModel("Model1");
        QE->Graphics->SetDestinationFramebuffer("FBO");
        QE->Graphics->SetColorBufferClearValue(QColor(1, 0, 0, 1));
        QE->Graphics->DisableDepthTest();
        QE->Graphics->ClearAllRenderTargets();
        /*
        for (u32_q i = 0; i < pModel->GetSubmeshCount(); ++i)
        {
            QE->Graphics->SetAspect(pModel->GetSubmeshAspectByIndex(i)->AspectId);
            QE->Graphics->Draw(EQPrimitiveType::E_Triangle, pModel->GetSubmeshByIndex(i)->FirstVertex, pModel->GetSubmeshByIndex(i)->VertexCount, pModel->GetSubmeshByIndex(i)->FirstIndex, pModel->GetSubmeshByIndex(i)->IndexCount);
        }
        */
        QE->Graphics->EnableDepthTest();
        QE->Graphics->SetDestinationFramebuffer("QE_DEFAULT");
        QE->Graphics->SetViewport(originalViewport);
        QE->Graphics->SetColorBufferClearValue(QColor(1, 1, 1, 1));
        QE->Graphics->ClearAllRenderTargets();

        for (u32_q i = 0; i < pModel->GetSubmeshCount(); ++i)
        {
            QE->Graphics->SetAspect(pModel->GetSubmeshAspectByIndex(i)->AspectId);
            QE->Graphics->Draw(EQPrimitiveType::E_Triangle, pModel->GetSubmeshByIndex(i)->FirstVertex, pModel->GetSubmeshByIndex(i)->VertexCount, pModel->GetSubmeshByIndex(i)->FirstIndex, pModel->GetSubmeshByIndex(i)->IndexCount);
        }

        QE->Graphics->CopyPixelsBetweenFramebuffers("QE_DEFAULT", "FBO", QScreenRectangle<u32_q>(QPoint<u32_q>(), QE->Graphics->GetCanvasWidth(), QE->Graphics->GetCanvasHeight()), QScreenRectangle<u32_q>(QPoint<u32_q>(), texture.GetValue()->GetWidth(), texture.GetValue()->GetHeight()), QGraphicsEngine::E_Color, QGraphicsEngine::E_Nearest);
        QE->Graphics->CopyPixelsBetweenFramebuffers("FBO", "QE_DEFAULT", QScreenRectangle<u32_q>(QPoint<u32_q>(), texture.GetValue()->GetWidth(), texture.GetValue()->GetHeight()), QScreenRectangle<u32_q>(QPoint<u32_q>(100, 100), texture.GetValue()->GetWidth(), texture.GetValue()->GetHeight()), QGraphicsEngine::E_Color, QGraphicsEngine::E_Nearest);

        //QE->Graphics->CopyPixelsBetweenFramebuffers("FBO2", "QE_DEFAULT", QScreenRectangle<u32_q>(QPoint<u32_q>(0, 0), texture2.GetValue()->GetWidth(), texture2.GetValue()->GetHeight()), QScreenRectangle<u32_q>(QPoint<u32_q>(100, 100), QE->Graphics->GetCanvasWidth(), QE->Graphics->GetCanvasHeight()), QGraphicsEngine::E_Color, QGraphicsEngine::E_Linear);
        
        QE->Graphics->SwapBuffers();

        while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // Translate the message and dispatch it to WindowProc()
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if(msg.message == WM_QUIT)
            break;
	}

    QE_LOG("LOG: Exiting de main loop...\n");

	return (int) msg.wParam;
}

QWindow* SetupWindowAndEngine(HINSTANCE hInstance)
{
    QWindow::QWindowSettings windowSettings;
    windowSettings.Title = "Quimera Engine OpenGL Graphics Engine Prototype";
    windowSettings.ClientAreaWidth = 1024;
    windowSettings.ClientAreaHeight = 768;
    windowSettings.Top = 0;
    windowSettings.Left = 0;
    windowSettings.ColorBufferFormat = EQPixelFormat::E_RGBA8UI_Normalized;
    windowSettings.DepthBufferFormat = EQPixelFormat::E_D24S8;
    windowSettings.StencilBufferFormat = EQPixelFormat::E_D24S8;
    windowSettings.Samples = 0;
    windowSettings.IsFullscreen = false;

    QWindow* pActualWindow = new QWindow(hInstance, windowSettings);
    pActualWindow->AfterOSMessageReceived += WndProc;
    pActualWindow->SizeChanged += OnWindowSizeChanged;
    pActualWindow->SetMinimizationOnDeactivation(true);

    QGraphicsEngine::QGraphicsEngineSettings graphicsEngineSettings;
    graphicsEngineSettings.Framebuffer.ColorBufferFormat = windowSettings.ColorBufferFormat;
    graphicsEngineSettings.Framebuffer.DepthBufferFormat = windowSettings.DepthBufferFormat;
    graphicsEngineSettings.Framebuffer.StencilBufferFormat = windowSettings.StencilBufferFormat;
    graphicsEngineSettings.Framebuffer.Width = windowSettings.ClientAreaWidth;
    graphicsEngineSettings.Framebuffer.Height = windowSettings.ClientAreaHeight;
    graphicsEngineSettings.Framebuffer.Samples = windowSettings.Samples;
    graphicsEngineSettings.DeviceContext = pActualWindow->GetDeviceContext();

    QuimeraEngine::Initilize(graphicsEngineSettings);

    pActualWindow->Show();

    return pActualWindow;
}

void SetupEngine(QWindow* pWindow)
{
    //glClearColor(0.4f, 0.6f, 0.9f, 0.0f);
}

void SetupShaders()
{
    QE->Resources->CreateShader("VS1", QPath("./Resources/VertexShader.glsl"), QShader::E_VertexShader);
    QE->Resources->CreateShader("FS1", QPath("./Resources/FragmentShader.glsl"), QShader::E_FragmentShader);
    QShadingPipeline* pShadingPipeline = QE->Resources->CreateShadingPipeline("Pipeline1").GetValue();
    pShadingPipeline->SetVertexShaderId("VS1");
    pShadingPipeline->SetFragmentShaderId("FS1");
}

void SetupModel()
{
    QE->Resources->CreateImage("DEFAULT", QPath("./Resources/wall.jpg"), QImage::E_RGB);

    QKeyValuePair<QHashedString, QStaticModel*> model = QE->Resources->CreateStaticModel("Model1", QPath("./Resources/sonic.obj"), &CUSTOM_VERTEX_DESCRIPTION);

    for (u32_q i = 0; i < model.GetValue()->GetSubmeshCount(); ++i)
    {
        QHashedString strAspectId = model.GetValue()->GetSubmeshAspectByIndex(i)->AspectId;
        QAspect* pAspect = QE->Resources->GetAspect(strAspectId);
        pAspect->SetShadingPipeline("Pipeline1");
    }

    
    /*
    QE_LOG("Listing triangle indices\n");
    QE_LOG("------------------------\n");

    for (u32_q i = 0; i < pModel->GetIndexCount(); i += 3)
        QE_LOG(string_q("[") + string_q::FromInteger(i / 3U) + "] \t" + string_q::FromInteger(pModel->GetIndexbuffer()[i + 0]) + ", \t" +
                                                                        string_q::FromInteger(pModel->GetIndexbuffer()[i + 1]) + ", \t" +
                                                                        string_q::FromInteger(pModel->GetIndexbuffer()[i + 2]) + "\n");
                                                                        */
   /* QE_LOG("Listing triangle vertices\n");
    QE_LOG("------------------------\n");

    unsigned int i2 = pModel->GetSubmeshByIndex(6)->FirstVertex;

    QVertexWith1Normal2TextureCoords* pVertex = (QVertexWith1Normal2TextureCoords*)pModel->GetVertexBuffer();
    for (u32_q i = 27804; i < pModel->GetVertexCount(); ++i)
        QE_LOG(string_q("[") + string_q::FromInteger(i) + "]\n" +
               pVertex[i].Position.ToString() + "\n" +
               pVertex[i].TextureCoords[0].ToString() + "\n" +
               pVertex[i].TextureCoords[1].ToString() + "\n"
               );*/
}

void SetupInputDevices()
{
    QE_KEYBOARD = new QKeyboard();
    QE_KEYBOARD->KeyPressedEvent += &OnKeyPressed;
    //QE_KEYBOARD->KeyKeptEvent += &OnKeyKept;
    //QE_KEYBOARD->KeyReleasedEvent += &OnKeyReleased;
}

void SetupScene()
{
    QE_CAMERA = new QCamera();
    QE_CAMERA->Frustum.AspectRatio = 1024.0f / 768.0f;
    QE_CAMERA->Frustum.FarPlaneDistance = 1000.0f;
    QE_CAMERA->Frustum.Fov = SQAngle::_QuarterPi;
    QE_CAMERA->Frustum.NearPlaneDistance = 0.1f;
    QE_CAMERA->SetPosition(QVector4(-5, 15, -50, 1.0f));
    QE_CAMERA->SetOrientation(QQuaternion::GetIdentity());
    QE_CAMERA->SetScale(QVector3::GetVectorOfOnes());
}

void CheckInputs()
{
    const float_q SPEED = 9.0f;

    if (QE_KEYBOARD->IsDown(QKeyboard::E_LEFT))
    {
        QE_CAMERA->Move(QVector3(-ANIMATION_TIMER.GetProgression() * SPEED, 0, 0));
    }

    if (QE_KEYBOARD->IsDown(QKeyboard::E_RIGHT))
    {
        QE_CAMERA->Move(QVector3(ANIMATION_TIMER.GetProgression() * SPEED, 0, 0));
    }

    if (QE_KEYBOARD->IsDown(QKeyboard::E_UP))
    {
        QE_CAMERA->Move(QVector3(0, 0, ANIMATION_TIMER.GetProgression() * SPEED));
    }

    if (QE_KEYBOARD->IsDown(QKeyboard::E_DOWN))
    {
        QE_CAMERA->Move(QVector3(0, 0, -ANIMATION_TIMER.GetProgression() * SPEED));
    }
    
    if (QE_KEYBOARD->IsDown(QKeyboard::E_Z))
    {
        QE_CAMERA->RotateYaw(-SQAngle::_QuarterPi * ANIMATION_TIMER.GetProgression());
    }
    
    if (QE_KEYBOARD->IsDown(QKeyboard::E_X))
    {
        QE_CAMERA->RotateYaw(SQAngle::_QuarterPi * ANIMATION_TIMER.GetProgression());
    }
    
    if (QE_KEYBOARD->IsDown(QKeyboard::E_F))
    {
        QE_CAMERA->RotatePitch(-SQAngle::_QuarterPi * ANIMATION_TIMER.GetProgression());
    }

    if (QE_KEYBOARD->IsDown(QKeyboard::E_V))
    {
        QE_CAMERA->RotatePitch(SQAngle::_QuarterPi * ANIMATION_TIMER.GetProgression());
    }

    if (QE_KEYBOARD->IsDown(QKeyboard::E_Q))
    {
        QE_CAMERA->RotateRoll(SQAngle::_QuarterPi * ANIMATION_TIMER.GetProgression());
    }

    if (QE_KEYBOARD->IsDown(QKeyboard::E_W))
    {
        QE_CAMERA->RotateRoll(-SQAngle::_QuarterPi * ANIMATION_TIMER.GetProgression());
    }

    if (QE_KEYBOARD->IsDown(QKeyboard::E_D))
    {
        QE_CAMERA->Move(QVector3(0, ANIMATION_TIMER.GetProgression() * SPEED, 0));
    }
    
    if (QE_KEYBOARD->IsDown(QKeyboard::E_C))
    {
        QE_CAMERA->Move(QVector3(0, -ANIMATION_TIMER.GetProgression() * SPEED, 0));
    }

    if (QE_KEYBOARD->IsDown(QKeyboard::E_ESCAPE))
    {
        exit(0);
    }
}

void OnKeyPressed(const QKeyboard* pKeyboard, const QKeyboard::KeyInfo &info)
{
   /* if (info.Code == QKeyboard::E_LEFT)
    {
        QE_CAMERA->Move(QVector3(-ANIMATION_TIMER.GetProgression() * 0.0001f, 0, 0));
    }
    else if (info.Code == QKeyboard::E_RIGHT)
    {
        QE_CAMERA->Move(QVector3(ANIMATION_TIMER.GetProgression() * 0.0001f, 0, 0));
    }
    else if (info.Code == QKeyboard::E_UP)
    {
        QE_CAMERA->Move(QVector3(0, 0, ANIMATION_TIMER.GetProgression() * 0.0001f));
    }
    else if (info.Code == QKeyboard::E_DOWN)
    {
        QE_CAMERA->Move(QVector3(0, 0, -ANIMATION_TIMER.GetProgression() * 0.0001f));
    }
    else if (info.Code == QKeyboard::E_Z)
    {
        QE_CAMERA->RotateYaw(-SQAngle::_QuarterPi * ANIMATION_TIMER.GetProgression());
    }
    else if (info.Code == QKeyboard::E_X)
    {
        QE_CAMERA->RotateYaw(SQAngle::_QuarterPi * ANIMATION_TIMER.GetProgression());
    }
    else if (info.Code == QKeyboard::E_D)
    {
        QE_CAMERA->Move(QVector3(0, ANIMATION_TIMER.GetProgression() * 0.0001f, 0));
    }
    else if (info.Code == QKeyboard::E_C)
    {
        QE_CAMERA->Move(QVector3(0, -ANIMATION_TIMER.GetProgression() * 0.0001f, 0));
    }
    else if (info.Code == QKeyboard::E_ESCAPE)
    {
        exit(0);
    }
    else*/ if (info.Code == QKeyboard::E_ENTER && pKeyboard->IsDown(QKeyboard::E_LEFTALT) && !info.HasCharacter)
    {
        if (pMainWindow->IsFullscreen())
            pMainWindow->SetWindowed();
        else
            pMainWindow->SetFullscreen();
    }
    else if (info.Code == QKeyboard::E_ENTER && pKeyboard->IsDown(QKeyboard::E_LEFTCONTROL) && !info.HasCharacter)
    {
        if (pMainWindow->GetWindowStatus() == QWindow::E_Restored)
            pMainWindow->SetWindowStatus(QWindow::E_Maximized);
        else
            pMainWindow->SetWindowStatus(QWindow::E_Restored);
    }

    /*QE_LOG("KEY PRESSED\n");
    QE_LOG(string_q("Code: 0x") + string_q::FromIntegerToHexadecimal(info.Code) + "\n");
    QE_LOG(string_q("TimePressed: ") + info.TimePressed.GetMilliseconds() + "\n");
    QE_LOG(string_q("Timestamp: ") + info.Timestamp.GetMilliseconds() + "\n");
    QE_LOG(string_q("TimeElapsedSinceLastEvent: ") + info.TimeElapsedSinceLastEvent.GetMilliseconds() + "\n");

    if (info.HasCharacter)
    {
        QE_LOG(string_q("Character: ") + info.Character + "\n");
    }*/
}

void OnKeyKept(const QKeyboard* pKeyboard, const QKeyboard::KeyInfo &info)
{
    const float_q SPEED = 0.1f;

    if (info.Code == QKeyboard::E_LEFT)
    {
        QE_CAMERA->Move(QVector3(-ANIMATION_TIMER.GetElapsedTimeAsFloat() * SPEED, 0, 0));
    }
    else if (info.Code == QKeyboard::E_RIGHT)
    {
        QE_CAMERA->Move(QVector3(ANIMATION_TIMER.GetElapsedTimeAsFloat() * SPEED, 0, 0));
    }
    else if (info.Code == QKeyboard::E_UP)
    {
        QE_CAMERA->Move(QVector3(0, 0, ANIMATION_TIMER.GetElapsedTimeAsFloat() * SPEED));
    }
    else if (info.Code == QKeyboard::E_DOWN)
    {
        QE_CAMERA->Move(QVector3(0, 0, -ANIMATION_TIMER.GetElapsedTimeAsFloat() * SPEED));
    }
    else if (info.Code == QKeyboard::E_Z)
    {
        QE_CAMERA->RotateYaw(-SQAngle::_QuarterPi * ANIMATION_TIMER.GetElapsedTimeAsFloat());
    }
    else if (info.Code == QKeyboard::E_X)
    {
        QE_CAMERA->RotateYaw(SQAngle::_QuarterPi * ANIMATION_TIMER.GetElapsedTimeAsFloat());
    }
    else if (info.Code == QKeyboard::E_D)
    {
        QE_CAMERA->Move(QVector3(0, ANIMATION_TIMER.GetElapsedTimeAsFloat() * SPEED, 0));
    }
    else if (info.Code == QKeyboard::E_C)
    {
        QE_CAMERA->Move(QVector3(0, -ANIMATION_TIMER.GetElapsedTimeAsFloat() * SPEED, 0));
    }

    /*QE_LOG("KEY KEPT\n");
    QE_LOG(string_q("Code: 0x") + string_q::FromIntegerToHexadecimal(info.Code) + "\n");
    QE_LOG(string_q("TimePressed: ") + info.TimePressed.GetMilliseconds() + "\n");
    QE_LOG(string_q("Timestamp: ") + info.Timestamp.GetMilliseconds() + "\n");
    QE_LOG(string_q("TimeElapsedSinceLastEvent: ") + info.TimeElapsedSinceLastEvent.GetMilliseconds() + "\n");

    if (info.HasCharacter)
    {
        QE_LOG(string_q("Character: ") + info.Character + "\n");
    }*/
}

void OnKeyReleased(const QKeyboard* pKeyboard, const QKeyboard::KeyInfo &info)
{
    /*QE_LOG("KEY RELEASED\n");
    QE_LOG(string_q("Code: 0x") + string_q::FromIntegerToHexadecimal(info.Code) + "\n");
    QE_LOG(string_q("TimePressed: ") + info.TimePressed.GetMilliseconds() + "\n");
    QE_LOG(string_q("Timestamp: ") + info.Timestamp.GetMilliseconds() + "\n");
    QE_LOG(string_q("TimeElapsedSinceLastEvent: ") + info.TimeElapsedSinceLastEvent.GetMilliseconds() + "\n");*/
}