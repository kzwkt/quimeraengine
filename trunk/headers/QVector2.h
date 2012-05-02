// [TERMS&CONDITIONS]

#ifndef __QVECTOR2__
#define __QVECTOR2__

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
/// This class implements two components vector functionality.<br>
///	A vector is a geometric object that has both a magnitude (or length) and direction.<br>
///	It is frequently represented by a line segment with a definite direction, or graphically as an arrow,
///	connecting an initial point A with a terminal point B.<br>
/// The vector is then denoted by AB with a arrow hat: \f$ \overrightarrow{AB}\f$.
/// </summary>
class QDllExport QVector2 : public QBaseVector2
{

public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	inline QVector2()
    {
    }

	/// <summary>
	/// Copy constructor.
	/// </summary>
	/// <param name="vVector">[IN] The 2D vector in which we want resident vector to be based.</param>
	inline QVector2(const QBaseVector2 &vVector) : QBaseVector2(vVector)
    {
    }

	/// <summary>
	/// Constructor from two floating point values for each component x and y.
	/// </summary>
	/// <param name="fValueX">[IN] Floating point value for x component.</param>
	/// <param name="fValueY">[IN] Floating point value for y component.</param>
	inline QVector2(const float_q &fValueX, const float_q &fValueY) : QBaseVector2(fValueX, fValueY)
    {
    }

	/// <summary>
	/// Constructor from a single floating point value for all components.
	/// </summary>
	/// <param name="fValueAll">[IN] Floating point value for all components.</param>
	inline explicit QVector2(const float_q &fValueAll) : QBaseVector2(fValueAll)
    {
    }

	/// <summary>
	/// Constructor from a two component array of floating point values.
	/// </summary>
	/// <param name="arValues">[IN] Pointer to array of floating point values. It must have at least two elements.</param>
	inline explicit QVector2(const float_q* arValues) : QBaseVector2(arValues)
    {
    }

	/// <summary>
    /// Constructor from a 4x32 packed floating point value.
    /// </summary>
    /// <param name="value">[IN] 4x32 packed floating point value containing the two components.</param>
    inline explicit QVector2(const vf32_q value) : QBaseVector2 (value)
    {
    }


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

	/// <summary>
	/// Vectors addition: it's performed component by component.
	/// </summary>
	/// <param name="vVector">[IN] Adding vector.</param>
	/// <returns>
	/// A vector that is the result of the addition.
	/// </returns>
	QVector2 operator+(const QBaseVector2 &vVector) const;

	/// <summary>
	/// Vectors subtraction: it's performed component by component.
	/// </summary>
	/// <param name="vVector">[IN] Subtracting vector.</param>
	/// <returns>
	/// A vector that is the result of the subtraction.
	/// </returns>
	QVector2 operator-(const QBaseVector2 &vVector) const;

	/// <summary>
	/// Product by a scalar: all components are multiplied by the floating point value provided.
	/// </summary>
	/// <param name="fScalar">[IN] Multiplying floating point value.</param>
	/// <returns>
	/// A vector that is the result of the product.
	/// </returns>
	QVector2 operator*(const float_q &fScalar) const;

	/// <summary>
	/// Product by a vector: it's performed component by component.<br>
	/// It's not dot product or cross product!
	/// </summary>
	/// <param name="vVector">[IN] Multiplying vector.</param>
	/// <returns>
	/// A vector that is the result of the product.
	/// </returns>
	QVector2 operator*(const QBaseVector2 &vVector) const;

    /// <summary>
    /// Product by a matrix with 2 rows and 2 columns: it's performed following the matrices product rules.
    /// </summary>
    /// <param name="matrix">[IN] Multiplying matrix.</param>
    /// <returns>
    /// A vector that is the result of the product.
    /// </returns>
	QVector2 operator*(const QBaseMatrix2x2 &matrix) const;

	/// <summary>
	/// Division by a scalar: all components are divided by the floating point value provided.
	/// </summary>
	/// <param name="fScalar">[IN] Dividing floating point value.</param>
	/// <returns>
	/// A vector that is the result of the division.
	/// </returns>
	QVector2 operator/(const float_q &fScalar) const;

	/// <summary>
	/// Division by a vector: it's performed component by component.
	/// </summary>
	/// <param name="vVector">[IN] Dividing vector.</param>
	/// <returns>
	/// A vector that is the result of the division.
	/// </returns>
	QVector2 operator/(const QBaseVector2 &vVector) const;

