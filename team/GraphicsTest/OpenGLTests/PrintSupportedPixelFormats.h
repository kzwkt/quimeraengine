
#include "QuimeraEngineIncludesAndUsings.h"
#include <Windows.h>


void PrintPixelFormats(HDC hdc)
{

::PIXELFORMATDESCRIPTOR pixelFormat;

int nMaxPixelFormatIndex = ::DescribePixelFormat(hdc, 1, sizeof(PIXELFORMATDESCRIPTOR), &pixelFormat);

    for(int i = 2; i < nMaxPixelFormatIndex; ++i)
    {
        ZeroMemory(&pixelFormat, sizeof(PIXELFORMATDESCRIPTOR));
        
        ::DescribePixelFormat(hdc, i, sizeof(PIXELFORMATDESCRIPTOR), &pixelFormat);
        string_q strPixelFormat = string_q("Format [") + i + "]\n" +
            
                                           "R" + pixelFormat.cRedBits +
                                           "G" + pixelFormat.cGreenBits +
                                           "B" + pixelFormat.cBlueBits +
                                           "A" + pixelFormat.cAlphaBits +
                                           "D" + pixelFormat.cDepthBits +
                                           "S" + pixelFormat.cStencilBits + "\n\n" +

                                           "bReserved = " + pixelFormat.bReserved + "\n" +
                                           "cAccumAlphaBits = " + pixelFormat.cAccumAlphaBits + "\n" +
                                           "cAccumBits = " + pixelFormat.cAccumBits + "\n" +
                                           "cAccumBlueBits = " + pixelFormat.cAccumBlueBits + "\n" +
                                           "cAccumGreenBits = " + pixelFormat.cAccumGreenBits + "\n" +
                                           "cAccumRedBits = " + pixelFormat.cAccumRedBits + "\n" +
                                           "cAlphaBits = " + pixelFormat.cAlphaBits + "\n" +
                                           "cAlphaShift = " + pixelFormat.cAlphaShift + "\n" +
                                           "cAuxBuffers = " + pixelFormat.cAuxBuffers + "\n" +
                                           "cBlueBits = " + pixelFormat.cBlueBits + "\n" +
                                           "cBlueShift = " + pixelFormat.cBlueShift + "\n" +
                                           "cColorBits = " + pixelFormat.cColorBits + "\n" +
                                           "cDepthBits = " + pixelFormat.cDepthBits + "\n" +
                                           "cGreenBits = " + pixelFormat.cGreenBits + "\n" +
                                           "cGreenShift = " + pixelFormat.cGreenShift + "\n" +
                                           "cRedBits = " + pixelFormat.cRedBits + "\n" +
                                           "cRedShift = " + pixelFormat.cRedShift + "\n" +
                                           "cStencilBits = " + pixelFormat.cStencilBits + "\n" +
                                           "dwDamageMask = " + scast_q(pixelFormat.dwDamageMask, u32_q) + "\n" +
                                           "dwFlags = " + scast_q(pixelFormat.dwFlags, u32_q) + "\n" +
                                           "dwLayerMask = " + scast_q(pixelFormat.dwLayerMask, u32_q) + "\n" +
                                           "dwVisibleMask = " + scast_q(pixelFormat.dwVisibleMask, u32_q) + "\n" +
                                           "iLayerType = " + pixelFormat.iLayerType + "\n" +
                                           "iPixelType = " + pixelFormat.iPixelType + "\n" +
                                           "nSize = " + pixelFormat.nSize + "\n" +
                                           "nVersion = " + pixelFormat.nVersion + "\n";

        QE_LOG(strPixelFormat);
    }

}