
#include "QDeviceContext.h"
#include "qe/Assertions.h"
#include "qe/StringsDefinitions.h"

QDeviceContext::QDeviceContext(const QDeviceContext::NativeDeviceContext deviceContext) : m_deviceContext(deviceContext)
{
}

QDeviceContext::NativeRenderingContext QDeviceContext::CreateRenderingContext() const
{
    QE_ASSERT_ERROR(m_deviceContext != null_q, "The device context must not be null.");

#ifdef QE_OS_WINDOWS

    HGLRC rc = ::wglCreateContext(m_deviceContext);

    QE_ASSERT_ERROR(rc != null_q, "The rendering context could not be created (wglCreateContext).");

    return rc;

#endif

}

void QDeviceContext::MakeRenderingContextCurrent(const QDeviceContext::NativeRenderingContext renderingContext) const
{
    QE_ASSERT_ERROR(m_deviceContext != null_q, "The device context must not be null.");

#ifdef QE_OS_WINDOWS

    BOOL bResult = ::wglMakeCurrent(m_deviceContext, renderingContext);

    QE_ASSERT_ERROR(bResult != 0, "The rendering context could not set as current (wglMakeCurrent).");

#endif
}

void QDeviceContext::ResetCurrentRenderingContext() const
{
#ifdef QE_OS_WINDOWS

    BOOL bResult = ::wglMakeCurrent(null_q, null_q);

    QE_ASSERT_ERROR(bResult != 0, "The current rendering context could not be nulled (wglMakeCurrent).");

#endif
}

void QDeviceContext::DeleteRenderingContext(const QDeviceContext::NativeRenderingContext renderingContext) const
{
#ifdef QE_OS_WINDOWS

    BOOL bResult = ::wglDeleteContext(renderingContext);

    QE_ASSERT_ERROR(bResult != 0, "The rendering context could not be deleted (wglDeleteContext).");

#endif
}



QDeviceContext::NativeRenderingContext QDeviceContext::GetCurrentRenderingContext() const
{
#ifdef QE_OS_WINDOWS

    HGLRC rc = ::wglGetCurrentContext();

    QE_ASSERT_ERROR(rc != null_q, "The rendering context could not be retrieved (wglGetCurrentContext).");

    return rc;

#endif
}

QDeviceContext::NativeDeviceContext QDeviceContext::GetNativeDeviceContext() const
{
    return m_deviceContext;
}

void QDeviceContext::SetNativeDeviceContext(const NativeDeviceContext deviceContext)
{
    m_deviceContext = deviceContext;
}

