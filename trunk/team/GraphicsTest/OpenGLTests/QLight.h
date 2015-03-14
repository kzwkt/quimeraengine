
#ifndef __QLIGHT__
#define __QLIGHT__

#include "QEntity.h"

class QLight : public QEntity
{
public:

    QLight()
    {
    }


public:

    QColor Ambient;
    QColor Diffuse;
    QColor Specular;
};

#endif // __QLIGHT__