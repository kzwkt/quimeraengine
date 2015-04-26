
#ifndef __QABSTRACTTEXTURECUBE__
#define __QABSTRACTTEXTURECUBE__

#include "QBaseTexture.h"

class QAbstractTextureCube : public QBaseTexture
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

    virtual void GetSubtexture( const i32_q nXOffset,
                                const i32_q nYOffset,
                                const EQCubeMapFace eFace,
                                const u32_q uWidth,
                                const u32_q uHeight,
                                const u8_q uMipmapLevel,
                                const u32_q uSubtextureSize,
                                void** ppOutputSubtexture) const = 0;

    virtual void GetFullContent(const u8_q uMipmapLevel, const u32_q uSubtextureSize, void** ppOutputSubtexture) const = 0;

    virtual void SetFullContent(const u8_q uMipmapLevel, const void* pSubtexture) = 0;

    virtual void SetSubtexture(const i32_q nXOffset, const i32_q nYOffset, const EQCubeMapFace eFace, const u32_q uWidth, const u32_q uHeight, const u8_q uMipmapLevel, const void* pSubtexture) = 0;


    u32_q GetHeight() const
    {
        return m_uHeight;
    }

protected:

    u32_q m_uHeight;
};

#endif // __QABSTRACTTEXTURECUBE__