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

#ifndef __QRAY3D__
#define __QRAY3D__

#include "QRay.h"
#include "QVector3.h"
#include "QLineSegment.h"
#include "QPlane.h"
#include "EQSpaceRelation.h"
#include "QBaseOrb.h"
#include "QBaseTriangle.h"
#include "QBaseHexahedron.h"
#include "SQPoint.h"

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
/// Represents a ray in 3D space, which consists of a origin point or position, and a direction.<br>
/// The direction symbolizes a line with only one end (which coincides with the origin) and that extends to the infinite.
/// </summary>
template <class VectorType>
class QDllExport QRay3D : public QRay<VectorType, QVector3>
{
    // BASE CLASS USINGS
    // ------------------
public:

    using QRay<VectorType, QVector3>::Intersection;
    using QRay<VectorType, QVector3>::IntersectionPoint;


	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	inline QRay3D()
    {
    }

    /// <summary>
	/// Copy constructor.
	/// </summary>
	/// <param name="ray">[IN] The 3D ray from which we want to create a copy in the resident 3D ray.</param>
	inline QRay3D(const QRay3D<VectorType> &ray) : QRay<VectorType, QVector3>(ray)
	{
	}

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <param name="ray">[IN] The 3D ray in which we want resident 3D ray to be based.</param>
    inline QRay3D(const QBaseRay<VectorType, QVector3> &ray) : QRay<VectorType, QVector3>(ray)
    {
    }

    /// <summary>
    /// Constructor that receives the ray's position and direction.
    /// </summary>
    /// <param name="vOrigin">[IN] Ray's position.</param>
    /// <param name="vDirection">[IN] Ray's direction.</param>
    /// <remarks>
    /// The direction vector must be normalized to construct the ray properly.
    /// </remarks>
    inline QRay3D(const VectorType &vOrigin, const QVector3 &vDirection) : QRay<VectorType, QVector3>(vOrigin, vDirection)
    {
    }


    // PROPERTIES
    // ---------------
public:

    /// <summary>
	/// Gets a ray placed at the coordinate origin and whose direction vector is null.
	/// </summary>
	/// <returns>
    /// The null ray.
    /// </returns>
    inline static const QRay3D<VectorType>& GetRayZero()
    {
        static const QRay3D<VectorType> RAY_ZERO(VectorType::GetZeroVector(), QVector3::GetZeroVector());
        return RAY_ZERO;
    }

    /// <summary>
	/// Gets a ray placed at the coordinate origin and whose direction vector is in X growing direction.
	/// </summary>
	/// <returns>
    /// A ray that points to X direction.
    /// </returns>
    inline static const QRay3D<VectorType>& GetRayX()
    {
        static const QRay3D<VectorType> RAY_X(VectorType::GetZeroVector(), QVector3::GetUnitVectorX());
        return RAY_X;
    }

    /// <summary>
	/// Gets a ray placed at the coordinate origin and whose direction vector is in Y growing direction.
	/// </summary>
	/// <returns>
    /// A ray that points to Y direction.
    /// </returns>
    inline static const QRay3D<VectorType>& GetRayY()
    {
        static const QRay3D<VectorType> RAY_Y(VectorType::GetZeroVector(), QVector3::GetUnitVectorY());
        return RAY_Y;
    }

    /// <summary>
	/// Gets a ray placed at the coordinate origin and whose direction vector is in Z growing direction.
	/// </summary>
	/// <returns>
    /// A ray that points to Z direction.
    /// </returns>
    inline static const QRay3D<VectorType>& GetRayZ()
    {
        static const QRay3D<VectorType> RAY_Z(VectorType::GetZeroVector(), QVector3::GetUnitVectorZ());
        return RAY_Z;
    }


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Assign operator that receives another ray.
    /// </summary>
    /// <param name="ray">[IN] An existing ray.</param>
    /// <returns>
    /// A reference to this ray, after assignation.
    /// </returns>
    inline QRay3D& operator=(const QBaseRay<VectorType, QVector3> &ray)
    {
        QBaseRay<VectorType, QVector3>::operator=(ray);
        return *this;
    }