	/// <summary>
	/// Product by a scalar: all components are multiplied by the floating point value provided.<br>
	/// Shorcut to multiply on the left.
	/// </summary>
	/// <param name="fScalar">[IN] Multiplying floating point value.</param>
	/// <param name="vVector">[IN] Vector to be multiplied.</param>
	/// <returns>
	/// A vector that is the result of the product.
	/// </returns>
	friend QVector2 operator*(const float_q &fScalar, const QVector2 &vVector);

	/// <summary>
	/// Adds a vector provided to current vector.
	/// </summary>
	/// <param name="vVector">[IN] Adding vector.</param>
	/// <returns>
	/// A reference to vector result of the addition.
	/// </returns>
	inline QVector2& operator+=(const QBaseVector2 &vVector)
	{
		this->x += vVector.x;
		this->y += vVector.y;

		return *this;
	}

	/// <summary>
	/// Subtracts a vector provided to current vector.
	/// </summary>
	/// <param name="vVector">[IN] Subtracting vector.</param>
	/// <returns>
	/// A reference to vector result of the subtraction.
	/// </returns>
	inline QVector2& operator-=(const QBaseVector2 &vVector)
	{
		this->x -= vVector.x;
		this->y -= vVector.y;

		return *this;
	}

	/// <summary>
	/// Multiplies current vector by a floating point value provided.
	/// </summary>
	/// <param name="fScalar">[IN] Multiplying floating point value.</param>
	/// <returns>
	/// A reference to vector result of the product.
	/// </returns>
	inline QVector2& operator*=(const float_q fScalar)
	{
		this->x *= fScalar;
		this->y *= fScalar;

		return *this;
	}

	/// <summary>
    /// Multiplies resident vector by a matrix with 2 rows and 2 columns provided.<br>
    /// It's performed with matrix product rules.
    /// </summary>
    /// <param name="matrix">[IN] Multiplying matrix.</param>
    /// <returns>
    /// A reference to vector result of the product.
    /// </returns>
    inline QVector2& operator*=(const QBaseMatrix2x2 &matrix)
	{

		float_q fValueX = this->x * matrix.ij[0][0] + this->y * matrix.ij[1][0];
		float_q fValueY = this->x * matrix.ij[0][1] + this->y * matrix.ij[1][1];

		this->x = fValueX;
		this->y = fValueY;

		return *this;
	}

	/// <summary>
	/// Multiplies current vector by a vector provided.<br>
	/// It's performed component by component.<br>
	/// It's not dot product or cross product!
	/// </summary>
	/// <param name="vVector">[IN] Multiplying vector.</param>
	/// <returns>
	/// A reference to vector result of the product.
	/// </returns>
	inline QVector2& operator*=(const QBaseVector2 &vVector)
	{
		this->x *= vVector.x;
		this->y *= vVector.y;

		return *this;
	}

	/// <summary>
	/// Divides current vector by a floating point value provided.
	/// </summary>
	/// <param name="fScalar">[IN] Dividing floating point value.</param>
	/// <returns>
	/// A reference to vector result of the division.
	/// </returns>
	inline QVector2& operator/=(const float_q &fScalar)
	{
		// Checkout to avoid division by 0
		QE_ASSERT(fScalar != SQFloat::_0)

		const float_q &fDivisor = SQFloat::_1/fScalar;

		this->x *= fDivisor;
		this->y *= fDivisor;

		return *this;
	}

	/// <summary>
	/// Divides current vector by a vector provided.<br>
	/// It's performed component by component.
	/// </summary>
	/// <param name="vVector">[IN] Dividing vector.</param>
	/// <returns>
	/// A reference to vector result of the division.
	/// </returns>
	inline QVector2& operator/=(const QBaseVector2 &vVector)
	{
		// Checkout to avoid division by 0
		QE_ASSERT (vVector.x != SQFloat::_0 && vVector.y != SQFloat::_0)

		this->x /= vVector.x;
		this->y /= vVector.y;


		return *this;
	}

    /// <summary>
    /// Assign operator.<br>
    /// Assigns the provided vector to the resident vector.
    /// </summary>
    /// <param name="vVector">[IN] The vector to be assigned.</param>
    /// <returns>
    /// A reference to the modified vector.
    /// </returns>
    inline QVector2& operator=(const QBaseVector2 &vVector)
    {
        QBaseVector2::operator=(vVector);
        return *this;
    }

