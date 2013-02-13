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

#ifndef __QBASEVECTOR4__
#define __QBASEVECTOR4__

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
/// It represents the basic form of a four-dimensional vector with three components: x, y, z and w.
/// </summary>
class QDllExport QBaseVector4 : public QConvertible
{
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Override default constructor. Sets attributes to zero.
	/// </summary>
	inline QBaseVector4() : x(SQFloat::_0), y(SQFloat::_0), z(SQFloat::_0), w(SQFloat::_0)
    {
    }

    /// <summary>
	/// Copy constructor. Copies attributes from given vector.
	/// </summary>
	/// <param name="vVector">[IN] The 4D vector from which we want to create a copy in the resident vector.</param>
	inline QBaseVector4(const QBaseVector4 &vVector)
	{
	    this->x = vVector.x;
	    this->y = vVector.y;
	    this->z = vVector.z;
	    this->w = vVector.w;
	}

	/// <summary>
	/// Constructor that receives 4 FloatTypes, one for each vector components.
	/// </summary>
	/// <param name="fValueX">[IN] Value for x component.</param>
	/// <param name="fValueY">[IN] Value for y component.</param>
	/// <param name="fValueZ">[IN] Value for z component.</param>
	/// <param name="fValueW">[IN] Value for w component.</param>
	inline QBaseVector4(const float_q &fValueX, const float_q &fValueY, const float_q &fValueZ, const float_q &fValueW) :
                            x(fValueX), y(fValueY), z(fValueZ), w(fValueW)
    {
    }

	/// <summary>
	/// Constructor that receives only 1 FloatType. Set all attributes to that value
	/// </summary>
	/// <param name="fValueAll">[IN] Value for all components</param>
	inline explicit QBaseVector4(const float_q &fValueAll) : x(fValueAll), y(fValueAll), z(fValueAll), w(fValueAll)
    {
    }

	/// <summary>
	/// Constructor that receives an array of 4 floating point numbers.
	/// </summary>
	/// <param name="arValues">[IN] Pointer to array of floating point values. It must have at least four elements.</param>
	inline explicit QBaseVector4(const float_q* arValues)
	{
		// Null pointer checkout
		QE_ASSERT(arValues != null_q)

		// Assignments
		x = arValues[0];
		y = arValues[1];
		z = arValues[2];
		w = arValues[3];
	}

	/// <summary>
	/// Constructor from a 4x32 packed floating point value.
	/// </summary>
	/// <param name="value">[IN] 4x32 packed floating point containing the three components.<br>
	/// The parse order: 1st value (X), 2nd value (Y), 3rd value (Z), 4th value (W).</param>
	inline explicit QBaseVector4(const vf32_q &value)
	{
        SQVF32::Unpack(value, this->x, this->y, this->z, this->w);
	}


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Equality operator. Compares two 4D vectors.
    /// </summary>
    /// <param name="vVector">[IN] Vector with which to compare.</param>
    /// <returns>
    /// True if vectors are the same, false otherwise.
    /// </returns>
    inline bool operator==(const QBaseVector4 &vVector) const
    {
        return SQFloat::AreEqual(vVector.x, this->x) && SQFloat::AreEqual(vVector.y, this->y) &&
               SQFloat::AreEqual(vVector.z, this->z) && SQFloat::AreEqual(vVector.w, this->w);
    }

    /// <summary>
    /// Inequality operator. Compares two 4D vectors.
    /// </summary>
    /// <param name="vVector">[IN] Vector with which to compare.</param>
    /// <returns>
    /// True if vectors are not the same, false otherwise.
    /// </returns>
    inline bool operator!=(const QBaseVector4 &vVector) const
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
