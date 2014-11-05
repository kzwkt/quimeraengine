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
#include "ArrayElementMock.h"

using Kinesis::QuimeraEngine::Common::DataTypes::u64_q;
using Kinesis::QuimeraEngine::Tools::Containers::QFixedArray;
using Kinesis::QuimeraEngine::Tools::Containers::Test::QFixedArrayWhiteBox;
using Kinesis::QuimeraEngine::Tools::Containers::Test::ArrayElementMock;

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
    const pointer_uint_q SIZEOF_VALUE_TYPE = sizeof(u64_q);
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
    const pointer_uint_q SIZEOF_VALUE_TYPE = sizeof(INITIAL_VALUE);
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
    const pointer_uint_q SIZEOF_VALUE_TYPE = sizeof(INITIAL_VALUE);
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
    const pointer_uint_q SIZEOF_VALUE_TYPE = sizeof(INITIAL_VALUE);
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

