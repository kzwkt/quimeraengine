
#include "QuimeraEngine.h"

bool QuimeraEngine::sm_bInitialized = false;
QuimeraEngine* QuimeraEngine::sm_pQuimeraEngine = null_q;


void QuimeraEngine::Initilize(const QGraphicsEngine::QGraphicsEngineSettings &graphicsEngineSettings)
{
    QE_ASSERT_ERROR(!sm_bInitialized, "Quimera Engine has been alredy initialized.");

    sm_pQuimeraEngine = new QuimeraEngine();

    sm_pQuimeraEngine->Resources = QuimeraEngine::_CreateResourceManager();
    sm_pQuimeraEngine->Graphics = QuimeraEngine::_CreateGraphicsEngine(graphicsEngineSettings, sm_pQuimeraEngine->Resources);

    sm_bInitialized = true;
}

bool QuimeraEngine::IsInitialized()
{
    return sm_bInitialized;
}

QuimeraEngine* QuimeraEngine::Get()
{
    return sm_pQuimeraEngine;
}

QGraphicsEngine* QuimeraEngine::_CreateGraphicsEngine(const QGraphicsEngine::QGraphicsEngineSettings &graphicsEngineSettings, QResourceManager* pResourceManager)
{
    QWindow::QWindowSettings windowSettings;
    windowSettings.Title = "TEMPORARY WINDOW";
    windowSettings.ClientAreaWidth = 800;
    windowSettings.ClientAreaHeight = 600;
    windowSettings.Top = 0;
    windowSettings.Left = 0;
    windowSettings.ColorBufferFormat = EQPixelFormat::E_RGBA8UI_Normalized;
    windowSettings.DepthBufferFormat = EQPixelFormat::E_D24S8;
    windowSettings.StencilBufferFormat = EQPixelFormat::E_D24S8;
    windowSettings.Samples = 0;
    windowSettings.IsFullscreen = false;

    QWindow* pFakeWindow = new QWindow(::GetModuleHandle(NULL), windowSettings);

    QGraphicsEngine* pGraphicsEngine = new QGraphicsEngine(graphicsEngineSettings, pFakeWindow->GetDeviceContext(), pResourceManager);

    pGraphicsEngine->RegisterDeviceContext("MainWindowDC", graphicsEngineSettings.DeviceContext);

    graphicsEngineSettings.DeviceContext->SetPixelFormat(graphicsEngineSettings.Framebuffer.ColorBufferFormat,
                                                         graphicsEngineSettings.Framebuffer.DepthBufferFormat, 
                                                         graphicsEngineSettings.Framebuffer.StencilBufferFormat, 
                                                         graphicsEngineSettings.Framebuffer.Samples);

    pGraphicsEngine->CreateRenderingContext("MainWindowRC", "MainWindowDC", true);

    pGraphicsEngine->UnregisterDeviceContext("FAKE");
    delete pFakeWindow;

    pGraphicsEngine->ResetDefaultState();

    if (graphicsEngineSettings.Framebuffer.Samples > 0)
        pGraphicsEngine->EnableMultisampling();

    return pGraphicsEngine;
}

QResourceManager* QuimeraEngine::_CreateResourceManager()
{
    return new QResourceManager(new QShaderCompositor());
}