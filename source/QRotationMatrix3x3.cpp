// [TERMS&CONDITIONS]

#include "QRotationMatrix3x3.h"

#include "QVector3.h"
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

const QRotationMatrix3x3 QRotationMatrix3x3::Identity(  QFloat::_1, QFloat::_0, QFloat::_0,
                                                        QFloat::_0, QFloat::_1, QFloat::_0,
                                                        QFloat::_0, QFloat::_0, QFloat::_1);

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QRotationMatrix3x3::QRotationMatrix3x3 (const QBaseVector3 &vAxis, const float_q &fAngle)
{
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        float_q &fAngleRad = QAngle::DegreesToRadians(fAngle, fAngleRad);

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

    const float_q& F = (QFloat::_1 - A) * C;
    const float_q& G = (QFloat::_1 - A) * D;
    const float_q& H = (QFloat::_1 - A) * E;

    const float_q& I = vAux.x * B;
    const float_q& J = vAux.y * B;
    const float_q& K = vAux.z * B;

    this->ij[0][0] = A + (QFloat::_1 - A) * vAux.x * vAux.x;
    this->ij[0][1] = F - K;
    this->ij[0][2] = H + J;

    this->ij[1][0] = F + K;
    this->ij[1][1] = A + (QFloat::_1 - A) * vAux.y * vAux.y;
    this->ij[1][2] = G - I;

    this->ij[2][0] = H - J;
    this->ij[2][1] = G + I;
    this->ij[2][2] = A + (QFloat::_1 - A) * vAux.z * vAux.z;
}

