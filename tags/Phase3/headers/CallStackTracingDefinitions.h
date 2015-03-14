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

#ifndef __CALLSTACKTRACINGDEFINITIONS__
#define __CALLSTACKTRACINGDEFINITIONS__

#include "SystemDefinitions.h"

#include "QScopedCallTraceNotifier.h"

namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace Diagnosis
{
    
// --------------------------------------------------------------------------------------------------------
// Quimera Engine's Call Stack Tracing utility: It must be placed at the very beginning of the body of 
// a free function.
// --------------------------------------------------------------------------------------------------------
#define QE_TRACE_CALLSTACK_FUNCTION_WITHOUT_PARAMS()                                          \
    const Kinesis::QuimeraEngine::System::Diagnosis::QScopedCallTraceNotifier SCOPED_TRACE(   \
            Kinesis::QuimeraEngine::System::Diagnosis::QCallTrace(QE_PRINT_FUNCTION,          \
                                                                  null_q,                     \
                                                                  0));

// --------------------------------------------------------------------------------------------------------
// Quimera Engine's Call Stack Tracing utility: It must be placed at the very beginning of the body of a method. 
// The class name, which is a null-terminated array of chars, is passed as parameter to this macro.
// --------------------------------------------------------------------------------------------------------
#define QE_TRACE_CALLSTACK_METHOD_WITHOUT_PARAMS(szClassName)                                 \
    const Kinesis::QuimeraEngine::System::Diagnosis::QScopedCallTraceNotifier SCOPED_TRACE(   \
            Kinesis::QuimeraEngine::System::Diagnosis::QCallTrace(QE_PRINT_FUNCTION,          \
                                                                  null_q,                     \
                                                                  0,                          \
                                                                  szClassName));

// --------------------------------------------------------------------------------------------------------
// Quimera Engine's Call Stack Tracing utility: It must be placed at the very beginning of the body of a 
// The class name, which is a null-terminated array of chars, is passed as parameter to this macro.
// It assumes that the class implements the ToString method, which is called to get the state of the object.
// --------------------------------------------------------------------------------------------------------
#define QE_TRACE_CALLSTACK_METHOD_WITHOUT_PARAMS_WITH_TOSTRING(szClassName)                   \
    const Kinesis::QuimeraEngine::System::Diagnosis::QScopedCallTraceNotifier SCOPED_TRACE(   \
            Kinesis::QuimeraEngine::System::Diagnosis::QCallTrace(QE_PRINT_FUNCTION,          \
                                                                  null_q,                     \
                                                                  0,                          \
                                                                  szClassName,                \
                                                                  this->ToString()));

// --------------------------------------------------------------------------------------------------------
// Quimera Engine's Call Stack Tracing utility: It must be placed at the very beginning of the body of 
// a free function. Every function parameter has to be passed to this macro.
// --------------------------------------------------------------------------------------------------------
#define QE_TRACE_CALLSTACK_FUNCTION_WITH_PARAMS(...)                                                                                                            \
    const Kinesis::QuimeraEngine::System::Diagnosis::QArgumentTrace ARGUMENT_TRACES[] = { __VA_ARGS__ };                                                        \
    const Kinesis::QuimeraEngine::System::Diagnosis::QScopedCallTraceNotifier SCOPED_TRACE(                                                                     \
            Kinesis::QuimeraEngine::System::Diagnosis::QCallTrace(QE_PRINT_FUNCTION,                                                                            \
                                                                  ARGUMENT_TRACES,                                                                              \
                                                                  sizeof(ARGUMENT_TRACES) / sizeof(Kinesis::QuimeraEngine::System::Diagnosis::QArgumentTrace)));

// --------------------------------------------------------------------------------------------------------
// Quimera Engine's Call Stack Tracing utility: It must be placed at the very beginning of the body of a method. 
// Every function parameter has to be passed to this macro after the class name, which is a null-terminated array of chars.
// --------------------------------------------------------------------------------------------------------
#define QE_TRACE_CALLSTACK_METHOD_WITH_PARAMS(szClassName, ...)                                                                                                 \
    const Kinesis::QuimeraEngine::System::Diagnosis::QArgumentTrace ARGUMENT_TRACES[] = { __VA_ARGS__ };                                                        \
    const Kinesis::QuimeraEngine::System::Diagnosis::QScopedCallTraceNotifier SCOPED_TRACE(                                                                     \
            Kinesis::QuimeraEngine::System::Diagnosis::QCallTrace(QE_PRINT_FUNCTION,                                                                            \
                                                                  ARGUMENT_TRACES,                                                                              \
                                                                  sizeof(ARGUMENT_TRACES) / sizeof(Kinesis::QuimeraEngine::System::Diagnosis::QArgumentTrace),  \
                                                                  szClassName));

// --------------------------------------------------------------------------------------------------------
// Quimera Engine's Call Stack Tracing utility: It must be placed at the very beginning of the body of a 
// non-static method. Every function parameter has to be passed to this macro after the class 
// name, which is a null-terminated array of chars. It assumes that the class implements the ToString method, 
// which is called to get the state of the object.
// --------------------------------------------------------------------------------------------------------
#define QE_TRACE_CALLSTACK_METHOD_WITH_PARAMS_WITH_TOSTRING(szClassName, ...)                                                                                   \
    const Kinesis::QuimeraEngine::System::Diagnosis::QArgumentTrace ARGUMENT_TRACES[] = { __VA_ARGS__ };                                                        \
    const Kinesis::QuimeraEngine::System::Diagnosis::QScopedCallTraceNotifier SCOPED_TRACE(                                                                     \
            Kinesis::QuimeraEngine::System::Diagnosis::QCallTrace(QE_PRINT_FUNCTION,                                                                            \
                                                                  ARGUMENT_TRACES,                                                                              \
                                                                  sizeof(ARGUMENT_TRACES) / sizeof(Kinesis::QuimeraEngine::System::Diagnosis::QArgumentTrace),  \
                                                                  szClassName,                                                                                  \
                                                                  this->ToString()));

// --------------------------------------------------------------------------------------------------------
// Quimera Engine's Call Stack Tracing utility: Encloses an argument that is known to provide an implementation
// of the ToString method, which returns a string representation of the object's state. This macro is intended to 
// be used in the list of parameters passed to QE_TRACE_CALLSTACK_* macros.
// --------------------------------------------------------------------------------------------------------
#define QE_TRACE_PARAM_HAS_TOSTRING(param) Kinesis::QuimeraEngine::System::Diagnosis::QArgumentTrace(param, Kinesis::QuimeraEngine::System::Diagnosis::QTypeWithToString())

// --------------------------------------------------------------------------------------------------------
// Quimera Engine's Call Stack Tracing utility: Encloses an argument that is known to provide an implementation
// of the GetTypeObjcet method, which returns a pointer to a QType instance that contains the name of the type. 
// This macro is intended to be used in the list of parameters passed to QE_TRACE_CALLSTACK_* macros.
// --------------------------------------------------------------------------------------------------------
#define QE_TRACE_PARAM_HAS_GETTYPE(param) Kinesis::QuimeraEngine::System::Diagnosis::QArgumentTrace(param, Kinesis::QuimeraEngine::System::Diagnosis::QTypeWithGetType())

// --------------------------------------------------------------------------------------------------------
// Quimera Engine's Call Stack Tracing utility: Encloses an argument that is known to provide an implementation
// of the ToString method, which returns a string representation of the object's state, and an implementation of 
// the GetTypeObjcet method, which returns a pointer to a QType instance that contains the name of the type. 
// This macro is intended to be used in the list of parameters passed to QE_TRACE_CALLSTACK_* macros.
// --------------------------------------------------------------------------------------------------------
#define QE_TRACE_PARAM_HAS_GETTYPE_TOSTRING(param) Kinesis::QuimeraEngine::System::Diagnosis::QArgumentTrace(param, Kinesis::QuimeraEngine::System::Diagnosis::QTypeWithGetType(), \
                                                                                                                    Kinesis::QuimeraEngine::System::Diagnosis::QTypeWithToString())


} //namespace Diagnosis
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __CALLSTACKTRACINGDEFINITIONS__
