
#ifndef __QABSTRACTTEXTURE2D__
#define __QABSTRACTTEXTURE2D__

#include "QBaseTexture.h"

class QAbstractTexture2D : public QBaseTexture
{
public:

    virtual void GetSubtexture( const i32_q nXOffset,
                                const i32_q nYOffset,
                                const u32_q uWidth,
                                const u32_q uHeight,
                                const u8_q uMipmapLevel,
                                const u32_q uSubtextureSize,
                                void** ppOutputSubtexture) const = 0;

    virtual void GetFullContent(const u8_q uMipmapLevel, const u32_q uSubtextureSize, void** ppOutputSubtexture) const = 0;
    
    virtual void SetFullContent(const u8_q uMipmapLevel, const void* pSubtexture) = 0;

    virtual void SetSubtexture(const i32_q nXOffset, const i32_q nYOffset, const u32_q uWidth, const u32_q uHeight, const u8_q uMipmapLevel, const void* pSubtexture) = 0;

    u32_q GetHeight() const
    {
        return m_uHeight;
    }

    bool IsMultisample() const
    {
        return m_uSamples > 0;
    }

    u8_q GetMultisamplingSamples() const
    {
        return m_uSamples;
    }

protected:

    u32_q m_uHeight;
    u8_q m_uSamples;
};

#endif // __QABSTRACTTEXTURE2D__