
#ifndef __QIMAGE__
#define __QIMAGE__

#include "QuimeraEngineIncludesAndUsings.h"

class QImage
{
public:

    enum EQImageColorComponents
    {
        E_RGB,
        E_RGBA
    };


    QImage(void* pImageData, const QPath &imagePath, const EQImageColorComponents eColorComponents, const unsigned int uWidth, const unsigned int uHeight) : 
                                                                                                    m_pData(pImageData),
                                                                                                    m_eComponennts(eColorComponents),
                                                                                                    m_uWidth(uWidth),
                                                                                                    m_uHeight(uHeight),
                                                                                                    m_imagePath(imagePath)
    {
    }

    const QPath& GetPath() const
    {
        return m_imagePath;
    }

    EQImageColorComponents GetColorComponents() const
    {
        return m_eComponennts;
    }

    const void* GetData() const
    {
        return m_pData;
    }

    unsigned int GetWidth() const
    {
        return m_uWidth;
    }

    unsigned int GetHeight() const
    {
        return m_uHeight;
    }

protected:

    const void* m_pData;
    const EQImageColorComponents m_eComponennts;
    const unsigned int m_uWidth;
    const unsigned int m_uHeight;
    const QPath m_imagePath;
};


#endif // __QIMAGE__