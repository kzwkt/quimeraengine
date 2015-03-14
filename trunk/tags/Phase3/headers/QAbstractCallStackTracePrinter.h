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

#ifndef __QABSTRACTCALLSTACKTRACEPRINTER__
#define __QABSTRACTCALLSTACKTRACEPRINTER__

#include "SystemDefinitions.h"

#include "IQCallStackTraceFormatter.h"
#include "QCallStackTrace.h"
#include "RTTIDefinitions.h"
#include <boost/shared_ptr.hpp>


namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace Diagnosis
{

/// <summary>
/// Represents a component whose job is to send the content of a call stack trace to an output channel, depending on the implementation.
/// </summary>
class QE_LAYER_SYSTEM_SYMBOLS QAbstractCallStackTracePrinter
{
    QE_RTTI_SUPPORT_ABSTRACT_CLASS(QAbstractCallStackTracePrinter);
    

    // METHODS
    // ---------------
public:
        
    /// <summary>
    /// Prints information from a call stack trace using the format provided by the stored formatter.
    /// </summary>
    /// <param name="callStackTrace">[IN] A call stack trace.</param>
    virtual void PrintCallStackTrace(const QCallStackTrace &callStackTrace);
    
    /// <summary>
    /// Prints text to the output channel.
    /// </summary>
    /// <param name="strText">[IN] Text to be printed.</param>
    virtual void PrintString(const string_q &strText)=0;


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Sets the call stack trace formatter to be used when printing.
    /// </summary>
    /// <param name="pFormatter">[IN] A call stack trace formatter. It will be stored in a shared smart pointer.</param>
    void SetFormatter(IQCallStackTraceFormatter* pFormatter);
    
    /// <summary>
    /// Sets the call stack trace formatter to be used when printing.
    /// </summary>
    /// <param name="pFormatter">[IN] A call stack trace formatter. It will be stored in a shared smart pointer.</param>
    void SetFormatter(boost::shared_ptr<IQCallStackTraceFormatter> &pFormatter);
    
    /// <summary>
    /// Gets the call stack trace formatter to be used when printing.
    /// </summary>
    /// <returns>
    /// The stored formatter instance.
    /// </returns>
    boost::shared_ptr<IQCallStackTraceFormatter> GetFormatter() const;
    

    // ATTRIBUTES
    // ---------------
protected:
    
    /// <summary>
    /// The call stack trace formatter to be used when printing.
    /// </summary>
    boost::shared_ptr<IQCallStackTraceFormatter> m_pFormatter;

};

} //namespace Diagnosis
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QABSTRACTCALLSTACKTRACEPRINTER__
