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

#include "QList.h"
#include "QListWhiteBox.h"
#include "ListElementMock.h"
#include "CallCounter.h"

using Kinesis::QuimeraEngine::Tools::Containers::QList;
using Kinesis::QuimeraEngine::Common::DataTypes::u64_q;
using Kinesis::QuimeraEngine::Tools::Containers::Test::QListWhiteBox;
using Kinesis::QuimeraEngine::Tools::Containers::Test::ListElementMock;


QTEST_SUITE_BEGIN( QList_TestSuite )

/// <summary>
/// Checks if constructor without parameteres initializes members correctly.
/// </summary>
QTEST_CASE ( Constructor1_ChecksIfConstructorWithoutParametersInitializesMembersCorrectly_Test )
{
    // [Preparation]
    static const pointer_uint_q EXPECTED_END_POSITION_FORWARD = -1;
    static const pointer_uint_q EXPECTED_END_POSITION_BACKWARD = -2;
    static const pointer_uint_q INITIAL_CAPACITY = QListWhiteBox<u64_q>::GetDefaultInitialCapacity();

    // [Execution]
    QListWhiteBox<u64_q> list;

    // [Verification]
    pointer_uint_q uFirst = list.GetFirstPosition();
    pointer_uint_q uLast  = list.GetLastPosition();

    pointer_uint_q uInitialCapacity = list.GetCapacity();


    BOOST_CHECK_EQUAL( uFirst, EXPECTED_END_POSITION_BACKWARD );
    BOOST_CHECK_EQUAL( uLast, EXPECTED_END_POSITION_FORWARD );
    BOOST_CHECK_EQUAL( uInitialCapacity, INITIAL_CAPACITY );
}

/// <summary>
/// Checks if constructor with number of elements to reserve by parameter initializes members correctly.
/// </summary>
QTEST_CASE ( Constructor2_ChecksIfConstructorInitializesMembersCorrectly_Test )
{
    // [Preparation]
    static const pointer_uint_q EXPECTED_END_POSITION_FORWARD = -1;
    static const pointer_uint_q EXPECTED_END_POSITION_BACKWARD = -2;
    static const pointer_uint_q INITIAL_CAPACITY = 5;

    // [Execution]
    QListWhiteBox<u64_q> list( INITIAL_CAPACITY );

    // [Verification]
    pointer_uint_q uFirst = list.GetFirstPosition();
    pointer_uint_q uLast  = list.GetLastPosition();

    pointer_uint_q uInitialCapacity = list.GetCapacity();

    BOOST_CHECK_EQUAL( uFirst, EXPECTED_END_POSITION_BACKWARD );
    BOOST_CHECK_EQUAL( uLast, EXPECTED_END_POSITION_FORWARD );
    BOOST_CHECK_EQUAL( uInitialCapacity, INITIAL_CAPACITY );

}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Assertion failed when passing zero elements as initial capacity.
/// </summary>
QTEST_CASE ( Constructor2_AssertionFailedWhenPassingZeroElementsAsInitialCapacity_Test )
{
    // [Preparation]
    const pointer_uint_q INITIAL_CAPACITY_ZERO = 0;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        QList<u64_q> list(INITIAL_CAPACITY_ZERO);
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
/// Checks if copy constructor initializes correctly when passing a list with zero elements.
/// </summary>
QTEST_CASE ( Constructor3_ChecksIfConstructorInitializesCorrectlyWhenPassingAListWithZeroElements_Test )
{
    // [Preparation]
    static const pointer_uint_q EXPECTED_END_POSITION_FORWARD = -1;
    static const pointer_uint_q EXPECTED_END_POSITION_BACKWARD = -2;

    // [Execution]
    QListWhiteBox<u64_q> listOrigin = QListWhiteBox<u64_q>();
    QListWhiteBox<u64_q> listDestination = QListWhiteBox<u64_q>(listOrigin);

    // [Verification]
    pointer_uint_q uFirst = listDestination.GetFirstPosition();
    pointer_uint_q uLast  = listDestination.GetLastPosition();

    BOOST_CHECK_EQUAL( uFirst, EXPECTED_END_POSITION_BACKWARD );
    BOOST_CHECK_EQUAL( uLast, EXPECTED_END_POSITION_FORWARD );
}

/// <summary>
/// Checks if copy constructor initializes correctly when passing a full list.
/// </summary>
QTEST_CASE ( Constructor3_ChecksIfConstructorInitializesCorrectlyWhenPassingAFullList_Test )
{
    // [Preparation]
    const pointer_uint_q NUMBER_OF_ELEMENTS = 5;
    const bool SAME_VALUES = true;

    QList<u64_q> listOrigin = QList<u64_q>(NUMBER_OF_ELEMENTS);

    for(u64_q uIndex = 0; uIndex < NUMBER_OF_ELEMENTS; uIndex++)
    {
        listOrigin.Add(uIndex);
    }

    // [Execution]
    QList<u64_q> listDestination = QList<u64_q>(listOrigin);

    // [Verification]
    bool bSameValues = true;

    for(pointer_uint_q uIndex = 0; uIndex < NUMBER_OF_ELEMENTS; uIndex++)
    {
        bSameValues = bSameValues && (listOrigin.GetValue(uIndex) == listDestination.GetValue(uIndex));
    }

    BOOST_CHECK_EQUAL( bSameValues, SAME_VALUES );
}

/// <summary>
/// Checks if it assigns correctly when the size of the origin list is equal to the destination list.
/// </summary>
QTEST_CASE ( OperatorAssignment_CorrectlyAssignedWhenOriginListSizeIsEqualToDestinationListSize_Test )
{
    // [Preparation]
    const pointer_uint_q LIST_COUNT = 5;
    QList<u64_q> listOrigin = QList<u64_q>(LIST_COUNT);
    QList<u64_q> listDestination = QList<u64_q>(LIST_COUNT);

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT; uIndex++)
    {
        listOrigin.Add(uIndex);
        listDestination.Add(LIST_COUNT-uIndex);
    }

    const bool SAME_VALUES = true;

    // [Execution]
    listDestination = listOrigin;

    // [Verification]
    bool bSameValues = true;

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT; uIndex++)
    {
        bSameValues = bSameValues && (listDestination.GetValue(uIndex) == listOrigin.GetValue(uIndex));
    }

    BOOST_CHECK_EQUAL( bSameValues, SAME_VALUES );
}

/// <summary>
/// Checks if it assigns correctly when assigning a list to itself.
/// </summary>
QTEST_CASE ( OperatorAssignment_CorrectlyAssignedWhenAssigningAListToItself_Test )
{
    // [Preparation]
    const pointer_uint_q LIST_COUNT = 5;
    QList<u64_q> list = QList<u64_q>(LIST_COUNT);

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT; uIndex++)
    {
        list.Add(uIndex);
    }

    const bool SAME_VALUES = true;

    // [Execution]
    list = list;

    // [Verification]
    bool bSameValues = true;

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT; uIndex++)
    {
        bSameValues = bSameValues && (list.GetValue(uIndex) == uIndex);
    }

    BOOST_CHECK_EQUAL( bSameValues, SAME_VALUES );
}

/// <summary>
/// Checks if it assigns correctly when the size of the origin list is minor than the destination list.
/// </summary>
QTEST_CASE ( OperatorAssignment_CorrectlyAssignedWhenOriginListSizeIsMinorThanDestinationListSize_Test )
{
    // [Preparation]
    const pointer_uint_q INITIAL_CAPACITY = 5;
    const pointer_uint_q LIST_COUNT_ORIGIN = 3;
    const pointer_uint_q LIST_COUNT_DESTINATION = 5;
    QList<u64_q> listOrigin = QList<u64_q>(INITIAL_CAPACITY);
    QList<u64_q> listDestination = QList<u64_q>(INITIAL_CAPACITY);

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        listOrigin.Add(uIndex+10);
    }

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT_DESTINATION; uIndex++)
    {
        listDestination.Add(uIndex);
    }

    const bool SAME_VALUES = true;

    // [Execution]
    listDestination = listOrigin;

    // [Verification]
    bool bSameValues = true;

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        bSameValues = bSameValues && (listDestination.GetValue(uIndex) == listOrigin.GetValue(uIndex));
    }

    BOOST_CHECK_EQUAL( bSameValues, SAME_VALUES );
}

