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

#include "QAbstractCallStackTracePrinter.h"


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

QE_RTTI_SUPPORT_TYPE_DEFINITION(QAbstractCallStackTracePrinter);


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QAbstractCallStackTracePrinter::QAbstractCallStackTracePrinter() : m_pFormatter((IQCallStackTraceFormatter*)null_q)
{
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |          DESTRUCTOR        |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QAbstractCallStackTracePrinter::~QAbstractCallStackTracePrinter()
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

void QAbstractCallStackTracePrinter::PrintCallStackTrace(const QCallStackTrace &callStackTrace)
{
    static const string_q NEW_LINE("\n");

    string_q strTextToPrint;
    m_pFormatter->FormatCallStackTraceHeader(callStackTrace, strTextToPrint);
    
    for(pointer_uint_q i = 0; i < callStackTrace.GetCount(); ++i)
    {
        m_pFormatter->FormatCallTraceHeader(callStackTrace.GetTrace(i), i, strTextToPrint);
        m_pFormatter->FormatCallTrace(callStackTrace.GetTrace(i), i, strTextToPrint);
        m_pFormatter->FormatCallTraceFooter(callStackTrace.GetTrace(i), i, strTextToPrint);
    }

    m_pFormatter->FormatCallStackTraceFooter(callStackTrace, strTextToPrint);
    this->PrintString(strTextToPrint);
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################
 
void QAbstractCallStackTracePrinter::SetFormatter(boost::shared_ptr<IQCallStackTraceFormatter> pFormatter)
{
    m_pFormatter = pFormatter;
}

boost::shared_ptr<IQCallStackTraceFormatter> QAbstractCallStackTracePrinter::GetFormatter() const
{
    return m_pFormatter;
}


} //namespace Diagnosis
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis
