// [TERMS&CONDITIONS]

#include "QPlane.h"

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

QPlane QPlane::operator*(const float_q &fScalar) const
{
    return QPlane(this->a * fScalar, this->b * fScalar, this->c * fScalar, this->d * fScalar);
}

// Left float product
QPlane operator*(const float_q &fScalar, const QBasePlane &plane)
{
    return QPlane(plane.a * fScalar, plane.b * fScalar, plane.c * fScalar, plane.d * fScalar);
}

QPlane QPlane::operator/(const float_q &fScalar) const
{
    QE_ASSERT(fScalar != SQFloat::_0)

    const float_q &fDivisor = SQFloat::_1/fScalar;

    return QPlane(this->a * fDivisor, this->b * fDivisor, this->c * fDivisor, this->d * fDivisor);
}

QPlane QPlane::operator-() const
{
    return QPlane(-this->a, -this->b, -this->c, this->d);
}

float_q QPlane::DotProduct(const QVector3 &vVector) const
{
    return this->DotProductImp(vVector);
}

float_q QPlane::DotProduct(const QVector4 &vVector) const
{
    return this->DotProductImp(vVector);
}

float_q QPlane::DotProduct(const QBasePlane &plane) const
{
    return plane.a * this->a + plane.b * this->b + plane.c * this->c;
}

float_q QPlane::DotProductAngle(const QVector3 &vVector) const
{
    return this->DotProductAngleImp(vVector);
}

float_q QPlane::DotProductAngle(const QVector4 &vVector) const
{
    return this->DotProductAngleImp(vVector);
}

float_q QPlane::DotProductAngle(const QBasePlane &plane) const
{
    const float_q &fDot = this->DotProduct(plane);

    // Checkout to avoid undefined values of acos. Remember that -1 <= cos(angle) <= 1.
    QE_ASSERT(SQFloat::Abs(fDot) <= SQFloat::_1)

    const float_q& fAngle = acos_q(fDot);
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts angle to degrees
        fAngle = SQAngle::RadiansToDegrees(fAngle, fAngle);
    #endif

    return fAngle;
}

bool QPlane::Contains(const QBaseVector3 &vPoint) const
{
    return this->ContainsImp(vPoint);
}

bool QPlane::Contains(const QBaseVector4 &vPoint) const
{
    return this->ContainsImp(vPoint);
}

float_q QPlane::GetLength() const
{
    return sqrt_q(this->a * this->a + this->b * this->b + this->c * this->c);
}

float_q QPlane::GetSquaredLength() const
{
    return this->a * this->a + this->b * this->b + this->c * this->c;
}

float_q QPlane::PointDistance(const QBaseVector3 &vPoint) const
{
    return PointDistanceImp(vPoint);
}

float_q QPlane::PointDistance(const QBaseVector4 &vPoint) const
{
    return PointDistanceImp(vPoint);
}

EQIntersections QPlane::IntersectionPoint(const QBasePlane &plane1, const QBasePlane &plane2, QBaseVector3 &vIntersection) const
{
    return IntersectionPointImp(plane1, plane2, vIntersection);
}

EQIntersections QPlane::IntersectionPoint(const QBasePlane &plane1, const QBasePlane &plane2, QBaseVector4 &vIntersection) const
{
    return IntersectionPointImp(plane1, plane2, vIntersection);
}

EQSpaceRelation QPlane::SpaceRelation(const QBasePlane &plane) const
{
    // Cross product: checks if planes are parallel or coincident
    if (SQFloat::IsZero(plane.b * this->c - plane.c * this->b) &&
        SQFloat::IsZero(plane.c * this->a - plane.a * this->c) &&
        SQFloat::IsZero(plane.a * this->b - plane.b * this->a))
    {
        if (plane == *this) // They are the same plane.
            return EQSpaceRelation::E_Contained;
        else if (SQFloat::IsNegative(plane.d - this->d))
            return EQSpaceRelation::E_NegativeSide;
        else
            return EQSpaceRelation::E_PositiveSide;
    }
    else // Are not parallel
        return EQSpaceRelation::E_BothSides;
}

string_q QPlane::ToString() const
{
    return QE_L("PL(") + SQFloat::ToString(this->a) + QE_L(",") + SQFloat::ToString(this->b) +
           QE_L(",")   + SQFloat::ToString(this->c) + QE_L(",") + SQFloat::ToString(this->d) + QE_L(")");
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
