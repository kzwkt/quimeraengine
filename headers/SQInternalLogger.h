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

#ifndef __SQINTERNALLOGGER__
#define __SQINTERNALLOGGER__

#include "DataTypesDefinitions.h"

#ifdef QE_COMPILER_MSVC
    #pragma warning( push )
    #pragma warning( disable: 4251 ) // This warning occurs when using a template specialization as attribute
#endif

#include "QDelegate.h"

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{

/// <summary>
/// Logger used internally by the engine's libraries to write text to a given output channel.
/// </summary>
/// <remarks>
/// This class is not intended to be used by final users but only by the engine.<br/>
/// Since the lowest layers of the engine do not have any logging utility (loggers are implemented in the System layer) and
/// it is not possible to access a class of an upper layer, it was necessary to provide a way to send all the log entries 
/// produced by lower layer libraries to external loggers. Using a delegate, upper layers can set it to call any function,
/// for example a logger instance's method. Lower layers will call that delegate, whatever function it points to.
/// </remarks>
class QE_LAYER_COMMON_SYMBOLS SQInternalLogger
{
	// CONSTRUCTORS
	// ---------------
private:

	/// <summary>
	/// Default constructor (hidden).
	/// </summary>
	SQInternalLogger();
    

	// METHODS
	// ---------------
public:

    /// <summary>
	/// Sends text to the active console, if any. When using Visual Studio, the text will be sent to the output debug window.
	/// </summary>
    /// <remarks>
	/// No end-of-line characters are added.
	/// </remarks>
    /// <param name="strMessage">[IN] The text to be sent to the console.</param>
    static void DefaultLogFunction(const DataTypes::string_q &strMessage);


	// PROPERTIES
	// ---------------
public:

    /// <summary>
	/// Sets the log function to which the delegate will point.
	/// </summary>
    /// <param name="loggingFunction">[IN] The new logging function.</param>
    static void SetLogFunction(QDelegate<void (const DataTypes::string_q&)> loggingFunction);


	// ATTRIBUTES
	// ---------------
public:

    /// <summary>
	/// Call the logging function directly.
	/// </summary>
    static QDelegate<void (const DataTypes::string_q&)> Log;
};

} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis

#ifdef QE_COMPILER_MSVC
    #pragma warning( pop )
#endif

#endif // __SQINTERNALLOGGER__
