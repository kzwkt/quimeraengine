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

#ifndef __QVECTOR2__
#define __QVECTOR2__

#include "MathDefinitions.h"
#include "QBaseVector2.h"
#include "QBaseMatrix2x2.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::DataTypes::float_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::vf32_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::string_q;


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
/// A vector with two components: X and Y.
/// </summary>
/// <remarks>
///	A vector is a geometric object that has both a magnitude (or length) and a direction.
/// </remarks>
class QDllExport QVector2 : public QBaseVector2
{
    // FRIENDS
    // ---------------
public:

	/// <summary>
	/// Product of a scalar by a vector. All the components are multiplied by the scalar provided.
	/// </summary>
	/// <param name="fScalar">[IN] Scalar to multiply.</param>
	/// <param name="vVector">[IN] Vector to be multiplied by.</param>
	/// <returns>
	/// A vector that is the result of the product.
	/// </returns>
	friend QVector2 operator*(const float_q &fScalar, const QVector2 &vVector);


    // CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
    /// <remarks>
    ///	By default, all the components are set to zero.
    /// </remarks>
	inline QVector2()
    {
    }

	/// <summary>
	/// Copy constructor.
	/// </summary>
	/// <param name="vVector">[IN] The vector whose components are to be copied.</param>
	inline QVector2(const QVector2 &vVector) : QBaseVector2(vVector)
	{
	}

	/// <summary>
	/// Constructor that receives an instance of the base type.
	/// </summary>
	/// <param name="vVector">[IN] The vector whose components are to be copied.</param>
	inline QVector2(const QBaseVector2 &vVector) : QBaseVector2(vVector)
    {
    }

	/// <summary>
	/// Constructor that receives the value of every vector's component.
	/// </summary>
	/// <param name="fValueX">[IN] The value for X component.</param>
	/// <param name="fValueY">[IN] The value for Y component.</param>
	inline QVector2(const float_q &fValueX, const float_q &fValueY) : QBaseVector2(fValueX, fValueY)
    {
    }

	/// <summary>
	/// Constructor from a single value for all the vector's components.
	/// </summary>
	/// <param name="fValueAll">[IN] The value for all components.</param>
	inline explicit QVector2(const float_q &fValueAll) : QBaseVector2(fValueAll)
    {
    }

	/// <summary>
	/// Constructor that receives an array of scalars.
	/// </summary>
    /// <remarks>
    /// The array must contain, at least, two elements. Only the first two elements will be considered; the rest will be ignored.
    /// </remarks>
	/// <param name="arValues">[IN] An array of scalars. It must contain, at least, two elements.</param>
	inline explicit QVector2(const float_q* arValues) : QBaseVector2(arValues)
    {
    }

	/// <summary>
    /// Constructor that receives a pack of four scalars.
    /// </summary>
    /// <remarks>
    /// Only the two first elements in the pack (most significant bits) are considered.
    /// </remarks>
    /// <param name="value">[IN] 4x32 packed floating point value containing the two components.</param>
    inline explicit QVector2(const vf32_q value) : QBaseVector2 (value)
    {
    }


    // PROPERTIES
	// ---------------
public:

	/// <summary>
	/// Gets a vector whose components equal zero.
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
	/// Gets a vector whose components equal one.
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
	/// Gets a unit vector that points to the positive direction of the X axis.
	/// </summary>
	/// <returns>
	/// A unit vector that points to the positive direction of the X axis.
	/// </returns>
	inline static const QVector2& GetUnitVectorX()
	{
	    static const QVector2 UNITVECTORX(SQFloat::_1,  SQFloat::_0);
	    return UNITVECTORX;
	}

	/// <summary>
	/// Gets a unit vector that points to the positive direction of the Y axis.
	/// </summary>
	/// <returns>
	/// A unit vector that points to the positive direction of the Y axis.
	/// </returns>
	inline static const QVector2& GetUnitVectorY()
	{
	    static const QVector2 UNITVECTORY(SQFloat::_0,  SQFloat::_1);
	    return UNITVECTORY;
	}

	/// <summary>
	/// Gets a unit vector that points to the negative direction of the X axis.
	/// </summary>
	/// <returns>
	/// A unit vector that points to the negative direction of the X axis.
	/// </returns>
	inline static const QVector2& GetUnitVectorInvX()
	{
	    static const QVector2 UNITVECTORINVX(-SQFloat::_1,  SQFloat::_0);
	    return UNITVECTORINVX;
	}

	/// <summary>
	/// Gets a unit vector that points to the negative direction of the Y axis.
	/// </summary>
	/// <returns>
	/// A unit vector that points to the negative direction of the Y axis.
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
	/// Adds two vectors by adding each component.
	/// </summary>
	/// <param name="vVector">[IN] Vector to be added.</param>
	/// <returns>
	/// A vector that is the result of the addition.
	/// </returns>
	QVector2 operator+(const QBaseVector2 &vVector) const;

