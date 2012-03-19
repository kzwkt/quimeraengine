// [TERMS&CONDITIONS]

#include "QRay2D.h"

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

bool QRay2D::Intersection(const QBaseRay<QVector2, QVector2> &ray) const
{
    const float_q &DENOMINATOR = this->Direction.x * ray.Direction.y - this->Direction.y * ray.Direction.x;

    if ( SQFloat::IsZero(DENOMINATOR) ) // Both directions are parallels
    {
        if ( this->Contains(ray.Origin) )
            return true;
        else
            return ( ray.As<const QRay2D>().Contains(this->Origin) );
    }
    else // rays are not parallel
    {
        const float_q &NUMERATOR1 = this->Direction.x * (this->Origin.y - ray.Origin.y) + this->Direction.y * (ray.Origin.x - this->Origin.x);
        if ((SQFloat::IsNegative(DENOMINATOR) == SQFloat::IsNegative(NUMERATOR1)) || SQFloat::IsZero(NUMERATOR1))
        {
            const float_q &NUMERATOR2 = ray.Direction.x * (this->Origin.y - ray.Origin.y) + ray.Direction.y * (ray.Origin.x - this->Origin.x);

            return ( (SQFloat::IsNegative(DENOMINATOR) == SQFloat::IsNegative(NUMERATOR2)) || SQFloat::IsZero(NUMERATOR2) );
        }
        else
            return false;
    }
}

