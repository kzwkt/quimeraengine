// [TERMS&CONDITIONS]

#ifndef __QLINESEGMENT__
#define __QLINESEGMENT__


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
    /// Unit segment lying on X axis (it's length equals 1).
    /// </summary>
	static const QLineSegment<VectorType> UnitLine;

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	inline QLineSegment() { }

	/// <summary>
    /// Constructor from two vectors.
    /// </summary>
    /// <param name="vA">[IN] Vector to define endpoint A.</param>
    /// <param name="vB">[IN] Vector to define endpoint B.</param>
	inline QLineSegment (const VectorType &vA, const VectorType &vB) : QBaseLineSegment(vA,vB) { }

	/// <summary>
    /// Constructor from a line segment.
    /// </summary>
    /// <param name="vBaseLineSegment">[IN] Line segment containing the two endpoints.</param>
	inline explicit QLineSegment (const QBaseLineSegment<VectorType>& vBaseLineSegment) : A(vBaseLineSegment.A), B(vBaseLineSegment.B)  { }


	// METHODS
	// ---------------
public:
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
	/// This method receives another line segment, and computes wheter they intersect each other or not.
	/// </summary>
	/// <param name="vBaseLineSegment">[IN] The segment to be compared to.</param>
	/// <returns>
	/// True if they intersect each other (or if they were coincident), false if they don't.
	/// </returns>
	inline bool Intersection (const QBaseLineSegment& vBaseLineSegment) const
	{
		// if MinDistance is 0		  --> there's intersection, return true
		// else						  --> return false
		return  QFloat::AreEquals(this->MinDistance(vBaseLineSegment), QFloat::_0);
	}


	/// <summary>
	/// Given an input line segment, this method returns the minimum distance between this and the input one,
	///	that is, the distance between their closest points.
	/// </summary>
	/// <param name="vBaseLineSegment">[IN] The line segment the distance will be measured to.</param>
	/// <returns>
	/// A floating point value (always nonnegative) which represents the minimum distance between the two segments.
	/// </returns>
	float_q MinDistance (const QBaseLineSegment& vBaseLineSegment) const
	{
		// STEP 0) -Segment S1 == (*this)		== B - A
		//		   -Segment S2 == the parameter == vBaseLineSegment.B - vBaseLineSegment.A
		//		   -fSFactor1,fSFactor2: [0,1]  == Sample factors, so the closest points between S1 and S2
		//										   will be given through:
		//
		//												S1(fSFactor1) = (A + (fSFactor1 * v1))
		//												S2(fSFactor2) = (vBaseLineSegment.A + (fSFactor2 * v2))
		float_q	   fSFactor1  = QFloat::_0;
		float_q	   fSFactor2  = QFloat::_0;
		VectorType v1		  = B - A;									 
	    VectorType v2		  = vBaseLineSegment.B - vBaseLineSegment.A;

		// STEP 1) Precomputing intermediate values for solving s and t.
	    float_q	   fSqrLengthv1		  = v1.DotProduct(v1);	// Squared length of segment S1, always nonnegative.
	    float_q	   fSqrLengthv2		  = v2.DotProduct(v2);	// Squared length of segment S2, always nonnegative.
		VectorType vTails			  = A - vBaseLineSegment.A;// Segment whose endpoints are the "tail" points of each segment.
	    float_q	   fDotProdv2vTails   = v2.DotProduct(vTails);

	    // STEP 2) Check if either or both segments degenerate into points
	    if ( (QFloat::IsZero(fSqrLengthv1)) && (QFloat::IsZero(fSqrLengthv2)) )
		{
	        // Both segments degenerate into points
	        return vTails.GetLength();
	    }

	    if (QFloat::IsZero(fSqrLengthv1))
		{
	        // S1 (*this) degenerates into a point;
			// fSFactor1 = 0 --> fSFactor2 = (((fDotProdv1v2 * fSFactor1) + fDotProdv2vTails) / fSqrLengthv2) = (fDotProdv2vTails / fSqrLengthv2)

			// Checkout to avoid division by 0
			QE_ASSERT(fSqrLengthv2);
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
				QE_ASSERT(fSqrLengthv1);
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
	            float_q fNom = QFloat::_0;
				fNom		 = (fSFactor1 * fDotProdv1v2) + fDotProdv2vTails;			
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
					QE_ASSERT(fSqrLengthv1);

					fSFactor1 = this->ClampFactor( (-fDotProdv1vTails / fSqrLengthv1), QFloat::_0, QFloat::_1);
				}
				else if (fNom > fSqrLengthv2)
				{
					fSFactor2 = QFloat::_1;

					// Checkout to avoid division by 0
					QE_ASSERT(fSqrLengthv1);
					fSFactor1 = this->ClampFactor( ((fDotProdv1v2 - fDotProdv1vTails) / fSqrLengthv1), QFloat::_0, QFloat::_1);
				}
				else // fNom in range [0..1]
				{
					// Checkout to avoid division by 0
					QE_ASSERT(fSqrLengthv2);

					fSFactor2 = fNom / fSqrLengthv2;
				}			
	        }
	    }

		// STEP 4) return the distance between the closest points between S1 and S2, that is,
		//		   S1(fSFactor1) and S2(fSFactor2)
		QLineSegment vDistance( (A + (fSFactor1 * v1)), (vBaseLineSegment.A + (fSFactor2 * v2)) );
		return vDistance.GetLength();
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
			float_q fDotProductv1v2 = QFloat::_0;
			fDotProductv1v2			= v1.DotProduct(v2);

			if ( (QFloat::IsNegative(fDotProductv1v2)) || (QFloat::IsZero(fDotProductv1v2)) )
			{
				return v2.GetLength();
			}
			else
			{
				fDotProductv1v1 = v1.DotProduct(v1);
				// [TODO] Replace the expression with QFloat::IsGreaterOrEqualThan(fDotProductv1v2, fDotProductv1v1) when it's implemented.
				if ( (fDotProductv1v2 - fDotProductv1v1) >= -QFloat::Epsilon )
				{
					return ( (vPoint - B).GetLength() );
				}
				else
				{
					// Checkout to avoid division by 0
					QE_ASSERT (fDotProductv1v1);
					
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
	/// <param name="vBaseLineSegment">[IN] The line segment the distance will be measured to.</param>
	/// <returns>
	/// A floating point value (always nonnegative) which represents the maximum distance between the two segments.
	/// </returns>
	inline float_q MaxDistance (const QBaseLineSegment& vBaseLineSegment) const
	{
		float_q fMaxDistance_vBLSA_This = QFloat::_0; 
		float_q fMaxDistance_vBLSB_This = QFloat::_0; 

		// STEP 1) Compute Maximum distance from endpoint A (belonging to the parameter) to this segment.
		// STEP 2) Compute Maximum distance from endpoint B (belonging to the parameter) to this segment.
		fMaxDistance_vBLSA_This = this->MaxDistance(vBaseLineSegment.A);
		fMaxDistance_vBLSB_This = this->MaxDistance(vBaseLineSegment.B);

		// STEP 3) Maximum distance between the segments = maximum distance between their farthest endpoints.
		//												 = the longer distance between the maximum distances from endpoints
		//												   of the segment passed by parameter to this segment.
		// [TODO] Replace the expression with QFloat::IsGreaterThan(fMaxDistance_vBLSA_This, fMaxDistance_vBLSB_This) when it's implemented.
		return ( (fMaxDistance_vBLSA_This - fMaxDistance_vBLSB_This) > QFloat::Epsilon )? fMaxDistance_vBLSA_This : fMaxDistance_vBLSB_This;
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
			float_q fDotProductv1v2 = QFloat::_0;
			float_q fDotProductv1v1 = QFloat::_0;
			fDotProductv1v2			= v1.DotProduct(v2);

			if ( (QFloat::IsNegative(fDotProductv1v2)) || (QFloat::IsZero(fDotProductv1v2)) )
			{
				return ( v3.GetLength() );
			}
			else
			{
				fDotProductv1v1 = v1.DotProduct(v1);
				// [TODO] Replace the expression with QFloat::IsGreaterOrEqualThan(fDotProductv1v2, fDotProductv1v1) when it's implemented.
				if ( (fDotProductv1v2 - fDotProductv1v1) >= -QFloat::Epsilon )
				{			
					return v2.GetLength();
				}
				else
				{	
					float_q fDistancePointToA = QFloat::_0;
					float_q fDistancePointToB = QFloat::_0;
	
					fDistancePointToA		  = v2.GetLength();
					fDistancePointToB		  = v3.GetLength();

					// [TODO] Replace the expression with QFloat::IsGreaterThan(fDistancePointToA, fDistancePointToB) when it's implemented.
					return ( (fDistancePointToA - fDistancePointToB) > QFloat::Epsilon )? fDistancePointToA : fDistancePointToB;
				}
			}
		}
		else
		{
			return QFloat::_0;
		}

	}

	/// <summary>
	/// Given a scale factor, this method computes the scaling of the segment; endpoints move away or approach to
	/// to the center, depending of the scale factor value.
	///
	/// Remarks:
	///   -If the scale factor is 0.0, the segment degenerates into a point (both endpoints become the center).
	///   -If the scale factor is 1.0, the segment won't experiment any scale, as this represent a 100% scaling.
	/// </summary>
	/// <param name="fScaleFactor">[IN] A floating point value that scales the segment.</param>
	void Scale (const float_q& fScaleFactor)
	{
		// if Factor Scale == 1 we just don't touch the segment.
		if ( QFloat::AreNotEquals(fScaleFactor, QFloat::_1) )
		{
			VectorType vCenter;
			this->GetCenter(vCenter);

			// if Factor Scale == 0, just reduce the endpoints to the center.
			if (QFloat::AreEquals(fScaleFactor, QFloat::_0))
			{
				A = vCenter;
				B = vCenter;
			}
			else // Compute the new segment endpoints from the center.
			{
				A = vCenter + (fScaleFactor * (A - vCenter) );
				B = vCenter + (fScaleFactor * (B - vCenter) );
			}
		}
	}

	/// <summary>
	/// Given a scale factor, this method computes the scaling of the segment; endpoint B move away or approach to A,
	/// depending of the scale factor value. In any case, A stays the same.
	///
	/// Remarks:
	///   -If the scale factor is 0.0, the segment degenerates into a point (both endpoints become A).
	///   -If the scale factor is 1.0, the segment won't experiment any scale, as this represent a 100% scaling.
	/// </summary>
	/// <param name="fScaleFactor">[IN] A floating point value that scales the segment.</param>
	void QLineSegment<VectorType>::ScaleFromA (const float_q& fScaleFactor)
	{
		// if Factor Scale == 1 we just don't touch the segment.
		if ( QFloat::AreNotEquals(fScaleFactor, QFloat::_1) )
		{
			// if Factor Scale == 0, just reduce the endpoints to A.
			if ( QFloat::AreEquals(fScaleFactor, QFloat::_0) )
			{
				B = A;
			}
			else // Scale from A --> Compute the new B.
			{
				B = A + (fScaleFactor * (B - A));
			}
		}
	}

	/// <summary>
	/// Given a scale factor, this method computes the scaling of the segment; endpoint A move away or approach to B,
	/// depending of the scale factor value. In any case, B stays the same.
	///
	/// Remarks:
	///   -If the scale factor is 0.0, the segment degenerates into a point (both endpoints become B).
	///   -If the scale factor is 1.0, the segment won't experiment any scale, as this represent a 100% scaling.
	/// </summary>
	/// <param name="fScaleFactor">[IN] A floating point value that scales the segment.</param>
	void ScaleFromB (const float_q& fScaleFactor)
	{
		// if Factor Scale == 1 we just don't touch the segment.
		if ( QFloat::AreNotEquals(fScaleFactor, QFloat::_1) )
		{
			// if Factor Scale == 0, just reduce the endpoints to B.
			if ( QFloat::AreEquals(fScaleFactor, QFloat::_0) )
			{			
				A = B;
			}
			else // Scale from B --> Compute the new A.
			{
				A = B + (fScaleFactor * (A - B));
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
		// [TODO] Replace the '>' ('<') expressions with QFloat::IsGreaterThan (QFloat::(IsLesserThan)) when they're implemented.
		return ((fFactor - fMax) > QFloat::Epsilon)? fMax : (((fFactor - fMin) < -QFloat::Epsilon)? fMin : fFactor);
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
/// <summary>
/// Unit segment lying on X axis (it's length equals 1).
/// </summary>
template <class VectorType>
const QLineSegment<VectorType> QLineSegment<VectorType>::UnitLine(VectorType::ZeroVector, VectorType::UnitVectorX);

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QLINESEGMENT__