	/// <summary>
	/// Substracts two vectors by substracting each component.
	/// </summary>
	/// <param name="vVector">[IN] Vector to be substracted.</param>
	/// <returns>
	/// A vector that is the result of the subtraction.
	/// </returns>
	QVector2 operator-(const QBaseVector2 &vVector) const;

	/// <summary>
	/// Multiplies the vector by a scalar.
	/// </summary>
	/// <param name="fScalar">[IN] The scalar to multiply by.</param>
	/// <returns>
	/// A vector that is the result of the product.
	/// </returns>
	QVector2 operator*(const float_q &fScalar) const;

	/// <summary>
	/// Multiplies two vectors by multiplying each component.
	/// </summary>
	/// <param name="vVector">[IN] Vector to multiply by.</param>
	/// <returns>
	/// A vector that is the result of the product.
	/// </returns>
	QVector2 operator*(const QBaseVector2 &vVector) const;

    /// <summary>
    /// Multiplies the vector by a 2x2 matrix.
    /// </summary>
    /// <remarks>
    /// The vector is treated as if it was a one-dimensional matrix with one row.
    /// </remarks>
    /// <param name="matrix">[IN] The matrix to multiply by.</param>
    /// <returns>
    /// A vector that is the result of the product.
    /// </returns>
	QVector2 operator*(const QBaseMatrix2x2 &matrix) const;

	/// <summary>
	/// Divides the vector by a scalar.
	/// </summary>
	/// <param name="fScalar">[IN] The scalar to divide by.</param>
	/// <returns>
	/// A vector that is the result of the division.
	/// </returns>
	QVector2 operator/(const float_q &fScalar) const;

	/// <summary>
	/// Divides two vectors by dividing each component.
	/// </summary>
	/// <param name="vVector">[IN] The vector to divide by.</param>
	/// <returns>
	/// A vector that is the result of the division.
	/// </returns>
	QVector2 operator/(const QBaseVector2 &vVector) const;

	/// <summary>
	/// Adds a vector to the resident vector. The resident vector is set to the result.
	/// </summary>
	/// <param name="vVector">[IN] The vector to be added.</param>
	/// <returns>
	/// A reference to the resident vector, result of the addition.
	/// </returns>
	inline QVector2& operator+=(const QBaseVector2 &vVector)
	{
		this->x += vVector.x;
		this->y += vVector.y;

		return *this;
	}

	/// <summary>
	/// Subtracts a vector to the resident vector. The resident vector is set to the result.
	/// </summary>
	/// <param name="vVector">[IN] The vector to be substracted.</param>
	/// <returns>
	/// A reference to the resident vector, result of the subtraction.
	/// </returns>
	inline QVector2& operator-=(const QBaseVector2 &vVector)
	{
		this->x -= vVector.x;
		this->y -= vVector.y;

		return *this;
	}

	/// <summary>
	/// Multiplies the resident vector by a scalar. The resident vector is set to the result.
	/// </summary>
	/// <param name="fScalar">[IN] The scalar to multiply by.</param>
	/// <returns>
	/// A reference to the resident vector, result of the product.
	/// </returns>
	inline QVector2& operator*=(const float_q fScalar)
	{
		this->x *= fScalar;
		this->y *= fScalar;

		return *this;
	}

	/// <summary>
    /// Multiplies the resident vector by a 2x2 matrix. The resident vector is set to the result.
    /// </summary>
    /// <remarks>
    /// The vector is treated as if it was a one-dimensional matrix with one row.
    /// </remarks>
    /// <param name="matrix">[IN] The matrix to multiply by.</param>
    /// <returns>
    /// A reference to the resident vector, result of the product.
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
	/// Multiplies two vectors by multiplying each component. The resident vector is set to the result.
	/// </summary>
	/// <param name="vVector">[IN] The vector to multiply by.</param>
	/// <returns>
	/// A reference to the resident vector, result of the product.
	/// </returns>
	inline QVector2& operator*=(const QBaseVector2 &vVector)
	{
		this->x *= vVector.x;
		this->y *= vVector.y;

		return *this;
	}

	/// <summary>
	/// Divides the vector by a scalar. The resident vector is set to the result.
	/// </summary>
	/// <param name="fScalar">[IN] The scalar to divide by.</param>
	/// <returns>
	/// A reference to the resident vector, result of the division.
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
	/// Divides two vectors by dividing each component. The resident vector is set to the result.
	/// </summary>
	/// <param name="vVector">[IN] The vector to divide by.</param>
	/// <returns>
	/// A reference to the resident vector, result of the division.
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
    /// Assigns the provided vector to the resident vector.
    /// </summary>
    /// <param name="vVector">[IN] The vector to be assigned.</param>
    /// <returns>
    /// A reference to the resident vector.
    /// </returns>
    inline QVector2& operator=(const QBaseVector2 &vVector)
    {
        QBaseVector2::operator=(vVector);
        return *this;
    }

   	/// <summary>
	/// Negates the vector by negating each component.
	/// </summary>
	/// <returns>
	/// A vector that is the result of the negation.
	/// </returns>
	QVector2 operator-() const;

