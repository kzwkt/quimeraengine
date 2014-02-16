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

#ifndef __QRAY__
#define __QRAY__

#include "MathDefinitions.h"
#include "QBaseRay.h"
#include "QBaseOrb.h"
#include "EQIntersections.h"

using Kinesis::QuimeraEngine::Common::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Common::DataTypes::float_q;
using Kinesis::QuimeraEngine::Common::DataTypes::string_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

/// <summary>
/// Represents a ray in the space, which consists of a origin point, or position, and a direction.
/// </summary>
/// <remarks>
/// The direction symbolizes a line with only one end (which coincides with the origin) and that extends to the infinite.
/// </remarks>
/// <typeparam name="VectorTypeOrigin">Allowed types: QVector2, QVector3, QVector4.</typeparam>
/// <typeparam name="VectorTypeDirection">Allowed types: QVector2 (when VectorTypeOrigin is QVector2), QVector3 (when VectorTypeOrigin is QVector3 or QVector4).</typeparam>
template<class VectorTypeOrigin, class VectorTypeDirection>
class QRay : public QBaseRay<VectorTypeOrigin, VectorTypeDirection>
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	QRay()
    {
    }

    /// <summary>
	/// Copy constructor.
	/// </summary>
	/// <param name="ray">[IN] The ray from which we want to create a copy in the resident ray.</param>
	QRay(const QRay<VectorTypeOrigin, VectorTypeDirection> &ray) : QBaseRay<VectorTypeOrigin, VectorTypeDirection>(ray)
	{
	}

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <param name="ray">[IN] The ray in which we want resident ray to be based.</param>
    QRay(const QBaseRay<VectorTypeOrigin, VectorTypeDirection> &ray) : QBaseRay<VectorTypeOrigin, VectorTypeDirection>(ray)
    {
    }

    /// <summary>
    /// Constructor that receives the ray's position and direction.
    /// </summary>
    /// <remarks>
    /// The direction vector must be normalized to construct the ray properly.
    /// </remarks>
    /// <param name="vOrigin">[IN] Ray's position.</param>
    /// <param name="vDirection">[IN] Ray's direction.</param>
    QRay(const VectorTypeOrigin &vOrigin, const VectorTypeDirection &vDirection) : QBaseRay<VectorTypeOrigin, VectorTypeDirection>(vOrigin, vDirection)
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
    static const QRay<VectorTypeOrigin, VectorTypeDirection>& GetNullRay()
    {
        static const QRay<VectorTypeOrigin, VectorTypeDirection> NULLRAY(VectorTypeOrigin::GetNullVector(), VectorTypeDirection::GetNullVector());
        return NULLRAY;
    }


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Assignation operator that receives another ray.
    /// </summary>
    /// <param name="ray">[IN] An existing ray.</param>
    /// <returns>
    /// A reference to this ray, after assignation.
    /// </returns>
    QRay<VectorTypeOrigin, VectorTypeDirection>& operator=(const QBaseRay<VectorTypeOrigin, VectorTypeDirection> &ray)
    {
        QBaseRay<VectorTypeOrigin, VectorTypeDirection>::operator=(ray);
        return *this;
    }

    /// <summary>
    /// Converts the ray's direction in its opposite.
    /// </summary>
    /// <returns>
    /// The inverse of the ray.
    /// </returns>
    QRay<VectorTypeOrigin, VectorTypeDirection> Invert() const
    {
        return QRay<VectorTypeOrigin, VectorTypeDirection>(this->Origin, -this->Direction);
    }

    /// <summary>
    /// Normalizes the ray, converting its direction in a unit vector.
    /// </summary>
    /// <returns>
    /// The normalized ray.
    /// </returns>
    QRay<VectorTypeOrigin, VectorTypeDirection> Normalize() const
    {
        return QRay<VectorTypeOrigin, VectorTypeDirection>(this->Origin, this->Direction.Normalize());
    }

    /// <summary>
    /// Calculates any point that belongs to the ray, based on the distance to the ray's position.
    /// </summary>
    /// <remarks>
    /// The ray must be normalized to obtain a correct result.
    /// </remarks>
    /// <param name="fDistance">[IN] Distance from the point which is to be found to the ray's position.</param>
    /// <returns>
    /// A point of the ray.
    /// </returns>
    VectorTypeOrigin GetPoint(const float_q &fDistance) const
    {
        // The direction vector must be normalized
        QE_ASSERT( SQFloat::AreEqual(this->Direction.GetLength(), SQFloat::_1), "The direction vector must be normalized" );

        // It's assumed that the ray's direction vector is normalized
        return this->Origin + this->Direction * fDistance;
    }

    /// <summary>
    /// Checks if resident ray intersects with the provided orb.
    /// </summary>
    /// <remarks>
    /// If the direction of the ray is null, the result is undefined.
    /// </remarks>
    /// <param name="orb">[IN] The orb whose intersection with the ray will be checked.</param>
    /// <returns>
	/// A boolean value that indicates whether the ray and the orb intersect or not.<br/>
    /// <br/>
    /// <b>True</b><br/>
    /// The ray and the orb intersect, including the following cases:
    /// - The ray intersects the orb in two points.
    /// - The origin of the ray lays on the surface / perimeter of the orb (and the ray does not point to the orb).
    /// - The origin of the ray is contained in the orb.
    /// - The ray is tangent to the orb.
    ///
    /// <b>False</b><br/>
    /// The ray and the orb do not intersect.
	/// </returns>
    bool Intersection(const QBaseOrb<VectorTypeOrigin> &orb) const
    {
        // The direction vector shouldn't be null and the radius of the orb shouldn't equal zero
        QE_ASSERT( SQFloat::IsNotZero(this->Direction.GetLength()) && SQFloat::IsNotZero(orb.Radius), 
                   "The direction vector shouldn't be null and the radius of the orb shouldn't equal zero" );

        // The direction vector must be normalized
        QE_ASSERT( SQFloat::AreEqual(this->Direction.GetLength(), SQFloat::_1), "The direction vector must be normalized" );

        // Converts all vectors to VectorTypeDirection, that always will be QVector2 or QVector3
        VectorTypeDirection vNewRayOrigin(this->Origin - orb.Center);

        //  B/2 (instead of B) is calculed here to optimize comparison.
        const float_q &fB = vNewRayOrigin.DotProduct(this->Direction);

        // Since ray is normalized, A = 1.
        //const float_q &fA = this->Direction.DotProduct(this->Direction);

        const float_q &fC = vNewRayOrigin.DotProduct(vNewRayOrigin) - orb.Radius * orb.Radius;

        // Discriminant: B^2 - 4AC
        const float_q fD = fB*fB - fC;

        if (SQFloat::IsNegative(fD)) // D = B^2 - 4AC < 0 => 0 intersections
            return false;
        else if ( SQFloat::IsZero(fD) ) // D = B^2 - 4AC = 0 => 1 intersection
        {
            if ( SQFloat::IsGreaterOrEquals(-fB, SQFloat::_0) ) // T = -B/2A -> must be >= 0
                return true;
            else
                return false;
        }
        else
            return SQFloat::IsLessOrEquals(fB, sqrt_q(fD));

            // Explanation:

            // In this case, there are two posible intersections:
            //    T1 = -fB - sqrt(fD)   from (-B - sqrt(B*B - 4AC))/2A, where A = 1, B = 2*fB
            //    T2 = -fB + sqrt(fD)   from (-B + sqrt(B*B - 4AC))/2A, where A = 1, B = 2*fB
            //
            // One of T1 and T2 must be positive:
            // T1 >= 0  => fB <= -sqrt(fD)
            //    OR
            // T2 >= 0 => fB <= sqrt(fD)
            //
            // That is, is sufficient that fB <= sqrt(fD)
    }

    /// <summary>
    /// This method receives an orb, and computes the point where the resident ray intersects with it,
    /// if it exists.
    /// </summary>
    /// <remarks>
    /// The ray must be normalized to obtain a correct result.<br/>
    /// If the direction of the ray is null, the result is undefined.<br/>
    /// If there's no intersection point, the output parameter used for storing the point won't be modified.
    /// </remarks>
    /// <param name="orb">[IN] The orb whose intersections with the ray we want to check.</param>
    /// <param name="vIntersection">[OUT] A vector where to store the closest intersection point to the origin of the ray.</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The origin of the ray lays on the surface / perimeter of the orb and the ray does not point to the orb.
    /// - The origin of the ray is contained in the orb.
    /// - The ray is tangent to the orb.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The ray intersects with the orb in two points.
    /// - The origin of the ray lays on the surface / perimeter of the orb and the ray points to the orb.
    /// </returns>
	EQIntersections IntersectionPoint(const QBaseOrb<VectorTypeOrigin> &orb, VectorTypeOrigin &vIntersection) const
	{
		VectorTypeOrigin vAux;
		return this->IntersectionPoint(orb, vIntersection, vAux);
	}


    /// <summary>
	/// Computes the intersection point between the ray and provided orb, if it exists.
	/// </summary>
    /// <remarks>
	/// The ray must be normalized to obtain a correct result.<br/>
	/// If there's no intersection point, the output parameters won't be modified.<br/>
    /// Neither the length of the direction vector nor the radius of the orb should equal zero.
	/// </remarks>
	/// <param name="orb">[IN] The orb whose intersection with the ray will be checked.</param>
	/// <param name="vIntersection1">[OUT] A vector where to store the closest intersection point to the origin of the ray.</param>
	/// <param name="vIntersection2">[OUT] A vector where to store the furthest intersection point to the origin of the ray.</param>
	/// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The origin of the ray lays on the surface / perimeter of the orb and the ray does not point to the orb.
    /// - The origin of the ray is contained in the orb.
    /// - The ray is tangent to the orb.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The ray intersects with the orb in two points.
    /// - The origin of the ray lays on the surface / perimeter of the orb and the ray points to the orb.
    /// </returns>
    EQIntersections IntersectionPoint(const QBaseOrb<VectorTypeOrigin> &orb, VectorTypeOrigin &vIntersection1, VectorTypeOrigin &vIntersection2) const
    {
        // The direction vector shouldn't be null and the radius of the orb shouldn't equal zero
        QE_ASSERT( SQFloat::IsNotZero(this->Direction.GetLength()) && SQFloat::IsNotZero(orb.Radius), 
                   "The direction vector shouldn't be null and the radius of the orb shouldn't equal zero" );

        // The direction vector must be normalized
        QE_ASSERT( SQFloat::AreEqual(this->Direction.GetLength(), SQFloat::_1), "The direction vector must be normalized" );

        // We set all vectors to the same type that output parameters to allow operations
        const VectorTypeDirection &DIRECTION(this->Direction);

        // We reduce ray and orb to origin, in order to simplify orb equation, and we calculate
        // the new ray origin point
        const VectorTypeOrigin &NEW_RAY_ORIGIN(this->Origin - orb.Center);

        // We replace then in the orb equation to force it to verify the ray equation
        // DIRECTION^2*T^2 + 2*vNewA*DIRECTION*T + vNewA^2 - r^2 = 0
        // The intersections with ray follows this rules (extracted from quadratic ecuation):
        //       D = B^2 - 4AC = 0 => 1 intersection
        //       D = B^2 - 4AC < 0 => 0 intersections
        //       D = B^2 - 4AC > 0 => 2 intersections

        // Since ray is normalized, A = 1
        // const float_q &fA = this->Direction.DotProduct(this->Direction);

        const float_q &fB = SQFloat::_2 * VectorTypeDirection(NEW_RAY_ORIGIN).DotProduct(DIRECTION);
        const float_q &fC = NEW_RAY_ORIGIN.DotProduct(NEW_RAY_ORIGIN) - orb.Radius * orb.Radius;

        // Remember that a = 1 -> D = B^2 - 4AC = B^2 - 4C
        const float_q &fD = fB * fB - SQFloat::_4 * fC;


        if (SQFloat::IsNegative(fD)) // D = B^2 - 4AC < 0 => 0 intersections
            return EQIntersections::E_None;
        else if (SQFloat::IsZero(fD)) // D = B^2 - 4AC = 0 => 1 intersection
        {
            // T = -B/2A -> Remember that a=1
            const float_q &fT = -fB*SQFloat::_0_5;

            // The intersection is backwards the ray origin
            if (SQFloat::IsNegative(fT))
                return EQIntersections::E_None;
            else
            {
                vIntersection1 = NEW_RAY_ORIGIN + fT * DIRECTION + orb.Center;
                return EQIntersections::E_One;
            }
        }
        else // D = B^2 - 4AC > 0 => 2 intersections
        {
            const float_q &SQRT_D = sqrt_q(fD);

            // Closest intersection to ls.A. T1 = (-B - sqrt(D))/2A -> Remember that A = 1
            const float_q &fT1 = -(fB + SQRT_D)*SQFloat::_0_5;

            // Farthest intersection to ls.A. T2 = (-B + sqrt(D))/2A -> Remember that A = 1
            const float_q &fT2 = (-fB + SQRT_D)*SQFloat::_0_5;

            // Prevent rays with origin point inside orb, which must have only one intersection.
            const bool &T1_FAILS = SQFloat::IsNegative(fT1);
            const bool &T2_FAILS = SQFloat::IsNegative(fT2);

            if (T1_FAILS && T2_FAILS)
                return EQIntersections::E_None; // Shouldn't happen this :(
            else if (T1_FAILS)  // One parameter is negative, there is only one intersection
            {
                vIntersection1 = NEW_RAY_ORIGIN + fT2 * DIRECTION + orb.Center;
                return EQIntersections::E_One;
            }
            else if (T2_FAILS) // One parameter is negative, there is only one intersection
            {
                vIntersection1 = NEW_RAY_ORIGIN + fT1 * DIRECTION + orb.Center;
                return EQIntersections::E_One;
            }
            else // Most of the cases: two intersections.
            {
                vIntersection1 = NEW_RAY_ORIGIN + fT1 * DIRECTION + orb.Center;
                vIntersection2 = NEW_RAY_ORIGIN + fT2 * DIRECTION + orb.Center;
                return EQIntersections::E_Two;
            }
        }
    }

    /// <summary>
	/// Converts ray into a string.
    /// </summary>
    /// <remarks>
    /// The format of the string is:<br/>
	/// "RY(o($Origin),d($Direction))".<br/>
    /// Where "$" means "string representation of attribute".
    /// </summary>
    /// <returns>
    /// The string representation with the format specified.
    /// </returns>
    string_q ToString() const
    {
        return QE_L("RY(o(") + this->Origin.ToString() + QE_L("),d(") + this->Direction.ToString() + QE_L("))");
    }

};


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QRAY__
