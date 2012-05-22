// [TERMS&CONDITIONS]

#ifndef __QLINESEGMENT__
#define __QLINESEGMENT__

//#include "MathDefinitions.h"
#include "EQIntersections.h"
#include "QBaseLineSegment.h"
#include "QBaseOrb.h"
#include "SQAngle.h"

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
/// Class which represents a chunk (segment) of straight line in the space, defined by two endpoints A and B.<br>
/// These points may be expressed as 2D or 3D points or vectors, depending on the template parameter,
/// which may be 2D vector, 3D vector or 4D vector.<br>
/// Please note there's really no "source" and "end" points implicit, that is, it's not an oriented segment
/// except for the unit line (see below).
/// </summary>
template <class VectorType>
class QDllExport QLineSegment : public QBaseLineSegment<VectorType>
{

    // BASE CLASS USINGS
    // -------------------
public:

    using QBaseLineSegment<VectorType>::A;
    using QBaseLineSegment<VectorType>::B;


	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	inline QLineSegment()
    {
    }

	/// <summary>
	/// Copy constructor.
	/// </summary>
	/// <param name="segment">[IN] The segment in which we want resident segment to be based.</param>
	inline QLineSegment(const QLineSegment<VectorType> &segment) : QBaseLineSegment<VectorType>(segment)
    {
    }

	/// <summary>
    /// Constructor from two vectors.
    /// </summary>
    /// <param name="vA">[IN] Vector to define endpoint A.</param>
    /// <param name="vB">[IN] Vector to define endpoint B.</param>
	inline QLineSegment(const VectorType &vA, const VectorType &vB) : QBaseLineSegment<VectorType>(vA,vB)
    {
    }

