
#ifndef __QWINDOW__
#define __QWINDOW__

#include "QuimeraEngineIncludesAndUsings.h"
#include "QDeviceContext.h"

using Kinesis::QuimeraEngine::Common::QDelegate;

class QWindow
{
public:

#ifdef QE_OS_WINDOWS
    typedef WNDPROC MessageDispatcherFunction;
    typedef HINSTANCE ProcessInstanceHandle;
    typedef HWND WindowHandle;
#else
    Error: Operating system not supported
#endif

    QWindow(const ProcessInstanceHandle handle);
    ~QWindow();

    void Show();

    QDeviceContext& GetDeviceContext() const;

    WindowHandle GetHandle() const;
    ProcessInstanceHandle GetInstanceHandle() const;

    unsigned int GetWidth() const;
    void SetWidth(const unsigned int uWidth);

    unsigned int GetHeight() const;
    void SetHeight(const unsigned int uHeight);

    unsigned int GetPositionX() const;
    void SetPositionX(const unsigned int uPosition);

    unsigned int GetPositionY() const;
    void SetPositionY(const unsigned int uPosition);

    MessageDispatcherFunction GetMessageDispatcher() const;
    void SetMessageDispatcher(const MessageDispatcherFunction &messageDispatcher);

    string_q GetTitle() const;
    void SetTitle(const string_q &strTitle);

protected:

    void _Initialize();

protected:

    unsigned int m_uPositionX;
    unsigned int m_uPositionY;
    unsigned int m_uWidth;
    unsigned int m_uHeight;
    MessageDispatcherFunction m_messageDispatcher;
    string_q m_strTitle;
    WindowHandle m_windowHandle;
    const ProcessInstanceHandle m_processInstanceHandle;
    mutable QDeviceContext m_deviceContext;

};

#endif // __QWINDOW__