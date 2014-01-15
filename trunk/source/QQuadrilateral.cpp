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

#include "QQuadrilateral.h"

#include "QLineSegment2D.h"
#include "SQAngle.h"
#include "SQPoint.h"

using Kinesis::QuimeraEngine::Common::DataTypes::SQFloat;


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

QQuadrilateral::QQuadrilateral()
{
}

QQuadrilateral::QQuadrilateral(const QQuadrilateral &quad) : QBaseQuadrilateral(quad)
{
}

QQuadrilateral::QQuadrilateral(const QBaseQuadrilateral &quad) : QBaseQuadrilateral(quad)
{
}

QQuadrilateral::QQuadrilateral(const QVector2 &vA, const QVector2 &vB, const QVector2 &vC, const QVector2 &vD ) :
                                    QBaseQuadrilateral(vA, vB, vC, vD)
{
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |            METHODS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QQuadrilateral& QQuadrilateral::operator=(const QBaseQuadrilateral &quad)
{
    QBaseQuadrilateral::operator=(quad);
    return *this;
}

bool QQuadrilateral::Contains (const QBaseVector2 &vPoint) const
{
    if (this->IsConvex()) // Its convex
    {
        return (PointsInSameSideOfLine(vPoint, this->C, this->A, this->B) &&
                PointsInSameSideOfLine(vPoint, this->D, this->B, this->C) &&
                PointsInSameSideOfLine(vPoint, this->A, this->C, this->D) &&
                PointsInSameSideOfLine(vPoint, this->B, this->D, this->A));
    }
    else if (this->IsComplex()) // Its crossed
    {
        QLineSegment2D ls1(this->A, this->D), ls2(this->B, this->C);
        QVector2 vAux;

        if (ls1.IntersectionPoint(ls2, vAux) == EQIntersections::E_One) // Check if AD and BC edges cross themselves
        {
            // It checks both triangles (ABvAux and CDvAux)
            return (( PointsInSameSideOfLine(vPoint, vAux, this->A, this->B) &&
                      PointsInSameSideOfLine(vPoint, this->A, this->B, vAux) &&
                      PointsInSameSideOfLine(vPoint, this->B, vAux, this->A) ) ||
                    ( PointsInSameSideOfLine(vPoint, this->C, vAux, this->D) &&
                      PointsInSameSideOfLine(vPoint, vAux, this->D, this->C) &&
                      PointsInSameSideOfLine(vPoint, this->D, this->C, vAux) ));
        }
        else // AB and CD edges must cross themselves
        {
            // It checks both triangles (ADvAux and BCvAux)
            return (( PointsInSameSideOfLine(vPoint, this->A, vAux, this->D) &&
                  PointsInSameSideOfLine(vPoint, vAux, this->D, this->A) &&
                  PointsInSameSideOfLine(vPoint, this->D, this->A, vAux) ) ||
                ( PointsInSameSideOfLine(vPoint, this->B, this->C, vAux) &&
                  PointsInSameSideOfLine(vPoint, this->C, vAux, this->B) &&
                  PointsInSameSideOfLine(vPoint, vAux, this->B, this->C) ));
        }
    }
    else if (this->IsReflexAngle(this->A, this->B, this->D, this->C)) // Its concave in A vertex
    {
        // We check the two triangles around A vertex
        return (( PointsInSameSideOfLine(vPoint, this->C, this->A, this->B) &&
                  PointsInSameSideOfLine(vPoint, this->A, this->B, this->C) &&
                  PointsInSameSideOfLine(vPoint, this->B, this->C, this->A) ) ||
                ( PointsInSameSideOfLine(vPoint, this->C, this->A, this->D) &&
                  PointsInSameSideOfLine(vPoint, this->A, this->D, this->C) &&
                  PointsInSameSideOfLine(vPoint, this->D, this->C, this->A) ));
    }
    else if (this->IsReflexAngle(this->B, this->A, this->C, this->D)) // Its concave in B vertex
    {
        // We check the two triangles around B vertex
        return (( PointsInSameSideOfLine(vPoint, this->D, this->B, this->C) &&
                  PointsInSameSideOfLine(vPoint, this->B, this->C, this->D) &&
                  PointsInSameSideOfLine(vPoint, this->C, this->D, this->B) ) ||
                ( PointsInSameSideOfLine(vPoint, this->A, this->B, this->D) &&
                  PointsInSameSideOfLine(vPoint, this->B, this->D, this->A) &&
                  PointsInSameSideOfLine(vPoint, this->D, this->A, this->B) ));
    }
    else if (this->IsReflexAngle(this->C, this->B, this->D, this->A)) // Its concave in C vertex
    {
        // We check the two triangles around C vertex
        return (( PointsInSameSideOfLine(vPoint, this->A, this->C, this->D) &&
                  PointsInSameSideOfLine(vPoint, this->C, this->D, this->A) &&
                  PointsInSameSideOfLine(vPoint, this->D, this->A, this->C) ) ||
                ( PointsInSameSideOfLine(vPoint, this->B, this->C, this->A) &&
                  PointsInSameSideOfLine(vPoint, this->C, this->A, this->B) &&
                  PointsInSameSideOfLine(vPoint, this->A, this->B, this->C) ));
    }
    else // It must be concave in D vertex
    {
        // We check the two triangles around D vertex
        return (( PointsInSameSideOfLine(vPoint, this->B, this->D, this->A) &&
                  PointsInSameSideOfLine(vPoint, this->D, this->A, this->B) &&
                  PointsInSameSideOfLine(vPoint, this->A, this->B, this->D) ) ||
                ( PointsInSameSideOfLine(vPoint, this->C, this->D, this->B) &&
                  PointsInSameSideOfLine(vPoint, this->D, this->B, this->C) &&
                  PointsInSameSideOfLine(vPoint, this->B, this->C, this->D) ));
    }
}

bool QQuadrilateral::Intersection(const QBaseQuadrilateral &quad) const
{

    // Checks if any edge of resident quadrilateral intersects with q
    QLineSegment2D ls1(this->A, this->B);
    if ( ls1.Intersection(quad) )
        return true;

    ls1 = QLineSegment2D(this->B, this->C);
    if ( ls1.Intersection(quad) )
        return true;

    ls1 = QLineSegment2D(this->C, this->D);
    if ( ls1.Intersection(quad) )
        return true;

    ls1 = QLineSegment2D(this->D, this->A);
    if ( ls1.Intersection(quad) )
        return true;

    // q may be contained by resident quadrilateral, we check it.
    if ( this->Contains(quad.A) )
        return true;

    return false;
}

bool QQuadrilateral::IsComplex() const
{
    return ( ( !PointsInSameSideOfLine(this->A, this->D, this->B, this->C) &&
               !PointsInSameSideOfLine(this->C, this->B, this->A, this->D) ) ||
             ( !PointsInSameSideOfLine(this->A, this->B, this->D, this->C) &&
               !PointsInSameSideOfLine(this->C, this->D, this->A, this->B) ) );
}

bool QQuadrilateral::IsConvex() const
{
    QLineSegment2D ls1(this->A, this->C);
    QLineSegment2D ls2(this->B, this->D);

    return ls1.Intersection(ls2);
}

bool QQuadrilateral::IsConcave() const
{
    return !this->IsConvex();
}

float_q QQuadrilateral::GetAngleA() const
{
    // Contiguous vertices shouldn't coincide
    QE_ASSERT(this->A != this->B && this->A != this->D);

    const float_q &ANGLE = (this->D - this->A).AngleBetween(this->B - this->A);

    if (this->IsReflexAngle(this->A, this->B, this->D, this->C))
    {
        #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
            return SQAngle::_360 - ANGLE;
        #else
            return SQAngle::_2Pi - ANGLE;
        #endif
    }
    else
        return ANGLE;
}

float_q QQuadrilateral::GetAngleB() const
{
    // Contiguous vertices shouldn't coincide
    QE_ASSERT(this->B != this->A && this->B != this->C);

    const float_q &ANGLE = (this->A - this->B).AngleBetween(this->C - this->B);

    if (this->IsReflexAngle(this->B, this->A, this->C, this->D))
    {
        #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
            return SQAngle::_360 - ANGLE;
        #else
            return SQAngle::_2Pi - ANGLE;
        #endif
    }
    else
        return ANGLE;
}

float_q QQuadrilateral::GetAngleC() const
{
    // Contiguous vertices shouldn't coincide
    QE_ASSERT(this->C != this->B && this->C != this->D);

    const float_q &ANGLE = (this->B - this->C).AngleBetween(this->D - this->C);

    if (this->IsReflexAngle(this->C, this->B, this->D, this->A))
    {
        #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
            return SQAngle::_360 - ANGLE;
        #else
            return SQAngle::_2Pi - ANGLE;
        #endif
    }
    else
        return ANGLE;
}

float_q QQuadrilateral::GetAngleD() const
{
    // Contiguous vertices shouldn't coincide
    QE_ASSERT(this->D != this->A && this->D != this->C);

    const float_q &ANGLE = (this->C - this->D).AngleBetween(this->A - this->D);

    if (this->IsReflexAngle(this->D, this->A, this->C, this->B))
    {
        #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
            return SQAngle::_360 - ANGLE;
        #else
            return SQAngle::_2Pi - ANGLE;
        #endif
    }
    else
        return ANGLE;
}

QQuadrilateral QQuadrilateral::Rotate(const float_q &fRotationAngle) const
{
    QQuadrilateral auxQuadrilateral = *this;
    SQPoint::Rotate(fRotationAngle, rcast_q(&auxQuadrilateral, QVector2*), 4);
    return auxQuadrilateral;
}

QQuadrilateral QQuadrilateral::Translate(const QBaseVector2 &vTranslation) const
{
    QQuadrilateral auxQuadrilateral = *this;
    SQPoint::Translate(vTranslation, rcast_q(&auxQuadrilateral, QVector2*), 4);
    return auxQuadrilateral;
}

QQuadrilateral QQuadrilateral::Translate(const float_q &fTranslationX, const float_q &fTranslationY) const
{
    QQuadrilateral auxQuadrilateral = *this;
    SQPoint::Translate(fTranslationX, fTranslationY, rcast_q(&auxQuadrilateral, QVector2*), 4);
    return auxQuadrilateral;
}

QQuadrilateral QQuadrilateral::Scale(const QBaseVector2 &vScale) const
{
    QQuadrilateral auxQuadrilateral = *this;
    SQPoint::Scale(vScale, rcast_q(&auxQuadrilateral, QVector2*), 4);
    return auxQuadrilateral;
}

QQuadrilateral QQuadrilateral::Scale(const float_q &fScaleX, const float_q &fScaleY) const
{
    QQuadrilateral auxQuadrilateral = *this;
    SQPoint::Scale(fScaleX, fScaleY, rcast_q(&auxQuadrilateral, QVector2*), 4);
    return auxQuadrilateral;
}

QQuadrilateral QQuadrilateral::Transform(const QTransformationMatrix3x3 &transformation) const
{
    QQuadrilateral auxQuadrilateral = *this;
    SQPoint::Transform(transformation, rcast_q(&auxQuadrilateral, QVector2*), 4);
    return auxQuadrilateral;
}

QQuadrilateral QQuadrilateral::RotateWithPivot(const float_q &fRotationAngle, const QVector2 &vPivot) const
{
    QQuadrilateral auxQuadrilateral = *this;
    SQPoint::RotateWithPivot(fRotationAngle, vPivot, rcast_q(&auxQuadrilateral, QVector2*), 4);
    return auxQuadrilateral;
}

QQuadrilateral QQuadrilateral::ScaleWithPivot(const QBaseVector2 &vScale, const QBaseVector2 &vPivot) const
{
    QQuadrilateral auxQuadrilateral = *this;
    SQPoint::ScaleWithPivot(vScale, vPivot, rcast_q(&auxQuadrilateral, QVector2*), 4);
    return auxQuadrilateral;
}

QQuadrilateral QQuadrilateral::ScaleWithPivot(const float_q &fScaleX, const float_q &fScaleY, const QBaseVector2 &vPivot) const
{
    QQuadrilateral auxQuadrilateral = *this;
    SQPoint::ScaleWithPivot(fScaleX, fScaleY, vPivot, rcast_q(&auxQuadrilateral, QVector2*), 4);
    return auxQuadrilateral;
}

QQuadrilateral QQuadrilateral::TransformWithPivot(const QTransformationMatrix3x3 &transformation, const QBaseVector2 &vPivot) const
{
    QQuadrilateral auxQuadrilateral = *this;
    SQPoint::TransformWithPivot(transformation, vPivot, rcast_q(&auxQuadrilateral, QVector2*), 4);
    return auxQuadrilateral;
}

string_q QQuadrilateral::ToString() const
{
    return QE_L("QL(a(") + this->A.ToString() + QE_L("),b(") +
                           this->B.ToString() + QE_L("),c(") +
                           this->C.ToString() + QE_L("),d(") +
                           this->D.ToString() + QE_L("))");
}

bool QQuadrilateral::PointsInSameSideOfLine(const QBaseVector2 &vPoint1, const QBaseVector2 &vPoint2,
                                            const QBaseVector2 &vLine1, const QBaseVector2 &vLine2) const
{

    const float_q &ORIENTATION1 = (vLine1.x - vPoint1.x)*(vLine2.y - vPoint1.y) - (vLine1.y - vPoint1.y)*(vLine2.x - vPoint1.x);
    const float_q &ORIENTATION2 = (vLine1.x - vPoint2.x)*(vLine2.y - vPoint2.y) - (vLine1.y - vPoint2.y)*(vLine2.x - vPoint2.x);

    if ( SQFloat::IsZero(ORIENTATION1) || SQFloat::IsZero(ORIENTATION2) )
        return true;
    else
        return ( SQFloat::IsNegative(ORIENTATION1) == SQFloat::IsNegative(ORIENTATION2) );
}


bool QQuadrilateral::IsReflexAngle(const QVector2 &vAngleVertex, const QVector2 &vContiguousVertex1,
                                   const QVector2 &vContiguousVertex2, const QVector2 &vOppositeVertex) const
{
    if (this->IsConvex() || this->IsComplex()) // There isn't a concave angle.
        return false;
    else if ( !PointsInSameSideOfLine(vOppositeVertex, vAngleVertex, vContiguousVertex1, vContiguousVertex2) )
        return false; // The outer diagonal should not divide quadrilateral
    else
    {
        QLineSegment2D ls(vContiguousVertex1, vContiguousVertex2);

        // Angle vertex must be the closest to outer diagonal
        return ( ls.MinDistance(vAngleVertex) < ls.MinDistance(vOppositeVertex) );
    }
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

const QQuadrilateral& QQuadrilateral::GetUnitSquare()
{
    static const QQuadrilateral UNITSQUARE(QVector2(-SQFloat::_0_5,   SQFloat::_0_5),
                                           QVector2( SQFloat::_0_5,   SQFloat::_0_5),
                                           QVector2( SQFloat::_0_5,  -SQFloat::_0_5),
                                           QVector2(-SQFloat::_0_5,  -SQFloat::_0_5));
    return UNITSQUARE;
}


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
