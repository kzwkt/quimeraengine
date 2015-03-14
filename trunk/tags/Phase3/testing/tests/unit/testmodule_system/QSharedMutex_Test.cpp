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

// Note: Testing a mutex is so hard. Since Boost is used as underlying implementation and it has been already tested both by the dev team and many users, our testing effort is reduced

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "QSharedMutex.h"

#include "QThread.h"
#include "SQThisThread.h"

using Kinesis::QuimeraEngine::System::Threading::QSharedMutex;

class QSharedMutexTestClass
{
public:

    static void Reset()
    {
        sm_uThreadCounter = 0;
        sm_uSharedResource = 0;
        sm_bOneThreadAtATime = true;
    }

    static void FunctionExclusiveLock(unsigned int uCheckValue)
    {
        using Kinesis::QuimeraEngine::System::Threading::SQThisThread;
        using Kinesis::QuimeraEngine::System::Threading::QThread;
        using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

        QTimeSpan Pause50ms(0, 0, 0, 0, 50, 0, 0);

        SQThisThread::Sleep(Pause50ms);

        sm_mutex.Lock();

        sm_uSharedResource += uCheckValue;

        SQThisThread::Sleep(Pause50ms);

        sm_uSharedResource -= uCheckValue;

        sm_bOneThreadAtATime = sm_bOneThreadAtATime && sm_uSharedResource == 0;

        sm_mutex.Unlock();

        SQThisThread::Sleep(Pause50ms);

        --sm_uThreadCounter;
    }
    
    static void FunctionSharedLock(unsigned int uCheckValue)
    {
        using Kinesis::QuimeraEngine::System::Threading::SQThisThread;
        using Kinesis::QuimeraEngine::System::Threading::QThread;
        using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

        QTimeSpan Pause50ms(0, 0, 0, 0, 50, 0, 0);

        SQThisThread::Sleep(Pause50ms);

        sm_mutex.LockShared();

        sm_uSharedResource += uCheckValue;

        SQThisThread::Sleep(Pause50ms);

        sm_uSharedResource -= uCheckValue;

        sm_bOneThreadAtATime = sm_bOneThreadAtATime && sm_uSharedResource == 0;

        sm_mutex.UnlockShared();

        SQThisThread::Sleep(Pause50ms);

        --sm_uThreadCounter;
    }

    static unsigned int sm_uSharedResource;
    static bool sm_bOneThreadAtATime;
    static QSharedMutex sm_mutex;
    static unsigned int sm_uThreadCounter;
};

QSharedMutex QSharedMutexTestClass::sm_mutex;
unsigned int QSharedMutexTestClass::sm_uThreadCounter = 0;
unsigned int QSharedMutexTestClass::sm_uSharedResource;
bool QSharedMutexTestClass::sm_bOneThreadAtATime = true;


QTEST_SUITE_BEGIN( QSharedMutex_TestSuite )
    
/// <summary>
/// Checks that only one thread can own the mutex at a time.
/// </summary>
QTEST_CASE ( Lock_OnlyOneThreadOwnsTheMutexAtATime_Test )
{
    using Kinesis::QuimeraEngine::System::Threading::QThread;
    using Kinesis::QuimeraEngine::System::Threading::SQThisThread;
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;
    using Kinesis::QuimeraEngine::Common::QDelegate;

    // [Preparation]
    static const unsigned int NUMBER_OF_THREADS = 50U;
    QSharedMutexTestClass::Reset();
    QSharedMutexTestClass::sm_uThreadCounter = NUMBER_OF_THREADS;

    // [Execution]
    for(unsigned int uValue = 0; uValue < NUMBER_OF_THREADS; ++uValue)
    {
        QThread thread(QDelegate<void(unsigned int)>(QSharedMutexTestClass::FunctionExclusiveLock), uValue);
        thread.Detach();
    }
    
    // [Verification]
    while(QSharedMutexTestClass::sm_uThreadCounter > 0)
        SQThisThread::Yield();

    BOOST_CHECK(QSharedMutexTestClass::sm_bOneThreadAtATime);
}

