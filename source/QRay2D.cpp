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

#include "QRay2D.h"

#include "QLineSegment2D.h"
#include "QBaseTriangle.h"
#include "QBaseQuadrilateral.h"
#include "QTransformationMatrix3x3.h"
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
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QRay2D::QRay2D()
{
}

QRay2D::QRay2D(const QRay2D &ray) : QRay<QVector2, QVector2>(ray)
{
}

QRay2D::QRay2D(const QBaseRay<QVector2, QVector2> &ray) : QRay<QVector2, QVector2>(ray)
{
}

QRay2D::QRay2D(const QVector2 &vOrigin, const QVector2 &vDirection) : QRay<QVector2, QVector2>(vOrigin, vDirection)
{
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QRay2D& QRay2D::operator=(const QBaseRay<QVector2, QVector2> &ray)
{
    QBaseRay<QVector2, QVector2>::operator=(ray);
    return *this;
}

bool QRay2D::Intersection(const QRay2D &ray) const
{
    // Direction vector of rays should not be null
    QE_ASSERT( !ray.Direction.IsZero() && !this->Direction.IsZero(), "Direction vector of rays should not be null" );

    const float_q &DENOMINATOR = this->Direction.x * ray.Direction.y - this->Direction.y * ray.Direction.x;

    if ( SQFloat::IsZero(DENOMINATOR) ) // Both directions are parallels
    {
        if ( this->Contains(ray.Origin) )
            return true;
        else
            return ray.Contains(this->Origin);
    }
    else // rays are not parallel
    {
        const float_q &NUMERATOR1 = this->Direction.x * (this->Origin.y - ray.Origin.y) + this->Direction.y * (ray.Origin.x - this->Origin.x);
        if ((SQFloat::IsNegative(DENOMINATOR) == SQFloat::IsNegative(NUMERATOR1)) || SQFloat::IsZero(NUMERATOR1))
        {
            const float_q &NUMERATOR2 = ray.Direction.x * (this->Origin.y - ray.Origin.y) + ray.Direction.y * (ray.Origin.x - this->Origin.x);

            return (SQFloat::IsNegative(DENOMINATOR) == SQFloat::IsNegative(NUMERATOR2)) || SQFloat::IsZero(NUMERATOR2);
        }
        else
            return false;
    }
}

bool QRay2D::Intersection(const QBaseTriangle<QVector2> &triangle) const
{
    // Vertices of the triangle must not coincide
    QE_ASSERT( triangle.A != triangle.B && 
               triangle.B != triangle.C &&
               triangle.C != triangle.A, "Vertices of the triangle must not coincide" );

    // The direction vector of the ray shouldn't be null
    QE_ASSERT( !this->Direction.IsZero(), "The direction vector of the ray shouldn't be null" );

    return ( this->Intersection(QBaseLineSegment<QVector2>(triangle.A, triangle.B)) ||
             this->Intersection(QBaseLineSegment<QVector2>(triangle.B, triangle.C)) ||
             this->Intersection(QBaseLineSegment<QVector2>(triangle.C, triangle.A)) );
}

bool QRay2D::Intersection(const QBaseQuadrilateral &quad) const
{
    return ( this->Intersection(QBaseLineSegment<QVector2>(quad.A, quad.B)) || this->Intersection(QBaseLineSegment<QVector2>(quad.B, quad.C)) ||
             this->Intersection(QBaseLineSegment<QVector2>(quad.C, quad.D)) || this->Intersection(QBaseLineSegment<QVector2>(quad.D, quad.A)));
}

EQIntersections QRay2D::IntersectionPoint(const QRay2D &ray, QBaseVector2 &vIntersection) const
{
    // Direction vector of rays should not be null
    QE_ASSERT( !ray.Direction.IsZero() && !this->Direction.IsZero(), "Direction vector of rays should not be null" );

    const float_q &DENOMINATOR = this->Direction.x * ray.Direction.y - this->Direction.y * ray.Direction.x;

    if ( SQFloat::IsZero(DENOMINATOR) ) // Both directions are parallels
    {
        if (this->Origin == ray.Origin)
        {
            if ( (this->Direction + ray.Direction) == QVector2::GetNullVector() ) // Directions are opposite (are supossed normalized)
            {
                vIntersection = this->Origin;
                return EQIntersections::E_One;
            }
            else
                return EQIntersections::E_Infinite; //Both rays are the same
        }
        else if(this->Contains(ray.Origin))
        {
            if(ray.Contains(this->Origin))
            {
                vIntersection = this->Origin;
                return EQIntersections::E_Two;
            }
            else
            {
                vIntersection = ray.Origin;
                return EQIntersections::E_One;
            }
        }
        else if(ray.Contains(this->Origin))
        {
            vIntersection = this->Origin;
            return EQIntersections::E_One;
        }
        else
            return EQIntersections::E_None;
    }
    else
    {
        const float_q &NUMERATOR1 = this->Direction.x * (this->Origin.y - ray.Origin.y) +
                                    this->Direction.y * (ray.Origin.x - this->Origin.x);

        // Forces first parameter to be greater o equal to 0
        if ((SQFloat::IsNegative(DENOMINATOR) == SQFloat::IsNegative(NUMERATOR1)) || SQFloat::IsZero(NUMERATOR1))
        {
            const float_q &NUMERATOR2 = ray.Direction.x * (this->Origin.y - ray.Origin.y) + ray.Direction.y * (ray.Origin.x - this->Origin.x);

            // Forces second parameter to be greater o equal to 0
            if ( (SQFloat::IsNegative(DENOMINATOR) == SQFloat::IsNegative(NUMERATOR2)) || SQFloat::IsZero(NUMERATOR2) )
            {
                vIntersection = this->Origin + (NUMERATOR2/DENOMINATOR) * this->Direction;
                return EQIntersections::E_One;
            }
            else
                return EQIntersections::E_None;
        }
        else
            return EQIntersections::E_None;
    }
}

EQIntersections QRay2D::IntersectionPoint(const QBaseTriangle<QVector2> &triangle, QBaseVector2 &vIntersection) const
{
    QBaseVector2 vAux;
    return this->IntersectionPoint(triangle, vIntersection, vAux);
}

EQIntersections QRay2D::IntersectionPoint(const QBaseTriangle<QVector2> &triangle, QBaseVector2 &vIntersection1, QBaseVector2 &vIntersection2) const
{
    // Vertices of the triangle must not coincide
    QE_ASSERT( triangle.A != triangle.B && 
               triangle.B != triangle.C &&
               triangle.C != triangle.A, "Vertices of the triangle must not coincide" );

    // The direction vector of the ray shouldn't be null
    QE_ASSERT( !this->Direction.IsZero(), "The direction vector of the ray shouldn't be null" );

    QVector2 vAux;

    if ( PointInsideTriangle(triangle, this->Origin) ) // Ray end point is inside triangle
    {
        if (this->Origin == triangle.A) // Ray end point is A triangle vertex
        {
            vIntersection1 = this->Origin;

            // Checks intersection with opposite edge (it should not return E_Infinite, is the opposite edge)
            if (this->IntersectionPoint(QBaseLineSegment<QVector2>(triangle.B, triangle.C), vAux) == EQIntersections::E_None) // No intersection found
                return EQIntersections::E_One;
            else // Intersection found
            {
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
        }
        else if (this->Origin == triangle.B) // Ray end point is B triangle vertex
        {
            vIntersection1 = this->Origin;

           // Checks intersection with opposite edge
            if (this->IntersectionPoint(QBaseLineSegment<QVector2>(triangle.C, triangle.A), vAux) == EQIntersections::E_None) // No intersection found
                return EQIntersections::E_One;
            else // Intersection found
            {
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
        }
        else if (this->Origin == triangle.C) // Ray end point is C triangle vertex
        {
            vIntersection1 = this->Origin;

            // Checks intersection with opposite edge
            if (this->IntersectionPoint(QBaseLineSegment<QVector2>(triangle.A, triangle.B), vAux) == EQIntersections::E_None) // No intersection found
                return EQIntersections::E_One;
            else // Intersection found
            {
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
        }
        else if (SQFloat::IsZero(QLineSegment2D(triangle.A, triangle.B).MinDistance(this->Origin))) // Ray end point is in AB triangle edge
        {
            vIntersection1 = this->Origin;

            if (this->IntersectionPoint(QBaseLineSegment<QVector2>(triangle.B, triangle.C), vAux) == EQIntersections::E_One ||
                this->IntersectionPoint(QBaseLineSegment<QVector2>(triangle.C, triangle.A), vAux) == EQIntersections::E_One) // Ray intersects edge BC or CA
            {
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            else // Ray doesn't intersect with other edge
            {
                return EQIntersections::E_One;
            }
        }
        else if (SQFloat::IsZero(QLineSegment2D(triangle.B, triangle.C).MinDistance(this->Origin))) // Ray end point is in BC triangle edge
        {
            vIntersection1 = this->Origin;

            if (this->IntersectionPoint(QBaseLineSegment<QVector2>(triangle.C, triangle.A), vAux) == EQIntersections::E_One ||
                this->IntersectionPoint(QBaseLineSegment<QVector2>(triangle.A, triangle.B), vAux) == EQIntersections::E_One) // Ray intersects edge AB or CA
            {
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            else // Ray doesn't intersect with other edge
            {
                return EQIntersections::E_One;
            }
        }
        else if (SQFloat::IsZero(QLineSegment2D(triangle.C, triangle.A).MinDistance(this->Origin))) // Ray end point is in CA triangle edge
        {
            vIntersection1 = this->Origin;

            if (this->IntersectionPoint(QBaseLineSegment<QVector2>(triangle.B, triangle.C), vAux) == EQIntersections::E_One ||
                this->IntersectionPoint(QBaseLineSegment<QVector2>(triangle.A, triangle.B), vAux) == EQIntersections::E_One) // Ray intersects edge AB or BC
            {
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            else // Ray doesn't intersect with other edge
            {
                return EQIntersections::E_One;
            }
        }
        else // Ray end point is strictly inside triangle (is not in a vertex or an edge
        {
            if (this->IntersectionPoint(QBaseLineSegment<QVector2>(triangle.A, triangle.B), vAux) == EQIntersections::E_One)
                vIntersection1 = vAux;
            else if (this->IntersectionPoint(QBaseLineSegment<QVector2>(triangle.B, triangle.C), vAux) == EQIntersections::E_One)
                vIntersection1 = vAux;
            else if (this->IntersectionPoint(QBaseLineSegment<QVector2>(triangle.C, triangle.A), vAux) == EQIntersections::E_One)
                vIntersection1 = vAux;
            else
                QE_ASSERT(false, "Something went very wrong, this code branch must never be reached");  // Something is wrong, if ray point is interior, it must be ONE intersection with a edge.

            return EQIntersections::E_One;
        }
    }
    else // Ray end point is outside triangle
    {
        QVector2 vPrevInt;
        bool bPrevInt = false;

        QVector2 vAuxAB;
        EQIntersections numIntAB = this->IntersectionPoint(QBaseLineSegment<QVector2>(triangle.A, triangle.B), vAuxAB); // Checks intersection with AB edge
        if (numIntAB == EQIntersections::E_Infinite) // Ray contains AB edge
        {
            // Looks for closest point to ray end point
            if  ( (triangle.A - this->Origin).GetSquaredLength() < (triangle.B - this->Origin).GetSquaredLength() )
            {
                vIntersection1 = triangle.A;
                vIntersection2 = triangle.B;
            }
            else
            {
                vIntersection1 = triangle.B;
                vIntersection2 = triangle.A;
            }
            return EQIntersections::E_Two;
        }

        QVector2 vAuxBC;
        EQIntersections numIntBC = this->IntersectionPoint(QBaseLineSegment<QVector2>(triangle.B, triangle.C), vAuxBC); // Checks intersection with BC edge
        if (numIntBC == EQIntersections::E_Infinite) // Ray contains BC edge
        {
            // Looks for closest point to ray end point
            if  ( (triangle.B - this->Origin).GetSquaredLength() < (triangle.C - this->Origin).GetSquaredLength() )
            {
                vIntersection1 = triangle.B;
                vIntersection2 = triangle.C;
            }
            else
            {
                vIntersection1 = triangle.C;
                vIntersection2 = triangle.B;
            }
            return EQIntersections::E_Two;
        }

        QVector2 vAuxCA;
        EQIntersections numIntCA = this->IntersectionPoint(QBaseLineSegment<QVector2>(triangle.C, triangle.A), vAuxCA); // Checks intersection with BC edge
        if (numIntCA == EQIntersections::E_Infinite) // Ray contains CA edge
        {
            // Looks for closest point to ray end point
            if  ( (triangle.C - this->Origin).GetSquaredLength() < (triangle.A - this->Origin).GetSquaredLength() )
            {
                vIntersection1 = triangle.C;
                vIntersection2 = triangle.A;
            }
            else
            {
                vIntersection1 = triangle.A;
                vIntersection2 = triangle.C;
            }
            return EQIntersections::E_Two;
        }

        if (numIntAB == EQIntersections::E_One) // Ray has ONE intersection with AB edge
        {
            bPrevInt = true;
            vPrevInt = vAuxAB;
        }

        if (numIntBC == EQIntersections::E_One) // Ray has ONE intersection with BC edge
        {
            if (bPrevInt) // There is a previous intersection with an edge
            {
                if (vAuxBC != vPrevInt)
                {
                    // Looks for closest point to ray end point
                    if  ( (vAuxBC - this->Origin).GetSquaredLength() < (vPrevInt - this->Origin).GetSquaredLength() )
                    {
                        vIntersection1 = vAuxBC;
                        vIntersection2 = vPrevInt;
                    }
                    else
                    {
                        vIntersection1 = vPrevInt;
                        vIntersection2 = vAuxBC;
                    }
                    return EQIntersections::E_Two;
                }
            }
            else // Its the first intersection found
            {
                bPrevInt = true;
                vPrevInt = vAuxBC;
            }
        }

        if (numIntCA == EQIntersections::E_One)
        {
            if (bPrevInt) // There is a previous intersection with an edge
            {
                if (vAuxCA != vPrevInt)
                {
                    // Looks for closest point to ray end point
                    if  ( (vAuxCA - this->Origin).GetSquaredLength() < (vPrevInt - this->Origin).GetSquaredLength() )
                    {
                        vIntersection1 = vAuxCA;
                        vIntersection2 = vPrevInt;
                    }
                    else
                    {
                        vIntersection1 = vPrevInt;
                        vIntersection2 = vAuxCA;
                    }
                    return EQIntersections::E_Two;
                }
            }
            else
                QE_ASSERT(false, "Something went very wrong, this code branch must never be reached");  // Something is wrong, there is ONE intersection and is not a vertex
        }

        if (bPrevInt)
        {
            vIntersection1 = vPrevInt;
            return EQIntersections::E_One;
        }
        else
            return EQIntersections::E_None;
    }
}

EQIntersections QRay2D::IntersectionPoint(const QBaseQuadrilateral &quad, QBaseVector2 &vIntersection) const
{
    QBaseVector2 vAux;
    return this->IntersectionPoint(quad, vIntersection, vAux);
}

EQIntersections QRay2D::IntersectionPoint(const QBaseQuadrilateral &quad, QBaseVector2 &vIntersection1, QBaseVector2 &vIntersection2) const
{
    QVector2 vAux;

    if ( PointInsideQuadrilateral(quad, this->Origin) ) // Ray end point is inside quadrilateral
    {
        if (this->Origin == quad.A) // Ray end point is A quadrilateral vertex
        {
            vIntersection1 = this->Origin;

            // Checks intersection with opposite edges
            if (this->IntersectionPoint(QBaseLineSegment<QVector2>(quad.B, quad.C), vAux) == EQIntersections::E_One) // Intersection found
            {
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            else if (this->IntersectionPoint(QBaseLineSegment<QVector2>(quad.C, quad.D), vAux) == EQIntersections::E_One) // Intersection found
            {
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            else // No intersection found
                return EQIntersections::E_One;
        }
        else if (this->Origin == quad.B) // Ray end point is B quadrilateral vertex
        {
            vIntersection1 = this->Origin;

           // Checks intersection with opposite edges
            if (this->IntersectionPoint(QBaseLineSegment<QVector2>(quad.C, quad.D), vAux) == EQIntersections::E_One) // Intersection found
            {
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            else if (this->IntersectionPoint(QBaseLineSegment<QVector2>(quad.D, quad.A), vAux) == EQIntersections::E_One) // Intersection found
            {
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            else // No intersection found
                return EQIntersections::E_One;
        }
        else if (this->Origin == quad.C) // Ray end point is C quadrilateral vertex
        {
            vIntersection1 = this->Origin;

            // Checks intersection with opposite edges
            if (this->IntersectionPoint(QBaseLineSegment<QVector2>(quad.D, quad.A), vAux) == EQIntersections::E_One) // Intersection found
            {
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            else if (this->IntersectionPoint(QBaseLineSegment<QVector2>(quad.A, quad.B), vAux) == EQIntersections::E_One) // Intersection found
            {
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            else // No intersection found
                return EQIntersections::E_One;
        }
        else if (this->Origin == quad.D) // Ray end point is D quadrilateral vertex
        {
            vIntersection1 = this->Origin;

            // Checks intersection with opposite edges
            if (this->IntersectionPoint(QBaseLineSegment<QVector2>(quad.A, quad.B), vAux) == EQIntersections::E_One) // Intersection found
            {
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            else if (this->IntersectionPoint(QBaseLineSegment<QVector2>(quad.B, quad.C), vAux) == EQIntersections::E_One) // Intersection found
            {
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            else // No intersection found
                return EQIntersections::E_One;
        }
        else if (SQFloat::IsZero(QLineSegment2D(quad.A, quad.B).MinDistance(this->Origin))) // Ray end point is in AB quadrilateral edge
        {
            if (this->IntersectionPoint(QBaseLineSegment<QVector2>(quad.B, quad.C), vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                // Origin belongs to AB edge and ray cuts BC
                vIntersection1 = this->Origin;
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            else if (this->IntersectionPoint(QBaseLineSegment<QVector2>(quad.C, quad.D), vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                // Origin belongs to AB edge and ray cuts to CD
                vIntersection1 = this->Origin;
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            else if (this->IntersectionPoint(QBaseLineSegment<QVector2>(quad.D, quad.A), vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                // Origin belongs to AB edge and ray cuts to DA
                vIntersection1 = this->Origin;
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            else // Ray don't intersects other edge
            {
                vIntersection1 = this->Origin;
                return EQIntersections::E_One;
            }
        }
        else if (SQFloat::IsZero(QLineSegment2D(quad.B, quad.C).MinDistance(this->Origin))) // Ray end point is in BC quadrilateral edge
        {
            if (this->IntersectionPoint(QBaseLineSegment<QVector2>(quad.C, quad.D), vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                // Origin belongs to BC edge and ray cuts to CD
                vIntersection1 = this->Origin;
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            else if (this->IntersectionPoint(QBaseLineSegment<QVector2>(quad.D, quad.A), vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                // Origin belongs to BC edge and ray cuts to DA
                vIntersection1 = this->Origin;
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            if (this->IntersectionPoint(QBaseLineSegment<QVector2>(quad.A, quad.B), vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                // Origin belongs to BC edge and ray cuts to AB
                vIntersection1 = this->Origin;
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            else // Ray don't intersects other edge
            {
                vIntersection1 = this->Origin;
                return EQIntersections::E_One;
            }
        }
        else if (SQFloat::IsZero(QLineSegment2D(quad.C, quad.D).MinDistance(this->Origin))) // Ray end point is in CD quadrilateral edge
        {
            if (this->IntersectionPoint(QBaseLineSegment<QVector2>(quad.D, quad.A), vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                // Origin belongs to CD edge and ray cuts to DA
                vIntersection1 = this->Origin;
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            else if (this->IntersectionPoint(QBaseLineSegment<QVector2>(quad.A, quad.B), vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                // Origin belongs to CD edge and ray cuts to AB
                vIntersection1 = this->Origin;
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            if (this->IntersectionPoint(QBaseLineSegment<QVector2>(quad.B, quad.C), vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                // Origin belongs to CD edge and ray cuts to BC
                vIntersection1 = this->Origin;
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            else // Ray don't intersects other edge
            {
                vIntersection1 = this->Origin;
                return EQIntersections::E_One;
            }
        }
        else if (SQFloat::IsZero(QLineSegment2D(quad.D, quad.A).MinDistance(this->Origin))) // Ray end point is in DA quadrilateral edge
        {
            if (this->IntersectionPoint(QBaseLineSegment<QVector2>(quad.A, quad.B), vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                // Origin belongs to DA edge and ray cuts to AB
                vIntersection1 = this->Origin;
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            else if (this->IntersectionPoint(QBaseLineSegment<QVector2>(quad.B, quad.C), vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                // Origin belongs to DA edge and ray cuts to BC
                vIntersection1 = this->Origin;
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            if (this->IntersectionPoint(QBaseLineSegment<QVector2>(quad.C, quad.D), vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                // Origin belongs to DA edge and ray cuts to CD
                vIntersection1 = this->Origin;
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            else // Ray don't intersects other edge
            {
                vIntersection1 = this->Origin;
                return EQIntersections::E_One;
            }
        }
        else // Ray end point is strictly inside quadrilateral (is not in a vertex or an edge)
        {
            if (this->IntersectionPoint(QBaseLineSegment<QVector2>(quad.A, quad.B), vAux) == EQIntersections::E_One)
                vIntersection1 = vAux;
            else if (this->IntersectionPoint(QBaseLineSegment<QVector2>(quad.B, quad.C), vAux) == EQIntersections::E_One)
                vIntersection1 = vAux;
            else if (this->IntersectionPoint(QBaseLineSegment<QVector2>(quad.C, quad.D), vAux) == EQIntersections::E_One)
                vIntersection1 = vAux;
            else if (this->IntersectionPoint(QBaseLineSegment<QVector2>(quad.D, quad.A), vAux) == EQIntersections::E_One)
                vIntersection1 = vAux;
            else
                QE_ASSERT(false, "Something went very wrong, this code branch must never be reached");  // Something is wrong, if ray point is interior, it must be ONE intersection with a edge.

            return EQIntersections::E_One;
        }
    }
    else // Ray end point is outside quadrilateral
    {
        QVector2 vPrevInt;
        bool bPrevInt = false;

        QVector2 vAuxAB;
        EQIntersections numIntAB = this->IntersectionPoint(QBaseLineSegment<QVector2>(quad.A, quad.B), vAuxAB); // Checks intersection with AB edge
        if (numIntAB == EQIntersections::E_Infinite) // Ray contains AB edge
        {
            // Looks for closest point to ray end point
            if  ( (quad.A - this->Origin).GetSquaredLength() < (quad.B - this->Origin).GetSquaredLength() )
            {
                vIntersection1 = quad.A;
                vIntersection2 = quad.B;
            }
            else
            {
                vIntersection1 = quad.B;
                vIntersection2 = quad.A;
            }
            return EQIntersections::E_Two;
        }

        QVector2 vAuxBC;
        EQIntersections numIntBC = this->IntersectionPoint(QBaseLineSegment<QVector2>(quad.B, quad.C), vAuxBC); // Checks intersection with BC edge
        if (numIntBC == EQIntersections::E_Infinite) // Ray contains BC edge
        {
            // Looks for closest point to ray end point
            if  ( (quad.B - this->Origin).GetSquaredLength() < (quad.C - this->Origin).GetSquaredLength() )
            {
                vIntersection1 = quad.B;
                vIntersection2 = quad.C;
            }
            else
            {
                vIntersection1 = quad.C;
                vIntersection2 = quad.B;
            }
            return EQIntersections::E_Two;
        }

        QVector2 vAuxCD;
        EQIntersections numIntCD = this->IntersectionPoint(QBaseLineSegment<QVector2>(quad.C, quad.D), vAuxCD); // Checks intersection with CD edge
        if (numIntCD == EQIntersections::E_Infinite) // Ray contains CD edge
        {
            // Looks for closest point to ray end point
            if  ( (quad.C - this->Origin).GetSquaredLength() < (quad.D - this->Origin).GetSquaredLength() )
            {
                vIntersection1 = quad.C;
                vIntersection2 = quad.D;
            }
            else
            {
                vIntersection1 = quad.D;
                vIntersection2 = quad.C;
            }
            return EQIntersections::E_Two;
        }

        QVector2 vAuxDA;
        EQIntersections numIntDA = this->IntersectionPoint(QBaseLineSegment<QVector2>(quad.D, quad.A), vAuxDA); // Checks intersection with DA edge
        if (numIntDA == EQIntersections::E_Infinite) // Ray contains DA edge
        {
            // Looks for closest point to ray end point
            if  ( (quad.D - this->Origin).GetSquaredLength() < (quad.A - this->Origin).GetSquaredLength() )
            {
                vIntersection1 = quad.D;
                vIntersection2 = quad.A;
            }
            else
            {
                vIntersection1 = quad.A;
                vIntersection2 = quad.D;
            }
            return EQIntersections::E_Two;
        }

        if (numIntAB == EQIntersections::E_One) // Ray has ONE intersection with AB edge
        {
            bPrevInt = true;
            vPrevInt = vAuxAB;
        }

        if (numIntBC == EQIntersections::E_One) // Ray has ONE intersection with BC edge
        {
            if (bPrevInt) // There is a previous intersection with an edge
            {
                if (vPrevInt != vAuxBC) // There are not the same point (a common vertex)
                {
                    // Looks for closest point to ray end point
                    if  ( (vAuxBC - this->Origin).GetSquaredLength() < (vPrevInt - this->Origin).GetSquaredLength() )
                    {
                        vIntersection1 = vAuxBC;
                        vIntersection2 = vPrevInt;
                    }
                    else
                    {
                        vIntersection1 = vPrevInt;
                        vIntersection2 = vAuxBC;
                    }
                    return EQIntersections::E_Two;
                }
            }
            else // Its the first intersection found
            {
                bPrevInt = true;
                vPrevInt = vAuxBC;
            }
        }

        if (numIntCD == EQIntersections::E_One)
        {
            if (bPrevInt) // There is a previous intersection with an edge
            {
                if (vPrevInt != vAuxCD) // There are not the same point (a common vertex)
                {
                    // Looks for closest point to ray end point
                    if  ( (vAuxCD - this->Origin).GetSquaredLength() < (vPrevInt - this->Origin).GetSquaredLength() )
                    {
                        vIntersection1 = vAuxCD;
                        vIntersection2 = vPrevInt;
                    }
                    else
                    {
                        vIntersection1 = vPrevInt;
                        vIntersection2 = vAuxCD;
                    }
                    return EQIntersections::E_Two;
                }
            }
            else // Its the first intersection found
            {
                bPrevInt = true;
                vPrevInt = vAuxCD;
            }
        }

        if (numIntDA == EQIntersections::E_One)
        {
            if (bPrevInt) // There is a previous intersection with an edge
            {
                if (vPrevInt != vAuxDA) // There are not the same point (a common vertex)
                {
                    // Looks for closest point to ray end point
                    if  ( (vAuxDA - this->Origin).GetSquaredLength() < (vPrevInt - this->Origin).GetSquaredLength() )
                    {
                        vIntersection1 = vAuxDA;
                        vIntersection2 = vPrevInt;
                    }
                    else
                    {
                        vIntersection1 = vPrevInt;
                        vIntersection2 = vAuxDA;
                    }
                    return EQIntersections::E_Two;
                }
            }
            else // Its the first intersection found
                QE_ASSERT(false, "Something went very wrong, this code branch must never be reached");  // Something is wrong
        }

        if (bPrevInt)
        {
            vIntersection1 = vPrevInt;
            return EQIntersections::E_One;
        }
        else
            return EQIntersections::E_None;
    }
}

bool QRay2D::Intersection(const QBaseLineSegment<QVector2> &segment) const
{
    // Direction vector of ray should not be null and the length of the segment should be greater than zero
    QE_ASSERT( segment.A != segment.B && !this->Direction.IsZero(), "Direction vector of ray should not be null and the length of the segment should be greater than zero" );

    QVector2 vAux(segment.B - segment.A);

    const float_q &DENOMINATOR = this->Direction.x * vAux.y - this->Direction.y * vAux.x;

    if ( SQFloat::IsZero(DENOMINATOR) ) // Both directions are parallels
    {
        if ( this->Contains(segment.A) )
            return true;
        else if ( this->Contains(segment.B) )
            return true;
        else
            return false;
    }
    else
    {
        const float_q &NUMERATOR1 = vAux.x * (this->Origin.y - segment.A.y) + vAux.y * (segment.A.x - this->Origin.x);
        if ((SQFloat::IsNegative(DENOMINATOR) == SQFloat::IsNegative(NUMERATOR1)) || SQFloat::IsZero(NUMERATOR1))
        {
            const float_q &NUMERATOR2 = this->Direction.x * (this->Origin.y - segment.A.y) + this->Direction.y * (segment.A.x - this->Origin.x);
            if ( ( SQFloat::IsNegative(DENOMINATOR) == SQFloat::IsNegative(NUMERATOR2) &&
                   SQFloat::IsGreaterOrEquals(SQFloat::Abs(DENOMINATOR), SQFloat::Abs(NUMERATOR2)) ) || SQFloat::IsZero(NUMERATOR2) )
                return true;
            else
                return false;
        }
        else
            return false;
    }
}

EQIntersections QRay2D::IntersectionPoint(const QBaseLineSegment<QVector2> &segment, QBaseVector2 &vIntersection) const
{
    // Direction vector of ray should not be null and the length of the segment should be greater than zero
    QE_ASSERT( segment.A != segment.B && !this->Direction.IsZero(), "Direction vector of ray should not be null and the length of the segment should be greater than zero" );

    QVector2 vAux(segment.B - segment.A);

    const float_q &DENOMINATOR = this->Direction.x * vAux.y - this->Direction.y * vAux.x;

    if ( SQFloat::IsZero(DENOMINATOR) ) // Both directions are parallels
    {
        const bool &A_IS_IN_RAY = this->Contains(segment.A);
        const bool &B_IS_IN_RAY = this->Contains(segment.B);

        if ( A_IS_IN_RAY && B_IS_IN_RAY )
        {
            if(this->Origin == segment.A)
            {
                vIntersection = segment.A;
            }
            else if(this->Origin == segment.B)
            {
                vIntersection = segment.B;
            }
            else if(SQFloat::IsNegative( (segment.B - segment.A).DotProduct(segment.B - this->Origin) ))// To know which endpoint is closer to the origin of the ray...
            {
                vIntersection = segment.A;
            }
            else
            {
                vIntersection = segment.B;
            }

            return EQIntersections::E_Two;
        }
        else if ( A_IS_IN_RAY )
        {
            if (segment.A == this->Origin)
            {
                vIntersection = this->Origin;
                return EQIntersections::E_One;
            }
            else
            {
                vIntersection = this->Origin;
                return EQIntersections::E_Two;
            }
        }
        else if ( B_IS_IN_RAY )
        {
            if (segment.B == this->Origin)
            {
                vIntersection = this->Origin;
                return EQIntersections::E_One;
            }
            else
            {
                vIntersection = this->Origin;
                return EQIntersections::E_Two;
            }
        }
        else
            return EQIntersections::E_None;
    }
    else
    {
        const float_q &NUMERATOR1 = vAux.x * (this->Origin.y - segment.A.y) + vAux.y * (segment.A.x - this->Origin.x);
        if ((SQFloat::IsNegative(DENOMINATOR) == SQFloat::IsNegative(NUMERATOR1)) || SQFloat::IsZero(NUMERATOR1))
        {
            const float_q &NUMERATOR2 = this->Direction.x * (this->Origin.y - segment.A.y) + this->Direction.y * (segment.A.x - this->Origin.x);
            if ( ( SQFloat::IsNegative(DENOMINATOR) == SQFloat::IsNegative(NUMERATOR2) &&
                   SQFloat::IsGreaterOrEquals(SQFloat::Abs(DENOMINATOR), SQFloat::Abs(NUMERATOR2)) ) || SQFloat::IsZero(NUMERATOR2) )
            {
                vIntersection = this->Origin + (NUMERATOR1/DENOMINATOR) * this->Direction;
                return EQIntersections::E_One;
            }
            else
                return EQIntersections::E_None;
        }
        else
            return EQIntersections::E_None;
    }
}

EQIntersections QRay2D::IntersectionPoint(const QBaseLineSegment<QVector2> &segment, QBaseVector2 &vIntersection1, QBaseVector2 &vIntersection2) const
{
    // Direction vector of ray should not be null and the length of the segment should be greater than zero
    QE_ASSERT( segment.A != segment.B && !this->Direction.IsZero(), "Direction vector of ray should not be null and the length of the segment should be greater than zero" );

    QVector2 vAux(segment.B - segment.A);

    const float_q &DENOMINATOR = this->Direction.x * vAux.y - this->Direction.y * vAux.x;

    if ( SQFloat::IsZero(DENOMINATOR) ) // Both directions are parallels
    {
        const bool &A_IS_IN_RAY = this->Contains(segment.A);
        const bool &B_IS_IN_RAY = this->Contains(segment.B);

        if ( A_IS_IN_RAY && B_IS_IN_RAY )
        {
            if(this->Origin == segment.A)
            {
                vIntersection1 = segment.A;
                vIntersection2 = segment.B;
            }
            else if(this->Origin == segment.B)
            {
                vIntersection1 = segment.B;
                vIntersection2 = segment.A;
            }
            else if(SQFloat::IsNegative( (segment.B - segment.A).DotProduct(segment.B - this->Origin) ))// To know which endpoint is closer to the origin of the ray...
            {
                vIntersection1 = segment.A;
                vIntersection2 = segment.B;
            }
            else
            {
                vIntersection1 = segment.B;
                vIntersection2 = segment.A;
            }

            return EQIntersections::E_Two;
        }
        else if ( A_IS_IN_RAY )
        {
            vIntersection1 = this->Origin;

            if (segment.A == this->Origin)
            {
                return EQIntersections::E_One;
            }
            else
            {
                vIntersection2 = segment.A;
                return EQIntersections::E_Two;
            }
        }
        else if ( B_IS_IN_RAY )
        {
            vIntersection1 = this->Origin;

            if (segment.B == this->Origin)
            {
                return EQIntersections::E_One;
            }
            else
            {
                vIntersection2 = segment.B;
                return EQIntersections::E_Two;
            }
        }
        else
            return EQIntersections::E_None;
    }
    else
    {
        const float_q &NUMERATOR1 = vAux.x * (this->Origin.y - segment.A.y) + vAux.y * (segment.A.x - this->Origin.x);
        if ((SQFloat::IsNegative(DENOMINATOR) == SQFloat::IsNegative(NUMERATOR1)) || SQFloat::IsZero(NUMERATOR1))
        {
            const float_q &NUMERATOR2 = this->Direction.x * (this->Origin.y - segment.A.y) + this->Direction.y * (segment.A.x - this->Origin.x);
            if ( ( SQFloat::IsNegative(DENOMINATOR) == SQFloat::IsNegative(NUMERATOR2) &&
                   SQFloat::IsGreaterOrEquals(SQFloat::Abs(DENOMINATOR), SQFloat::Abs(NUMERATOR2)) ) || SQFloat::IsZero(NUMERATOR2) )
            {
                vIntersection1 = this->Origin + (NUMERATOR1/DENOMINATOR) * this->Direction;
                return EQIntersections::E_One;
            }
            else
                return EQIntersections::E_None;
        }
        else
            return EQIntersections::E_None;
    }
}

void QRay2D::Reflection(const QBaseLineSegment<QVector2> &segment, QBaseRay<QVector2, QVector2> &ray) const
{
    // The direction vector of the ray must not be null
    QE_ASSERT( !this->Direction.IsZero(), "The direction vector of the ray must not be null" );

    // The endpoints of the line segment shouldn't coincide
    QE_ASSERT( segment.A != segment.B, "The endpoints of the line segment must not coincide" );

    // Method based in this: http://www.inmensia.com/articulos/raytracing/mecanismosluz.html

    QVector2 vAtoB = QVector2(segment.B - segment.A).Normalize();

    ray = *this;

    // Avoiding cases where ray and line segment are parallels or coincident.
    if (vAtoB != this->Direction && vAtoB != -this->Direction)
    {
        QVector2 vPoint;
        EQIntersections numInt = this->IntersectionPoint(segment, vPoint);
        if (numInt == EQIntersections::E_One)
        {
            // If the origin coincides with the intersection point, the ray is not reflexted
            if(ray.Origin != vPoint)
            {
                // Reflected origin is the intersection point
                ray.Origin = vPoint;

                // Calculates normal to line segment (is normalized like vAux)
                QVector2 vNorm = vAtoB.GetPerpendicular();

                // Calculates reflected direction
                ray.Direction -= SQFloat::_2 * (this->Direction.DotProduct(vNorm)) * vNorm;
            }
        }
    }
}

void QRay2D::Reflection(const QBaseLineSegment<QVector2> &segment, QBaseVector2 &vDirection) const
{
    // The direction vector of the ray must not be null
    QE_ASSERT( !this->Direction.IsZero(), "The direction vector of the ray must not be null" );

    // The endpoints of the line segment shouldn't coincide
    QE_ASSERT( segment.A != segment.B, "The endpoints of the line segment must not coincide" );

    // Method based in this: http://www.inmensia.com/articulos/raytracing/mecanismosluz.html

    QVector2 vAtoB = QVector2(segment.B - segment.A).Normalize();

    vDirection = this->Direction;

    if (vAtoB != this->Direction && vAtoB != -this->Direction && // Avoiding cases where ray and line segment are parallels or coincident.
        segment.A != this->Origin && segment.B != this->Origin && // No reflection if the origin belongs to the line
        this->Intersection(segment))
    {
        // If the origin of the ray does not belong to the line
        const QVector2& vAtoOrigin = (this->Origin - segment.A).Normalize();
        const bool& bOriginBelongsToLine = SQFloat::AreEqual(vAtoB.DotProduct(vAtoOrigin), SQFloat::_1);

        if(!bOriginBelongsToLine)
        {
            // Calculates normal to line segment (is normalized like vAtoB)
            QVector2 vNorm = vAtoB.GetPerpendicular();

            // Calculates reflected direction
            vDirection = this->Direction - SQFloat::_2 * (this->Direction.DotProduct(vNorm)) * vNorm;
        }
    }
}

QRay2D QRay2D::Transform(const QTransformationMatrix3x3 &transformation) const
{
    QRay2D auxRay = *this;
    auxRay.Origin = auxRay.Origin.Transform(transformation);

    // Direction is transformed without translation. The calculation takes into account only the submatrix that contains
    // the rotation and the scale.
    const float_q NEW_X = this->Direction.x * transformation.ij[0][0] + this->Direction.y * transformation.ij[1][0];
    const float_q NEW_Y = this->Direction.x * transformation.ij[0][1] + this->Direction.y * transformation.ij[1][1];

    auxRay.Direction = QVector2(NEW_X, NEW_Y).Normalize();

    return auxRay;
}

QRay2D QRay2D::Rotate(const float_q &fRotationAngle) const
{
    QRay2D auxRay = *this;
    SQPoint::Rotate(fRotationAngle, rcast_q(&auxRay, QVector2*), 2);
    return auxRay;
}

QRay2D QRay2D::RotateWithPivot(const float_q &fRotationAngle, const QBaseVector2 &vPivot) const
{
    QRay2D auxRay = *this;
    SQPoint::RotateWithPivot(fRotationAngle, vPivot, &auxRay.Origin, 1);
    SQPoint::Rotate(fRotationAngle, &auxRay.Direction, 1);
    return auxRay;
}

QRay2D QRay2D::Translate(const QBaseVector2 &vTranslation) const
{
    QRay2D auxRay = *this;
    SQPoint::Translate(vTranslation, &auxRay.Origin, 1);
    return auxRay;
}

QRay2D QRay2D::Translate(const float_q &fTranslationX, const float_q &fTranslationY) const
{
    QRay2D auxRay = *this;
    SQPoint::Translate(fTranslationX, fTranslationY, &auxRay.Origin, 1);
    return auxRay;
}

QRay2D QRay2D::Scale(const QBaseVector2 &vScale) const
{
    QRay2D auxRay = *this;
    SQPoint::Scale(vScale, rcast_q(&auxRay, QVector2*), 2);
    return QRay2D(auxRay.Origin, auxRay.Direction.Normalize());
}

QRay2D QRay2D::Scale(const float_q &vScaleX, const float_q &vScaleY) const
{
    QRay2D auxRay = *this;
    SQPoint::Scale(vScaleX, vScaleY, rcast_q(&auxRay, QVector2*), 2);
    return QRay2D(auxRay.Origin, auxRay.Direction.Normalize());
}

QRay2D QRay2D::ScaleWithPivot(const QBaseVector2 &vScale, const QBaseVector2 &vPivot) const
{
    QRay2D auxRay = *this;
    SQPoint::ScaleWithPivot(vScale, vPivot, &auxRay.Origin, 1);
    SQPoint::Scale(vScale, &auxRay.Direction, 1);
    return QRay2D(auxRay.Origin, auxRay.Direction.Normalize());
}

QRay2D QRay2D::ScaleWithPivot(const float_q &vScaleX, const float_q &vScaleY, const QBaseVector2 &vPivot) const
{
    QRay2D auxRay = *this;
    SQPoint::ScaleWithPivot(vScaleX, vScaleY, vPivot, &auxRay.Origin, 1);
    SQPoint::Scale(vScaleX, vScaleY, &auxRay.Direction, 1);
    return QRay2D(auxRay.Origin, auxRay.Direction.Normalize());
}

QRay2D QRay2D::TransformWithPivot(const QTransformationMatrix3x3 &transformation, const QBaseVector2 &vPivot) const
{
    QRay2D auxRay = *this;
    SQPoint::TransformWithPivot(transformation, vPivot, &auxRay.Origin, 1);

    const float_q NEW_X = this->Direction.x * transformation.ij[0][0] + this->Direction.y * transformation.ij[1][0];
    const float_q NEW_Y = this->Direction.x * transformation.ij[0][1] + this->Direction.y * transformation.ij[1][1];

    auxRay.Direction = QVector2(NEW_X, NEW_Y).Normalize();

    return auxRay;
}

bool QRay2D::Contains(const QVector2 &vPoint) const
{
    if (this->Origin == vPoint)
        return true;
    else if ( SQFloat::IsZero(this->Direction.x) )
    {
        if ( SQFloat::AreNotEqual(vPoint.x, this->Origin.x) )
            return false;
        if ( SQFloat::IsNegative(vPoint.y - this->Origin.y) == SQFloat::IsNegative(this->Direction.y) )
            return true;
        else
            return false;
    }
    else if ( SQFloat::IsZero(this->Direction.y) )
    {
        if ( SQFloat::AreNotEqual(vPoint.y, this->Origin.y) )
            return false;
        if ( SQFloat::IsNegative(vPoint.x - this->Origin.x) == SQFloat::IsNegative(this->Direction.x) )
            return true;
        else
            return false;
    }
    else
    {
        const float_q &PARAM_X = (vPoint.x - this->Origin.x)/this->Direction.x;
        const float_q &PARAM_Y = (vPoint.y - this->Origin.y)/this->Direction.y;

        if ( SQFloat::AreNotEqual(PARAM_X, PARAM_Y) || SQFloat::IsNegative(PARAM_X))
            return false;
        else
            return true;
    }

}

bool QRay2D::PointInsideTriangle(const QBaseTriangle<QVector2>& triangle, const QVector2& vPoint) const
{
    return ( PointsInSameSideOfLine(vPoint, triangle.A, triangle.B, triangle.C) &&
                PointsInSameSideOfLine(vPoint, triangle.B, triangle.C, triangle.A) &&
                PointsInSameSideOfLine(vPoint, triangle.C, triangle.A, triangle.B) );
}

bool QRay2D::PointsInSameSideOfLine(const QVector2 &vP1, const QVector2 &vP2, const QVector2 &vLine1, const QVector2 &vLine2) const
{
    const float_q &ORIENTATION1 = (vLine1.x - vP1.x)*(vLine2.y - vP1.y) - (vLine1.y - vP1.y)*(vLine2.x - vP1.x);
    const float_q &ORIENTATION2 = (vLine1.x - vP2.x)*(vLine2.y - vP2.y) - (vLine1.y - vP2.y)*(vLine2.x - vP2.x);

    if ( SQFloat::IsZero(ORIENTATION1) || SQFloat::IsZero(ORIENTATION2) )
        return true;
    else if ( SQFloat::IsNegative(ORIENTATION1) == SQFloat::IsNegative(ORIENTATION2) )
        return true;
    else
        return false;
}

bool QRay2D::PointInsideQuadrilateral(const QBaseQuadrilateral& quad, const QVector2& vPoint) const
{
    return ( PointsInSameSideOfLine(vPoint, quad.C, quad.A, quad.B) &&
                PointsInSameSideOfLine(vPoint, quad.A, quad.B, quad.C) &&
                PointsInSameSideOfLine(vPoint, quad.A, quad.C, quad.D) &&
                PointsInSameSideOfLine(vPoint, quad.C, quad.D, quad.A) );
}

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const QRay2D& QRay2D::GetNullRay()
{
    static const QRay2D NULLRAY(QVector2::GetNullVector(), QVector2::GetNullVector());
    return NULLRAY;
}

const QRay2D& QRay2D::GetRayX()
{
    static const QRay2D RAYX(QVector2::GetNullVector(), QVector2::GetUnitVectorX());
    return RAYX;
}

const QRay2D& QRay2D::GetRayY()
{
    static const QRay2D RAYY(QVector2::GetNullVector(), QVector2::GetUnitVectorY());
    return RAYY;
}


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
