
#include "QDeviceContext.h"
#include "QuimeraEngineIncludesAndUsings.h"
#include "GL/glew.h"
#include "GL/wglew.h"

void QDeviceContext::_GeneratePixelFormatDescriptorFromEnum(const QDeviceContext::EQPixelFormat ePixelFormat, PIXELFORMATDESCRIPTOR& descriptor)
{
    ::ZeroMemory(&descriptor, sizeof(::PIXELFORMATDESCRIPTOR));

    descriptor.nSize = sizeof(::PIXELFORMATDESCRIPTOR);
    descriptor.nVersion = 1;
    descriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_GENERIC_ACCELERATED | PFD_DOUBLEBUFFER;
    descriptor.iPixelType = PFD_TYPE_RGBA;
    descriptor.iLayerType = PFD_MAIN_PLANE;

    switch(ePixelFormat)
    {
    case QDeviceContext::E_A8B8G8R8:
        {
            descriptor.cColorBits = 24;
            descriptor.cRedBits = 8;
            descriptor.cRedShift = 0;
            descriptor.cGreenBits = 8;
            descriptor.cGreenShift = 8;
            descriptor.cBlueBits = 8;
            descriptor.cBlueShift = 16;
            descriptor.cAlphaBits = 8;
            descriptor.cAlphaShift = 24;
            descriptor.cDepthBits = 0;
            descriptor.cStencilBits = 0;
            break;
        }
    case QDeviceContext::E_R32G32B32A32:
        {
            descriptor.cColorBits = 96;
            descriptor.cRedBits = 32;
            descriptor.cRedShift = 96;
            descriptor.cGreenBits = 32;
            descriptor.cGreenShift = 64;
            descriptor.cBlueBits = 32;
            descriptor.cBlueShift = 32;
            descriptor.cAlphaBits = 32;
            descriptor.cAlphaShift = 0;
            descriptor.cDepthBits = 0;
            descriptor.cStencilBits = 0;
            break;
        }
    case QDeviceContext::E_R8G8B8A8:
        {
            descriptor.cColorBits = 24;
            descriptor.cRedBits = 8;
            descriptor.cRedShift = 24;
            descriptor.cGreenBits = 8;
            descriptor.cGreenShift = 16;
            descriptor.cBlueBits = 8;
            descriptor.cBlueShift = 8;
            descriptor.cAlphaBits = 8;
            descriptor.cAlphaShift = 0;
            descriptor.cDepthBits = 0;
            descriptor.cStencilBits = 0;
            break;
        }
    case QDeviceContext::E_R8G8B8A8D24S8:
        {
            descriptor.cColorBits = 24;
            descriptor.cRedBits = 8;
            descriptor.cRedShift = 24;
            descriptor.cGreenBits = 8;
            descriptor.cGreenShift = 16;
            descriptor.cBlueBits = 8;
            descriptor.cBlueShift = 8;
            descriptor.cAlphaBits = 8;
            descriptor.cAlphaShift = 0;
            descriptor.cDepthBits = 24;
            descriptor.cStencilBits = 8;
            break;
        }
    case QDeviceContext::E_R8G8B8A8D32:
        {
            descriptor.cColorBits = 24;
            descriptor.cRedBits = 8;
            descriptor.cRedShift = 24;
            descriptor.cGreenBits = 8;
            descriptor.cGreenShift = 16;
            descriptor.cBlueBits = 8;
            descriptor.cBlueShift = 8;
            descriptor.cAlphaBits = 8;
            descriptor.cAlphaShift = 0;
            descriptor.cDepthBits = 32;
            descriptor.cStencilBits = 0;
            break;
        }
    default:
        {
            QE_ASSERT_ERROR(false, "The pixel format is not supported.");
            break;
        }
    }

    // Accumulation buffers were deprected since OpenGL 3.0
    descriptor.cAccumBits;
    descriptor.cAccumRedBits;
    descriptor.cAccumGreenBits;
    descriptor.cAccumBlueBits;
    descriptor.cAccumAlphaBits;

    // Not used
    descriptor.cAuxBuffers;
    descriptor.bReserved;

    // Ignored for now
    descriptor.dwLayerMask;
    descriptor.dwVisibleMask;
    descriptor.dwDamageMask;
}

