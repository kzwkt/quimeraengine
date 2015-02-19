
#include "QWindow.h"

QWindow::QWindow(const ProcessInstanceHandle handle) : m_uWidth(0),
                                                       m_uHeight(0),
                                                       m_uPositionX(0),
                                                       m_uPositionY(0),
                                                       m_messageDispatcher(null_q),
                                                       m_strTitle(string_q::GetEmpty()),
                                                       m_windowHandle(null_q),
                                                       m_processInstanceHandle(handle),
                                                       m_deviceContext(null_q)
{
}

QWindow::~QWindow()
{
#ifdef QE_OS_WINDOWS

    if(m_windowHandle)
        ::DestroyWindow(m_windowHandle);

#endif
}

void QWindow::Show()
{
    if(m_windowHandle == null_q)
        this->_Initialize();

#ifdef QE_OS_WINDOWS

    ::ShowWindow(m_windowHandle, SW_SHOW);
    ::UpdateWindow(m_windowHandle);

#endif
}

void QWindow::_Initialize()
{
    QE_ASSERT_ERROR(m_messageDispatcher != null_q, "The message dispatcher must not be null.");
    QE_ASSERT_ERROR(m_processInstanceHandle != null_q, "The process instance handle must not be null.");

#ifdef QE_OS_WINDOWS

    WNDCLASSEX windowClass;

	windowClass.cbSize = sizeof(WNDCLASSEX);

	windowClass.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    windowClass.lpfnWndProc	    = m_messageDispatcher;
	windowClass.cbClsExtra		= 0;
	windowClass.cbWndExtra		= 0;
	windowClass.hInstance		= m_processInstanceHandle;
	windowClass.hIcon			= null_q;
	windowClass.hCursor		    = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	windowClass.lpszMenuName	= null_q;

    QArrayResult<i8_q> className = string_q::FromIntegerToHexadecimal(m_processInstanceHandle).ToBytes(EQTextEncoding::E_UTF16LE);
    className.Detach();

    windowClass.lpszClassName	= rcast_q(className.Get(), wchar_t*);
	windowClass.hIconSm		    = null_q;

	ATOM result = ::RegisterClassEx(&windowClass);

    QE_ASSERT_ERROR(result != 0, "Failed to register the window class (RegisterClassEx)");

    QArrayResult<i8_q> title = m_strTitle.ToBytes(EQTextEncoding::E_UTF16LE); 
    title.Detach();

    m_windowHandle = CreateWindow(windowClass.lpszClassName, 
                                  rcast_q(title.Get(), wchar_t*), WS_OVERLAPPEDWINDOW,
                                  m_uPositionX, m_uPositionY, 
                                  m_uWidth, m_uHeight, 
                                  NULL, NULL, m_processInstanceHandle, NULL);
#endif

    QE_ASSERT_ERROR(m_windowHandle, "Failed to create a window handle (CreateWindow).");
}





QDeviceContext& QWindow::GetDeviceContext() const
{
    QE_ASSERT_ERROR(m_windowHandle != null_q, "The window handle must not be null.");

#ifdef QE_OS_WINDOWS
    if(m_deviceContext.GetNativeDeviceContext() == null_q)
        m_deviceContext = QDeviceContext(::GetDC(m_windowHandle));
#endif

    return m_deviceContext;
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
    return m_uWidth;
}

void QWindow::SetWidth(const unsigned int uWidth)
{
    m_uWidth = uWidth;
}

unsigned int QWindow::GetHeight() const
{
    return m_uHeight;
}

void QWindow::SetHeight(const unsigned int uHeight)
{
    m_uHeight = uHeight;
}

unsigned int QWindow::GetPositionX() const
{
    return m_uPositionX;
}

void QWindow::SetPositionX(const unsigned int uPosition)
{
    m_uPositionX = uPosition;
}

unsigned int QWindow::GetPositionY() const
{
    return m_uPositionY;
}

void QWindow::SetPositionY(const unsigned int uPosition)
{
    m_uPositionY = uPosition;
}

QWindow::MessageDispatcherFunction QWindow::GetMessageDispatcher() const
{
    return m_messageDispatcher;
}

void QWindow::SetMessageDispatcher(const QWindow::MessageDispatcherFunction &messageDispatcher)
{
    m_messageDispatcher = messageDispatcher;
}

string_q QWindow::GetTitle() const
{
    return m_strTitle;
}

void QWindow::SetTitle(const string_q &strTitle)
{
    m_strTitle = strTitle;
}

