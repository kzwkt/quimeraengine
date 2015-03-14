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

#ifndef __QTYPE__
#define __QTYPE__

#include "CommonDefinitions.h"
#include "DataTypesDefinitions.h"

#ifdef QE_COMPILER_MSVC
    // This warning appears when instancing a template to create a data member and that template instance is not exported.
    // In this case, it is not important since the data member is not accessible.
    #pragma warning( disable : 4251 ) // http://msdn.microsoft.com/en-us/library/esew7y1w.aspx
#endif


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace DataTypes
{

/// <summary>
/// Describes a data type.
/// </summary>
/// <remarks>
/// QType instances are intended to be unique for every class for which they are defined. Do not create
/// any instance unless you are defining a new class.<br/>
/// This class is immutable and it is not intended to be derived.
/// </remarks>
class QE_LAYER_COMMON_SYMBOLS QType
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Constructor that receives the type's information.
	/// </summary>
    /// <param name="strName">The unqualified name of the type.</param>
	explicit QType(const string_q &strName);


	// METHODS
	// ---------------
public:

    /// <summary>
	/// Equality operator that checks if two instances are the same or not.
	/// </summary>
    /// <param name="type">The other instance to compare to.</param>
    /// <returns>
    /// True if both instances are equal (same memory address); False otherwise.
    /// </returns>
    bool operator==(const QType &type) const;

    /// <summary>
	/// Inequality operator that checks if two instances are different or not.
	/// </summary>
    /// <param name="type">The other instance to compare to.</param>
    /// <returns>
    /// True if instances are not equal (different memory address); False otherwise.
    /// </returns>
    bool operator!=(const QType &type) const;


	// PROPERTIES
	// ---------------
public:

    /// <summary>
	/// Gets the unqualified name of the type.
	/// </summary>
    /// <returns>
    /// The unqualified name of the type.
    /// </returns>
    const string_q& GetName() const;


	// ATTRIBUTES
	// ---------------
private:

    /// <summary>
    /// The unqualified name of the type.
    /// </summary>
    const string_q m_strName;

};

} //namespace DataTypes
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QTYPE__