   	/// <summary>
	/// Vector's negation: it's performed component by component.
	/// </summary>
	/// <returns>
	/// A vector that is the result of the negation.
	/// </returns>
	QVector2 operator-() const;

	/// <summary>
	/// Calculates the length of current vector.
	/// </summary>
	/// <returns>
	/// A floating point value which is the length of the vector.
	/// </returns>
	float_q GetLength() const;

	/// <summary>
    /// Calculates the squared length of resident vector.
    /// </summary>
    /// <returns>
    /// A floating point value which is the squared length of the vector.
    /// </returns>
    float_q GetSquaredLength() const;

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
    /// <returns>
	/// The normalized vector.
	/// </returns>
	inline QVector2 Normalize() const
	{
		// Gets vector length
		const float_q fLength = this->GetLength();

		// Checkout to avoid division by 0
		QE_ASSERT(fLength != SQFloat::_0)

		//Normalize
        return QVector2(this->x / fLength, this->y / fLength);
	}

	/// <summary>
	/// Convert current vector in its opposite vector.
	/// </summary>
    /// <returns>
	/// The inverted vector.
	/// </returns>
	inline QVector2 Invert() const
	{
        return QVector2(-this->x, -this->y);
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
	/// to transform it.<br>
	/// The transformation can be a rotation, scaling or translation, or a combination of them.
	/// </summary>
	/// <param name="matrix">[IN] The transformation matrix.</param>
    /// <returns>
	/// The transformed vector.
	/// </returns>
	QVector2 Transform(const QTransformationMatrix3x3 &matrix) const;

	/// <summary>
	/// Apply a 2D rotation about the origin of the resident vector.
	/// </summary>
	/// <param name="fRotationAngle">[IN] The rotation angle.</param>
    /// <returns>
	/// The transformed vector.
	/// </returns>
	QVector2 Transform(const float_q &fRotationAngle) const;

	/// <summary>
	/// Check if all components of current vector are 0.
	/// </summary>
	/// <returns>
	/// True if all components are 0. False otherwise.
	/// </returns>
	bool IsZero() const;

	/// <summary>
	/// Check if all components of current vector are 1.
	/// </summary>
	/// <returns>
	/// True if all components are 1. False otherwise.
	/// </returns>
	bool IsVectorOfOnes() const;

	/// <summary>
	/// Calculates Dot Product by a vector provided.
	/// </summary>
	/// <param name="vVector">[IN] Multiplying vector.</param>
	/// <returns>
	/// A floating point value which is the result of Dot Product.
	/// </returns>
	float_q DotProduct(const QVector2 &vVector) const;

    /// <summary>
    /// Calculates the angle between resident vector and the provided vector via Dot Product.
    /// </summary>
    /// <param name="vVector">[IN] Multiplying vector.</param>
    /// <returns>
    /// A floating point value which is the smaller angle between vectors (less or equal \f$ 180^0\f$).
    /// </returns>
    float_q DotProductAngle(const QVector2 &vVector) const;

	/// <summary>
	/// Makes a Linear Interpolation between current vector and other vector provided.<br>
	/// It stores result in current vector.
	/// </summary>
	/// <param name="fProportion">[IN] A floating point value which represents how close is the result vector from the current vector (per one).</param>
	/// <param name="vVector">[IN] Vector with which to interpolate.</param>
    /// <returns>
    /// The "lerped" vector.
    /// </returns>
	inline QVector2 Lerp(const float_q &fProportion, const QBaseVector2 &vVector) const
	{
        return QVector2(this->x * fProportion + vVector.x * (SQFloat::_1 - fProportion), 
                        this->y * fProportion + vVector.y * (SQFloat::_1 - fProportion));
	}

	/// <summary>
	/// Calculates the distance between two vector heads (or two points).<br>
	/// It computes the difference of two vectors and returns its length.
	/// </summary>
	/// <param name="vVector">[IN] Vector we want to calculate the distance from current vector.</param>
	/// <returns>
	/// A positive floating point value containing the distance between both vectors.
	/// </returns>
	inline float_q Distance(const QVector2 &vVector) const
	{
		return hypot_q(this->x-vVector.x, this->y-vVector.y);
	}

	/// <summary>
	/// Converts vector into a string with the following format:<br>
	/// "V2($x,$y)".<br>
    /// Where "$" means "string representation of attribute".
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
