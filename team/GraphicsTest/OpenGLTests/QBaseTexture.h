
#ifndef __QBASETEXTURE__
#define __QBASETEXTURE__

#include "QuimeraEngineIncludesAndUsings.h"
#include "EQPixelFormat.h"

class QBaseTexture
{
public:

    EQPixelFormat::EnumType GetFormat() const
    {
        return m_eFormat;
    }

    u8_q GetMipmapLevels() const
    {
        return m_uMipmapLevels;
    }

    u32_q GetWidth() const
    {
        return m_uWidth;
    }


protected:

    u32_q m_uWidth;
    EQPixelFormat::EnumType m_eFormat;
    // EQTextureDataArrangement m_eDataArrangement;
    u8_q m_uMipmapLevels;
};


#endif // __QBASETEXTURE__