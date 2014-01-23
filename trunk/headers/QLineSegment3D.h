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

#ifndef __QLINESEGMENT3D__
#define __QLINESEGMENT3D__

#include "QBaseLineSegment.h"
#include "QLineSegment.h"
#include "QPlane.h"
#include "EQSpaceRelation.h"
#include "QBaseOrb.h"
#include "QBaseTriangle.h"
#include "QBaseHexahedron.h"
#include "QQuaternion.h"
#include "QDualQuaternion.h"
#include "SQPoint.h"
#include "QTransformationMatrix.h"
#include "QTranslationMatrix.h"
#include "QSpaceConversionMatrix.h"
#include "QRotationMatrix3x3.h"
#include "QScalingMatrix3x3.h"

using Kinesis::QuimeraEngine::Common::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Common::DataTypes::float_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

/// <summary>
/// Class which represents a chunk (segment) of straight line in 3D space, defined by two endpoints A and B.
/// </summary>
/// <remarks>
/// These points may be expressed as 3D points or vectors, depending on the template parameter,
/// which may be 3D vector or 4D vector.<br/>
/// Please note there's really no "source" and "end" points implicit, that is, it's not an oriented segment.
/// </remarks>
/// <typeparam name="VectorType">Allowed types: QVector3, QVector4.</typeparam>
template <class VectorType>
class QLineSegment3D : public QLineSegment<VectorType>
{
    // BASE TYPE USINGS
    // ---------------
public:

