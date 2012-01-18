// [TERMS&CONDITIONS]

#include "QRotationMatrix3x3.h"

#include "QVector3.h"
#include "QQuaternion.h"
#include "QTranslationMatrix.h"
#include "QScaleMatrix3x3.h"
#include "QTransformationMatrix.h"

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QRotationMatrix3x3::QRotationMatrix3x3(const float_q &fRotationAngleX, const float_q &fRotationAngleY, const float_q &fRotationAngleZ)
{

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        float_q &fAngleXRad = SQAngle::DegreesToRadians(fRotationAngleX, fAngleXRad);
        float_q &fAngleYRad = SQAngle::DegreesToRadians(fRotationAngleY, fAngleYRad);
        float_q &fAngleZRad = SQAngle::DegreesToRadians(fRotationAngleZ, fAngleZRad);

        const float_q& fA   = cos_q(fAngleXRad);
        const float_q& fB   = sin_q(fAngleXRad);
        const float_q& fC   = cos_q(fAngleYRad);
        const float_q& fD   = sin_q(fAngleYRad);
        const float_q& fE   = cos_q(fAngleZRad);
        const float_q& fF   = sin_q(fAngleZRad);
    #else
        const float_q& fA   = cos_q(fRotationAngleX);
        const float_q& fB   = sin_q(fRotationAngleX);
        const float_q& fC   = cos_q(fRotationAngleY);
        const float_q& fD   = sin_q(fRotationAngleY);
        const float_q& fE   = cos_q(fRotationAngleZ);
        const float_q& fF   = sin_q(fRotationAngleZ);
    #endif

    float_q fBC  = -fB * fC;
    float_q fBD  = fB * fD;

    ij[0][0]  =  fE * fC + fF * fBD;
    ij[0][1]  =  fA * fF;
    ij[0][2]  =  -fE * fD - fF * fBC;

    ij[1][0]  =  -fF * fC + fE * fBD;
    ij[1][1]  =  fA * fE;
    ij[1][2]  =  fF * fD - fE * fBC;

    ij[2][0]  =  fA * fD;
    ij[2][1]  =  -fB;
    ij[2][2]  =  fA * fC;
}

QRotationMatrix3x3::QRotationMatrix3x3 (const QBaseVector3 &vRotationAxis, const float_q &fRotationAngle)
{
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        float_q &fAngleRad = SQAngle::DegreesToRadians(fRotationAngle, fAngleRad);

        const float_q& fA = cos_q(fAngleRad);
        const float_q& fB = sin_q(fAngleRad);
    #else
        const float_q& fA = cos_q(fRotationAngle);
        const float_q& fB = sin_q(fRotationAngle);
    #endif

    const float_q& fC = vRotationAxis.x*vRotationAxis.y;
    const float_q& fD = vRotationAxis.y*vRotationAxis.z;
    const float_q& fE = vRotationAxis.z*vRotationAxis.x;

    const float_q& fF = (SQFloat::_1 - fA) * fC;
    const float_q& fG = (SQFloat::_1 - fA) * fD;
    const float_q& fH = (SQFloat::_1 - fA) * fE;

    const float_q& fI = -vRotationAxis.x * fB;
    const float_q& fJ = -vRotationAxis.y * fB;
    const float_q& fK = -vRotationAxis.z * fB;

    this->ij[0][0] = fA + (SQFloat::_1 - fA) * vRotationAxis.x * vRotationAxis.x;
    this->ij[0][1] = fF - fK;
    this->ij[0][2] = fH + fJ;

    this->ij[1][0] = fF + fK;
    this->ij[1][1] = fA + (SQFloat::_1 - fA) * vRotationAxis.y * vRotationAxis.y;
    this->ij[1][2] = fG - fI;

    this->ij[2][0] = fH - fJ;
    this->ij[2][1] = fG + fI;
    this->ij[2][2] = fA + (SQFloat::_1 - fA) * vRotationAxis.z * vRotationAxis.z;
}

