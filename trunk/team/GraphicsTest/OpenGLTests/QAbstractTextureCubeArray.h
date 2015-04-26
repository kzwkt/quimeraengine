
#ifndef __QABSTRACTTEXTURECUBEARRAY__
#define __QABSTRACTTEXTURECUBEARRAY__

#include "QBaseTextureArray.h"

class QAbstractTextureCubeArray : public QBaseTextureArray
{
public:

    enum EQCubeMapFace
    {
        E_TextureCubeFacePositiveX,
        E_TextureCubeFaceNegativeX,
        E_TextureCubeFacePositiveY,
        E_TextureCubeFaceNegativeY,
        E_TextureCubeFacePositiveZ,
        E_TextureCubeFaceNegativeZ
    };

    virtual void GetSubtexture(const i32_q uXOffset, const i32_q uYOffset, const i32_q uZOffset, const u32_q uWidth, const u32_q uHeight, const u32_q uDepth, const u8_q uMipmapLevel, const u32_q uLayer, void** ppOutputSubtexture) const = 0;

    virtual void SetSubtexture(const i32_q uXOffset, const i32_q uYOffset, const i32_q uZOffset, const u32_q uWidth, const u32_q uHeight, const u32_q uDepth, const u8_q uMipmapLevel, const u32_q uLayer, const void* pSubtexture) = 0;

    u32_q GetHeight() const
    {
        return m_uHeight;
    }

protected:

    u32_q m_uHeight;
};

#endif // __QABSTRACTTEXTURECUBEARRAY__