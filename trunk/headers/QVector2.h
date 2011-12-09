// [TERMS&CONDITIONS]

#ifndef __QVECTOR2__
#define __QVECTOR2__

// [TODO] This two ranges may have to be deleted when a solution to
//		  solve values out of range for 'acos' function has been planned.
#ifndef __CURRENT_COS_MAX_RANGE__
	#define __CURRENT_COS_MAX_RANGE__	(1.0000001f)
#endif
#ifndef __CURRENT_COS_MIN_RANGE__
	#define __CURRENT_COS_MIN_RANGE__	(-1.0000001f)
#endif

#include "MathDefinitions.h"
#include "QBaseVector2.h"
#include "QBaseMatrix2x2.h"

using namespace Kinesis::QuimeraEngine::Tools::DataTypes;

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

// Forward declarations
class QTransformationMatrix3x3;

/// <summary>
/// This class implements two components vector functionality. It inherits from QBaseVector2.
///	A vector is a geometric object that has both a magnitude (or length) and direction.
///	It is frequently represented by a line segment with a definite direction, or graphically as an arrow,
///	connecting an initial point A with a terminal point B. The vector is then denoted by AB with a arrow hat.
/// </summary>
class QDllExport QVector2 : public QBaseVector2
{

public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	inline QVector2() { }

	/// <summary>
	/// Constructor from a 2D vector.
	/// </summary>
	/// <param name="v">[IN] The 2D vector in which we want resident vector to be based.</param>
	inline explicit QVector2(const QBaseVector2 &v) : QBaseVector2(v) { }

	/// <summary>
	/// Constructor from two floating point values for each component x and y.
	/// </summary>
	/// <param name="fValueX">[IN] Floating point value for x component.</param>
	/// <param name="fValueY">[IN] Floating point value for y component.</param>
	inline QVector2(const float_q &fValueX, const float_q &fValueY) : QBaseVector2(fValueX, fValueY) { }

	/// <summary>
	/// Constructor from a single floating point value for all components.
	/// </summary>
	/// <param name="fValue">[IN] Floating point value for all components.</param>
	inline explicit QVector2(const float_q &fValue) : QBaseVector2(fValue) { }

	/// <summary>
	/// Constructor from a two component array of floating point values.
	/// </summary>
	/// <param name="pValue">[IN] Pointer to array of floating point values. It must have at least two elements.</param>
	inline explicit QVector2(const float_q *pValue) : QBaseVector2(pValue) { }

	/// <summary>
    /// Constructor from a 4x32 packed floating point value.
    /// </summary>
    /// <param name="vfValue">[IN] 4x32 packed floating point value containing the two components.</param>
    inline explicit QVector2(const vf32_q vfValue) : QBaseVector2 (vfValue) { }


    // PROPERTIES
	// ---------------
public:

	/// <summary>
	/// Gets a vector with all components set to 0.
	/// </summary>
	/// <returns>
	/// A null vector.
	/// </returns>
	inline static const QVector2& GetZeroVector()
	{
	    static const QVector2 ZEROVECTOR(SQFloat::_0,  SQFloat::_0);
	    return ZEROVECTOR;
	}

	/// <summary>
	/// Gets a vector with all components set to 1.
	/// </summary>
	/// <returns>
	/// A vector of ones.
	/// </returns>
	inline static const QVector2& GetVectorOfOnes()
	{
	    static const QVector2 VECTOROFONES(SQFloat::_1,  SQFloat::_1);
	    return VECTOROFONES;
    }

	/// <summary>
	/// Gets a unit vector in X positive direction.
	/// </summary>
	/// <returns>
	/// A vector that points to X axis direction.
	/// </returns>
	inline static const QVector2& GetUnitVectorX()
	{
	    static const QVector2 UNITVECTORX(SQFloat::_1,  SQFloat::_0);
	    return UNITVECTORX;
	}

	/// <summary>
	/// Gets a unit vector in Y positive direction.
	/// </summary>
	/// <returns>
	/// A vector that points to Y axis direction.
	/// </returns>
	inline static const QVector2& GetUnitVectorY()
	{
	    static const QVector2 UNITVECTORY(SQFloat::_0,  SQFloat::_1);
	    return UNITVECTORY;
	}

