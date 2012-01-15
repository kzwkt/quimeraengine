// [TERMS&CONDITIONS]

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
#include "QScaleMatrix3x3.h"

using namespace Kinesis::QuimeraEngine::Tools::DataTypes;

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
/// These points may be expressed as 3D points or vectors, depending on the template parameter,
/// which may be 3D vector or 4D vector.
/// Please note there's really no "source" and "end" points implicit, that is, it's not an oriented segment.
/// </summary>
template <class VectorType>
class QDllExport QLineSegment3D : public QLineSegment<VectorType>
{


 	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
    inline QLineSegment3D()
    {
    }

    /// <summary>
    /// Constructor from two vectors.
    /// </summary>
    /// <param name="vA">[IN] Vector to define endpoint A.</param>
    /// <param name="vB">[IN] Vector to define endpoint B.</param>
	inline QLineSegment3D(const VectorType &vA, const VectorType &vB) : QLineSegment<VectorType>(vA,vB)
    {
    }

	/// <summary>
    /// Constructor from a line segment.
    /// </summary>
    /// <param name="segment">[IN] Line segment in which we want resident line segment is based on.</param>
	inline explicit QLineSegment3D(const QBaseLineSegment<VectorType> &segment) : QLineSegment<VectorType>(segment.A, segment.B)
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
	inline static const QLineSegment3D<VectorType>& GetUnitLine()
	{
	    static const QLineSegment3D<VectorType> UNITLINE(VectorType::GetZeroVector(), VectorType::GetUnitVectorX());
	    return UNITLINE;
    }

    /// <summary>
    /// Zero segment lying in the coordinates center whose endpoints
	/// both equals (0, 0, 0) and it's length equals 0.
    /// </summary>
    /// <returns>
	/// A 0-length line segment.
	/// </returns>
	inline static const QLineSegment3D<VectorType>& GetLineZero()
	{
	    static const QLineSegment3D<VectorType> LINEZERO(VectorType::GetZeroVector(), VectorType::GetZeroVector());
	    return LINEZERO;
	}


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Assign operator. Assigns the provided line segment to the resident line segment.
    /// </summary>
    /// <param name="segment">[IN] The line segment to be assigned.</param>
    /// <returns>
    /// A reference to the modified line segment.
    /// </returns>
    inline QLineSegment3D& operator=(const QBaseLineSegment<VectorType> &segment)
    {
        QBaseLineSegment<VectorType>::operator=(segment);
        return *this;
    }

    /// <summary>
    /// Checks if resident line segment intersects with the provided plane.
    /// Since a plane divides space into two sides (positive and negative), we can check how the end points of
    /// the line segment satisfies the plane equation:
    /// Being the plane equation \f$ ax + by + cz + d = 0 \f$,
    /// and the end points of the line segment \f$ A(A_x, A_y, A_z)\f$, \f$ B(B_x, B_y, B_z)\f$,
    /// we have to check the value of:
    ///
    /// (1) \f$ a\cdot A_x + b\cdot A_y + c\cdot A_z + d \f$
    ///
    /// (2) \f$ a\cdot B_x + b\cdot B_y + c\cdot B_z + d \f$
    ///
    /// If (1) = 0 or (2) = 0, then the line segment intersects the plane (one of the end points lies on plane).
    /// If the sign of (1) and (2) are different, each end point are in a different side of the space
    /// from the plane, and then the line segment intersects the plane.
    /// If (1) and (2) have equal sign, then there are in the same side of the space from the plane,
    /// and the line segment don't intersects the plane.
    /// If one end point of the line segment lies on the plane, we consider there is an intersection.
    /// </summary>
    /// <param name="plane">[IN] The plane we want check if intersects with resident line segment.</param>
    /// <returns>
    /// True if plane and line segment intersects, false otherwise.
    /// </returns>
    inline bool Intersection (const QBasePlane &plane) const
    {
        const float_q &fDistA = plane.a * this->A.x + plane.b * this->A.y + plane.c * this->A.z + plane.d;

        if (SQFloat::IsZero(fDistA))
            return true;

        const float_q &fDistB = plane.a * this->B.x + plane.b * this->B.y + plane.c * this->B.z + plane.d;

        if (SQFloat::IsZero(fDistB))
            return true;

        return SQFloat::IsNegative(fDistA * fDistB);
    }

    /// <summary>
    /// Checks if resident line segment intersects with the provided triangle.
    /// If one end point of the line segment lies on the triangle, or on an edge or vertex of the triangle,
    /// we consider there is an intersection.
    /// </summary>
    /// <param name="triangle">[IN] The triangle we want check if intersects with resident line segment.</param>
    /// <returns>
    /// True if triangle and line segment intersects, false otherwise.
    /// </returns>
    bool Intersection(const QBaseTriangle<VectorType> &triangle) const
    {
        // Calculates if segment intersects with the plane defined by the triangle.

        // Plane equation
        QPlane auxP(triangle.A, triangle.B, triangle.C);

        // Line Segment don't intersects the triangle plane.
        if (!this->Intersection(auxP))
            return false;

        // If both end points satisfy plane equation, the line segment lies on plane
        const float_q &fDot1 = auxP.a * this->B.x + auxP.b * this->B.y + auxP.c * this->B.z + auxP.d;
        const float_q &fDot2 = auxP.a * this->A.x + auxP.b * this->A.y + auxP.c * this->A.z + auxP.d;

        if (SQFloat::IsZero(fDot1) && SQFloat::IsZero(fDot2))
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

        QE_ASSERT(SQFloat::IsNotZero(fDot2 - fDot1))

        // The point which satisfies both line and plane equations.
        VectorType vAux = this->A + (this->B - this->A) * fDot2/(fDot2 - fDot1);

        // Tests if the point is inside the triangle.
        return PointInsideTriangle(triangle, vAux);
    }

    /// <summary>
    /// Checks if resident line segment intersects with the provided sphere.
    /// If one end point of the line segment lies on the sphere surface, we consider that there is an intersection.
    /// </summary>
    /// <param name="orb">[IN] The sphere we want check if intersects with resident line segment.</param>
    /// <returns>
    /// True if sphere and line segment intersects, false otherwise.
    /// </returns>
    inline bool Intersection(const QBaseOrb<VectorType> &orb) const
    {
        return QLineSegment<VectorType>::Intersection(orb);
    }

    /// <summary>
    /// Checks if resident line segment intersects with the provided hexahedron.
    /// If one end point of the line segment lies on one of the hexahedron faces,
    /// we consider there is an intersection.
    /// </summary>
    /// <param name="hexahedron">[IN] The hexahedron we want check if intersects with resident line segment.</param>
    /// <returns>
    /// True if hexahedron and line segment intersects, false otherwise.
    /// </returns>
    bool Intersection(const QBaseHexahedron<VectorType> &hexahedron) const
    {
        // Checks if there is an intersection with any face.
        if (CuadrilateralIntersection(*this, hexahedron.A, hexahedron.B, hexahedron.C, hexahedron.D) ||
            CuadrilateralIntersection(*this, hexahedron.E, hexahedron.F, hexahedron.G, hexahedron.H) ||
            CuadrilateralIntersection(*this, hexahedron.A, hexahedron.B, hexahedron.H, hexahedron.E) ||
            CuadrilateralIntersection(*this, hexahedron.B, hexahedron.C, hexahedron.G, hexahedron.H) ||
            CuadrilateralIntersection(*this, hexahedron.A, hexahedron.D, hexahedron.F, hexahedron.E) ||
            CuadrilateralIntersection(*this, hexahedron.C, hexahedron.D, hexahedron.F, hexahedron.G))
            return true;

        return false;
    }

	/// <summary>
	/// This method receives another line segment, and computes whether they intersect each other or not.
	/// </summary>
	/// <param name="segment">[IN] The segment to be compared to.</param>
	/// <returns>
	/// True if they intersect each other (or if they were coincident), false if they don't.
	/// </returns>
	inline bool Intersection(const QBaseLineSegment<VectorType> &segment) const
	{
		return QLineSegment<VectorType>::Intersection(segment);
	}

	/// <summary>
	/// This method receives another line segment, and computes the intersection point between them,
	/// if it exists.
	/// </summary>
	/// <param name="segment">[IN] The segment to be compared to.</param>
	/// <param name="vIntersection">[OUT] The intersection point, if it exists.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the two line segments, and can take
    /// the following values: E_None, E_One and E_Infinite.
	/// </returns>
	/// <remarks>
	/// -If there's no intersection point, the output parameter used for storing that point won't be modified.
	/// -If segments are totally or parcially coincident only a single point will be stored in the output
	///  parameter, presumingly an endpoint belonging to one of the segments.
	/// </remarks>
	inline EQIntersections IntersectionPoint(const QBaseLineSegment<VectorType> &segment, VectorType &vIntersection) const
	{
		return QLineSegment<VectorType>::IntersectionPoint(segment, vIntersection);
	}

	/// <summary>
	/// This method receives an orb, computes the intersections with the resident line segment and stores the intersection point
	/// closest to A end point, if it exists.
	/// </summary>
	/// <param name="orb">[IN] The orb whose intersection point with resident line segment we want to check.</param>
    /// <param name="vIntersection">[OUT] A vector where to store the intersection point closest to A end point.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the orb, and can take
    /// the following values: E_None, E_One and E_Two.
	/// </returns>
	/// <remarks>
	/// -If there's no intersection point, the output parameter used for storing that point won't be modified.
	/// -If there are two intersections, the output parameter stores only the closest to A end point.
	/// </remarks>
	EQIntersections IntersectionPoint (const QBaseOrb<VectorType> &orb, VectorType &vIntersection) const
	{
        return QLineSegment<VectorType>::IntersectionPoint(orb, vIntersection);
	}

