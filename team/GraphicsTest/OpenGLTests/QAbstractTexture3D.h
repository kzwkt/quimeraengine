
#ifndef __QABSTRACTTEXTURE3D__
#define __QABSTRACTTEXTURE3D__

#include "QBaseTexture.h"

class QAbstractTexture3D : public QBaseTexture
{
public:

    virtual void GetSubtexture( const i32_q nXOffset,
                                const i32_q nYOffset,
                                const i32_q nZOffset,
                                const u32_q uWidth,
                                const u32_q uHeight,
                                const u32_q uDepth,
                                const u8_q uMipmapLevel,
                                const u32_q uSubtextureSize,
                                void** ppOutputSubtexture) const = 0;

    virtual void GetFullContent(const u8_q uMipmapLevel, const u32_q uSubtextureSize, void** ppOutputSubtexture) const = 0;

    virtual void SetFullContent(const u8_q uMipmapLevel, const void* pSubtexture) = 0;

    virtual void SetSubtexture(const i32_q nXOffset, const i32_q nYOffset, const i32_q nZOffset, const u32_q uWidth, const u32_q uHeight, const u32_q uDepth, const u8_q uMipmapLevel, const void* pSubtexture) = 0;

    u32_q GetHeight() const
    {
        return m_uHeight;
    }

    u32_q GetDepth() const
    {
        return m_uDepth;
    }

protected:

    u32_q m_uHeight;
    u32_q m_uDepth;
};

#endif // __QABSTRACTTEXTURE3D__