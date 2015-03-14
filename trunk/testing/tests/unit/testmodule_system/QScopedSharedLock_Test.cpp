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

#include "QScopedSharedLock.h"

using Kinesis::QuimeraEngine::System::Threading::QScopedSharedLock;
using Kinesis::QuimeraEngine::System::Threading::QSharedMutex;


QTEST_SUITE_BEGIN( QScopedSharedLock_TestSuite )
    
/// <summary>
/// Checks that it owns the mutex when it was not locked and input is True.
/// </summary>
QTEST_CASE ( Constructor_OwnsTheMutexWhenItWasNotLockedAndInputIsTrue_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = true;
    const bool INPUT_VALUE = true;
    QSharedMutex mutex;

    // [Execution]
    QScopedSharedLock<QSharedMutex> lock(mutex, INPUT_VALUE);
    
    // [Verification]
    bool bOwnsMutex = lock.IsOwner();
    BOOST_CHECK_EQUAL(bOwnsMutex, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it does not own the mutex when it was not locked and input is False.
/// </summary>
QTEST_CASE ( Constructor_DoesNotOwnTheMutexWhenItWasNotLockedAndInputIsFalse_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = false;
    const bool INPUT_VALUE = false;
    QSharedMutex mutex;

    // [Execution]
    QScopedSharedLock<QSharedMutex> lock(mutex, INPUT_VALUE);
    
    // [Verification]
    bool bOwnsMutex = lock.IsOwner();
    BOOST_CHECK_EQUAL(bOwnsMutex, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the mutex is unlocked.
/// </summary>
QTEST_CASE ( Destructor_MutexIsUnlocked_Test )
{
    // [Preparation]
    const bool MUTEX_IS_UNLOCKED = true;
    QSharedMutex mutex;
    {
        QScopedSharedLock<QSharedMutex> lock(mutex, true);

    // [Execution]
    } // Calls destructor
    
    // [Verification]
    bool bCanBeLocked = mutex.TryLock();
    mutex.Unlock();
    BOOST_CHECK_EQUAL(bCanBeLocked, MUTEX_IS_UNLOCKED);
}

/// <summary>
/// Checks that nothing happens when the mutex was not locked.
/// </summary>
QTEST_CASE ( Destructor_ItDoesNothingWhenMutexIsNotLocked_Test )
{
    // [Preparation]
    const bool NOTHING_HAPPENS = true;
    QSharedMutex mutex;
    {
        QScopedSharedLock<QSharedMutex> lock(mutex, false);

    // [Execution]
    } // Calls destructor
    
    // [Verification]
    BOOST_CHECK(NOTHING_HAPPENS);
}

/// <summary>
/// Checks that it owns the mutex when it was not locked.
/// </summary>
QTEST_CASE ( Lock_OwnsTheMutexWhenItWasNotLocked_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = true;
    QSharedMutex mutex;
    QScopedSharedLock<QSharedMutex> lock(mutex, false);

    // [Execution]
    lock.Lock();
    
    // [Verification]
    bool bOwnsMutex = lock.IsOwner();
    BOOST_CHECK_EQUAL(bOwnsMutex, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it stops owning the mutex when it was locked.
/// </summary>
QTEST_CASE ( Unlock_StopsOwningMutexWhenItWasLocked_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = false;
    QSharedMutex mutex;
    QScopedSharedLock<QSharedMutex> lock(mutex, true);

    // [Execution]
    lock.Unlock();
    
    // [Verification]
    bool bOwnsMutex = lock.IsOwner();
    BOOST_CHECK_EQUAL(bOwnsMutex, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns True when the mutex can be locked.
/// </summary>
QTEST_CASE ( TryLock_ReturnsTrueWhenMutexCanBeLocked_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = true;
    QSharedMutex mutex;
    QScopedSharedLock<QSharedMutex> lock(mutex, false);

    // [Execution]
    bool bResult = lock.TryLock();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns False when the mutex cannot be locked.
/// </summary>
QTEST_CASE ( TryLock_ReturnsFalseWhenMutexCannotBeLocked_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = false;
    QSharedMutex mutex;
    QScopedSharedLock<QSharedMutex> lock(mutex, false);
    mutex.Lock();

    // [Execution]
    bool bResult = lock.TryLock();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);

    // [Cleaning]
    mutex.Unlock();
}

// End - Test Suite: QScopedSharedLock
QTEST_SUITE_END()
