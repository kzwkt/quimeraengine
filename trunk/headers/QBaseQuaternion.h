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

#ifndef __QBASEQUATERNION__
#define __QBASEQUATERNION__

#include "DataTypesDefinitions.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::vf32_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::float_q;


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
class QDllExport QBaseQuaternion
{

	// CONSTRUCTORS
	// ---------------
public:

    /// <summary>
	/// Default constructor.
	/// </summary>
    QBaseQuaternion();

    /// <summary>
	/// Copy constructor. Copies attributes from given quaternion.
	/// </summary>
	/// <param name="qQuat">[IN] The quaternion from which we want to create a copy in the resident quaternion.</param>
	QBaseQuaternion(const QBaseQuaternion &qQuat);

    /// <summary>
    /// Constructor that receives 4 values, one per quaternion's component.
    /// </summary>
    /// <param name="fValueX">[IN] X component value.</param>
    /// <param name="fValueY">[IN] Y component value.</param>
    /// <param name="fValueZ">[IN] Z component value.</param>
    /// <param name="fValueW">[IN] W component value.</param>
    QBaseQuaternion(const float_q &fValueX, const float_q &fValueY, const float_q &fValueZ, const float_q &fValueW);

    /// <summary>
    /// Constructor that receives a pointer to a sequence of 4 contiguous values, one per quaternion's component.
    /// </summary>
    /// <param name="arValues">[IN] Array of 4 values. If the pointer is null, the behavior  
    /// is undefined.</param>
    explicit QBaseQuaternion(const float_q* arValues);

    /// <summary>
    /// Constructor that receives four 32 bits floating point type, one per quaternion's component, packaged
    /// into a 128 bits structure.<br/>
    /// The values order is: X, Y, Z and W.
    /// </summary>
    /// <param name="value">[IN] A four 32 bits floating point types pack.</param>
    explicit QBaseQuaternion(const vf32_q &value);


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
    bool operator==(const QBaseQuaternion &qQuat) const;

    /// <summary>
    /// Inequality operator. Compares two quaternions.
    /// </summary>
    /// <param name="qQuat">[IN] The quaternion to compare to.</param>
    /// <returns>
    /// If quaternions are not equals, then it returns true. Otherwise, it returns false.
    /// </returns>
    bool operator!=(const QBaseQuaternion &qQuat) const;


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
