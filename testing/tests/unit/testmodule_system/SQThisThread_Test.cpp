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

// Note: Several methods are not testable since it's not possible to have a reference value or to measure the result of their execution

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "SQThisThread.h"

#include "QStopwatch.h"
#include "EQComparisonType.h"

using Kinesis::QuimeraEngine::System::Threading::SQThisThread;
using Kinesis::QuimeraEngine::System::Threading::QThread;

// Class whose methods are to be used in the tests of SQThisThread
class SQThisThreadTestClass
{
public:

    static bool sm_bFunctionInterrupted;

    static void ResetFlags()
    {
        sm_bFunctionInterrupted = false;
    }

    static void FunctionToBeInterrupted()
    {
        using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;
        
        // Waits for a little amount of time
        int i = 0;
        while(i < 1000000)
            i = i + i - i * 10 + 10;

        sm_bFunctionInterrupted = SQThisThread::IsInterrupted();
    }
};

bool SQThisThreadTestClass::sm_bFunctionInterrupted = false;



QTEST_SUITE_BEGIN( SQThisThread_TestSuite )
    
/// <summary>
/// Checks that no error ocurrs when it is called.
/// </summary>
QTEST_CASE ( Yield_NoErrorOccurs_Test )
{
    // [Preparation]
    const bool NO_ERRORS_OCCURRED = true;

    // [Execution]
    SQThisThread::Yield();

    // [Verification]
    BOOST_CHECK(NO_ERRORS_OCCURRED);
}

/// <summary>
/// Checks that the thread sleeps for the expected time.
/// </summary>
QTEST_CASE ( Sleep_ThreadSleepsForTheExpectedTime_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;
    using Kinesis::QuimeraEngine::System::Timing::QStopwatch;

    // [Preparation]
    const QTimeSpan EXPECTED_TIME(0, 0, 0, 0, 500, 0 ,0); // ms
    QStopwatch timer;
    timer.Set();

    // [Execution]
    SQThisThread::Sleep(EXPECTED_TIME);

    // [Verification]
    QTimeSpan ellapsedTime = timer.GetElapsedTimeAsTimeSpan();
    const QTimeSpan TOLERANCE(0, 0, 0, 0, 10, 0, 0); // ms
    BOOST_CHECK(ellapsedTime >= EXPECTED_TIME - TOLERANCE && ellapsedTime < EXPECTED_TIME + TOLERANCE);
}

/// <summary>
/// Checks that the output format is what expected.
/// </summary>
QTEST_CASE ( ToString_FormatIsWhatExpected_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_PART1("Thread(");
    const string_q EXPECTED_PART2(")");

    // [Execution]
    string_q strResult = SQThisThread::ToString();

    // [Verification]
    bool bFormatIsWhatExpected = strResult.IndexOf(EXPECTED_PART1, EQComparisonType::E_BinaryCaseSensitive) == 0;
    bFormatIsWhatExpected = bFormatIsWhatExpected && strResult.IndexOf(EXPECTED_PART2, EQComparisonType::E_BinaryCaseSensitive) == scast_q(strResult.GetLength() - 1U, int);
    BOOST_CHECK(bFormatIsWhatExpected);
}

/// <summary>
/// Checks that it returns True when the thread was interrupted.
/// </summary>
QTEST_CASE ( IsInterrupted_ReturnsTrueWhenThreadWasInterrupted_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;
    using Kinesis::QuimeraEngine::Common::QDelegate;

    // [Preparation]
    const bool EXPECTED_RESULT = true;
    QDelegate<void()> function(&SQThisThreadTestClass::FunctionToBeInterrupted);
    QThread thread(function);
    SQThisThreadTestClass::ResetFlags();
    thread.Interrupt();

    // [Execution]
    thread.Join();

    // [Verification]
    bool bIsInterrupted = SQThisThreadTestClass::sm_bFunctionInterrupted;
    BOOST_CHECK_EQUAL(bIsInterrupted, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the thread was not interrupted.
/// </summary>
QTEST_CASE ( IsInterrupted_ReturnsFalseWhenThreadWasNotInterrupted_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;
    using Kinesis::QuimeraEngine::Common::QDelegate;

    // [Preparation]
    const bool EXPECTED_RESULT = false;
    QDelegate<void()> function(&SQThisThreadTestClass::FunctionToBeInterrupted);
    QThread thread(function);
    SQThisThreadTestClass::ResetFlags();

    // [Execution]
    thread.Join();

    // [Verification]
    bool bIsInterrupted = SQThisThreadTestClass::sm_bFunctionInterrupted;
    BOOST_CHECK_EQUAL(bIsInterrupted, EXPECTED_RESULT);
}

/// <summary>
/// Checks that no error ocurrs when it is called.
/// </summary>
QTEST_CASE ( GetId_NoErrorOccurs_Test )
{
    // [Preparation]
    const bool NO_ERRORS_OCCURRED = true;

    // [Execution]
    SQThisThread::GetId();

    // [Verification]
    BOOST_CHECK(NO_ERRORS_OCCURRED);
}

/// <summary>
/// Checks that no error ocurrs when it is called.
/// </summary>
QTEST_CASE ( GetNativeHandle_NoErrorOccurs_Test )
{
    // [Preparation]
    const bool NO_ERRORS_OCCURRED = true;

    // [Execution]
    SQThisThread::GetNativeHandle();

    // [Verification]
    BOOST_CHECK(NO_ERRORS_OCCURRED);
}


// End - Test Suite: SQThisThread
QTEST_SUITE_END()
