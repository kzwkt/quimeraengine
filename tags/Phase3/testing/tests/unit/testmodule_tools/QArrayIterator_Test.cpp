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

#include "QArrayFixed.h"
#include "QArrayDynamic.h"

#include "EQIterationDirection.h"
#include "QAssertException.h"

using Kinesis::QuimeraEngine::Common::Exceptions::QAssertException;
using Kinesis::QuimeraEngine::Tools::Containers::QArrayFixed;
using Kinesis::QuimeraEngine::Tools::Containers::QArrayDynamic;

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
    QArrayFixed<int> SOURCE_ARRAY(3, 0);
    const unsigned int POSITION = 1;
    QArrayFixed<int>::QArrayIterator EXPECTED_ITERATOR(&SOURCE_ARRAY, 0);
    EXPECTED_ITERATOR.MoveFirst();
    ++EXPECTED_ITERATOR;

	// [Execution]
    QArrayFixed<int>::QArrayIterator iterator(&SOURCE_ARRAY, POSITION);
    
    // [Verification]
    BOOST_CHECK(iterator == EXPECTED_ITERATOR);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator points to the end position (forward iteration) when using an empty array.
/// </summary>
QTEST_CASE ( Constructor_IteratorPointsToForwardEndPositionWhenUsingEmptyArray_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const QArrayDynamic<int> SOURCE_ARRAY(1U);
    const bool IS_END = true;

	// [Execution]
    QArrayDynamic<int>::QArrayIterator iterator(&SOURCE_ARRAY, 0);

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
    QArrayFixed<int> SOURCE_ARRAY(3, 0);
    const int EXPECTED_VALUE = 1;
    SOURCE_ARRAY[1] = EXPECTED_VALUE;
    QArrayFixed<int>::QArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR++;

	// [Execution]
    int nValue = *ITERATOR;

    // [Verification]
    BOOST_CHECK_EQUAL(nValue, EXPECTED_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is pointing to the end position (forward iteration).
/// </summary>
QTEST_CASE ( OperatorIndirection_AssertionFailsWhenIteratorPointsToForwardEndPosition_Test )
{
    // [Preparation]
    QArrayFixed<int> SOURCE_ARRAY(3, 0);
    QArrayFixed<int>::QArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR.MoveLast();
    ++ITERATOR;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        *ITERATOR;
    }
    catch(const QAssertException&)
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
    QArrayFixed<int> SOURCE_ARRAY(3, 0);
    QArrayFixed<int>::QArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR.MoveFirst();
    --ITERATOR;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        *ITERATOR;
    }
    catch(const QAssertException&)
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
    QArrayFixed<TestStructure> SOURCE_ARRAY(3, TestStructure(0));
    const int EXPECTED_VALUE = 1;
    SOURCE_ARRAY[1] = TestStructure(EXPECTED_VALUE);
    QArrayFixed<TestStructure>::QArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR++;

	// [Execution]
    int nValue = ITERATOR->m_nField;

    // [Verification]
    BOOST_CHECK_EQUAL(nValue, EXPECTED_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is pointing to the end position (forward iteration).
/// </summary>
QTEST_CASE ( OperatorDereferencing_AssertionFailsWhenIteratorPointsToForwardEndPosition_Test )
{
    // [Preparation]
    QArrayFixed<TestStructure> SOURCE_ARRAY(3, TestStructure(0));
    QArrayFixed<TestStructure>::QArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR.MoveLast();
    ++ITERATOR;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ITERATOR->m_nField;
    }
    catch(const QAssertException&)
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
    QArrayFixed<TestStructure> SOURCE_ARRAY(3, TestStructure(0));
    QArrayFixed<TestStructure>::QArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR.MoveFirst();
    --ITERATOR;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ITERATOR->m_nField;
    }
    catch(const QAssertException&)
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
    QArrayFixed<int> SOURCE_ARRAY(3, 0);
    SOURCE_ARRAY[1] = SECOND_ELEMENT_VALUE;
    QArrayFixed<int>::QArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ORIGINAL_ITERATOR.MoveFirst();

	// [Execution]
    QArrayFixed<int>::QArrayIterator iterator(ORIGINAL_ITERATOR);
    QArrayFixed<int>::QArrayIterator iteratorPreviousState = iterator++;

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
    QArrayFixed<int> SOURCE_ARRAY(3, 0);
    SOURCE_ARRAY[0] = FIRST_ELEMENT_VALUE;
    QArrayFixed<int>::QArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ORIGINAL_ITERATOR.MoveFirst();
    --ORIGINAL_ITERATOR;

	// [Execution]
    QArrayFixed<int>::QArrayIterator iterator(ORIGINAL_ITERATOR);
    QArrayFixed<int>::QArrayIterator iteratorPreviousState = iterator++;
    int currentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(currentElement == FIRST_ELEMENT_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position.
/// </summary>
QTEST_CASE ( OperatorPostIncrement_AssertionFailsWhenIteratorAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    QArrayFixed<int> SOURCE_ARRAY(3, 0);
    QArrayFixed<int>::QArrayIterator ITERATOR_END(&SOURCE_ARRAY, 0);
    ITERATOR_END.MoveLast();
    ++ITERATOR_END;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ITERATOR_END++;
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator changes when it already points to the end position.
/// </summary>
QTEST_CASE ( OperatorPostIncrement_IteratorChangesWhenItAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    QArrayDynamic<int> SOURCE_ARRAY(3);
    QArrayFixed<int>::QArrayIterator ITERATOR_END(&SOURCE_ARRAY, 0);

	// [Execution]
    QArrayFixed<int>::QArrayIterator iterator(ITERATOR_END);
    iterator++;

    // [Verification]
    BOOST_CHECK(iterator != ITERATOR_END);
}

#endif

/// <summary>
/// Checks that the iterator steps backward properly and returns the previous state.
/// </summary>
QTEST_CASE ( OperatorPostDecrement_CommonIteratorStepsBackwardProperlyAndReturnsPreviousState_Test )
{
    // [Preparation]
    const int SECOND_ELEMENT_VALUE = 2;
    QArrayFixed<int> SOURCE_ARRAY(3, 0);
    SOURCE_ARRAY[1] = SECOND_ELEMENT_VALUE;
    QArrayFixed<int>::QArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ORIGINAL_ITERATOR.MoveLast();

	// [Execution]
    QArrayFixed<int>::QArrayIterator iterator(ORIGINAL_ITERATOR);
    QArrayFixed<int>::QArrayIterator iteratorPreviousState = iterator--;

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
    QArrayFixed<int> SOURCE_ARRAY(3, 0);
    SOURCE_ARRAY[2] = LAST_ELEMENT_VALUE;
    QArrayFixed<int>::QArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ORIGINAL_ITERATOR.MoveLast();
    ++ORIGINAL_ITERATOR;

	// [Execution]
    QArrayFixed<int>::QArrayIterator iterator(ORIGINAL_ITERATOR);
    QArrayFixed<int>::QArrayIterator iteratorPreviousState = iterator--;
    int currentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(currentElement == LAST_ELEMENT_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position before the first one.
/// </summary>
QTEST_CASE ( OperatorPostDecrement_AssertionFailsWhenIteratorAlreadyPointsToEndPositionBeforeFirst_Test )
{
    // [Preparation]
    QArrayFixed<int> SOURCE_ARRAY(3, 0);
    QArrayFixed<int>::QArrayIterator ITERATOR_END(&SOURCE_ARRAY, 0);
    ITERATOR_END.MoveFirst();
    --ITERATOR_END;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ITERATOR_END--;
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator changes when it already points to the end position.
/// </summary>
QTEST_CASE ( OperatorPostDecrement_IteratorChangesWhenItAlreadyPointsToEndPositionBeforeFirst_Test )
{
    // [Preparation]
    QArrayFixed<int> SOURCE_ARRAY(1, 0);
    QArrayFixed<int>::QArrayIterator ITERATOR_END(&SOURCE_ARRAY, 0);
    --ITERATOR_END;

	// [Execution]
    QArrayFixed<int>::QArrayIterator iterator(ITERATOR_END);
    iterator--;

    // [Verification]
    BOOST_CHECK(iterator != ITERATOR_END);
}

#endif

/// <summary>
/// Checks that the iterator steps forward properly and returns the current state.
/// </summary>
QTEST_CASE ( OperatorPreIncrement_CommonIteratorStepsForwardProperlyAndReturnsCurrentState_Test )
{
    // [Preparation]
    const int SECOND_ELEMENT_VALUE = 2;
    QArrayFixed<int> SOURCE_ARRAY(3, 0);
    SOURCE_ARRAY[1] = SECOND_ELEMENT_VALUE;
    QArrayFixed<int>::QArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ORIGINAL_ITERATOR.MoveFirst();

	// [Execution]
    QArrayFixed<int>::QArrayIterator iterator(ORIGINAL_ITERATOR);
    QArrayFixed<int>::QArrayIterator iteratorCurrentState = ++iterator;

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
    QArrayFixed<int> SOURCE_ARRAY(3, 0);
    SOURCE_ARRAY[0] = FIRST_ELEMENT_VALUE;
    QArrayFixed<int>::QArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ORIGINAL_ITERATOR.MoveFirst();
    --ORIGINAL_ITERATOR;

	// [Execution]
    QArrayFixed<int>::QArrayIterator iterator(ORIGINAL_ITERATOR);
    QArrayFixed<int>::QArrayIterator iteratorCurrentState = ++iterator;
    int currentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorCurrentState == iterator);
    BOOST_CHECK(currentElement == FIRST_ELEMENT_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position.
/// </summary>
QTEST_CASE ( OperatorPreIncrement_AssertionFailsWhenIteratorAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    QArrayFixed<int> SOURCE_ARRAY(3, 0);
    QArrayFixed<int>::QArrayIterator ITERATOR_END(&SOURCE_ARRAY, 0);
    ITERATOR_END.MoveLast();
    ++ITERATOR_END;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ++ITERATOR_END;
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator changes when it already points to the end position.
/// </summary>
QTEST_CASE ( OperatorPreIncrement_IteratorChangesWhenItAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    QArrayDynamic<int> SOURCE_ARRAY(3);
    QArrayFixed<int>::QArrayIterator ITERATOR_END(&SOURCE_ARRAY, 0);

	// [Execution]
    QArrayFixed<int>::QArrayIterator iterator(ITERATOR_END);
    ++iterator;

    // [Verification]
    BOOST_CHECK(iterator != ITERATOR_END);
}

#endif

/// <summary>
/// Checks that the iterator steps backward properly and returns the current state.
/// </summary>
QTEST_CASE ( OperatorPreDecrement_CommonIteratorStepsBackwardProperlyAndReturnsCurrentState_Test )
{
    // [Preparation]
    const int SECOND_ELEMENT_VALUE = 2;
    QArrayFixed<int> SOURCE_ARRAY(3, 0);
    SOURCE_ARRAY[1] = SECOND_ELEMENT_VALUE;
    QArrayFixed<int>::QArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ORIGINAL_ITERATOR.MoveLast();

	// [Execution]
    QArrayFixed<int>::QArrayIterator iterator(ORIGINAL_ITERATOR);
    QArrayFixed<int>::QArrayIterator iteratorCurrentState = --iterator;

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
    QArrayFixed<int> SOURCE_ARRAY(3, 0);
    SOURCE_ARRAY[2] = LAST_ELEMENT_VALUE;
    QArrayFixed<int>::QArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ORIGINAL_ITERATOR.MoveLast();
    ++ORIGINAL_ITERATOR;

	// [Execution]
    QArrayFixed<int>::QArrayIterator iterator(ORIGINAL_ITERATOR);
    QArrayFixed<int>::QArrayIterator iteratorCurrentState = --iterator;
    int currentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorCurrentState == iterator);
    BOOST_CHECK(currentElement == LAST_ELEMENT_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position before the first one.
/// </summary>
QTEST_CASE ( OperatorPreDecrement_AssertionFailsWhenIteratorAlreadyPointsToEndPositionBeforeFirst_Test )
{
    // [Preparation]
    QArrayFixed<int> SOURCE_ARRAY(3, 0);
    QArrayFixed<int>::QArrayIterator ITERATOR_END(&SOURCE_ARRAY, 0);
    ITERATOR_END.MoveFirst();
    --ITERATOR_END;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        --ITERATOR_END;
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator changes when it already points to the end position.
/// </summary>
QTEST_CASE ( OperatorPreDecrement_IteratorChangesWhenItAlreadyPointsToEndPositionBeforeFirst_Test )
{
    // [Preparation]
    QArrayFixed<int> SOURCE_ARRAY(3, 0);
    QArrayFixed<int>::QArrayIterator ITERATOR_END(&SOURCE_ARRAY, 0);
    --ITERATOR_END;

	// [Execution]
    QArrayFixed<int>::QArrayIterator iterator(ITERATOR_END);
    --iterator;

    // [Verification]
    BOOST_CHECK(iterator != ITERATOR_END);
}

#endif

/// <summary>
/// Checks that a common iterator is copied.
/// </summary>
QTEST_CASE ( OperatorAssignment_CommonIteratorIsCorrectlyCopied_Test )
{
    // [Preparation]
    QArrayFixed<int> SOURCE_ARRAY(3, 0);
    QArrayFixed<int>::QArrayIterator ITERATOR_A(&SOURCE_ARRAY, 0);
    QArrayFixed<int>::QArrayIterator ITERATOR_B(&SOURCE_ARRAY, 0);

	// [Execution]
    QArrayFixed<int>::QArrayIterator iterator = ITERATOR_B;
    iterator = ITERATOR_A;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_A);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different array.
/// </summary>
QTEST_CASE ( OperatorAssignment_AssertionFailsWhenInputIteratorPointsToDifferentArray_Test )
{
    // [Preparation]
    QArrayFixed<int> ARRAY_A(3, 0);
    QArrayFixed<int> ARRAY_B(3, 0);
    QArrayFixed<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QArrayFixed<int>::QArrayIterator iterator(&ARRAY_B, 0);
        iterator = ITERATOR_A;
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator is not copied when it points to a different array.
/// </summary>
QTEST_CASE ( OperatorAssignment_IteratorDoesNotChangeIfInputIteratorPointsToDifferentArray_Test )
{
    // [Preparation]
    QArrayFixed<int> ARRAY_A(3, 0);
    QArrayFixed<int> ARRAY_B(3, 0);
    QArrayFixed<int>::QArrayIterator ITERATOR_A(&ARRAY_A, 0);
    QArrayFixed<int>::QArrayIterator ITERATOR_B(&ARRAY_B, 0);

	// [Execution]
    QArrayFixed<int>::QArrayIterator iterator = ITERATOR_B;
    iterator = ITERATOR_A;

    // [Verification]
    BOOST_CHECK(iterator != ITERATOR_A);
    BOOST_CHECK(iterator == ITERATOR_B);
}

#endif

/// <summary>
/// Checks that the iterator points to the first position when the array is not empty.
/// </summary>
QTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenArrayIsNotEmpty_Test )
{
    // [Preparation]
    QArrayFixed<int> SOURCE_ARRAY(10, 0);
    QArrayFixed<int>::QArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ++ORIGINAL_ITERATOR;
    ++ORIGINAL_ITERATOR;
    ++ORIGINAL_ITERATOR;
    QArrayFixed<int>::QArrayIterator ITERATOR_FIRST(&SOURCE_ARRAY, 0);

	// [Execution]
    QArrayFixed<int>::QArrayIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveFirst();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_FIRST);
}

/// <summary>
/// Checks that the iterator points to the first position even when it was pointing to the position before the first.
/// </summary>
QTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenArrayIsNotEmptyAndIteratorWasPointingToPositionBeforeFirst_Test )
{
    // [Preparation]
    QArrayFixed<int> SOURCE_ARRAY(3, 0);
    QArrayFixed<int>::QArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ORIGINAL_ITERATOR--;

    QArrayFixed<int>::QArrayIterator ITERATOR_FIRST(&SOURCE_ARRAY, 0);

	// [Execution]
    QArrayFixed<int>::QArrayIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveFirst();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_FIRST);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the array is empty.
/// </summary>
QTEST_CASE ( MoveFirst_AssertionFailsWhenArrayIsEmpty_Test )
{
    // [Preparation]
    QArrayDynamic<int> EMPTY_ARRAY;
    EMPTY_ARRAY.Add(0);
    QArrayFixed<int>::QArrayIterator ITERATOR(&EMPTY_ARRAY, 0);
    EMPTY_ARRAY.Remove(0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ITERATOR.MoveFirst();
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator points to the end position when the array is empty.
/// </summary>
QTEST_CASE ( MoveFirst_IteratorPointsToEndPositionWhenArrayIsEmpty_Test )
{
    // [Preparation]
    QArrayDynamic<int> EMPTY_ARRAY;
    QArrayFixed<int>::QArrayIterator END_ITERATOR(&EMPTY_ARRAY, 0);
    QArrayFixed<int>::QArrayIterator ITERATOR(&EMPTY_ARRAY, 0);

	// [Execution]
    ITERATOR.MoveFirst();

    // [Verification]
    BOOST_CHECK(ITERATOR == END_ITERATOR);
}

#endif

/// <summary>
/// Checks that the iterator points to the last position when the array is not empty.
/// </summary>
QTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenArrayIsNotEmpty_Test )
{
    // [Preparation]
    QArrayFixed<int> SOURCE_ARRAY(3, 0);
    QArrayFixed<int>::QArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    QArrayFixed<int>::QArrayIterator ITERATOR_LAST(&SOURCE_ARRAY, 0);
    ++ITERATOR_LAST;
    ++ITERATOR_LAST;

	// [Execution]
    QArrayFixed<int>::QArrayIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveLast();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_LAST);
}

/// <summary>
/// Checks that the iterator points to the last position even when it was pointing to the position before the first.
/// </summary>
QTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenArrayIsNotEmptyAndIteratorWasPointingToPositionBeforeFirst_Test )
{
    // [Preparation]
    QArrayFixed<int> SOURCE_ARRAY(3, 0);
    QArrayFixed<int>::QArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    --ORIGINAL_ITERATOR;

    QArrayFixed<int>::QArrayIterator ITERATOR_LAST(&SOURCE_ARRAY, 0);
    ++ITERATOR_LAST;
    ++ITERATOR_LAST;

	// [Execution]
    QArrayFixed<int>::QArrayIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveLast();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_LAST);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the array is empty.
/// </summary>
QTEST_CASE ( MoveLast_AssertionFailsWhenArrayIsEmpty_Test )
{
    // [Preparation]
    QArrayDynamic<int> EMPTY_ARRAY;
    EMPTY_ARRAY.Add(0);
    QArrayFixed<int>::QArrayIterator ITERATOR(&EMPTY_ARRAY, 0);
    EMPTY_ARRAY.Remove(0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ITERATOR.MoveLast();
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator points to the end position when the array is empty.
/// </summary>
QTEST_CASE ( MoveLast_IteratorPointsToEndPositionWhenArrayIsEmpty_Test )
{
    // [Preparation]
    QArrayDynamic<int> EMPTY_ARRAY;
    QArrayFixed<int>::QArrayIterator END_ITERATOR(&EMPTY_ARRAY, 0);
    QArrayFixed<int>::QArrayIterator ITERATOR(&EMPTY_ARRAY, 0);

	// [Execution]
    ITERATOR.MoveLast();

    // [Verification]
    BOOST_CHECK(ITERATOR == END_ITERATOR);
}

#endif

/// <summary>
/// Checks that the iterator is correctly incremented when the increment is greater than zero.
/// </summary>
QTEST_CASE ( MoveForward_CommonIteratorIsCorrectlyIncrementedWhenIncrementIsGreaterThanZero_Test )
{
    // [Preparation]
    const int THIRD_ELEMENT_VALUE = 3;
    const int INCREMENT = 2;
    QArrayFixed<int> arSourceArray(3, 0);
    arSourceArray[2] = THIRD_ELEMENT_VALUE;
    QArrayFixed<int>::QArrayIterator iterator(&arSourceArray, 0);
    iterator.MoveFirst();

	// [Execution]
    iterator.MoveForward(INCREMENT);

    // [Verification]
    int uElementValue = *iterator;
    BOOST_CHECK_EQUAL(uElementValue, THIRD_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the iterator is not modified when the increment equals zero.
/// </summary>
QTEST_CASE ( MoveForward_CommonIteratorDoesNotChangeWhenIncrementIsZero_Test )
{
    // [Preparation]
    const int FIRST_ELEMENT_VALUE = 3;
    const int INCREMENT = 0;
    QArrayFixed<int> arSourceArray(3, 0);
    arSourceArray[0] = FIRST_ELEMENT_VALUE;
    QArrayFixed<int>::QArrayIterator iterator(&arSourceArray, 0);
    iterator.MoveFirst();

	// [Execution]
    iterator.MoveForward(INCREMENT);

    // [Verification]
    int uElementValue = *iterator;
    BOOST_CHECK_EQUAL(uElementValue, FIRST_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the iterator points to the forward end position when the new position is out of bounds.
/// </summary>
QTEST_CASE ( MoveForward_CommonIteratorPointsToForwardEndPositionWhenNewPositionIsOutOfBounds_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    QArrayFixed<int> arSourceArray(3, 0);
    const int INCREMENT = arSourceArray.GetCount();
    const bool EXPECTED_RESULT = true;
    QArrayFixed<int>::QArrayIterator iterator(&arSourceArray, 0);
    iterator.MoveFirst();

	// [Execution]
    iterator.MoveForward(INCREMENT);

    // [Verification]
    bool bIsForwardEnd = iterator.IsEnd(EQIterationDirection::E_Forward);
    BOOST_CHECK_EQUAL(bIsForwardEnd, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the iterator points to the first position when it was pointing to the backward end position and then was incremented by 1.
/// </summary>
QTEST_CASE ( MoveForward_CommonIteratorPointsToFirstElementWhenStartsFromBackwardEndPositionAndIsIncrementedByOne_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const int FIRST_ELEMENT_VALUE = 5;
    QArrayFixed<int> arSourceArray(3, 0);
    arSourceArray[0] = FIRST_ELEMENT_VALUE;
    const int INCREMENT = 1;
    QArrayFixed<int>::QArrayIterator iterator(&arSourceArray, 0);
    iterator.MoveFirst();
    --iterator;

	// [Execution]
    iterator.MoveForward(INCREMENT);

    // [Verification]
    int nCurrentElementValue = *iterator;
    BOOST_CHECK_EQUAL(nCurrentElementValue, FIRST_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the iterator points to the forward end position when it was pointing to the backward end position and then was incremented by the size of the array.
/// </summary>
QTEST_CASE ( MoveForward_CommonIteratorPointsToForwardEndWhenStartsFromBackwardEndPositionAndIsIncrementedByMoreThanCount_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    QArrayFixed<int> SOURCE_ARRAY(3, 0);
    const int INCREMENT = SOURCE_ARRAY.GetCount() + 1U;
    const bool EXPECTED_RESULT = true;
    QArrayFixed<int>::QArrayIterator iterator(&SOURCE_ARRAY, 0);
    iterator.MoveFirst();
    --iterator;

	// [Execution]
    iterator.MoveForward(INCREMENT);

    // [Verification]
    bool bIsForwardEnd = iterator.IsEnd(EQIterationDirection::E_Forward);
    BOOST_CHECK_EQUAL(bIsForwardEnd, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator points to forward end position.
/// </summary>
QTEST_CASE ( MoveForward_AssertionFailsWhenIteratorPointsToForwardEndPosition_Test )
{
    // [Preparation]
    QArrayFixed<int> SOURCE_ARRAY(3, 0);
    const int INCREMENT = 1;
    const bool ASSERTION_FAILED = true;
    QArrayFixed<int>::QArrayIterator iterator(&SOURCE_ARRAY, 0);
    iterator.MoveLast();
    ++iterator;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        iterator.MoveForward(INCREMENT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that the iterator is correctly decremented when the decrement is greater than zero.
/// </summary>
QTEST_CASE ( MoveBackward_CommonIteratorIsCorrectlyDecrementedWhenDecrementIsGreaterThanZero_Test )
{
    // [Preparation]
    const int FIRST_ELEMENT_VALUE = 3;
    const int DECREMENT = 2;
    QArrayFixed<int> arSourceArray(3, 0);
    arSourceArray[0] = FIRST_ELEMENT_VALUE;
    QArrayFixed<int>::QArrayIterator iterator(&arSourceArray, 0);
    iterator.MoveLast();

	// [Execution]
    iterator.MoveBackward(DECREMENT);

    // [Verification]
    int uElementValue = *iterator;
    BOOST_CHECK_EQUAL(uElementValue, FIRST_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the iterator is not modified when the decrement equals zero.
/// </summary>
QTEST_CASE ( MoveBackward_CommonIteratorDoesNotChangeWhenDecrementIsZero_Test )
{
    // [Preparation]
    const int THIRD_ELEMENT_VALUE = 3;
    const int DECREMENT = 0;
    QArrayFixed<int> arSourceArray(3, 0);
    arSourceArray[2] = THIRD_ELEMENT_VALUE;
    QArrayFixed<int>::QArrayIterator iterator(&arSourceArray, 0);
    iterator.MoveLast();

	// [Execution]
    iterator.MoveBackward(DECREMENT);

    // [Verification]
    int uElementValue = *iterator;
    BOOST_CHECK_EQUAL(uElementValue, THIRD_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the iterator points to the backward end position when the new position is out of bounds.
/// </summary>
QTEST_CASE ( MoveBackward_CommonIteratorPointsToBackwardEndPositionWhenNewPositionIsOutOfBounds_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    QArrayFixed<int> arSourceArray(3, 0);
    const int DECREMENT = arSourceArray.GetCount();
    const bool EXPECTED_RESULT = true;
    QArrayFixed<int>::QArrayIterator iterator(&arSourceArray, 0);
    iterator.MoveLast();

	// [Execution]
    iterator.MoveBackward(DECREMENT);

    // [Verification]
    bool bIsBackwardEnd = iterator.IsEnd(EQIterationDirection::E_Backward);
    BOOST_CHECK_EQUAL(bIsBackwardEnd, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the iterator points to the last position when it was pointing to the forward end position and then was decremented by 1.
/// </summary>
QTEST_CASE ( MoveBackward_CommonIteratorPointsToFirstElementWhenStartsFromForwardEndPositionAndIsIncrementedByOne_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const int LAST_ELEMENT_VALUE = 5;
    QArrayFixed<int> arSourceArray(3, 0);
    arSourceArray[2] = LAST_ELEMENT_VALUE;
    const int DECREMENT = 1;
    QArrayFixed<int>::QArrayIterator iterator(&arSourceArray, 0);
    iterator.MoveLast();
    ++iterator;

	// [Execution]
    iterator.MoveBackward(DECREMENT);

    // [Verification]
    int nCurrentElementValue = *iterator;
    BOOST_CHECK_EQUAL(nCurrentElementValue, LAST_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the iterator points to the backward end position when it was pointing to the forward end position and then was decremented by the size of the array.
/// </summary>
QTEST_CASE ( MoveBackward_CommonIteratorPointsToBackwardEndWhenStartsFromForwardEndPositionAndIsDecrementedByMoreThanCount_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    QArrayFixed<int> arSourceArray(3, 0);
    const int DECREMENT = arSourceArray.GetCount() + 1U;
    const bool EXPECTED_RESULT = true;
    QArrayFixed<int>::QArrayIterator iterator(&arSourceArray, 0);
    iterator.MoveLast();
    ++iterator;

	// [Execution]
    iterator.MoveBackward(DECREMENT);

    // [Verification]
    bool bIsBackwardEnd = iterator.IsEnd(EQIterationDirection::E_Backward);
    BOOST_CHECK_EQUAL(bIsBackwardEnd, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is pointing to the backward end position.
/// </summary>
QTEST_CASE ( MoveBackward_AssertionFailsWhenIteratorPointsToBackwardEndPosition_Test )
{
    // [Preparation]
    QArrayFixed<int> arSourceArray(3, 0);
    const int DECREMENT = 1;
    const bool ASSERTION_FAILED = true;
    QArrayFixed<int>::QArrayIterator iterator(&arSourceArray, 0);
    iterator.MoveFirst();
    --iterator;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        iterator.MoveBackward(DECREMENT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

// End - Test Suite: QArrayIterator
QTEST_SUITE_END()
