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

#ifndef __QSTRINGUNICODE__
#define __QSTRINGUNICODE__

#include "DataTypesDefinitions.h"
#include "CommonDefinitions.h"

#include "unicode/unistr.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace DataTypes
{

/// <summary>
/// Represents text formed by a sequence of Unicode characters.
/// </summary>
/// <remarks>
/// Internally, characters are encoded in UTF-16. This may change in the future.
/// Instances of this class are mutable, this means, the same instance can take different values during its lifecycle.
/// Instances of this class are not thread-safe.
/// </remarks>
class QE_LAYER_COMMON_SYMBOLS QStringUnicode
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	QStringUnicode();

    /// <summary>
    /// Constructor that makes a copy of another string.
    /// </summary>
    /// <param name="strString">[IN] The input string to be copied.</param>
    QStringUnicode(const QStringUnicode &strString);


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Assignation operator that copies the value of another string.
    /// </summary>
    /// <param name="strString">[IN] The input string to be copied.</param>
    /// <remarks>
    /// A reference to the resident string.
    /// </remarks>
    QStringUnicode& operator=(const QStringUnicode &strString);


	// PROPERTIES
	// ---------------
public:


	// ATTRIBUTES
	// ---------------
private:

    /// <summary>
    /// Internal string representation.
    /// </summary>
    icu::UnicodeString m_strString;

};

} //namespace DataTypes
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QSTRINGUNICODE__
