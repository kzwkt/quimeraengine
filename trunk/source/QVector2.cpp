//-------------------------------------------------------------------------------//
//                         QUIMERA ENGINE : LICENSE                              //
//-------------------------------------------------------------------------------//
// This file is part of Quimera Engine.                                          //
// Quimera Engine is free software: you can redistribute it and/or modify        //
// it under the terms of the Lesser GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or             //
// (at your option) any later version.                                           //
//                                                                               //
// Quimera Engine is distributed in the hope that it will be useful,             //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// Lesser GNU General Public License for more details.                           //
//                                                                               //
// You should have received a copy of the Lesser GNU General Public License      //
// along with Quimera Engine. If not, see <http://www.gnu.org/licenses/>.        //
//                                                                               //
// This license doesn't force you to put any kind of banner or logo telling      //
// that you are using Quimera Engine in your project but we would appreciate     //
// if you do so or, at least, if you let us know about that.                     //
//                                                                               //
// Enjoy!                                                                        //
//                                                                               //
// Kinesis Team                                                                  //
//-------------------------------------------------------------------------------//

#include "QVector2.h"
#include "SQAngle.h"
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
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QVector2 QVector2::operator-() const
{
	return QVector2(-this->x, -this->y);
}

QVector2 QVector2::operator+(const QBaseVector2 &vVector) const
{
	return QVector2(this->x + vVector.x, this->y + vVector.y);
}

QVector2 QVector2::operator-(const QBaseVector2 &vVector) const
{
	return QVector2(this->x - vVector.x, this->y - vVector.y);
}

QVector2 QVector2::operator*(const float_q &fScalar) const
{
	return QVector2(this->x * fScalar, this->y * fScalar);
}

QVector2 QVector2::operator*(const QBaseVector2 &vVector) const
{
	return QVector2(this->x * vVector.x, this->y * vVector.y);
}

QVector2 QVector2::operator*(const QBaseMatrix2x2 &matrix) const
{
	return QVector2(this->x * matrix.ij[0][0] + this->y * matrix.ij[1][0],
                    this->x * matrix.ij[0][1] + this->y * matrix.ij[1][1]);
}

QVector2 QVector2::operator/(const float_q &fScalar) const
{
	// Checkout to avoid division by 0
	QE_ASSERT(fScalar)

	const float_q &fDivisor = SQFloat::_1/fScalar;

	return QVector2(this->x * fDivisor, this->y * fDivisor);
}

QVector2 QVector2::operator/(const QBaseVector2 &vVector) const
{
	// Checkout to avoid division by 0
	QE_ASSERT(vVector.x && vVector.y)

	return QVector2(this->x / vVector.x, this->y / vVector.y);
}

// Left float product
QVector2 operator*(const float_q &fScalar, const QVector2 &vVector)
{
	return QVector2(vVector.x * fScalar, vVector.y * fScalar);
}

float_q QVector2::GetLength() const
{
	return hypot_q(this->x, this->y);
}

float_q QVector2::GetSquaredLength() const
{
    return this->x*this->x + this->y*this->y;
}

QVector2 QVector2::GetPerpendicular() const
{
    return QVector2(this->y, -this->x);
}

bool QVector2::IsZero() const
{
	return SQFloat::IsZero(this->x) && SQFloat::IsZero(this->y);
}

bool QVector2::IsVectorOfOnes() const
{
	return SQFloat::AreEqual(this->x, SQFloat::_1) && SQFloat::AreEqual(this->y, SQFloat::_1);
}

float_q QVector2::DotProduct(const QVector2 &vVector) const
{
	return this->x * vVector.x + this->y * vVector.y;
}

float_q QVector2::DotProductAngle(const QVector2 &vVector) const
{
    // Note: Square root is performed outside to avoid loss of precision and gain performance
    float_q fLengthProd = sqrt_q(this->GetSquaredLength() * vVector.GetSquaredLength());

    // Checkout to avoid division by zero.
    QE_ASSERT(fLengthProd != SQFloat::_0);

    float_q fDot = this->DotProduct(vVector) / fLengthProd;

    // Sometimes the result of the dot product is not accurate and must be clampped [-1, 1]
    if(fDot > SQFloat::_1)
        fDot = SQFloat::_1;
    else if(fDot < -SQFloat::_1)
        fDot = -SQFloat::_1;

    float_q fAngle = acos_q(fDot);

    QE_ASSERT( !SQFloat::IsNaN(fAngle) );

	// At this stage we have the angle stored in fAngle expressed in RADIANS.

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts angle to degrees
        fAngle = SQAngle::RadiansToDegrees(fAngle);
    #endif

    return fAngle;
}

string_q QVector2::ToString() const
{
	return QE_L("V2(") + SQFloat::ToString(this->x) +
		   QE_L(",")  + SQFloat::ToString(this->y) +
		   QE_L(")");
}

QVector2 QVector2::Transform(const QTransformationMatrix3x3 &matrix) const
{
    return QVector2(this->x * matrix.ij[0][0] + this->y * matrix.ij[1][0] + matrix.ij[2][0],
                    this->x * matrix.ij[0][1] + this->y * matrix.ij[1][1] + matrix.ij[2][1]);
}

QVector2 QVector2::Transform(const float_q &fRotationAngle) const
{
	#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
		float_q fAngleRad = SQAngle::DegreesToRadians(fRotationAngle);
	#else
		float_q fAngleRad = fRotationAngle;
	#endif

	const float_q fCosAngle = cos_q(fAngleRad);
	const float_q fSinAngle = sin_q(fAngleRad);

    return QVector2(this->x * fCosAngle - this->y * fSinAngle, this->y * fCosAngle + this->x * fSinAngle);
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
