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

#include "QDynamicArray.h"

#include "CallCounter.h"

using Kinesis::QuimeraEngine::Tools::Containers::QDynamicArray;


QTEST_SUITE_BEGIN( QDynamicArray_TestSuite )

/// <summary>
/// Checks that an empty array is correctly created.
/// </summary>
QTEST_CASE ( Constructor1_CreatesAnEmptyArray_Test )
{
    // [Preparation]
    const bool IS_EMPTY = true;

	// [Execution]
    QDynamicArray<int> arDynamicArray;
    
    // [Verification]
    bool bIsEmpty = arDynamicArray.IsEmpty();

    BOOST_CHECK_EQUAL(bIsEmpty, IS_EMPTY);
}

/// <summary>
/// Checks that the capacity is not zero by default.
/// </summary>
QTEST_CASE ( Constructor1_CapacityIsNotZero_Test )
{
    // [Preparation]
    const pointer_uint_q ZERO = 0;

	// [Execution]
    QDynamicArray<int> arDynamicArray;
    
    // [Verification]
    pointer_uint_q uCapacity = arDynamicArray.GetCapacity();

    BOOST_CHECK_NE(uCapacity, ZERO);
}

/// <summary>
/// Checks that an empty array is correctly created.
/// </summary>
QTEST_CASE ( Constructor2_CreatesAnEmptyArray_Test )
{
    // [Preparation]
    const bool IS_EMPTY = true;
    const pointer_uint_q INPUT_CAPACITY = 3;
    
	// [Execution]
    QDynamicArray<int> arDynamicArray(INPUT_CAPACITY);;
    
    // [Verification]
    bool bIsEmpty = arDynamicArray.IsEmpty();

    BOOST_CHECK_EQUAL(bIsEmpty, IS_EMPTY);
}

/// <summary>
/// Checks that the initial capacity is set correctly.
/// </summary>
QTEST_CASE ( Constructor2_CapacityIsSetCorrectly_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_CAPACITY = 3;

	// [Execution]
    QDynamicArray<int> arDynamicArray(EXPECTED_CAPACITY);
    
    // [Verification]
    pointer_uint_q uCapacity = arDynamicArray.GetCapacity();

    BOOST_CHECK_EQUAL(uCapacity, EXPECTED_CAPACITY);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input capacity equals zero.
/// </summary>
QTEST_CASE ( Constructor2_AssertionFailsWhenInputCapacityEqualsZero_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const pointer_uint_q ZERO_CAPACITY = 0;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDynamicArray<int> arDynamicArray(ZERO_CAPACITY);;
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the capacity is not zero when the input initial capacity was equal to zero.
/// </summary>
QTEST_CASE ( Constructor2_CapacityIsNotZeroWhenInputCapacityEqualsZero_Test )
{
    // [Preparation]
    const pointer_uint_q ZERO_CAPACITY = 0;

	// [Execution]
    QDynamicArray<int> arDynamicArray(ZERO_CAPACITY);;
    
    // [Verification]
    pointer_uint_q uCapacity = arDynamicArray.GetCapacity();
    BOOST_CHECK_NE(uCapacity, ZERO_CAPACITY);
}

#endif

/// <summary>
/// Checks that the amount of elements in the source array and the array copy are the same.
/// </summary>
QTEST_CASE ( Constructor3_ElementCountIsCorrectAfterCopyingCommonArray_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QFixedArray;

    // [Preparation]
    int arOriginalArrayElements[] = {1, 2, 3};
    QFixedArray<int> arOriginalArray(arOriginalArrayElements, 3U);
    const pointer_uint_q ORIGINAL_COUNT = arOriginalArray.GetCount();

	// [Execution]
    QDynamicArray<int> arDynamicArray(arOriginalArray);
    
    // [Verification]
    pointer_uint_q uCount = arDynamicArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, ORIGINAL_COUNT);
}

/// <summary>
/// Checks that the capacity of the resultant array equals the element count of the input array.
/// </summary>
QTEST_CASE ( Constructor3_CapacityEqualsInputArrayCount_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QFixedArray;

    // [Preparation]
    int arOriginalArrayElements[] = {1, 2, 3};
    QFixedArray<int> arOriginalArray(arOriginalArrayElements, 3U);
    const pointer_uint_q ORIGINAL_COUNT = arOriginalArray.GetCount();

	// [Execution]
    QDynamicArray<int> arDynamicArray(arOriginalArray);
    
    // [Verification]
    pointer_uint_q uCapacity = arDynamicArray.GetCapacity();
    BOOST_CHECK_EQUAL(uCapacity, ORIGINAL_COUNT);
}

/// <summary>
/// Checks that the copy constructor of every element is called.
/// </summary>
QTEST_CASE ( Constructor3_CopyConstructorOfEveryElementIsCalled_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QFixedArray;
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    CallCounter arOriginalArrayElements[3];
    QFixedArray<CallCounter> arOriginalArray(arOriginalArrayElements, 3U);

    const pointer_uint_q ORIGINAL_COUNT = arOriginalArray.GetCount();
    CallCounter::ResetCounters();

	// [Execution]
    QDynamicArray<CallCounter> arDynamicArray = arOriginalArray;
    
    // [Verification]
    pointer_uint_q uCopyConstructorsCalled = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uCopyConstructorsCalled, ORIGINAL_COUNT);
}

/// <summary>
/// Checks that elements are copied in the same order.
/// </summary>
QTEST_CASE ( Constructor3_ElementsAreCopiedInOrder_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QFixedArray;

    // [Preparation]
    int arOriginalArrayElements[] = {1, 2, 3};
    QFixedArray<int> arOriginalArray(arOriginalArrayElements, 3U);
    const pointer_uint_q ORIGINAL_COUNT = arOriginalArray.GetCount();
    const bool ARE_EQUAL = true;

	// [Execution]
    QDynamicArray<int> arDynamicArray(arOriginalArray);
    
    // [Verification]
    bool bAreEqual = true;

    for(pointer_uint_q i = 0; i < arOriginalArray.GetCount(); ++i)
        bAreEqual = bAreEqual && (arOriginalArray[i] == arDynamicArray[i]);

    BOOST_CHECK_EQUAL(bAreEqual, ARE_EQUAL);
}

/// <summary>
/// Checks that the amount of elements in the source array and the array copy are the same.
/// </summary>
QTEST_CASE ( Constructor4_ElementCountIsCorrectAfterCopyingCommonArray_Test )
{
    // [Preparation]
    QDynamicArray<int> arOriginalArray(5);
    arOriginalArray.Add(1);
    arOriginalArray.Add(2);
    arOriginalArray.Add(3);
    const pointer_uint_q ORIGINAL_COUNT = arOriginalArray.GetCount();

	// [Execution]
    QDynamicArray<int> arDynamicArray(arOriginalArray);
    
    // [Verification]
    pointer_uint_q uCount = arDynamicArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, ORIGINAL_COUNT);
}

/// <summary>
/// Checks that the capacity of the resultant array equals the element count of the input array.
/// </summary>
QTEST_CASE ( Constructor4_CapacityEqualsInputArrayCount_Test )
{
    // [Preparation]
    QDynamicArray<int> arOriginalArray(5);
    arOriginalArray.Add(1);
    arOriginalArray.Add(2);
    arOriginalArray.Add(3);
    const pointer_uint_q ORIGINAL_COUNT = arOriginalArray.GetCount();

	// [Execution]
    QDynamicArray<int> arDynamicArray(arOriginalArray);
    
    // [Verification]
    pointer_uint_q uCapacity = arDynamicArray.GetCapacity();
    BOOST_CHECK_EQUAL(uCapacity, ORIGINAL_COUNT);
}

/// <summary>
/// Checks that the copy constructor of every element is called.
/// </summary>
QTEST_CASE ( Constructor4_CopyConstructorOfEveryElementIsCalled_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    QDynamicArray<CallCounter> arOriginalArray;
    arOriginalArray.Add(CallCounter());
    arOriginalArray.Add(CallCounter());
    arOriginalArray.Add(CallCounter());
    const pointer_uint_q ORIGINAL_COUNT = arOriginalArray.GetCount();
    CallCounter::ResetCounters();

	// [Execution]
    QDynamicArray<CallCounter> arDynamicArray = arOriginalArray;
    
    // [Verification]
    pointer_uint_q uCopyConstructorsCalled = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uCopyConstructorsCalled, ORIGINAL_COUNT);
}

/// <summary>
/// Checks that the amount of elements in the resultant array equals zero when input array is empty.
/// </summary>
QTEST_CASE ( Constructor4_ElementCountIsZeroAfterCopyingEmptyArray_Test )
{
    // [Preparation]
    QDynamicArray<int> arOriginalArray;
    const pointer_uint_q ZERO_COUNT = 0;

	// [Execution]
    QDynamicArray<int> arDynamicArray(arOriginalArray);
    
    // [Verification]
    pointer_uint_q uCount = arDynamicArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, ZERO_COUNT);
}

/// <summary>
/// Checks that elements are copied in the same order.
/// </summary>
QTEST_CASE ( Constructor4_ElementsAreCopiedInOrder_Test )
{
    // [Preparation]
    QDynamicArray<int> arOriginalArray(3U);
    arOriginalArray.Add(1);
    arOriginalArray.Add(2);
    arOriginalArray.Add(3);
    const pointer_uint_q ORIGINAL_COUNT = arOriginalArray.GetCount();
    const bool ARE_EQUAL = true;

	// [Execution]
    QDynamicArray<int> arDynamicArray(arOriginalArray);
    
    // [Verification]
    bool bAreEqual = true;

    for(pointer_uint_q i = 0; i < arOriginalArray.GetCount(); ++i)
        bAreEqual = bAreEqual && (arOriginalArray[i] == arDynamicArray[i]);

    BOOST_CHECK_EQUAL(bAreEqual, ARE_EQUAL);
}

