
#ifndef __QABSTRACTTEXTURE1DARRAY__
#define __QABSTRACTTEXTURE1DARRAY__

#include "QBaseTextureArray.h"

class QAbstractTexture1DArray : public QBaseTextureArray
{
public:

    virtual void GetSubtexture( const i32_q nOffset,
                                const i32_q nFirstSlice,
                                const u32_q uWidth,
                                const u32_q uSlices,
                                const u8_q uMipmapLevel,
                                const u32_q uSubtextureSize,
                                void** ppOutputSubtexture) const = 0;

    virtual void GetFullContent(const u8_q uMipmapLevel, const u32_q uSubtextureSize, void** ppOutputSubtexture) const = 0;

    virtual void SetFullContent(const u8_q uMipmapLevel, const void* pSubtexture) = 0;

    virtual void SetSubtexture(const i32_q nOffset, const i32_q nFirstSlice, const u32_q uWidth, const u32_q uSlices, const u8_q uMipmapLevel, const void* pSubtexture) = 0;

};

#endif // __QABSTRACTTEXTURE1DARRAY__