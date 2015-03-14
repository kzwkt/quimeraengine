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

#include "EQIterationDirection.h"

using Kinesis::QuimeraEngine::Tools::Containers::QFixedArray;

/// <summary>
/// Small structure used in operator* and operator-> tests.
/// </summary>
struct TestStructure
{
    TestStructure(const int nField) : m_nField(nField)
    {
    }

    int m_nField;
};

QTEST_SUITE_BEGIN( QArrayIterator_TestSuite )

/// <summary>
/// Checks that the iterator points to the given position when using a common array.
/// </summary>
QTEST_CASE ( Constructor_IteratorPointsToGivenPositionWhenUsingCommonArray_Test )
{
    // [Preparation]
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    const unsigned int POSITION = 1;
    QFixedArray<int>::QArrayIterator EXPECTED_ITERATOR(&SOURCE_ARRAY, 0);
    EXPECTED_ITERATOR.MoveFirst();
    ++EXPECTED_ITERATOR;

	// [Execution]
    QFixedArray<int>::QArrayIterator iterator(&SOURCE_ARRAY, POSITION);
    
    // [Verification]
    BOOST_CHECK(iterator == EXPECTED_ITERATOR);
}

/// <summary>
/// Checks that the iterator points to the end position (forward iteration) when using an empty array.
/// </summary>
QTEST_CASE ( Constructor_IteratorPointsToForwardEndPositionWhenUsingEmptyArray_Test )
{
    /*[TODO] Thund: Uncomment when QDynamicArray exists
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const QDynamicArray<int> SOURCE_ARRAY(3, 0);
    const bool IS_END = true;

	// [Execution]
    QDynamicArray<int>::QArrayIterator iterator(SOURCE_ARRAY, 0);

    // [Verification]
    bool bIsEndIterationForward = iterator.IsEnd(EQIterationDirection::E_Forward);
    BOOST_CHECK_EQUAL(bIsEndIterationForward, IS_END);*/
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when input array is null.
/// </summary>
QTEST_CASE ( Constructor_AssertionFailsWhenInputArrayIsNull_Test )
{
    // [Preparation]
    QFixedArray<int>* SOURCE_ARRAY = null_q;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QFixedArray<int>::QArrayIterator INVALID_ITERATOR(SOURCE_ARRAY, 0);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when input position is not lower than the number of elements.
/// </summary>
QTEST_CASE ( Constructor_AssertionFailsWhenInputPositionIsNotLowerThanCount_Test )
{
    // [Preparation]
    const unsigned int NUMBER_OF_ELEMENTS = 3;
    QFixedArray<int> SOURCE_ARRAY(NUMBER_OF_ELEMENTS, 0);
    const unsigned int INVALID_POSITION = NUMBER_OF_ELEMENTS;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QFixedArray<int>::QArrayIterator INVALID_ITERATOR(&SOURCE_ARRAY, INVALID_POSITION);
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
/// Checks that the iterator points to the end position (forward iteration) when using an invalid position.
/// </summary>
QTEST_CASE ( Constructor_IteratorPointsToForwardEndPositionWhenUsingInvalidPosition_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const unsigned int NUMBER_OF_ELEMENTS = 3;
    QFixedArray<int> SOURCE_ARRAY(NUMBER_OF_ELEMENTS, 0);
    const unsigned int INVALID_POSITION = NUMBER_OF_ELEMENTS;
    const bool IS_END = true;

	// [Execution]
    QFixedArray<int>::QArrayIterator iterator(&SOURCE_ARRAY, INVALID_POSITION);

    // [Verification]
    bool bIsEndIterationForward = iterator.IsEnd(EQIterationDirection::E_Forward);
    BOOST_CHECK_EQUAL(bIsEndIterationForward, IS_END);
}

#endif

/// <summary>
/// Checks that the element pointed to by the iterator is returned.
/// </summary>
QTEST_CASE ( OperatorIndirection_ReturnsTheCorrespondingElement_Test )
{
    // [Preparation]
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    const int EXPECTED_VALUE = 1;
    SOURCE_ARRAY[1] = EXPECTED_VALUE;
    QFixedArray<int>::QArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR++;

	// [Execution]
    int nValue = *ITERATOR;

    // [Verification]
    BOOST_CHECK_EQUAL(nValue, EXPECTED_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorIndirection_AssertionFailsWhenIteratorIsInvalid_Test )
{
    /* [TODO] Thund: Uncomment when QDynamicArray exists
    // [Preparation]
    QDynamicArray<int> SOURCE_ARRAY(10, 0);
    QFixedArray<int>::QArrayIterator INVALID_ITERATOR(&SOURCE_ARRAY, 0);
    INVALID_ITERATOR.MoveLast();
    SOURCE_ARRAY.Remove(0);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        *INVALID_ITERATOR;
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);*/
}

/// <summary>
/// Checks that an assertion fails when the iterator is pointing to the end position (forward iteration).
/// </summary>
QTEST_CASE ( OperatorIndirection_AssertionFailsWhenIteratorPointsToForwardEndPosition_Test )
{
    // [Preparation]
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR.MoveLast();
    ++ITERATOR;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        *ITERATOR;
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the iterator is pointing to the end position (backward iteration).
/// </summary>
QTEST_CASE ( OperatorIndirection_AssertionFailsWhenIteratorPointsToBackwardEndPosition_Test )
{
    // [Preparation]
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR.MoveFirst();
    --ITERATOR;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        *ITERATOR;
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that the element pointed to by the iterator is returned.
/// </summary>
QTEST_CASE ( OperatorDereferencing_ReturnsTheCorrespondingElement_Test )
{
    // [Preparation]
    QFixedArray<TestStructure> SOURCE_ARRAY(3, TestStructure(0));
    const int EXPECTED_VALUE = 1;
    SOURCE_ARRAY[1] = TestStructure(EXPECTED_VALUE);
    QFixedArray<TestStructure>::QArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR++;

	// [Execution]
    int nValue = ITERATOR->m_nField;

    // [Verification]
    BOOST_CHECK_EQUAL(nValue, EXPECTED_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorDereferencing_AssertionFailsWhenIteratorIsInvalid_Test )
{
    /* [TODO] Thund: Uncomment when QDynamicArray exists
    // [Preparation]
    QDynamicArray<TestStructure> SOURCE_ARRAY(10, TestStructure(0));
    QFixedArray<TestStructure>::QArrayIterator INVALID_ITERATOR(&SOURCE_ARRAY, 0);
    INVALID_ITERATOR.MoveLast();
    SOURCE_ARRAY.Remove(0);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        INVALID_ITERATOR->m_nField;
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);*/
}

/// <summary>
/// Checks that an assertion fails when the iterator is pointing to the end position (forward iteration).
/// </summary>
QTEST_CASE ( OperatorDereferencing_AssertionFailsWhenIteratorPointsToForwardEndPosition_Test )
{
    // [Preparation]
    QFixedArray<TestStructure> SOURCE_ARRAY(3, TestStructure(0));
    QFixedArray<TestStructure>::QArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR.MoveLast();
    ++ITERATOR;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ITERATOR->m_nField;
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the iterator is pointing to the end position (backward iteration).
/// </summary>
QTEST_CASE ( OperatorDereferencing_AssertionFailsWhenIteratorPointsToBackwardEndPosition_Test )
{
    // [Preparation]
    QFixedArray<TestStructure> SOURCE_ARRAY(3, TestStructure(0));
    QFixedArray<TestStructure>::QArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR.MoveFirst();
    --ITERATOR;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ITERATOR->m_nField;
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that the iterator steps forward properly and returns the previous state.
/// </summary>
QTEST_CASE ( OperatorPostIncrement_CommonIteratorStepsForwardProperlyAndReturnsPreviousState_Test )
{
    // [Preparation]
    const int SECOND_ELEMENT_VALUE = 2;
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    SOURCE_ARRAY[1] = SECOND_ELEMENT_VALUE;
    QFixedArray<int>::QArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ORIGINAL_ITERATOR.MoveFirst();

	// [Execution]
    QFixedArray<int>::QArrayIterator iterator(ORIGINAL_ITERATOR);
    QFixedArray<int>::QArrayIterator iteratorPreviousState = iterator++;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(*iterator == SECOND_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the iterator points to the first position and returns the previous state when it was pointing to the end position before the first one.
/// </summary>
QTEST_CASE ( OperatorPostIncrement_IteratorPointsToFirstPositionAndReturnsPreviousStateWhenItWasPointingToPositionBeforeFirst_Test )
{
    // [Preparation]
    const int FIRST_ELEMENT_VALUE = 1;
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    SOURCE_ARRAY[0] = FIRST_ELEMENT_VALUE;
    QFixedArray<int>::QArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ORIGINAL_ITERATOR.MoveFirst();
    --ORIGINAL_ITERATOR;

	// [Execution]
    QFixedArray<int>::QArrayIterator iterator(ORIGINAL_ITERATOR);
    QFixedArray<int>::QArrayIterator iteratorPreviousState = iterator++;
    int currentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(currentElement == FIRST_ELEMENT_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorPostIncrement_AssertionFailsWhenIteratorIsNotValid_Test )
{/* [TODO] Thund: Uncomment when QDynamicArray exists
    // [Preparation]
    QDynamicArray<int> SOURCE_ARRAY(10, 0);
    QFixedArray<int>::QArrayIterator INVALID_ITERATOR(&SOURCE_ARRAY, 0);
    INVALID_ITERATOR.MoveLast();
    SOURCE_ARRAY.Remove(0);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        INVALID_ITERATOR++;
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);*/
}

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position.
/// </summary>
QTEST_CASE ( OperatorPostIncrement_AssertionFailsWhenIteratorAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_END(&SOURCE_ARRAY, 0);
    ITERATOR_END.MoveLast();
    ++ITERATOR_END;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ITERATOR_END++;
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
/// Checks that the iterator does not change when it already points to the end position.
/// </summary>
QTEST_CASE ( OperatorPostIncrement_IteratorDoesNotChangeWhenItAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_END(&SOURCE_ARRAY, 0);
    ITERATOR_END.MoveLast();
    ++ITERATOR_END;

	// [Execution]
    QFixedArray<int>::QArrayIterator iterator(ITERATOR_END);
    iterator++;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_END);
}

#endif

/// <summary>
/// Checks that the iterator steps backward properly and returns the previous state.
/// </summary>
QTEST_CASE ( OperatorPostDecrement_CommonIteratorStepsBackwardProperlyAndReturnsPreviousState_Test )
{
    // [Preparation]
    const int SECOND_ELEMENT_VALUE = 2;
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    SOURCE_ARRAY[1] = SECOND_ELEMENT_VALUE;
    QFixedArray<int>::QArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ORIGINAL_ITERATOR.MoveLast();

	// [Execution]
    QFixedArray<int>::QArrayIterator iterator(ORIGINAL_ITERATOR);
    QFixedArray<int>::QArrayIterator iteratorPreviousState = iterator--;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(*iterator == SECOND_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the iterator points to the last position and returns the previous state when it was pointing to the end position after the last one.
/// </summary>
QTEST_CASE ( OperatorPostDecrement_IteratorPointsToLastPositionAndReturnsPreviousStateWhenItWasPointingToLastEndPosition_Test )
{
    // [Preparation]
    const int LAST_ELEMENT_VALUE = 3;
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    SOURCE_ARRAY[2] = LAST_ELEMENT_VALUE;
    QFixedArray<int>::QArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ORIGINAL_ITERATOR.MoveLast();
    ++ORIGINAL_ITERATOR;

	// [Execution]
    QFixedArray<int>::QArrayIterator iterator(ORIGINAL_ITERATOR);
    QFixedArray<int>::QArrayIterator iteratorPreviousState = iterator--;
    int currentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(currentElement == LAST_ELEMENT_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorPostDecrement_AssertionFailsWhenIteratorIsNotValid_Test )
{/* [TODO] Thund: Uncomment when QDynamicArray exists
    // [Preparation]
    QDynamicArray<int> SOURCE_ARRAY(10, 0);
    QFixedArray<int>::QArrayIterator INVALID_ITERATOR(&SOURCE_ARRAY, 0);
    INVALID_ITERATOR.MoveLast();
    SOURCE_ARRAY.Remove(0);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        INVALID_ITERATOR--;
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);*/
}

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position before the first one.
/// </summary>
QTEST_CASE ( OperatorPostDecrement_AssertionFailsWhenIteratorAlreadyPointsToEndPositionBeforeFirst_Test )
{
    // [Preparation]
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_END(&SOURCE_ARRAY, 0);
    ITERATOR_END.MoveFirst();
    --ITERATOR_END;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ITERATOR_END--;
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
/// Checks that the iterator does not change when it already points to the end position.
/// </summary>
QTEST_CASE ( OperatorPostDecrement_IteratorDoesNotChangeWhenItAlreadyPointsToEndPositionBeforeFirst_Test )
{
    // [Preparation]
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_END(&SOURCE_ARRAY, 0);
    ITERATOR_END.MoveFirst();
    --ITERATOR_END;

	// [Execution]
    QFixedArray<int>::QArrayIterator iterator(ITERATOR_END);
    iterator--;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_END);
}

#endif

/// <summary>
/// Checks that the iterator steps forward properly and returns the current state.
/// </summary>
QTEST_CASE ( OperatorPreIncrement_CommonIteratorStepsForwardProperlyAndReturnsCurrentState_Test )
{
    // [Preparation]
    const int SECOND_ELEMENT_VALUE = 2;
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    SOURCE_ARRAY[1] = SECOND_ELEMENT_VALUE;
    QFixedArray<int>::QArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ORIGINAL_ITERATOR.MoveFirst();

	// [Execution]
    QFixedArray<int>::QArrayIterator iterator(ORIGINAL_ITERATOR);
    QFixedArray<int>::QArrayIterator iteratorCurrentState = ++iterator;

    // [Verification]
    BOOST_CHECK(iteratorCurrentState == iterator);
    BOOST_CHECK(*iterator == SECOND_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the iterator points to the first position and returns the current state when it was pointing to the end position before the first one.
/// </summary>
QTEST_CASE ( OperatorPreIncrement_IteratorPointsToFirstPositionAndReturnsCurrentStateWhenItWasPointingToPositionBeforeFirst_Test )
{
    // [Preparation]
    const int FIRST_ELEMENT_VALUE = 1;
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    SOURCE_ARRAY[0] = FIRST_ELEMENT_VALUE;
    QFixedArray<int>::QArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ORIGINAL_ITERATOR.MoveFirst();
    --ORIGINAL_ITERATOR;

	// [Execution]
    QFixedArray<int>::QArrayIterator iterator(ORIGINAL_ITERATOR);
    QFixedArray<int>::QArrayIterator iteratorCurrentState = ++iterator;
    int currentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorCurrentState == iterator);
    BOOST_CHECK(currentElement == FIRST_ELEMENT_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorPreIncrement_AssertionFailsWhenIteratorIsNotValid_Test )
{/* [TODO] Thund: Uncomment when QDynamicArray exists
    // [Preparation]
    QDynamicArray<int> SOURCE_ARRAY(10, 0);
    QFixedArray<int>::QArrayIterator INVALID_ITERATOR(&SOURCE_ARRAY, 0);
    INVALID_ITERATOR.MoveLast();
    SOURCE_ARRAY.Remove(0);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ++INVALID_ITERATOR;
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);*/
}

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position.
/// </summary>
QTEST_CASE ( OperatorPreIncrement_AssertionFailsWhenIteratorAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_END(&SOURCE_ARRAY, 0);
    ITERATOR_END.MoveLast();
    ++ITERATOR_END;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ++ITERATOR_END;
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
/// Checks that the iterator does not change when it already points to the end position.
/// </summary>
QTEST_CASE ( OperatorPreIncrement_IteratorDoesNotChangeWhenItAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_END(&SOURCE_ARRAY, 0);
    ITERATOR_END.MoveLast();
    ++ITERATOR_END;

	// [Execution]
    QFixedArray<int>::QArrayIterator iterator(ITERATOR_END);
    ++iterator;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_END);
}

#endif

/// <summary>
/// Checks that the iterator steps backward properly and returns the current state.
/// </summary>
QTEST_CASE ( OperatorPreDecrement_CommonIteratorStepsBackwardProperlyAndReturnsCurrentState_Test )
{
    // [Preparation]
    const int SECOND_ELEMENT_VALUE = 2;
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    SOURCE_ARRAY[1] = SECOND_ELEMENT_VALUE;
    QFixedArray<int>::QArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ORIGINAL_ITERATOR.MoveLast();

	// [Execution]
    QFixedArray<int>::QArrayIterator iterator(ORIGINAL_ITERATOR);
    QFixedArray<int>::QArrayIterator iteratorCurrentState = --iterator;

    // [Verification]
    BOOST_CHECK(iteratorCurrentState == iterator);
    BOOST_CHECK(*iterator == SECOND_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the iterator points to the last position and returns the current state when it was pointing to the end position after the last one.
/// </summary>
QTEST_CASE ( OperatorPreDecrement_IteratorPointsToLastPositionAndReturnsCurrentStateWhenItWasPointingToLastEndPosition_Test )
{
    // [Preparation]
    const int LAST_ELEMENT_VALUE = 3;
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    SOURCE_ARRAY[2] = LAST_ELEMENT_VALUE;
    QFixedArray<int>::QArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ORIGINAL_ITERATOR.MoveLast();
    ++ORIGINAL_ITERATOR;

	// [Execution]
    QFixedArray<int>::QArrayIterator iterator(ORIGINAL_ITERATOR);
    QFixedArray<int>::QArrayIterator iteratorCurrentState = --iterator;
    int currentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorCurrentState == iterator);
    BOOST_CHECK(currentElement == LAST_ELEMENT_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorPreDecrement_AssertionFailsWhenIteratorIsNotValid_Test )
{/* [TODO] Thund: Uncomment when QDynamicArray exists
    // [Preparation]
    QDynamicArray<int> SOURCE_ARRAY(10, 0);
    QFixedArray<int>::QArrayIterator INVALID_ITERATOR(&SOURCE_ARRAY, 0);
    INVALID_ITERATOR.MoveLast();
    SOURCE_ARRAY.Remove(0);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        --INVALID_ITERATOR;
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);*/
}

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position before the first one.
/// </summary>
QTEST_CASE ( OperatorPreDecrement_AssertionFailsWhenIteratorAlreadyPointsToEndPositionBeforeFirst_Test )
{
    // [Preparation]
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_END(&SOURCE_ARRAY, 0);
    ITERATOR_END.MoveFirst();
    --ITERATOR_END;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        --ITERATOR_END;
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
/// Checks that the iterator does not change when it already points to the end position.
/// </summary>
QTEST_CASE ( OperatorPreDecrement_IteratorDoesNotChangeWhenItAlreadyPointsToEndPositionBeforeFirst_Test )
{
    // [Preparation]
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_END(&SOURCE_ARRAY, 0);
    ITERATOR_END.MoveFirst();
    --ITERATOR_END;

	// [Execution]
    QFixedArray<int>::QArrayIterator iterator(ITERATOR_END);
    --iterator;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_END);
}

#endif

/// <summary>
/// Checks that a common iterator is copied.
/// </summary>
QTEST_CASE ( OperatorAssignment_CommonIteratorIsCorrectlyCopied_Test )
{
    // [Preparation]
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_A(&SOURCE_ARRAY, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_B(&SOURCE_ARRAY, 0);

	// [Execution]
    QFixedArray<int>::QArrayIterator iterator = ITERATOR_B;
    iterator = ITERATOR_A;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_A);
}

/// <summary>
/// Checks that input iterator is copied when resident iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorAssignment_InputIteratorIsCorrectlyCopiedWhenResidentIteratorIsNotValid_Test )
{/* [TODO] Thund: Uncomment when QDynamicArray exists
    // [Preparation]
    QDynamicArray<int> SOURCE_ARRAY(10, 0);
    QDynamicArray<int>::QArrayIterator INVALID_ITERATOR(&SOURCE_ARRAY, 0);
    INVALID_ITERATOR.MoveLast();
    SOURCE_ARRAY.Remove(0);
    QFixedArray<int>::QArrayIterator VALID_ITERATOR(&SOURCE_ARRAY, 0);

	// [Execution]
    QDynamicArray<int>::QDynamicIterator iterator = INVALID_ITERATOR;
    iterator = VALID_ITERATOR;

    // [Verification]
    BOOST_CHECK(iterator.IsValid());
    BOOST_CHECK(iterator == VALID_ITERATOR);*/
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorAssignment_AssertionFailsWhenInputIteratorIsNotValid_Test )
{/* [TODO] Thund: Uncomment when QDynamicArray exists
    // [Preparation]
    QDynamicArray<int> SOURCE_ARRAY(10, 0);
    QDynamicArray<int>::QDynamicArray INVALID_ITERATOR(&SOURCE_ARRAY, 0);
    INVALID_ITERATOR.MoveLast();
    SOURCE_ARRAY.Remove(0);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QFixedArray<int>::QArrayIterator iterator(SOURCE_ARRAY);
        iterator = INVALID_ITERATOR;
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);*/
}

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different array.
/// </summary>
QTEST_CASE ( OperatorAssignment_AssertionFailsWhenInputIteratorPointsToDifferentArray_Test )
{
    // [Preparation]
    QFixedArray<int> ARRAY_A(3, 0);
    QFixedArray<int> ARRAY_B(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QFixedArray<int>::QArrayIterator iterator(&ARRAY_B, 0);
        iterator = ITERATOR_A;
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
/// Checks that the iterator is copied when it is not valid.
/// </summary>
QTEST_CASE ( OperatorAssignment_IteratorIsCopiedWhenInputIteratorIsNotValid_Test )
{/* [TODO] Thund: Uncomment when QDynamicArray exists
    // [Preparation]
    QDynamicArray<int> SOURCE_ARRAY(10, 0);
    QDynamicArray<int>::QArrayIterator INVALID_ITERATOR(&SOURCE_ARRAY, 0);
    INVALID_ITERATOR.MoveLast();
    SOURCE_ARRAY.Remove(0);

	// [Execution]
    QDynamicArray<int>::QArrayIterator iterator(&SOURCE_ARRAY, 0);
    iterator = INVALID_ITERATOR;

    // [Verification]
    BOOST_CHECK(iterator == INVALID_ITERATOR);*/
}

/// <summary>
/// Checks that the iterator is not copied when it points to a different array.
/// </summary>
QTEST_CASE ( OperatorAssignment_IteratorDoesNotChangeIfInputIteratorPointsToDifferentArray_Test )
{
    // [Preparation]
    QFixedArray<int> ARRAY_A(3, 0);
    QFixedArray<int> ARRAY_B(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_B(&ARRAY_B, 0);

	// [Execution]
    QFixedArray<int>::QArrayIterator iterator = ITERATOR_B;
    iterator = ITERATOR_A;

    // [Verification]
    BOOST_CHECK(iterator != ITERATOR_A);
    BOOST_CHECK(iterator == ITERATOR_B);
}

#endif

/// <summary>
/// Checks that it returns True when iterators are equal.
/// </summary>
QTEST_CASE ( OperatorEquality_ReturnsTrueWhenIteratorsAreEqual_Test )
{
    // [Preparation]
    QFixedArray<int> ARRAY_A(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_B(&ARRAY_A, 0);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_A == ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when iterators are not equal.
/// </summary>
QTEST_CASE ( OperatorEquality_ReturnsFalseWhenIteratorsAreNotEqual_Test )
{
    // [Preparation]
    QFixedArray<int> ARRAY_A(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_B(&ARRAY_A, 0);
    ++ITERATOR_B;

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A == ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when either the input or the resident iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorEquality_AssertionFailsWhenIteratorsAreNotValid_Test )
{/* [TODO] Thund: Uncomment when QDynamicArray exists
    // [Preparation]
    QDynamicArray<int> SOURCE_ARRAY(10, 0);
    QDynamicArray<int>::QArrayIterator INVALID_ITERATOR(&SOURCE_ARRAY, 0);
    INVALID_ITERATOR.MoveLast();
    SOURCE_ARRAY.Remove(0);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        QFixedArray<int>::QArrayIterator iterator(&SOURCE_ARRAY, 0);
        iterator == INVALID_ITERATOR;
    }
    catch(...)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QFixedArray<int>::QArrayIterator iterator(&SOURCE_ARRAY, 0);
        INVALID_ITERATOR == iterator;
    }
    catch(...)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);*/
}

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different array.
/// </summary>
QTEST_CASE ( OperatorEquality_AssertionFailsWhenIteratorsPointToDifferentArrays_Test )
{
    // [Preparation]
    QFixedArray<int> ARRAY_A(3, 0);
    QFixedArray<int> ARRAY_B(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QFixedArray<int>::QArrayIterator iterator(&ARRAY_B, 0);
        iterator == ITERATOR_A;
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
/// Checks that it returns False when iterators point to a different array.
/// </summary>
QTEST_CASE ( OperatorEquality_ReturnsFalseWhenIteratorsPointToDifferentArrays_Test )
{
    // [Preparation]
    QFixedArray<int> ARRAY_A(3, 0);
    QFixedArray<int> ARRAY_B(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_B(&ARRAY_B, 0);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A == ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns False when iterators are equal.
/// </summary>
QTEST_CASE ( OperatorInequality_ReturnsFalseWhenIteratorsAreEqual_Test )
{
    // [Preparation]
    QFixedArray<int> ARRAY_A(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_B(&ARRAY_A, 0);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A != ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when iterators are not equal.
/// </summary>
QTEST_CASE ( OperatorInequality_ReturnsTrueWhenIteratorsAreNotEqual_Test )
{
    // [Preparation]
    QFixedArray<int> ARRAY_A(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_B(&ARRAY_A, 0);
    ++ITERATOR_B;

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_A != ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when either the input or the resident iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorInequality_AssertionFailsWhenIteratorsAreNotValid_Test )
{/* [TODO] Thund: Uncomment when QDynamicArray exists
    // [Preparation]
    QDynamicArray<int> SOURCE_ARRAY(10, 0);
    QDynamicArray<int>::QArrayIterator INVALID_ITERATOR(&SOURCE_ARRAY, 0);
    INVALID_ITERATOR.MoveLast();
    SOURCE_ARRAY.Remove(0);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        QFixedArray<int>::QArrayIterator iterator(SOURCE_ARRAY);
        iterator != INVALID_ITERATOR;
    }
    catch(...)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QFixedArray<int>::QArrayIterator iterator(SOURCE_ARRAY);
        INVALID_ITERATOR != iterator;
    }
    catch(...)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);*/
}

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different array.
/// </summary>
QTEST_CASE ( OperatorInequality_AssertionFailsWhenIteratorsPointToDifferentArrays_Test )
{
    // [Preparation]
    QFixedArray<int> ARRAY_A(3, 0);
    QFixedArray<int> ARRAY_B(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QFixedArray<int>::QArrayIterator iterator(&ARRAY_B, 0);
        iterator != ITERATOR_A;
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
/// Checks that it returns True when iterators point to a different array.
/// </summary>
QTEST_CASE ( OperatorInequality_ReturnsTrueWhenIteratorsPointToDifferentArrays_Test )
{
    // [Preparation]
    QFixedArray<int> ARRAY_A(3, 0);
    QFixedArray<int> ARRAY_B(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_B(&ARRAY_B, 0);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_A != ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when the resident iterator is greater than the input iterator.
/// </summary>
QTEST_CASE ( OperatorGreaterThan_ReturnsTrueWhenResidentIteratorIsGreaterThanInputIterator_Test )
{
    // [Preparation]
    QFixedArray<int> ARRAY_A(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_B(&ARRAY_A, 0);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B > ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident iterator is not greater than the input iterator.
/// </summary>
QTEST_CASE ( OperatorGreaterThan_ReturnsFalseWhenResidentIteratorIsNotGreaterThanInputIterator_Test )
{
    // [Preparation]
    QFixedArray<int> ARRAY_A(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_B(&ARRAY_A, 0);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A > ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when either the input or the resident iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorGreaterThan_AssertionFailsWhenIteratorsAreNotValid_Test )
{/* [TODO] Thund: Uncomment when QDynamicArray exists
    // [Preparation]
    QDynamicArray<int> SOURCE_ARRAY(3, 0);
    QDynamicArray<int>::QArrayIterator INVALID_ITERATOR(&SOURCE_ARRAY, 0);
    INVALID_ITERATOR.MoveLast();
    SOURCE_ARRAY.Remove(0);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        QFixedArray<int>::QArrayIterator iterator(&SOURCE_ARRAY, 0);
        iterator > INVALID_ITERATOR;
    }
    catch(...)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QFixedArray<int>::QArrayIterator iterator(&SOURCE_ARRAY, 0);
        INVALID_ITERATOR > iterator;
    }
    catch(...)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);*/
}

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different array.
/// </summary>
QTEST_CASE ( OperatorGreaterThan_AssertionFailsWhenIteratorsPointToDifferentArrays_Test )
{
    // [Preparation]
    QFixedArray<int> ARRAY_A(3, 0);
    QFixedArray<int> ARRAY_B(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QFixedArray<int>::QArrayIterator iterator(&ARRAY_B, 0);
        iterator > ITERATOR_A;
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
/// Checks that it returns False when iterators point to a different array.
/// </summary>
QTEST_CASE ( OperatorGreaterThan_ReturnsFalseWhenIteratorsPointToDifferentArrays_Test )
{
    // [Preparation]
    QFixedArray<int> ARRAY_A(3, 0);
    QFixedArray<int> ARRAY_B(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);
    ++ITERATOR_A;
    QFixedArray<int>::QArrayIterator ITERATOR_B(&ARRAY_B, 0);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A > ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when the resident iterator is lower than the input iterator.
/// </summary>
QTEST_CASE ( OperatorLowerThan_ReturnsTrueWhenResidentIteratorIsLowerThanInputIterator_Test )
{
    // [Preparation]
    QFixedArray<int> ARRAY_A(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_B(&ARRAY_A, 0);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_A < ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident iterator is not lower than the input iterator.
/// </summary>
QTEST_CASE ( OperatorLowerThan_ReturnsFalseWhenResidentIteratorIsNotLowerThanInputIterator_Test )
{
    // [Preparation]
    QFixedArray<int> ARRAY_A(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_B(&ARRAY_A, 0);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_B < ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when either the input or the resident iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorLowerThan_AssertionFailsWhenIteratorsAreNotValid_Test )
{/* [TODO] Thund: Uncomment when QDynamicArray exists
    // [Preparation]
    QDynamicArray<int> SOURCE_ARRAY(3, 0);
    QDynamicArray<int>::QArrayIterator INVALID_ITERATOR(SOURCE_ARRAY);
    INVALID_ITERATOR.MoveLast();
    SOURCE_ARRAY.Remove(0);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        QFixedArray<int>::QArrayIterator iterator(SOURCE_ARRAY);
        iterator < INVALID_ITERATOR;
    }
    catch(...)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QFixedArray<int>::QArrayIterator iterator(SOURCE_ARRAY);
        INVALID_ITERATOR < iterator;
    }
    catch(...)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);*/
}

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different array.
/// </summary>
QTEST_CASE ( OperatorLowerThan_AssertionFailsWhenIteratorsPointToDifferentArrays_Test )
{
    // [Preparation]
    QFixedArray<int> ARRAY_A(3, 0);
    QFixedArray<int> ARRAY_B(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);
    ++ITERATOR_A;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QFixedArray<int>::QArrayIterator iterator(&ARRAY_B, 0);
        iterator < ITERATOR_A;
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
/// Checks that it returns False when iterators point to a different array.
/// </summary>
QTEST_CASE ( OperatorLowerThan_ReturnsFalseWhenIteratorsPointToDifferentArrays_Test )
{
    // [Preparation]
    QFixedArray<int> ARRAY_A(3, 0);
    QFixedArray<int> ARRAY_B(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_B(&ARRAY_B, 0);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A < ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when the resident iterator is greater than the input iterator.
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsTrueWhenResidentIteratorIsGreaterThanInputIterator_Test )
{
    // [Preparation]
    QFixedArray<int> ARRAY_A(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_B(&ARRAY_A, 0);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B >= ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the resident iterator is equal to the input iterator.
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsTrueWhenResidentIteratorEqualsInputIterator_Test )
{
    // [Preparation]
    QFixedArray<int> ARRAY_A(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_B(&ARRAY_A, 0);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B >= ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident iterator is neither greater than nor equals to the input iterator.
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsFalseWhenResidentIteratorIsNotGreaterThanAndDoNotEqualsInputIterator_Test )
{
    // [Preparation]
    QFixedArray<int> ARRAY_A(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_B(&ARRAY_A, 0);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A >= ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when either the input or the resident iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_AssertionFailsWhenIteratorsAreNotValid_Test )
{/* [TODO] Thund: Uncomment when QDynamicArray exists
    // [Preparation]
    QDynamicArray<int> SOURCE_ARRAY(3, 0);
    QDynamicArray<int>::QArrayIterator INVALID_ITERATOR(&SOURCE_ARRAY, 0);
    INVALID_ITERATOR.MoveLast();
    SOURCE_ARRAY.Remove(0);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        QFixedArray<int>::QArrayIterator iterator(SOURCE_ARRAY);
        iterator >= INVALID_ITERATOR;
    }
    catch(...)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QFixedArray<int>::QArrayIterator iterator(SOURCE_ARRAY);
        INVALID_ITERATOR >= iterator;
    }
    catch(...)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);*/
}

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different array.
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_AssertionFailsWhenIteratorsPointToDifferentArrays_Test )
{
    // [Preparation]
    QFixedArray<int> ARRAY_A(3, 0);
    QFixedArray<int> ARRAY_B(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QFixedArray<int>::QArrayIterator iterator(&ARRAY_B, 0);
        iterator >= ITERATOR_A;
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
/// Checks that it returns False when iterators point to a different array.
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsFalseWhenIteratorsPointToDifferentArrays_Test )
{
    // [Preparation]
    QFixedArray<int> ARRAY_A(3, 0);
    QFixedArray<int> ARRAY_B(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);
    ++ITERATOR_A;
    QFixedArray<int>::QArrayIterator ITERATOR_B(&ARRAY_B, 0);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A >= ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when the resident iterator is lower than the input iterator.
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_ReturnsTrueWhenResidentIteratorIsLowerThanInputIterator_Test )
{
    // [Preparation]
    QFixedArray<int> ARRAY_A(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_B(&ARRAY_A, 0);
    ++ITERATOR_A;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B <= ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the resident iterator is equal to the input iterator.
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_ReturnsTrueWhenResidentIteratorEqualsInputIterator_Test )
{
    // [Preparation]
    QFixedArray<int> ARRAY_A(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_B(&ARRAY_A, 0);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B <= ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident iterator is neither greater than nor equals to the input iterator.
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_ReturnsFalseWhenResidentIteratorIsNotLowerThanAndDoNotEqualsInputIterator_Test )
{
    // [Preparation]
    QFixedArray<int> ARRAY_A(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_B(&ARRAY_A, 0);
    ++ITERATOR_A;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A <= ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when either the input or the resident iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_AssertionFailsWhenIteratorsAreNotValid_Test )
{/* [TODO] Thund: Uncomment when QDynamicArray exists
    // [Preparation]
    QDynamicArray<int> SOURCE_ARRAY(3, 0);
    QDynamicArray<int>::QArrayIterator INVALID_ITERATOR(&SOURCE_ARRAY, 0);
    INVALID_ITERATOR.MoveLast();
    SOURCE_ARRAY.Remove(0);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        QFixedArray<int>::QArrayIterator iterator(&SOURCE_ARRAY, 0);
        iterator <= INVALID_ITERATOR;
    }
    catch(...)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QFixedArray<int>::QArrayIterator iterator(&SOURCE_ARRAY, 0);
        INVALID_ITERATOR <= iterator;
    }
    catch(...)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);*/
}

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different array.
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_AssertionFailsWhenIteratorsPointToDifferentArrays_Test )
{
    // [Preparation]
    QFixedArray<int> ARRAY_A(3, 0);
    QFixedArray<int> ARRAY_B(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QFixedArray<int>::QArrayIterator iterator(&ARRAY_B, 0);
        iterator <= ITERATOR_A;
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
/// Checks that it returns False when iterators point to a different array.
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_ReturnsFalseWhenIteratorsPointToDifferentArrays_Test )
{
    // [Preparation]
    QFixedArray<int> ARRAY_A(3, 0);
    QFixedArray<int> ARRAY_B(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_B(&ARRAY_B, 0);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A <= ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when the iterator points to the position before the first.
/// </summary>
QTEST_CASE ( IsEnd1_ReturnsTrueWhenIteratorPointsToPositionBeforeFirst_Test )
{
    // [Preparation]
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR.MoveFirst();
    ITERATOR--;

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR.IsEnd();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the iterator points to the position after the last.
/// </summary>
QTEST_CASE ( IsEnd1_ReturnsTrueWhenIteratorPointsToPositionAfterLast_Test )
{
    // [Preparation]
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR.MoveLast();
    ++ITERATOR;

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR.IsEnd();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the iterator does not point to an end position.
/// </summary>
QTEST_CASE ( IsEnd1_ReturnsFalseWhenIteratorDoesNotPointToEndPosition_Test )
{
    // [Preparation]
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR.MoveLast();

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR.IsEnd();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
QTEST_CASE ( IsEnd1_AssertionFailsWhenIteratorIsNotValid_Test )
{/* [TODO] Thund: Uncomment when QDynamicArray exists
    // [Preparation]
    QDynamicArray<int> SOURCE_ARRAY(3, 0);
    QDynamicArray<int>::QArrayIterator INVALID_ITERATOR(&SOURCE_ARRAY, 0);
    INVALID_ITERATOR.MoveLast();
    SOURCE_ARRAY.Remove(0);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        INVALID_ITERATOR.IsEnd();
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);*/
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns False when the iterator is not valid.
/// </summary>
QTEST_CASE ( IsEnd1_ReturnsFalseWhenIteratorIsNotValid_Test )
{/* [TODO] Thund: Uncomment when QDynamicArray exists
    // [Preparation]
    QDynamicArray<int> SOURCE_ARRAY(3, 0);
    QDynamicArray<int>::QArrayIterator INVALID_ITERATOR(SOURCE_ARRAY);
    INVALID_ITERATOR.MoveLast();
    SOURCE_ARRAY;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = INVALID_ITERATOR.IsEnd();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);*/
}

#endif

/// <summary>
/// Checks that it returns True when the iterator points to the position before the first.
/// </summary>
QTEST_CASE ( IsEnd2_ReturnsTrueWhenIteratorPointsToPositionBeforeFirst_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR.MoveFirst();
    ITERATOR--;

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR.IsEnd(EQIterationDirection::E_Backward);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the iterator points to the position after the last.
/// </summary>
QTEST_CASE ( IsEnd2_ReturnsTrueWhenIteratorPointsToPositionAfterLast_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR.MoveLast();
    ++ITERATOR;

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR.IsEnd(EQIterationDirection::E_Forward);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the iterator does not point to an end position.
/// </summary>
QTEST_CASE ( IsEnd2_ReturnsFalseWhenIteratorDoesNotPointToEndPosition_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR.MoveLast();

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR.IsEnd(EQIterationDirection::E_Backward);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
QTEST_CASE ( IsEnd2_AssertionFailsWhenIteratorIsNotValid_Test )
{/* [TODO] Thund: Uncomment when QDynamicArray exists
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    QDynamicArray<int> SOURCE_ARRAY(3, 0);
    QDynamicArray<int>::QArrayIterator INVALID_ITERATOR(&SOURCE_ARRAY, 0);
    INVALID_ITERATOR.MoveLast();
    SOURCE_ARRAY.Remove(0);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        INVALID_ITERATOR.IsEnd(EQIterationDirection::E_Backward);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);*/
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns False when the iterator is not valid.
/// </summary>
QTEST_CASE ( IsEnd2_ReturnsFalseWhenIteratorIsNotValid_Test )
{/* [TODO] Thund: Uncomment when QDynamicArray exists
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    QDynamicArray<int> SOURCE_ARRAY(3, 0);
    QDynamicArray<int>::QArrayIterator INVALID_ITERATOR(SOURCE_ARRAY);
    INVALID_ITERATOR.MoveLast();
    SOURCE_ARRAY;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = INVALID_ITERATOR.IsEnd(EQIterationDirection::E_Backward);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);*/
}

#endif

/// <summary>
/// Checks that the iterator points to the first position when the array is not empty.
/// </summary>
QTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenArrayIsNotEmpty_Test )
{
    // [Preparation]
    QFixedArray<int> SOURCE_ARRAY(10, 0);
    QFixedArray<int>::QArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ++ORIGINAL_ITERATOR;
    ++ORIGINAL_ITERATOR;
    ++ORIGINAL_ITERATOR;
    QFixedArray<int>::QArrayIterator ITERATOR_FIRST(&SOURCE_ARRAY, 0);

	// [Execution]
    QFixedArray<int>::QArrayIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveFirst();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_FIRST);
}

/// <summary>
/// Checks that the iterator points to the first position even when it was not valid.
/// </summary>
QTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenArrayIsNotEmptyAndIteratorWasNotValid_Test )
{/* [TODO] Thund: Uncomment when QDynamicArray exists
    // [Preparation]
    QDynamicArray<int> SOURCE_ARRAY(3, 0);
    QDynamicArray<int>::QArrayIterator ITERATOR_FIRST(SOURCE_ARRAY);
    QDynamicArray<int>::QArrayIterator INVALID_ITERATOR(SOURCE_ARRAY);
    INVALID_ITERATOR.MoveLast();
    SOURCE_ARRAY.Remove(0);

	// [Execution]
    QFixedArray<int>::QArrayIterator iterator(INVALID_ITERATOR);
    iterator.MoveFirst();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_FIRST);*/
}

/// <summary>
/// Checks that the iterator points to the first position even when it was pointing to the position before the first.
/// </summary>
QTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenArrayIsNotEmptyAndIteratorWasPointingToPositionBeforeFirst_Test )
{
    // [Preparation]
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    QFixedArray<int>::QArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ORIGINAL_ITERATOR--;

    QFixedArray<int>::QArrayIterator ITERATOR_FIRST(&SOURCE_ARRAY, 0);

	// [Execution]
    QFixedArray<int>::QArrayIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveFirst();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_FIRST);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the array is empty.
/// </summary>
QTEST_CASE ( MoveFirst_AssertionFailsWhenArrayIsEmpty_Test )
{/* [TODO] Thund: Uncomment when QDynamicArray exists
    // [Preparation]
    QDynamicArray<int> EMPTY_ARRAY;
    QFixedArray<int>::QArrayIterator ITERATOR(&EMPTY_ARRAY);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ITERATOR.MoveFirst();
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);*/
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator points to the end position when the array is empty.
/// </summary>
QTEST_CASE ( MoveFirst_IteratorPointsToEndPositionWhenArrayIsEmpty_Test )
{/* [TODO] Thund: Uncomment when QDynamicArray exists
    // [Preparation]
    QDynamicArray<int> EMPTY_ARRAY;
    QFixedArray<int>::QArrayIterator END_ITERATOR(&EMPTY_ARRAY);
    END_ITERATOR.MoveLast();
    ++END_ITERATOR;
    QFixedArray<int>::QArrayIterator ITERATOR(&EMPTY_ARRAY);

	// [Execution]
    ITERATOR.MoveFirst();

    // [Verification]
    BOOST_CHECK(ITERATOR == END_ITERATOR);*/
}

#endif

/// <summary>
/// Checks that the iterator points to the last position when the array is not empty.
/// </summary>
QTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenArrayIsNotEmpty_Test )
{
    // [Preparation]
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    QFixedArray<int>::QArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    QFixedArray<int>::QArrayIterator ITERATOR_LAST(&SOURCE_ARRAY, 0);
    ++ITERATOR_LAST;
    ++ITERATOR_LAST;

	// [Execution]
    QFixedArray<int>::QArrayIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveLast();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_LAST);
}

/// <summary>
/// Checks that the iterator points to the last position even when it was not valid.
/// </summary>
QTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenArrayIsNotEmptyAndIteratorWasNotValid_Test )
{/* [TODO] Thund: Uncomment when QDynamicArray exists
    // [Preparation]
    QDynamicArray<int> SOURCE_ARRAY(3, 0);
    QDynamicArray<int>::QArrayIterator ITERATOR_LAST(&SOURCE_ARRAY, 0);
    ++ITERATOR_LAST;
    ++ITERATOR_LAST;
    QDynamicArray<int>::QArrayIterator INVALID_ITERATOR(&SOURCE_ARRAY, 0);
    ++INVALID_ITERATOR;
    ++INVALID_ITERATOR;
    SOURCE_ARRAY.Remove(0);

	// [Execution]
    QFixedArray<int>::QArrayIterator iterator(INVALID_ITERATOR);
    iterator.MoveLast();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_LAST);*/
}

/// <summary>
/// Checks that the iterator points to the last position even when it was pointing to the position before the first.
/// </summary>
QTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenArrayIsNotEmptyAndIteratorWasPointingToPositionBeforeFirst_Test )
{
    // [Preparation]
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    QFixedArray<int>::QArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    --ORIGINAL_ITERATOR;

    QFixedArray<int>::QArrayIterator ITERATOR_LAST(&SOURCE_ARRAY, 0);
    ++ITERATOR_LAST;
    ++ITERATOR_LAST;

	// [Execution]
    QFixedArray<int>::QArrayIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveLast();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_LAST);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the array is empty.
/// </summary>
QTEST_CASE ( MoveLast_AssertionFailsWhenArrayIsEmpty_Test )
{/* [TODO] Thund: Uncomment when QDynamicArray exists
    // [Preparation]
    QDynamicArray<int> EMPTY_ARRAY;
    QDynamicArray<int>::QArrayIterator ITERATOR(&EMPTY_ARRAY);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ITERATOR.MoveLast();
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);*/
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator points to the end position when the array is empty.
/// </summary>
QTEST_CASE ( MoveLast_IteratorPointsToEndPositionWhenArrayIsEmpty_Test )
{/* [TODO] Thund: Uncomment when QDynamicArray exists
    // [Preparation]
    QDynamicArray<int> EMPTY_ARRAY;
    QDynamicArray<int>::QArrayIterator END_ITERATOR(&EMPTY_ARRAY);
    END_ITERATOR.MoveLast();
    ++END_ITERATOR;
    QFixedArray<int>::QArrayIterator ITERATOR(&EMPTY_ARRAY);

	// [Execution]
    ITERATOR.MoveLast();

    // [Verification]
    BOOST_CHECK(ITERATOR == END_ITERATOR);*/
}

#endif


/// <summary>
/// Checks that it returns True when iterator points to a common position.
/// </summary>
QTEST_CASE ( IsValid_ReturnsTrueWhenIteratorPointsToCommonPosition_Test )
{
    // [Preparation]
    QFixedArray<int> SOURCE_ARRAY(3, 0);
    QFixedArray<int>::QArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR.IsValid();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the iterator points to an out of bounds position.
/// </summary>
QTEST_CASE ( IsValid_ReturnsFalseWhenIteratorPointsToOutOfBoundPosition_Test )
{/* [TODO] Thund: Uncomment when QDynamicArray exists
    // [Preparation]
    QDynamicArray<int> SOURCE_ARRAY(3, 0);
    QDynamicArray<int>::QArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR.MoveLast();
    SOURCE_ARRAY.Remove(0);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR.IsValid();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);*/
}

// End - Test Suite: QArrayIterator
QTEST_SUITE_END()
