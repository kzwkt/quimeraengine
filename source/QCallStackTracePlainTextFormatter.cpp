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

#include "QCallStackTracePlainTextFormatter.h"

#include "SQInteger.h"


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

QE_RTTI_SUPPORT_TYPE_DEFINITION(QCallStackTracePlainTextFormatter);
    

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |          DESTRUCTOR        |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QCallStackTracePlainTextFormatter::~QCallStackTracePlainTextFormatter()
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

void QCallStackTracePlainTextFormatter::FormatCallStackTraceFooter(const QCallStackTrace &trace, string_q &strFormattedTrace) const
{
    static const string_q FOOTER("End of call stack trace information.\n");
    strFormattedTrace.Append(FOOTER);
}

void QCallStackTracePlainTextFormatter::FormatCallStackTraceHeader(const QCallStackTrace &trace, string_q &strFormattedTrace) const
{
    static const string_q HEADER("Call stack trace for ");
    static const string_q NEW_LINE("\n");

    strFormattedTrace.Append(HEADER);
    strFormattedTrace.Append(trace.GetThreadId());
    strFormattedTrace.Append(NEW_LINE);
}

void QCallStackTracePlainTextFormatter::FormatCallTrace(const QCallTrace &trace, const unsigned int uDepthLevel, string_q &strFormattedTrace) const
{
    using Kinesis::QuimeraEngine::Common::DataTypes::SQInteger;
        
    static const string_q ONE_LEVEL("  ");
    string_q strIndentation;
    for(unsigned int i = 0; i < uDepthLevel; ++i)
        strIndentation.Append(ONE_LEVEL);

    static const string_q NEW_LINE("\n");
    strFormattedTrace.Append(trace.GetFunctionSignature());
    strFormattedTrace.Append(NEW_LINE);

    static const string_q ARGUMENT_PREFIX1("  | -{");
    static const string_q ARGUMENT_PREFIX2("}");
    static const string_q EQUAL_SIGN("=");
    const QArgumentTrace* arArguments = trace.GetArguments();

    for(unsigned int i = 0; i < trace.GetArgumentsCount(); ++i)
    {
        strFormattedTrace.Append(strIndentation);
        strFormattedTrace.Append(ARGUMENT_PREFIX1);
        strFormattedTrace.Append(SQInteger::ToString(i));
        strFormattedTrace.Append(ARGUMENT_PREFIX2);
        strFormattedTrace.Append(arArguments[i].GetTypeName());
        strFormattedTrace.Append(EQUAL_SIGN);
        strFormattedTrace.Append(arArguments[i].GetValue());
        strFormattedTrace.Append(NEW_LINE);
    }
}

void QCallStackTracePlainTextFormatter::FormatCallTraceFooter(const QCallTrace &trace, const unsigned int uDepthLevel, string_q &strFormattedTrace) const
{
    // Nothing
}

void QCallStackTracePlainTextFormatter::FormatCallTraceHeader(const QCallTrace &trace, const unsigned int uDepthLevel, string_q &strFormattedTrace) const
{
    static const string_q HEADER("-->");
    static const string_q ONE_LEVEL("  ");

    for(unsigned int i = 0; i < uDepthLevel; ++i)
        strFormattedTrace.Append(ONE_LEVEL);

    strFormattedTrace.Append(HEADER);
}

string_q QCallStackTracePlainTextFormatter::ToString() const
{
    static const string_q CLASS_NAME("QCallStackTracePlainTextFormatter");
    return CLASS_NAME;
}

} //namespace Diagnosis
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis
