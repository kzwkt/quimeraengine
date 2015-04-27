
#ifndef __EQTEXTUREFORMAT__
#define __EQTEXTUREFORMAT__

#include "EQPixelFormat.h"

// There will be an original set, pixel format, and several subsets for every use: color buffer, depth buffer, textures, etc. so it's easier to maintain and more usable for users
class EQTextureFormat
{
public:

    enum EnumType
    {
        E_R8UI_Normalized = EQPixelFormat::E_R8UI_Normalized,
        E_R16UI_Normalized = EQPixelFormat::E_R16UI_Normalized,
        E_RG8UI_Normalized = EQPixelFormat::E_RG8UI_Normalized,
        E_RG16UI_Normalized = EQPixelFormat::E_RG16UI_Normalized,
        E_R3G3B2UI_Normalized = EQPixelFormat::E_R3G3B2UI_Normalized,
        E_RGB4UI_Normalized = EQPixelFormat::E_RGB4UI_Normalized,
        E_RGB5UI_Normalized = EQPixelFormat::E_RGB5UI_Normalized,
        E_RGB8UI_Normalized = EQPixelFormat::E_RGB8UI_Normalized,
        E_RGB10UI_Normalized = EQPixelFormat::E_RGB10UI_Normalized,
        E_RGB12UI_Normalized = EQPixelFormat::E_RGB12UI_Normalized,
        E_RGB16UI_Normalized = EQPixelFormat::E_RGB16UI_Normalized,
        E_RGB565UI_Normalized = EQPixelFormat::E_RGB565UI_Normalized,
        E_RGBA2UI_Normalized = EQPixelFormat::E_RGBA2UI_Normalized,
        E_RGBA4UI_Normalized = EQPixelFormat::E_RGBA4UI_Normalized,
        E_RGB5A1UI_Normalized = EQPixelFormat::E_RGB5A1UI_Normalized,
        E_RGBA8UI_Normalized = EQPixelFormat::E_RGB5A1UI_Normalized,
        E_RGB10A2UI_Normalized = EQPixelFormat::E_RGB10A2UI_Normalized,
        E_RGBA12UI_Normalized = EQPixelFormat::E_RGBA12UI_Normalized,
        E_RGBA16UI_Normalized = EQPixelFormat::E_RGBA16UI_Normalized,
        E_SRGB8_Compressed = EQPixelFormat::E_SRGB8_Compressed,
        E_SRGB8A8_Compressed = EQPixelFormat::E_SRGB8A8_Compressed,
        E_R16F = EQPixelFormat::E_R16F,
        E_R32F = EQPixelFormat::E_R32F,
        E_RG16F = EQPixelFormat::E_RG16F,
        E_RG32F = EQPixelFormat::E_RG32F,
        E_RGB16F = EQPixelFormat::E_RGB16F,
        E_RGB32F = EQPixelFormat::E_RGB32F,
        E_RGBA16F = EQPixelFormat::E_RGBA16F,
        E_RGBA32F = EQPixelFormat::E_RGBA32F,
        E_R11FG11FB10F = EQPixelFormat::E_R11FG11FB10F,
        E_RGB9F_E5 = EQPixelFormat::E_RGB9F_E5,
        E_R8I = EQPixelFormat::E_R8I,
        E_R8UI = EQPixelFormat::E_R8UI,
        E_R16I = EQPixelFormat::E_R16I,
        E_R16UI = EQPixelFormat::E_R16UI,
        E_R32I = EQPixelFormat::E_R32I,
        E_R32UI = EQPixelFormat::E_R32UI,
        E_RG8I = EQPixelFormat::E_RG8I,
        E_RG8UI = EQPixelFormat::E_RG8UI,
        E_RG16I = EQPixelFormat::E_RG16I,
        E_RG16UI = EQPixelFormat::E_RG16UI,
        E_RG32I = EQPixelFormat::E_RG32I,
        E_RG32UI = EQPixelFormat::E_RG32UI,
        E_RGB8I = EQPixelFormat::E_RGB8I,
        E_RGB8UI = EQPixelFormat::E_RGB8UI,
        E_RGB16I = EQPixelFormat::E_RGB16I,
        E_RGB16UI = EQPixelFormat::E_RGB16UI,
        E_RGB32I = EQPixelFormat::E_RGB32I,
        E_RGB32UI = EQPixelFormat::E_RGB32UI,
        E_RGBA8I = EQPixelFormat::E_RGBA8I,
        E_RGBA8UI = EQPixelFormat::E_RGBA8UI,
        E_RGBA16I = EQPixelFormat::E_RGBA16I,
        E_RGBA16UI = EQPixelFormat::E_RGBA16UI,
        E_RGBA32I = EQPixelFormat::E_RGBA32I,
        E_RGBA32UI = EQPixelFormat::E_RGBA32UI,
        E_RGB10A2UI = EQPixelFormat::E_RGB10A2UI,
        E_R8I_Normalized = EQPixelFormat::E_R8I_Normalized,
        E_R16I_Normalized = EQPixelFormat::E_R16I_Normalized,
        E_RG8I_Normalized = EQPixelFormat::E_RG8I_Normalized,
        E_RG16I_Normalized = EQPixelFormat::E_RG16I_Normalized,
        E_RGB8I_Normalized = EQPixelFormat::E_RGB8I_Normalized,
        E_RGB16I_Normalized = EQPixelFormat::E_RGB16I_Normalized,
        E_RGBA8I_Normalized = EQPixelFormat::E_RGBA8I_Normalized,
        E_RGBA16I_Normalized = EQPixelFormat::E_RGBA16I_Normalized,
        E_Undefined = EQPixelFormat::E_Undefined
    };
};

#endif // __EQTEXTUREFORMAT__