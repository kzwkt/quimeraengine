
#ifndef __QBASETEXTUREARRAY__
#define __QBASETEXTUREARRAY__

#include "QBaseTexture.h"

class QBaseTextureArray : public QBaseTexture
{
public:

    u32_q GetSliceCount() const
    {
        return m_uSlices;
    }

protected:

    u32_q m_uSlices;
};

#endif // __QBASETEXTUREARRAY__