#ifndef __QBASETEXTUREBUFFER__
#define __QBASETEXTUREBUFFER__

#include "QuimeraEngineIncludesAndUsings.h"
#include "EQTextureFormat.h"

class QBaseTextureBuffer
{
public:

    EQTextureFormat::EnumType GetFormat() const
    {
        return m_eFormat;
    }

    u32_q GetWidth() const
    {
        return m_uWidth;
    }

    QHashedString GetBufferId() const
    {
        return m_strBufferId;
    }

protected:

    QHashedString m_strBufferId;
    u32_q m_uWidth;
    EQTextureFormat::EnumType m_eFormat;
};

#endif // __QBASETEXTUREBUFFER__