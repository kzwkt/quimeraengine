// [TERMS&CONDITIONS]

#ifndef __QBASEVECTOR2__
#define __QBASEVECTOR2__

#include "QFloat.h"

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
class QDllExport QBaseVector2
{
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Override default constructor. Sets attributes to zero.
	/// </summary>
	inline QBaseVector2 () : x(QFloat::_0), y(QFloat::_0) {}

	/// <summary>
	/// Constructor that receives 2 FloatTypes, one for each vector components.
	/// </summary>
	/// <param name="fValueX">[IN] Value for x component</param>
	/// <param name="fValueY">[IN] Value for y component</param>
	inline QBaseVector2 (const float_q &fValueX, const float_q &fValueY) : x(fValueX), y(fValueY) {}

	/// <summary>
	/// Constructor that receives only 1 FloatType. Set all attributes to that value.
	/// </summary>
	/// <param name="fValueAll">[IN] Value for all components</param>
	inline explicit QBaseVector2 (const float_q &fValueAll) : x(fValueAll), y(fValueAll) {}

	/// <summary>
	/// Constructor that receives a pointer-to-FloatType. The pointer should point to a dynamically allocated 2-FloatTypes array.
	/// </summary>
	/// <param name="pValues">[IN] Pointer to array of floating point values. It must have at least two elements.</param>		
	inline explicit QBaseVector2 (const float_q *pValues) 
	{ 
		// Null pointer checkout
		QE_ASSERT(pValues != null_q);

		// Assignments
		x = pValues[0]; 
		y = pValues[1]; 
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