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

#ifndef __QASSERTEXCEPTION__
#define __QASSERTEXCEPTION__

#include "CommonDefinitions.h"
#include "StringsDefinitions.h"

using Kinesis::QuimeraEngine::Common::DataTypes::string_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace Exceptions
{

/// <summary>
/// Exception used for testing purposes only. It stores information about a failed assertion.
/// </summary>
class QE_LAYER_COMMON_SYMBOLS QAssertException
{
    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Constructor that receives all the information about a failed assertion.
    /// </summary>
    /// <param name="strCondition">[IN] The condition that failed.</param>
    /// <param name="strMessage">[IN] The error message.</param>
    /// <param name="nLineNumber">[IN] The number of the line where the assertion failed.</param>
    /// <param name="strFileName">[IN] The source code file where the assertion failed.</param>
    QAssertException(const string_q &strCondition, const string_q &strMessage, const int nLineNumber, const string_q &strFileName);


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets the condition that failed.
    /// </summary>
    /// <returns>
    /// A string that contains the condition that failed.
    /// </returns>
    string_q GetCondition() const;

    /// <summary>
    /// Gets the error message.
    /// </summary>
    /// <returns>
    /// The error message.
    /// </returns>
    string_q GetMessage() const;

    /// <summary>
    /// Gets the number of the line where the assertion failed.
    /// </summary>
    /// <returns>
    /// The number of the line where the assertion failed.
    /// </returns>
    int GetLineNumber() const;

    /// <summary>
    /// Gets the source code file where the assertion failed.
    /// </summary>
    /// <returns>
    /// The source code file where the assertion failed.
    /// </returns>
    string_q GetFileName() const;


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// A string that contains the condition that failed.
    /// </summary>
    string_q m_strCondition;

    /// <summary>
    /// The error message.
    /// </summary>
    string_q m_strMessage;

    /// <summary>
    /// The number of the line where the assertion failed.
    /// </summary>
    int m_nLineNumber;

    /// <summary>
    /// The source code file where the assertion failed.
    /// </summary>
    string_q m_strFileName;

};

} //namespace Exceptions
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QASSERTEXCEPTION__
