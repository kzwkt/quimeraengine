
#ifndef __QDEVICECONTEXT__
#define __QDEVICECONTEXT__

#include "QuimeraEngineIncludesAndUsings.h"
#include "EQPixelFormat.h"
#include "ErrorTracingDefinitions.h"
#include <GL/glew.h>
#include <GL/wglew.h>
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



public:

    QDeviceContext(const NativeDeviceContext nativeDeviceContext);
    
protected:

#ifdef QE_OS_WINDOWS

    static void _GeneratePixelFormatDescriptorFromEnum(const EQPixelFormat::EnumType ePixelFormat, PIXELFORMATDESCRIPTOR& descriptor);
    static void _GeneratePixelFormatAttributeListFromEnum(const EQPixelFormat::EnumType ePixelFormat, const u32_q uSamples, int arAttributes[38]);

#endif

public:

    NativeDeviceContext GetNativeDeviceContext() const;
    void SetNativeDeviceContext(const NativeDeviceContext deviceContext);

    void SetPixelFormat(const EQPixelFormat::EnumType eFormat);
    EQPixelFormat::EnumType GetPixelFormat() const;

    void SetMultisamplingSamples(const u32_q uSampleCount);
    u32_q GetMultisamplingSamples() const;

    void GetNativePixelFormatInfo(void* pPixelFormat) const;

    void SetPixelFormat(const EQPixelFormat::EnumType ePixelFormat, const u32_q uMultisamplingSamples)
    {
        QE_ASSERT_ERROR(m_ePixelFormat == EQPixelFormat::E_Undefined, "The pixel format of a device context can only be set once.");

        int arAttributes[38];

        QDeviceContext::_GeneratePixelFormatAttributeListFromEnum(ePixelFormat, uMultisamplingSamples, arAttributes);

        const unsigned int MAX_DESIRED_FORMATS = 5;
        unsigned int nActualMatchingFormats = 0;
        int arMatchingFormatIndices[MAX_DESIRED_FORMATS];
        ::wglChoosePixelFormatARB(m_deviceContext, arAttributes, null_q, MAX_DESIRED_FORMATS, arMatchingFormatIndices, &nActualMatchingFormats);

        QE_LOG(string_q("LOG: Matching pixel formats: ") + nActualMatchingFormats + "\n");
        QE_ASSERT_ERROR(nActualMatchingFormats > 0, "There is no matching pixel format supported (wglChoosePixelFormatARB).");

        QE_LOG(string_q("LOG: Using pixel format: ") + arMatchingFormatIndices[0] + "\n");
        BOOL bResult = ::SetPixelFormat(m_deviceContext, arMatchingFormatIndices[0], null_q);
        //    PrintPixelFormats(m_deviceContext);
        if (bResult == FALSE)
        {
            QE_ASSERT_WINDOWS_ERROR("Failed to set the pixel format when creating the rendering context (SetPixelFormat).");
        }

        m_ePixelFormat = ePixelFormat;
        m_uMultisamplingSamples = uMultisamplingSamples;
    }

private:

    QArrayDynamic<HGLRC> m_arRenderingContexts;
    NativeDeviceContext m_deviceContext;
    EQPixelFormat::EnumType m_ePixelFormat;
    u32_q m_uMultisamplingSamples;

};


#endif // __QDEVICECONTEXT__