/// <summary>
/// Checks if the instance is correctly constructed when it receives a common array and its size.
/// </summary>
QTEST_CASE ( Constructor5_ItIsCorrectlyConstructedFromCommonArray_Test )
{
    // [Preparation]
    const unsigned int ARRAY_SIZE = 3;
    const char SOURCE_ARRAY[ARRAY_SIZE] = {0, 1, 2};

    // [Execution]
    QDynamicArray<char> arArray(SOURCE_ARRAY, ARRAY_SIZE);

    // [Verification]
    unsigned int uArraySize = arArray.GetCount();
    BOOST_CHECK_EQUAL(uArraySize, ARRAY_SIZE);

    for(unsigned int i = 0; i < arArray.GetCount(); ++i)
        BOOST_CHECK_EQUAL( arArray[i], SOURCE_ARRAY[i] );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks than assertion fails when the input array is null.
/// </summary>
QTEST_CASE ( Constructor5_AssertionFailsWhenArrayIsNull_Test )
{
    // [Preparation]
    const int* NULL_ARRAY = null_q;
    const unsigned int NON_ZERO_SIZE = 3;
    const bool ASSERTION_FAILED = true;

    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        QDynamicArray<int> arArray = QDynamicArray<int>(NULL_ARRAY, NON_ZERO_SIZE);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

/// <summary>
/// Checks than assertion fails when the input array size equals zero.
/// </summary>
QTEST_CASE ( Constructor5_AssertionFailsWhenCountIsZero_Test )
{
    // [Preparation]
    const int SOURCE_ARRAY[3] = {0, 1, 2};
    const unsigned int ZERO_SIZE = 0;
    const bool ASSERTION_FAILED = true;

    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        QDynamicArray<int> arArray = QDynamicArray<int>(SOURCE_ARRAY, ZERO_SIZE);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that all he elements are properly copied when the resident array is not empty.
/// </summary>
QTEST_CASE ( AssignmentOperator1_ElementsAreProperlyCopiedWhenArrayIsNotEmpty_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QFixedArray;

    // [Preparation]
    int arOriginalArrayElements[] = {1, 2, 3};
    QFixedArray<int> arOriginalArray(arOriginalArrayElements, 3U);
    QDynamicArray<int> arDynamicArray(arOriginalArray);
    int arExpectedArrayElements[] = {4, 5, 6};
    QFixedArray<int> arExpectedArray(arExpectedArrayElements, 3U);

    bool ARE_EQUAL = true;

	// [Execution]
    arDynamicArray = arExpectedArray;
    
    // [Verification]
    bool bAreEqual = true;

    for(pointer_uint_q i = 0; i < arExpectedArray.GetCount(); ++i)
        bAreEqual = bAreEqual && (arExpectedArray[i] == arDynamicArray[i]);

    BOOST_CHECK_EQUAL(bAreEqual, ARE_EQUAL);
}

/// <summary>
/// Checks that the amount of elements in the source array and the array copy are the same.
/// </summary>
QTEST_CASE ( AssignmentOperator1_ElementCountIsCorrectAfterCopyingCommonArray_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QFixedArray;

    // [Preparation]
    int arOriginalArrayElements[] = {1, 2, 3};
    QFixedArray<int> arOriginalArray(arOriginalArrayElements, 3U);
    const pointer_uint_q ORIGINAL_COUNT = arOriginalArray.GetCount();

	// [Execution]
    QDynamicArray<int> arDynamicArray;
    arDynamicArray = arOriginalArray;
    
    // [Verification]
    pointer_uint_q uCount = arDynamicArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, ORIGINAL_COUNT);
}

/// <summary>
/// Checks that the capacity of the resultant array equals the element count of the input array when it is greater than the resident array.
/// </summary>
QTEST_CASE ( AssignmentOperator1_CapacityEqualsInputArrayCountWhenItIsGreaterThanResidentArray_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QFixedArray;

    // [Preparation]
    int arOriginalArrayElements[] = {1, 2, 3};
    QFixedArray<int> arOriginalArray(arOriginalArrayElements, 3U);
    const pointer_uint_q ORIGINAL_COUNT = arOriginalArray.GetCount();

	// [Execution]
    QDynamicArray<int> arDynamicArray;
    arDynamicArray = arOriginalArray;
    
    // [Verification]
    pointer_uint_q uCapacity = arDynamicArray.GetCapacity();
    BOOST_CHECK_EQUAL(uCapacity, ORIGINAL_COUNT);
}

/// <summary>
/// Checks that the copy constructor of every new element is called when copying a bigger array.
/// </summary>
QTEST_CASE ( AssignmentOperator1_CopyConstructorOfEveryNewElementIsCalledWhenCopyingBiggerArray_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QFixedArray;
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    CallCounter arOriginalArrayElements[1];
    QFixedArray<CallCounter> arOriginalArray(arOriginalArrayElements, 1U);
    CallCounter arBiggerArrayElements[3];
    QFixedArray<CallCounter> arBiggerArray(arBiggerArrayElements, 3U);
    const pointer_uint_q NEW_ELEMENTS = 2U;

	// [Execution]
    QDynamicArray<CallCounter> arDynamicArray(arOriginalArray);
    CallCounter::ResetCounters();
    arDynamicArray = arBiggerArray;
    
    // [Verification]
    pointer_uint_q uCopyConstructorIsCalled = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uCopyConstructorIsCalled, NEW_ELEMENTS);
}

/// <summary>
/// Checks that the assignment operator of every existing element is called.
/// </summary>
QTEST_CASE ( AssignmentOperator1_AssignmentOperatorOfEveryExistingElementIsCalled_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QFixedArray;
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    CallCounter arOriginalArrayElements[2];
    QFixedArray<CallCounter> arOriginalArray(arOriginalArrayElements, 2U);
    CallCounter arBiggerArrayElements[3];
    QFixedArray<CallCounter> arBiggerArray(arBiggerArrayElements, 3U);
    const pointer_uint_q EXISTING_ELEMENTS = 2U;

	// [Execution]
    QDynamicArray<CallCounter> arDynamicArray(arOriginalArray);
    CallCounter::ResetCounters();
    arDynamicArray = arBiggerArray;
    
    // [Verification]
    pointer_uint_q uAssignmentOperatorIsCalled = CallCounter::GetAssignmentCallsCount();
    BOOST_CHECK_EQUAL(uAssignmentOperatorIsCalled, EXISTING_ELEMENTS);
}

/// <summary>
/// Checks that the destructor of every exceeding element is called when copying a smaller array.
/// </summary>
QTEST_CASE ( AssignmentOperator1_DestructorOfElementsIsCalledWhenCopyingSmallerArray_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QFixedArray;
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    CallCounter arOriginalArrayElements[3];
    QFixedArray<CallCounter> arOriginalArray(arOriginalArrayElements, 3U);
    CallCounter arSmallerArrayElements[1];
    QFixedArray<CallCounter> arSmallerArray(arSmallerArrayElements, 1U);
    const pointer_uint_q EXCEEDING_ELEMENTS = 2U;

	// [Execution]
    QDynamicArray<CallCounter> arDynamicArray(arOriginalArray);
    CallCounter::ResetCounters();
    arDynamicArray = arSmallerArray;
    
    // [Verification]
    pointer_uint_q uDestructorIsCalled = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorIsCalled, EXCEEDING_ELEMENTS);
}

/// <summary>
/// Checks that the capacity of the resident array does not change when assigned to smaller array.
/// </summary>
QTEST_CASE ( AssignmentOperator1_CapacityDoesNotChangeWhenAssigningToSmallerArray_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QFixedArray;

    // [Preparation]
    QDynamicArray<int> arEmptyArray;
    int arNonEmptyArrayElements[] = {1, 2, 3};
    int arSmallerArrayElements[] = {1, 2};
    QDynamicArray<int> arNonEmptyArray(QFixedArray<int>(arNonEmptyArrayElements, 3U));
    QFixedArray<int> arSmallerArray(arSmallerArrayElements, 2U);
    const pointer_uint_q ORIGINAL_CAPACITY = arNonEmptyArray.GetCapacity();

	// [Execution]
    arNonEmptyArray = arSmallerArray;
    
    // [Verification]
    pointer_uint_q uCapacity = arNonEmptyArray.GetCapacity();
    BOOST_CHECK_EQUAL(uCapacity, ORIGINAL_CAPACITY);
}

/// <summary>
/// Checks that elements are copied in the same order.
/// </summary>
QTEST_CASE ( AssignmentOperator1_ElementsAreCopiedInOrder_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QFixedArray;

    // [Preparation]
    int arOriginalArrayElements[] = {1, 2, 3};
    QFixedArray<int> arOriginalArray(arOriginalArrayElements, 3U);
    const pointer_uint_q ORIGINAL_COUNT = arOriginalArray.GetCount();
    const bool ARE_EQUAL = true;

	// [Execution]
    QDynamicArray<int> arDynamicArray;
    arDynamicArray = arOriginalArray;
    
    // [Verification]
    bool bAreEqual = true;

    for(pointer_uint_q i = 0; i < arOriginalArray.GetCount(); ++i)
        bAreEqual = bAreEqual && (arOriginalArray[i] == arDynamicArray[i]);

    BOOST_CHECK_EQUAL(bAreEqual, ARE_EQUAL);
}

/// <summary>
/// Checks that it returns a reference to the resident array.
/// </summary>
QTEST_CASE ( AssignmentOperator1_ReturnsReferenceToResidentArray_Test )
{
    // [Preparation]
    QDynamicArray<int> arEmptyArray;
    QDynamicArray<int> arNonEmptyArray;

    // [Execution]
    QDynamicArray<int>& referenceToResult = arNonEmptyArray = arEmptyArray;
    
    // [Verification]
    BOOST_CHECK_EQUAL(&referenceToResult, &arNonEmptyArray);
}

/// <summary>
/// Checks that the amount of elements in the resultant array equals zero when input array is empty.
/// </summary>
QTEST_CASE ( AssignmentOperator2_ElementCountIsZeroAfterCopyingEmptyArray_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QFixedArray;

    // [Preparation]
    QDynamicArray<int> arEmptyArray;
    const pointer_uint_q ZERO_COUNT = 0;

    // [Preparation]
    int arNonEmptyArrayElements[] = {1, 2, 3};
    QDynamicArray<int> arNonEmptyArray(QFixedArray<int>(arNonEmptyArrayElements, 3U));

	// [Execution]
    arNonEmptyArray = arEmptyArray;
    
    // [Verification]
    pointer_uint_q uCount = arNonEmptyArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, ZERO_COUNT);
}

/// <summary>
/// Checks that all he elements are properly copied when the resident array is not empty.
/// </summary>
QTEST_CASE ( AssignmentOperator2_ElementsAreProperlyCopiedWhenArrayIsNotEmpty_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QFixedArray;

    // [Preparation]
    int arOriginalArrayElements[] = {1, 2, 3};
    QFixedArray<int> arOriginalArray(arOriginalArrayElements, 3U);
    QDynamicArray<int> arDynamicArray(arOriginalArray);
    int arExpectedArrayElements[] = {4, 5, 6};
    QDynamicArray<int> arExpectedArray(QFixedArray<int>(arExpectedArrayElements, 3U));

    bool ARE_EQUAL = true;

	// [Execution]
    arDynamicArray = arExpectedArray;
    
    // [Verification]
    bool bAreEqual = true;

    for(pointer_uint_q i = 0; i < arExpectedArray.GetCount(); ++i)
        bAreEqual = bAreEqual && (arExpectedArray[i] == arDynamicArray[i]);

    BOOST_CHECK_EQUAL(bAreEqual, ARE_EQUAL);
}

/// <summary>
/// Checks that the amount of elements in the source array and the array copy are the same.
/// </summary>
QTEST_CASE ( AssignmentOperator2_ElementCountIsCorrectAfterCopyingCommonArray_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QFixedArray;

    // [Preparation]
    int arOriginalArrayElements[] = {1, 2, 3};
    QDynamicArray<int> arOriginalArray(QFixedArray<int>(arOriginalArrayElements, 3U));
    const pointer_uint_q ORIGINAL_COUNT = arOriginalArray.GetCount();

	// [Execution]
    QDynamicArray<int> arDynamicArray;
    arDynamicArray = arOriginalArray;
    
    // [Verification]
    pointer_uint_q uCount = arDynamicArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, ORIGINAL_COUNT);
}

/// <summary>
/// Checks that the capacity of the resultant array equals the element count of the input array when it is greater than the resident array.
/// </summary>
QTEST_CASE ( AssignmentOperator2_CapacityEqualsInputArrayCountWhenItIsGreaterThanResidentArray_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QFixedArray;

    // [Preparation]
    int arOriginalArrayElements[] = {1, 2, 3};
    QDynamicArray<int> arOriginalArray(QFixedArray<int>(arOriginalArrayElements, 3U));
    const pointer_uint_q ORIGINAL_COUNT = arOriginalArray.GetCount();

	// [Execution]
    QDynamicArray<int> arDynamicArray;
    arDynamicArray = arOriginalArray;
    
    // [Verification]
    pointer_uint_q uCapacity = arDynamicArray.GetCapacity();
    BOOST_CHECK_EQUAL(uCapacity, ORIGINAL_COUNT);
}

/// <summary>
/// Checks that the copy constructor of every new element is called when copying a bigger array.
/// </summary>
QTEST_CASE ( AssignmentOperator2_CopyConstructorOfEveryNewElementIsCalledWhenCopyingBiggerArray_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QFixedArray;
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    CallCounter arOriginalArrayElements[1];
    QFixedArray<CallCounter> arOriginalArray(arOriginalArrayElements, 1U);
    CallCounter arBiggerArrayElements[3];
    QDynamicArray<CallCounter> arBiggerArray(QFixedArray<CallCounter>(arBiggerArrayElements, 3U));
    const pointer_uint_q NEW_ELEMENTS = 2U;

	// [Execution]
    QDynamicArray<CallCounter> arDynamicArray(arOriginalArray);
    CallCounter::ResetCounters();
    arDynamicArray = arBiggerArray;
    
    // [Verification]
    pointer_uint_q uCopyConstructorIsCalled = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uCopyConstructorIsCalled, NEW_ELEMENTS);
}

/// <summary>
/// Checks that the assignment operator of every existing element is called.
/// </summary>
QTEST_CASE ( AssignmentOperator2_AssignmentOperatorOfEveryExistingElementIsCalled_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QFixedArray;
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    CallCounter arOriginalArrayElements[2];
    QFixedArray<CallCounter> arOriginalArray(arOriginalArrayElements, 2U);
    CallCounter arBiggerArrayElements[3];
    QDynamicArray<CallCounter> arBiggerArray(QFixedArray<CallCounter>(arBiggerArrayElements, 3U));
    const pointer_uint_q EXISTING_ELEMENTS = 2U;

	// [Execution]
    QDynamicArray<CallCounter> arDynamicArray(arOriginalArray);
    CallCounter::ResetCounters();
    arDynamicArray = arBiggerArray;
    
    // [Verification]
    pointer_uint_q uAssignmentOperatorIsCalled = CallCounter::GetAssignmentCallsCount();
    BOOST_CHECK_EQUAL(uAssignmentOperatorIsCalled, EXISTING_ELEMENTS);
}

