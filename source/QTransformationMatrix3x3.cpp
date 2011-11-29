// [TERMS&CONDITIONS]

#include "QTransformationMatrix3x3.h"

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |  CONSTANTS INITIALIZATION  |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const QTransformationMatrix3x3 QTransformationMatrix3x3::Identity(QMatrix3x3::Identity);

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QTransformationMatrix3x3::QTransformationMatrix3x3 (const QBaseVector2 &vDisp, const float_q &fRot, const QBaseVector2 &vScale)
{
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        float_q &fRotRad = SQAngle::DegreesToRadians(fRot, fRotRad);

        const float_q& A   = cos(fRotRad);
        const float_q& B   = sin(fRotRad);
    #else
        const float_q& A   = cos(fRot);
        const float_q& B   = sin(fRot);
    #endif

    this->ij[0][0] =  vScale.x * A;
    this->ij[0][1] =  vScale.x * B;
    this->ij[0][2] =  SQFloat::_0;

    this->ij[1][0] = -vScale.y * B;
    this->ij[1][1] =  vScale.y * A;
    this->ij[1][2] =  SQFloat::_0;

    this->ij[2][0] =  vDisp.x;
    this->ij[2][1] =  vDisp.y;
    this->ij[2][2] =  SQFloat::_1;

}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |            METHODS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

void QTransformationMatrix3x3::Decompose (QBaseVector2 &vOutDisp, float_q &fOutRot, QBaseVector2 &vOutScale) const
{
    vOutDisp.x = this->ij[2][0];
    vOutDisp.x = this->ij[2][1];

    vOutScale.x = sqrt(this->ij[0][0]*this->ij[0][0] + this->ij[0][1]*this->ij[0][1]);
    vOutScale.y = sqrt(this->ij[1][0]*this->ij[1][0] + this->ij[1][1]*this->ij[1][1]);

    // Checkout to avoid division by zero.
    QE_ASSERT(vOutScale.x != SQFloat::_0);

    const float_q &fCosRot = this->ij[0][0]/vOutScale.x;

    // checkout to avoid improper values of cosine. Remember cosine must be in [-1,1] range.
    QE_ASSERT(SQFloat::Abs(fCosRot) <= SQFloat::_1);

    fOutRot = acos(fCosRot);

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles must be specified in degrees, then converts it.
        SQAngle::RadiansToDegrees(fOutRot, fOutRot);
    #endif
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
