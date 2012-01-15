// [TERMS&CONDITIONS]

#ifndef __QBASEVECTOR2__
#define __QBASEVECTOR2__

#include "SQFloat.h"
#include "SQVF32.h"
#include "QConvertible.h"

using Kinesis::QuimeraEngine::Core::QConvertible;
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
/// It represents the basic form of a two-dimensional vector with two components: x and y.
/// </summary>
class QDllExport QBaseVector2 : public QConvertible
{
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Override default constructor. Sets attributes to zero.
	/// </summary>
	inline QBaseVector2() : x(SQFloat::_0), y(SQFloat::_0)
    {
    }

	/// <summary>
	/// Constructor that receives 2 numbers, one for each vector component.
	/// </summary>
	/// <param name="fValueX">[IN] Value for x component</param>
	/// <param name="fValueY">[IN] Value for y component</param>
	inline QBaseVector2(const float_q &fValueX, const float_q &fValueY) : x(fValueX), y(fValueY)
    {
    }

	/// <summary>
	/// Constructor that receives only 1 number. Sets all attributes to that value.
	/// </summary>
	/// <param name="fValueAll">[IN] Value for all components</param>
	inline explicit QBaseVector2(const float_q &fValueAll) : x(fValueAll), y(fValueAll) 
    {
    }

	/// <summary>
	/// Constructor that receives an array of 2 floating point numbers.
	/// </summary>
	/// <param name="arValues">[IN] Pointer to array of floating point values. It must have at least two elements.</param>
	inline explicit QBaseVector2(const float_q* arValues)
	{
		// Null pointer checkout
		QE_ASSERT(arValues != null_q)

		// Assignments
		x = arValues[0];
		y = arValues[1];
	}

	/// <summary>
	/// Constructor that receives a 4x32 packed floating point value. The first two packed components are saved into the components of the vector.
	/// </summary>
	/// <param name="value">[IN] 4x32 packed floating point containing the three components.
	/// The parse order: 1st value (X), 2nd value (Y), 3rd value (Ignored), 4th value (Ignored).</param>
	inline explicit QBaseVector2(const vf32_q &value)
	{
		float_q fAux;

		SQVF32::Unpack(value, this->x, this->y, fAux, fAux);
	}


	// METHODS
	// ---------------
public:

    /// <summary>
	/// Equality operator. Compares two 2D vectors.
	/// </summary>
	/// <param name="vVector">[IN] Vector with which to compare.</param>
	/// <returns>
	/// True if vectors are the same, false otherwise.
	/// </returns>
	inline bool operator==(const QBaseVector2 &vVector) const
	{
        return ( SQFloat::AreEquals(vVector.x, this->x) && SQFloat::AreEquals(vVector.y, this->y) );
	}

	/// <summary>
	/// Inequality operator. Compares two 2D vectors.
	/// </summary>
	/// <param name="vVector">[IN] Vector with which to compare.</param>
	/// <returns>
	/// True if vectors are not the same, false otherwise.
	/// </returns>
	inline bool operator!=(const QBaseVector2 &vVector) const
	{
        return !(*this == vVector);
	}

	// ATTRIBUTES
	// ---------------
public:

	/// <summary>
	/// Vector's x coordinate.
	/// </summary>
	float_q x;

	/// <summary>
	/// Vector's y coordinate.
	/// </summary>
	float_q y;

};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASEVECTOR2__