/*
Según http://osdir.com/ml/games.devel.algorithms/2002-11/msg00318.html
...
i.e.
        "3D Game Engine Design", Page 17, Section 2.3.5, Eqn 2.13
            and
         "Rotating Objects Using Quaterions" (Corrected matrix)
         Game Developer, Feb 98, Nick Bobick

RHCS?
                 2    2
         [ 1 - 2y - 2z    2xy + 2wz      2xz - 2wy    ]
         [                      2    2                ]
         [ 2xy - 2wz      1 - 2x - 2z    2yz + 2wx    ]
         [                                     2    2 ]
         [ 2xz + 2wy      2yz - 2wx      1 - 2x - 2y  ]

         Used by Watt&Watt, Parameetrization of orientation, Page 362
LHCS?
                 2    2
         [ 1 - 2y - 2z    2xy - 2wz      2xz + 2wy    ]
         [                      2    2                ]
         [ 2xy + 2wz      1 - 2x - 2z    2yz - 2wx    ]
         [                                     2    2 ]
         [ 2xz - 2wy      2yz + 2wx      1 - 2x - 2y  ]
*/
QRotationMatrix3x3::QRotationMatrix3x3(const QBaseQuaternion &qRotation)
{
    const float_q& fA   = SQFloat::_2 * qRotation.x * qRotation.x;
    const float_q& fB   = SQFloat::_2 * qRotation.y * qRotation.y;
    const float_q& fC   = SQFloat::_2 * qRotation.z * qRotation.z;

    const float_q& fD   = SQFloat::_2 * qRotation.x * qRotation.y;
    const float_q& fE   = SQFloat::_2 * qRotation.x * qRotation.z;
    const float_q& fF   = SQFloat::_2 * qRotation.x * qRotation.w;
    const float_q& fG   = SQFloat::_2 * qRotation.y * qRotation.z;
    const float_q& fH   = SQFloat::_2 * qRotation.y * qRotation.w;
    const float_q& fI   = SQFloat::_2 * qRotation.z * qRotation.w;

    this->ij[0][0] = SQFloat::_1 - fB - fC;
    this->ij[0][1] = fD + fI;
    this->ij[0][2] = fE - fH;

    this->ij[1][0] = fD - fI;
    this->ij[1][1] = SQFloat::_1 - fA - fC;
    this->ij[1][2] = fG + fF;

    this->ij[2][0] = fE + fH;
    this->ij[2][1] = fG - fF;
    this->ij[2][2] = SQFloat::_1 - fA - fB;
}

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

// Binary operators

QRotationMatrix3x3 QRotationMatrix3x3::operator*(const QRotationMatrix3x3 &matrix) const
{
    QRotationMatrix3x3 aux;

    aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0] + this->ij[0][1] * matrix.ij[1][0] + this->ij[0][2] * matrix.ij[2][0];
    aux.ij[0][1] = this->ij[0][0] * matrix.ij[0][1] + this->ij[0][1] * matrix.ij[1][1] + this->ij[0][2] * matrix.ij[2][1];
    aux.ij[0][2] = this->ij[0][0] * matrix.ij[0][2] + this->ij[0][1] * matrix.ij[1][2] + this->ij[0][2] * matrix.ij[2][2];

    aux.ij[1][0] = this->ij[1][0] * matrix.ij[0][0] + this->ij[1][1] * matrix.ij[1][0] + this->ij[1][2] * matrix.ij[2][0];
    aux.ij[1][1] = this->ij[1][0] * matrix.ij[0][1] + this->ij[1][1] * matrix.ij[1][1] + this->ij[1][2] * matrix.ij[2][1];
    aux.ij[1][2] = this->ij[1][0] * matrix.ij[0][2] + this->ij[1][1] * matrix.ij[1][2] + this->ij[1][2] * matrix.ij[2][2];

    aux.ij[2][0] = this->ij[2][0] * matrix.ij[0][0] + this->ij[2][1] * matrix.ij[1][0] + this->ij[2][2] * matrix.ij[2][0];
    aux.ij[2][1] = this->ij[2][0] * matrix.ij[0][1] + this->ij[2][1] * matrix.ij[1][1] + this->ij[2][2] * matrix.ij[2][1];
    aux.ij[2][2] = this->ij[2][0] * matrix.ij[0][2] + this->ij[2][1] * matrix.ij[1][2] + this->ij[2][2] * matrix.ij[2][2];

    return aux;
}

QTransformationMatrix<QMatrix4x4> QRotationMatrix3x3::operator*(const QTranslationMatrix<QMatrix4x4> &matrix) const
{
    return this->ProductOperatorImp<QMatrix4x4>(matrix);
}

QTransformationMatrix<QMatrix4x3> QRotationMatrix3x3::operator*(const QTranslationMatrix<QMatrix4x3> &matrix) const
{
    return this->ProductOperatorImp<QMatrix4x3>(matrix);
}

QTransformationMatrix<QMatrix4x4> QRotationMatrix3x3::operator*(const QScaleMatrix3x3 &matrix) const
{
    QTransformationMatrix<QMatrix4x4> aux;

    aux.ResetToIdentity();

    aux.ij[0][0] = matrix.ij[0][0] * this->ij[0][0] ;
    aux.ij[0][1] = matrix.ij[1][1] * this->ij[0][1];
    aux.ij[0][2] = matrix.ij[2][2] * this->ij[0][2];

    aux.ij[1][0] = matrix.ij[0][0] * this->ij[1][0];
    aux.ij[1][1] = matrix.ij[1][1] * this->ij[1][1];
    aux.ij[1][2] = matrix.ij[2][2] * this->ij[1][2];

    aux.ij[2][0] = matrix.ij[0][0] * this->ij[2][0];
    aux.ij[2][1] = matrix.ij[1][1] * this->ij[2][1];
    aux.ij[2][2] = matrix.ij[2][2] * this->ij[2][2];

    return aux;
}