    /// <summary>
	/// This method receives a orb, and computes and stores the points where the resident line segment intersects with it,
    /// if they exists.
	/// </summary>
	/// <param name="orb">[IN] The orb whose intersections with resident line segment we want to check.</param>
    /// <param name="vIntersection1">[OUT] A vector where to store the intersection point closest to A end point.</param>
    /// <param name="vIntersection2">[OUT] A vector where to store the intersection point farthest to A end point.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the orb, and can take
    /// the following values: E_None, E_One and E_Two.
	/// </returns>
	/// <remarks>
	/// -If there's no intersection point, the two output parameters used for storing the points won't be modified.
	/// -If there is one intersection, it's stored in the first output parameter.
	/// -If there are two intersections, the first output parameter stores the closest to A end point of
    ///  line segment, and the second one stores the closest to B end point.
	/// </remarks>
	EQIntersections IntersectionPoint(const QBaseOrb<VectorType> &orb, VectorType &vIntersection1, VectorType &vIntersection2) const
	{
        return QLineSegment<VectorType>::IntersectionPoint(orb, vIntersection1, vIntersection2);
	}

    /// <summary>
	/// This method receives a plane, and computes the point where the resident line segment intersects with it,
    /// if it exists.
	/// </summary>
	/// <param name="plane">[IN] The plane whose intersection with resident line segment we want to check.</param>
	/// <param name="vIntersection">[OUT] A vector where to store the intersection point.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the plane, and can take
    /// the following values: E_None, E_One and E_Infinite.
	/// </returns>
	/// <remarks>
	/// -If there's no intersection point or the line segment lies on plane, the output
    ///  parameter used for storing that point won't be modified.
	/// </remarks>
	EQIntersections IntersectionPoint(const QBasePlane &plane, VectorType &vIntersection) const
	{
        const float_q &fDistA = plane.a * this->A.x + plane.b * this->A.y + plane.c * this->A.z + plane.d;
        const float_q &fDistB = plane.a * this->B.x + plane.b * this->B.y + plane.c * this->B.z + plane.d;

        const bool &bIsZeroDistA = SQFloat::IsZero(fDistA);
        const bool &bIsZeroDistB = SQFloat::IsZero(fDistB);

        if (bIsZeroDistA && !bIsZeroDistB) // A point lies on plane
        {
            vIntersection = this->A;
            return EQIntersections::E_One;
        }
        else if (!bIsZeroDistA && bIsZeroDistB) // B point lies on plane
        {
            vIntersection = this->B;
            return EQIntersections::E_One;
        }
        else if (bIsZeroDistA && bIsZeroDistB) // All line segment lies on plane
            return EQIntersections::E_Infinite;
        else if ( SQFloat::IsLessThan(fDistA * fDistB, SQFloat::_0) ) // Line segment intersects plane in a point
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

            const float_q &fDenom = fDistA - fDistB;

            QE_ASSERT(fDenom != SQFloat::_0)

            vIntersection = this->A + fDistA * (this->B - this->A)/fDenom;

            return EQIntersections::E_One;
        }
        else // Line segment don't intersects plane
            return EQIntersections::E_None;
    }

    /// <summary>
	/// This method receives a triangle, computes the points where the resident line segment intersects with it, and stores
    /// the closest intersection to A end point, if it exists.
	/// </summary>
	/// <param name="triangle">[IN] The triangle whose intersection with resident line segment we want to check.</param>
	/// <param name="vIntersection">[OUT] A vector where to store the intersection point closest to A end point.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the triangle, and can take
    /// the following values: E_None, E_One, E_Two and E_Infinite.
	/// </returns>
	/// <remarks>
	/// -If there's no intersection point or the line segment lies on triangle, the output
    ///  parameter used for storing that point won't be modified.
    /// -if the line segment lies partially on triangle, the intersection point stored is the intersection of
    ///  segment and an edge of the triangle.
	/// </remarks>
	EQIntersections IntersectionPoint(const QBaseTriangle<VectorType> &triangle, VectorType &vIntersection) const
    {
        // Calculates if segment intersects with the plane defined by the triangle.
		VectorType vAux;
		return this->IntersectionPoint(triangle, vIntersection, vAux);
    }

    /// <summary>
	/// This method receives a triangle, and computes the points where the resident line segment intersects with it,
    /// if they exists.
	/// </summary>
	/// <param name="triangle">[IN] The triangle whose intersection with resident line segment we want to check.</param>
	/// <param name="vIntersection1">[OUT] A vector where to store the intersection point closest to A end point of line segment.</param>
    /// <param name="vIntersection2">[OUT] A vector where to store the intersection point farthest to A end point of line segment.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the triangle, and can take
    /// the following values: E_None, E_One, E_Two and E_Infinite.
	/// </returns>
	/// <remarks>
	/// -If there's no intersection point or the line segment lies on triangle, the output
    ///  parameter used for storing that point won't be modified.
    /// -if the line segment lies partially on triangle, the intersection point stored is the intersection of
    ///  segment and an edge of the triangle.
	/// </remarks>
	EQIntersections IntersectionPoint(const QBaseTriangle<VectorType> &triangle, VectorType &vIntersection1, VectorType &vIntersection2) const
	{
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
            const bool &bAIsInside = PointInsideTriangle(triangle, this->A);
            const bool &bBIsInside = PointInsideTriangle(triangle, this->B);

            if (bAIsInside && bBIsInside) // Both line segment end points are inside triangle.
            {
				// A or B are vertex
				const bool &bAIsVertex = (this->A == triangle.A || this->A == triangle.B || this->A == triangle.C);
				const bool &bBIsVertex = (this->B == triangle.A || this->B == triangle.B || this->B == triangle.C);

				if (bAIsVertex && bBIsVertex) // Both endpoints are vertices of triangle
				{
					vIntersection1 = this->A;
					vIntersection2 = this->B;
					return EQIntersections::E_Two;
				}
				else if (bAIsVertex) // Only A endpoint is a vertex of triangle
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
				else if (bBIsVertex)
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
						if (SQFloat::IsZero(QLineSegment<VectorType>(triangle.A, triangle.B).MinDistance(this->B))) // B is in AB triangle edge (but not a vertex)
							return EQIntersections::E_Infinite;
						else if ( SQFloat::IsZero(QLineSegment<VectorType>(triangle.B, triangle.C).MinDistance(this->B)) || // B is in other edge (but not a vertex)
								  SQFloat::IsZero(QLineSegment<VectorType>(triangle.C, triangle.A).MinDistance(this->B)) )
						{
							vIntersection1 = this->A;
							vIntersection2 = this->B;
							return EQIntersections::E_Two;
						}
						else // B is not in an edge
						{
							vIntersection1 = this->A;
							return EQIntersections::E_One;
						}
					}
					else if (SQFloat::IsZero(QLineSegment<VectorType>(triangle.B, triangle.C).MinDistance(this->A))) // A is in BC triangle edge (but not a vertex)
					{
						if (SQFloat::IsZero(QLineSegment<VectorType>(triangle.B, triangle.C).MinDistance(this->B))) // B is in BC triangle edge (but not a vertex)
							return EQIntersections::E_Infinite;
						else if ( SQFloat::IsZero(QLineSegment<VectorType>(triangle.A, triangle.B).MinDistance(this->B)) || // B is in other edge (but not a vertex)
								  SQFloat::IsZero(QLineSegment<VectorType>(triangle.C, triangle.A).MinDistance(this->B)) )
						{
							vIntersection1 = this->A;
							vIntersection2 = this->B;
							return EQIntersections::E_Two;
						}
						else // B is not in an edge
						{
							vIntersection1 = this->A;
							return EQIntersections::E_One;
						}
					}
					else if (SQFloat::IsZero(QLineSegment<VectorType>(triangle.C, triangle.A).MinDistance(this->A))) // A is in CA triangle edge (but not a vertex)
					{
						if (SQFloat::IsZero(QLineSegment<VectorType>(triangle.C, triangle.A).MinDistance(this->B))) // B is in CA triangle edge (but not a vertex)
							return EQIntersections::E_Infinite;
						else if ( SQFloat::IsZero(QLineSegment<VectorType>(triangle.A, triangle.B).MinDistance(this->B)) || // B is in other edge (but not a vertex)
								  SQFloat::IsZero(QLineSegment<VectorType>(triangle.B, triangle.C).MinDistance(this->B)) )
						{
							vIntersection1 = this->A;
							vIntersection2 = this->B;
							return EQIntersections::E_Two;
						}
						else // B is not in an edge
						{
							vIntersection1 = this->A;
							return EQIntersections::E_One;
						}
					}
					else // A is not in an edge
					{
						if ( SQFloat::IsZero(QLineSegment<VectorType>(triangle.A, triangle.B).MinDistance(this->B)) || // B is in an edge (but not a vertex)
							 SQFloat::IsZero(QLineSegment<VectorType>(triangle.B, triangle.C).MinDistance(this->B)) ||
							 SQFloat::IsZero(QLineSegment<VectorType>(triangle.C, triangle.A).MinDistance(this->B)) )
						{
							vIntersection1 = this->B;
							return EQIntersections::E_One;
						}
						else // B is not in an edge
							return EQIntersections::E_Infinite;
					}
				}
			}
            else if (!bAIsInside && !bBIsInside) // Both line segment end points are outside triangle.
            {
                VectorType vPointAB, vPointBC, vPointCA;

                EQIntersections value2AB = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.A, triangle.B), vPointAB);

                if (value2AB == EQIntersections::E_Infinite) // Line segment contains AB edge of triangle
                {
                    if  ( (triangle.A - this->A).GetSquaredLength() < (triangle.B - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
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

                // Line segment contains BC edge of triangle
                EQIntersections value2BC = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.B, triangle.C), vPointBC);
                if (value2BC == EQIntersections::E_Infinite)
                {
                    if  ( (triangle.B - this->A).GetSquaredLength() < (triangle.C - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
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

                // Line segment contains CA edge of triangle
                EQIntersections value2CA = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.C, triangle.A), vPointCA);
                if (value2CA == EQIntersections::E_Infinite)
                {
                    if  ( (triangle.C - this->A).GetSquaredLength() < (triangle.A - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
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

                if (value2AB == EQIntersections::E_One) // Line segment intersects AB edge of triangle
                {
                    if (value2BC == EQIntersections::E_One) // Line segment intersects BC edge of triangle
                    {
                        if (vPointAB == vPointBC) // Are the same point
                        {
							if (value2CA ==EQIntersections::E_One) // Line segment intersects CA edge of triangle
							{
								if  ( (vPointAB - this->A).GetSquaredLength() < (vPointCA - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
								{
									vIntersection1 = vPointAB;
									vIntersection2 = vPointCA;
								}
								else
								{
									vIntersection1 = vPointCA;
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
                            if  ( (vPointAB - this->A).GetSquaredLength() < (vPointBC - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
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
                    else if (value2CA == EQIntersections::E_One) // Line segment intersects CA edge of triangle
                    {
                        if (vPointAB == vPointCA) // Are the same point
                        {
                            vIntersection1 = vPointAB;
                            return EQIntersections::E_One;
                        }
                        else
                        {
                            if  ( (vPointAB - this->A).GetSquaredLength() < (vPointCA - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                            {
                                vIntersection1 = vPointAB;
                                vIntersection2 = vPointCA;
                            }
                            else
                            {
                                vIntersection1 = vPointCA;
                                vIntersection2 = vPointAB;
                            }

                            return EQIntersections::E_Two;
                        }
                    }
		            else                  // Something is wrong: if end points of line segment are outside triangle,
						QE_ASSERT(false)  // line segment must intersects none or two edges, never only one.
                }
                else if (value2BC == EQIntersections::E_One) // Line segment intersects BC edge of triangle
                {
                    if (value2CA == EQIntersections::E_One) // Line segment intersects CA edge of triangle
                    {
                        if (vPointBC == vPointCA) // Are the same point
                        {
                            vIntersection1 = vPointBC;
                            return EQIntersections::E_One;
                        }
                        else
                        {
                            if  ( (vPointBC - this->A).GetSquaredLength() < (vPointCA - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                            {
                                vIntersection1 = vPointBC;
                                vIntersection2 = vPointCA;
                            }
                            else
                            {
                                vIntersection1 = vPointCA;
                                vIntersection2 = vPointBC;
                            }

                            return EQIntersections::E_Two;
                        }
                    }
                    else                  // Something is wrong: if end points of line segment are outside triangle,
                        QE_ASSERT(false)  // line segment must intersects none, two or the three edges, never only one.
                }

                // Line segment don't intersects triangle
                if (value2AB == EQIntersections::E_None && value2BC == EQIntersections::E_None && value2CA == EQIntersections::E_None)
                    return EQIntersections::E_None;
            }
            else // one line segment end point is inside and the other one is outside triangle.
            {
                VectorType vAux; // To store intersection points

				if (bAIsInside) // this->A is inside triangle
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
						else if (value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.C, triangle.A), vAux) == EQIntersections::E_One)
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
						else if (value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.C, triangle.A), vAux) == EQIntersections::E_One)
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
						else if (value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.A, triangle.B), vAux) == EQIntersections::E_One)
						{
							if (vAux == triangle.A || vAux == triangle.B) // Both intersections are in the same edge
								return EQIntersections::E_One;

							vIntersection2 = vAux;
							return EQIntersections::E_Two;
						}
						else
							return EQIntersections::E_One;
					}
					else // this->A is strictly inside triangle: is not in a vertex or edge.
					{
						EQIntersections value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.A, triangle.B), vAux);
						if (value2 == EQIntersections::E_One)
							vIntersection1 = vAux;
						else if (value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.B, triangle.C), vAux) == EQIntersections::E_One)
							vIntersection1 = vAux;
						else if (value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.C, triangle.A), vAux)== EQIntersections::E_One)
							vIntersection1 = vAux;
						else                  // Something is wrong, if one point is inside and the other is outside,
							QE_ASSERT(false)  // there must be intersections.

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
						else if (value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.C, triangle.A), vAux) == EQIntersections::E_One)
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
						else if (value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.C, triangle.A), vAux) == EQIntersections::E_One)
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
						else if (value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.A, triangle.B), vAux) == EQIntersections::E_One)
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
						else if (value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.B, triangle.C), vAux) == EQIntersections::E_One)
							vIntersection1 = vAux;
						else if (value2 = this->IntersectionPoint(QLineSegment3D<VectorType>(triangle.C, triangle.A), vAux)== EQIntersections::E_One)
							vIntersection1 = vAux;
						else                  // Something is wrong, if one point is inside and the other is outside,
							QE_ASSERT(false)  // there must be intersections.

						return EQIntersections::E_One;
					}
				}
            }
        }
    }

    /// <summary>
	/// This method receives a convex hexahedron, and computes the intersection points with the resident line segment,
    /// and stores the closest to A end point, if it exists.
	/// </summary>
	/// <param name="hexahedron">[IN] The hexahedron whose intersections with resident line segment we want to check.</param>
    /// <param name="vIntersection">[OUT] A vector where to store the intersection point.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the hexahedron,
    /// which can takes the following values: E_None, E_One, E_Two and E_Infinite.
	/// </returns>
	/// <remarks>
	/// -If there's no intersection point, the output parameter used for storing that point won't be modified.
	/// -If there are two intersections, the output parameter stores only one of them.
	/// </remarks>
	EQIntersections IntersectionPoint (const QBaseHexahedron<VectorType> &hexahedron, VectorType &vIntersection) const
	{
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
        else if (value1 == EQIntersections::E_Infinite) // Line segment lies in this face (with out intersections with any edge or vertex)
        {
            return EQIntersections::E_Infinite;
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
        else if (value2 == EQIntersections::E_Infinite) // Line segment lies in this face (with out intersections with any edge or vertex)
        {
            return EQIntersections::E_Infinite;
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
        else if (value3 == EQIntersections::E_Infinite) // Line segment lies in this face (with out intersections with any edge or vertex)
        {
            return EQIntersections::E_Infinite;
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
        else if (value4 == EQIntersections::E_Infinite) // Line segment lies in this face (with out intersections with any edge or vertex)
        {
            return EQIntersections::E_Infinite;
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
        else if (value5 == EQIntersections::E_Infinite) // Line segment lies in this face (with out intersections with any edge or vertex)
        {
            return EQIntersections::E_Infinite;
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
        else if (value6 == EQIntersections::E_Infinite) // Line segment lies in this face (with out intersections with any edge or vertex)
        {
            return EQIntersections::E_Infinite;
        }

        if (bPreviousInt) // There is only one intersection with hexahedron
        {
            vIntersection = vAuxPoint;
            return EQIntersections::E_One;
        }
        else // There are no intersections with hexahedron
        {
            const bool &IsInsideA = PointInsideHexahedron(hexahedron, this->A);
            const bool &IsInsideB = PointInsideHexahedron(hexahedron, this->B);

            if (IsInsideA && IsInsideB) // Both line segment end points are inside hexahedron
                return EQIntersections::E_Infinite;
            else if (!IsInsideA && !IsInsideB) // Both line segment end points are outside hexahedron
                return EQIntersections::E_None;
            else // Something is wrong!! There must be intersections in this case.
                QE_ASSERT(false) 
        }
    }

    /// <summary>
	/// This method receives a convex hexahedron, and computes the points where the resident line segment intersects with it,
    /// if they exists.
	/// </summary>
	/// <param name="hexahedron">[IN] The hexahedron whose intersections with resident line segment we want to check.</param>
    /// <param name="vIntersection1">[OUT] A vector where to store the intersection point closest to A end point of line segment.</param>
    /// <param name="vIntersection2">[OUT] A vector where to store the intersection point farthest to A end point of line segment.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the hexahedron,
    /// which can takes the following values: E_None, E_One, E_Two and E_Infinite.
	/// </returns>
	/// <remarks>
	/// -If there's no intersection point, the output parameters used for storing the intersection points won't be modified.
	/// -If there are two intersections, the first output parameter stores the closest point to A end point of line segment.
	/// </remarks>
	EQIntersections IntersectionPoint(const QBaseHexahedron<VectorType> &hexahedron, VectorType &vIntersection1, VectorType &vIntersection2) const
	{
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
        else if (value1 == EQIntersections::E_Infinite) // Line segment lies in this face (with out intersections with any edge or vertex)
        {
            return EQIntersections::E_Infinite;
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
        else if (value2 == EQIntersections::E_Infinite) // Line segment lies in this face (with out intersections with any edge or vertex)
        {
            return EQIntersections::E_Infinite;
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
        else if (value3 == EQIntersections::E_Infinite) // Line segment lies in this face (with out intersections with any edge or vertex)
        {
            return EQIntersections::E_Infinite;
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
        else if (value4 == EQIntersections::E_Infinite) // Line segment lies in this face (with out intersections with any edge or vertex)
        {
            return EQIntersections::E_Infinite;
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
        else if (value3 == EQIntersections::E_Infinite) // Line segment lies in this face (with out intersections with any edge or vertex)
        {
            return EQIntersections::E_Infinite;
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
        }
        else if (value6 == EQIntersections::E_Infinite) // Line segment lies in this face (with out intersections with any edge or vertex)
        {
            return EQIntersections::E_Infinite;
        }

        if (bPreviousInt) // There is only one intersection with hexahedron
        {
            vIntersection1 = vAuxPoint;
            return EQIntersections::E_One;
        }
        else // There are no intersections with hexahedron
        {
            const bool &IsInsideA = PointInsideHexahedron(hexahedron, this->A);
            const bool &IsInsideB = PointInsideHexahedron(hexahedron, this->B);

            if (IsInsideA && IsInsideB) // Both line segment end points are inside hexahedron
                return EQIntersections::E_Infinite;
            else if (!IsInsideA && !IsInsideB) // Both line segment end points are outside hexahedron
                return EQIntersections::E_None;
            else // Something is wrong!! There must be intersections in this case.
                QE_ASSERT(false) 
        }
    }

    /// <summary>
    /// Calculates the maximum distance between the resident line segment and a plane provided.
    /// </summary>
    /// <param name="plane">[IN] The plane we want to know the maximum distance from the line segment.</param>
    /// <returns>
    /// A floating point value containing the maximum distance between the resident line segment and a plane provided.
    /// </returns>
    /// <remarks>
    /// The plane must be normalized to obtain correct result.
    /// </remarks>
    inline float_q MaxDistance(const QBasePlane &plane) const
    {
        const float_q &fDistA = plane.As<QPlane>().PointDistance(this->A);
        const float_q &fDistB = plane.As<QPlane>().PointDistance(this->B);

        return std::max(fDistA, fDistB);
    }

    /// <summary>
	/// Given an input line segment, this method returns the maximum distance between this and the input one,
	///	that is, the distance between their farthest points.
	/// This method calls base class' implementation.
    /// </summary>
    /// <param name="segment">[IN] The line segment the distance will be measured to.</param>
    /// <returns>
    /// A floating point value containing the maximum distance between both line segments.
    /// </returns>
    inline float_q MaxDistance(const QBaseLineSegment<VectorType> &segment) const
    {
		return QLineSegment<VectorType>::MaxDistance(segment);
    }

    /// <summary>
	/// Given an input vector (which represents a point), this method returns the maximum distance between this and
	/// the segment, that is, the distance between the input point and the farthest point lying into the segment...
	/// ...and this will be one of the segment endpoints!.
	/// Please note the above is correct only when the point lies outside the segment; if it's inside the segment,
	/// the maximum distance equals to 0.
	/// This method calls base class' implementation.
	/// </summary>
	/// <param name="vPoint">[IN] The point the distance will be measured to.</param>
    /// <returns>
    /// A floating point value containing the maximum distance between the resident line segment and a point provided.
    /// </returns>
    inline float_q MaxDistance(const VectorType &vPoint) const
    {
		return QLineSegment<VectorType>::MaxDistance(vPoint);
    }

    /// <summary>
    /// Calculates the minimum distance between the resident line segment and a plane provided.
    /// </summary>
    /// <param name="plane">[IN] The plane we want to know the minimum distance from the line segment.</param>
    /// <returns>
    /// A floating point value containing the minimum distance between the resident line segment and a plane provided.
    /// </returns>
    /// <remarks>
    /// The plane must be normalized to obtain correct result.
    /// </remarks>
    inline float_q MinDistance(const QBasePlane &plane) const
    {
        const float_q &fDistA = plane.As<QPlane>().PointDistance(this->A);
        const float_q &fDistB = plane.As<QPlane>().PointDistance(this->B);

        return std::min(fDistA, fDistB);
    }

	/// <summary>
	/// Given an input line segment, this method returns the minimum distance between this and the input one,
	///	that is, the distance between their closest points.
	/// This method calls base class' implementation.
	/// </summary>
	/// <param name="segment">[IN] The line segment the distance will be measured to.</param>
	/// <returns>
	/// A floating point value (always nonnegative) which represents the minimum distance between the two segments.
	/// </returns>
	inline float_q MinDistance(const QBaseLineSegment<VectorType> &segment) const
	{
		return QLineSegment<VectorType>::MinDistance(segment);
	}

	/// <summary>
	/// Given an input vector (which represents a point), this method returns the minimum distance between this and
	/// the segment, that is, the distance between the input point and the closest point lying into the segment.
	/// This method calls base class' implementation.
	/// </summary>
	/// <param name="vPoint">[IN] The point the distance will be measured to.</param>
	/// <returns>
	/// A floating point value (always nonnegative) which represents the minimum distance between point and segment.
	/// </returns>
	inline float_q MinDistance(const VectorType& vPoint) const
	{
		return QLineSegment<VectorType>::MinDistance(vPoint);
	}

    /// <summary>
    /// Projects the resident line segment over the plane provided.
    /// </summary>
    /// <param name="plane">[IN] The plane where we want to project the resident line segment.</param>
    /// <remarks>
    /// The plane must be normalized to obtain correct result.
    /// </remarks>
    inline void ProjectToPlane(const QBasePlane &plane)
    {
        plane.As<QPlane>().PointProjection(this->A, this->A);
        plane.As<QPlane>().PointProjection(this->B, this->B);
    }

    /// <summary>
    /// Projects the resident line segment over the plane provided. The projection is stored in the line segment provided.
    /// </summary>
    /// <param name="plane">[IN] The plane where we want to project the resident line segment.</param>
    /// <param name="segment">[OUT] The line segment where to store the result of projection.</param>
    inline void ProjectToPlane (const QBasePlane &plane, QBaseLineSegment<VectorType> &segment) const
    {
        plane.As<QPlane>().PointProjection(this->A, segment.A);
        plane.As<QPlane>().PointProjection(this->B, segment.B);
    }

    /// <summary>
    /// Checks the relation between resident line segment and the provided plane.
    /// Since a plane divides space into two parts, we can check if the "distances" (allowing distances having sign) from
    /// the plane to both end points of line segment are 0, or have diferent sign, in which case the segment crosses the plane.
    /// If distances from plane to both end points have the same sign, all line segment is in the same
    /// side of the space, and they haven't a common point.
    ///
    /// </summary>
    /// <remarks>
    /// Note that if only one end point of the resident line segment lies on the plane, we consider that it is
    /// in one of the sides in which the plane divides the space.
    /// </remarks>
    /// <param name="plane">[IN] The plane we want check the relation with resident line segment.</param>
    /// <returns>
    /// An integer value like follows:
    ///     0 (Contained): All the line segment lies on plane.
    ///     1 (PositiveSide): The line segment is fully contained in the positive side of the space defined by the plane.
    ///     2 (NegativeSide): The line segment is fully contained in the negative side of the space defined by the plane.
    ///     3 (BothSides): One end point of the line segment is in the positive side and the other is in the negative one.
    /// We consider "positive part of the space" the locus of points which verifies \f$ Ax + By + Cz + D > 0 \f$.
    /// </returns>
    EQSpaceRelation SpaceRelation(const QBasePlane &plane)
    {
        const float_q &distA = plane.a * this->A.x + plane.b * this->A.y + plane.c * this->A.z + plane.d;
        const float_q &distB = plane.a * this->B.x + plane.b * this->B.y + plane.c * this->B.z + plane.d;

        if (SQFloat::IsZero(distA) && SQFloat::IsZero(distB))
            return EQSpaceRelation::E_Contained;
        else if ( SQFloat::IsGreaterOrEquals(distA, SQFloat::_0) && SQFloat::IsGreaterOrEquals(distB, SQFloat::_0) )
            return EQSpaceRelation::E_PositiveSide;
        else if ( SQFloat::IsLowerOrEquals(distA, SQFloat::_0) && SQFloat::IsLowerOrEquals(distB, SQFloat::_0) )
            return EQSpaceRelation::E_NegativeSide;
        else
            return EQSpaceRelation::E_BothSides;
    }

    /// <summary>
    /// Transforms the resident line segment.
    /// </summary>
    /// <param name="transformation">[IN] 4x3 Matrix which contains the transformation.</param>
    inline void Transform(const QTransformationMatrix<QMatrix4x3> &transformation)
    {
        SQPoint::Transform(transformation, this->template AsPtr<VectorType>(), 2);
    }

    /// <summary>
    /// Transforms the resident line segment.
    /// </summary>
    /// <param name="transformation">[IN] 4x3 Matrix which contains the transformation.</param>
    /// <param name="outSegment">[OUT] Line segment to store the transformed one.</param>
    inline void Transform(const QTransformationMatrix<QMatrix4x3> &transformation, QBaseLineSegment<VectorType> &outSegment) const
    {
        outSegment = *this;
        outSegment.template As<QLineSegment3D<VectorType> >().Transform(transformation);
    }

    /// <summary>
    /// Transforms the resident line segment.
    /// </summary>
    /// <param name="transformation">[IN] 4x4 Matrix which contains the transformation.</param>
    inline void Transform(const QTransformationMatrix<QMatrix4x4> &transformation)
    {
        SQPoint::Transform(transformation, this->template AsPtr<VectorType>(), 2);
    }

    /// <summary>
    /// Transforms the resident line segment.
    /// </summary>
    /// <param name="transformation">[IN] 4x4 Matrix which contains the transformation.</param>
    /// <param name="outSegment">[OUT] Line segment to store the transformed one.</param>
    inline void Transform(const QTransformationMatrix<QMatrix4x4> &transformation, QBaseLineSegment<VectorType> &outSegment) const
    {
        outSegment = *this;
        outSegment.template As<QLineSegment3D<VectorType> >().Transform(transformation);
    }

    /// <summary>
    /// Transforms the resident line segment.
    /// </summary>
    /// <param name="spaceConversion">[IN] Space conversion matrix which contains the transformation.</param>
    inline void Transform(const QSpaceConversionMatrix &spaceConversion)
    {
        SQPoint::Transform(spaceConversion, this->template AsPtr<VectorType>(), 2);
    }

    /// <summary>
    /// Transforms the resident line segment.
    /// </summary>
    /// <param name="spaceConversion">[IN] Space conversion matrix which contains the transformation.</param>
    /// <param name="outSegment">[OUT] Line segment to store the transformed one.</param>
    inline void Transform(const QSpaceConversionMatrix &spaceConversion, QBaseLineSegment<VectorType> &outSegment) const
    {
        outSegment = *this;
        outSegment.template As<QLineSegment3D<VectorType> >().Transform(spaceConversion);
    }

    /// <summary>
    /// Transforms the resident line segment with the transformation contained in the dual quaternion provided.
    /// </summary>
    /// <param name="transformation">[IN] The dual quaternion which contains the transformation.</param>
    inline void Transform(const QDualQuaternion &transformation)
    {
        this->A.Transform(transformation);
        this->B.Transform(transformation);
    }

    /// <summary>
    /// Transforms the resident line segment with the transformation contained in the dual quaternion provided, acting
    /// the "A" end point as pivot of rotation. The resultant line segment is stored in the line segment provided.
    /// </summary>
    /// <param name="transformation">[IN] The dual quaternion which contains the transformation.</param>
    /// <param name="outSegment">[OUT] Line segment to store the transformed one.</param>
    inline void Transform(const QDualQuaternion &transformation, QBaseLineSegment<VectorType> &outSegment) const
    {
        outSegment = *this;
        outSegment.template As<QLineSegment3D<VectorType> >().Transform(transformation);
    }

    /// <summary>
    /// Transforms the resident line segment using a pivot.
    /// </summary>
    /// <param name="transformation">[IN] 4x3 Matrix which contains the transformation.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the rotation.</param>
    inline void TransformWithPivot(const QTransformationMatrix<QMatrix4x3> &transformation, const VectorType &vPivot)
    {
        SQPoint::TransformWithPivot(transformation, vPivot, this->template AsPtr<VectorType>(), 2);
    }

    /// <summary>
    /// Transforms the resident line segment using a pivot.
    /// </summary>
    /// <param name="transformation">[IN] 4x3 Matrix which contains the transformation.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the rotation.</param>
    /// <param name="outSegment">[OUT] Line segment to store the transformed one.</param>
    inline void TransformWithPivot(const QTransformationMatrix<QMatrix4x3> &transformation, const VectorType &vPivot,
                                   QBaseLineSegment<VectorType> &outSegment) const
    {
        outSegment = *this;
        outSegment.template As<QLineSegment3D<VectorType> >().TransformWithPivot(transformation, vPivot);
    }

    /// <summary>
    /// Transforms the resident line segment using a pivot.
    /// </summary>
    /// <param name="transformation">[IN] 4x4 Matrix which contains the transformation.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the rotation.</param>
    inline void TransformWithPivot(const QTransformationMatrix<QMatrix4x4> &transformation, const VectorType &vPivot)
    {
        SQPoint::TransformWithPivot(transformation, vPivot, this->template AsPtr<VectorType>(), 2);
    }

    /// <summary>
    /// Transforms the resident line segment using a pivot.
    /// </summary>
    /// <param name="transformation">[IN] 4x4 Matrix which contains the transformation.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the rotation.</param>
    /// <param name="outSegment">[OUT] Line segment to store the transformed one.</param>
    inline void TransformWithPivot(const QTransformationMatrix<QMatrix4x4> &transformation, const VectorType &vPivot,
                                   QBaseLineSegment<VectorType> &outSegment) const
    {
        outSegment = *this;
        outSegment.template As<QLineSegment3D<VectorType> >().TransformWithPivot(transformation, vPivot);
    }

    /// <summary>
    /// Transforms the resident line segment with the transformation contained in the dual quaternion provided using a pivot.
    /// </summary>
    /// <param name="transformation">[IN] The dual quaternion which contains the transformation.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the rotation.</param>
    inline void TransformWithPivot(const QDualQuaternion &transformation, const VectorType &vPivot)
    {
        this->A -= vPivot;
        this->B -= vPivot;

        this->A.Transform(transformation);
        this->B.Transform(transformation);

        this->A += vPivot;
        this->B += vPivot;
    }

    /// <summary>
    /// Transforms the resident line segment with the transformation contained in the dual quaternion provided using a pivot.
    /// The resultant line segment is stored in the line segment provided.
    /// </summary>
    /// <param name="transformation">[IN] The dual quaternion which contains the transformation.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the rotation.</param>
    /// <param name="outSegment">[OUT] Line segment to store the transformed one.</param>
    inline void TransformWithPivot(const QDualQuaternion &transformation, const VectorType &vPivot, QLineSegment3D<VectorType> &outSegment) const
    {
        outSegment = *this;
        outSegment.template As<QLineSegment3D<VectorType> >().TransformWithPivot(transformation, vPivot);
    }

	/// <summary>
	/// Translates the line segment.
	/// </summary>
    /// <param name="vTranslation">[IN] Vector that contains the translation to be applied.</param>
    inline void Translate(const QBaseVector3 &vTranslation)
    {
        SQPoint::Translate(vTranslation, this->template AsPtr<VectorType>(), 2);
    }

	/// <summary>
	/// Translates the line segment. Translated line segment will be stored in the line segment received as parameter.
	/// </summary>
    /// <param name="vTranslate">[IN] Vector that contains the translation to be applied.</param>
    /// <param name="outputLineSegment">[OUT] Line segment that will store the translated line segment.</param>
    inline void Translate(const QBaseVector3 &vTranslate, QBaseLineSegment<VectorType> &outputLineSegment) const
    {
        outputLineSegment = *this;
        outputLineSegment.template As<QLineSegment3D<VectorType> >().Translate(vTranslate);
    }

	/// <summary>
	/// Translates the line segment.
	/// </summary>
    /// <param name="fTranslationX">[IN] Scalar that contains the translation on X axis.</param>
    /// <param name="fTranslationY">[IN] Scalar that contains the translation on Y axis.</param>
    /// <param name="fTranslationZ">[IN] Scalar that contains the translation on Z axis.</param>
    inline void Translate(const float_q &fTranslationX, const float_q &fTranslationY, const float_q &fTranslationZ)
    {
        SQPoint::Translate(fTranslationX, fTranslationY, fTranslationZ, this->template AsPtr<VectorType>(), 2);
    }

	/// <summary>
	/// Translates the line segment. Translated line segment will be stored in the line segment received as parameter.
	/// </summary>
    /// <param name="fTranslationX">[IN] Scalar that contains the translation on X axis.</param>
    /// <param name="fTranslationY">[IN] Scalar that contains the translation on Y axis.</param>
    /// <param name="fTranslationZ">[IN] Scalar that contains the translation on Z axis.</param>
    /// <param name="outSegment">[OUT] Line segment that will store the translated line segment.</param>
    inline void Translate(const float_q& fTranslationX, const float_q& fTranslationY, const float_q& fTranslationZ,
                          QBaseLineSegment<VectorType>& outSegment) const
    {
        outSegment = *this;
        outSegment.template As<QLineSegment3D<VectorType> >().Translate(fTranslationX, fTranslationY, fTranslationZ);
    }

	/// <summary>
	/// Translates the line segment.
	/// </summary>
    /// <param name="translation">[IN] 4x3 Matrix which contains the translation to be applied.</param>
    inline void Translate(const QTranslationMatrix<QMatrix4x3> &translation)
    {
        SQPoint::Translate(translation, this->template AsPtr<VectorType>(), 2);
    }

	/// <summary>
	/// Translates the line segment.
	/// </summary>
    /// <param name="translation">[IN] 4x4 Matrix which contains the translation to be applied.</param>
    inline void Translate(const QTranslationMatrix<QMatrix4x4> &translation)
    {
        SQPoint::Translate(translation, this->template AsPtr<VectorType>(), 2);
    }

	/// <summary>
	/// Translates the line segment.
	/// </summary>
    /// <param name="translation">[IN] 4x3 Matrix which contains the translation to be applied.</param>
    /// <param name="outSegment">[OUT] Line segment that will store the translated line segment.</param>
    inline void Translate(const QTranslationMatrix<QMatrix4x3> &translation, QBaseLineSegment<VectorType> &outSegment) const
    {
        outSegment = *this;
        outSegment.template As<QLineSegment3D<VectorType> >().Translate(translation);
    }

	/// <summary>
	/// Translates the line segment.
	/// </summary>
    /// <param name="translation">[IN] 4x4 Matrix which contains the translation to be applied.</param>
    /// <param name="outSegment">[OUT] Line segment that will store the translated line segment.</param>
    inline void Translate (const QTranslationMatrix<QMatrix4x4> &translation, QBaseLineSegment<VectorType> &outSegment) const
    {
        outSegment = *this;
        outSegment.template As<QLineSegment3D<VectorType> >().Translate(translation);
    }

	/// <summary>
	/// Rotates the line segment.
	/// </summary>
    /// <param name="qRotation">[IN] Quaternion that represents the rotation.</param>
    inline void Rotate(const QQuaternion &qRotation)
    {
        SQPoint::Rotate(qRotation, this->template AsPtr<VectorType>(), 2);
    }

	/// <summary>
	/// Rotates the line segment. Rotated line segment will be stored in the line segment received as parameter.
	/// </summary>
    /// <param name="qRotation">[IN] Quaternion that represents the rotation.</param>
    /// <param name="outSegment">[OUT] Line segment that will store the rotated line segment.</param>
    inline void Rotate(const QQuaternion &qRotation, QBaseLineSegment<VectorType> &outSegment) const
    {
        outSegment = *this;
        outSegment.template As<QLineSegment3D<VectorType> >().Rotate(qRotation);
    }

	/// <summary>
	/// Rotates the line segment.
	/// </summary>
    /// <param name="rotation">[IN] Matrix which contains the rotation to be applied.</param>
    inline void Rotate(const QRotationMatrix3x3 &rotation)
    {
        SQPoint::Rotate(rotation, this->template AsPtr<VectorType>(), 2);
    }

	/// <summary>
	/// Rotates the line segment.
	/// </summary>
    /// <param name="rotation">[IN] Matrix which contains the rotation to be applied.</param>
    /// <param name="outSegment">[OUT] Line segment that will store the rotated line segment.</param>
    inline void Rotate(const QRotationMatrix3x3 &rotation, QBaseLineSegment<VectorType> &outSegment) const
    {
        outSegment = *this;
        outSegment.template As<QLineSegment3D<VectorType> >().Rotate(rotation);
    }

	/// <summary>
	/// Rotates the line segment using a pivot.
	/// </summary>
    /// <param name="qRotation">[IN] Quaternion that represents the rotation.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the rotation.</param>
    inline void RotateWithPivot(const QQuaternion &qRotation, const VectorType &vPivot)
    {
        SQPoint::RotateWithPivot(qRotation, vPivot, this->template AsPtr<VectorType>(), 2);
    }

	/// <summary>
	/// Rotates the line segment using a pivot. Rotated line segment will be stored in the line segment received as parameter.
	/// </summary>
    /// <param name="qRotation">[IN] Quaternion that represents the rotation.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the rotation.</param>
    /// <param name="outSegment">[OUT] Line segment that will store the rotated line segment.</param>
    inline void RotateWithPivot(const QQuaternion &qRotation, const VectorType &vPivot, QBaseLineSegment<VectorType> &outSegment) const
    {
        outSegment = *this;
        outSegment.template As<QLineSegment3D<VectorType> >().RotateWithPivot(qRotation, vPivot);
    }

	/// <summary>
	/// Rotates the line segment using a pivot.
	/// </summary>
    /// <param name="rotation">[IN] Matrix which contains the rotation to be applied.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the rotation.</param>
    inline void RotateWithPivot(const QRotationMatrix3x3 &rotation, const VectorType &vPivot)
    {
        SQPoint::RotateWithPivot(rotation, vPivot, this->template AsPtr<VectorType>(), 2);
    }

	/// <summary>
	/// Rotates the line segment using a pivot.
	/// </summary>
    /// <param name="rotation">[IN] Matrix which contains the rotation to be applied.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the rotation.</param>
    /// <param name="outSegment">[OUT] Line segment that will store the rotated line segment.</param>
    inline void RotateWithPivot(const QRotationMatrix3x3 &rotation, const VectorType &vPivot,
                                QBaseLineSegment<VectorType> &outSegment) const
    {
        outSegment = *this;
        outSegment.template As<QLineSegment3D<VectorType> >().RotateWithPivot(rotation, vPivot);
    }

 	/// <summary>
	/// Scales the line segment.
	/// </summary>
    /// <param name="vScale">[IN] Vector that contains the scale to be applied.</param>
    inline void Scale(const VectorType &vScale)
    {
        SQPoint::Scale(vScale, this->template AsPtr<VectorType>(), 2);
    }

 	/// <summary>
	/// Scales the line segment. Scaled line segment will be stored in the line segment received as parameter.
	/// </summary>
    /// <param name="vScale">[IN] Vector that contains the scale to be applied.</param>
    /// <param name="outSegment">[OUT] Line segment that will store the scaled line segment.</param>
    inline void Scale(const VectorType &vScale, QBaseLineSegment<VectorType> &outSegment) const
    {
        outSegment = *this;
        outSegment.template As<QLineSegment3D<VectorType> >().Scale(vScale);
    }

 	/// <summary>
	/// Scales the line segment.
	/// </summary>
    /// <param name="fScaleX">[IN] Scalar that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar that contains the scale on Y axis.</param>
    /// <param name="fScaleZ">[IN] Scalar that contains the scale on Z axis.</param>
    inline void Scale(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ)
    {
        SQPoint::Scale(fScaleX, fScaleY, fScaleZ, this->template AsPtr<VectorType>(), 2);
    }

 	/// <summary>
	/// Scales the line segment. Scaled line segment will be stored in the line segment received as parameter.
	/// </summary>
    /// <param name="fScaleX">[IN] Scalar that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar that contains the scale on Y axis.</param>
    /// <param name="fScaleZ">[IN] Scalar that contains the scale on Z axis.</param>
    /// <param name="outSegment">[OUT] Line segment that will store the scaled line segment.</param>
    inline void Scale(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ, QBaseLineSegment<VectorType> &outSegment) const
    {
        outSegment = *this;
        outSegment.template As<QLineSegment3D<VectorType> >().Scale(fScaleX, fScaleY, fScaleZ);
    }

 	/// <summary>
	/// Scales the line segment.
	/// </summary>
    /// <param name="scale">[IN] Matrix which contains the scale to be applied.</param>
    inline void Scale(const QScaleMatrix3x3& scale)
    {
        SQPoint::Scale(scale, this->template AsPtr<VectorType>(), 2);
    }

 	/// <summary>
	/// Scales the line segment.
	/// </summary>
    /// <param name="scale">[IN] Matrix which contains the scale to be applied.</param>
    /// <param name="outSegment">[OUT] Line segment that will store the scaled line segment.</param>
    inline void Scale(const QScaleMatrix3x3 &scale, QBaseLineSegment<VectorType> &outSegment) const
    {
        outSegment = *this;
        outSegment.template As<QLineSegment3D<VectorType> >().Scale(scale);
    }

 	/// <summary>
	/// Scales the line segment using a pivot.
	/// </summary>
    /// <param name="vScale">[IN] Vector that contains the scale to be applied.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    inline void ScaleWithPivot(const VectorType &vScale, const VectorType &vPivot)
    {
        SQPoint::ScaleWithPivot(vScale, vPivot, this->template AsPtr<VectorType>(), 2);
    }

 	/// <summary>
	/// Scales the line segment using a pivot. Scaled line segment will be stored in the line segment received as parameter.
	/// </summary>
    /// <param name="vScale">[IN] Vector that contains the scale to be applied.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    /// <param name="outSegment">[OUT] Line segment that will store the scaled line segment.</param>
    inline void ScaleWithPivot(const VectorType &vScale, const VectorType &vPivot, QBaseLineSegment<VectorType> &outSegment) const
    {
        outSegment = *this;
        outSegment.template As<QLineSegment3D<VectorType> >().ScaleWithPivot(vScale, vPivot);
    }

 	/// <summary>
	/// Scales the line segment using a pivot.
	/// </summary>
    /// <param name="fScaleX">[IN] Scalar that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar that contains the scale on Y axis.</param>
    /// <param name="fScaleZ">[IN] Scalar that contains the scale on Z axis.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    inline void ScaleWithPivot(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ, const VectorType &vPivot)
    {
        SQPoint::ScaleWithPivot(fScaleX, fScaleY, fScaleZ, vPivot, this->template AsPtr<VectorType>(), 2);
    }

 	/// <summary>
	/// Scales the line segment using a pivot. Scaled line segment will be stored in the line segment received as parameter.
	/// </summary>
    /// <param name="fScaleX">[IN] Scalar that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar that contains the scale on Y axis.</param>
    /// <param name="fScaleZ">[IN] Scalar that contains the scale on Z axis.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    /// <param name="outSegment">[OUT] Line segment that will store the scaled line segment.</param>
    inline void ScaleWithPivot(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ, const VectorType &vPivot,
                               QBaseLineSegment<VectorType> &outSegment) const
    {
        outSegment = *this;
        outSegment.template As<QLineSegment3D<VectorType> >().ScaleWithPivot(fScaleX, fScaleY, fScaleZ, vPivot);
    }

 	/// <summary>
	/// Scales the line segment using a pivot.
	/// </summary>
    /// <param name="scale">[IN] Matrix which contains the scale to be applied.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    inline void ScaleWithPivot(const QScaleMatrix3x3& scale, const VectorType& vPivot)
    {
        SQPoint::ScaleWithPivot(scale, vPivot, this->template AsPtr<VectorType>(), 2);
    }

 	/// <summary>
	/// Scales the line segment using a pivot.
	/// </summary>
    /// <param name="scale">[IN] Matrix which contains the scale to be applied.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    /// <param name="outSegment">[OUT] Line segment that will store the scaled line segment.</param>
    inline void ScaleWithPivot(const QScaleMatrix3x3 &scale, const VectorType &vPivot, QBaseLineSegment<VectorType> &outSegment) const
    {
        outSegment = *this;
        outSegment.template As<QLineSegment3D<VectorType> >().ScaleWithPivot(scale, vPivot);
    }

protected:

    // Calculates if two points are in the same side of a line segment. Can be used to know
    // if a point is inside or outside a plane convex polygon, being point and polygon coplanars.
    // The point must be in the same side of every polygon edge than any
    // other polygon vertex not included in the analized edge.
    template <class VectorTypeParam>
    inline bool PointsInSameSideOfLine(const VectorTypeParam &vPoint1, const VectorTypeParam &vPoint2,
                                       const VectorTypeParam &vLine1, const VectorTypeParam &vLine2) const
    {
        VectorTypeParam vLine(vLine2 - vLine1);
        VectorTypeParam vCP1;
        VectorTypeParam vCP2;

        vLine.CrossProduct(vPoint1 - vLine1, vCP1);
        vLine.CrossProduct(vPoint2 - vLine1, vCP2);

        return SQFloat::IsPositive(vCP1.DotProduct(vCP2));
    }

    // Calculates if a point is inside the triangle provided applying barycentric technique.
    template <class VectorTypeParam>
    inline bool PointInsideTriangle(const QBaseTriangle<VectorTypeParam> &triangle, const VectorTypeParam &vPoint) const
    {
        // Compute vectors
        const VectorTypeParam &v0(triangle.C - triangle.A);
        const VectorTypeParam &v1(triangle.B - triangle.A);
        const VectorTypeParam &v2(vPoint - triangle.A);

        // Compute dot products
        const float_q &fDot00 = v0.DotProduct(v0);
        const float_q &fDot01 = v0.DotProduct(v1);
        const float_q &fDot02 = v0.DotProduct(v2);
        const float_q &fDot11 = v1.DotProduct(v1);
        const float_q &fDot12 = v1.DotProduct(v2);

        // Compute barycentric coordinates
        const float_q &fDenom = fDot00 * fDot11 - fDot01 * fDot01;

        QE_ASSERT(fDenom != SQFloat::_0)

        const float_q &fInvDenom = SQFloat::_1 / fDenom;

        const float_q &fU = (fDot11 * fDot02 - fDot01 * fDot12) * fInvDenom;
        const float_q &fV = (fDot00 * fDot12 - fDot01 * fDot02) * fInvDenom;

        // Check if point is in triangle
        return SQFloat::IsPositive(fU) && SQFloat::IsPositive(fV) && SQFloat::IsLowerOrEquals(fU + fV, SQFloat::_1);
    }

    // Calculates if a point is inside the convex quadrilateral provided by the vertex A, B, C and D,
    // applying barycentric technique. Is supossed that quadrilateral vertex are consecutive.
    template <class VectorTypeParam>
    inline bool PointInsideQuadrilateral(const VectorTypeParam &vA, const VectorTypeParam &vB,
                                         const VectorTypeParam &vC, const VectorTypeParam &vD, const VectorTypeParam &vPoint) const
    {
        // Compute vectors
        const VectorTypeParam &v0(vC - vA);
        const VectorTypeParam &v1(vB - vA);
        const VectorTypeParam &v2(vPoint - vA);

        // Compute dot products
        const float_q &fDot00 = v0.DotProduct(v0);
        const float_q &fDot01 = v0.DotProduct(v1);
        const float_q &fDot02 = v0.DotProduct(v2);
        const float_q &fDot11 = v1.DotProduct(v1);
        const float_q &fDot12 = v1.DotProduct(v2);

        // Compute barycentric coordinates
        const float_q &fDenom = fDot00 * fDot11 - fDot01 * fDot01;

        QE_ASSERT(fDenom != SQFloat::_0)

        const float_q &fInvDenom = SQFloat::_1 / fDenom;

        const float_q &fU = (fDot11 * fDot02 - fDot01 * fDot12) * fInvDenom;
        const float_q &fV = (fDot00 * fDot12 - fDot01 * fDot02) * fInvDenom;

        // Check if point is in triangle
        if ( SQFloat::IsPositive(fU) && SQFloat::IsPositive(fV) && SQFloat::IsLowerOrEquals(fU + fV, SQFloat::_1) )
            return true;

        // Compute new vector
        const VectorTypeParam &v3(vD - vA);

        // Compute new dot products
        const float_q &fDot03 = v0.DotProduct(v3);
        const float_q &fDot33 = v3.DotProduct(v3);
        const float_q &fDot32 = v3.DotProduct(v2);

        // Compute new barycentric coordinates
        const float_q &fDenom2 = fDot00 * fDot33 - fDot03 * fDot03;

        QE_ASSERT(fDenom2 != SQFloat::_0)

        const float_q &fInvDenom2 = SQFloat::_1 / fDenom2;

        const float_q &fU2 = (fDot33 * fDot02 - fDot03 * fDot32) * fInvDenom2;
        const float_q &fV2 = (fDot00 * fDot32 - fDot03 * fDot02) * fInvDenom2;

        // Check if point is in triangle
        return SQFloat::IsPositive(fU2) && SQFloat::IsPositive(fV2) && SQFloat::IsLowerOrEquals(fU2 + fV2, SQFloat::_1);
    }

    // Calculates if two points are in the same side of a plane defined by 3 points.
    template <class VectorTypeParam>
    inline bool PointsInSameSideOfPlane(const VectorTypeParam &vPoint1, const VectorTypeParam &vPoint2,
                                        const VectorTypeParam &vA, const VectorTypeParam &vB, const VectorTypeParam &vC) const
    {
        QPlane p(vA, vB, vC);

        const float_q &distP1 = p.a * vPoint1.x + p.b * vPoint1.y + p.c * vPoint1.z + p.d;
        const float_q &distP2 = p.a * vPoint2.x + p.b * vPoint2.y + p.c * vPoint2.z + p.d;

        return SQFloat::IsPositive(distP1 * distP2);
    }

    // Calculates if two points are in the same side of a plane defined by 3 points.
    template <class VectorTypeParam>
    inline bool PointInsideHexahedron(const QBaseHexahedron<VectorTypeParam> &hexahedron, const VectorTypeParam &vPoint) const
    {
        return (PointsInSameSideOfPlane(vPoint, hexahedron.E, hexahedron.A, hexahedron.B, hexahedron.C) &&
                PointsInSameSideOfPlane(vPoint, hexahedron.A, hexahedron.E, hexahedron.F, hexahedron.G) &&
                PointsInSameSideOfPlane(vPoint, hexahedron.C, hexahedron.A, hexahedron.B, hexahedron.hexahedron) &&
                PointsInSameSideOfPlane(vPoint, hexahedron.A, hexahedron.B, hexahedron.C, hexahedron.G) &&
                PointsInSameSideOfPlane(vPoint, hexahedron.C, hexahedron.A, hexahedron.D, hexahedron.F) &&
                PointsInSameSideOfPlane(vPoint, hexahedron.A, hexahedron.C, hexahedron.D, hexahedron.F) );
    }

    // Checks if a segment intersects a cuadrilateral. It's supossed that A, B, C, D are consecutive
    // vertices of a cuadrilateral.
    template <class VectorTypeParam>
    bool CuadrilateralIntersection(const QLineSegment3D<VectorTypeParam> &segment,
                                   const VectorTypeParam &vA, const VectorTypeParam &vB,
                                   const VectorTypeParam &vC, const VectorTypeParam &vD) const
    {
        // Plane equation
        QPlane auxP(vA, vB, vC);

        // Line Segment don't intersects the cuadrilateral plane.
        if (!segment.Intersection(auxP))
            return false;

        // If both end points satisfy plane equation, the line segment lies on plane
        const float_q &fDot1 = auxP.a * segment.B.x + auxP.b * segment.B.y + auxP.c * segment.B.z + auxP.d;
        const float_q &fDot2 = auxP.a * segment.A.x + auxP.b * segment.A.y + auxP.c * segment.A.z + auxP.d;

        if (SQFloat::IsZero(fDot1) && SQFloat::IsZero(fDot2))
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

        QE_ASSERT(SQFloat::IsNotZero(fDot2 - fDot1))

        // The point which satisfies both line and plane equations.
        VectorTypeParam vAux = segment.A + (segment.B - segment.A) * fDot2/(fDot2 - fDot1);

        // For every edge, it tests if the intersection point is in the same side of each edge
        // than any other vextex (not of the edge). If it does, then it's inside the cuadrilateral,
        // otherwise it's outside.
        return PointInsideQuadrilateral(vA, vB, vC, vD, vAux);
    }

    // Computes the intersection between a line segment and a cuadrilateral. It's supossed that A, B, C, D are consecutive
    // vertices of a cuadrilateral.
    // Returns a value indicating the number of intersections (E_None, E_One, E_Two and E_Infinite)
    // Stores the closest intersection point to A end point of line segment in the vector provided.
    template <class VectorTypeParam>
    EQIntersections QuadrilateralIntersectionPoint(const QLineSegment3D<VectorTypeParam> &segment,
                                                   const VectorTypeParam &vA, const VectorTypeParam &vB,
                                                   const VectorTypeParam &vC, const VectorTypeParam &vD,
                                                   VectorTypeParam &vIntersection) const
    {
        VectorTypeParam vAux;
        return this->QuadrilateralIntersectionPoint(segment, vA, vB, vC, vD, vIntersection, vAux);
    }

    // Computes the intersection between a line segment and a cuadrilateral. It's supossed that A, B, C, D are consecutive
    // vertices of a cuadrilateral.
    // Returns a value indicating the number of intersections (E_None, E_One, E_Two and E_Infinite)
    // Stores the closest intersection point to A end point of line segment in the first vector provided, and the farthest intersection
    // point in the second one, if it exists.
    template <class VectorTypeParam>
    EQIntersections QuadrilateralIntersectionPoint(const QLineSegment3D<VectorTypeParam> &segment,
                                                   const VectorTypeParam &vA, const VectorTypeParam &vB,
                                                   const VectorTypeParam &vC, const VectorTypeParam &vD,
                                                   VectorTypeParam &vIntersection1, VectorTypeParam &vIntersection2) const
    {
        // Plane equation
        QPlane auxP(vA, vB, vC);
        VectorTypeParam vAux;

        const EQIntersections &value = segment.IntersectionPoint(auxP, vAux);

        if (value == EQIntersections::E_None) // Line Segment don't intersects the cuadrilateral plane.
            return EQIntersections::E_None;
        else if (value == EQIntersections::E_One) // Line segment has one intersection with quadrilateral plane
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
            const bool &bAIsInside = PointInsideQuadrilateral(vA, vB, vC, vD, segment.A);
            const bool &bBIsInside = PointInsideQuadrilateral(vA, vB, vC, vD, segment.B);

            if (bAIsInside && bBIsInside) // Both line segment end points are inside quadrilateral.
            {
                // A or B are vertex
                const bool &bAIsVertex = (segment.A == vA || segment.A == vB || segment.A == vC || segment.A == vD);
                const bool &bBIsVertex = (segment.B == vA || segment.B == vB || segment.B == vC || segment.B == vD);

                if (bAIsVertex && bBIsVertex) // Both endpoints are vertices of quadrilateral
                {
                    vIntersection1 = segment.A;
                    vIntersection2 = segment.B;
                    return EQIntersections::E_Two;
                }
                else if (bAIsVertex) // Only A endpoint is a vertex of quadrilateral
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
                else if (bBIsVertex)
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
                        if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vA, vB).MinDistance(segment.B))) // B is in vAvB edge (but not a vertex)
                            return EQIntersections::E_Infinite;
                        else if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vB, vC).MinDistance(segment.B)) || // B is in other edge (but not a vertex)
                                 SQFloat::IsZero(QLineSegment<VectorTypeParam>(vC, vD).MinDistance(segment.B)) ||
                                 SQFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(segment.B)))
                        {
                            vIntersection1 = segment.A;
                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                        else // B is not in an edge
                        {
                            vIntersection1 = segment.A;
                            return EQIntersections::E_One;
                        }
                    }
                    else if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vB, vC).MinDistance(segment.A))) // A is in vBvC edge (but not a vertex)
                    {
                        if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vB, vC).MinDistance(segment.B))) // B is in vBvC edge (but not a vertex)
                            return EQIntersections::E_Infinite;
                        else if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vA, vB).MinDistance(segment.B)) || // B is in other edge (but not a vertex)
                                 SQFloat::IsZero(QLineSegment<VectorTypeParam>(vC, vD).MinDistance(segment.B)) ||
                                 SQFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(segment.B)))
                        {
                            vIntersection1 = segment.A;
                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                        else // B is not in an edge
                        {
                            vIntersection1 = segment.A;
                            return EQIntersections::E_One;
                        }
                    }
                    else if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vC, vD).MinDistance(segment.A))) // A is in vCvD edge (but not a vertex)
                    {
                        if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vC, vD).MinDistance(segment.B))) // B is in vCvD edge (but not a vertex)
                            return EQIntersections::E_Infinite;
                        else if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vA, vB).MinDistance(segment.B)) || // B is in other edge (but not a vertex)
                                 SQFloat::IsZero(QLineSegment<VectorTypeParam>(vB, vC).MinDistance(segment.B)) ||
                                 SQFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(segment.B)))
                        {
                            vIntersection1 = segment.A;
                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                        else // B is not in an edge
                        {
                            vIntersection1 = segment.A;
                            return EQIntersections::E_One;
                        }
                    }
                    else if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(segment.A))) // A is in vDvA edge (but not a vertex)
                    {
                        if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(segment.B))) // B is in vDvA edge (but not a vertex)
                            return EQIntersections::E_Infinite;
                        else if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vA, vB).MinDistance(segment.B)) || // B is in other edge (but not a vertex)
                                 SQFloat::IsZero(QLineSegment<VectorTypeParam>(vB, vC).MinDistance(segment.B)) ||
                                 SQFloat::IsZero(QLineSegment<VectorTypeParam>(vC, vD).MinDistance(segment.B)))
                        {
                            vIntersection1 = segment.A;
                            vIntersection2 = segment.B;
                            return EQIntersections::E_Two;
                        }
                        else // B is not in an edge
                        {
                            vIntersection1 = segment.A;
                            return EQIntersections::E_One;
                        }
                    }
		            else if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(segment.A))) // A is in DA quad edge (but not a vertex)
					{
						if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(segment.B))) // B is in DA quad edge (but not a vertex)
							return EQIntersections::E_Infinite;
						else if (SQFloat::IsZero(QLineSegment<VectorTypeParam>(vA, vB).MinDistance(segment.B)) || // B is in other edge (but not a vertex)
								 SQFloat::IsZero(QLineSegment<VectorTypeParam>(vB, vC).MinDistance(segment.B)) ||
								 SQFloat::IsZero(QLineSegment<VectorTypeParam>(vC, vD).MinDistance(segment.B)))
						{
							vIntersection1 = segment.A;
							vIntersection2 = segment.B;
							return EQIntersections::E_Two;
						}
						else // B is not in an edge
						{
							vIntersection1 = segment.A;
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
                        else // B is not in an edge
                            return EQIntersections::E_Infinite;
                    }
                }
            }
            else if (!bAIsInside && !bBIsInside) // Both line segment end points are outside quadrilateral.
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

                if (value2AB ==EQIntersections::E_One) // Line segment intersects AB edge of quadrilateral
                {
                    if (value2BC ==EQIntersections::E_One) // Line segment intersects BC edge of quadrilateral
                    {
                        if (vPointAB == vPointBC) // Are the same point
                        {
							if (value2CD ==EQIntersections::E_One) // Line segment intersects CD edge of quadrilateral
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
							else if (value2DA ==EQIntersections::E_One) // Line segment intersects DA edge of quadrilateral
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
                    else if (value2CD ==EQIntersections::E_One) // Line segment intersects CD edge of quadrilateral
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
                    else if (value2DA ==EQIntersections::E_One) // Line segment intersects DA edge of quadrilateral
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
                    else                  // Something is wrong: if end points of line segment are outside quadrilateral,
                        QE_ASSERT(false)  // line segment must intersects none, two or three edges, never only one.
                }
                else if (value2BC ==EQIntersections::E_One) // Line segment intersects BC edge of quadrilateral
                {
                    if (value2CD ==EQIntersections::E_One) // Line segment intersects CA edge of quadrilateral
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
                    else                  // Something is wrong: if end points of line segment are outside quadrilateral,
                        QE_ASSERT(false)  // line segment must intersects none, two or three edges, never only one.
                }
                else if (value2CD ==EQIntersections::E_One) // Line segment intersects CD edge of quadrilateral
                {
                    if (value2DA ==EQIntersections::E_One) // Line segment intersects DA edge of quadrilateral
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
                    else                  // Something is wrong: if end points of line segment are outside quadrilateral,
                        QE_ASSERT(false)  // line segment must intersects none, two or three edges, never only one.
                }
				else if (value2DA ==EQIntersections::E_One) // Line segment intersects DA edge of quadrilateral
					QE_ASSERT(false)    // Something is wrong: if end points of line segment are outside quadrilateral,
				else                    // line segment must intersects none, two or three edges, never only one.
					return EQIntersections::E_None; // There are no intersections.
            }
            else // one line segment end point is inside and the other one is outside triangle.
            {
                if (bAIsInside) // segment.A is inside quadrilateral
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
                        else if (value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vC, vD), vAux)== EQIntersections::E_One)
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
                        else if (value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vD, vA), vAux)== EQIntersections::E_One)
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
                        else if (value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vA, vB), vAux)== EQIntersections::E_One)
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
                        else if (value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vB, vC), vAux)== EQIntersections::E_One)
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
                        else                  // Something is wrong, if one point is inside and the other is outside,
                            QE_ASSERT(false)  // there must be intersections.

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
                        else if (value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vB, vC), vAux) == EQIntersections::E_One)
                            vIntersection1 = vAux;
                        else if (value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vC, vD), vAux)== EQIntersections::E_One)
                            vIntersection1 = vAux;
                        else if (value2 = segment.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vD, vA), vAux)== EQIntersections::E_One)
                            vIntersection1 = vAux;
                        else                  // Something is wrong, if one point is inside and the other is outside,
                            QE_ASSERT(false)  // there must be intersections.

                        return EQIntersections::E_One;
                    }
                }
            }
        }
    }

    // Changes the coordinate system of a point to other system based in three normal
    // vectors and a point which is the origin.
    template <class VectorTypeParam>
    inline void ChangeCoordSys(const VectorTypeParam &vPoint, VectorTypeParam &vNewPoint,
                               const VectorTypeParam &vX, const VectorTypeParam &vY, const VectorTypeParam &vZ,
                               const VectorTypeParam &vO) const
    {
        vNewPoint.x = (vPoint.x-vO.x)*vX.x + (vPoint.y-vO.y)*vX.y + (vPoint.z-vO.z)*vX.z;
        vNewPoint.y = (vPoint.x-vO.x)*vY.x + (vPoint.y-vO.y)*vY.y + (vPoint.z-vO.z)*vY.z;
        vNewPoint.z = (vPoint.x-vO.x)*vZ.x + (vPoint.y-vO.y)*vZ.y + (vPoint.z-vO.z)*vZ.z;
    }

};


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QLINESEGMENT3D__
