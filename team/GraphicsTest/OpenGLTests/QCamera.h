
#ifndef __QCAMERA__
#define __QCAMERA__

#include "QEntity.h"
#include "QFrustum.h"

class QCamera : public QEntity
{
public:

    QSpaceConversionMatrix GetViewSpaceMatrix()
    {
        // Camera from LH to RH

        QSpaceConversionMatrix viewSpaceMatrix;
        viewSpaceMatrix.SetViewSpaceMatrix(this->LocalPosition, this->LocalPosition + QVector4::GetUnitVectorInvZ().Transform(this->LocalOrientation.UnitInvert()), QVector4::GetUnitVectorY().Transform(this->LocalOrientation.UnitInvert()));
        // Inverts X-axis
        viewSpaceMatrix.ij[0][0] = -viewSpaceMatrix.ij[0][0];
        viewSpaceMatrix.ij[1][0] = -viewSpaceMatrix.ij[1][0];
        viewSpaceMatrix.ij[2][0] = -viewSpaceMatrix.ij[2][0];
        viewSpaceMatrix.ij[3][0] = -viewSpaceMatrix.ij[3][0];

        return viewSpaceMatrix;
    }

    QFrustum Frustum;
};

#endif // __QCAMERA__