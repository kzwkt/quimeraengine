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

	// CONSTANTS
    // ---------------
public:

    /// <summary>
    /// Unit segment lying on positive X axis (it's length equals 1).
    /// </summary>
	static const QLineSegment3D<VectorType> UnitLine;

    /// <summary>
    /// Zero segment lying in the coordinates center whose endpoints
	/// both equals to (0,0) and it's length equals 0.
    /// </summary>
	static const QLineSegment3D<VectorType> LineZero;


 	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
    inline QLineSegment3D() { }

    /// <summary>
    /// Constructor from two vectors.
    /// </summary>
    /// <param name="vA">[IN] Vector to define endpoint A.</param>
    /// <param name="vB">[IN] Vector to define endpoint B.</param>
	inline QLineSegment3D (const VectorType &vA, const VectorType &vB) : QLineSegment<VectorType>(vA,vB) { }

	/// <summary>
    /// Constructor from a line segment.
    /// </summary>
    /// <param name="ls">[IN] Line segment in which we want resident line segment is based on.</param>
	inline explicit QLineSegment3D (const QBaseLineSegment<VectorType> &ls) : QLineSegment<VectorType>(ls.A, ls.B)  { }

	// METHODS
	// ---------------
public:

    /// <summary>
    /// Assign operator. Assigns the provided line segment to the resident line segment.
    /// </summary>
    /// <param name="ls">[IN] The line segment to be assigned.</param>
    /// <returns>
    /// A reference to the modified line segment.
    /// </returns>
    inline QLineSegment3D& operator=(const QBaseLineSegment<VectorType> &ls)
    {
        QBaseLineSegment<VectorType>::operator=(ls);
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
    /// <param name="p">[IN] The plane we want check if intersects with resident line segment.</param>
    /// <returns>
    /// True if plane and line segment intersects, false otherwise.
    /// </returns>
    inline bool Intersection (const QBasePlane &p) const
    {
        const float_q &distA = p.a * this->A.x + p.b * this->A.y + p.c * this->A.z + p.d;

        if (QFloat::IsZero(distA))
            return true;

        const float_q &distB = p.a * this->B.x + p.b * this->B.y + p.c * this->B.z + p.d;

        if (QFloat::IsZero(distB))
            return true;

        else if ( QFloat::IsLessThan(distA * distB, QFloat::_0) )
            return true;
        else
            return false;
    }

    /// <summary>
    /// Checks if resident line segment intersects with the provided triangle.
    /// If one end point of the line segment lies on the triangle, or on an edge or vertex of the triangle,
    /// we consider there is an intersection.
    /// </summary>
    /// <param name="t">[IN] The triangle we want check if intersects with resident line segment.</param>
    /// <returns>
    /// True if triangle and line segment intersects, false otherwise.
    /// </returns>
    template <class VectorTypeParam>
    bool Intersection (const QBaseTriangle<VectorTypeParam> &t) const
    {
        // Calculates if segment intersects with the plane defined by the triangle.

        // This is necessary due to there are dot products between the normal vector to the plane (VectorTypeParam)
        // and the line segment end points, which are VectorType.
        QLineSegment3D<VectorTypeParam> lsAux(VectorTypeParam(this->A), VectorTypeParam(this->B));

        // Plane equation
        QPlane auxP(t.A, t.B, t.C);

        // Line Segment don't intersects the triangle plane.
        if (!lsAux.Intersection(auxP))
            return false;

        // If both end points satisfy plane equation, the line segment lies on plane
        const float_q &fDot1 = auxP.a * lsAux.B.x + auxP.b * lsAux.B.y + auxP.c * lsAux.B.z + auxP.d;
        const float_q &fDot2 = auxP.a * lsAux.A.x + auxP.b * lsAux.A.y + auxP.c * lsAux.A.z + auxP.d;

        if (QFloat::IsZero(fDot1) && QFloat::IsZero(fDot2))
        {
            // Both triangle and line segment are coplanars. If the line segment
            // intersects one of the edges of the triangle, then the line segment intersects the triangle.
            if (lsAux.QLineSegment<VectorTypeParam>::Intersection(QLineSegment<VectorTypeParam> (t.A, t.B)) ||
                lsAux.QLineSegment<VectorTypeParam>::Intersection(QLineSegment<VectorTypeParam> (t.B, t.C)) ||
                lsAux.QLineSegment<VectorTypeParam>::Intersection(QLineSegment<VectorTypeParam> (t.C, t.A)))
                return true;

            // If not, we check if segment is fully contained in the triangle
            // We only check "A" end point, since if "A" is inside, "B" must be inside too (see previus test).
            else if ( PointInsideTriangle(t, lsAux.A) )
                return true;
            else
                return false;
        }

        QE_ASSERT(QFloat::IsNotZero(fDot2 - fDot1));

        // The point which satisfies both line and plane equations.
        VectorTypeParam vAux = lsAux.A + (lsAux.B - lsAux.A) * fDot2/(fDot2 - fDot1);

        // For every edge, it tests if the intersection point is in the same side of each edge
        // than the third vextex. If it does, then it's inside the triangle, otherwise it's outside.
        if ( PointInsideTriangle(t, vAux) )
            return true;
        else
            return false;
    }

    /// <summary>
    /// Checks if resident line segment intersects with the provided sphere.
    /// If one end point of the line segment lies on the sphere surface, we consider that there is an intersection.
    /// </summary>
    /// <param name="orb">[IN] The sphere we want check if intersects with resident line segment.</param>
    /// <returns>
    /// True if sphere and line segment intersects, false otherwise.
    /// </returns>
    template <class VectorTypeParam>
    inline bool Intersection (const QBaseOrb<VectorTypeParam> &orb) const
    {
        return QLineSegment<VectorType>::Intersection(orb);
    }

    /// <summary>
    /// Checks if resident line segment intersects with the provided hexahedron.
    /// If one end point of the line segment lies on one of the hexahedron faces,
    /// we consider there is an intersection.
    /// </summary>
    /// <param name="h">[IN] The hexahedron we want check if intersects with resident line segment.</param>
    /// <returns>
    /// True if hexahedron and line segment intersects, false otherwise.
    /// </returns>
    template <class VectorTypeParam>
    bool Intersection (const QBaseHexahedron<VectorTypeParam> &h) const
    {
        QLineSegment3D<VectorTypeParam> lsAux(VectorTypeParam(this->A), VectorTypeParam(this->B));

        // Checks if there is an intersection with any face.
        if (CuadrilateralIntersection(lsAux, h.A, h.B, h.C, h.D) ||
            CuadrilateralIntersection(lsAux, h.E, h.F, h.G, h.H) ||
            CuadrilateralIntersection(lsAux, h.A, h.B, h.H, h.E) ||
            CuadrilateralIntersection(lsAux, h.B, h.C, h.G, h.H) ||
            CuadrilateralIntersection(lsAux, h.A, h.D, h.F, h.E) ||
            CuadrilateralIntersection(lsAux, h.C, h.D, h.F, h.G))
            return true;
        return false;
    }

	/// <summary>
	/// This method receives another line segment, and computes whether they intersect each other or not.
	/// </summary>
	/// <param name="vBaseLineSegment">[IN] The segment to be compared to.</param>
	/// <returns>
	/// True if they intersect each other (or if they were coincident), false if they don't.
	/// </returns>
	inline bool Intersection (const QBaseLineSegment<VectorType>& vBaseLineSegment) const
	{
		return QLineSegment<VectorType>::Intersection(vBaseLineSegment);
	}

	/// <summary>
	/// This method receives another line segment, and computes the intersection point between them,
	/// if it exists.
	/// </summary>
	/// <param name="vBaseLineSegment">[IN] The segment to be compared to.</param>
	/// <param name="vPoint">[OUT] The intersection point, if it exists.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the two line segments, and can take
    /// the following values: E_None, E_One and E_Infinite.
	/// </returns>
	/// <remarks>
	/// -If there's no intersection point, the output parameter used for storing that point won't be modified.
	/// -If segments are totally or parcially coincident only a single point will be stored in the output
	///  parameter, presumingly an endpoint belonging to one of the segments.
	/// </remarks>
	inline EQIntersections IntersectionPoint (const QBaseLineSegment<VectorType>& vBaseLineSegment, VectorType &vPoint) const
	{
		return QLineSegment<VectorType>::IntersectionPoint(vBaseLineSegment, vPoint);
	}

	/// <summary>
	/// This method receives an orb, computes the intersections with the resident line segment and stores the intersection point
	/// closest to A end point, if it exists.
	/// </summary>
	/// <param name="orb">[IN] The orb whose intersection point with resident line segment we want to check.</param>
    /// <param name="vPoint">[OUT] A vector where to store the intersection point closest to A end point.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the orb, and can take
    /// the following values: E_None, E_One and E_Two.
	/// </returns>
	/// <remarks>
	/// -If there's no intersection point, the output parameter used for storing that point won't be modified.
	/// -If there are two intersections, the output parameter stores only the closest to A end point.
	/// </remarks>
	EQIntersections IntersectionPoint (const QBaseOrb<VectorType> &orb, VectorType &vPoint) const
	{
        return QLineSegment<VectorType>::IntersectionPoint(orb, vPoint);
	}

    /// <summary>
	/// This method receives a orb, and computes and stores the points where the resident line segment intersects with it,
    /// if they exists.
	/// </summary>
	/// <param name="orb">[IN] The orb whose intersections with resident line segment we want to check.</param>
    /// <param name="vPoint1">[OUT] A vector where to store the intersection point closest to A end point.</param>
    /// <param name="vPoint2">[OUT] A vector where to store the intersection point farthest to A end point.</param>
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
	EQIntersections IntersectionPoint (const QBaseOrb<VectorType> &orb, VectorType &vPoint1, VectorType &vPoint2) const
	{
        return QLineSegment<VectorType>::IntersectionPoint(orb, vPoint1, vPoint2);
	}

    /// <summary>
	/// This method receives a plane, and computes the point where the resident line segment intersects with it,
    /// if it exists.
	/// </summary>
	/// <param name="plane">[IN] The plane whose intersection with resident line segment we want to check.</param>
	/// <param name="vPoint">[OUT] A vector where to store the intersection point.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the plane, and can take
    /// the following values: E_None, E_One and E_Infinite.
	/// </returns>
	/// <remarks>
	/// -If there's no intersection point or the line segment lies on plane, the output
    ///  parameter used for storing that point won't be modified.
	/// </remarks>
	EQIntersections IntersectionPoint (const QBasePlane &plane, VectorType &vPoint) const
	{
        const float_q &fDistA = plane.a * this->A.x + plane.b * this->A.y + plane.c * this->A.z + plane.d;
        const float_q &fDistB = plane.a * this->B.x + plane.b * this->B.y + plane.c * this->B.z + plane.d;

        const bool &bIsZeroDistA = QFloat::IsZero(fDistA);
        const bool &bIsZeroDistB = QFloat::IsZero(fDistB);

        if (bIsZeroDistA && !bIsZeroDistB) // A point lies on plane
        {
            vPoint = this->A;
            return EQIntersections::E_One;
        }
        else if (!bIsZeroDistA && bIsZeroDistB) // B point lies on plane
        {
            vPoint = this->B;
            return EQIntersections::E_One;
        }
        else if (bIsZeroDistA && bIsZeroDistB) // All line segment lies on plane
            return EQIntersections::E_Infinite;
        else if ( QFloat::IsLessThan(fDistA * fDistB, QFloat::_0) ) // Line segment intersects plane in a point
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

            QE_ASSERT(fDenom != QFloat::_0);

            vPoint = this->A + fDistA * (this->B - this->A)/fDenom;

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
	/// <param name="vPoint">[OUT] A vector where to store the intersection point closest to A end point.</param>
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
    template <class VectorTypeParam>
	EQIntersections IntersectionPoint (const QBaseTriangle<VectorTypeParam> &triangle, VectorTypeParam &vPoint) const
	{
		VectorTypeParam aux;
		return this->IntersectionPoint(triangle, vPoint, aux);
    }

    /// <summary>
	/// This method receives a triangle, and computes the points where the resident line segment intersects with it,
    /// if they exists.
	/// </summary>
	/// <param name="triangle">[IN] The triangle whose intersection with resident line segment we want to check.</param>
	/// <param name="vPoint1">[OUT] A vector where to store the intersection point closest to A end point of line segment.</param>
    /// <param name="vPoint2">[OUT] A vector where to store the intersection point farthest to A end point of line segment.</param>
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
    template <class VectorTypeParam>
	EQIntersections IntersectionPoint (const QBaseTriangle<VectorTypeParam> &triangle, VectorTypeParam &vPoint1, VectorTypeParam &vPoint2) const
	{
        // This is necessary due to there are dot products between the normal vector to the plane (VectorTypeParam)
        // and the line segment end points, which are VectorType.
        QLineSegment3D<VectorTypeParam> lsAux(VectorTypeParam(lsAux.A), VectorTypeParam(lsAux.B));

        // Plane equation
        QPlane auxP(triangle.A, triangle.B, triangle.C);

        VectorTypeParam vPoint;

        EQIntersections value = lsAux.IntersectionPoint(auxP, vPoint);

        if (value == EQIntersections::E_None) // Line segment don't intersects the triangle plane.
            return EQIntersections::E_None;
        else if (value == EQIntersections::E_One) // Line segment has one intersection with the triangle plane.
        {
            if (PointInsideTriangle(triangle, vPoint))
            {
                vPoint1 = vPoint;
                return EQIntersections::E_One;
            }
            else
                return EQIntersections::E_None;
        }
        else // Line segment and triangle are coplanars (value == EQIntersections::E_Infinite)
        {
            const bool &bAIsInside = PointInsideTriangle(triangle, lsAux.A);
            const bool &bBIsInside = PointInsideTriangle(triangle, lsAux.B);

            if (bAIsInside && bBIsInside) // Both line segment end points are inside triangle.
            {
				// A or B are vertex
				const bool &bAIsVertex = (lsAux.A == triangle.A || lsAux.A == triangle.B || lsAux.A == triangle.C);
				const bool &bBIsVertex = (lsAux.B == triangle.A || lsAux.B == triangle.B || lsAux.B == triangle.C);

				if (bAIsVertex && bBIsVertex) // Both endpoints are vertices of triangle
				{
					vPoint1 = lsAux.A;
					vPoint2 = lsAux.B;
					return EQIntersections::E_Two;
				}
				else if (bAIsVertex) // Only A endpoint is a vertex of triangle
				{
					vPoint1 = lsAux.A;

					if (QFloat::IsZero(QLineSegment<VectorTypeParam>(triangle.A, triangle.B).MinDistance(lsAux.B))) // B is in AB triangle edge
					{
						if (lsAux.A == triangle.A || lsAux.A == triangle.B) // A and B are in the same edge
							return EQIntersections::E_One;
						else
						{
							vPoint2 = lsAux.B;
							return EQIntersections::E_Two;
						}
					}
					else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(triangle.B, triangle.C).MinDistance(lsAux.B))) // B is in BC triangle edge
					{
						if (lsAux.A == triangle.B || lsAux.A == triangle.C) // A and B are in the same edge
							return EQIntersections::E_One;
						else
						{
							vPoint2 = lsAux.B;
							return EQIntersections::E_Two;
						}
					}
					else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(triangle.C, triangle.A).MinDistance(lsAux.B))) // B is in CA triangle edge
					{
						if (lsAux.A == triangle.C || lsAux.A == triangle.A) // A and B are in the same edge
							return EQIntersections::E_One;
						else
						{
							vPoint2 = lsAux.B;
							return EQIntersections::E_Two;
						}
					}
					else // B is not in an edge
					{
						vPoint1 = lsAux.A;
						return EQIntersections::E_One;
					}
				}
				else if (bBIsVertex)
				{
					if (QFloat::IsZero(QLineSegment<VectorTypeParam>(triangle.A, triangle.B).MinDistance(lsAux.A))) // A is in AB triangle edge
					{
						if (lsAux.B == triangle.A || lsAux.B == triangle.B) // A and B are in the same edge
						{
							vPoint1 = lsAux.B;
							return EQIntersections::E_One;
						}
						else
						{
							vPoint1 = lsAux.A;
							vPoint2 = lsAux.B;
							return EQIntersections::E_Two;
						}
					}
					else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(triangle.B, triangle.C).MinDistance(lsAux.A))) // B is in BC triangle edge
					{
						if (lsAux.B == triangle.B || lsAux.B == triangle.C) // A and B are in the same edge
						{
							vPoint1 = lsAux.B;
							return EQIntersections::E_One;
						}
						else
						{
							vPoint1 = lsAux.A;
							vPoint2 = lsAux.B;
							return EQIntersections::E_Two;
						}
					}
					else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(triangle.C, triangle.A).MinDistance(lsAux.A))) // B is in CA triangle edge
					{
						if (lsAux.B == triangle.C || lsAux.B == triangle.A) // A and B are in the same edge
						{
							vPoint1 = lsAux.B;
							return EQIntersections::E_One;
						}
						else
						{
							vPoint1 = lsAux.A;
							vPoint2 = lsAux.B;
							return EQIntersections::E_Two;
						}
					}
					else
					{
						vPoint1 = lsAux.B;
						return EQIntersections::E_One;
					}
				}
				else // Neither A or B are vertices of triangle
				{
					if (QFloat::IsZero(QLineSegment<VectorTypeParam>(triangle.A, triangle.B).MinDistance(lsAux.A))) // A is in AB triangle edge (but not a vertex)
					{
						if (QFloat::IsZero(QLineSegment<VectorTypeParam>(triangle.A, triangle.B).MinDistance(lsAux.B))) // B is in AB triangle edge (but not a vertex)
							return EQIntersections::E_Infinite;
						else if ( QFloat::IsZero(QLineSegment<VectorTypeParam>(triangle.B, triangle.C).MinDistance(lsAux.B)) || // B is in other edge (but not a vertex)
								  QFloat::IsZero(QLineSegment<VectorTypeParam>(triangle.C, triangle.A).MinDistance(lsAux.B)) )
						{
							vPoint1 = lsAux.A;
							vPoint2 = lsAux.B;
							return EQIntersections::E_Two;
						}
						else // B is not in an edge
						{
							vPoint1 = lsAux.A;
							return EQIntersections::E_One;
						}
					}
					else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(triangle.B, triangle.C).MinDistance(lsAux.A))) // A is in BC triangle edge (but not a vertex)
					{
						if (QFloat::IsZero(QLineSegment<VectorTypeParam>(triangle.B, triangle.C).MinDistance(lsAux.B))) // B is in BC triangle edge (but not a vertex)
							return EQIntersections::E_Infinite;
						else if ( QFloat::IsZero(QLineSegment<VectorTypeParam>(triangle.A, triangle.B).MinDistance(lsAux.B)) || // B is in other edge (but not a vertex)
								  QFloat::IsZero(QLineSegment<VectorTypeParam>(triangle.C, triangle.A).MinDistance(lsAux.B)) )
						{
							vPoint1 = lsAux.A;
							vPoint2 = lsAux.B;
							return EQIntersections::E_Two;
						}
						else // B is not in an edge
						{
							vPoint1 = lsAux.A;
							return EQIntersections::E_One;
						}
					}
					else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(triangle.C, triangle.A).MinDistance(lsAux.A))) // A is in CA triangle edge (but not a vertex)
					{
						if (QFloat::IsZero(QLineSegment<VectorTypeParam>(triangle.C, triangle.A).MinDistance(lsAux.B))) // B is in CA triangle edge (but not a vertex)
							return EQIntersections::E_Infinite;
						else if ( QFloat::IsZero(QLineSegment<VectorTypeParam>(triangle.A, triangle.B).MinDistance(lsAux.B)) || // B is in other edge (but not a vertex)
								  QFloat::IsZero(QLineSegment<VectorTypeParam>(triangle.B, triangle.C).MinDistance(lsAux.B)) )
						{
							vPoint1 = lsAux.A;
							vPoint2 = lsAux.B;
							return EQIntersections::E_Two;
						}
						else // B is not in an edge
						{
							vPoint1 = lsAux.A;
							return EQIntersections::E_One;
						}
					}
					else // A is not in an edge
					{
						if ( QFloat::IsZero(QLineSegment<VectorTypeParam>(triangle.A, triangle.B).MinDistance(lsAux.B)) || // B is in an edge (but not a vertex)
							 QFloat::IsZero(QLineSegment<VectorTypeParam>(triangle.B, triangle.C).MinDistance(lsAux.B)) ||
							 QFloat::IsZero(QLineSegment<VectorTypeParam>(triangle.C, triangle.A).MinDistance(lsAux.B)) )
						{
							vPoint1 = lsAux.B;
							return EQIntersections::E_One;
						}
						else // B is not in an edge
							return EQIntersections::E_Infinite;
					}
				}
			}
            else if (!bAIsInside && !bBIsInside) // Both line segment end points are outside triangle.
            {
                VectorTypeParam vPointAB, vPointBC, vPointCA;

                EQIntersections value2AB = lsAux.IntersectionPoint(QLineSegment3D<VectorTypeParam>(triangle.A, triangle.B), vPointAB);

                if (value2AB == EQIntersections::E_Infinite) // Line segment contains AB edge of triangle
                {
                    if  ( (triangle.A - lsAux.A).GetSquaredLength() < (triangle.B - lsAux.A).GetSquaredLength() ) // Returns closest point to A end point of line segment
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
                EQIntersections value2BC = lsAux.IntersectionPoint(QLineSegment3D<VectorTypeParam>(triangle.B, triangle.C), vPointBC);
                if (value2BC == EQIntersections::E_Infinite)
                {
                    if  ( (triangle.B - lsAux.A).GetSquaredLength() < (triangle.C - lsAux.A).GetSquaredLength() ) // Returns closest point to A end point of line segment
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
                EQIntersections value2CA = lsAux.IntersectionPoint(QLineSegment3D<VectorTypeParam>(triangle.C, triangle.A), vPointCA);
                if (value2CA == EQIntersections::E_Infinite)
                {
                    if  ( (triangle.C - lsAux.A).GetSquaredLength() < (triangle.A - lsAux.A).GetSquaredLength() ) // Returns closest point to A end point of line segment
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

                if (value2AB == EQIntersections::E_One) // Line segment intersects AB edge of triangle
                {
                    if (value2BC == EQIntersections::E_One) // Line segment intersects BC edge of triangle
                    {
                        if (vPointAB == vPointBC) // Are the same point
                        {
							if (value2CA ==EQIntersections::E_One) // Line segment intersects CA edge of triangle
							{
								if  ( (vPointAB - lsAux.A).GetSquaredLength() < (vPointCA - lsAux.A).GetSquaredLength() ) // Returns closest point to A end point of line segment
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
                            if  ( (vPointAB - lsAux.A).GetSquaredLength() < (vPointBC - lsAux.A).GetSquaredLength() ) // Returns closest point to A end point of line segment
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
                    else if (value2CA == EQIntersections::E_One) // Line segment intersects CA edge of triangle
                    {
                        if (vPointAB == vPointCA) // Are the same point
                        {
                            vPoint1 = vPointAB;
                            return EQIntersections::E_One;
                        }
                        else
                        {
                            if  ( (vPointAB - lsAux.A).GetSquaredLength() < (vPointCA - lsAux.A).GetSquaredLength() ) // Returns closest point to A end point of line segment
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
                else if (value2BC == EQIntersections::E_One) // Line segment intersects BC edge of triangle
                {
                    if (value2CA == EQIntersections::E_One) // Line segment intersects CA edge of triangle
                    {
                        if (vPointBC == vPointCA) // Are the same point
                        {
                            vPoint1 = vPointBC;
                            return EQIntersections::E_One;
                        }
                        else
                        {
                            if  ( (vPointBC - lsAux.A).GetSquaredLength() < (vPointCA - lsAux.A).GetSquaredLength() ) // Returns closest point to A end point of line segment
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
                        QE_ASSERT(false); // line segment must intersects none, two or the three edges, never only one.
                }

                // Line segment don't intersects triangle
                if (value2AB == EQIntersections::E_None && value2BC == EQIntersections::E_None && value2CA == EQIntersections::E_None)
                    return EQIntersections::E_None;
            }
            else // one line segment end point is inside and the other one is outside triangle.
            {
                VectorTypeParam vAux; // To store intersection points

				if (bAIsInside) // lsAux.A is inside triangle
				{
					if (lsAux.A == triangle.A) // lsAux.A is A triangle vertex
					{
						vPoint1 = lsAux.A;

						EQIntersections value2 = lsAux.IntersectionPoint(QLineSegment3D<VectorTypeParam>(triangle.B, triangle.C), vAux);
						if (value2 == EQIntersections::E_One) // ls intersects opposite edge
						{
							vPoint2 = vAux;
							return EQIntersections::E_Two;
						}
						else
							return EQIntersections::E_One; // ls only intersects triangle in A vertex
					}
					else if (lsAux.A == triangle.B) // lsAux.A is B triangle vertex
					{
						vPoint1 = lsAux.A;

						EQIntersections value2 = lsAux.IntersectionPoint(QLineSegment3D<VectorTypeParam>(triangle.C, triangle.A), vAux);
						if (value2 == EQIntersections::E_One) // ls intersects opposite edge
						{
							vPoint2 = vAux;
							return EQIntersections::E_Two;
						}
						else
							return EQIntersections::E_One; // ls only intersects triangle in B vertex
					}
					else if (lsAux.A == triangle.C) // lsAux.A is C triangle vertex
					{
						vPoint1 = lsAux.A;

						EQIntersections value2 = lsAux.IntersectionPoint(QLineSegment3D<VectorTypeParam>(triangle.B, triangle.A), vAux);
						if (value2 == EQIntersections::E_One) // ls intersects opposite edge
						{
							vPoint2 = vAux;
							return EQIntersections::E_Two;
						}
						else
							return EQIntersections::E_One;  // ls only intersects triangle in C vertex
					}
					else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(triangle.A, triangle.B).MinDistance(lsAux.A))) // lsAux.A is in AB triangle edge (but not a vertex)
					{
						vPoint1 = lsAux.A;

						// ls intersects other edges
						EQIntersections value2 = lsAux.IntersectionPoint(QLineSegment3D<VectorTypeParam>(triangle.B, triangle.C), vAux);
						if (value2 == EQIntersections::E_One)
						{
							if (vAux == triangle.B || vAux == triangle.C) // Both intersections are in the same edge
								return EQIntersections::E_One;

							vPoint2 = vAux;
							return EQIntersections::E_Two;
						}
						else if (value2 = lsAux.IntersectionPoint(QLineSegment3D<VectorTypeParam>(triangle.C, triangle.A), vAux) == EQIntersections::E_One)
						{
							if (vAux == triangle.C || vAux == triangle.A) // Both intersections are in the same edge
								return EQIntersections::E_One;

							vPoint2 = vAux;
							return EQIntersections::E_Two;
						}
						else
							return EQIntersections::E_One;
					}
					else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(triangle.B, triangle.C).MinDistance(lsAux.A))) // lsAux.A is in BC triangle edge (but not a vertex)
					{
						vPoint1 = lsAux.A;

						 // ls intersects other edges
						EQIntersections value2 = lsAux.IntersectionPoint(QLineSegment3D<VectorTypeParam>(triangle.A, triangle.B), vAux);
						if (value2 == EQIntersections::E_One)
						{
							if (vAux == triangle.A || vAux == triangle.B) // Both intersections are in the same edge
								return EQIntersections::E_One;

							vPoint2 = vAux;
							return EQIntersections::E_Two;
						}
						else if (value2 = lsAux.IntersectionPoint(QLineSegment3D<VectorTypeParam>(triangle.C, triangle.A), vAux) == EQIntersections::E_One)
						{
							if (vAux == triangle.C || vAux == triangle.A) // Both intersections are in the same edge
								return EQIntersections::E_One;

							vPoint2 = vAux;
							return EQIntersections::E_Two;
						}
						else
							return EQIntersections::E_One;
					}
					else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(triangle.C, triangle.A).MinDistance(lsAux.A))) // lsAux.A is in CA triangle edge (but not a vertex)
					{
						vPoint1 = lsAux.A;

						 // ls intersects other edges
						EQIntersections value2 = lsAux.IntersectionPoint(QLineSegment3D<VectorTypeParam>(triangle.B, triangle.C), vAux);
						if (value2 == EQIntersections::E_One)
						{
							if (vAux == triangle.B || vAux == triangle.C) // Both intersections are in the same edge
								return EQIntersections::E_One;

							vPoint2 = vAux;
							return EQIntersections::E_Two;
						}
						else if (value2 = lsAux.IntersectionPoint(QLineSegment3D<VectorTypeParam>(triangle.A, triangle.B), vAux) == EQIntersections::E_One)
						{
							if (vAux == triangle.A || vAux == triangle.B) // Both intersections are in the same edge
								return EQIntersections::E_One;

							vPoint2 = vAux;
							return EQIntersections::E_Two;
						}
						else
							return EQIntersections::E_One;
					}
					else // lsAux.A is strictly inside triangle: is not in a vertex or edge.
					{
						EQIntersections value2 = lsAux.IntersectionPoint(QLineSegment3D<VectorTypeParam>(triangle.A, triangle.B), vAux);
						if (value2 == EQIntersections::E_One)
							vPoint1 = vAux;
						else if (value2 = lsAux.IntersectionPoint(QLineSegment3D<VectorTypeParam>(triangle.B, triangle.C), vAux) == EQIntersections::E_One)
							vPoint1 = vAux;
						else if (value2 = lsAux.IntersectionPoint(QLineSegment3D<VectorTypeParam>(triangle.C, triangle.A), vAux)== EQIntersections::E_One)
							vPoint1 = vAux;
						else                  // Something is wrong, if one point is inside and the other is outside,
							QE_ASSERT(false); // there must be intersections.

						return EQIntersections::E_One;
					}
				}
				else // lsAux.B is inside triangle (A is outside)
				{
					if (lsAux.B == triangle.A) // lsAux.B is triangle.A vertex
					{

						EQIntersections value2 = lsAux.IntersectionPoint(QLineSegment3D<VectorTypeParam>(triangle.B, triangle.C), vAux);
						if (value2 == EQIntersections::E_One) // ls intersects opposite edge
						{
							vPoint1 = vAux;
							vPoint2 = lsAux.B;
							return EQIntersections::E_Two;
						}
						else // ls only intersects in A vertex
						{
							vPoint1 = lsAux.B;
							return EQIntersections::E_One;
						}
					}
					else if (lsAux.B == triangle.B) // lsAux.B is triangle.B vertex
					{
						EQIntersections value2 = lsAux.IntersectionPoint(QLineSegment3D<VectorTypeParam>(triangle.C, triangle.A), vAux);
						if (value2 == EQIntersections::E_One) // ls intersects opposite edge
						{
							vPoint1 = vAux;
							vPoint2 = lsAux.B;
							return EQIntersections::E_Two;
						}
						else // ls only intersects in B vertex
						{
							vPoint1 = lsAux.B;
							return EQIntersections::E_One;
						}
					}
					else if (lsAux.B == triangle.C) // lsAux.B is triangle.C vertex
					{
						EQIntersections value2 = lsAux.IntersectionPoint(QLineSegment3D<VectorTypeParam>(triangle.A, triangle.B), vAux);
						if (value2 == EQIntersections::E_One) // ls intersects opposite edge
						{
							vPoint1 = vAux;
							vPoint2 = lsAux.B;
							return EQIntersections::E_Two;
						}
						else // ls only intersects in C vertex
						{
							vPoint1 = lsAux.B;
							return EQIntersections::E_One;
						}
					}
					else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(triangle.A, triangle.B).MinDistance(lsAux.B))) // lsAux.B is in AB triangle edge (but not a vertex)
					{
						// ls intersects the other edges
						EQIntersections value2 = lsAux.IntersectionPoint(QLineSegment3D<VectorTypeParam>(triangle.B, triangle.C), vAux);
						if (value2 == EQIntersections::E_One)
						{
							vPoint1 = vAux;

							if (vAux == triangle.B || vAux == triangle.C) // Both intersections are in the same edge
								return EQIntersections::E_One;

							vPoint2 = lsAux.B;
							return EQIntersections::E_Two;
						}
						else if (value2 = lsAux.IntersectionPoint(QLineSegment3D<VectorTypeParam>(triangle.C, triangle.A), vAux) == EQIntersections::E_One)
						{
							vPoint1 = vAux;

							if (vAux == triangle.C || vAux == triangle.A) // Both intersections are in the same edge
								return EQIntersections::E_One;

							vPoint2 = lsAux.B;
							return EQIntersections::E_Two;
						}
						else // There is no other intersection
						{
							vPoint1 = lsAux.B;
							return EQIntersections::E_One;
						}
					}
					else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(triangle.B, triangle.C).MinDistance(lsAux.B))) // lsAux.B is in BC triangle edge (but not a vertex)
					{
						// ls intersects the other edges
						EQIntersections value2 = lsAux.IntersectionPoint(QLineSegment3D<VectorTypeParam>(triangle.A, triangle.B), vAux);
						if (value2 == EQIntersections::E_One)
						{
							vPoint1 = vAux;

							if (vAux == triangle.A || vAux == triangle.B) // Both intersections are in the same edge
								return EQIntersections::E_One;

							vPoint2 = lsAux.B;
							return EQIntersections::E_Two;
						}
						else if (value2 = lsAux.IntersectionPoint(QLineSegment3D<VectorTypeParam>(triangle.C, triangle.A), vAux) == EQIntersections::E_One)
						{
							vPoint1 = vAux;
							vPoint2 = lsAux.B;
							return EQIntersections::E_Two;
						}
						else // There is no other intersection
						{
							vPoint1 = lsAux.B;
							return EQIntersections::E_One;
						}
					}
					else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(triangle.C, triangle.A).MinDistance(lsAux.B))) // lsAux.B is in CA triangle edge (but not a vertex)
					{
						// ls intersects the other edges
						EQIntersections value2 = lsAux.IntersectionPoint(QLineSegment3D<VectorTypeParam>(triangle.B, triangle.C), vAux);
						if (value2 == EQIntersections::E_One)
						{
							vPoint1 = vAux;

							if (vAux == triangle.B || vAux == triangle.C) // Both intersections are in the same edge
								return EQIntersections::E_One;

							vPoint2 = lsAux.B;
							return EQIntersections::E_Two;
						}
						else if (value2 = lsAux.IntersectionPoint(QLineSegment3D<VectorTypeParam>(triangle.A, triangle.B), vAux) == EQIntersections::E_One)
						{
							vPoint1 = vAux;

							if (vAux == triangle.A || vAux == triangle.B) // Both intersections are in the same edge
								return EQIntersections::E_One;

							vPoint2 = lsAux.B;
							return EQIntersections::E_Two;
						}
						else // There is no other intersection
						{
							vPoint1 = lsAux.B;
							return EQIntersections::E_One;
						}
					}
					else // lsAux.B is strictly inside triangle: is not in a vertex or edge.
					{
						EQIntersections value2 = lsAux.IntersectionPoint(QLineSegment3D<VectorTypeParam>(triangle.A, triangle.B), vAux);
						if (value2 == EQIntersections::E_One)
							vPoint1 = vAux;
						else if (value2 = lsAux.IntersectionPoint(QLineSegment3D<VectorTypeParam>(triangle.B, triangle.C), vAux) == EQIntersections::E_One)
							vPoint1 = vAux;
						else if (value2 = lsAux.IntersectionPoint(QLineSegment3D<VectorTypeParam>(triangle.C, triangle.A), vAux)== EQIntersections::E_One)
							vPoint1 = vAux;
						else                  // Something is wrong, if one point is inside and the other is outside,
							QE_ASSERT(false); // there must be intersections.

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
	/// <param name="hex">[IN] The hexahedron whose intersections with resident line segment we want to check.</param>
    /// <param name="vPoint">[OUT] A vector where to store the intersection point.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the hexahedron,
    /// which can takes the following values: E_None, E_One, E_Two and E_Infinite.
	/// </returns>
	/// <remarks>
	/// -If there's no intersection point, the output parameter used for storing that point won't be modified.
	/// -If there are two intersections, the output parameter stores only one of them.
	/// </remarks>
	EQIntersections IntersectionPoint (const QBaseHexahedron<VectorType> &hex, VectorType &vPoint) const
	{
        VectorType vAuxPoint, vAux;
        bool bPreviousInt = false;

        // Check if resident line segment intersects ABCD face
        EQIntersections value1 = QuadrilateralIntersectionPoint(*this, hex.A, hex.B, hex.C, hex.D, vAux);

        if ( value1 == EQIntersections::E_Two ) // There are 2 intersections
        {
            vPoint = vAux;
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
        EQIntersections value2 = QuadrilateralIntersectionPoint(*this, hex.E, hex.F, hex.G, hex.H, vAux);

        if ( value2 == EQIntersections::E_Two ) // There are 2 intersections
        {
            vPoint = vAux;
            return EQIntersections::E_Two;
        }
        else if (value2 == EQIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                    vPoint = vAuxPoint;
                else
                    vPoint = vAux;
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
        EQIntersections value3 = QuadrilateralIntersectionPoint(*this, hex.A, hex.B, hex.H, hex.E, vAux);

        if (value3 == EQIntersections::E_Two ) // There are 2 intersections
        {
            vPoint = vAux;
            return EQIntersections::E_Two;
        }
        else if (value3 == EQIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                    vPoint = vAuxPoint;
                else
                    vPoint = vAux;
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
        EQIntersections value4 = QuadrilateralIntersectionPoint(*this, hex.B, hex.C, hex.G, hex.H, vAux);

        if ( value4 == EQIntersections::E_Two ) // There are 2 intersections
        {
            vPoint = vAux;
            return EQIntersections::E_Two;
        }
        else if (value4 == EQIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                    vPoint = vAuxPoint;
                else
                    vPoint = vAux;
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
        EQIntersections value5 = QuadrilateralIntersectionPoint(*this, hex.A, hex.D, hex.F, hex.E, vAux);

        if ( value5 == EQIntersections::E_Two ) // There are 2 intersections
        {
            vPoint = vAux;
            return EQIntersections::E_Two;
        }
        else if (value5 == EQIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                    vPoint = vAuxPoint;
                else
                    vPoint = vAux;
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
        EQIntersections value6 = QuadrilateralIntersectionPoint(*this, hex.C, hex.D, hex.F, hex.G, vAux);

        if ( value6 == EQIntersections::E_Two ) // There are 2 intersections
        {
            vPoint = vAux;
            return EQIntersections::E_Two;
        }
        else if (value6 == EQIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                    vPoint = vAuxPoint;
                else
                    vPoint = vAux;
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
            vPoint = vAuxPoint;
            return EQIntersections::E_One;
        }
        else // There are no intersections with hexahedron
        {
            const bool &IsInsideA = PointInsideHexahedron(hex, this->A);
            const bool &IsInsideB = PointInsideHexahedron(hex, this->B);

            if (IsInsideA && IsInsideB) // Both line segment end points are inside hexahedron
                return EQIntersections::E_Infinite;
            else if (!IsInsideA && !IsInsideB) // Both line segment end points are outside hexahedron
                return EQIntersections::E_None;
            else // Something is wrong!! There must be intersections in this case.
                QE_ASSERT(false);
        }
    }

    /// <summary>
	/// This method receives a convex hexahedron, and computes the points where the resident line segment intersects with it,
    /// if they exists.
	/// </summary>
	/// <param name="hex">[IN] The hexahedron whose intersections with resident line segment we want to check.</param>
    /// <param name="vPoint1">[OUT] A vector where to store the intersection point closest to A end point of line segment.</param>
    /// <param name="vPoint2">[OUT] A vector where to store the intersection point farthest to A end point of line segment.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the hexahedron,
    /// which can takes the following values: E_None, E_One, E_Two and E_Infinite.
	/// </returns>
	/// <remarks>
	/// -If there's no intersection point, the output parameters used for storing the intersection points won't be modified.
	/// -If there are two intersections, the first output parameter stores the closest point to A end point of line segment.
	/// </remarks>
	EQIntersections IntersectionPoint (const QBaseHexahedron<VectorType> &hex, VectorType &vPoint1, VectorType &vPoint2) const
	{
        VectorType vAuxPoint, vAux1, vAux2;
        bool bPreviousInt = false;

        // Check if resident line segment intersects ABCD face
        EQIntersections value1 = QuadrilateralIntersectionPoint(*this, hex.A, hex.B, hex.C, hex.D, vAux1, vAux2);

        if ( value1 == EQIntersections::E_Two ) // There are 2 intersections
        {
            vPoint1 = vAux1;
            vPoint2 = vAux2;
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
        EQIntersections value2 = QuadrilateralIntersectionPoint(*this, hex.E, hex.F, hex.G, hex.H, vAux1, vAux2);

        if ( value2 == EQIntersections::E_Two ) // There are 2 intersections
        {
            vPoint1 = vAux1;
            vPoint2 = vAux2;
            return EQIntersections::E_Two;
        }
        else if (value2 == EQIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux1)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux1 - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                {
                    vPoint1 = vAuxPoint;
                    vPoint2 = vAux1;
                }
                else
                {
                    vPoint1 = vAux1;
                    vPoint2 = vAuxPoint;
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
        EQIntersections value3 = QuadrilateralIntersectionPoint(*this, hex.A, hex.B, hex.H, hex.E, vAux1, vAux2);

        if ( value3 == EQIntersections::E_Two ) // There are 2 intersections
        {
            vPoint1 = vAux1;
            vPoint2 = vAux2;
            return EQIntersections::E_Two;
        }
        else if (value3 == EQIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux1)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux1 - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                {
                    vPoint1 = vAuxPoint;
                    vPoint2 = vAux1;
                }
                else
                {
                    vPoint1 = vAux1;
                    vPoint2 = vAuxPoint;
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
        EQIntersections value4 = QuadrilateralIntersectionPoint(*this, hex.B, hex.C, hex.G, hex.H, vAux1,vAux2);

        if ( value4 == EQIntersections::E_Two ) // There are 2 intersections
        {
            vPoint1 = vAux1;
            vPoint2 = vAux2;
            return EQIntersections::E_Two;
        }
        else if (value4 == EQIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux1)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux1 - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                {
                    vPoint1 = vAuxPoint;
                    vPoint2 = vAux1;
                }
                else
                {
                    vPoint1 = vAux1;
                    vPoint2 = vAuxPoint;
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
        EQIntersections value5 = QuadrilateralIntersectionPoint(*this, hex.A, hex.D, hex.F, hex.E, vAux1, vAux2);

        if ( value5 == EQIntersections::E_Two ) // There are 2 intersections
        {
            vPoint1 = vAux1;
            vPoint2 = vAux2;
            return EQIntersections::E_Two;
        }
        else if (value5 == EQIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux1)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux1 - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                {
                    vPoint1 = vAuxPoint;
                    vPoint2 = vAux1;
                }
                else
                {
                    vPoint1 = vAux1;
                    vPoint2 = vAuxPoint;
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
        EQIntersections value6 = QuadrilateralIntersectionPoint(*this, hex.C, hex.D, hex.F, hex.G, vAux1, vAux2);

        if ( value6 == EQIntersections::E_Two ) // There are 2 intersections
        {
            vPoint1 = vAux1;
            vPoint2 = vAux2;
            return EQIntersections::E_Two;
        }
        else if (value6 == EQIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux1)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux1 - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                {
                    vPoint1 = vAuxPoint;
                    vPoint2 = vAux1;
                }
                else
                {
                    vPoint1 = vAux1;
                    vPoint2 = vAuxPoint;
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
            vPoint1 = vAuxPoint;
            return EQIntersections::E_One;
        }
        else // There are no intersections with hexahedron
        {
            const bool &IsInsideA = PointInsideHexahedron(hex, this->A);
            const bool &IsInsideB = PointInsideHexahedron(hex, this->B);

            if (IsInsideA && IsInsideB) // Both line segment end points are inside hexahedron
                return EQIntersections::E_Infinite;
            else if (!IsInsideA && !IsInsideB) // Both line segment end points are outside hexahedron
                return EQIntersections::E_None;
            else // Something is wrong!! There must be intersections in this case.
                QE_ASSERT(false);
        }
    }

    /// <summary>
    /// Calculates the maximum distance between the resident line segment and a plane provided.
    /// </summary>
    /// <param name="p">[IN] The plane we want to know the maximum distance from the line segment.</param>
    /// <returns>
    /// A floating point value containing the maximum distance between the resident line segment and a plane provided.
    /// </returns>
    inline float_q MaxDistance(const QBasePlane &p) const
    {
        const float_q &fSquaredLength = p.a*p.a + p.b*p.b + p.c*p.c;

        QE_ASSERT(QFloat::IsNotZero(fSquaredLength));

        const float_q &fInvNormalLenght = QFloat::_1/sqrt(fSquaredLength);

        const float_q &distA = QFloat::Abs(p.a * this->A.x + p.b * this->A.y + p.c * this->A.z + p.d) * fInvNormalLenght;
        const float_q &distB = QFloat::Abs(p.a * this->B.x + p.b * this->B.y + p.c * this->B.z + p.d) * fInvNormalLenght;

        return std::max(distA, distB);
    }

    /// <summary>
	/// Given an input line segment, this method returns the maximum distance between this and the input one,
	///	that is, the distance between their farthest points.
	/// This method calls base class' implementation.
    /// </summary>
    /// <param name="q">[IN] The line segment the distance will be measured to.</param>
    /// <returns>
    /// A floating point value containing the maximum distance between both line segments.
    /// </returns>
    inline float_q MaxDistance(const QBaseLineSegment<VectorType>& vBaseLineSegment) const
    {
		return QLineSegment<VectorType>::MaxDistance(vBaseLineSegment);
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
    inline float_q MaxDistance(const VectorType& vPoint) const
    {
		return QLineSegment<VectorType>::MaxDistance(vPoint);
    }

    /// <summary>
    /// Calculates the minimum distance between the resident line segment and a plane provided.
    /// </summary>
    /// <param name="p">[IN] The plane we want to know the minimum distance from the line segment.</param>
    /// <returns>
    /// A floating point value containing the minimum distance between the resident line segment and a plane provided.
    /// </returns>
    inline float_q MinDistance(const QBasePlane &p) const
    {
        const float_q &fSquaredLength = p.a*p.a + p.b*p.b + p.c*p.c;

        QE_ASSERT(QFloat::IsNotZero(fSquaredLength));

        const float_q &fInvNormalLenght = QFloat::_1/sqrt(fSquaredLength);

        const float_q &distA = QFloat::Abs(p.a * this->A.x + p.b * this->A.y + p.c * this->A.z + p.d) * fInvNormalLenght;
        const float_q &distB = QFloat::Abs(p.a * this->B.x + p.b * this->B.y + p.c * this->B.z + p.d) * fInvNormalLenght;

        return std::min(distA, distB);
    }

	/// <summary>
	/// Given an input line segment, this method returns the minimum distance between this and the input one,
	///	that is, the distance between their closest points.
	/// This method calls base class' implementation.
	/// </summary>
	/// <param name="vBaseLineSegment">[IN] The line segment the distance will be measured to.</param>
	/// <returns>
	/// A floating point value (always nonnegative) which represents the minimum distance between the two segments.
	/// </returns>
	inline float_q MinDistance (const QBaseLineSegment<VectorType>& vBaseLineSegment) const
	{
		return QLineSegment<VectorType>::MinDistance(vBaseLineSegment);
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
	inline float_q MinDistance (const VectorType& vPoint) const
	{
		return QLineSegment<VectorType>::MinDistance(vPoint);
	}

    /// <summary>
    /// Projects the resident line segment over the plane provided.
    /// </summary>
    /// <param name="p">[IN] The plane where we want to project the resident line segment.</param>
    inline void ProjectToPlane (const QBasePlane &p)
    {
        const float_q &fSquaredLength = p.a*p.a + p.b*p.b + p.c*p.c;

        QE_ASSERT(QFloat::IsNotZero(fSquaredLength));

        const float_q &fInvSquaredLength = QFloat::_1/fSquaredLength;

        const float_q &fProjA = -(p.a * this->A.x + p.b * this->A.y + p.c * this->A.z + p.d);

        this->A.x += fProjA * p.a * fInvSquaredLength;
        this->A.y += fProjA * p.b * fInvSquaredLength;
        this->A.z += fProjA * p.c * fInvSquaredLength;

        const float_q &fProjB = -(p.a * this->B.x + p.b * this->B.y + p.c * this->B.z + p.d);

        this->B.x += fProjB * p.a * fInvSquaredLength;
        this->B.y += fProjB * p.b * fInvSquaredLength;
        this->B.z += fProjB * p.c * fInvSquaredLength;
    }

    /// <summary>
    /// Projects the resident line segment over the plane provided. The projection is stored in the line segment provided.
    /// </summary>
    /// <param name="p">[IN] The plane where we want to project the resident line segment.</param>
    /// <param name="ls">[OUT] The line segment where to store the result of projection.</param>
    inline void ProjectToPlane (const QBasePlane &p, QBaseLineSegment<VectorType> &ls) const
    {
        ls = *this;
        reinterpret_cast<QLineSegment3D<VectorType> &> (ls).ProjectToPlane(p);
    }

    /// <summary>
    /// Transforms the resident line segment with the rotation contained in the quaternion provided, acting
    /// the "A" end point as pivot of rotation.
    /// </summary>
    /// <param name="q">[IN] The quaternion which contains the rotation.</param>
    inline void Transform(const QQuaternion &q)
    {
        this->B -= this->A;

        this->B.Transform(q);

        this->B += this->A;
    }

    /// <summary>
    /// Transforms the resident line segment with the rotation contained in the quaternion provided, acting
    /// the "A" end point as pivot of rotation. The resultant line segment is stored in the line segment provided.
    /// </summary>
    /// <param name="q">[IN] The quaternion which contains the rotation.</param>
    /// <param name="ls">[OUT] Line segment to store the rotated one.</param>
    inline void Transform(const QQuaternion &q, QLineSegment3D<VectorType> &ls) const
    {
        ls = *this;
        ls.Transform(q);
    }

    /// <summary>
    /// Transforms the resident line segment with the transformation contained in the dual quaternion provided, acting
    /// the "A" end point as pivot of rotation.
    /// </summary>
    /// <param name="dq">[IN] The dual quaternion which contains the transformation.</param>
    inline void Transform(const QDualQuaternion &dq)
    {
        VectorType vAux(VectorType::ZeroVector);

        this->B -= this->A;

        this->B.Transform(dq);
        vAux.Transform(dq);

        this->B += this->A;
        this->A += vAux;
    }

    /// <summary>
    /// Transforms the resident line segment with the transformation contained in the dual quaternion provided, acting
    /// the "A" end point as pivot of rotation. The resultant line segment is stored in the line segment provided.
    /// </summary>
    /// <param name="dq">[IN] The dual quaternion which contains the transformation.</param>
    /// <param name="ls">[OUT] Line segment to store the transformed one.</param>
    inline void Transform(const QDualQuaternion &dq, QLineSegment3D<VectorType> &ls) const
    {
        ls = *this;
        ls.Transform(dq);
    }

    /// <summary>
    /// Transforms the resident line segment with a transformation of types rotation, scale, translation,
    /// generic transformation or space conversion transformation contained in the matrix provided, acting
    /// the coordinate origin as pivot.
    /// </summary>
    /// <param name="m">[IN] The matrix which contains the transformation to be applied.</param>
    template <class MatrixType>
    inline void Transform (const MatrixType &m)
    {
        this->A.Transform(m);
        this->B.Transform(m);
    }

    /// <summary>
    /// Transforms the resident line segment with a transformation of types rotation, scale, translation,
    /// generic transformation or space conversion transformation contained in the matrix provided, acting
    /// the coordinate origin as pivot.
    /// The resultant line segment is stored in the line segment provided.
    /// </summary>
    /// <param name="m">[IN] The matrix which contains the transformation to be applied.</param>
    /// <param name="ls">[OUT] Line segment to store the transformed one.</param>
    template <class MatrixType>
    inline void Transform (const MatrixType &m, QBaseLineSegment<VectorType> &ls) const
    {
        ls = *this;
        reinterpret_cast<QLineSegment3D<VectorType> &> (ls).Transform(m);
    }

    /// <summary>
    /// Transforms the resident line segment with the rotation contained in the quaternion provided, acting
    /// the center point of the line segment as pivot of rotation.
    /// </summary>
    /// <param name="q">[IN] The quaternion which contains the rotation.</param>
    inline void TransformFromCenter(const QQuaternion &q)
    {
        VectorType vCenter;

        this->GetCenter(vCenter);

        this->A -= vCenter;
        this->B -= vCenter;

        this->A.Transform(q);
        this->B.Transform(q);

        this->A += vCenter;
        this->B += vCenter;
    }

    /// <summary>
    /// Transforms the resident line segment with the rotation contained in the quaternion provided, acting
    /// the center point of the line segment as pivot of rotation. The resultant line segment is stored in the line segment provided.
    /// </summary>
    /// <param name="q">[IN] The quaternion which contains the rotation.</param>
    /// <param name="ls">[OUT] Line segment to store the rotated one.</param>
    inline void TransformFromCenter(const QQuaternion &q, QLineSegment3D<VectorType> &ls) const
    {
        ls = *this;
        ls.TransformFromCenter(q);
    }

    /// <summary>
    /// Transforms the resident line segment with the transformation contained in the dual quaternion provided, acting
    /// the center point of line segment as pivot of rotation.
    /// </summary>
    /// <param name="dq">[IN] The dual quaternion which contains the transformation.</param>
    inline void TransformFromCenter(const QDualQuaternion &dq)
    {
        VectorType vCenter;

        this->GetCenter(vCenter);

        this->A -= vCenter;
        this->B -= vCenter;

        this->A.Transform(dq);
        this->B.Transform(dq);

        this->A += vCenter;
        this->B += vCenter;
    }

    /// <summary>
    /// Transforms the resident line segment with the transformation contained in the dual quaternion provided, acting
    /// the center point of line segment as pivot of rotation. The resultant line segment is stored in the line segment provided.
    /// </summary>
    /// <param name="dq">[IN] The dual quaternion which contains the transformation.</param>
    /// <param name="ls">[OUT] Line segment to store the transformed one.</param>
    inline void TransformFromCenter(const QDualQuaternion &dq, QLineSegment3D<VectorType> &ls) const
    {
        ls = *this;
        ls.TransformFromCenter(dq);
    }

    /// <summary>
    /// Transforms the resident line segment with a transformation of types rotation, scale, translation,
    /// generic transformation or space conversion transformation contained in the matrix provided, acting
    /// the point provided as pivot.
    /// </summary>
    /// <param name="m">[IN] The matrix which contains the transformation to be applied.</param>
    /// <param name="vPivot">[IN] A 3D or 4D point we want to act as pivot of transformation.</param>
    template <class MatrixType>
    inline void TransformWithPivot (const MatrixType &m, const VectorType &vPivot)
    {
        this->A -= vPivot;
        this->B -= vPivot;

        this->A.Transform(m);
        this->B.Transform(m);

        this->A += vPivot;
        this->B += vPivot;
    }

    /// <summary>
    /// Transforms the resident line segment with a transformation of types rotation, scale, translation,
    /// generic transformation or space conversion transformation contained in the matrix provided, acting
    /// the point provided as pivot.
    /// The resultant line segment is stored in the line segment provided.
    /// </summary>
    /// <param name="m">[IN] The matrix which contains the transformation to be applied.</param>
    /// <param name="vPivot">[IN] A 3D or 4D point we want to act as pivot of transformation.</param>
    /// <param name="ls">[OUT] Line segment to store the transformed one.</param>
    template <class MatrixType>
    inline void TransformWithPivot (const MatrixType &m, const VectorType &vPivot, QBaseLineSegment<VectorType> &ls) const
    {
        ls = *this;
        reinterpret_cast<QLineSegment3D<VectorType> &> (ls).TransformWithPivot(m, vPivot);
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
    /// <param name="p">[IN] The plane we want check the relation with resident line segment.</param>
    /// <returns>
    /// An integer value like follows:
    ///     0 (Contained): All the line segment lies on plane.
    ///     1 (PositiveSide): The line segment is fully contained in the positive side of the space defined by the plane.
    ///     2 (NegativeSide): The line segment is fully contained in the negative side of the space defined by the plane.
    ///     3 (BothSides): One end point of the line segment is in the positive side and the other is in the negative one.
    /// We consider "positive part of the space" the locus of points which verifies \f$ Ax + By + Cz + D > 0 \f$.
    /// </returns>
    EQSpaceRelation SpaceRelation(const QBasePlane &p)
    {
        const float_q &distA = p.a * this->A.x + p.b * this->A.y + p.c * this->A.z + p.d;
        const float_q &distB = p.a * this->B.x + p.b * this->B.y + p.c * this->B.z + p.d;

        if (QFloat::IsZero(distA) && QFloat::IsZero(distB))
            return EQSpaceRelation::E_Contained;
        else if ( QFloat::IsGreaterOrEquals(distA, QFloat::_0) && QFloat::IsGreaterOrEquals(distB, QFloat::_0) )
            return EQSpaceRelation::E_PositiveSide;
        else if ( QFloat::IsLowerOrEquals(distA, QFloat::_0) && QFloat::IsLowerOrEquals(distB, QFloat::_0) )
            return EQSpaceRelation::E_NegativeSide;
        else
            return EQSpaceRelation::E_BothSides;
    }

protected:

    // Calculates if two points are in the same side of a line segment. Can be used to know
    // if a point is inside or outside a plane convex polygon, being point and polygon coplanars.
    // The point must be in the same side of every polygon edge than any
    // other polygon vertex not included in the analized edge.
    template <class VectorTypeParam>
    inline bool PointsInSameSideOfLine(const VectorTypeParam &vP1, const VectorTypeParam &vP2,
        const VectorTypeParam &vLine1, const VectorTypeParam &vLine2) const
    {
        VectorTypeParam vLine(vLine2 - vLine1);
        VectorTypeParam vCP1;
        VectorTypeParam vCP2;

        vLine.CrossProduct(vP1 - vLine1, vCP1);
        vLine.CrossProduct(vP2 - vLine1, vCP2);

        if ( QFloat::IsLessThan(vCP1.DotProduct(vCP2), QFloat::_0) )
            return false;
        else
            return true;
    }

    // Calculates if a point is inside the triangle provided applying barycentric technique.
    template <class VectorTypeParam>
    inline bool PointInsideTriangle(const QBaseTriangle<VectorTypeParam> &T, const VectorTypeParam &vP) const
    {
        // Compute vectors
        const VectorTypeParam &v0(T.C - T.A);
        const VectorTypeParam &v1(T.B - T.A);
        const VectorTypeParam &v2(vP - T.A);

        // Compute dot products
        const float_q &fDot00 = v0.DotProduct(v0);
        const float_q &fDot01 = v0.DotProduct(v1);
        const float_q &fDot02 = v0.DotProduct(v2);
        const float_q &fDot11 = v1.DotProduct(v1);
        const float_q &fDot12 = v1.DotProduct(v2);

        // Compute barycentric coordinates
        const float_q &fDenom = fDot00 * fDot11 - fDot01 * fDot01;

        QE_ASSERT(fDenom != QFloat::_0);

        const float_q &fInvDenom = QFloat::_1 / fDenom;

        const float_q &fU = (fDot11 * fDot02 - fDot01 * fDot12) * fInvDenom;
        const float_q &fV = (fDot00 * fDot12 - fDot01 * fDot02) * fInvDenom;

        // Check if point is in triangle
        return QFloat::IsPositive(fU) && QFloat::IsPositive(fV) && QFloat::IsLowerOrEquals(fU + fV, QFloat::_1);
    }

    // Calculates if a point is inside the convex quadrilateral provided by the vertex A, B, C and D,
    // applying barycentric technique. Is supossed that quadrilateral vertex are consecutive.
    template <class VectorTypeParam>
    inline bool PointInsideQuadrilateral(const VectorTypeParam &vA, const VectorTypeParam &vB,
        const VectorTypeParam &vC,const VectorTypeParam &vD, const VectorTypeParam &vP) const
    {
        // Compute vectors
        const VectorTypeParam &v0(vC - vA);
        const VectorTypeParam &v1(vB - vA);
        const VectorTypeParam &v2(vP - vA);

        // Compute dot products
        const float_q &fDot00 = v0.DotProduct(v0);
        const float_q &fDot01 = v0.DotProduct(v1);
        const float_q &fDot02 = v0.DotProduct(v2);
        const float_q &fDot11 = v1.DotProduct(v1);
        const float_q &fDot12 = v1.DotProduct(v2);

        // Compute barycentric coordinates
        const float_q &fDenom = fDot00 * fDot11 - fDot01 * fDot01;

        QE_ASSERT(fDenom != QFloat::_0);

        const float_q &fInvDenom = QFloat::_1 / fDenom;

        const float_q &fU = (fDot11 * fDot02 - fDot01 * fDot12) * fInvDenom;
        const float_q &fV = (fDot00 * fDot12 - fDot01 * fDot02) * fInvDenom;

        // Check if point is in triangle
        if ( QFloat::IsPositive(fU) && QFloat::IsPositive(fV) && QFloat::IsLowerOrEquals(fU + fV, QFloat::_1) )
            return true;

        // Compute new vector
        const VectorTypeParam &v3(vD - vA);

        // Compute new dot products
        const float_q &fDot03 = v0.DotProduct(v3);
        const float_q &fDot33 = v3.DotProduct(v3);
        const float_q &fDot32 = v3.DotProduct(v2);

        // Compute new barycentric coordinates
        const float_q &fDenom2 = fDot00 * fDot33 - fDot03 * fDot03;

        QE_ASSERT(fDenom2 != QFloat::_0);

        const float_q &fInvDenom2 = QFloat::_1 / fDenom2;

        const float_q &fU2 = (fDot33 * fDot02 - fDot03 * fDot32) * fInvDenom2;
        const float_q &fV2 = (fDot00 * fDot32 - fDot03 * fDot02) * fInvDenom2;

        // Check if point is in triangle
        return QFloat::IsPositive(fU2) && QFloat::IsPositive(fV2) && QFloat::IsLowerOrEquals(fU2 + fV2, QFloat::_1);
    }

    // Calculates if two points are in the same side of a plane defined by 3 points.
    template <class VectorTypeParam>
    inline bool PointsInSameSideOfPlane(const VectorTypeParam &vP1, const VectorTypeParam &vP2,
        const VectorTypeParam &vA, const VectorTypeParam &vB, const VectorTypeParam &vC) const
    {
        QBasePlane p;

        PlaneFrom3Points(vA, vB, vC, p);

        const float_q &distP1 = p.a * vP1.x + p.b * vP1.y + p.c * vP1.z + p.d;
        const float_q &distP2 = p.a * vP2.x + p.b * vP2.y + p.c * vP2.z + p.d;

        if ( QFloat::IsLessThan(distP1 * distP2, QFloat::_0) )
            return false;
        else
            return true;
    }

    // Calculates if two points are in the same side of a plane defined by 3 points.
    template <class VectorTypeParam>
    inline bool PointInsideHexahedron(const QBaseHexahedron<VectorTypeParam> &H, const VectorTypeParam &vP) const
    {
        return (PointsInSameSideOfPlane(vP, H.E, H.A, H.B, H.C) &&
                PointsInSameSideOfPlane(vP, H.A, H.E, H.F, H.G) &&
                PointsInSameSideOfPlane(vP, H.C, H.A, H.B, H.H) &&
                PointsInSameSideOfPlane(vP, H.A, H.B, H.C, H.G) &&
                PointsInSameSideOfPlane(vP, H.C, H.A, H.D, H.F) &&
                PointsInSameSideOfPlane(vP, H.A, H.C, H.D, H.F) );
    }

    // Checks if a segment intersects a cuadrilateral. It's supossed that A, B, C, D are consecutive
    // vertices of a cuadrilateral.
    template <class VectorTypeParam>
    bool CuadrilateralIntersection(const QLineSegment3D<VectorTypeParam> &ls,
        const VectorTypeParam &vA, const VectorTypeParam &vB, const VectorTypeParam &vC, const VectorTypeParam &vD) const
    {
        // Plane equation
        QBasePlane auxP;
        PlaneFrom3Points(vA, vB, vC, auxP);

        // Line Segment don't intersects the cuadrilateral plane.
        if (!ls.Intersection(auxP))
            return false;

        // If both end points satisfy plane equation, the line segment lies on plane
        const float_q &fDot1 = auxP.a * ls.B.x + auxP.b * ls.B.y + auxP.c * ls.B.z + auxP.d;
        const float_q &fDot2 = auxP.a * ls.A.x + auxP.b * ls.A.y + auxP.c * ls.A.z + auxP.d;

        if (QFloat::IsZero(fDot1) && QFloat::IsZero(fDot2))
        {
            if (ls.QLineSegment<VectorTypeParam>::Intersection(QLineSegment<VectorTypeParam> (vA, vB)) ||   // Both cuadrilateral and line segment are coplanar. If the line segment
                ls.QLineSegment<VectorTypeParam>::Intersection(QLineSegment<VectorTypeParam> (vB, vC)) ||   // intersects one of the edges of the cuadrilateral, then the line segment intersects the cuadrilateral.
                ls.QLineSegment<VectorTypeParam>::Intersection(QLineSegment<VectorTypeParam> (vC, vD)) ||
                ls.QLineSegment<VectorTypeParam>::Intersection(QLineSegment<VectorTypeParam> (vD, vA)))
                return true;
            else if ( PointInsideQuadrilateral(vA, vB, vC, vD, ls.A) ) // Now we check if segment is fully contained in the cuadrilateral
                return true;                                           // We only check "A" end point, since if "A" is inside, "B" must be inside too (see previus test).
            else
                return false;
        }

        QE_ASSERT(QFloat::IsNotZero(fDot2 - fDot1));

        // The point which satisfies both line and plane equations.
        VectorTypeParam vAux = ls.A + (ls.B - ls.A) * fDot2/(fDot2 - fDot1);

        // For every edge, it tests if the intersection point is in the same side of each edge
        // than any other vextex (not of the edge). If it does, then it's inside the cuadrilateral,
        // otherwise it's outside.
        if ( PointInsideQuadrilateral(vA, vB, vC, vD, vAux) )
            return true;
        else
            return false;
    }

    // Computes the intersection between a line segment and a cuadrilateral. It's supossed that A, B, C, D are consecutive
    // vertices of a cuadrilateral.
    // Returns a value indicating the number of intersections (E_None, E_One, E_Two and E_Infinite)
    // Stores the closest intersection point to A end point of line segment in the vector provided.
    template <class VectorTypeParam>
    EQIntersections QuadrilateralIntersectionPoint(const QLineSegment3D<VectorTypeParam> &ls,
        const VectorTypeParam &vA, const VectorTypeParam &vB, const VectorTypeParam &vC, const VectorTypeParam &vD,
        VectorTypeParam &vOut) const
    {
        VectorTypeParam vAux;
        return this->QuadrilateralIntersectionPoint(ls, vA, vB, vC, vD, vOut, vAux);
    }

    // Computes the intersection between a line segment and a cuadrilateral. It's supossed that A, B, C, D are consecutive
    // vertices of a cuadrilateral.
    // Returns a value indicating the number of intersections (E_None, E_One, E_Two and E_Infinite)
    // Stores the closest intersection point to A end point of line segment in the first vector provided, and the farthest intersection
    // point in the second one, if it exists.
    template <class VectorTypeParam>
    EQIntersections QuadrilateralIntersectionPoint(const QLineSegment3D<VectorTypeParam> &ls,
        const VectorTypeParam &vA, const VectorTypeParam &vB, const VectorTypeParam &vC, const VectorTypeParam &vD,
        VectorTypeParam &vOut1, VectorTypeParam &vOut2) const
    {
        // Plane equation
        QBasePlane auxP;
        VectorTypeParam vAux;
        PlaneFrom3Points(vA, vB, vC, auxP);

        const EQIntersections &value = ls.IntersectionPoint(auxP, vAux);

        if (value == EQIntersections::E_None) // Line Segment don't intersects the cuadrilateral plane.
            return EQIntersections::E_None;
        else if (value == EQIntersections::E_One) // Line segment has one intersection with quadrilateral plane
        {
            if (PointInsideQuadrilateral(vA, vB, vC, vD, vAux))
            {
                vOut1 = vAux;
                return EQIntersections::E_One;
            }
            else
                return EQIntersections::E_None;
        }
        else // Line segment lies on plane (value == EQIntersections::E_Infinite)
        {
            const bool &bAIsInside = PointInsideQuadrilateral(vA, vB, vC, vD, ls.A);
            const bool &bBIsInside = PointInsideQuadrilateral(vA, vB, vC, vD, ls.B);

            if (bAIsInside && bBIsInside) // Both line segment end points are inside quadrilateral.
            {
                // A or B are vertex
                const bool &bAIsVertex = (ls.A == vA || ls.A == vB || ls.A == vC || ls.A == vD);
                const bool &bBIsVertex = (ls.B == vA || ls.B == vB || ls.B == vC || ls.B == vD);

                if (bAIsVertex && bBIsVertex) // Both endpoints are vertices of quadrilateral
                {
                    vOut1 = ls.A;
                    vOut2 = ls.B;
                    return EQIntersections::E_Two;
                }
                else if (bAIsVertex) // Only A endpoint is a vertex of quadrilateral
                {
                    if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vA, vB).MinDistance(ls.B))) // B is in vAvB edge
                    {
                        if (ls.A == vA || ls.A == vB) // A and B are in the same edge
                        {
                            vOut1 = ls.A;
                            return EQIntersections::E_One;
                        }
                        else
                        {
                            vOut1 = ls.A;
                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                    }
                    else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vB, vC).MinDistance(ls.B))) // B is in vBvC edge
                    {
                        if (ls.A == vB || ls.A == vC) // A and B are in the same edge
                        {
                            vOut1 = ls.A;
                            return EQIntersections::E_One;
                        }
                        else
                        {
                            vOut1 = ls.A;
                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                    }
                    else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vC, vD).MinDistance(ls.B))) // B is in vCvD edge
                    {
                        if (ls.A == vC || ls.A == vD) // A and B are in the same edge
                        {
                            vOut1 = ls.A;
                            return EQIntersections::E_One;
                        }
                        else
                        {
                            vOut1 = ls.A;
                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                    }
                    else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(ls.B))) // B is in vDvA edge
                    {
                        if (ls.A == vD || ls.A == vA) // A and B are in the same edge
                        {
                            vOut1 = ls.A;
                            return EQIntersections::E_One;
                        }
                        else
                        {
                            vOut1 = ls.A;
                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                    }
                    else // B is not in an edge
                    {
                        vOut1 = ls.A;
                        return EQIntersections::E_One;
                    }
                }
                else if (bBIsVertex)
                {
                    if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vA, vB).MinDistance(ls.A))) // A is in vAvB edge
                    {
                        if (ls.B == vA || ls.B == vB) // A and B are in the same edge
                        {
                            vOut1 = ls.B;
                            return EQIntersections::E_One;
                        }
                        else
                        {
                            vOut1 = ls.A;
                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                    }
                    else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vB, vC).MinDistance(ls.A))) // B is in vBvC edge
                    {
                        if (ls.B == vB || ls.B == vC) // A and B are in the same edge
                        {
                            vOut1 = ls.B;
                            return EQIntersections::E_One;
                        }
                        else
                        {
                            vOut1 = ls.A;
                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                    }
                    else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vC, vD).MinDistance(ls.A))) // B is in vCvD edge
                    {
                        if (ls.B == vC || ls.B == vD) // A and B are in the same edge
                        {
                            vOut1 = ls.B;
                            return EQIntersections::E_One;
                        }
                        else
                        {
                            vOut1 = ls.A;
                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                    }
                    else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(ls.A))) // B is in vDvA edge
                    {
                        if (ls.B == vD || ls.B == vA) // A and B are in the same edge
                        {
                            vOut1 = ls.B;
                            return EQIntersections::E_One;
                        }
                        else
                        {
                            vOut1 = ls.A;
                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                    }
                    else
                    {
                        vOut1 = ls.B;
                        return EQIntersections::E_One;
                    }
                }
                else // Neither A or B are vertices of quadrilateral
                {
                    if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vA, vB).MinDistance(ls.A))) // A is in vAvB edge (but not a vertex)
                    {
                        if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vA, vB).MinDistance(ls.B))) // B is in vAvB edge (but not a vertex)
                            return EQIntersections::E_Infinite;
                        else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vB, vC).MinDistance(ls.B)) || // B is in other edge (but not a vertex)
                                 QFloat::IsZero(QLineSegment<VectorTypeParam>(vC, vD).MinDistance(ls.B)) ||
                                 QFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(ls.B)))
                        {
                            vOut1 = ls.A;
                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                        else // B is not in an edge
                        {
                            vOut1 = ls.A;
                            return EQIntersections::E_One;
                        }
                    }
                    else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vB, vC).MinDistance(ls.A))) // A is in vBvC edge (but not a vertex)
                    {
                        if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vB, vC).MinDistance(ls.B))) // B is in vBvC edge (but not a vertex)
                            return EQIntersections::E_Infinite;
                        else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vA, vB).MinDistance(ls.B)) || // B is in other edge (but not a vertex)
                                 QFloat::IsZero(QLineSegment<VectorTypeParam>(vC, vD).MinDistance(ls.B)) ||
                                 QFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(ls.B)))
                        {
                            vOut1 = ls.A;
                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                        else // B is not in an edge
                        {
                            vOut1 = ls.A;
                            return EQIntersections::E_One;
                        }
                    }
                    else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vC, vD).MinDistance(ls.A))) // A is in vCvD edge (but not a vertex)
                    {
                        if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vC, vD).MinDistance(ls.B))) // B is in vCvD edge (but not a vertex)
                            return EQIntersections::E_Infinite;
                        else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vA, vB).MinDistance(ls.B)) || // B is in other edge (but not a vertex)
                                 QFloat::IsZero(QLineSegment<VectorTypeParam>(vB, vC).MinDistance(ls.B)) ||
                                 QFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(ls.B)))
                        {
                            vOut1 = ls.A;
                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                        else // B is not in an edge
                        {
                            vOut1 = ls.A;
                            return EQIntersections::E_One;
                        }
                    }
                    else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(ls.A))) // A is in vDvA edge (but not a vertex)
                    {
                        if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(ls.B))) // B is in vDvA edge (but not a vertex)
                            return EQIntersections::E_Infinite;
                        else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vA, vB).MinDistance(ls.B)) || // B is in other edge (but not a vertex)
                                 QFloat::IsZero(QLineSegment<VectorTypeParam>(vB, vC).MinDistance(ls.B)) ||
                                 QFloat::IsZero(QLineSegment<VectorTypeParam>(vC, vD).MinDistance(ls.B)))
                        {
                            vOut1 = ls.A;
                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                        else // B is not in an edge
                        {
                            vOut1 = ls.A;
                            return EQIntersections::E_One;
                        }
                    }
		            else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(ls.A))) // A is in DA quad edge (but not a vertex)
					{
						if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(ls.B))) // B is in DA quad edge (but not a vertex)
							return EQIntersections::E_Infinite;
						else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vA, vB).MinDistance(ls.B)) || // B is in other edge (but not a vertex)
								 QFloat::IsZero(QLineSegment<VectorTypeParam>(vB, vC).MinDistance(ls.B)) ||
								 QFloat::IsZero(QLineSegment<VectorTypeParam>(vC, vD).MinDistance(ls.B)))
						{
							vOut1 = ls.A;
							vOut2 = ls.B;
							return EQIntersections::E_Two;
						}
						else // B is not in an edge
						{
							vOut1 = ls.A;
							return EQIntersections::E_One;
						}
					}
                    else // A is not in an edge
                    {
                        if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vA, vB).MinDistance(ls.B)) || // B is in an edge (but not a vertex)
                            QFloat::IsZero(QLineSegment<VectorTypeParam>(vB, vC).MinDistance(ls.B)) ||
                            QFloat::IsZero(QLineSegment<VectorTypeParam>(vC, vD).MinDistance(ls.B)) ||
                            QFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(ls.B)))
                        {
                            vOut1 = ls.B;
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

                EQIntersections value2AB = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vA, vB), vPointAB);

                if (value2AB == EQIntersections::E_Infinite) // Line segment contains AB edge of quadrilateral
                {
                    if  ( (vA - ls.A).GetSquaredLength() < (vB - ls.A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                    {
                        vOut1 = vA;
                        vOut2 = vB;
                    }
                    else
                    {
                        vOut1 = vB;
                        vOut2 = vA;
                    }
                    return EQIntersections::E_Two;
                }

                // Line segment contains BC edge of quadrilateral
                EQIntersections value2BC = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vB, vC), vPointBC);
                if (value2BC == EQIntersections::E_Infinite)
                {
                    if  ( (vB - ls.A).GetSquaredLength() < (vC - ls.A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                    {
                        vOut1 = vB;
                        vOut2 = vC;
                    }
                    else
                    {
                        vOut1 = vC;
                        vOut2 = vB;
                    }
                    return EQIntersections::E_Two;
                }

                // Line segment contains CA edge of quadrilateral
                EQIntersections value2CD = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vC, vD), vPointCD);
                if (value2CD == EQIntersections::E_Infinite)
                {
                    if  ( (vC - ls.A).GetSquaredLength() < (vD - ls.A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                    {
                        vOut1 = vC;
                        vOut2 = vD;
                    }
                    else
                    {
                        vOut1 = vD;
                        vOut2 = vC;
                    }
                    return EQIntersections::E_Two;
                }

                // Line segment contains DA edge of quadrilateral
                EQIntersections value2DA = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vD, vA), vPointDA);
                if (value2DA == EQIntersections::E_Infinite)
                {
                    if  ( (vD - ls.A).GetSquaredLength() < (vA - ls.A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                    {
                        vOut1 = vD;
                        vOut2 = vA;
                    }
                    else
                    {
                        vOut1 = vA;
                        vOut2 = vD;
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
								if  ( (vPointAB - ls.A).GetSquaredLength() < (vPointCD - ls.A).GetSquaredLength() )
								{
									vOut1 = vPointAB;
									vOut2 = vPointCD;
								}
								else
								{
									vOut1 = vPointCD;
									vOut2 = vPointAB;
								}

								return EQIntersections::E_Two;
							}
							else if (value2DA ==EQIntersections::E_One) // Line segment intersects DA edge of quadrilateral
							{
								// Returns closest point to A end point of line segment
								if  ( (vPointAB - ls.A).GetSquaredLength() < (vPointDA - ls.A).GetSquaredLength() )
								{
									vOut1 = vPointAB;
									vOut2 = vPointDA;
								}
								else
								{
									vOut1 = vPointDA;
									vOut2 = vPointAB;
								}

								return EQIntersections::E_Two;
							}
							else
							{
								vOut1 = vPointAB;
								return EQIntersections::E_One;
							}
						}
                        else
                        {
                            if  ( (vPointAB - ls.A).GetSquaredLength() < (vPointBC - ls.A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                            {
                                vOut1 = vPointAB;
                                vOut2 = vPointBC;
                            }
                            else
                            {
                                vOut1 = vPointBC;
                                vOut2 = vPointAB;
                            }
                            return EQIntersections::E_Two;
                        }
                    }
                    else if (value2CD ==EQIntersections::E_One) // Line segment intersects CD edge of quadrilateral
                    {
                        // Returns closest point to A end point of line segment
                        if  ( (vPointAB - ls.A).GetSquaredLength() < (vPointCD - ls.A).GetSquaredLength() )
                        {
                            vOut1 = vPointAB;
                            vOut2 = vPointCD;
                        }
                        else
                        {
                            vOut1 = vPointCD;
                            vOut2 = vPointAB;
                        }

                        return EQIntersections::E_Two;
                    }
                    else if (value2DA ==EQIntersections::E_One) // Line segment intersects DA edge of quadrilateral
                    {
                        if (vPointAB == vPointDA) // Are the same point
                        {
                            vOut1 = vPointAB;
                            return EQIntersections::E_One;
                        }
                        else
                        {
                            // Returns closest point to A end point of line segment
                            if  ( (vPointAB - ls.A).GetSquaredLength() < (vPointDA - ls.A).GetSquaredLength() )
                            {
                                vOut1 = vPointAB;
                                vOut2 = vPointDA;
                            }
                            else
                            {
                                vOut1 = vPointDA;
                                vOut2 = vPointAB;
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
                        if (vPointBC == vPointCD) // Are the same point
                        {
                            if (value2DA ==EQIntersections::E_One) // Line segment intersects DA edge of quadrilateral
							{
								// Returns closest point to A end point of line segment
								if  ( (vPointBC - ls.A).GetSquaredLength() < (vPointDA - ls.A).GetSquaredLength() )
								{
									vOut1 = vPointBC;
									vOut2 = vPointDA;
								}
								else
								{
									vOut1 = vPointDA;
									vOut2 = vPointBC;
								}

								return EQIntersections::E_Two;
							}
							else
							{
								vOut1 = vPointBC;
								return EQIntersections::E_One;
							}
                        }
                        else
                        {
                            // Returns closest point to A end point of line segment
                            if  ( (vPointBC - ls.A).GetSquaredLength() < (vPointCD - ls.A).GetSquaredLength() )
                            {
                                vOut1 = vPointBC;
                                vOut2 = vPointCD;
                            }
                            else
                            {
                                vOut1 = vPointCD;
                                vOut2 = vPointBC;
                            }

                            return EQIntersections::E_Two;
                        }
                    }
                    else if (value2DA ==EQIntersections::E_One)
                    {
                        // Returns closest point to A end point of line segment
                        if  ( (vPointBC - ls.A).GetSquaredLength() < (vPointDA - ls.A).GetSquaredLength() )
                        {
                            vOut1 = vPointBC;
                            vOut2 = vPointDA;
                        }
                        else
                        {
                            vOut1 = vPointDA;
                            vOut2 = vPointBC;
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
                        if (vPointCD == vPointDA) // Are the same point
                        {
                            vOut1 = vPointCD;
                            return EQIntersections::E_One;
                        }
                        else
                        {
                            // Returns closest point to A end point of line segment
                            if  ( (vPointCD - ls.A).GetSquaredLength() < (vPointDA - ls.A).GetSquaredLength() )
                            {
                                vOut1 = vPointCD;
                                vOut2 = vPointDA;
                            }
                            else
                            {
                                vOut1 = vPointDA;
                                vOut2 = vPointCD;
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
                if (bAIsInside) // ls.A is inside quadrilateral
                {
                    if (ls.A == vA) // ls.A is vA vertex
                    {
                        vOut1 = ls.A;

                        // ls intersects opposite edges
                        EQIntersections value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vB, vC), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
                            vOut2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vC, vD), vAux)== EQIntersections::E_One)
                        {
                            vOut2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else
                            return EQIntersections::E_One;
                    }
                    else if (ls.A == vB) // ls.A is vB vertex
                    {
                        vOut1 = ls.A;

                        // ls intersects opposite edges
                        EQIntersections value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vC, vD), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
                            vOut2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vD, vA), vAux)== EQIntersections::E_One)
                        {
                            vOut2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else
                            return EQIntersections::E_One;
                    }
                    else if (ls.A == vC) // ls.A is vC vertex
                    {
                        vOut1 = ls.A;

                        // ls intersects opposite edges
                        EQIntersections value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vD, vA), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
                            vOut2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vA, vB), vAux)== EQIntersections::E_One)
                        {
                            vOut2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else
                            return EQIntersections::E_One;
                    }
                    else if (ls.A == vD) // ls.A is vD vertex
                    {
                        vOut1 = ls.A;

                        // ls intersects opposite edges
                        EQIntersections value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vA, vB), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
                            vOut2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vB, vC), vAux)== EQIntersections::E_One)
                        {
                            vOut2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else
                            return EQIntersections::E_One;
                    }
                    else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vA, vB).MinDistance(ls.A))) // ls.A is in vAvB edge (but not a vertex)
                    {
                        vOut1 = ls.A;

                        // ls intersects other edges
                        EQIntersections value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vB, vC), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
		                    if (vAux == vB || vAux == vC) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vOut2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vC, vD), vAux) == EQIntersections::E_One)
                        {
							if (vAux == vC || vAux == vD) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vOut2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vD, vA), vAux) == EQIntersections::E_One)
                        {
							if (vAux == vD || vAux == vA) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vOut2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else
                            return EQIntersections::E_One;
                    }
                    else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vB, vC).MinDistance(ls.A))) // ls.A is in vBvC edge (but not a vertex)
                    {
                        vOut1 = ls.A;

                         // ls intersects other edges
                        EQIntersections value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vA, vB), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
							if (vAux == vA || vAux == vB) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vOut2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vC, vD), vAux) == EQIntersections::E_One)
                        {
							if (vAux == vC || vAux == vD) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vOut2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vD, vA), vAux) == EQIntersections::E_One)
                        {
							if (vAux == vD || vAux == vA) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vOut2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else
                            return EQIntersections::E_One;
                    }
                    else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vC, vD).MinDistance(ls.A))) // ls.A is in vCvD edge (but not a vertex)
                    {
                        vOut1 = ls.A;

                         // ls intersects other edges
                        EQIntersections value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vB, vC), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
							if (vAux == vB || vAux == vC) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vOut2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vA, vB), vAux) == EQIntersections::E_One)
                        {
							if (vAux == vA || vAux == vB) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vOut2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vD, vA), vAux) == EQIntersections::E_One)
                        {
							if (vAux == vD || vAux == vA) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vOut2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else
                            return EQIntersections::E_One;
                    }
                    else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(ls.A))) // ls.A is in vDvA edge (but not a vertex)
                    {
                        vOut1 = ls.A;

                         // ls intersects other edges
                        EQIntersections value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vB, vC), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
							if (vAux == vB || vAux == vC) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vOut2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vC, vD), vAux) == EQIntersections::E_One)
                        {
							if (vAux == vC || vAux == vD) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vOut2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vA, vB), vAux) == EQIntersections::E_One)
                        {
							if (vAux == vA || vAux == vB) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vOut2 = vAux;
                            return EQIntersections::E_Two;
                        }
                        else
                            return EQIntersections::E_One;
                    }
                    else // ls.A is strictly inside quadrilateral: is not in a vertex or edge.
                    {
                        EQIntersections value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vA, vB), vAux);
                        if (value2 == EQIntersections::E_One)
                            vOut1 = vAux;
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vB, vC), vAux) == EQIntersections::E_One)
                            vOut1 = vAux;
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vC, vD), vAux)== EQIntersections::E_One)
                            vOut1 = vAux;
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vD, vA), vAux)== EQIntersections::E_One)
                            vOut1 = vAux;
                        else                  // Something is wrong, if one point is inside and the other is outside,
                            QE_ASSERT(false); // there must be intersections.

                        return EQIntersections::E_One;
                    }
                }
                else // ls.B is inside quadrilateral (A is outside)
                {
                    if (ls.B == vA) // ls.B is vA vertex
                    {
                        // ls intersects opposite edges
                        EQIntersections value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vB, vC), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
                            vOut1 = vAux;
                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vC, vD), vAux) == EQIntersections::E_One)
                        {
                            vOut1 = vAux;
                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                        else
                        {
                            vOut1 = ls.B;
                            return EQIntersections::E_One;
                        }
                    }
                    else if (ls.B == vB) // ls.B is vB vertex
                    {
                        // ls intersects opposite edges
                        EQIntersections value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vC, vD), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
                            vOut1 = vAux;
                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vD, vA), vAux) == EQIntersections::E_One)
                        {
                            vOut1 = vAux;
                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                        else
                        {
                            vOut1 = ls.B;
                            return EQIntersections::E_One;
                        }
                    }
                    else if (ls.B == vC) // ls.B is vC vertex
                    {
                        // ls intersects opposite edges
                        EQIntersections value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vD, vA), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
                            vOut1 = vAux;
                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vA, vB), vAux) == EQIntersections::E_One)
                        {
                            vOut1 = vAux;
                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                        else
                        {
                            vOut1 = ls.B;
                            return EQIntersections::E_One;
                        }
                    }
                    else if (ls.B == vD) // ls.B is vB vertex
                    {
                        // ls intersects opposite edges
                        EQIntersections value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vA, vB), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
                            vOut1 = vAux;
                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vB, vC), vAux) == EQIntersections::E_One)
                        {
                            vOut1 = vAux;
                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                        else
                        {
                            vOut1 = ls.B;
                            return EQIntersections::E_One;
                        }
                    }
                    else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vA, vB).MinDistance(ls.B))) // ls.B is in vAvB edge (but not a vertex)
                    {
                        // ls intersects the other edges
                        EQIntersections value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vB, vC), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
                            vOut1 = vAux;

							if (vAux == vB || vAux == vC) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vC, vD), vAux) == EQIntersections::E_One)
                        {
                            vOut1 = vAux;

							if (vAux == vC || vAux == vD) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vD, vA), vAux) == EQIntersections::E_One)
                        {
                            vOut1 = vAux;

							if (vAux == vD || vAux == vA) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                        else // There is no other intersection
                        {
                            vOut1 = ls.B;
                            return EQIntersections::E_One;
                        }
                    }
                    else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vB, vC).MinDistance(ls.B))) // ls.B is in vBvC edge (but not a vertex)
                    {
                        // ls intersects the other edges
                        EQIntersections value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vA, vB), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
                            vOut1 = vAux;

							if (vAux == vA || vAux == vB) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vC, vD), vAux) == EQIntersections::E_One)
                        {
                            vOut1 = vAux;

							if (vAux == vC || vAux == vD) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vD, vA), vAux) == EQIntersections::E_One)
                        {
                            vOut1 = vAux;

							if (vAux == vD || vAux == vA) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                        else // There is no other intersection
                        {
                            vOut1 = ls.B;
                            return EQIntersections::E_One;
                        }
                    }
                    else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vC, vD).MinDistance(ls.B))) // ls.B is in vCvD edge (but not a vertex)
                    {
                        // ls intersects the other edges
                        EQIntersections value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vB, vC), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
                            vOut1 = vAux;

							if (vAux == vB || vAux == vC) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vA, vB), vAux) == EQIntersections::E_One)
                        {
                            vOut1 = vAux;

							if (vAux == vA || vAux == vB) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vD, vA), vAux) == EQIntersections::E_One)
                        {
                            vOut1 = vAux;

							if (vAux == vD || vAux == vA) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                        else // There is no other intersection
                        {
                            vOut1 = ls.B;
                            return EQIntersections::E_One;
                        }
                    }
                    else if (QFloat::IsZero(QLineSegment<VectorTypeParam>(vD, vA).MinDistance(ls.B))) // ls.B is in vDvA edge (but not a vertex)
                    {
                        // ls intersects the other edges
                        EQIntersections value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vB, vC), vAux);
                        if (value2 == EQIntersections::E_One)
                        {
                            vOut1 = vAux;

							if (vAux == vB || vAux == vC) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vC, vD), vAux) == EQIntersections::E_One)
                        {
                            vOut1 = vAux;

							if (vAux == vC || vAux == vD) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vA, vB), vAux) == EQIntersections::E_One)
                        {
                            vOut1 = vAux;

							if (vAux == vA || vAux == vB) // Both intersections are in the same edge
								return EQIntersections::E_One;

                            vOut2 = ls.B;
                            return EQIntersections::E_Two;
                        }
                        else // There is no other intersection
                        {
                            vOut1 = ls.B;
                            return EQIntersections::E_One;
                        }
                    }
                    else // ls.B is strictly inside quadrilateral: is not in a vertex or edge.
                    {
                        EQIntersections value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vA, vB), vAux);
                        if (value2 == EQIntersections::E_One)
                            vOut1 = vAux;
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vB, vC), vAux) == EQIntersections::E_One)
                            vOut1 = vAux;
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vC, vD), vAux)== EQIntersections::E_One)
                            vOut1 = vAux;
                        else if (value2 = ls.IntersectionPoint(QLineSegment3D<VectorTypeParam>(vD, vA), vAux)== EQIntersections::E_One)
                            vOut1 = vAux;
                        else                  // Something is wrong, if one point is inside and the other is outside,
                            QE_ASSERT(false); // there must be intersections.

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

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |    CONSTANTS DEFINITIONS	 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

template <class VectorType>
const QLineSegment3D<VectorType> QLineSegment3D<VectorType>::UnitLine(VectorType::ZeroVector, VectorType::UnitVectorX);

template <class VectorType>
const QLineSegment3D<VectorType> QLineSegment3D<VectorType>::LineZero(VectorType::ZeroVector, VectorType::ZeroVector);

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QLINESEGMENT3D__
