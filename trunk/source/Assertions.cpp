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

#include "Assertions.h"

#include "LoggingUtilities.h"
#include "SQInteger.h"

using Kinesis::QuimeraEngine::Common::DataTypes::string_q;
using Kinesis::QuimeraEngine::Common::SQInternalLogger;
using Kinesis::QuimeraEngine::Common::DataTypes::SQInteger;


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           FUNCTIONS         |               ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################


#ifdef QE_COMPILER_GCC

void QE_ASSERT_FAILED()
{
    asm("int $3"); // This sentence makes GDB to stop at the failing line and continue the execution later
}

#endif


void QE_TRACE_FAILED_ASSERT(const string_q &strExpression, const string_q &strErrorMessage, const int nLineNumber, const string_q &strFileName)
{
    string_q strLogText("!! QE ASSERTION FAILED !! : \"");
    strLogText.Append(strErrorMessage);
    strLogText.Append(string_q("\" at "));
    strLogText.Append(strFileName);
    strLogText.Append(" (");
    strLogText.Append(SQInteger::ToString(nLineNumber));
    strLogText.Append(") [");
    strLogText.Append(strExpression);
    strLogText.Append("]");
    strLogText.Append(string_q("\n"));
    QE_LOG(strLogText);
}