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

#include "QThread.h"

#include "QStopwatch.h"
#include "EQComparisonType.h"
#include "QAssertException.h"
#include "SQThisThread.h"

using Kinesis::QuimeraEngine::System::Threading::QThread;
using Kinesis::QuimeraEngine::Common::QDelegate;
using Kinesis::QuimeraEngine::Common::Exceptions::QAssertException;

// Class whose methods are to be used in the tests of QThread
class QThreadTestClass
{
public:

    int m_nMember;

    static bool sm_bFunction0Called;
    static bool sm_bFunction1Called;
    static bool sm_bFunction2Called;
    static bool sm_bFunction3Called;
    static bool sm_bFunction4Called;
    static bool sm_bFunction5Called;
    static bool sm_bFunction6Called;
    static bool sm_bFunction7Called;
    static bool sm_bFunction8Called;
    static bool sm_bFunctionInterrupted;

    QThreadTestClass(int param) : m_nMember(param)
    {
    }

    void SetMember(int param)
    {
        m_nMember = param;
    }

    static void ResetFlags()
    {
        sm_bFunction0Called = false;
        sm_bFunction1Called = false;
        sm_bFunction2Called = false;
        sm_bFunction3Called = false;
        sm_bFunction4Called = false;
        sm_bFunction5Called = false;
        sm_bFunction6Called = false;
        sm_bFunction7Called = false;
        sm_bFunction8Called = false;
        sm_bFunctionInterrupted = false;
    }

    static void Wait(unsigned int milliseconds)
    {
        using Kinesis::QuimeraEngine::System::Threading::SQThisThread;
        using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

        SQThisThread::Sleep(QTimeSpan(0, 0, 0, 0, milliseconds, 0, 0));
    }

    static void FunctionToBeInterrupted() try
    {
        QDelegate<void()> function(&QThreadTestClass::WorkSomeTime);

        QThread thread(function); // The function is assumed to take enough time

        try
        {
            thread.Join();
        }
        catch(const QAssertException&)
        {
            sm_bFunctionInterrupted = true;
        }
    }
    catch(...)
    {
        // This block silences the exception thrown in the destructor of the thread instance, don't remove it this time
    }
    
#ifdef QE_COMPILER_GCC
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-variable"
#endif

    static void WorkSomeTime()
    {
        for(int i = 1; i < 1000000; ++i)
        {
            for(int ii = 1; ii < 50000; ++ii)
            {
                int x = ii / i;
            }
        }
    }
    
#ifdef QE_COMPILER_GCC
    #pragma GCC diagnostic pop
#endif

    static void FunctionWith0Params()
    {
        sm_bFunction0Called = true;
    }
    
    static void FunctionWith1Params(int)
    {
        sm_bFunction1Called = true;
    }
    
    static void FunctionWith2Params(int, int)
    {
        sm_bFunction2Called = true;
    }
    
    static void FunctionWith3Params(int, int, int)
    {
        sm_bFunction3Called = true;
    }
    
    static void FunctionWith4Params(int, int, int, int)
    {
        sm_bFunction4Called = true;
    }
    
    static void FunctionWith5Params(int, int, int, int, int)
    {
        sm_bFunction5Called = true;
    }
    
    static void FunctionWith6Params(int, int, int, int, int, int)
    {
        sm_bFunction6Called = true;
    }
    
    static void FunctionWith7Params(int, int, int, int, int, int, int)
    {
        sm_bFunction7Called = true;
    }
    
    static void FunctionWith8Params(int, int, int, int, int, int, int, int)
    {
        sm_bFunction8Called = true;
    }
};

bool QThreadTestClass::sm_bFunction0Called = false;
bool QThreadTestClass::sm_bFunction1Called = false;
bool QThreadTestClass::sm_bFunction2Called = false;
bool QThreadTestClass::sm_bFunction3Called = false;
bool QThreadTestClass::sm_bFunction4Called = false;
bool QThreadTestClass::sm_bFunction5Called = false;
bool QThreadTestClass::sm_bFunction6Called = false;
bool QThreadTestClass::sm_bFunction7Called = false;
bool QThreadTestClass::sm_bFunction8Called = false;
bool QThreadTestClass::sm_bFunctionInterrupted = false;



QTEST_SUITE_BEGIN( QThread_TestSuite )

