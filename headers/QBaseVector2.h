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

#ifndef __QBASEVECTOR2__
#define __QBASEVECTOR2__

#include "SQFloat.h"
#include "SQVF32.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::DataTypes::float_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::vf32_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

/// <summary>
/// A vector with two components: X and Y.
/// </summary>
/// <remarks>
///	A vector is a geometric object that has both a magnitude (or length) and a direction.
/// </remarks>
class QDllExport QBaseVector2
{
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
    /// <remarks>
    ///	By default, all the components are set to zero.
    /// </remarks>
	inline QBaseVector2() : x(SQFloat::_0), y(SQFloat::_0)
    {
    }

	/// <summary>
	/// Copy constructor.
	/// </summary>
	/// <param name="vVector">[IN] The vector whose components are to be copied.</param>
	inline QBaseVector2(const QBaseVector2 &vVector)
	{
	    this->x = vVector.x;
	    this->y = vVector.y;
	}

	/// <summary>
	/// Constructor that receives the value of every vector's component.
	/// </summary>
	/// <param name="fValueX">[IN] The value for X component.</param>
	/// <param name="fValueY">[IN] The value for Y component.</param>
	inline QBaseVector2(const float_q &fValueX, const float_q &fValueY) : x(fValueX), y(fValueY)
    {
    }

	/// <summary>
	/// Constructor from a single value for all the vector's components.
	/// </summary>
	/// <param name="fValueAll">[IN] The value for all components.</param>
	inline explicit QBaseVector2(const float_q &fValueAll) : x(fValueAll), y(fValueAll)
    {
    }

	/// <summary>
	/// Constructor that receives an array of scalars.
	/// </summary>
    /// <remarks>
    /// The array must contain, at least, two elements. Only the first two elements will be considered; the rest will be ignored.
    /// </remarks>
	/// <param name="arValues">[IN] An array of scalars. It must contain, at least, two elements.</param>
	inline explicit QBaseVector2(const float_q* arValues)
	{
		// Null pointer checkout
		QE_ASSERT(arValues != null_q)

		// Assignments
		x = arValues[0];
		y = arValues[1];
	}

	/// <summary>
    /// Constructor that receives a pack of four scalars.
    /// </summary>
    /// <remarks>
    /// Only the two first elements in the pack (most significant bits) are considered.
    /// </remarks>
    /// <param name="value">[IN] 4x32 packed floating point value containing the two components.</param>
    inline explicit QBaseVector2(const vf32_q &value)
	{
        using Kinesis::QuimeraEngine::Tools::DataTypes::SQVF32;

		float_q fAux;

		SQVF32::Unpack(value, this->x, this->y, fAux, fAux);
	}


	// METHODS
	// ---------------
public:

    /// <summary>
	/// Checks if two vectors are equal.
	/// </summary>
	/// <param name="vVector">[IN] The vector to which to compare.</param>
	/// <returns>
	/// True if vectors are the same; False otherwise.
	/// </returns>
	inline bool operator==(const QBaseVector2 &vVector) const
	{
        return ( SQFloat::AreEqual(vVector.x, this->x) && SQFloat::AreEqual(vVector.y, this->y) );
	}

	/// <summary>
	/// Checks if two vectors are not equal.
	/// </summary>
	/// <param name="vVector">[IN] The vector to which to compare.</param>
	/// <returns>
	/// True if vectors are not the same; False otherwise.
	/// </returns>
	inline bool operator!=(const QBaseVector2 &vVector) const
	{
        return !(*this == vVector);
	}

	// ATTRIBUTES
	// ---------------
public:

	/// <summary>
	/// Vector's X coordinate.
	/// </summary>
	float_q x;

	/// <summary>
	/// Vector's Y coordinate.
	/// </summary>
	float_q y;

};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASEVECTOR2__