    /// <summary>
    /// Checks if resident ray intersects with the provided one.
    /// </summary>
    /// <param name="ray">[IN] The ray whose intersection with resident one will be checked.</param>
    /// <returns>
    /// True if both rays intersect, false otherwise.
    /// </returns>
    /// <remarks>
    /// If both rays intesect, the intersection point must verify both vectorial ecuations:
    ///
    /// \f$ P \equiv P_1 + t_1 \cdot D_1 \f$
    ///
    /// \f$ P \equiv P_2 + t_2 \cdot D_2 \f$
    ///
    /// This ecuation is solved via vectorial products as follovs:
    ///
    /// \f$ t_1 = \frac{\begin{vmatrix} (P_2 - P_1)_x & (P_2 - P_1)_y & (P_2 - P_1)_z \\ D_{2x} & D_{2y} & D_{2z}
    /// \\ (D_1 \times D_2)_x & (D_1 \times D_2)_y & (D_1 \times D_2)_z \end{vmatrix}}{\left | D_1 \times D_2 \right |^2} \f$
    ///
    /// \f$ t_2 = \frac{\begin{vmatrix} (P_2 - P_1)_x & (P_2 - P_1)_y & (P_2 - P_1)_z \\ D_{1x} & D_{1y} & D_{1z}
    /// \\ (D_1 \times D_2)_x & (D_1 \times D_2)_y & (D_1 \times D_2)_z \end{vmatrix}}{\left | D_1 \times D_2 \right |^2} \f$
    ///
    /// Both \f$ t_1 \f$ and \f$ t_2 \f$ are forced to be greater or equal to 0, to ensure ray direction is being followed, and
    /// it is verified that \f$ P_1 + t_1 \cdot D_1 = P_2 + t_2 \cdot D_2 \f$<br>
    /// When rays direction vector are parallel, one ray containing the other ray origin point is checked.
    /// </remarks>
    bool Intersection(const QBaseRay<VectorType, QVector3> &ray) const
    {
        // Direction vector of rays should not be null
        QE_ASSERT( !ray.Direction.IsZero() && !this->Direction.IsZero() );

        const QVector3& vP = QVector3(ray.Origin - this->Origin); // Difference of positions
        QVector3 vCross = this->Direction.CrossProduct(ray.Direction); // Cross product of directions

        const float_q &DENOMINATOR = vCross.GetSquaredLength(); // That is always positive

        if ( SQFloat::IsZero(DENOMINATOR) ) // Both directions are parallel
        {
            if ( this->Contains(ray.Origin) )
                return true;
            else
                return ( ray.template As<const QRay3D<VectorType> >().Contains(this->Origin) );
        }
        else // Directions are not parallel
        {
            const float_q NUMERATOR1 = vP.x * ray.Direction.y * vCross.z +   vP.y * ray.Direction.z * vCross.x +
                                       vP.z * ray.Direction.x * vCross.y - ( vP.z * ray.Direction.y * vCross.x +
                                       vP.y * ray.Direction.x * vCross.z +   vP.x * ray.Direction.z * vCross.y );

            if ( SQFloat::IsPositive(NUMERATOR1) ) // Remember that the denominator is always positive
            {
                const float_q &NUMERATOR2 = vP.x * this->Direction.y * vCross.z +   vP.y * this->Direction.z * vCross.x +
                                            vP.z * this->Direction.x * vCross.y - ( vP.z * this->Direction.y * vCross.x +
                                            vP.y * this->Direction.x * vCross.z +   vP.x * this->Direction.z * vCross.y );

                if ( SQFloat::IsPositive(NUMERATOR2) ) // Remember that the denominator is always positive
                {
                    const QVector3 &P_INT1 = QVector3(this->Origin) + (NUMERATOR1/DENOMINATOR) * this->Direction;
                    const QVector3 &P_INT2 = QVector3(ray.Origin) + (NUMERATOR2/DENOMINATOR) * ray.Direction;

                    if (P_INT1 == P_INT2)
                        return true;
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return false;
        }
    }

    /// <summary>
	/// Checks if resident ray and provided line segment intersects.
	/// </summary>
    /// <remarks>
    /// A ray with direction from A to B with origin in A is constructed.<br>
    /// If both rays intersects, the intersection point must verify both vectorial ecuations:
    ///
    /// \f$ P \equiv P_1 + t_1 \cdot D_1 \f$
    ///
    /// \f$ P \equiv P_2 + t_2 \cdot D_2 \f$
    ///
    /// This ecuation is solved via vectorial products as follovs:
    ///
    /// \f$ t_1 = \frac{\begin{vmatrix} (P_2 - P_1)_x & (P_2 - P_1)_y & (P_2 - P_1)_z \\ D_{2x} & D_{2y} & D_{2z}
    /// \\ (D_1 \times D_2)_x & (D_1 \times D_2)_y & (D_1 \times D_2)_z \end{vmatrix}}{\left | D_1 \times D_2 \right |^2} \f$
    ///
    /// \f$ t_2 = \frac{\begin{vmatrix} (P_2 - P_1)_x & (P_2 - P_1)_y & (P_2 - P_1)_z \\ D_{1x} & D_{1y} & D_{1z}
    /// \\ (D_1 \times D_2)_x & (D_1 \times D_2)_y & (D_1 \times D_2)_z \end{vmatrix}}{\left | D_1 \times D_2 \right |^2} \f$
    ///
    /// Both \f$ t_1 \f$ and \f$ t_2 \f$ are forced to be greater or equal to 0, to ensure ray direction is being followed,
    /// and \f$ t_2 \f$ is forced to be in [0, 1] interval, to ensure the point is inside segment.<br>
    /// Finally it's verified that \f$ P_1 + t_1 \cdot D_1 = P_2 + t_2 \cdot D_2 \f$<br>
    /// When rays direction vector are parallel, one ray containing the other ray origin point is checked.
    /// </remarks>
	/// <param name="segment">[IN] The line segment whose intersection with resident ray will be checked.</param>
	/// <returns>
    /// True if line segment and resident ray intersects, false otherwise.
	/// </returns>
    bool Intersection(const QBaseLineSegment<VectorType> &segment) const
    {
        // Direction vector of ray should not be null and the length of the segment should be greater than zero
        QE_ASSERT( segment.A != segment.B && !this->Direction.IsZero() );

        // Same method that intersection with other ray. A ray with Position in A and direction B-A is created.
        // After intersection method, the ray parameter is forced to be in [0, 1] interval.
        QBaseRay<QVector3, QVector3> ray(QVector3(segment.A), QVector3(segment.B - segment.A));

        const QVector3& vP = QVector3(segment.A - this->Origin); // Difference of positions

        QVector3 vCross = this->Direction.CrossProduct(ray.Direction); // Cross product of directions

        const float_q &DENOMINATOR = vCross.GetSquaredLength(); // That is always positive

        if ( SQFloat::IsZero(DENOMINATOR) ) // Both directions are parallels
        {
            if ( this->Contains(segment.A) )
                return true;
            else
                return this->Contains(segment.B);
        }
        else // Directions are not parallel
        {
            const float_q NUMERATOR1 = vP.x * ray.Direction.y * vCross.z +   vP.y * ray.Direction.z * vCross.x +
                                       vP.z * ray.Direction.x * vCross.y - ( vP.z * ray.Direction.y * vCross.x +
                                       vP.y * ray.Direction.x * vCross.z +   vP.x * ray.Direction.z * vCross.y );

            if ( SQFloat::IsPositive(NUMERATOR1) ) // Remember that the denominator is always positive
            {
                const float_q &NUMERATOR2 = vP.x * this->Direction.y * vCross.z +   vP.y * this->Direction.z * vCross.x +
                                            vP.z * this->Direction.x * vCross.y - ( vP.z * this->Direction.y * vCross.x +
                                            vP.y * this->Direction.x * vCross.z +   vP.x * this->Direction.z * vCross.y );

                const float_q PARAM2 = NUMERATOR2 / DENOMINATOR;
                if ( SQFloat::IsPositive(NUMERATOR2) && SQFloat::IsLessOrEquals(PARAM2, SQFloat::_1) ) // Remember that the denominator is always positive
                {
                    const QVector3 &P_INT1 = QVector3(this->Origin) + (NUMERATOR1 / DENOMINATOR) * this->Direction;
                    const QVector3 &P_INT2 = ray.Origin + PARAM2 * ray.Direction;

                    if (P_INT1 == P_INT2)
                        return true;
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return false;
        }
    }

    /// <summary>
    /// Checks if resident ray intersects with the provided plane.<br>
    /// Intersection point \f$ P_0 \f$ must verify both ecuations:
    ///
    /// Ray equation: \f$ P_0 = P + t \cdot V \f$
    ///
    /// Plane equation: \f$ aP_{0x} + bP_{0y} + cP_{0z} + d = N \cdot P_0 + d = 0 \f$
    ///
    /// That is:
    ///
    /// \f$ t = \frac{-(d + N \cdot P)}{N \cdot V} \f$
    ///
    /// - If \f$ N \cdot V = 0 \f$ ray and plane are parallels.
    ///  - Then, if \f$ d + N \cdot P = 0 \f$ ray lies on plane, otherwise there are no intersection.
    /// - If t < 0, there are no intersection (the ray straight line intersects the plane backwards the ray origin).
    /// </summary>
    /// <param name="plane">[IN] The plane we want check if intersects with resident ray.</param>
    /// <returns>
    /// True if plane and ray intersects, false otherwise.
    /// </returns>
    inline bool Intersection(const QBasePlane &plane) const
    {
        // The plane shouldn't be null
        QE_ASSERT( !(SQFloat::IsZero(plane.a) && SQFloat::IsZero(plane.b) && SQFloat::IsZero(plane.c)) );

        // The direction vector of the ray mustn't be null
        QE_ASSERT( !this->Direction.IsZero() );

        const QVector3 vN(plane.a, plane.b, plane.c); // Normal to plane (Normalize not necessary)
        const QVector3 vP(this->Origin); // Homogeinizing vector types

        const float_q &NUMERATOR = -(plane.d + vP.DotProduct(vN));
        const float_q &DENOMINATOR = this->Direction.DotProduct(vN);

        if ( SQFloat::IsZero(DENOMINATOR) )
            return SQFloat::IsZero(NUMERATOR);
        else
            return SQFloat::IsPositive(NUMERATOR / DENOMINATOR);
    }

    /// <summary>
    /// Checks if resident ray intersects with the provided triangle.
    /// </summary>
    /// <param name="triangle">[IN] The triangle whose intersection with resident ray will be checked.</param>
    /// <returns>
    /// True if ray intersect triangle, false otherwise.
    /// </returns>
    inline bool Intersection(const QBaseTriangle<VectorType> &triangle) const
    {
        // Vertices of the triangle must not coincide
        QE_ASSERT( triangle.A != triangle.B && 
                   triangle.B != triangle.C &&
                   triangle.C != triangle.A );

        // The direction vector of the ray shouldn't be null
        QE_ASSERT( !this->Direction.IsZero() )

        // Plane that contains triangle
        QPlane auxPlane(triangle.A, triangle.B, triangle.C);

        VectorType vIntersectionPoint;

        const EQIntersections &NUM_INTERSECT = this->IntersectionPoint(auxPlane, vIntersectionPoint);
        if (NUM_INTERSECT == EQIntersections::E_Infinite) // Ray and plane are coplanar.
        {
            return ( this->Intersection(triangle.A, triangle.B) ||
                     this->Intersection(triangle.B, triangle.C) ||
                     this->Intersection(triangle.C, triangle.A) );
        }
        else if (NUM_INTERSECT == EQIntersections::E_One) // Ray and plane intersects in one point
        {
            return this->PointInsideTriangle(triangle, vIntersectionPoint);
        }
        else
            return false;
    }

    /// <summary>
    /// Checks if resident ray intersects with the provided hexahedron.<br>
    /// If the origin of the ray lies on one of the hexahedron faces, we consider there is an intersection.
    /// </summary>
    /// <param name="hexahedron">[IN] The hexahedron we want check if intersects with resident ray.</param>
    /// <returns>
    /// True if hexahedron and ray intersects, false otherwise.
    /// </returns>
    inline bool Intersection(const QBaseHexahedron<VectorType> &hexahedron) const
    {
        // The direction vector of the ray mustn't be null
        QE_ASSERT( !this->Direction.IsZero() );

         // Checks if there is an intersection with any face.
        return (this->Intersection(hexahedron.A, hexahedron.B, hexahedron.C, hexahedron.D) ||
                this->Intersection(hexahedron.E, hexahedron.F, hexahedron.G, hexahedron.H) ||
                this->Intersection(hexahedron.A, hexahedron.B, hexahedron.H, hexahedron.E) ||
                this->Intersection(hexahedron.B, hexahedron.C, hexahedron.G, hexahedron.H) ||
                this->Intersection(hexahedron.A, hexahedron.D, hexahedron.F, hexahedron.E) ||
                this->Intersection(hexahedron.C, hexahedron.D, hexahedron.F, hexahedron.G));
    }


    /// <summary>
	/// Computes the intersection point between resident and provided ray, if it exists.
	/// </summary>
    /// <remarks>
	/// Rays must be normalized to ensure correct results.<br>
	/// If there's no intersection point, or the rays are totally or parcially coincident,
	/// the output parameter used for storing that point won't be modified.
    ///
    /// If both rays intesect, the intersection point must verify both vectorial ecuations:
    ///
    /// \f$ P \equiv P_1 + t_1 \cdot D_1 \f$
    ///
    /// \f$ P \equiv P_2 + t_2 \cdot D_2 \f$
    ///
    /// This ecuation is solved via vectorial products as follovs:
    ///
    /// \f$ t_1 = \frac{\begin{vmatrix} (P_2 - P_1)_x & (P_2 - P_1)_y & (P_2 - P_1)_z \\ D_{2x} & D_{2y} & D_{2z}
    /// \\ (D_1 \times D_2)_x & (D_1 \times D_2)_y & (D_1 \times D_2)_z \end{vmatrix}}{\left | D_1 \times D_2 \right |^2} \f$
    ///
    /// \f$ t_2 = \frac{\begin{vmatrix} (P_2 - P_1)_x & (P_2 - P_1)_y & (P_2 - P_1)_z \\ D_{1x} & D_{1y} & D_{1z}
    /// \\ (D_1 \times D_2)_x & (D_1 \times D_2)_y & (D_1 \times D_2)_z \end{vmatrix}}{\left | D_1 \times D_2 \right |^2} \f$
    ///
    /// Both \f$ t_1 \f$ and \f$ t_2 \f$ are forced to be greater or equal to 0, to ensure ray direction is being followed, and
    /// it is verified that:
    ///
    /// \f$ P_1 + t_1 \cdot D_1 = P_2 + t_2 \cdot D_2 \f$
    ///
    /// When rays direction vector are parallel, one ray containing the other ray origin point is checked.
	/// </remarks>
	/// <param name="ray">[IN] The ray whose intersection with resident ray will be checked.</param>
	/// <param name="vIntersection">[OUT] The point where they intersect, if they do.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the rays, and can take
    /// the following values: E_None, E_One and E_Infinite.
	/// </returns>
    EQIntersections IntersectionPoint(const QBaseRay<VectorType, QVector3> &ray, VectorType &vIntersection) const
    {
        // The direction vector of the ray shouldn't be null
        QE_ASSERT( !this->Direction.IsZero() && !ray.Direction.IsZero() );

        const VectorType &vP(ray.Origin - this->Origin); // Difference of positions
        QVector3 vCross = this->Direction.CrossProduct(ray.Direction); // Cross product of directions

        const float_q &DENOMINATOR = vCross.GetSquaredLength(); // That is always positive

        if ( SQFloat::IsZero(DENOMINATOR) ) // Both directions are parallel
        {
            if (this->Origin == ray.Origin)
            {
                if ( (this->Direction + ray.Direction) == QVector3::GetZeroVector() ) // Directions are opposite (are supossed normalized)
                {
                    vIntersection.x = this->Origin.x;
                    vIntersection.y = this->Origin.y;
                    vIntersection.z = this->Origin.z;
                    return EQIntersections::E_One;
                }
                else
                    return EQIntersections::E_Infinite; //Both rays are the same
            }
            else if ( this->Contains(ray.Origin) || ray.template As<const QRay3D<VectorType> >().Contains(this->Origin) )
                return EQIntersections::E_Infinite;
            else
                return EQIntersections::E_None;
        }
        else // Directions are not parallel
        {
            const float_q NUMERATOR1 = vP.x * ray.Direction.y * vCross.z +   vP.y * ray.Direction.z * vCross.x +
                                       vP.z * ray.Direction.x * vCross.y - ( vP.z * ray.Direction.y * vCross.x +
                                       vP.y * ray.Direction.x * vCross.z +   vP.x * ray.Direction.z * vCross.y );

            if ( SQFloat::IsPositive(NUMERATOR1) ) // Remember that fDenominator is always positive
            {
                const float_q &NUMERATOR2 = vP.x * this->Direction.y * vCross.z +   vP.y * this->Direction.z * vCross.x +
                                            vP.z * this->Direction.x * vCross.y - ( vP.z * this->Direction.y * vCross.x +
                                            vP.y * this->Direction.x * vCross.z +   vP.x * this->Direction.z * vCross.y );

                if ( SQFloat::IsPositive(NUMERATOR2) ) // Remember that fDenominator is always positive
                {
                    const QVector3 &P_INT1 = QVector3(this->Origin) + (NUMERATOR1 / DENOMINATOR) * this->Direction;
                    const QVector3 &P_INT2 = QVector3(ray.Origin) + (NUMERATOR2 / DENOMINATOR) * ray.Direction;

                    if (P_INT1 == P_INT2)
                    {
                        vIntersection.x = P_INT1.x;
                        vIntersection.y = P_INT1.y;
                        vIntersection.z = P_INT1.z;
                        return EQIntersections::E_One;
                    }
                    else
                        return EQIntersections::E_None;
                }
                else
                    return EQIntersections::E_None;
            }
            else
                return EQIntersections::E_None;
        }
    }

    /// <summary>
	/// Computes the intersection point between resident ray and provided line segment, if it exists.
	/// </summary>
    /// <remarks>
    /// A ray with direction from A to B with origin in A is constructed.<br>
    /// If both rays intersects, the intersection point must verify both vectorial ecuations:
    ///
    /// \f$ P \equiv P_1 + t_1 \cdot D_1 \f$
    ///
    /// \f$ P \equiv P_2 + t_2 \cdot D_2 \f$
    ///
    /// This ecuation is solved via vectorial products as follovs:
    ///
    /// \f$ t_1 = \frac{\begin{vmatrix} (P_2 - P_1)_x & (P_2 - P_1)_y & (P_2 - P_1)_z \\ D_{2x} & D_{2y} & D_{2z}
    /// \\ (D_1 \times D_2)_x & (D_1 \times D_2)_y & (D_1 \times D_2)_z \end{vmatrix}}{\left | D_1 \times D_2 \right |^2} \f$
    ///
    /// \f$ t_2 = \frac{\begin{vmatrix} (P_2 - P_1)_x & (P_2 - P_1)_y & (P_2 - P_1)_z \\ D_{1x} & D_{1y} & D_{1z}
    /// \\ (D_1 \times D_2)_x & (D_1 \times D_2)_y & (D_1 \times D_2)_z \end{vmatrix}}{\left | D_1 \times D_2 \right |^2} \f$
    ///
    /// Both \f$ t_1 \f$ and \f$ t_2 \f$ are forced to be greater or equal to 0, to ensure ray direction is being followed,
    /// and \f$ t_2 \f$ is forced to be in [0, 1] interval, to ensure the point is inside segment.<br>
    /// Finally it's verified that:
    ///
    /// \f$ P_1 + t_1 \cdot D_1 = P_2 + t_2 \cdot D_2 \f$
    ///
    /// When rays direction vector are parallel, one ray containing the other ray origin point is checked.<br>
	/// - If there's no intersection point, the output parameters won't be modified.
	/// - If there's one intersection point, output parameter is filled with the intersection point.
    /// - If there are infinite intersection points, the output parameters won't be modified.
	/// </remarks>
	/// <param name="segment">[IN] The line segment whose intersection with resident ray will be checked.</param>
	/// <param name="vIntersection">[OUT] The intersection point with line segment, if it exists.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the ray and the quadrilateral, and can take
    /// the following values: E_None, E_One or E_Infinite.
	/// </returns>
    EQIntersections IntersectionPoint (const QBaseLineSegment<VectorType> &segment, VectorType &vIntersection) const
    {
        // The direction vector of the ray shouldn't be null
        QE_ASSERT( !this->Direction.IsZero() );

        // The legth of the line shouldn't equal zero
        QE_ASSERT( segment.A != segment.B );

        // Same method that intersection with other ray. A ray with Position in A and direction B-A is created.
        // After intersection method, the ray parameter is forced to be in [0, 1] interval.
        QBaseRay<VectorType, QVector3> ray( segment.A, QVector3(segment.B - segment.A) );

        const VectorType &vP(segment.A - this->Origin); // Difference of positions

        QVector3 vCross = this->Direction.CrossProduct(ray.Direction); // Cross product of directions

        const float_q &DENOMINATOR = vCross.GetSquaredLength(); // That is always positive

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
                    vIntersection.x = segment.A.x;
                    vIntersection.y = segment.A.y;
                    vIntersection.z = segment.A.z;
                    return EQIntersections::E_One;
                }
                else
                    return EQIntersections::E_Infinite;
            }
            else if ( B_IS_IN_RAY )
            {
                if (segment.B == this->Origin)
                {
                    vIntersection.x = segment.B.x;
                    vIntersection.y = segment.B.y;
                    vIntersection.z = segment.B.z;
                    return EQIntersections::E_One;
                }
                else
                    return EQIntersections::E_Infinite;
            }
            else
                return EQIntersections::E_None;
        }
        else // Directions are not parallel
        {
            const float_q NUMERATOR1 = vP.x * ray.Direction.y * vCross.z +   vP.y * ray.Direction.z * vCross.x +
                                       vP.z * ray.Direction.x * vCross.y - ( vP.z * ray.Direction.y * vCross.x +
                                       vP.y * ray.Direction.x * vCross.z +   vP.x * ray.Direction.z * vCross.y );

            if ( SQFloat::IsPositive(NUMERATOR1) ) // Remember that fDenominator is always positive
            {
                const float_q &NUMERATOR2 = vP.x * this->Direction.y * vCross.z +   vP.y * this->Direction.z * vCross.x +
                                            vP.z * this->Direction.x * vCross.y - ( vP.z * this->Direction.y * vCross.x +
                                            vP.y * this->Direction.x * vCross.z +   vP.x * this->Direction.z * vCross.y );

                const float_q PARAM2 = NUMERATOR2 / DENOMINATOR;
                if ( SQFloat::IsPositive(NUMERATOR2) && SQFloat::IsLessOrEquals(PARAM2, SQFloat::_1) ) // Remember that fDenominator is always positive
                {
                    const QVector3 &P_INT1 = QVector3(this->Origin) + (NUMERATOR1 / DENOMINATOR) * this->Direction;
                    const QVector3 &P_INT2 = QVector3(ray.Origin) + PARAM2 * ray.Direction;

                    if (P_INT1 == P_INT2)
                    {
                        vIntersection.x = P_INT1.x;
                        vIntersection.y = P_INT1.y;
                        vIntersection.z = P_INT1.z;
                        return EQIntersections::E_One;
                    }
                    else
                        return EQIntersections::E_None;
                }
                else
                    return EQIntersections::E_None;
            }
            else
                return EQIntersections::E_None;
        }
    }

    /// <summary>
    /// Checks if resident ray intersects with the provided plane, calculating the intersection point.<br>
    /// Intersection point \f$ P_0 \f$ must verify both ecuations:
    ///
    /// Ray equation: \f$ P_0 = P + t \cdot V \f$
    ///
    /// Plane equation: \f$ aP_{0x} + bP_{0y} + cP_{0z} + d = N \cdot P_0 + D = 0 \f$
    ///
    /// That is:
    ///
    /// \f$ t = \frac{-(d + N \cdot P)}{N \cdot V} \f$
    ///
    /// - If \f$ N \cdot V = 0 \f$ ray and plane are parallels.
    ///  - Then, if \f$ d + N \cdot P = 0 \f$ ray lies on plane, otherwise there are no intersection.
    /// - If t < 0, there are no intersection (the ray straight line intersects the plane backwards the ray position).
    /// </summary>
    /// <param name="plane">[IN] The plane we want check if intersects with resident ray.</param>
    /// <param name="vIntersection">[OUT] The point where they intersect, if they do.</param>
    /// <returns>
    /// An enumerated value which represents the number of intersections between the ray and the plane, and can take
    /// the following values: E_None, E_One and E_Infinite.<br>
    /// If there are no intersections or ray lies on plane, the output parameter is not modified.
    /// </returns>
    EQIntersections IntersectionPoint(const QBasePlane &plane, VectorType &vIntersection) const
    {
        // The direction vector of the ray shouldn't be null
        QE_ASSERT( !this->Direction.IsZero() );

        // The plane shouldn't be null
        QE_ASSERT( !(SQFloat::IsZero(plane.a) && SQFloat::IsZero(plane.b) && SQFloat::IsZero(plane.c)) );

        const VectorType vN( QVector3(plane.a, plane.b, plane.c) );

        const float_q &NUMERATOR = -(plane.d + this->Origin.DotProduct(vN));
        const float_q &DENOMINATOR = VectorType(this->Direction).DotProduct(vN);

        if ( SQFloat::IsZero(DENOMINATOR) ) // Ray is parallel to plane
            if ( SQFloat::IsZero(NUMERATOR) ) // Ray lies on plane
                return EQIntersections::E_Infinite;
            else // Ray is parallel but don't lies on plane.
                return EQIntersections::E_None;
        else if ( SQFloat::IsZero(NUMERATOR) ) // Ray origin lies on plane
        {
            vIntersection.x = this->Origin.x;
            vIntersection.y = this->Origin.y;
            vIntersection.z = this->Origin.z;
            return EQIntersections::E_One;
        }
        else
        {
            const float_q &PARAM = NUMERATOR / DENOMINATOR;
            if ( SQFloat::IsPositive(PARAM) ) // Intersection in one point.
            {
                vIntersection.x = this->Origin.x + PARAM * this->Direction.x;
                vIntersection.y = this->Origin.y + PARAM * this->Direction.y;
                vIntersection.z = this->Origin.z + PARAM * this->Direction.z;
                
                return EQIntersections::E_One;
            }
            else // No intersection
                return EQIntersections::E_None;
        }
    }

	/// <summary>
	/// Computes the intersection points between resident ray and provided triangle, if they exists.
	/// </summary>
    /// <remarks>
	/// - If there's no intersection point, the output parameter won't be modified.
	/// - If there's one intersection point, the output parameter stores it.
    /// - If there are two intersection points, the output parameter is filled with the closest to the origin point of the ray.
	/// </remarks>
	/// <param name="triangle">[IN] The triangle whose intersection with resident ray will be checked.</param>
	/// <param name="vIntersection">[OUT] Closest point to ray origin where they intersect, if they do.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the ray and the triangle, that can take
    /// the following values: E_None, E_One or E_Two.
	/// </returns>
    EQIntersections IntersectionPoint(const QBaseTriangle<VectorType> &triangle, VectorType &vIntersection) const
    {
        VectorType vAux;
        return this->IntersectionPoint(triangle, vIntersection, vAux);
    }


	/// <summary>
	/// Computes the intersection point between resident ray and provided triangle, if it exists.
	/// </summary>
    /// <remarks>
	/// - If there's no intersection point, the output parameters won't be modified.
	/// - If there's one intersection point, the second output parameter won't be modified,
	/// and first output parameter is filled with the intersection point.
    /// - If there are two intersection points, both output parameters are filled with the intersection points, storing
    /// in the first output parameter the closest to the origin point of the ray.
	/// </remarks>
	/// <param name="triangle">[IN] The triangle whose intersection with resident ray will be checked.</param>
	/// <param name="vIntersection1">[OUT] First point where they intersect, if they do.</param>
	/// <param name="vIntersection2">[OUT] Second point where they intersect, if they do.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the ray and the triangle, and can take
    /// the following values: E_None, E_One or E_Two.
	/// </returns>
    EQIntersections IntersectionPoint(const QBaseTriangle<VectorType> &triangle, VectorType &vIntersection1, VectorType &vIntersection2) const
    {
        // Plane that contains triangle
        QPlane auxP(triangle.A, triangle.B, triangle.C);

        VectorType vAux;

        const EQIntersections &NUM_INTERSECT = this->IntersectionPoint(auxP, vAux);
        if (NUM_INTERSECT == EQIntersections::E_Infinite) // Ray and plane are coplanar.
        {
            if ( PointInsideTriangle(triangle, this->Origin) ) // Ray origin is inside triangle
            {
                if (this->Origin == triangle.A) // Ray origin is A triangle vertex
                {
                    vIntersection1.x = this->Origin.x;
                    vIntersection1.y = this->Origin.y;
                    vIntersection1.z = this->Origin.z;

                    // Checks intersection with opposite edge
                    if (this->IntersectionPoint(triangle.B, triangle.C, vAux) == EQIntersections::E_None) // No intersection found
                        return EQIntersections::E_One;
                    else // Intersection found
                    {
                        vIntersection2.x = vAux.x;
                        vIntersection2.y = vAux.y;
                        vIntersection2.z = vAux.z;
                        return EQIntersections::E_Two;
                    }
                }
                else if (this->Origin == triangle.B) // Ray origin is B triangle vertex
                {
                    vIntersection1.x = this->Origin.x;
                    vIntersection1.y = this->Origin.y;
                    vIntersection1.z = this->Origin.z;

                   // Checks intersection with opposite edge
                    if (this->IntersectionPoint(triangle.C, triangle.A, vAux) == EQIntersections::E_None) // No intersection found
                        return EQIntersections::E_One;
                    else // Intersection found
                    {
                        vIntersection2.x = vAux.x;
                        vIntersection2.y = vAux.y;
                        vIntersection2.z = vAux.z;
                        return EQIntersections::E_Two;
                    }
                }
                else if (this->Origin == triangle.C) // Ray origin is C triangle vertex
                {
                    vIntersection1 = this->Origin;

                    // Checks intersection with opposite edge
                    if (this->IntersectionPoint(triangle.A, triangle.B, vAux) == EQIntersections::E_None) // No intersection found
                        return EQIntersections::E_One;
                    else // Intersection found
                    {
                        vIntersection2.x = vAux.x;
                        vIntersection2.y = vAux.y;
                        vIntersection2.z = vAux.z;
                        return EQIntersections::E_Two;
                    }
                }
                else if (SQFloat::IsZero(QLineSegment<VectorType>(triangle.A, triangle.B).MinDistance(this->Origin))) // Ray origin is in AB triangle edge
                {
                    if (this->IntersectionPoint(triangle.B, triangle.C, vAux) == EQIntersections::E_One) // Ray intersects other edge
                    {
                        if (vAux == triangle.B) // Intersection is in common vertex
                        {
                            vIntersection1.x = triangle.B.x;
                            vIntersection1.y = triangle.B.y;
                            vIntersection1.z = triangle.B.z;
                            return EQIntersections::E_One;
                        }
                        else // Intersection is in edge
                        {
                            vIntersection1.x = this->Origin.x;
                            vIntersection1.y = this->Origin.y;
                            vIntersection1.z = this->Origin.z;
                            vIntersection2.x = vAux.x;
                            vIntersection2.y = vAux.y;
                            vIntersection2.z = vAux.z;
                            return EQIntersections::E_Two;
                        }
                    }
                    else if (this->IntersectionPoint(triangle.C, triangle.A, vAux) == EQIntersections::E_One) // Ray intersects other edge
                    {
                        if (vAux == triangle.A) // Intersection is in common vertex
                        {
                            vIntersection1.x = triangle.A.x;
                            vIntersection1.y = triangle.A.y;
                            vIntersection1.z = triangle.A.z;
                            return EQIntersections::E_One;
                        }
                        else // Intersection is in edge
                        {
                            vIntersection1.x = this->Origin.x;
                            vIntersection1.y = this->Origin.y;
                            vIntersection1.z = this->Origin.z;
                            vIntersection2.x = vAux.x;
                            vIntersection2.y = vAux.y;
                            vIntersection2.z = vAux.z;
                            return EQIntersections::E_Two;
                        }
                    }
                    else // Ray don't intersects other edge
                    {
                        vIntersection1.x = this->Origin.x;
                        vIntersection1.y = this->Origin.y;
                        vIntersection1.z = this->Origin.z;
                        return EQIntersections::E_One;
                    }
                }
                else if (SQFloat::IsZero(QLineSegment<VectorType>(triangle.B, triangle.C).MinDistance(this->Origin))) // Ray origin is in BC triangle edge
                {
                    if (this->IntersectionPoint(triangle.C, triangle.A, vAux) == EQIntersections::E_One) // Ray intersects other edge
                    {
                        if (vAux == triangle.C) // Intersection is in common vertex
                        {
                            vIntersection1.x = triangle.C.x;
                            vIntersection1.y = triangle.C.y;
                            vIntersection1.z = triangle.C.z;
                            return EQIntersections::E_One;
                        }
                        else // Intersection is in edge
                        {
                            vIntersection1.x = this->Origin.x;
                            vIntersection1.y = this->Origin.y;
                            vIntersection1.z = this->Origin.z;
                            vIntersection2.x = vAux.x;
                            vIntersection2.y = vAux.y;
                            vIntersection2.z = vAux.z;
                            return EQIntersections::E_Two;
                        }
                    }
                    else if (this->IntersectionPoint(triangle.A, triangle.B, vAux) == EQIntersections::E_One) // Ray intersects other edge
                    {
                        if (vAux == triangle.B) // Intersection is in common vertex
                        {
                            vIntersection1.x = triangle.B.x;
                            vIntersection1.y = triangle.B.y;
                            vIntersection1.z = triangle.B.z;
                            return EQIntersections::E_One;
                        }
                        else // Intersection is in edge
                        {
                            vIntersection1.x = this->Origin.x;
                            vIntersection1.y = this->Origin.y;
                            vIntersection1.z = this->Origin.z;
                            vIntersection2.x = vAux.x;
                            vIntersection2.y = vAux.y;
                            vIntersection2.z = vAux.z;
                            return EQIntersections::E_Two;
                        }
                    }
                    else // Ray don't intersects other edge
                    {
                        vIntersection1.x = this->Origin.x;
                        vIntersection1.y = this->Origin.y;
                        vIntersection1.z = this->Origin.z;
                        return EQIntersections::E_One;
                    }
                }
                else if (SQFloat::IsZero(QLineSegment<VectorType>(triangle.C, triangle.A).MinDistance(this->Origin))) // Ray origin is in CA triangle edge
                {
                    if (this->IntersectionPoint(triangle.A, triangle.B, vAux) == EQIntersections::E_One) // Ray intersects other edge
                    {
                        if (vAux == triangle.A) // Intersection is in common vertex
                        {
                            vIntersection1.x = triangle.A.x;
                            vIntersection1.y = triangle.A.y;
                            vIntersection1.z = triangle.A.z;
                            return EQIntersections::E_One;
                        }
                        else // Intersection is in edge
                        {
                            vIntersection1.x = this->Origin.x;
                            vIntersection1.y = this->Origin.y;
                            vIntersection1.z = this->Origin.z;
                            vIntersection2.x = vAux.x;
                            vIntersection2.y = vAux.y;
                            vIntersection2.z = vAux.z;
                            return EQIntersections::E_Two;
                        }
                    }
                    else if (this->IntersectionPoint(triangle.B, triangle.C, vAux) == EQIntersections::E_One) // Ray intersects other edge
                    {
                        if (vAux == triangle.C) // Intersection is in common vertex
                        {
                            vIntersection1.x = triangle.C.x;
                            vIntersection1.y = triangle.C.y;
                            vIntersection1.z = triangle.C.z;
                            return EQIntersections::E_One;
                        }
                        else // Intersection is in edge
                        {
                            vIntersection1.x = this->Origin.x;
                            vIntersection1.y = this->Origin.y;
                            vIntersection1.z = this->Origin.z;
                            vIntersection2.x = vAux.x;
                            vIntersection2.y = vAux.y;
                            vIntersection2.z = vAux.z;
                            return EQIntersections::E_Two;
                        }
                    }
                    else // Ray don't intersects other edge
                    {
                        vIntersection1.x = this->Origin.x;
                        vIntersection1.y = this->Origin.y;
                        vIntersection1.z = this->Origin.z;
                        return EQIntersections::E_One;
                    }
                }
                else // Ray origin is strictly inside triangle (is not in a vertex or an edge
                {
                    if (this->IntersectionPoint(triangle.A, triangle.B, vAux) == EQIntersections::E_One ||
                        this->IntersectionPoint(triangle.B, triangle.C, vAux) == EQIntersections::E_One ||
                        this->IntersectionPoint(triangle.C, triangle.A, vAux) == EQIntersections::E_One )
                    {
                        vIntersection1.x = vAux.x;
                        vIntersection1.y = vAux.y;
                        vIntersection1.z = vAux.z;
                    }
                    else
                        QE_ASSERT(false)  // Something is wrong, if ray point is interior, it must be ONE intersection with a edge.

                    return EQIntersections::E_One;
                }
            }
            else // Ray origin is outside triangle
            {
                VectorType vPrevInt;
                bool bPrevInt = false;

                VectorType vAuxAB;
                EQIntersections numIntersectAB = this->IntersectionPoint(triangle.A, triangle.B, vAuxAB); // Checks intersection with AB edge
                if (numIntersectAB == EQIntersections::E_Infinite) // Ray contains AB edge
                {
                    // Looks for closest point to ray origin
                    if  ( (triangle.A - this->Origin).GetSquaredLength() < (triangle.B - this->Origin).GetSquaredLength() )
                    {
                        vIntersection1.x = triangle.A.x;
                        vIntersection1.y = triangle.A.y;
                        vIntersection1.z = triangle.A.z;
                        vIntersection2.x = triangle.B.x;
                        vIntersection2.y = triangle.B.y;
                        vIntersection2.z = triangle.B.z;
                    }
                    else
                    {
                        vIntersection1.x = triangle.B.x;
                        vIntersection1.y = triangle.B.y;
                        vIntersection1.z = triangle.B.z;
                        vIntersection2.x = triangle.A.x;
                        vIntersection2.y = triangle.A.y;
                        vIntersection2.z = triangle.A.z;
                    }
                    return EQIntersections::E_Two;
                }

                VectorType vAuxBC;
                EQIntersections numIntersectBC = this->IntersectionPoint(triangle.B, triangle.C, vAuxBC); // Checks intersection with BC edge
                if (numIntersectBC == EQIntersections::E_Infinite) // Ray contains BC edge
                {
                    // Looks for closest point to ray origin
                    if  ( (triangle.B - this->Origin).GetSquaredLength() < (triangle.C - this->Origin).GetSquaredLength() )
                    {
                        vIntersection1.x = triangle.B.x;
                        vIntersection1.y = triangle.B.y;
                        vIntersection1.z = triangle.B.z;
                        vIntersection2.x = triangle.C.x;
                        vIntersection2.y = triangle.C.y;
                        vIntersection2.z = triangle.C.z;
                    }
                    else
                    {
                        vIntersection1.x = triangle.C.x;
                        vIntersection1.y = triangle.C.y;
                        vIntersection1.z = triangle.C.z;
                        vIntersection2.x = triangle.B.x;
                        vIntersection2.y = triangle.B.y;
                        vIntersection2.z = triangle.B.z;
                    }
                    return EQIntersections::E_Two;
                }

                VectorType vAuxCA;
                EQIntersections numIntersectCA = this->IntersectionPoint(triangle.C, triangle.A, vAuxCA); // Checks intersection with BC edge
                if (numIntersectCA == EQIntersections::E_Infinite) // Ray contains CA edge
                {
                    // Looks for closest point to ray origin
                    if  ( (triangle.C - this->Origin).GetSquaredLength() < (triangle.A - this->Origin).GetSquaredLength() )
                    {
                        vIntersection1.x = triangle.C.x;
                        vIntersection1.y = triangle.C.y;
                        vIntersection1.z = triangle.C.z;
                        vIntersection2.x = triangle.A.x;
                        vIntersection2.y = triangle.A.y;
                        vIntersection2.z = triangle.A.z;
                    }
                    else
                    {
                        vIntersection1.x = triangle.A.x;
                        vIntersection1.y = triangle.A.y;
                        vIntersection1.z = triangle.A.z;
                        vIntersection2.x = triangle.C.x;
                        vIntersection2.y = triangle.C.y;
                        vIntersection2.z = triangle.C.z;
                    }
                    return EQIntersections::E_Two;
                }

                if (numIntersectAB == EQIntersections::E_One) // Ray has ONE intersection with AB edge
                {
                    bPrevInt = true;
                    vPrevInt.x = vAuxAB.x;
                    vPrevInt.y = vAuxAB.y;
                    vPrevInt.z = vAuxAB.z;
                }

                if (numIntersectBC == EQIntersections::E_One) // Ray has ONE intersection with BC edge
                {
                    if (bPrevInt) // There is a previous intersection with an edge
                    {
                        if (vAuxBC != vPrevInt)
                        {
                            // Looks for closest point to ray origin
                            if  ( (vAuxBC - this->Origin).GetSquaredLength() < (vPrevInt - this->Origin).GetSquaredLength() )
                            {
                                vIntersection1.x = vAuxBC.x;
                                vIntersection1.y = vAuxBC.y;
                                vIntersection1.z = vAuxBC.z;
                                vIntersection2.x = vPrevInt.x;
                                vIntersection2.y = vPrevInt.y;
                                vIntersection2.z = vPrevInt.z;
                            }
                            else
                            {
                                vIntersection1.x = vPrevInt.x;
                                vIntersection1.y = vPrevInt.y;
                                vIntersection1.z = vPrevInt.z;
                                vIntersection2.x = vAuxBC.x;
                                vIntersection2.y = vAuxBC.y;
                                vIntersection2.z = vAuxBC.z;
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

                if (numIntersectCA == EQIntersections::E_One)
                {
                    if (bPrevInt) // There is a previous intersection with an edge
                    {
                        if (vAuxCA != vPrevInt)
                        {
                            // Looks for closest point to ray origin
                            if  ( (vAuxCA - this->Origin).GetSquaredLength() < (vPrevInt - this->Origin).GetSquaredLength() )
                            {
                                vIntersection1.x = vAuxCA.x;
                                vIntersection1.y = vAuxCA.y;
                                vIntersection1.z = vAuxCA.z;
                                vIntersection2.x = vPrevInt.x;
                                vIntersection2.y = vPrevInt.y;
                                vIntersection2.z = vPrevInt.z;
                            }
                            else
                            {
                                vIntersection1.x = vPrevInt.x;
                                vIntersection1.y = vPrevInt.y;
                                vIntersection1.z = vPrevInt.z;
                                vIntersection2.x = vAuxCA.x;
                                vIntersection2.y = vAuxCA.y;
                                vIntersection2.z = vAuxCA.z;
                            }
                            return EQIntersections::E_Two;
                        }
                    }
                    else
                        QE_ASSERT(false)  // Something is wrong, there is ONE intersection and is not a vertex
                }

                if (bPrevInt)
                {
                    vIntersection1.x = vPrevInt.x;
                    vIntersection1.y = vPrevInt.y;
                    vIntersection1.z = vPrevInt.z;
                    return EQIntersections::E_One;
                }
                else
                    return EQIntersections::E_None;
            }
        }
        else if (NUM_INTERSECT == EQIntersections::E_One) // Ray and plane intersects in one point, are not coplanar
        {
            if (this->PointInsideTriangle(triangle, vAux) )
            {
                vIntersection1.x = vAux.x;
                vIntersection1.y = vAux.y;
                vIntersection1.z = vAux.z;
                return EQIntersections::E_One;
            }
            else
                return EQIntersections::E_None;
        }
        else
            return EQIntersections::E_None;;
    }

    /// <summary>
	/// This method receives a convex hexahedron, and computes the points where the resident ray intersects with it,
    /// if they exists.
	/// </summary>
    /// <remarks>
	/// - If there's no intersection point, the output parameter used for storing the intersection point won't be modified.
	/// - If there is only one intersection point, it's stored in the output parameter.
	/// - If there are two intersections, the output parameter stores the closest point to origin of ray.
	/// </remarks>
	/// <param name="hexahedron">[IN] The hexahedron whose intersections with resident ray are wanted.</param>
    /// <param name="vIntersection">[OUT] A vector where to store the intersection point closest to origin of ray.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the ray and the hexahedron,
    /// which can takes the following values: E_None, E_One, E_Two.
	/// </returns>
	EQIntersections IntersectionPoint(const QBaseHexahedron<VectorType> &hexahedron, VectorType &vIntersection) const
	{
	    VectorType vAux;
	    return this->IntersectionPoint(hexahedron, vIntersection, vAux);
	}

    /// <summary>
	/// This method receives a convex hexahedron, and computes the points where the resident ray intersects with it,
    /// if they exists.
	/// </summary>
    /// <remarks>
	/// - If there's no intersection point, the output parameters used for storing the intersection points won't be modified.
	/// - If there is only one intersection point, it's stored in the first output parameter, and the second one is not modified.
	/// - If there are two intersections, the first output parameter stores the closest point to origin of ray.
	/// </remarks>
	/// <param name="hexahedron">[IN] The hexahedron whose intersections with resident ray are wanted.</param>
    /// <param name="vIntersection1">[OUT] A vector where to store the intersection point closest to origin of ray.</param>
    /// <param name="vIntersection2">[OUT] A vector where to store the intersection point farthest to origin of ray.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the resident ray and the hexahedron,
    /// which can takes the following values: E_None, E_One, E_Two.
	/// </returns>
	EQIntersections IntersectionPoint(const QBaseHexahedron<VectorType> &hexahedron, VectorType &vIntersection1, VectorType &vIntersection2) const
	{
        VectorType vAuxPoint, vAux1, vAux2;
        bool bPreviousInt = false;

        // Check if resident ray intersects ABCD face
        EQIntersections value1 = this->IntersectionPoint(hexahedron.A, hexahedron.B, hexahedron.C, hexahedron.D, vAux1, vAux2);

        if ( value1 == EQIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection1.x = vAux1.x;
            vIntersection1.y = vAux1.y;
            vIntersection1.z = vAux1.z;
            vIntersection2.x = vAux2.x;
            vIntersection2.y = vAux2.y;
            vIntersection2.z = vAux2.z;
            return EQIntersections::E_Two;
        }
        else if (value1 == EQIntersections::E_One) // There is only one intersection
        {
            vAuxPoint = vAux1;
            bPreviousInt = true;
        }

        // Check if resident ray intersects EFGH face
        EQIntersections value2 = this->IntersectionPoint(hexahedron.E, hexahedron.F, hexahedron.G, hexahedron.H, vAux1, vAux2);

        if ( value2 == EQIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection1.x = vAux1.x;
            vIntersection1.y = vAux1.y;
            vIntersection1.z = vAux1.z;
            vIntersection2.x = vAux2.x;
            vIntersection2.y = vAux2.y;
            vIntersection2.z = vAux2.z;
            return EQIntersections::E_Two;
        }
        else if (value2 == EQIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux1)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->Origin).GetSquaredLength() < (vAux1 - this->Origin).GetSquaredLength() ) // Computes the closest intersection to ray origin
                {
                    vIntersection1.x = vAuxPoint.x;
                    vIntersection1.y = vAuxPoint.y;
                    vIntersection1.z = vAuxPoint.z;
                    vIntersection2.x = vAux1.x;
                    vIntersection2.y = vAux1.y;
                    vIntersection2.z = vAux1.z;
                }
                else
                {
                    vIntersection1.x = vAux1.x;
                    vIntersection1.y = vAux1.y;
                    vIntersection1.z = vAux1.z;
                    vIntersection2.x = vAuxPoint.x;
                    vIntersection2.y = vAuxPoint.y;
                    vIntersection2.z = vAuxPoint.z;
                }
                return EQIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux1;
                bPreviousInt = true;
            }
        }

        // Check if resident ray intersects ABHE face
        EQIntersections value3 = this->IntersectionPoint(hexahedron.A, hexahedron.B, hexahedron.H, hexahedron.E, vAux1, vAux2);

        if ( value3 == EQIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection1.x = vAux1.x;
            vIntersection1.y = vAux1.y;
            vIntersection1.z = vAux1.z;
            vIntersection2.x = vAux2.x;
            vIntersection2.y = vAux2.y;
            vIntersection2.z = vAux2.z;
            return EQIntersections::E_Two;
        }
        else if (value3 == EQIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux1)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->Origin).GetSquaredLength() < (vAux1 - this->Origin).GetSquaredLength() ) // Computes the closest intersection to ray origin
                {
                    vIntersection1.x = vAuxPoint.x;
                    vIntersection1.y = vAuxPoint.y;
                    vIntersection1.z = vAuxPoint.z;
                    vIntersection2.x = vAux1.x;
                    vIntersection2.y = vAux1.y;
                    vIntersection2.z = vAux1.z;
                }
                else
                {
                    vIntersection1.x = vAux1.x;
                    vIntersection1.y = vAux1.y;
                    vIntersection1.z = vAux1.z;
                    vIntersection2.x = vAuxPoint.x;
                    vIntersection2.y = vAuxPoint.y;
                    vIntersection2.z = vAuxPoint.z;
                }
                return EQIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux1;
                bPreviousInt = true;
            }
        }

        // Check if resident ray intersects BCGH face
        EQIntersections value4 = this->IntersectionPoint(hexahedron.B, hexahedron.C, hexahedron.G, hexahedron.H, vAux1,vAux2);

        if ( value4 == EQIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection1.x = vAux1.x;
            vIntersection1.y = vAux1.y;
            vIntersection1.z = vAux1.z;
            vIntersection2.x = vAux2.x;
            vIntersection2.y = vAux2.y;
            vIntersection2.z = vAux2.z;
            return EQIntersections::E_Two;
        }
        else if (value4 == EQIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux1)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->Origin).GetSquaredLength() < (vAux1 - this->Origin).GetSquaredLength() ) // Computes the closest intersection to ray origin
                {
                    vIntersection1.x = vAuxPoint.x;
                    vIntersection1.y = vAuxPoint.y;
                    vIntersection1.z = vAuxPoint.z;
                    vIntersection2.x = vAux1.x;
                    vIntersection2.y = vAux1.y;
                    vIntersection2.z = vAux1.z;
                }
                else
                {
                    vIntersection1.x = vAux1.x;
                    vIntersection1.y = vAux1.y;
                    vIntersection1.z = vAux1.z;
                    vIntersection2.x = vAuxPoint.x;
                    vIntersection2.y = vAuxPoint.y;
                    vIntersection2.z = vAuxPoint.z;
                }
                return EQIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux1;
                bPreviousInt = true;
            }
        }

        // Check if resident ray intersects ADFE face
        EQIntersections value5 = this->IntersectionPoint(hexahedron.A, hexahedron.D, hexahedron.F, hexahedron.E, vAux1, vAux2);

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
                if  ( (vAuxPoint - this->Origin).GetSquaredLength() < (vAux1 - this->Origin).GetSquaredLength() ) // Computes the closest intersection ray origin
                {
                    vIntersection1.x = vAuxPoint.x;
                    vIntersection1.y = vAuxPoint.y;
                    vIntersection1.z = vAuxPoint.z;
                    vIntersection2.x = vAux1.x;
                    vIntersection2.y = vAux1.y;
                    vIntersection2.z = vAux1.z;
                }
                else
                {
                    vIntersection1.x = vAux1.x;
                    vIntersection1.y = vAux1.y;
                    vIntersection1.z = vAux1.z;
                    vIntersection2.x = vAuxPoint.x;
                    vIntersection2.y = vAuxPoint.y;
                    vIntersection2.z = vAuxPoint.z;
                }
                return EQIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux1;
                bPreviousInt = true;
            }
        }

        // Check if resident ray intersects CDFG face
        EQIntersections value6 = this->IntersectionPoint(hexahedron.C, hexahedron.D, hexahedron.F, hexahedron.G, vAux1, vAux2);

        if ( value6 == EQIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection1.x = vAux1.x;
            vIntersection1.y = vAux1.y;
            vIntersection1.z = vAux1.z;
            vIntersection2.x = vAux2.x;
            vIntersection2.y = vAux2.y;
            vIntersection2.z = vAux2.z;
            return EQIntersections::E_Two;
        }
        else if (value6 == EQIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux1)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->Origin).GetSquaredLength() < (vAux1 - this->Origin).GetSquaredLength() ) // Computes the closest intersection to ray origin
                {
                    vIntersection1.x = vAuxPoint.x;
                    vIntersection1.y = vAuxPoint.y;
                    vIntersection1.z = vAuxPoint.z;
                    vIntersection2.x = vAux1.x;
                    vIntersection2.y = vAux1.y;
                    vIntersection2.z = vAux1.z;
                }
                else
                {
                    vIntersection1.x = vAux1.x;
                    vIntersection1.y = vAux1.y;
                    vIntersection1.z = vAux1.z;
                    vIntersection2.x = vAuxPoint.x;
                    vIntersection2.y = vAuxPoint.y;
                    vIntersection2.z = vAuxPoint.z;
                }
                return EQIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux1;
                bPreviousInt = true;
            }
        }

        if (bPreviousInt) // There is only one intersection with hexahedron
        {
            vIntersection1.x = vAuxPoint.x;
            vIntersection1.y = vAuxPoint.y;
            vIntersection1.z = vAuxPoint.z;
            return EQIntersections::E_One;
        }
        else // There are no intersections with hexahedron
            return EQIntersections::E_None;
    }

    /// <summary>
    /// Checks the relation between resident ray and the provided plane.
    /// </summary>
    /// <remarks>
    /// Note that if the origin of resident ray lies on the plane, we don't consider that the ray is crossing the plane.
    /// </remarks>
    /// <param name="plane">[IN] The plane we want check the relation with resident ray.</param>
    /// <returns>
    /// An enumerated value like follows:<br>
    /// - 0 (E_Contained): The ray lies on plane.
    /// - 1 (E_PositiveSide): The ray is fully contained in the positive side of the space defined by the plane.
    /// - 2 (E_NegativeSide): The ray is fully contained in the negative side of the space defined by the plane.
    /// - 3 (E_BothSides): The ray cross the plane.
    /// We consider "positive part of the space" the locus of points which verifies \f$ Ax + By + Cz + D > 0 \f$.
    /// </returns>
    EQSpaceRelation SpaceRelation(const QBasePlane &plane) const
    {
        // The plane shouldn't be null
        QE_ASSERT( !(SQFloat::IsZero(plane.a) && SQFloat::IsZero(plane.b) && SQFloat::IsZero(plane.c)) );

        // The direction vector of the ray mustn't be null
        QE_ASSERT( !this->Direction.IsZero() );

        // We take as auxiliar point the head of the direction vector, as if it was positioned in the origin point of the ray
        QVector3 vAux(QVector3(this->Origin) + this->Direction);

        // Distances to the plane from both auxiliar point and origin of ray
        // To compare the two distances is not necessary to divide by de normal length (it is invariant)
        const float_q& DIST_ORIGIN = plane.a * this->Origin.x + plane.b * this->Origin.y + plane.c * this->Origin.z + plane.d;
        const float_q& DIST_AUX = plane.a * vAux.x + plane.b * vAux.y + plane.c * vAux.z + plane.d;

        if ( SQFloat::IsZero(DIST_ORIGIN) ) // Origin point of ray lies on plane
        {
            if ( SQFloat::IsZero(DIST_AUX) ) // Ray lies on plane
                return EQSpaceRelation::E_Contained;
            else if ( SQFloat::IsNegative(DIST_AUX) ) // Direction vector goes to positive side
                return EQSpaceRelation::E_NegativeSide;
            else // Direction vector goes to negative side
                return EQSpaceRelation::E_PositiveSide;
        }
        else if ( SQFloat::IsNegative(DIST_ORIGIN) )// Origin point of ray is in negative side
        {
            if ( SQFloat::IsLessOrEquals(DIST_AUX, DIST_ORIGIN) ) // Direction vector moves away from plane or is parallel to it.
                return EQSpaceRelation::E_NegativeSide;
            else // Direction vector is approaching to plane
                return EQSpaceRelation::E_BothSides;
        }
        else // Origin point of ray is in positive side
        {
            if ( SQFloat::IsGreaterOrEquals(DIST_AUX, DIST_ORIGIN) ) // Direction vector moves away from plane or is parallel to it.
                return EQSpaceRelation::E_PositiveSide;
            else // Direction vector is approaching to plane
                return EQSpaceRelation::E_BothSides;
        }
    }

    /// <summary>
	/// This method rotates the resident ray applying the rotation contained in the provided quaternion
	/// around the coordinate axis centre.
	/// </summary>
	/// <param name="qRotation">[IN] Quaternion which contains the rotation to be applied.</param>
    /// <returns>
    /// The rotated ray.
    /// </returns>
	inline QRay3D<VectorType> Rotate(const QQuaternion &qRotation) const
	{
        QRay3D<VectorType> auxRay = *this;
        SQPoint::Rotate(qRotation, &auxRay.Origin, 1);
        SQPoint::Rotate(qRotation, &auxRay.Direction, 1);
        return auxRay;
	}

    /// <summary>
	/// This method rotates the resident ray applying the rotation contained in the provided quaternion
	/// around the point provided as pivot.
	/// </summary>
	/// <param name="qRotation">[IN] Quaternion which contains the rotation to be applied.</param>
	/// <param name="vPivot">[IN] Point which acts as pivot.</param>
    /// <returns>
    /// The rotated ray.
    /// </returns>
	inline QRay3D<VectorType> RotateWithPivot(const QQuaternion &qRotation, const VectorType &vPivot) const
	{
        QRay3D<VectorType> auxRay = *this;
        SQPoint::RotateWithPivot(qRotation, vPivot, &auxRay.Origin, 1);
        SQPoint::Rotate(qRotation, &auxRay.Direction, 1);
        return auxRay;
	}

    /// <summary>
	/// This method translates the resident ray by the translation contained in the provided vector.
	/// </summary>
	/// <param name="vTranslation">[IN] Vector which contains the translation to be applied.</param>
    /// <returns>
    /// The translated ray.
    /// </returns>
	inline QRay3D<VectorType> Translate(const QBaseVector3 &vTranslation) const
	{
        QRay3D<VectorType> auxRay = *this;
        SQPoint::Translate(vTranslation, &auxRay.Origin, 1);
        return auxRay;
	}

    /// <summary>
	/// This method translates the resident ray by the provided amounts for every axis.
	/// </summary>
	/// <param name="fTranslationX">[IN] Amount of translation in X direction.</param>
	/// <param name="fTranslationY">[IN] Amount of translation in Y direction.</param>
	/// <param name="fTranslationZ">[IN] Amount of translation in Z direction.</param>
    /// <returns>
    /// The translated ray.
    /// </returns>
	inline QRay3D<VectorType> Translate(const float_q &fTranslationX, const float_q &fTranslationY, const float_q &fTranslationZ) const
	{
        QRay3D<VectorType> auxRay = *this;
        SQPoint::Translate(fTranslationX, fTranslationY, fTranslationZ, &auxRay.Origin, 1);
        return auxRay;
	}

    /// <summary>
	/// This method scales the resident ray by the scale contained in the provided vector.
	/// </summary>
    /// <remarks>
	/// Resultant ray is normalized after this operation.
	/// </remarks>
	/// <param name="vScale">[IN] Vector which contains the scale to be applied in every axis.</param>
    /// <returns>
    /// The scaled ray.
    /// </returns>
	inline QRay3D<VectorType> Scale(const QBaseVector3 &vScale) const
	{
        QRay3D<VectorType> auxRay = *this;
        SQPoint::Scale(vScale, &auxRay.Origin, 1);
        SQPoint::Scale(vScale, &auxRay.Direction, 1);
        return QRay3D<VectorType>(auxRay.Origin, auxRay.Direction.Normalize());
	}

    /// <summary>
	/// This method scales the resident ray by the amounts provided for every axis.
	/// </summary>
    /// <remarks>
	/// Resultant ray is normalized after this operation.
	/// </remarks>
	/// <param name="vScaleX">[IN] Scale to be applied in X direction.</param>
	/// <param name="vScaleY">[IN] Scale to be applied in Y direction.</param>
	/// <param name="vScaleZ">[IN] Scale to be applied in Z direction.</param>
    /// <returns>
    /// The scaled ray.
    /// </returns>
	inline QRay3D<VectorType> Scale(const float_q &vScaleX, const float_q &vScaleY, const float_q &vScaleZ) const
	{
        QRay3D<VectorType> auxRay = *this;
        SQPoint::Scale(vScaleX, vScaleY, vScaleZ, &auxRay.Origin, 1);
        SQPoint::Scale(vScaleX, vScaleY, vScaleZ, &auxRay.Direction, 1);
        return QRay3D<VectorType>(auxRay.Origin, auxRay.Direction.Normalize());
	}

    /// <summary>
	/// This method scales the resident ray by the scale contained in the provided vector from
	/// the provided point that acts as pivot.
	/// </summary>
    /// <remarks>
	/// Resultant ray is normalized after this operation.
	/// </remarks>
	/// <param name="vScale">[IN] Vector which contains the scale to be applied in every axis.</param>
	/// <param name="vPivot">[IN] Point that acts as pivot of the scale.</param>
    /// <returns>
    /// The scaled ray.
    /// </returns>
	inline QRay3D<VectorType> ScaleWithPivot(const QBaseVector3 &vScale, const VectorType &vPivot) const
	{
        QRay3D<VectorType> auxRay = *this;
        SQPoint::ScaleWithPivot(vScale, vPivot, &auxRay.Origin, 1);
        SQPoint::Scale(vScale, &auxRay.Direction, 1);
        return QRay3D<VectorType>(auxRay.Origin, auxRay.Direction.Normalize());
	}

    /// <summary>
	/// This method scales the resident ray by the amounts provided for every axis from
	/// the provided point that acts as pivot.
	/// </summary>
    /// <remarks>
	/// Resultant ray is normalized after this operation.
	/// </remarks>
	/// <param name="vScaleX">[IN] Scale to be applied in X direction.</param>
	/// <param name="vScaleY">[IN] Scale to be applied in Y direction.</param>
	/// <param name="vScaleZ">[IN] Scale to be applied in Z direction.</param>
	/// <param name="vPivot">[IN] Point that acts as pivot of the scale.</param>
    /// <returns>
    /// The scaled ray.
    /// </returns>
	inline QRay3D<VectorType> ScaleWithPivot(const float_q &vScaleX, const float_q &vScaleY, const float_q &vScaleZ, const VectorType &vPivot) const
	{
        QRay3D<VectorType> auxRay = *this;
        SQPoint::ScaleWithPivot(vScaleX, vScaleY, vScaleZ, vPivot, &auxRay.Origin, 1);
        SQPoint::Scale(vScaleX, vScaleY, vScaleZ, &auxRay.Direction, 1);
        return QRay3D<VectorType>(auxRay.Origin, auxRay.Direction.Normalize());
	}

    /// <summary>
	/// This method rotates the resident ray applying the rotation contained in the provided matrix
	/// around the coordinate axis centre.
	/// </summary>
	/// <param name="rotation">[IN] Rotation matrix which contains the rotation to be applied.</param>
    /// <returns>
    /// The rotated ray.
    /// </returns>
	inline QRay3D<VectorType> Rotate(const QRotationMatrix3x3 &rotation) const
	{
        QRay3D<VectorType> auxRay = *this;
        SQPoint::Rotate(rotation, &auxRay.Origin, 1);
        SQPoint::Rotate(rotation, &auxRay.Direction, 1);
        return auxRay;
	}

    /// <summary>
	/// This method translates the resident ray by the translation contained in the provided matrix.
	/// </summary>
	/// <param name="translation">[IN] Matrix which contains the translation to be applied.</param>
    /// <returns>
    /// The translated ray.
    /// </returns>
	inline QRay3D<VectorType> Translate(const QTranslationMatrix<QMatrix4x3> &translation) const
	{
        QRay3D<VectorType> auxRay = *this;
        SQPoint::Translate(translation, &auxRay.Origin, 1);
        return auxRay;
	}

    /// <summary>
	/// This method translates the resident ray by the translation contained in the provided matrix.
	/// </summary>
	/// <param name="translation">[IN] Matrix which contains the translation to be applied.</param>
    /// <returns>
    /// The translated ray.
    /// </returns>
	inline QRay3D<VectorType> Translate(const QTranslationMatrix<QMatrix4x4> &translation) const
	{
        QRay3D<VectorType> auxRay = *this;
        SQPoint::Translate(translation, &auxRay.Origin, 1);
        return auxRay;
	}

    /// <summary>
	/// This method scales the resident ray by the scale contained in the provided matrix.
	/// </summary>
    /// <remarks>
	/// Resultant ray is normalized after this operation.
	/// </remarks>
	/// <param name="scale">[IN] Matrix which contains the scale to be applied in every axis.</param>
    /// <returns>
    /// The scaled ray.
    /// </returns>
	inline QRay3D<VectorType> Scale(const QScalingMatrix3x3 &scale) const
	{
        QRay3D<VectorType> auxRay = *this;
        SQPoint::Scale(scale, &auxRay.Origin, 1);
        SQPoint::Scale(scale, &auxRay.Direction, 1);
        return QRay3D<VectorType>(auxRay.Origin, auxRay.Direction.Normalize());
	}

    /// <summary>
	/// This method applies to the resident ray the transformation contained in the provided matrix.
	/// </summary>
    /// <remarks>
	/// Resultant ray is normalized after this operation.
	/// </remarks>
	/// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
    /// <returns>
    /// The transformed ray.
    /// </returns>
	inline QRay3D<VectorType> Transform(const QTransformationMatrix<QMatrix4x3> &transformation) const
    {
        return this->TransformImp(transformation);
	}

    /// <summary>
	/// This method applies to the resident ray the transformation contained in the provided matrix.
	/// </summary>
    /// <remarks>
	/// Resultant ray is normalized after this operation.
	/// </remarks>
	/// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
    /// <returns>
    /// The transformed ray.
    /// </returns>
	inline QRay3D<VectorType> Transform(const QTransformationMatrix<QMatrix4x4> &transformation) const
    {
        return this->TransformImp(transformation);
	}

	/// <summary>
	/// This method applies to the resident ray the transformation contained in the provided matrix.
	/// </summary>
    /// <remarks>
	/// Resultant ray is normalized after this operation.
	/// </remarks>
	/// <param name="spaceConversion">[IN] Matrix which contains the transformation to be applied.</param>
    /// <returns>
    /// The transformed ray.
    /// </returns>
	inline QRay3D<VectorType> Transform(const QSpaceConversionMatrix &spaceConversion) const
	{
        return QRay3D<VectorType>(this->Origin.Transform(spaceConversion), 
                                  this->Direction.Transform(spaceConversion));
	}

    /// <summary>
	/// This method rotates the resident ray applying the rotation contained in the provided matrix
	/// around a given point that acts as pivot of rotation.
	/// </summary>
	/// <param name="rotation">[IN] Rotation matrix which contains the rotation to be applied.</param>
	/// <param name="vPivot">[IN] Point which acts as pivot.</param>
    /// <returns>
    /// The rotated ray.
    /// </returns>
	inline QRay3D<VectorType> RotateWithPivot(const QRotationMatrix3x3 &rotation, const VectorType &vPivot) const
	{
        QRay3D<VectorType> auxRay = *this;
        SQPoint::RotateWithPivot(rotation, vPivot, &auxRay.Origin, 1);
        SQPoint::Rotate(rotation, &auxRay.Direction, 1);
        return auxRay;
	}

    /// <summary>
	/// This method scales the resident ray by the scale contained in the provided matrix from
	/// a given point that acts as pivot.
	/// </summary>
    /// <remarks>
	/// Resultant ray is normalized after this operation.
	/// </remarks>
	/// <param name="scale">[IN] Matrix which contains the scale to be applied.</param>
	/// <param name="vPivot">[IN] Point that acts as pivot of the scale.</param>
    /// <returns>
    /// The rotated ray.
    /// </returns>
	inline QRay3D<VectorType> ScaleWithPivot(const QScalingMatrix3x3 &scale, const VectorType &vPivot) const
	{
        QRay3D<VectorType> auxRay = *this;
        SQPoint::ScaleWithPivot(scale, vPivot, &auxRay.Origin, 1);
        SQPoint::Scale(scale, &auxRay.Direction, 1);
        return QRay3D<VectorType>(auxRay.Origin, auxRay.Direction.Normalize());
	}

    /// <summary>
	/// This method applies the transformation contained in the provided matrix using
	/// a given point as pivot of transformation.
	/// </summary>
    /// <remarks>
	/// Resultant ray is normalized after this operation.<br />
    /// When using 4D vectors, the W component of the pivot point doesn't affect the result.
	/// </remarks>
	/// <param name="transformation">[IN] Tranformation matrix to be applied.</param>
	/// <param name="vPivot">[IN] Point that acts as pivot of the transformation.</param>
    /// <returns>
    /// The transformed ray.
    /// </returns>
	inline QRay3D<VectorType> TransformWithPivot(const QTransformationMatrix<QMatrix4x3> &transformation, const VectorType &vPivot) const
    {
        return this->TransformWithPivotImp(transformation, vPivot);
	}

    /// <summary>
	/// This method applies the transformation contained in the provided matrix using
	/// a given point as pivot of transformation.
	/// </summary>
    /// <remarks>
	/// Resultant ray is normalized after this operation.<br />
    /// When using 4D vectors, the W component of the pivot point doesn't affect the result.
	/// </remarks>
	/// <param name="transformation">[IN] Tranformation matrix to be applied.</param>
	/// <param name="vPivot">[IN] Point that acts as pivot of the transformation.</param>
    /// <returns>
    /// The transformed ray.
    /// </returns>
	inline QRay3D<VectorType> TransformWithPivot(const QTransformationMatrix<QMatrix4x4> &transformation, const VectorType &vPivot) const
    {
        return this->TransformWithPivotImp(transformation, vPivot);
	}

