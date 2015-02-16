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

#include "QCallStackTraceConsolePrinter.h"

#include "SQInteger.h"
#include "SQInternalLogger.h"

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
//##################            |  ATTRIBUTES INITIALIZATION |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QE_RTTI_SUPPORT_TYPE_DEFINITION(QCallStackTraceConsolePrinter);
    

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QCallStackTraceConsolePrinter::QCallStackTraceConsolePrinter(IQCallStackTraceFormatter* pFormatter)
{
    m_pFormatter = boost::shared_ptr<IQCallStackTraceFormatter>(pFormatter);
}

QCallStackTraceConsolePrinter::QCallStackTraceConsolePrinter(boost::shared_ptr<IQCallStackTraceFormatter> &pFormatter)
{
    m_pFormatter = pFormatter;
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |          DESTRUCTOR        |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QCallStackTraceConsolePrinter::~QCallStackTraceConsolePrinter()
{
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

void QCallStackTraceConsolePrinter::PrintString(const string_q &strText)
{
    using Kinesis::QuimeraEngine::Common::SQInternalLogger;

    SQInternalLogger::DefaultLogFunction(strText);
}

string_q QCallStackTraceConsolePrinter::ToString() const
{
    static const string_q CLASS_NAME("QCallStackTraceConsolePrinter");
    return CLASS_NAME;
}


} //namespace Diagnosis
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis
