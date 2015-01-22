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

#include "QScopedCallTraceNotifier.h"

#include "QCallStackTracer.h"
#include "QAbstractCallStackTracePrinterMock.h"
#include "QCallStackTracePlainTextFormatter.h"
#include "EQComparisonType.h"
using Kinesis::QuimeraEngine::System::Diagnosis::QScopedCallTraceNotifier;
using Kinesis::QuimeraEngine::System::Diagnosis::QCallTrace;
using Kinesis::QuimeraEngine::System::Diagnosis::QCallStackTracer;
using Kinesis::QuimeraEngine::System::Diagnosis::QArgumentTrace;
using Kinesis::QuimeraEngine::System::Diagnosis::QCallStackTracePlainTextFormatter;
using Kinesis::QuimeraEngine::System::Diagnosis::Test::QAbstractCallStackTracePrinterMock;
using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;


QTEST_SUITE_BEGIN( QScopedCallTraceNotifier_TestSuite )

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
/// Checks that a trace is added to the call stack trace.
/// </summary>
QTEST_CASE ( Constructor_TraceIsAdded_Test )
{
    InitializeCallStackTracer_TestMethod();
    const string_q EXPECTED_TEXT("\
void function(int i)\n\
  | -{0}i32=2\n");

    // [Preparation]
    int i = 2;
    QArgumentTrace argument(i);
    QCallTrace trace("void function(int i)", &argument, 1);

    // [Execution]
    QScopedCallTraceNotifier notifier(trace);

    // [Verification]
    QCallStackTracer::Get()->Dump();
    QAbstractCallStackTracePrinterMock* pPrinter = QCallStackTracer::Get()->GetPrinter().get()->As<QAbstractCallStackTracePrinterMock>();
    string_q strPrintedText = pPrinter->GetPrintedText();

    bool bPrintedTextContainsExpectedTrace = pPrinter->GetPrintedText().Contains(EXPECTED_TEXT, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bPrintedTextContainsExpectedTrace);

    // [Cleaning]
    pPrinter->ClearPrintedText();
}

/// <summary>
/// Checks that the last trace is removed from the call stack tracer.
/// </summary>
QTEST_CASE ( Destructor_TraceIsRemoved_Test )
{
    InitializeCallStackTracer_TestMethod();
    const string_q EXPECTED_TEXT("");

    // [Preparation]
    int i = 2;
    QArgumentTrace argument(i);
    QCallTrace trace("void function(int i)", &argument, 1);
    {
        QScopedCallTraceNotifier notifier(trace);

    // [Execution]
    } // Destructor is called

    // [Verification]
    QCallStackTracer::Get()->Dump();
    QAbstractCallStackTracePrinterMock* pPrinter = QCallStackTracer::Get()->GetPrinter().get()->As<QAbstractCallStackTracePrinterMock>();
    string_q strPrintedText = pPrinter->GetPrintedText();

    BOOST_CHECK(strPrintedText == EXPECTED_TEXT);

    // [Cleaning]
    pPrinter->ClearPrintedText();
}

// End - Test Suite: QScopedCallTraceNotifier
QTEST_SUITE_END()
