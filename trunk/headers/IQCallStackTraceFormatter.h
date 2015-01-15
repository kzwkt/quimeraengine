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

#ifndef __IQCALLSTACKTRACEFORMATTER__
#define __IQCALLSTACKTRACEFORMATTER__

#include "SystemDefinitions.h"

#include "QCallStackTrace.h"
#include "RTTIDefinitions.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace Diagnosis
{

/// <summary>
/// Represents a component whose job is to convert call stack traces to text with a concrete format, depending on the implementation.
/// </summary>
class QE_LAYER_SYSTEM_SYMBOLS IQCallStackTraceFormatter
{
public:

    QE_RTTI_SUPPORT_INTERFACE(IQCallStackTraceFormatter);


    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Creates a footer text from the information provided by a call stack trace.
    /// </summary>
    /// <param name="trace">[IN] A call stack trace.</param>
    /// <param name="strFormattedTrace">[OUT] The text to which the formatted footer will be appended.</param>
    virtual void FormatCallStackTraceFooter(const QCallStackTrace &trace, string_q &strFormattedTrace) const=0;
    
    /// <summary>
    /// Creates a header text from the information provided by a call stack trace.
    /// </summary>
    /// <param name="trace">[IN] A call stack trace.</param>
    /// <param name="strFormattedTrace">[OUT] The text to which the formatted header will be appended.</param>
    virtual void FormatCallStackTraceHeader(const QCallStackTrace &trace, string_q &strFormattedTrace) const=0;
    
    /// <summary>
    /// Creates a text with a certain format using the information provided by a call trace.
    /// </summary>
    /// <param name="trace">[IN] A call trace.</param>
    /// <param name="uDepthLevel">[IN] The position of the call trace in the stack, from bottom to top, starting at zero. It is used commonly for indentation.</param>
    /// <param name="strFormattedTrace">[OUT] The text to which the formatted text will be appended.</param>
    virtual void FormatCallTrace(const QCallTrace &trace, const unsigned int uDepthLevel, string_q &strFormattedTrace) const=0;
    
    /// <summary>
    /// Creates a footer text with a certain format using the information provided by a call trace.
    /// </summary>
    /// <param name="trace">[IN] A call trace.</param>
    /// <param name="uDepthLevel">[IN] The position of the call trace in the stack, from bottom to top, starting at zero. It is used commonly for indentation.</param>
    /// <param name="strFormattedTrace">[OUT] The text to which the footer text will be appended.</param>
    virtual void FormatCallTraceFooter(const QCallTrace &trace, const unsigned int uDepthLevel, string_q &strFormattedTrace) const=0;
    
    /// <summary>
    /// Creates a header text with a certain format using the information provided by a call trace.
    /// </summary>
    /// <param name="trace">[IN] A call trace.</param>
    /// <param name="uDepthLevel">[IN] The position of the call trace in the stack, from bottom to top, starting at zero. It is used commonly for indentation.</param>
    /// <param name="strFormattedTrace">[OUT] The text to which the header text will be appended.</param>
    virtual void FormatCallTraceHeader(const QCallTrace &trace, const unsigned int uDepthLevel, string_q &strFormattedTrace) const=0;

};

} //namespace Diagnosis
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __IQCALLSTACKTRACEFORMATTER__
