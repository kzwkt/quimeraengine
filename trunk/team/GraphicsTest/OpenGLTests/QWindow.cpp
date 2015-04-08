
#include "QWindow.h"

QWindow::QWindow(const ProcessInstanceHandle handle, const QWindow::QWindowSettings& settings) : 
                                                                                       m_windowHandle(null_q),
                                                                                       m_processInstanceHandle(handle),
                                                                                       m_pDeviceContext(null_q)
{
    m_windowHandle = QWindow::_CreateWindow(settings, handle);
    m_pDeviceContext = QWindow::_SetUpDeviceContext(settings, ::GetDC(m_windowHandle));

    m_settings.MessageDispatcher = settings.MessageDispatcher;
    m_settings.Title = settings.Title;
    m_settings.Top = settings.Top;
    m_settings.Left = settings.Left;
    m_settings.Width = settings.Width;
    m_settings.Height = settings.Height;
    m_settings.PixelFormat = settings.PixelFormat;
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

QWindow::WindowHandle QWindow::_CreateWindow(const QWindowSettings &settings, const ProcessInstanceHandle instanceHandle)
{
    QE_ASSERT_ERROR(settings.MessageDispatcher != null_q, "The message dispatcher must not be null.");
    QE_ASSERT_ERROR(instanceHandle != null_q, "The process instance handle must not be null.");

#ifdef QE_OS_WINDOWS

    WNDCLASSEX windowClass;

    windowClass.cbSize = sizeof(WNDCLASSEX);

    windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    windowClass.lpfnWndProc = settings.MessageDispatcher;
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
    className.Detach();

    windowClass.lpszClassName = rcast_q(className.Get(), wchar_t*);
    windowClass.hIconSm = null_q;

    ATOM result = ::RegisterClassEx(&windowClass);

    QE_ASSERT_WINDOWS_ERROR("Failed to register the window class (RegisterClassEx)");
    QE_ASSERT_ERROR(result != 0, "Failed to register the window class (RegisterClassEx)");

    QArrayResult<i8_q> title = settings.Title.ToBytes(EQTextEncoding::E_UTF16LE);
    title.Detach();

    HWND windowHandle = CreateWindow(windowClass.lpszClassName,
                                     rcast_q(title.Get(), wchar_t*), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                                     settings.Top, settings.Left,
                                     settings.Width, settings.Height,
                                     NULL, NULL, instanceHandle, NULL);
#endif

    QE_ASSERT_ERROR(windowHandle, "Failed to create a window handle (CreateWindow).");

    return windowHandle;
}

QDeviceContext* QWindow::_SetUpDeviceContext(const QWindowSettings &settings, const QDeviceContext::NativeDeviceContext deviceContextHandle)
{
#ifdef QE_OS_WINDOWS
    QDeviceContext* pDeviceContext = new QDeviceContext(deviceContextHandle);
#endif

    return pDeviceContext;
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

unsigned int QWindow::GetWidth() const
{
    return m_settings.Width;
}

unsigned int QWindow::GetHeight() const
{
    return m_settings.Height;
}

unsigned int QWindow::GetTop() const
{
    return m_settings.Top;
}


unsigned int QWindow::GetLeft() const
{
    return m_settings.Left;
}

QWindow::MessageDispatcherFunction QWindow::GetMessageDispatcher() const
{
    return m_settings.MessageDispatcher;
}

string_q QWindow::GetTitle() const
{
    return m_settings.Title;
}


