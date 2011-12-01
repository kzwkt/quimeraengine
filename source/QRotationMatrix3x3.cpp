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
//##################		    |  CONSTANTS INITIALIZATION  |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

const QRotationMatrix3x3 QRotationMatrix3x3::Identity(  SQFloat::_1, SQFloat::_0, SQFloat::_0,
                                                        SQFloat::_0, SQFloat::_1, SQFloat::_0,
                                                        SQFloat::_0, SQFloat::_0, SQFloat::_1);

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QRotationMatrix3x3::QRotationMatrix3x3(const float_q &fAngleX, const float_q &fAngleY, const float_q &fAngleZ)
{

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        float_q &fAngleXRad = SQAngle::DegreesToRadians(fAngleX, fAngleXRad);
        float_q &fAngleYRad = SQAngle::DegreesToRadians(fAngleY, fAngleYRad);
        float_q &fAngleZRad = SQAngle::DegreesToRadians(fAngleZ, fAngleZRad);

        const float_q& A   = cos(fAngleXRad);
        const float_q& B   = sin(fAngleXRad);
        const float_q& C   = cos(fAngleYRad);
        const float_q& D   = sin(fAngleYRad);
        const float_q& E   = cos(fAngleZRad);
        const float_q& F   = sin(fAngleZRad);
    #else
        const float_q& A   = cos(fAngleX);
        const float_q& B   = sin(fAngleX);
        const float_q& C   = cos(fAngleY);
        const float_q& D   = sin(fAngleY);
        const float_q& E   = cos(fAngleZ);
        const float_q& F   = sin(fAngleZ);
    #endif

    float_q BC  = B*C;
    float_q BD  = B*D;

    ij[0][0]  =  E*C - F*BD;
    ij[0][1]  = -A*F;
    ij[0][2]  =  E*D + F*BC;

    ij[1][0]  =  F*C + E*BD;
    ij[1][1]  =  A*E;
    ij[1][2]  =  F*D - E*BC;

    ij[2][0]  =  -A*D;
    ij[2][1]  =  B;
    ij[2][2]  =  A*C;
}

QRotationMatrix3x3::QRotationMatrix3x3 (const QBaseVector3 &vAxis, const float_q &fAngle)
{
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        float_q &fAngleRad = SQAngle::DegreesToRadians(fAngle, fAngleRad);

        const float_q& A = cos(fAngleRad);
        const float_q& B = sin(fAngleRad);
    #else
        const float_q& A = cos(fAngle);
        const float_q& B = sin(fAngle);
    #endif

    QVector3 vAux(vAxis);

    vAux.Normalize();

    const float_q& C = vAux.x*vAux.y;
    const float_q& D = vAux.y*vAux.z;
    const float_q& E = vAux.z*vAux.x;

    const float_q& F = (SQFloat::_1 - A) * C;
    const float_q& G = (SQFloat::_1 - A) * D;
    const float_q& H = (SQFloat::_1 - A) * E;

    const float_q& I = vAux.x * B;
    const float_q& J = vAux.y * B;
    const float_q& K = vAux.z * B;

    this->ij[0][0] = A + (SQFloat::_1 - A) * vAux.x * vAux.x;
    this->ij[0][1] = F - K;
    this->ij[0][2] = H + J;

    this->ij[1][0] = F + K;
    this->ij[1][1] = A + (SQFloat::_1 - A) * vAux.y * vAux.y;
    this->ij[1][2] = G - I;

    this->ij[2][0] = H - J;
    this->ij[2][1] = G + I;
    this->ij[2][2] = A + (SQFloat::_1 - A) * vAux.z * vAux.z;
}

