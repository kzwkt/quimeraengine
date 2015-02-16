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

#include "QCallTrace.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace Diagnosis
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QCallTrace::QCallTrace(const char* szFunctionSignature, const QArgumentTrace* arArgumentTraces, const unsigned int uNumberOfArguments) : 
                                                                                                                        m_szFunctionSignature(szFunctionSignature),
                                                                                                                        m_arArgumentTraces(arArgumentTraces),
                                                                                                                        m_uNumberOfArguments(uNumberOfArguments),
                                                                                                                        m_szClassName(null_q),
                                                                                                                        m_strObjectState(string_q::GetEmpty())
{
    QE_ASSERT_WARNING(!(arArgumentTraces == null_q && uNumberOfArguments > 0), "The number of arguments cannot be greater than zero if the argument array is null.");
    QE_ASSERT_WARNING(!(arArgumentTraces != null_q && uNumberOfArguments == 0), "The number of arguments cannot be zero if the argument array is not null.");
    QE_ASSERT_WARNING(szFunctionSignature != null_q, "The function signature cannot be empty.");
}

QCallTrace::QCallTrace(const char* szFunctionSignature, const QArgumentTrace* arArgumentTraces, const unsigned int uNumberOfArguments, const char* szClassName) : 
                                                                                                                        m_szFunctionSignature(szFunctionSignature),
                                                                                                                        m_arArgumentTraces(arArgumentTraces),
                                                                                                                        m_uNumberOfArguments(uNumberOfArguments),
                                                                                                                        m_szClassName(szClassName),
                                                                                                                        m_strObjectState(string_q::GetEmpty())
{
    QE_ASSERT_WARNING(!(arArgumentTraces == null_q && uNumberOfArguments > 0), "The number of arguments cannot be greater than zero if the argument array is null.");
    QE_ASSERT_WARNING(!(arArgumentTraces != null_q && uNumberOfArguments == 0), "The number of arguments cannot be zero if the argument array is not null.");
    QE_ASSERT_WARNING(szFunctionSignature != null_q, "The function signature cannot be empty.");
    QE_ASSERT_WARNING(szClassName != null_q, "The class name cannot be empty.");
}

QCallTrace::QCallTrace(const char* szFunctionSignature, const QArgumentTrace* arArgumentTraces, const unsigned int uNumberOfArguments, const char* szClassName, const string_q& strObjectState) : 
                                                                                                                        m_szFunctionSignature(szFunctionSignature),
                                                                                                                        m_arArgumentTraces(arArgumentTraces),
                                                                                                                        m_uNumberOfArguments(uNumberOfArguments),
                                                                                                                        m_szClassName(szClassName),
                                                                                                                        m_strObjectState(strObjectState)
{
    QE_ASSERT_WARNING(!(arArgumentTraces == null_q && uNumberOfArguments > 0), "The number of arguments cannot be greater than zero if the argument array is null.");
    QE_ASSERT_WARNING(!(arArgumentTraces != null_q && uNumberOfArguments == 0), "The number of arguments cannot be zero if the argument array is not null.");
    QE_ASSERT_WARNING(szFunctionSignature != null_q, "The function signature cannot be empty.");
    QE_ASSERT_WARNING(szClassName != null_q, "The class name cannot be empty.");
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################
 
const char* QCallTrace::GetFunctionSignature() const
{
    return m_szFunctionSignature;
}

const QArgumentTrace* QCallTrace::GetArguments() const
{
    return m_arArgumentTraces;
}

unsigned int QCallTrace::GetArgumentsCount() const
{
    return m_uNumberOfArguments;
}

const char* QCallTrace::GetClassName() const
{
    return m_szClassName;
}

const string_q& QCallTrace::GetObjectState() const
{
    return m_strObjectState;
}


} //namespace Diagnosis
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis
