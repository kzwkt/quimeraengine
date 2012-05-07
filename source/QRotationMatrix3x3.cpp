// [TERMS&CONDITIONS]

#include "QRotationMatrix3x3.h"

#include "QVector3.h"
#include "QQuaternion.h"
#include "QTranslationMatrix.h"
#include "QScalingMatrix3x3.h"
#include "QTransformationMatrix.h"
#include "SQAngle.h"

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
        const float_q& ANGLE_X_RAD = SQAngle::DegreesToRadians(fRotationAngleX);
        const float_q& ANGLE_Y_RAD = SQAngle::DegreesToRadians(fRotationAngleY);
        const float_q& ANGLE_Z_RAD = SQAngle::DegreesToRadians(fRotationAngleZ);

        const float_q& fA   = cos_q(ANGLE_X_RAD);
        const float_q& fB   = sin_q(ANGLE_X_RAD);
        const float_q& fC   = cos_q(ANGLE_Y_RAD);
        const float_q& fD   = sin_q(ANGLE_Y_RAD);
        const float_q& fE   = cos_q(ANGLE_Z_RAD);
        const float_q& fF   = sin_q(ANGLE_Z_RAD);
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
    // Taken from http://en.wikipedia.org/wiki/Rotation_representation#Rotation_matrix_.E2.86.94_Euler_axis.2Fangle
    // but changing factors affected by sinus to get a left handed matrix.

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        const float_q& ANGLE_RAD = SQAngle::DegreesToRadians(fRotationAngle);

        const float_q& fA = cos_q(ANGLE_RAD);
        const float_q& fB = sin_q(ANGLE_RAD);
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

