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
{/* [TODO] Thund: Uncomment when the method Add is implemented
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
    BOOST_CHECK_EQUAL(uCount, ORIGINAL_COUNT);*/
}

/// <summary>
/// Checks that the capacity of the resultant array equals the element count of the input array.
/// </summary>
QTEST_CASE ( Constructor4_CapacityEqualsInputArrayCount_Test )
{/* [TODO] Thund: Uncomment when the method Add is implemented
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
    BOOST_CHECK_EQUAL(uCapacity, ORIGINAL_COUNT);*/
}

/// <summary>
/// Checks that the copy constructor of every element is called.
/// </summary>
QTEST_CASE ( Constructor4_CopyConstructorOfEveryElementIsCalled_Test )
{/* [TODO] Thund: Uncomment when the method Add is implemented
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
    BOOST_CHECK_EQUAL(uCopyConstructorsCalled, ORIGINAL_COUNT);*/
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
{/* [TODO] Thund: Uncomment when the method Add is implemented
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

    BOOST_CHECK_EQUAL(bAreEqual, ARE_EQUAL);*/
}

/// <summary>
/// Checks that the destructor of every element is called.
/// </summary>
QTEST_CASE ( Destructor_DestructorIsCalledForEveryElement_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QFixedArray;
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    const pointer_uint_q NUMBER_OF_ELEMENTS = 3U;
    CallCounter arOriginalArrayElements[3];
    {
        // [Preparation]
        QFixedArray<CallCounter> arOriginalArray(arOriginalArrayElements, 3U);
        CallCounter::ResetCounters();

	// [Execution]
    } // Destructor is called
    
    // [Verification]
    pointer_uint_q uDestructorsCalled = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorsCalled, NUMBER_OF_ELEMENTS);
}

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

// End - Test Suite: QDynamicArray
QTEST_SUITE_END()
