// [TERMS&CONDITIONS]

#ifndef __QBASEDUALQUATERNION__
#define __QBASEDUALQUATERNION__

#include "QFloat.h"
#include "QQuaternion.h"

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
/// A dual quaternion is a complex number with two components, a non-dual component and a dual one, e.g. r + d€. 
/// Both components (r and d) of a dual quaternion are (regular) quaternions.
/// The dual unit, called epsilon (€), verifies €*€ = 0. Then, a full quaternion looks like:
/// w1 + x1*i + y1*j + z1*k + (w2 + x2*i + y2*j + z2*k)*€
/// We'll normally employ it to represent and execute rigid transformations, that is, transformations which involves
/// one rotation and one translation, without deforming the transformed solid (which acts as a rigid solid).
/// </summary>
class QDllExport QBaseDualQuaternion
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
    QBaseDualQuaternion() : r(QQuaternion::Identity), d(QQuaternion::Identity) { } 

    /// <summary>
    /// Constructor from two quaternions, one to initialize the non-dual part and another to do it with the dual part.
    /// </summary>
    /// <param name="qR">[IN] Quaternion which is the non-dual part of the dual quaternion.</param>
    /// <param name="qD">[IN] Quaternion which is the dual part of the dual quaternion.</param>
    QBaseDualQuaternion(const QQuaternion &qR, const QQuaternion &qD) : r(qR), d(qD) { }

	// ATTRIBUTES
	// ---------------
public:

    /// <summary>
    /// Non-dual part of the dual quaternion. Generally it represents the rotation applied.
    /// </summary>
    QQuaternion r;

    /// <summary>
    /// Dual part of the dual quaternion. Generally it represents the traslation applied.
    /// </summary>
    QQuaternion d;


};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASEDUALQUATERNION__
