// [TERMS&CONDITIONS]

#ifndef __QBASEDUALQUATERNION__
#define __QBASEDUALQUATERNION__

#include "SQFloat.h"
#include "QQuaternion.h"
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
/// Base class which implements the basic functionality of a dual quaternion.
/// A dual quaternion is a complex number with two components, a non-dual component and a dual one, e.g. \f$ r + d\varepsilon \f$
/// Both components (r and d) of a dual quaternion are (regular) quaternions.
/// The dual unit, called epsilon (\f$ \varepsilon \f$), verifies \f$ \varepsilon^2=0 \f$. Then, a full quaternion looks like:
/// \f$ r_w + r_xi + r_yj + r_zk + (d_w + d_xi + d_yj + d_zk)\varepsilon\f$
/// We'll normally employ it to represent and execute rigid transformations, that is, transformations which involves
/// one rotation and one translation, without deforming the transformed solid (which acts as a rigid solid).
/// </summary>
class QDllExport QBaseDualQuaternion : public QConvertible
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
    inline QBaseDualQuaternion() : r(QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0)),
                            d(QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0)) { }

    /// <summary>
    /// Constructor from two quaternions, one to initialize the non-dual part and another to do it with the dual part.
    /// </summary>
    /// <param name="qR">[IN] Quaternion which is the non-dual part of the dual quaternion.</param>
    /// <param name="qD">[IN] Quaternion which is the dual part of the dual quaternion.</param>
    inline QBaseDualQuaternion(const QBaseQuaternion &qR, const QBaseQuaternion &qD) : r(qR), d(qD) { }

	// METHODS
	// ---------------
public:

    /// <summary>
    /// Equality operator. Compares two dual quaternions component by component.
    /// </summary>
    /// <param name="dqQuat">[IN] The dual quaternion to compare to.</param>
    /// <returns>
    /// If dual quaternions are equals, then it returns true. Otherwise, it returns false.
    /// </returns>
    inline bool operator==(const QBaseDualQuaternion &dqQuat) const
    {
        return this->r == dqQuat.r && this->d == dqQuat.d;
    }

    /// <summary>
    /// Inequality operator. Compares two dual quaternions component by component.
    /// </summary>
    /// <param name="dqQuat">[IN] The dual quaternion to compare to.</param>
    /// <returns>
    /// If dual quaternions are not equals, then it returns true. Otherwise, it returns false.
    /// </returns>
    inline bool operator!=(const QBaseDualQuaternion &dqQuat) const
    {
        return !(*this == dqQuat);
    }

	// ATTRIBUTES
	// ---------------
public:

    /// <summary>
    /// Non-dual part of the dual quaternion. Generally it represents the rotation applied.
    /// </summary>
    QQuaternion r;

    /// <summary>
    /// Dual part of the dual quaternion. Generally it represents the traslation applied (modified by the rotation).
    /// </summary>
    QQuaternion d;


};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASEDUALQUATERNION__
