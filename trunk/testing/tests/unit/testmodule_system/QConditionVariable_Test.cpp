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

#include "QConditionVariable.h"

#include "QThread.h"
#include "SQThisThread.h"
#include "QMutex.h"
#include "QScopedExclusiveLock.h"

using Kinesis::QuimeraEngine::System::Threading::QConditionVariable;
using Kinesis::QuimeraEngine::System::Threading::QMutex;
using Kinesis::QuimeraEngine::System::Threading::QThread;
using Kinesis::QuimeraEngine::System::Threading::SQThisThread;
using Kinesis::QuimeraEngine::Common::QDelegate;

class QConditionVariableTestClass
{
public:

    static void Reset()
    {
        sm_uThreadCounterAfterWait = 0;
        sm_uThreadCounterBeforeWait = 0;
        sm_bLockIsLockedAfterWait = false;
    }

    static void WaitingFunction()
    {
        using Kinesis::QuimeraEngine::System::Threading::QScopedExclusiveLock;

        QScopedExclusiveLock<QMutex> lock(sm_mutex);

        ++sm_uThreadCounterBeforeWait;

        sm_conditionVariable.Wait(lock);

        sm_bLockIsLockedAfterWait = lock.IsOwner();

        ++sm_uThreadCounterAfterWait;
    }

    static bool sm_bLockIsLockedAfterWait;
    static unsigned int sm_uThreadCounterBeforeWait;
    static unsigned int sm_uThreadCounterAfterWait;
    static QMutex sm_mutex;
    static QConditionVariable sm_conditionVariable;

};

bool QConditionVariableTestClass::sm_bLockIsLockedAfterWait = false;
unsigned int QConditionVariableTestClass::sm_uThreadCounterBeforeWait = 0;
unsigned int QConditionVariableTestClass::sm_uThreadCounterAfterWait = 0;
QMutex QConditionVariableTestClass::sm_mutex;
QConditionVariable QConditionVariableTestClass::sm_conditionVariable;


QTEST_SUITE_BEGIN( QConditionVariable_TestSuite )

/// <summary>
/// Checks that the thread blocks, waiting until it gets notified.
/// </summary>
QTEST_CASE ( Wait_ThreadBlocksUntilNotified_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    QDelegate<void()> function(&QConditionVariableTestClass::WaitingFunction);
    QThread thread(function);

    // [Execution]
    SQThisThread::Sleep(QTimeSpan(0, 0, 0, 0, 200, 0, 0));
    bool bThreadPassedFirstHalf = QConditionVariableTestClass::sm_uThreadCounterBeforeWait > 0;
    bool bThreadDidNotPassSecondHalfBeforeNotification = QConditionVariableTestClass::sm_uThreadCounterAfterWait == 0;
    QConditionVariableTestClass::sm_conditionVariable.NotifyOne();
    thread.Join();
    bool bThreadPassedSecondHalfAfterNotification = QConditionVariableTestClass::sm_uThreadCounterAfterWait > 0;

    // [Verification]
    BOOST_CHECK(bThreadPassedFirstHalf);
    BOOST_CHECK(bThreadDidNotPassSecondHalfBeforeNotification);
    BOOST_CHECK(bThreadPassedSecondHalfAfterNotification);
}

/// <summary>
/// Checks that the mutex is unlocked when the thread waits for a notification.
/// </summary>
QTEST_CASE ( Wait_MutexIsUnlockedWhileWaiting_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    QConditionVariableTestClass::Reset();
    QDelegate<void()> function(&QConditionVariableTestClass::WaitingFunction);
    QThread thread1(function);
    QThread thread2(function);

    // [Execution]
    SQThisThread::Sleep(QTimeSpan(0, 0, 0, 0, 200, 0, 0));
    bool bSecondThreadEnteredCriticalSectionWhileWaiting = QConditionVariableTestClass::sm_uThreadCounterBeforeWait == 2;
    QConditionVariableTestClass::sm_conditionVariable.NotifyAll();

    // [Verification]
    thread1.Join();
    thread2.Join();
    BOOST_CHECK(bSecondThreadEnteredCriticalSectionWhileWaiting);
}

// [TODO] Thund: What happens when the lock is not locked?

/// <summary>
/// Checks that only one thread is notified.
/// </summary>
QTEST_CASE ( NotifyOne_OnlyOneThreadIsNotified_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    QConditionVariableTestClass::Reset();
    QDelegate<void()> function(&QConditionVariableTestClass::WaitingFunction);
    QThread thread1(function);
    QThread thread2(function);

    // [Execution]
    SQThisThread::Sleep(QTimeSpan(0, 0, 0, 0, 200, 0, 0));
    bool bSecondThreadEnteredCriticalSectionWhileWaiting = QConditionVariableTestClass::sm_uThreadCounterBeforeWait == 2;
    QConditionVariableTestClass::sm_conditionVariable.NotifyOne();
    SQThisThread::Sleep(QTimeSpan(0, 0, 0, 0, 200, 0, 0));
    bool bOnlyOneThreadPassedSecondHalfAfterNotification = QConditionVariableTestClass::sm_uThreadCounterAfterWait == 1;

    // [Verification]
    QConditionVariableTestClass::sm_conditionVariable.NotifyOne(); // Notifies the other thread
    thread1.Join();
    thread2.Join();
    BOOST_CHECK(bSecondThreadEnteredCriticalSectionWhileWaiting);
    BOOST_CHECK(bOnlyOneThreadPassedSecondHalfAfterNotification);
}

/// <summary>
/// Checks that the mutex is locked again when the thread gets notified.
/// </summary>
QTEST_CASE ( NotifyAll_MutexIsLockedAgainWhenNotified_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    QConditionVariableTestClass::Reset();
    QDelegate<void()> function(&QConditionVariableTestClass::WaitingFunction);
    QThread thread1(function);
    QThread thread2(function);

    // [Execution]
    SQThisThread::Sleep(QTimeSpan(0, 0, 0, 0, 200, 0, 0));
    QConditionVariableTestClass::sm_conditionVariable.NotifyAll();

    // [Verification]
    thread1.Join();
    thread2.Join();
    BOOST_CHECK(QConditionVariableTestClass::sm_bLockIsLockedAfterWait);
}

/// <summary>
/// Checks that all the threads are notified.
/// </summary>
QTEST_CASE ( NotifyAll_AllThreadsAreNotified_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    QConditionVariableTestClass::Reset();
    QDelegate<void()> function(&QConditionVariableTestClass::WaitingFunction);
    QThread thread1(function);
    QThread thread2(function);

    // [Execution]
    SQThisThread::Sleep(QTimeSpan(0, 0, 0, 0, 200, 0, 0));
    bool bSecondThreadEnteredCriticalSectionWhileWaiting = QConditionVariableTestClass::sm_uThreadCounterBeforeWait == 2;
    QConditionVariableTestClass::sm_conditionVariable.NotifyAll();
    SQThisThread::Sleep(QTimeSpan(0, 0, 0, 0, 200, 0, 0));
    bool bTwoThreadsPassedSecondHalfAfterNotification = QConditionVariableTestClass::sm_uThreadCounterAfterWait == 2;

    // [Verification]
    thread1.Join();
    thread2.Join();
    BOOST_CHECK(bSecondThreadEnteredCriticalSectionWhileWaiting);
    BOOST_CHECK(bTwoThreadsPassedSecondHalfAfterNotification);
}


// End - Test Suite: QConditionVariable
QTEST_SUITE_END()
