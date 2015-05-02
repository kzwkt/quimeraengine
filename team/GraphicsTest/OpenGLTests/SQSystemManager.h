#ifndef __SQSYSTEMMANAGER__
#define __SQSYSTEMMANAGER__

#include "QuimeraEngineIncludesAndUsings.h"
#include "QWindow.h"

// [TODO]: Split this class among every component (peripherals, audio, graphics, etc.)
class SQSystemManager // [TODO]: Look for a better name
{
public:

    struct QScreenResolution
    {
        u32_q Width;
        u32_q Height;
    };

    struct QGraphicsDeviceInfo
    {
        string_q GraphicsDeviceId;
        string_q GraphicsDeviceName;
        bool IsPrimary;
    };
    
    static void ChangeScreenResolution(const QScreenResolution resolution, const u32_q uBitDepth)
    {
        DEVMODE settings;
        settings.dmSize = sizeof(DEVMODE);
        ::EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &settings);

        if (settings.dmPelsHeight != resolution.Height ||
            settings.dmPelsWidth != resolution.Width   ||
            settings.dmBitsPerPel != uBitDepth)
        {
            settings.dmPelsHeight = resolution.Height;
            settings.dmPelsWidth = resolution.Width;
            settings.dmBitsPerPel = uBitDepth;
            ::ChangeDisplaySettings(&settings, 0);
        }
    }

    static QScreenResolution GetWindowScreen(QWindow* pWindow)
    {
        QScreenResolution info;

        MONITORINFO monitorInfo;
        monitorInfo.cbSize = sizeof(MONITORINFO);
        ::GetMonitorInfo(::MonitorFromWindow(pWindow->GetHandle(), MONITOR_DEFAULTTONEAREST), &monitorInfo);

        info.Width = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
        info.Height = monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;

        return info;
    }

    static BOOL CALLBACK _EnumerateDisplayMonitorsCallback( _In_ HMONITOR hMonitor,
                                                            _In_ HDC hdcMonitor,
                                                            _In_ LPRECT lprcMonitor,
                                                            _In_ LPARAM dwData)
    {
        QE_LOG(string_q("- ") + u32_q(lprcMonitor->right - lprcMonitor->left) + "x" + u32_q(lprcMonitor->bottom - lprcMonitor->top) + "\n");
        return TRUE;
    }

    static void EnumerateScreens()
    {
        QE_LOG("Listing monitors:\n");
        ::EnumDisplayMonitors(NULL, NULL, &SQSystemManager::_EnumerateDisplayMonitorsCallback, 0);
    }

    static void EnumerateGraphicsDevices()
    {
        QE_LOG("Listing display devices:\n");

        PDISPLAY_DEVICE pDisplayDevice = new DISPLAY_DEVICE;
        pDisplayDevice->cb = sizeof(DISPLAY_DEVICE);

        QArrayDynamic<DISPLAY_DEVICE> arDevices(5);

        int i = 0;

        while (::EnumDisplayDevices(NULL, i, pDisplayDevice, EDD_GET_DEVICE_INTERFACE_NAME))
        {
            if (pDisplayDevice->StateFlags & DISPLAY_DEVICE_ACTIVE)
            {
                QE_LOG(string_q("- ") + string_q(pDisplayDevice->DeviceName) + "\n");
                QE_LOG(string_q("  ") + string_q(pDisplayDevice->DeviceString) + "\n");
                QE_LOG(string_q("  ") + string_q(pDisplayDevice->DeviceID) + "\n");
                QE_LOG(string_q("  ") + string_q(pDisplayDevice->DeviceKey) + "\n");
                arDevices.Add(*pDisplayDevice);
            }
            ++i;
        }

        delete pDisplayDevice;

        QE_LOG("\n");
        QE_LOG("Listing display settings:\n");

        i = 0;
        DEVMODE* pDisplaySettings = new DEVMODE;
        pDisplaySettings->dmSize = sizeof(DEVMODE);

        for (pointer_uint_q iDisplayDevice = 0; iDisplayDevice < arDevices.GetCount(); ++iDisplayDevice)
        {
            QE_LOG(string_q("Device: ") + string_q(arDevices[iDisplayDevice].DeviceName) + "\n");

            while (::EnumDisplaySettings(arDevices[iDisplayDevice].DeviceName, i, pDisplaySettings))
            {
                if (pDisplaySettings->dmBitsPerPel >= 32)
                {
                    QE_LOG(string_q("- ") + (u32_q)pDisplaySettings->dmPelsWidth + "x" + (u32_q)pDisplaySettings->dmPelsHeight + " - " + (u32_q)pDisplaySettings->dmBitsPerPel + " bits\n");
                }
                ++i;
            }
        }

        delete pDisplaySettings;

        // [TODO]: Remove repeated elements
    }

    static void EnumerateAudioDevices()
    {
    }

    static void EnumerateInputPeripherals()
    {
    }
};

#endif // __SQSYSTEMMANAGER__