/// <summary>
/// Checks if it assigns correctly when the size of the origin list is zero and the destination list has elements.
/// </summary>
QTEST_CASE ( OperatorAssignment_CorrectlyAssignedWhenOriginListIsZeroAndTheDestinationListHasElements_Test )
{
    // [Preparation]
    const pointer_uint_q INITIAL_CAPACITY = 5;
    const pointer_uint_q LIST_COUNT_DESTINATION = 5;
    QList<u64_q> listOrigin = QList<u64_q>(INITIAL_CAPACITY);
    QList<u64_q> listDestination = QList<u64_q>(INITIAL_CAPACITY);
    const bool DESTINATION_IS_EMPTY = true;

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT_DESTINATION; uIndex++)
    {
        listDestination.Add(uIndex);
    }

    const bool SAME_VALUES = true;

    // [Execution]
    listDestination = listOrigin;

    // [Verification]
    bool bDestinationIsEmpty = listDestination.IsEmpty();

    BOOST_CHECK_EQUAL( bDestinationIsEmpty, DESTINATION_IS_EMPTY );
}

/// <summary>
/// Checks if it assigns correctly when the size of the origin list is greater than the destination list and
/// destination list capacity is not minor than origin list capacity.
/// </summary>
QTEST_CASE ( OperatorAssignment_CorrectlyAssignedWhenOriginListSizeIsGreaterThanDestinationListSizeAndDestinationListCapacityIsNotMinorThanOriginListCapacity_Test )
{
    // [Preparation]
    const pointer_uint_q LISTS_CAPACITY = 5;
    const pointer_uint_q LIST_COUNT_ORIGIN = 5;
    const pointer_uint_q LIST_COUNT_DESTINATION = 3;
    QList<u64_q> listOrigin = QList<u64_q>(LISTS_CAPACITY);
    QList<u64_q> listDestination = QList<u64_q>(LISTS_CAPACITY);

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        listOrigin.Add(uIndex+10);
    }

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT_DESTINATION; uIndex++)
    {
        listDestination.Add(uIndex);
    }

    const bool SAME_VALUES = true;

    // [Execution]
    listDestination = listOrigin;

    // [Verification]
    bool bSameValues = true;

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        bSameValues = bSameValues && (listDestination.GetValue(uIndex) == listOrigin.GetValue(uIndex));
    }

    BOOST_CHECK_EQUAL( bSameValues, SAME_VALUES );
}

/// <summary>
/// Checks if it assigns correctly when the size of the origin list is greater than the destination list and
/// the capacity of the origin list is greater than the capacity of the destination list.
/// </summary>
QTEST_CASE ( OperatorAssignment_CorrectlyAssignedWhenOriginListSizeIsGreaterThanDestinationListSizeAndOriginListCapacityIsGreaterThanDestinationListCapacity_Test )
{
    // [Preparation]
    const pointer_uint_q LIST_CAPACITY_ORIGIN = 5;
    const pointer_uint_q LIST_CAPACITY_DESTINATION = 3;
    const pointer_uint_q LIST_COUNT_ORIGIN = 5;
    const pointer_uint_q LIST_COUNT_DESTINATION = 3;
    QList<u64_q> listOrigin = QList<u64_q>(LIST_CAPACITY_ORIGIN);
    QList<u64_q> listDestination = QList<u64_q>(LIST_CAPACITY_DESTINATION);

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        listOrigin.Add(uIndex+10);
    }

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT_DESTINATION; uIndex++)
    {
        listDestination.Add(uIndex);
    }

    const bool SAME_VALUES = true;

    // [Execution]
    listDestination = listOrigin;

    // [Verification]
    bool bSameValues = true;

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        bSameValues = bSameValues && (listDestination.GetValue(uIndex) == listOrigin.GetValue(uIndex));
    }

    BOOST_CHECK_EQUAL( bSameValues, SAME_VALUES );
}

/// <summary>
/// Checks if it assigns correctly when the size of the origin list is greater than the destination list and
/// the capacity of the two lists are equal.
/// </summary>
QTEST_CASE ( OperatorAssignment_CorrectlyAssignedWhenOriginListSizeIsGreaterThanDestinationListSizeAndOriginListCapacityOfBothIsEqual_Test )
{
    // [Preparation]
    const pointer_uint_q LIST_CAPACITY = 5;
    const pointer_uint_q LIST_COUNT_ORIGIN = 5;
    const pointer_uint_q LIST_COUNT_DESTINATION = 3;
    QList<u64_q> listOrigin = QList<u64_q>(LIST_CAPACITY);
    QList<u64_q> listDestination = QList<u64_q>(LIST_CAPACITY);

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        listOrigin.Add(uIndex+10);
    }

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT_DESTINATION; uIndex++)
    {
        listDestination.Add(uIndex);
    }

    const bool SAME_VALUES = true;

    // [Execution]
    listDestination = listOrigin;

    // [Verification]
    bool bSameValues = true;

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        bSameValues = bSameValues && (listDestination.GetValue(uIndex) == listOrigin.GetValue(uIndex));
    }

    BOOST_CHECK_EQUAL( bSameValues, SAME_VALUES );
}

/// <summary>
/// Checks if it the clone method works properly.
/// </summary>
QTEST_CASE ( Clone_ClonedListHasSameValuesThanTheOriginalList_Test )
{
    // [Preparation]
    const pointer_uint_q LIST_CAPACITY = 5;
    const pointer_uint_q LIST_COUNT_ORIGIN = 5;
    QList<u64_q> listOrigin = QList<u64_q>(LIST_CAPACITY);
    QList<u64_q> listDestination = QList<u64_q>(LIST_CAPACITY);
    const bool VALUES_ARE_THE_SAME = true;

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        listOrigin.Add(uIndex+10);
    }

    // [Execution]
    listOrigin.Clone(listDestination);

    // [Verification]
    bool bSameValues = true;

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        bSameValues = bSameValues && (listDestination.GetValue(uIndex) == listOrigin.GetValue(uIndex));
    }

    BOOST_CHECK_EQUAL( bSameValues, VALUES_ARE_THE_SAME );
}

/// <summary>
/// Checks if it the clone method works properly when the size of the destination list is bigger.
/// </summary>
QTEST_CASE ( Clone_ClonedListHasSameValuesThanTheOriginalListWhenInputListSizeIsBigger_Test )
{
    // [Preparation]
    const pointer_uint_q LIST_CAPACITY_ORIGIN = 5;
    const pointer_uint_q LIST_CAPACITY_DESTINATION = 8;
    const pointer_uint_q LIST_COUNT_ORIGIN = 5;
    QList<u64_q> listOrigin = QList<u64_q>(LIST_CAPACITY_ORIGIN);
    QList<u64_q> listDestination = QList<u64_q>(LIST_CAPACITY_DESTINATION);
    const bool VALUES_ARE_THE_SAME = true;

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        listOrigin.Add(uIndex+10);
    }

    // [Execution]
    listOrigin.Clone(listDestination);

    // [Verification]
    bool bSameValues = true;

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        bSameValues = bSameValues && (listDestination.GetValue(uIndex) == listOrigin.GetValue(uIndex));
    }

    BOOST_CHECK_EQUAL( bSameValues, VALUES_ARE_THE_SAME );
}

