
#include "QWindow.h"

#include "SQSystemManager.h"

QWindow::QWindow(const ProcessInstanceHandle handle, const QWindow::QWindowSettings& settings) : 
                                                                                       m_windowHandle(null_q),
                                                                                       m_processInstanceHandle(handle),
                                                                                       m_pDeviceContext(null_q)
{
    // Width and Height are calculated inside _CreateWindow
    m_windowHandle = QWindow::_CreateWindow(settings, handle, this);
    m_pDeviceContext = QWindow::_SetUpDeviceContext(settings, ::GetDC(m_windowHandle));
    m_eStatus = QWindow::E_Restored;
    m_bMinimizeWhenFullscreenAndDeactivated = false;

    m_settings.IsFullscreen = false;

    if (settings.IsFullscreen)
        this->SetFullscreen();

    this->SetTitle(settings.Title);
    m_settings.Top = settings.Top;
    m_settings.Left = settings.Left;
    m_settings.ColorBufferFormat = settings.ColorBufferFormat;
    m_settings.DepthBufferFormat = settings.DepthBufferFormat;
    m_settings.StencilBufferFormat = settings.StencilBufferFormat;
    m_settings.Samples = settings.Samples;
}

QWindow::~QWindow()
{
#ifdef QE_OS_WINDOWS

    if (m_windowHandle)
    {
        delete m_pDeviceContext;

        wchar_t szClassName[256];
        ::RealGetWindowClass(m_windowHandle, szClassName, 256);
        
        ::DestroyWindow(m_windowHandle);

        BOOL bResult = ::UnregisterClass(szClassName, m_processInstanceHandle);
        
        QE_ASSERT_WINDOWS_ERROR("LOG: An error occurred when destroying the window.");
    }

#endif
}

void QWindow::Show()
{
#ifdef QE_OS_WINDOWS

    QWindow::_SetUpDeviceContext(m_settings, ::GetDC(m_windowHandle));

    ::ShowWindow(m_windowHandle, SW_SHOW);
    ::UpdateWindow(m_windowHandle);

#endif
}

QWindow::WindowHandle QWindow::_CreateWindow(const QWindowSettings &settings, const ProcessInstanceHandle instanceHandle, QWindow* pWindow)
{
    QE_ASSERT_ERROR(instanceHandle != null_q, "The process instance handle must not be null.");

#ifdef QE_OS_WINDOWS

    WNDCLASSEX windowClass;

    windowClass.cbSize = sizeof(WNDCLASSEX);

    windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    windowClass.lpfnWndProc = &QWindow::_WndProc;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = instanceHandle;
    windowClass.hIcon = null_q;
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    windowClass.lpszMenuName = null_q;

    static u32_q uWindowCounter = 0;
    string_q strClassName = string_q::FromIntegerToHexadecimal(instanceHandle) + uWindowCounter;
    ++uWindowCounter;

    QArrayResult<i8_q> className = strClassName.ToBytes(EQTextEncoding::E_UTF16LE);

    windowClass.lpszClassName = rcast_q(className.Get(), wchar_t*);
    windowClass.hIconSm = null_q;

    ATOM result = ::RegisterClassEx(&windowClass);

    QE_ASSERT_WINDOWS_ERROR("Failed to register the window class (RegisterClassEx)");
    QE_ASSERT_ERROR(result != 0, "Failed to register the window class (RegisterClassEx)");

    QArrayResult<i8_q> title = settings.Title.ToBytes(EQTextEncoding::E_UTF16);
    title.Detach();

    const DWORD STYLE_FLAGS = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS; // WS_OVERLAPPEDWINDOW already includes  WS_CAPTION | WS_THICKFRAME;
    RECT adjustedWindorRect = {0, 0, settings.ClientAreaWidth, settings.ClientAreaHeight};
    ::AdjustWindowRect(&adjustedWindorRect, STYLE_FLAGS, FALSE);
    
    HWND windowHandle = ::CreateWindow(windowClass.lpszClassName,
                                       NULL, STYLE_FLAGS,
                                       settings.Top, settings.Left,
                                       adjustedWindorRect.right - adjustedWindorRect.left, adjustedWindorRect.bottom - adjustedWindorRect.top,
                                       NULL, NULL, instanceHandle, NULL);

    QE_ASSERT_ERROR(windowHandle, "Failed to create a window handle (CreateWindow).");

    ::SetWindowLong(windowHandle, GWL_USERDATA, rcast_q(pWindow, pointer_uint_q));

    pWindow->m_settings.ClientAreaWidth  = settings.ClientAreaWidth;
    pWindow->m_settings.ClientAreaHeight = settings.ClientAreaHeight;
    pWindow->m_uWindowedClientAreaWidth  = settings.ClientAreaWidth;
    pWindow->m_uWindowedClientAreaHeight = settings.ClientAreaHeight;
    pWindow->m_uWindowedWidth = adjustedWindorRect.right - adjustedWindorRect.left;
    pWindow->m_uWindowedHeight = adjustedWindorRect.bottom - adjustedWindorRect.top;
    pWindow->m_uWidth = adjustedWindorRect.right - adjustedWindorRect.left;
    pWindow->m_uHeight = adjustedWindorRect.bottom - adjustedWindorRect.top;

#endif

    return windowHandle;
}