	/// <summary>
	/// Calculates the length (magnitude) of the vector.
	/// </summary>
	/// <returns>
	/// A scalar whose value equals the length of the vector.
	/// </returns>
	float_q GetLength() const;

	/// <summary>
    /// Calculates the squared length of the vector.
    /// </summary>
    /// <remarks>
    /// The squared length is calculated faster than the length and is commonly used to compare two vectors.
    /// </remarks>
    /// <returns>
    /// A scalar whose value equals the squared length of the vector.
    /// </returns>
    float_q GetSquaredLength() const;

	/// <summary>
	/// Calculates the vector that is perpendicular to the resident vector.
	/// </summary>
    /// <remarks>
    /// It's like rotating the vector by a quarter of circunference, clockwise.
    /// </remarks>
	/// <returns>
	/// A vector that is perpendicular to the resident vector.
	/// </returns>
	QVector2 GetPerpendicular() const;

	/// <summary>
	/// Normalizes the vector. The vector keeps its direction but its length equals one.
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
	/// Converts the vector into its opposite vector.
	/// </summary>
    /// <returns>
	/// The inverted vector.
	/// </returns>
	inline QVector2 Invert() const
	{
        return QVector2(-this->x, -this->y);
	}

	/// <summary>
	/// Sets all the components of the vector to one.
	/// </summary>
	inline void ResetToOne()
	{
		this->x = SQFloat::_1;
		this->y = SQFloat::_1;
	}

	/// <summary>
	/// Sets all the components of the vector to zero.
	/// </summary>
	inline void ResetToZero()
	{
		this->x = SQFloat::_0;
		this->y = SQFloat::_0;
	}

	/// <summary>
	/// Applies a transformation to the resident vector, multiplying it by a transformation matrix.
	/// The transformation can be a rotation, scale, translation or a combination of them.
	/// </summary>
	/// <param name="matrix">[IN] The transformation matrix.</param>
    /// <returns>
	/// The transformed vector.
	/// </returns>
	QVector2 Transform(const QTransformationMatrix3x3 &matrix) const;

	/// <summary>
	/// Rotates the vector by a concrete angle.
	/// </summary>
	/// <param name="fRotationAngle">[IN] The rotation angle.</param>
    /// <returns>
	/// The rotated vector.
	/// </returns>
	QVector2 Transform(const float_q &fRotationAngle) const;

	/// <summary>
	/// Checks if all components equal zero.
	/// </summary>
	/// <returns>
	/// True if all components equal zero; False otherwise.
	/// </returns>
	bool IsZero() const;

	/// <summary>
	/// Checks if all components equal one.
	/// </summary>
	/// <returns>
	/// True if all components equal one; False otherwise.
	/// </returns>
	bool IsVectorOfOnes() const;

	/// <summary>
	/// Calculates the dot product of two vectors.
	/// </summary>
    /// <remarks>
	/// Remember that the dot product is commutative.
	/// </remarks>
	/// <param name="vVector">[IN] The second operand of the product.</param>
	/// <returns>
	/// A scalar whose value equals the result of dot product.
	/// </returns>
	float_q DotProduct(const QVector2 &vVector) const;

    /// <summary>
    /// Calculates the smaller angle between two vectors.
    /// </summary>
    /// <remarks>
    /// The angle will be always lower than or equal to \f$\pi\f$ radians (\f$ 180^0\f$). The order of the operands doesn't affect the result.
    /// </remarks>
    /// <param name="vVector">[IN] The second operand.</param>
    /// <returns>
    /// A scalar whose value equals the angle between the vectors.
    /// </returns>
    float_q DotProductAngle(const QVector2 &vVector) const;

	/// <summary>
	/// Calculates the linear interpolation between two vectors.
	/// </summary>
	/// <param name="fProportion">[IN] A value that represents how close is the resultant vector to the provided 
    /// vector. A value of 0 will produce a vector that equals the resident vector; a value of 1 will produce a vector that
    /// equals the input vector. Note tha values lower than 0 and higher than 1 are also valid.</param>
	/// <param name="vVector">[IN] Vector with which to interpolate.</param>
    /// <returns>
    /// A vector that is the result of the interpolation.
    /// </returns>
	inline QVector2 Lerp(const float_q &fProportion, const QBaseVector2 &vVector) const
	{
        return QVector2(this->x * (SQFloat::_1 - fProportion) + vVector.x * fProportion,
                        this->y * (SQFloat::_1 - fProportion) + vVector.y * fProportion);
	}

	/// <summary>
	/// Calculates the distance between two vectors (two points).
	/// </summary>
	/// <param name="vVector">[IN] Vector to calculate the distance to.</param>
	/// <returns>
	/// A positive value that equals the distance between both vectors.
	/// </returns>
	inline float_q Distance(const QVector2 &vVector) const
	{
		return hypot_q(this->x-vVector.x, this->y-vVector.y);
	}

	/// <summary>
	/// Converts vector into a string with the following format:<br/>
	/// "V2($x,$y)".<br/>
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
