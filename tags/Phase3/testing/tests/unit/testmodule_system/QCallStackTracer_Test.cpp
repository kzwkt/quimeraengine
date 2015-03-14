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

#include "QCallStackTracer.h"
#include "QAbstractCallStackTracePrinterMock.h"
#include "QCallStackTracePlainTextFormatter.h"
#include "EQComparisonType.h"

using Kinesis::QuimeraEngine::System::Diagnosis::QCallStackTracer;
using Kinesis::QuimeraEngine::System::Diagnosis::Test::QAbstractCallStackTracePrinterMock;
using Kinesis::QuimeraEngine::System::Diagnosis::QAbstractCallStackTracePrinter;
using Kinesis::QuimeraEngine::System::Diagnosis::IQCallStackTraceFormatter;
using Kinesis::QuimeraEngine::System::Diagnosis::QCallStackTracePlainTextFormatter;
using Kinesis::QuimeraEngine::System::Diagnosis::QCallTrace;
using Kinesis::QuimeraEngine::System::Diagnosis::QArgumentTrace;


QTEST_SUITE_BEGIN( QCallStackTracer_TestSuite )

void InitializeCallStackTracer_TestMethod()
{
    static bool bInitialized = false;

    if(!bInitialized)
    {
        QCallStackTracer::Get()->SetPrinter(new QAbstractCallStackTracePrinterMock(new QCallStackTracePlainTextFormatter()));
        bInitialized = true;
    }
}

/// <summary>
/// Checks that it creates a call stack trace when it does not exist yet.
/// </summary>
QTEST_CASE ( AddTrace_CallStackTraceIsCreatedWhenItDoesNotExist_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    InitializeCallStackTracer_TestMethod();
    const string_q EXPECTED_TEXT("\
int function(int i, float f)\n\
  | -{0}i32=5\n\
  | -{1}f32=1\n");
    int i = 5;
    float f = 1.0f;
    QArgumentTrace arArgumentTraces[] = { QArgumentTrace(i), QArgumentTrace(f) };
    QCallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);

    // [Execution]
    QCallStackTracer::Get()->AddTrace(callTrace);
    
    // [Verification]
    QCallStackTracer::Get()->Dump();
    QAbstractCallStackTracePrinterMock* pPrinter = QCallStackTracer::Get()->GetPrinter()->As<QAbstractCallStackTracePrinterMock>();
    bool bPrintedTextContainsExpectedTrace = pPrinter->GetPrintedText().Contains(EXPECTED_TEXT, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bPrintedTextContainsExpectedTrace);

    // [Cleaning]
    QCallStackTracer::Get()->RemoveLastTrace();
    pPrinter->ClearPrintedText();
}

/// <summary>
/// Checks that a call trace is correctly added to the call stack trace.
/// </summary>
QTEST_CASE ( AddTrace_CallTraceIsAddedToExistingStack_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    InitializeCallStackTracer_TestMethod();
    const string_q EXPECTED_TEXT("\
int function(int i, float f)\n\
  | -{0}i32=5\n\
  | -{1}f32=1\n\
  -->int function2(float f)\n\
    | -{0}f32=2\n");
    int i = 5;
    float f = 1.0f;
    float f2 = 2.0f;
    QArgumentTrace arArgumentTraces[] = { QArgumentTrace(i), QArgumentTrace(f) };
    QArgumentTrace arArgumentTraces2[] = { QArgumentTrace(f2) };
    QCallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    QCallTrace callTrace2("int function2(float f)", arArgumentTraces2, 1);
    QCallStackTracer::Get()->AddTrace(callTrace);

    // [Execution]
    QCallStackTracer::Get()->AddTrace(callTrace2);
    
    // [Verification]
    QCallStackTracer::Get()->Dump();
    QAbstractCallStackTracePrinterMock* pPrinter = QCallStackTracer::Get()->GetPrinter()->As<QAbstractCallStackTracePrinterMock>();
    bool bPrintedTextContainsExpectedTrace = pPrinter->GetPrintedText().Contains(EXPECTED_TEXT, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bPrintedTextContainsExpectedTrace);
    
    // [Cleaning]
    QCallStackTracer::Get()->RemoveLastTrace();
    QCallStackTracer::Get()->RemoveLastTrace();
    pPrinter->ClearPrintedText();
}

/// <summary>
/// Checks that it removes the last trace only.
/// </summary>
QTEST_CASE ( RemoveLastTrace_RemovesTheLastTraceOnly_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    InitializeCallStackTracer_TestMethod();
    const string_q EXPECTED_TEXT("\
int function(int i, float f)\n\
  | -{0}i32=5\n\
  | -{1}f32=1\n\
End of call stack trace information.\n");
    int i = 5;
    float f = 1.0f;
    float f2 = 2.0f;
    QArgumentTrace arArgumentTraces[] = { QArgumentTrace(i), QArgumentTrace(f) };
    QArgumentTrace arArgumentTraces2[] = { QArgumentTrace(f2) };
    QCallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    QCallTrace callTrace2("int function2(float f)", arArgumentTraces2, 1);
    QCallStackTracer::Get()->AddTrace(callTrace);
    QCallStackTracer::Get()->AddTrace(callTrace2);

    // [Execution]
    QCallStackTracer::Get()->RemoveLastTrace();
    
    // [Verification]
    QCallStackTracer::Get()->Dump();
    QAbstractCallStackTracePrinterMock* pPrinter = QCallStackTracer::Get()->GetPrinter()->As<QAbstractCallStackTracePrinterMock>();
    bool bPrintedTextContainsExpectedTrace = pPrinter->GetPrintedText().Contains(EXPECTED_TEXT, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bPrintedTextContainsExpectedTrace);
    
    // [Cleaning]
    QCallStackTracer::Get()->RemoveLastTrace();
    pPrinter->ClearPrintedText();
}

/// <summary>
/// Checks that it deletes a call stack trace when it is empty.
/// </summary>
QTEST_CASE ( RemoveLastTrace_CallStackTraceIsDeletedWhenItIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    InitializeCallStackTracer_TestMethod();
    int i = 5;
    float f = 1.0f;
    QArgumentTrace arArgumentTraces[] = { QArgumentTrace(i), QArgumentTrace(f) };
    QCallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    QCallStackTracer::Get()->AddTrace(callTrace);

    // [Execution]
    QCallStackTracer::Get()->RemoveLastTrace();
    
    // [Verification]
    QCallStackTracer::Get()->Dump();
    QAbstractCallStackTracePrinterMock* pPrinter = QCallStackTracer::Get()->GetPrinter()->As<QAbstractCallStackTracePrinterMock>();
    bool bPrintedTextIsEmpty = pPrinter->GetPrintedText().IsEmpty();
    BOOST_CHECK(bPrintedTextIsEmpty);
}

// End - Test Suite: QCallStackTracer
QTEST_SUITE_END()
