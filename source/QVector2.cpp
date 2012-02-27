// [TERMS&CONDITIONS]

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
	return SQFloat::AreEquals(this->x, SQFloat::_1) && SQFloat::AreEquals(this->y, SQFloat::_1);
}

float_q QVector2::DotProduct(const QVector2 &vVector) const
{
	return(this->x * vVector.x + this->y * vVector.y);
}

float_q QVector2::DotProductAngle(const QVector2 &vVector) const
{
    float_q fLengthProd = this->GetLength() * vVector.GetLength();

    // Checkout to avoid division by zero.
    QE_ASSERT(fLengthProd != SQFloat::_0)

    float_q fDot = this->DotProduct(vVector) / fLengthProd;

    QE_ASSERT(SQFloat::Abs(fDot) <= SQFloat::_1)

    float_q fAngle = acos_q(fDot);

	// At this stage we have the angle stored in fAngle expressed in RADIANS.

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts angle to degrees
        fAngle = SQAngle::RadiansToDegrees(fAngle);

		// At this stage we have the angle expressed in DEGREES.
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