EQIntersections QRay2D::IntersectionPoint(const QBaseRay<QVector2, QVector2> &ray, QBaseVector2 &vIntersection) const
{
    const float_q &DENOMINATOR = this->Direction.x * ray.Direction.y - this->Direction.y * ray.Direction.x;

    if ( SQFloat::IsZero(DENOMINATOR) ) // Both directions are parallels
    {
        if (this->Origin == ray.Origin)
        {
            if ( (this->Direction + ray.Direction) == QVector2::GetZeroVector() ) // Directions are opposite (are supossed normalized)
            {
                vIntersection = this->Origin;
                return EQIntersections::E_One;
            }
            else
                return EQIntersections::E_Infinite; //Both rays are the same
        }
        else if ( this->Contains(ray.Origin) || ray.As<const QRay2D>().Contains(this->Origin))
            return EQIntersections::E_Infinite;
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

EQIntersections QRay2D::IntersectionPoint(const QBaseTriangle<QVector2> &triangle, QBaseVector2 &vIntersection1, QBaseVector2 &vIntersection2) const
{
    QVector2 vAux;

    if ( PointInsideTriangle(triangle, this->Origin) ) // Ray end point is inside triangle
    {
        if (this->Origin == triangle.A) // Ray end point is A triangle vertex
        {
            vIntersection1 = this->Origin;

            // Checks intersection with opposite edge (it should not return E_Infinite, is the opposite edge)
            if (this->IntersectionPoint(triangle.B, triangle.C, vAux) == EQIntersections::E_None) // No intersection found
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
            if (this->IntersectionPoint(triangle.C, triangle.A, vAux) == EQIntersections::E_None) // No intersection found
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
            if (this->IntersectionPoint(triangle.A, triangle.B, vAux) == EQIntersections::E_None) // No intersection found
                return EQIntersections::E_One;
            else // Intersection found
            {
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
        }
        else if (SQFloat::IsZero(QLineSegment2D(triangle.A, triangle.B).MinDistance(this->Origin))) // Ray end point is in AB triangle edge
        {
            if (this->IntersectionPoint(triangle.B, triangle.C, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                if (vAux == triangle.B) // Intersection is in common vertex
                {
                    vIntersection1 = triangle.B;
                    return EQIntersections::E_One;
                }
                else // Intersection is in edge
                {
                    vIntersection1 = this->Origin;
                    vIntersection2 = vAux;
                    return EQIntersections::E_Two;
                }
            }
            else if (this->IntersectionPoint(triangle.C, triangle.A, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                if (vAux == triangle.A) // Intersection is in common vertex
                {
                    vIntersection1 = triangle.A;
                    return EQIntersections::E_One;
                }
                else // Intersection is in edge
                {
                    vIntersection1 = this->Origin;
                    vIntersection2 = vAux;
                    return EQIntersections::E_Two;
                }
            }
            else // Ray don't intersects other edge
            {
                vIntersection1 = this->Origin;
                return EQIntersections::E_One;
            }
        }
        else if (SQFloat::IsZero(QLineSegment2D(triangle.B, triangle.C).MinDistance(this->Origin))) // Ray end point is in BC triangle edge
        {
            if (this->IntersectionPoint(triangle.C, triangle.A, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                if (vAux == triangle.C) // Intersection is in common vertex
                {
                    vIntersection1 = triangle.C;
                    return EQIntersections::E_One;
                }
                else // Intersection is in edge
                {
                    vIntersection1 = this->Origin;
                    vIntersection2 = vAux;
                    return EQIntersections::E_Two;
                }
            }
            else if (this->IntersectionPoint(triangle.A, triangle.B, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                if (vAux == triangle.B) // Intersection is in common vertex
                {
                    vIntersection1 = triangle.B;
                    return EQIntersections::E_One;
                }
                else // Intersection is in edge
                {
                    vIntersection1 = this->Origin;
                    vIntersection2 = vAux;
                    return EQIntersections::E_Two;
                }
            }
            else // Ray don't intersects other edge
            {
                vIntersection1 = this->Origin;
                return EQIntersections::E_One;
            }
        }
        else if (SQFloat::IsZero(QLineSegment2D(triangle.C, triangle.A).MinDistance(this->Origin))) // Ray end point is in CA triangle edge
        {
            if (this->IntersectionPoint(triangle.A, triangle.B, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                if (vAux == triangle.A) // Intersection is in common vertex
                {
                    vIntersection1 = triangle.A;
                    return EQIntersections::E_One;
                }
                else // Intersection is in edge
                {
                    vIntersection1 = this->Origin;
                    vIntersection2 = vAux;
                    return EQIntersections::E_Two;
                }
            }
            else if (this->IntersectionPoint(triangle.B, triangle.C, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                if (vAux == triangle.C) // Intersection is in common vertex
                {
                    vIntersection1 = triangle.C;
                    return EQIntersections::E_One;
                }
                else // Intersection is in edge
                {
                    vIntersection1 = this->Origin;
                    vIntersection2 = vAux;
                    return EQIntersections::E_Two;
                }
            }
            else // Ray don't intersects other edge
            {
                vIntersection1 = this->Origin;
                return EQIntersections::E_One;
            }
        }
        else // Ray end point is strictly inside triangle (is not in a vertex or an edge
        {
            if (this->IntersectionPoint(triangle.A, triangle.B, vAux) == EQIntersections::E_One)
                vIntersection1 = vAux;
            else if (this->IntersectionPoint(triangle.B, triangle.C, vAux) == EQIntersections::E_One)
                vIntersection1 = vAux;
            else if (this->IntersectionPoint(triangle.C, triangle.A, vAux) == EQIntersections::E_One)
                vIntersection1 = vAux;
            else
                QE_ASSERT(false)  // Something is wrong, if ray point is interior, it must be ONE intersection with a edge.

            return EQIntersections::E_One;
        }
    }
    else // Ray end point is outside triangle
    {
        QVector2 vPrevInt;
        bool bPrevInt = false;

        QVector2 vAuxAB;
        EQIntersections numIntAB = this->IntersectionPoint(triangle.A, triangle.B, vAuxAB); // Checks intersection with AB edge
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
        EQIntersections numIntBC = this->IntersectionPoint(triangle.B, triangle.C, vAuxBC); // Checks intersection with BC edge
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
        EQIntersections numIntCA = this->IntersectionPoint(triangle.C, triangle.A, vAuxCA); // Checks intersection with BC edge
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
                QE_ASSERT(false)  // Something is wrong, there is ONE intersection and is not a vertex
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

EQIntersections QRay2D::IntersectionPoint(const QBaseQuadrilateral &quad, QBaseVector2 &vIntersection1, QBaseVector2 &vIntersection2) const
{
    QVector2 vAux;

    if ( PointInsideQuadrilateral(quad, this->Origin) ) // Ray end point is inside quadrilateral
    {
        if (this->Origin == quad.A) // Ray end point is A quadrilateral vertex
        {
            vIntersection1 = this->Origin;

            // Checks intersection with opposite edges
            if (this->IntersectionPoint(quad.B, quad.C, vAux) == EQIntersections::E_One) // Intersection found
            {
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            else if (this->IntersectionPoint(quad.C, quad.D, vAux) == EQIntersections::E_One) // Intersection found
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
            if (this->IntersectionPoint(quad.C, quad.D, vAux) == EQIntersections::E_One) // Intersection found
            {
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            else if (this->IntersectionPoint(quad.D, quad.A, vAux) == EQIntersections::E_One) // Intersection found
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
            if (this->IntersectionPoint(quad.D, quad.A, vAux) == EQIntersections::E_One) // Intersection found
            {
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            else if (this->IntersectionPoint(quad.A, quad.B, vAux) == EQIntersections::E_One) // Intersection found
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
            if (this->IntersectionPoint(quad.A, quad.B, vAux) == EQIntersections::E_One) // Intersection found
            {
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            else if (this->IntersectionPoint(quad.B, quad.C, vAux) == EQIntersections::E_One) // Intersection found
            {
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            else // No intersection found
                return EQIntersections::E_One;
        }
        else if (SQFloat::IsZero(QLineSegment2D(quad.A, quad.B).MinDistance(this->Origin))) // Ray end point is in AB quadrilateral edge
        {
            if (this->IntersectionPoint(quad.B, quad.C, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                if (vAux == quad.B) // Intersection is in common vertex
                {
                    vIntersection1 = quad.B;
                    return EQIntersections::E_One;
                }
                else // Intersection is in edge
                {
                    vIntersection1 = this->Origin;
                    vIntersection2 = vAux;
                    return EQIntersections::E_Two;
                }
            }
            else if (this->IntersectionPoint(quad.C, quad.D, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                vIntersection1 = this->Origin;
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            else if (this->IntersectionPoint(quad.D, quad.A, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                if (vAux == quad.A) // Intersection is in common vertex
                {
                    vIntersection1 = quad.A;
                    return EQIntersections::E_One;
                }
                else // Intersection is in edge
                {
                    vIntersection1 = this->Origin;
                    vIntersection2 = vAux;
                    return EQIntersections::E_Two;
                }
            }
            else // Ray don't intersects other edge
            {
                vIntersection1 = this->Origin;
                return EQIntersections::E_One;
            }
        }
        else if (SQFloat::IsZero(QLineSegment2D(quad.B, quad.C).MinDistance(this->Origin))) // Ray end point is in BC quadrilateral edge
        {
            if (this->IntersectionPoint(quad.C, quad.D, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                if (vAux == quad.C) // Intersection is in common vertex
                {
                    vIntersection1 = quad.C;
                    return EQIntersections::E_One;
                }
                else // Intersection is in edge
                {
                    vIntersection1 = this->Origin;
                    vIntersection2 = vAux;
                    return EQIntersections::E_Two;
                }
            }
            else if (this->IntersectionPoint(quad.D, quad.A, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                vIntersection1 = this->Origin;
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            if (this->IntersectionPoint(quad.A, quad.B, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                if (vAux == quad.B) // Intersection is in common vertex
                {
                    vIntersection1 = quad.B;
                    return EQIntersections::E_One;
                }
                else // Intersection is in edge
                {
                    vIntersection1 = this->Origin;
                    vIntersection2 = vAux;
                    return EQIntersections::E_Two;
                }
            }
            else // Ray don't intersects other edge
            {
                vIntersection1 = this->Origin;
                return EQIntersections::E_One;
            }
        }
        else if (SQFloat::IsZero(QLineSegment2D(quad.C, quad.D).MinDistance(this->Origin))) // Ray end point is in CD quadrilateral edge
        {
            if (this->IntersectionPoint(quad.D, quad.A, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                if (vAux == quad.D) // Intersection is in common vertex
                {
                    vIntersection1 = quad.D;
                    return EQIntersections::E_One;
                }
                else // Intersection is in edge
                {
                    vIntersection1 = this->Origin;
                    vIntersection2 = vAux;
                    return EQIntersections::E_Two;
                }
            }
            else if (this->IntersectionPoint(quad.A, quad.B, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                vIntersection1 = this->Origin;
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            if (this->IntersectionPoint(quad.B, quad.C, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                if (vAux == quad.C) // Intersection is in common vertex
                {
                    vIntersection1 = quad.C;
                    return EQIntersections::E_One;
                }
                else // Intersection is in edge
                {
                    vIntersection1 = this->Origin;
                    vIntersection2 = vAux;
                    return EQIntersections::E_Two;
                }
            }
            else // Ray don't intersects other edge
            {
                vIntersection1 = this->Origin;
                return EQIntersections::E_One;
            }
        }
        else if (SQFloat::IsZero(QLineSegment2D(quad.D, quad.A).MinDistance(this->Origin))) // Ray end point is in DA quadrilateral edge
        {
            if (this->IntersectionPoint(quad.A, quad.B, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                if (vAux == quad.A) // Intersection is in common vertex
                {
                    vIntersection1 = quad.A;
                    return EQIntersections::E_One;
                }
                else // Intersection is in edge
                {
                    vIntersection1 = this->Origin;
                    vIntersection2 = vAux;
                    return EQIntersections::E_Two;
                }
            }
            else if (this->IntersectionPoint(quad.B, quad.C, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                vIntersection1 = this->Origin;
                vIntersection2 = vAux;
                return EQIntersections::E_Two;
            }
            if (this->IntersectionPoint(quad.C, quad.D, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                if (vAux == quad.D) // Intersection is in common vertex
                {
                    vIntersection1 = quad.D;
                    return EQIntersections::E_One;
                }
                else // Intersection is in edge
                {
                    vIntersection1 = this->Origin;
                    vIntersection2 = vAux;
                    return EQIntersections::E_Two;
                }
            }
            else // Ray don't intersects other edge
            {
                vIntersection1 = this->Origin;
                return EQIntersections::E_One;
            }
        }
        else // Ray end point is strictly inside quadrilateral (is not in a vertex or an edge)
        {
            if (this->IntersectionPoint(quad.A, quad.B, vAux) == EQIntersections::E_One)
                vIntersection1 = vAux;
            else if (this->IntersectionPoint(quad.B, quad.C, vAux) == EQIntersections::E_One)
                vIntersection1 = vAux;
            else if (this->IntersectionPoint(quad.C, quad.D, vAux) == EQIntersections::E_One)
                vIntersection1 = vAux;
            else if (this->IntersectionPoint(quad.D, quad.A, vAux) == EQIntersections::E_One)
                vIntersection1 = vAux;
            else
                QE_ASSERT(false)  // Something is wrong, if ray point is interior, it must be ONE intersection with a edge.

            return EQIntersections::E_One;
        }
    }
    else // Ray end point is outside quadrilateral
    {
        QVector2 vPrevInt;
        bool bPrevInt = false;

        QVector2 vAuxAB;
        EQIntersections numIntAB = this->IntersectionPoint(quad.A, quad.B, vAuxAB); // Checks intersection with AB edge
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
        EQIntersections numIntBC = this->IntersectionPoint(quad.B, quad.C, vAuxBC); // Checks intersection with BC edge
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
        EQIntersections numIntCD = this->IntersectionPoint(quad.C, quad.D, vAuxCD); // Checks intersection with CD edge
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
        EQIntersections numIntDA = this->IntersectionPoint(quad.D, quad.A, vAuxDA); // Checks intersection with DA edge
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
                QE_ASSERT(false)  // Something is wrong
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
    QVector2 vAux(segment.B - segment.A);

    const float_q &DENOMINATOR = this->Direction.x * vAux.y - this->Direction.y * vAux.x;

    if ( SQFloat::IsZero(DENOMINATOR) ) // Both directions are parallels
    {
        const bool &A_IS_IN_RAY = this->Contains(segment.A);
        const bool &B_IS_IN_RAY = this->Contains(segment.B);

        if ( A_IS_IN_RAY && B_IS_IN_RAY )
            return EQIntersections::E_Infinite;
        else if ( A_IS_IN_RAY )
        {
            if (segment.A == this->Origin)
            {
                vIntersection = segment.A;
                return EQIntersections::E_One;
            }
            else
                return EQIntersections::E_Infinite;
        }
        else if ( B_IS_IN_RAY )
        {
            if (segment.B == this->Origin)
            {
                vIntersection = segment.B;
                return EQIntersections::E_One;
            }
            else
                return EQIntersections::E_Infinite;
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

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