/// <summary>
/// Checks that the input function is called.
/// </summary>
QTEST_CASE ( Constructor1_FunctionIsCalled_Test )
{
    // [Preparation]
    QThreadTestClass::ResetFlags();
    QDelegate<void()> function(&QThreadTestClass::FunctionWith0Params);

    // [Execution]
    QThread thread(function);

    // [Verification]
    thread.Join();

    BOOST_CHECK(QThreadTestClass::sm_bFunction0Called);
}

/// <summary>
/// Checks that the input function is called.
/// </summary>
QTEST_CASE ( Constructor2_FunctionIsCalled_Test )
{
    // [Preparation]
    QThreadTestClass::ResetFlags();
    QDelegate<void(int)> function(&QThreadTestClass::FunctionWith1Params);
    int p1 = 0;

    // [Execution]
    QThread thread(function, p1);

    // [Verification]
    thread.Join();

    BOOST_CHECK(QThreadTestClass::sm_bFunction1Called);
}

/// <summary>
/// Checks that the correct method of an object is called.
/// </summary>
QTEST_CASE ( Constructor2_MethodOfCorrectObjectIsCalled_Test )
{
    // [Preparation]
    QThreadTestClass::ResetFlags();
    QThreadTestClass object(0);
    QDelegate<void(int)> function(&object, &QThreadTestClass::SetMember);
    const int EXPECTED_VALUE = 1;

    // [Execution]
    QThread thread(function, EXPECTED_VALUE);

    // [Verification]
    thread.Join();

    BOOST_CHECK_EQUAL(object.m_nMember, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the input function is called.
/// </summary>
QTEST_CASE ( Constructor3_FunctionIsCalled_Test )
{
    // [Preparation]
    QThreadTestClass::ResetFlags();
    QDelegate<void(int, int)> function(&QThreadTestClass::FunctionWith2Params);
    int p1 = 0;
    int p2 = 0;

    // [Execution]
    QThread thread(function, p1, p2);

    // [Verification]
    thread.Join();

    BOOST_CHECK(QThreadTestClass::sm_bFunction2Called);
}

/// <summary>
/// Checks that the input function is called.
/// </summary>
QTEST_CASE ( Constructor4_FunctionIsCalled_Test )
{
    // [Preparation]
    QThreadTestClass::ResetFlags();
    QDelegate<void(int, int, int)> function(&QThreadTestClass::FunctionWith3Params);
    int p1 = 0;
    int p2 = 0;
    int p3 = 0;

    // [Execution]
    QThread thread(function, p1, p2, p3);

    // [Verification]
    thread.Join();

    BOOST_CHECK(QThreadTestClass::sm_bFunction3Called);
}

/// <summary>
/// Checks that the input function is called.
/// </summary>
QTEST_CASE ( Constructor5_FunctionIsCalled_Test )
{
    // [Preparation]
    QThreadTestClass::ResetFlags();
    QDelegate<void(int, int, int, int)> function(&QThreadTestClass::FunctionWith4Params);
    int p1 = 0;
    int p2 = 0;
    int p3 = 0;
    int p4 = 0;

    // [Execution]
    QThread thread(function, p1, p2, p3, p4);

    // [Verification]
    thread.Join();

    BOOST_CHECK(QThreadTestClass::sm_bFunction4Called);
}

/// <summary>
/// Checks that the input function is called.
/// </summary>
QTEST_CASE ( Constructor6_FunctionIsCalled_Test )
{
    // [Preparation]
    QThreadTestClass::ResetFlags();
    QDelegate<void(int, int, int, int, int)> function(&QThreadTestClass::FunctionWith5Params);
    int p1 = 0;
    int p2 = 0;
    int p3 = 0;
    int p4 = 0;
    int p5 = 0;

    // [Execution]
    QThread thread(function, p1, p2, p3, p4, p5);

    // [Verification]
    thread.Join();

    BOOST_CHECK(QThreadTestClass::sm_bFunction5Called);
}

/// <summary>
/// Checks that the input function is called.
/// </summary>
QTEST_CASE ( Constructor7_FunctionIsCalled_Test )
{
    // [Preparation]
    QThreadTestClass::ResetFlags();
    QDelegate<void(int, int, int, int, int, int)> function(&QThreadTestClass::FunctionWith6Params);
    int p1 = 0;
    int p2 = 0;
    int p3 = 0;
    int p4 = 0;
    int p5 = 0;
    int p6 = 0;

    // [Execution]
    QThread thread(function, p1, p2, p3, p4, p5, p6);

    // [Verification]
    thread.Join();

    BOOST_CHECK(QThreadTestClass::sm_bFunction6Called);
}

/// <summary>
/// Checks that the input function is called.
/// </summary>
QTEST_CASE ( Constructor8_FunctionIsCalled_Test )
{
    // [Preparation]
    QThreadTestClass::ResetFlags();
    QDelegate<void(int, int, int, int, int, int, int)> function(&QThreadTestClass::FunctionWith7Params);
    int p1 = 0;
    int p2 = 0;
    int p3 = 0;
    int p4 = 0;
    int p5 = 0;
    int p6 = 0;
    int p7 = 0;

    // [Execution]
    QThread thread(function, p1, p2, p3, p4, p5, p6, p7);

    // [Verification]
    thread.Join();

    BOOST_CHECK(QThreadTestClass::sm_bFunction7Called);
}

/// <summary>
/// Checks that the input function is called.
/// </summary>
QTEST_CASE ( Constructor9_FunctionIsCalled_Test )
{
    // [Preparation]
    QThreadTestClass::ResetFlags();
    QDelegate<void(int, int, int, int, int, int, int, int)> function(&QThreadTestClass::FunctionWith8Params);
    int p1 = 0;
    int p2 = 0;
    int p3 = 0;
    int p4 = 0;
    int p5 = 0;
    int p6 = 0;
    int p7 = 0;
    int p8 = 0;

    // [Execution]
    QThread thread(function, p1, p2, p3, p4, p5, p6, p7, p8);

    // [Verification]
    thread.Join();

    BOOST_CHECK(QThreadTestClass::sm_bFunction8Called);
}

/// <summary>
/// Checks that no exceptions are thrown when the thread already finished.
/// </summary>
QTEST_CASE ( Destructor_NothingHappensWhenThreadWasNotRunning_Test )
{
    // [Preparation]
    const bool NO_EXCEPTIONS_THROWN = true;
    QDelegate<void()> function(&QThreadTestClass::FunctionWith0Params);
    {
        QThread thread(function);
        thread.Join();
    // [Execution]
    } // Destructor called

    // [Verification]
    BOOST_CHECK(NO_EXCEPTIONS_THROWN);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the instance is destroyed before the thread has finished.
/// </summary>
QTEST_CASE ( Destructor_AssertionFailsWhenInstanceIsDestroyedBeforeTheThreadHasFinished_Test )
{
    // [Preparation]
    QDelegate<void()> function(&QThreadTestClass::FunctionWith0Params);
    bool bAssertionFailed = false;

    try
    {
        QThread thread(function); // The function is assumed to take enough time

    // [Execution]
    } // Destructor called
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the thread is not running.
/// </summary>
QTEST_CASE ( Interrupt_AssertionFailsWhenThreadIsNotRunning_Test )
{
    // [Preparation]
    QDelegate<void(unsigned int)> function(&QThreadTestClass::Wait);
    const unsigned int WAIT_TIME = 100;
    bool bAssertionFailed = false;

    try
    {
        QThread thread(function, WAIT_TIME); // The function is assumed to take enough time
        thread.Join();
    // [Execution]
        thread.Interrupt();
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that this thread waits until the other thread has finished.
/// </summary>
QTEST_CASE ( Join_WaitsUntilThreadFinishes_Test )
{
    using Kinesis::QuimeraEngine::System::Timing::QStopwatch;

    // [Preparation]
    QDelegate<void(unsigned int)> function(&QThreadTestClass::Wait);
    const unsigned int WAIT_TIME = 600;

    QStopwatch elapsedTime;
    elapsedTime.Set();
    QThread thread(function, WAIT_TIME);

    // [Execution]
    thread.Join();

    // [Verification]
    u64_q uMilliseconds = elapsedTime.GetElapsedTimeAsInteger() / 1000000ULL;
    BOOST_CHECK(uMilliseconds >= WAIT_TIME - 10U); // 10 ms tolerance
    BOOST_CHECK(uMilliseconds < (WAIT_TIME + 10U)); // 10 ms tolerance
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the thread is joined after it has been interrupted.
/// </summary>
QTEST_CASE ( Join_AssertionFailsWhenThreadIsJoinedAfterItHasBeenInterrupted_Test )
{
    // [Preparation]
    QDelegate<void()> function(&QThreadTestClass::FunctionToBeInterrupted);
    QThreadTestClass::ResetFlags();

    // [Execution]
    QThread thread(function); // The function is assumed to take enough time
    thread.Interrupt();
    thread.Join();

    // [Verification]
    BOOST_CHECK(QThreadTestClass::sm_bFunctionInterrupted);
}

#endif

/// <summary>
/// Checks that the output format is what expected.
/// </summary>
QTEST_CASE ( ToString_FormatIsWhatExpected_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_PART1("Thread(");
    const string_q EXPECTED_PART2(")");
    QDelegate<void(unsigned int)> function(&QThreadTestClass::Wait);
    const unsigned int WAIT_TIME = 200;
    QThread thread(function, WAIT_TIME);

    // [Execution]
    string_q strResult = thread.ToString();

    // [Verification]
    thread.Join();
    bool bFormatIsWhatExpected = strResult.IndexOf(EXPECTED_PART1, EQComparisonType::E_BinaryCaseSensitive) == 0;
    bFormatIsWhatExpected = bFormatIsWhatExpected && strResult.IndexOf(EXPECTED_PART2, EQComparisonType::E_BinaryCaseSensitive) == scast_q(strResult.GetLength() - 1U, int);
    BOOST_CHECK(bFormatIsWhatExpected);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the method is called after the thread has stopped.
/// </summary>
QTEST_CASE ( ToString_AssertionFailsWhenMethodIsCalledAfterThreadHasStopped_Test )
{
    // [Preparation]
    QDelegate<void()> function(&QThreadTestClass::FunctionWith0Params);
    QThread thread(function);
    thread.Join();
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        thread.ToString();
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that no error occurs when the method is called.
/// </summary>
QTEST_CASE ( Detach_NoErrorOccursWhenCalled_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    QDelegate<void(unsigned int)> function(&QThreadTestClass::Wait);
    const unsigned int WAIT_TIME = 200;
    QThread thread(function, WAIT_TIME);

    // [Execution]
    thread.Detach();

    // [Verification]
    const bool NO_ERROR_OCCURRED = true;
    BOOST_CHECK(NO_ERROR_OCCURRED);
}

/// <summary>
/// Checks that it returns True when the thread is still running.
/// </summary>
QTEST_CASE ( IsAlive_ReturnsTrueWhenThreadIsRunning_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const bool EXPECTED_RESULT = true;
    QDelegate<void(unsigned int)> function(&QThreadTestClass::Wait);
    const unsigned int WAIT_TIME = 200;
    QThread thread(function, WAIT_TIME);

    // [Execution]
    bool bIsAlive = thread.IsAlive();
    thread.Join();

    // [Verification]
    BOOST_CHECK_EQUAL(bIsAlive, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the thread is not running.
/// </summary>
QTEST_CASE ( IsAlive_ReturnsFalseWhenThreadIsNotRunning_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const bool EXPECTED_RESULT = false;
    QDelegate<void()> function(&QThreadTestClass::FunctionWith0Params);
    QThread thread(function);
    thread.Join();

    // [Execution]
    bool bIsAlive = thread.IsAlive();

    // [Verification]
    BOOST_CHECK_EQUAL(bIsAlive, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the thread was interrupted.
/// </summary>
QTEST_CASE ( IsInterrupted_ReturnsTrueWhenThreadWasInterrupted_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const bool EXPECTED_RESULT = true;
    QDelegate<void(unsigned int)> function(&QThreadTestClass::Wait);
    const unsigned int WAIT_TIME = 300;
    QThread thread(function, WAIT_TIME);
    thread.Interrupt();

    // [Execution]
    bool bIsInterrupted = thread.IsInterrupted();
    thread.Join();

    // [Verification]
    BOOST_CHECK_EQUAL(bIsInterrupted, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the thread was not interrupted.
/// </summary>
QTEST_CASE ( IsInterrupted_ReturnsFalseWhenThreadWasNotInterrupted_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const bool EXPECTED_RESULT = false;
    QDelegate<void(unsigned int)> function(&QThreadTestClass::Wait);
    const unsigned int WAIT_TIME = 200;
    QThread thread(function, WAIT_TIME);

    // [Execution]
    bool bIsInterrupted = thread.IsInterrupted();
    thread.Join();

    // [Verification]
    BOOST_CHECK_EQUAL(bIsInterrupted, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the method is called after the thread has stopped.
/// </summary>
QTEST_CASE ( GetId_AssertionFailsWhenMethodIsCalledAfterThreadHasStopped_Test )
{
    // [Preparation]
    QDelegate<void()> function(&QThreadTestClass::FunctionWith0Params);
    QThread thread(function);
    thread.Join();
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        thread.GetId();
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the method is called after the thread has stopped.
/// </summary>
QTEST_CASE ( GetNativeHandle_AssertionFailsWhenMethodIsCalledAfterThreadHasStopped_Test )
{
    // [Preparation]
    QDelegate<void()> function(&QThreadTestClass::FunctionWith0Params);
    QThread thread(function);
    thread.Join();
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        thread.GetNativeHandle();
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that the priority is correctly set when it is the Lowest.
/// </summary>
QTEST_CASE ( SetPriority_PriorityIsCorrectlySetWhenItIsLowest_Test )
{
    using Kinesis::QuimeraEngine::System::Threading::EQThreadPriority;

    // [Preparation]
    QDelegate<void(unsigned int)> function(&QThreadTestClass::Wait);
    unsigned int uWaitTime = 100;
    QThread thread(function, uWaitTime);

    const EQThreadPriority INPUT_PRIORITY = EQThreadPriority::E_Lowest;
#if defined(QE_OS_WINDOWS) || defined(QE_OS_MAC)
    const EQThreadPriority EXPECTED_PRIORITY = EQThreadPriority::E_Lowest;
#elif defined(QE_OS_LINUX)
    const EQThreadPriority EXPECTED_PRIORITY = EQThreadPriority::E_Normal;
#endif

    // [Execution]
    thread.SetPriority(INPUT_PRIORITY);

    // [Verification]
    EQThreadPriority ePriority = thread.GetPriority();
    thread.Join();
    BOOST_CHECK(ePriority == EXPECTED_PRIORITY);
}

/// <summary>
/// Checks that the priority is correctly set when it is Low.
/// </summary>
QTEST_CASE ( SetPriority_PriorityIsCorrectlySetWhenItIsLow_Test )
{
    using Kinesis::QuimeraEngine::System::Threading::EQThreadPriority;

    // [Preparation]
    QDelegate<void(unsigned int)> function(&QThreadTestClass::Wait);
    unsigned int uWaitTime = 100;
    QThread thread(function, uWaitTime);

    const EQThreadPriority INPUT_PRIORITY = EQThreadPriority::E_Low;
#if defined(QE_OS_WINDOWS) || defined(QE_OS_MAC)
    const EQThreadPriority EXPECTED_PRIORITY = EQThreadPriority::E_Low;
#elif defined(QE_OS_LINUX)
    const EQThreadPriority EXPECTED_PRIORITY = EQThreadPriority::E_Normal;
#endif

    // [Execution]
    thread.SetPriority(INPUT_PRIORITY);

    // [Verification]
    EQThreadPriority ePriority = thread.GetPriority();
    thread.Join();
    BOOST_CHECK(ePriority == EXPECTED_PRIORITY);
}

/// <summary>
/// Checks that the priority is correctly set when it is Normal.
/// </summary>
QTEST_CASE ( SetPriority_PriorityIsCorrectlySetWhenItIsNormal_Test )
{
    using Kinesis::QuimeraEngine::System::Threading::EQThreadPriority;

    // [Preparation]
    QDelegate<void(unsigned int)> function(&QThreadTestClass::Wait);
    unsigned int uWaitTime = 100;
    QThread thread(function, uWaitTime);

    const EQThreadPriority INPUT_PRIORITY = EQThreadPriority::E_Normal;

    // [Execution]
    thread.SetPriority(INPUT_PRIORITY);

    // [Verification]
    EQThreadPriority ePriority = thread.GetPriority();
    thread.Join();
    BOOST_CHECK(ePriority == INPUT_PRIORITY);
}

/// <summary>
/// Checks that the priority is correctly set when it is High.
/// </summary>
QTEST_CASE ( SetPriority_PriorityIsCorrectlySetWhenItIsHigh_Test )
{
    using Kinesis::QuimeraEngine::System::Threading::EQThreadPriority;

    // [Preparation]
    QDelegate<void(unsigned int)> function(&QThreadTestClass::Wait);
    unsigned int uWaitTime = 100;
    QThread thread(function, uWaitTime);

    const EQThreadPriority INPUT_PRIORITY = EQThreadPriority::E_High;
#if defined(QE_OS_WINDOWS) || defined(QE_OS_MAC)
    const EQThreadPriority EXPECTED_PRIORITY = EQThreadPriority::E_High;
#elif defined(QE_OS_LINUX)
    const EQThreadPriority EXPECTED_PRIORITY = EQThreadPriority::E_Normal;
#endif

    // [Execution]
    thread.SetPriority(INPUT_PRIORITY);

    // [Verification]
    EQThreadPriority ePriority = thread.GetPriority();
    thread.Join();
    BOOST_CHECK(ePriority == EXPECTED_PRIORITY);
}

/// <summary>
/// Checks that the priority is correctly set when it is the Highest.
/// </summary>
QTEST_CASE ( SetPriority_PriorityIsCorrectlySetWhenItIsHighest_Test )
{
    using Kinesis::QuimeraEngine::System::Threading::EQThreadPriority;

    // [Preparation]
    QDelegate<void(unsigned int)> function(&QThreadTestClass::Wait);
    unsigned int uWaitTime = 100;
    QThread thread(function, uWaitTime);

    const EQThreadPriority INPUT_PRIORITY = EQThreadPriority::E_Highest;
#if defined(QE_OS_WINDOWS) || defined(QE_OS_MAC)
    const EQThreadPriority EXPECTED_PRIORITY = EQThreadPriority::E_Highest;
#elif defined(QE_OS_LINUX)
    const EQThreadPriority EXPECTED_PRIORITY = EQThreadPriority::E_Normal;
#endif

    // [Execution]
    thread.SetPriority(INPUT_PRIORITY);

    // [Verification]
    EQThreadPriority ePriority = thread.GetPriority();
    thread.Join();
    BOOST_CHECK(ePriority == EXPECTED_PRIORITY);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the method is called after the thread has stopped.
/// </summary>
QTEST_CASE ( SetPriority_AssertionFailsWhenMethodIsCalledAfterThreadHasStopped_Test )
{
    using Kinesis::QuimeraEngine::System::Threading::EQThreadPriority;

    // [Preparation]
    QDelegate<void()> function(&QThreadTestClass::FunctionWith0Params);
    QThread thread(function);
    thread.Join();
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        thread.SetPriority(EQThreadPriority::E_Normal);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that the priority is correctly obtained.
/// </summary>
QTEST_CASE ( GetPriority_PriorityIsCorrectlyObtained_Test )
{
    using Kinesis::QuimeraEngine::System::Threading::EQThreadPriority;

    // [Preparation]
    QDelegate<void(unsigned int)> function(&QThreadTestClass::Wait);
    unsigned int uWaitTime = 100;
    QThread thread(function, uWaitTime);

    // [Execution]
    EQThreadPriority ePriority = thread.GetPriority();

    // [Verification]
    thread.Join();
    BOOST_CHECK(ePriority == EQThreadPriority::E_Lowest ||
                ePriority == EQThreadPriority::E_Low    ||
                ePriority == EQThreadPriority::E_Normal ||
                ePriority == EQThreadPriority::E_High   ||
                ePriority == EQThreadPriority::E_Highest);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the method is called after the thread has stopped.
/// </summary>
QTEST_CASE ( GetPriority_AssertionFailsWhenMethodIsCalledAfterThreadHasStopped_Test )
{
    using Kinesis::QuimeraEngine::System::Threading::EQThreadPriority;

    // [Preparation]
    QDelegate<void()> function(&QThreadTestClass::FunctionWith0Params);
    QThread thread(function);
    thread.Join();
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        thread.GetPriority();
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

// End - Test Suite: QThread
QTEST_SUITE_END()