protected:

    // Checks if resident ray contains a given point. Ray must be normalized to works fine.
    inline bool Contains(const VectorType &vPoint) const
    {
        if (vPoint == this->Origin) // The point is the ray position.
            return true;

        QVector3 vAux(vPoint - this->Origin); // Calculates a vector from ray origin to point.

        QVector3 vCross = vAux.CrossProduct(this->Direction); // Calculates cross product to check if both vectors are parallel

        if (vCross != QVector3::GetZeroVector()) // Vectors are not parallel
            return false;
        else // Vectors are parallel. It checks if they are opposite or not.
            return ( SQFloat::IsNegative(vAux.x) == SQFloat::IsNegative(this->Direction.x) ) &&
                   ( SQFloat::IsNegative(vAux.y) == SQFloat::IsNegative(this->Direction.y) ) &&
                   ( SQFloat::IsNegative(vAux.z) == SQFloat::IsNegative(this->Direction.z) );

    }

    // Calculates if a point is inside the triangle provided applying barycentric technique.
    template <class VectorTypeParam>
    inline bool PointInsideTriangle(const QBaseTriangle<VectorTypeParam> &triangle, const VectorTypeParam &vPoint) const
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
        return SQFloat::IsPositive(fU) && SQFloat::IsPositive(fV) && SQFloat::IsLessOrEquals(fU + fV, SQFloat::_1);
    }

    // Calculates if a point is inside the convex quadrilateral provided by the vertex A, B, C and D,
    // applying barycentric technique. Is supossed that quadrilateral vertex are consecutive.
    template <class VectorTypeParam>
    bool PointInsideQuadrilateral(const VectorTypeParam &vVertexA, const VectorTypeParam &vVertexB,
                                  const VectorTypeParam &vVertexC,const VectorTypeParam &vVertexD,
                                  const VectorTypeParam &vPoint) const
    {
        // Compute vectors
        const VectorTypeParam &V0(vVertexC - vVertexA);
        const VectorTypeParam &V1(vVertexB - vVertexA);
        const VectorTypeParam &V2(vPoint - vVertexA);

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
        if ( SQFloat::IsPositive(fU) && SQFloat::IsPositive(fV) && SQFloat::IsLessOrEquals(fU + fV, SQFloat::_1) )
            return true;

        // Compute new vector
        const VectorTypeParam &V3(vVertexD - vVertexA);

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
        return  SQFloat::IsPositive(fU2) && SQFloat::IsPositive(fV2) && SQFloat::IsLessOrEquals(fU2 + fV2, SQFloat::_1);;
    }

    // Checks if resident ray intersects the AB line segment and calculates the intersection point if it exists
    inline EQIntersections IntersectionPoint(const VectorType &vA, const VectorType &vB, VectorType &vIntersection) const
    {
        return this->IntersectionPoint(QBaseLineSegment<VectorType>(vA, vB), vIntersection);
    }

    // Checks if resident ray intersects the AB line segment
    inline bool Intersection(const VectorType &vA, const VectorType &vB) const
    {
        return this->Intersection(QBaseLineSegment<VectorType>(vA, vB));
    }

    // Checks if resident ray intersects with a quadrilateral given by its four vertices
    inline bool Intersection(const VectorType &vVertexA, const VectorType &vVertexB, const VectorType &vVertexC, const VectorType &vVertexD) const
    {
        // Plane that contains quadrilateral
        QPlane auxP(vVertexA, vVertexB, vVertexC);

        VectorType vAux;

        const EQIntersections &NUM_INTERSECT = this->IntersectionPoint(auxP, vAux);
        if (NUM_INTERSECT == EQIntersections::E_Infinite) // Ray and plane are coplanar.
            return ( this->Intersection(vVertexA, vVertexB) || this->Intersection(vVertexB, vVertexC) ||
                     this->Intersection(vVertexC, vVertexD) || this->Intersection(vVertexD, vVertexA) );
        else if (NUM_INTERSECT == EQIntersections::E_One) // Ray and plane intersects in one point
            return this->PointInsideQuadrilateral(vVertexA, vVertexB, vVertexC, vVertexD, vAux);
        else
            return false;
    }

    // Calculates the intersection point between a quadrilateral given by its four vertices and resident ray, if it exists.
    EQIntersections IntersectionPoint (const VectorType &vVertexA, const VectorType &vVertexB, const VectorType &vVertexC, const VectorType &vVertexD,
                                       VectorType &vIntersection1, VectorType &vIntersection2) const
    {
        // Plane that contains quadrilateral
        QPlane auxP(vVertexA, vVertexB, vVertexC);

        VectorType vAux;

        const EQIntersections &NUM_INTERSECT = this->IntersectionPoint(auxP, vAux);
        if (NUM_INTERSECT == EQIntersections::E_Infinite) // Ray and quadrilateral are coplanar.
        {
            if ( PointInsideQuadrilateral(vVertexA, vVertexB, vVertexC, vVertexD, this->Origin) ) // Ray origin is inside quadrilateral
            {
                if (this->Origin == vVertexA) // Ray origin is A quadrilateral vertex
                {
                    vIntersection1 = this->Origin;

                    // Checks intersection with opposite edges
                    if (this->IntersectionPoint(vVertexB, vVertexC, vAux) == EQIntersections::E_One) // Intersection found
                    {
                        vIntersection2 = vAux;
                        return EQIntersections::E_Two;
                    }
                    else if (this->IntersectionPoint(vVertexC, vVertexD, vAux) == EQIntersections::E_One) // Intersection found
                    {
                        vIntersection2 = vAux;
                        return EQIntersections::E_Two;
                    }
                    else // No intersection found
                        return EQIntersections::E_One;
                }
                else if (this->Origin == vVertexB) // Ray origin is B quadrilateral vertex
                {
                    vIntersection1 = this->Origin;

                   // Checks intersection with opposite edges
                    if (this->IntersectionPoint(vVertexC, vVertexD, vAux) == EQIntersections::E_One) // Intersection found
                    {
                        vIntersection2 = vAux;
                        return EQIntersections::E_Two;
                    }
                    else if (this->IntersectionPoint(vVertexD, vVertexA, vAux) == EQIntersections::E_One) // Intersection found
                    {
                        vIntersection2 = vAux;
                        return EQIntersections::E_Two;
                    }
                    else // No intersection found
                        return EQIntersections::E_One;
                }
                else if (this->Origin == vVertexC) // Ray origin is C quadrilateral vertex
                {
                    vIntersection1 = this->Origin;

                    // Checks intersection with opposite edges
                    if (this->IntersectionPoint(vVertexD, vVertexA, vAux) == EQIntersections::E_One) // Intersection found
                    {
                        vIntersection2 = vAux;
                        return EQIntersections::E_Two;
                    }
                    else if (this->IntersectionPoint(vVertexA, vVertexB, vAux) == EQIntersections::E_One) // Intersection found
                    {
                        vIntersection2 = vAux;
                        return EQIntersections::E_Two;
                    }
                    else // No intersection found
                        return EQIntersections::E_One;
                }
                else if (this->Origin == vVertexD) // Ray origin is D quadrilateral vertex
                {
                    vIntersection1 = this->Origin;

                    // Checks intersection with opposite edges
                    if (this->IntersectionPoint(vVertexA, vVertexB, vAux) == EQIntersections::E_One) // Intersection found
                    {
                        vIntersection2 = vAux;
                        return EQIntersections::E_Two;
                    }
                    else if (this->IntersectionPoint(vVertexB, vVertexC, vAux) == EQIntersections::E_One) // Intersection found
                    {
                        vIntersection2 = vAux;
                        return EQIntersections::E_Two;
                    }
                    else // No intersection found
                        return EQIntersections::E_One;
                }
                else if (SQFloat::IsZero(QLineSegment<VectorType>(vVertexA, vVertexB).MinDistance(this->Origin))) // Ray origin is in AB quadrilateral edge
                {
                    if (this->IntersectionPoint(vVertexB, vVertexC, vAux) == EQIntersections::E_One) // Ray intersects other edge
                    {
                        if (vAux == vVertexB) // Intersection is in common vertex
                        {
                            vIntersection1 = vVertexB;
                            return EQIntersections::E_One;
                        }
                        else // Intersection is in edge
                        {
                            vIntersection1 = this->Origin;
                            vIntersection2 = vAux;
                            return EQIntersections::E_Two;
                        }
                    }
                    else if (this->IntersectionPoint(vVertexC, vVertexD, vAux) == EQIntersections::E_One) // Ray intersects other edge
                    {
                        vIntersection1 = this->Origin;
                        vIntersection2 = vAux;
                        return EQIntersections::E_Two;
                    }
                    else if (this->IntersectionPoint(vVertexD, vVertexA, vAux) == EQIntersections::E_One) // Ray intersects other edge
                    {
                        if (vAux == vVertexA) // Intersection is in common vertex
                        {
                            vIntersection1 = vVertexA;
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
                else if (SQFloat::IsZero(QLineSegment<VectorType>(vVertexB, vVertexC).MinDistance(this->Origin))) // Ray origin is in BC quadrilateral edge
                {
                    if (this->IntersectionPoint(vVertexC, vVertexD, vAux) == EQIntersections::E_One) // Ray intersects other edge
                    {
                        if (vAux == vVertexC) // Intersection is in common vertex
                        {
                            vIntersection1 = vVertexC;
                            return EQIntersections::E_One;
                        }
                        else // Intersection is in edge
                        {
                            vIntersection1 = this->Origin;
                            vIntersection2 = vAux;
                            return EQIntersections::E_Two;
                        }
                    }
                    else if (this->IntersectionPoint(vVertexD, vVertexA, vAux) == EQIntersections::E_One) // Ray intersects other edge
                    {
                        vIntersection1 = this->Origin;
                        vIntersection2 = vAux;
                        return EQIntersections::E_Two;
                    }
                    if (this->IntersectionPoint(vVertexA, vVertexB, vAux) == EQIntersections::E_One) // Ray intersects other edge
                    {
                        if (vAux == vVertexB) // Intersection is in common vertex
                        {
                            vIntersection1 = vVertexB;
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
                else if (SQFloat::IsZero(QLineSegment<VectorType>(vVertexC, vVertexD).MinDistance(this->Origin))) // Ray origin is in CD quadrilateral edge
                {
                    if (this->IntersectionPoint(vVertexD, vVertexA, vAux) == EQIntersections::E_One) // Ray intersects other edge
                    {
                        if (vAux == vVertexD) // Intersection is in common vertex
                        {
                            vIntersection1 = vVertexD;
                            return EQIntersections::E_One;
                        }
                        else // Intersection is in edge
                        {
                            vIntersection1 = this->Origin;
                            vIntersection2 = vAux;
                            return EQIntersections::E_Two;
                        }
                    }
                    else if (this->IntersectionPoint(vVertexA, vVertexB, vAux) == EQIntersections::E_One) // Ray intersects other edge
                    {
                        vIntersection1 = this->Origin;
                        vIntersection2 = vAux;
                        return EQIntersections::E_Two;
                    }
                    if (this->IntersectionPoint(vVertexB, vVertexC, vAux) == EQIntersections::E_One) // Ray intersects other edge
                    {
                        if (vAux == vVertexC) // Intersection is in common vertex
                        {
                            vIntersection1 = vVertexC;
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
                else if (SQFloat::IsZero(QLineSegment<VectorType>(vVertexD, vVertexA).MinDistance(this->Origin))) // Ray origin is in DA quadrilateral edge
                {
                    if (this->IntersectionPoint(vVertexA, vVertexB, vAux) == EQIntersections::E_One) // Ray intersects other edge
                    {
                        if (vAux == vVertexA) // Intersection is in common vertex
                        {
                            vIntersection1 = vVertexA;
                            return EQIntersections::E_One;
                        }
                        else // Intersection is in edge
                        {
                            vIntersection1 = this->Origin;
                            vIntersection2 = vAux;
                            return EQIntersections::E_Two;
                        }
                    }
                    else if (this->IntersectionPoint(vVertexB, vVertexC, vAux) == EQIntersections::E_One) // Ray intersects other edge
                    {
                        vIntersection1 = this->Origin;
                        vIntersection2 = vAux;
                        return EQIntersections::E_Two;
                    }
                    if (this->IntersectionPoint(vVertexC, vVertexD, vAux) == EQIntersections::E_One) // Ray intersects other edge
                    {
                        if (vAux == vVertexD) // Intersection is in common vertex
                        {
                            vIntersection1 = vVertexD;
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
                else // Ray origin is strictly inside quadrilateral (is not in a vertex or an edge)
                {
                    if (this->IntersectionPoint(vVertexA, vVertexB, vAux) == EQIntersections::E_One)
                        vIntersection1 = vAux;
                    else if (this->IntersectionPoint(vVertexB, vVertexC, vAux) == EQIntersections::E_One)
                        vIntersection1 = vAux;
                    else if (this->IntersectionPoint(vVertexC, vVertexD, vAux) == EQIntersections::E_One)
                        vIntersection1 = vAux;
                    else if (this->IntersectionPoint(vVertexD, vVertexA, vAux) == EQIntersections::E_One)
                        vIntersection1 = vAux;
                    else
                        QE_ASSERT(false)  // Something is wrong, if ray point is interior, it must be ONE intersection with a edge.

                    return EQIntersections::E_One;
                }
            }
            else // Ray origin is outside quadrilateral
            {
                VectorType vPrevInt;
                bool bPrevInt = false;

                VectorType vAuxAB;
                EQIntersections numIntersectAB = this->IntersectionPoint(vVertexA, vVertexB, vAuxAB); // Checks intersection with AB edge
                if (numIntersectAB == EQIntersections::E_Infinite) // Ray contains AB edge
                {
                    // Looks for closest point to ray origin
                    if  ( (vVertexA - this->Origin).GetSquaredLength() < (vVertexB - this->Origin).GetSquaredLength() )
                    {
                        vIntersection1 = vVertexA;
                        vIntersection2 = vVertexB;
                    }
                    else
                    {
                        vIntersection1 = vVertexB;
                        vIntersection2 = vVertexA;
                    }
                    return EQIntersections::E_Two;
                }

                VectorType vAuxBC;
                EQIntersections numIntersectBC = this->IntersectionPoint(vVertexB, vVertexC, vAuxBC); // Checks intersection with BC edge
                if (numIntersectBC == EQIntersections::E_Infinite) // Ray contains BC edge
                {
                    // Looks for closest point to ray origin
                    if  ( (vVertexB - this->Origin).GetSquaredLength() < (vVertexC - this->Origin).GetSquaredLength() )
                    {
                        vIntersection1 = vVertexB;
                        vIntersection2 = vVertexC;
                    }
                    else
                    {
                        vIntersection1 = vVertexC;
                        vIntersection2 = vVertexB;
                    }
                    return EQIntersections::E_Two;
                }

                VectorType vAuxCD;
                EQIntersections numIntersectCD = this->IntersectionPoint(vVertexC, vVertexD, vAuxCD); // Checks intersection with CD edge
                if (numIntersectCD == EQIntersections::E_Infinite) // Ray contains CD edge
                {
                    // Looks for closest point to ray origin
                    if  ( (vVertexC - this->Origin).GetSquaredLength() < (vVertexD - this->Origin).GetSquaredLength() )
                    {
                        vIntersection1 = vVertexC;
                        vIntersection2 = vVertexD;
                    }
                    else
                    {
                        vIntersection1 = vVertexD;
                        vIntersection2 = vVertexC;
                    }
                    return EQIntersections::E_Two;
                }

                VectorType vAuxDA;
                EQIntersections numIntersectDA = this->IntersectionPoint(vVertexD, vVertexA, vAuxDA); // Checks intersection with DA edge
                if (numIntersectDA == EQIntersections::E_Infinite) // Ray contains DA edge
                {
                    // Looks for closest point to ray origin
                    if  ( (vVertexD - this->Origin).GetSquaredLength() < (vVertexA - this->Origin).GetSquaredLength() )
                    {
                        vIntersection1 = vVertexD;
                        vIntersection2 = vVertexA;
                    }
                    else
                    {
                        vIntersection1 = vVertexA;
                        vIntersection2 = vVertexD;
                    }
                    return EQIntersections::E_Two;
                }

                if (numIntersectAB == EQIntersections::E_One) // Ray has ONE intersection with AB edge
                {
                    bPrevInt = true;
                    vPrevInt = vAuxAB;
                }

                if (numIntersectBC == EQIntersections::E_One) // Ray has ONE intersection with BC edge
                {
                    if (bPrevInt) // There is a previous intersection with an edge
                    {
                        if (vPrevInt != vAuxBC) // There are not the same point (a common vertex)
                        {
                            // Looks for closest point to ray origin
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

                if (numIntersectCD == EQIntersections::E_One)
                {
                    if (bPrevInt) // There is a previous intersection with an edge
                    {
                        if (vPrevInt != vAuxCD) // There are not the same point (a common vertex)
                        {
                            // Looks for closest point to ray origin
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

                if (numIntersectDA == EQIntersections::E_One)
                {
                    if (bPrevInt) // There is a previous intersection with an edge
                    {
                        if (vPrevInt != vAuxDA) // There are not the same point (a common vertex)
                        {
                            // Looks for closest point to ray origin
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
        else if (NUM_INTERSECT == EQIntersections::E_One) // Ray and plane intersects only in one point
        {
            if ( this->PointInsideQuadrilateral(vVertexA, vVertexB, vVertexC, vVertexD, vAux) )
            {
                vIntersection1 = vAux;
                return EQIntersections::E_One;
            }
            else
                return EQIntersections::E_None;
        }
        else
            return EQIntersections::E_None;
    }

    // <summary>
	// This method applies to the resident ray the transformation contained in the provided matrix.
	// </summary>
	// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
	// <remarks>
	// Resultant ray is normalized after this operation.
	// </remarks>
    // <returns>
    // The transformed ray.
    // </returns>
	template <class MatrixType>
	inline QRay3D<VectorType> TransformImp(const MatrixType &transformation) const
	{
        QRay3D<VectorType> auxRay = *this;
        SQPoint::Transform(transformation, &auxRay.Origin, 1);

        // Only rotation and scale part of the matrix is applyed to direction vector
        // These operations must be the same those used in QVector3::Transform, except for the translation operations.
        auxRay.Direction = QVector3(this->Direction.x * transformation.ij[0][0] + this->Direction.y * transformation.ij[1][0] + this->Direction.z * transformation.ij[2][0],
                                    this->Direction.x * transformation.ij[0][1] + this->Direction.y * transformation.ij[1][1] + this->Direction.z * transformation.ij[2][1],
                                    this->Direction.x * transformation.ij[0][2] + this->Direction.y * transformation.ij[1][2] + this->Direction.z * transformation.ij[2][2])
                                    .Normalize();
        return auxRay;
	}

    // <summary>
	// This method applies to the resident ray the transformation contained in the provided matrix using
	// a given point as pivot of transformation.
	// </summary>
	// <param name="transformation">[IN] Tranformation matrix to be applied.</param>
	// <param name="vPivot">[IN] Point that acts as pivot of the transformation.</param>
	// <remarks>
	// Resultant ray is normalized after this operation.
	// </remarks>
    // <returns>
    // The transformed ray.
    // </returns>
	template <class MatrixType>
	inline QRay3D<VectorType> TransformWithPivotImp(const MatrixType &transformation, const VectorType &vPivot) const
	{
        QRay3D<VectorType> auxRay = *this;
        SQPoint::TransformWithPivot(transformation, vPivot, &auxRay.Origin, 1);

        // Only rotation and scale part of the matrix is applyed to direction vector
        // These operations must be the same those used in QVector3::Transform, except for the translation operations.
        auxRay.Direction = QVector3(this->Direction.x * transformation.ij[0][0] + this->Direction.y * transformation.ij[1][0] + this->Direction.z * transformation.ij[2][0],
                                    this->Direction.x * transformation.ij[0][1] + this->Direction.y * transformation.ij[1][1] + this->Direction.z * transformation.ij[2][1],
                                    this->Direction.x * transformation.ij[0][2] + this->Direction.y * transformation.ij[1][2] + this->Direction.z * transformation.ij[2][2])
                                    .Normalize();
        return auxRay;
	}
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QRAY3D__