/// <summary>
/// Checks that the destructor of every exceeding element is called when copying a smaller array.
/// </summary>
QTEST_CASE ( AssignmentOperator2_DestructorOfElementsIsCalledWhenCopyingSmallerArray_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QFixedArray;
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    CallCounter arOriginalArrayElements[3];
    QFixedArray<CallCounter> arOriginalArray(arOriginalArrayElements, 3U);
    CallCounter arSmallerArrayElements[1];
    QDynamicArray<CallCounter> arSmallerArray(QFixedArray<CallCounter>(arSmallerArrayElements, 1U));
    const pointer_uint_q EXCEEDING_ELEMENTS = 2U;

	// [Execution]
    QDynamicArray<CallCounter> arDynamicArray(arOriginalArray);
    CallCounter::ResetCounters();
    arDynamicArray = arSmallerArray;
    
    // [Verification]
    pointer_uint_q uDestructorIsCalled = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorIsCalled, EXCEEDING_ELEMENTS);
}

/// <summary>
/// Checks that the capacity of the resident array does not change when assigned to smaller array.
/// </summary>
QTEST_CASE ( AssignmentOperator2_CapacityDoesNotChangeWhenAssigningToSmallerArray_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QFixedArray;

    // [Preparation]
    QDynamicArray<int> arEmptyArray;
    int arNonEmptyArrayElements[] = {1, 2, 3};
    int arSmallerArrayElements[] = {1, 2};
    QDynamicArray<int> arNonEmptyArray(QFixedArray<int>(arNonEmptyArrayElements, 3U));
    QDynamicArray<int> arSmallerArray(QFixedArray<int>(arSmallerArrayElements, 2U));
    const pointer_uint_q ORIGINAL_CAPACITY = arNonEmptyArray.GetCapacity();

	// [Execution]
    arNonEmptyArray = arSmallerArray;
    
    // [Verification]
    pointer_uint_q uCapacity = arNonEmptyArray.GetCapacity();
    BOOST_CHECK_EQUAL(uCapacity, ORIGINAL_CAPACITY);
}

/// <summary>
/// Checks that elements are copied in the same order.
/// </summary>
QTEST_CASE ( AssignmentOperator2_ElementsAreCopiedInOrder_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QFixedArray;

    // [Preparation]
    int arOriginalArrayElements[] = {1, 2, 3};
    QDynamicArray<int> arOriginalArray(QFixedArray<int>(arOriginalArrayElements, 3U));
    const pointer_uint_q ORIGINAL_COUNT = arOriginalArray.GetCount();
    const bool ARE_EQUAL = true;

	// [Execution]
    QDynamicArray<int> arDynamicArray;
    arDynamicArray = arOriginalArray;
    
    // [Verification]
    bool bAreEqual = true;

    for(pointer_uint_q i = 0; i < arOriginalArray.GetCount(); ++i)
        bAreEqual = bAreEqual && (arOriginalArray[i] == arDynamicArray[i]);

    BOOST_CHECK_EQUAL(bAreEqual, ARE_EQUAL);
}

/// <summary>
/// Checks that it returns a reference to the resident array.
/// </summary>
QTEST_CASE ( AssignmentOperator2_ReturnsReferenceToResidentArray_Test )
{
    // [Preparation]
    QDynamicArray<int> arEmptyArray;
    QDynamicArray<int> arNonEmptyArray;

    // [Execution]
    QDynamicArray<int>& referenceToResult = arNonEmptyArray = arEmptyArray;
    
    // [Verification]
    BOOST_CHECK_EQUAL(&referenceToResult, &arNonEmptyArray);
}

/// <summary>
/// Checks that the capacity is correctly increased.
/// </summary>
QTEST_CASE ( Reserve_CapacityIsCorrectlyIncreased_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_CAPACITY = 4U;
    QDynamicArray<int> arDynamicArray(1U);

    // [Execution]
    arDynamicArray.Reserve(EXPECTED_CAPACITY);

    // [Verification]
    pointer_uint_q uStoredCapacity = arDynamicArray.GetCapacity();

    BOOST_CHECK_EQUAL(uStoredCapacity, EXPECTED_CAPACITY);
}

/// <summary>
/// Checks that elements are correctly reallocated.
/// </summary>
QTEST_CASE ( Reserve_ElementsAreCorrectlyReallocated_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QFixedArray;

    // [Preparation]
    int arOriginalArrayElements[] = {0, 1, 2};
    QFixedArray<int> arOriginalArray(arOriginalArrayElements, 3U);
    QDynamicArray<int> arDynamicArray(arOriginalArray);

    const bool ELEMENTS_ARE_THE_SAME = true;
    const pointer_uint_q INPUT_CAPACITY = 20U;

    // [Execution]
    arDynamicArray.Reserve(INPUT_CAPACITY); // A reallocation occurs

    // [Verification]
    bool bElementsAreTheSame = true;

    for(pointer_uint_q i = 0; i < arDynamicArray.GetCount(); ++i)
        bElementsAreTheSame = bElementsAreTheSame && (arDynamicArray[i] == i);

    BOOST_CHECK_EQUAL(bElementsAreTheSame, ELEMENTS_ARE_THE_SAME);
}

/// <summary>
/// Checks that elements are not reallocated and capacity does not change when attempting to reserve less memory than current reserved.
/// </summary>
QTEST_CASE ( Reserve_NothingHappensWhenTheAmountToReserveIsNoGreaterThanCurrentCapacity_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QFixedArray;

    // [Preparation]
    const bool ELEMENTS_ARE_THE_SAME = true;
    const pointer_uint_q INPUT_CAPACITY = 1U;
    const pointer_uint_q EXPECTED_CAPACITY = 3U;

    int arOriginalArrayElements[] = {1, 2, 3};
    QFixedArray<int> arOriginalArray(arOriginalArrayElements, 3U);
    QDynamicArray<int> arDynamicArray(arOriginalArray);

    const int* ORIGINAL_FIRST_ELEMENT_ADDRESS = &arDynamicArray[0];

    // [Execution]
    arDynamicArray.Reserve(INPUT_CAPACITY);

    // [Verification]
    pointer_uint_q uCapacity = arDynamicArray.GetCapacity();
    int* pFirstElementAddress = &arDynamicArray[0];

    BOOST_CHECK_EQUAL(pFirstElementAddress, ORIGINAL_FIRST_ELEMENT_ADDRESS);
    BOOST_CHECK_EQUAL(uCapacity, EXPECTED_CAPACITY);
}

