
#include "QDeviceContext.h"
#include "QuimeraEngineIncludesAndUsings.h"
#include "ErrorTracingDefinitions.h"
#include "GL/glew.h"
#include "GL/wglew.h"

QDeviceContext::QDeviceContext(const NativeDeviceContext nativeDeviceContext) : m_deviceContext(nativeDeviceContext),
                                                                                m_ePixelFormat(EQPixelFormat::E_Undefined),
                                                                                m_uMultisamplingSamples(0)
{
}

QDeviceContext::NativeDeviceContext QDeviceContext::GetNativeDeviceContext() const
{
    return m_deviceContext;
}

void QDeviceContext::SetNativeDeviceContext(const NativeDeviceContext deviceContext)
{
    m_deviceContext = deviceContext;
}

EQPixelFormat::EnumType QDeviceContext::GetPixelFormat() const
{
    return m_ePixelFormat;
}

void QDeviceContext::SetMultisamplingSamples(const u32_q uSampleCount)
{
    m_uMultisamplingSamples = uSampleCount;
}

u32_q QDeviceContext::GetMultisamplingSamples() const
{
    return m_uMultisamplingSamples;
}

void QDeviceContext::GetNativePixelFormatInfo(void* pPixelFormat) const
{
    QE_ASSERT_ERROR(m_deviceContext != null_q, "The device context must not be null.");

#ifdef QE_OS_WINDOWS
    int nPixelFormat = ::GetPixelFormat(m_deviceContext);

    QE_ASSERT_ERROR(nPixelFormat != 0, "An error occurred when attempting to get the native pixel format (GetPixelFormat).");

    int nResult = ::DescribePixelFormat(m_deviceContext, nPixelFormat, sizeof(::PIXELFORMATDESCRIPTOR), rcast_q(pPixelFormat, ::PIXELFORMATDESCRIPTOR*));

    QE_ASSERT_ERROR(nResult != 0, "An error occurred when attempting to get the native pixel format (DescribePixelFormat).");

#endif
}