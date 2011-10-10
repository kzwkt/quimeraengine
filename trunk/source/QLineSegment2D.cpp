// [TERMS&CONDITIONS]

#include "QBaseTriangle.h"
#include "QBaseQuadrilateral.h"

#include "QTransformationMatrix3x3.h"

#include "QLineSegment2D.h"

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
const QLineSegment2D QLineSegment2D::UnitLine(QVector2::ZeroVector, QVector2::UnitVectorX);
const QLineSegment2D QLineSegment2D::LineZero(QVector2::ZeroVector, QVector2::ZeroVector);


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

bool QLineSegment2D::Intersection (const QBaseTriangle2& triangl) const
{
	// Just checking if the segment instersects with any edge of the triangle.

	if ( this->Intersection(QLineSegment2D(triangl.A, triangl.B)) ||
         this->Intersection(QLineSegment2D(triangl.B, triangl.C)) ||
         this->Intersection(QLineSegment2D(triangl.C, triangl.A)) )
        return true;
    else if (this->PointInsideTriangle(triangl, this->A))
        return true;
    else
        return false;
}

bool QLineSegment2D::Intersection (const QBaseQuadrilateral& quadrl) const
{
	if ( this->Intersection(QLineSegment2D(quadrl.A, quadrl.B)) ||
         this->Intersection(QLineSegment2D(quadrl.B, quadrl.C)) ||
         this->Intersection(QLineSegment2D(quadrl.C, quadrl.D)) ||
         this->Intersection(QLineSegment2D(quadrl.D, quadrl.A)))
        return true;
    else if (this->PointInsideQuadrilateral(quadrl, this->A))
        return true;
    else
        return false;
}