    using QLineSegment<VectorType>::Intersection;
	using QLineSegment<VectorType>::IntersectionPoint;
	using QLineSegment<VectorType>::MinDistance;


 	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
    QLineSegment3D()
    {
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="segment">[IN] Line segment from which we want to create a copy in the resident segment.</param>
	QLineSegment3D(const QLineSegment3D &segment) : QLineSegment<VectorType>(segment.A, segment.B)
    {
    }

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <param name="segment">[IN] Line segment in which we want resident segment to be based.</param>
	QLineSegment3D(const QBaseLineSegment<VectorType> &segment) : QLineSegment<VectorType>(segment.A, segment.B)
    {
    }

    /// <summary>
    /// Constructor from two vectors.
    /// </summary>
    /// <param name="vA">[IN] Vector to define endpoint A.</param>
    /// <param name="vB">[IN] Vector to define endpoint B.</param>
	QLineSegment3D(const VectorType &vA, const VectorType &vB) : QLineSegment<VectorType>(vA,vB)
    {
    }


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Unit segment lying on positive X axis (it's length equals 1).
    /// </summary>
    /// <returns>
	/// A 1-length line segment.
	/// </returns>
	static const QLineSegment3D<VectorType>& GetUnitLine()
	{
	    static const QLineSegment3D<VectorType> UNITLINE(VectorType::GetNullVector(), VectorType::GetUnitVectorX());
	    return UNITLINE;
    }

    /// <summary>
    /// Zero segment lying in the coordinates center whose endpoints both equals (0, 0, 0) and it's length equals 0.
    /// </summary>
    /// <returns>
	/// A 0-length line segment.
	/// </returns>
	static const QLineSegment3D<VectorType>& GetLineZero()
	{
	    static const QLineSegment3D<VectorType> LINEZERO(VectorType::GetNullVector(), VectorType::GetNullVector());
	    return LINEZERO;
	}


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Assignation operator. Assigns the provided line segment to the resident line segment.
    /// </summary>
    /// <param name="segment">[IN] The line segment to be assigned.</param>
    /// <returns>
    /// A reference to the modified line segment.
    /// </returns>
    QLineSegment3D& operator=(const QBaseLineSegment<VectorType> &segment)
    {
        QBaseLineSegment<VectorType>::operator=(segment);
        return *this;
    }

    /// <summary>
    /// Checks if the line segment intersects with the provided plane.
    /// </summary>
    /// <remarks>
    /// Since a plane divides space into two sides (positive and negative), we can check how the end points of
    /// the line segment satisfies the plane equation.<br/>
    /// Being the plane equation:<br/><br/>
    /// \f$ ax + by + cz + d = 0 \f$,<br/><br/>
    /// and the end points of the line segment \f$ A(A_x, A_y, A_z)\f$, \f$ B(B_x, B_y, B_z)\f$,
    /// we have to check the value of:<br/><br/>
    /// (1) \f$ a\cdot A_x + b\cdot A_y + c\cdot A_z + d \f$
    /// <br/>
    /// (2) \f$ a\cdot B_x + b\cdot B_y + c\cdot B_z + d \f$
    /// <br/><br/>
    /// If (1) = 0 or (2) = 0, then the line segment intersects the plane (one of the end points lies on plane).<br/>
    /// If the sign of (1) and (2) are different, each end point is in a different side of the space
    /// divided by the plane, and then the line segment intersects the plane.<br/>
    /// If (1) and (2) have the same sign, then they are in the same side of the space divided by the plane,
    /// and the line segment does not intersect with the plane.<br/>
    /// If one end point of the line segment lies on the plane, we consider there is an intersection.
    /// </remarks>
    /// <param name="plane">[IN] The plane we want check if intersects with resident line segment. If the plane is null,
    /// the behavior is undefined.</param>
    /// <returns>
	/// A boolean value that indicates whether the segment and the plane intersect or not.<br/>
    /// <br/>
    /// <b>True</b><br/>
    /// The segment and the plane intersect, including the following cases:
    /// - The endpoints are in different sides of the space divided by the plane.
    /// - The segment is contained in the plane.
    /// - Only one endpoint belongs to the plane.
    ///
    /// <b>False</b><br/>
    /// The line segment does not intersect with the plane.
	/// </returns>
    bool Intersection(const QBasePlane &plane) const
    {
        // The length of the segment should be greater than zero
        QE_ASSERT(this->A != this->B);

        // The plane shouldn't be null
        QE_ASSERT( SQFloat::IsNotZero(plane.a) || SQFloat::IsNotZero(plane.b) || SQFloat::IsNotZero(plane.c) );

        const float_q &DIST_A = plane.a * this->A.x + plane.b * this->A.y + plane.c * this->A.z + plane.d;

        if (SQFloat::IsZero(DIST_A))
            return true;

        const float_q &DIST_B = plane.a * this->B.x + plane.b * this->B.y + plane.c * this->B.z + plane.d;

        if (SQFloat::IsZero(DIST_B))
            return true;

        return SQFloat::IsNegative(DIST_A * DIST_B);
    }

    /// <summary>
    /// Checks if the line segment intersects with the provided triangle.
    /// </summary>
    /// <param name="triangle">[IN] The triangle we want check if intersects with resident line segment. If any of its vertices 
    /// coincide, the behavior is undefined.</param>
    /// <returns>
	/// A boolean value that indicates whether the segment and the triangle intersect or not.<br/>
    /// <br/>
    /// <b>True</b><br/>
    /// The segment and the triangle intersect, including the following cases:
    /// - The segment intersects with one or two edges of the triangle.
    /// - The segment intersects with a vertex of the triangle.
    /// - Only one endpoint is inside of the triangle (not intersecting with any edge).
    /// - The segment intersects with the interior (the face) of the triangle (not intersecting with any edge and not being contained).
    /// - The segment is completely contained in the triangle.
    /// - An endpoint of the segment is contained in an edge of the triangle, even if the other endpoint is inside of the triangle.
    /// - The segment is contained in an edge of the triangle.
    /// - The segment contains an edge of the triangle.
    /// - One or both endpoints coincide with the vertices of the triangle.
    /// 
    /// <b>False</b><br/>
    /// The line segment does not intersect with the triangle.
	/// </returns>
    bool Intersection(const QBaseTriangle<VectorType> &triangle) const
    {
        // The length of the segment should be greater than zero
        QE_ASSERT(this->A != this->B);

        // Vertices of the triangle should not coincide
        QE_ASSERT(triangle.A != triangle.B && triangle.B != triangle.C && triangle.C != triangle.A);

        // Calculates if segment intersects with the plane defined by the triangle.

        // Plane equation
        QPlane auxP(triangle.A, triangle.B, triangle.C);

        // Line Segment don't intersects the triangle plane.
        if (!this->Intersection(auxP))
            return false;

        // If both end points satisfy plane equation, the line segment lies on plane
        const float_q &DOT1 = auxP.a * this->B.x + auxP.b * this->B.y + auxP.c * this->B.z + auxP.d;
        const float_q &DOT2 = auxP.a * this->A.x + auxP.b * this->A.y + auxP.c * this->A.z + auxP.d;

        if (SQFloat::IsZero(DOT1) && SQFloat::IsZero(DOT2))
        {
            // Both triangle and line segment are coplanars. If the line segment
            // intersects one of the edges of the triangle, then the line segment intersects the triangle.
            if (this->QLineSegment<VectorType>::Intersection(QLineSegment<VectorType> (triangle.A, triangle.B)) ||
                this->QLineSegment<VectorType>::Intersection(QLineSegment<VectorType> (triangle.B, triangle.C)) ||
                this->QLineSegment<VectorType>::Intersection(QLineSegment<VectorType> (triangle.C, triangle.A)))
                return true;

            // If not, we check if segment is fully contained in the triangle
            // We only check "A" end point, since if "A" is inside, "B" must be inside too (see previus test).
            else
                return PointInsideTriangle(triangle, this->A);
        }

        QE_ASSERT(SQFloat::IsNotZero(DOT2 - DOT1))

        // The point which satisfies both line and plane equations.
        VectorType vAux = this->A + (this->B - this->A) * DOT2/(DOT2 - DOT1);

        // Tests if the point is inside the triangle.
        return PointInsideTriangle(triangle, vAux);
    }
    
    /// <summary>
    /// Checks if resident line segment intersects with the provided hexahedron.
    /// </summary>
    /// <param name="hexahedron">[IN] The hexahedron to be used for intersection calculation. If any of its vertices 
    /// coincide, the behavior is undefined.</param>
    /// <returns>
	/// A boolean value that indicates whether the segment and the hexahedron intersect or not.<br/>
    /// <br/>
    /// <b>True</b><br/>
    /// The segment and the hexahedron intersect, including the following cases:
    /// - The segment intersects with two faces of the hexahedron.
    /// - The segment intersects with a vertex of the hexahedron.
    /// - An endpoint is contained in a face of the hexahedron.
    /// - The entire segment is contained in a face of the hexahedron.
    /// - Only one endpoint is contained in the hexahedron.
    /// - Only one endpoint belongs to an edge of the hexahedron.
    /// - The segment is fully contained in the hexahedron.
    /// - The segment is contained in an edge of the hexahedron.
    /// - The segment intersects with an edge of the hexahedron, even if it does not intersect with any vertex.
    /// - One or both endpoints coincide with vertices of the hexahedron.
    /// 
    /// <b>False</b><br/>
    /// The line segment does not intersect with the hexahedron.
	/// </returns>
    bool Intersection(const QBaseHexahedron<VectorType> &hexahedron) const
    {
        // The length of the segment should be greater than zero
        QE_ASSERT(this->A != this->B);

        // Checks if there is an intersection with any face.
        if (QuadrilateralIntersection(*this, hexahedron.A, hexahedron.B, hexahedron.C, hexahedron.D) ||
            QuadrilateralIntersection(*this, hexahedron.E, hexahedron.F, hexahedron.G, hexahedron.H) ||
            QuadrilateralIntersection(*this, hexahedron.A, hexahedron.B, hexahedron.H, hexahedron.E) ||
            QuadrilateralIntersection(*this, hexahedron.B, hexahedron.C, hexahedron.G, hexahedron.H) ||
            QuadrilateralIntersection(*this, hexahedron.A, hexahedron.D, hexahedron.F, hexahedron.E) ||
            QuadrilateralIntersection(*this, hexahedron.C, hexahedron.D, hexahedron.F, hexahedron.G) ||
            (this->PointInsideHexahedron(hexahedron, this->A) && this->PointInsideHexahedron(hexahedron, this->B)) )
            return true;
        else
            return false;
    }

    /// <summary>
	/// This method receives a plane, and computes the point where the resident line segment intersects with it,
    /// if it exists.
	/// </summary>
    /// <remarks>
	/// If there's no intersection point or if there are infinite, the output
    /// parameter used for storing that point won't be modified.
	/// </remarks>
	/// <param name="plane">[IN] The plane whose intersection with resident line segment we want to check. If the plane is null,
    /// the behavior is undefined.</param>
	/// <param name="vIntersection">[OUT] The point where they intersect that is closest to A (segment).</param>
	/// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The endpoints belong to different sides of the space divided by the plane.
    /// - Only one endpoint belongs to the plane.
    ///
    /// <b>Infinite</b><br/>
    /// There are infinite intersections.<br/>
    /// - The segment is contained in the plane.
    /// </returns>
	EQIntersections IntersectionPoint(const QBasePlane &plane, VectorType &vIntersection) const
	{
        // The length of the segment should be greater than zero
        QE_ASSERT(this->A != this->B);

        // The plane shouldn't be null
        QE_ASSERT( SQFloat::IsNotZero(plane.a) || SQFloat::IsNotZero(plane.b) || SQFloat::IsNotZero(plane.c) );

        const float_q &DIST_A = plane.a * this->A.x + plane.b * this->A.y + plane.c * this->A.z + plane.d;
        const float_q &DIST_B = plane.a * this->B.x + plane.b * this->B.y + plane.c * this->B.z + plane.d;

        const bool &IS_ZERO_DIST_A = SQFloat::IsZero(DIST_A);
        const bool &IS_ZERO_DIST_B = SQFloat::IsZero(DIST_B);

        if (IS_ZERO_DIST_A && !IS_ZERO_DIST_B) // A point lies on plane
        {
            vIntersection = this->A;
            return EQIntersections::E_One;
        }
        else if (!IS_ZERO_DIST_A && IS_ZERO_DIST_B) // B point lies on plane
        {
            vIntersection = this->B;
            return EQIntersections::E_One;
        }
        else if (IS_ZERO_DIST_A && IS_ZERO_DIST_B) // All line segment lies on plane
            return EQIntersections::E_Infinite;
        else if ( SQFloat::IsLessThan(DIST_A * DIST_B, SQFloat::_0) ) // Line segment intersects plane in a point
        {
            // Being n the plane direction vector, v floating point parameter
            // Point which satisfies plane equation: P.n + d = 0              (1)
            // Point in segment: P: A + v (B - A)                             (2)
            // Therefore:
            // (A + v (B-A)).n + d = 0
            // Reordering:
            // A.n + d + v (B + d - A - d).n = 0; A.n + d = fDistA; B.n + d = fDistB, then
            // fDistA + v (fDistB - fDistA) = 0
            // v = - fDistA/(fDistB - fDistA) = fDistA/(fDistA - fDistB)
            // then we replace v in (2) and we get the intersection point

            const float_q &DENOM = DIST_A - DIST_B;

            QE_ASSERT(DENOM != SQFloat::_0)

            vIntersection = this->A + DIST_A * (this->B - this->A) / DENOM;

            return EQIntersections::E_One;
        }
        else // Line segment don't intersects plane
            return EQIntersections::E_None;
    }

    /// <summary>
	/// Computes the points where the line segment and a triangle intersect.
	/// </summary>
    /// <remarks>
	/// If there's no intersection point or if there are infinite, the output
    /// parameter used for storing that point won't be modified.<br/>
	/// </remarks>
	/// <param name="triangle">[IN] The triangle to be used for intersection calculation. If any of its vertices coincide,
    /// the behavior is undefined.</param>
	/// <param name="vIntersection">[OUT] A vector where to store the closest intersection point to endpoint A (segment).</param>
	/// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The line segment intersects with one edge of the triangle (not intersecting with any vertex).
    /// - The segment intersects with one vertex of the triangle.
    /// - Only one endpoint belongs to the triangle (not intersecting any edge or vertex).
    /// - Only one endpoint belongs to an edge of the triangle, even if the other endpoint is inside of the triangle.
    /// - An endpoint coincides with a vertex of the triangle.
    /// - The line segment intersects with the interior (the face) of the triangle (not intersecting with any edge or vertex).
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The line segment intersects with two edges of the triangle.
    /// - The line segment intersects with two vertices of the triangle.
    /// - The line segment belongs to an edge of the triangle.
    /// - The segment and an edge of the triangle coincide partially, so there is a vertex inside of the segment, and an endpoint inside of the edge.
    ///
    /// <b>Infinite</b><br/>
    /// There are infinite intersections.<br/>
    /// - The segment is contained in the triangle (endpoints are not tangent to any edge).
    /// </returns>
	EQIntersections IntersectionPoint(const QBaseTriangle<VectorType> &triangle, VectorType &vIntersection) const
    {
        // [TODO] Thund: This must be optimized
        // Calculates if segment intersects with the plane defined by the triangle.
		VectorType vAux;
		return this->IntersectionPoint(triangle, vIntersection, vAux);
    }

    /// <summary>
	/// Computes the points where the line segment and a triangle intersect.
	/// </summary>
    /// <remarks>
	/// If there are no intersection points or if there are infinite, the output
    /// parameters used for storing those points will not be modified.<br/>
	/// </remarks>
	/// <param name="triangle">[IN] The triangle whose intersection with resident line segment we want to check. If any of its vertices coincide,
    /// the behavior is undefined.</param>
	/// <param name="vIntersection1">[OUT] A vector where to store the closest intersection point to endpoint A (segment).</param>
    /// <param name="vIntersection2">[OUT] A vector where to store the furthest intersection point to endpoint A (segment).</param>
	/// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The line segment intersects with one edge of the triangle (not intersecting with any vertex).
    /// - The segment intersects with one vertex of the triangle.
    /// - Only one endpoint belongs to the triangle (not intersecting any edge or vertex).
    /// - Only one endpoint belongs to an edge of the triangle, even if the other endpoint is inside of the triangle.
    /// - An endpoint coincides with a vertex of the triangle.
    /// - The line segment intersects with the interior (the face) of the triangle (not intersecting with any edge or vertex).
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The line segment intersects with two edges of the triangle.
    /// - The line segment intersects with two vertices of the triangle.
    /// - The line segment belongs to an edge of the triangle.
    /// - The segment and an edge of the triangle coincide partially, so there is a vertex inside of the segment, and an endpoint inside of the edge.
    ///
    /// <b>Infinite</b><br/>
    /// There are infinite intersections.<br/>
    /// - The segment is contained in the triangle (endpoints are not tangent to any edge).
    /// </returns>
	EQIntersections IntersectionPoint(const QBaseTriangle<VectorType> &triangle, VectorType &vIntersection1, VectorType &vIntersection2) const
	{
        // The length of the segment should be greater than zero
        QE_ASSERT(this->A != this->B);

        // Vertices of the triangle should not coincide
        QE_ASSERT(triangle.A != triangle.B && triangle.B != triangle.C && triangle.C != triangle.A);

        // Plane equation
        QPlane auxP(triangle.A, triangle.B, triangle.C);

        VectorType vPoint;

        EQIntersections value = this->IntersectionPoint(auxP, vPoint);

        if (value == EQIntersections::E_None) // Line segment don't intersects the triangle plane.
            return EQIntersections::E_None;
        else if (value == EQIntersections::E_One) // Line segment has one intersection with the triangle plane.
        {
            if (PointInsideTriangle(triangle, vPoint))
            {
                vIntersection1 = vPoint;
                return EQIntersections::E_One;
            }
            else
                return EQIntersections::E_None;
        }
        else // Line segment and triangle are coplanars (value == EQIntersections::E_Infinite)
        {
            const bool &A_IS_INSIDE = PointInsideTriangle(triangle, this->A);
            const bool &B_IS_INSIDE = PointInsideTriangle(triangle, this->B);

            if (A_IS_INSIDE && B_IS_INSIDE) // Both line segment end points are inside triangle.
            {
				// A or B are vertex
				const bool &A_IS_VERTEX = (this->A == triangle.A || this->A == triangle.B || this->A == triangle.C);
				const bool &B_IS_VERTEX = (this->B == triangle.A || this->B == triangle.B || this->B == triangle.C);

				if (A_IS_VERTEX && B_IS_VERTEX) // Both endpoints are vertices of triangle
				{
					vIntersection1 = this->A;
					vIntersection2 = this->B;
					return EQIntersections::E_Two;
				}
				else if (A_IS_VERTEX) // Only A endpoint is a vertex of triangle
				{
					vIntersection1 = this->A;

					if (SQFloat::IsZero(QLineSegment<VectorType>(triangle.A, triangle.B).MinDistance(this->B))) // B is in AB triangle edge
					{
						if (this->A == triangle.A || this->A == triangle.B) // A and B are in the same edge
							return EQIntersections::E_One;
						else
						{
							vIntersection2 = this->B;
							return EQIntersections::E_Two;
						}
					}
					else if (SQFloat::IsZero(QLineSegment<VectorType>(triangle.B, triangle.C).MinDistance(this->B))) // B is in BC triangle edge
					{
						if (this->A == triangle.B || this->A == triangle.C) // A and B are in the same edge
							return EQIntersections::E_One;
						else
						{
							vIntersection2 = this->B;
							return EQIntersections::E_Two;
						}
					}
					else if (SQFloat::IsZero(QLineSegment<VectorType>(triangle.C, triangle.A).MinDistance(this->B))) // B is in CA triangle edge
					{
						if (this->A == triangle.C || this->A == triangle.A) // A and B are in the same edge
							return EQIntersections::E_One;
						else
						{
							vIntersection2 = this->B;
							return EQIntersections::E_Two;
						}
					}
					else // B is not in an edge
					{
						vIntersection1 = this->A;
						return EQIntersections::E_One;
					}
				}
				else if (B_IS_VERTEX)
				{
					if (SQFloat::IsZero(QLineSegment<VectorType>(triangle.A, triangle.B).MinDistance(this->A))) // A is in AB triangle edge
					{
						if (this->B == triangle.A || this->B == triangle.B) // A and B are in the same edge
						{
							vIntersection1 = this->B;
							return EQIntersections::E_One;
						}
						else
						{
							vIntersection1 = this->A;
							vIntersection2 = this->B;
							return EQIntersections::E_Two;
						}
					}
					else if (SQFloat::IsZero(QLineSegment<VectorType>(triangle.B, triangle.C).MinDistance(this->A))) // B is in BC triangle edge
					{
						if (this->B == triangle.B || this->B == triangle.C) // A and B are in the same edge
						{
							vIntersection1 = this->B;
							return EQIntersections::E_One;
						}
						else
						{
							vIntersection1 = this->A;
							vIntersection2 = this->B;
							return EQIntersections::E_Two;
						}
					}
					else if (SQFloat::IsZero(QLineSegment<VectorType>(triangle.C, triangle.A).MinDistance(this->A))) // B is in CA triangle edge
					{
						if (this->B == triangle.C || this->B == triangle.A) // A and B are in the same edge
						{
							vIntersection1 = this->B;
							return EQIntersections::E_One;
						}
						else
						{
							vIntersection1 = this->A;
							vIntersection2 = this->B;
							return EQIntersections::E_Two;
						}
					}
					else
					{
						vIntersection1 = this->B;
						return EQIntersections::E_One;
					}
				}
				else // Neither A or B are vertices of triangle
				{
					if (SQFloat::IsZero(QLineSegment<VectorType>(triangle.A, triangle.B).MinDistance(this->A))) // A is in AB triangle edge (but not a vertex)
					{
                        vIntersection1 = this->A;

						if (SQFloat::IsZero(QLineSegment<VectorType>(triangle.A, triangle.B).MinDistance(this->B)) || // B is in AB triangle edge (but not a vertex)
						    SQFloat::IsZero(QLineSegment<VectorType>(triangle.B, triangle.C).MinDistance(this->B)) || // B is in other edge (but not a vertex)
							SQFloat::IsZero(QLineSegment<VectorType>(triangle.C, triangle.A).MinDistance(this->B)) )
						{
							vIntersection2 = this->B;
							return EQIntersections::E_Two;
						}
						else // B is not in an edge
						{
							return EQIntersections::E_One;
						}
					}
					else if (SQFloat::IsZero(QLineSegment<VectorType>(triangle.B, triangle.C).MinDistance(this->A))) // A is in BC triangle edge (but not a vertex)
					{
                        vIntersection1 = this->A;

						if (SQFloat::IsZero(QLineSegment<VectorType>(triangle.B, triangle.C).MinDistance(this->B)) || // B is in BC triangle edge (but not a vertex)
						    SQFloat::IsZero(QLineSegment<VectorType>(triangle.A, triangle.B).MinDistance(this->B)) || // B is in other edge (but not a vertex)
							SQFloat::IsZero(QLineSegment<VectorType>(triangle.C, triangle.A).MinDistance(this->B)) )
						{
							vIntersection2 = this->B;
							return EQIntersections::E_Two;
						}
						else // B is not in an edge
						{
							return EQIntersections::E_One;
						}
					}
					else if (SQFloat::IsZero(QLineSegment<VectorType>(triangle.C, triangle.A).MinDistance(this->A))) // A is in CA triangle edge (but not a vertex)
					{
                        vIntersection1 = this->A;

						if (SQFloat::IsZero(QLineSegment<VectorType>(triangle.C, triangle.A).MinDistance(this->B)) || // B is in CA triangle edge (but not a vertex)
						    SQFloat::IsZero(QLineSegment<VectorType>(triangle.A, triangle.B).MinDistance(this->B)) || // B is in other edge (but not a vertex)
							SQFloat::IsZero(QLineSegment<VectorType>(triangle.B, triangle.C).MinDistance(this->B)) )
						{
							vIntersection2 = this->B;
							return EQIntersections::E_Two;
						}
						else // B is not in an edge
						{
							return EQIntersections::E_One;
						}
					}
					else // A is not in an edge
					{
						if ( SQFloat::IsZero(QLineSegment<VectorType>(triangle.A, triangle.B).MinDistance(this->B)) || // B is in an edge (but not a vertex)
							 SQFloat::IsZero(QLineSegment<VectorType>(triangle.B, triangle.C).MinDistance(this->B)) ||
							 SQFloat::IsZero(QLineSegment<VectorType>(triangle.C, triangle.A).MinDistance(this->B)) )
						{
                            // B belongs to an edge
							vIntersection1 = this->B;
							return EQIntersections::E_One;
						}
						else // A and B don't belong to any edge and are inside the triangle
							return EQIntersections::E_Infinite;
					}
				}
			}
            else if (!A_IS_INSIDE && !B_IS_INSIDE) // Both line segment end points are outside triangle.
            {
                VectorType vPointAB1, vPointBC1, vPointCA1;
                VectorType vPointAB2, vPointBC2, vPointCA2;

                EQIntersections value2AB = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.A, triangle.B), vPointAB1, vPointAB2);

                if (value2AB == EQIntersections::E_Two) // Line segment contains AB edge of triangle
                {
                    vIntersection1 = vPointAB1;
                    vIntersection2 = vPointAB2;
                    return EQIntersections::E_Two;
                }
                else if(value2AB == EQIntersections::E_Infinite)
                {
                    vIntersection1 = this->A;
                    vIntersection2 = this->B;
                    return EQIntersections::E_Two;
                }

                // Line segment contains BC edge of triangle
                EQIntersections value2BC = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.B, triangle.C), vPointBC1, vPointBC2);
                if (value2BC == EQIntersections::E_Two)
                {
                    vIntersection1 = vPointBC1;
                    vIntersection2 = vPointBC2;
                    return EQIntersections::E_Two;
                }
                else if(value2BC == EQIntersections::E_Infinite)
                {
                    vIntersection1 = this->A;
                    vIntersection2 = this->B;
                    return EQIntersections::E_Two;
                }

                // Line segment contains CA edge of triangle
                EQIntersections value2CA = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.C, triangle.A), vPointCA1, vPointCA2);
                if (value2CA == EQIntersections::E_Two)
                {
                    vIntersection1 = vPointCA1;
                    vIntersection2 = vPointCA2;
                    return EQIntersections::E_Two;
                }
                else if(value2CA == EQIntersections::E_Infinite)
                {
                    vIntersection1 = this->A;
                    vIntersection2 = this->B;
                    return EQIntersections::E_Two;
                }

                if (value2AB == EQIntersections::E_One) // Line segment intersects AB edge of triangle
                {
                    if (value2BC == EQIntersections::E_One) // Line segment intersects BC edge of triangle
                    {
                        if (vPointAB1 == vPointBC1) // Are the same point
                        {
							if (value2CA == EQIntersections::E_One) // Line segment intersects CA edge of triangle
							{
								if  ( (vPointAB1 - this->A).GetSquaredLength() < (vPointCA1 - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
								{
									vIntersection1 = vPointAB1;
									vIntersection2 = vPointCA1;
								}
								else
								{
									vIntersection1 = vPointCA1;
									vIntersection2 = vPointAB1;
								}
								return EQIntersections::E_Two;
							}
							else
							{
								vIntersection1 = vPointAB1;
								return EQIntersections::E_One;
							}
                        }
                        else
                        {
                            if  ( (vPointAB1 - this->A).GetSquaredLength() < (vPointBC1 - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                            {
                                vIntersection1 = vPointAB1;
                                vIntersection2 = vPointBC1;
                            }
                            else
                            {
                                vIntersection1 = vPointBC1;
                                vIntersection2 = vPointAB1;
                            }

                            return EQIntersections::E_Two;
                        }
                    }
                    else if (value2CA == EQIntersections::E_One) // Line segment intersects CA edge of triangle
                    {
                        if (vPointAB1 == vPointCA1) // Are the same point
                        {
                            vIntersection1 = vPointAB1;
                            return EQIntersections::E_One;
                        }
                        else
                        {
                            if  ( (vPointAB1 - this->A).GetSquaredLength() < (vPointCA1 - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                            {
                                vIntersection1 = vPointAB1;
                                vIntersection2 = vPointCA1;
                            }
                            else
                            {
                                vIntersection1 = vPointCA1;
                                vIntersection2 = vPointAB1;
                            }

                            return EQIntersections::E_Two;
                        }
                    }
                }
                else if (value2BC == EQIntersections::E_One) // Line segment intersects BC edge of triangle
                {
                    if (value2CA == EQIntersections::E_One) // Line segment intersects CA edge of triangle
                    {
                        if (vPointBC1 == vPointCA1) // Are the same point
                        {
                            vIntersection1 = vPointBC1;
                            return EQIntersections::E_One;
                        }
                        else
                        {
                            if  ( (vPointBC1 - this->A).GetSquaredLength() < (vPointCA1 - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                            {
                                vIntersection1 = vPointBC1;
                                vIntersection2 = vPointCA1;
                            }
                            else
                            {
                                vIntersection1 = vPointCA1;
                                vIntersection2 = vPointBC1;
                            }

                            return EQIntersections::E_Two;
                        }
                    }
                }

                // Line segment don't intersects triangle
                if (value2AB == EQIntersections::E_None && value2BC == EQIntersections::E_None && value2CA == EQIntersections::E_None)
                    return EQIntersections::E_None;
            }
            else // one line segment end point is inside and the other one is outside triangle.
            {
                VectorType vAux; // To store intersection points

				if (A_IS_INSIDE) // this->A is inside triangle
				{
					if (this->A == triangle.A) // this->A is A triangle vertex
					{
						vIntersection1 = this->A;

						EQIntersections value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.B, triangle.C), vAux);
						if (value2 == EQIntersections::E_One) // ls intersects opposite edge
						{
							vIntersection2 = vAux;
							return EQIntersections::E_Two;
						}
						else
							return EQIntersections::E_One; // ls only intersects triangle in A vertex
					}
					else if (this->A == triangle.B) // this->A is B triangle vertex
					{
						vIntersection1 = this->A;

						EQIntersections value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.C, triangle.A), vAux);
						if (value2 == EQIntersections::E_One) // ls intersects opposite edge
						{
							vIntersection2 = vAux;
							return EQIntersections::E_Two;
						}
						else
							return EQIntersections::E_One; // ls only intersects triangle in B vertex
					}
					else if (this->A == triangle.C) // this->A is C triangle vertex
					{
						vIntersection1 = this->A;

						EQIntersections value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.B, triangle.A), vAux);
						if (value2 == EQIntersections::E_One) // ls intersects opposite edge
						{
							vIntersection2 = vAux;
							return EQIntersections::E_Two;
						}
						else
							return EQIntersections::E_One;  // ls only intersects triangle in C vertex
					}
					else if (SQFloat::IsZero(QLineSegment<VectorType>(triangle.A, triangle.B).MinDistance(this->A))) // this->A is in AB triangle edge (but not a vertex)
					{
						vIntersection1 = this->A;

						// ls intersects other edges
						EQIntersections value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.B, triangle.C), vAux);
						if (value2 == EQIntersections::E_One)
						{
							if (vAux == triangle.B || vAux == triangle.C) // Both intersections are in the same edge
								return EQIntersections::E_One;

							vIntersection2 = vAux;
							return EQIntersections::E_Two;
						}
						else if ((value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.C, triangle.A), vAux)) == EQIntersections::E_One)
						{
							if (vAux == triangle.C || vAux == triangle.A) // Both intersections are in the same edge
								return EQIntersections::E_One;

							vIntersection2 = vAux;
							return EQIntersections::E_Two;
						}
						else
							return EQIntersections::E_One;
					}
					else if (SQFloat::IsZero(QLineSegment<VectorType>(triangle.B, triangle.C).MinDistance(this->A))) // this->A is in BC triangle edge (but not a vertex)
					{
						vIntersection1 = this->A;

						 // ls intersects other edges
						EQIntersections value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.A, triangle.B), vAux);
						if (value2 == EQIntersections::E_One)
						{
							if (vAux == triangle.A || vAux == triangle.B) // Both intersections are in the same edge
								return EQIntersections::E_One;

							vIntersection2 = vAux;
							return EQIntersections::E_Two;
						}
						else if ((value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.C, triangle.A), vAux)) == EQIntersections::E_One)
						{
							if (vAux == triangle.C || vAux == triangle.A) // Both intersections are in the same edge
								return EQIntersections::E_One;

							vIntersection2 = vAux;
							return EQIntersections::E_Two;
						}
						else
							return EQIntersections::E_One;
					}
					else if (SQFloat::IsZero(QLineSegment<VectorType>(triangle.C, triangle.A).MinDistance(this->A))) // this->A is in CA triangle edge (but not a vertex)
					{
						vIntersection1 = this->A;

						 // ls intersects other edges
						EQIntersections value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.B, triangle.C), vAux);
						if (value2 == EQIntersections::E_One)
						{
							if (vAux == triangle.B || vAux == triangle.C) // Both intersections are in the same edge
								return EQIntersections::E_One;

							vIntersection2 = vAux;
							return EQIntersections::E_Two;
						}
						else if ((value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.A, triangle.B), vAux)) == EQIntersections::E_One)
						{
							if (vAux == triangle.A || vAux == triangle.B) // Both intersections are in the same edge
								return EQIntersections::E_One;

							vIntersection2 = vAux;
							return EQIntersections::E_Two;
						}
						else
							return EQIntersections::E_One;
					}
					else // this->A is strictly inside triangle: it is not in a vertex or edge
					{
						EQIntersections value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.A, triangle.B), vAux);
						if (value2 == EQIntersections::E_One)
							vIntersection1 = vAux;
						else if ((value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.B, triangle.C), vAux)) == EQIntersections::E_One)
							vIntersection1 = vAux;
						else if ((value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.C, triangle.A), vAux)) == EQIntersections::E_One)
							vIntersection1 = vAux;

						return EQIntersections::E_One;
					}
				}
				else // this->B is inside triangle (A is outside)
				{
					if (this->B == triangle.A) // this->B is triangle.A vertex
					{

						EQIntersections value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.B, triangle.C), vAux);
						if (value2 == EQIntersections::E_One) // ls intersects opposite edge
						{
							vIntersection1 = vAux;
							vIntersection2 = this->B;
							return EQIntersections::E_Two;
						}
						else // ls only intersects in A vertex
						{
							vIntersection1 = this->B;
							return EQIntersections::E_One;
						}
					}
					else if (this->B == triangle.B) // this->B is triangle.B vertex
					{
						EQIntersections value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.C, triangle.A), vAux);
						if (value2 == EQIntersections::E_One) // ls intersects opposite edge
						{
							vIntersection1 = vAux;
							vIntersection2 = this->B;
							return EQIntersections::E_Two;
						}
						else // ls only intersects in B vertex
						{
							vIntersection1 = this->B;
							return EQIntersections::E_One;
						}
					}
					else if (this->B == triangle.C) // this->B is triangle.C vertex
					{
						EQIntersections value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.A, triangle.B), vAux);
						if (value2 == EQIntersections::E_One) // ls intersects opposite edge
						{
							vIntersection1 = vAux;
							vIntersection2 = this->B;
							return EQIntersections::E_Two;
						}
						else // ls only intersects in C vertex
						{
							vIntersection1 = this->B;
							return EQIntersections::E_One;
						}
					}
					else if (SQFloat::IsZero(QLineSegment<VectorType>(triangle.A, triangle.B).MinDistance(this->B))) // this->B is in AB triangle edge (but not a vertex)
					{
						// ls intersects the other edges
						EQIntersections value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.B, triangle.C), vAux);
						if (value2 == EQIntersections::E_One)
						{
							vIntersection1 = vAux;

							if (vAux == triangle.B || vAux == triangle.C) // Both intersections are in the same edge
								return EQIntersections::E_One;

							vIntersection2 = this->B;
							return EQIntersections::E_Two;
						}
						else if ((value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.C, triangle.A), vAux)) == EQIntersections::E_One)
						{
							vIntersection1 = vAux;

							if (vAux == triangle.C || vAux == triangle.A) // Both intersections are in the same edge
								return EQIntersections::E_One;

							vIntersection2 = this->B;
							return EQIntersections::E_Two;
						}
						else // There is no other intersection
						{
							vIntersection1 = this->B;
							return EQIntersections::E_One;
						}
					}
					else if (SQFloat::IsZero(QLineSegment<VectorType>(triangle.B, triangle.C).MinDistance(this->B))) // this->B is in BC triangle edge (but not a vertex)
					{
						// ls intersects the other edges
						EQIntersections value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.A, triangle.B), vAux);
						if (value2 == EQIntersections::E_One)
						{
							vIntersection1 = vAux;

							if (vAux == triangle.A || vAux == triangle.B) // Both intersections are in the same edge
								return EQIntersections::E_One;

							vIntersection2 = this->B;
							return EQIntersections::E_Two;
						}
						else if ((value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.C, triangle.A), vAux)) == EQIntersections::E_One)
						{
							vIntersection1 = vAux;
							vIntersection2 = this->B;
							return EQIntersections::E_Two;
						}
						else // There is no other intersection
						{
							vIntersection1 = this->B;
							return EQIntersections::E_One;
						}
					}
					else if (SQFloat::IsZero(QLineSegment<VectorType>(triangle.C, triangle.A).MinDistance(this->B))) // this->B is in CA triangle edge (but not a vertex)
					{
						// ls intersects the other edges
						EQIntersections value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.B, triangle.C), vAux);
						if (value2 == EQIntersections::E_One)
						{
							vIntersection1 = vAux;

							if (vAux == triangle.B || vAux == triangle.C) // Both intersections are in the same edge
								return EQIntersections::E_One;

							vIntersection2 = this->B;
							return EQIntersections::E_Two;
						}
						else if ((value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.A, triangle.B), vAux)) == EQIntersections::E_One)
						{
							vIntersection1 = vAux;

							if (vAux == triangle.A || vAux == triangle.B) // Both intersections are in the same edge
								return EQIntersections::E_One;

							vIntersection2 = this->B;
							return EQIntersections::E_Two;
						}
						else // There is no other intersection
						{
							vIntersection1 = this->B;
							return EQIntersections::E_One;
						}
					}
					else // this->B is strictly inside triangle: is not in a vertex or edge.
					{
						EQIntersections value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.A, triangle.B), vAux);
						if (value2 == EQIntersections::E_One)
							vIntersection1 = vAux;
						else if ((value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.B, triangle.C), vAux)) == EQIntersections::E_One)
							vIntersection1 = vAux;
						else if ((value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.C, triangle.A), vAux)) == EQIntersections::E_One)
							vIntersection1 = vAux;

						return EQIntersections::E_One;
					}
				}
            }
        }

        // Something was wrong, this line should be never reached
		QE_ASSERT(false)

        return EQIntersections::E_None;
    }
    
    /// <summary>
	/// Computes the points where the line segment and a hexahedron intersect.
	/// </summary>
    /// <remarks>
	/// If there's no intersection point of if there are infinite, the output parameter used for storing that point won't be modified.
	/// </remarks>
	/// <param name="hexahedron">[IN] The hexahedron whose intersections with the line segment are to be checked. If any of its vertices coincide,
    /// the behavior is undefined.</param>
    /// <param name="vIntersection">[OUT] A vector where to store the closest intersection point to endpoint A (segment).</param>
	/// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The line segment intersects with a vertex of the hexahedron.
    /// - Only one endpoint is contained in a face of the hexahedron, even if the other endpoint is inside of the hexahedron.
    /// - Only one endpoint is contained in the hexahedron.
    /// - Only one endpoint is contained in an edge of the hexahedron.
    /// - The line segment intersects with an edge of the hexahedron, being both endpoints outside.
    /// - An endpoint coincide with a vertex of the hexahedron.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The segment intersects with two faces of the hexahedron.
    /// - Both endpoints belong to two different faces of the hexahedron.
    /// - Both endpoints belong to the same edge of the hexahedron.
    /// - An endpoint is contained in a face and the other is contained in an edge of the hexahedron.
    ///
    /// <b>Infinite</b><br/>
    /// There are infinite intersections.<br/>
    /// - The segment is contained in the hexahedron (endpoints are not tangent to any face).
    /// </returns>
	EQIntersections IntersectionPoint(const QBaseHexahedron<VectorType> &hexahedron, VectorType &vIntersection) const
	{
        // The length of the segment should be greater than zero
        QE_ASSERT(this->A != this->B);

        VectorType vAuxPoint, vAux;
        bool bPreviousInt = false;

        // Check if resident line segment intersects ABCD face
        EQIntersections value1 = QuadrilateralIntersectionPoint(*this, hexahedron.A, hexahedron.B, hexahedron.C, hexahedron.D, vAux);

        if ( value1 == EQIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection = vAux;
            return EQIntersections::E_Two;
        }
        else if (value1 == EQIntersections::E_One) // There is only one intersection
        {
            vAuxPoint = vAux;
            bPreviousInt = true;
        }
        else if (value1 == EQIntersections::E_Infinite) // Line segment lies in this face (without intersections with any edge or vertex)
        {
            vIntersection = this->A;
            return EQIntersections::E_Two;
        }

        // Check if resident line segment intersects EFGH face
        EQIntersections value2 = QuadrilateralIntersectionPoint(*this, hexahedron.E, hexahedron.F, hexahedron.G, hexahedron.H, vAux);

        if ( value2 == EQIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection = vAux;
            return EQIntersections::E_Two;
        }
        else if (value2 == EQIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                    vIntersection = vAuxPoint;
                else
                    vIntersection = vAux;
                return EQIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux;
                bPreviousInt = true;
            }
        }
        else if (value2 == EQIntersections::E_Infinite) // Line segment lies in this face (without intersections with any edge or vertex)
        {
            vIntersection = this->A;
            return EQIntersections::E_Two;
        }

        // Check if resident line segment intersects ABHE face
        EQIntersections value3 = QuadrilateralIntersectionPoint(*this, hexahedron.A, hexahedron.B, hexahedron.H, hexahedron.E, vAux);

        if (value3 == EQIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection = vAux;
            return EQIntersections::E_Two;
        }
        else if (value3 == EQIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                    vIntersection = vAuxPoint;
                else
                    vIntersection = vAux;
                return EQIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux;
                bPreviousInt = true;
            }
        }
        else if (value3 == EQIntersections::E_Infinite) // Line segment lies in this face (without intersections with any edge or vertex)
        {
            vIntersection = this->A;
            return EQIntersections::E_Two;
        }

        // Check if resident line segment intersects BCGH face
        EQIntersections value4 = QuadrilateralIntersectionPoint(*this, hexahedron.B, hexahedron.C, hexahedron.G, hexahedron.H, vAux);

        if ( value4 == EQIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection = vAux;
            return EQIntersections::E_Two;
        }
        else if (value4 == EQIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                    vIntersection = vAuxPoint;
                else
                    vIntersection = vAux;
                return EQIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux;
                bPreviousInt = true;
            }
        }
        else if (value4 == EQIntersections::E_Infinite) // Line segment lies in this face (without intersections with any edge or vertex)
        {
            vIntersection = this->A;
            return EQIntersections::E_Two;
        }

        // Check if resident line segment intersects ADFE face
        EQIntersections value5 = QuadrilateralIntersectionPoint(*this, hexahedron.A, hexahedron.D, hexahedron.F, hexahedron.E, vAux);

        if ( value5 == EQIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection = vAux;
            return EQIntersections::E_Two;
        }
        else if (value5 == EQIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                    vIntersection = vAuxPoint;
                else
                    vIntersection = vAux;
                return EQIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux;
                bPreviousInt = true;
            }
        }
        else if (value5 == EQIntersections::E_Infinite) // Line segment lies in this face (without intersections with any edge or vertex)
        {
            vIntersection = this->A;
            return EQIntersections::E_Two;
        }

        // Check if resident line segment intersects CDFG face
        EQIntersections value6 = QuadrilateralIntersectionPoint(*this, hexahedron.C, hexahedron.D, hexahedron.F, hexahedron.G, vAux);

        if ( value6 == EQIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection = vAux;
            return EQIntersections::E_Two;
        }
        else if (value6 == EQIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                    vIntersection = vAuxPoint;
                else
                    vIntersection = vAux;
                return EQIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux;
                bPreviousInt = true;
            }
        }
        else if (value6 == EQIntersections::E_Infinite) // Line segment lies in this face (without intersections with any edge or vertex)
        {
            vIntersection = this->A;
            return EQIntersections::E_Two;
        }

        if (bPreviousInt) // There is only one intersection with hexahedron
        {
            vIntersection = vAuxPoint;
            return EQIntersections::E_One;
        }
        else // There are no intersections with hexahedron
        {
            const bool &A_IS_INSIDE = PointInsideHexahedron(hexahedron, this->A);
            const bool &B_IS_INSIDE = PointInsideHexahedron(hexahedron, this->B);

            if (A_IS_INSIDE && B_IS_INSIDE) // Both line segment end points are inside hexahedron
                return EQIntersections::E_Infinite;
            else if (!A_IS_INSIDE && !B_IS_INSIDE) // Both line segment end points are outside hexahedron
                return EQIntersections::E_None;
        }

        // Something was wrong, this line should be never reached
		QE_ASSERT(false)

        return EQIntersections::E_None;
    }

    /// <summary>
	/// Computes the points where the line segment and a hexahedron intersect.
	/// </summary>
    /// <remarks>
	/// If there's no intersection point or there are infinite, the output parameters used for storing the intersection points won't be modified.
	/// </remarks>
	/// <param name="hexahedron">[IN] The hexahedron whose intersections with resident line segment we want to check. If any of its vertices coincide,
    /// the behavior is undefined.</param>
    /// <param name="vIntersection1">[OUT] A vector where to store the closest intersection point to endpoint A (segment).</param>
    /// <param name="vIntersection2">[OUT] A vector where to store the furthest intersection point to endpoint A (segment).</param>
	/// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The line segment intersects with a vertex of the hexahedron.
    /// - Only one endpoint is contained in a face of the hexahedron, even if the other endpoint is inside of the hexahedron.
    /// - Only one endpoint is contained in the hexahedron.
    /// - Only one endpoint is contained in an edge of the hexahedron.
    /// - The line segment intersects with an edge of the hexahedron, being both endpoints outside.
    /// - An endpoint coincide with a vertex of the hexahedron.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The segment intersects with two faces of the hexahedron.
    /// - Both endpoints belong to two different faces of the hexahedron.
    /// - Both endpoints belong to the same edge of the hexahedron.
    /// - An endpoint is contained in a face and the other is contained in an edge of the hexahedron.
    ///
    /// <b>Infinite</b><br/>
    /// There are infinite intersections.<br/>
    /// - The segment is contained in the hexahedron (endpoints are not tangent to any face).
    /// </returns>
	EQIntersections IntersectionPoint(const QBaseHexahedron<VectorType> &hexahedron, VectorType &vIntersection1, VectorType &vIntersection2) const
	{
        // The length of the segment should be greater than zero
        QE_ASSERT(this->A != this->B);

        VectorType vAuxPoint, vAux1, vAux2;
        bool bPreviousInt = false;

        // Check if resident line segment intersects ABCD face
        EQIntersections value1 = QuadrilateralIntersectionPoint(*this, hexahedron.A, hexahedron.B, hexahedron.C, hexahedron.D, vAux1, vAux2);

        if ( value1 == EQIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection1 = vAux1;
            vIntersection2 = vAux2;
            return EQIntersections::E_Two;
        }
        else if (value1 == EQIntersections::E_One) // There is only one intersection
        {
            vAuxPoint = vAux1;
            bPreviousInt = true;
        }
        else if (value1 == EQIntersections::E_Infinite) // Line segment lies in this face (without intersections with any edge or vertex)
        {
            vIntersection1 = this->A;
            vIntersection2 = this->B;
            return EQIntersections::E_Two;
        }

        // Check if resident line segment intersects EFGH face
        EQIntersections value2 = QuadrilateralIntersectionPoint(*this, hexahedron.E, hexahedron.F, hexahedron.G, hexahedron.H, vAux1, vAux2);

        if ( value2 == EQIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection1 = vAux1;
            vIntersection2 = vAux2;
            return EQIntersections::E_Two;
        }
        else if (value2 == EQIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux1)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux1 - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                {
                    vIntersection1 = vAuxPoint;
                    vIntersection2 = vAux1;
                }
                else
                {
                    vIntersection1 = vAux1;
                    vIntersection2 = vAuxPoint;
                }
                return EQIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux1;
                bPreviousInt = true;
            }
        }
        else if (value2 == EQIntersections::E_Infinite) // Line segment lies in this face (without intersections with any edge or vertex)
        {
            vIntersection1 = this->A;
            vIntersection2 = this->B;
            return EQIntersections::E_Two;
        }

        // Check if resident line segment intersects ABHE face
        EQIntersections value3 = QuadrilateralIntersectionPoint(*this, hexahedron.A, hexahedron.B, hexahedron.H, hexahedron.E, vAux1, vAux2);

        if ( value3 == EQIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection1 = vAux1;
            vIntersection2 = vAux2;
            return EQIntersections::E_Two;
        }
        else if (value3 == EQIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux1)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux1 - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                {
                    vIntersection1 = vAuxPoint;
                    vIntersection2 = vAux1;
                }
                else
                {
                    vIntersection1 = vAux1;
                    vIntersection2 = vAuxPoint;
                }
                return EQIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux1;
                bPreviousInt = true;
            }
        }
        else if (value3 == EQIntersections::E_Infinite) // Line segment lies in this face (without intersections with any edge or vertex)
        {
            vIntersection1 = this->A;
            vIntersection2 = this->B;
            return EQIntersections::E_Two;
        }

        // Check if resident line segment intersects BCGH face
        EQIntersections value4 = QuadrilateralIntersectionPoint(*this, hexahedron.B, hexahedron.C, hexahedron.G, hexahedron.H, vAux1,vAux2);

        if ( value4 == EQIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection1 = vAux1;
            vIntersection2 = vAux2;
            return EQIntersections::E_Two;
        }
        else if (value4 == EQIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux1)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux1 - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                {
                    vIntersection1 = vAuxPoint;
                    vIntersection2 = vAux1;
                }
                else
                {
                    vIntersection1 = vAux1;
                    vIntersection2 = vAuxPoint;
                }
                return EQIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux1;
                bPreviousInt = true;
            }
        }
        else if (value4 == EQIntersections::E_Infinite) // Line segment lies in this face (without intersections with any edge or vertex)
        {
            vIntersection1 = this->A;
            vIntersection2 = this->B;
            return EQIntersections::E_Two;
        }

        // Check if resident line segment intersects ADFE face
        EQIntersections value5 = QuadrilateralIntersectionPoint(*this, hexahedron.A, hexahedron.D, hexahedron.F, hexahedron.E, vAux1, vAux2);

        if ( value5 == EQIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection1 = vAux1;
            vIntersection2 = vAux2;
            return EQIntersections::E_Two;
        }
        else if (value5 == EQIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux1)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux1 - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                {
                    vIntersection1 = vAuxPoint;
                    vIntersection2 = vAux1;
                }
                else
                {
                    vIntersection1 = vAux1;
                    vIntersection2 = vAuxPoint;
                }
                return EQIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux1;
                bPreviousInt = true;
            }
        }
        else if (value5 == EQIntersections::E_Infinite) // Line segment lies in this face (without intersections with any edge or vertex)
        {
            vIntersection1 = this->A;
            vIntersection2 = this->B;
            return EQIntersections::E_Two;
        }

        // Check if resident line segment intersects CDFG face
        EQIntersections value6 = QuadrilateralIntersectionPoint(*this, hexahedron.C, hexahedron.D, hexahedron.F, hexahedron.G, vAux1, vAux2);

        if ( value6 == EQIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection1 = vAux1;
            vIntersection2 = vAux2;
            return EQIntersections::E_Two;
        }
        else if (value6 == EQIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux1)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux1 - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                {
                    vIntersection1 = vAuxPoint;
                    vIntersection2 = vAux1;
                }
                else
                {
                    vIntersection1 = vAux1;
                    vIntersection2 = vAuxPoint;
                }
                return EQIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux1;
                bPreviousInt = true;
            }
        }
        else if (value6 == EQIntersections::E_Infinite) // Line segment lies in this face (without intersections with any edge or vertex)
        {
            vIntersection1 = this->A;
            vIntersection2 = this->B;
            return EQIntersections::E_Two;
        }

        if (bPreviousInt) // There is only one intersection with hexahedron
        {
            vIntersection1 = vAuxPoint;
            return EQIntersections::E_One;
        }
        else // There are no intersections with hexahedron
        {
            const bool &A_IS_INSIDE = PointInsideHexahedron(hexahedron, this->A);
            const bool &B_IS_INSIDE = PointInsideHexahedron(hexahedron, this->B);

            if (A_IS_INSIDE && B_IS_INSIDE) // Both line segment end points are inside hexahedron
                return EQIntersections::E_Infinite;
            else if (!A_IS_INSIDE && !B_IS_INSIDE) // Both line segment end points are outside hexahedron
                return EQIntersections::E_None;
        }

        // Something was wrong, this line should be never reached
		QE_ASSERT(false)

        return EQIntersections::E_None;
    }

    /// <summary>
    /// Calculates the maximum distance between the resident line segment and a plane provided.
    /// </summary>
    /// <remarks>
    /// The plane must be normalized to obtain correct result.
    /// </remarks>
    /// <param name="plane">[IN] The plane we want to know the maximum distance from the line segment. If it is null, the result
    /// is undefined.</param>
    /// <returns>
    /// A floating point value containing the maximum distance between the resident line segment and a plane provided.
    /// </returns>
    float_q MaxDistance(const QPlane &plane) const
    {
        QE_ASSERT( SQFloat::IsNotZero(plane.a) || SQFloat::IsNotZero(plane.b) || SQFloat::IsNotZero(plane.c) );

        const float_q &DIST_A = plane.PointDistance(this->A);
        const float_q &DIST_B = plane.PointDistance(this->B);

        return std::max(DIST_A, DIST_B);
    }

    /// <summary>
    /// Calculates the minimum distance between the resident line segment and a plane provided.
    /// </summary>
    /// <remarks>
    /// The plane must be normalized to obtain correct result.
    /// </remarks>
    /// <param name="plane">[IN] The plane we want to know the minimum distance from the line segment. If it is null, the result
    /// is undefined.</param>
    /// <returns>
    /// A floating point value containing the minimum distance between the resident line segment and a plane provided.
    /// </returns>
    float_q MinDistance(const QPlane &plane) const
    {
        QE_ASSERT( SQFloat::IsNotZero(plane.a) || SQFloat::IsNotZero(plane.b) || SQFloat::IsNotZero(plane.c) );

        // [TODO] Thund: This has to be optimized, maybe with an additional constructor in QVector4
        const float_q PLANE_POINT_COMPONENTS[] = {plane.a * -plane.d, plane.b * -plane.d, plane.c * -plane.d, SQFloat::_0};
        const VectorType PLANE_POINT = VectorType(PLANE_POINT_COMPONENTS);

        // If the line and the plane don't intersect...
        if(SQFloat::IsGreaterOrEquals(PLANE_POINT.DotProduct(this->A), SQFloat::_0) == SQFloat::IsGreaterOrEquals(PLANE_POINT.DotProduct(this->B), SQFloat::_0) ||
           SQFloat::IsNegative(PLANE_POINT.DotProduct(this->A)) == SQFloat::IsNegative(PLANE_POINT.DotProduct(this->B)))
        {
            const float_q &DIST_A = plane.PointDistance(this->A);
            const float_q &DIST_B = plane.PointDistance(this->B);
            return std::min(DIST_A, DIST_B);
        }

        return SQFloat::_0;
    }

    /// <summary>
    /// Projects the resident line segment over the plane provided.
    /// </summary>
    /// <remarks>
    /// The plane must be normalized to obtain correct result.
    /// </remarks>
    /// <param name="plane">[IN] The plane where we want to project the resident line segment. If it is null, the result
    /// is undefined.</param>
    /// <returns>
	/// The projected segment.
	/// </returns>
    QLineSegment3D<VectorType> ProjectToPlane(const QPlane &plane) const
    {
        // The plane must not be null
        QE_ASSERT( SQFloat::IsNotZero(plane.a) || SQFloat::IsNotZero(plane.b) || SQFloat::IsNotZero(plane.c) );

        return QLineSegment3D<VectorType>(plane.PointProjection(this->A),
                                          plane.PointProjection(this->B));
    }

    /// <summary>
    /// Checks the relation between resident line segment and the provided plane.
    /// </summary>
    /// <remarks>
    /// Since a plane divides space into two parts, we can check if the "distances" (allowing distances having sign) from
    /// the plane to both end points of line segment are 0, or have diferent sign, in which case the segment crosses the plane.<br/>
    /// If distances from plane to both end points have the same sign, all line segment is in the same
    /// side of the space, and they haven't a common point.<br/>
    /// Note that if only one end point of the resident line segment lies on the plane, we consider that it is
    /// in one of the sides in which the plane divides the space.
    /// </remarks>
    /// <param name="plane">[IN] The plane we want check the relation with resident line segment. If it is null, the result
    /// is undefined.</param>
    /// <returns>
    /// An integer value like follows:<br/><ul>
    /// <li>Contained: All the line segment lies on plane.</li>
    /// <li>Positive Side: The line segment is fully contained in the positive side of the space defined by the plane.</li>
    /// <li>Negative Side: The line segment is fully contained in the negative side of the space defined by the plane.</li>
    /// <li>BothSides: One end point of the line segment is in the positive side and the other is in the negative one.</li>
    /// </ul><br/>
    /// We consider "positive part of the space" the locus of points which verifies \f$ Ax + By + Cz + D > 0 \f$.
    /// </returns>
    EQSpaceRelation SpaceRelation(const QBasePlane &plane) const
    {
        // The plane must not be null
        QE_ASSERT( SQFloat::IsNotZero(plane.a) || SQFloat::IsNotZero(plane.b) || SQFloat::IsNotZero(plane.c) );

        const float_q &DIST_A = plane.a * this->A.x + plane.b * this->A.y + plane.c * this->A.z + plane.d;
        const float_q &DIST_B = plane.a * this->B.x + plane.b * this->B.y + plane.c * this->B.z + plane.d;

        if (SQFloat::IsZero(DIST_A) && SQFloat::IsZero(DIST_B))
            return EQSpaceRelation::E_Contained;
        else if ( SQFloat::IsGreaterOrEquals(DIST_A, SQFloat::_0) && SQFloat::IsGreaterOrEquals(DIST_B, SQFloat::_0) )
            return EQSpaceRelation::E_PositiveSide;
        else if ( SQFloat::IsLessOrEquals(DIST_A, SQFloat::_0) && SQFloat::IsLessOrEquals(DIST_B, SQFloat::_0) )
            return EQSpaceRelation::E_NegativeSide;
        else
            return EQSpaceRelation::E_BothSides;
    }

    /// <summary>
    /// Transforms the resident line segment.
    /// </summary>
    /// <param name="transformation">[IN] 4x3 Matrix which contains the transformation.</param>
    /// <returns>
	/// The transformed segment.
	/// </returns>
    QLineSegment3D<VectorType> Transform(const QTransformationMatrix<QMatrix4x3> &transformation) const
    {
        QLineSegment3D<VectorType> auxLineSegment = *this;
        SQPoint::Transform(transformation, rcast_q(&auxLineSegment, VectorType*), 2);
        return auxLineSegment;
    }

    /// <summary>
    /// Transforms the resident line segment.
    /// </summary>
    /// <param name="transformation">[IN] 4x4 Matrix which contains the transformation.</param>
    /// <returns>
	/// The transformed segment.
	/// </returns>
    QLineSegment3D<VectorType> Transform(const QTransformationMatrix<QMatrix4x4> &transformation) const
    {
        QLineSegment3D<VectorType> auxLineSegment = *this;
        SQPoint::Transform(transformation, rcast_q(&auxLineSegment, VectorType*), 2);
        return auxLineSegment;
    }

    /// <summary>
    /// Transforms the resident line segment.
    /// </summary>
    /// <param name="spaceConversion">[IN] Space conversion matrix which contains the transformation.</param>
    /// <returns>
	/// The converted segment.
	/// </returns>
    QLineSegment3D<VectorType> Transform(const QSpaceConversionMatrix &spaceConversion) const
    {
        QLineSegment3D<VectorType> auxLineSegment = *this;
        SQPoint::Transform(spaceConversion, rcast_q(&auxLineSegment, VectorType*), 2);
        return auxLineSegment;
    }

    /// <summary>
    /// Transforms the resident line segment using a pivot.
    /// </summary>
    /// <remarks>
    /// When using 4D vectors, the W component of the pivot point doesn't affect the result.
    /// </remarks>
    /// <param name="transformation">[IN] 4x3 Matrix which contains the transformation.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the rotation.</param>
    /// <returns>
	/// The transformed segment.
	/// </returns>
    QLineSegment3D<VectorType> TransformWithPivot(const QTransformationMatrix<QMatrix4x3> &transformation, const VectorType &vPivot) const
    {
        QLineSegment3D<VectorType> auxLineSegment = *this;
        SQPoint::TransformWithPivot(transformation, vPivot, rcast_q(&auxLineSegment, VectorType*), 2);
        return auxLineSegment;
    }

    /// <summary>
    /// Transforms the resident line segment using a pivot.
    /// </summary>
    /// <remarks>
    /// When using 4D vectors, the W component of the pivot point doesn't affect the result.
    /// </remarks>
    /// <param name="transformation">[IN] 4x4 Matrix which contains the transformation.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the rotation.</param>
    /// <returns>
	/// The transformed segment.
	/// </returns>
    QLineSegment3D<VectorType> TransformWithPivot(const QTransformationMatrix<QMatrix4x4> &transformation, const VectorType &vPivot) const
    {
        QLineSegment3D<VectorType> auxLineSegment = *this;
        SQPoint::TransformWithPivot(transformation, vPivot, rcast_q(&auxLineSegment, VectorType*), 2);
        return auxLineSegment;
    }
    
	/// <summary>
	/// Translates the line segment.
	/// </summary>
    /// <param name="vTranslation">[IN] Vector that contains the translation to be applied.</param>
    /// <returns>
	/// The translated segment.
	/// </returns>
    QLineSegment3D<VectorType> Translate(const QBaseVector3 &vTranslation) const
    {
        QLineSegment3D<VectorType> auxLineSegment = *this;
        SQPoint::Translate(vTranslation, rcast_q(&auxLineSegment, VectorType*), 2);
        return auxLineSegment;
    }

	/// <summary>
	/// Translates the line segment.
	/// </summary>
    /// <param name="fTranslationX">[IN] Scalar that contains the translation on X axis.</param>
    /// <param name="fTranslationY">[IN] Scalar that contains the translation on Y axis.</param>
    /// <param name="fTranslationZ">[IN] Scalar that contains the translation on Z axis.</param>
    /// <returns>
	/// The translated segment.
	/// </returns>
    QLineSegment3D<VectorType> Translate(const float_q &fTranslationX, const float_q &fTranslationY, const float_q &fTranslationZ) const
    {
        QLineSegment3D<VectorType> auxLineSegment = *this;
        SQPoint::Translate(fTranslationX, fTranslationY, fTranslationZ, rcast_q(&auxLineSegment, VectorType*), 2);
        return auxLineSegment;
    }

	/// <summary>
	/// Translates the line segment.
	/// </summary>
    /// <param name="translation">[IN] 4x3 Matrix which contains the translation to be applied.</param>
    /// <returns>
	/// The translated segment.
	/// </returns>
    QLineSegment3D<VectorType> Translate(const QTranslationMatrix<QMatrix4x3> &translation) const
    {
        QLineSegment3D<VectorType> auxLineSegment = *this;
        SQPoint::Translate(translation, rcast_q(&auxLineSegment, VectorType*), 2);
        return auxLineSegment;
    }

	/// <summary>
	/// Translates the line segment.
	/// </summary>
    /// <param name="translation">[IN] 4x4 Matrix which contains the translation to be applied.</param>
    /// <returns>
	/// The translated segment.
	/// </returns>
    QLineSegment3D<VectorType> Translate(const QTranslationMatrix<QMatrix4x4> &translation) const
    {
        QLineSegment3D<VectorType> auxLineSegment = *this;
        SQPoint::Translate(translation, rcast_q(&auxLineSegment, VectorType*), 2);
        return auxLineSegment;
    }

	/// <summary>
	/// Rotates the line segment.
	/// </summary>
    /// <param name="qRotation">[IN] Quaternion that represents the rotation.</param>
    /// <returns>
	/// The rotated segment.
	/// </returns>
    QLineSegment3D<VectorType> Rotate(const QQuaternion &qRotation) const
    {
        QLineSegment3D<VectorType> auxLineSegment = *this;
        SQPoint::Rotate(qRotation, rcast_q(&auxLineSegment, VectorType*), 2);
        return auxLineSegment;
    }

	/// <summary>
	/// Rotates the line segment.
	/// </summary>
    /// <param name="rotation">[IN] Matrix which contains the rotation to be applied.</param>
    /// <returns>
	/// The rotated segment.
	/// </returns>
    QLineSegment3D<VectorType> Rotate(const QRotationMatrix3x3 &rotation) const
    {
        QLineSegment3D<VectorType> auxLineSegment = *this;
        SQPoint::Rotate(rotation, rcast_q(&auxLineSegment, VectorType*), 2);
        return auxLineSegment;
    }

	/// <summary>
	/// Rotates the line segment using a pivot.
	/// </summary>
    /// <param name="qRotation">[IN] Quaternion that represents the rotation.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the rotation.</param>
    /// <returns>
	/// The rotated segment.
	/// </returns>
    QLineSegment3D<VectorType> RotateWithPivot(const QQuaternion &qRotation, const VectorType &vPivot) const
    {
        QLineSegment3D<VectorType> auxLineSegment = *this;
        SQPoint::RotateWithPivot(qRotation, vPivot, rcast_q(&auxLineSegment, VectorType*), 2);
        return auxLineSegment;
    }

	/// <summary>
	/// Rotates the line segment using a pivot.
	/// </summary>
    /// <param name="rotation">[IN] Matrix which contains the rotation to be applied.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the rotation.</param>
    /// <returns>
	/// The rotated segment.
	/// </returns>
    QLineSegment3D<VectorType> RotateWithPivot(const QRotationMatrix3x3 &rotation, const VectorType &vPivot) const
    {
        QLineSegment3D<VectorType> auxLineSegment = *this;
        SQPoint::RotateWithPivot(rotation, vPivot, rcast_q(&auxLineSegment, VectorType*), 2);
        return auxLineSegment;
    }

 	/// <summary>
	/// Scales the line segment.
	/// </summary>
    /// <param name="vScale">[IN] Vector that contains the scale to be applied.</param>
    /// <returns>
	/// The scaled segment.
	/// </returns>
    QLineSegment3D<VectorType> Scale(const QVector3 &vScale) const
    {
        QLineSegment3D<VectorType> auxLineSegment = *this;
        SQPoint::Scale(vScale, rcast_q(&auxLineSegment, VectorType*), 2);
        return auxLineSegment;
    }

 	/// <summary>
	/// Scales the line segment.
	/// </summary>
    /// <param name="fScaleX">[IN] Scalar that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar that contains the scale on Y axis.</param>
    /// <param name="fScaleZ">[IN] Scalar that contains the scale on Z axis.</param>
    /// <returns>
	/// The scaled segment.
	/// </returns>
    QLineSegment3D<VectorType> Scale(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ) const
    {
        QLineSegment3D<VectorType> auxLineSegment = *this;
        SQPoint::Scale(fScaleX, fScaleY, fScaleZ, rcast_q(&auxLineSegment, VectorType*), 2);
        return auxLineSegment;
    }

 	/// <summary>
	/// Scales the line segment.
	/// </summary>
    /// <param name="scale">[IN] Matrix which contains the scale to be applied.</param>
    /// <returns>
	/// The scaled segment.
	/// </returns>
    QLineSegment3D<VectorType> Scale(const QScalingMatrix3x3& scale) const
    {
        QLineSegment3D<VectorType> auxLineSegment = *this;
        SQPoint::Scale(scale, rcast_q(&auxLineSegment, VectorType*), 2);
        return auxLineSegment;
    }

 	/// <summary>
	/// Scales the line segment using a pivot.
	/// </summary>
    /// <param name="vScale">[IN] Vector that contains the scale to be applied.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    /// <returns>
	/// The scaled segment.
	/// </returns>
    QLineSegment3D<VectorType> ScaleWithPivot(const QVector3 &vScale, const VectorType &vPivot) const
    {
        QLineSegment3D<VectorType> auxLineSegment = *this;
        SQPoint::ScaleWithPivot(vScale, vPivot, rcast_q(&auxLineSegment, VectorType*), 2);
        return auxLineSegment;
    }

 	/// <summary>
	/// Scales the line segment using a pivot.
	/// </summary>
    /// <param name="fScaleX">[IN] Scalar that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar that contains the scale on Y axis.</param>
    /// <param name="fScaleZ">[IN] Scalar that contains the scale on Z axis.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    /// <returns>
	/// The scaled segment.
	/// </returns>
    QLineSegment3D<VectorType> ScaleWithPivot(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ, const VectorType &vPivot) const
    {
        QLineSegment3D<VectorType> auxLineSegment = *this;
        SQPoint::ScaleWithPivot(fScaleX, fScaleY, fScaleZ, vPivot, rcast_q(&auxLineSegment, VectorType*), 2);
        return auxLineSegment;
    }

 	/// <summary>
	/// Scales the line segment using a pivot.
	/// </summary>
    /// <param name="scale">[IN] Matrix which contains the scale to be applied.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    /// <returns>
	/// The scaled segment.
	/// </returns>
    QLineSegment3D<VectorType> ScaleWithPivot(const QScalingMatrix3x3& scale, const VectorType& vPivot) const
    {
        QLineSegment3D<VectorType> auxLineSegment = *this;
        SQPoint::ScaleWithPivot(scale, vPivot, rcast_q(&auxLineSegment, VectorType*), 2);
        return auxLineSegment;
    }