QTransformationMatrix<QMatrix4x4> QRotationMatrix3x3::operator*(const QTransformationMatrix<QMatrix4x4> &matrix) const
{
    return this->ProductOperatorImp<QMatrix4x4>(matrix);
}

QTransformationMatrix<QMatrix4x3> QRotationMatrix3x3::operator*(const QTransformationMatrix<QMatrix4x3> &matrix) const
{
    return this->ProductOperatorImp<QMatrix4x3>(matrix);
}

void QRotationMatrix3x3::GetRotation(float_q &fRotationAngleX, float_q &fRotationAngleY, float_q &fRotationAngleZ) const
{
    const float_q &diff = SQFloat::_1 - SQFloat::Epsilon;

    if ( SQFloat::IsLessThan(this->ij[2][0], diff) )
    {
        if ( SQFloat::IsGreaterThan(this->ij[2][0], -diff ))
        {

            // Checkout ij[2][0] <= 1 not needed :)
            fRotationAngleY = asin_q(-this->ij[2][0]);

            // Checkout to avoid passing two zeros to atan2
            QE_ASSERT(this->ij[1][0] != SQFloat::_0 || this->ij[0][0] != SQFloat::_0)
            fRotationAngleZ = atan2_q(this->ij[1][0], this->ij[0][0]);

            // Checkout to avoid passing two zeros to atan2
            QE_ASSERT(this->ij[2][1] != SQFloat::_0 || this->ij[2][2] != SQFloat::_0)
            fRotationAngleX = atan2_q(this->ij[2][1], this->ij[2][2]);
        }
        else
        {
            fRotationAngleY = SQAngle::_HalfPi;

            // Checkout to avoid passing two zeros to atan2
            QE_ASSERT(this->ij[0][1] != SQFloat::_0 || this->ij[0][2] != SQFloat::_0)
            fRotationAngleZ = -atan2_q(this->ij[0][1], this->ij[0][2]);

            fRotationAngleX = SQFloat::_0;
        }
    }
    else
    {
        fRotationAngleY = -SQAngle::_HalfPi;

        // Checkout to avoid passing two zeros to atan2
        QE_ASSERT(this->ij[0][1] != SQFloat::_0 || this->ij[0][2] != SQFloat::_0)
        fRotationAngleZ = atan2_q(-this->ij[0][1], -this->ij[0][2]);

        fRotationAngleX = SQFloat::_0;
    }

    // Checkout to avoid NaN values
    QE_ASSERT( !SQFloat::IsNaN(fRotationAngleX) && !SQFloat::IsNaN(fRotationAngleY) && !SQFloat::IsNaN(fRotationAngleZ) )

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // Since angles are specified in radians, we convert it to degrees
        SQAngle::RadiansToDegrees(fRotationAngleX, fRotationAngleX);
        SQAngle::RadiansToDegrees(fRotationAngleY, fRotationAngleY);
        SQAngle::RadiansToDegrees(fRotationAngleZ, fRotationAngleZ);
    #endif
}

void QRotationMatrix3x3::GetRotation(QQuaternion &qRotation) const
{
    qRotation.w = sqrt_q( std::max(SQFloat::_0, SQFloat::_1 + this->ij[0][0] + this->ij[1][1] + this->ij[2][2]) ) * SQFloat::_0_5;
    qRotation.x = sqrt_q( std::max(SQFloat::_0, SQFloat::_1 + this->ij[0][0] - this->ij[1][1] - this->ij[2][2]) ) * SQFloat::_0_5;
    qRotation.y = sqrt_q( std::max(SQFloat::_0, SQFloat::_1 - this->ij[0][0] + this->ij[1][1] - this->ij[2][2]) ) * SQFloat::_0_5;
    qRotation.z = sqrt_q( std::max(SQFloat::_0, SQFloat::_1 - this->ij[0][0] - this->ij[1][1] + this->ij[2][2]) ) * SQFloat::_0_5;

    // [TODO] jwladi: it's necessary verify if this signs correspond to our conventions.
    SQFloat::CopySign(this->ij[2][1] - this->ij[1][2], qRotation.x);
    SQFloat::CopySign(this->ij[0][2] - this->ij[2][0], qRotation.y);
    SQFloat::CopySign(this->ij[1][0] - this->ij[0][1], qRotation.z);
}

