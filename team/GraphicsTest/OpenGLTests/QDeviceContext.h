
#ifndef __QDEVICECONTEXT__
#define __QDEVICECONTEXT__

#include "qe/InternalDefinitions.h"
#include <Windows.h>

class QDeviceContext
{
public:

#ifdef QE_OS_WINDOWS
    typedef HDC NativeDeviceContext;
    typedef HGLRC NativeRenderingContext;
#else
    Error: Operating system not supported
#endif

public:

    enum PixelFormat
    {
        E_R8G8B8A8D24S8,
        E_R8G8B8A8D32,
        E_R32G32B32A32,
        E_A8B8G8R8,
        E_R8G8B8A8
    };

public:

    QDeviceContext(const NativeDeviceContext deviceContext);

    NativeRenderingContext CreateRenderingContext() const;

    void MakeRenderingContextCurrent(const NativeRenderingContext renderingContext) const;

    void ResetCurrentRenderingContext() const;

    void DeleteRenderingContext(const NativeRenderingContext renderingContext) const;

    

public:

    NativeRenderingContext GetCurrentRenderingContext() const;

    NativeDeviceContext GetNativeDeviceContext() const;
    void SetNativeDeviceContext(const NativeDeviceContext deviceContext);

    void SetPixelFormat(const PixelFormat eFormat);
    void GetNativePixelFormatInfo(void* pPixelFormat) const;

private:

    NativeDeviceContext m_deviceContext;

};


#endif // __QDEVICECONTEXT__