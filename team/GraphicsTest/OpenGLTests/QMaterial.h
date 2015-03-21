
#ifndef __QMATERIAL__
#define __QMATERIAL__

#include "QuimeraEngineIncludesAndUsings.h"

class QMaterial
{
public:

    QMaterial() : SpecularPower(SQFloat::_0),
                  Shininess(SQFloat::_0)
    {
    }

    QColor Ambient;
    QColor Diffuse;
    QColor Emissive;
    QColor Specular;
    QColor Transparent;
    QColor Reflective;
    float_q SpecularPower; // This could be the .a component of Specular
    float_q Shininess; // Glossiness?
};

#endif // __QMATERIAL__