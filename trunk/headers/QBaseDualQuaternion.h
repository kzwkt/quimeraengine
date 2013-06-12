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

#ifndef __QBASEDUALQUATERNION__
#define __QBASEDUALQUATERNION__

#include "SQFloat.h"
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
/// Base class which implements the basic functionality of a dual quaternion.<br>
/// A dual quaternion is a complex number with two components, a non-dual component and a dual one, e.g. \f$ r + d\varepsilon \f$<br>
/// Both components (r and d) of a dual quaternion are (regular) quaternions.<br>
/// The dual unit, called epsilon (\f$ \varepsilon \f$), verifies \f$ \varepsilon^2=0 \f$. Then, a full quaternion looks like:
///<br>
/// \f$ r_w + r_xi + r_yj + r_zk + (d_w + d_xi + d_yj + d_zk)\varepsilon\f$
///<br>
/// We'll normally employ it to represent and execute rigid transformations, that is, transformations which involves
/// one rotation and one translation, without deforming the transformed solid (which acts as a rigid solid).
/// </summary>
/// <remarks>
/// This class is experimental and therefore subject to changes.
/// </remarks>
class QDllExport QBaseDualQuaternion
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
    inline QBaseDualQuaternion() : r(QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0)),
                                   d(QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0))
    {
    }

    /// <summary>
	/// Copy constructor. Copies attributes from given dual quaternion.
	/// </summary>
	/// <param name="dualQuat">[IN] The dual quaternion from which we want to create a copy in the resident dual quaternion.</param>
	inline QBaseDualQuaternion(const QBaseDualQuaternion &dualQuat)
	{
	    this->r.x = dualQuat.r.x;
	    this->d.x = dualQuat.d.x;
	    this->r.y = dualQuat.r.y;
	    this->d.y = dualQuat.d.y;
	    this->r.z = dualQuat.r.z;
	    this->d.z = dualQuat.d.z;
	    this->r.w = dualQuat.r.w;
        this->d.w = dualQuat.d.w;
    }

    /// <summary>
    /// Constructor from two quaternions, one to initialize the non-dual part and another to do it with the dual part.
    /// </summary>
    /// <param name="qReal">[IN] Quaternion which is the non-dual part of the dual quaternion.</param>
    /// <param name="qDual">[IN] Quaternion which is the dual part of the dual quaternion.</param>
    inline QBaseDualQuaternion(const QBaseQuaternion &qReal, const QBaseQuaternion &qDual) : r(qReal), d(qDual)
    {
    }

	// METHODS
	// ---------------
public:

    /// <summary>
    /// Equality operator. Compares two dual quaternions component by component.
    /// </summary>
    /// <param name="dualQuat">[IN] The dual quaternion to compare to.</param>
    /// <returns>
    /// If dual quaternions are equals, then it returns true. Otherwise, it returns false.
    /// </returns>
    inline bool operator==(const QBaseDualQuaternion &dualQuat) const
    {
        return this->r == dualQuat.r && this->d == dualQuat.d;
    }

    /// <summary>
    /// Inequality operator. Compares two dual quaternions component by component.
    /// </summary>
    /// <param name="dualQuat">[IN] The dual quaternion to compare to.</param>
    /// <returns>
    /// If dual quaternions are not equals, then it returns true. Otherwise, it returns false.
    /// </returns>
    inline bool operator!=(const QBaseDualQuaternion &dualQuat) const
    {
        return !(*this == dualQuat);
    }

	// ATTRIBUTES
	// ---------------
public:

    /// <summary>
    /// Non-dual (real) part of the dual quaternion. Generally it represents the rotation applied.
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
