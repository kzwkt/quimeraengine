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

#include "QFixedArray.h"
#include "QFixedArrayWhiteBox.h"
#include "QFixedArrayTestClass.h"
#include "ArrayElementMock.h"

using Kinesis::QuimeraEngine::Common::DataTypes::u64_q;
using Kinesis::QuimeraEngine::Common::DataTypes::u32_q;
using Kinesis::QuimeraEngine::Tools::Containers::QFixedArray;
using Kinesis::QuimeraEngine::Tools::Containers::Test::QFixedArrayWhiteBox;
using Kinesis::QuimeraEngine::Tools::Containers::Test::ArrayElementMock;
using Kinesis::QuimeraEngine::Tools::Containers::Test::QFixedArrayTestClass;

i16_q ArrayElementMock::m_nNumberOfAllocatedObjects = 0;

QTEST_SUITE_BEGIN( QFixedArray_TestSuite )


#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks than assertion fails when attempting to create an array with zero elements.
/// </summary>
QTEST_CASE ( Constructor1_AssertionFailsWhenCreatingArrayWithZeroElements_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE = 12;
    const pointer_uint_q ZERO_ARRAY_COUNT = 0;
    const bool ASSERTION_FAILED = true;

    bool bAssertionFailed = false;

    // [Execution]

    try
    {
        QFixedArray<u64_q> fixedArray = QFixedArray<u64_q>(ZERO_ARRAY_COUNT, INITIAL_VALUE);
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
/// Checks if it's correctly initialized with initial value.
/// </summary>
QTEST_CASE ( Constructor1_ChecksifIsCorrectlyInitializedWithInitialValue_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE = 12;
    const pointer_uint_q ARRAY_COUNT = 10;
    const bool VALUES_ARE_AS_EXPECTED = true;

    // [Execution]
    QFixedArray<u64_q> fixedArray = QFixedArray<u64_q>(ARRAY_COUNT, INITIAL_VALUE);

    // [Verification]
    u64_q uValue;
    bool bValuesAreAsExpected = true;

    for(pointer_uint_q uIndex = 0; uIndex < ARRAY_COUNT; uIndex++ )
    {
        uValue = fixedArray[uIndex];
        bValuesAreAsExpected &= ( uValue == INITIAL_VALUE );
    }

    BOOST_CHECK_EQUAL( bValuesAreAsExpected, VALUES_ARE_AS_EXPECTED );
}

/// <summary>
/// Checks if the allocator has the expected size.
/// </summary>
QTEST_CASE ( Constructor1_AllocatorHasExpectedSize_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE = 12;
    const pointer_uint_q ARRAY_COUNT = 10;
    const pointer_uint_q SIZEOF_VALUE_TYPE = sizeof(u64_q);
    const pointer_uint_q ALLOCATOR_EXPECTED_SIZE = ARRAY_COUNT * SIZEOF_VALUE_TYPE;

    // [Execution]
    QFixedArray<u64_q> fixedArray = QFixedArray<u64_q>(ARRAY_COUNT, INITIAL_VALUE);

    // [Verification]
    pointer_uint_q uAllocatorSize = fixedArray.GetAllocator()->GetPoolSize();

    BOOST_CHECK_EQUAL( uAllocatorSize, ALLOCATOR_EXPECTED_SIZE );
}

/// <summary>
/// Checks if the copy constructor of the array elements are called.
/// </summary>
QTEST_CASE ( Constructor1_CopyConstructorOfArrayElementsAreCalled_Test )
{
    // [Preparation]
    const ArrayElementMock INITIAL_VALUE = ArrayElementMock(12);
    const pointer_uint_q ARRAY_COUNT = 10;
    const pointer_uint_q EXPECTED_CALLS_TO_COPY_CONSTRUCTOR = ARRAY_COUNT;

    // [Execution]
    QFixedArray<ArrayElementMock> fixedArray = QFixedArray<ArrayElementMock>(ARRAY_COUNT, INITIAL_VALUE);

    // [Verification]
    pointer_uint_q uCallsToCopyConstructor = 0;

    for(pointer_uint_q uIndex = 0; uIndex < ARRAY_COUNT; uIndex++)
    {
        if(((ArrayElementMock*)
            ((pointer_uint_q)fixedArray.GetAllocator()->GetPointer() + uIndex * sizeof(ArrayElementMock)))
            ->GetCallToCopyConstructor())
        {
            uCallsToCopyConstructor++;
        }
    }

    BOOST_CHECK_EQUAL( uCallsToCopyConstructor, EXPECTED_CALLS_TO_COPY_CONSTRUCTOR );
}

/// <summary>
/// Checks if the destructor of the array elements are called.
/// </summary>
QTEST_CASE ( Constructor1_DestructorOfArrayElementsAreCalled_Test )
{
    // [Preparation]
    const ArrayElementMock INITIAL_VALUE = ArrayElementMock(12);
    const pointer_uint_q ARRAY_COUNT = 10;
    const i16_q EXPECTED_REMAINING_OBJECTS_ALLOCATED = 1;

    // [Execution]
    QFixedArray<ArrayElementMock> *pFixedArray = new QFixedArray<ArrayElementMock>(ARRAY_COUNT, INITIAL_VALUE);
    delete pFixedArray;

    // [Verification]
    i16_q nRemainingObjectsAllocated = ArrayElementMock::GetNumberOfAllocatedObjects();

    BOOST_CHECK_EQUAL( nRemainingObjectsAllocated, EXPECTED_REMAINING_OBJECTS_ALLOCATED );
}

/// <summary>
/// Checks if the copy constructor of the array elements are called for the second constructor.
/// </summary>
QTEST_CASE ( Constructor2_CopyConstructorOfArrayElementsAreCalled_Test )
{
    // [Preparation]
    const ArrayElementMock INITIAL_VALUE = ArrayElementMock(12);
    const pointer_uint_q ARRAY_COUNT = 10;
    const pointer_uint_q EXPECTED_CALLS_TO_COPY_CONSTRUCTOR = ARRAY_COUNT;

    QFixedArray<ArrayElementMock> fixedArrayOrigin = QFixedArray<ArrayElementMock>(ARRAY_COUNT, INITIAL_VALUE);

    // [Execution]
    QFixedArray<ArrayElementMock> fixedArrayDestination = QFixedArray<ArrayElementMock>(fixedArrayOrigin);

    // [Verification]
    pointer_uint_q uCallsToCopyConstructor = 0;

    for(pointer_uint_q uIndex = 0; uIndex < ARRAY_COUNT; uIndex++)
    {
        if(((ArrayElementMock*)
            ((pointer_uint_q)fixedArrayDestination.GetAllocator()->GetPointer() + uIndex * sizeof(ArrayElementMock)))
            ->GetCallToCopyConstructor())
        {
            uCallsToCopyConstructor++;
        }
    }

    BOOST_CHECK_EQUAL( uCallsToCopyConstructor, EXPECTED_CALLS_TO_COPY_CONSTRUCTOR );
}

/// <summary>
/// Checks if the constructor without parameters initializes correctly.
/// </summary>
QTEST_CASE ( Constructor3_ConstructorWithoutParametersInitializesCorrectly_Test )
{
    // [Preparation]

    const pointer_uint_q END_POSITION_FORWARD = -1;
    const pointer_uint_q END_POSITION_BACKWARD = -2;

    // [Execution]

    QFixedArrayWhiteBox<u64_q> fixedArray;

    // [Verification]

    pointer_uint_q uFirst = fixedArray.GetFirst();
    pointer_uint_q uLast  = fixedArray.GetLast();

    BOOST_CHECK_EQUAL( uFirst, END_POSITION_BACKWARD );
    BOOST_CHECK_EQUAL( uLast, END_POSITION_FORWARD );
}

/// <summary>
/// Checks if the instance is correctly constructed when it receives a common array and its size.
/// </summary>
QTEST_CASE ( Constructor4_ItIsCorrectlyConstructedFromCommonArray_Test )
{
    // [Preparation]
    const unsigned int ARRAY_SIZE = 3;
    const char SOURCE_ARRAY[ARRAY_SIZE] = {0, 1, 2};

    // [Execution]
    QFixedArray<char> arArray(SOURCE_ARRAY, ARRAY_SIZE);

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
QTEST_CASE ( Constructor4_AssertionFailsWhenArrayIsNull_Test )
{
    // [Preparation]
    const int* NULL_ARRAY = null_q;
    const unsigned int NON_ZERO_SIZE = 3;
    const bool ASSERTION_FAILED = true;

    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        QFixedArray<int> arArray = QFixedArray<int>(NULL_ARRAY, NON_ZERO_SIZE);
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
QTEST_CASE ( Constructor4_AssertionFailsWhenCountIsZero_Test )
{
    // [Preparation]
    const int SOURCE_ARRAY[3] = {0, 1, 2};
    const unsigned int ZERO_SIZE = 0;
    const bool ASSERTION_FAILED = true;

    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        QFixedArray<int> arArray = QFixedArray<int>(SOURCE_ARRAY, ZERO_SIZE);
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
/// Checks if it assigns correctly when the size of the origin array is equal to the destination array.
/// </summary>
QTEST_CASE ( OperatorAssignment_CorrectlyAssignedWhenOriginArraySizeIsEqualToDestinationArraySize_Test )
{
    // [Preparation]
    const u64_q ORIGIN_VALUES[] = {0, 1, 2, 3};
    QFixedArray<u64_q> arOrigin = QFixedArray<u64_q>(ORIGIN_VALUES, 4U);
    const u64_q DESTINATION_VALUES[] = {4, 5, 6, 7};
    QFixedArray<u64_q> arDestination = QFixedArray<u64_q>(DESTINATION_VALUES, 4U);

    // [Execution]
    arDestination = arOrigin;

    // [Verification]
    BOOST_CHECK(arDestination == arOrigin);
}

/// <summary>
/// Checks if it assigns correctly when the size of the origin array is lower than the destination array.
/// </summary>
QTEST_CASE ( OperatorAssignment_CorrectlyAssignedWhenOriginArraySizeIsLowerThanDestinationArraySize_Test )
{
    // [Preparation]
    const u64_q ORIGIN_VALUES[] = {0, 1, 2};
    QFixedArray<u64_q> arOrigin = QFixedArray<u64_q>(ORIGIN_VALUES, 3U);
    const u64_q DESTINATION_VALUES[] = {4, 5, 6, 7};
    QFixedArray<u64_q> arDestination = QFixedArray<u64_q>(DESTINATION_VALUES, 4U);
    const u64_q EXPECTED_VALUES[] = {0, 1, 2, 7};
    QFixedArray<u64_q> arExpectedValues = QFixedArray<u64_q>(EXPECTED_VALUES, 4U);

    // [Execution]
    arDestination = arOrigin;

    // [Verification]
    BOOST_CHECK(arDestination == arExpectedValues);
}

/// <summary>
/// Checks if it calls to operator assignment of the array elements.
/// </summary>
QTEST_CASE ( OperatorAssignment_OperatorAssignmentOfArrayElementsIsCalled_Test )
{
    // [Preparation]
    const ArrayElementMock INITIAL_VALUE = ArrayElementMock(12);
    const pointer_uint_q ARRAY_COUNT = 10;
    const pointer_uint_q EXPECTED_CALLS_TO_OPERATOR_ASSIGNMENT = ARRAY_COUNT;

    QFixedArray<ArrayElementMock> fixedArrayOrigin = QFixedArray<ArrayElementMock>(ARRAY_COUNT, INITIAL_VALUE);
    QFixedArray<ArrayElementMock> fixedArrayDestination = QFixedArray<ArrayElementMock>(ARRAY_COUNT, INITIAL_VALUE);

    // [Execution]
    fixedArrayDestination = fixedArrayOrigin;

    // [Verification]
    pointer_uint_q uCallsToOperatorAssignment = 0;

    for(pointer_uint_q uIndex = 0; uIndex < ARRAY_COUNT; uIndex++)
    {
        if(((ArrayElementMock*)
            ((pointer_uint_q)fixedArrayDestination.GetAllocator()->GetPointer() + uIndex * sizeof(ArrayElementMock)))
            ->GetCallToOperatorAssignment())
        {
            uCallsToOperatorAssignment++;
        }
    }

    BOOST_CHECK_EQUAL( uCallsToOperatorAssignment, EXPECTED_CALLS_TO_OPERATOR_ASSIGNMENT );
}

/// <summary>
/// Checks if it calls operator assignment of elements as number of times as number of elements has the
/// origin array, when it's less than the destination array.
/// </summary>
QTEST_CASE ( OperatorAssignment_OriginSizeNumberOfCopiesAreDoneWhereIsLessThanDestinationSize_Test )
{
    // [Preparation]
    const ArrayElementMock INITIAL_VALUE = ArrayElementMock(12);
    const pointer_uint_q ARRAY_COUNT_ORIGIN = 5;
    const pointer_uint_q ARRAY_COUNT_DESTINATION = 10;

    QFixedArray<ArrayElementMock> fixedArrayOrigin = QFixedArray<ArrayElementMock>(ARRAY_COUNT_ORIGIN, INITIAL_VALUE);
    QFixedArray<ArrayElementMock> fixedArrayDestination = QFixedArray<ArrayElementMock>(ARRAY_COUNT_DESTINATION, INITIAL_VALUE);

    const pointer_uint_q EXPECTED_CALLS_TO_OPERATOR_ASSIGNMENT = ARRAY_COUNT_ORIGIN;

    // [Execution]
    fixedArrayDestination = fixedArrayOrigin;

    // [Verification]
    pointer_uint_q uCallsToOperatorAssignment = 0;

    for(pointer_uint_q uIndex = 0; uIndex < ARRAY_COUNT_DESTINATION; uIndex++)
    {
        if(((ArrayElementMock*)
            ((pointer_uint_q)fixedArrayDestination.GetAllocator()->GetPointer() + uIndex * sizeof(ArrayElementMock)))
            ->GetCallToOperatorAssignment())
        {
            uCallsToOperatorAssignment++;
        }
    }

    BOOST_CHECK_EQUAL( uCallsToOperatorAssignment, EXPECTED_CALLS_TO_OPERATOR_ASSIGNMENT );

}

/// <summary>
/// Checks if it calls operator assignment of elements as number of times as number of elements has the
/// destination array, when the origin array is greater than the destination array.
/// </summary>
QTEST_CASE ( OperatorAssignment_DestinationSizeNumberOfCopiesAreDoneWhereOriginSizeIsGreatherThanDestinationSize_Test )
{
    // [Preparation]
    const ArrayElementMock INITIAL_VALUE = ArrayElementMock(12);
    const pointer_uint_q ARRAY_COUNT_ORIGIN = 10;
    const pointer_uint_q ARRAY_COUNT_DESTINATION = 5;

    QFixedArray<ArrayElementMock> fixedArrayOrigin = QFixedArray<ArrayElementMock>(ARRAY_COUNT_ORIGIN, INITIAL_VALUE);
    QFixedArray<ArrayElementMock> fixedArrayDestination = QFixedArray<ArrayElementMock>(ARRAY_COUNT_DESTINATION, INITIAL_VALUE);

    const pointer_uint_q EXPECTED_CALLS_TO_OPERATOR_ASSIGNMENT = ARRAY_COUNT_DESTINATION;

    // [Execution]
    fixedArrayDestination = fixedArrayOrigin;

    // [Verification]

    pointer_uint_q uCallsToOperatorAssignment = 0;

    for(pointer_uint_q uIndex = 0; uIndex < ARRAY_COUNT_DESTINATION; uIndex++)
    {
        if(((ArrayElementMock*)
            ((pointer_uint_q)fixedArrayDestination.GetAllocator()->GetPointer() + uIndex * sizeof(ArrayElementMock)))
            ->GetCallToOperatorAssignment())
        {
            uCallsToOperatorAssignment++;
        }
    }

    BOOST_CHECK_EQUAL( uCallsToOperatorAssignment, EXPECTED_CALLS_TO_OPERATOR_ASSIGNMENT );
}


/// <sumary>
/// Checks if the value is set at correct position.
/// </sumary>
QTEST_CASE( OperatorArraySubscript_ValueIsSetAtCorrectPosition_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE = 12;
    const pointer_uint_q ARRAY_COUNT = 5;
    const u64_q NEW_VALUE = 10;
    const pointer_uint_q POSITION_TO_SET_NEW_VALUE = 2;
    const bool OTHER_POSITIONS_UNTOUCHED = true;

    QFixedArray<u64_q> fixedArray = QFixedArray<u64_q>(ARRAY_COUNT, INITIAL_VALUE);

    // [Execution]
    fixedArray[POSITION_TO_SET_NEW_VALUE] = NEW_VALUE;

    // [Verification]
    u64_q uValue = fixedArray.GetValue(POSITION_TO_SET_NEW_VALUE);

    bool bOtherPositionsUntouched = true;

    for(pointer_uint_q uIndex = 0; uIndex < ARRAY_COUNT; uIndex++)
    {
        if(uIndex != POSITION_TO_SET_NEW_VALUE)
            bOtherPositionsUntouched = bOtherPositionsUntouched &&
                (fixedArray.GetValue(uIndex) == INITIAL_VALUE);
    }

    BOOST_CHECK_EQUAL( uValue, NEW_VALUE );
    BOOST_CHECK_EQUAL( bOtherPositionsUntouched, OTHER_POSITIONS_UNTOUCHED );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks than assertion fails when attempts to set a value to a position greater than the array's size.
/// </summary>
QTEST_CASE ( OperatorArraySubscript_AssertionFailsWhenAttemptsToSetAValueToAPositionGreaterThanArraySize_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE = 12;
    const pointer_uint_q ARRAY_COUNT = 5;
    const bool ASSERTION_FAILED = true;
    const pointer_uint_q POSITION_GREATER_THAN_ARRAY_SIZE = ARRAY_COUNT;
    bool bAssertionFailed = false;

    QFixedArray<u64_q> fixedArray = QFixedArray<u64_q>(ARRAY_COUNT, INITIAL_VALUE);

    // [Execution]

    try
    {
        fixedArray[POSITION_GREATER_THAN_ARRAY_SIZE] = INITIAL_VALUE;
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]

    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS


/// <sumary>
/// Checks if it gets the correct value at supplied position.
/// </sumary>
QTEST_CASE( OperatorArraySubscript_GetsCorrectValueAtSuppliedPosition_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE = 12;
    const pointer_uint_q ARRAY_COUNT = 5;
    const u64_q NEW_VALUE = 10;
    const pointer_uint_q POSITION_TO_SET_NEW_VALUE = 2;

    QFixedArray<u64_q> fixedArray = QFixedArray<u64_q>(ARRAY_COUNT, INITIAL_VALUE);
    fixedArray.SetValue(POSITION_TO_SET_NEW_VALUE, NEW_VALUE);

    // [Execution]
    u64_q uValue = fixedArray[POSITION_TO_SET_NEW_VALUE];

    // [Verification]
    BOOST_CHECK_EQUAL( uValue, NEW_VALUE );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks than assertion fails when it attempts to get the value from a position greater than the array's size.
/// </summary>
QTEST_CASE ( OperatorArraySubscript_AssertionFailsWhenAttemptsToGetTheValueFromAPositionGreaterThanArraySize_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE = 12;
    const pointer_uint_q ARRAY_COUNT = 5;
    const bool ASSERTION_FAILED = true;
    const pointer_uint_q POSITION_GREATER_THAN_ARRAY_SIZE = ARRAY_COUNT;
    bool bAssertionFailed = false;

    QFixedArray<u64_q> fixedArray = QFixedArray<u64_q>(ARRAY_COUNT, INITIAL_VALUE);

    // [Execution]

    try
    {
        fixedArray[POSITION_GREATER_THAN_ARRAY_SIZE];
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]

    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks if gets the correct value at supplied position.
/// </sumary>
QTEST_CASE( GetValue_GetsCorrectValueAtSuppliedPosition_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE = 12;
    const pointer_uint_q ARRAY_COUNT = 5;
    const u64_q NEW_VALUE = 10;
    const pointer_uint_q POSITION_TO_SET_NEW_VALUE = 2;

    QFixedArray<u64_q> fixedArray = QFixedArray<u64_q>(ARRAY_COUNT, INITIAL_VALUE);
    fixedArray.SetValue(POSITION_TO_SET_NEW_VALUE, NEW_VALUE);

    // [Execution]
    u64_q uValue = fixedArray.GetValue(POSITION_TO_SET_NEW_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL( uValue, NEW_VALUE );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks than assertion fails when attempts to get the value from a position greater than the array's size.
/// </summary>
QTEST_CASE ( GetValue_AssertionFailsWhenAttemptsToGetTheValueFromAPositionNotLessThanArraySize_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE = 12;
    const pointer_uint_q ARRAY_COUNT = 5;
    const bool ASSERTION_FAILED = true;
    const pointer_uint_q POSITION_GREATER_THAN_ARRAY_SIZE = ARRAY_COUNT;
    bool bAssertionFailed = false;

    QFixedArray<u64_q> fixedArray = QFixedArray<u64_q>(ARRAY_COUNT, INITIAL_VALUE);

    // [Execution]

    try
    {
        fixedArray.GetValue(POSITION_GREATER_THAN_ARRAY_SIZE);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]

    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Clones an array and checks if the arrays have the same values.
/// </sumary>
QTEST_CASE( Clone_ClonedArrayHasSameValuesThanTheOriginArray_Test )
{
    // [Preparation]
    const u64_q VALUE_ORIGIN = 12;
    const u64_q VALUE_DESTINATION = 15;
    const pointer_uint_q ARRAY_COUNT = 5;
    const bool SAME_VALUES = true;

    QFixedArray<u64_q> fixedArrayOrigin = QFixedArray<u64_q>(ARRAY_COUNT, VALUE_ORIGIN);
    QFixedArray<u64_q> fixedArrayDestination = QFixedArray<u64_q>(ARRAY_COUNT, VALUE_DESTINATION);

    // [Execution]
    fixedArrayOrigin.Clone(fixedArrayDestination);

    // [Verification]
    bool bSameValues = true;

    for(pointer_uint_q uIndex = 0; uIndex < ARRAY_COUNT; uIndex++)
    {
        bSameValues = bSameValues && ( VALUE_ORIGIN == fixedArrayDestination[uIndex] );
    }

    BOOST_CHECK_EQUAL( bSameValues, SAME_VALUES );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks than assertion fails when the two array's capacities are different.
/// </summary>
QTEST_CASE ( Clone_AssertionFailsWhenArrayCapacitiesAreDifferent_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE = 12;
    const pointer_uint_q ARRAY_COUNT_ORIGIN = 5;
    const pointer_uint_q ARRAY_COUNT_DESTINATION = 6;
    const bool ASSERTION_FAILED = true;

    bool bAssertionFailed = false;

    QFixedArray<u64_q> fixedArrayOrigin = QFixedArray<u64_q>(ARRAY_COUNT_ORIGIN, INITIAL_VALUE);
    QFixedArray<u64_q> fixedArrayDestination = QFixedArray<u64_q>(ARRAY_COUNT_DESTINATION, INITIAL_VALUE);

    // [Execution]

    try
    {
        fixedArrayOrigin.Clone(fixedArrayDestination);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]

    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks if the value is set at correct position.
/// </sumary>
QTEST_CASE( SetValue_ValueIsSetAtCorrectPosition_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE = 12;
    const pointer_uint_q ARRAY_COUNT = 5;
    const u64_q NEW_VALUE = 10;
    const pointer_uint_q POSITION_TO_SET_NEW_VALUE = 2;
    const bool OTHER_POSITIONS_UNTOUCHED = true;

    QFixedArray<u64_q> fixedArray = QFixedArray<u64_q>(ARRAY_COUNT, INITIAL_VALUE);

    // [Execution]
    fixedArray.SetValue(POSITION_TO_SET_NEW_VALUE, NEW_VALUE);

    // [Verification]
    u64_q uValue = fixedArray.GetValue(POSITION_TO_SET_NEW_VALUE);
    bool bOtherPositionsUntouched = true;

    for(pointer_uint_q uIndex = 0; uIndex < ARRAY_COUNT; uIndex++)
    {
        if(uIndex != POSITION_TO_SET_NEW_VALUE)
            bOtherPositionsUntouched = bOtherPositionsUntouched &&
                (fixedArray.GetValue(uIndex) == INITIAL_VALUE);
    }

    BOOST_CHECK_EQUAL( uValue, NEW_VALUE );
    BOOST_CHECK_EQUAL( bOtherPositionsUntouched, OTHER_POSITIONS_UNTOUCHED );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks than assertion fails when attempts to set a value to a position greater than the array's size.
/// </summary>
QTEST_CASE ( SetValue_AssertionFailsWhenAttemptsToSetAValueToAPositionNotLessThanArraySize_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE = 12;
    const pointer_uint_q ARRAY_COUNT = 5;
    const bool ASSERTION_FAILED = true;
    const pointer_uint_q POSITION_GREATER_THAN_ARRAY_SIZE = ARRAY_COUNT;
    bool bAssertionFailed = false;

    QFixedArray<u64_q> fixedArray = QFixedArray<u64_q>(ARRAY_COUNT, INITIAL_VALUE);

    // [Execution]

    try
    {
        fixedArray.SetValue(POSITION_GREATER_THAN_ARRAY_SIZE, INITIAL_VALUE);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]

    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Returns an iterator to the position passed as parameter.
/// </sumary>
QTEST_CASE( GetIterator_ReturnsIteratorToSpecificPositionInTheArray_Test )
{
    // [Preparation]
    const u32_q INITIAL_VALUE = 12;
    const pointer_uint_q ARRAY_COUNT = 5;
    const pointer_uint_q INDEX = 2;
    const u32_q NEW_VALUE = 10;
    QFixedArray<u32_q> arFixedArray = QFixedArray<u32_q>(ARRAY_COUNT, INITIAL_VALUE);
    arFixedArray.SetValue(INDEX, NEW_VALUE);

    // [Execution]
    QFixedArray<u32_q>::QConstArrayIterator it = arFixedArray.GetIterator(INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(*it, NEW_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// This test checks that the assert is thrown when trying to get an iterator passing an index bigger than array´s size.
/// </sumary>
QTEST_CASE( GetIterator_AssertionFailsWhenParameterIsBiggerThanArraySize_Test )
{
    // [Preparation]
    const u32_q INITIAL_VALUE = 12;
    const pointer_uint_q ARRAY_COUNT = 5;
    const pointer_uint_q INDEX = 7;
    QFixedArray<u32_q> arFixedArray(ARRAY_COUNT, INITIAL_VALUE);
    bool bAssertionFailed = false;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    try
    {
        arFixedArray.GetIterator(INDEX);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <sumary>
/// Checks that if parameter bigger than array´s size is passed forward end position of the array is returned.
/// </sumary>
QTEST_CASE( GetIterator_ReturnsIteratorToForwardEndPositionInTheArrayWhenParameterIsBiggerThanArraySize_Test )
{
    // [Preparation]
    const u32_q INITIAL_VALUE = 12;
    const pointer_uint_q ARRAY_COUNT = 5;
    const pointer_uint_q INDEX = 7;
    const bool EXPECTED_VALUE = true;
    bool bForwardEndPosition = false;
    QFixedArray<u32_q> arFixedArray = QFixedArray<u32_q>(ARRAY_COUNT, INITIAL_VALUE);

    // [Execution]
    QFixedArray<u32_q>::QConstArrayIterator it = arFixedArray.GetIterator(INDEX);
    bForwardEndPosition = it.IsEnd();

    // [Verification]
    BOOST_CHECK_EQUAL(bForwardEndPosition, EXPECTED_VALUE);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <sumary>
/// Returns an iterator to the first element in the array.
/// </sumary>
QTEST_CASE( GetFirst_ReturnsIteratorToFirstElementInTheArray_Test )
{
    // [Preparation]
    const u32_q INITIAL_VALUE = 12;
    const pointer_uint_q ARRAY_COUNT = 5;
    const pointer_uint_q INITIAL_POS = 0;
    const u32_q NEW_VALUE = 10;
    QFixedArray<u32_q> arFixedArray = QFixedArray<u32_q>(ARRAY_COUNT, INITIAL_VALUE);
    arFixedArray.SetValue(INITIAL_POS, NEW_VALUE);

    // [Execution]
    QFixedArray<u32_q>::QConstArrayIterator it = arFixedArray.GetFirst();

    // [Verification]
    BOOST_CHECK_EQUAL(*it, NEW_VALUE);
}

/// <sumary>
/// Checks that if the array is empty backward end position of the array is returned.
/// </sumary>
QTEST_CASE( GetFirst_ReturnsIteratorToBackwardEndPositionInTheArrayWhenArrayIsEmpty_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = true;
    bool bBackwardEndPosition = false;
    QFixedArrayTestClass<u32_q> arFixedArray;

    // [Execution]
    QFixedArrayTestClass<u32_q>::QConstArrayIterator it = arFixedArray.GetFirst();
    bBackwardEndPosition = it.IsEnd(); 

    // [Verification]
    BOOST_CHECK_EQUAL(bBackwardEndPosition, EXPECTED_VALUE);
}

/// <sumary>
/// Returns an iterator to the last element in the array.
/// </sumary>
QTEST_CASE( GetLast_ReturnsIteratorToLastElementInTheArray_Test )
{
    // [Preparation]
    const u32_q INITIAL_VALUE = 12;
    const pointer_uint_q ARRAY_COUNT = 5;
    const pointer_uint_q LAST_POS = 4;
    const u32_q NEW_VALUE = 10;
    QFixedArray<u32_q> arFixedArray = QFixedArray<u32_q>(ARRAY_COUNT, INITIAL_VALUE);
    arFixedArray.SetValue(LAST_POS, NEW_VALUE);

    // [Execution]
    QFixedArray<u32_q>::QConstArrayIterator it = arFixedArray.GetLast();

    // [Verification]
    BOOST_CHECK_EQUAL(*it, NEW_VALUE);
}

/// <sumary>
/// Checks that if the array is empty forward end position of the array is returned.
/// </sumary>
QTEST_CASE( GetLast_ReturnsIteratorToForwardEndPositionInTheArrayWhenArrayIsEmpty_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = true;
    bool bForwardEndPosition = false;
    QFixedArrayTestClass<u32_q> arFixedArray;

    // [Execution]
    QFixedArrayTestClass<u32_q>::QConstArrayIterator it = arFixedArray.GetLast();
    bForwardEndPosition = it.IsEnd(); 

    // [Verification]
    BOOST_CHECK_EQUAL(bForwardEndPosition, EXPECTED_VALUE);
}

/// <sumary>
/// Checks that it returns the expected array when the selected range encloses the entire array.
/// </sumary>
QTEST_CASE( GetRange1_ReturnsExpectedArrayWhenRangeIsTheEntireArray_Test )
{
    // [Preparation]
    u32_q arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const QFixedArray<u32_q> EXPECTED_RESULT(arValues, sizeof(arValues) / sizeof(u32_q));
    const pointer_uint_q FIRST_POSITION = 0;
    const pointer_uint_q LAST_POSITION = sizeof(arValues) / sizeof(u32_q) - 1U;

    // [Execution]
    QFixedArray<u32_q> arResult = arFixedArray.GetRange(FIRST_POSITION, LAST_POSITION);

    // [Verification]
    bool bArrayIsWhatExpected = true;

    for(pointer_uint_q i = 0; i < arResult.GetCapacity(); ++i)
        bArrayIsWhatExpected = bArrayIsWhatExpected && arResult[i] == EXPECTED_RESULT[i];

    BOOST_CHECK(bArrayIsWhatExpected);
}

/// <sumary>
/// Checks that it returns the expected array when the selected range encloses just one element.
/// </sumary>
QTEST_CASE( GetRange1_ReturnsExpectedArrayWhenRangeIsOnlyOneElement_Test )
{
    // [Preparation]
    u32_q arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    u32_q arExpectedValues[] = {3U};
    const QFixedArray<u32_q> EXPECTED_RESULT(arExpectedValues, sizeof(arExpectedValues) / sizeof(u32_q));
    const pointer_uint_q FIRST_POSITION = 3U;
    const pointer_uint_q LAST_POSITION = FIRST_POSITION;
    const pointer_uint_q EXPECTED_COUNT = 1U;

    // [Execution]
    QFixedArray<u32_q> arResult = arFixedArray.GetRange(FIRST_POSITION, LAST_POSITION);

    // [Verification]
    bool bArrayIsWhatExpected = arResult[0] == EXPECTED_RESULT[0];
    pointer_uint_q uCount = arResult.GetCount();

    BOOST_CHECK(bArrayIsWhatExpected);
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <sumary>
/// Checks that it returns the expected array when the selected range encloses a common subarray.
/// </sumary>
QTEST_CASE( GetRange1_ReturnsExpectedArrayWhenRangeEnclosesCommonSubarray_Test )
{
    // [Preparation]
    u32_q arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    u32_q arExpectedValues[] = {2U, 3U, 4U};
    const QFixedArray<u32_q> EXPECTED_RESULT(arExpectedValues, sizeof(arExpectedValues) / sizeof(u32_q));
    const pointer_uint_q FIRST_POSITION = 2U;
    const pointer_uint_q LAST_POSITION = 4U;

    // [Execution]
    QFixedArray<u32_q> arResult = arFixedArray.GetRange(FIRST_POSITION, LAST_POSITION);

    // [Verification]
    bool bArrayIsWhatExpected = true;

    for(pointer_uint_q i = 0; i < arResult.GetCapacity(); ++i)
        bArrayIsWhatExpected = bArrayIsWhatExpected && arResult[i] == EXPECTED_RESULT[i];

    BOOST_CHECK(bArrayIsWhatExpected);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when positions are out of bounds.
/// </sumary>
QTEST_CASE( GetRange1_AssertionFailsWhenPositionsAreOutOfBounds_Test )
{
    // [Preparation]
    u32_q arValues[] = {0, 1U, 2U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const pointer_uint_q FIRST_POSITION = sizeof(arValues) / sizeof(u32_q);
    const pointer_uint_q LAST_POSITION = FIRST_POSITION;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arFixedArray.GetRange(FIRST_POSITION, LAST_POSITION);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

/// <sumary>
/// Checks that an assertion fails when the first position is greater than the last position.
/// </sumary>
QTEST_CASE( GetRange1_AssertionFailsWhenFirstPositionIsGreaterThanLastPosition_Test )
{
    // [Preparation]
    u32_q arValues[] = {0, 1U, 2U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const pointer_uint_q LAST_POSITION = 0;
    const pointer_uint_q FIRST_POSITION = LAST_POSITION + 1U;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arFixedArray.GetRange(FIRST_POSITION, LAST_POSITION);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that it returns the expected array when the selected range encloses the entire array.
/// </sumary>
QTEST_CASE( GetRange2_ReturnsExpectedArrayWhenRangeIsTheEntireArray_Test )
{
    // [Preparation]
    u32_q arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const QFixedArray<u32_q> EXPECTED_RESULT(arValues, sizeof(arValues) / sizeof(u32_q));
    const QFixedArray<u32_q>::QConstArrayIterator FIRST_POSITION = arFixedArray.GetFirst();
    const QFixedArray<u32_q>::QConstArrayIterator LAST_POSITION = arFixedArray.GetLast();

    // [Execution]
    QFixedArray<u32_q> arResult = arFixedArray.GetRange(FIRST_POSITION, LAST_POSITION);

    // [Verification]
    bool bArrayIsWhatExpected = true;

    for(pointer_uint_q i = 0; i < arResult.GetCapacity(); ++i)
        bArrayIsWhatExpected = bArrayIsWhatExpected && arResult[i] == EXPECTED_RESULT[i];

    BOOST_CHECK(bArrayIsWhatExpected);
}

/// <sumary>
/// Checks that it returns the expected array when the selected range encloses just one element.
/// </sumary>
QTEST_CASE( GetRange2_ReturnsExpectedArrayWhenRangeIsOnlyOneElement_Test )
{
    // [Preparation]
    u32_q arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    u32_q arExpectedValues[] = {3U};
    const QFixedArray<u32_q> EXPECTED_RESULT(arExpectedValues, sizeof(arExpectedValues) / sizeof(u32_q));
    const QFixedArray<u32_q>::QConstArrayIterator FIRST_POSITION = arFixedArray.GetIterator(3U);
    const QFixedArray<u32_q>::QConstArrayIterator LAST_POSITION = FIRST_POSITION;
    const pointer_uint_q EXPECTED_COUNT = 1U;

    // [Execution]
    QFixedArray<u32_q> arResult = arFixedArray.GetRange(FIRST_POSITION, LAST_POSITION);

    // [Verification]
    bool bArrayIsWhatExpected = arResult[0] == EXPECTED_RESULT[0];
    pointer_uint_q uCount = arResult.GetCount();

    BOOST_CHECK(bArrayIsWhatExpected);
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <sumary>
/// Checks that it returns the expected array when the selected range encloses a common subarray.
/// </sumary>
QTEST_CASE( GetRange2_ReturnsExpectedArrayWhenRangeEnclosesCommonSubarray_Test )
{
    // [Preparation]
    u32_q arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    u32_q arExpectedValues[] = {2U, 3U, 4U};
    const QFixedArray<u32_q> EXPECTED_RESULT(arExpectedValues, sizeof(arExpectedValues) / sizeof(u32_q));
    const QFixedArray<u32_q>::QConstArrayIterator FIRST_POSITION = arFixedArray.GetIterator(2U);
    const QFixedArray<u32_q>::QConstArrayIterator LAST_POSITION = arFixedArray.GetIterator(4U);

    // [Execution]
    QFixedArray<u32_q> arResult = arFixedArray.GetRange(FIRST_POSITION, LAST_POSITION);

    // [Verification]
    bool bArrayIsWhatExpected = true;

    for(pointer_uint_q i = 0; i < arResult.GetCapacity(); ++i)
        bArrayIsWhatExpected = bArrayIsWhatExpected && arResult[i] == EXPECTED_RESULT[i];

    BOOST_CHECK(bArrayIsWhatExpected);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the first position is an end position.
/// </sumary>
QTEST_CASE( GetRange2_AssertionFailsWhenFirstPositionIsEnd_Test )
{
    // [Preparation]
    u32_q arValues[] = {0, 1U, 2U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    QFixedArray<u32_q>::QConstArrayIterator FIRST_POSITION = arFixedArray.GetLast();
    ++FIRST_POSITION;
    const QFixedArray<u32_q>::QConstArrayIterator LAST_POSITION = arFixedArray.GetIterator(0);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arFixedArray.GetRange(FIRST_POSITION, LAST_POSITION);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

/// <sumary>
/// Checks that an assertion fails when the last position is an end position.
/// </sumary>
QTEST_CASE( GetRange2_AssertionFailsWhenLastPositionIsEnd_Test )
{
    // [Preparation]
    u32_q arValues[] = {0, 1U, 2U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    QFixedArray<u32_q>::QConstArrayIterator LAST_POSITION = arFixedArray.GetLast();
    ++LAST_POSITION;
    const QFixedArray<u32_q>::QConstArrayIterator FIRST_POSITION = arFixedArray.GetIterator(0);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arFixedArray.GetRange(FIRST_POSITION, LAST_POSITION);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

/// <sumary>
/// Checks that an assertion fails when the first position is greater than the last position.
/// </sumary>
QTEST_CASE( GetRange2_AssertionFailsWhenFirstPositionIsGreaterThanLastPosition_Test )
{
    // [Preparation]
    u32_q arValues[] = {0, 1U, 2U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const QFixedArray<u32_q>::QConstArrayIterator FIRST_POSITION = arFixedArray.GetLast();
    QFixedArray<u32_q>::QConstArrayIterator LAST_POSITION = FIRST_POSITION;
    --LAST_POSITION;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arFixedArray.GetRange(FIRST_POSITION, LAST_POSITION);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that elements are correctly swapped when they occupy the first and the last positions.
/// </sumary>
QTEST_CASE( Swap1_ElementsAreCorrectlySwappedWhenTheyAreTheFirstAndTheLast_Test )
{
    // [Preparation]
    u32_q arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const pointer_uint_q POSITION_A = 0;
    const pointer_uint_q POSITION_B = sizeof(arValues) / sizeof(u32_q) - 1U;
    const u32_q EXPECTED_VALUE_A = arValues[POSITION_B];
    const u32_q EXPECTED_VALUE_B = arValues[POSITION_A];

    // [Execution]
    arFixedArray.Swap(POSITION_A, POSITION_B);

    // [Verification]
    BOOST_CHECK_EQUAL(arFixedArray[POSITION_A], EXPECTED_VALUE_A);
    BOOST_CHECK_EQUAL(arFixedArray[POSITION_B], EXPECTED_VALUE_B);
}

/// <sumary>
/// Checks that elements are correctly swapped when selecting any position.
/// </sumary>
QTEST_CASE( Swap1_ElementsAreCorrectlySwappedWhenSelectingAnyPosition_Test )
{
    // [Preparation]
    u32_q arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const pointer_uint_q POSITION_A = 2U;
    const pointer_uint_q POSITION_B = 4U;
    const u32_q EXPECTED_VALUE_A = arValues[POSITION_B];
    const u32_q EXPECTED_VALUE_B = arValues[POSITION_A];

    // [Execution]
    arFixedArray.Swap(POSITION_A, POSITION_B);

    // [Verification]
    BOOST_CHECK_EQUAL(arFixedArray[POSITION_A], EXPECTED_VALUE_A);
    BOOST_CHECK_EQUAL(arFixedArray[POSITION_B], EXPECTED_VALUE_B);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the first position provided is out of bounds.
/// </sumary>
QTEST_CASE( Swap1_AssertionFailsWhenFirstPositionIsOutOfBounds_Test )
{
    // [Preparation]
    u32_q arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const pointer_uint_q POSITION_A = sizeof(arValues) / sizeof(u32_q);
    const pointer_uint_q POSITION_B = 4U;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arFixedArray.Swap(POSITION_A, POSITION_B);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

/// <sumary>
/// Checks that an assertion fails when the second position provided is out of bounds.
/// </sumary>
QTEST_CASE( Swap1_AssertionFailsWhenSecondPositionIsOutOfBounds_Test )
{
    // [Preparation]
    u32_q arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const pointer_uint_q POSITION_A = 4U;
    const pointer_uint_q POSITION_B = sizeof(arValues) / sizeof(u32_q);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arFixedArray.Swap(POSITION_A, POSITION_B);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

/// <sumary>
/// Checks that an assertion fails when swapping the same element.
/// </sumary>
QTEST_CASE( Swap1_AssertionFailsWhenSwappingTheSameElement_Test )
{
    // [Preparation]
    u32_q arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const pointer_uint_q POSITION_A = 4U;
    const pointer_uint_q POSITION_B = POSITION_A;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arFixedArray.Swap(POSITION_A, POSITION_B);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <sumary>
/// Checks that nothing happens when swapping the same element.
/// </sumary>
QTEST_CASE( Swap1_NothingHappensWhenSwappingTheSameElement_Test )
{
    // [Preparation]
    u32_q arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const pointer_uint_q POSITION_A = 4U;
    const pointer_uint_q POSITION_B = POSITION_A;
    const u32_q EXPECTED_VALUE_A = arValues[POSITION_A];
    const u32_q EXPECTED_VALUE_B = arValues[POSITION_A];

    // [Execution]
    arFixedArray.Swap(POSITION_A, POSITION_B);

    // [Verification]
    BOOST_CHECK_EQUAL(arFixedArray[POSITION_A], EXPECTED_VALUE_A);
    BOOST_CHECK_EQUAL(arFixedArray[POSITION_B], EXPECTED_VALUE_B);
}

#endif

/// <sumary>
/// Checks that elements are correctly swapped when they occupy the first and the last positions.
/// </sumary>
QTEST_CASE( Swap2_ElementsAreCorrectlySwappedWhenTheyAreTheFirstAndTheLast_Test )
{
    // [Preparation]
    u32_q arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const QFixedArray<u32_q>::QArrayIterator POSITION_A = arFixedArray.GetFirst();
    const QFixedArray<u32_q>::QArrayIterator POSITION_B = arFixedArray.GetLast();
    const u32_q EXPECTED_VALUE_A = *POSITION_B;
    const u32_q EXPECTED_VALUE_B = *POSITION_A;

    // [Execution]
    arFixedArray.Swap(POSITION_A, POSITION_B);

    // [Verification]
    BOOST_CHECK_EQUAL(*POSITION_A, EXPECTED_VALUE_A);
    BOOST_CHECK_EQUAL(*POSITION_B, EXPECTED_VALUE_B);
}

/// <sumary>
/// Checks that elements are correctly swapped when selecting any position.
/// </sumary>
QTEST_CASE( Swap2_ElementsAreCorrectlySwappedWhenSelectingAnyPosition_Test )
{
    // [Preparation]
    u32_q arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const QFixedArray<u32_q>::QArrayIterator POSITION_A = arFixedArray.GetIterator(2U);
    const QFixedArray<u32_q>::QArrayIterator POSITION_B = arFixedArray.GetIterator(4U);
    const u32_q EXPECTED_VALUE_A = *POSITION_B;
    const u32_q EXPECTED_VALUE_B = *POSITION_A;

    // [Execution]
    arFixedArray.Swap(POSITION_A, POSITION_B);

    // [Verification]
    BOOST_CHECK_EQUAL(*POSITION_A, EXPECTED_VALUE_A);
    BOOST_CHECK_EQUAL(*POSITION_B, EXPECTED_VALUE_B);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the first position provided is an end position.
/// </sumary>
QTEST_CASE( Swap2_AssertionFailsWhenFirstPositionIsEndPosition_Test )
{
    // [Preparation]
    u32_q arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    QFixedArray<u32_q>::QArrayIterator POSITION_A = arFixedArray.GetLast();
    ++POSITION_A;
    const QFixedArray<u32_q>::QArrayIterator POSITION_B = arFixedArray.GetFirst();
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arFixedArray.Swap(POSITION_A, POSITION_B);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

/// <sumary>
/// Checks that an assertion fails when the second position provided is an end position.
/// </sumary>
QTEST_CASE( Swap2_AssertionFailsWhenSecondPositionIsEndPosition_Test )
{
    // [Preparation]
    u32_q arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const QFixedArray<u32_q>::QArrayIterator POSITION_A = arFixedArray.GetFirst();
    QFixedArray<u32_q>::QArrayIterator POSITION_B = arFixedArray.GetLast();
    ++POSITION_B;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arFixedArray.Swap(POSITION_A, POSITION_B);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

/// <sumary>
/// Checks that an assertion fails when swapping the same element.
/// </sumary>
QTEST_CASE( Swap2_AssertionFailsWhenSwappingTheSameElement_Test )
{
    // [Preparation]
    u32_q arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const QFixedArray<u32_q>::QArrayIterator POSITION_A = arFixedArray.GetFirst();
    const QFixedArray<u32_q>::QArrayIterator POSITION_B = POSITION_A;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arFixedArray.Swap(POSITION_A, POSITION_B);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <sumary>
/// Checks that nothing happens when swapping the same element.
/// </sumary>
QTEST_CASE( Swap2_NothingHappensWhenSwappingTheSameElement_Test )
{
    // [Preparation]
    u32_q arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const QFixedArray<u32_q>::QArrayIterator POSITION_A = arFixedArray.GetFirst();
    const QFixedArray<u32_q>::QArrayIterator POSITION_B = POSITION_A;
    const u32_q EXPECTED_VALUE_A = *POSITION_A;
    const u32_q EXPECTED_VALUE_B = *POSITION_A;

    // [Execution]
    arFixedArray.Swap(POSITION_A, POSITION_B);

    // [Verification]
    BOOST_CHECK_EQUAL(*POSITION_A, EXPECTED_VALUE_A);
    BOOST_CHECK_EQUAL(*POSITION_B, EXPECTED_VALUE_B);
}

#endif

/// <sumary>
/// Checks that it returns True when arrays have the same number of elements and those elements are equal.
/// </sumary>
QTEST_CASE( OperatorEquality_ReturnsTrueWhenArraysHaveSameNumberOfElementsAndElementsAreEqual_Test )
{
    // [Preparation]
    u32_q arValues1[] = {0, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray1(arValues1, sizeof(arValues1) / sizeof(u32_q));
    u32_q arValues2[] = {0, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray2(arValues2, sizeof(arValues2) / sizeof(u32_q));
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = arFixedArray1 == arFixedArray2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when arrays are the same instance.
/// </sumary>
QTEST_CASE( OperatorEquality_ReturnsTrueWhenArraysAreSameInstance_Test )
{
    // [Preparation]
    u32_q arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = arFixedArray == arFixedArray;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when arrays have the same number of elements but elements are not equal.
/// </sumary>
QTEST_CASE( OperatorEquality_ReturnsFalseWhenArraysHaveSameNumberOfElementsButElementsAreNotEqual_Test )
{
    // [Preparation]
    u32_q arValues1[] = {0, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray1(arValues1, sizeof(arValues1) / sizeof(u32_q));
    u32_q arValues2[] = {7U, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray2(arValues2, sizeof(arValues2) / sizeof(u32_q));
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = arFixedArray1 == arFixedArray2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when arrays have different number of elements although elements are equal.
/// </sumary>
QTEST_CASE( OperatorEquality_ReturnsFalseWhenArraysHaveDifferentNumberOfElementsAlthoughElementsAreEqual_Test )
{
    // [Preparation]
    u32_q arValues1[] = {0, 1U, 2U, 3U};
    QFixedArray<u32_q> arFixedArray1(arValues1, sizeof(arValues1) / sizeof(u32_q));
    u32_q arValues2[] = {0, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray2(arValues2, sizeof(arValues2) / sizeof(u32_q));
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = arFixedArray1 == arFixedArray2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when arrays have the same number of elements and those elements are equal.
/// </sumary>
QTEST_CASE( OperatorInequality_ReturnsFalseWhenArraysHaveSameNumberOfElementsAndElementsAreEqual_Test )
{
    // [Preparation]
    u32_q arValues1[] = {0, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray1(arValues1, sizeof(arValues1) / sizeof(u32_q));
    u32_q arValues2[] = {0, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray2(arValues2, sizeof(arValues2) / sizeof(u32_q));
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = arFixedArray1 != arFixedArray2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when arrays are the same instance.
/// </sumary>
QTEST_CASE( OperatorInequality_ReturnsFalseWhenArraysAreSameInstance_Test )
{
    // [Preparation]
    u32_q arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = arFixedArray != arFixedArray;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when arrays have the same number of elements but elements are not equal.
/// </sumary>
QTEST_CASE( OperatorInequality_ReturnsTrueWhenArraysHaveSameNumberOfElementsButElementsAreNotEqual_Test )
{
    // [Preparation]
    u32_q arValues1[] = {0, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray1(arValues1, sizeof(arValues1) / sizeof(u32_q));
    u32_q arValues2[] = {7U, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray2(arValues2, sizeof(arValues2) / sizeof(u32_q));
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = arFixedArray1 != arFixedArray2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when arrays have different number of elements although elements are equal.
/// </sumary>
QTEST_CASE( OperatorInequality_ReturnsTrueWhenArraysHaveDifferentNumberOfElementsAlthoughElementsAreEqual_Test )
{
    // [Preparation]
    u32_q arValues1[] = {0, 1U, 2U, 3U};
    QFixedArray<u32_q> arFixedArray1(arValues1, sizeof(arValues1) / sizeof(u32_q));
    u32_q arValues2[] = {0, 1U, 2U, 3U, 4U, 5U};
    QFixedArray<u32_q> arFixedArray2(arValues2, sizeof(arValues2) / sizeof(u32_q));
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = arFixedArray1 != arFixedArray2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when the element appears the first.
/// </sumary>
QTEST_CASE( Contains_ReturnsTrueWhenElementAppearsTheFirst_Test )
{
    // [Preparation]
    const u32_q INPUT_ELEMENT = 2U;
    u32_q arValues[] = {INPUT_ELEMENT, 1U, 3U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = arFixedArray.Contains(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when the element appears in the middle.
/// </sumary>
QTEST_CASE( Contains_ReturnsTrueWhenElementAppearsInTheMiddle_Test )
{
    // [Preparation]
    const u32_q INPUT_ELEMENT = 2U;
    u32_q arValues[] = {1U, INPUT_ELEMENT, 3U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = arFixedArray.Contains(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when the element appears the last.
/// </sumary>
QTEST_CASE( Contains_ReturnsTrueWhenElementAppearsTheLast_Test )
{
    // [Preparation]
    const u32_q INPUT_ELEMENT = 2U;
    u32_q arValues[] = {1U, 3U, INPUT_ELEMENT};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = arFixedArray.Contains(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when the element is not in the array.
/// </sumary>
QTEST_CASE( Contains_ReturnsFalseWhenElementIsNotFound_Test )
{
    // [Preparation]
    const u32_q INPUT_ELEMENT = 2U;
    u32_q arValues[] = {1U, 3U, 4U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = arFixedArray.Contains(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns the expected index when the element appears the first.
/// </sumary>
QTEST_CASE( IndexOf1_ReturnsExpectedIndexWhenElementAppearsTheFirst_Test )
{
    // [Preparation]
    const u32_q INPUT_ELEMENT = 2U;
    u32_q arValues[] = {INPUT_ELEMENT, 1U, 3U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const pointer_uint_q EXPECTED_RESULT = 0;

    // [Execution]
    pointer_uint_q uResult = arFixedArray.IndexOf(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns the expected index when the element appears in the middle.
/// </sumary>
QTEST_CASE( IndexOf1_ReturnsExpectedIndexWhenElementAppearsInTheMiddle_Test )
{
    // [Preparation]
    const u32_q INPUT_ELEMENT = 2U;
    u32_q arValues[] = {1U, INPUT_ELEMENT, 3U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const pointer_uint_q EXPECTED_RESULT = 1U;

    // [Execution]
    pointer_uint_q uResult = arFixedArray.IndexOf(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns the expected index when the element appears the last.
/// </sumary>
QTEST_CASE( IndexOf1_ReturnsExpectedIndexWhenElementAppearsTheLast_Test )
{
    // [Preparation]
    const u32_q INPUT_ELEMENT = 2U;
    u32_q arValues[] = {1U, 3U, INPUT_ELEMENT};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const pointer_uint_q EXPECTED_RESULT = 2U;

    // [Execution]
    pointer_uint_q uResult = arFixedArray.IndexOf(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns ELEMENT_NOT_FOUND when the element is not in the array.
/// </sumary>
QTEST_CASE( IndexOf1_ReturnsElementNotFoundWhenElementIsNotFound_Test )
{
    // [Preparation]
    const u32_q INPUT_ELEMENT = 2U;
    u32_q arValues[] = {1U, 3U, 4U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const pointer_uint_q EXPECTED_RESULT = QFixedArray<u32_q>::ELEMENT_NOT_FOUND;

    // [Execution]
    pointer_uint_q uResult = arFixedArray.IndexOf(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns the expected index when the element appears the first.
/// </sumary>
QTEST_CASE( IndexOf2_ReturnsExpectedIndexWhenElementAppearsTheFirst_Test )
{
    // [Preparation]
    const pointer_uint_q START_POSITION = 0;
    const u32_q INPUT_ELEMENT = 2U;
    u32_q arValues[] = {INPUT_ELEMENT, 1U, 3U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const pointer_uint_q EXPECTED_RESULT = 0;

    // [Execution]
    pointer_uint_q uResult = arFixedArray.IndexOf(INPUT_ELEMENT, START_POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns the expected index when the element appears in the middle.
/// </sumary>
QTEST_CASE( IndexOf2_ReturnsExpectedIndexWhenElementAppearsInTheMiddle_Test )
{
    // [Preparation]
    const pointer_uint_q START_POSITION = 2U;
    const u32_q INPUT_ELEMENT = 2U;
    u32_q arValues[] = {INPUT_ELEMENT, 1U, INPUT_ELEMENT, 3U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const pointer_uint_q EXPECTED_RESULT = 2U;

    // [Execution]
    pointer_uint_q uResult = arFixedArray.IndexOf(INPUT_ELEMENT, START_POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns the expected index when the element appears the last.
/// </sumary>
QTEST_CASE( IndexOf2_ReturnsExpectedIndexWhenElementAppearsTheLast_Test )
{
    // [Preparation]
    const pointer_uint_q START_POSITION = 3U;
    const u32_q INPUT_ELEMENT = 2U;
    u32_q arValues[] = {INPUT_ELEMENT, 1U, 3U, INPUT_ELEMENT};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const pointer_uint_q EXPECTED_RESULT = 3U;

    // [Execution]
    pointer_uint_q uResult = arFixedArray.IndexOf(INPUT_ELEMENT, START_POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns ELEMENT_NOT_FOUND when the element is not in the array.
/// </sumary>
QTEST_CASE( IndexOf2_ReturnsElementNotFoundWhenElementIsNotFound_Test )
{
    // [Preparation]
    const pointer_uint_q START_POSITION = 0;
    const u32_q INPUT_ELEMENT = 2U;
    u32_q arValues[] = {1U, 3U, 4U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const pointer_uint_q EXPECTED_RESULT = QFixedArray<u32_q>::ELEMENT_NOT_FOUND;

    // [Execution]
    pointer_uint_q uResult = arFixedArray.IndexOf(INPUT_ELEMENT, START_POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns ELEMENT_NOT_FOUND when the element appears before the start position.
/// </sumary>
QTEST_CASE( IndexOf2_ReturnsElementNotFoundWhenElementAppearsBeforeTheStartPosition_Test )
{
    // [Preparation]
    const pointer_uint_q START_POSITION = 2U;
    const u32_q INPUT_ELEMENT = 2U;
    u32_q arValues[] = {INPUT_ELEMENT, 1U, 3U, 4U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const pointer_uint_q EXPECTED_RESULT = QFixedArray<u32_q>::ELEMENT_NOT_FOUND;

    // [Execution]
    pointer_uint_q uResult = arFixedArray.IndexOf(INPUT_ELEMENT, START_POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the start index is not lower than the number of elements.
/// </sumary>
QTEST_CASE( IndexOf2_AssertionFailsWhenStartIndexIsNotLowerThanCount_Test )
{
    // [Preparation]
    const u32_q INPUT_ELEMENT = 2U;
    u32_q arValues[] = {INPUT_ELEMENT, 1U, 3U, 4U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const pointer_uint_q START_POSITION = arFixedArray.GetCount();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arFixedArray.IndexOf(INPUT_ELEMENT, START_POSITION);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <sumary>
/// Checks that it returns ELEMENT_NOT_FOUND when the start position is not lower than the number of elements.
/// </sumary>
QTEST_CASE( IndexOf2_ReturnsElementNotFoundWhenStartPositionIsNotLowerThanCount_Test )
{
    // [Preparation]
    const u32_q INPUT_ELEMENT = 2U;
    u32_q arValues[] = {INPUT_ELEMENT, 1U, 3U, 4U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const pointer_uint_q START_POSITION = arFixedArray.GetCount();
    const pointer_uint_q EXPECTED_RESULT = QFixedArray<u32_q>::ELEMENT_NOT_FOUND;

    // [Execution]
    pointer_uint_q uResult = arFixedArray.IndexOf(INPUT_ELEMENT, START_POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_RESULT);
}

#endif

/// <sumary>
/// Checks that it returns the expected position when the element appears the first.
/// </sumary>
QTEST_CASE( PositionOf1_ReturnsExpectedPositionWhenElementAppearsTheFirst_Test )
{
    // [Preparation]
    const u32_q INPUT_ELEMENT = 2U;
    u32_q arValues[] = {INPUT_ELEMENT, 1U, 3U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const QFixedArray<u32_q>::QConstArrayIterator EXPECTED_RESULT = arFixedArray.GetFirst();

    // [Execution]
    QFixedArray<u32_q>::QConstArrayIterator itResult = arFixedArray.PositionOf(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK(itResult == EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns the expected position when the element appears in the middle.
/// </sumary>
QTEST_CASE( PositionOf1_ReturnsExpectedPositionWhenElementAppearsInTheMiddle_Test )
{
    // [Preparation]
    const u32_q INPUT_ELEMENT = 2U;
    u32_q arValues[] = {1U, INPUT_ELEMENT, 3U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const QFixedArray<u32_q>::QConstArrayIterator EXPECTED_RESULT = arFixedArray.GetIterator(1U);

    // [Execution]
    QFixedArray<u32_q>::QConstArrayIterator itResult = arFixedArray.PositionOf(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK(itResult == EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns the expected position when the element appears the last.
/// </sumary>
QTEST_CASE( PositionOf1_ReturnsExpectedPositionWhenElementAppearsTheLast_Test )
{
    // [Preparation]
    const u32_q INPUT_ELEMENT = 2U;
    u32_q arValues[] = {1U, 3U, INPUT_ELEMENT};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const QFixedArray<u32_q>::QConstArrayIterator EXPECTED_RESULT = arFixedArray.GetLast();

    // [Execution]
    QFixedArray<u32_q>::QConstArrayIterator itResult = arFixedArray.PositionOf(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK(itResult == EXPECTED_RESULT);
}

/// <sumary>
/// Checks that the returned iterator points to the end position when the element is not in the array.
/// </sumary>
QTEST_CASE( PositionOf1_ReturnsEndPositionWhenElementIsNotFound_Test )
{
    // [Preparation]
    const u32_q INPUT_ELEMENT = 2U;
    u32_q arValues[] = {1U, 3U, 4U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    QFixedArray<u32_q>::QConstArrayIterator EXPECTED_RESULT = arFixedArray.GetLast();
    ++EXPECTED_RESULT;

    // [Execution]
    QFixedArray<u32_q>::QConstArrayIterator itResult = arFixedArray.PositionOf(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK(itResult == EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns the expected position when the element appears the first.
/// </sumary>
QTEST_CASE( PositionOf2_ReturnsExpectedPositionWhenElementAppearsTheFirst_Test )
{
    // [Preparation]
    const u32_q INPUT_ELEMENT = 2U;
    u32_q arValues[] = {INPUT_ELEMENT, 1U, 3U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const QFixedArray<u32_q>::QConstArrayIterator START_POSITION = arFixedArray.GetFirst();
    const QFixedArray<u32_q>::QConstArrayIterator EXPECTED_RESULT = arFixedArray.GetFirst();

    // [Execution]
    QFixedArray<u32_q>::QConstArrayIterator itResult = arFixedArray.PositionOf(INPUT_ELEMENT, START_POSITION);

    // [Verification]
    BOOST_CHECK(itResult == EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns the expected position when the element appears in the middle.
/// </sumary>
QTEST_CASE( PositionOf2_ReturnsExpectedPositionWhenElementAppearsInTheMiddle_Test )
{
    // [Preparation]
    const u32_q INPUT_ELEMENT = 2U;
    u32_q arValues[] = {INPUT_ELEMENT, 1U, INPUT_ELEMENT, 3U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const QFixedArray<u32_q>::QConstArrayIterator START_POSITION = arFixedArray.GetIterator(2U);
    const QFixedArray<u32_q>::QConstArrayIterator EXPECTED_RESULT = arFixedArray.GetIterator(2U);

    // [Execution]
    QFixedArray<u32_q>::QConstArrayIterator itResult = arFixedArray.PositionOf(INPUT_ELEMENT, START_POSITION);

    // [Verification]
    BOOST_CHECK(itResult == EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns the expected position when the element appears the last.
/// </sumary>
QTEST_CASE( PositionOf2_ReturnsExpectedPositionWhenElementAppearsTheLast_Test )
{
    // [Preparation]
    const u32_q INPUT_ELEMENT = 2U;
    u32_q arValues[] = {INPUT_ELEMENT, 1U, 3U, INPUT_ELEMENT};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const QFixedArray<u32_q>::QConstArrayIterator START_POSITION = arFixedArray.GetIterator(3U);
    const QFixedArray<u32_q>::QConstArrayIterator EXPECTED_RESULT = arFixedArray.GetLast();

    // [Execution]
    QFixedArray<u32_q>::QConstArrayIterator itResult = arFixedArray.PositionOf(INPUT_ELEMENT, START_POSITION);

    // [Verification]
    BOOST_CHECK(itResult == EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns an iterator that points to the end position when the element is not in the array.
/// </sumary>
QTEST_CASE( PositionOf2_ReturnsEndPositionWhenElementIsNotFound_Test )
{
    // [Preparation]
    const u32_q INPUT_ELEMENT = 2U;
    u32_q arValues[] = {1U, 3U, 4U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const QFixedArray<u32_q>::QConstArrayIterator START_POSITION = arFixedArray.GetFirst();
    QFixedArray<u32_q>::QConstArrayIterator EXPECTED_RESULT = arFixedArray.GetLast();
    ++EXPECTED_RESULT;

    // [Execution]
    QFixedArray<u32_q>::QConstArrayIterator itResult = arFixedArray.PositionOf(INPUT_ELEMENT, START_POSITION);

    // [Verification]
    BOOST_CHECK(itResult == EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns an iterator that points to the end position when the element appears before the start position.
/// </sumary>
QTEST_CASE( PositionOf2_ReturnsEndPositionWhenElementAppearsBeforeTheStartPosition_Test )
{
    // [Preparation]
    const u32_q INPUT_ELEMENT = 2U;
    u32_q arValues[] = {INPUT_ELEMENT, 1U, 3U, 4U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    const QFixedArray<u32_q>::QConstArrayIterator START_POSITION = arFixedArray.GetIterator(2U);
    QFixedArray<u32_q>::QConstArrayIterator EXPECTED_RESULT = arFixedArray.GetLast();
    ++EXPECTED_RESULT;

    // [Execution]
    QFixedArray<u32_q>::QConstArrayIterator itResult = arFixedArray.PositionOf(INPUT_ELEMENT, START_POSITION);

    // [Verification]
    BOOST_CHECK(itResult == EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the input start position points to the end position.
/// </sumary>
QTEST_CASE( PositionOf2_AssertionFailsWhenStartPositionIsEnd_Test )
{
    // [Preparation]
    const u32_q INPUT_ELEMENT = 2U;
    u32_q arValues[] = {INPUT_ELEMENT, 1U, 3U, 4U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    QFixedArray<u32_q>::QConstArrayIterator START_POSITION = arFixedArray.GetLast();
    ++START_POSITION;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arFixedArray.PositionOf(INPUT_ELEMENT, START_POSITION);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <sumary>
/// Checks that it returns an iterator that points to the end position when the start position points to an end position.
/// </sumary>
QTEST_CASE( PositionOf2_ReturnsEndPositionWhenStartPositionPointsToEndPosition_Test )
{
    // [Preparation]
    const u32_q INPUT_ELEMENT = 2U;
    u32_q arValues[] = {INPUT_ELEMENT, 1U, 3U, 4U};
    QFixedArray<u32_q> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_q));
    QFixedArray<u32_q>::QConstArrayIterator START_POSITION = arFixedArray.GetLast();
    ++START_POSITION;
    QFixedArray<u32_q>::QConstArrayIterator EXPECTED_RESULT = arFixedArray.GetLast();
    ++EXPECTED_RESULT;

    // [Execution]
    QFixedArray<u32_q>::QConstArrayIterator itResult = arFixedArray.PositionOf(INPUT_ELEMENT, START_POSITION);

    // [Verification]
    BOOST_CHECK(itResult == EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks if returns a valid allocator.
/// </summary>
QTEST_CASE ( GetAllocator_ReturnsValidAllocator_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE = 12;
    const pointer_uint_q ARRAY_COUNT = 5;

    // [Execution]
    QFixedArray<u64_q> fixedArray = QFixedArray<u64_q>(ARRAY_COUNT, INITIAL_VALUE);

    u64_q uFirstValue = *((u64_q*)fixedArray.GetAllocator()->GetPointer());

    // [Verification]
    BOOST_CHECK_EQUAL( uFirstValue, INITIAL_VALUE );
}

/// <sumary>
/// Returns the number of elements in the array.
/// </sumary>
QTEST_CASE( GetCount_ReturnsNumberOfElementsInTheArray_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE = 12;
    const pointer_uint_q ARRAY_COUNT = 5;
    const pointer_uint_q EXPECTED_NUMBER_OF_ELEMENTS = ARRAY_COUNT;

    QFixedArray<u64_q> fixedArray = QFixedArray<u64_q>(ARRAY_COUNT, INITIAL_VALUE);

    // [Execution]
    pointer_uint_q uNumberOfElements = fixedArray.GetCount();

    // [Verification]
    BOOST_CHECK_EQUAL( uNumberOfElements, EXPECTED_NUMBER_OF_ELEMENTS );
}

/// <sumary>
/// Returns the capacity of the array.
/// </sumary>
QTEST_CASE( GetCapacity_ReturnsTheCapacityOfTheArray_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE = 12;
    const pointer_uint_q ARRAY_COUNT = 5;
    const pointer_uint_q EXPECTED_CAPACITY = ARRAY_COUNT;

    QFixedArray<u64_q> fixedArray = QFixedArray<u64_q>(ARRAY_COUNT, INITIAL_VALUE);

    // [Execution]
    pointer_uint_q uCapacity = fixedArray.GetCapacity();

    // [Verification]
    BOOST_CHECK_EQUAL( uCapacity, EXPECTED_CAPACITY );
}

/// <sumary>
/// Returns false when the array is not empty.
/// </sumary>
QTEST_CASE( IsEmpty_ReturnsFalseWhenTheArrayIsNotEmpty_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE = 12;
    const pointer_uint_q ARRAY_COUNT = 5;
    const bool ARRAY_NOT_EMPTY = false;

    QFixedArray<u64_q> fixedArray = QFixedArray<u64_q>(ARRAY_COUNT, INITIAL_VALUE);

    // [Execution]
    bool bIsEmpty = fixedArray.IsEmpty();

    // [Verification]
    BOOST_CHECK_EQUAL( bIsEmpty, ARRAY_NOT_EMPTY );
}

// End - Test Suite: QFixedArray
QTEST_SUITE_END()

