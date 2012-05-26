// [TERMS&CONDITIONS]

#ifndef __QBASEVECTOR3__
#define __QBASEVECTOR3__

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
/// It represents the basic form of a three-dimensional vector with three components: x, y and z.
/// </summary>
class QDllExport QBaseVector3 : public QConvertible
{

    // CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor. Initializes vector to (0,0,0)
	/// </summary>
	inline QBaseVector3() : x(SQFloat::_0), y(SQFloat::_0), z(SQFloat::_0)
    {
    }

	/// <summary>
	/// Constructor from a floating point value for each component.
	/// </summary>
	/// <param name="fValueX">[IN] Value for x component.</param>
	/// <param name="fValueY">[IN] Value for y component.</param>
	/// <param name="fValueZ">[IN] Value for z component.</param>
	inline QBaseVector3(const float_q &fValueX, const float_q &fValueY, const float_q &fValueZ) :
                            x(fValueX), y(fValueY), z(fValueZ)
    {
    }

	/// <summary>
	/// Constructor from a floating point value for all components.
	/// </summary>
	/// <param name="fValueAll">[IN] Value for all components.</param>
	inline explicit QBaseVector3(const float_q &fValueAll) : x(fValueAll), y(fValueAll), z(fValueAll)
    {
    }

	/// <summary>
	/// Constructor from a three floating point components array.
	/// </summary>
	/// <param name="arValues">[IN] Pointer to array of floating point values. It must have at least three elements.</param>
	inline explicit QBaseVector3(const float_q* arValues)
	{
		// Null pointer checkout
		QE_ASSERT(arValues != null_q)

		// Assignments
		this->x = arValues[0];
		this->y = arValues[1];
		this->z = arValues[2];
	}

	/// <summary>
	/// Constructor from a 4x32 packed floating point value.
	/// </summary>
	/// <param name="value">[IN] 4x32 packed floating point containing the three components.<br>
	/// The parse order: 1st value (X), 2nd value (Y), 3rd value (Z), 4th value (Ignored).</param>
	inline explicit QBaseVector3(const vf32_q value)
	{
		float_q fAux;

		SQVF32::Unpack(value, this->x, this->y, this->z, fAux);
	}


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Equality operator. Compares two 3D vectors.
    /// </summary>
    /// <param name="vVector">[IN] Vector with which to compare.</param>
    /// <returns>
    /// True if vectors are the same, false otherwise.
    /// </returns>
    inline bool operator==(const QBaseVector3 &vVector) const
    {
        return ( SQFloat::AreEqual(vVector.x, this->x) && SQFloat::AreEqual(vVector.y, this->y) && SQFloat::AreEqual(vVector.z, this->z) );
    }

    /// <summary>
    /// Inequality operator. Compares two 3D vectors.
    /// </summary>
    /// <param name="vVector">[IN] Vector with which to compare.</param>
    /// <returns>
    /// True if vectors are not the same, false otherwise.
    /// </returns>
    inline bool operator!=(const QBaseVector3 &vVector) const
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