void QRotationMatrix3x3::GetRotation(float_q &fRotationAngle, QBaseVector3 &vRotationAxis) const
{
    const float_q &cosAux = (this->ij[0][0] + this->ij[1][1] + this->ij[2][2] - SQFloat::_1) * SQFloat::_0_5;

    // Checkout to avoid undefined values of acos. Remember that -1 <= cos(angle) <= 1.
    QE_ASSERT( SQFloat::Abs(cosAux) <= SQFloat::_1 )

    fRotationAngle = acos_q(cosAux);

    // Singularity 1: Angle = 0 -> we choose arbitrary axis.
    if (SQFloat::IsZero(fRotationAngle))
    {
        vRotationAxis.x = SQFloat::_1;
        vRotationAxis.y = SQFloat::_0;
        vRotationAxis.z = SQFloat::_0;
    }
    // Singularity 2: Angle = PI -> we calculate axis.
    else if ( SQFloat::AreEquals(fRotationAngle, SQAngle::_Pi) )
    {
        const float_q &fHalfSqrt2 = sqrt_q(SQFloat::_2) * SQFloat::_0_5;

        const float_q &xx = (this->ij[0][0] + SQFloat::_1) * SQFloat::_0_5;
		const float_q &yy = (this->ij[1][1] + SQFloat::_1) * SQFloat::_0_5;
		const float_q &zz = (this->ij[2][2] + SQFloat::_1) * SQFloat::_0_5;

        // m[0][0] is the largest diagonal term
        if ( SQFloat::IsGreaterThan(xx, yy) && SQFloat::IsGreaterThan(xx, zz) )
        {
			if (SQFloat::IsZero(xx))
            {
				vRotationAxis.x = SQFloat::_0;
				vRotationAxis.y = fHalfSqrt2;
				vRotationAxis.z = fHalfSqrt2;
			}
            else
            {
                QE_ASSERT( SQFloat::IsGreaterThan(xx, SQFloat::_0) )

                vRotationAxis.x = sqrt_q(xx);

                const float_q &fInvX = SQFloat::_1 / vRotationAxis.x;
                const float_q &xy = (this->ij[0][1] + this->ij[1][0]) * SQFloat::_0_25;
		        const float_q &xz = (this->ij[0][2] + this->ij[2][0]) * SQFloat::_0_25;

                vRotationAxis.y = xy * fInvX;
				vRotationAxis.z = xz * fInvX;
			}
		}
        // m[1][1] is the largest diagonal term
        else if ( SQFloat::IsGreaterThan(yy, zz) )
        {
			if (SQFloat::IsZero(yy))
            {
				vRotationAxis.x = fHalfSqrt2;
				vRotationAxis.y = SQFloat::_0;
				vRotationAxis.z = fHalfSqrt2;
			}
            else
            {
                QE_ASSERT( SQFloat::IsGreaterThan(yy, SQFloat::_0) )

				vRotationAxis.y = sqrt_q(yy);

                const float_q &fInvY = SQFloat::_1 / vRotationAxis.y;
                const float_q &xy = (this->ij[0][1] + this->ij[1][0]) * SQFloat::_0_25;
		        const float_q &yz = (this->ij[1][2] + this->ij[2][1]) * SQFloat::_0_25;

                vRotationAxis.x = xy * fInvY;
				vRotationAxis.z = yz * fInvY;
			}
		}
        // m[2][2] is the largest diagonal term so base result on this
        else
        {
			if (SQFloat::IsZero(zz))
            {
				vRotationAxis.x = fHalfSqrt2;
				vRotationAxis.y = fHalfSqrt2;
				vRotationAxis.z = SQFloat::_0;
			}
            else
            {
                QE_ASSERT( SQFloat::IsGreaterThan(zz, SQFloat::_0) )

				vRotationAxis.z = sqrt_q(zz);

                const float_q &fInvZ = SQFloat::_1 / vRotationAxis.z;
                const float_q &xz = (this->ij[0][2] + this->ij[2][0]) * SQFloat::_0_25;
		        const float_q &yz = (this->ij[1][2] + this->ij[2][1]) * SQFloat::_0_25;

				vRotationAxis.x = xz * fInvZ;
				vRotationAxis.y = yz * fInvZ;
			}
		}

        #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
            // Since angles are specified in radians, we convert it to degrees
            fRotationAngle = SQAngle::_180;
        #endif
    }
    else
    {
        const float_q &fHalfInvSin = SQFloat::_0_5 / sin_q(fRotationAngle);

        vRotationAxis.x = (this->ij[2][1] - this->ij[1][2]) * fHalfInvSin;
        vRotationAxis.y = (this->ij[0][2] - this->ij[2][0]) * fHalfInvSin;
        vRotationAxis.z = (this->ij[1][0] - this->ij[0][1]) * fHalfInvSin;

        #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
            // Since angles are specified in radians, we convert it to degrees
            SQAngle::RadiansToDegrees(fRotationAngle, fRotationAngle);
        #endif
    }
}

float_q QRotationMatrix3x3::GetDeterminant()
{
	return SQFloat::_1;
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