QDeviceContext* QWindow::_SetUpDeviceContext(const QWindowSettings &settings, const QDeviceContext::NativeDeviceContext deviceContextHandle)
{
#ifdef QE_OS_WINDOWS
    QDeviceContext* pDeviceContext = new QDeviceContext(deviceContextHandle);
#endif

    return pDeviceContext;
}

LRESULT CALLBACK QWindow::_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    PAINTSTRUCT ps;
    HDC hdc;
    wchar_t msg[32];

    QWindow* pWindow = (QWindow*) ::GetWindowLong(hWnd, GWL_USERDATA);

    if(pWindow)
        pWindow->BeforeOSMessageReceived.Raise(pWindow, message, wParam, lParam);
    
    switch (message)
    {
    case WM_GETMINMAXINFO:
        QE_LOG("LOG: Calculating first window size (WM_GETMINMAXINFO)\n");
        result = 0;
        break;
    case WM_NCCREATE:
        QE_LOG("LOG: Creating window (WM_NCCREATE)\n");
        result = TRUE;
        break;
    case WM_NCCALCSIZE:
        QE_LOG("LOG: Calculating first window size (WM_NCCALCSIZE)\n");
        result = DefWindowProc(hWnd, message, wParam, lParam);
        break;
    case WM_NCDESTROY:
        QE_LOG("LOG: Destroying window (WM_NCDESTROY)\n");
        result = 0;
        break;
    case WM_CREATE:
        QE_LOG("LOG: Creating window (WM_CREATE)\n");
        result = 0;
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code here...
        EndPaint(hWnd, &ps);
        break;
    case WM_ACTIVATEAPP:
    {
        QE_LOG("LOG: Deactivating window (WM_ACTIVATEAPP)\n");

        break;
    }
    case WM_ACTIVATE:
    {
        QE_LOG("LOG: Activating window (WM_ACTIVATE)\n");

        break;
    }
    case WM_NCACTIVATE:
    {
        BOOL bActivate = (BOOL)wParam;

        QE_LOG(string_q("LOG: Activating/deactivating window (WM_NCACTIVATE): ") + (bool)bActivate + "\n");

        if (!bActivate && pWindow->IsFullscreen() && pWindow->m_bMinimizeWhenFullscreenAndDeactivated)
        {
            pWindow->SetWindowStatus(E_Minimized);
        }

        result = TRUE;
        break;
    }
    case WM_SIZE:
    {
        QSizeChangedEventData eventArgs;
        eventArgs.NewClientAreaWidth = LOWORD(lParam);
        eventArgs.NewClientAreaHeight = HIWORD(lParam);
        const pointer_uint_q RESIZE_TYPE = wParam;

        if (RESIZE_TYPE == SIZE_MAXIMIZED)
            pWindow->m_eStatus = QWindow::E_Maximized;
        else if (RESIZE_TYPE == SIZE_MINIMIZED)
            pWindow->m_eStatus = QWindow::E_Minimized;
        else if (RESIZE_TYPE == SIZE_RESTORED)
            pWindow->m_eStatus = QWindow::E_Restored;
        
        eventArgs.WindowStatus = pWindow->m_eStatus;

        QE_LOG(string_q("LOG: Resizing window (WM_SIZE): Old(") + pWindow->GetWidth() + ", " + pWindow->GetHeight() + ") --> New(" + eventArgs.NewClientAreaWidth + ", " + eventArgs.NewClientAreaHeight + ")\n");

        eventArgs.OldClientAreaWidth = pWindow->GetClientAreaWidth();
        eventArgs.OldClientAreaHeight = pWindow->GetClientAreaHeight();
        pWindow->SizeChanged.Raise(pWindow, eventArgs);
        pWindow->m_settings.ClientAreaWidth = eventArgs.NewClientAreaWidth;
        pWindow->m_settings.ClientAreaHeight = eventArgs.NewClientAreaHeight;

        RECT adjustedWindorRect = { 0, 0, pWindow->m_settings.ClientAreaWidth, pWindow->m_settings.ClientAreaHeight };
        const LONG STYLE_FLAGS = ::GetWindowLong(pWindow->m_windowHandle, GWL_STYLE);
        ::AdjustWindowRect(&adjustedWindorRect, STYLE_FLAGS, FALSE);
        pWindow->m_uWidth = adjustedWindorRect.right - adjustedWindorRect.left;
        pWindow->m_uHeight = adjustedWindorRect.bottom - adjustedWindorRect.top;

        result = 0;
        break;
    }
    case WM_MOVE:
    {
        QPositionChangedEventData eventArgs;
        eventArgs.NewLeft = LOWORD(lParam);
        eventArgs.NewTop = HIWORD(lParam);
        eventArgs.OldLeft = pWindow->GetLeft();
        eventArgs.OldTop = pWindow->GetTop();

        QE_LOG(string_q("LOG: Moving window (WM_MOVE): Old(") + eventArgs.OldLeft + ", " + eventArgs.OldTop + ") --> New(" + eventArgs.NewLeft + ", " + eventArgs.NewTop + ")\n");

        pWindow->PositionChanged.Raise(pWindow, eventArgs); // Uses event args structure, it's more readable sin its members are known, whilst the signature of the event does not show the name of the parameters and the user cannnot know their meaning
        pWindow->m_settings.Left = eventArgs.NewLeft;
        pWindow->m_settings.Top = eventArgs.NewTop;

        result = 0;
        break;
    }
    case WM_DESTROY:
        QE_LOG("LOG: Destroying window (WM_DESTROY)\n");
        result = 0;
        PostQuitMessage(0);
        break;
    default:
        result = DefWindowProc(hWnd, message, wParam, lParam);
    }

    if (pWindow)
        pWindow->AfterOSMessageReceived.Raise(pWindow, message, wParam, lParam);

    return result;
}

