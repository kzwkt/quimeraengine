
#ifndef __QABSTRACTTEXTURE2D__
#define __QABSTRACTTEXTURE2D__

#include "QBaseTexture.h"

class QAbstractTexture2D : public QBaseTexture
{
public:

    virtual void GetSubtexture( const i32_q nSourceOffsetX,
                                const i32_q nSourceOffsetY,
                                const u32_q nSourceWidth,
                                const u32_q nSourceHeight,
                                const EQTextureFormat::EnumType eSourceFormat,
                                const u8_q uSourceMipmapLevel,
                                u32_q &uSourceSize,
                                void** ppDestination) const = 0;

    virtual void GetFullContent(const EQTextureFormat::EnumType eSourceFormat, const u8_q uDestinationMipmapLevel, u32_q &uDestinationSize, void** ppDestination) const = 0;
    
    virtual void SetFullContent(const u8_q uDestinationMipmapLevel, const EQTextureFormat::EnumType eSourceFormat, const void* pSource) = 0;

    virtual void SetSubtexture(const i32_q nDestinationOffsetX, const i32_q nDestinationOffsetY, const u32_q nDestinationWidth, const u32_q nDestinationHeight, const u8_q uDestinationMipmapLevel, const EQTextureFormat::EnumType eSourceFormat, const void* pSource) = 0;

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