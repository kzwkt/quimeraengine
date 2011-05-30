// [TERMS&CONDITIONS]

#ifndef __QLINESEGMENT__
#define __QLINESEGMENT__

#include "EQIntersections.h"
#include "QBaseLineSegment.h"

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
/// Class which represents a chunk (segment) of straight line in the space, defined by two endpoints A and B.
/// These points may be expressed as 2D or 3D points or vectors, depending on the template parameter, 
/// which may be 2D vector, 3D vector or 4D vector.
/// Please note there's really no "source" and "end" points implicit, that is, it's not an oriented segment
/// except for the unit line (see below).
/// </summary>
template <class VectorType>
class QDllExport QLineSegment : public QBaseLineSegment<VectorType>
{

    // CONSTANTS
    // ---------------
public:

    /// <summary>
    /// Unit segment lying on positive X axis (it's length equals 1).
    /// </summary>
	static const QLineSegment<VectorType> UnitLine;

    /// <summary>
    /// Zero segment lying in the coordinates center whose endpoints
	/// both equals to (0,0) and it's length equals 0.
    /// </summary>
	static const QLineSegment<VectorType> LineZero;


	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	inline QLineSegment() : QBaseLineSegment<VectorType>() { }

	/// <summary>
    /// Constructor from two vectors.
    /// </summary>
    /// <param name="vA">[IN] Vector to define endpoint A.</param>
    /// <param name="vB">[IN] Vector to define endpoint B.</param>
	inline QLineSegment (const VectorType &vA, const VectorType &vB) : QBaseLineSegment<VectorType>(vA,vB) { }

	/// <summary>
    /// Constructor from a line segment.
    /// </summary>
    /// <param name="segmt">[IN] Line segment containing the two endpoints.</param>
	inline explicit QLineSegment (const QBaseLineSegment<VectorType>& segmt) : A(segmt.A), B(segmt.B) { }


	// METHODS
	// ---------------
public:

	/// <summary>
	/// Assigning operator.
	/// </summary>
	/// <param name="segmt">[IN] The 2D segment to be copied from.</param>
	/// <returns>
	/// A reference to the modified line segment.
	/// </returns>
    inline QLineSegment& operator=(const QBaseLineSegment<VectorType>& segmt)
    {
        reinterpret_cast<QBaseLineSegment<VectorType>&>(*this) = segmt;    
        return *this;
    }

	/// <summary>
    /// Computes the length of the segment, that is, the distance between the segment endpoints A and B.
    /// </summary>
    /// <returns>
    /// The resultant distance between the two endpoints.
    /// </returns>
	inline float_q GetLength () const
	{
		return A.Distance(B);
	}

	/// <summary>
	/// Computes the central point of the segment.
	/// </summary>
	/// <param name="vCenter">[OUT] A vector which represents the central point of the segment.</param>
	inline void GetCenter (VectorType& vCenter) const
	{
		// 1) Direction: AB --> B - A, so that: S(t) = A + [t(B - A)] = ... = t(A + B)
		// 2) Center:    S(0.5f) --> A + [0.5f(B - A)] --> ... --> 0.5f(A + B)
		vCenter = QFloat::_0_5 * (A + B);
	}

	/// <summary>
	/// This method receives another line segment, and computes whether they intersect each other or not.
	/// </summary>
	/// <param name="segmt">[IN] The segment to be compared to.</param>
	/// <returns>
	/// True if they intersect each other (or if they were coincident), false if they don't.
	/// </returns>
	inline bool Intersection (const QBaseLineSegment<VectorType>& segmt) const
	{
		// if MinDistance is 0		  --> there's intersection, return true
		// else						  --> return false
		return  QFloat::IsZero(this->MinDistance(segmt));
	}

