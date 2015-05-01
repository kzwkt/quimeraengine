#ifndef __SQSYSTEMMANAGER__
#define __SQSYSTEMMANAGER__

#include "QuimeraEngineIncludesAndUsings.h"
#include "QWindow.h"

class SQSystemManager // [TODO]: Look for a better name
{
public:

    struct QScreenInfo
    {
        u32_q Width;
        u32_q Height;
    };


    static void ChangeScreenResolution()
    {
    }

    static QScreenInfo GetWindowScreen(QWindow* pWindow)
    {
        QScreenInfo info;

        MONITORINFO monitorInfo;
        monitorInfo.cbSize = sizeof(MONITORINFO);
        ::GetMonitorInfo(::MonitorFromWindow(pWindow->GetHandle(), MONITOR_DEFAULTTONEAREST), &monitorInfo);

        info.Width = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
        info.Height = monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;

        return info;
    }

    static void EnumerateScreens()
    {
    }

    static void EnumerateGraphicDevices()
    {
    }

    static void EnumerateAudioDevices()
    {
    }

    static void EnumerateInputPeripherals()
    {
    }
};

#endif // __SQSYSTEMMANAGER__