/// <summary>
/// Checks if it the clone method works properly when the size of the destination list is lower.
/// </summary>
QTEST_CASE ( Clone_ClonedListHasSameValuesThanTheOriginalListWhenInputListSizeIsLower_Test )
{
    // [Preparation]
    const pointer_uint_q LIST_CAPACITY_ORIGIN = 8;
    const pointer_uint_q LIST_CAPACITY_DESTINATION = 5;
    const pointer_uint_q LIST_COUNT_ORIGIN = 8;
    QList<u64_q> listOrigin = QList<u64_q>(LIST_CAPACITY_ORIGIN);
    QList<u64_q> listDestination = QList<u64_q>(LIST_CAPACITY_DESTINATION);
    const bool VALUES_ARE_THE_SAME = true;

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        listOrigin.Add(uIndex+10);
    }

    // [Execution]
    listOrigin.Clone(listDestination);

    // [Verification]
    bool bSameValues = true;

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        bSameValues = bSameValues && (listDestination.GetValue(uIndex) == listOrigin.GetValue(uIndex));
    }

    BOOST_CHECK_EQUAL( bSameValues, VALUES_ARE_THE_SAME );
}

/// <summary>
/// Checks if it the getValue method method returns the value placed in the position passed as parameter.
/// </summary>
QTEST_CASE ( GetValue_CorrectValueReturned_Test )
{
    // [Preparation]
    const pointer_uint_q LIST_CAPACITY = 5;
    const pointer_uint_q LIST_COUNT_ORIGIN = 5;
    const u64_q VALUE_TO_RETURN = 19;
    const u64_q VALUE_TO_FILL_LIST = 4;
    const pointer_uint_q INDEX_POSITION_TO_RETURN = 3;
    u64_q uReturnedValue = 0;
    QList<u64_q> list = QList<u64_q>(LIST_CAPACITY);

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        if (uIndex == INDEX_POSITION_TO_RETURN)
        {
            list.Add(VALUE_TO_RETURN);
        }
        else
        {
            list.Add(VALUE_TO_FILL_LIST);
        }
    }

    // [Execution]
    uReturnedValue = list.GetValue(INDEX_POSITION_TO_RETURN);

    // [Verification]
    BOOST_CHECK_EQUAL( uReturnedValue, VALUE_TO_RETURN );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Assertion failed when passing non existant index to get the value.