QArrayBasic<const int> QDeviceContext::_GeneratePixelFormatAttributeListFromEnum(const QDeviceContext::EQPixelFormat ePixelFormat)
{
    QArrayBasic<const int>arAttributeList(null_q, 0);

    switch(ePixelFormat)
    {
    case QDeviceContext::E_A8B8G8R8:
        {
            static const int A8B8G8R8_ATTRIBS[] = { WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
                                                    WGL_ACCELERATION_ARB,   GL_TRUE,
                                                    WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
                                                    WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
                                                    WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
                                                    WGL_COLOR_BITS_ARB,     24,
                                                    WGL_RED_BITS_ARB,       8,
                                                    WGL_RED_SHIFT_ARB,      0,
                                                    WGL_GREEN_BITS_ARB,     8,
                                                    WGL_GREEN_SHIFT_ARB,    8,
                                                    WGL_BLUE_BITS_ARB,      8,
                                                    WGL_BLUE_SHIFT_ARB,     16,
                                                    WGL_ALPHA_BITS_ARB,     8,
                                                    WGL_ALPHA_SHIFT_ARB,    24,
                                                    WGL_DEPTH_BITS_ARB,     0,
                                                    WGL_STENCIL_BITS_ARB,   0,
                                                    0};
            arAttributeList = QArrayBasic<const int>(A8B8G8R8_ATTRIBS, sizeof(A8B8G8R8_ATTRIBS) / sizeof(int));
            break;
        }
    case QDeviceContext::E_R32G32B32A32:
        {
            static const int R32G32B32A32_ATTRIBS[] = { WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
                                                        WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB,
                                                        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
                                                        WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
                                                        WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
                                                        WGL_COLOR_BITS_ARB,     96,
                                                        WGL_RED_BITS_ARB,       32,
                                                        WGL_RED_SHIFT_ARB,      96,
                                                        WGL_GREEN_BITS_ARB,     32,
                                                        WGL_GREEN_SHIFT_ARB,    64,
                                                        WGL_BLUE_BITS_ARB,      32,
                                                        WGL_BLUE_SHIFT_ARB,     32,
                                                        WGL_ALPHA_BITS_ARB,     32,
                                                        WGL_ALPHA_SHIFT_ARB,    0,
                                                        WGL_DEPTH_BITS_ARB,     0,
                                                        WGL_STENCIL_BITS_ARB,   0,
                                                        0};
            arAttributeList = QArrayBasic<const int>(R32G32B32A32_ATTRIBS, sizeof(R32G32B32A32_ATTRIBS) / sizeof(int));
            break;
        }
    case QDeviceContext::E_R8G8B8A8:
        {
            static const int R8G8B8A8_ATTRIBS[] = { WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
                                                    WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB,
                                                    WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
                                                    WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
                                                    WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
                                                    WGL_COLOR_BITS_ARB,     24,
                                                    WGL_RED_BITS_ARB,       8,
                                                    WGL_RED_SHIFT_ARB,      24,
                                                    WGL_GREEN_BITS_ARB,     8,
                                                    WGL_GREEN_SHIFT_ARB,    16,
                                                    WGL_BLUE_BITS_ARB,      8,
                                                    WGL_BLUE_SHIFT_ARB,     8,
                                                    WGL_ALPHA_BITS_ARB,     8,
                                                    WGL_ALPHA_SHIFT_ARB,    0,
                                                    WGL_DEPTH_BITS_ARB,     0,
                                                    WGL_STENCIL_BITS_ARB,   0,
                                                    0};
            arAttributeList = QArrayBasic<const int>(R8G8B8A8_ATTRIBS, sizeof(R8G8B8A8_ATTRIBS) / sizeof(int));
            break;
        }
    case QDeviceContext::E_R8G8B8A8D24S8:
        {
            static const int R8G8B8A8D24S8_ATTRIBS[] = { WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
                                                         WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB,
                                                         WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
                                                         WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
                                                         WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
                                                         WGL_COLOR_BITS_ARB,     24,
                                                         WGL_RED_BITS_ARB,       8,
                                                         WGL_RED_SHIFT_ARB,      24,
                                                         WGL_GREEN_BITS_ARB,     8,
                                                         WGL_GREEN_SHIFT_ARB,    16,
                                                         WGL_BLUE_BITS_ARB,      8,
                                                         WGL_BLUE_SHIFT_ARB,     8,
                                                         WGL_ALPHA_BITS_ARB,     8,
                                                         WGL_ALPHA_SHIFT_ARB,    0,
                                                         WGL_DEPTH_BITS_ARB,     24,
                                                         WGL_STENCIL_BITS_ARB,   8,
                                                         //WGL_ACCUM_ALPHA_BITS_ARB, 0, // [TODO] : Deactivate all accums
                                                         0};
            arAttributeList = QArrayBasic<const int>(R8G8B8A8D24S8_ATTRIBS, sizeof(R8G8B8A8D24S8_ATTRIBS) / sizeof(int));
            break;
        }
    case QDeviceContext::E_R8G8B8A8D32:
        {
            static const int R8G8B8A8D32_ATTRIBS[] = { WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
                                                       WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB,
                                                       WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
                                                       WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
                                                       WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
                                                       WGL_COLOR_BITS_ARB,     24,
                                                       WGL_RED_BITS_ARB,       8,
                                                       WGL_RED_SHIFT_ARB,      24,
                                                       WGL_GREEN_BITS_ARB,     8,
                                                       WGL_GREEN_SHIFT_ARB,    16,
                                                       WGL_BLUE_BITS_ARB,      8,
                                                       WGL_BLUE_SHIFT_ARB,     8,
                                                       WGL_ALPHA_BITS_ARB,     8,
                                                       WGL_ALPHA_SHIFT_ARB,    0,
                                                       WGL_DEPTH_BITS_ARB,     32,
                                                       WGL_STENCIL_BITS_ARB,   0,
                                                       0};
            arAttributeList = QArrayBasic<const int>(R8G8B8A8D32_ATTRIBS, sizeof(R8G8B8A8D32_ATTRIBS) / sizeof(int));
            break;
        }
    default:
        {
            QE_ASSERT_ERROR(false, "The pixel format is not supported.");
            break;
        }
    }

    return arAttributeList;
}
