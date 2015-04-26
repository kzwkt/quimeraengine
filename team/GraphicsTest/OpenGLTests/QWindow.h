
#ifndef __QWINDOW__
#define __QWINDOW__

#include "QuimeraEngineIncludesAndUsings.h"
#include "QDeviceContext.h"
#include "ErrorTracingDefinitions.h"

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

    struct QWindowSettings
    {
        MessageDispatcherFunction MessageDispatcher;
        string_q Title;
        u32_q Width;
        u32_q Height;
        u32_q Top;
        u32_q Left;
        EQPixelFormat::EnumType ColorBufferFormat;
        EQPixelFormat::EnumType DepthBufferFormat;
        EQPixelFormat::EnumType StencilBufferFormat;
        u32_q Samples;
    };

    QWindow(const ProcessInstanceHandle handle, const QWindowSettings &settings);
    ~QWindow();

    void Show();

    QDeviceContext* GetDeviceContext() const;

    WindowHandle GetHandle() const;
    ProcessInstanceHandle GetInstanceHandle() const;

    unsigned int GetWidth() const;
    unsigned int GetHeight() const;

    unsigned int GetTop() const;
    unsigned int GetLeft() const;

    MessageDispatcherFunction GetMessageDispatcher() const;

    string_q GetTitle() const;

protected:

    static WindowHandle _CreateWindow(const QWindowSettings &settings, const ProcessInstanceHandle instanceHandle);

    static QDeviceContext* _SetUpDeviceContext(const QWindowSettings &settings, const QDeviceContext::NativeDeviceContext deviceContextHandle);

protected:

    QWindowSettings m_settings;
    WindowHandle m_windowHandle;
    const ProcessInstanceHandle m_processInstanceHandle;
    QDeviceContext* m_pDeviceContext;

};

#endif // __QWINDOW__