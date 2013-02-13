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

#ifndef __QBASEPLANE__
#define __QBASEPLANE__

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
/// It represents the basic form of a 3D plane, defined by the equation \f$ ax + by + cz + d = 0 \f$.<br>
/// We can see that the vector (a, b, c) is normal to the plane, and d represents the sorthest distance from plane to the origin.
/// </summary>
class QDllExport QBasePlane : public QConvertible
{
    // CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	inline QBasePlane() : a(SQFloat::_0), b(SQFloat::_0), c(SQFloat::_0), d(SQFloat::_0)
    {
    }

    /// <summary>
	/// Copy constructor.
	/// </summary>
	/// <param name="plane">[IN] The plane from which we want to create a copy in the resident plane.</param>
	inline QBasePlane(const QBasePlane &plane)
	{
	    this->a = plane.a;
	    this->b = plane.b;
	    this->c = plane.c;
	    this->d = plane.d;
	}

	/// <summary>
	/// Constructor from a floating point value for each coefficient.
	/// </summary>
	/// <param name="fValueA">[IN] Floating point value for a coefficient.</param>
	/// <param name="fValueB">[IN] Floating point value for b coefficient.</param>
	/// <param name="fValueC">[IN] Floating point value for c coefficient.</param>
	/// <param name="fValueD">[IN] Floating point value for independent term d.</param>
	inline QBasePlane(const float_q &fValueA, const float_q &fValueB, const float_q &fValueC, const float_q &fValueD) :
                        a(fValueA), b(fValueB), c(fValueC), d(fValueD)
    {
    }

	/// <summary>
	/// Constructor from a floating point value for all coefficients.
	/// </summary>
	/// <param name="fValueAll">[IN] Floating point value.</param>
	inline explicit QBasePlane(const float_q &fValueAll) : a(fValueAll), b(fValueAll), c(fValueAll), d(fValueAll)
    {
    }

	/// <summary>
	/// Constructor from a pointer to a array of floating point values.
	/// </summary>
	/// <param name="arValues">[IN] Pointer to array of floating point values. It must have at least four elements.</param>
	inline explicit QBasePlane(float_q* arValues)
	{
		// Null pointer checkout
		QE_ASSERT(arValues != null_q)

		// Assignments
		this->a = arValues[0];
		this->b = arValues[1];
		this->c = arValues[2];
		this->d = arValues[3];
	}

	/// <summary>
	/// Constructor from a 4x32 packed float value.
	/// </summary>
	/// <param name="value">[IN] 4x32 packed float containing the four components.<br>
	/// The parse order: 1st value (a coefficient), 2nd value (b coefficient),
	/// 3rd value (c coefficient), 4th value (d independent term).</param>
	inline explicit QBasePlane(const vf32_q &value)
	{
		SQVF32::Unpack(value, this->a, this->b, this->c, this->d);
	}

    // METHODS
    // --------------
public:

    /// <summary>
    /// Equality operator. Compares two planes.
    /// </summary>
    /// <remarks>
    /// Note that if any of the planes are not normalized, the result may be false, even if they are the same plane:
    /// <br>
    /// \f$ x + y + z + 1 = 0\f$ and \f$ 2x + 2y + 2z + 2 = 0\f$ are the same plane but their components are different.
    /// </remarks>
    /// <param name="plane">[IN] Plane with which to compare.</param>
    /// <returns>
    /// True if planes are the same, false otherwise.
    /// </returns>
    inline bool operator==(const QBasePlane &plane) const
    {
        return ( SQFloat::AreEqual(plane.a, this->a) && SQFloat::AreEqual(plane.b, this->b) &&
                 SQFloat::AreEqual(plane.c, this->c) && SQFloat::AreEqual(plane.d, this->d) );
    }

    /// <summary>
    /// Inequality operator. Compares two planes.
    /// </summary>
    /// <remarks>
    /// Note that if any of the planes are not normalized, the result may be true, even if they are the same plane.
    /// <br>
    /// \f$ x + y + z + 1 = 0\f$ and \f$ 2x + 2y + 2z + 2 = 0\f$ are the same plane but their components are different.
    /// </remarks>
    /// <param name="plane">[IN] Plane with which to compare.</param>
    /// <returns>
    /// True if planes are not the same, false otherwise.
    /// </returns>
    inline bool operator!=(const QBasePlane &plane) const
    {
        return !(*this == plane);
    }


	// ATTRIBUTES
	// ---------------
public:

	/// <summary>
	/// X coefficient of the plane equation.
	/// </summary>
	float_q a;

	/// <summary>
	/// Y coefficient of the plane equation.
	/// </summary>
	float_q b;

	/// <summary>
	/// Z coefficient of the plane equation.
	/// </summary>
	float_q c;

	/// <summary>
	/// Independent term of the plane equation.
	/// </summary>
	float_q d;
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASEPLANE__
