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
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |  CONSTANTS INITIALIZATION  |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################
const QRay2D QRay2D::RayZero(QVector2::ZeroVector, QVector2::ZeroVector);
const QRay2D QRay2D::RayX(QVector2::ZeroVector, QVector2::UnitVectorX);
const QRay2D QRay2D::RayY(QVector2::ZeroVector, QVector2::UnitVectorY);

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
    const float_q &fDenominator = this->Direction.x * ray.Direction.y - this->Direction.y * ray.Direction.x;

    if ( QFloat::IsZero(fDenominator) ) // Both directions are parallels
    {
        if ( this->Contains(ray.Point) )
            return true;
        else
            return ( reinterpret_cast<const QRay2D &> (ray).Contains(this->Point) );
    }
    else // rays are not parallel
    {
        const float_q &fNumerator1 = this->Direction.x * (this->Point.y - ray.Point.y) + this->Direction.y * (ray.Point.x - this->Point.x);
        if ((QFloat::IsNegative(fDenominator) == QFloat::IsNegative(fNumerator1)) || QFloat::IsZero(fNumerator1))
        {
            const float_q &fNumerator2 = ray.Direction.x * (this->Point.y - ray.Point.y) + ray.Direction.y * (ray.Point.x - this->Point.x);

            return ( (QFloat::IsNegative(fDenominator) == QFloat::IsNegative(fNumerator2)) || QFloat::IsZero(fNumerator2) );
        }
        else
            return false;
    }
}

EQIntersections QRay2D::IntersectionPoint(const QBaseRay<QVector2, QVector2> &ray, QBaseVector2 &vPoint) const
{
    const float_q &fDenominator = this->Direction.x * ray.Direction.y - this->Direction.y * ray.Direction.x;

    if ( QFloat::IsZero(fDenominator) ) // Both directions are parallels
    {
        if (this->Point == ray.Point)
        {
            if ( (this->Direction + ray.Direction) == QVector2::ZeroVector ) // Directions are opposite (are supossed normalized)
            {
                vPoint = this->Point;
                return EQIntersections::E_One;
            }
            else
                return EQIntersections::E_Infinite; //Both rays are the same
        }
        else if ( this->Contains(ray.Point) || reinterpret_cast<const QRay2D &> (ray).Contains(this->Point))
            return EQIntersections::E_Infinite;
        else
            return EQIntersections::E_None;
    }
    else
    {
        const float_q &fNumerator1 = this->Direction.x * (this->Point.y - ray.Point.y) +
                                     this->Direction.y * (ray.Point.x - this->Point.x);

        // Forces first parameter to be greater o equal to 0
        if ((QFloat::IsNegative(fDenominator) == QFloat::IsNegative(fNumerator1)) || QFloat::IsZero(fNumerator1))
        {
            const float_q &fNumerator2 = ray.Direction.x * (this->Point.y - ray.Point.y) + ray.Direction.y * (ray.Point.x - this->Point.x);

            // Forces second parameter to be greater o equal to 0
            if ( (QFloat::IsNegative(fDenominator) == QFloat::IsNegative(fNumerator2)) || QFloat::IsZero(fNumerator2) )
            {
                vPoint = this->Point + (fNumerator2/fDenominator) * this->Direction;
                return EQIntersections::E_One;
            }
            else
                return EQIntersections::E_None;
        }
        else
            return EQIntersections::E_None;
    }
}

