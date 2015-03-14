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

#include "QArrayResult.h"

using Kinesis::QuimeraEngine::Common::DataTypes::QArrayResult;
using Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q;

// Class used for testing the call to the destructor
class DestructorCallCounter
{
public:

    ~DestructorCallCounter()
    {
        ++sm_uDestructorCallCounter;
    }

    static void ResetCounter()
    {
        sm_uDestructorCallCounter = 0;
    }

    static unsigned int GetDestructorCallCount()
    {
        return sm_uDestructorCallCounter;
    }

private:

    static unsigned int sm_uDestructorCallCounter;
};

unsigned int DestructorCallCounter::sm_uDestructorCallCounter = 0;



QTEST_SUITE_BEGIN( QArrayResult_TestSuite )

/// <summary>
/// Checks that input values are correctly stored.
/// </summary>
QTEST_CASE ( Constructor1_CommonValuesAreCorrectlyStored_Test )
{
    // [Preparation]
    const pointer_uint_q COUNT = 4U;
    const int* ARRAY = new int[COUNT];

    // [Execution]
    QArrayResult<const int> array(ARRAY, COUNT);

    // [Verification]
    BOOST_CHECK_EQUAL(array.Get(), ARRAY);
    BOOST_CHECK_EQUAL(array.GetCount(), COUNT);
}

/// <summary>
/// Checks that a non-null array is attached.
/// </summary>
QTEST_CASE ( Constructor1_NonNullArrayIsAttached_Test )
{
    // [Preparation]
    const bool ATTACH = true;
    const pointer_uint_q COUNT = 4U;
    const int* ARRAY = new int[COUNT];

    // [Execution]
    QArrayResult<const int> array(ARRAY, COUNT);

    // [Verification]
    BOOST_CHECK_EQUAL(array.IsAttached(), ATTACH);
}

/// <summary>
/// Checks that input values are correctly stored when they are null and zero.
/// </summary>
QTEST_CASE ( Constructor1_InputValuesAreCorrectlyStoredWhenTheyAreNullAndZero_Test )
{
    // [Preparation]
    const pointer_uint_q COUNT = 0;
    const int* ARRAY = null_q;

    // [Execution]
    QArrayResult<const int> array(ARRAY, COUNT);

    // [Verification]
    BOOST_CHECK_EQUAL(array.Get(), ARRAY);
    BOOST_CHECK_EQUAL(array.GetCount(), COUNT);
}

/// <summary>
/// Checks that instance cannot be attached if array is null.
/// </summary>
QTEST_CASE ( Constructor1_InstanceCannotBeAttachedIfArrayIsNull_Test )
{
    // [Preparation]
    const bool EXPECTED_ATTACH = false;
    const pointer_uint_q COUNT = 0;
    const int* ARRAY = null_q;

    // [Execution]
    QArrayResult<const int> array(ARRAY, COUNT);

    // [Verification]
    BOOST_CHECK_EQUAL(array.IsAttached(), EXPECTED_ATTACH);
}

/// <summary>
/// Checks that all the values of the input instance are correctly copied.
/// </summary>
QTEST_CASE ( Constructor2_AllValuesAreCorrectlyCopied_Test )
{
    // [Preparation]
    const pointer_uint_q COUNT = 4U;
    const int* ARRAY = new int[COUNT];
    QArrayResult<const int> INPUT_INSTANCE(ARRAY, COUNT);

    // [Execution]
    QArrayResult<const int> array(INPUT_INSTANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(array.Get(), ARRAY);
    BOOST_CHECK_EQUAL(array.GetCount(), COUNT);
}

/// <summary>
/// Checks that the new instance is attached.
/// </summary>
QTEST_CASE ( Constructor2_NewInstanceIsAttached_Test )
{
    // [Preparation]
    const bool ATTACH = true;
    const pointer_uint_q COUNT = 4U;
    const int* ARRAY = new int[COUNT];
    QArrayResult<const int> INPUT_INSTANCE(ARRAY, COUNT);

    // [Execution]
    QArrayResult<const int> array(INPUT_INSTANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(array.IsAttached(), ATTACH);
}

/// <summary>
/// Checks that the input instance is detached.
/// </summary>
QTEST_CASE ( Constructor2_InputInstanceIsDetached_Test )
{
    // [Preparation]
    const pointer_uint_q COUNT = 4U;
    const int* ARRAY = new int[COUNT];
    const QArrayResult<const int> INPUT_INSTANCE(ARRAY, COUNT);
    const bool EXPECTED_ATTACH_OF_INPUT_INSTANCE = false;

    // [Execution]
    QArrayResult<const int> array(INPUT_INSTANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(INPUT_INSTANCE.IsAttached(), EXPECTED_ATTACH_OF_INPUT_INSTANCE);
}

/// <summary>
/// Checks that the destructor of the each element is called when instance is attached.
/// </summary>
QTEST_CASE ( Destructor_DestructorOfEachElementIsCalled_Test )
{
    // [Preparation]
    const pointer_uint_q COUNT = 4U;
    DestructorCallCounter* ARRAY = new DestructorCallCounter[COUNT];

    {
        QArrayResult<DestructorCallCounter> INPUT_INSTANCE(ARRAY, COUNT);
        DestructorCallCounter::ResetCounter();

    // [Execution]
    } // Destructor called

    // [Verification]
    BOOST_CHECK_EQUAL(DestructorCallCounter::GetDestructorCallCount(), COUNT);
}

/// <summary>
/// Checks that the array is destroyed when instance is attached.
/// </summary>
QTEST_CASE ( Destructor_ArrayIsDestroyedWhenWrapperIsAttached_Test )
{
    // [Preparation]
    const pointer_uint_q COUNT = 4U;
    DestructorCallCounter* ARRAY = new DestructorCallCounter[COUNT];

    {
        QArrayResult<DestructorCallCounter> INPUT_INSTANCE(ARRAY, COUNT);
        DestructorCallCounter::ResetCounter();

    // [Execution]
    } // Destructor called

    // [Verification]
    BOOST_CHECK(DestructorCallCounter::GetDestructorCallCount() > 0);
}

/// <summary>
/// Checks that the array is not destroyed when instance is not attached.
/// </summary>
QTEST_CASE ( Destructor_ArrayIsNotDestroyedWhenWrapperIsNotAttached_Test )
{
    // [Preparation]
    const pointer_uint_q COUNT = 4U;
    DestructorCallCounter* ARRAY = new DestructorCallCounter[COUNT];

    {
        QArrayResult<DestructorCallCounter> INPUT_INSTANCE(ARRAY, COUNT);
        INPUT_INSTANCE.Detach();
        DestructorCallCounter::ResetCounter();

    // [Execution]
    }

    // [Verification]
    BOOST_CHECK(DestructorCallCounter::GetDestructorCallCount() == 0);

    // [Cleaning]
    delete[] ARRAY;
}

/// <summary>
/// Checks that the wrapper is detached.
/// </summary>
QTEST_CASE ( Detach_WrapperIsDetached_Test )
{
    // [Preparation]
    const bool EXPECTED_ATTACH = false;
    const pointer_uint_q COUNT = 4U;
    const int* ARRAY = new int[COUNT];
    QArrayResult<const int> INSTANCE(ARRAY, COUNT);

    // [Execution]
    INSTANCE.Detach();

    // [Verification]
    BOOST_CHECK_EQUAL(INSTANCE.IsAttached(), EXPECTED_ATTACH);

    // [Cleaning]
    delete[] ARRAY;
}

// End - Test Suite: QArrayResult
QTEST_SUITE_END()
