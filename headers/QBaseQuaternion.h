// [TERMS&CONDITIONS]

#ifndef __QBASEQUATERNION__
#define __QBASEQUATERNION__

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
/// It represents the basic form of a quaternion with its four components: x, y, z and w.
/// </summary>
class QDllExport QBaseQuaternion : public QConvertible
{

	// CONSTRUCTORS
	// ---------------
public:

    /// <summary>
	/// Default constructor.
	/// </summary>
    inline QBaseQuaternion() : x(SQFloat::_0), y(SQFloat::_0), z(SQFloat::_0), w(SQFloat::_0)
    {
    }

    /// <summary>
    /// Constructor that receives 4 values, one per quaternion's component.
    /// </summary>
    /// <param name="fValueX">[IN] X component value.</param>
    /// <param name="fValueY">[IN] Y component value.</param>
    /// <param name="fValueZ">[IN] Z component value.</param>
    /// <param name="fValueW">[IN] W component value.</param>
    inline QBaseQuaternion(const float_q &fValueX, const float_q &fValueY, 
                           const float_q &fValueZ, const float_q &fValueW) : 
                               x(fValueX), y(fValueY), z(fValueZ), w(fValueW)
    {
    }

    /// <summary>
    /// Constructor that receives a pointer to a sequence of 4 contiguous values, one per quaternion's component.
    /// </summary>
    /// <param name="arValues">[IN] Sequence of 4 contiguous values.</param>
    inline explicit QBaseQuaternion(const float_q* arValues)
    {
        // [REVIEW] Thund: Should we put these constants in another place?
        const int QE_X_INDEX_IN_FLOATTYPE_ARRAY = 0;
        const int QE_Y_INDEX_IN_FLOATTYPE_ARRAY = 1;
        const int QE_Z_INDEX_IN_FLOATTYPE_ARRAY = 2;
        const int QE_W_INDEX_IN_FLOATTYPE_ARRAY = 3;

        QE_ASSERT(arValues != null_q)

        this->x = arValues[QE_X_INDEX_IN_FLOATTYPE_ARRAY];
        this->y = arValues[QE_Y_INDEX_IN_FLOATTYPE_ARRAY];
        this->z = arValues[QE_Z_INDEX_IN_FLOATTYPE_ARRAY];
        this->w = arValues[QE_W_INDEX_IN_FLOATTYPE_ARRAY];
    }

    /// <summary>
    /// Constructor that receives four 32 bits floating point type, one per quaternion's component, packaged
    /// into a 128 bits structure. The values order is: X, Y, Z and W.
    /// </summary>
    /// <param name="value">[IN] A four 32 bits floating point types pack.</param>
    inline explicit QBaseQuaternion(const vf32_q &value)
    {
        // Quaternion's components are mapped into the 4x32 pack as configured (see DataTypesDefinitions.h for further information)
        SQVF32::Unpack(value, QE_VF32_FIRST_COMPONENT, QE_VF32_SECOND_COMPONENT, QE_VF32_THIRD_COMPONENT, QE_VF32_SECOND_COMPONENT);
    }

	// METHODS
	// ---------------
public:

    /// <summary>
    /// Equality operator. Compares two quaternions.
    /// </summary>
    /// <param name="qQuat">[IN] The quaternion to compare to.</param>
    /// <returns>
    /// If quaternions are equals, then it returns true. Otherwise, it returns false.
    /// </returns>
    inline bool operator==(const QBaseQuaternion &qQuat) const
    {
        return   SQFloat::AreEquals(this->x, qQuat.x) &&
                 SQFloat::AreEquals(this->y, qQuat.y) &&
                 SQFloat::AreEquals(this->z, qQuat.z) &&
                 SQFloat::AreEquals(this->w, qQuat.w);
    }

    /// <summary>
    /// Inequality operator. Compares two quaternions.
    /// </summary>
    /// <param name="qQuat">[IN] The quaternion to compare to.</param>
    /// <returns>
    /// If quaternions are not equals, then it returns true. Otherwise, it returns false.
    /// </returns>
    inline bool operator!=(const QBaseQuaternion &qQuat) const
    {
        return !(*this == qQuat);
    }

	// ATTRIBUTES
	// ---------------
public:

	/// <summary>
	/// Quaternion's x component.
	/// </summary>
	float_q x;

	/// <summary>
	/// Quaternion's y component.
	/// </summary>
	float_q y;

	/// <summary>
	/// Quaternion's z component.
	/// </summary>
	float_q z;

	/// <summary>
	/// Quaternion's w component.
	/// </summary>
	float_q w;
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASEQUATERNION__
