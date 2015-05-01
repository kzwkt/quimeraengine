
#ifndef __QWINDOW__
#define __QWINDOW__

#include "QuimeraEngineIncludesAndUsings.h"
#include "QDeviceContext.h"
#include "ErrorTracingDefinitions.h"
#include "QPoint.h"

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

    enum EQWindowStatus
    {
        E_Restored,
        E_Maximized,
        E_Minimized
    };

    struct QSizeChangedEventData
    {
        u32_q OldClientAreaWidth;
        u32_q OldClientAreaHeight;
        u32_q NewClientAreaWidth;
        u32_q NewClientAreaHeight;
        EQWindowStatus WindowStatus;
    };

    struct QPositionChangedEventData
    {
        u32_q OldLeft;
        u32_q OldTop;
        u32_q NewLeft;
        u32_q NewTop;
    };

    struct QWindowSettings
    {
        string_q Title;
        u32_q ClientAreaWidth; // Client area
        u32_q ClientAreaHeight; // Client area
        u32_q Top;
        u32_q Left;
        EQPixelFormat::EnumType ColorBufferFormat;
        EQPixelFormat::EnumType DepthBufferFormat;
        EQPixelFormat::EnumType StencilBufferFormat;
        u32_q Samples;
        bool IsFullscreen;
    };

    QWindow(const ProcessInstanceHandle handle, const QWindowSettings &settings);
    ~QWindow();

    void Show();

    QDeviceContext* GetDeviceContext() const;

    WindowHandle GetHandle() const;
    ProcessInstanceHandle GetInstanceHandle() const;

    unsigned int GetClientAreaWidth() const;
    unsigned int GetClientAreaHeight() const;
    unsigned int GetWidth() const;
    unsigned int GetHeight() const;

    unsigned int GetTop() const;
    unsigned int GetLeft() const;

    bool IsFullscreen() const;
    void SetFullscreen();
    void SetWindowed();

    void SetMinimizationOnDeactivation(const bool bMinimize);

    EQWindowStatus GetWindowStatus() const;
    void SetWindowStatus(const EQWindowStatus eStatus);

    MessageDispatcherFunction GetMessageDispatcher() const;

    string_q GetTitle() const;
    void SetTitle(const string_q &strTitle);

    QEvent<void(QWindow*, QSizeChangedEventData)> SizeChanged;
    QEvent<void(QWindow*, QPositionChangedEventData)> PositionChanged;
    QEvent<LRESULT(QWindow*, UINT, WPARAM, LPARAM)> BeforeOSMessageReceived;
    QEvent<LRESULT(QWindow*, UINT, WPARAM, LPARAM)> AfterOSMessageReceived;

protected:

    static WindowHandle _CreateWindow(const QWindowSettings &settings, const ProcessInstanceHandle instanceHandle, QWindow* pWindow);

    static QDeviceContext* _SetUpDeviceContext(const QWindowSettings &settings, const QDeviceContext::NativeDeviceContext deviceContextHandle);

    static LRESULT CALLBACK _WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

protected:

    QWindowSettings m_settings;
    EQWindowStatus m_eStatus;
    u32_q m_uWindowedClientAreaWidth;
    u32_q m_uWindowedClientAreaHeight;
    u32_q m_uWindowedWidth;
    u32_q m_uWindowedHeight;
    u32_q m_uWidth;
    u32_q m_uHeight;
    QPoint<u32_q> m_windowedPosition;
    WindowHandle m_windowHandle;
    const ProcessInstanceHandle m_processInstanceHandle;
    QDeviceContext* m_pDeviceContext;
    QPoint<u32_q> m_uClientAreaOrigin;
    bool m_bMinimizeWhenFullscreenAndDeactivated;
};

#endif // __QWINDOW__