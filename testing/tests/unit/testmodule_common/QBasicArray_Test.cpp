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

#include "QBasicArray.h"

using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;
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



QTEST_SUITE_BEGIN( QBasicArray_TestSuite )

/// <summary>
/// Checks that input values are correctly stored.
/// </summary>
QTEST_CASE ( Constructor1_CommonValuesAreCorrectlyStored_Test )
{
    // [Preparation]
    const bool ATTACH = true;
    const pointer_uint_q COUNT = 4U;
    const int* ARRAY = new int[COUNT];

    // [Execution]
    QBasicArray<const int> array(ARRAY, COUNT, ATTACH);

    // [Verification]
    BOOST_CHECK_EQUAL(array.Get(), ARRAY);
    BOOST_CHECK_EQUAL(array.GetCount(), COUNT);
    BOOST_CHECK_EQUAL(array.IsAttached(), ATTACH);
}

/// <summary>
/// Checks that input values are correctly stored when they are null and zero.
/// </summary>
QTEST_CASE ( Constructor1_InputValuesAreCorrectlyStoredWhenTheyAreNullAndZero_Test )
{
    // [Preparation]
    const bool ATTACH = false;
    const pointer_uint_q COUNT = 0;
    const int* ARRAY = null_q;

    // [Execution]
    QBasicArray<const int> array(ARRAY, COUNT, ATTACH);

    // [Verification]
    BOOST_CHECK_EQUAL(array.Get(), ARRAY);
    BOOST_CHECK_EQUAL(array.GetCount(), COUNT);
    BOOST_CHECK_EQUAL(array.IsAttached(), ATTACH);
}

/// <summary>
/// Checks that instance cannot be attached if array is null.
/// </summary>
QTEST_CASE ( Constructor1_InstanceCannotBeAttachedIfArrayIsNull_Test )
{
    // [Preparation]
    const bool ATTACH = true;
    const bool EXPECTED_ATTACH = false;
    const pointer_uint_q COUNT = 0;
    const int* ARRAY = null_q;

    // [Execution]
    QBasicArray<const int> array(ARRAY, COUNT, ATTACH);

    // [Verification]
    BOOST_CHECK_EQUAL(array.IsAttached(), EXPECTED_ATTACH);
}

/// <summary>
/// Checks that input values are correctly stored.
/// </summary>
QTEST_CASE ( Constructor2_CommonValuesAreCorrectlyStored_Test )
{
    // [Preparation]
    const bool ATTACH = true;
    const pointer_uint_q COUNT = 4U;
    const int* ARRAY = new int[COUNT];
    QBasicArray<const int> INPUT_INSTANCE(ARRAY, COUNT, ATTACH);

    // [Execution]
    QBasicArray<const int> array(INPUT_INSTANCE, ATTACH);

    // [Verification]
    BOOST_CHECK_EQUAL(array.Get(), ARRAY);
    BOOST_CHECK_EQUAL(array.GetCount(), COUNT);
    BOOST_CHECK_EQUAL(array.IsAttached(), ATTACH);
}

/// <summary>
/// Checks that input wrapper is detached when the attach flag is true.
/// </summary>
QTEST_CASE ( Constructor2_InputWrapperIsDetachedWhenInputAttachFlagIsTrue_Test )
{
    // [Preparation]
    const bool ATTACH = true;
    const pointer_uint_q COUNT = 4U;
    const int* ARRAY = new int[COUNT];
    const QBasicArray<const int> INPUT_INSTANCE(ARRAY, COUNT, ATTACH);
    const bool EXPECTED_ATTACH_OF_INPUT_ARRAY = false;

    // [Execution]
    QBasicArray<const int> array(INPUT_INSTANCE, ATTACH);

    // [Verification]
    BOOST_CHECK_EQUAL(INPUT_INSTANCE.IsAttached(), EXPECTED_ATTACH_OF_INPUT_ARRAY);
}

/// <summary>
/// Checks that input wrapper is not detached when the attach flag is false.
/// </summary>
QTEST_CASE ( Constructor2_InputWrapperIsNotDetachedWhenInputAttachFlagIsFalse_Test )
{
    // [Preparation]
    const bool ATTACH = false;
    const pointer_uint_q COUNT = 4U;
    const int* ARRAY = new int[COUNT];
    const QBasicArray<const int> INPUT_INSTANCE(ARRAY, COUNT, true);
    const bool EXPECTED_ATTACH_OF_INPUT_ARRAY = true;

    // [Execution]
    QBasicArray<const int> array(INPUT_INSTANCE, ATTACH);

    // [Verification]
    BOOST_CHECK_EQUAL(INPUT_INSTANCE.IsAttached(), EXPECTED_ATTACH_OF_INPUT_ARRAY);
}