EQIntersections QLineSegment2D::IntersectionPoint(const QBaseTriangle2& triangle, QBaseVector2& vPoint1, QBaseVector2& vPoint2) const
{
    const bool &bAIsInside = PointInsideTriangle(triangle, this->A);
    const bool &bBIsInside = PointInsideTriangle(triangle, this->B);

    if (bAIsInside && bBIsInside) // Both line segment end points are inside triangle.
    {
        // A or B are vertex
        const bool &bAIsVertex = (this->A == triangle.A || this->A == triangle.B || this->A == triangle.C);
        const bool &bBIsVertex = (this->B == triangle.A || this->B == triangle.B || this->B == triangle.C);

        if (bAIsVertex && bBIsVertex) // Both endpoints are vertices of triangle
        {
            vPoint1 = this->A;
            vPoint2 = this->B;
            return EQIntersections::E_Two;
        }
        else if (bAIsVertex) // Only A endpoint is a vertex of triangle
        {
            vPoint1 = this->A;

            if (QFloat::IsZero(QLineSegment2D(triangle.A, triangle.B).MinDistance(this->B))) // B is in AB triangle edge
            {
                if (this->A == triangle.A || this->A == triangle.B) // A and B are in the same edge
                    return EQIntersections::E_One;
                else
                {
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
            }
            else if (QFloat::IsZero(QLineSegment2D(triangle.B, triangle.C).MinDistance(this->B))) // B is in BC triangle edge
            {
                if (this->A == triangle.B || this->A == triangle.C) // A and B are in the same edge
                    return EQIntersections::E_One;
                else
                {
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
            }
            else if (QFloat::IsZero(QLineSegment2D(triangle.C, triangle.A).MinDistance(this->B))) // B is in CA triangle edge
            {
                if (this->A == triangle.C || this->A == triangle.A) // A and B are in the same edge
                    return EQIntersections::E_One;
                else
                {
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
            }
            else // B is not in an edge
            {
                vPoint1 = this->A;
                return EQIntersections::E_One;
            }
        }
        else if (bBIsVertex)
        {
            if (QFloat::IsZero(QLineSegment2D(triangle.A, triangle.B).MinDistance(this->A))) // A is in AB triangle edge
            {
                if (this->B == triangle.A || this->B == triangle.B) // A and B are in the same edge
                {
                    vPoint1 = this->B;
                    return EQIntersections::E_One;
                }
                else
                {
                    vPoint1 = this->A;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
            }
            else if (QFloat::IsZero(QLineSegment2D(triangle.B, triangle.C).MinDistance(this->A))) // B is in BC triangle edge
            {
                if (this->B == triangle.B || this->B == triangle.C) // A and B are in the same edge
                {
                    vPoint1 = this->B;
                    return EQIntersections::E_One;
                }
                else
                {
                    vPoint1 = this->A;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
            }
            else if (QFloat::IsZero(QLineSegment2D(triangle.C, triangle.A).MinDistance(this->A))) // B is in CA triangle edge
            {
                if (this->B == triangle.C || this->B == triangle.A) // A and B are in the same edge
                {
                    vPoint1 = this->B;
                    return EQIntersections::E_One;
                }
                else
                {
                    vPoint1 = this->A;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
            }
            else
            {
                vPoint1 = this->B;
                return EQIntersections::E_One;
            }
        }
        else // Neither A or B are vertices of triangle
        {
            if (QFloat::IsZero(QLineSegment2D(triangle.A, triangle.B).MinDistance(this->A))) // A is in AB triangle edge (but not a vertex)
            {
                if (QFloat::IsZero(QLineSegment2D(triangle.A, triangle.B).MinDistance(this->B))) // B is in AB triangle edge (but not a vertex)
                    return EQIntersections::E_Infinite;
                else if ( QFloat::IsZero(QLineSegment2D(triangle.B, triangle.C).MinDistance(this->B)) || // B is in other edge (but not a vertex)
                          QFloat::IsZero(QLineSegment2D(triangle.C, triangle.A).MinDistance(this->B)) )
                {
                    vPoint1 = this->A;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else // B is not in an edge
                {
                    vPoint1 = this->A;
                    return EQIntersections::E_One;
                }
            }
            else if (QFloat::IsZero(QLineSegment2D(triangle.B, triangle.C).MinDistance(this->A))) // A is in BC triangle edge (but not a vertex)
            {
                if (QFloat::IsZero(QLineSegment2D(triangle.B, triangle.C).MinDistance(this->B))) // B is in BC triangle edge (but not a vertex)
                    return EQIntersections::E_Infinite;
                else if ( QFloat::IsZero(QLineSegment2D(triangle.A, triangle.B).MinDistance(this->B)) || // B is in other edge (but not a vertex)
                          QFloat::IsZero(QLineSegment2D(triangle.C, triangle.A).MinDistance(this->B)) )
                {
                    vPoint1 = this->A;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else // B is not in an edge
                {
                    vPoint1 = this->A;
                    return EQIntersections::E_One;
                }
            }
            else if (QFloat::IsZero(QLineSegment2D(triangle.C, triangle.A).MinDistance(this->A))) // A is in CA triangle edge (but not a vertex)
            {
                if (QFloat::IsZero(QLineSegment2D(triangle.C, triangle.A).MinDistance(this->B))) // B is in CA triangle edge (but not a vertex)
                    return EQIntersections::E_Infinite;
                else if ( QFloat::IsZero(QLineSegment2D(triangle.A, triangle.B).MinDistance(this->B)) || // B is in other edge (but not a vertex)
                          QFloat::IsZero(QLineSegment2D(triangle.B, triangle.C).MinDistance(this->B)) )
                {
                    vPoint1 = this->A;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else // B is not in an edge
                {
                    vPoint1 = this->A;
                    return EQIntersections::E_One;
                }
            }
            else // A is not in an edge
            {
                if ( QFloat::IsZero(QLineSegment2D(triangle.A, triangle.B).MinDistance(this->B)) || // B is in an edge (but not a vertex)
                     QFloat::IsZero(QLineSegment2D(triangle.B, triangle.C).MinDistance(this->B)) ||
                     QFloat::IsZero(QLineSegment2D(triangle.C, triangle.A).MinDistance(this->B)) )
                {
                    vPoint1 = this->B;
                    return EQIntersections::E_One;
                }
                else // B is not in an edge
                    return EQIntersections::E_Infinite;
            }
        }
    }
    else if (!bAIsInside && !bBIsInside) // Both line segment end points are outside triangle.
    {
        QVector2 vPointAB, vPointBC, vPointCA;

        EQIntersections value2AB = this->IntersectionPoint(QLineSegment2D(triangle.A, triangle.B), vPointAB);

        if (value2AB == EQIntersections::E_Infinite) // Line segment contains AB edge of triangle
        {
            if  ( (triangle.A - this->A).GetSquaredLength() < (triangle.B - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
            {
                vPoint1 = triangle.A;
                vPoint2 = triangle.B;
            }
            else
            {
                vPoint1 = triangle.B;
                vPoint2 = triangle.A;
            }
            return EQIntersections::E_Two;
        }

        // Line segment contains BC edge of triangle
        EQIntersections value2BC = this->IntersectionPoint(QLineSegment2D(triangle.B, triangle.C), vPointBC);
        if (value2BC == EQIntersections::E_Infinite)
        {
            if  ( (triangle.B - this->A).GetSquaredLength() < (triangle.C - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
            {
                vPoint1 = triangle.B;
                vPoint2 = triangle.C;
            }
            else
            {
                vPoint1 = triangle.C;
                vPoint2 = triangle.B;
            }
            return EQIntersections::E_Two;
        }

        // Line segment contains CA edge of triangle
        EQIntersections value2CA = this->IntersectionPoint(QLineSegment2D(triangle.C, triangle.A), vPointCA);
        if (value2CA == EQIntersections::E_Infinite)
        {
            if  ( (triangle.C - this->A).GetSquaredLength() < (triangle.A - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
            {
                vPoint1 = triangle.C;
                vPoint2 = triangle.A;
            }
            else
            {
                vPoint1 = triangle.A;
                vPoint2 = triangle.C;
            }
            return EQIntersections::E_Two;
        }

        if (value2AB ==EQIntersections::E_One) // Line segment intersects AB edge of triangle
        {
            if (value2BC ==EQIntersections::E_One) // Line segment intersects BC edge of triangle
            {
                if (vPointAB == vPointBC) // Are the same point (B vertex of triangle)
                {
                    if (value2CA ==EQIntersections::E_One) // Line segment intersects CA edge of triangle
                    {
                        if  ( (vPointAB - this->A).GetSquaredLength() < (vPointCA - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                        {
                            vPoint1 = vPointAB;
                            vPoint2 = vPointCA;
                        }
                        else
                        {
                            vPoint1 = vPointCA;
                            vPoint2 = vPointAB;
                        }
                        return EQIntersections::E_Two;
                    }
                    else
                    {
                        vPoint1 = vPointAB;
                        return EQIntersections::E_One;
                    }
                }
                else
                {
                    if  ( (vPointAB - this->A).GetSquaredLength() < (vPointBC - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                    {
                        vPoint1 = vPointAB;
                        vPoint2 = vPointBC;
                    }
                    else
                    {
                        vPoint1 = vPointBC;
                        vPoint2 = vPointAB;
                    }
                    return EQIntersections::E_Two;
                }
            }
            else if (value2CA ==EQIntersections::E_One) // Line segment intersects CA edge of triangle
            {
                if (vPointAB == vPointCA) // Are the same point
                {
                    vPoint1 = vPointAB;
                    return EQIntersections::E_One;
                }
                else
                {
                    // Returns closest point to A end point of line segment
                    if  ( (vPointAB - this->A).GetSquaredLength() < (vPointCA - this->A).GetSquaredLength() )
                    {
                        vPoint1 = vPointAB;
                        vPoint2 = vPointCA;
                    }
                    else
                    {
                        vPoint1 = vPointCA;
                        vPoint2 = vPointAB;
                    }

                    return EQIntersections::E_Two;
                }
            }
            else                  // Something is wrong: if end points of line segment are outside triangle,
                QE_ASSERT(false); // line segment must intersects none or two edges, never only one.
        }
        else if (value2BC ==EQIntersections::E_One) // Line segment intersects BC edge of triangle
        {
            if (value2CA ==EQIntersections::E_One) // Line segment intersects CA edge of triangle
            {
                if (vPointBC == vPointCA) // Are the same point
                {
                    vPoint1 = vPointBC;
                    return EQIntersections::E_One;
                }
                else
                {
                    // Returns closest point to A end point of line segment
                    if  ( (vPointBC - this->A).GetSquaredLength() < (vPointCA - this->A).GetSquaredLength() )
                    {
                        vPoint1 = vPointBC;
                        vPoint2 = vPointCA;
                    }
                    else
                    {
                        vPoint1 = vPointCA;
                        vPoint2 = vPointBC;
                    }

                    return EQIntersections::E_Two;
                }
            }
            else                  // Something is wrong: if end points of line segment are outside triangle,
                QE_ASSERT(false); // line segment must intersects none or two, never only one.
        }

        // Line segment don't intersects triangle
        if (value2AB == EQIntersections::E_None && value2BC == EQIntersections::E_None && value2CA == EQIntersections::E_None)
            return EQIntersections::E_None;
    }
    else // one line segment end point is inside and the other one is outside triangle.
    {
        QVector2 vAux; // To store intersection points

        if (bAIsInside) // this->A is inside triangle
        {
            if (this->A == triangle.A) // this->A is A triangle vertex
            {
                vPoint1 = this->A;

                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(triangle.B, triangle.C), vAux);
                if (value2 == EQIntersections::E_One) // ls intersects opposite edge
                {
                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
                else
                    return EQIntersections::E_One; // ls only intersects triangle in A vertex
            }
            else if (this->A == triangle.B) // this->A is B triangle vertex
            {
                vPoint1 = this->A;

                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(triangle.C, triangle.A), vAux);
                if (value2 == EQIntersections::E_One) // ls intersects opposite edge
                {
                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
                else
                    return EQIntersections::E_One; // ls only intersects triangle in B vertex
            }
            else if (this->A == triangle.C) // this->A is C triangle vertex
            {
                vPoint1 = this->A;

                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(triangle.B, triangle.A), vAux);
                if (value2 == EQIntersections::E_One) // ls intersects opposite edge
                {
                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
                else
                    return EQIntersections::E_One;  // ls only intersects triangle in C vertex
            }
            else if (QFloat::IsZero(QLineSegment2D(triangle.A, triangle.B).MinDistance(this->A))) // this->A is in AB triangle edge (but not a vertex)
            {
                vPoint1 = this->A;

                // ls intersects other edges
                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(triangle.B, triangle.C), vAux);
                if (value2 == EQIntersections::E_One)
                {
                    if (vAux == triangle.B || vAux == triangle.C) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(triangle.C, triangle.A), vAux) == EQIntersections::E_One)
                {
                    if (vAux == triangle.C || vAux == triangle.A) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
                else
                    return EQIntersections::E_One;
            }
            else if (QFloat::IsZero(QLineSegment2D(triangle.B, triangle.C).MinDistance(this->A))) // this->A is in BC triangle edge (but not a vertex)
            {
                vPoint1 = this->A;

                 // ls intersects other edges
                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(triangle.A, triangle.B), vAux);
                if (value2 == EQIntersections::E_One)
                {
                    if (vAux == triangle.A || vAux == triangle.B) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(triangle.C, triangle.A), vAux) == EQIntersections::E_One)
                {
                    if (vAux == triangle.C || vAux == triangle.A) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
                else
                    return EQIntersections::E_One;
            }
            else if (QFloat::IsZero(QLineSegment2D(triangle.C, triangle.A).MinDistance(this->A))) // this->A is in CA triangle edge (but not a vertex)
            {
                vPoint1 = this->A;

                 // ls intersects other edges
                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(triangle.B, triangle.C), vAux);
                if (value2 == EQIntersections::E_One)
                {
                    if (vAux == triangle.B || vAux == triangle.C) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(triangle.A, triangle.B), vAux) == EQIntersections::E_One)
                {
                    if (vAux == triangle.A || vAux == triangle.B) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
                else
                    return EQIntersections::E_One;
            }
            else // this->A is strictly inside triangle: is not in a vertex or edge.
            {
                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(triangle.A, triangle.B), vAux);
                if (value2 == EQIntersections::E_One)
                    vPoint1 = vAux;
                else if (value2 = this->IntersectionPoint(QLineSegment2D(triangle.B, triangle.C), vAux) == EQIntersections::E_One)
                    vPoint1 = vAux;
                else if (value2 = this->IntersectionPoint(QLineSegment2D(triangle.C, triangle.A), vAux)== EQIntersections::E_One)
                    vPoint1 = vAux;
                else                  // Something is wrong, if one point is inside and the other is outside,
                    QE_ASSERT(false); // there must be intersections.

                return EQIntersections::E_One;
            }
        }
        else // this->B is inside triangle (A is outside)
        {
            if (this->B == triangle.A) // this->B is triangle.A vertex
            {

                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(triangle.B, triangle.C), vAux);
                if (value2 == EQIntersections::E_One) // ls intersects opposite edge
                {
                    vPoint1 = vAux;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else // ls only intersects in A vertex
                {
                    vPoint1 = this->B;
                    return EQIntersections::E_One;
                }
            }
            else if (this->B == triangle.B) // this->B is triangle.B vertex
            {
                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(triangle.C, triangle.A), vAux);
                if (value2 == EQIntersections::E_One) // ls intersects opposite edge
                {
                    vPoint1 = vAux;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else // ls only intersects in B vertex
                {
                    vPoint1 = this->B;
                    return EQIntersections::E_One;
                }
            }
            else if (this->B == triangle.C) // this->B is triangle.C vertex
            {
                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(triangle.A, triangle.B), vAux);
                if (value2 == EQIntersections::E_One) // ls intersects opposite edge
                {
                    vPoint1 = vAux;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else // ls only intersects in C vertex
                {
                    vPoint1 = this->B;
                    return EQIntersections::E_One;
                }
            }
            else if (QFloat::IsZero(QLineSegment2D(triangle.A, triangle.B).MinDistance(this->B))) // this->B is in AB triangle edge (but not a vertex)
            {
                // ls intersects the other edges
                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(triangle.B, triangle.C), vAux);
                if (value2 == EQIntersections::E_One)
                {
                    vPoint1 = vAux;

                    if (vAux == triangle.B || vAux == triangle.C) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(triangle.C, triangle.A), vAux) == EQIntersections::E_One)
                {
                    vPoint1 = vAux;

                    if (vAux == triangle.C || vAux == triangle.A) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else // There is no other intersection
                {
                    vPoint1 = this->B;
                    return EQIntersections::E_One;
                }
            }
            else if (QFloat::IsZero(QLineSegment2D(triangle.B, triangle.C).MinDistance(this->B))) // this->B is in BC triangle edge (but not a vertex)
            {
                // ls intersects the other edges
                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(triangle.A, triangle.B), vAux);
                if (value2 == EQIntersections::E_One)
                {
                    vPoint1 = vAux;

                    if (vAux == triangle.A || vAux == triangle.B) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(triangle.C, triangle.A), vAux) == EQIntersections::E_One)
                {
                    vPoint1 = vAux;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else // There is no other intersection
                {
                    vPoint1 = this->B;
                    return EQIntersections::E_One;
                }
            }
            else if (QFloat::IsZero(QLineSegment2D(triangle.C, triangle.A).MinDistance(this->B))) // this->B is in CA triangle edge (but not a vertex)
            {
                // ls intersects the other edges
                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(triangle.B, triangle.C), vAux);
                if (value2 == EQIntersections::E_One)
                {
                    vPoint1 = vAux;

                    if (vAux == triangle.B || vAux == triangle.C) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(triangle.A, triangle.B), vAux) == EQIntersections::E_One)
                {
                    vPoint1 = vAux;

                    if (vAux == triangle.A || vAux == triangle.B) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else // There is no other intersection
                {
                    vPoint1 = this->B;
                    return EQIntersections::E_One;
                }
            }
            else // this->B is strictly inside triangle: is not in a vertex or edge.
            {
                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(triangle.A, triangle.B), vAux);
                if (value2 == EQIntersections::E_One)
                    vPoint1 = vAux;
                else if (value2 = this->IntersectionPoint(QLineSegment2D(triangle.B, triangle.C), vAux) == EQIntersections::E_One)
                    vPoint1 = vAux;
                else if (value2 = this->IntersectionPoint(QLineSegment2D(triangle.C, triangle.A), vAux)== EQIntersections::E_One)
                    vPoint1 = vAux;
                else                  // Something is wrong, if one point is inside and the other is outside,
                    QE_ASSERT(false); // there must be intersections.

                return EQIntersections::E_One;
            }
        }
    }
}

EQIntersections QLineSegment2D::IntersectionPoint(const QBaseQuadrilateral& quad, QBaseVector2& vPoint1, QBaseVector2& vPoint2) const
{
    const bool &bAIsInside = PointInsideQuadrilateral(quad, this->A);
    const bool &bBIsInside = PointInsideQuadrilateral(quad, this->B);

    if (bAIsInside && bBIsInside) // Both line segment end points are inside quadrilateral.
    {
        // A or B are vertex
        const bool &bAIsVertex = (this->A == quad.A || this->A == quad.B || this->A == quad.C || this->A == quad.D);
        const bool &bBIsVertex = (this->B == quad.A || this->B == quad.B || this->B == quad.C || this->B == quad.D);

        if (bAIsVertex && bBIsVertex) // Both endpoints are vertices of quadrilateral
        {
            vPoint1 = this->A;
            vPoint2 = this->B;
            return EQIntersections::E_Two;
        }
        else if (bAIsVertex) // Only A endpoint is a vertex of quadrilateral
        {
            if (QFloat::IsZero(QLineSegment2D(quad.A, quad.B).MinDistance(this->B))) // B is in AB quad edge
            {
                if (this->A == quad.A || this->A == quad.B) // A and B are in the same edge
                {
                    vPoint1 = this->A;
                    return EQIntersections::E_One;
                }
                else
                {
                    vPoint1 = this->A;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
            }
            else if (QFloat::IsZero(QLineSegment2D(quad.B, quad.C).MinDistance(this->B))) // B is in BC quad edge
            {
                if (this->A == quad.B || this->A == quad.C) // A and B are in the same edge
                {
                    vPoint1 = this->A;
                    return EQIntersections::E_One;
                }
                else
                {
                    vPoint1 = this->A;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
            }
            else if (QFloat::IsZero(QLineSegment2D(quad.C, quad.D).MinDistance(this->B))) // B is in CD quad edge
            {
                if (this->A == quad.C || this->A == quad.D) // A and B are in the same edge
                {
                    vPoint1 = this->A;
                    return EQIntersections::E_One;
                }
                else
                {
                    vPoint1 = this->A;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
            }
            else if (QFloat::IsZero(QLineSegment2D(quad.D, quad.A).MinDistance(this->B))) // B is in DA quad edge
            {
                if (this->A == quad.D || this->A == quad.A) // A and B are in the same edge
                {
                    vPoint1 = this->A;
                    return EQIntersections::E_One;
                }
                else
                {
                    vPoint1 = this->A;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
            }
            else // B is not in an edge
            {
                vPoint1 = this->A;
                return EQIntersections::E_One;
            }
        }
        else if (bBIsVertex)
        {
            if (QFloat::IsZero(QLineSegment2D(quad.A, quad.B).MinDistance(this->A))) // A is in AB quad edge
            {
                if (this->B == quad.A || this->B == quad.B) // A and B are in the same edge
                {
                    vPoint1 = this->B;
                    return EQIntersections::E_One;
                }
                else
                {
                    vPoint1 = this->A;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
            }
            else if (QFloat::IsZero(QLineSegment2D(quad.B, quad.C).MinDistance(this->A))) // B is in BC quad edge
            {
                if (this->B == quad.B || this->B == quad.C) // A and B are in the same edge
                {
                    vPoint1 = this->B;
                    return EQIntersections::E_One;
                }
                else
                {
                    vPoint1 = this->A;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
            }
            else if (QFloat::IsZero(QLineSegment2D(quad.C, quad.D).MinDistance(this->A))) // B is in CD quad edge
            {
                if (this->B == quad.C || this->B == quad.D) // A and B are in the same edge
                {
                    vPoint1 = this->B;
                    return EQIntersections::E_One;
                }
                else
                {
                    vPoint1 = this->A;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
            }
            else if (QFloat::IsZero(QLineSegment2D(quad.D, quad.A).MinDistance(this->A))) // B is in DA quad edge
            {
                if (this->B == quad.D || this->B == quad.A) // A and B are in the same edge
                {
                    vPoint1 = this->B;
                    return EQIntersections::E_One;
                }
                else
                {
                    vPoint1 = this->A;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
            }
            else
            {
                vPoint1 = this->B;
                return EQIntersections::E_One;
            }
        }
        else // Neither A or B are vertices of quadrilateral
        {
            if (QFloat::IsZero(QLineSegment2D(quad.A, quad.B).MinDistance(this->A))) // A is in AB quad edge (but not a vertex)
            {
                if (QFloat::IsZero(QLineSegment2D(quad.A, quad.B).MinDistance(this->B))) // B is in AB quad edge (but not a vertex)
                    return EQIntersections::E_Infinite;
                else if (QFloat::IsZero(QLineSegment2D(quad.B, quad.C).MinDistance(this->B)) || // B is in other edge (but not a vertex)
                         QFloat::IsZero(QLineSegment2D(quad.C, quad.D).MinDistance(this->B)) ||
                         QFloat::IsZero(QLineSegment2D(quad.D, quad.A).MinDistance(this->B)))
                {
                    vPoint1 = this->A;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else // B is not in an edge
                {
                    vPoint1 = this->A;
                    return EQIntersections::E_One;
                }
            }
            else if (QFloat::IsZero(QLineSegment2D(quad.B, quad.C).MinDistance(this->A))) // A is in BC quad edge (but not a vertex)
            {
                if (QFloat::IsZero(QLineSegment2D(quad.B, quad.C).MinDistance(this->B))) // B is in BC quad edge (but not a vertex)
                    return EQIntersections::E_Infinite;
                else if (QFloat::IsZero(QLineSegment2D(quad.A, quad.B).MinDistance(this->B)) || // B is in other edge (but not a vertex)
                         QFloat::IsZero(QLineSegment2D(quad.C, quad.D).MinDistance(this->B)) ||
                         QFloat::IsZero(QLineSegment2D(quad.D, quad.A).MinDistance(this->B)))
                {
                    vPoint1 = this->A;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else // B is not in an edge
                {
                    vPoint1 = this->A;
                    return EQIntersections::E_One;
                }
            }
            else if (QFloat::IsZero(QLineSegment2D(quad.C, quad.D).MinDistance(this->A))) // A is in CD quad edge (but not a vertex)
            {
                if (QFloat::IsZero(QLineSegment2D(quad.C, quad.D).MinDistance(this->B))) // B is in CD quad edge (but not a vertex)
                    return EQIntersections::E_Infinite;
                else if (QFloat::IsZero(QLineSegment2D(quad.A, quad.B).MinDistance(this->B)) || // B is in other edge (but not a vertex)
                         QFloat::IsZero(QLineSegment2D(quad.B, quad.C).MinDistance(this->B)) ||
                         QFloat::IsZero(QLineSegment2D(quad.D, quad.A).MinDistance(this->B)))
                {
                    vPoint1 = this->A;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else // B is not in an edge
                {
                    vPoint1 = this->A;
                    return EQIntersections::E_One;
                }
            }
            else if (QFloat::IsZero(QLineSegment2D(quad.D, quad.A).MinDistance(this->A))) // A is in DA quad edge (but not a vertex)
            {
                if (QFloat::IsZero(QLineSegment2D(quad.D, quad.A).MinDistance(this->B))) // B is in DA quad edge (but not a vertex)
                    return EQIntersections::E_Infinite;
                else if (QFloat::IsZero(QLineSegment2D(quad.A, quad.B).MinDistance(this->B)) || // B is in other edge (but not a vertex)
                         QFloat::IsZero(QLineSegment2D(quad.B, quad.C).MinDistance(this->B)) ||
                         QFloat::IsZero(QLineSegment2D(quad.C, quad.D).MinDistance(this->B)))
                {
                    vPoint1 = this->A;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else // B is not in an edge
                {
                    vPoint1 = this->A;
                    return EQIntersections::E_One;
                }
            }
            else // A is not in an edge
            {
                if (QFloat::IsZero(QLineSegment2D(quad.A, quad.B).MinDistance(this->B)) || // B is in an edge (but not a vertex)
                    QFloat::IsZero(QLineSegment2D(quad.B, quad.C).MinDistance(this->B)) ||
                    QFloat::IsZero(QLineSegment2D(quad.C, quad.D).MinDistance(this->B)) ||
                    QFloat::IsZero(QLineSegment2D(quad.D, quad.A).MinDistance(this->B)))
                {
                    vPoint1 = this->B;
                    return EQIntersections::E_One;
                }
                else // B is not in an edge
                    return EQIntersections::E_Infinite;
            }
        }
    }
    else if (!bAIsInside && !bBIsInside) // Both line segment end points are outside quadrilateral.
    {
        QVector2 vPointAB, vPointBC, vPointCD, vPointDA;

        EQIntersections value2AB = this->IntersectionPoint(QLineSegment2D(quad.A, quad.B), vPointAB);

        if (value2AB == EQIntersections::E_Infinite) // Line segment contains AB edge of quadrilateral
        {
            if  ( (quad.A - this->A).GetSquaredLength() < (quad.B - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
            {
                vPoint1 = quad.A;
                vPoint2 = quad.B;
            }
            else
            {
                vPoint1 = quad.B;
                vPoint2 = quad.A;
            }
            return EQIntersections::E_Two;
        }

        // Line segment contains BC edge of quadrilateral
        EQIntersections value2BC = this->IntersectionPoint(QLineSegment2D(quad.B, quad.C), vPointBC);
        if (value2BC == EQIntersections::E_Infinite)
        {
            if  ( (quad.B - this->A).GetSquaredLength() < (quad.C - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
            {
                vPoint1 = quad.B;
                vPoint2 = quad.C;
            }
            else
            {
                vPoint1 = quad.C;
                vPoint2 = quad.B;
            }
            return EQIntersections::E_Two;
        }

        // Line segment contains CA edge of quadrilateral
        EQIntersections value2CD = this->IntersectionPoint(QLineSegment2D(quad.C, quad.D), vPointCD);
        if (value2CD == EQIntersections::E_Infinite)
        {
            if  ( (quad.C - this->A).GetSquaredLength() < (quad.D - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
            {
                vPoint1 = quad.C;
                vPoint2 = quad.D;
            }
            else
            {
                vPoint1 = quad.D;
                vPoint2 = quad.C;
            }
            return EQIntersections::E_Two;
        }

        // Line segment contains DA edge of quadrilateral
        EQIntersections value2DA = this->IntersectionPoint(QLineSegment2D(quad.D, quad.A), vPointDA);
        if (value2DA == EQIntersections::E_Infinite)
        {
            if  ( (quad.D - this->A).GetSquaredLength() < (quad.A - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
            {
                vPoint1 = quad.D;
                vPoint2 = quad.A;
            }
            else
            {
                vPoint1 = quad.A;
                vPoint2 = quad.D;
            }
            return EQIntersections::E_Two;
        }

        if (value2AB ==EQIntersections::E_One) // Line segment intersects AB edge of quadrilateral
        {
            if (value2BC ==EQIntersections::E_One) // Line segment intersects BC edge of quadrilateral
            {
                if (vPointAB == vPointBC) // Are the same point (B vertex of quadrilateral)
                {
                    if (value2CD ==EQIntersections::E_One) // Line segment intersects CD edge of quadrilateral
                    {
                        // Returns closest point to A end point of line segment
                        if  ( (vPointAB - this->A).GetSquaredLength() < (vPointCD - this->A).GetSquaredLength() )
                        {
                            vPoint1 = vPointAB;
                            vPoint2 = vPointCD;
                        }
                        else
                        {
                            vPoint1 = vPointCD;
                            vPoint2 = vPointAB;
                        }

                        return EQIntersections::E_Two;
                    }
                    else if (value2DA ==EQIntersections::E_One) // Line segment intersects DA edge of quadrilateral
                    {
                        // Returns closest point to A end point of line segment
                        if  ( (vPointAB - this->A).GetSquaredLength() < (vPointDA - this->A).GetSquaredLength() )
                        {
                            vPoint1 = vPointAB;
                            vPoint2 = vPointDA;
                        }
                        else
                        {
                            vPoint1 = vPointDA;
                            vPoint2 = vPointAB;
                        }

                        return EQIntersections::E_Two;
                    }
                    else
                    {
                        vPoint1 = vPointAB;
                        return EQIntersections::E_One;
                    }
                }
                else
                {
                    if  ( (vPointAB - this->A).GetSquaredLength() < (vPointBC - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                    {
                        vPoint1 = vPointAB;
                        vPoint2 = vPointBC;
                    }
                    else
                    {
                        vPoint1 = vPointBC;
                        vPoint2 = vPointAB;
                    }
                    return EQIntersections::E_Two;
                }
            }
            else if (value2CD ==EQIntersections::E_One) // Line segment intersects CD edge of quadrilateral
            {
                // Returns closest point to A end point of line segment
                if  ( (vPointAB - this->A).GetSquaredLength() < (vPointCD - this->A).GetSquaredLength() )
                {
                    vPoint1 = vPointAB;
                    vPoint2 = vPointCD;
                }
                else
                {
                    vPoint1 = vPointCD;
                    vPoint2 = vPointAB;
                }

                return EQIntersections::E_Two;
            }
            else if (value2DA ==EQIntersections::E_One) // Line segment intersects DA edge of quadrilateral
            {
                if (vPointAB == vPointDA) // Are the same point
                {
                    vPoint1 = vPointAB;
                    return EQIntersections::E_One;
                }
                else
                {
                    // Returns closest point to A end point of line segment
                    if  ( (vPointAB - this->A).GetSquaredLength() < (vPointDA - this->A).GetSquaredLength() )
                    {
                        vPoint1 = vPointAB;
                        vPoint2 = vPointDA;
                    }
                    else
                    {
                        vPoint1 = vPointDA;
                        vPoint2 = vPointAB;
                    }

                    return EQIntersections::E_Two;
                }
            }
            else                  // Something is wrong: if end points of line segment are outside quadrilateral,
                QE_ASSERT(false); // line segment must intersects none, two or three edges, never only one.
        }
        else if (value2BC ==EQIntersections::E_One) // Line segment intersects BC edge of quadrilateral
        {
            if (value2CD ==EQIntersections::E_One) // Line segment intersects CA edge of quadrilateral
            {
                if (vPointBC == vPointCD) // Are the same point (C vertex of quadrilateral)
                {
                    if (value2DA ==EQIntersections::E_One) // Line segment intersects DA edge of quadrilateral
                    {
                        // Returns closest point to A end point of line segment
                        if  ( (vPointBC - this->A).GetSquaredLength() < (vPointDA - this->A).GetSquaredLength() )
                        {
                            vPoint1 = vPointBC;
                            vPoint2 = vPointDA;
                        }
                        else
                        {
                            vPoint1 = vPointDA;
                            vPoint2 = vPointBC;
                        }

                        return EQIntersections::E_Two;
                    }
                    else
                    {
                        vPoint1 = vPointBC;
                        return EQIntersections::E_One;
                    }
                }
                else
                {
                    // Returns closest point to A end point of line segment
                    if  ( (vPointBC - this->A).GetSquaredLength() < (vPointCD - this->A).GetSquaredLength() )
                    {
                        vPoint1 = vPointBC;
                        vPoint2 = vPointCD;
                    }
                    else
                    {
                        vPoint1 = vPointCD;
                        vPoint2 = vPointBC;
                    }

                    return EQIntersections::E_Two;
                }
            }
            else if (value2DA ==EQIntersections::E_One)
            {
                // Returns closest point to A end point of line segment
                if  ( (vPointBC - this->A).GetSquaredLength() < (vPointDA - this->A).GetSquaredLength() )
                {
                    vPoint1 = vPointBC;
                    vPoint2 = vPointDA;
                }
                else
                {
                    vPoint1 = vPointDA;
                    vPoint2 = vPointBC;
                }

                return EQIntersections::E_Two;
            }
            else                  // Something is wrong: if end points of line segment are outside quadrilateral,
                QE_ASSERT(false); // line segment must intersects none, two or three edges, never only one.
        }
        else if (value2CD ==EQIntersections::E_One) // Line segment intersects CD edge of quadrilateral
        {
            if (value2DA ==EQIntersections::E_One) // Line segment intersects DA edge of quadrilateral
            {
                if (vPointCD == vPointDA) // Are the same point (D vertex of quadrilateral)
                {
                    vPoint1 = vPointCD;
                    return EQIntersections::E_One;
                }
                else
                {
                    // Returns closest point to A end point of line segment
                    if  ( (vPointCD - this->A).GetSquaredLength() < (vPointDA - this->A).GetSquaredLength() )
                    {
                        vPoint1 = vPointCD;
                        vPoint2 = vPointDA;
                    }
                    else
                    {
                        vPoint1 = vPointDA;
                        vPoint2 = vPointCD;
                    }

                    return EQIntersections::E_Two;
                }
            }
            else                  // Something is wrong: if end points of line segment are outside quadrilateral,
                QE_ASSERT(false); // line segment must intersects none, two or three edges, never only one.
        }
        else if (value2DA ==EQIntersections::E_One) // Line segment intersects DA edge of quadrilateral
            QE_ASSERT(false);   // Something is wrong: if end points of line segment are outside quadrilateral,
        else                    // line segment must intersects none, two or three edges, never only one.
            return EQIntersections::E_None; // There are no intersections.
    }
    else // one line segment end point is inside and the other one is outside triangle.
    {
        QVector2 vAux; // To store intersection points

        if (bAIsInside) // this->A is inside quadrilateral
        {
            if (this->A == quad.A) // this->A is quad.A vertex
            {
                vPoint1 = this->A;

                // ls intersects opposite edges
                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(quad.B, quad.C), vAux);
                if (value2 == EQIntersections::E_One)
                {
                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.C, quad.D), vAux)== EQIntersections::E_One)
                {
                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
                else
                    return EQIntersections::E_One;
            }
            else if (this->A == quad.B) // this->A is quad.B vertex
            {
                vPoint1 = this->A;

                // ls intersects opposite edges
                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(quad.C, quad.D), vAux);
                if (value2 == EQIntersections::E_One)
                {
                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.D, quad.A), vAux)== EQIntersections::E_One)
                {
                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
                else
                    return EQIntersections::E_One;
            }
            else if (this->A == quad.C) // this->A is quad.C vertex
            {
                vPoint1 = this->A;

                // ls intersects opposite edges
                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(quad.D, quad.A), vAux);
                if (value2 == EQIntersections::E_One)
                {
                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.A, quad.B), vAux)== EQIntersections::E_One)
                {
                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
                else
                    return EQIntersections::E_One;
            }
            else if (this->A == quad.D) // this->A is quad.D vertex
            {
                vPoint1 = this->A;

                // ls intersects opposite edges
                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(quad.A, quad.B), vAux);
                if (value2 == EQIntersections::E_One)
                {
                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.B, quad.C), vAux)== EQIntersections::E_One)
                {
                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
                else
                    return EQIntersections::E_One;
            }
            else if (QFloat::IsZero(QLineSegment2D(quad.A, quad.B).MinDistance(this->A))) // this->A is in AB quad edge (but not a vertex)
            {
                vPoint1 = this->A;

                // ls intersects other edges
                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(quad.B, quad.C), vAux);
                if (value2 == EQIntersections::E_One)
                {
                    if (vAux == quad.B || vAux == quad.C) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.C, quad.D), vAux) == EQIntersections::E_One)
                {
                    if (vAux == quad.C || vAux == quad.D) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.D, quad.A), vAux) == EQIntersections::E_One)
                {
                    if (vAux == quad.D || vAux == quad.A) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
                else
                    return EQIntersections::E_One;
            }
            else if (QFloat::IsZero(QLineSegment2D(quad.B, quad.C).MinDistance(this->A))) // this->A is in BC quad edge (but not a vertex)
            {
                vPoint1 = this->A;

                 // ls intersects other edges
                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(quad.A, quad.B), vAux);
                if (value2 == EQIntersections::E_One)
                {
                    if (vAux == quad.A || vAux == quad.B) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.C, quad.D), vAux) == EQIntersections::E_One)
                {
                    if (vAux == quad.C || vAux == quad.D) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.D, quad.A), vAux) == EQIntersections::E_One)
                {
                    if (vAux == quad.D || vAux == quad.A) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
                else
                    return EQIntersections::E_One;
            }
            else if (QFloat::IsZero(QLineSegment2D(quad.C, quad.D).MinDistance(this->A))) // this->A is in CD quad edge (but not a vertex)
            {
                vPoint1 = this->A;

                 // ls intersects other edges
                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(quad.B, quad.C), vAux);
                if (value2 == EQIntersections::E_One)
                {
                    if (vAux == quad.B || vAux == quad.C) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.A, quad.B), vAux) == EQIntersections::E_One)
                {
                    if (vAux == quad.A || vAux == quad.B) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.D, quad.A), vAux) == EQIntersections::E_One)
                {
                    if (vAux == quad.D || vAux == quad.A) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
                else
                    return EQIntersections::E_One;
            }
            else if (QFloat::IsZero(QLineSegment2D(quad.D, quad.A).MinDistance(this->A))) // this->A is in DA quad edge (but not a vertex)
            {
                vPoint1 = this->A;

                 // ls intersects other edges
                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(quad.B, quad.C), vAux);
                if (value2 == EQIntersections::E_One)
                {
                    if (vAux == quad.B || vAux == quad.C) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.C, quad.D), vAux) == EQIntersections::E_One)
                {
                    if (vAux == quad.C || vAux == quad.D) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.A, quad.B), vAux) == EQIntersections::E_One)
                {
                    if (vAux == quad.A || vAux == quad.B) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
                else
                    return EQIntersections::E_One;
            }
            else // this->A is strictly inside quadrilateral: is not in a vertex or edge.
            {
                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(quad.A, quad.B), vAux);
                if (value2 == EQIntersections::E_One)
                    vPoint1 = vAux;
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.B, quad.C), vAux) == EQIntersections::E_One)
                    vPoint1 = vAux;
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.C, quad.D), vAux)== EQIntersections::E_One)
                    vPoint1 = vAux;
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.D, quad.A), vAux)== EQIntersections::E_One)
                    vPoint1 = vAux;
                else                  // Something is wrong, if one point is inside and the other is outside,
                    QE_ASSERT(false); // there must be intersections.

                return EQIntersections::E_One;
            }
        }
        else // this->B is inside quadrilateral (A is outside)
        {
            if (this->B == quad.A) // this->B is quad.A vertex
            {
                // ls intersects opposite edges
                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(quad.B, quad.C), vAux);
                if (value2 == EQIntersections::E_One)
                {
                    vPoint1 = vAux;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.C, quad.D), vAux) == EQIntersections::E_One)
                {
                    vPoint1 = vAux;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else
                {
                    vPoint1 = this->B;
                    return EQIntersections::E_One;
                }
            }
            else if (this->B == quad.B) // this->B is quad.B vertex
            {
                // ls intersects opposite edges
                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(quad.C, quad.D), vAux);
                if (value2 == EQIntersections::E_One)
                {
                    vPoint1 = vAux;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.D, quad.A), vAux) == EQIntersections::E_One)
                {
                    vPoint1 = vAux;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else
                {
                    vPoint1 = this->B;
                    return EQIntersections::E_One;
                }
            }
            else if (this->B == quad.C) // this->B is quad.C vertex
            {
                // ls intersects opposite edges
                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(quad.D, quad.A), vAux);
                if (value2 == EQIntersections::E_One)
                {
                    vPoint1 = vAux;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.A, quad.B), vAux) == EQIntersections::E_One)
                {
                    vPoint1 = vAux;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else
                {
                    vPoint1 = this->B;
                    return EQIntersections::E_One;
                }
            }
            else if (this->B == quad.D) // this->B is quad.B vertex
            {
                // ls intersects opposite edges
                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(quad.A, quad.B), vAux);
                if (value2 == EQIntersections::E_One)
                {
                    vPoint1 = vAux;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.B, quad.C), vAux) == EQIntersections::E_One)
                {
                    vPoint1 = vAux;
                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else
                {
                    vPoint1 = this->B;
                    return EQIntersections::E_One;
                }
            }
            else if (QFloat::IsZero(QLineSegment2D(quad.A, quad.B).MinDistance(this->B))) // this->B is in AB quad edge (but not a vertex)
            {
                // ls intersects the other edges
                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(quad.B, quad.C), vAux);
                if (value2 == EQIntersections::E_One)
                {
                    vPoint1 = vAux;

                    if (vAux == quad.B || vAux == quad.C) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.C, quad.D), vAux) == EQIntersections::E_One)
                {
                    vPoint1 = vAux;

                    if (vAux == quad.C || vAux == quad.D) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.D, quad.A), vAux) == EQIntersections::E_One)
                {
                    vPoint1 = vAux;

                    if (vAux == quad.D || vAux == quad.A) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else // There is no other intersection
                {
                    vPoint1 = this->B;
                    return EQIntersections::E_One;
                }
            }
            else if (QFloat::IsZero(QLineSegment2D(quad.B, quad.C).MinDistance(this->B))) // this->B is in BC quad edge (but not a vertex)
            {
                // ls intersects the other edges
                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(quad.A, quad.B), vAux);
                if (value2 == EQIntersections::E_One)
                {
                    vPoint1 = vAux;

                    if (vAux == quad.A || vAux == quad.B) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.C, quad.D), vAux) == EQIntersections::E_One)
                {
                    vPoint1 = vAux;

                    if (vAux == quad.C || vAux == quad.D) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.D, quad.A), vAux) == EQIntersections::E_One)
                {
                    vPoint1 = vAux;

                    if (vAux == quad.D || vAux == quad.A) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else // There is no other intersection
                {
                    vPoint1 = this->B;
                    return EQIntersections::E_One;
                }
            }
            else if (QFloat::IsZero(QLineSegment2D(quad.C, quad.D).MinDistance(this->B))) // this->B is in CD quad edge (but not a vertex)
            {
                // ls intersects the other edges
                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(quad.B, quad.C), vAux);
                if (value2 == EQIntersections::E_One)
                {
                    vPoint1 = vAux;

                    if (vAux == quad.B || vAux == quad.C) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.A, quad.B), vAux) == EQIntersections::E_One)
                {
                    vPoint1 = vAux;

                    if (vAux == quad.A || vAux == quad.B) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.D, quad.A), vAux) == EQIntersections::E_One)
                {
                    vPoint1 = vAux;

                    if (vAux == quad.D || vAux == quad.A) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else // There is no other intersection
                {
                    vPoint1 = this->B;
                    return EQIntersections::E_One;
                }
            }
            else if (QFloat::IsZero(QLineSegment2D(quad.D, quad.A).MinDistance(this->B))) // this->B is in DA quad edge (but not a vertex)
            {
                // ls intersects the other edges
                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(quad.B, quad.C), vAux);
                if (value2 == EQIntersections::E_One)
                {
                    vPoint1 = vAux;

                    if (vAux == quad.B || vAux == quad.C) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.C, quad.D), vAux) == EQIntersections::E_One)
                {
                    vPoint1 = vAux;

                    if (vAux == quad.C || vAux == quad.D) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.A, quad.B), vAux) == EQIntersections::E_One)
                {
                    vPoint1 = vAux;

                    if (vAux == quad.A || vAux == quad.B) // Both intersections are in the same edge
                        return EQIntersections::E_One;

                    vPoint2 = this->B;
                    return EQIntersections::E_Two;
                }
                else // There is no other intersection
                {
                    vPoint1 = this->B;
                    return EQIntersections::E_One;
                }
            }
            else // this->B is strictly inside quadrilateral: is not in a vertex or edge.
            {
                EQIntersections value2 = this->IntersectionPoint(QLineSegment2D(quad.A, quad.B), vAux);
                if (value2 == EQIntersections::E_One)
                    vPoint1 = vAux;
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.B, quad.C), vAux) == EQIntersections::E_One)
                    vPoint1 = vAux;
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.C, quad.D), vAux)== EQIntersections::E_One)
                    vPoint1 = vAux;
                else if (value2 = this->IntersectionPoint(QLineSegment2D(quad.D, quad.A), vAux)== EQIntersections::E_One)
                    vPoint1 = vAux;
                else                  // Something is wrong, if one point is inside and the other is outside,
                    QE_ASSERT(false); // there must be intersections.

                return EQIntersections::E_One;
            }
        }
    }
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