/// </summary>
QTEST_CASE ( GetValue_AssertionFailedWhenPassingAnIndexBiggerThanNumberOfElements_Test )
{
    // [Preparation]
    const pointer_uint_q LIST_CAPACITY = 5;
    const pointer_uint_q LIST_COUNT_ORIGIN = 5;
    const u64_q VALUE_TO_FILL_LIST = 4;
    const pointer_uint_q INDEX_POSITION_TO_RETURN = 10;
    QList<u64_q> list = QList<u64_q>(LIST_CAPACITY);
    const bool ASSERTION_FAILED = true;
    u64_q uReturnedValue = 0;

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        list.Add(VALUE_TO_FILL_LIST);
    }

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        uReturnedValue = list.GetValue(INDEX_POSITION_TO_RETURN);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Assertion failed when empty list.
/// </summary>
QTEST_CASE ( GetValue_AssertionFailedWhenListIsEmpty_Test )
{
    // [Preparation]
    const pointer_uint_q LIST_CAPACITY = 5;
    const pointer_uint_q INDEX_POSITION_TO_RETURN = 4;
    QList<u64_q> list = QList<u64_q>(LIST_CAPACITY);
    const bool ASSERTION_FAILED = true;
    u64_q uReturnedValue = 0;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        uReturnedValue = list.GetValue(INDEX_POSITION_TO_RETURN);
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
/// Checks if it the method set the value in the position passed as parameter.
/// </summary>
QTEST_CASE ( SetValue_CorrectValueSet_Test )
{
    // [Preparation]
    const pointer_uint_q LIST_CAPACITY = 5;
    const pointer_uint_q LIST_COUNT_ORIGIN = 5;
    const u64_q VALUE_TO_SET = 19;
    const u64_q VALUE_TO_FILL_LIST = 4;
    const pointer_uint_q INDEX_POSITION_TO_SET = 3;
    QList<u64_q> list = QList<u64_q>(LIST_CAPACITY);

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        list.Add(VALUE_TO_FILL_LIST);
    }

    // [Execution]
    list.SetValue(INDEX_POSITION_TO_SET, VALUE_TO_SET);

    // [Verification]
    u64_q uReturnedValue = list.GetValue(INDEX_POSITION_TO_SET);
    BOOST_CHECK_EQUAL( uReturnedValue, VALUE_TO_SET );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Assertion failed when empty list.
/// </summary>
QTEST_CASE ( SetValue_AssertionFailedWhenListIsEmpty_Test )
{
    // [Preparation]
    const pointer_uint_q LIST_CAPACITY = 5;
    const pointer_uint_q INDEX_POSITION_TO_SET = 4;
    QList<u64_q> list(LIST_CAPACITY);
    const u64_q VALUE_TO_SET = 10;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        list.SetValue(INDEX_POSITION_TO_SET, VALUE_TO_SET);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Assertion failed when trying to set a value in a wrong index.
/// </summary>
QTEST_CASE ( SetValue_AssertionFailedWhenSettingValueInWrongIndex_Test )
{
    // [Preparation]
    const pointer_uint_q LIST_CAPACITY = 5;
    const pointer_uint_q LIST_COUNT_ORIGIN = 5;
    const u64_q VALUE_TO_FILL_LIST = 4;
    const pointer_uint_q INDEX_POSITION_TO_SET = 10;
    QList<u64_q> list = QList<u64_q>(LIST_CAPACITY);
    const bool ASSERTION_FAILED = true;

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        list.Add(VALUE_TO_FILL_LIST);
    }

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        list.SetValue(INDEX_POSITION_TO_SET, VALUE_TO_FILL_LIST);
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
/// Checks if it the operator returns the value placed in the position passed as parameter.
/// </summary>
QTEST_CASE ( OperatorListSubscript_CorrectValueReturned_Test )
{
    // [Preparation]
    const pointer_uint_q LIST_CAPACITY = 5;
    const pointer_uint_q LIST_COUNT_ORIGIN = 5;
    const u64_q VALUE_TO_RETURN = 19;
    const u64_q VALUE_TO_FILL_LIST = 4;
    const pointer_uint_q INDEX_POSITION_TO_RETURN = 3;
    u64_q uReturnedValue = 0;
    QList<u64_q> list = QList<u64_q>(LIST_CAPACITY);

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        if (uIndex == INDEX_POSITION_TO_RETURN)
        {
            list.Add(VALUE_TO_RETURN);
        }
        else
        {
            list.Add(VALUE_TO_FILL_LIST);
        }
    }

    // [Execution]
    uReturnedValue = list[INDEX_POSITION_TO_RETURN];

    // [Verification]
    BOOST_CHECK_EQUAL( uReturnedValue, VALUE_TO_RETURN );
}


#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Assertion failed when empty list.
/// </summary>
QTEST_CASE ( OperatorListSubscript_AssertionFailedWhenListIsEmpty_Test )
{
    // [Preparation]
    const pointer_uint_q LIST_CAPACITY = 5;
    const pointer_uint_q INDEX_POSITION_TO_RETURN = 4;
    QList<u64_q> list = QList<u64_q>(LIST_CAPACITY);
    const bool ASSERTION_FAILED = true;
    u64_q uReturnedValue = 0;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        uReturnedValue = list[INDEX_POSITION_TO_RETURN];
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Assertion failed when passing a wrong index to get the element.
/// </summary>
QTEST_CASE ( OperatorListSubscript_AssertionFailedWhenPassingAnIndexBiggerThanNumberOfElements_Test )
{
    // [Preparation]
    const pointer_uint_q LIST_CAPACITY = 5;
    const pointer_uint_q LIST_COUNT = 5;
    const u64_q VALUE_TO_FILL_LIST = 4;
     const pointer_uint_q INDEX_POSITION_TO_RETURN = 10;
    QList<u64_q> list = QList<u64_q>(LIST_CAPACITY);
    const bool ASSERTION_FAILED = true;
    u64_q uReturnedValue = 0;

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT; uIndex++)
    {
        list.Add(VALUE_TO_FILL_LIST);
    }

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        uReturnedValue = list[INDEX_POSITION_TO_RETURN];
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
/// Checks that the expected iterator is returned when using a common list and a common index.
/// </sumary>
QTEST_CASE( GetIterator_ReturnsTheExpectedIteratorWhenUsingCommonListAndPosition_Test )
{
    // [Preparation]
    const pointer_uint_q NUMBER_OF_ELEMENTS = 5;
    const pointer_uint_q INPUT_INDEX = 1;
    QList<int> list = QList<int>(NUMBER_OF_ELEMENTS);

    for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
        list.Add(i);

    QList<int>::QListIterator EXPECTED_ITERATOR = list.GetFirst();
    ++EXPECTED_ITERATOR;

    // [Execution]
    QList<int>::QListIterator it = list.GetIterator(INPUT_INDEX);

    // [Verification]
    BOOST_CHECK(it == EXPECTED_ITERATOR);
}

/// <sumary>
/// Checks that the first position is returned when using a common list and the index equals zero.
/// </sumary>
QTEST_CASE( GetIterator_ReturnsTheFirstPositionWhenUsingCommonListAndZeroIndex_Test )
{
    // [Preparation]
    const pointer_uint_q NUMBER_OF_ELEMENTS = 5;
    const pointer_uint_q INPUT_INDEX = 0;
    QList<int> list = QList<int>(NUMBER_OF_ELEMENTS);

    for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
        list.Add(i);

    QList<int>::QListIterator EXPECTED_ITERATOR = list.GetFirst();

    // [Execution]
    QList<int>::QListIterator it = list.GetIterator(INPUT_INDEX);

    // [Verification]
    BOOST_CHECK(it == EXPECTED_ITERATOR);
}

/// <sumary>
/// Checks that the last position is returned when using a common list and the last index.
/// </sumary>
QTEST_CASE( GetIterator_ReturnsTheLastPositionWhenUsingCommonListAndLastIndex_Test )
{
    // [Preparation]
    const pointer_uint_q NUMBER_OF_ELEMENTS = 5;
    const pointer_uint_q INPUT_INDEX = NUMBER_OF_ELEMENTS - 1U;
    QList<int> list = QList<int>(NUMBER_OF_ELEMENTS);

    for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
        list.Add(i);

    QList<int>::QListIterator EXPECTED_ITERATOR = list.GetLast();

    // [Execution]
    QList<int>::QListIterator it = list.GetIterator(INPUT_INDEX);

    // [Verification]
    BOOST_CHECK(it == EXPECTED_ITERATOR);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the list is empty.
/// </sumary>
QTEST_CASE( GetIterator_AssertionFailsWhenListIsEmpty_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_INDEX = 0;
    QList<int> list = QList<int>();
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        list.GetIterator(INPUT_INDEX);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <sumary>
/// Checks that an assertion fails when the input index is out of bounds.
/// </sumary>
QTEST_CASE( GetIterator_AssertionFailsWhenIndexIsOutOfBounds_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const pointer_uint_q NUMBER_OF_ELEMENTS = 5;
    const pointer_uint_q OUT_OF_BOUNDS_INDEX = NUMBER_OF_ELEMENTS;
    QList<int> list = QList<int>(NUMBER_OF_ELEMENTS);

    for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
        list.Add(i);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        list.GetIterator(OUT_OF_BOUNDS_INDEX);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <sumary>
/// Checks that the resultant iterator points to the end position when the list is empty.
/// </sumary>
QTEST_CASE( GetIterator_IteratorPointsToEndPositionWhenListIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const pointer_uint_q INPUT_INDEX = 0;
    QList<int> list = QList<int>();
    const bool ITERATOR_POINTS_END_POSITION = true;

    // [Execution]
    QList<int>::QListIterator it = list.GetIterator(INPUT_INDEX);

    // [Verification]
    bool bIsEnd = it.IsEnd(EQIterationDirection::E_Forward);
    BOOST_CHECK_EQUAL(bIsEnd, ITERATOR_POINTS_END_POSITION);
}

/// <sumary>
/// Checks that the resultant iterator points to the end position when the input index is out of bounds.
/// </sumary>
QTEST_CASE( GetIterator_IteratorPointsToEndPositionWhenIndexIsOutOfBounds_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const bool ITERATOR_POINTS_END_POSITION = true;
    const pointer_uint_q NUMBER_OF_ELEMENTS = 5;
    const pointer_uint_q OUT_OF_BOUNDS_INDEX = NUMBER_OF_ELEMENTS;
    QList<int> list = QList<int>(NUMBER_OF_ELEMENTS);

    for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
        list.Add(i);

    // [Execution]
    QList<int>::QListIterator it = list.GetIterator(OUT_OF_BOUNDS_INDEX);

    // [Verification]
    bool bIsEnd = it.IsEnd(EQIterationDirection::E_Forward);
    BOOST_CHECK_EQUAL(bIsEnd, ITERATOR_POINTS_END_POSITION);
}

#endif

/// <sumary>
/// Checks that the first position is returned when using a common list.
/// </sumary>
QTEST_CASE( GetFirst_ReturnsTheFirstPositionWhenUsingCommonList_Test )
{
    // [Preparation]
    const pointer_uint_q NUMBER_OF_ELEMENTS = 5;
    QList<int> list = QList<int>(NUMBER_OF_ELEMENTS);

    for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
        list.Add(i);

    QList<int>::QListIterator EXPECTED_ITERATOR(&list, 0);

    // [Execution]
    QList<int>::QListIterator it = list.GetFirst();

    // [Verification]
    BOOST_CHECK(it == EXPECTED_ITERATOR);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the list is empty.
/// </sumary>
QTEST_CASE( GetFirst_AssertionFailsWhenListIsEmpty_Test )
{
    // [Preparation]
    QList<int> list = QList<int>();
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        list.GetFirst();
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <sumary>
/// Checks that the resultant iterator points to the end position when the list is empty.
/// </sumary>
QTEST_CASE( GetFirst_IteratorPointsToEndPositionWhenListIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    QList<int> list = QList<int>();
    const bool ITERATOR_POINTS_END_POSITION = true;

    // [Execution]
    QList<int>::QListIterator it = list.GetFirst();

    // [Verification]
    bool bIsEnd = it.IsEnd(EQIterationDirection::E_Forward);
    BOOST_CHECK_EQUAL(bIsEnd, ITERATOR_POINTS_END_POSITION);
}

#endif

/// <sumary>
/// Checks that the last position is returned when using a common list.
/// </sumary>
QTEST_CASE( GetLast_ReturnsTheLastPositionWhenUsingCommonList_Test )
{
    // [Preparation]
    const pointer_uint_q NUMBER_OF_ELEMENTS = 5;
    QList<int> list = QList<int>(NUMBER_OF_ELEMENTS);

    for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
        list.Add(i);

    QList<int>::QListIterator EXPECTED_ITERATOR(&list, NUMBER_OF_ELEMENTS - 1U);

    // [Execution]
    QList<int>::QListIterator it = list.GetLast();

    // [Verification]
    BOOST_CHECK(it == EXPECTED_ITERATOR);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the list is empty.
/// </sumary>
QTEST_CASE( GetLast_AssertionFailsWhenListIsEmpty_Test )
{
    // [Preparation]
    QList<int> list = QList<int>();
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        list.GetLast();
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <sumary>
/// Checks that the resultant iterator points to the end position when the list is empty.
/// </sumary>
QTEST_CASE( GetLast_IteratorPointsToEndPositionWhenListIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    QList<int> list = QList<int>();
    const bool ITERATOR_POINTS_END_POSITION = true;

    // [Execution]
    QList<int>::QListIterator it = list.GetLast();

    // [Verification]
    bool bIsEnd = it.IsEnd(EQIterationDirection::E_Forward);
    BOOST_CHECK_EQUAL(bIsEnd, ITERATOR_POINTS_END_POSITION);
}

#endif

/// <summary>
/// Checks that the capacity is correctly increased.
/// </summary>
QTEST_CASE ( Reserve_CapacityIsCorrectlyIncreased_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_CAPACITY = 4U;
    QList<int> list(1U);

    // [Execution]
    list.Reserve(EXPECTED_CAPACITY);

    // [Verification]
    pointer_uint_q uStoredCapacity = list.GetCapacity();

    BOOST_CHECK_EQUAL(uStoredCapacity, EXPECTED_CAPACITY);
}

/// <summary>
/// Checks that elements are correctly reallocated.
/// </summary>
QTEST_CASE ( Reserve_ElementsAreCorrectlyReallocated_Test )
{
    // [Preparation]
    const bool ELEMENTS_ARE_THE_SAME = true;
    const pointer_uint_q INPUT_CAPACITY = 20U;
    QList<int> list(3U);
    const pointer_uint_q NUMBER_OF_ELEMENTS = 3;
    
    for(pointer_uint_q i = 0; i < NUMBER_OF_ELEMENTS; ++i)
        list.Add(i);

    // [Execution]
    list.Reserve(INPUT_CAPACITY); // A reallocation occurs

    // [Verification]
    bool bElementsAreTheSame = true;

    for(pointer_uint_q i = 0; i < NUMBER_OF_ELEMENTS; ++i)
        bElementsAreTheSame = bElementsAreTheSame && (list[i] == i);

    BOOST_CHECK_EQUAL(bElementsAreTheSame, ELEMENTS_ARE_THE_SAME);
}

/// <summary>
/// Checks that elements are not reallocated and capacity does not change when attempting to reserve less memory than currently reserved.
/// </summary>
QTEST_CASE ( Reserve_NothingHappensWhenTheAmountToReserveIsNoGreaterThanCurrentCapacity_Test )
{/* [TODO] Thund: Uncomment when Add is implemented
    // [Preparation]
    const bool ELEMENTS_ARE_THE_SAME = true;
    const pointer_uint_q INPUT_CAPACITY = 1U;
    const pointer_uint_q EXPECTED_CAPACITY = 3U;
    QList<int> list(EXPECTED_CAPACITY);
    
    for(pointer_uint_q i = 0; i < EXPECTED_CAPACITY; ++i)
        list.Add(i);

    const int* ORIGINAL_FIRST_ELEMENT_ADDRESS = &list[0];

    // [Execution]
    list.Reserve(INPUT_CAPACITY);

    // [Verification]
    pointer_uint_q uCapacity = list.GetCapacity();
    int* pFirstElementAddress = &list[0];

    BOOST_CHECK_EQUAL(pFirstElementAddress, ORIGINAL_FIRST_ELEMENT_ADDRESS);
    BOOST_CHECK_EQUAL(uCapacity, EXPECTED_CAPACITY);*/
}

// [TODO] raul. Uncomment the test when method Add exists.
/*
/// <summary>
/// Checks if the method returns the correct number of elements in the list.
/// </summary>
QTEST_CASE ( GetCount_CorrectNumberOfElementsReturned_Test )
{
    // [Preparation]
    const pointer_uint_q LIST_CAPACITY = 5;
    const pointer_uint_q LIST_COUNT_ORIGIN = 5;
    pointer_uint_q uReturnedValue = 0;
    QList<u64_q> list = QList<u64_q>(LIST_CAPACITY);

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        list.Add(VALUE_TO_FILL_LIST);
    }

    // [Execution]
    uReturnedValue = list.GetCount();

    // [Verification]
    BOOST_CHECK_EQUAL( uReturnedValue, LIST_COUNT_ORIGIN );
}
*/

/// <summary>
/// Checks that elements can be added to empty lists.
/// </summary>
QTEST_CASE ( Add_ElementIsCorrectlyAddedToEmptyList_Test )
{
    // [Preparation]
    QList<int> arEmptyList;
    const int ELEMENT_VALUE = 1;

    // [Execution]
    arEmptyList.Add(ELEMENT_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(arEmptyList[0], ELEMENT_VALUE);
}

/// <summary>
/// Checks that the capacity is increased when elements are added to a full list.
/// </summary>
QTEST_CASE ( Add_CapacityIsIncreasedWhenAddingElementsToFullList_Test )
{
    // [Preparation]
    const pointer_uint_q INITIAL_CAPACITY = 3U;
    QList<int> arFullList(INITIAL_CAPACITY);
    arFullList.Add(0);
    arFullList.Add(0);
    arFullList.Add(0);
    const int ELEMENT_VALUE = 1;

    // [Execution]
    arFullList.Add(ELEMENT_VALUE);

    // [Verification]
    pointer_uint_q uCapacity =  arFullList.GetCapacity();
    BOOST_CHECK(uCapacity > INITIAL_CAPACITY);
}

/// <summary>
/// Checks that elements are correctly added when lists are full.
/// </summary>
QTEST_CASE ( Add_ElementIsCorrectlyAddedWhenListIsFull_Test )
{
    // [Preparation]
    const pointer_uint_q INITIAL_CAPACITY = 3U;
    QList<int> arFullList(INITIAL_CAPACITY);
    arFullList.Add(0);
    arFullList.Add(0);
    arFullList.Add(0);
    const int ELEMENT_VALUE = 1;

    // [Execution]
    arFullList.Add(ELEMENT_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(arFullList[3], ELEMENT_VALUE);
}

/// <summary>
/// Checks that elements are correctly added at the end of a common list.
/// </summary>
QTEST_CASE ( Add_ElementIsCorrectlyAddedAtTheEnd_Test )
{
    // [Preparation]
    const pointer_uint_q INITIAL_CAPACITY = 3U;
    QList<int> arCommonList(INITIAL_CAPACITY);
    arCommonList.Add(0);
    const int ELEMENT_VALUE = 1;

    // [Execution]
    arCommonList.Add(ELEMENT_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(arCommonList[1], ELEMENT_VALUE);
}

/// <summary>
/// Checks that the count of elements of the list is increased after an element is added.
/// </summary>
QTEST_CASE ( Add_CountIsIncreasedAfterAddingAnElement_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_COUNT = 1;
    const int ELEMENT_VALUE = 1;
    const pointer_uint_q INITIAL_CAPACITY = 3U;
    QList<int> arCommonList(INITIAL_CAPACITY);

    // [Execution]
    arCommonList.Add(ELEMENT_VALUE);

    // [Verification]
    pointer_uint_q uCount = arCommonList.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the copy constructor of the element is called when adding it to the list.
/// </summary>
QTEST_CASE ( Add_CopyConstructorIsCalledForAddedElements_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    const pointer_uint_q EXPECTED_CALLS = 1;
    const pointer_uint_q INITIAL_CAPACITY = 3U;
    QList<CallCounter> arCommonList(INITIAL_CAPACITY);
    CallCounter newElement;
    CallCounter::ResetCounters();

    // [Execution]
    arCommonList.Add(newElement);

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
    QList<int> arCommonList;
    arCommonList.Add(0);
    const int ELEMENT_VALUE = 1;
    const QList<int>::QListIterator POSITION = arCommonList.GetFirst();

    // [Execution]
    arCommonList.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(arCommonList[0], ELEMENT_VALUE);
}

/// <summary>
/// Checks that elements can be inserted in between of two existing elements.
/// </summary>
QTEST_CASE ( Insert1_ElementIsCorrectlyInsertedInBetween_Test )
{
    // [Preparation]
    QList<int> arCommonList(3U);
    arCommonList.Add(0);
    arCommonList.Add(0);
    const int ELEMENT_VALUE = 1;
    const QList<int>::QListIterator POSITION = arCommonList.GetIterator(1);

    // [Execution]
    arCommonList.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(arCommonList[1], ELEMENT_VALUE);
}

/// <summary>
/// Checks that the capacity is increased when elements are added to a full list.
/// </summary>
QTEST_CASE ( Insert1_CapacityIsIncreasedWhenAddingElementsToFullList_Test )
{
    // [Preparation]
    const pointer_uint_q INITIAL_CAPACITY = 3U;
    QList<int> arFullList(INITIAL_CAPACITY);
    arFullList.Add(0);
    arFullList.Add(0);
    arFullList.Add(0);
    const int ELEMENT_VALUE = 1;
    const QList<int>::QListIterator POSITION = arFullList.GetFirst();

    // [Execution]
    arFullList.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    pointer_uint_q uCapacity =  arFullList.GetCapacity();
    BOOST_CHECK(uCapacity > INITIAL_CAPACITY);
}

/// <summary>
/// Checks that the count of elements of the list is increased after an element is added.
/// </summary>
QTEST_CASE ( Insert1_CountIsIncreasedAfterAddingAnElement_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_COUNT = 2;
    const int ELEMENT_VALUE = 1;
    const pointer_uint_q INITIAL_CAPACITY = 3U;
    QList<int> arCommonList(INITIAL_CAPACITY);
    arCommonList.Add(0);
    const QList<int>::QListIterator POSITION = arCommonList.GetFirst();

    // [Execution]
    arCommonList.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    pointer_uint_q uCount = arCommonList.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the copy constructor of the element is called when adding it to the list.
/// </summary>
QTEST_CASE ( Insert1_CopyConstructorIsCalledForAddedElements_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    const pointer_uint_q EXPECTED_CALLS = 1;
    const pointer_uint_q INITIAL_CAPACITY = 3U;
    QList<CallCounter> arCommonList(INITIAL_CAPACITY);
    arCommonList.Add(CallCounter());
    CallCounter newElement;
    CallCounter::ResetCounters();
    const QList<CallCounter>::QListIterator POSITION = arCommonList.GetFirst();

    // [Execution]
    arCommonList.Insert(newElement, POSITION);

    // [Verification]
    pointer_uint_q uCopyConstructorCalls = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uCopyConstructorCalls, EXPECTED_CALLS);
}

/// <summary>
/// Checks that it returns an iterator that returns to the inserted element.
/// </summary>
QTEST_CASE ( Insert1_ReturnsIteratorThatPointsToInsertedElement_Test )
{
    // [Preparation]
    QList<int> arCommonList(3U);
    arCommonList.Add(0);
    arCommonList.Add(0);
    const int ELEMENT_VALUE = 1;
    const QList<int>::QListIterator POSITION = arCommonList.GetIterator(1);

    // [Execution]
    QList<int>::QListIterator itResult = arCommonList.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(*itResult, ELEMENT_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator points to the forward end position.
/// </summary>
QTEST_CASE ( Insert1_AssertionFailsWhenIteratorsPointsToForwardEndPosition_Test )
{
    // [Preparation]
    QList<int> arCommonList;
    arCommonList.Add(0);
    QList<int>::QListIterator ITERATOR_END = arCommonList.GetLast();
    ++ITERATOR_END;
    const bool ASSERTION_FAILED = true;
    const int ELEMENT_VALUE = 1;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonList.Insert(ELEMENT_VALUE, ITERATOR_END);
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
/// Checks that elements can be inserted into empty lists.
/// </summary>
QTEST_CASE ( Insert1_ElementIsInsertedIntoEmptyList_Test )
{
    // [Preparation]
    QList<int> arEmptyList;
    QList<int>::QListIterator ITERATOR = arEmptyList.GetFirst();
    const int ELEMENT_VALUE = 1;

    // [Execution]
    arEmptyList.Insert(ELEMENT_VALUE, ITERATOR);

    // [Verification]
    BOOST_CHECK_EQUAL(arEmptyList[0], ELEMENT_VALUE);
}

/// <summary>
/// Checks that elements are inserted at the end when the iterator points to the forward end position.
/// </summary>
QTEST_CASE ( Insert1_ElementIsInsertedAtTheEndWhenIteratorsPointsToForwardEndPosition_Test )
{
    // [Preparation]
    QList<int> arCommonList;
    arCommonList.Add(0);
    QList<int>::QListIterator ITERATOR_END = arCommonList.GetLast();
    ++ITERATOR_END;
    const int ELEMENT_VALUE = 1;

    // [Execution]
    arCommonList.Insert(ELEMENT_VALUE, ITERATOR_END);

    // [Verification]
    BOOST_CHECK_EQUAL(arCommonList[1], ELEMENT_VALUE);
}

#endif

/// <summary>
/// Checks that elements can be inserted at the first position.
/// </summary>
QTEST_CASE ( Insert2_ElementIsCorrectlyInsertedAtFirstPosition_Test )
{
    // [Preparation]
    QList<int> arCommonList;
    arCommonList.Add(0);
    const int ELEMENT_VALUE = 1;
    const pointer_uint_q POSITION = 0;

    // [Execution]
    arCommonList.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(arCommonList[0], ELEMENT_VALUE);
}

/// <summary>
/// Checks that elements can be inserted in between of two existing elements.
/// </summary>
QTEST_CASE ( Insert2_ElementIsCorrectlyInsertedInBetween_Test )
{
    // [Preparation]
    QList<int> arCommonList(3U);
    arCommonList.Add(0);
    arCommonList.Add(0);
    const int ELEMENT_VALUE = 1;
    const pointer_uint_q POSITION = 1;

    // [Execution]
    arCommonList.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(arCommonList[1], ELEMENT_VALUE);
}

/// <summary>
/// Checks that the capacity is increased when elements are added to a full list.
/// </summary>
QTEST_CASE ( Insert2_CapacityIsIncreasedWhenAddingElementsToFullList_Test )
{
    // [Preparation]
    const pointer_uint_q INITIAL_CAPACITY = 3U;
    QList<int> arFullList(INITIAL_CAPACITY);
    arFullList.Add(0);
    arFullList.Add(0);
    arFullList.Add(0);
    const int ELEMENT_VALUE = 1;
    const pointer_uint_q POSITION = 0;

    // [Execution]
    arFullList.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    pointer_uint_q uCapacity = arFullList.GetCapacity();
    BOOST_CHECK(uCapacity > INITIAL_CAPACITY);
}

/// <summary>
/// Checks that the count of elements of the list is increased after an element is added.
/// </summary>
QTEST_CASE ( Insert2_CountIsIncreasedAfterAddingAnElement_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_COUNT = 2;
    const int ELEMENT_VALUE = 1;
    const pointer_uint_q INITIAL_CAPACITY = 3U;
    QList<int> arCommonList(INITIAL_CAPACITY);
    arCommonList.Add(0);
    const pointer_uint_q POSITION = 0;

    // [Execution]
    arCommonList.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    pointer_uint_q uCount = arCommonList.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the copy constructor of the element is called when adding it to the list.
/// </summary>
QTEST_CASE ( Insert2_CopyConstructorIsCalledForAddedElements_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    const pointer_uint_q EXPECTED_CALLS = 1;
    const pointer_uint_q INITIAL_CAPACITY = 3U;
    QList<CallCounter> arCommonList(INITIAL_CAPACITY);
    arCommonList.Add(CallCounter());
    CallCounter newElement;
    CallCounter::ResetCounters();
    const pointer_uint_q POSITION = 0;

    // [Execution]
    arCommonList.Insert(newElement, POSITION);

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
    QList<int> arCommonList;
    arCommonList.Add(0);
    const pointer_uint_q OUT_OF_BOUNDS_INDEX = arCommonList.GetCount();
    const bool ASSERTION_FAILED = true;
    const int ELEMENT_VALUE = 1;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonList.Insert(ELEMENT_VALUE, OUT_OF_BOUNDS_INDEX);
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
/// Checks that elements can be inserted into empty lists.
/// </summary>
QTEST_CASE ( Insert2_ElementIsInsertedIntoEmptyList_Test )
{
    // [Preparation]
    QList<int> arEmptyList;
    const pointer_uint_q POSITION = 0;
    const int ELEMENT_VALUE = 1;

    // [Execution]
    arEmptyList.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(arEmptyList[0], ELEMENT_VALUE);
}

/// <summary>
/// Checks that elements are inserted at the end when the index is out of bounds.
/// </summary>
QTEST_CASE ( Insert2_ElementIsInsertedAtTheEndWhenIndexIsOutOfBounds_Test )
{
    // [Preparation]
    QList<int> arCommonList;
    arCommonList.Add(0);
    const pointer_uint_q INDEX_OUT_OF_BOUNDS = arCommonList.GetCount();
    const int ELEMENT_VALUE = 1;

    // [Execution]
    arCommonList.Insert(ELEMENT_VALUE, INDEX_OUT_OF_BOUNDS);

    // [Verification]
    BOOST_CHECK_EQUAL(arCommonList[1], ELEMENT_VALUE);
}

#endif

/// <summary>
/// Checks that elements are correctly removed from the last position of the list.
/// </summary>
QTEST_CASE ( Remove1_ElementIsCorrectlyRemovedFromLastPosition_Test )
{
    // [Preparation]
    const bool ELEMENT_DOES_NOT_EXIST = true;
    const int ELEMENT_VALUE = 1;
    QList<int> arCommonList(3U);
    arCommonList.Add(0);
    arCommonList.Add(0);
    arCommonList.Add(ELEMENT_VALUE);
    const QList<int>::QListIterator POSITION = arCommonList.GetLast();

    // [Execution]
    arCommonList.Remove(POSITION);

    // [Verification]
    /* [TODO] Thund: Uncomment when Contains method exists
    bool bElementDoesNotExist = !arCommonList.Contains(ELEMENT_VALUE);
    BOOST_CHECK_EQUAL(bElementDoesNotExist, ELEMENT_DOES_NOT_EXIST);*/
}

/// <summary>
/// Checks that elements are correctly removed from the first position of the list.
/// </summary>
QTEST_CASE ( Remove1_ElementIsCorrectlyRemovedFromFirstPosition_Test )
{
    // [Preparation]
    const bool ELEMENT_DOES_NOT_EXIST = true;
    const int ELEMENT_VALUE = 1;
    QList<int> arCommonList(3U);
    arCommonList.Add(ELEMENT_VALUE);
    arCommonList.Add(0);
    arCommonList.Add(0);
    const QList<int>::QListIterator POSITION = arCommonList.GetFirst();

    // [Execution]
    arCommonList.Remove(POSITION);

    // [Verification]
    /* [TODO] Thund: Uncomment when Contains method exists
    bool bElementDoesNotExist = !arCommonList.Contains(ELEMENT_VALUE);
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
    QList<int> arCommonList(3U);
    arCommonList.Add(0);
    arCommonList.Add(ELEMENT_VALUE);
    arCommonList.Add(0);
    const QList<int>::QListIterator POSITION = arCommonList.GetIterator(1);

    // [Execution]
    arCommonList.Remove(POSITION);

    // [Verification]
    /* [TODO] Thund: Uncomment when Contains method exists
    bool bElementDoesNotExist = !arCommonList.Contains(ELEMENT_VALUE);
    BOOST_CHECK_EQUAL(bElementDoesNotExist, ELEMENT_DOES_NOT_EXIST);*/
}

/// <summary>
/// Checks that count of elements in the list decreases after they are removed.
/// </summary>
QTEST_CASE ( Remove1_CountDecreasesAfterRemovingElements_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_COUNT = 2;
    QList<int> arCommonList(3U);
    arCommonList.Add(0);
    arCommonList.Add(0);
    arCommonList.Add(0);
    const QList<int>::QListIterator POSITION = arCommonList.GetFirst();

    // [Execution]
    arCommonList.Remove(POSITION);

    // [Verification]
    pointer_uint_q uCount = arCommonList.GetCount();
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
    QList<CallCounter> arCommonList;
    arCommonList.Add(CallCounter());
    const QList<CallCounter>::QListIterator POSITION = arCommonList.GetFirst();
    CallCounter::ResetCounters();

    // [Execution]
    arCommonList.Remove(POSITION);

    // [Verification]
    pointer_uint_q uDestructorCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorCalls, EXPECTED_CALLS);
}

/// <summary>
/// Checks that the returned iterator points to the next element when the removed element was not the last one.
/// </summary>
QTEST_CASE ( Remove1_ReturnedIteratorPointsNextWhenElementWasNotTheLastOne_Test )
{
    // [Preparation]
    const int EXPECTED_ELEMENT = 1;
    QList<int> arCommonList(3U);
    arCommonList.Add(0);
    arCommonList.Add(EXPECTED_ELEMENT);
    arCommonList.Add(0);
    const QList<int>::QListIterator POSITION = arCommonList.GetFirst();

    // [Execution]
    QList<int>::QListIterator itResult = arCommonList.Remove(POSITION);

    // [Verification]
    int nValue = *itResult;
    BOOST_CHECK_EQUAL(nValue, EXPECTED_ELEMENT);
}

/// <summary>
/// Checks that the returned iterator points to the end position when the removed element was the last one.
/// </summary>
QTEST_CASE ( Remove1_ReturnedIteratorPointsEndPositionWhenElementWasTheLastOne_Test )
{
    // [Preparation]
    const bool POINTS_END_POSITION = true;
    QList<int> arCommonList(3U);
    arCommonList.Add(0);
    arCommonList.Add(0);
    arCommonList.Add(0);
    const QList<int>::QListIterator POSITION = arCommonList.GetLast();

    // [Execution]
    QList<int>::QListIterator itResult = arCommonList.Remove(POSITION);

    // [Verification]
    bool bPointsToEndPosition = itResult.IsEnd();
    BOOST_CHECK_EQUAL(bPointsToEndPosition, POINTS_END_POSITION);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator points to the forward end position.
/// </summary>
QTEST_CASE ( Remove1_AssertionFailsWhenIteratorsPointsToForwardEndPosition_Test )
{
    // [Preparation]
    QList<int> arCommonList;
    arCommonList.Add(0);
    QList<int>::QListIterator ITERATOR_END = arCommonList.GetLast();
    ++ITERATOR_END;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonList.Remove(ITERATOR_END);
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
    QList<int> arCommonList;
    arCommonList.Add(0);
    const pointer_uint_q EXPECTED_COUNT = arCommonList.GetCount();
    QList<int>::QListIterator ITERATOR_END = arCommonList.GetLast();
    ++ITERATOR_END;

    // [Execution]
    arCommonList.Remove(ITERATOR_END);

    // [Verification]
    pointer_uint_q uCount = arCommonList.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that nothing happens when the list is empty.
/// </summary>
QTEST_CASE ( Remove1_NothingHappensWhenListIsEmpty_Test )
{
    // [Preparation]
    QList<int> arCommonList;
    const pointer_uint_q EXPECTED_COUNT = 0;
    QList<int>::QListIterator ITERATOR = arCommonList.GetFirst();

    // [Execution]
    arCommonList.Remove(ITERATOR);

    // [Verification]
    pointer_uint_q uCount = arCommonList.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

#endif

/// <summary>
/// Checks that elements are correctly removed from the last position of the list.
/// </summary>
QTEST_CASE ( Remove2_ElementIsCorrectlyRemovedFromLastPosition_Test )
{
    // [Preparation]
    const bool ELEMENT_DOES_NOT_EXIST = true;
    const int ELEMENT_VALUE = 1;
    QList<int> arCommonList(3U);
    arCommonList.Add(0);
    arCommonList.Add(0);
    arCommonList.Add(ELEMENT_VALUE);
    const pointer_uint_q POSITION = arCommonList.GetCount() - 1U;

    // [Execution]
    arCommonList.Remove(POSITION);

    // [Verification]
    /* [TODO] Thund: Uncomment when Contains method exists
    bool bElementDoesNotExist = !arCommonList.Contains(ELEMENT_VALUE);
    BOOST_CHECK_EQUAL(bElementDoesNotExist, ELEMENT_DOES_NOT_EXIST);*/
}

/// <summary>
/// Checks that elements are correctly removed from the first position of the list.
/// </summary>
QTEST_CASE ( Remove2_ElementIsCorrectlyRemovedFromFirstPosition_Test )
{
    // [Preparation]
    const bool ELEMENT_DOES_NOT_EXIST = true;
    const int ELEMENT_VALUE = 1;
    QList<int> arCommonList(3U);
    arCommonList.Add(ELEMENT_VALUE);
    arCommonList.Add(0);
    arCommonList.Add(0);
    const pointer_uint_q POSITION = 0;

    // [Execution]
    arCommonList.Remove(POSITION);

    // [Verification]
    /* [TODO] Thund: Uncomment when Contains method exists
    bool bElementDoesNotExist = !arCommonList.Contains(ELEMENT_VALUE);
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
    QList<int> arCommonList(3U);
    arCommonList.Add(0);
    arCommonList.Add(ELEMENT_VALUE);
    arCommonList.Add(0);
    const pointer_uint_q POSITION = 1;

    // [Execution]
    arCommonList.Remove(POSITION);

    // [Verification]
    /* [TODO] Thund: Uncomment when Contains method exists
    bool bElementDoesNotExist = !arCommonList.Contains(ELEMENT_VALUE);
    BOOST_CHECK_EQUAL(bElementDoesNotExist, ELEMENT_DOES_NOT_EXIST);*/
}

/// <summary>
/// Checks that count of elements in the list decreases after they are removed.
/// </summary>
QTEST_CASE ( Remove2_CountDecreasesAfterRemovingElements_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_COUNT = 2;
    QList<int> arCommonList(3U);
    arCommonList.Add(0);
    arCommonList.Add(0);
    arCommonList.Add(0);
    const pointer_uint_q POSITION = 0;

    // [Execution]
    arCommonList.Remove(POSITION);

    // [Verification]
    pointer_uint_q uCount = arCommonList.GetCount();
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
    QList<CallCounter> arCommonList;
    arCommonList.Add(CallCounter());
    const pointer_uint_q POSITION = 0;
    CallCounter::ResetCounters();

    // [Execution]
    arCommonList.Remove(POSITION);

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
    QList<int> arCommonList;
    arCommonList.Add(0);
    const pointer_uint_q POSITION = arCommonList.GetCount();
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonList.Remove(POSITION);
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
    QList<int> arCommonList;
    arCommonList.Add(0);
    const pointer_uint_q EXPECTED_COUNT = arCommonList.GetCount();
    const pointer_uint_q POSITION = arCommonList.GetCount();

    // [Execution]
    arCommonList.Remove(POSITION);

    // [Verification]
    pointer_uint_q uCount = arCommonList.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that nothing happens when the list is empty.
/// </summary>
QTEST_CASE ( Remove2_NothingHappensWhenListIsEmpty_Test )
{
    // [Preparation]
    QList<int> arCommonList;
    const pointer_uint_q EXPECTED_COUNT = 0;
    const pointer_uint_q POSITION = 0;

    // [Execution]
    arCommonList.Remove(POSITION);

    // [Verification]
    pointer_uint_q uCount = arCommonList.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

#endif

/// <summary>
/// Checks that nothing happens when the list is empty.
/// </summary>
QTEST_CASE ( Clear_NothingHappensWhenListIsEmpty_Test )
{
    // [Preparation]
    QList<int> arCommonList;
    const pointer_uint_q EXPECTED_COUNT = 0;

    // [Execution]
    arCommonList.Clear();

    // [Verification]
    pointer_uint_q uCount = arCommonList.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that all the elements are removed when the list is full.
/// </summary>
QTEST_CASE ( Clear_AllElemensAreRemovedWhenListIsFull_Test )
{
    // [Preparation]
    QList<int> arCommonList(3U);
    arCommonList.Add(0);
    arCommonList.Add(0);
    arCommonList.Add(0);
    const pointer_uint_q EXPECTED_COUNT = 0;

    // [Execution]
    arCommonList.Clear();

    // [Verification]
    pointer_uint_q uCount = arCommonList.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that all the elements are removed when the list contains some elements.
/// </summary>
QTEST_CASE ( Clear_AllElementsAreRemovedWhenListContainsSomeElements_Test )
{
    // [Preparation]
    QList<int> arCommonList(3U);
    arCommonList.Add(0);
    arCommonList.Add(0);
    const pointer_uint_q EXPECTED_COUNT = 0;

    // [Execution]
    arCommonList.Clear();

    // [Verification]
    pointer_uint_q uCount = arCommonList.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the destructor of every element is called.
/// </summary>
QTEST_CASE ( Clear_DestructorIsCalledForEveryElement_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    QList<CallCounter> arCommonList(3U);
    arCommonList.Add(CallCounter());
    arCommonList.Add(CallCounter());
    const pointer_uint_q EXPECTED_CALLS = 2;
    CallCounter::ResetCounters();

    // [Execution]
    arCommonList.Clear();

    // [Verification]
    pointer_uint_q uDestructorCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorCalls, EXPECTED_CALLS);
}

/// <summary>
/// Checks if the method returns the correct number of elements in the list.
/// </summary>
QTEST_CASE ( GetCount_MethodReturnsZeroWithEmptyList_Test )
{
    // [Preparation]
    const pointer_uint_q LIST_CAPACITY = 5;
    pointer_uint_q uReturnedValue = 0;
    const pointer_uint_q EXPECTED_VALUE = 0;
    QList<u64_q> list(LIST_CAPACITY);

    // [Execution]
    uReturnedValue = list.GetCount();

    // [Verification]
    BOOST_CHECK_EQUAL( uReturnedValue, EXPECTED_VALUE );
}

/// <summary>
/// Checks if the method returns true when the list is empty.
/// </summary>
QTEST_CASE ( IsEmpty_ReturnsTrueWhenEmptyList_Test )
{
    // [Preparation]
    const pointer_uint_q LIST_CAPACITY = 5;
    const bool LIST_IS_EMPTY = true;
    bool bIsEmptyList = false;
    QList<u64_q> list(LIST_CAPACITY);

    // [Execution]
    bIsEmptyList = list.IsEmpty();

    // [Verification]
    BOOST_CHECK_EQUAL( bIsEmptyList, LIST_IS_EMPTY );
}

/// <summary>
/// Checks if the method returns false when the list is not empty.
/// </summary>
QTEST_CASE ( IsEmpty_ReturnsFalseWhenNoEmptyList_Test )
{
    // [Preparation]
    const pointer_uint_q LIST_CAPACITY = 1;
    const pointer_uint_q LIST_COUNT_ORIGIN = 1;
    const bool LIST_IS_EMPTY = false;
    bool bIsEmptyList = true;
    QList<u64_q> list = QList<u64_q>(LIST_CAPACITY);

    for(pointer_uint_q uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        list.Add(uIndex + 10);
    }

    // [Execution]
    bIsEmptyList = list.IsEmpty();

    // [Verification]
    BOOST_CHECK_EQUAL( bIsEmptyList, LIST_IS_EMPTY );
}

/// <sumary>
/// Returns the capacity of the list.
/// </sumary>
QTEST_CASE( GetCapacity_ReturnsTheCapacityOfTheList_Test )
{
    // [Preparation]
    const pointer_uint_q LIST_CAPACITY = 5;
    const pointer_uint_q EXPECTED_CAPACITY = LIST_CAPACITY;
    QList<u64_q> list(LIST_CAPACITY);

    // [Execution]
    pointer_uint_q uCapacity = list.GetCapacity();

    // [Verification]
    BOOST_CHECK_EQUAL( uCapacity, EXPECTED_CAPACITY );
}


// End - Test Suite: QList

QTEST_SUITE_END()