QRotationMatrix3x3::QRotationMatrix3x3(const QBaseQuaternion &qQuat)
{
    const float_q& A   = SQFloat::_2 * qQuat.x * qQuat.x;
    const float_q& B   = SQFloat::_2 * qQuat.y * qQuat.y;
    const float_q& C   = SQFloat::_2 * qQuat.z * qQuat.z;

    const float_q& D   = SQFloat::_2 * qQuat.x * qQuat.y;
    const float_q& E   = SQFloat::_2 * qQuat.x * qQuat.z;
    const float_q& F   = SQFloat::_2 * qQuat.x * qQuat.w;
    const float_q& G   = SQFloat::_2 * qQuat.y * qQuat.z;
    const float_q& H   = SQFloat::_2 * qQuat.y * qQuat.w;
    const float_q& I   = SQFloat::_2 * qQuat.z * qQuat.w;

    this->ij[0][0] = SQFloat::_1 - B - C;
    this->ij[0][1] = D - I;
    this->ij[0][2] = E + H;

    this->ij[1][0] = D + I;
    this->ij[1][1] = SQFloat::_1 - A - C;
    this->ij[1][2] = G - F;

    this->ij[2][0] = E - H;
    this->ij[2][1] = G + F;
    this->ij[2][2] = SQFloat::_1 - A - B;
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

QRotationMatrix3x3 QRotationMatrix3x3::operator*(const QRotationMatrix3x3 &m) const
{
    QRotationMatrix3x3 aux;

    aux.ij[0][0] = this->ij[0][0]*m.ij[0][0] + this->ij[0][1]*m.ij[1][0] + this->ij[0][2]*m.ij[2][0];
    aux.ij[0][1] = this->ij[0][0]*m.ij[0][1] + this->ij[0][1]*m.ij[1][1] + this->ij[0][2]*m.ij[2][1];
    aux.ij[0][2] = this->ij[0][0]*m.ij[0][2] + this->ij[0][1]*m.ij[1][2] + this->ij[0][2]*m.ij[2][2];

    aux.ij[1][0] = this->ij[1][0]*m.ij[0][0] + this->ij[1][1]*m.ij[1][0] + this->ij[1][2]*m.ij[2][0];
    aux.ij[1][1] = this->ij[1][0]*m.ij[0][1] + this->ij[1][1]*m.ij[1][1] + this->ij[1][2]*m.ij[2][1];
    aux.ij[1][2] = this->ij[1][0]*m.ij[0][2] + this->ij[1][1]*m.ij[1][2] + this->ij[1][2]*m.ij[2][2];

    aux.ij[2][0] = this->ij[2][0]*m.ij[0][0] + this->ij[2][1]*m.ij[1][0] + this->ij[2][2]*m.ij[2][0];
    aux.ij[2][1] = this->ij[2][0]*m.ij[0][1] + this->ij[2][1]*m.ij[1][1] + this->ij[2][2]*m.ij[2][1];
    aux.ij[2][2] = this->ij[2][0]*m.ij[0][2] + this->ij[2][1]*m.ij[1][2] + this->ij[2][2]*m.ij[2][2];

    return aux;
}

QTransformationMatrix<QMatrix4x4> QRotationMatrix3x3::operator*(const QTranslationMatrix<QMatrix4x4> &m) const
{
    QTransformationMatrix<QMatrix4x4> aux(QTransformationMatrix<QMatrix4x4>::Identity);

    aux.ij[3][0] = m.ij[3][0];
    aux.ij[3][1] = m.ij[3][1];
    aux.ij[3][2] = m.ij[3][2];

    aux.ij[0][0] = this->ij[0][0];
    aux.ij[0][1] = this->ij[0][1];
    aux.ij[0][2] = this->ij[0][2];

    aux.ij[1][0] = this->ij[1][0];
    aux.ij[1][1] = this->ij[1][1];
    aux.ij[1][2] = this->ij[1][2];

    aux.ij[2][0] = this->ij[2][0];
    aux.ij[2][1] = this->ij[2][1];
    aux.ij[2][2] = this->ij[2][2];

    return aux;
}

QTransformationMatrix<QMatrix4x3> QRotationMatrix3x3::operator*(const QTranslationMatrix<QMatrix4x3> &m) const
{
    QTransformationMatrix<QMatrix4x3> aux(QTransformationMatrix<QMatrix4x3>::Identity);

    aux.ij[3][0] = m.ij[3][0];
    aux.ij[3][1] = m.ij[3][1];
    aux.ij[3][2] = m.ij[3][2];

    aux.ij[0][0] = this->ij[0][0];
    aux.ij[0][1] = this->ij[0][1];
    aux.ij[0][2] = this->ij[0][2];

    aux.ij[1][0] = this->ij[1][0];
    aux.ij[1][1] = this->ij[1][1];
    aux.ij[1][2] = this->ij[1][2];

    aux.ij[2][0] = this->ij[2][0];
    aux.ij[2][1] = this->ij[2][1];
    aux.ij[2][2] = this->ij[2][2];

    return aux;
}

QTransformationMatrix<QMatrix4x4> QRotationMatrix3x3::operator*(const QScaleMatrix3x3 &m) const
{
    QTransformationMatrix<QMatrix4x4> aux;

    aux.ResetToIdentity();

    aux.ij[0][0] = m.ij[0][0]*this->ij[0][0] ;
    aux.ij[0][1] = m.ij[1][1]*this->ij[0][1];
    aux.ij[0][2] = m.ij[2][2]*this->ij[0][2];

    aux.ij[1][0] = m.ij[0][0]*this->ij[1][0];
    aux.ij[1][1] = m.ij[1][1]*this->ij[1][1];
    aux.ij[1][2] = m.ij[2][2]*this->ij[1][2];

    aux.ij[2][0] = m.ij[0][0]*this->ij[2][0];
    aux.ij[2][1] = m.ij[1][1]*this->ij[2][1];
    aux.ij[2][2] = m.ij[2][2]*this->ij[2][2];

    return aux;
}

QTransformationMatrix<QMatrix4x4> QRotationMatrix3x3::operator*(const QTransformationMatrix<QMatrix4x4> &m) const
{
    QTransformationMatrix<QMatrix4x4> aux(QTransformationMatrix<QMatrix4x4>::Identity);

    aux.ij[3][0] = m.ij[3][0];
    aux.ij[3][1] = m.ij[3][1];
    aux.ij[3][2] = m.ij[3][2];

    aux.ij[0][0] = this->ij[0][0]*m.ij[0][0] + this->ij[0][1]*m.ij[1][0] + this->ij[0][2]*m.ij[2][0];
    aux.ij[0][1] = this->ij[0][0]*m.ij[0][1] + this->ij[0][1]*m.ij[1][1] + this->ij[0][2]*m.ij[2][1];
    aux.ij[0][2] = this->ij[0][0]*m.ij[0][2] + this->ij[0][1]*m.ij[1][2] + this->ij[0][2]*m.ij[2][2];

    aux.ij[1][0] = this->ij[1][0]*m.ij[0][0] + this->ij[1][1]*m.ij[1][0] + this->ij[1][2]*m.ij[2][0];
    aux.ij[1][1] = this->ij[1][0]*m.ij[0][1] + this->ij[1][1]*m.ij[1][1] + this->ij[1][2]*m.ij[2][1];
    aux.ij[1][2] = this->ij[1][0]*m.ij[0][2] + this->ij[1][1]*m.ij[1][2] + this->ij[1][2]*m.ij[2][2];

    aux.ij[2][0] = this->ij[2][0]*m.ij[0][0] + this->ij[2][1]*m.ij[1][0] + this->ij[2][2]*m.ij[2][0];
    aux.ij[2][1] = this->ij[2][0]*m.ij[0][1] + this->ij[2][1]*m.ij[1][1] + this->ij[2][2]*m.ij[2][1];
    aux.ij[2][2] = this->ij[2][0]*m.ij[0][2] + this->ij[2][1]*m.ij[1][2] + this->ij[2][2]*m.ij[2][2];

    return aux;
}

QTransformationMatrix<QMatrix4x3> QRotationMatrix3x3::operator*(const QTransformationMatrix<QMatrix4x3> &m) const
{
    QTransformationMatrix<QMatrix4x3> aux(QTransformationMatrix<QMatrix4x3>::Identity);

    aux.ij[3][0] = m.ij[3][0];
    aux.ij[3][1] = m.ij[3][1];
    aux.ij[3][2] = m.ij[3][2];

    aux.ij[0][0] = this->ij[0][0]*m.ij[0][0] + this->ij[0][1]*m.ij[1][0] + this->ij[0][2]*m.ij[2][0];
    aux.ij[0][1] = this->ij[0][0]*m.ij[0][1] + this->ij[0][1]*m.ij[1][1] + this->ij[0][2]*m.ij[2][1];
    aux.ij[0][2] = this->ij[0][0]*m.ij[0][2] + this->ij[0][1]*m.ij[1][2] + this->ij[0][2]*m.ij[2][2];

    aux.ij[1][0] = this->ij[1][0]*m.ij[0][0] + this->ij[1][1]*m.ij[1][0] + this->ij[1][2]*m.ij[2][0];
    aux.ij[1][1] = this->ij[1][0]*m.ij[0][1] + this->ij[1][1]*m.ij[1][1] + this->ij[1][2]*m.ij[2][1];
    aux.ij[1][2] = this->ij[1][0]*m.ij[0][2] + this->ij[1][1]*m.ij[1][2] + this->ij[1][2]*m.ij[2][2];

    aux.ij[2][0] = this->ij[2][0]*m.ij[0][0] + this->ij[2][1]*m.ij[1][0] + this->ij[2][2]*m.ij[2][0];
    aux.ij[2][1] = this->ij[2][0]*m.ij[0][1] + this->ij[2][1]*m.ij[1][1] + this->ij[2][2]*m.ij[2][1];
    aux.ij[2][2] = this->ij[2][0]*m.ij[0][2] + this->ij[2][1]*m.ij[1][2] + this->ij[2][2]*m.ij[2][2];

    return aux;
}

void QRotationMatrix3x3::GetRotation(float_q &fAngleX, float_q &fAngleY, float_q &fAngleZ) const
{
    const float_q &diff = SQFloat::_1 - SQFloat::Epsilon;

    if ( SQFloat::IsLessThan(this->ij[2][0], diff) )
    {
        if ( SQFloat::IsGreaterThan(this->ij[2][0], -diff ))
        {

            // Checkout ij[2][0] <= 1 not needed :)
            fAngleY = asin(-this->ij[2][0]);

            // Checkout to avoid passing two zeros to atan2
            QE_ASSERT(this->ij[1][0] != SQFloat::_0 || this->ij[0][0] != SQFloat::_0);
            fAngleZ = atan2(this->ij[1][0], this->ij[0][0]);

            // Checkout to avoid passing two zeros to atan2
            QE_ASSERT(this->ij[2][1] != SQFloat::_0 || this->ij[2][2] != SQFloat::_0);
            fAngleX = atan2(this->ij[2][1], this->ij[2][2]);
        }
        else
        {
            fAngleY = SQAngle::_HalfPi;

            // Checkout to avoid passing two zeros to atan2
            QE_ASSERT(this->ij[0][1] != SQFloat::_0 || this->ij[0][2] != SQFloat::_0);
            fAngleZ = -atan2(this->ij[0][1], this->ij[0][2]);

            fAngleX = SQFloat::_0;
        }
    }
    else
    {
        fAngleY = -SQAngle::_HalfPi;

        // Checkout to avoid passing two zeros to atan2
        QE_ASSERT(this->ij[0][1] != SQFloat::_0 || this->ij[0][2] != SQFloat::_0);
        fAngleZ = atan2(-this->ij[0][1], -this->ij[0][2]);

        fAngleX = SQFloat::_0;
    }

    // Checkout to avoid NaN values
    QE_ASSERT( !SQFloat::IsNaN(fAngleX) && !SQFloat::IsNaN(fAngleY) && !SQFloat::IsNaN(fAngleZ) );

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // Since angles are specified in radians, we convert it to degrees
        SQAngle::RadiansToDegrees(fAngleX, fAngleX);
        SQAngle::RadiansToDegrees(fAngleY, fAngleY);
        SQAngle::RadiansToDegrees(fAngleZ, fAngleZ);
    #endif
}

void QRotationMatrix3x3::GetRotation(QQuaternion &qQuat) const
{
    qQuat.w = sqrt( std::max(SQFloat::_0, SQFloat::_1 + this->ij[0][0] + this->ij[1][1] + this->ij[2][2]) ) * SQFloat::_0_5;
    qQuat.x = sqrt( std::max(SQFloat::_0, SQFloat::_1 + this->ij[0][0] - this->ij[1][1] - this->ij[2][2]) ) * SQFloat::_0_5;
    qQuat.y = sqrt( std::max(SQFloat::_0, SQFloat::_1 - this->ij[0][0] + this->ij[1][1] - this->ij[2][2]) ) * SQFloat::_0_5;
    qQuat.z = sqrt( std::max(SQFloat::_0, SQFloat::_1 - this->ij[0][0] - this->ij[1][1] + this->ij[2][2]) ) * SQFloat::_0_5;

    // [TODO] jwladi: it's necessary verify if this signs correspond to our conventions.
    SQFloat::CopySign(this->ij[2][1] - this->ij[1][2], qQuat.x);
    SQFloat::CopySign(this->ij[0][2] - this->ij[2][0], qQuat.y);
    SQFloat::CopySign(this->ij[1][0] - this->ij[0][1], qQuat.z);
}

void QRotationMatrix3x3::GetRotation(float_q &fAngle, QBaseVector3 &vAxis) const
{
    const float_q &cosAux = (this->ij[0][0] + this->ij[1][1] + this->ij[2][2] - SQFloat::_1) * SQFloat::_0_5;

    // Checkout to avoid undefined values of acos. Remember that -1 <= cos(angle) <= 1.
    QE_ASSERT( SQFloat::Abs(cosAux) <= SQFloat::_1 );

    fAngle = acos(cosAux);

    // Singularity 1: Angle = 0 -> we choose arbitrary axis.
    if (SQFloat::IsZero(fAngle))
    {
        vAxis.x = SQFloat::_1;
        vAxis.y = SQFloat::_0;
        vAxis.z = SQFloat::_0;
    }
    // Singularity 2: Angle = PI -> we calculate axis.
    else if ( SQFloat::AreEquals(fAngle, SQAngle::_Pi) )
    {
        const float_q &fHalfSqrt2 = sqrt(SQFloat::_2) * SQFloat::_0_5;

        const float_q &xx = (this->ij[0][0] + SQFloat::_1) * SQFloat::_0_5;
		const float_q &yy = (this->ij[1][1] + SQFloat::_1) * SQFloat::_0_5;
		const float_q &zz = (this->ij[2][2] + SQFloat::_1) * SQFloat::_0_5;

        // m[0][0] is the largest diagonal term
        if ( SQFloat::IsGreaterThan(xx, yy) && SQFloat::IsGreaterThan(xx, zz) )
        {
			if (SQFloat::IsZero(xx))
            {
				vAxis.x = SQFloat::_0;
				vAxis.y = fHalfSqrt2;
				vAxis.z = fHalfSqrt2;
			}
            else
            {
                QE_ASSERT( SQFloat::IsGreaterThan(xx, SQFloat::_0) );

                vAxis.x = sqrt(xx);

                const float_q &fInvX = SQFloat::_1 / vAxis.x;
                const float_q &xy = (this->ij[0][1] + this->ij[1][0]) * SQFloat::_0_25;
		        const float_q &xz = (this->ij[0][2] + this->ij[2][0]) * SQFloat::_0_25;

                vAxis.y = xy * fInvX;
				vAxis.z = xz * fInvX;
			}
		}
        // m[1][1] is the largest diagonal term
        else if ( SQFloat::IsGreaterThan(yy, zz) )
        {
			if (SQFloat::IsZero(yy))
            {
				vAxis.x = fHalfSqrt2;
				vAxis.y = SQFloat::_0;
				vAxis.z = fHalfSqrt2;
			}
            else
            {
                QE_ASSERT( SQFloat::IsGreaterThan(yy, SQFloat::_0) );

				vAxis.y = sqrt(yy);

                const float_q &fInvY = SQFloat::_1 / vAxis.y;
                const float_q &xy = (this->ij[0][1] + this->ij[1][0]) * SQFloat::_0_25;
		        const float_q &yz = (this->ij[1][2] + this->ij[2][1]) * SQFloat::_0_25;

                vAxis.x = xy * fInvY;
				vAxis.z = yz * fInvY;
			}
		}
        // m[2][2] is the largest diagonal term so base result on this
        else
        {
			if (SQFloat::IsZero(zz))
            {
				vAxis.x = fHalfSqrt2;
				vAxis.y = fHalfSqrt2;
				vAxis.z = SQFloat::_0;
			}
            else
            {
                QE_ASSERT( SQFloat::IsGreaterThan(zz, SQFloat::_0) );

				vAxis.z = sqrt(zz);

                const float_q &fInvZ = SQFloat::_1 / vAxis.z;
                const float_q &xz = (this->ij[0][2] + this->ij[2][0]) * SQFloat::_0_25;
		        const float_q &yz = (this->ij[1][2] + this->ij[2][1]) * SQFloat::_0_25;

				vAxis.x = xz * fInvZ;
				vAxis.y = yz * fInvZ;
			}
		}

        #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
            // Since angles are specified in radians, we convert it to degrees
            fAngle = SQAngle::_180;
        #endif
    }
    else
    {
        const float_q &fHalfInvSin = SQFloat::_0_5/sin(fAngle);

        vAxis.x = (this->ij[2][1] - this->ij[1][2]) * fHalfInvSin;
        vAxis.y = (this->ij[0][2] - this->ij[2][0]) * fHalfInvSin;
        vAxis.z = (this->ij[1][0] - this->ij[0][1]) * fHalfInvSin;

        #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
            // Since angles are specified in radians, we convert it to degrees
            SQAngle::RadiansToDegrees(fAngle, fAngle);
        #endif
    }
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