	/// <summary>
    /// Constructor from a line segment.
    /// </summary>
    /// <param name="segment">[IN] Line segment containing the two endpoints.</param>
	inline explicit QLineSegment(const QBaseLineSegment<VectorType> &segment) : QBaseLineSegment<VectorType>(segment)
    {
    }


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets a unit segment lying on positive X axis (it's length equals 1).
    /// </summary>
    /// <returns>
	/// A 1-length segment.
	/// </returns>
	inline static const QLineSegment<VectorType>& GetUnitLine()
	{
	    static const QLineSegment<VectorType> UNITLINE(VectorType::GetZeroVector(), VectorType::GetUnitVectorX());
	    return UNITLINE;
	}

    /// <summary>
    /// Gets a zero segment lying in the coordinates center whose endpoints
	/// both equals to (0,0) and it's length equals 0.
    /// </summary>
    /// <returns>
	/// A zero-length segment.
	/// </returns>
	inline static const QLineSegment<VectorType>& GetLineZero()
	{
	    static const QLineSegment<VectorType> LINEZERO(VectorType::GetZeroVector(), VectorType::GetZeroVector());
	    return LINEZERO;
	}


	// METHODS
	// ---------------
public:

	/// <summary>
	/// Assigning operator.
	/// </summary>
	/// <param name="segment">[IN] The 2D segment to be copied from.</param>
	/// <returns>
	/// A reference to the modified line segment.
	/// </returns>
    inline QLineSegment& operator=(const QBaseLineSegment<VectorType> &segment)
    {
        QBaseLineSegment<VectorType>::operator=(segment);
        return *this;
    }

	/// <summary>
    /// Computes the length of the segment, that is, the distance between the segment endpoints A and B.
    /// </summary>
    /// <returns>
    /// The resultant distance between the two endpoints.
    /// </returns>
	inline float_q GetLength() const
	{
		return A.Distance(B);
	}

	/// <summary>
	/// Computes the central point of the segment.
	/// </summary>
    /// <returns>
    /// The center of the segment.
    /// </returns>
	inline QLineSegment<VectorType> GetCenter() const
	{
		// 1) Direction: AB --> B - A, so that: S(t) = A + [t(B - A)] = ... = t(A + B)
		// 2) Center:    S(0.5f) --> A + [0.5f(B - A)] --> ... --> 0.5f(A + B)
		return SQFloat::_0_5 * (A + B);
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
		// if MinDistance is 0		  --> there's intersection, return true
		// else						  --> return false
		return  SQFloat::IsZero(this->MinDistance(segment));
	}

	/// <summary>
	/// This method receives a orb, and computes if it intersects the resident segment or not.
	/// </summary>
	/// <param name="orb">[IN] The orb to be compared to.</param>
	/// <returns>
	/// True if the segment intersects the orb (or if they were either tangent or coincident). Otherwise returns false.
	/// </returns>
	inline bool Intersection(const QBaseOrb<VectorType> &orb) const
	{
		// An intersection between the segment and the orb is considered if the minimum
		// distance between "the whole segment" and the center of the orb (this is, the
		// minimum distance between the center of the orb and the closest point inside
		// the segment) is either lesser or equal to the radius of the orb.
		return SQFloat::IsLessOrEquals(this->MinDistance(orb.Center), orb.Radius);

	};

	/// <summary>
	/// This method receives another line segment, and computes the intersection point between them,
	/// if it exists.
	/// </summary>
	/// <param name="segment">[IN] The segment to be compared to.</param>
	/// <param name="vIntersection">[OUT] The point where they intersect.</param>
	/// <returns>
	/// Returns how many intersections have been detected.
	/// </returns>
	/// <remarks>
	/// If there's no intersection points, the output parameters used for storing these points won't be modified.
	/// </remarks>
	inline EQIntersections IntersectionPoint(const QBaseLineSegment<VectorType> &segment, VectorType &vIntersection) const
 	{
		// Remark: S1 == (*this), Segment S2 == the input segment parameter.

		VectorType v1		   = B - A;
	    VectorType v2		   = segment.B - segment.A;

        float_q fSqrLengthProd = v1.GetSquaredLength() * v2.GetSquaredLength();

		if ( SQFloat::IsZero(fSqrLengthProd) )
		{
			// CASE 1)
			// Either S1 or S2 (or both) degenerates into a point --> Intersections: None or One.
			//
			// In this case, just compute the closests points between the segments.
			//	 -If they result to be the same point at last, there's
			//    an intersection, and that point is the point of intersection.
			//
			VectorType vClosestPtInS1ToS2, vClosestPtInS2ToS1;
			this->GetClosestPoints(segment, vClosestPtInS1ToS2, vClosestPtInS2ToS1);

			if (vClosestPtInS1ToS2 == vClosestPtInS2ToS1) // One single intersection is assumed.
			{
				vIntersection = vClosestPtInS1ToS2; // The same with vClosestPtInS2ToS1.
				return EQIntersections::E_One;
			}
			else										 // No intersections.
			{
				return EQIntersections::E_None;
			}
		}
		else // Neither segments have length 0 --> fSqrLengthProd ALWAYS > 0 at this stage.
		{

			// Compute the sinus of the angle between v1 and v2.

			float_q fAngle = v1.DotProductAngle(v2);

			// If angles are currently specified in degrees, then converts angle to radians
			// so we can use "sin" function.
			#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
				fAngle = SQAngle::DegreesToRadians(fAngle);
			#endif

			// At this stage we have the angle expressed in RADIANS.
			float_q fSin   = sin_q(fAngle);

			// Compute Squared Module of cross product:
			float_q fSquaredMod = fSqrLengthProd * fSin * fSin;

			if ( SQFloat::IsNotZero(fSquaredMod) )
			{
				// CASE 2)
				// In this case, the situation is as follows:
				//
				//  -The lines containing the segments doesn't intersect between themselves,
				//	 so the same can be said for the segments.
				// OR
				//	-The lines containing the segments intersect in a single point...
				//	 ...but do the segments make the same?.
				//
				//  For asking these questions we need the closest points to each segment
				//  from respect the other one.
				VectorType vClosestPtInS1ToS2, vClosestPtInS2ToS1;
				this->GetClosestPoints(segment, vClosestPtInS1ToS2, vClosestPtInS2ToS1);

				if (vClosestPtInS1ToS2 == vClosestPtInS2ToS1)
				{
					// Segments intersect each other IN A SINGLE POINT.

					vIntersection = vClosestPtInS1ToS2; // The same with vClosestPtInS2ToS1.
					return EQIntersections::E_One;
				}
				else
				{
					// Segments doesn't intersect each other either:
					//  - The lines containing the segments DOESN'T intersect between themselves.
					// OR
					//  - The lines containing the segments DOES intersect between themselves in a single point...
					//	  ...but that intersection occurs "outside" of the segments, it's not a point belonging
					//	  to them.

					return EQIntersections::E_None;
				}
			}
			else // 0 == fSquaredMod
			{
				// CASE 3)
				// In this case, the situation is as follows:
				//
				//  -The lines containing the segments are PARALLEL between themselves, so do the segments --> NO intersections.
				// OR
				//  -Both segments lie on the SAME line, so there can be:
				//
				//	   -No intersection points.
				//	   -One single intersection point.
				//     -Infinite intersection points.
				//
				//   It may depend of the situation, more info provided below on the walk.

				float_q fMinDistance = this->MinDistance(segment);

				if ( SQFloat::IsNotZero(fMinDistance) ) // fMinDistance always nonnegative --> fMinDistance > 0
				{
					// fMinDistance > 0 -->  -Segments are PARALLEL
					//						OR
					//						 -They lie on the same line, but they DOESN'T intersect.
					//
					//						Anyway, NO intersections.

					return EQIntersections::E_None;
				}
				else // 0 == fMinDistance, Intersection Points: One OR Infinite.
				{
					// BOTH segments lie on the SAME line --> Angle (v1,v2) == 0 OR 180 degrees <-- Please note at this stage v1.DotProduct(v2) ALWAYS != 0

					if (A == segment.A)
					{
						if (B == segment.B)
						{
							// Segments are totally coincident (both sharing their two
							// endpoints: A <-> segment.A, B <-> segment.B) --> Infinite intersection points.

							return EQIntersections::E_Infinite;
						}
						else // Not totally coincident.
						{
							if ( SQFloat::IsGreaterThan(v1.DotProduct(v2), SQFloat::_0) ) // Angle(v1,v2) is 0 degrees, v1 and v2 have the same direction.
							{
								// One of the segments are totally cointained inside the other
								// AND sharing one single endpoint (A <-> segment.A) --> Infinite intersection points.

								return EQIntersections::E_Infinite;
							}
							else														// v1.DotProduct(v2) < 0 --> Angle(v1,v2) is 180 degrees, v1 and v2 have opposite direction.
							{
								// Segments are not contained inside themselves AND intersect in
								// a single point, an endpoint of share (A <-> segment.A) --> One intersection.

								vIntersection = A;			// The same with segment.A
								return EQIntersections::E_One;
							}
						}
					}
					else if (B == segment.B) // A != segment.A
					{
						if ( SQFloat::IsGreaterThan(v1.DotProduct(v2), SQFloat::_0) ) // Angle(v1,v2) is 0 degrees, v1 and v2 have the same direction.
						{
							// One of the segments are totally cointained inside the other
							// AND sharing one single endpoint (B <-> segment.B) --> Infinite intersection points.

							return EQIntersections::E_Infinite;
						}
						else														// v1.DotProduct(v2) < 0 --> Angle(v1,v2) is 180 degrees, v1 and v2 have opposite direction.
						{
							// Segments are not contained inside themselves AND intersect in
							// a single point, an endpoint of share (B <-> segment.B) --> One intersection.

							vIntersection = B;			// The same with segment.B
							return EQIntersections::E_One;
						}
					}
					else if (A == segment.B) // (A != segment.A) && (B != segment.B)
					{
						if (segment.A == B)
						{
							// Segments are totally coincident (both sharing their two
							// endpoints: A <-> segment.B, segment.A <-> B) --> Infinite intersection points.

							return EQIntersections::E_Infinite;
						}
						else // Not totally coincident.
						{
							if ( SQFloat::IsGreaterThan(v1.DotProduct(v2), SQFloat::_0) ) // Angle(v1,v2) is 0 degrees, v1 and v2 have the same direction.
							{
								// Segments are not contained inside themselves AND intersect in
								// a single point, an endpoint of share (A <-> segment.B) --> One intersection.

								vIntersection = A;			// The same with segment.B
								return EQIntersections::E_One;
							}
							else														// v1.DotProduct(v2) < 0 --> Angle(v1,v2) is 180 degrees, v1 and v2 have opposite direction.
							{
								// One of the segments are totally cointained inside the other
								// AND sharing one single endpoint (A <-> segment.b) --> Infinite intersection points.

								return EQIntersections::E_Infinite;
							}
						}
					}
					else if (segment.A == B) // (A != segment.A) && (B != segment.B) && (A != segment.B)
					{
						if ( SQFloat::IsGreaterThan(v1.DotProduct(v2), SQFloat::_0) )  // Angle(v1,v2) is 0 degrees, v1 and v2 have the same direction.
						{
							// Segments are not contained inside themselves AND intersect in
							// a single point, an endpoint of share (B <-> segment.A) --> One intersection.

							vIntersection = B;			// The same with segment.A
							return EQIntersections::E_One;
						}
						else														 // v1.DotProduct(v2) < 0 --> Angle(v1,v2) is 180 degrees, v1 and v2 have opposite direction.
						{
							// One of the segments are totally cointained inside the other
							// AND sharing one single endpoint (B <-> segment.A) --> Infinite intersection points.

							return EQIntersections::E_Infinite;
						}
					}
					else				  // (A != segment.A) && (B != segment.B) && (A != segment.B) && (segment.A != B)
					{
						//  -Segments are just parcially coincident (no endpoints shared).
						// OR
						//  -One of the segments are totally cointained inside the other, AND no endpoints shared.
						//
						// Anyway, Infinite intersection points (the chunk of segment -OR the whole segment- contained inside).

						return EQIntersections::E_Infinite;
					}
				} // if ( SQFloat::IsNotZero(fMinDistance)
			} // if ( SQFloat::IsNotZero(fSquaredMod)
		} // if ( SQFloat::IsZero(fLenght)

	}

	/// <summary>
    /// This method receives an orb and computes the points where the resident line segment intersects with it,
    /// if they exist.
    /// </summary>
    /// <param name="orb">[IN] The orb whose intersections with resident line segment we want to check.</param>
    /// <param name="vIntersection1">[OUT] A vector where to store the first intersection point.</param>
    /// <param name="vIntersection2">[OUT] A vector where to store the second intersection point.</param>
    /// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the orb, and can take
    /// the following values: E_None, E_One and E_Two.
    /// </returns>
    /// <remarks>
    /// If there's no intersection point, the two output parameters used for storing the points won't be modified.<br>
    /// If there are two intersections, the first output parameter stores the closest to A end point of
    /// line segment, and the second one stores the closest to B end point.
    /// </remarks>
	inline EQIntersections IntersectionPoint(const QBaseOrb<VectorType> &orb, VectorType &vIntersection1, VectorType &vIntersection2) const
	{
		// We reduce line segment and orb to origin, in order to simplify orb equation, and we calculate
		// the new point A and vector B-A, to compute intersection as with a ray
		VectorType vNewA(this->A - orb.Center);
		VectorType vDirection(this->B - this->A);

		// We replace then in the orb equation to force it to verify the ray equation
		// vDirection^2*t^2 + 2*vNewA*vDirection*t + vNewA^2 - r^2 = 0
		// The intersections with ray follows this rules (extracted from quadratic ecuation):
		//       D = b^2 - 4ac = 0 => 1 intersection
		//       D = b^2 - 4ac < 0 => 0 intersections
		//       D = b^2 - 4ac > 0 => 2 intersections

		const float_q &a = vDirection.DotProduct(vDirection);
		const float_q &b = SQFloat::_2 * vNewA.DotProduct(vDirection);
		const float_q &c = vNewA.DotProduct(vNewA) - orb.Radius * orb.Radius;

		const float_q &D = b * b - SQFloat::_4 * a * c;

		// D = b^2 - 4ac < 0 => 0 intersections
		if (SQFloat::IsNegative(D))
			return EQIntersections::E_None;

		// D = b^2 - 4ac = 0 => 1 intersection
		else if (SQFloat::IsZero(D))
		{
			QE_ASSERT(SQFloat::IsNotZero(a))

			const float_q &t = -(b*SQFloat::_0_5/a);

			VectorType vAux(vNewA + t * vDirection + orb.Center);

			if (SQFloat::IsZero(this->MinDistance(vAux)))
			{
				vIntersection1 = vAux;
				return EQIntersections::E_One;
			}
			else
				return EQIntersections::E_None;
		}

		// D = b^2 - 4ac > 0 => 2 intersections
		else
		{
			QE_ASSERT(SQFloat::IsNotZero(a))

			const float_q &fAux1 = sqrt_q(D);
			const float_q &fAux2 = SQFloat::_0_5/a;

			// Closest intersection to ls.A
			const float_q &t1 = (-b - fAux1)*fAux2;
			VectorType vAux1(vNewA + t1 * vDirection + orb.Center);

			// Farthest intersection to ls.A
			const float_q &t2 = (-b + fAux1)*fAux2;
			VectorType vAux2(vNewA + t2 * vDirection + orb.Center);

			const bool &bIsInSegment1 = SQFloat::IsZero(this->MinDistance(vAux1));
			const bool &bIsInSegment2 = SQFloat::IsZero(this->MinDistance(vAux2));

			// Both points are in line segment.
			if (bIsInSegment1 && bIsInSegment2)
			{
				vIntersection1 = vAux1;
				vIntersection2 = vAux2;
				return EQIntersections::E_Two;
			}
			// Only t1 point is in line segment.
			else if (bIsInSegment1)
			{
				vIntersection1 = vAux1;
				return EQIntersections::E_One;
			}

			// Only t2 is in line segment.
			else if (bIsInSegment2)
			{
				vIntersection1 = vAux2;
				return EQIntersections::E_One;
			}
			// There are no intersections.
			else
				return EQIntersections::E_None;
		}
	}

	/// <summary>
    /// This method receives an orb, and computes the point where the resident line segment intersects with it,
    /// if it exists.
    /// </summary>
    /// <param name="orb">[IN] The orb whose intersections with resident line segment we want to check.</param>
    /// <param name="vIntersection">[OUT] A vector where to store the intersection point.</param>
    /// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the orb, and can take
    /// the following values: E_None, E_One and E_Two.
    /// </returns>
    /// <remarks>
    /// If there's no intersection point, the output parameter used for storing the point won't be modified.<br>
    /// If there is an intersection, the output parameter stores the closest point to A.
    /// </remarks>
	inline EQIntersections IntersectionPoint(const QBaseOrb<VectorType> &orb, VectorType &vIntersection) const
	{
		VectorType vAux;
		return this->IntersectionPoint(orb, vIntersection, vAux);
	}

	/// <summary>
	/// Given an input line segment, this method returns the minimum distance between this and the input one,
	///	that is, the distance between their closest points.
	/// </summary>
	/// <param name="segment">[IN] The line segment the distance will be measured to.</param>
	/// <returns>
	/// A floating point value (always nonnegative) which represents the minimum distance between the two segments.
	/// </returns>
	float_q MinDistance(const QBaseLineSegment<VectorType> &segment) const
	{
		// Just compute the closests points between the segments, and return
		// the distance between them; that is the minimum distance.
		//
		// Remark: S1 == (*this), Segment S2 == the input segment parameter.

		VectorType vClosestPtInS1ToS2, vClosestPtInS2ToS1;
		this->GetClosestPoints(segment, vClosestPtInS1ToS2, vClosestPtInS2ToS1);

		return vClosestPtInS1ToS2.Distance(vClosestPtInS2ToS1);
	}

	/// <summary>
	/// Given an input vector (which represents a point), this method returns the minimum distance between this and
	/// the segment, that is, the distance between the input point and the closest point lying into the segment.
	/// </summary>
	/// <param name="vPoint">[IN] The point the distance will be measured to.</param>
	/// <returns>
	/// A floating point value (always nonnegative) which represents the minimum distance between point and segment.
	/// </returns>
	float_q MinDistance(const VectorType &vPoint) const
	{
		if (A != B)
		{
			// STEP 0) v1 = B - A, v2 = vPoint - A
			// STEP 1) if ( DotProduct(v1, v2) <= 0 ) --> Angle(v1, v2) >= (PI / 2) --> vPoint is closer to A, MinDistance = Length(v2)
			//		   else
			//		   STEP 2) if ( DotProduct (v1, v2) >= DotProduct(v1, v1) ) --> vPoint is closer to B, MinDistance = Length(vPoint - B)
			//				   else
			//				   STEP 3) ProjectionOverAB(vPoint) falls into the segment, so:
			//						   MinDistance = Length( ProjectionOverAB(vPoint) - vPoint ) = Length( (A + ((DotProduct(v1, v2) / DotProduct(v1, v1)) * v1)) - vPoint )
			float_q fDotProductv1v1 = SQFloat::_0;
			VectorType v1		    = B - A;
			VectorType v2			= vPoint - A;
			float_q fDotProductv1v2 = v1.DotProduct(v2);

			if ( (SQFloat::IsNegative(fDotProductv1v2)) || (SQFloat::IsZero(fDotProductv1v2)) )
			{
				return v2.GetLength();
			}
			else
			{
				fDotProductv1v1 = v1.DotProduct(v1);

                if ( SQFloat::IsGreaterOrEquals(fDotProductv1v2, fDotProductv1v1) )
				{
					return ( (vPoint - B).GetLength() );
				}
				else
				{
					// Checkout to avoid division by 0
					QE_ASSERT (fDotProductv1v1 != SQFloat::_0)

					return ((A + ((fDotProductv1v2 / fDotProductv1v1) * v1)) - vPoint).GetLength();
				}

			}
		} // if (A != B
		else
		{
			return (vPoint - B).GetLength(); // (vPoint - A) could have been used as well.
		}
	}

	/// <summary>
	/// Given an input line segment, this method returns the maximum distance between this and the input one,
	///	that is, the distance between their farthest points.
	/// </summary>
	/// <param name="segment">[IN] The line segment the distance will be measured to.</param>
	/// <returns>
	/// A floating point value (always nonnegative) which represents the maximum distance between the two segments.
	/// </returns>
	inline float_q MaxDistance(const QBaseLineSegment<VectorType> &segment) const
	{
		// STEP 1) Compute Maximum distance from endpoint A (belonging to the parameter) to this segment.
		// STEP 2) Compute Maximum distance from endpoint B (belonging to the parameter) to this segment.
		float_q fMaxDistance_segmtA_This = this->MaxDistance(segment.A);
		float_q fMaxDistance_segmtB_This = this->MaxDistance(segment.B);

		// STEP 3) Maximum distance between the segments = maximum distance between their farthest endpoints.
		//												 = the longer distance between the maximum distances from endpoints
		//												   of the segment passed by parameter to this segment.
        return SQFloat::IsGreaterThan(fMaxDistance_segmtA_This, fMaxDistance_segmtB_This) ? fMaxDistance_segmtA_This : fMaxDistance_segmtB_This;
	}

	/// <summary>
	/// Given an input vector (which represents a point), this method returns the maximum distance between this and
	/// the segment, that is, the distance between the input point and the farthest point lying into the segment...
	/// ...and this will be one of the segment endpoints!.<br>
	/// Please note the above is correct only when the point lies outside the segment; if it's inside the segment,
	/// the maximum distance equals to 0.
	/// </summary>
	/// <param name="vPoint">[IN] The point the distance will be measured to.</param>
	/// <returns>
	/// A floating point value (always nonnegative) which represents the maximum distance between point and segment.
	/// </returns>
	float_q MaxDistance(const VectorType &vPoint) const
	{
		// STEP 0) if vPoint is inside the segment the maximum distance will be 0
		//		   else
		//		   STEP 1) v1 = B - A, v2 = vPoint - A
		//		   STEP 2) if ( DotProduct(v1, v2) <= 0 ) --> Angle(v1, v2) >= (PI / 2) --> vPoint is closer to A, MaxDistance = Length(vPoint - B)
		//				   else
		//				   STEP 3) if ( DotProduct (v1, v2) >= DotProduct(v1, v1) ) --> vPoint is closer to B, MaxDistance = Length(v2)
		//						   else
		//						   STEP 4) ProjectionOverAB(vPoint) falls into the segment, so:
		//								   MaxDistance = Biggest( Distance(vPoint,A) , Distance(vPoint,B) )
		if ( SQFloat::IsNotZero(this->MinDistance(vPoint)) )
		{
			VectorType v1		    = B - A;
			VectorType v2			= vPoint - A;
			VectorType v3			= vPoint - B;
			float_q fDotProductv1v1 = SQFloat::_0;
			float_q fDotProductv1v2 = v1.DotProduct(v2);

			if ( (SQFloat::IsNegative(fDotProductv1v2)) || (SQFloat::IsZero(fDotProductv1v2)) )
			{
				return ( v3.GetLength() );
			}
			else
			{
				fDotProductv1v1 = v1.DotProduct(v1);

                if ( SQFloat::IsGreaterOrEquals(fDotProductv1v2, fDotProductv1v1) )

				{
					return v2.GetLength();
				}
				else
				{
					float_q fDistancePointToA = v2.GetLength();
					float_q fDistancePointToB = v3.GetLength();

                    return SQFloat::IsGreaterThan(fDistancePointToA, fDistancePointToB) ? fDistancePointToA : fDistancePointToB;
				}
			}
		}
		else
		{
			return SQFloat::_0;
		}

	}

	/// <summary>
	/// Given a lengthening factor, this method computes the lengthening of the segment; endpoints move away or approach
	/// to the center, depending of the lengthening factor value.
	/// </summary>
	/// <param name="fLengtheningFactor">[IN] A floating point value that lengthens the segment.</param>
	/// <remarks>
	/// If the lengthening factor is 0.0, the segment degenerates into a point (both endpoints become the center).<br>
	/// If the lengthening factor is 1.0, the segment won't experiment any modification, as this represent a 100% lengthening.
	/// </remarks>
	void Lengthen(const float_q &fLengtheningFactor)
	{
		// If Lengthening Factor == 1 we just don't touch the segment.
		if ( SQFloat::AreNotEquals(fLengtheningFactor, SQFloat::_1) )
		{
			VectorType vCenter;
			this->GetCenter(vCenter);

			// If Lengthening Factor == 0, just reduce the endpoints to the center.
			if (SQFloat::AreEquals(fLengtheningFactor, SQFloat::_0))
			{
				A = vCenter;
				B = vCenter;
			}
			else // Compute the new segment endpoints from the center.
			{
				A = vCenter + (fLengtheningFactor * (A - vCenter) );
				B = vCenter + (fLengtheningFactor * (B - vCenter) );
			}
		}
	}

	/// <summary>
	/// Given a lengthening factor, this method computes the lengthening of the segment; endpoint B moves away or approaches to A,
	/// depending of the lengthening factor value. In any case, A stays the same.
	/// </summary>
	/// <param name="fLengtheningFactor">[IN] A floating point value that lengthens the segment.</param>
	/// <remarks>
	/// If lengthening factor is 0.0, the segment degenerates into a point (both endpoints become A).<br>
	/// If lengthening factor is 1.0, the segment won't experiment any modification, as this represent a 100% lengthening.
	/// </remarks>
	void LengthenFromA(const float_q &fLengtheningFactor)
	{
		// If Lengthening Factor == 1 we just don't touch the segment.
		if ( SQFloat::AreNotEquals(fLengtheningFactor, SQFloat::_1) )
		{
			// If Lengthening Factor == 0, just reduce the endpoints to A.
			if ( SQFloat::AreEquals(fLengtheningFactor, SQFloat::_0) )
			{
				B = A;
			}
			else // Lengthen from A --> Compute the new B.
			{
				B = A + (fLengtheningFactor * (B - A));
			}
		}
	}

	/// <summary>
	/// Given a lengthening factor, this method computes the lengthening of the segment; endpoint A moves away or approaches to B,
	/// depending of the lengthening factor value. In any case, B stays the same.
	/// </summary>
	/// <param name="fLengtheningFactor">[IN] A floating point value that lengthens the segment.</param>
	/// <remarks>
	/// If lengthening factor is 0.0, the segment degenerates into a point (both endpoints become B).<br>
	/// If lengthening factor is 1.0, the segment won't experiment any modification, as this represent a 100% lengthening.
	/// </remarks>
	void LengthenFromB(const float_q &fLengtheningFactor)
	{
		// If Lengthening Factor == 1 we just don't touch the segment.
		if ( SQFloat::AreNotEquals(fLengtheningFactor, SQFloat::_1) )
		{
			// If Lengthening Factor == 0, just reduce the endpoints to B.
			if ( SQFloat::AreEquals(fLengtheningFactor, SQFloat::_0) )
			{
				A = B;
			}
			else // Lengthen from B --> Compute the new A.
			{
				A = B + (fLengtheningFactor * (A - B));
			}
		}
	}

	/// <summary>
	/// Converts vector into a string with the following format:<br>
	/// "LS(a($A),b($B))".<br>
    /// Where "$" means "string representation of attribute".
	/// </summary>
	/// <returns>
    /// The string with the format specified.
    /// </returns>
	string_q ToString()
	{
		return QE_L("LS(a(") + A.ToString() + QE_L("),b(") + B.ToString() + QE_L("))");
	}

protected:

	// <summary>
	// This method computes the closest points between two line segments.
	// </summary>
	// <param name="segment">[IN] The segment to whom the distace has to be computed from.</param>
	// <param name="vClosestPtInS1ToS2">[OUT] It stores the closest point to S2 belonging to S1.</param>
	// <param name="vClosestPtInS2ToS1">[OUT] It stores the closest point to S1 belonging to S2.</param>
	// <remarks>
	// We assume S1 is the segment which executes this member function, and S2 the segment passed as
	// a parameter to S1.
	// </remarks>
	void GetClosestPoints(const QBaseLineSegment<VectorType> &segment,
						  VectorType& vClosestPtInS1ToS2, VectorType& vClosestPtInS2ToS1) const
	{
		bool bBothDegeneratedIntoPoints = false; // True if both segments degenerate into points.

		// STEP 0) -Segment S1 == (*this)		== B - A
		//		   -Segment S2 == the parameter == segment.B - segment.A
		//		   -fSFactor1,fSFactor2: [0,1]  == Sample factors, so the closest points between S1 and S2
		//										   will be given through:
		//
		//												S1(fSFactor1) = (A + (fSFactor1 * v1))
		//												S2(fSFactor2) = (segment.A + (fSFactor2 * v2))
		float_q	   fSFactor1  = SQFloat::_0;
		float_q	   fSFactor2  = SQFloat::_0;
		VectorType v1		  = B - A;
	    VectorType v2		  = segment.B - segment.A;

		// STEP 1) Precomputing intermediate values for solving s and t.
	    float_q	   fSqrLengthv1		  = v1.DotProduct(v1);	// Squared length of segment S1, always nonnegative.
	    float_q	   fSqrLengthv2		  = v2.DotProduct(v2);	// Squared length of segment S2, always nonnegative.
		VectorType vTails			  = A - segment.A;			// Segment whose endpoints are the "tail" points of each segment.
	    float_q	   fDotProdv2vTails   = v2.DotProduct(vTails);

	    // STEP 2) Check if either or both segments degenerate into points
	    if ( (SQFloat::IsZero(fSqrLengthv1)) && (SQFloat::IsZero(fSqrLengthv2)) )
		{
	        // BOTH segments degenerate into points --> The closest points are THEMSELVES.
			vClosestPtInS1ToS2		   = A;		  // The same with B.
			vClosestPtInS2ToS1		   = segment.A; // The same with segment.B
			bBothDegeneratedIntoPoints = true;
	    }

		if (!bBothDegeneratedIntoPoints)
		{
		    if (SQFloat::IsZero(fSqrLengthv1))
			{
		        // S1 (*this) degenerates into a point;
				// fSFactor1 = 0 --> fSFactor2 = (((fDotProdv1v2 * fSFactor1) + fDotProdv2vTails) / fSqrLengthv2) = (fDotProdv2vTails / fSqrLengthv2)

				// Checkout to avoid division by 0
				QE_ASSERT(fSqrLengthv2 != SQFloat::_0)

				fSFactor2 = SQFloat::Clamp( (fDotProdv2vTails / fSqrLengthv2), SQFloat::_0, SQFloat::_1);
		    }
			else
			{
		        float_q fDotProdv1vTails = v1.DotProduct(vTails);

		        if (SQFloat::IsZero(fSqrLengthv2))
				{
		            // S2 (the parameter) degenerates into a point;
					// fSFactor2 = 0 --> fSFactor1 = (((fDotProdv1v2 * fSFactor2) - fDotProdv1vTails) / fSqrLengthv1) = (-fDotProdv1vTails / fSqrLengthv1)

					// Checkout to avoid division by 0
					QE_ASSERT(fSqrLengthv1 != SQFloat::_0)

					fSFactor1 = SQFloat::Clamp( (-fDotProdv1vTails / fSqrLengthv1), SQFloat::_0, SQFloat::_1 );

		        }
				else
				{
		            // Length of both segments are > 0;
					// STEP 3) Compute values for fSFactor1 and fSFactor2
					//
		            float_q fDotProdv1v2 = v1.DotProduct(v2);
		            float_q fDenom       = (fSqrLengthv1 * fSqrLengthv2) - (fDotProdv1v2 * fDotProdv1v2); // Always nonnegative:
																								      //	fDenom == 0 --> S1 || S2;
																								      //	fDenom >  0 --> S1 not || S2
					// STEP 3.1)
		            // If segments not parallel, compute sample factor for S1, fSFactor1, and
		            // clamp to segment S1. (** if they're paraller pick arbitrary fSFactor1 -here 0- **)
					//
					// fSFactor1 = ((fDotProdv1v2 * fDotProdv2vTails) - (fDotProdv1vTails * fSqrLengthv2)) / fDenom
		            if (SQFloat::IsNotZero(fDenom))
					{
						fSFactor1 = SQFloat::Clamp( ((fDotProdv1v2 * fDotProdv2vTails) - (fDotProdv1vTails * fSqrLengthv2)) / fDenom, SQFloat::_0, SQFloat::_1 );
		            }
					else
					{
						fSFactor1 = SQFloat::_0;
					}

		            // STEP 3.2) Compute sample factor for S2, fSFactor2
		            float_q fNom = (fSFactor1 * fDotProdv1v2) + fDotProdv2vTails;

		            // If fNom in range [0..1] --> fSFactor2 = fNom / fSqrLengthv2;
					// else clamp fSFactor2 to 0 or 1, recompute fSFactor1 for the new value
		            // of fSFactor2 using:
					//
					//		fSFactor1 = ((fSFactor2 * fDotProdv1v2) - fDotProdv1vTails) / fSqrLengthv1
					//
		            // and clamp fSFactor1 to range [0..1]
					if (SQFloat::IsNegative(fNom))
					{
						fSFactor2 = SQFloat::_0;

						// Checkout to avoid division by 0
						QE_ASSERT(fSqrLengthv1 != SQFloat::_0)

						fSFactor1 = SQFloat::Clamp( (-fDotProdv1vTails / fSqrLengthv1), SQFloat::_0, SQFloat::_1 );
					}
					else if (fNom > fSqrLengthv2)
					{
						fSFactor2 = SQFloat::_1;

						// Checkout to avoid division by 0
						QE_ASSERT(fSqrLengthv1 != SQFloat::_0)

						fSFactor1 = SQFloat::Clamp( ((fDotProdv1v2 - fDotProdv1vTails) / fSqrLengthv1), SQFloat::_0, SQFloat::_1 );

					}
					else // fNom in range [0..1]
					{
						// Checkout to avoid division by 0
						QE_ASSERT(fSqrLengthv2 != SQFloat::_0)

						fSFactor2 = fNom / fSqrLengthv2;
					}
		        }
		    }

			// STEP 4) Finally compute the closest points between S1 and S2 and storing them
			// in the output parameters.
			vClosestPtInS1ToS2 = A + (fSFactor1 * v1);
			vClosestPtInS2ToS1 = segment.A + (fSFactor2 * v2);

		} // if (!bBothDegeneratedIntoPoints
	}

};


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QLINESEGMENT__
