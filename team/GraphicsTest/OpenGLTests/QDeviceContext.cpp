
#include "QDeviceContext.h"
#include "QuimeraEngineIncludesAndUsings.h"
#include "ErrorTracingDefinitions.h"
#include "GL/glew.h"
#include "GL/wglew.h"

QDeviceContext::QDeviceContext(const QDeviceContext::NativeDeviceContext deviceContext) : m_deviceContext(deviceContext),
                                                                                          m_renderingContext(null_q),
                                                                                          m_ePixelFormat(QDeviceContext::E_Undefined)
{
}

QDeviceContext::NativeRenderingContext QDeviceContext::CreateRenderingContext()
{
    QE_ASSERT_ERROR(m_deviceContext != null_q, "The device context must not be null.");

#ifdef QE_OS_WINDOWS

    m_renderingContext = ::wglCreateContext(m_deviceContext);

    QE_ASSERT_ERROR(m_renderingContext != null_q, "The rendering context could not be created (wglCreateContext).");
    QE_ASSERT_WINDOWS_ERROR("The rendering context could not be created (wglCreateContext).");

    return m_renderingContext;

#endif

}
#include "PrintSupportedPixelFormats.h"
QDeviceContext::NativeRenderingContext QDeviceContext::CreateAdvancedRenderingContext(const QDeviceContext::EQPixelFormat ePixelFormat, const bool bDebug)
{
    QE_LOG("LOG: Creating rendering context...\n"); 

    QE_ASSERT_ERROR(m_deviceContext != null_q, "The device context must not be null.");
    QE_ASSERT_ERROR(m_renderingContext != null_q, "The rendering context must not be null.");

#ifdef QE_OS_WINDOWS
    
    QArrayBasic<const int> arAttribs = QDeviceContext::_GeneratePixelFormatAttributeListFromEnum(ePixelFormat);

    const unsigned int MAX_DESIRED_FORMATS = 5;
    unsigned int nActualMatchingFormats = 0;
    int arMatchingFormatIndices[MAX_DESIRED_FORMATS];
    ::wglChoosePixelFormatARB(m_deviceContext, arAttribs.Get(), null_q, MAX_DESIRED_FORMATS, arMatchingFormatIndices, &nActualMatchingFormats);

    QE_LOG(string_q("LOG: Matching pixel formats: ") + nActualMatchingFormats + "\n");
    QE_ASSERT_ERROR(nActualMatchingFormats > 0, "There is no matching pixel format supported (wglChoosePixelFormatARB).");

    QE_LOG(string_q("LOG: Using pixel format: ") + arMatchingFormatIndices[0] + "\n");
    BOOL bResult = ::SetPixelFormat(m_deviceContext, arMatchingFormatIndices[0], null_q);
    //PrintPixelFormats(m_deviceContext);
    if(bResult == FALSE)
    {
        QE_ASSERT_WINDOWS_ERROR("Failed to set the pixel format when creating the rendering context (SetPixelFormat).");
    }
    
    int arContextAttributes[] = { WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
                                  WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
                                  WGL_CONTEXT_MINOR_VERSION_ARB, 3,
                                  WGL_CONTEXT_FLAGS_ARB, bDebug ? WGL_CONTEXT_DEBUG_BIT_ARB : 0,
                                  0};

    // [TODO]: Multiple rendering contexts? Sharing?
    m_renderingContext = ::wglCreateContextAttribsARB(m_deviceContext, null_q, arContextAttributes);

    if(m_renderingContext == null_q)
    {
        QE_ASSERT_WINDOWS_ERROR("Failed when attempring to create a custom rendering context (wglCreateContext).");
    }

    QE_LOG("LOG: OpenGL 4.0 Rendering context created.\n");

    return m_renderingContext;

#endif

}

void QDeviceContext::MakeRenderingContextCurrent() const
{
    QE_ASSERT_ERROR(m_deviceContext != null_q, "The device context must not be null.");
    QE_ASSERT_ERROR(m_renderingContext != null_q, "The rendering context must not be null.");

#ifdef QE_OS_WINDOWS

    BOOL bResult = ::wglMakeCurrent(m_deviceContext, m_renderingContext);

    QE_ASSERT_ERROR(bResult != 0, "The rendering context could not set as current (wglMakeCurrent).");

#endif
}

void QDeviceContext::ResetCurrentRenderingContext() const
{
    QE_ASSERT_ERROR(m_deviceContext != null_q, "The device context must not be null.");

#ifdef QE_OS_WINDOWS

    BOOL bResult = ::wglMakeCurrent(m_deviceContext, null_q);

    if(bResult == FALSE)
    {
        QE_ASSERT_WINDOWS_ERROR("The current rendering context could not be nulled (wglMakeCurrent).");
    }

#endif
}

void QDeviceContext::DeleteRenderingContext()
{
    QE_ASSERT_ERROR(m_renderingContext != null_q, "The rendering context must not be null.");

#ifdef QE_OS_WINDOWS

    BOOL bResult = ::wglDeleteContext(m_renderingContext);

    QE_ASSERT_ERROR(bResult != 0, "The rendering context could not be deleted (wglDeleteContext).");

    m_renderingContext = null_q;

#endif
}

void QDeviceContext::DeleteRenderingContext(QDeviceContext::NativeRenderingContext renderingContext) const
{
    QE_ASSERT_ERROR(renderingContext != null_q, "The rendering context must not be null.");

#ifdef QE_OS_WINDOWS

    BOOL bResult = ::wglDeleteContext(renderingContext);

    QE_ASSERT_ERROR(bResult != 0, "The rendering context could not be deleted (wglDeleteContext).");

    renderingContext = null_q;

#endif
}

void QDeviceContext::SwapBuffers() const
{
    QE_ASSERT_ERROR(m_deviceContext != null_q, "The device context must not be null.");

#ifdef QE_OS_WINDOWS

    BOOL bResult = ::SwapBuffers(m_deviceContext);

    if(bResult == FALSE)
    {
        QE_TRACE_WINDOWS_ERROR("Rendering buffers could not be swapped (SwapBuffers).");
    }

#endif
}

QDeviceContext::NativeRenderingContext QDeviceContext::GetCurrentRenderingContext() const
{
#ifdef QE_OS_WINDOWS

    return m_renderingContext;

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

void QDeviceContext::SetPixelFormat(const QDeviceContext::EQPixelFormat eFormat)
{
    QE_ASSERT_ERROR(m_deviceContext != null_q, "The device context must not be null.");

    m_ePixelFormat = eFormat;

#ifdef QE_OS_WINDOWS

    ::PIXELFORMATDESCRIPTOR pixelFormat;
    QDeviceContext::_GeneratePixelFormatDescriptorFromEnum(eFormat, pixelFormat);

    int nPixelFormat = ::ChoosePixelFormat(m_deviceContext, &pixelFormat);
    
    QE_ASSERT_ERROR(nPixelFormat != 0, "The pixel format could not be set (ChoosePixelFormat).");

    BOOL bResult = ::SetPixelFormat(m_deviceContext, nPixelFormat, &pixelFormat);

    QE_ASSERT_ERROR(bResult != 0, "The pixel format could not be set (SetPixelFormat).");

#endif
}

QDeviceContext::EQPixelFormat QDeviceContext::GetPixelFormat() const
{
    return m_ePixelFormat;
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