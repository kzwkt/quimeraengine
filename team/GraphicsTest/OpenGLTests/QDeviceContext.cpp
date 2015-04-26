
#include "QDeviceContext.h"
#include "QuimeraEngineIncludesAndUsings.h"
#include "ErrorTracingDefinitions.h"
#include "QPixelFormatDescriptor.h"
#include "GL/glew.h"
#include "GL/wglew.h"

QDeviceContext::QDeviceContext(const NativeDeviceContext nativeDeviceContext) : m_deviceContext(nativeDeviceContext),
                                                                                m_eColorBufferFormat(EQPixelFormat::E_Undefined),
                                                                                m_eDepthBufferFormat(EQPixelFormat::E_Undefined),
                                                                                m_eStencilBufferFormat(EQPixelFormat::E_Undefined),
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

EQPixelFormat::EnumType QDeviceContext::GetColorBufferFormat() const
{
    return m_eColorBufferFormat;
}

EQPixelFormat::EnumType QDeviceContext::GetDepthBufferFormat() const
{
    return m_eDepthBufferFormat;
}

EQPixelFormat::EnumType QDeviceContext::GetStencilBufferFormat() const
{
    return m_eStencilBufferFormat;
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

// [TODO]: Divide EQPixelFormat into 3: color, depth and stencil?
void QDeviceContext::_GeneratePixelFormatAttributeListFromEnum(const EQPixelFormat::EnumType eColorBuffersFormat, const EQPixelFormat::EnumType eDepthBufferFormat, const EQPixelFormat::EnumType eStencilBufferFormat, const u32_q uSamples, int arAttributes[38])
{
    QPixelFormatDescriptor pixelFormatDescriptorColorBuffer(eColorBuffersFormat);
    QPixelFormatDescriptor pixelFormatDescriptorDepthBuffer(eDepthBufferFormat);
    QPixelFormatDescriptor pixelFormatDescriptorStencilBuffer(eStencilBufferFormat);

    unsigned int i = 0;
    arAttributes[i++] = WGL_DRAW_TO_WINDOW_ARB;     arAttributes[i++] = GL_TRUE;
    arAttributes[i++] = WGL_ACCELERATION_ARB;       arAttributes[i++] = WGL_FULL_ACCELERATION_ARB;
    arAttributes[i++] = WGL_SUPPORT_OPENGL_ARB;     arAttributes[i++] = GL_TRUE;
    arAttributes[i++] = WGL_DOUBLE_BUFFER_ARB;      arAttributes[i++] = GL_TRUE;
    arAttributes[i++] = WGL_PIXEL_TYPE_ARB;         arAttributes[i++] = WGL_TYPE_RGBA_ARB;
    arAttributes[i++] = WGL_COLOR_BITS_ARB;         arAttributes[i++] = 32;
    arAttributes[i++] = WGL_RED_BITS_ARB;           arAttributes[i++] = pixelFormatDescriptorColorBuffer.r;
    arAttributes[i++] = WGL_RED_SHIFT_ARB;          arAttributes[i++] = 24;
    arAttributes[i++] = WGL_GREEN_BITS_ARB;         arAttributes[i++] = pixelFormatDescriptorColorBuffer.g;
    arAttributes[i++] = WGL_GREEN_SHIFT_ARB;        arAttributes[i++] = 16;
    arAttributes[i++] = WGL_BLUE_BITS_ARB;          arAttributes[i++] = pixelFormatDescriptorColorBuffer.b;
    arAttributes[i++] = WGL_BLUE_SHIFT_ARB;         arAttributes[i++] = 8;
    arAttributes[i++] = WGL_ALPHA_BITS_ARB;         arAttributes[i++] = pixelFormatDescriptorColorBuffer.a;
    arAttributes[i++] = WGL_ALPHA_SHIFT_ARB;        arAttributes[i++] = 0;
    arAttributes[i++] = WGL_DEPTH_BITS_ARB;         arAttributes[i++] = pixelFormatDescriptorDepthBuffer.d;
    arAttributes[i++] = WGL_STENCIL_BITS_ARB;       arAttributes[i++] = pixelFormatDescriptorStencilBuffer.s;
    arAttributes[i++] = WGL_SAMPLE_BUFFERS_ARB;     arAttributes[i++] = uSamples > 0 ? GL_TRUE : GL_FALSE;
    arAttributes[i++] = WGL_SAMPLES_ARB;            arAttributes[i++] = uSamples;
    arAttributes[i++] = 0;                          arAttributes[i++] = 0;
}