QRotationMatrix3x3::QRotationMatrix3x3(const QBaseQuaternion &qQuat)
{
    const float_q& A   = QFloat::_2 * qQuat.x * qQuat.x;
    const float_q& B   = QFloat::_2 * qQuat.y * qQuat.y;
    const float_q& C   = QFloat::_2 * qQuat.z * qQuat.z;
        
    const float_q& D   = QFloat::_2 * qQuat.x * qQuat.y;
    const float_q& E   = QFloat::_2 * qQuat.x * qQuat.z;
    const float_q& F   = QFloat::_2 * qQuat.x * qQuat.w;
    const float_q& G   = QFloat::_2 * qQuat.y * qQuat.z;
    const float_q& H   = QFloat::_2 * qQuat.y * qQuat.w;
    const float_q& I   = QFloat::_2 * qQuat.z * qQuat.w;

    this->ij[0][0] = QFloat::_1 - B - C;
    this->ij[0][1] = D - I;
    this->ij[0][2] = E + H;

    this->ij[1][0] = D + I;
    this->ij[1][1] = QFloat::_1 - A - C;
    this->ij[1][2] = G - F;

    this->ij[2][0] = E - H;
    this->ij[2][1] = G + F;
    this->ij[2][2] = QFloat::_1 - A - B;
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

void QRotationMatrix3x3::GetRotation(float_q &fAngleX, float_q &fAngleY, float_q &fAngleZ) const
{
    const float_q &diff = QFloat::_1 - QFloat::Epsilon;

    if (this->ij[2][0] < diff)
    {
        if (this->ij[2][0] > -diff) {

            // Checkout ij[2][0] <= 1 not needed :)
            fAngleY = asin(-this->ij[2][0]);

            // Checkout to avoid passing two zeros to atan2
            QE_ASSERT(this->ij[1][0] != QFloat::_0 || this->ij[0][0] != QFloat::_0);
            fAngleZ = atan2(this->ij[1][0], this->ij[0][0]);

            // Checkout to avoid passing two zeros to atan2
            QE_ASSERT(this->ij[2][1] != QFloat::_0 || this->ij[2][2] != QFloat::_0);
            fAngleX = atan2(this->ij[2][1], this->ij[2][2]);
        }
        else
        {
            fAngleY = QAngle::_HalfPi;

            // Checkout to avoid passing two zeros to atan2
            QE_ASSERT(this->ij[0][1] != QFloat::_0 || this->ij[0][2] != QFloat::_0);
            fAngleZ = -atan2(this->ij[0][1], this->ij[0][2]);

            fAngleX = QFloat::_0;
        }
    }
    else
    {
        fAngleY = -QAngle::_HalfPi;

        // Checkout to avoid passing two zeros to atan2
        QE_ASSERT(this->ij[0][1] != QFloat::_0 || this->ij[0][2] != QFloat::_0);
        fAngleZ = atan2(-this->ij[0][1], -this->ij[0][2]);
            
        fAngleX = QFloat::_0;
    }

    // Checkout to avoid NaN values
    QE_ASSERT( !QFloat::IsNaN(fAngleX) && !QFloat::IsNaN(fAngleY) && !QFloat::IsNaN(fAngleZ) );

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // Since angles are specified in radians, we convert it to degrees
        QAngle::RadiansToDegrees(fAngleX, fAngleX);
        QAngle::RadiansToDegrees(fAngleY, fAngleY);
        QAngle::RadiansToDegrees(fAngleZ, fAngleZ);
    #endif
}

void QRotationMatrix3x3::GetRotation(QQuaternion &qQuat) const
{
    qQuat.w = sqrt( std::max(QFloat::_0, QFloat::_1 + this->ij[0][0] + this->ij[1][1] + this->ij[2][2]) ) * QFloat::_0_5;
    qQuat.x = sqrt( std::max(QFloat::_0, QFloat::_1 + this->ij[0][0] - this->ij[1][1] - this->ij[2][2]) ) * QFloat::_0_5;
    qQuat.y = sqrt( std::max(QFloat::_0, QFloat::_1 - this->ij[0][0] + this->ij[1][1] - this->ij[2][2]) ) * QFloat::_0_5;
    qQuat.z = sqrt( std::max(QFloat::_0, QFloat::_1 - this->ij[0][0] - this->ij[1][1] + this->ij[2][2]) ) * QFloat::_0_5;
        
    // [TODO] jwladi: it's necessary verify if this signs correspond to our conventions.
    QFloat::CopySign(this->ij[2][1] - this->ij[1][2], qQuat.x);
    QFloat::CopySign(this->ij[0][2] - this->ij[2][0], qQuat.y);
    QFloat::CopySign(this->ij[1][0] - this->ij[0][1], qQuat.z);
}

void QRotationMatrix3x3::GetRotation(float_q &fAngle, QBaseVector3 &vAxis) const
{
    const float_q &cosAux = (this->ij[0][0] + this->ij[1][1] + this->ij[2][2] - QFloat::_1) * QFloat::_0_5;

    // Checkout to avoid undefined values of acos. Remember that -1 <= cos(angle) <= 1.
    QE_ASSERT( abs(cosAux) <= QFloat::_1 );

    fAngle = acos(cosAux);
                
    // Singularity 1: Angle = 0 -> we choose arbitrary axis.
    if (QFloat::IsZero(fAngle)) 
    {
        vAxis.x = QFloat::_1;
        vAxis.y = QFloat::_0;
        vAxis.z = QFloat::_0;
    }
    // Singularity 2: Angle = PI -> we calculate axis.
    else if ( QFloat::AreEquals(fAngle, QAngle::_Pi) ) 
    {
        const float_q &fHalfSqrt2 = sqrt(QFloat::_2) * QFloat::_0_5;

        const float_q &xx = (this->ij[0][0] + QFloat::_1) * QFloat::_0_5;
		const float_q &yy = (this->ij[1][1] + QFloat::_1) * QFloat::_0_5;
		const float_q &zz = (this->ij[2][2] + QFloat::_1) * QFloat::_0_5;

        // m[0][0] is the largest diagonal term
		if ((xx > yy) && (xx > zz)) 
        { 
			if (QFloat::IsZero(xx))
            {
				vAxis.x = QFloat::_0;
				vAxis.y = fHalfSqrt2;
				vAxis.z = fHalfSqrt2;
			} 
            else
            {
                QE_ASSERT(xx > QFloat::_0);
                    
                vAxis.x = sqrt(xx);

                const float_q &fInvX = QFloat::_1 / vAxis.x;
                const float_q &xy = (this->ij[0][1] + this->ij[1][0]) * QFloat::_0_25;
		        const float_q &xz = (this->ij[0][2] + this->ij[2][0]) * QFloat::_0_25;
				    
                vAxis.y = xy * fInvX;
				vAxis.z = xz * fInvX;
			}
		}
        // m[1][1] is the largest diagonal term
        else if (yy > zz) 
        { 
			if (QFloat::IsZero(yy)) 
            {
				vAxis.x = fHalfSqrt2;
				vAxis.y = QFloat::_0;
				vAxis.z = fHalfSqrt2;
			} 
            else 
            {
                QE_ASSERT(yy > QFloat::_0);

				vAxis.y = sqrt(yy);
				    
                const float_q &fInvY = QFloat::_1 / vAxis.y;
                const float_q &xy = (this->ij[0][1] + this->ij[1][0]) * QFloat::_0_25;
		        const float_q &yz = (this->ij[1][2] + this->ij[2][1]) * QFloat::_0_25;
                
                vAxis.x = xy * fInvY;
				vAxis.z = yz * fInvY;
			}	
		} 
        // m[2][2] is the largest diagonal term so base result on this
        else
        { 
			if (QFloat::IsZero(zz)) 
            {
				vAxis.x = fHalfSqrt2;
				vAxis.y = fHalfSqrt2;
				vAxis.z = QFloat::_0;
			} 
            else 
            {
                QE_ASSERT(zz > QFloat::_0);

				vAxis.z = sqrt(zz);

                const float_q &fInvZ = QFloat::_1 / vAxis.z;
                const float_q &xz = (this->ij[0][2] + this->ij[2][0]) * QFloat::_0_25;
		        const float_q &yz = (this->ij[1][2] + this->ij[2][1]) * QFloat::_0_25;

				vAxis.x = xz * fInvZ;
				vAxis.y = yz * fInvZ;
			}
		}

        #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
            // Since angles are specified in radians, we convert it to degrees
            fAngle = QAngle::_180;
        #endif
    }
    else
    {
        const float_q &fHalfInvSin = QFloat::_0_5/sin(fAngle);

        vAxis.x = (this->ij[2][1] - this->ij[1][2]) * fHalfInvSin;
        vAxis.y = (this->ij[0][2] - this->ij[2][0]) * fHalfInvSin;
        vAxis.z = (this->ij[1][0] - this->ij[0][1]) * fHalfInvSin;

        #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
            // Since angles are specified in radians, we convert it to degrees
            QAngle::RadiansToDegrees(fAngle, fAngle);
        #endif
    }
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
