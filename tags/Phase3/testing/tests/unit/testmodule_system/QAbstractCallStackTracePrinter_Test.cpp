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

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "QAbstractCallStackTracePrinter.h"
#include "QCallStackTracePlainTextFormatter.h"
#include "QAbstractCallStackTracePrinterMock.h"

using Kinesis::QuimeraEngine::System::Diagnosis::QAbstractCallStackTracePrinter;
using Kinesis::QuimeraEngine::System::Diagnosis::QCallStackTracePlainTextFormatter;
using Kinesis::QuimeraEngine::System::Diagnosis::QCallStackTrace;
using Kinesis::QuimeraEngine::System::Diagnosis::QCallTrace;
using Kinesis::QuimeraEngine::System::Diagnosis::QArgumentTrace;


QTEST_SUITE_BEGIN( QAbstractCallStackTracePrinter_TestSuite )

/// <summary>
/// Checks that the expected text is obtained when using a common call stack trace.
/// </summary>
QTEST_CASE ( PrintCallStack_ExpectedTextIsPrintedWhenUsingCommonStackTrace_Test )
{
    using Kinesis::QuimeraEngine::System::Diagnosis::IQCallStackTraceFormatter;
    using Kinesis::QuimeraEngine::System::Diagnosis::Test::QAbstractCallStackTracePrinterMock;

    // [Preparation]
    boost::shared_ptr<IQCallStackTraceFormatter> pFormatter(new QCallStackTracePlainTextFormatter());
    QAbstractCallStackTracePrinterMock printer;
    printer.SetFormatter(pFormatter);
    const string_q EXPECTED_TEXT("Call stack trace for ThreadId\n\
-->int function(int i, float f)\n\
  | -{0}i32=5\n\
  | -{1}f32=1\n\
  -->int function(int i)\n\
    | -{0}i32=5\n\
    -->int function()\n\
End of call stack trace information.\n");
    QCallStackTrace stackTrace("ThreadId");
    int i = 5;
    float f = 1.0f;
    QArgumentTrace arArgumentTraces[] = { QArgumentTrace(i), QArgumentTrace(f) };
    stackTrace.Push(QCallTrace("int function(int i, float f)", arArgumentTraces, 2));
    stackTrace.Push(QCallTrace("int function(int i)", arArgumentTraces, 1));
    stackTrace.Push(QCallTrace("int function()", null_q, 0));

    // [Execution]
    printer.PrintCallStackTrace(stackTrace);
    
    // [Verification]
    BOOST_CHECK(printer.GetPrintedText() == EXPECTED_TEXT);
}


// End - Test Suite: QAbstractCallStackTracePrinter
QTEST_SUITE_END()