/// <summary>
/// Checks that the resident wrapper cannot be attached to the array if input instance is not attached.
/// </summary>
QTEST_CASE ( Constructor2_ResidentWrapperCannotBeAttachedIfInputInstanceIsNotAttached_Test )
{
    // [Preparation]
    const bool ATTACH = true;
    const bool EXPECTED_ATTACH = false;
    const pointer_uint_q COUNT = 4U;
    const int* ARRAY = new int[COUNT];
    const QBasicArray<const int> INPUT_INSTANCE(ARRAY, COUNT, false);

    // [Execution]
    QBasicArray<const int> array(INPUT_INSTANCE, ATTACH);

    // [Verification]
    BOOST_CHECK_EQUAL(array.IsAttached(), EXPECTED_ATTACH);

    // [Cleaning]
    delete[] ARRAY;
}

/// <summary>
/// Checks that all the values of the input instance are correctly copied.
/// </summary>
QTEST_CASE ( Constructor3_AllValuesAreCorrectlyCopied_Test )
{
    // [Preparation]
    const bool ATTACH = true;
    const pointer_uint_q COUNT = 4U;
    const int* ARRAY = new int[COUNT];
    QBasicArray<const int> INPUT_INSTANCE(ARRAY, COUNT, ATTACH);

    // [Execution]
    QBasicArray<const int> array(INPUT_INSTANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(array.Get(), ARRAY);
    BOOST_CHECK_EQUAL(array.GetCount(), COUNT);
    BOOST_CHECK_EQUAL(array.IsAttached(), ATTACH);
}

/// <summary>
/// Checks that the input instance is detached.
/// </summary>
QTEST_CASE ( Constructor3_InputInstanceIsDetached_Test )
{
    // [Preparation]
    const bool ATTACH = true;
    const pointer_uint_q COUNT = 4U;
    const int* ARRAY = new int[COUNT];
    const QBasicArray<const int> INPUT_INSTANCE(ARRAY, COUNT, ATTACH);
    const bool EXPECTED_ATTACH_OF_INPUT_INSTANCE = false;

    // [Execution]
    QBasicArray<const int> array(INPUT_INSTANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(INPUT_INSTANCE.IsAttached(), EXPECTED_ATTACH_OF_INPUT_INSTANCE);
}

/// <summary>
/// Checks that the destructor of the each element is called when instance is attached.
/// </summary>
QTEST_CASE ( Destructor_DestructorOfEachElementIsCalled_Test )
{
    // [Preparation]
    const bool ATTACH = true;
    const pointer_uint_q COUNT = 4U;
    DestructorCallCounter* ARRAY = new DestructorCallCounter[COUNT];

    {
        QBasicArray<DestructorCallCounter> INPUT_INSTANCE(ARRAY, COUNT, ATTACH);
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
    const bool ATTACH = true;
    const pointer_uint_q COUNT = 4U;
    DestructorCallCounter* ARRAY = new DestructorCallCounter[COUNT];

    {
        QBasicArray<DestructorCallCounter> INPUT_INSTANCE(ARRAY, COUNT, ATTACH);
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
    const bool ATTACH = false;
    const pointer_uint_q COUNT = 4U;
    DestructorCallCounter* ARRAY = new DestructorCallCounter[COUNT];

    {
        QBasicArray<DestructorCallCounter> INPUT_INSTANCE(ARRAY, COUNT, ATTACH);
        DestructorCallCounter::ResetCounter();

    // [Execution]
    }

    // [Verification]
    BOOST_CHECK(DestructorCallCounter::GetDestructorCallCount() == 0);

    // [Cleaning]
    delete[] ARRAY;
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
QTEST_CASE ( OperatorArraySubscript_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// Checks that all the values of the input instance are correctly copied.
/// </summary>
QTEST_CASE ( OperatorAssignment_AllValuesAreCorrectlyCopied_Test )
{
    // [Preparation]
    const bool ATTACH = true;
    const pointer_uint_q COUNT = 4U;
    const int* ARRAY = new int[COUNT];
    QBasicArray<const int> INPUT_INSTANCE(ARRAY, COUNT, ATTACH);
    QBasicArray<const int> arResidentInstance(null_q, 0, false);

    // [Execution]
    arResidentInstance = INPUT_INSTANCE;

    // [Verification]
    BOOST_CHECK_EQUAL(arResidentInstance.Get(), ARRAY);
    BOOST_CHECK_EQUAL(arResidentInstance.GetCount(), COUNT);
    BOOST_CHECK_EQUAL(arResidentInstance.IsAttached(), ATTACH);
}

/// <summary>
/// Checks that the input instance is detached.
/// </summary>
QTEST_CASE ( OperatorAssignment_InputInstanceIsDetached_Test )
{
    // [Preparation]
    const bool ATTACH = true;
    const pointer_uint_q COUNT = 4U;
    const int* ARRAY = new int[COUNT];
    const QBasicArray<const int> INPUT_INSTANCE(ARRAY, COUNT, ATTACH);
    QBasicArray<const int> arResidentInstance(null_q, 0, false);
    const bool EXPECTED_ATTACH_OF_INPUT_INSTANCE = false;

    // [Execution]
    arResidentInstance = INPUT_INSTANCE;

    // [Verification]
    BOOST_CHECK_EQUAL(INPUT_INSTANCE.IsAttached(), EXPECTED_ATTACH_OF_INPUT_INSTANCE);
}

/// <summary>
/// Checks that the array is destroyed when instance is attached.
/// </summary>
QTEST_CASE ( OperatorAssignment_ArrayIsDestroyedWhenWrapperIsAttached_Test )
{
    // [Preparation]
    const bool ATTACH = true;
    const pointer_uint_q COUNT = 4U;
    DestructorCallCounter* ARRAY = new DestructorCallCounter[COUNT];
    QBasicArray<DestructorCallCounter> INPUT_INSTANCE(null_q, 0, ATTACH);
    QBasicArray<DestructorCallCounter> arResidentInstance(ARRAY, COUNT, ATTACH);
    DestructorCallCounter::ResetCounter();

    // [Execution]
    arResidentInstance = INPUT_INSTANCE;

    // [Verification]
    BOOST_CHECK(DestructorCallCounter::GetDestructorCallCount() > 0);
}

/// <summary>
/// Checks that the array is not destroyed when instance is not attached.
/// </summary>
QTEST_CASE ( OperatorAssignment_ArrayIsNotDestroyedWhenWrapperIsNotAttached_Test )
{
    // [Preparation]
    const bool ATTACH = true;
    const pointer_uint_q COUNT = 4U;
    DestructorCallCounter* ARRAY = new DestructorCallCounter[COUNT];
    QBasicArray<DestructorCallCounter> INPUT_INSTANCE(ARRAY, COUNT, ATTACH);
    QBasicArray<DestructorCallCounter> arResidentInstance(null_q, 0, false);
    DestructorCallCounter::ResetCounter();

    // [Execution]
    arResidentInstance = INPUT_INSTANCE;

    // [Verification]
    BOOST_CHECK(DestructorCallCounter::GetDestructorCallCount() == 0);
}

/// <summary>
/// Checks that it returns a reference to itself.
/// </summary>
QTEST_CASE ( OperatorAssignment_ReturnsReferenceToItself_Test )
{
    // [Preparation]
    const bool ATTACH = true;
    const pointer_uint_q COUNT = 4U;
    const int* ARRAY = new int[COUNT];
    const QBasicArray<const int> INPUT_INSTANCE(ARRAY, COUNT, ATTACH);
    QBasicArray<const int> arResidentInstance(null_q, 0, false);

    // [Execution]
    QBasicArray<const int>& reference = (arResidentInstance = INPUT_INSTANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(&reference, &arResidentInstance);
}

/// <summary>
/// Checks that the wrapper is detached.
/// </summary>
QTEST_CASE ( Detach_WrapperIsDetached_Test )
{
    // [Preparation]
    const bool ATTACH = true;
    const bool EXPECTED_ATTACH = false;
    const pointer_uint_q COUNT = 4U;
    const int* ARRAY = new int[COUNT];
    QBasicArray<const int> INSTANCE(ARRAY, COUNT, ATTACH);

    // [Execution]
    INSTANCE.Detach();

    // [Verification]
    BOOST_CHECK_EQUAL(INSTANCE.IsAttached(), EXPECTED_ATTACH);

    // [Cleaning]
    delete[] ARRAY;
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
QTEST_CASE ( Get_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
QTEST_CASE ( GetCount_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// Checks that it returns the correct number of bytes.
/// </summary>
QTEST_CASE ( GetSize_ReturnsCorrectNumberOfBytes_Test )
{
    // [Preparation]
    const bool ATTACH = true;
    const pointer_uint_q COUNT = 4U;
    const int* ARRAY = new int[COUNT];
    const QBasicArray<const int> INSTANCE(ARRAY, COUNT, ATTACH);
    const pointer_uint_q EXPECTED_SIZE = 16U;

    // [Execution]
    pointer_uint_q uSize = INSTANCE.GetSize();

    // [Verification]
    BOOST_CHECK_EQUAL(uSize, EXPECTED_SIZE);
}

/// <summary>
/// Checks that it returns zero when the number of elements stored in the wrapper is zero.
/// </summary>
QTEST_CASE ( GetSize_ReturnsZeroWhenWrapperContainsZeroArrayElements_Test )
{
    // [Preparation]
    const bool ATTACH = false;
    const pointer_uint_q COUNT = 0;
    const int* ARRAY = null_q;
    const QBasicArray<const int> INSTANCE(ARRAY, COUNT, ATTACH);
    const pointer_uint_q EXPECTED_SIZE = 0;

    // [Execution]
    pointer_uint_q uSize = INSTANCE.GetSize();

    // [Verification]
    BOOST_CHECK_EQUAL(uSize, EXPECTED_SIZE);
}

// End - Test Suite: QBasicArray
QTEST_SUITE_END()