QRotationMatrix3x3::QRotationMatrix3x3(const QBaseQuaternion &qRotation)
{
    // Taken from http://osdir.com/ml/games.devel.algorithms/2002-11/msg00318.html

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

QTransformationMatrix<QMatrix4x4> QRotationMatrix3x3::operator*(const QScalingMatrix3x3 &matrix) const
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
    const float_q &DIFF = SQFloat::_1 - SQFloat::Epsilon;

    if ( SQFloat::IsLessThan(this->ij[2][0], DIFF) )
    {
        if ( SQFloat::IsGreaterThan(this->ij[2][0], -DIFF ))
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
        fRotationAngleX = SQAngle::RadiansToDegrees(fRotationAngleX);
        fRotationAngleY = SQAngle::RadiansToDegrees(fRotationAngleY);
        fRotationAngleZ = SQAngle::RadiansToDegrees(fRotationAngleZ);
    #endif
}

void QRotationMatrix3x3::GetRotation(QQuaternion &qRotation) const
{
    // Source: http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/christian.htm

    // If the main diagonal is zero, the rotation matrix is not well-formed
    QE_ASSERT( SQFloat::IsNotZero(this->ij[0][0] + this->ij[1][1] + this->ij[2][2]) )

    qRotation.w = sqrt_q( std::max(SQFloat::_0, SQFloat::_1 + this->ij[0][0] + this->ij[1][1] + this->ij[2][2]) ) * SQFloat::_0_5;
    qRotation.x = sqrt_q( std::max(SQFloat::_0, SQFloat::_1 + this->ij[0][0] - this->ij[1][1] - this->ij[2][2]) ) * SQFloat::_0_5;
    qRotation.y = sqrt_q( std::max(SQFloat::_0, SQFloat::_1 - this->ij[0][0] + this->ij[1][1] - this->ij[2][2]) ) * SQFloat::_0_5;
    qRotation.z = sqrt_q( std::max(SQFloat::_0, SQFloat::_1 - this->ij[0][0] - this->ij[1][1] + this->ij[2][2]) ) * SQFloat::_0_5;

    // This sing depends on hand convention
    SQFloat::CopySign(this->ij[1][2] - this->ij[2][1], qRotation.x);
    SQFloat::CopySign(this->ij[2][0] - this->ij[0][2], qRotation.y);
    SQFloat::CopySign(this->ij[0][1] - this->ij[1][0], qRotation.z);
}

void QRotationMatrix3x3::GetRotation(float_q &fRotationAngle, QBaseVector3 &vRotationAxis) const
{
    // Source: http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToAngle/index.htm
    // Source: http://en.wikipedia.org/wiki/Rotation_representation_%28mathematics%29#Rotation_matrix_.E2.86.94_Euler_axis.2Fangle

    const float_q &COS_AUX = (this->ij[0][0] + this->ij[1][1] + this->ij[2][2] - SQFloat::_1) * SQFloat::_0_5;

    // Checkout to avoid undefined values of acos. Remember that -1 <= cos(angle) <= 1.
    QE_ASSERT( SQFloat::Abs(COS_AUX) <= SQFloat::_1 )

    fRotationAngle = acos_q(COS_AUX);

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
        const float_q &HALF_SQRT_2 = sqrt_q(SQFloat::_2) * SQFloat::_0_5;

        const float_q &XX = (this->ij[0][0] + SQFloat::_1) * SQFloat::_0_5;
		const float_q &YY = (this->ij[1][1] + SQFloat::_1) * SQFloat::_0_5;
		const float_q &ZZ = (this->ij[2][2] + SQFloat::_1) * SQFloat::_0_5;

        // m[0][0] is the largest diagonal term
        if ( SQFloat::IsGreaterThan(XX, YY) && SQFloat::IsGreaterThan(XX, ZZ) )
        {
			if (SQFloat::IsZero(XX))
            {
				vRotationAxis.x = SQFloat::_0;
				vRotationAxis.y = HALF_SQRT_2;
				vRotationAxis.z = HALF_SQRT_2;
			}
            else
            {
                QE_ASSERT( SQFloat::IsGreaterThan(XX, SQFloat::_0) )

                vRotationAxis.x = sqrt_q(XX);

                const float_q &INV_X = SQFloat::_1 / vRotationAxis.x;
                const float_q &XY = (this->ij[0][1] + this->ij[1][0]) * SQFloat::_0_25;
		        const float_q &XZ = (this->ij[0][2] + this->ij[2][0]) * SQFloat::_0_25;

                vRotationAxis.y = XY * INV_X;
				vRotationAxis.z = XZ * INV_X;
			}
		}
        // m[1][1] is the largest diagonal term
        else if ( SQFloat::IsGreaterThan(YY, ZZ) )
        {
			if (SQFloat::IsZero(YY))
            {
				vRotationAxis.x = HALF_SQRT_2;
				vRotationAxis.y = SQFloat::_0;
				vRotationAxis.z = HALF_SQRT_2;
			}
            else
            {
                QE_ASSERT( SQFloat::IsGreaterThan(YY, SQFloat::_0) )

				vRotationAxis.y = sqrt_q(YY);

                const float_q &INV_Y = SQFloat::_1 / vRotationAxis.y;
                const float_q &XY = (this->ij[0][1] + this->ij[1][0]) * SQFloat::_0_25;
		        const float_q &YZ = (this->ij[1][2] + this->ij[2][1]) * SQFloat::_0_25;

                vRotationAxis.x = XY * INV_Y;
				vRotationAxis.z = YZ * INV_Y;
			}
		}
        // m[2][2] is the largest diagonal term so base result on this
        else
        {
			if (SQFloat::IsZero(ZZ))
            {
				vRotationAxis.x = HALF_SQRT_2;
				vRotationAxis.y = HALF_SQRT_2;
				vRotationAxis.z = SQFloat::_0;
			}
            else
            {
                QE_ASSERT( SQFloat::IsGreaterThan(ZZ, SQFloat::_0) )

				vRotationAxis.z = sqrt_q(ZZ);

                const float_q &INV_Z = SQFloat::_1 / vRotationAxis.z;
                const float_q &XZ = (this->ij[0][2] + this->ij[2][0]) * SQFloat::_0_25;
		        const float_q &YZ = (this->ij[1][2] + this->ij[2][1]) * SQFloat::_0_25;

				vRotationAxis.x = XZ * INV_Z;
				vRotationAxis.y = YZ * INV_Z;
			}
		}

        #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
            // Since angles are specified in radians, we convert it to degrees
            fRotationAngle = SQAngle::_180;
        #endif
    }
    else
    {
        const float_q &HALF_INV_SIN = SQFloat::_0_5 / sin_q(fRotationAngle);

        vRotationAxis.x = (this->ij[2][1] - this->ij[1][2]) * HALF_INV_SIN;
        vRotationAxis.y = (this->ij[0][2] - this->ij[2][0]) * HALF_INV_SIN;
        vRotationAxis.z = (this->ij[1][0] - this->ij[0][1]) * HALF_INV_SIN;

        #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
            // Since angles are specified in radians, we convert it to degrees
            fRotationAngle = SQAngle::RadiansToDegrees(fRotationAngle);
        #endif
    }
}

float_q QRotationMatrix3x3::GetDeterminant() const
{
	return SQFloat::_1;
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