protected:

    /// <summary>
	/// Calculates if a point is inside the triangle provided applying barycentric technique.
    /// </summary>
    /// <typeparam name="VectorTypeParam">Allowed types: QVector3, QVector4.</typeparam>
    /// <param name="triangle">[IN] The triangle that may contain the point.</param>
    /// <param name="vPoint">[IN] The point that may be contained in the triangle.</param>
    /// <returns>
	/// True if the point is inside the triangle; False otherwise.
	/// </returns>
    template <class VectorTypeParam>
    bool PointInsideTriangle(const QBaseTriangle<VectorTypeParam> &triangle, const VectorTypeParam &vPoint) const
    {
        // Compute vectors
        const VectorTypeParam &V0(triangle.C - triangle.A);
        const VectorTypeParam &V1(triangle.B - triangle.A);
        const VectorTypeParam &V2(vPoint - triangle.A);

        // Compute dot products
        const float_q &DOT_00 = V0.DotProduct(V0);
        const float_q &DOT_01 = V0.DotProduct(V1);
        const float_q &DOT_02 = V0.DotProduct(V2);
        const float_q &DOT_11 = V1.DotProduct(V1);
        const float_q &DOT_12 = V1.DotProduct(V2);

        // Compute barycentric coordinates
        const float_q &DENOM = DOT_00 * DOT_11 - DOT_01 * DOT_01;

        QE_ASSERT(DENOM != SQFloat::_0)

        const float_q &INV_DENOM = SQFloat::_1 / DENOM;

        const float_q &fU = (DOT_11 * DOT_02 - DOT_01 * DOT_12) * INV_DENOM;
        const float_q &fV = (DOT_00 * DOT_12 - DOT_01 * DOT_02) * INV_DENOM;

        // Check if point is in triangle
        return SQFloat::IsGreaterOrEquals(fU, SQFloat::_0) && 
               SQFloat::IsGreaterOrEquals(fV, SQFloat::_0) && 
               SQFloat::IsLessOrEquals(fU + fV, SQFloat::_1);
    }

    /// <summary>
	/// Calculates if a point is inside the convex quadrilateral provided by the vertex A, B, C and D,
    /// applying barycentric technique. Is supossed that quadrilateral vertex are consecutive.
    /// </summary>
    /// <typeparam name="VectorTypeParam">Allowed types: QVector3, QVector4.</typeparam>
    /// <param name="vA">[IN] The point A of the quadrilateral.</param>
    /// <param name="vB">[IN] The point B of the quadrilateral.</param>
    /// <param name="vC">[IN] The point C of the quadrilateral.</param>
    /// <param name="vD">[IN] The point D of the quadrilateral.</param>
    /// <param name="vPoint">[IN] The point that may be contained in the quadrilateral.</param>
    /// <returns>
	/// True if the point belongs to the quadrilateral; False otherwise.
	/// </returns>
    template <class VectorTypeParam>
    bool PointInsideQuadrilateral(const VectorTypeParam &vA, const VectorTypeParam &vB,
                                  const VectorTypeParam &vC, const VectorTypeParam &vD, const VectorTypeParam &vPoint) const
    {
        // Compute vectors
        const VectorTypeParam &V0(vC - vA);
        const VectorTypeParam &V1(vB - vA);
        const VectorTypeParam &V2(vPoint - vA);

        // Compute dot products
        const float_q &DOT_00 = V0.DotProduct(V0);
        const float_q &DOT_01 = V0.DotProduct(V1);
        const float_q &DOT_02 = V0.DotProduct(V2);
        const float_q &DOT_11 = V1.DotProduct(V1);
        const float_q &DOT_12 = V1.DotProduct(V2);

        // Compute barycentric coordinates
        const float_q &DENOM = DOT_00 * DOT_11 - DOT_01 * DOT_01;

        QE_ASSERT(DENOM != SQFloat::_0)

        const float_q &INV_DENOM = SQFloat::_1 / DENOM;

        const float_q &fU = (DOT_11 * DOT_02 - DOT_01 * DOT_12) * INV_DENOM;
        const float_q &fV = (DOT_00 * DOT_12 - DOT_01 * DOT_02) * INV_DENOM;

        // Check if point is in triangle
        if ( SQFloat::IsGreaterOrEquals(fU, SQFloat::_0) && 
             SQFloat::IsGreaterOrEquals(fV, SQFloat::_0) && 
             SQFloat::IsLessOrEquals(fU + fV, SQFloat::_1) )
            return true;

        // Compute new vector
        const VectorTypeParam &V3(vD - vA);

        // Compute new dot products
        const float_q &DOT_03 = V0.DotProduct(V3);
        const float_q &DOT_33 = V3.DotProduct(V3);
        const float_q &DOT_32 = V3.DotProduct(V2);

        // Compute new barycentric coordinates
        const float_q &DENOM2 = DOT_00 * DOT_33 - DOT_03 * DOT_03;

        QE_ASSERT(DENOM2 != SQFloat::_0)

        const float_q &INV_DENOM2 = SQFloat::_1 / DENOM2;

        const float_q &fU2 = (DOT_33 * DOT_02 - DOT_03 * DOT_32) * INV_DENOM2;
        const float_q &fV2 = (DOT_00 * DOT_32 - DOT_03 * DOT_02) * INV_DENOM2;

        // Check if point is in triangle
        return SQFloat::IsGreaterOrEquals(fU2, SQFloat::_0) && 
               SQFloat::IsGreaterOrEquals(fV2, SQFloat::_0) && 
               SQFloat::IsLessOrEquals(fU2 + fV2, SQFloat::_1);
    }

    /// <summary>
	/// Calculates if two points are in the same side of a plane defined by 3 points.
    /// </summary>
    /// <typeparam name="VectorTypeParam">Allowed types: QVector3, QVector4.</typeparam>
    /// <param name="vPoint1">[IN] The first point to be checked.</param>
    /// <param name="vPoint2">[IN] The second point to be checked.</param>
    /// <param name="vA">[IN] One of the points that define the plane that divides the space in two parts.</param>
    /// <param name="vB">[IN] One of the points that define the plane that divides the space in two parts.</param>
    /// <param name="vC">[IN] One of the points that define the plane that divides the space in two parts.</param>
    /// <returns>
	/// True if both points lies in the same side of the plane.
	/// </returns>
    template <class VectorTypeParam>
    bool PointsInSameSideOfPlane(const VectorTypeParam &vPoint1, const VectorTypeParam &vPoint2,
                                 const VectorTypeParam &vA, const VectorTypeParam &vB, const VectorTypeParam &vC) const
    {
        QPlane p(vA, vB, vC);

        const float_q &DIST_P1 = p.a * vPoint1.x + p.b * vPoint1.y + p.c * vPoint1.z + p.d;
        const float_q &DIST_P2 = p.a * vPoint2.x + p.b * vPoint2.y + p.c * vPoint2.z + p.d;

        return SQFloat::IsGreaterOrEquals(DIST_P1 * DIST_P2, SQFloat::_0);
    }

    // [TODO] Thund: This may be replaced with a call to QHexahedron::Contains. This would add a dependency to QHexahedron.
    
    /// <summary>
	/// Checks whether a point is contained or not in a hexahedron.
    /// </summary>
    /// <typeparam name="VectorTypeParam">Allowed types: QVector3, QVector4.</typeparam>
    /// <param name="hexahedron">[IN] The hexahedron where the point may be contained.</param>
    /// <param name="vPoint">[IN] The point to be checked.</param>
    /// <returns>
	/// True if the point is inside the hexahedron (if it lies in a face, it is considered as inside); False otherwise.
	/// </returns>
    template <class VectorTypeParam>
    bool PointInsideHexahedron(const QBaseHexahedron<VectorTypeParam> &hexahedron, const VectorTypeParam &vPoint) const
    {
        return (PointsInSameSideOfPlane(vPoint, hexahedron.E, hexahedron.A, hexahedron.B, hexahedron.C) &&
                PointsInSameSideOfPlane(vPoint, hexahedron.A, hexahedron.E, hexahedron.F, hexahedron.G) &&
                PointsInSameSideOfPlane(vPoint, hexahedron.C, hexahedron.A, hexahedron.B, hexahedron.H) &&
                PointsInSameSideOfPlane(vPoint, hexahedron.A, hexahedron.B, hexahedron.C, hexahedron.G) &&
                PointsInSameSideOfPlane(vPoint, hexahedron.C, hexahedron.A, hexahedron.D, hexahedron.F) &&
                PointsInSameSideOfPlane(vPoint, hexahedron.A, hexahedron.C, hexahedron.D, hexahedron.F) );
    }

    /// <summary>
	/// Checks if a segment intersects a cuadrilateral.
    /// </summary>
    /// <remarks>
    /// It's supossed that A, B, C, D are consecutive vertices of a cuadrilateral.
	/// </remarks>
    /// <typeparam name="VectorTypeParam">Allowed types: QVector3, QVector4.</typeparam>
    /// <param name="segment">[IN] The segment whose intersections are to be calculated.</param>
    /// <param name="vA">[IN] The point A of the quadrilateral.</param>
    /// <param name="vB">[IN] The point B of the quadrilateral.</param>
    /// <param name="vC">[IN] The point C of the quadrilateral.</param>
    /// <param name="vD">[IN] The point D of the quadrilateral.</param>
    /// <returns>
	/// A boolean value that indicates whether the segment and the quadrilateral intersect or not.<br/>
    /// <br/>
    /// <b>True</b><br/>
    /// The segment and the quadrilateral intersect, including the following cases:
    /// - The line segment intersects with a vertex of the quadrilateral.
    /// - Only one endpoint is contained in the quadrilateral.
    /// - Only one endpoint is contained in an edge of the quadrilateral.
    /// - The line segment intersects with an edge of the quadrilateral, being both endpoints outside.
    /// - An endpoint coincide with a vertex of the quadrilateral.
    /// - The segment intersects with two edges of the quadrilateral.
    /// - Both endpoints belong to two different edges of the quadrilateral.
    /// - Both endpoints belong to the same edge of the quadrilateral.
    /// - The segment is contained in the quadrilateral (endpoints are not tangent to any edge).
    ///
    /// <b>False</b><br/>
    /// The line segment does not intersect with the quadrilateral.
	/// </returns>
    template <class VectorTypeParam>
    bool QuadrilateralIntersection(const QLineSegment3D<VectorTypeParam> &segment,
                                   const VectorTypeParam &vA, const VectorTypeParam &vB,
                                   const VectorTypeParam &vC, const VectorTypeParam &vD) const
    {
        // Plane equation
        QPlane auxP(vA, vB, vC);

        // Line Segment don't intersects the cuadrilateral plane.
        if (!segment.Intersection(auxP))
            return false;

        // If both end points satisfy plane equation, the line segment lies on plane
        const float_q &DOT1 = auxP.a * segment.B.x + auxP.b * segment.B.y + auxP.c * segment.B.z + auxP.d;
        const float_q &DOT2 = auxP.a * segment.A.x + auxP.b * segment.A.y + auxP.c * segment.A.z + auxP.d;

        if (SQFloat::IsZero(DOT1) && SQFloat::IsZero(DOT2))
        {
            if (segment.QLineSegment<VectorTypeParam>::Intersection(QLineSegment<VectorTypeParam> (vA, vB)) ||   // Both cuadrilateral and line segment are coplanar. If the line segment
                segment.QLineSegment<VectorTypeParam>::Intersection(QLineSegment<VectorTypeParam> (vB, vC)) ||   // intersects one of the edges of the cuadrilateral, then the line segment intersects the cuadrilateral.
                segment.QLineSegment<VectorTypeParam>::Intersection(QLineSegment<VectorTypeParam> (vC, vD)) ||
                segment.QLineSegment<VectorTypeParam>::Intersection(QLineSegment<VectorTypeParam> (vD, vA)))
                return true;
            else if ( PointInsideQuadrilateral(vA, vB, vC, vD, segment.A) ) // Now we check if segment is fully contained in the cuadrilateral
                return true;                                           // We only check "A" end point, since if "A" is inside, "B" must be inside too (see previus test).
            else
                return false;
        }

        QE_ASSERT(SQFloat::IsNotZero(DOT2 - DOT1))

        // The point which satisfies both line and plane equations.
        VectorTypeParam vAux = segment.A + (segment.B - segment.A) * DOT2/(DOT2 - DOT1);

        // For every edge, it tests if the intersection point is in the same side of each edge
        // than any other vextex (not of the edge). If it does, then it's inside the cuadrilateral,
        // otherwise it's outside.
        return PointInsideQuadrilateral(vA, vB, vC, vD, vAux);
    }
        
    /// <summary>
	/// Computes the intersection between a line segment and a cuadrilateral. 
    /// </summary>
    /// <remarks>
    /// It's supossed that A, B, C, D are consecutive vertices of a cuadrilateral.
	/// </remarks>
    /// <typeparam name="VectorTypeParam">Allowed types: QVector3, QVector4.</typeparam>
    /// <param name="segment">[IN] The segment whose intersections are to be calculated.</param>
    /// <param name="vA">[IN] The point A of the quadrilateral.</param>
    /// <param name="vB">[IN] The point B of the quadrilateral.</param>
    /// <param name="vC">[IN] The point C of the quadrilateral.</param>
    /// <param name="vD">[IN] The point D of the quadrilateral.</param>
    /// <param name="vIntersection">[OUT] The closest intersection point to the endpoint A.</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The line segment intersects with a vertex of the quadrilateral.
    /// - Only one endpoint is contained in the quadrilateral.
    /// - Only one endpoint is contained in an edge of the quadrilateral.
    /// - The line segment intersects with an edge of the quadrilateral, being both endpoints outside.
    /// - An endpoint coincide with a vertex of the quadrilateral.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The segment intersects with two edges of the quadrilateral.
    /// - Both endpoints belong to two different edges of the quadrilateral.
    /// - Both endpoints belong to the same edge of the quadrilateral.
    ///
    /// <b>Infinite</b><br/>
    /// There are infinite intersections.<br/>
    /// - The segment is contained in the quadrilateral (endpoints are not tangent to any edge).
    /// </returns>
    template <class VectorTypeParam>
    EQIntersections QuadrilateralIntersectionPoint(const QLineSegment3D<VectorTypeParam> &segment,
                                                   const VectorTypeParam &vA, const VectorTypeParam &vB,
                                                   const VectorTypeParam &vC, const VectorTypeParam &vD,
                                                   VectorTypeParam &vIntersection) const
    {
        VectorTypeParam vAux;
        return this->QuadrilateralIntersectionPoint(segment, vA, vB, vC, vD, vIntersection, vAux);
    }

    /// <summary>
	/// Computes the intersection between a line segment and a cuadrilateral. 
    /// </summary>
    /// <remarks>
    /// It's supossed that A, B, C, D are consecutive vertices of a cuadrilateral.
	/// </remarks>
    /// <typeparam name="VectorTypeParam">Allowed types: QVector3, QVector4.</typeparam>
    /// <param name="segment">[IN] The segment whose intersections are to be calculated.</param>
    /// <param name="vA">[IN] The point A of the quadrilateral.</param>
    /// <param name="vB">[IN] The point B of the quadrilateral.</param>
    /// <param name="vC">[IN] The point C of the quadrilateral.</param>
    /// <param name="vD">[IN] The point D of the quadrilateral.</param>
    /// <param name="vIntersection1">[OUT] The closest intersection point to the endpoint A.</param>
    /// <param name="vIntersection2">[OUT] The furthest intersection point to the endpoint B.</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The line segment intersects with a vertex of the quadrilateral.
    /// - Only one endpoint is contained in the quadrilateral.
    /// - Only one endpoint is contained in an edge of the quadrilateral.
    /// - The line segment intersects with an edge of the quadrilateral, being both endpoints outside.
    /// - An endpoint coincide with a vertex of the quadrilateral.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The segment intersects with two edges of the quadrilateral.
    /// - Both endpoints belong to two different edges of the quadrilateral.
    /// - Both endpoints belong to the same edge of the quadrilateral.
    ///
    /// <b>Infinite</b><br/>
    /// There are infinite intersections.<br/>
    /// - The segment is contained in the quadrilateral (endpoints are not tangent to any edge).
    /// </returns>
    template <class VectorTypeParam>
    EQIntersections QuadrilateralIntersectionPoint(const QLineSegment3D<VectorTypeParam> &segment,
                                                   const VectorTypeParam &vA, const VectorTypeParam &vB,
                                                   const VectorTypeParam &vC, const VectorTypeParam &vD,
                                                   VectorTypeParam &vIntersection1, VectorTypeParam &vIntersection2) const
    {
        // Plane equation
        QPlane auxP(vA, vB, vC);
        VectorTypeParam vAux;

        const EQIntersections &VALUE = segment.IntersectionPoint(auxP, vAux);

        if (VALUE == EQIntersections::E_None) // Line Segment don't intersects the cuadrilateral plane.
            return EQIntersections::E_None;
        else if (VALUE == EQIntersections::E_One) // Line segment has one intersection with quadrilateral plane
        {
            if (PointInsideQuadrilateral(vA, vB, vC, vD, vAux))
            {
                vIntersection1 = vAux;
                return EQIntersections::E_One;
            }
            else
                return EQIntersections::E_None;
        }
        else // Line segment lies on plane (value == EQIntersections::E_Infinite)
        {
            const bool &A_IS_INSIDE = PointInsideQuadrilateral(vA, vB, vC, vD, segment.A);
            const bool &B_IS_INSIDE = PointInsideQuadrilateral(vA, vB, vC, vD, segment.B);

            if (A_IS_INSIDE && B_IS_INSIDE) // Both line segment end points are inside quadrilateral.
            {
                // A or B are vertex
                const bool &A_IS_VERTEX = (segment.A == vA || segment.A == vB || segment.A == vC || segment.A == vD);
                const bool &B_IS_VERTEX = (segment.B == vA || segment.B == vB || segment.B == vC || segment.B == vD);

                if (A_IS_VERTEX && B_IS_VERTEX) // Both endpoints are vertices of quadrilateral
                {
                    vIntersection1 = segment.A;
                    vIntersection2 = segment.B;
                    return EQIntersections::E_Two;
                }
                else if (A_IS_VERTEX) // Only A endpoint is a vertex of quadrilateral
                {
                    if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vA, vB).MinDistance(segment.B))) // B is in vAvB edge
                    {
                        if (segment.A == vA || segment.A == vB) // A and B are in the same edge
                        {
                            vIntersection1 = segment.A;
                            return EQIntersections::E_One;
                        }
                        else
                        {
                            vIntersection1 = segment.A;
                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                    }
                    else if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vB, vC).MinDistance(segment.B))) // B is in vBvC edge
                    {
                        if (segment.A == vB || segment.A == vC) // A and B are in the same edge
                        {
                            vIntersection1 = segment.A;
                            return EQIntersections::E_One;
                        }
                        else
                        {
                            vIntersection1 = segment.A;
                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                    }
                    else if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vC, vD).MinDistance(segment.B))) // B is in vCvD edge
                    {
                        if (segment.A == vC || segment.A == vD) // A and B are in the same edge
                        {
                            vIntersection1 = segment.A;
                            return EQIntersections::E_One;
                        }
                        else
                        {
                            vIntersection1 = segment.A;
                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                    }
                    else if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(segment.B))) // B is in vDvA edge
                    {
                        if (segment.A == vD || segment.A == vA) // A and B are in the same edge
                        {
                            vIntersection1 = segment.A;
                            return EQIntersections::E_One;
                        }
                        else
                        {
                            vIntersection1 = segment.A;
                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                    }
                    else // B is not in an edge
                    {
                        vIntersection1 = segment.A;
                        return EQIntersections::E_One;
                    }
                }
                else if (B_IS_VERTEX)
                {
                    if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vA, vB).MinDistance(segment.A))) // A is in vAvB edge
                    {
                        if (segment.B == vA || segment.B == vB) // A and B are in the same edge
                        {
                            vIntersection1 = segment.B;
                            return EQIntersections::E_One;
                        }
                        else
                        {
                            vIntersection1 = segment.A;
                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                    }
                    else if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vB, vC).MinDistance(segment.A))) // B is in vBvC edge
                    {
                        if (segment.B == vB || segment.B == vC) // A and B are in the same edge
                        {
                            vIntersection1 = segment.B;
                            return EQIntersections::E_One;
                        }
                        else
                        {
                            vIntersection1 = segment.A;
                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                    }
                    else if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vC, vD).MinDistance(segment.A))) // B is in vCvD edge
                    {
                        if (segment.B == vC || segment.B == vD) // A and B are in the same edge
                        {
                            vIntersection1 = segment.B;
                            return EQIntersections::E_One;
                        }
                        else
                        {
                            vIntersection1 = segment.A;
                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                    }
                    else if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(segment.A))) // B is in vDvA edge
                    {
                        if (segment.B == vD || segment.B == vA) // A and B are in the same edge
                        {
                            vIntersection1 = segment.B;
                            return EQIntersections::E_One;
                        }
                        else
                        {
                            vIntersection1 = segment.A;
                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                    }
                    else
                    {
                        vIntersection1 = segment.B;
                        return EQIntersections::E_One;
                    }
                }
                else // Neither A or B are vertices of quadrilateral
                {
                    if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vA, vB).MinDistance(segment.A))) // A is in vAvB edge (but not a vertex)
                    {
                        vIntersection1 = segment.A;

                        if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vA, vB).MinDistance(segment.B)) || // B is in vAvB edge (but not a vertex)
                            SQFloat::IsZero(QLineSegment<VectorTypeParam>(vB, vC).MinDistance(segment.B)) || // B is in other edge (but not a vertex)
                            SQFloat::IsZero(QLineSegment<VectorTypeParam>(vC, vD).MinDistance(segment.B)) ||
                            SQFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(segment.B)))
                        {
                            
                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                        else // B is not in an edge
                        {
                            return EQIntersections::E_One;
                        }
                    }
                    else if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vB, vC).MinDistance(segment.A))) // A is in vBvC edge (but not a vertex)
                    {
                        vIntersection1 = segment.A;

                        if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vB, vC).MinDistance(segment.B)) || // B is in vBvC edge (but not a vertex)
                            SQFloat::IsZero(QLineSegment<VectorTypeParam>(vA, vB).MinDistance(segment.B)) || // B is in other edge (but not a vertex)
                            SQFloat::IsZero(QLineSegment<VectorTypeParam>(vC, vD).MinDistance(segment.B)) ||
                            SQFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(segment.B)))
                        {
                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                        else // B is not in an edge
                        {
                            return EQIntersections::E_One;
                        }
                    }
                    else if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vC, vD).MinDistance(segment.A))) // A is in vCvD edge (but not a vertex)
                    {
                        vIntersection1 = segment.A;

                        if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vC, vD).MinDistance(segment.B)) || // B is in vCvD edge (but not a vertex)
                            SQFloat::IsZero(QLineSegment<VectorTypeParam>(vA, vB).MinDistance(segment.B)) || // B is in other edge (but not a vertex)
                            SQFloat::IsZero(QLineSegment<VectorTypeParam>(vB, vC).MinDistance(segment.B)) ||
                            SQFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(segment.B)))
                        {
                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                        else // B is not in an edge
                        {
                            return EQIntersections::E_One;
                        }
                    }
                    else if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(segment.A))) // A is in vDvA edge (but not a vertex)
                    {
                        vIntersection1 = segment.A;

                        if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(segment.B)) || // B is in vDvA edge (but not a vertex)
                            SQFloat::IsZero(QLineSegment<VectorTypeParam>(vA, vB).MinDistance(segment.B)) || // B is in other edge (but not a vertex)
                            SQFloat::IsZero(QLineSegment<VectorTypeParam>(vB, vC).MinDistance(segment.B)) ||
                            SQFloat::IsZero(QLineSegment<VectorTypeParam>(vC, vD).MinDistance(segment.B)))
                        {
                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                        else // B is not in an edge
                        {
                            return EQIntersections::E_One;
                        }
                    }
		            else if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(segment.A))) // A is in DA quad edge (but not a vertex)
					{
                        vIntersection1 = segment.A;

						if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(segment.B)) || // B is in DA quad edge (but not a vertex)
						    SQFloat::IsZero(QLineSegment<VectorTypeParam>(vA, vB).MinDistance(segment.B)) || // B is in other edge (but not a vertex)
							SQFloat::IsZero(QLineSegment<VectorTypeParam>(vB, vC).MinDistance(segment.B)) ||
							SQFloat::IsZero(QLineSegment<VectorTypeParam>(vC, vD).MinDistance(segment.B)))
						{
							vIntersection2 = segment.B;
							return EQIntersections::E_Two;
						}
						else // B is not in an edge
						{
							return EQIntersections::E_One;
						}
					}
                    else // A is not in an edge
                    {
                        if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vA, vB).MinDistance(segment.B)) || // B is in an edge (but not a vertex)
                            SQFloat::IsZero(QLineSegment<VectorTypeParam>(vB, vC).MinDistance(segment.B)) ||
                            SQFloat::IsZero(QLineSegment<VectorTypeParam>(vC, vD).MinDistance(segment.B)) ||
                            SQFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(segment.B)))
                        {
                            vIntersection1 = segment.B;
                            return EQIntersections::E_One;
                        }
                        else // B is not in an edge, so A and B are inside the quadrilateral
                            return EQIntersections::E_Infinite;
                    }
                }
            }
            else if (!A_IS_INSIDE && !B_IS_INSIDE) // Both line segment end points are outside quadrilateral.
            {
                VectorTypeParam vPointAB, vPointBC, vPointCD, vPointDA;

                EQIntersections value2AB = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vA, vB), vPointAB);

                if (value2AB == EQIntersections::E_Infinite) // Line segment contains AB edge of quadrilateral
                {
                    if  ( (vA - segment.A).GetSquaredLength() < (vB - segment.A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                    {
                        vIntersection1 = vA;
                        vIntersection2 = vB;
                    }
                    else
                    {
                        vIntersection1 = vB;
                        vIntersection2 = vA;
                    }
                    return EQIntersections::E_Two;
                }

                // Line segment contains BC edge of quadrilateral
                EQIntersections value2BC = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vB, vC), vPointBC);
                if (value2BC == EQIntersections::E_Infinite)
                {
                    if  ( (vB - segment.A).GetSquaredLength() < (vC - segment.A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                    {
                        vIntersection1 = vB;
                        vIntersection2 = vC;
                    }
                    else
                    {
                        vIntersection1 = vC;
                        vIntersection2 = vB;
                    }
                    return EQIntersections::E_Two;
                }

                // Line segment contains CA edge of quadrilateral
                EQIntersections value2CD = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vC, vD), vPointCD);
                if (value2CD == EQIntersections::E_Infinite)
                {
                    if  ( (vC - segment.A).GetSquaredLength() < (vD - segment.A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                    {
                        vIntersection1 = vC;
                        vIntersection2 = vD;
                    }
                    else
                    {
                        vIntersection1 = vD;
                        vIntersection2 = vC;
                    }
                    return EQIntersections::E_Two;
                }

                // Line segment contains DA edge of quadrilateral
                EQIntersections value2DA = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vD, vA), vPointDA);
                if (value2DA == EQIntersections::E_Infinite)
                {
                    if  ( (vD - segment.A).GetSquaredLength() < (vA - segment.A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                    {
                        vIntersection1 = vD;
                        vIntersection2 = vA;
                    }
                    else
                    {
                        vIntersection1 = vA;
                        vIntersection2 = vD;
                    }
                    return EQIntersections::E_Two;
                }

                if (value2AB == EQIntersections::E_One) // Line segment intersects AB edge of quadrilateral
                {
                    if (value2BC == EQIntersections::E_One) // Line segment intersects BC edge of quadrilateral
                    {
                        if (vPointAB == vPointBC) // Are the same point
                        {
							if (value2CD == EQIntersections::E_One) // Line segment intersects CD edge of quadrilateral
							{
								// Returns closest point to A end point of line segment
								if  ( (vPointAB - segment.A).GetSquaredLength() < (vPointCD - segment.A).GetSquaredLength() )
								{
									vIntersection1 = vPointAB;
									vIntersection2 = vPointCD;
								}
								else
								{
									vIntersection1 = vPointCD;
									vIntersection2 = vPointAB;
								}

								return EQIntersections::E_Two;
							}
							else if (value2DA == EQIntersections::E_One) // Line segment intersects DA edge of quadrilateral
							{
								// Returns closest point to A end point of line segment
								if  ( (vPointAB - segment.A).GetSquaredLength() < (vPointDA - segment.A).GetSquaredLength() )
								{
									vIntersection1 = vPointAB;
									vIntersection2 = vPointDA;
								}
								else
								{
									vIntersection1 = vPointDA;
									vIntersection2 = vPointAB;
								}

								return EQIntersections::E_Two;
							}
							else
							{
								vIntersection1 = vPointAB;
								return EQIntersections::E_One;
							}
						}
                        else
                        {
                            if  ( (vPointAB - segment.A).GetSquaredLength() < (vPointBC - segment.A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                            {
                                vIntersection1 = vPointAB;
                                vIntersection2 = vPointBC;
                            }
                            else
                            {
                                vIntersection1 = vPointBC;
                                vIntersection2 = vPointAB;
                            }
                            return EQIntersections::E_Two;
                        }
                    }
                    else if (value2CD == EQIntersections::E_One) // Line segment intersects CD edge of quadrilateral
                    {
                        // Returns closest point to A end point of line segment
                        if  ( (vPointAB - segment.A).GetSquaredLength() < (vPointCD - segment.A).GetSquaredLength() )
                        {
                            vIntersection1 = vPointAB;
                            vIntersection2 = vPointCD;
                        }
                        else
                        {
                            vIntersection1 = vPointCD;
                            vIntersection2 = vPointAB;
                        }

                        return EQIntersections::E_Two;
                    }
                    else if (value2DA == EQIntersections::E_One) // Line segment intersects DA edge of quadrilateral
                    {
                        if (vPointAB == vPointDA) // Are the same point
                        {
                            vIntersection1 = vPointAB;
                            return EQIntersections::E_One;
                        }
                        else
                        {
                            // Returns closest point to A end point of line segment
                            if  ( (vPointAB - segment.A).GetSquaredLength() < (vPointDA - segment.A).GetSquaredLength() )
                            {
                                vIntersection1 = vPointAB;
                                vIntersection2 = vPointDA;
                            }
                            else
                            {
                                vIntersection1 = vPointDA;
                                vIntersection2 = vPointAB;
                            }

                            return EQIntersections::E_Two;
                        }
                    }
                }
                else if (value2BC == EQIntersections::E_One) // Line segment intersects BC edge of quadrilateral
                {
                    if (value2CD == EQIntersections::E_One) // Line segment intersects CA edge of quadrilateral
                    {
                        if (vPointBC == vPointCD) // Are the same point
                        {
                            if (value2DA ==EQIntersections::E_One) // Line segment intersects DA edge of quadrilateral
							{
								// Returns closest point to A end point of line segment
								if  ( (vPointBC - segment.A).GetSquaredLength() < (vPointDA - segment.A).GetSquaredLength() )
								{
									vIntersection1 = vPointBC;
									vIntersection2 = vPointDA;
								}
								else
								{
									vIntersection1 = vPointDA;
									vIntersection2 = vPointBC;
								}

								return EQIntersections::E_Two;
							}
							else
							{
								vIntersection1 = vPointBC;
								return EQIntersections::E_One;
							}
                        }
                        else
                        {
                            // Returns closest point to A end point of line segment
                            if  ( (vPointBC - segment.A).GetSquaredLength() < (vPointCD - segment.A).GetSquaredLength() )
                            {
                                vIntersection1 = vPointBC;
                                vIntersection2 = vPointCD;
                            }
                            else
                            {
                                vIntersection1 = vPointCD;
                                vIntersection2 = vPointBC;
                            }

                            return EQIntersections::E_Two;
                        }
                    }
                    else if (value2DA ==EQIntersections::E_One)
                    {
                        // Returns closest point to A end point of line segment
                        if  ( (vPointBC - segment.A).GetSquaredLength() < (vPointDA - segment.A).GetSquaredLength() )
                        {
                            vIntersection1 = vPointBC;
                            vIntersection2 = vPointDA;
                        }
                        else
                        {
                            vIntersection1 = vPointDA;
                            vIntersection2 = vPointBC;
                        }

                        return EQIntersections::E_Two;
                    }
                }
                else if (value2CD == EQIntersections::E_One) // Line segment intersects CD edge of quadrilateral
                {
                    if (value2DA == EQIntersections::E_One) // Line segment intersects DA edge of quadrilateral
                    {
                        if (vPointCD == vPointDA) // Are the same point
                        {
                            vIntersection1 = vPointCD;
                            return EQIntersections::E_One;
                        }
                        else
                        {
                            // Returns closest point to A end point of line segment
                            if  ( (vPointCD - segment.A).GetSquaredLength() < (vPointDA - segment.A).GetSquaredLength() )
                            {
                                vIntersection1 = vPointCD;
                                vIntersection2 = vPointDA;
                            }
                            else
                            {
                                vIntersection1 = vPointDA;
                                vIntersection2 = vPointCD;
                            }

                            return EQIntersections::E_Two;
                        }
                    }
                }
				else                    // line segment must intersects none, two or three edges, never only one.
					return EQIntersections::E_None; // There are no intersections.
            }
            else // one line segment end point is inside and the other one is outside triangle.
            {
                if (A_IS_INSIDE) // segment.A is inside quadrilateral
                {
                    if (segment.A == vA) // segment.A is vA vertex
                    {
                        vIntersection1 = segment.A;

                        // segment intersects opposite edges
                        EQIntersections value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vB, vC), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
                            vIntersection2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vC, vD), vAux)) == EQIntersections::E_One)
                        {
                            vIntersection2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else
                            return EQIntersections::E_One;
                    }
                    else if (segment.A == vB) // segment.A is vB vertex
                    {
                        vIntersection1 = segment.A;

                        // segment intersects opposite edges
                        EQIntersections value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vC, vD), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
                            vIntersection2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vD, vA), vAux)) == EQIntersections::E_One)
                        {
                            vIntersection2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else
                            return EQIntersections::E_One;
                    }
                    else if (segment.A == vC) // segment.A is vC vertex
                    {
                        vIntersection1 = segment.A;

                        // segment intersects opposite edges
                        EQIntersections value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vD, vA), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
                            vIntersection2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vA, vB), vAux)) == EQIntersections::E_One)
                        {
                            vIntersection2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else
                            return EQIntersections::E_One;
                    }
                    else if (segment.A == vD) // segment.A is vD vertex
                    {
                        vIntersection1 = segment.A;

                        // segment intersects opposite edges
                        EQIntersections value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vA, vB), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
                            vIntersection2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vB, vC), vAux)) == EQIntersections::E_One)
                        {
                            vIntersection2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else
                            return EQIntersections::E_One;
                    }
                    else if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vA, vB).MinDistance(segment.A))) // segment.A is in vAvB edge (but not a vertex)
                    {
                        vIntersection1 = segment.A;

                        // segment intersects other edges
                        EQIntersections value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vB, vC), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
		                    if (vAux == vB || vAux == vC) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vIntersection2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vC, vD), vAux)) == EQIntersections::E_One)
                        {
							if (vAux == vC || vAux == vD) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vIntersection2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vD, vA), vAux)) == EQIntersections::E_One)
                        {
							if (vAux == vD || vAux == vA) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vIntersection2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else
                            return EQIntersections::E_One;
                    }
                    else if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vB, vC).MinDistance(segment.A))) // segment.A is in vBvC edge (but not a vertex)
                    {
                        vIntersection1 = segment.A;

                         // segment intersects other edges
                        EQIntersections value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vA, vB), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
							if (vAux == vA || vAux == vB) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vIntersection2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vC, vD), vAux) == EQIntersections::E_One)
                        {
							if (vAux == vC || vAux == vD) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vIntersection2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vD, vA), vAux) == EQIntersections::E_One)
                        {
							if (vAux == vD || vAux == vA) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vIntersection2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else
                            return EQIntersections::E_One;
                    }
                    else if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vC, vD).MinDistance(segment.A))) // segment.A is in vCvD edge (but not a vertex)
                    {
                        vIntersection1 = segment.A;

                         // segment intersects other edges
                        EQIntersections value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vB, vC), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
							if (vAux == vB || vAux == vC) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vIntersection2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vA, vB), vAux) == EQIntersections::E_One)
                        {
							if (vAux == vA || vAux == vB) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vIntersection2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vD, vA), vAux) == EQIntersections::E_One)
                        {
							if (vAux == vD || vAux == vA) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vIntersection2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else
                            return EQIntersections::E_One;
                    }
                    else if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(segment.A))) // segment.A is in vDvA edge (but not a vertex)
                    {
                        vIntersection1 = segment.A;

                         // segment intersects other edges
                        EQIntersections value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vB, vC), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
							if (vAux == vB || vAux == vC) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vIntersection2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vC, vD), vAux) == EQIntersections::E_One)
                        {
							if (vAux == vC || vAux == vD) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vIntersection2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vA, vB), vAux) == EQIntersections::E_One)
                        {
							if (vAux == vA || vAux == vB) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vIntersection2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else
                            return EQIntersections::E_One;
                    }
                    else // segment.A is strictly inside quadrilateral: is not in a vertex or edge.
                    {
                        EQIntersections value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vA, vB), vAux);
                        if (value2 == EQIntersections::E_One)
                            vIntersection1 = vAux;
                        else if (value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vB, vC), vAux) == EQIntersections::E_One)
                            vIntersection1 = vAux;
                        else if (value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vC, vD), vAux)== EQIntersections::E_One)
                            vIntersection1 = vAux;
                        else if (value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vD, vA), vAux)== EQIntersections::E_One)
                            vIntersection1 = vAux;

                        return EQIntersections::E_One;
                    }
                }
                else // segment.B is inside quadrilateral (A is outside)
                {
                    if (segment.B == vA) // segment.B is vA vertex
                    {
                        // segment intersects opposite edges
                        EQIntersections value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vB, vC), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
                            vIntersection1 = vAux;
                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vC, vD), vAux) == EQIntersections::E_One)
                        {
                            vIntersection1 = vAux;
                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                        else
                        {
                            vIntersection1 = segment.B;
                            return EQIntersections::E_One;
                        }
                    }
                    else if (segment.B == vB) // segment.B is vB vertex
                    {
                        // segment intersects opposite edges
                        EQIntersections value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vC, vD), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
                            vIntersection1 = vAux;
                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vD, vA), vAux) == EQIntersections::E_One)
                        {
                            vIntersection1 = vAux;
                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                        else
                        {
                            vIntersection1 = segment.B;
                            return EQIntersections::E_One;
                        }
                    }
                    else if (segment.B == vC) // segment.B is vC vertex
                    {
                        // segment intersects opposite edges
                        EQIntersections value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vD, vA), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
                            vIntersection1 = vAux;
                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vA, vB), vAux) == EQIntersections::E_One)
                        {
                            vIntersection1 = vAux;
                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                        else
                        {
                            vIntersection1 = segment.B;
                            return EQIntersections::E_One;
                        }
                    }
                    else if (segment.B == vD) // segment.B is vB vertex
                    {
                        // segment intersects opposite edges
                        EQIntersections value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vA, vB), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
                            vIntersection1 = vAux;
                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vB, vC), vAux) == EQIntersections::E_One)
                        {
                            vIntersection1 = vAux;
                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                        else
                        {
                            vIntersection1 = segment.B;
                            return EQIntersections::E_One;
                        }
                    }
                    else if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vA, vB).MinDistance(segment.B))) // segment.B is in vAvB edge (but not a vertex)
                    {
                        // segment intersects the other edges
                        EQIntersections value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vB, vC), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
                            vIntersection1 = vAux;

							if (vAux == vB || vAux == vC) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vC, vD), vAux) == EQIntersections::E_One)
                        {
                            vIntersection1 = vAux;

							if (vAux == vC || vAux == vD) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vD, vA), vAux) == EQIntersections::E_One)
                        {
                            vIntersection1 = vAux;

							if (vAux == vD || vAux == vA) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                        else // There is no other intersection
                        {
                            vIntersection1 = segment.B;
                            return EQIntersections::E_One;
                        }
                    }
                    else if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vB, vC).MinDistance(segment.B))) // segment.B is in vBvC edge (but not a vertex)
                    {
                        // segment intersects the other edges
                        EQIntersections value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vA, vB), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
                            vIntersection1 = vAux;

							if (vAux == vA || vAux == vB) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vC, vD), vAux) == EQIntersections::E_One)
                        {
                            vIntersection1 = vAux;

							if (vAux == vC || vAux == vD) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vD, vA), vAux) == EQIntersections::E_One)
                        {
                            vIntersection1 = vAux;

							if (vAux == vD || vAux == vA) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                        else // There is no other intersection
                        {
                            vIntersection1 = segment.B;
                            return EQIntersections::E_One;
                        }
                    }
                    else if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vC, vD).MinDistance(segment.B))) // segment.B is in vCvD edge (but not a vertex)
                    {
                        // segment intersects the other edges
                        EQIntersections value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vB, vC), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
                            vIntersection1 = vAux;

							if (vAux == vB || vAux == vC) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vA, vB), vAux) == EQIntersections::E_One)
                        {
                            vIntersection1 = vAux;

							if (vAux == vA || vAux == vB) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vD, vA), vAux) == EQIntersections::E_One)
                        {
                            vIntersection1 = vAux;

							if (vAux == vD || vAux == vA) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                        else // There is no other intersection
                        {
                            vIntersection1 = segment.B;
                            return EQIntersections::E_One;
                        }
                    }
                    else if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(segment.B))) // segment.B is in vDvA edge (but not a vertex)
                    {
                        // segment intersects the other edges
                        EQIntersections value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vB, vC), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
                            vIntersection1 = vAux;

							if (vAux == vB || vAux == vC) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vC, vD), vAux) == EQIntersections::E_One)
                        {
                            vIntersection1 = vAux;

							if (vAux == vC || vAux == vD) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vA, vB), vAux) == EQIntersections::E_One)
                        {
                            vIntersection1 = vAux;

							if (vAux == vA || vAux == vB) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                        else // There is no other intersection
                        {
                            vIntersection1 = segment.B;
                            return EQIntersections::E_One;
                        }
                    }
                    else // segment.B is strictly inside quadrilateral: is not in a vertex or edge.
                    {
                        EQIntersections value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vA, vB), vAux);
                        if (value2 == EQIntersections::E_One)
                            vIntersection1 = vAux;
                        else if ((value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vB, vC), vAux)) == EQIntersections::E_One)
                            vIntersection1 = vAux;
                        else if ((value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vC, vD), vAux)) == EQIntersections::E_One)
                            vIntersection1 = vAux;
                        else if ((value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vD, vA), vAux)) == EQIntersections::E_One)
                            vIntersection1 = vAux;

                        return EQIntersections::E_One;
                    }
                }
            }
        }

        // Something was wrong, this line should be never reached
		QE_ASSERT(false)

        return EQIntersections::E_None;
    }
};


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QLINESEGMENT3D__
