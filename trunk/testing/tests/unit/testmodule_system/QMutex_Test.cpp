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

#include "QMutex.h"

#include "QThreadWhiteBox.h"
#include "QThread.h"
#include "SQThisThread.h"

using Kinesis::QuimeraEngine::System::Threading::QMutex;

class QMutexTestClass
{
public:

    static void Reset()
    {
        sm_uSharedResource = 0;
        sm_bOneThreadAtATime = true;
    }

    static void Function(unsigned int uCheckValue)
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
    }

    static unsigned int sm_uSharedResource;
    static bool sm_bOneThreadAtATime;
    static QMutex sm_mutex;
};

QMutex QMutexTestClass::sm_mutex;
unsigned int QMutexTestClass::sm_uSharedResource;
bool QMutexTestClass::sm_bOneThreadAtATime = true;


QTEST_SUITE_BEGIN( QMutex_TestSuite )

/// <summary>
/// Checks that only one thread can own the mutex at a time.
/// </summary>
QTEST_CASE ( Lock_OnlyOneThreadOwnsTheMutexAtATime_Test )
{
    using Kinesis::QuimeraEngine::System::Threading::Test::QThreadWhiteBox;
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;
    using Kinesis::QuimeraEngine::Common::QDelegate;

    // [Preparation]
    QMutexTestClass::Reset();

    // [Execution]
    for(unsigned int uValue = 0; uValue < 100U; ++uValue)
    {
        QThreadWhiteBox thread(QDelegate<void(unsigned int)>(QMutexTestClass::Function), uValue);
        thread.Detach();
    }
    
    // [Verification]
    Kinesis::QuimeraEngine::System::Threading::SQThisThread::Sleep(QTimeSpan(0, 0, 0, 0, 300, 0, 0));
    BOOST_CHECK(QMutexTestClass::sm_bOneThreadAtATime);
}

/// <summary>
/// Checks that it returns True when the mutex can be locked.
/// </summary>
QTEST_CASE ( TryLock_ReturnsTrueWhenMutexCanBeLocked_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = true;
    QMutex mutex;

    // [Execution]
    bool bResult = mutex.TryLock();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);

    // [Cleaning]
    mutex.Unlock();
}

/// <summary>
/// Checks that it returns False when the mutex cannot be locked.
/// </summary>
QTEST_CASE ( TryLock_ReturnsFalseWhenMutexCannotBeLocked_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = false;
    QMutex mutex;
    mutex.Lock();

    // [Execution]
    bool bResult = mutex.TryLock();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);

    // [Cleaning]
    mutex.Unlock();
}

// End - Test Suite: QMutex
QTEST_SUITE_END()
