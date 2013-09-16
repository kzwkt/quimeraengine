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
QPlane operator*(const float_q &fScalar, const QPlane &plane)
{
    return QPlane(plane.a * fScalar, plane.b * fScalar, plane.c * fScalar, plane.d * fScalar);
}

QPlane QPlane::operator/(const float_q &fScalar) const
{
    QE_ASSERT(fScalar != SQFloat::_0)

    const float_q &DIVISOR = SQFloat::_1/fScalar;

    return QPlane(this->a * DIVISOR, this->b * DIVISOR, this->c * DIVISOR, this->d * DIVISOR);
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
    // When the length of a plane equals zero, the calculated angle is not correct
    QE_ASSERT( SQFloat::IsNotZero(this->GetSquaredLength()) && !(SQFloat::IsZero(plane.a) && SQFloat::IsZero(plane.b) && SQFloat::IsZero(plane.c)) );

    float_q DOT = this->DotProduct(plane);

    // Sometimes the result of the dot product is not accurate and must be clampped [-1, 1]
    if(DOT > SQFloat::_1)
        DOT = SQFloat::_1;
    else if(DOT < -SQFloat::_1)
        DOT = -SQFloat::_1;

    float_q fAngle = acos_q(DOT);

    QE_ASSERT( !SQFloat::IsNaN(fAngle) )
    
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts angle to degrees
        fAngle = SQAngle::RadiansToDegrees(fAngle);
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
    EQIntersections eNumIntersections = IntersectionPointImp(plane1, plane2, vIntersection);
    return eNumIntersections;
}

EQSpaceRelation QPlane::SpaceRelation(const QBasePlane &plane) const
{
    // It's impossible to calculate the spacial relation for a null plane
    QE_ASSERT( !(SQFloat::IsZero(this->a) && SQFloat::IsZero(this->b) && SQFloat::IsZero(this->c)) );
    QE_ASSERT( !(SQFloat::IsZero(plane.a) && SQFloat::IsZero(plane.b) && SQFloat::IsZero(plane.c)) );

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
