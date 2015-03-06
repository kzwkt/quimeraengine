
#ifndef __QMATERIAL__
#define __QMATERIAL__

#include "QuimeraEngineIncludesAndUsings.h"

class QMaterial
{
public:

    QColor Ambient;
    QColor Diffuse;
    QColor Emissive;
    QColor Specular;
    float_q Power; // This could be the .a component of Specular
};

#endif // __QMATERIAL__