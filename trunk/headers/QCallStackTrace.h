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

#ifndef __QCALLSTACKTRACE__
#define __QCALLSTACKTRACE__

#include "SystemDefinitions.h"

#include "QCallTrace.h"
#include "QArrayDynamic.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace Diagnosis
{

/// <summary>
/// A call stack trace, which stores information about function calls and is associated to a concrete thread.
/// </summary>
class QE_LAYER_SYSTEM_SYMBOLS QCallStackTrace
{

    // CONSTRUCTORS
    // ---------------
public:
    
    /// <summary>
    /// Constructor that receives the id of a thread as a string.
    /// </summary>
    /// <param name="strThreadId">[IN] The Id of the thread.</param>
    explicit QCallStackTrace(const string_q &strThreadId);
    
private:

    // Hidden
    QCallStackTrace(const QCallStackTrace&);


    // METHODS
    // ---------------
private:

    // Hidden
    QCallStackTrace& operator=(const QCallStackTrace&);

public:

    /// <summary>
    /// Adds a new call trace to the top of the stack.
    /// </summary>
    /// <param name="callTrace">[IN] A call trace to be copied.</param>
    void Push(const QCallTrace &callTrace);

    /// <summary>
    /// Removes the call trace from the top of the stack.
    /// </summary>
    void Pop();

    /// <summary>
    /// Gets a call trace.
    /// </summary>
    /// <param name="strThreadId">[IN] The position index (zero-based) in the stack of call traces, from bottom to top. It must be lower than the number of call traces in the stack.</param>
    /// <returns>
    /// The obtained call trace.
    /// </returns>
    QCallTrace GetTrace(const pointer_uint_q uIndex) const;


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Gets the number of call traces in the stack.
    /// </summary>
    /// <returns>
    /// The number of call traces in the stack.
    /// </returns>
    pointer_uint_q GetCount() const;
    
    /// <summary>
    /// Gets the thread Id.
    /// </summary>
    /// <returns>
    /// The thread Id as a string.
    /// </returns>
    string_q GetThreadId() const;


    // ATTRIBUTES
    // ---------------
protected:
    
    /// <summary>
    /// The function call traces in the call stack trace. It is used as a stack.
    /// </summary>
    Kinesis::QuimeraEngine::Tools::Containers::QArrayDynamic<QCallTrace> m_arCallTraces;
    
    /// <summary>
    /// The Id of the thread associated to this call stack trace.
    /// </summary>
    string_q m_strThreadId;

};

} //namespace Diagnosis
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QCALLSTACKTRACE__
