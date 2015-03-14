
#ifndef __QFRUSTUM__
#define __QFRUSTUM__

#include "QuimeraEngineIncludesAndUsings.h"

class QFrustum
{
public:

    QFrustum() : NearPlaneDistance(SQFloat::_0),
                 FarPlaneDistance(SQFloat::_0),
                 AspectRatio(SQFloat::_0),
                 Fov(SQFloat::_0)
    {
    }

    QSpaceConversionMatrix GetProjectionSpaceMatrix()
    {
        static const float_q MIN_DEPTH_VALUE = -SQFloat::_1;
        static const float_q MAX_DEPTH_VALUE = SQFloat::_1;
        return this->CalculateMatrixWithVariableDepthRange(this->NearPlaneDistance, this->FarPlaneDistance, this->AspectRatio, this->Fov, MIN_DEPTH_VALUE, MAX_DEPTH_VALUE).Transpose();
    }

    QSpaceConversionMatrix CalculateMatrixWithVariableDepthRange(const float_q fNearClipPlane, const float_q fFarClipPlane,
                                                                 const float_q fAspectRatio, const float_q fVerticalFOV,
                                                                 const float_q fMinDepthValue, const float_q fMaxDepthValue)
    {
        // See also: https://msdn.microsoft.com/en-us/library/windows/desktop/bb205350%28v=vs.85%29.aspx
        //           http://www-01.ibm.com/support/knowledgecenter/ssw_aix_61/com.ibm.aix.opengl/doc/openglrf/gluPerspective.htm%23b5c8872587rree
        //           https://solarianprogrammer.com/2013/05/22/opengl-101-matrices-projection-view-model/

        // Implementing this: https://anteru.net/2011/12/27/1830/
        QSpaceConversionMatrix projectionSpaceMatrix;
        const float_q& SCALE_Y = float_q((double)SQFloat::_1 / tan_q((double)fVerticalFOV * (double)SQFloat::_0_5));
        const float_q& SCALE_X = float_q((double)SCALE_Y / (double)fAspectRatio);

        projectionSpaceMatrix.ij[0][0] = SCALE_X;
        projectionSpaceMatrix.ij[0][1] = SQFloat::_0;
        projectionSpaceMatrix.ij[0][2] = SQFloat::_0;
        projectionSpaceMatrix.ij[0][3] = SQFloat::_0;
        projectionSpaceMatrix.ij[1][0] = SQFloat::_0;
        projectionSpaceMatrix.ij[1][1] = SCALE_Y;
        projectionSpaceMatrix.ij[1][2] = SQFloat::_0;
        projectionSpaceMatrix.ij[1][3] = SQFloat::_0;
        projectionSpaceMatrix.ij[2][0] = SQFloat::_0;
        projectionSpaceMatrix.ij[2][1] = SQFloat::_0;
        projectionSpaceMatrix.ij[2][2] = (fMaxDepthValue * fFarClipPlane - fMinDepthValue * fNearClipPlane) / (fNearClipPlane - fFarClipPlane);
        projectionSpaceMatrix.ij[2][3] = (fMaxDepthValue - fMinDepthValue) * (fNearClipPlane * fFarClipPlane) / (fNearClipPlane - fFarClipPlane);
        projectionSpaceMatrix.ij[3][0] = SQFloat::_0;
        projectionSpaceMatrix.ij[3][1] = SQFloat::_0;
        projectionSpaceMatrix.ij[3][2] = -SQFloat::_1;
        projectionSpaceMatrix.ij[3][3] = SQFloat::_0;

        // Note that it is RH
        return projectionSpaceMatrix;
    }

public:

    float_q NearPlaneDistance;
    float_q FarPlaneDistance;
    float_q AspectRatio;
    float_q Fov;
    
};

#endif // __QFRUSTUM__