	/// <summary>
	/// This method receives another line segment, and computes the intersection point between them,
	/// if it exists.
	/// </summary>
	/// <param name="segmt">[IN] The segment to be compared to.</param>
	/// <param name="vIntersectionPt">[OUT] The point where they intersect.</param>
	/// <returns>
	/// True if they intersect each other (or if they were coincident), false if they don't.
	/// </returns>
	/// <remarks>
	/// -If there's no intersection point, the output parameter used for storing that point won't be modified.
	/// -If segments are totally or parcially coincident only a single point will be stored in the output
	///  parameter, presumingly an endpoint belonging to one of the segments.
	/// </remarks>
	inline EQIntersections IntersectionPoint(const QBaseLineSegment<VectorType>& segmt, VectorType& vIntersectionPt) const
 	{
		// Remark: S1 == (*this), Segment S2 == the input segment parameter.

		VectorType v1		   = B - A;									 
	    VectorType v2		   = segmt.B - segmt.A;

        float_q fSqrLengthProd = v1.GetSquaredLength() * v2.GetSquaredLength();

		if ( QFloat::IsZero(fSqrLengthProd) )
		{
			// CASE 1)
			// Either S1 or S2 (or both) degenerates into a point --> Intersections: None or One.
			// 
			// In this case, just compute the closests points between the segments.
			//	 -If they result to be the same point at last, there's
			//    an intersection, and that point is the point of intersection.
			// 
			VectorType vClosestPtInS1ToS2, vClosestPtInS2ToS1;
			this->GetClosestPoints(segmt, vClosestPtInS1ToS2, vClosestPtInS2ToS1);

			if (vClosestPtInS1ToS2 == vClosestPtInS2ToS1) // One single intersection is assumed.
			{
				vIntersectionPt = vClosestPtInS1ToS2; // The same with vClosestPtInS2ToS1.
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

			// [TODO] This block won't serve to any purpose in the future, delete it
			//		  when it's useness has come to an end.
			///////////////////////////////
			// If angles are currently specified in degrees, then converts angle to radians
			// so we can use "sin" function.
			#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
				fAngle = QAngle::DegreesToRadians(fAngle, fAngle);
			#endif
			///////////////////////////////

			// At this stage we have the angle expressed in RADIANS.

			float_q fSin   = sin(fAngle);

			// [TODO] This block won't serve to any purpose in the future, delete it
			//		  when it's useness has come to an end.
			///////////////////////////////
			// Just for safety:
			// If angles are currently specified in degrees, then reconvert angle to degrees.
			#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
				fAngle = QAngle::RadiansToDegrees(fAngle, fAngle);

				// At this stage we'll have the angle expressed in DEGREES.
			#endif
			///////////////////////////////

			// Compute Squared Module of cross product:
			float_q fSquaredMod = fSqrLengthProd * fSin * fSin;

			if ( QFloat::IsNotZero(fSquaredMod) )
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
				this->GetClosestPoints(segmt, vClosestPtInS1ToS2, vClosestPtInS2ToS1);

				if (vClosestPtInS1ToS2 == vClosestPtInS2ToS1)
				{
					// Segments intersect each other IN A SINGLE POINT.

					vIntersectionPt = vClosestPtInS1ToS2; // The same with vClosestPtInS2ToS1.
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
				
				float_q fMinDistance = this->MinDistance(segmt);

				if ( QFloat::IsNotZero(fMinDistance) ) // fMinDistance always nonnegative --> fMinDistance > 0
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

					if (A == segmt.A)
					{
						if (B == segmt.B)
						{
							// Segments are totally coincident (both sharing their two
							// endpoints: A <-> segmt.A, B <-> segmt.B) --> Infinite intersection points.

							return EQIntersections::E_Infinite;
						}
						else // Not totally coincident.
						{
							if ( QFloat::IsGreaterThan(v1.DotProduct(v2), QFloat::_0) ) // Angle(v1,v2) is 0 degrees, v1 and v2 have the same direction.
							{
								// One of the segments are totally cointained inside the other
								// AND sharing one single endpoint (A <-> segmt.A) --> Infinite intersection points.

								return EQIntersections::E_Infinite;
							}
							else														// v1.DotProduct(v2) < 0 --> Angle(v1,v2) is 180 degrees, v1 and v2 have opposite direction.
							{
								// Segments are not contained inside themselves AND intersect in
								// a single point, an endpoint of share (A <-> segmt.A) --> One intersection.

								vIntersectionPt = A;			// The same with segmt.A
								return EQIntersections::E_One;
							}
						}
					}
					else if (B == segmt.B) // A != segmt.A
					{
						if ( QFloat::IsGreaterThan(v1.DotProduct(v2), QFloat::_0) ) // Angle(v1,v2) is 0 degrees, v1 and v2 have the same direction.
						{
							// One of the segments are totally cointained inside the other
							// AND sharing one single endpoint (B <-> segmt.B) --> Infinite intersection points.

							return EQIntersections::E_Infinite;
						}
						else														// v1.DotProduct(v2) < 0 --> Angle(v1,v2) is 180 degrees, v1 and v2 have opposite direction.
						{
							// Segments are not contained inside themselves AND intersect in
							// a single point, an endpoint of share (B <-> segmt.B) --> One intersection.

							vIntersectionPt = B;			// The same with segmt.B
							return EQIntersections::E_One;
						}
					}
					else if (A == segmt.B) // (A != segmt.A) && (B != segmt.B)
					{
						if (segmt.A == B)
						{
							// Segments are totally coincident (both sharing their two
							// endpoints: A <-> segmt.B, segmt.A <-> B) --> Infinite intersection points.

							return EQIntersections::E_Infinite;
						}
						else // Not totally coincident.
						{
							if ( QFloat::IsGreaterThan(v1.DotProduct(v2), QFloat::_0) ) // Angle(v1,v2) is 0 degrees, v1 and v2 have the same direction.
							{
								// Segments are not contained inside themselves AND intersect in
								// a single point, an endpoint of share (A <-> segmt.B) --> One intersection.

								vIntersectionPt = A;			// The same with segmt.B
								return EQIntersections::E_One;
							}
							else														// v1.DotProduct(v2) < 0 --> Angle(v1,v2) is 180 degrees, v1 and v2 have opposite direction.
							{
								// One of the segments are totally cointained inside the other
								// AND sharing one single endpoint (A <-> segmt.b) --> Infinite intersection points.

								return EQIntersections::E_Infinite;
							}
						}
					}
					else if (segmt.A == B) // (A != segmt.A) && (B != segmt.B) && (A != segmt.B)
					{
						if ( QFloat::IsGreaterThan(v1.DotProduct(v2), QFloat::_0) )  // Angle(v1,v2) is 0 degrees, v1 and v2 have the same direction.
						{
							// Segments are not contained inside themselves AND intersect in
							// a single point, an endpoint of share (B <-> segmt.A) --> One intersection.

							vIntersectionPt = B;			// The same with segmt.A
							return EQIntersections::E_One;
						}
						else														 // v1.DotProduct(v2) < 0 --> Angle(v1,v2) is 180 degrees, v1 and v2 have opposite direction.
						{
							// One of the segments are totally cointained inside the other
							// AND sharing one single endpoint (B <-> segmt.A) --> Infinite intersection points.

							return EQIntersections::E_Infinite;
						}
					}
					else				  // (A != segmt.A) && (B != segmt.B) && (A != segmt.B) && (segmt.A != B)
					{
						//  -Segments are just parcially coincident (no endpoints shared).
						// OR
						//  -One of the segments are totally cointained inside the other, AND no endpoints shared.
						//
						// Anyway, Infinite intersection points (the chunk of segment -OR the whole segment- contained inside).

						return EQIntersections::E_Infinite;
					}
				} // if ( QFloat::IsNotZero(fMinDistance)
			} // if ( QFloat::IsNotZero(fSquaredMod)
		} // if ( QFloat::IsZero(fLenght)

	}