	/// <summary>
	/// Gets a unit vector in X negative direction.
	/// </summary>
	/// <returns>
	/// A vector that points to X axis opposite direction.
	/// </returns>
	inline static const QVector2& GetUnitVectorInvX()
	{
	    static const QVector2 UNITVECTORINVX(-SQFloat::_1,  SQFloat::_0);
	    return UNITVECTORINVX;
	}

	/// <summary>
	/// Gets a unit vector in Y negative direction.
	/// </summary>
	/// <returns>
	/// A vector that points to Y axis opposite direction.
	/// </returns>
	inline static const QVector2& GetUnitVectorInvY()
	{
	    static const QVector2 UNITVECTORINVY(SQFloat::_0,  -SQFloat::_1);
	    return UNITVECTORINVY;
	}


	// METHODS
	// ---------------
public:

	// binary operators

	/// <summary>
	/// Vectors addition: it's performed component by component.
	/// </summary>
	/// <param name="v">[IN] Adding vector.</param>
	/// <returns>
	/// A vector that is the result of the addition.
	/// </returns>
	QVector2 operator + (const QBaseVector2 &v) const;

	/// <summary>
	/// Vectors subtraction: it's performed component by component.
	/// </summary>
	/// <param name="v">[IN] Subtracting vector.</param>
	/// <returns>
	/// A vector that is the result of the subtraction.
	/// </returns>
	QVector2 operator - (const QBaseVector2 &v) const;

	/// <summary>
	/// Product by a scalar: all components are multiplied by the floating point value provided.
	/// </summary>
	/// <param name="fValue">[IN] Multiplying floating point value.</param>
	/// <returns>
	/// A vector that is the result of the product.
	/// </returns>
	QVector2 operator * (const float_q &fValue) const;

	/// <summary>
	/// Product by a vector: it's performed component by component. It's not dot product or cross product!
	/// </summary>
	/// <param name="v">[IN] Multiplying vector.</param>
	/// <returns>
	/// A vector that is the result of the product.
	/// </returns>
	QVector2 operator * (const QBaseVector2 &v) const;

    /// <summary>
    /// Product by a matrix with 2 rows and 2 columns: it's performed following the matrices product rules.
    /// </summary>
    /// <param name="m">[IN] Multiplying matrix.</param>
    /// <returns>
    /// A vector that is the result of the product.
    /// </returns>
	QVector2 operator * (const QBaseMatrix2x2 &m) const;

	/// <summary>
	/// Division by a scalar: all components are divided by the floating point value provided.
	/// </summary>
	/// <param name="fValue">[IN] Dividing floating point value.</param>
	/// <returns>
	/// A vector that is the result of the division.
	/// </returns>
	QVector2 operator / (const float_q &fValue) const;

	/// <summary>
	/// Division by a vector: it's performed component by component.
	/// </summary>
	/// <param name="v">[IN] Dividing vector.</param>
	/// <returns>
	/// A vector that is the result of the division.
	/// </returns>
	QVector2 operator / (const QBaseVector2 &v) const;

	/// <summary>
	/// Product by a scalar: all components are multiplied by the floating point value provided.
	/// Shorcut to multiply on the left.
	/// </summary>
	/// <param name="fValue">[IN] Multiplying floating point value.</param>
	/// <param name="v">[IN] Vector to be multiplied.</param>
	/// <returns>
	/// A vector that is the result of the product.
	/// </returns>
	friend QVector2 operator * (const float_q &fValue, const QVector2 &v);

	// assignment operators

	/// <summary>
	/// Adds a vector provided to current vector.
	/// </summary>
	/// <param name="v">[IN] Adding vector.</param>
	/// <returns>
	/// A reference to vector result of the addition.
	/// </returns>
	inline QVector2& operator += (const QBaseVector2 &v)
	{
		this->x += v.x;
		this->y += v.y;

		return *this;
	}

