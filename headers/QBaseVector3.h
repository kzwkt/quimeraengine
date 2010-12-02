// [TERMS&CONDITIONS]

#ifndef __QBASEVECTOR3__
#define __QBASEVECTOR3__

#include "QFloat.h"
#include "QVF32.h"

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
/// It represents the basic form of a three-dimensional vector with three components: x, y and z.
/// </summary>
class QDllExport QBaseVector3
{

public:

	/// <summary>
	/// Default constructor. Initializes vector to (0,0,0)
	/// </summary>
	inline QBaseVector3() : x(QFloat::_0), y(QFloat::_0), z(QFloat::_0) { }

	/// <summary>
	/// Constructor from a floating point value for each component.
	/// </summary>
	/// <param name="fValueX">[IN] Value for x component.</param>
	/// <param name="fValueY">[IN] Value for y component.</param>
	/// <param name="fValueZ">[IN] Value for z component.</param>
	inline QBaseVector3(const float_q &fValueX, const float_q &fValueY, const float_q &fValueZ) : x(fValueX), y(fValueY), z(fValueZ) { }

	/// <summary>
	/// Constructor from a floating point value for all components.
	/// </summary>
	/// <param name="fValue">[IN] Value for all components.</param>
	inline explicit QBaseVector3(const float_q &fValue) : x(fValue), y(fValue), z(fValue) { }

	/// <summary>
	/// Constructor from a three floating point components array.
	/// </summary>
	/// <param name="pValue">[IN] Pointer to array of floating point values. It must have at least three elements.</param>
	inline explicit QBaseVector3(const float_q *pValue)
	{
		// Null pointer checkout
		QE_ASSERT(pValue != null_q);

		// Assignments
		this->x = pValue[0]; 
		this->y = pValue[1]; 
		this->z = pValue[2];
	}

	/// <summary>
	/// Constructor from a 4x32 packed floating point value.
	/// </summary>
	/// <param name="fValue">[IN] 4x32 packed floating point containing the three components.
	/// The parse order: 1st value (X), 2nd value (Y), 3rd value (Z), 4th value (Ignored).</param>
	inline explicit QBaseVector3(const vf32_q fValue) 
	{
		float_q aux;

		QVF32::Unpack(fValue, this->x, this->y, this->z, aux);
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

	/// <summary>
	/// Vector's z coordinate.
	/// </summary>
	float_q z;
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASEVECTOR3__