	/// <summary>
	/// Given an input line segment, this method returns the minimum distance between this and the input one,
	///	that is, the distance between their closest points.
	/// </summary>
	/// <param name="segmt">[IN] The line segment the distance will be measured to.</param>
	/// <returns>
	/// A floating point value (always nonnegative) which represents the minimum distance between the two segments.
	/// </returns>
	float_q MinDistance (const QBaseLineSegment<VectorType>& segmt) const
	{
		// Just compute the closests points between the segments, and return
		// the distance between them; that is the minimum distance.
		// 
		// Remark: S1 == (*this), Segment S2 == the input segment parameter.

		VectorType vClosestPtInS1ToS2, vClosestPtInS2ToS1;
		this->GetClosestPoints(segmt, vClosestPtInS1ToS2, vClosestPtInS2ToS1);

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
	float_q MinDistance (const VectorType& vPoint) const
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
			float_q fDotProductv1v1 = QFloat::_0;
			VectorType v1		    = B - A;
			VectorType v2			= vPoint - A;
			float_q fDotProductv1v2 = v1.DotProduct(v2);

			if ( (QFloat::IsNegative(fDotProductv1v2)) || (QFloat::IsZero(fDotProductv1v2)) )
			{
				return v2.GetLength();
			}
			else
			{
				fDotProductv1v1 = v1.DotProduct(v1);
				
                if ( QFloat::IsGreaterOrEquals(fDotProductv1v2, fDotProductv1v1) )
				{
					return ( (vPoint - B).GetLength() );
				}
				else
				{
					// Checkout to avoid division by 0
					QE_ASSERT (fDotProductv1v1 != QFloat::_0);
					
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
	/// <param name="segmt">[IN] The line segment the distance will be measured to.</param>
	/// <returns>
	/// A floating point value (always nonnegative) which represents the maximum distance between the two segments.
	/// </returns>
	inline float_q MaxDistance (const QBaseLineSegment& segmt) const
	{
		// STEP 1) Compute Maximum distance from endpoint A (belonging to the parameter) to this segment.
		// STEP 2) Compute Maximum distance from endpoint B (belonging to the parameter) to this segment.
		float_q fMaxDistance_segmtA_This = this->MaxDistance(segmt.A);
		float_q fMaxDistance_segmtB_This = this->MaxDistance(segmt.B);

		// STEP 3) Maximum distance between the segments = maximum distance between their farthest endpoints.
		//												 = the longer distance between the maximum distances from endpoints
		//												   of the segment passed by parameter to this segment.
<<<<<<< .mine
        return QFloat::IsGreaterThan(fMaxDistance_segmtA_This, fMaxDistance_segmtB_This) ? fMaxDistance_segmtA_This : fMaxDistance_segmtB_This;
=======
        return QFloat::IsGreaterThan(fMaxDistance_vBLSA_This, fMaxDistance_vBLSB_This) ? fMaxDistance_vBLSA_This : fMaxDistance_vBLSB_This;
>>>>>>> .r716
	}

	/// <summary>
	/// Given an input vector (which represents a point), this method returns the maximum distance between this and
	/// the segment, that is, the distance between the input point and the farthest point lying into the segment...
	/// ...and this will be one of the segment endpoints!.
	/// Please note the above is correct only when the point lies outside the segment; if it's inside the segment,
	/// the maximum distance equals to 0.
	/// </summary>
	/// <param name="vPoint">[IN] The point the distance will be measured to.</param>
	/// <returns>
	/// A floating point value (always nonnegative) which represents the maximum distance between point and segment.
	/// </returns>
	float_q MaxDistance (const VectorType& vPoint) const
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
		if ( QFloat::IsNotZero(this->MinDistance(vPoint)) )
		{
			VectorType v1		    = B - A;
			VectorType v2			= vPoint - A;
			VectorType v3			= vPoint - B;
			float_q fDotProductv1v1 = QFloat::_0;
			float_q fDotProductv1v2 = v1.DotProduct(v2);

			if ( (QFloat::IsNegative(fDotProductv1v2)) || (QFloat::IsZero(fDotProductv1v2)) )
			{
				return ( v3.GetLength() );
			}
			else
			{
				fDotProductv1v1 = v1.DotProduct(v1);
				
                if ( QFloat::IsGreaterOrEquals(fDotProductv1v2, fDotProductv1v1) )

				{			
					return v2.GetLength();
				}
				else
				{	
					float_q fDistancePointToA = v2.GetLength();
					float_q fDistancePointToB = v3.GetLength();

                    return QFloat::IsGreaterThan(fDistancePointToA, fDistancePointToB) ? fDistancePointToA : fDistancePointToB;
				}
			}
		}
		else
		{
			return QFloat::_0;
		}

	}

	/// <summary>
	/// Given a lengthening factor, this method computes the lengthening of the segment; endpoints move away or approach
	/// to the center, depending of the lengthening factor value.
	/// </summary>
	/// <param name="fLengtheningFactor">[IN] A floating point value that lengthens the segment.</param>
	/// <remarks>
	/// -If the lengthening factor is 0.0, the segment degenerates into a point (both endpoints become the center).
	/// -If the lengthening factor is 1.0, the segment won't experiment any modification, as this represent a 100% lengthening.
	/// </remarks>
	void Lengthen (const float_q& fLengtheningFactor)
	{
		// If Lengthening Factor == 1 we just don't touch the segment.
		if ( QFloat::AreNotEquals(fLengtheningFactor, QFloat::_1) )
		{
			VectorType vCenter;
			this->GetCenter(vCenter);

			// If Lengthening Factor == 0, just reduce the endpoints to the center.
			if (QFloat::AreEquals(fLengtheningFactor, QFloat::_0))
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
	/// -If lengthening factor is 0.0, the segment degenerates into a point (both endpoints become A).
	/// -If lengthening factor is 1.0, the segment won't experiment any modification, as this represent a 100% lengthening.
	/// </remarks>
	void LengthenFromA (const float_q& fLengtheningFactor)
	{
		// If Lengthening Factor == 1 we just don't touch the segment.
		if ( QFloat::AreNotEquals(fLengtheningFactor, QFloat::_1) )
		{
			// If Lengthening Factor == 0, just reduce the endpoints to A.
			if ( QFloat::AreEquals(fLengtheningFactor, QFloat::_0) )
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
	/// -If lengthening factor is 0.0, the segment degenerates into a point (both endpoints become B).
	/// -If lengthening factor is 1.0, the segment won't experiment any modification, as this represent a 100% lengthening.
	/// </remarks>
	void LengthenFromB (const float_q& fLengtheningFactor)
	{
		// If Lengthening Factor == 1 we just don't touch the segment.
		if ( QFloat::AreNotEquals(fLengtheningFactor, QFloat::_1) )
		{
			// If Lengthening Factor == 0, just reduce the endpoints to B.
			if ( QFloat::AreEquals(fLengtheningFactor, QFloat::_0) )
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
	/// Converts vector into a string with the following format:
	/// LS:A(VectorType::ToString)-B(VectorType::ToString)
	/// </summary>
	/// <returns>The string with the format specified.</returns>
	string_q ToString()
	{
		return QE_L("LS:A(") + A.ToString() + QE_L(")-B(") + B.ToString() + QE_L(")");
	}

protected:
	/// <summary>
	// [TODO] Thund, put this method as a generic non-member function and delete it from here when it's done.
	///
	/// This method clamps the input value to lie within the range [Min..Max]
	/// </summary>
	/// <param name="fFactor">[IN] A floating point value; the value to be clamped, if neccesary.</param>
	/// <param name="fMin">[IN] A floating point value; the minimum value into the range.</param>
	/// <param name="fMax">[IN] A floating point value; the maximum value into the range.</param>
	/// <returns>
	/// A floating point value that represents the input value, clamped (if was really necessary); otherwise,
	/// the same value.
	/// </returns>
	float_q ClampFactor (const float_q& fFactor, const float_q& fMin, const float_q& fMax) const
	{
        return QFloat::IsGreaterThan(fFactor, fMax) ? 
                                                    fMax : 
                                                    QFloat::IsLessThan(fFactor, fMin) ? 
                                                                                        fMin : 
                                                                                        fFactor;
	}

	/// <summary>
	/// This method computes the closest points between two line segments.
	/// </summary>
	/// <param name="segmt">[IN] The segment to whom the distace has to be computed from.</param>
	/// <param name="vClosestPtInS1ToS2">[OUT] It stores the closest point to S2 belonging to S1.</param>
	/// <param name="vClosestPtInS2ToS1">[OUT] It stores the closest point to S1 belonging to S2.</param>
	/// <remarks>
	/// We assume S1 is the segment which executes this member function, and S2 the segment passed as
	/// a parameter to S1.
	/// </remarks>
	void GetClosestPoints(const QBaseLineSegment<VectorType>& segmt,
						  VectorType& vClosestPtInS1ToS2, VectorType& vClosestPtInS2ToS1) const
	{
		bool bBothDegeneratedIntoPoints = false; // True if both segments degenerate into points.

		// STEP 0) -Segment S1 == (*this)		== B - A
		//		   -Segment S2 == the parameter == segmt.B - segmt.A
		//		   -fSFactor1,fSFactor2: [0,1]  == Sample factors, so the closest points between S1 and S2
		//										   will be given through:
		//
		//												S1(fSFactor1) = (A + (fSFactor1 * v1))
		//												S2(fSFactor2) = (segmt.A + (fSFactor2 * v2))
		float_q	   fSFactor1  = QFloat::_0;
		float_q	   fSFactor2  = QFloat::_0;
		VectorType v1		  = B - A;									 
	    VectorType v2		  = segmt.B - segmt.A;

		// STEP 1) Precomputing intermediate values for solving s and t.
	    float_q	   fSqrLengthv1		  = v1.DotProduct(v1);	// Squared length of segment S1, always nonnegative.
	    float_q	   fSqrLengthv2		  = v2.DotProduct(v2);	// Squared length of segment S2, always nonnegative.
		VectorType vTails			  = A - segmt.A;			// Segment whose endpoints are the "tail" points of each segment.
	    float_q	   fDotProdv2vTails   = v2.DotProduct(vTails);

	    // STEP 2) Check if either or both segments degenerate into points
	    if ( (QFloat::IsZero(fSqrLengthv1)) && (QFloat::IsZero(fSqrLengthv2)) )
		{
	        // BOTH segments degenerate into points --> The closest points are THEMSELVES.
			vClosestPtInS1ToS2		   = A;		  // The same with B.
			vClosestPtInS2ToS1		   = segmt.A; // The same with segmt.B
			bBothDegeneratedIntoPoints = true;
	    }

		if (!bBothDegeneratedIntoPoints)
		{
		    if (QFloat::IsZero(fSqrLengthv1))
			{
		        // S1 (*this) degenerates into a point;
				// fSFactor1 = 0 --> fSFactor2 = (((fDotProdv1v2 * fSFactor1) + fDotProdv2vTails) / fSqrLengthv2) = (fDotProdv2vTails / fSqrLengthv2)

				// Checkout to avoid division by 0
				QE_ASSERT(fSqrLengthv2 != QFloat::_0);
				fSFactor2 = this->ClampFactor( (fDotProdv2vTails / fSqrLengthv2), QFloat::_0, QFloat::_1 );
		    }
			else
			{	
		        float_q fDotProdv1vTails = v1.DotProduct(vTails);
	
		        if (QFloat::IsZero(fSqrLengthv2))
				{
		            // S2 (the parameter) degenerates into a point;
					// fSFactor2 = 0 --> fSFactor1 = (((fDotProdv1v2 * fSFactor2) - fDotProdv1vTails) / fSqrLengthv1) = (-fDotProdv1vTails / fSqrLengthv1)
	
					// Checkout to avoid division by 0
					QE_ASSERT(fSqrLengthv1 != QFloat::_0);
					fSFactor1 = this->ClampFactor( (-fDotProdv1vTails / fSqrLengthv1), QFloat::_0, QFloat::_1 );
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
		            if (QFloat::IsNotZero(fDenom))
					{
		                fSFactor1 = this->ClampFactor( ((fDotProdv1v2 * fDotProdv2vTails) - (fDotProdv1vTails * fSqrLengthv2)) / fDenom, QFloat::_0, QFloat::_1 );
		            }
					else
					{
						fSFactor1 = QFloat::_0;
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
					if (QFloat::IsNegative(fNom))
					{
						fSFactor2 = QFloat::_0;
	
						// Checkout to avoid division by 0
						QE_ASSERT(fSqrLengthv1 != QFloat::_0);
	
						fSFactor1 = this->ClampFactor( (-fDotProdv1vTails / fSqrLengthv1), QFloat::_0, QFloat::_1);
					}
					else if (fNom > fSqrLengthv2)
					{
						fSFactor2 = QFloat::_1;
	
						// Checkout to avoid division by 0
						QE_ASSERT(fSqrLengthv1 != QFloat::_0);
						fSFactor1 = this->ClampFactor( ((fDotProdv1v2 - fDotProdv1vTails) / fSqrLengthv1), QFloat::_0, QFloat::_1);
					}
					else // fNom in range [0..1]
					{
						// Checkout to avoid division by 0
						QE_ASSERT(fSqrLengthv2 != QFloat::_0);
	
						fSFactor2 = fNom / fSqrLengthv2;
					}			
		        }
		    }

			// STEP 4) Finally compute the closest points between S1 and S2 and storing them
			// in the output parameters.
			vClosestPtInS1ToS2 = A + (fSFactor1 * v1);
			vClosestPtInS2ToS1 = segmt.A + (fSFactor2 * v2);

		} // if (!bBothDegeneratedIntoPoints
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
const QLineSegment<VectorType> QLineSegment<VectorType>::UnitLine(VectorType::ZeroVector, VectorType::UnitVectorX);

template <class VectorType>
const QLineSegment<VectorType> QLineSegment<VectorType>::LineZero(VectorType::ZeroVector, VectorType::ZeroVector);

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QLINESEGMENT__