	/// <summary>
	/// Subtracts a vector provided to current vector.
	/// </summary>
	/// <param name="v">[IN] Subtracting vector.</param>
	/// <returns>
	/// A reference to vector result of the subtraction.
	/// </returns>
	inline QVector2& operator -= (const QBaseVector2 &v)
	{
		this->x -= v.x;
		this->y -= v.y;

		return *this;
	}

	/// <summary>
	/// Multiplies current vector by a floating point value provided.
	/// </summary>
	/// <param name="fValue">[IN] Multiplying floating point value.</param>
	/// <returns>
	/// A reference to vector result of the product.
	/// </returns>
	inline QVector2& operator *= (const float_q &fValue)
	{
		this->x *= fValue;
		this->y *= fValue;

		return *this;
	}

	/// <summary>
    /// Multiplies resident vector by a matrix with 2 rows and 2 columns provided. It's performed with matrix product rules.
    /// </summary>
    /// <param name="m">[IN] Multiplying matrix.</param>
    /// <returns>
    /// A reference to vector result of the product.
    /// </returns>
    inline QVector2& operator *= (const QBaseMatrix2x2 &m)
	{

		float_q fValueX = this->x * m.ij[0][0] + this->y * m.ij[1][0];
		float_q fValueY = this->x * m.ij[0][1] + this->y * m.ij[1][1];

		this->x = fValueX;
		this->y = fValueY;

		return *this;
	}

	/// <summary>
	/// Multiplies current vector by a vector provided. It's performed component by component. It's not dot product or cross product!
	/// </summary>
	/// <param name="v">[IN] Multiplying vector.</param>
	/// <returns>
	/// A reference to vector result of the product.
	/// </returns>
	inline QVector2& operator *= (const QBaseVector2 &v)
	{
		this->x *= v.x;
		this->y *= v.y;

		return *this;
	}

	/// <summary>
	/// Divides current vector by a floating point value provided.
	/// </summary>
	/// <param name="fValue">[IN] Dividing floating point value.</param>
	/// <returns>
	/// A reference to vector result of the division.
	/// </returns>
	inline QVector2& operator /= (const float_q &fValue)
	{
		// Checkout to avoid division by 0
		QE_ASSERT(fValue != SQFloat::_0);

		this->x /= fValue;
		this->y /= fValue;

		return *this;
	}

	/// <summary>
	/// Divides current vector by a vector provided. It's performed component by component.
	/// </summary>
	/// <param name="v">[IN] Dividing vector.</param>
	/// <returns>
	/// A reference to vector result of the division.
	/// </returns>
	inline QVector2& operator /= (const QBaseVector2 &v)
	{
		// Checkout to avoid division by 0
		QE_ASSERT (v.x != SQFloat::_0 && v.y != SQFloat::_0);

		this->x /= v.x;
		this->y /= v.y;


		return *this;
	}

    // Unary operators

    /// <summary>
    /// Assign operator. Assigns the provided vector to the resident vector.
    /// </summary>
    /// <param name="v">[IN] The vector to be assigned.</param>
    /// <returns>
    /// A reference to the modified vector.
    /// </returns>
    inline QVector2& operator=(const QBaseVector2 &v)
    {
        QBaseVector2::operator=(v);
        return *this;
    }

   	/// <summary>
	/// Vector's negation: it's performed component by component.
	/// </summary>
	/// <returns>
	/// A vector that is the result of the negation.
	/// </returns>
	QVector2 operator - () const;

	/// <summary>
	/// Calculates the length of current vector.
	/// </summary>
	/// <returns>
	/// A floating point value which is the length of the vector.
	/// </returns>
	inline float_q GetLength() const
	{
		return hypot_q(this->x, this->y);
	}

	/// <summary>
    /// Calculates the squared length of resident vector.
    /// </summary>
    /// <returns>
    /// A floating point value which is the squared length of the vector.
    /// </returns>
    inline float_q GetSquaredLength() const
    {
        return this->x*this->x + this->y*this->y;
    }

	/// <summary>
	/// Calculates the vector which is perpendicular to the current vector.
	/// </summary>
	/// <returns>
	/// A Vector which is perpendicular of the vector.
	/// </returns>
	QVector2 GetPerpendicular() const;