void QDeviceContext::SetPixelFormat(const QDeviceContext::PixelFormat eFormat)
{
    QE_ASSERT_ERROR(m_deviceContext != null_q, "The device context must not be null.");

#ifdef QE_OS_WINDOWS

    ::PIXELFORMATDESCRIPTOR pixelFormat;
    ::ZeroMemory(&pixelFormat, sizeof(::PIXELFORMATDESCRIPTOR));

    pixelFormat.nSize = sizeof(::PIXELFORMATDESCRIPTOR);
    pixelFormat.nVersion = 1;
    pixelFormat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_GENERIC_ACCELERATED | PFD_DOUBLEBUFFER;
    pixelFormat.iPixelType = PFD_TYPE_RGBA;

    switch(eFormat)
    {
    case QDeviceContext::E_A8B8G8R8:
        {
            pixelFormat.cColorBits = 24;
            pixelFormat.cRedBits = 8;
            pixelFormat.cRedShift = 0;
            pixelFormat.cGreenBits = 8;
            pixelFormat.cGreenShift = 8;
            pixelFormat.cBlueBits = 8;
            pixelFormat.cBlueShift = 16;
            pixelFormat.cAlphaBits = 8;
            pixelFormat.cAlphaShift = 24;
            pixelFormat.cDepthBits = 0;
            pixelFormat.cStencilBits = 0;
            break;
        }
    case QDeviceContext::E_R32G32B32A32:
        {
            pixelFormat.cColorBits = 96;
            pixelFormat.cRedBits = 32;
            pixelFormat.cRedShift = 96;
            pixelFormat.cGreenBits = 32;
            pixelFormat.cGreenShift = 64;
            pixelFormat.cBlueBits = 32;
            pixelFormat.cBlueShift = 32;
            pixelFormat.cAlphaBits = 32;
            pixelFormat.cAlphaShift = 0;
            pixelFormat.cDepthBits = 0;
            pixelFormat.cStencilBits = 0;
            break;
        }
    case QDeviceContext::E_R8G8B8A8:
        {
            pixelFormat.cColorBits = 24;
            pixelFormat.cRedBits = 8;
            pixelFormat.cRedShift = 24;
            pixelFormat.cGreenBits = 8;
            pixelFormat.cGreenShift = 16;
            pixelFormat.cBlueBits = 8;
            pixelFormat.cBlueShift = 8;
            pixelFormat.cAlphaBits = 8;
            pixelFormat.cAlphaShift = 0;
            pixelFormat.cDepthBits = 0;
            pixelFormat.cStencilBits = 0;
            break;
        }
    case QDeviceContext::E_R8G8B8A8D24S8:
        {
            pixelFormat.cColorBits = 24;
            pixelFormat.cRedBits = 8;
            pixelFormat.cRedShift = 24;
            pixelFormat.cGreenBits = 8;
            pixelFormat.cGreenShift = 16;
            pixelFormat.cBlueBits = 8;
            pixelFormat.cBlueShift = 8;
            pixelFormat.cAlphaBits = 8;
            pixelFormat.cAlphaShift = 0;
            pixelFormat.cDepthBits = 24;
            pixelFormat.cStencilBits = 8;
            break;
        }
    case QDeviceContext::E_R8G8B8A8D32:
        {
            pixelFormat.cColorBits = 24;
            pixelFormat.cRedBits = 8;
            pixelFormat.cRedShift = 24;
            pixelFormat.cGreenBits = 8;
            pixelFormat.cGreenShift = 16;
            pixelFormat.cBlueBits = 8;
            pixelFormat.cBlueShift = 8;
            pixelFormat.cAlphaBits = 8;
            pixelFormat.cAlphaShift = 0;
            pixelFormat.cDepthBits = 32;
            pixelFormat.cStencilBits = 0;
            break;
        }
    default:
        {
            QE_ASSERT_ERROR(false, "The pixel format is not supported.");
            break;
        }
    }

    // Accumulation buffers were deprected since OpenGL 3.0
    pixelFormat.cAccumBits;
    pixelFormat.cAccumRedBits;
    pixelFormat.cAccumGreenBits;
    pixelFormat.cAccumBlueBits;
    pixelFormat.cAccumAlphaBits;

    // Not used
    pixelFormat.cAuxBuffers;
    pixelFormat.iLayerType;
    pixelFormat.bReserved;

    // Ignored for now
    pixelFormat.dwLayerMask;
    pixelFormat.dwVisibleMask;
    pixelFormat.dwDamageMask;

    int nPixelFormat = ::ChoosePixelFormat(m_deviceContext, &pixelFormat);
    
    QE_ASSERT_ERROR(nPixelFormat != 0, "The pixel format could not be set (ChoosePixelFormat).");

    BOOL bResult = ::SetPixelFormat(m_deviceContext, nPixelFormat, &pixelFormat);

    QE_ASSERT_ERROR(bResult != 0, "The pixel format could not be set (SetPixelFormat).");

#endif
}

void QDeviceContext::GetNativePixelFormatInfo(void* pPixelFormat) const
{
    QE_ASSERT_ERROR(m_deviceContext != null_q, "The device context must not be null.");

#ifdef QE_OS_WINDOWS
    int nPixelFormat = ::GetPixelFormat(m_deviceContext);

    QE_ASSERT_ERROR(nPixelFormat != 0, "An error occurred when attempting to get the native pixel format (GetPixelFormat).");

    ::PIXELFORMATDESCRIPTOR pixelFormat;
    ::ZeroMemory(&pixelFormat, sizeof(::PIXELFORMATDESCRIPTOR));

    int nResult = ::DescribePixelFormat(m_deviceContext, nPixelFormat, sizeof(::PIXELFORMATDESCRIPTOR), rcast_q(pPixelFormat, ::PIXELFORMATDESCRIPTOR*));

    QE_ASSERT_ERROR(nResult != 0, "An error occurred when attempting to get the native pixel format (DescribePixelFormat).");

#endif
}