EQIntersections QRay2D::IntersectionPoint(const QBaseOrb<QVector2> &orb, QBaseVector2 &vPoint1, QBaseVector2 &vPoint2) const
{
    // [TODO] jwladi: esto debería ir a QRay, pues no depende de coordenadas

    // We reduce ray and orb to origin, in order to simplify orb equation, and we calculate
    // the new ray origin point
    QVector2 vNewRayPoint(this->Point - orb.P);

    // We replace then in the orb equation to force it to verify the ray equation
    // vDirection^2*t^2 + 2*vNewA*vDirection*t + vNewA^2 - r^2 = 0
    // The intersections with ray follows this rules (extracted from quadratic ecuation):
    //       D = b^2 - 4ac = 0 => 1 intersection
    //       D = b^2 - 4ac < 0 => 0 intersections
    //       D = b^2 - 4ac > 0 => 2 intersections

    // Since ray is normalized, a = 1
    // const float_q &a = this->Direction.DotProduct(this->Direction);

    const float_q &b = QFloat::_2 * vNewRayPoint.DotProduct(this->Direction);
    const float_q &c = vNewRayPoint.DotProduct(vNewRayPoint) - orb.Radius * orb.Radius;

    // Remember that a = 1 -> D = b^2 - 4ac = b^2 - 4c
    const float_q &D = b * b - QFloat::_4 * c;


    if (QFloat::IsNegative(D)) // D = b^2 - 4ac < 0 => 0 intersections
        return EQIntersections::E_None;
    else if (QFloat::IsZero(D)) // D = b^2 - 4ac = 0 => 1 intersection
    {
        // t = -b/2a -> Remember that a=1
        const float_q &t = -b*QFloat::_0_5;

        vPoint1 = vNewRayPoint + t * this->Direction + orb.P;
        return EQIntersections::E_One;
    }
    else // D = b^2 - 4ac > 0 => 2 intersections
    {
        const float_q &fAux1 = sqrt(D);

        // Closest intersection to ls.A. t = (-b - sqrt(D))/2a -> Remember that a = 1
        const float_q &t1 = -(b + fAux1)*QFloat::_0_5;
        vPoint1 = vNewRayPoint + t1 * this->Direction + orb.P;

        // Farthest intersection to ls.A. t = (-b + sqrt(D))/2a -> Remember that a = 1
        const float_q &t2 = (-b + fAux1)*QFloat::_0_5;

        // Prevent rays with end point inside orb.
        const bool &t1Fails = QFloat::IsNegative(t1);
        const bool &t2Fails = QFloat::IsNegative(t2);

        if (t1Fails && t2Fails)
            return EQIntersections::E_None; // Shouldn't happen this :(
        else if (QFloat::IsNegative(t1))  // One parameter is negative, there is only one intersection
        {
            vPoint1 = vNewRayPoint + t2 * this->Direction + orb.P; // First vPoint1 is bad computed.
            return EQIntersections::E_One;
        }
        else if (QFloat::IsNegative(t2)) // One parameter is negative, there is only one intersection
            return EQIntersections::E_One; // First vPoint1 is ok, vPoint2 is not used.
        else // Most of the cases: two intersections.
        {
            vPoint2 = vNewRayPoint + t2 * this->Direction + orb.P; // vPoint1 and vPoint2 are ok.
            return EQIntersections::E_Two;
        }
    }
}