	/// <summary>
	/// Makes current vector unitary
	/// </summary>
	inline void Normalize()
	{
		// Gets vector length
		float_q fLength = this->GetLength();

		// Checkout to avoid division by 0
		QE_ASSERT(fLength != SQFloat::_0);

		//Normalize
		this->x /= fLength;
		this->y /= fLength;
	}

	/// <summary>
    /// Calculates a normalized vector from the resident one and stores it in an output vector provided.
    /// </summary>
    /// <param name="vOut">[OUT] Vector where we want to store the normalized vector.</param>
    inline void Normalize(QBaseVector2 &vOut) const
    {
        vOut = *this;
        reinterpret_cast<QVector2&> (vOut).Normalize();
    }

	/// <summary>
	/// Convert current vector in its opposite vector.
	/// </summary>
	inline void Reverse()
	{
		this->x = -this->x;
		this->y = -this->y;
	}

    /// <summary>
    /// Calculates the opposite to resident vector and stores it in an output vector provided.
    /// </summary>
    /// <param name="vOut">[OUT] Vector where we want to store the opposite vector.</param>
    inline void Reverse(QBaseVector2 &vOut) const
    {
        vOut = *this;
        reinterpret_cast<QVector2&> (vOut).Reverse();
    }

	/// <summary>
	/// Resets all components of current vector to 1.
	/// </summary>
	inline void ResetToOne()
	{
		this->x = SQFloat::_1;
		this->y = SQFloat::_1;
	}

	/// <summary>
	/// Resets all components of current vector to 0.
	/// </summary>
	inline void ResetToZero()
	{
		this->x = SQFloat::_0;
		this->y = SQFloat::_0;
	}

	/// <summary>
	/// Applies a transformation to resident vector, multiplying the vector by a transformation matrix
	/// to transform it. The transformation can be a rotation, scaling or translation, or a combination of them.
	/// </summary>
	/// <param name="matrix">[IN] The transformation matrix.</param>
	void Transform(const QTransformationMatrix3x3& matrix);

	/// <summary>
	/// Applies a transformation to resident vector, multiplying the vector by a transformation matrix
	/// to transform it. The transformation can be a rotation, scaling or translation, or a combination of them.
	/// The transformed vector is stored into the provided one. No change to the resident vector.
	/// </summary>
	/// <param name="matrix">[IN] The transformation matrix.</param>
	/// <param name="vectorOut">[OUT] Vector where to store the result of transformation.</param>
	void Transform(const QTransformationMatrix3x3& matrix, QBaseVector2& vectorOut);

	/// <summary>
	/// Apply a 2D rotation about the origin of the resident vector.
	/// </summary>
	/// <param name="fAngle">[IN] The rotation angle.</param>
	void Transform(const float_q& fAngle);

	/// <summary>
	/// Apply a 2D rotation about the origin of the resident vector. The rotated vector is stored into the provided
	/// one. No change to the resident vector.
	/// </summary>
	/// <param name="fAngle">[IN] The rotation angle.</param>
	/// <param name="vectorOut">[OUT] Vector where to store the result of rotation.</param>
	void Transform(const float_q& fAngle, QBaseVector2& vectorOut);

	/// <summary>
	/// Check if all components of current vector are 0.
	/// </summary>
	/// <returns>
	/// True if all components are 0. False otherwise.
	/// </returns>
	inline bool IsZero()
	{
		return SQFloat::IsZero(this->x) && SQFloat::IsZero(this->y);
	}

	/// <summary>
	/// Check if all components of current vector are 1.
	/// </summary>
	/// <returns>
	/// True if all components are 1. False otherwise.
	/// </returns>
	inline bool IsVectorOfOnes()
	{
		return SQFloat::AreEquals(this->x, SQFloat::_1) && SQFloat::AreEquals(this->y, SQFloat::_1);
	}

	/// <summary>
	/// Calculates Dot Product by a vector provided.
	/// </summary>
	/// <param name="v">[IN] Multiplying vector.</param>
	/// <returns>
	/// A floating point value which is the result of Dot Product.
	/// </returns>
	inline float_q DotProduct(const QVector2 &v) const
	{
		return(this->x*v.x + this->y*v.y);
	}