/// <summary>
/// Checks that elements can be added to empty arrays.
/// </summary>
QTEST_CASE ( Add_ElementIsCorrectlyAddedToEmptyArray_Test )
{
    // [Preparation]
    QDynamicArray<int> arEmptyArray;
    const int ELEMENT_VALUE = 1;

    // [Execution]
    arEmptyArray.Add(ELEMENT_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(arEmptyArray[0], ELEMENT_VALUE);
}

/// <summary>
/// Checks that the capacity is increased when elements are added to a full array.
/// </summary>
QTEST_CASE ( Add_CapacityIsIncreasedWhenAddingElementsToFullArray_Test )
{
    // [Preparation]
    const pointer_uint_q INITIAL_CAPACITY = 3U;
    QDynamicArray<int> arFullArray(INITIAL_CAPACITY);
    arFullArray.Add(0);
    arFullArray.Add(0);
    arFullArray.Add(0);
    const int ELEMENT_VALUE = 1;

    // [Execution]
    arFullArray.Add(ELEMENT_VALUE);

    // [Verification]
    pointer_uint_q uCapacity =  arFullArray.GetCapacity();
    BOOST_CHECK(uCapacity > INITIAL_CAPACITY);
}

/// <summary>
/// Checks that elements are correctly added when arrays are full.
/// </summary>
QTEST_CASE ( Add_ElementIsCorrectlyAddedWhenArrayIsFull_Test )
{
    // [Preparation]
    const pointer_uint_q INITIAL_CAPACITY = 3U;
    QDynamicArray<int> arFullArray(INITIAL_CAPACITY);
    arFullArray.Add(0);
    arFullArray.Add(0);
    arFullArray.Add(0);
    const int ELEMENT_VALUE = 1;

    // [Execution]
    arFullArray.Add(ELEMENT_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(arFullArray[3], ELEMENT_VALUE);
}

/// <summary>
/// Checks that elements are correctly added at the end of a common array.
/// </summary>
QTEST_CASE ( Add_ElementIsCorrectlyAddedAtTheEnd_Test )
{
    // [Preparation]
    const pointer_uint_q INITIAL_CAPACITY = 3U;
    QDynamicArray<int> arCommonArray(INITIAL_CAPACITY);
    arCommonArray.Add(0);
    const int ELEMENT_VALUE = 1;

    // [Execution]
    arCommonArray.Add(ELEMENT_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(arCommonArray[1], ELEMENT_VALUE);
}

/// <summary>
/// Checks that the count of elements of the array is increased after an element is added.
/// </summary>
QTEST_CASE ( Add_CountIsIncreasedAfterAddingAnElement_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_COUNT = 1;
    const int ELEMENT_VALUE = 1;
    const pointer_uint_q INITIAL_CAPACITY = 3U;
    QDynamicArray<int> arCommonArray(INITIAL_CAPACITY);

    // [Execution]
    arCommonArray.Add(ELEMENT_VALUE);

    // [Verification]
    pointer_uint_q uCount = arCommonArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the copy constructor of the element is called when adding it to the array.
/// </summary>
QTEST_CASE ( Add_CopyConstructorIsCalledForAddedElements_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    const pointer_uint_q EXPECTED_CALLS = 1;
    const pointer_uint_q INITIAL_CAPACITY = 3U;
    QDynamicArray<CallCounter> arCommonArray(INITIAL_CAPACITY);
    CallCounter newElement;
    CallCounter::ResetCounters();

    // [Execution]
    arCommonArray.Add(newElement);

    // [Verification]
    pointer_uint_q uCopyConstructorCalls = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uCopyConstructorCalls, EXPECTED_CALLS);
}

/// <summary>
/// Checks that elements can be inserted at the first position.
/// </summary>
QTEST_CASE ( Insert1_ElementIsCorrectlyInsertedAtFirstPosition_Test )
{
    // [Preparation]
    QDynamicArray<int> arCommonArray;
    arCommonArray.Add(0);
    const int ELEMENT_VALUE = 1;
    const QDynamicArray<int>::QArrayIterator POSITION = arCommonArray.GetFirst();

    // [Execution]
    arCommonArray.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(arCommonArray[0], ELEMENT_VALUE);
}

/// <summary>
/// Checks that elements can be inserted in between of two existing elements.
/// </summary>
QTEST_CASE ( Insert1_ElementIsCorrectlyInsertedInBetween_Test )
{
    // [Preparation]
    QDynamicArray<int> arCommonArray(3U);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    const int ELEMENT_VALUE = 1;
    const QDynamicArray<int>::QArrayIterator POSITION = arCommonArray.GetIterator(1);

    // [Execution]
    arCommonArray.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(arCommonArray[1], ELEMENT_VALUE);
}

/// <summary>
/// Checks that the capacity is increased when elements are added to a full array.
/// </summary>
QTEST_CASE ( Insert1_CapacityIsIncreasedWhenAddingElementsToFullArray_Test )
{
    // [Preparation]
    const pointer_uint_q INITIAL_CAPACITY = 3U;
    QDynamicArray<int> arFullArray(INITIAL_CAPACITY);
    arFullArray.Add(0);
    arFullArray.Add(0);
    arFullArray.Add(0);
    const int ELEMENT_VALUE = 1;
    const QDynamicArray<int>::QArrayIterator POSITION = arFullArray.GetFirst();

    // [Execution]
    arFullArray.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    pointer_uint_q uCapacity =  arFullArray.GetCapacity();
    BOOST_CHECK(uCapacity > INITIAL_CAPACITY);
}

/// <summary>
/// Checks that the count of elements of the array is increased after an element is added.
/// </summary>
QTEST_CASE ( Insert1_CountIsIncreasedAfterAddingAnElement_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_COUNT = 2;
    const int ELEMENT_VALUE = 1;
    const pointer_uint_q INITIAL_CAPACITY = 3U;
    QDynamicArray<int> arCommonArray(INITIAL_CAPACITY);
    arCommonArray.Add(0);
    const QDynamicArray<int>::QArrayIterator POSITION = arCommonArray.GetFirst();

    // [Execution]
    arCommonArray.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    pointer_uint_q uCount = arCommonArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the copy constructor of the element is called when adding it to the array.
/// </summary>
QTEST_CASE ( Insert1_CopyConstructorIsCalledForAddedElements_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    const pointer_uint_q EXPECTED_CALLS = 1;
    const pointer_uint_q INITIAL_CAPACITY = 3U;
    QDynamicArray<CallCounter> arCommonArray(INITIAL_CAPACITY);
    arCommonArray.Add(CallCounter());
    CallCounter newElement;
    CallCounter::ResetCounters();
    const QDynamicArray<CallCounter>::QArrayIterator POSITION = arCommonArray.GetFirst();

    // [Execution]
    arCommonArray.Insert(newElement, POSITION);

    // [Verification]
    pointer_uint_q uCopyConstructorCalls = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uCopyConstructorCalls, EXPECTED_CALLS);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator points to the forward end position.
/// </summary>
QTEST_CASE ( Insert1_AssertionFailsWhenIteratorsPointsToForwardEndPosition_Test )
{
    // [Preparation]
    QDynamicArray<int> arCommonArray;
    arCommonArray.Add(0);
    QDynamicArray<int>::QArrayIterator ITERATOR_END = arCommonArray.GetLast();
    ++ITERATOR_END;
    const bool ASSERTION_FAILED = true;
    const int ELEMENT_VALUE = 1;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.Insert(ELEMENT_VALUE, ITERATOR_END);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the iterator is invalid.
/// </summary>
QTEST_CASE ( Insert1_AssertionFailsWhenIteratorIsInvalid_Test )
{
    // [Preparation]
    QDynamicArray<int> arCommonArray(3U);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    QDynamicArray<int>::QArrayIterator ITERATOR = arCommonArray.GetLast();
    arCommonArray.Remove(ITERATOR);
    const bool ASSERTION_FAILED = true;
    const int ELEMENT_VALUE = 1;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.Insert(ELEMENT_VALUE, ITERATOR);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that elements can be inserted into empty arrays.
/// </summary>
QTEST_CASE ( Insert1_ElementIsInsertedIntoEmptyArray_Test )
{
    // [Preparation]
    QDynamicArray<int> arEmptyArray;
    QDynamicArray<int>::QArrayIterator ITERATOR = arEmptyArray.GetFirst();
    const int ELEMENT_VALUE = 1;

    // [Execution]
    arEmptyArray.Insert(ELEMENT_VALUE, ITERATOR);

    // [Verification]
    BOOST_CHECK_EQUAL(arEmptyArray[0], ELEMENT_VALUE);
}

/// <summary>
/// Checks that elements are inserted at the end when the iterator points to the forward end position.
/// </summary>
QTEST_CASE ( Insert1_ElementIsInsertedAtTheEndWhenIteratorsPointsToForwardEndPosition_Test )
{
    // [Preparation]
    QDynamicArray<int> arCommonArray;
    arCommonArray.Add(0);
    QDynamicArray<int>::QArrayIterator ITERATOR_END = arCommonArray.GetLast();
    ++ITERATOR_END;
    const int ELEMENT_VALUE = 1;

    // [Execution]
    arCommonArray.Insert(ELEMENT_VALUE, ITERATOR_END);

    // [Verification]
    BOOST_CHECK_EQUAL(arCommonArray[1], ELEMENT_VALUE);
}

#endif

/// <summary>
/// Checks that elements can be inserted at the first position.
/// </summary>
QTEST_CASE ( Insert2_ElementIsCorrectlyInsertedAtFirstPosition_Test )
{
    // [Preparation]
    QDynamicArray<int> arCommonArray;
    arCommonArray.Add(0);
    const int ELEMENT_VALUE = 1;
    const pointer_uint_q POSITION = 0;

    // [Execution]
    arCommonArray.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(arCommonArray[0], ELEMENT_VALUE);
}

/// <summary>
/// Checks that elements can be inserted in between of two existing elements.
/// </summary>
QTEST_CASE ( Insert2_ElementIsCorrectlyInsertedInBetween_Test )
{
    // [Preparation]
    QDynamicArray<int> arCommonArray(3U);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    const int ELEMENT_VALUE = 1;
    const pointer_uint_q POSITION = 1;

    // [Execution]
    arCommonArray.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(arCommonArray[1], ELEMENT_VALUE);
}

/// <summary>
/// Checks that the capacity is increased when elements are added to a full array.
/// </summary>
QTEST_CASE ( Insert2_CapacityIsIncreasedWhenAddingElementsToFullArray_Test )
{
    // [Preparation]
    const pointer_uint_q INITIAL_CAPACITY = 3U;
    QDynamicArray<int> arFullArray(INITIAL_CAPACITY);
    arFullArray.Add(0);
    arFullArray.Add(0);
    arFullArray.Add(0);
    const int ELEMENT_VALUE = 1;
    const pointer_uint_q POSITION = 0;

    // [Execution]
    arFullArray.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    pointer_uint_q uCapacity =  arFullArray.GetCapacity();
    BOOST_CHECK(uCapacity > INITIAL_CAPACITY);
}

/// <summary>
/// Checks that the count of elements of the array is increased after an element is added.
/// </summary>
QTEST_CASE ( Insert2_CountIsIncreasedAfterAddingAnElement_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_COUNT = 2;
    const int ELEMENT_VALUE = 1;
    const pointer_uint_q INITIAL_CAPACITY = 3U;
    QDynamicArray<int> arCommonArray(INITIAL_CAPACITY);
    arCommonArray.Add(0);
    const pointer_uint_q POSITION = 0;

    // [Execution]
    arCommonArray.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    pointer_uint_q uCount = arCommonArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the copy constructor of the element is called when adding it to the array.
/// </summary>
QTEST_CASE ( Insert2_CopyConstructorIsCalledForAddedElements_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    const pointer_uint_q EXPECTED_CALLS = 1;
    const pointer_uint_q INITIAL_CAPACITY = 3U;
    QDynamicArray<CallCounter> arCommonArray(INITIAL_CAPACITY);
    arCommonArray.Add(CallCounter());
    CallCounter newElement;
    CallCounter::ResetCounters();
    const pointer_uint_q POSITION = 0;

    // [Execution]
    arCommonArray.Insert(newElement, POSITION);

    // [Verification]
    pointer_uint_q uCopyConstructorCalls = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uCopyConstructorCalls, EXPECTED_CALLS);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the index is out of bounds.
/// </summary>
QTEST_CASE ( Insert2_AssertionFailsWhenIndexIsOutOfBounds_Test )
{
    // [Preparation]
    QDynamicArray<int> arCommonArray;
    arCommonArray.Add(0);
    const pointer_uint_q OUT_OF_BOUNDS_INDEX = arCommonArray.GetCount();
    const bool ASSERTION_FAILED = true;
    const int ELEMENT_VALUE = 1;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.Insert(ELEMENT_VALUE, OUT_OF_BOUNDS_INDEX);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that elements can be inserted into empty arrays.
/// </summary>
QTEST_CASE ( Insert2_ElementIsInsertedIntoEmptyArray_Test )
{
    // [Preparation]
    QDynamicArray<int> arEmptyArray;
    const pointer_uint_q POSITION = 0;
    const int ELEMENT_VALUE = 1;

    // [Execution]
    arEmptyArray.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(arEmptyArray[0], ELEMENT_VALUE);
}

/// <summary>
/// Checks that elements are inserted at the end when the index is out of bounds.
/// </summary>
QTEST_CASE ( Insert2_ElementIsInsertedAtTheEndWhenIndexIsOutOfBounds_Test )
{
    // [Preparation]
    QDynamicArray<int> arCommonArray;
    arCommonArray.Add(0);
    const pointer_uint_q INDEX_OUT_OF_BOUNDS = arCommonArray.GetCount();
    const int ELEMENT_VALUE = 1;

    // [Execution]
    arCommonArray.Insert(ELEMENT_VALUE, INDEX_OUT_OF_BOUNDS);

    // [Verification]
    BOOST_CHECK_EQUAL(arCommonArray[1], ELEMENT_VALUE);
}

#endif

/// <summary>
/// Checks that elements are correctly removed from the last position of the array.
/// </summary>
QTEST_CASE ( Remove1_ElementIsCorrectlyRemovedFromLastPosition_Test )
{
    // [Preparation]
    const bool ELEMENT_DOES_NOT_EXIST = true;
    const int ELEMENT_VALUE = 1;
    QDynamicArray<int> arCommonArray(3U);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    arCommonArray.Add(ELEMENT_VALUE);
    const QDynamicArray<int>::QArrayIterator POSITION = arCommonArray.GetLast();

    // [Execution]
    arCommonArray.Remove(POSITION);

    // [Verification]
    /* [TODO] Thund: Uncomment when Contains method exists
    bool bElementDoesNotExist = !arCommonArray.Contains(ELEMENT_VALUE);
    BOOST_CHECK_EQUAL(bElementDoesNotExist, ELEMENT_DOES_NOT_EXIST);*/
}

/// <summary>
/// Checks that elements are correctly removed from the first position of the array.
/// </summary>
QTEST_CASE ( Remove1_ElementIsCorrectlyRemovedFromFirstPosition_Test )
{
    // [Preparation]
    const bool ELEMENT_DOES_NOT_EXIST = true;
    const int ELEMENT_VALUE = 1;
    QDynamicArray<int> arCommonArray(3U);
    arCommonArray.Add(ELEMENT_VALUE);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    const QDynamicArray<int>::QArrayIterator POSITION = arCommonArray.GetFirst();

    // [Execution]
    arCommonArray.Remove(POSITION);

    // [Verification]
    /* [TODO] Thund: Uncomment when Contains method exists
    bool bElementDoesNotExist = !arCommonArray.Contains(ELEMENT_VALUE);
    BOOST_CHECK_EQUAL(bElementDoesNotExist, ELEMENT_DOES_NOT_EXIST);*/
}

/// <summary>
/// Checks that elements are correctly removed when they are in between of two elements.
/// </summary>
QTEST_CASE ( Remove1_ElementIsCorrectlyRemovedFromBetweenTwoElements_Test )
{
    // [Preparation]
    const bool ELEMENT_DOES_NOT_EXIST = true;
    const int ELEMENT_VALUE = 1;
    QDynamicArray<int> arCommonArray(3U);
    arCommonArray.Add(0);
    arCommonArray.Add(ELEMENT_VALUE);
    arCommonArray.Add(0);
    const QDynamicArray<int>::QArrayIterator POSITION = arCommonArray.GetIterator(1);

    // [Execution]
    arCommonArray.Remove(POSITION);

    // [Verification]
    /* [TODO] Thund: Uncomment when Contains method exists
    bool bElementDoesNotExist = !arCommonArray.Contains(ELEMENT_VALUE);
    BOOST_CHECK_EQUAL(bElementDoesNotExist, ELEMENT_DOES_NOT_EXIST);*/
}

/// <summary>
/// Checks that count of elements in the array decreases after they are removed.
/// </summary>
QTEST_CASE ( Remove1_CountDecreasesAfterRemovingElements_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_COUNT = 2;
    QDynamicArray<int> arCommonArray(3U);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    const QDynamicArray<int>::QArrayIterator POSITION = arCommonArray.GetFirst();

    // [Execution]
    arCommonArray.Remove(POSITION);

    // [Verification]
    pointer_uint_q uCount = arCommonArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the destructor of the element is called when it is removed.
/// </summary>
QTEST_CASE ( Remove1_DestructorOfElementIsCalled_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    const pointer_uint_q EXPECTED_CALLS = 1;
    QDynamicArray<CallCounter> arCommonArray;
    arCommonArray.Add(CallCounter());
    const QDynamicArray<CallCounter>::QArrayIterator POSITION = arCommonArray.GetFirst();
    CallCounter::ResetCounters();

    // [Execution]
    arCommonArray.Remove(POSITION);

    // [Verification]
    pointer_uint_q uDestructorCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorCalls, EXPECTED_CALLS);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator points to the forward end position.
/// </summary>
QTEST_CASE ( Remove1_AssertionFailsWhenIteratorsPointsToForwardEndPosition_Test )
{
    // [Preparation]
    QDynamicArray<int> arCommonArray;
    arCommonArray.Add(0);
    QDynamicArray<int>::QArrayIterator ITERATOR_END = arCommonArray.GetLast();
    ++ITERATOR_END;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.Remove(ITERATOR_END);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the iterator is invalid.
/// </summary>
QTEST_CASE ( Remove1_AssertionFailsWhenInteratorIsInvalid_Test )
{
    // [Preparation]
    QDynamicArray<int> arCommonArray(3U);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    QDynamicArray<int>::QArrayIterator ITERATOR = arCommonArray.GetLast();
    arCommonArray.Remove(ITERATOR);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.Remove(ITERATOR);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that nothing happens when the iterator points to the forward end position.
/// </summary>
QTEST_CASE ( Remove1_NothingHappensWhenIteratorsPointsToForwardEndPosition_Test )
{
    // [Preparation]
    QDynamicArray<int> arCommonArray;
    arCommonArray.Add(0);
    const pointer_uint_q EXPECTED_COUNT = arCommonArray.GetCount();
    QDynamicArray<int>::QArrayIterator ITERATOR_END = arCommonArray.GetLast();
    ++ITERATOR_END;

    // [Execution]
    arCommonArray.Remove(ITERATOR_END);

    // [Verification]
    pointer_uint_q uCount = arCommonArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that nothing happens when the array is empty.
/// </summary>
QTEST_CASE ( Remove1_NothingHappensWhenArrayIsEmpty_Test )
{
    // [Preparation]
    QDynamicArray<int> arCommonArray;
    const pointer_uint_q EXPECTED_COUNT = 0;
    QDynamicArray<int>::QArrayIterator ITERATOR = arCommonArray.GetFirst();

    // [Execution]
    arCommonArray.Remove(ITERATOR);

    // [Verification]
    pointer_uint_q uCount = arCommonArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

#endif

/// <summary>
/// Checks that elements are correctly removed from the last position of the array.
/// </summary>
QTEST_CASE ( Remove2_ElementIsCorrectlyRemovedFromLastPosition_Test )
{
    // [Preparation]
    const bool ELEMENT_DOES_NOT_EXIST = true;
    const int ELEMENT_VALUE = 1;
    QDynamicArray<int> arCommonArray(3U);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    arCommonArray.Add(ELEMENT_VALUE);
    const pointer_uint_q POSITION = arCommonArray.GetCount() - 1U;

    // [Execution]
    arCommonArray.Remove(POSITION);

    // [Verification]
    /* [TODO] Thund: Uncomment when Contains method exists
    bool bElementDoesNotExist = !arCommonArray.Contains(ELEMENT_VALUE);
    BOOST_CHECK_EQUAL(bElementDoesNotExist, ELEMENT_DOES_NOT_EXIST);*/
}

/// <summary>
/// Checks that elements are correctly removed from the first position of the array.
/// </summary>
QTEST_CASE ( Remove2_ElementIsCorrectlyRemovedFromFirstPosition_Test )
{
    // [Preparation]
    const bool ELEMENT_DOES_NOT_EXIST = true;
    const int ELEMENT_VALUE = 1;
    QDynamicArray<int> arCommonArray(3U);
    arCommonArray.Add(ELEMENT_VALUE);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    const pointer_uint_q POSITION = 0;

    // [Execution]
    arCommonArray.Remove(POSITION);

    // [Verification]
    /* [TODO] Thund: Uncomment when Contains method exists
    bool bElementDoesNotExist = !arCommonArray.Contains(ELEMENT_VALUE);
    BOOST_CHECK_EQUAL(bElementDoesNotExist, ELEMENT_DOES_NOT_EXIST);*/
}

/// <summary>
/// Checks that elements are correctly removed when they are in between of two elements.
/// </summary>
QTEST_CASE ( Remove2_ElementIsCorrectlyRemovedFromBetweenTwoElements_Test )
{
    // [Preparation]
    const bool ELEMENT_DOES_NOT_EXIST = true;
    const int ELEMENT_VALUE = 1;
    QDynamicArray<int> arCommonArray(3U);
    arCommonArray.Add(0);
    arCommonArray.Add(ELEMENT_VALUE);
    arCommonArray.Add(0);
    const pointer_uint_q POSITION = 1;

    // [Execution]
    arCommonArray.Remove(POSITION);

    // [Verification]
    /* [TODO] Thund: Uncomment when Contains method exists
    bool bElementDoesNotExist = !arCommonArray.Contains(ELEMENT_VALUE);
    BOOST_CHECK_EQUAL(bElementDoesNotExist, ELEMENT_DOES_NOT_EXIST);*/
}

/// <summary>
/// Checks that count of elements in the array decreases after they are removed.
/// </summary>
QTEST_CASE ( Remove2_CountDecreasesAfterRemovingElements_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_COUNT = 2;
    QDynamicArray<int> arCommonArray(3U);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    const pointer_uint_q POSITION = 0;

    // [Execution]
    arCommonArray.Remove(POSITION);

    // [Verification]
    pointer_uint_q uCount = arCommonArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the destructor of the element is called when it is removed.
/// </summary>
QTEST_CASE ( Remove2_DestructorOfElementIsCalled_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    const pointer_uint_q EXPECTED_CALLS = 1;
    QDynamicArray<CallCounter> arCommonArray;
    arCommonArray.Add(CallCounter());
    const pointer_uint_q POSITION = 0;
    CallCounter::ResetCounters();

    // [Execution]
    arCommonArray.Remove(POSITION);

    // [Verification]
    pointer_uint_q uDestructorCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorCalls, EXPECTED_CALLS);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the index is out of bounds.
/// </summary>
QTEST_CASE ( Remove2_AssertionFailsWhenIndexIsOutOfBounds_Test )
{
    // [Preparation]
    QDynamicArray<int> arCommonArray;
    arCommonArray.Add(0);
    const pointer_uint_q POSITION = arCommonArray.GetCount();
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.Remove(POSITION);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that nothing happens when the index is out of bounds.
/// </summary>
QTEST_CASE ( Remove2_NothingHappensWhenIndexIsOutOfBounds_Test )
{
    // [Preparation]
    QDynamicArray<int> arCommonArray;
    arCommonArray.Add(0);
    const pointer_uint_q EXPECTED_COUNT = arCommonArray.GetCount();
    const pointer_uint_q POSITION = arCommonArray.GetCount();

    // [Execution]
    arCommonArray.Remove(POSITION);

    // [Verification]
    pointer_uint_q uCount = arCommonArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that nothing happens when the array is empty.
/// </summary>
QTEST_CASE ( Remove2_NothingHappensWhenArrayIsEmpty_Test )
{
    // [Preparation]
    QDynamicArray<int> arCommonArray;
    const pointer_uint_q EXPECTED_COUNT = 0;
    const pointer_uint_q POSITION = 0;

    // [Execution]
    arCommonArray.Remove(POSITION);

    // [Verification]
    pointer_uint_q uCount = arCommonArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

#endif

/// <summary>
/// Checks that nothing happens when the array is empty.
/// </summary>
QTEST_CASE ( Clear_NothingHappensWhenArrayIsEmpty_Test )
{
    // [Preparation]
    QDynamicArray<int> arCommonArray;
    const pointer_uint_q EXPECTED_COUNT = 0;

    // [Execution]
    arCommonArray.Clear();

    // [Verification]
    pointer_uint_q uCount = arCommonArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that all the elements are removed when the array is full.
/// </summary>
QTEST_CASE ( Clear_AllElemensAreRemovedWhenArrayIsFull_Test )
{
    // [Preparation]
    QDynamicArray<int> arCommonArray(3U);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    const pointer_uint_q EXPECTED_COUNT = 0;

    // [Execution]
    arCommonArray.Clear();

    // [Verification]
    pointer_uint_q uCount = arCommonArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that all the elements are removed when the array contains some elements.
/// </summary>
QTEST_CASE ( Clear_AllElementsAreRemovedWhenArrayContainsSomeElements_Test )
{
    // [Preparation]
    QDynamicArray<int> arCommonArray(3U);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    const pointer_uint_q EXPECTED_COUNT = 0;

    // [Execution]
    arCommonArray.Clear();

    // [Verification]
    pointer_uint_q uCount = arCommonArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the destructor of every element is called.
/// </summary>
QTEST_CASE ( Clear_DestructorIsCalledForEveryElement_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    QDynamicArray<CallCounter> arCommonArray(3U);
    arCommonArray.Add(CallCounter());
    arCommonArray.Add(CallCounter());
    const pointer_uint_q EXPECTED_CALLS = 2;
    CallCounter::ResetCounters();

    // [Execution]
    arCommonArray.Clear();

    // [Verification]
    pointer_uint_q uDestructorCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorCalls, EXPECTED_CALLS);
}

/// <summary>
/// Checks that the capacity of the destination allocator is increased when it is lower than the capacity of the source.
/// </summary>
QTEST_CASE ( Clone_CapacityOfDestinationIsIncreasedWhenItIsLowerThanCapacityOfSource_Test )
{
    // [Preparation]
    QDynamicArray<int> arCommonArray(10U);
    for(int i = 0; i < 10; ++i)
        arCommonArray.Add(i);
    QDynamicArray<int> arDestination;
    const pointer_uint_q INITIAL_CAPACITY = arDestination.GetCapacity();
    const pointer_uint_q EXPECTED_CAPACITY = arCommonArray.GetCapacity();

    // [Execution]
    arCommonArray.Clone(arDestination);

    // [Verification]
    pointer_uint_q uCapacity = arDestination.GetCapacity();
    BOOST_CHECK(uCapacity > INITIAL_CAPACITY);
    BOOST_CHECK_EQUAL(uCapacity, EXPECTED_CAPACITY);
}

/// <summary>
/// Checks that no elements are copied when the source array is empty.
/// </summary>
QTEST_CASE ( Clone_NoElementsAreCopiedWhenSourceArrayIsEmpty_Test )
{
    // [Preparation]
    QDynamicArray<int> arCommonArray;
    QDynamicArray<int> arDestination;

    // [Execution]
    arCommonArray.Clone(arDestination);

    // [Verification]
    pointer_uint_q uSourceCount = arCommonArray.GetCount();
    pointer_uint_q uDestinationCount = arDestination.GetCount();

    BOOST_CHECK_EQUAL(uSourceCount, uDestinationCount);
}

/// <summary>
/// Checks that all elements are correctly copied when the source array is partially full.
/// </summary>
QTEST_CASE ( Clone_ElementsAreCorrectlyCopiedWhenSourceArrayIsPartiallyFull_Test )
{
    // [Preparation]
    const bool ARE_EQUAL = true;
    QDynamicArray<int> arCommonArray(10U);
    for(int i = 0; i < 5; ++i)
        arCommonArray.Add(i);
    QDynamicArray<int> arDestination;

    // [Execution]
    arCommonArray.Clone(arDestination);

    // [Verification]
    bool bAreEqual = true;

    for(int i = 0; i < 5; ++i)
        bAreEqual = bAreEqual && (arCommonArray[i] == arDestination[i]);

    pointer_uint_q uSourceCount = arCommonArray.GetCount();
    pointer_uint_q uDestinationCount = arDestination.GetCount();

    BOOST_CHECK_EQUAL(uSourceCount, uDestinationCount);
    BOOST_CHECK_EQUAL(bAreEqual, ARE_EQUAL);
}

/// <summary>
/// Checks that all elements are correctly copied when the source array is full.
/// </summary>
QTEST_CASE ( Clone_ElementsAreCorrectlyCopiedWhenSourceArrayIsFull_Test )
{
    // [Preparation]
    const bool ARE_EQUAL = true;
    QDynamicArray<int> arCommonArray(10U);
    for(int i = 0; i < 10; ++i)
        arCommonArray.Add(i);
    QDynamicArray<int> arDestination;

    // [Execution]
    arCommonArray.Clone(arDestination);

    // [Verification]
    bool bAreEqual = true;

    for(int i = 0; i < 10; ++i)
        bAreEqual = bAreEqual && (arCommonArray[i] == arDestination[i]);

    pointer_uint_q uSourceCount = arCommonArray.GetCount();
    pointer_uint_q uDestinationCount = arDestination.GetCount();

    BOOST_CHECK_EQUAL(uSourceCount, uDestinationCount);
    BOOST_CHECK_EQUAL(bAreEqual, ARE_EQUAL);
}

/// <summary>
/// Checks that all elements are correctly copied when the destination array is not empty.
/// </summary>
QTEST_CASE ( Clone_ElementsAreCorrectlyCopiedWhenDestinationIsNotEmpty_Test )
{
    // [Preparation]
    const bool ARE_EQUAL = true;
    QDynamicArray<int> arCommonArray(10U);
    for(int i = 0; i < 10; ++i)
        arCommonArray.Add(i);
    QDynamicArray<int> arDestination;
    for(int i = 10; i < 15; ++i)
        arDestination.Add(i);

    // [Execution]
    arCommonArray.Clone(arDestination);

    // [Verification]
    bool bAreEqual = true;

    for(int i = 0; i < 10; ++i)
        bAreEqual = bAreEqual && (arCommonArray[i] == arDestination[i]);

    pointer_uint_q uSourceCount = arCommonArray.GetCount();
    pointer_uint_q uDestinationCount = arDestination.GetCount();

    BOOST_CHECK_EQUAL(uSourceCount, uDestinationCount);
    BOOST_CHECK_EQUAL(bAreEqual, ARE_EQUAL);
}

/// <summary>
/// Checks that neither the destructor nor the copy constructor of any element is called when cloning.
/// </summary>
QTEST_CASE ( Clone_NeitherDestructorNorConstructorsAreCalledWhenCloning_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    const pointer_uint_q EXPECTED_CALLS = 0;
    QDynamicArray<CallCounter> arCommonArray(10U);
    for(int i = 0; i < 10; ++i)
        arCommonArray.Add(CallCounter());
    QDynamicArray<CallCounter> arDestination;
    for(int i = 10; i < 15; ++i)
        arCommonArray.Add(CallCounter());

    CallCounter::ResetCounters();

    // [Execution]
    arCommonArray.Clone(arDestination);

    // [Verification]
    pointer_uint_q uDestructorCalls = CallCounter::GetDestructorCallsCount();
    pointer_uint_q uCopyConstructorCalls = CallCounter::GetCopyConstructorCallsCount();

    BOOST_CHECK_EQUAL(uDestructorCalls, EXPECTED_CALLS);
    BOOST_CHECK_EQUAL(uCopyConstructorCalls, EXPECTED_CALLS);
}

/// <sumary>
/// Checks that it returns False when the array is empty.
/// </sumary>
QTEST_CASE( Contains_ReturnsFalseWhenArrayIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::u32_q;

    // [Preparation]
    const u32_q INPUT_ELEMENT = 2U;
    QDynamicArray<u32_q> dynamicArray;
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = dynamicArray.Contains(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns ELEMENT_NOT_FOUND when the array is empty.
/// </sumary>
QTEST_CASE( IndexOf1_ReturnsElementNotFoundWhenArrayIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::u32_q;

    // [Preparation]
    const u32_q INPUT_ELEMENT = 2U;
    QDynamicArray<u32_q> dynamicArray;
    const pointer_uint_q EXPECTED_RESULT = QDynamicArray<u32_q>::ELEMENT_NOT_FOUND;

    // [Execution]
    pointer_uint_q uResult = dynamicArray.IndexOf(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that elements can be added to empty arrays.
/// </summary>
QTEST_CASE ( AddRange_ElementIsCorrectlyAddedToEmptyArray_Test )
{
    // [Preparation]
    QDynamicArray<int> arEmptyArray;
    const int EXPECTED_VALUES[] = {2, 3, 4};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetIterator(1);
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetIterator(3);
    
    // [Execution]
    arEmptyArray.AddRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arEmptyArray == arExpectedArray);
}

/// <summary>
/// Checks that the capacity is increased when elements are added to a full array.
/// </summary>
QTEST_CASE ( AddRange_CapacityIsIncreasedWhenAddingElementsToFullArray_Test )
{
    // [Preparation]
    const pointer_uint_q INITIAL_CAPACITY = 1U;
    QDynamicArray<int> arFullArray(INITIAL_CAPACITY);
    arFullArray.Add(0);
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetIterator(1);
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetIterator(3);
    
    // [Execution]
    arFullArray.AddRange(itFirst, itLast);

    // [Verification]
    pointer_uint_q uCapacity = arFullArray.GetCapacity();
    BOOST_CHECK(uCapacity > INITIAL_CAPACITY);
}

/// <summary>
/// Checks that elements are correctly added when arrays are full.
/// </summary>
QTEST_CASE ( AddRange_ElementRangeIsCorrectlyAddedWhenArrayIsFull_Test )
{
    // [Preparation]
    const pointer_uint_q INITIAL_CAPACITY = 3U;
    QDynamicArray<int> arFullArray(INITIAL_CAPACITY);
    arFullArray.Add(8);
    arFullArray.Add(9);
    arFullArray.Add(0);
    const int EXPECTED_VALUES[] = {8, 9, 0, 2, 3, 4};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetIterator(1);
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetIterator(3);

    // [Execution]
    arFullArray.AddRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arFullArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly added at the end of a common array.
/// </summary>
QTEST_CASE ( AddRange_ElementRangeIsCorrectlyAddedAtTheEnd_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 1, 2, 3, 4, 5};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetIterator(2);
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetIterator(4);

    // [Execution]
    arCommonArray.AddRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that the count of elements of the array is increased after some elements are added.
/// </summary>
QTEST_CASE ( AddRange_CountIsIncreasedAfterAddingElements_Test )
{
    // [Preparation]
    const pointer_uint_q INITIAL_COUNT = 1U;
    QDynamicArray<int> arCommonArray(3);
    arCommonArray.Add(0);
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetIterator(1);
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetIterator(3);
    
    // [Execution]
    arCommonArray.AddRange(itFirst, itLast);

    // [Verification]
    pointer_uint_q uCount = arCommonArray.GetCount();
    BOOST_CHECK(uCount > INITIAL_COUNT);
}

/// <summary>
/// Checks that the copy constructor of the elements is called when adding them to the array.
/// </summary>
QTEST_CASE ( AddRange_CopyConstructorIsCalledForAddedElements_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    const pointer_uint_q EXPECTED_CALLS = 3;
    const CallCounter COMMON_VALUES[] = {CallCounter()};
    QDynamicArray<CallCounter> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(CallCounter));
    const CallCounter ELEMENT_VALUES[] = {CallCounter(), CallCounter(), CallCounter()};
    QDynamicArray<CallCounter> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(CallCounter));
    QDynamicArray<CallCounter>::QArrayIterator itFirst = arInputArray.GetIterator(0);
    QDynamicArray<CallCounter>::QArrayIterator itLast = arInputArray.GetIterator(2);
    CallCounter newElement;
    CallCounter::ResetCounters();

    // [Execution]
    arCommonArray.AddRange(itFirst, itLast);

    // [Verification]
    pointer_uint_q uCopyConstructorCalls = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uCopyConstructorCalls, EXPECTED_CALLS);
}

/// <summary>
/// Checks that elements are correctly added at the end when both iterators are equal.
/// </summary>
QTEST_CASE ( AddRange_ElementRangeIsCorrectlyAddedWhenBothIteratorsAreEqual_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 1, 2, 3};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetIterator(2);
    QDynamicArray<int>::QArrayIterator itLast = itFirst;

    // [Execution]
    arCommonArray.AddRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly added at the end of a common array when using all the elements of another array.
/// </summary>
QTEST_CASE ( AddRange_ElementRangeIsCorrectlyAddedWhenUsingAllTheElementsOfAnotherArray_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 1, 2, 1, 2, 3, 4, 5};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetFirst();
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetLast();

    // [Execution]
    arCommonArray.AddRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly added at the end of a common array when using elements of the same array.
/// </summary>
QTEST_CASE ( AddRange_ElementRangeIsCorrectlyAddedWhenUsingElementsOfTheSameArray_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 1, 2, 1, 2};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arCommonArray.GetIterator(1);
    QDynamicArray<int>::QArrayIterator itLast = arCommonArray.GetLast();

    // [Execution]
    arCommonArray.AddRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the last element is anterior to the first element in the range.
/// </summary>
QTEST_CASE ( AddRange_AssertionFailsWhenLastElementIsAnteriorToFirstElement_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetLast();
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetFirst();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.AddRange(itFirst, itLast);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the first element points to the end position.
/// </summary>
QTEST_CASE ( AddRange_AssertionFailsWhenFirstElementIsEnd_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetLast();
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetLast();
    ++itFirst;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.AddRange(itFirst, itLast);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the last element points to the end position.
/// </summary>
QTEST_CASE ( AddRange_AssertionFailsWhenLastElementIsEnd_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetLast();
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetLast();
    ++itLast;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.AddRange(itFirst, itLast);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that elements can be inserted at the first position.
/// </summary>
QTEST_CASE ( InsertRange1_ElementsAreCorrectlyInsertedAtFirstPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {2, 3, 4, 0, 1, 2};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int INPUT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(INPUT_VALUES, sizeof(INPUT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetIterator(1);
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetIterator(3);
    const pointer_uint_q POSITION = 0;

    // [Execution]
    arCommonArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that elements can be inserted in between of two existing elements.
/// </summary>
QTEST_CASE ( InsertRange1_ElementsAreCorrectlyInsertedInBetween_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 2, 3, 4, 1, 2};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int INPUT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(INPUT_VALUES, sizeof(INPUT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetIterator(1);
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetIterator(3);
    const pointer_uint_q POSITION = 1;


    // [Execution]
    arCommonArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that the capacity is increased when elements are added to a full array.
/// </summary>
QTEST_CASE ( InsertRange1_CapacityIsIncreasedWhenAddingElementsToFullArray_Test )
{
    // [Preparation]
    const pointer_uint_q INITIAL_CAPACITY = 1U;
    QDynamicArray<int> arFullArray(INITIAL_CAPACITY);
    arFullArray.Add(0);
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetIterator(1);
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetIterator(3);
    const pointer_uint_q POSITION = 0;
    
    // [Execution]
    arFullArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    pointer_uint_q uCapacity = arFullArray.GetCapacity();
    BOOST_CHECK(uCapacity > INITIAL_CAPACITY);
}

/// <summary>
/// Checks that the count of elements of the array is increased after an element is added.
/// </summary>
QTEST_CASE ( InsertRange1_CountIsIncreasedAfterAddingAnElement_Test )
{
    // [Preparation]
    const pointer_uint_q INITIAL_COUNT = 1U;
    QDynamicArray<int> arCommonArray(3);
    arCommonArray.Add(0);
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetIterator(1);
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetIterator(3);
    const pointer_uint_q POSITION = 0;
    
    // [Execution]
    arCommonArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    pointer_uint_q uCount = arCommonArray.GetCount();
    BOOST_CHECK(uCount > INITIAL_COUNT);
}

/// <summary>
/// Checks that the copy constructor of the element is called when adding it to the array.
/// </summary>
QTEST_CASE ( InsertRange1_CopyConstructorIsCalledForAddedElements_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    const pointer_uint_q EXPECTED_CALLS = 3;
    const CallCounter COMMON_VALUES[] = {CallCounter()};
    QDynamicArray<CallCounter> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(CallCounter));
    const CallCounter ELEMENT_VALUES[] = {CallCounter(), CallCounter(), CallCounter()};
    QDynamicArray<CallCounter> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(CallCounter));
    QDynamicArray<CallCounter>::QArrayIterator itFirst = arInputArray.GetIterator(0);
    QDynamicArray<CallCounter>::QArrayIterator itLast = arInputArray.GetIterator(2);
    const pointer_uint_q POSITION = 0;

    CallCounter newElement;
    CallCounter::ResetCounters();

    // [Execution]
    arCommonArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    pointer_uint_q uCopyConstructorCalls = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uCopyConstructorCalls, EXPECTED_CALLS);
}

/// <summary>
/// Checks that elements are correctly inserted when both positions are equal.
/// </summary>
QTEST_CASE ( InsertRange1_ElementRangeIsCorrectlyAddedWhenBothIteratorsAreEqual_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {3, 0, 1, 2};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetIterator(2);
    QDynamicArray<int>::QArrayIterator itLast = itFirst;
    const pointer_uint_q POSITION = 0;

    // [Execution]
    arCommonArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly added at the end of a common array when using all the elements of another array.
/// </summary>
QTEST_CASE ( InsertRange1_ElementRangeIsCorrectlyAddedWhenUsingAllTheElementsOfAnotherArray_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {1, 2, 3, 4, 5, 0, 1, 2};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetFirst();
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetLast();
    const pointer_uint_q POSITION = 0;

    // [Execution]
    arCommonArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the last element is anterior to the first element in the range.
/// </summary>
QTEST_CASE ( InsertRange1_AssertionFailsWhenLastElementIsAnteriorToFirstElement_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetLast();
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetFirst();
    const pointer_uint_q POSITION = 0;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.InsertRange(itFirst, itLast, POSITION);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the first element points to the end position.
/// </summary>
QTEST_CASE ( InsertRange1_AssertionFailsWhenFirstElementIsEnd_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetLast();
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetLast();
    ++itFirst;
    const pointer_uint_q POSITION = 0;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.InsertRange(itFirst, itLast, POSITION);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the last element points to the end position.
/// </summary>
QTEST_CASE ( InsertRange1_AssertionFailsWhenLastElementIsEnd_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetLast();
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetLast();
    ++itLast;
    const pointer_uint_q POSITION = 0;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.InsertRange(itFirst, itLast, POSITION);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the insertion position is not lower than the number of elements in the array.
/// </summary>
QTEST_CASE ( InsertRange1_AssertionFailsWhenInsertionPositionIsNotLowerThanCount_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetFirst();
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetLast();
    const pointer_uint_q POSITION = arCommonArray.GetCount();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.InsertRange(itFirst, itLast, POSITION);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that elements can be inserted into empty arrays.
/// </summary>
QTEST_CASE ( InsertRange1_ElementIsInsertedIntoEmptyArray_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {2, 3, 4};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int INPUT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(INPUT_VALUES, sizeof(INPUT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetIterator(1);
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetIterator(3);
    QDynamicArray<int> arEmptyArray(5);
    const pointer_uint_q POSITION = 0;

    // [Execution]
    arEmptyArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(arEmptyArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are inserted at the end when the insertion position is not lower than the number of elements in the array.
/// </summary>
QTEST_CASE ( InsertRange1_ElementIsInsertedAtTheEndWhenInsertionPositionIsNotLowerThanCount_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 1, 2, 2, 3, 4};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int INPUT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(INPUT_VALUES, sizeof(INPUT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetIterator(1);
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetIterator(3);
    const pointer_uint_q POSITION = arCommonArray.GetCount();

    // [Execution]
    arCommonArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

#endif

/// <summary>
/// Checks that elements can be inserted at the first position.
/// </summary>
QTEST_CASE ( InsertRange2_ElementsAreCorrectlyInsertedAtFirstPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {2, 3, 4, 0, 1, 2};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int INPUT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(INPUT_VALUES, sizeof(INPUT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetIterator(1);
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetIterator(3);
    const QDynamicArray<int>::QArrayIterator POSITION = arCommonArray.GetFirst();

    // [Execution]
    arCommonArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that elements can be inserted in between of two existing elements.
/// </summary>
QTEST_CASE ( InsertRange2_ElementsAreCorrectlyInsertedInBetween_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 2, 3, 4, 1, 2};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int INPUT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(INPUT_VALUES, sizeof(INPUT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetIterator(1);
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetIterator(3);
    const QDynamicArray<int>::QArrayIterator POSITION = arCommonArray.GetIterator(1);

    // [Execution]
    arCommonArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that the capacity is increased when elements are added to a full array.
/// </summary>
QTEST_CASE ( InsertRange2_CapacityIsIncreasedWhenAddingElementsToFullArray_Test )
{
    // [Preparation]
    const pointer_uint_q INITIAL_CAPACITY = 1U;
    QDynamicArray<int> arFullArray(INITIAL_CAPACITY);
    arFullArray.Add(0);
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetIterator(1);
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetIterator(3);
    const QDynamicArray<int>::QArrayIterator POSITION = arFullArray.GetFirst();
    
    // [Execution]
    arFullArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    pointer_uint_q uCapacity = arFullArray.GetCapacity();
    BOOST_CHECK(uCapacity > INITIAL_CAPACITY);
}

/// <summary>
/// Checks that the count of elements of the array is increased after an element is added.
/// </summary>
QTEST_CASE ( InsertRange2_CountIsIncreasedAfterAddingAnElement_Test )
{
    // [Preparation]
    const pointer_uint_q INITIAL_COUNT = 1U;
    QDynamicArray<int> arCommonArray(3);
    arCommonArray.Add(0);
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetIterator(1);
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetIterator(3);
    const QDynamicArray<int>::QArrayIterator POSITION = arCommonArray.GetFirst();
    
    // [Execution]
    arCommonArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    pointer_uint_q uCount = arCommonArray.GetCount();
    BOOST_CHECK(uCount > INITIAL_COUNT);
}

/// <summary>
/// Checks that the copy constructor of the element is called when adding it to the array.
/// </summary>
QTEST_CASE ( InsertRange2_CopyConstructorIsCalledForAddedElements_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    const pointer_uint_q EXPECTED_CALLS = 3;
    const CallCounter COMMON_VALUES[] = {CallCounter()};
    QDynamicArray<CallCounter> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(CallCounter));
    const CallCounter ELEMENT_VALUES[] = {CallCounter(), CallCounter(), CallCounter()};
    QDynamicArray<CallCounter> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(CallCounter));
    QDynamicArray<CallCounter>::QArrayIterator itFirst = arInputArray.GetIterator(0);
    QDynamicArray<CallCounter>::QArrayIterator itLast = arInputArray.GetIterator(2);
    const QDynamicArray<CallCounter>::QArrayIterator POSITION = arCommonArray.GetFirst();

    CallCounter newElement;
    CallCounter::ResetCounters();

    // [Execution]
    arCommonArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    pointer_uint_q uCopyConstructorCalls = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uCopyConstructorCalls, EXPECTED_CALLS);
}

/// <summary>
/// Checks that elements are correctly added at the end of a common array.
/// </summary>
QTEST_CASE ( InsertRange2_ElementRangeIsCorrectlyAddedWhenBothIteratorsAreEqual_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {3, 0, 1, 2};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetIterator(2);
    QDynamicArray<int>::QArrayIterator itLast = itFirst;
    const QDynamicArray<int>::QArrayIterator POSITION = arCommonArray.GetFirst();

    // [Execution]
    arCommonArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly added at the end of a common array when using all the elements of another array.
/// </summary>
QTEST_CASE ( InsertRange2_ElementRangeIsCorrectlyAddedWhenUsingAllTheElementsOfAnotherArray_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {1, 2, 3, 4, 5, 0, 1, 2};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetFirst();
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetLast();
    const QDynamicArray<int>::QArrayIterator POSITION = arCommonArray.GetFirst();

    // [Execution]
    arCommonArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the last element is anterior to the first element in the range.
/// </summary>
QTEST_CASE ( InsertRange2_AssertionFailsWhenLastElementIsAnteriorToFirstElement_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetLast();
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetFirst();
    const QDynamicArray<int>::QArrayIterator POSITION = arCommonArray.GetFirst();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.InsertRange(itFirst, itLast, POSITION);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the first element points to the end position.
/// </summary>
QTEST_CASE ( InsertRange2_AssertionFailsWhenFirstElementIsEnd_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetLast();
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetLast();
    ++itFirst;
    const QDynamicArray<int>::QArrayIterator POSITION = arCommonArray.GetFirst();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.InsertRange(itFirst, itLast, POSITION);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the last element points to the end position.
/// </summary>
QTEST_CASE ( InsertRange2_AssertionFailsWhenLastElementIsEnd_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetLast();
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetLast();
    ++itLast;
    const QDynamicArray<int>::QArrayIterator POSITION = arCommonArray.GetFirst();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.InsertRange(itFirst, itLast, POSITION);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the insertion position points to the end position.
/// </summary>
QTEST_CASE ( InsertRange2_AssertionFailsWhenInsertionPositionIsEnd_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetFirst();
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetLast();
    QDynamicArray<int>::QArrayIterator POSITION = arCommonArray.GetLast();
    ++POSITION;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.InsertRange(itFirst, itLast, POSITION);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that elements can be inserted into empty arrays.
/// </summary>
QTEST_CASE ( InsertRange2_ElementIsInsertedIntoEmptyArray_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {2, 3, 4};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int INPUT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(INPUT_VALUES, sizeof(INPUT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetIterator(1);
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetIterator(3);
    QDynamicArray<int> arEmptyArray(5);
    arEmptyArray.Add(0);
    const QDynamicArray<int>::QArrayIterator POSITION = arEmptyArray.GetFirst();
    arEmptyArray.Clear();

    // [Execution]
    arEmptyArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(arEmptyArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are inserted at the end when the insertion position points to the forward end position.
/// </summary>
QTEST_CASE ( InsertRange2_ElementIsInsertedAtTheEndWhenInsertionPositionPointsToForwardEndPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 1, 2, 2, 3, 4};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int INPUT_VALUES[] = {1, 2, 3, 4, 5};
    QDynamicArray<int> arInputArray(INPUT_VALUES, sizeof(INPUT_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arInputArray.GetIterator(1);
    QDynamicArray<int>::QArrayIterator itLast = arInputArray.GetIterator(3);
    QDynamicArray<int>::QArrayIterator POSITION = arCommonArray.GetLast();
    ++POSITION;

    // [Execution]
    arCommonArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

#endif

/// <summary>
/// Checks that elements are correctly removed from the last position of the array.
/// </summary>
QTEST_CASE ( RemoveRange1_ElementsAreCorrectlyRemovedFromLastPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arCommonArray.GetIterator(3);
    QDynamicArray<int>::QArrayIterator itLast = arCommonArray.GetLast();

    // [Execution]
    arCommonArray.RemoveRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly removed from the first position of the array.
/// </summary>
QTEST_CASE ( RemoveRange1_ElementsAreCorrectlyRemovedFromFirstPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {3, 4, 5};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arCommonArray.GetFirst();
    QDynamicArray<int>::QArrayIterator itLast = arCommonArray.GetIterator(2);

    // [Execution]
    arCommonArray.RemoveRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly removed when they are in between of two elements.
/// </summary>
QTEST_CASE ( RemoveRange1_ElementsAreCorrectlyRemovedFromBetweenTwoElements_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 4, 5};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arCommonArray.GetIterator(1);
    QDynamicArray<int>::QArrayIterator itLast = arCommonArray.GetIterator(3);

    // [Execution]
    arCommonArray.RemoveRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that all elements of the array can be removed.
/// </summary>
QTEST_CASE ( RemoveRange1_AllElementsCanBeRemoved_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    QDynamicArray<int> arExpectedArray;
    QDynamicArray<int>::QArrayIterator itFirst = arCommonArray.GetFirst();
    QDynamicArray<int>::QArrayIterator itLast = arCommonArray.GetLast();

    // [Execution]
    arCommonArray.RemoveRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly removed when both positions are the same.
/// </summary>
QTEST_CASE ( RemoveRange1_ElementsAreCorrectlyRemovedWhenBothPositionsAreTheSame_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 2, 3, 4, 5};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arCommonArray.GetIterator(1);
    QDynamicArray<int>::QArrayIterator itLast = itFirst;

    // [Execution]
    arCommonArray.RemoveRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that count of elements in the array decreases after they are removed.
/// </summary>
QTEST_CASE ( RemoveRange1_CountDecreasesAfterRemovingElements_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_COUNT = 3;
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));

    QDynamicArray<int>::QArrayIterator itFirst = arCommonArray.GetIterator(1);
    QDynamicArray<int>::QArrayIterator itLast = arCommonArray.GetIterator(3);

    // [Execution]
    arCommonArray.RemoveRange(itFirst, itLast);

    // [Verification]
    pointer_uint_q uCount = arCommonArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the destructor of each element is called when it is removed.
/// </summary>
QTEST_CASE ( RemoveRange1_DestructorOfEachElementIsCalled_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    const pointer_uint_q EXPECTED_CALLS = 2;
    const CallCounter COMMON_VALUES[] = {CallCounter(), CallCounter(), CallCounter()};
    QDynamicArray<CallCounter> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(CallCounter));

    QDynamicArray<CallCounter>::QArrayIterator itFirst = arCommonArray.GetIterator(1);
    QDynamicArray<CallCounter>::QArrayIterator itLast = arCommonArray.GetIterator(2);
    CallCounter::ResetCounters();

    // [Execution]
    arCommonArray.RemoveRange(itFirst, itLast);

    // [Verification]
    pointer_uint_q uDestructorCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorCalls, EXPECTED_CALLS);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the last element is anterior to the first element in the range.
/// </summary>
QTEST_CASE ( RemoveRange1_AssertionFailsWhenLastElementIsAnteriorToFirstElement_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arCommonArray.GetLast();
    QDynamicArray<int>::QArrayIterator itLast = arCommonArray.GetFirst();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.RemoveRange(itFirst, itLast);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the first element points to the end position.
/// </summary>
QTEST_CASE ( RemoveRange1_AssertionFailsWhenFirstElementIsEnd_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arCommonArray.GetLast();
    QDynamicArray<int>::QArrayIterator itLast = arCommonArray.GetLast();
    ++itFirst;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.RemoveRange(itFirst, itLast);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the last element points to the end position.
/// </summary>
QTEST_CASE ( RemoveRange1_AssertionFailsWhenLastElementIsEnd_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arCommonArray.GetLast();
    QDynamicArray<int>::QArrayIterator itLast = arCommonArray.GetLast();
    ++itLast;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.RemoveRange(itFirst, itLast);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that elements are correctly removed from the last position of the array.
/// </summary>
QTEST_CASE ( RemoveRange2_ElementsAreCorrectlyRemovedFromLastPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const pointer_uint_q FIRST = 3U;
    const pointer_uint_q LAST = 5U;

    // [Execution]
    arCommonArray.RemoveRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly removed from the first position of the array.
/// </summary>
QTEST_CASE ( RemoveRange2_ElementsAreCorrectlyRemovedFromFirstPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {3, 4, 5};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const pointer_uint_q FIRST = 0;
    const pointer_uint_q LAST = 2U;

    // [Execution]
    arCommonArray.RemoveRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly removed when they are in between of two elements.
/// </summary>
QTEST_CASE ( RemoveRange2_ElementsAreCorrectlyRemovedFromBetweenTwoElements_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 4, 5};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const pointer_uint_q FIRST = 1U;
    const pointer_uint_q LAST = 3U;

    // [Execution]
    arCommonArray.RemoveRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that all elements of the array can be removed.
/// </summary>
QTEST_CASE ( RemoveRange2_AllElementsCanBeRemoved_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    QDynamicArray<int> arExpectedArray;
    const pointer_uint_q FIRST = 0;
    const pointer_uint_q LAST = arCommonArray.GetCount() - 1U;

    // [Execution]
    arCommonArray.RemoveRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly removed when both positions are the same.
/// </summary>
QTEST_CASE ( RemoveRange2_ElementsAreCorrectlyRemovedWhenBothPositionsAreTheSame_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 2, 3, 4, 5};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const pointer_uint_q FIRST = 1U;
    const pointer_uint_q LAST = FIRST;

    // [Execution]
    arCommonArray.RemoveRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that count of elements in the array decreases after they are removed.
/// </summary>
QTEST_CASE ( RemoveRange2_CountDecreasesAfterRemovingElements_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_COUNT = 3;
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const pointer_uint_q FIRST = 1U;
    const pointer_uint_q LAST = 3U;

    // [Execution]
    arCommonArray.RemoveRange(FIRST, LAST);

    // [Verification]
    pointer_uint_q uCount = arCommonArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the destructor of each element is called when it is removed.
/// </summary>
QTEST_CASE ( RemoveRange2_DestructorOfEachElementIsCalled_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    const pointer_uint_q EXPECTED_CALLS = 2;
    const CallCounter COMMON_VALUES[] = {CallCounter(), CallCounter(), CallCounter()};
    QDynamicArray<CallCounter> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(CallCounter));
    const pointer_uint_q FIRST = 1U;
    const pointer_uint_q LAST = 2U;
    CallCounter::ResetCounters();

    // [Execution]
    arCommonArray.RemoveRange(FIRST, LAST);

    // [Verification]
    pointer_uint_q uDestructorCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorCalls, EXPECTED_CALLS);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the last element is anterior to the first element in the range.
/// </summary>
QTEST_CASE ( RemoveRange2_AssertionFailsWhenLastElementIsAnteriorToFirstElement_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const pointer_uint_q FIRST = 1U;
    const pointer_uint_q LAST = 0;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.RemoveRange(FIRST, LAST);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the first position is not lower than the number of elements in the array.
/// </summary>
QTEST_CASE ( RemoveRange2_AssertionFailsWhenFirstPositionIsNotLowerThanCount_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const pointer_uint_q FIRST = arCommonArray.GetCount();
    const pointer_uint_q LAST = 2U;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.RemoveRange(FIRST, LAST);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the last position is not lower than the number of elements in the array
/// </summary>
QTEST_CASE ( RemoveRange2_AssertionFailsWhenLastPositionIsNotLowerThanCount_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const pointer_uint_q FIRST = 1U;
    const pointer_uint_q LAST = arCommonArray.GetCount();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.RemoveRange(FIRST, LAST);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that elements are correctly retrieved from the last position of the array.
/// </summary>
QTEST_CASE ( GetRange1_ElementsAreCorrectlyGotFromLastPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {3, 4, 5};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arCommonArray.GetIterator(3);
    QDynamicArray<int>::QArrayIterator itLast = arCommonArray.GetLast();

    // [Execution]
    QDynamicArray<int> arReturnedArray = arCommonArray.GetRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arReturnedArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly retrieved from the first position of the array.
/// </summary>
QTEST_CASE ( GetRange1_ElementsAreCorrectlyGotFromFirstPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arCommonArray.GetFirst();
    QDynamicArray<int>::QArrayIterator itLast = arCommonArray.GetIterator(2);
    
    // [Execution]
    QDynamicArray<int> arReturnedArray = arCommonArray.GetRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arReturnedArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly retrieved when they are in between of two elements.
/// </summary>
QTEST_CASE ( GetRange1_ElementsAreCorrectlyGotFromBetweenTwoElements_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {1, 2, 3};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arCommonArray.GetIterator(1);
    QDynamicArray<int>::QArrayIterator itLast = arCommonArray.GetIterator(3);
    
    // [Execution]
    QDynamicArray<int> arReturnedArray = arCommonArray.GetRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arReturnedArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly removed when both positions are the same.
/// </summary>
QTEST_CASE ( GetRange1_ElementsAreCorrectlyRemovedWhenBothPositionsAreTheSame_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {1};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arCommonArray.GetIterator(1);
    QDynamicArray<int>::QArrayIterator itLast = itFirst;
    
    // [Execution]
    QDynamicArray<int> arReturnedArray = arCommonArray.GetRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arReturnedArray == arExpectedArray);
}

/// <summary>
/// Checks that the copy constructor of each element is called when it is copied, at least once.
/// </summary>
QTEST_CASE ( GetRange1_CopyConstructorOfEachElementIsCalledAtLeastOnce_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    const pointer_uint_q EXPECTED_CALLS = 2;
    const CallCounter COMMON_VALUES[] = {CallCounter(), CallCounter(), CallCounter()};
    QDynamicArray<CallCounter> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(CallCounter));

    QDynamicArray<CallCounter>::QArrayIterator itFirst = arCommonArray.GetIterator(1);
    QDynamicArray<CallCounter>::QArrayIterator itLast = arCommonArray.GetIterator(2);
    CallCounter::ResetCounters();

    // [Execution]
    arCommonArray.GetRange(itFirst, itLast);

    // [Verification]
    pointer_uint_q uCopyConstructor = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK(uCopyConstructor >= EXPECTED_CALLS);
}

/// <summary>
/// Checks that all elements of the array can be retrieved.
/// </summary>
QTEST_CASE ( GetRange1_AllElementsCanBeRetrieved_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    QDynamicArray<int> arExpectedArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));;
    QDynamicArray<int>::QArrayIterator itFirst = arCommonArray.GetFirst();
    QDynamicArray<int>::QArrayIterator itLast = arCommonArray.GetLast();

    // [Execution]
    QDynamicArray<int> arReturnedArray = arCommonArray.GetRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the last element is anterior to the first element in the range.
/// </summary>
QTEST_CASE ( GetRange1_AssertionFailsWhenLastElementIsAnteriorToFirstElement_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arCommonArray.GetLast();
    QDynamicArray<int>::QArrayIterator itLast = arCommonArray.GetFirst();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.GetRange(itFirst, itLast);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the first element points to the end position.
/// </summary>
QTEST_CASE ( GetRange1_AssertionFailsWhenFirstElementIsEnd_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arCommonArray.GetLast();
    QDynamicArray<int>::QArrayIterator itLast = arCommonArray.GetLast();
    ++itFirst;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.GetRange(itFirst, itLast);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the last element points to the end position.
/// </summary>
QTEST_CASE ( GetRange1_AssertionFailsWhenLastElementIsEnd_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    QDynamicArray<int>::QArrayIterator itFirst = arCommonArray.GetLast();
    QDynamicArray<int>::QArrayIterator itLast = arCommonArray.GetLast();
    ++itLast;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.GetRange(itFirst, itLast);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that elements are correctly retrieved from the last position of the array.
/// </summary>
QTEST_CASE ( GetRange2_ElementsAreCorrectlyGotFromLastPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {3, 4, 5};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const pointer_uint_q FIRST = 3U;
    const pointer_uint_q LAST = 5U;

    // [Execution]
    QDynamicArray<int> arReturnedArray = arCommonArray.GetRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(arReturnedArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly retrieved from the first position of the array.
/// </summary>
QTEST_CASE ( GetRange2_ElementsAreCorrectlyGotFromFirstPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const pointer_uint_q FIRST = 0;
    const pointer_uint_q LAST = 2U;
    
    // [Execution]
    QDynamicArray<int> arReturnedArray = arCommonArray.GetRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(arReturnedArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly retrieved when they are in between of two elements.
/// </summary>
QTEST_CASE ( GetRange2_ElementsAreCorrectlyGotFromBetweenTwoElements_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {1, 2, 3};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const pointer_uint_q FIRST = 1U;
    const pointer_uint_q LAST = 3U;
    
    // [Execution]
    QDynamicArray<int> arReturnedArray = arCommonArray.GetRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(arReturnedArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly removed when both positions are the same.
/// </summary>
QTEST_CASE ( GetRange2_ElementsAreCorrectlyRemovedWhenBothPositionsAreTheSame_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {1};
    QDynamicArray<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const pointer_uint_q FIRST = 1U;
    const pointer_uint_q LAST = FIRST;
    
    // [Execution]
    QDynamicArray<int> arReturnedArray = arCommonArray.GetRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(arReturnedArray == arExpectedArray);
}

/// <summary>
/// Checks that the copy constructor of each element is called when it is copied, at least once.
/// </summary>
QTEST_CASE ( GetRange2_CopyConstructorOfEachElementIsCalledAtLeastOnce_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    const pointer_uint_q EXPECTED_CALLS = 2;
    const CallCounter COMMON_VALUES[] = {CallCounter(), CallCounter(), CallCounter()};
    QDynamicArray<CallCounter> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(CallCounter));

    const pointer_uint_q FIRST = 1U;
    const pointer_uint_q LAST = 2U;
    CallCounter::ResetCounters();

    // [Execution]
    arCommonArray.GetRange(FIRST, LAST);

    // [Verification]
    pointer_uint_q uCopyConstructor = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK(uCopyConstructor >= EXPECTED_CALLS);
}

/// <summary>
/// Checks that all elements of the array can be retrieved.
/// </summary>
QTEST_CASE ( GetRange2_AllElementsCanBeRetrieved_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    QDynamicArray<int> arExpectedArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const pointer_uint_q FIRST = 0;
    const pointer_uint_q LAST = arCommonArray.GetCount() - 1U;

    // [Execution]
    QDynamicArray<int> arReturnedArray = arCommonArray.GetRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the last element is anterior to the first element in the range.
/// </summary>
QTEST_CASE ( GetRange2_AssertionFailsWhenLastElementIsAnteriorToFirstElement_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const pointer_uint_q FIRST = 1U;
    const pointer_uint_q LAST = 0;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.GetRange(FIRST, LAST);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the first position is not lower than the number of elements in the array.
/// </summary>
QTEST_CASE ( GetRange2_AssertionFailsWhenFirstPositionIsNotLowerThanCount_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const pointer_uint_q FIRST = arCommonArray.GetCount();
    const pointer_uint_q LAST = 2U;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.GetRange(FIRST, LAST);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the last position is not lower than the number of elements in the array
/// </summary>
QTEST_CASE ( GetRange2_AssertionFailsWhenLastPositionIsNotLowerThanCount_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    QDynamicArray<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const pointer_uint_q FIRST = 1U;
    const pointer_uint_q LAST = arCommonArray.GetCount();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.GetRange(FIRST, LAST);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

// End - Test Suite: QDynamicArray
QTEST_SUITE_END()
