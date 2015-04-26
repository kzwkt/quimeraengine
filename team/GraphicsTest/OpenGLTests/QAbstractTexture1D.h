
#ifndef __QABSTRACTTEXTURE1D__
#define __QABSTRACTTEXTURE1D__

#include "QBaseTexture.h"

class QAbstractTexture1D : public QBaseTexture
{
public:

    virtual void GetSubtexture(const i32_q nOffset,
                                const u32_q uWidth,
                                const u8_q uMipmapLevel,
                                const u32_q uSubtextureSize,
                                void** ppOutputSubtexture) const = 0;

    virtual void GetFullContent(const u8_q uMipmapLevel, const u32_q uSubtextureSize, void** ppOutputSubtexture) const = 0;

    virtual void SetFullContent(const u8_q uMipmapLevel, const void* pSubtexture) = 0;

    virtual void SetSubtexture(const i32_q nOffset, const u32_q uWidth, const u8_q uMipmapLevel, const void* pSubtexture) = 0;


};

#endif // __QABSTRACTTEXTURE1D__