    /// <summary>
    /// Calculates the angle between resident vector and the provided vector via Dot Product.
    /// </summary>
    /// <param name="v">[IN] Multiplying vector.</param>
    /// <returns>
    /// A floating point value which is the smaller angle between vectors (less or equal 180º).
    /// </returns>
    inline float_q DotProductAngle(const QVector2& v) const
    {
        float_q fLengthProd = this->GetLength() * v.GetLength();

        // Checkout to avoid division by zero.
        QE_ASSERT(fLengthProd != SQFloat::_0);

        float_q fDot = this->DotProduct(v) / fLengthProd;

		// Checkout to avoid undefined values of acos. Remember that -1 <= cos(angle) <= 1.
		//
		// [TODO] This code block has to be reviewed when a solution to
		//		  solve values out of range for 'acos' function has been planned, and then:
		//
		//				 1) Replace the current QE_ASSERT with one using SQFloat::IsLowerOrEquals,
		//					because something like QE_ASSERT( SQFloat::IsLowerOrEquals(abs(fDot), SQFloat::_1) )
		//					or QE_ASSERT( SQFloat::IsLowerOrEquals(abs(fDot), CURRENT_COS_MAX_RANGE) )
		//				    actually doesn't make their work.
		//
		//				 2) Replace the two conditional branches and then use Clamp funcion, once this is defined
		//					as a non-member function.
		///////////////////////////////////////////////////////////////////
        QE_ASSERT(SQFloat::Abs(fDot) <= SQFloat::_1);

		if ( SQFloat::IsGreaterOrEquals(fDot, __CURRENT_COS_MAX_RANGE__) )
		{
			fDot = 1.0000000f;
		}
		else if ( SQFloat::IsLowerOrEquals(fDot, __CURRENT_COS_MIN_RANGE__) )
		{
			fDot = -1.0000000f;
		}
		///////////////////////////////////////////////////////////////////

        float_q fAngle = acos_q(fDot);

		// At this stage we have the angle stored in fAngle expressed in RADIANS.

        #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
            // If angles are specified in degrees, then converts angle to degrees
            fAngle = SQAngle::RadiansToDegrees(fAngle, fAngle);

			// At this stage we have the angle expressed in DEGREES.
        #endif

        return fAngle;
    }

	/// <summary>
	/// Makes a Linear Interpolation between current vector and other vector provided. It stores result in current vector.
	/// </summary>
	/// <param name="fFactor">[IN] A floating point value which represents how close is the result vector from the current vector (per one).</param>
	/// <param name="v">[IN] Vector with which to interpolate.</param>
	inline void Lerp(const float_q &fFactor, const QBaseVector2 &v)
	{
		this->x = this->x*fFactor + v.x*(SQFloat::_1 - fFactor);
		this->y = this->y*fFactor + v.y*(SQFloat::_1 - fFactor);
	}

    /// <summary>
    /// Makes a Linear Interpolation between resident vector and other vector provided. It stores result in a vector provided.
    /// </summary>
    /// <param name="fFactor">[IN] A floating point value which represents how close is the result vector from the resident vector (per one).</param>
    /// <param name="v">[IN] Vector with which to interpolate.</param>
    /// <param name="vOut">[OUT] Vector to store results of interpolation.</param>
    inline void Lerp(const float_q &fFactor, const QBaseVector2 &v, QBaseVector2 &vOut) const
    {
        vOut = *this;
        reinterpret_cast<QVector2&> (vOut).Lerp(fFactor, v);
    }

	/// <summary>
	/// Calculates the distance between two vector heads (or two points). It computes the difference of two vectors and returns its length.
	/// </summary>
	/// <param name="v">[IN] Vector we want to calculate the distance from current vector.</param>
	/// <returns>
	/// A positive floating point value containing the distance between both vectors.
	/// </returns>
	inline float_q Distance(const QVector2 &v) const
	{
		return hypot_q(this->x-v.x, this->y-v.y);
	}

	/// <summary>
	/// Converts vector into a string with the following format: "V2(x, y)".
	/// </summary>
	/// <returns>
	/// The string with the format specified.
	/// </returns>
	string_q ToString() const;

};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QVECTOR2__