EQIntersections QRay2D::IntersectionPoint(const QBaseTriangle2 &triangle, QBaseVector2 &vPoint1, QBaseVector2 &vPoint2) const
{
    QVector2 vAux;

    if ( PointInsideTriangle(triangle, this->Point) ) // Ray end point is inside triangle
    {
        if (this->Point == triangle.A) // Ray end point is A triangle vertex
        {
            vPoint1 = this->Point;

            // Checks intersection with opposite edge (it should not return E_Infinite, is the opposite edge)
            if (this->IntersectionPoint(triangle.B, triangle.C, vAux) == EQIntersections::E_None) // No intersection found
                return EQIntersections::E_One;
            else // Intersection found
            {
                vPoint2 = vAux;
                return EQIntersections::E_Two;
            }
        }
        else if (this->Point == triangle.B) // Ray end point is B triangle vertex
        {
            vPoint1 = this->Point;

           // Checks intersection with opposite edge
            if (this->IntersectionPoint(triangle.C, triangle.A, vAux) == EQIntersections::E_None) // No intersection found
                return EQIntersections::E_One;
            else // Intersection found
            {
                vPoint2 = vAux;
                return EQIntersections::E_Two;
            }
        }
        else if (this->Point == triangle.C) // Ray end point is C triangle vertex
        {
            vPoint1 = this->Point;

            // Checks intersection with opposite edge
            if (this->IntersectionPoint(triangle.A, triangle.B, vAux) == EQIntersections::E_None) // No intersection found
                return EQIntersections::E_One;
            else // Intersection found
            {
                vPoint2 = vAux;
                return EQIntersections::E_Two;
            }
        }
        else if (QFloat::IsZero(QLineSegment2D(triangle.A, triangle.B).MinDistance(this->Point))) // Ray end point is in AB triangle edge
        {
            if (this->IntersectionPoint(triangle.B, triangle.C, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                if (vAux == triangle.B) // Intersection is in common vertex
                {
                    vPoint1 = triangle.B;
                    return EQIntersections::E_One;
                }
                else // Intersection is in edge
                {
                    vPoint1 = this->Point;
                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
            }
            else if (this->IntersectionPoint(triangle.C, triangle.A, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                if (vAux == triangle.A) // Intersection is in common vertex
                {
                    vPoint1 = triangle.A;
                    return EQIntersections::E_One;
                }
                else // Intersection is in edge
                {
                    vPoint1 = this->Point;
                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
            }
            else // Ray don't intersects other edge
            {
                vPoint1 = this->Point;
                return EQIntersections::E_One;
            }
        }
        else if (QFloat::IsZero(QLineSegment2D(triangle.B, triangle.C).MinDistance(this->Point))) // Ray end point is in BC triangle edge
        {
            if (this->IntersectionPoint(triangle.C, triangle.A, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                if (vAux == triangle.C) // Intersection is in common vertex
                {
                    vPoint1 = triangle.C;
                    return EQIntersections::E_One;
                }
                else // Intersection is in edge
                {
                    vPoint1 = this->Point;
                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
            }
            else if (this->IntersectionPoint(triangle.A, triangle.B, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                if (vAux == triangle.B) // Intersection is in common vertex
                {
                    vPoint1 = triangle.B;
                    return EQIntersections::E_One;
                }
                else // Intersection is in edge
                {
                    vPoint1 = this->Point;
                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
            }
            else // Ray don't intersects other edge
            {
                vPoint1 = this->Point;
                return EQIntersections::E_One;
            }
        }
        else if (QFloat::IsZero(QLineSegment2D(triangle.C, triangle.A).MinDistance(this->Point))) // Ray end point is in CA triangle edge
        {
            if (this->IntersectionPoint(triangle.A, triangle.B, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                if (vAux == triangle.A) // Intersection is in common vertex
                {
                    vPoint1 = triangle.A;
                    return EQIntersections::E_One;
                }
                else // Intersection is in edge
                {
                    vPoint1 = this->Point;
                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
            }
            else if (this->IntersectionPoint(triangle.B, triangle.C, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                if (vAux == triangle.C) // Intersection is in common vertex
                {
                    vPoint1 = triangle.C;
                    return EQIntersections::E_One;
                }
                else // Intersection is in edge
                {
                    vPoint1 = this->Point;
                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
            }
            else // Ray don't intersects other edge
            {
                vPoint1 = this->Point;
                return EQIntersections::E_One;
            }
        }
        else // Ray end point is strictly inside triangle (is not in a vertex or an edge
        {
            if (this->IntersectionPoint(triangle.A, triangle.B, vAux) == EQIntersections::E_One)
                vPoint1 = vAux;
            else if (this->IntersectionPoint(triangle.B, triangle.C, vAux) == EQIntersections::E_One)
                vPoint1 = vAux;
            else if (this->IntersectionPoint(triangle.C, triangle.A, vAux) == EQIntersections::E_One)
                vPoint1 = vAux;
            else
                QE_ASSERT(false); // Something is wrong, if ray point is interior, it must be ONE intersection with a edge.

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
            if  ( (triangle.A - this->Point).GetSquaredLength() < (triangle.B - this->Point).GetSquaredLength() )
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

        QVector2 vAuxBC;
        EQIntersections numIntBC = this->IntersectionPoint(triangle.B, triangle.C, vAuxBC); // Checks intersection with BC edge
        if (numIntBC == EQIntersections::E_Infinite) // Ray contains BC edge
        {
            // Looks for closest point to ray end point
            if  ( (triangle.B - this->Point).GetSquaredLength() < (triangle.C - this->Point).GetSquaredLength() )
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

        QVector2 vAuxCA;
        EQIntersections numIntCA = this->IntersectionPoint(triangle.C, triangle.A, vAuxCA); // Checks intersection with BC edge
        if (numIntCA == EQIntersections::E_Infinite) // Ray contains CA edge
        {
            // Looks for closest point to ray end point
            if  ( (triangle.C - this->Point).GetSquaredLength() < (triangle.A - this->Point).GetSquaredLength() )
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
                    if  ( (vAuxBC - this->Point).GetSquaredLength() < (vPrevInt - this->Point).GetSquaredLength() )
                    {
                        vPoint1 = vAuxBC;
                        vPoint2 = vPrevInt;
                    }
                    else
                    {
                        vPoint1 = vPrevInt;
                        vPoint2 = vAuxBC;
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
                    if  ( (vAuxCA - this->Point).GetSquaredLength() < (vPrevInt - this->Point).GetSquaredLength() )
                    {
                        vPoint1 = vAuxCA;
                        vPoint2 = vPrevInt;
                    }
                    else
                    {
                        vPoint1 = vPrevInt;
                        vPoint2 = vAuxCA;
                    }
                    return EQIntersections::E_Two;
                }
            }
            else
                QE_ASSERT(false); // Something is wrong, there is ONE intersection and is not a vertex
        }

        if (bPrevInt)
        {
            vPoint1 = vPrevInt;
            return EQIntersections::E_One;
        }
        else
            return EQIntersections::E_None;
    }
}

EQIntersections QRay2D::IntersectionPoint(const QBaseQuadrilateral &quad, QBaseVector2 &vPoint1, QBaseVector2 &vPoint2) const
{
    QVector2 vAux;

    if ( PointInsideQuadrilateral(quad, this->Point) ) // Ray end point is inside quadrilateral
    {
        if (this->Point == quad.A) // Ray end point is A quadrilateral vertex
        {
            vPoint1 = this->Point;

            // Checks intersection with opposite edges
            if (this->IntersectionPoint(quad.B, quad.C, vAux) == EQIntersections::E_One) // Intersection found
            {
                vPoint2 = vAux;
                return EQIntersections::E_Two;
            }
            else if (this->IntersectionPoint(quad.C, quad.D, vAux) == EQIntersections::E_One) // Intersection found
            {
                vPoint2 = vAux;
                return EQIntersections::E_Two;
            }
            else // No intersection found
                return EQIntersections::E_One;
        }
        else if (this->Point == quad.B) // Ray end point is B quadrilateral vertex
        {
            vPoint1 = this->Point;

           // Checks intersection with opposite edges
            if (this->IntersectionPoint(quad.C, quad.D, vAux) == EQIntersections::E_One) // Intersection found
            {
                vPoint2 = vAux;
                return EQIntersections::E_Two;
            }
            else if (this->IntersectionPoint(quad.D, quad.A, vAux) == EQIntersections::E_One) // Intersection found
            {
                vPoint2 = vAux;
                return EQIntersections::E_Two;
            }
            else // No intersection found
                return EQIntersections::E_One;
        }
        else if (this->Point == quad.C) // Ray end point is C quadrilateral vertex
        {
            vPoint1 = this->Point;

            // Checks intersection with opposite edges
            if (this->IntersectionPoint(quad.D, quad.A, vAux) == EQIntersections::E_One) // Intersection found
            {
                vPoint2 = vAux;
                return EQIntersections::E_Two;
            }
            else if (this->IntersectionPoint(quad.A, quad.B, vAux) == EQIntersections::E_One) // Intersection found
            {
                vPoint2 = vAux;
                return EQIntersections::E_Two;
            }
            else // No intersection found
                return EQIntersections::E_One;
        }
        else if (this->Point == quad.D) // Ray end point is D quadrilateral vertex
        {
            vPoint1 = this->Point;

            // Checks intersection with opposite edges
            if (this->IntersectionPoint(quad.A, quad.B, vAux) == EQIntersections::E_One) // Intersection found
            {
                vPoint2 = vAux;
                return EQIntersections::E_Two;
            }
            else if (this->IntersectionPoint(quad.B, quad.C, vAux) == EQIntersections::E_One) // Intersection found
            {
                vPoint2 = vAux;
                return EQIntersections::E_Two;
            }
            else // No intersection found
                return EQIntersections::E_One;
        }
        else if (QFloat::IsZero(QLineSegment2D(quad.A, quad.B).MinDistance(this->Point))) // Ray end point is in AB quadrilateral edge
        {
            if (this->IntersectionPoint(quad.B, quad.C, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                if (vAux == quad.B) // Intersection is in common vertex
                {
                    vPoint1 = quad.B;
                    return EQIntersections::E_One;
                }
                else // Intersection is in edge
                {
                    vPoint1 = this->Point;
                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
            }
            else if (this->IntersectionPoint(quad.C, quad.D, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                vPoint1 = this->Point;
                vPoint2 = vAux;
                return EQIntersections::E_Two;
            }
            else if (this->IntersectionPoint(quad.D, quad.A, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                if (vAux == quad.A) // Intersection is in common vertex
                {
                    vPoint1 = quad.A;
                    return EQIntersections::E_One;
                }
                else // Intersection is in edge
                {
                    vPoint1 = this->Point;
                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
            }
            else // Ray don't intersects other edge
            {
                vPoint1 = this->Point;
                return EQIntersections::E_One;
            }
        }
        else if (QFloat::IsZero(QLineSegment2D(quad.B, quad.C).MinDistance(this->Point))) // Ray end point is in BC quadrilateral edge
        {
            if (this->IntersectionPoint(quad.C, quad.D, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                if (vAux == quad.C) // Intersection is in common vertex
                {
                    vPoint1 = quad.C;
                    return EQIntersections::E_One;
                }
                else // Intersection is in edge
                {
                    vPoint1 = this->Point;
                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
            }
            else if (this->IntersectionPoint(quad.D, quad.A, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                vPoint1 = this->Point;
                vPoint2 = vAux;
                return EQIntersections::E_Two;
            }
            if (this->IntersectionPoint(quad.A, quad.B, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                if (vAux == quad.B) // Intersection is in common vertex
                {
                    vPoint1 = quad.B;
                    return EQIntersections::E_One;
                }
                else // Intersection is in edge
                {
                    vPoint1 = this->Point;
                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
            }
            else // Ray don't intersects other edge
            {
                vPoint1 = this->Point;
                return EQIntersections::E_One;
            }
        }
        else if (QFloat::IsZero(QLineSegment2D(quad.C, quad.D).MinDistance(this->Point))) // Ray end point is in CD quadrilateral edge
        {
            if (this->IntersectionPoint(quad.D, quad.A, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                if (vAux == quad.D) // Intersection is in common vertex
                {
                    vPoint1 = quad.D;
                    return EQIntersections::E_One;
                }
                else // Intersection is in edge
                {
                    vPoint1 = this->Point;
                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
            }
            else if (this->IntersectionPoint(quad.A, quad.B, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                vPoint1 = this->Point;
                vPoint2 = vAux;
                return EQIntersections::E_Two;
            }
            if (this->IntersectionPoint(quad.B, quad.C, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                if (vAux == quad.C) // Intersection is in common vertex
                {
                    vPoint1 = quad.C;
                    return EQIntersections::E_One;
                }
                else // Intersection is in edge
                {
                    vPoint1 = this->Point;
                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
            }
            else // Ray don't intersects other edge
            {
                vPoint1 = this->Point;
                return EQIntersections::E_One;
            }
        }
        else if (QFloat::IsZero(QLineSegment2D(quad.D, quad.A).MinDistance(this->Point))) // Ray end point is in DA quadrilateral edge
        {
            if (this->IntersectionPoint(quad.A, quad.B, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                if (vAux == quad.A) // Intersection is in common vertex
                {
                    vPoint1 = quad.A;
                    return EQIntersections::E_One;
                }
                else // Intersection is in edge
                {
                    vPoint1 = this->Point;
                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
            }
            else if (this->IntersectionPoint(quad.B, quad.C, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                vPoint1 = this->Point;
                vPoint2 = vAux;
                return EQIntersections::E_Two;
            }
            if (this->IntersectionPoint(quad.C, quad.D, vAux) == EQIntersections::E_One) // Ray intersects other edge
            {
                if (vAux == quad.D) // Intersection is in common vertex
                {
                    vPoint1 = quad.D;
                    return EQIntersections::E_One;
                }
                else // Intersection is in edge
                {
                    vPoint1 = this->Point;
                    vPoint2 = vAux;
                    return EQIntersections::E_Two;
                }
            }
            else // Ray don't intersects other edge
            {
                vPoint1 = this->Point;
                return EQIntersections::E_One;
            }
        }
        else // Ray end point is strictly inside quadrilateral (is not in a vertex or an edge)
        {
            if (this->IntersectionPoint(quad.A, quad.B, vAux) == EQIntersections::E_One)
                vPoint1 = vAux;
            else if (this->IntersectionPoint(quad.B, quad.C, vAux) == EQIntersections::E_One)
                vPoint1 = vAux;
            else if (this->IntersectionPoint(quad.C, quad.D, vAux) == EQIntersections::E_One)
                vPoint1 = vAux;
            else if (this->IntersectionPoint(quad.D, quad.A, vAux) == EQIntersections::E_One)
                vPoint1 = vAux;
            else
                QE_ASSERT(false); // Something is wrong, if ray point is interior, it must be ONE intersection with a edge.

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
            if  ( (quad.A - this->Point).GetSquaredLength() < (quad.B - this->Point).GetSquaredLength() )
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

        QVector2 vAuxBC;
        EQIntersections numIntBC = this->IntersectionPoint(quad.B, quad.C, vAuxBC); // Checks intersection with BC edge
        if (numIntBC == EQIntersections::E_Infinite) // Ray contains BC edge
        {
            // Looks for closest point to ray end point
            if  ( (quad.B - this->Point).GetSquaredLength() < (quad.C - this->Point).GetSquaredLength() )
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

        QVector2 vAuxCD;
        EQIntersections numIntCD = this->IntersectionPoint(quad.C, quad.D, vAuxCD); // Checks intersection with CD edge
        if (numIntCD == EQIntersections::E_Infinite) // Ray contains CD edge
        {
            // Looks for closest point to ray end point
            if  ( (quad.C - this->Point).GetSquaredLength() < (quad.D - this->Point).GetSquaredLength() )
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

        QVector2 vAuxDA;
        EQIntersections numIntDA = this->IntersectionPoint(quad.D, quad.A, vAuxDA); // Checks intersection with DA edge
        if (numIntDA == EQIntersections::E_Infinite) // Ray contains DA edge
        {
            // Looks for closest point to ray end point
            if  ( (quad.D - this->Point).GetSquaredLength() < (quad.A - this->Point).GetSquaredLength() )
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
                    if  ( (vAuxBC - this->Point).GetSquaredLength() < (vPrevInt - this->Point).GetSquaredLength() )
                    {
                        vPoint1 = vAuxBC;
                        vPoint2 = vPrevInt;
                    }
                    else
                    {
                        vPoint1 = vPrevInt;
                        vPoint2 = vAuxBC;
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
                    if  ( (vAuxCD - this->Point).GetSquaredLength() < (vPrevInt - this->Point).GetSquaredLength() )
                    {
                        vPoint1 = vAuxCD;
                        vPoint2 = vPrevInt;
                    }
                    else
                    {
                        vPoint1 = vPrevInt;
                        vPoint2 = vAuxCD;
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
                    if  ( (vAuxDA - this->Point).GetSquaredLength() < (vPrevInt - this->Point).GetSquaredLength() )
                    {
                        vPoint1 = vAuxDA;
                        vPoint2 = vPrevInt;
                    }
                    else
                    {
                        vPoint1 = vPrevInt;
                        vPoint2 = vAuxDA;
                    }
                    return EQIntersections::E_Two;
                }
            }
            else // Its the first intersection found
                QE_ASSERT(false); // Something is wrong
        }

        if (bPrevInt)
        {
            vPoint1 = vPrevInt;
            return EQIntersections::E_One;
        }
        else
            return EQIntersections::E_None;
    }
}

bool QRay2D::Intersection (const QBaseLineSegment2 &ls) const
{
    QVector2 vAux(ls.B - ls.A);

    const float_q &fDenominator = this->Direction.x * vAux.y - this->Direction.y * vAux.x;

    if ( QFloat::IsZero(fDenominator) ) // Both directions are parallels
    {
        if ( this->Contains(ls.A) )
            return true;
        else if ( this->Contains(ls.B) )
            return true;
        else
            return false;
    }
    else
    {
        const float_q &fNumerator1 = vAux.x * (this->Point.y - ls.A.y) + vAux.y * (ls.A.x - this->Point.x);
        if ((QFloat::IsNegative(fDenominator) == QFloat::IsNegative(fNumerator1)) || QFloat::IsZero(fNumerator1))
        {
            const float_q &fNumerator2 = this->Direction.x * (this->Point.y - ls.A.y) + this->Direction.y * (ls.A.x - this->Point.x);
            if ( ( QFloat::IsNegative(fDenominator) == QFloat::IsNegative(fNumerator2) &&
                   QFloat::IsGreaterOrEquals(QFloat::Abs(fDenominator), QFloat::Abs(fNumerator2)) ) || QFloat::IsZero(fNumerator2) )
                return true;
            else
                return false;
        }
        else
            return false;
    }
}

EQIntersections QRay2D::IntersectionPoint (const QBaseLineSegment2 &ls, QBaseVector2 &vPoint) const
{
    QVector2 vAux(ls.B - ls.A);

    const float_q &fDenominator = this->Direction.x * vAux.y - this->Direction.y * vAux.x;

    if ( QFloat::IsZero(fDenominator) ) // Both directions are parallels
    {
        const bool &bAIsInRay = this->Contains(ls.A);
        const bool &bBIsInRay = this->Contains(ls.B);

        if ( bAIsInRay && bBIsInRay )
            return EQIntersections::E_Infinite;
        else if ( bAIsInRay )
        {
            if (ls.A == this->Point)
            {
                vPoint = ls.A;
                return EQIntersections::E_One;
            }
            else
                return EQIntersections::E_Infinite;
        }
        else if ( bBIsInRay )
        {
            if (ls.B == this->Point)
            {
                vPoint = ls.B;
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
        const float_q &fNumerator1 = vAux.x * (this->Point.y - ls.A.y) + vAux.y * (ls.A.x - this->Point.x);
        if ((QFloat::IsNegative(fDenominator) == QFloat::IsNegative(fNumerator1)) || QFloat::IsZero(fNumerator1))
        {
            const float_q &fNumerator2 = this->Direction.x * (this->Point.y - ls.A.y) + this->Direction.y * (ls.A.x - this->Point.x);
            if ( ( QFloat::IsNegative(fDenominator) == QFloat::IsNegative(fNumerator2) &&
                   QFloat::IsGreaterOrEquals(QFloat::Abs(fDenominator), QFloat::Abs(fNumerator2)) ) || QFloat::IsZero(fNumerator2) )
            {
                vPoint = this->Point + (fNumerator1/fDenominator) * this->Direction;
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
