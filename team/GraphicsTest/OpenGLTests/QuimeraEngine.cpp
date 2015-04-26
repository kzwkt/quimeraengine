
#include "QuimeraEngine.h"

bool QuimeraEngine::sm_bInitialized = false;
QuimeraEngine* QuimeraEngine::sm_pQuimeraEngine = null_q;


void QuimeraEngine::Initilize(QDeviceContext* pDeviceContext)
{
    QE_ASSERT_ERROR(!sm_bInitialized, "Quimera Engine has been alredy initialized.");

    sm_pQuimeraEngine = new QuimeraEngine();

    sm_pQuimeraEngine->Resources = QuimeraEngine::_CreateResourceManager();
    sm_pQuimeraEngine->Graphics = QuimeraEngine::_CreateGraphicsEngine(pDeviceContext, sm_pQuimeraEngine->Resources);

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

QGraphicsEngine* QuimeraEngine::_CreateGraphicsEngine(QDeviceContext* pDeviceContext, QResourceManager* pResourceManager)
{
    QWindow::QWindowSettings windowSettings;
    windowSettings.MessageDispatcher = &DefWindowProc;
    windowSettings.Title = "TEMPORARY WINDOW";
    windowSettings.Width = 800;
    windowSettings.Height = 600;
    windowSettings.Top = 0;
    windowSettings.Left = 0;
    windowSettings.ColorBufferFormat = EQPixelFormat::E_RGBA8UI_Normalized;
    windowSettings.DepthBufferFormat = EQPixelFormat::E_D24S8;
    windowSettings.StencilBufferFormat = EQPixelFormat::E_D24S8;
    windowSettings.Samples = 4;

    QWindow* pFakeWindow = new QWindow(::GetModuleHandle(NULL), windowSettings);

    QGraphicsEngine* pGraphicsEngine = new QGraphicsEngine(pResourceManager, pFakeWindow->GetDeviceContext());

    pGraphicsEngine->RegisterDeviceContext("MainWindowDC", pDeviceContext);

    pDeviceContext->SetPixelFormat(windowSettings.ColorBufferFormat, windowSettings.DepthBufferFormat, windowSettings.StencilBufferFormat, windowSettings.Samples);

    pGraphicsEngine->CreateRenderingContext("MainWindowRC", "MainWindowDC", true);

    pGraphicsEngine->UnregisterDeviceContext("FAKE");
    delete pFakeWindow;

    return pGraphicsEngine;
}

QResourceManager* QuimeraEngine::_CreateResourceManager()
{
    return new QResourceManager(new QShaderCompositor());
}