bool QWindow::IsFullscreen() const
{
    return m_settings.IsFullscreen;
}

void QWindow::SetFullscreen()
{
    if (!m_settings.IsFullscreen)
    {
        m_settings.IsFullscreen = true;
        m_windowedPosition.x = this->GetLeft();
        m_windowedPosition.y = this->GetTop();
        m_uWindowedWidth = this->GetWidth();
        m_uWindowedHeight = this->GetHeight(); 
        m_uWindowedClientAreaWidth = this->GetClientAreaWidth();
        m_uWindowedClientAreaHeight = this->GetClientAreaHeight();

        LONG windowStyle = ::GetWindowLong(m_windowHandle, GWL_STYLE);
        ::SetWindowLong(m_windowHandle, GWL_STYLE, windowStyle & ~(WS_CAPTION |     // Title bar
                                                                   WS_THICKFRAME)); // Sizing border

        LONG windowStyleEx = ::GetWindowLong(m_windowHandle, GWL_EXSTYLE);
        ::SetWindowLong(m_windowHandle, GWL_EXSTYLE, windowStyleEx & ~(WS_EX_DLGMODALFRAME | // Double border
                                                                       WS_EX_WINDOWEDGE |    // Border with raised edge
                                                                       WS_EX_CLIENTEDGE |    // Border with sunken edge
                                                                       WS_EX_STATICEDGE));   // 3D border

        SQSystemManager::QScreenInfo screenInfo = SQSystemManager::GetWindowScreen(this);
        ::SetWindowPos( m_windowHandle, NULL,
                        0, 0,
                        screenInfo.Width, screenInfo.Height,
                        SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
    }
}

void QWindow::SetWindowed()
{
    if (m_settings.IsFullscreen)
    {
        m_settings.IsFullscreen = false;

        LONG windowStyle = ::GetWindowLong(m_windowHandle, GWL_STYLE);
        ::SetWindowLong(m_windowHandle, GWL_STYLE, windowStyle | (WS_CAPTION | WS_THICKFRAME));

        LONG windowStyleEx = ::GetWindowLong(m_windowHandle, GWL_EXSTYLE);
        ::SetWindowLong(m_windowHandle, GWL_EXSTYLE, windowStyleEx | (/*WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE |*/ WS_EX_STATICEDGE));

        ::SetWindowPos( m_windowHandle, NULL,
                        m_windowedPosition.x, m_windowedPosition.y,
                        m_uWindowedWidth, m_uWindowedHeight, // Client area or window rect?
                        SWP_NOZORDER |      // Retains Z order
                        SWP_NOACTIVATE |    // Window is not activated
                        SWP_FRAMECHANGED);  // Applies styles set with SetWindowLong. Sends WM_NCCALCSIZE

        this->SetWindowStatus(m_eStatus);
    }
}

QWindow::EQWindowStatus QWindow::GetWindowStatus() const
{
    return m_eStatus;
}

void QWindow::SetWindowStatus(const QWindow::EQWindowStatus eStatus)
{
    if (!m_settings.IsFullscreen || eStatus == E_Minimized)
    {
        switch (eStatus)
        {
        case E_Restored:
            ::SendMessage(m_windowHandle, WM_SYSCOMMAND, SC_RESTORE, 0);
            break;
        case E_Maximized:
            ::SendMessage(m_windowHandle, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
            break;
        case E_Minimized:
            ::SendMessage(m_windowHandle, WM_SYSCOMMAND, SC_MINIMIZE, 0);
            break;
        }

        m_eStatus = eStatus;
    }
}

QDeviceContext* QWindow::GetDeviceContext() const
{
    return m_pDeviceContext;
}

QWindow::WindowHandle QWindow::GetHandle() const
{
    return m_windowHandle;
}

QWindow::ProcessInstanceHandle QWindow::GetInstanceHandle() const
{
    return m_processInstanceHandle;
}

unsigned int QWindow::GetClientAreaWidth() const
{
    return m_settings.ClientAreaWidth;
}

unsigned int QWindow::GetClientAreaHeight() const
{
    return m_settings.ClientAreaHeight;
}

unsigned int QWindow::GetWidth() const
{
    return m_uWidth;
}

unsigned int QWindow::GetHeight() const
{
    return m_uHeight;
}

unsigned int QWindow::GetTop() const
{
    return m_settings.Top;
}

unsigned int QWindow::GetLeft() const
{
    return m_settings.Left;
}

string_q QWindow::GetTitle() const
{
    return m_settings.Title;
}

void QWindow::SetTitle(const string_q &strTitle)
{
    m_settings.Title = strTitle;
    QArrayResult<i8_q> szText = strTitle.ToBytes(EQTextEncoding::E_UTF16);
    ::SetWindowTextW(m_windowHandle, rcast_q(szText.Get(), wchar_t*));

    QE_ASSERT_WINDOWS_ERROR("LOG: Error when setting the title of the window (SetWindowTextW).");
}

void QWindow::SetMinimizationOnDeactivation(const bool bMinimize)
{
    m_bMinimizeWhenFullscreenAndDeactivated = bMinimize;
}