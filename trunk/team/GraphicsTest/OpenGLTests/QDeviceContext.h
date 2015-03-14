
#ifndef __QDEVICECONTEXT__
#define __QDEVICECONTEXT__

#include "QuimeraEngineIncludesAndUsings.h"
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

    enum EQPixelFormat
    {
        E_R8G8B8A8D24S8,
        E_R8G8B8A8D32,
        E_R32G32B32A32,
        E_A8B8G8R8,
        E_R8G8B8A8,
        E_Undefined
    };

public:

    QDeviceContext(const NativeDeviceContext deviceContext);

    NativeRenderingContext CreateRenderingContext();

    NativeRenderingContext CreateAdvancedRenderingContext(const QDeviceContext::EQPixelFormat ePixelFormat, const bool bDebug);

    void MakeRenderingContextCurrent() const;

    void ResetCurrentRenderingContext() const;

    void DeleteRenderingContext();

    void DeleteRenderingContext(QDeviceContext::NativeRenderingContext renderingContext) const;

    void SwapBuffers() const;
    
protected:

#ifdef QE_OS_WINDOWS

    static void _GeneratePixelFormatDescriptorFromEnum(const QDeviceContext::EQPixelFormat ePixelFormat, PIXELFORMATDESCRIPTOR& descriptor);
    static QArrayBasic<const int> _GeneratePixelFormatAttributeListFromEnum(const QDeviceContext::EQPixelFormat ePixelFormat);

#endif

public:

    NativeRenderingContext GetCurrentRenderingContext() const;

    NativeDeviceContext GetNativeDeviceContext() const;
    void SetNativeDeviceContext(const NativeDeviceContext deviceContext);

    void SetPixelFormat(const EQPixelFormat eFormat);
    EQPixelFormat GetPixelFormat() const;

    void GetNativePixelFormatInfo(void* pPixelFormat) const;

private:

    NativeDeviceContext m_deviceContext;
    NativeRenderingContext m_renderingContext;
    EQPixelFormat m_ePixelFormat;

};


#endif // __QDEVICECONTEXT__