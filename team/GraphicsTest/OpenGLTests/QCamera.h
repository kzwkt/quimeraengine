
#ifndef __QCAMERA__
#define __QCAMERA__

#include "QEntity.h"
#include "QFrustum.h"

class QCamera : public QEntity
{
public:

    QSpaceConversionMatrix GetViewSpaceMatrix()
    {
        QSpaceConversionMatrix viewSpaceMatrix;
        viewSpaceMatrix.SetViewSpaceMatrix(this->LocalPosition, this->LocalPosition + QVector4::GetUnitVectorZ().Transform(this->LocalOrientation), QVector4::GetUnitVectorY().Transform(this->LocalOrientation));
        return viewSpaceMatrix;
    }

    QFrustum Frustum;
};

#endif // __QCAMERA__