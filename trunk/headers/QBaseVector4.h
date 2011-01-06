// [TERMS&CONDITIONS]

#ifndef __QBASEVECTOR4__
#define __QBASEVECTOR4__

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
/// It represents the basic form of a four-dimensional vector with three components: x, y, z and w.
/// </summary>
class QDllExport QBaseVector4
{
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Override default constructor. Sets attributes to zero.
	/// </summary>	
	inline QBaseVector4 () : x(QFloat::_0), y(QFloat::_0), z(QFloat::_0), w(QFloat::_0) {}

	/// <summary>
	/// Constructor that receives 4 FloatTypes, one for each vector components.
	/// </summary>
	/// <param name="fX">[IN] Value for x component.</param>
	/// <param name="fY">[IN] Value for y component.</param>
	/// <param name="fZ">[IN] Value for z component.</param>
	/// <param name="fW">[IN] Value for w component.</param>
	inline QBaseVector4 (const float_q &fX, const float_q &fY, const float_q &fZ, const float_q &fW) : x(fX), y(fY), z(fZ), w(fW) {}

	/// <summary>
	/// Constructor that receives only 1 FloatType. Set all attributes to that value
	/// </summary>
	/// <param name="fValueAll">[IN] Value for all components</param>
	inline explicit QBaseVector4 (const float_q &fValueAll) : x(fValueAll), y(fValueAll), z(fValueAll), w(fValueAll) {}

	/// <summary>
	/// Constructor that receives a pointer-to-FloatType. The pointer should point to a dynamically allocated 4-FloatTypes array.
	/// </summary>
	/// <param name="pValues">[IN] Pointer to array of floating point values. It must have at least four elements.</param>
	inline explicit QBaseVector4 (const float_q *pValues)
	{
		// Null pointer checkout
		QE_ASSERT(pValues != null_q);

		// Assignments
		x = pValues[0]; 
		y = pValues[1]; 
		z = pValues[2];
		w = pValues[3];
	}

	/// <summary>
	/// Constructor from a 4x32 packed floating point value.
	/// </summary>
	/// <param name="fValue">[IN] 4x32 packed floating point containing the three components.
	/// The parse order: 1st value (X), 2nd value (Y), 3rd value (Z), 4th value (W).</param>
	inline explicit QBaseVector4(const vf32_q &fValue) 
	{
        QVF32::Unpack(fValue, this->x, this->y, this->z, this->w);
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

	/// <summary>
	/// Vector's w coordinate.
	/// </summary>
	float_q w;
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASEVECTOR4__
