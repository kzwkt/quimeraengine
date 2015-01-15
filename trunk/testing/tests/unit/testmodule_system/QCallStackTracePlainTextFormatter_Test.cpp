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

#include "QCallStackTracePlainTextFormatter.h"

using Kinesis::QuimeraEngine::System::Diagnosis::QCallStackTracePlainTextFormatter;
using Kinesis::QuimeraEngine::System::Diagnosis::QCallStackTrace;
using Kinesis::QuimeraEngine::System::Diagnosis::QCallTrace;
using Kinesis::QuimeraEngine::System::Diagnosis::QArgumentTrace;


QTEST_SUITE_BEGIN( QCallStackTracePlainTextFormatter_TestSuite )

/// <summary>
/// Checks that the expected text is obtained when using a common call stack trace.
/// </summary>
QTEST_CASE ( FormatCallStackTraceFooter_ExpectedTextIsObtained_Test )
{
    // [Preparation]
    QCallStackTracePlainTextFormatter formatter;
    const string_q EXPECTED_TEXT("End of call stack trace information.\n");
    QCallStackTrace stackTrace("ThreadId");
    int i = 5;
    float f = 1.0f;
    QArgumentTrace arArgumentTraces[] = { QArgumentTrace(i), QArgumentTrace(f) };
    QCallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    stackTrace.Push(callTrace);
    string_q strOutput;

    // [Execution]
    formatter.FormatCallStackTraceFooter(stackTrace, strOutput);
    
    // [Verification]
    BOOST_CHECK(strOutput == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the generated text is appended to the output string.
/// </summary>
QTEST_CASE ( FormatCallStackTraceFooter_TextIsAppended_Test )
{
    // [Preparation]
    QCallStackTracePlainTextFormatter formatter;
    const string_q EXPECTED_TEXT("Previous textEnd of call stack trace information.\n");
    QCallStackTrace stackTrace("ThreadId");
    int i = 5;
    float f = 1.0f;
    QArgumentTrace arArgumentTraces[] = { QArgumentTrace(i), QArgumentTrace(f) };
    QCallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    stackTrace.Push(callTrace);
    string_q strOutput("Previous text");

    // [Execution]
    formatter.FormatCallStackTraceFooter(stackTrace, strOutput);
    
    // [Verification]
    BOOST_CHECK(strOutput == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the expected text is obtained when using a common call stack trace.
/// </summary>
QTEST_CASE ( FormatCallStackTraceHeader_ExpectedTextIsObtained_Test )
{
    // [Preparation]
    QCallStackTracePlainTextFormatter formatter;
    const string_q EXPECTED_TEXT("Call stack trace for ThreadId\n");
    QCallStackTrace stackTrace("ThreadId");
    int i = 5;
    float f = 1.0f;
    QArgumentTrace arArgumentTraces[] = { QArgumentTrace(i), QArgumentTrace(f) };
    QCallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    stackTrace.Push(callTrace);
    string_q strOutput;

    // [Execution]
    formatter.FormatCallStackTraceHeader(stackTrace, strOutput);
    
    // [Verification]
    BOOST_CHECK(strOutput == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the generated text is appended to the output string.
/// </summary>
QTEST_CASE ( FormatCallStackTraceHeader_TextIsAppended_Test )
{
    // [Preparation]
    QCallStackTracePlainTextFormatter formatter;
    const string_q EXPECTED_TEXT("Previous textCall stack trace for ThreadId\n");
    QCallStackTrace stackTrace("ThreadId");
    int i = 5;
    float f = 1.0f;
    QArgumentTrace arArgumentTraces[] = { QArgumentTrace(i), QArgumentTrace(f) };
    QCallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    stackTrace.Push(callTrace);
    string_q strOutput("Previous text");

    // [Execution]
    formatter.FormatCallStackTraceHeader(stackTrace, strOutput);
    
    // [Verification]
    BOOST_CHECK(strOutput == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the expected text is obtained when using a common call stack trace.
/// </summary>
QTEST_CASE ( FormatCallTrace_ExpectedTextIsObtained_Test )
{
    // [Preparation]
    QCallStackTracePlainTextFormatter formatter;
    const string_q EXPECTED_TEXT("\
int function(int i, float f)\n\
  | -{0}i32=5\n\
  | -{1}f32=1\n");
    int i = 5;
    float f = 1.0f;
    QArgumentTrace arArgumentTraces[] = { QArgumentTrace(i), QArgumentTrace(f) };
    QCallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    string_q strOutput;

    // [Execution]
    formatter.FormatCallTrace(callTrace, 0, strOutput);
    
    // [Verification]
    BOOST_CHECK(strOutput == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the expected text is obtained when using a common call stack trace.
/// </summary>
QTEST_CASE ( FormatCallTrace_DepthLevelAffestsTheResult_Test )
{
    // [Preparation]
    QCallStackTracePlainTextFormatter formatter;
    const string_q EXPECTED_TEXT("\
int function(int i, float f)\n\
    | -{0}i32=5\n\
    | -{1}f32=1\n");
    int i = 5;
    float f = 1.0f;
    QArgumentTrace arArgumentTraces[] = { QArgumentTrace(i), QArgumentTrace(f) };
    QCallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    string_q strOutput1;
    string_q strOutput2;
    const unsigned int DEPTH1 = 0;
    const unsigned int DEPTH2 = 1;

    // [Execution]
    formatter.FormatCallTrace(callTrace, DEPTH1, strOutput1);
    formatter.FormatCallTrace(callTrace, DEPTH2, strOutput2);
    
    // [Verification]
    BOOST_CHECK(strOutput1 != strOutput2);
    BOOST_CHECK(strOutput2 == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the generated text is appended to the output string.
/// </summary>
QTEST_CASE ( FormatCallTrace_TextIsAppended_Test )
{
    // [Preparation]
    QCallStackTracePlainTextFormatter formatter;
    const string_q EXPECTED_TEXT("Previous text\
int function(int i, float f)\n\
  | -{0}i32=5\n\
  | -{1}f32=1\n");
    int i = 5;
    float f = 1.0f;
    QArgumentTrace arArgumentTraces[] = { QArgumentTrace(i), QArgumentTrace(f) };
    QCallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    string_q strOutput("Previous text");

    // [Execution]
    formatter.FormatCallTrace(callTrace, 0, strOutput);
    
    // [Verification]
    BOOST_CHECK(strOutput == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the expected text is obtained when using a common call stack trace.
/// </summary>
QTEST_CASE ( FormatCallTraceHeader_ExpectedTextIsObtained_Test )
{
    // [Preparation]
    QCallStackTracePlainTextFormatter formatter;
    const string_q EXPECTED_TEXT("-->");
    int i = 5;
    float f = 1.0f;
    QArgumentTrace arArgumentTraces[] = { QArgumentTrace(i), QArgumentTrace(f) };
    QCallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    string_q strOutput;

    // [Execution]
    formatter.FormatCallTraceHeader(callTrace, 0, strOutput);
    
    // [Verification]
    BOOST_CHECK(strOutput == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the expected text is obtained when using a common call stack trace.
/// </summary>
QTEST_CASE ( FormatCallTraceHeader_DepthLevelAffestsTheResult_Test )
{
    // [Preparation]
    QCallStackTracePlainTextFormatter formatter;
    const string_q EXPECTED_TEXT("  -->");
    int i = 5;
    float f = 1.0f;
    QArgumentTrace arArgumentTraces[] = { QArgumentTrace(i), QArgumentTrace(f) };
    QCallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    string_q strOutput1;
    string_q strOutput2;
    const unsigned int DEPTH1 = 0;
    const unsigned int DEPTH2 = 1;

    // [Execution]
    formatter.FormatCallTraceHeader(callTrace, DEPTH1, strOutput1);
    formatter.FormatCallTraceHeader(callTrace, DEPTH2, strOutput2);
    
    // [Verification]
    BOOST_CHECK(strOutput1 != strOutput2);
    BOOST_CHECK(strOutput2 == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the generated text is appended to the output string.
/// </summary>
QTEST_CASE ( FormatCallTraceHeader_TextIsAppended_Test )
{
    // [Preparation]
    QCallStackTracePlainTextFormatter formatter;
    const string_q EXPECTED_TEXT("Previous text-->");
    int i = 5;
    float f = 1.0f;
    QArgumentTrace arArgumentTraces[] = { QArgumentTrace(i), QArgumentTrace(f) };
    QCallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    string_q strOutput("Previous text");

    // [Execution]
    formatter.FormatCallTraceHeader(callTrace, 0, strOutput);
    
    // [Verification]
    BOOST_CHECK(strOutput == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the expected text is obtained when using a common call stack trace.
/// </summary>
QTEST_CASE ( FormatCallTraceFooter_ExpectedTextIsObtained_Test )
{
    // [Preparation]
    QCallStackTracePlainTextFormatter formatter;
    const string_q EXPECTED_TEXT("");
    int i = 5;
    float f = 1.0f;
    QArgumentTrace arArgumentTraces[] = { QArgumentTrace(i), QArgumentTrace(f) };
    QCallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    string_q strOutput;

    // [Execution]
    formatter.FormatCallTraceFooter(callTrace, 0, strOutput);
    
    // [Verification]
    BOOST_CHECK(strOutput == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the generated text is appended to the output string.
/// </summary>
QTEST_CASE ( FormatCallTraceFooter_TextIsAppended_Test )
{
    // [Preparation]
    QCallStackTracePlainTextFormatter formatter;
    const string_q EXPECTED_TEXT("Previous text");
    int i = 5;
    float f = 1.0f;
    QArgumentTrace arArgumentTraces[] = { QArgumentTrace(i), QArgumentTrace(f) };
    QCallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    string_q strOutput("Previous text");

    // [Execution]
    formatter.FormatCallTraceFooter(callTrace, 0, strOutput);
    
    // [Verification]
    BOOST_CHECK(strOutput == EXPECTED_TEXT);
}

// End - Test Suite: QCallStackTracePlainTextFormatter
QTEST_SUITE_END()