/// <summary>
/// Checks that many threads can own the shared mutex at a time.
/// </summary>
QTEST_CASE ( LockShared_ManyThreadsOwnTheMutexAtATime_Test )
{
    using Kinesis::QuimeraEngine::System::Threading::QThread;
    using Kinesis::QuimeraEngine::System::Threading::SQThisThread;
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;
    using Kinesis::QuimeraEngine::Common::QDelegate;

    // [Preparation]
    static const unsigned int NUMBER_OF_THREADS = 50U;
    QSharedMutexTestClass::sm_uThreadCounter = NUMBER_OF_THREADS;
    QSharedMutexTestClass::sm_bOneThreadAtATime = true;
    const bool EXPECTED_VALUE = false;

    // [Execution]
    for(unsigned int uValue = 0; uValue < NUMBER_OF_THREADS; ++uValue)
    {
        QThread thread(QDelegate<void(unsigned int)>(QSharedMutexTestClass::FunctionSharedLock), uValue);
        thread.Detach();
    }
    
    // [Verification]
    while(QSharedMutexTestClass::sm_uThreadCounter > 0)
        SQThisThread::Yield();

    BOOST_CHECK_EQUAL(QSharedMutexTestClass::sm_bOneThreadAtATime, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns True when the mutex was not locked.
/// </summary>
QTEST_CASE ( TryLock_ReturnsTrueWhenMutexWasNotAlreadyLocked_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = true;
    QSharedMutex mutex;

    // [Execution]
    bool bResult = mutex.TryLock();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);

    // [Cleaning]
    mutex.Unlock();
}

/// <summary>
/// Checks that it returns False when the mutex was locked in an exclusive way.
/// </summary>
QTEST_CASE ( TryLock_ReturnsFalseWhenMutexWasLockedExclusive_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = false;
    QSharedMutex mutex;
    mutex.Lock();

    // [Execution]
    bool bResult = mutex.TryLock();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);

    // [Cleaning]
    mutex.Unlock();
}

/// <summary>
/// Checks that it returns False when the mutex was locked in a shared way.
/// </summary>
QTEST_CASE ( TryLock_ReturnsFalseWhenMutexWasAlreadyLockedShared_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = false;
    QSharedMutex mutex;
    mutex.LockShared();

    // [Execution]
    bool bResult = mutex.TryLock();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);

    // [Cleaning]
    mutex.UnlockShared();
}

/// <summary>
/// Checks that it returns True when the mutex was locked in a shared way.
/// </summary>
QTEST_CASE ( TryLockShared_ReturnsTrueWhenMutexWasAlreadyLockedShared_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = true;
    QSharedMutex mutex;
    mutex.LockShared();

    // [Execution]
    bool bResult = mutex.TryLockShared();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);

    // [Cleaning]
    mutex.UnlockShared();
    mutex.UnlockShared();
}

/// <summary>
/// Checks that it returns True when the mutex was was not locked.
/// </summary>
QTEST_CASE ( TryLockShared_ReturnsTrueWhenMutexWasNotLocked_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = true;
    QSharedMutex mutex;

    // [Execution]
    bool bResult = mutex.TryLockShared();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);

    // [Cleaning]
    mutex.UnlockShared();
}

/// <summary>
/// Checks that it returns False when the mutex was locked in an exclusive way.
/// </summary>
QTEST_CASE ( TryLockShared_ReturnsFalseWhenMutexWasLockedExclusive_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = false;
    QSharedMutex mutex;
    mutex.Lock();

    // [Execution]
    bool bResult = mutex.TryLockShared();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);

    // [Cleaning]
    mutex.Unlock();
}

// End - Test Suite: QSharedMutex
QTEST_SUITE_END()
