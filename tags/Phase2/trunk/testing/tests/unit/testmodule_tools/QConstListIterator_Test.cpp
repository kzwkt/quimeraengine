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

#include "EQIterationDirection.h"

using Kinesis::QuimeraEngine::Tools::Containers::QList;

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

QTEST_SUITE_BEGIN( QConstListIterator_TestSuite )

/// <summary>
/// Checks that the iterator points to the given position when using a common list.
/// </summary>
QTEST_CASE ( Constructor_IteratorPointsToGivenPositionWhenUsingCommonList_Test )
{
    // [Preparation]
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    const unsigned int POSITION = 1;
    QList<int>::QConstListIterator EXPECTED_ITERATOR(&SOURCE_LIST, 0);
    EXPECTED_ITERATOR.MoveFirst();
    ++EXPECTED_ITERATOR;

	// [Execution]
    QList<int>::QConstListIterator iterator(&SOURCE_LIST, POSITION);
    
    // [Verification]
    BOOST_CHECK(iterator == EXPECTED_ITERATOR);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when input list is null.
/// </summary>
QTEST_CASE ( Constructor_AssertionFailsWhenInputListIsNull_Test )
{
    // [Preparation]
    QList<int>* SOURCE_LIST = null_q;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QList<int>::QConstListIterator INVALID_ITERATOR(SOURCE_LIST, 0);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when input position is not lower than the capacity.
/// </summary>
QTEST_CASE ( Constructor_AssertionFailsWhenInputPositionIsNotLowerThanCapacity_Test )
{
    // [Preparation]
    const unsigned int CAPACITY = 3;
    QList<int> SOURCE_LIST(CAPACITY);
    for(unsigned int i = 0; i < CAPACITY; ++i)
    {
        SOURCE_LIST.Add(i);
    }

    const unsigned int INVALID_POSITION = CAPACITY;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QList<int>::QConstListIterator INVALID_ITERATOR(&SOURCE_LIST, INVALID_POSITION);
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
    QList<int> SOURCE_LIST(NUMBER_OF_ELEMENTS);
    for(unsigned int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
    {
        SOURCE_LIST.Add(i);
    }

    const unsigned int INVALID_POSITION = NUMBER_OF_ELEMENTS;
    const bool IS_END = true;

	// [Execution]
    QList<int>::QConstListIterator iterator(&SOURCE_LIST, INVALID_POSITION);

    // [Verification]
    bool bIsEndIterationForward = iterator.IsEnd(EQIterationDirection::E_Forward);
    BOOST_CHECK_EQUAL(bIsEndIterationForward, IS_END);
}

/// <summary>
/// Checks that the iterator points to the end position (forward iteration) when using an empty list.
/// </summary>
QTEST_CASE ( Constructor_IteratorPointsToForwardEndPositionWhenUsingEmptyList_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const QList<int> SOURCE_LIST(3);
    const bool IS_END = true;

	// [Execution]
    QList<int>::QConstListIterator iterator(&SOURCE_LIST, 0);

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
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    const int EXPECTED_VALUE = 1;
    QList<int>::QConstListIterator ITERATOR(&SOURCE_LIST, 0);
    ++ITERATOR;

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
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR(&SOURCE_LIST, 0);
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
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR(&SOURCE_LIST, 0);
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
    QList<TestStructure> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(TestStructure(i));
    }

    const int EXPECTED_VALUE = 1;
    QList<TestStructure>::QConstListIterator ITERATOR(&SOURCE_LIST, 0);
    ++ITERATOR;

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
    QList<TestStructure> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(TestStructure(i));
    }

    QList<TestStructure>::QConstListIterator ITERATOR(&SOURCE_LIST, 0);
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
    QList<TestStructure> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(TestStructure(i));
    }

    QList<TestStructure>::QConstListIterator ITERATOR(&SOURCE_LIST, 0);
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
    const int SECOND_ELEMENT_VALUE = 1;
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ORIGINAL_ITERATOR.MoveFirst();

	// [Execution]
    QList<int>::QConstListIterator iterator(ORIGINAL_ITERATOR);
    QList<int>::QConstListIterator iteratorPreviousState = iterator++;

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
    const int FIRST_ELEMENT_VALUE = 0;
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ORIGINAL_ITERATOR.MoveFirst();
    --ORIGINAL_ITERATOR;

	// [Execution]
    QList<int>::QConstListIterator iterator(ORIGINAL_ITERATOR);
    QList<int>::QConstListIterator iteratorPreviousState = iterator++;
    int nCurrentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(nCurrentElement == FIRST_ELEMENT_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position.
/// </summary>
QTEST_CASE ( OperatorPostIncrement_AssertionFailsWhenIteratorAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_END(&SOURCE_LIST, 0);
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
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_END(&SOURCE_LIST, 0);
    ITERATOR_END.MoveLast();
    ++ITERATOR_END;

	// [Execution]
    QList<int>::QConstListIterator iterator(ITERATOR_END);
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
    const int SECOND_ELEMENT_VALUE = 1;
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ORIGINAL_ITERATOR.MoveLast();

	// [Execution]
    QList<int>::QConstListIterator iterator(ORIGINAL_ITERATOR);
    QList<int>::QConstListIterator iteratorPreviousState = iterator--;

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
    const int LAST_ELEMENT_VALUE = 2;
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ORIGINAL_ITERATOR.MoveLast();
    ++ORIGINAL_ITERATOR;

	// [Execution]
    QList<int>::QConstListIterator iterator(ORIGINAL_ITERATOR);
    QList<int>::QConstListIterator iteratorPreviousState = iterator--;
    int nCurrentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(nCurrentElement == LAST_ELEMENT_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position before the first one.
/// </summary>
QTEST_CASE ( OperatorPostDecrement_AssertionFailsWhenIteratorAlreadyPointsToEndPositionBeforeFirst_Test )
{
    // [Preparation]
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_END(&SOURCE_LIST, 0);
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
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_END(&SOURCE_LIST, 0);
    ITERATOR_END.MoveFirst();
    --ITERATOR_END;

	// [Execution]
    QList<int>::QConstListIterator iterator(ITERATOR_END);
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
    const int SECOND_ELEMENT_VALUE = 1;
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ORIGINAL_ITERATOR.MoveFirst();

	// [Execution]
    QList<int>::QConstListIterator iterator(ORIGINAL_ITERATOR);
    QList<int>::QConstListIterator iteratorCurrentState = ++iterator;

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
    const int FIRST_ELEMENT_VALUE = 0;
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ORIGINAL_ITERATOR.MoveFirst();
    --ORIGINAL_ITERATOR;

	// [Execution]
    QList<int>::QConstListIterator iterator(ORIGINAL_ITERATOR);
    QList<int>::QConstListIterator iteratorCurrentState = ++iterator;
    int nCurrentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorCurrentState == iterator);
    BOOST_CHECK(nCurrentElement == FIRST_ELEMENT_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position.
/// </summary>
QTEST_CASE ( OperatorPreIncrement_AssertionFailsWhenIteratorAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_END(&SOURCE_LIST, 0);
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
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_END(&SOURCE_LIST, 0);
    ITERATOR_END.MoveLast();
    ++ITERATOR_END;

	// [Execution]
    QList<int>::QConstListIterator iterator(ITERATOR_END);
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
    const int SECOND_ELEMENT_VALUE = 1;
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ORIGINAL_ITERATOR.MoveLast();

	// [Execution]
    QList<int>::QConstListIterator iterator(ORIGINAL_ITERATOR);
    QList<int>::QConstListIterator iteratorCurrentState = --iterator;

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
    const int LAST_ELEMENT_VALUE = 2;
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ORIGINAL_ITERATOR.MoveLast();
    ++ORIGINAL_ITERATOR;

	// [Execution]
    QList<int>::QConstListIterator iterator(ORIGINAL_ITERATOR);
    QList<int>::QConstListIterator iteratorCurrentState = --iterator;
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
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_END(&SOURCE_LIST, 0);
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
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_END(&SOURCE_LIST, 0);
    ITERATOR_END.MoveFirst();
    --ITERATOR_END;

	// [Execution]
    QList<int>::QConstListIterator iterator(ITERATOR_END);
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
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_A(&SOURCE_LIST, 0);
    QList<int>::QConstListIterator ITERATOR_B(&SOURCE_LIST, 0);
    ++ITERATOR_A;

	// [Execution]
    QList<int>::QConstListIterator iterator = ITERATOR_B;
    iterator = ITERATOR_A;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_A);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different list.
/// </summary>
QTEST_CASE ( OperatorAssignment_AssertionFailsWhenInputIteratorPointsToDifferentList_Test )
{
    // [Preparation]
    QList<int> LIST_A(3);
    QList<int> LIST_B(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
        LIST_B.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QList<int>::QConstListIterator iterator(&LIST_B, 0);
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
/// Checks that the iterator is not copied when it points to a different list.
/// </summary>
QTEST_CASE ( OperatorAssignment_IteratorDoesNotChangeIfInputIteratorPointsToDifferentList_Test )
{
    // [Preparation]
    QList<int> LIST_A(3);
    QList<int> LIST_B(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
        LIST_B.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);
    QList<int>::QConstListIterator ITERATOR_B(&LIST_B, 0);

	// [Execution]
    QList<int>::QConstListIterator iterator = ITERATOR_B;
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
    QList<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);
    QList<int>::QConstListIterator ITERATOR_B(&LIST_A, 0);
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
    QList<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);
    QList<int>::QConstListIterator ITERATOR_B(&LIST_A, 0);
    ++ITERATOR_B;

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A == ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different list.
/// </summary>
QTEST_CASE ( OperatorEquality_AssertionFailsWhenIteratorsPointToDifferentLists_Test )
{
    // [Preparation]
    QList<int> LIST_A(3);
    QList<int> LIST_B(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
        LIST_B.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QList<int>::QConstListIterator iterator(&LIST_B, 0);
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
/// Checks that it returns False when iterators point to a different list.
/// </summary>
QTEST_CASE ( OperatorEquality_ReturnsFalseWhenIteratorsPointToDifferentLists_Test )
{
    // [Preparation]
    QList<int> LIST_A(3);
    QList<int> LIST_B(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
        LIST_B.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);
    QList<int>::QConstListIterator ITERATOR_B(&LIST_B, 0);
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
    QList<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);
    QList<int>::QConstListIterator ITERATOR_B(&LIST_A, 0);
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
    QList<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);
    QList<int>::QConstListIterator ITERATOR_B(&LIST_A, 0);
    ++ITERATOR_B;

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_A != ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different list.
/// </summary>
QTEST_CASE ( OperatorInequality_AssertionFailsWhenIteratorsPointToDifferentLists_Test )
{
    // [Preparation]
    QList<int> LIST_A(3);
    QList<int> LIST_B(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
        LIST_B.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QList<int>::QConstListIterator iterator(&LIST_B, 0);
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
/// Checks that it returns True when iterators point to a different list.
/// </summary>
QTEST_CASE ( OperatorInequality_ReturnsTrueWhenIteratorsPointToDifferentLists_Test )
{
    // [Preparation]
    QList<int> LIST_A(3);
    QList<int> LIST_B(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
        LIST_B.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);
    QList<int>::QConstListIterator ITERATOR_B(&LIST_B, 0);
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
    QList<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);
    QList<int>::QConstListIterator ITERATOR_B(&LIST_A, 0);
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
    QList<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);
    QList<int>::QConstListIterator ITERATOR_B(&LIST_A, 0);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A > ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident iterator is not greater than the input iterator, even if the internal position to which the resident iterator is greater.
/// </summary>
QTEST_CASE ( OperatorGreaterThan_ReturnsFalseWhenResidentIteratorIsNotGreaterThanInputIteratorEvenIfPositionIsGreater_Test )
{
    // [Preparation]
    QList<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    LIST_A.Remove(0);
    LIST_A.Remove(0);
    LIST_A.Add(1);
    LIST_A.Add(1);

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);
    ITERATOR_A.MoveFirst(); // Internal position: 2
    QList<int>::QConstListIterator ITERATOR_B(&LIST_A, 0);
    ITERATOR_B.MoveLast(); // Internal position: 0
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A > ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different list.
/// </summary>
QTEST_CASE ( OperatorGreaterThan_AssertionFailsWhenIteratorsPointToDifferentLists_Test )
{
    // [Preparation]
    QList<int> LIST_A(3);
    QList<int> LIST_B(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
        LIST_B.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QList<int>::QConstListIterator iterator(&LIST_B, 0);
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
/// Checks that it returns False when iterators point to a different list.
/// </summary>
QTEST_CASE ( OperatorGreaterThan_ReturnsFalseWhenIteratorsPointToDifferentLists_Test )
{
    // [Preparation]
    QList<int> LIST_A(3);
    QList<int> LIST_B(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
        LIST_B.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);
    ++ITERATOR_A;
    QList<int>::QConstListIterator ITERATOR_B(&LIST_B, 0);
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
    QList<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);
    QList<int>::QConstListIterator ITERATOR_B(&LIST_A, 0);
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
    QList<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);
    QList<int>::QConstListIterator ITERATOR_B(&LIST_A, 0);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_B < ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident iterator is not lower than the input iterator, even if the internal position to which the resident iterator is lower.
/// </summary>
QTEST_CASE ( OperatorLowerThan_ReturnsFalseWhenResidentIteratorIsNotLowerThanInputIteratorEvenIfPositionIsLower_Test )
{
    // [Preparation]
    QList<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    LIST_A.Remove(0);
    LIST_A.Remove(0);
    LIST_A.Add(1);
    LIST_A.Add(1);

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);
    ITERATOR_A.MoveFirst(); // Internal position: 2
    QList<int>::QConstListIterator ITERATOR_B(&LIST_A, 0);
    ITERATOR_B.MoveLast(); // Internal position: 0
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_B < ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different list.
/// </summary>
QTEST_CASE ( OperatorLowerThan_AssertionFailsWhenIteratorsPointToDifferentLists_Test )
{
    // [Preparation]
    QList<int> LIST_A(3);
    QList<int> LIST_B(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
        LIST_B.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);
    ++ITERATOR_A;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QList<int>::QConstListIterator iterator(&LIST_B, 0);
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
/// Checks that it returns False when iterators point to a different list.
/// </summary>
QTEST_CASE ( OperatorLowerThan_ReturnsFalseWhenIteratorsPointToDifferentLists_Test )
{
    // [Preparation]
    QList<int> LIST_A(3);
    QList<int> LIST_B(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
        LIST_B.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);
    QList<int>::QConstListIterator ITERATOR_B(&LIST_B, 0);
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
    QList<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);
    QList<int>::QConstListIterator ITERATOR_B(&LIST_A, 0);
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
    QList<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);
    QList<int>::QConstListIterator ITERATOR_B(&LIST_A, 0);
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
    QList<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);
    QList<int>::QConstListIterator ITERATOR_B(&LIST_A, 0);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A >= ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different list.
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_AssertionFailsWhenIteratorsPointToDifferentLists_Test )
{
    // [Preparation]
    QList<int> LIST_A(3);
    QList<int> LIST_B(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
        LIST_B.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QList<int>::QConstListIterator iterator(&LIST_B, 0);
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
/// Checks that it returns False when iterators point to a different list.
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsFalseWhenIteratorsPointToDifferentLists_Test )
{
    // [Preparation]
    QList<int> LIST_A(3);
    QList<int> LIST_B(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
        LIST_B.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);
    ++ITERATOR_A;
    QList<int>::QConstListIterator ITERATOR_B(&LIST_B, 0);
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
    QList<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);
    QList<int>::QConstListIterator ITERATOR_B(&LIST_A, 0);
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
    QList<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);
    QList<int>::QConstListIterator ITERATOR_B(&LIST_A, 0);
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
    QList<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);
    QList<int>::QConstListIterator ITERATOR_B(&LIST_A, 0);
    ++ITERATOR_A;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A <= ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different list.
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_AssertionFailsWhenIteratorsPointToDifferentLists_Test )
{
    // [Preparation]
    QList<int> LIST_A(3);
    QList<int> LIST_B(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
        LIST_B.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QList<int>::QConstListIterator iterator(&LIST_B, 0);
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
/// Checks that it returns False when iterators point to a different list.
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_ReturnsFalseWhenIteratorsPointToDifferentLists_Test )
{
    // [Preparation]
    QList<int> LIST_A(3);
    QList<int> LIST_B(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
        LIST_B.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR_A(&LIST_A, 0);
    QList<int>::QConstListIterator ITERATOR_B(&LIST_B, 0);
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
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR(&SOURCE_LIST, 0);
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
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR(&SOURCE_LIST, 0);
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
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR(&SOURCE_LIST, 0);
    ITERATOR.MoveLast();

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR.IsEnd();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the iterator points to the position before the first.
/// </summary>
QTEST_CASE ( IsEnd2_ReturnsTrueWhenIteratorPointsToPositionBeforeFirst_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR(&SOURCE_LIST, 0);
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
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR(&SOURCE_LIST, 0);
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
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR(&SOURCE_LIST, 0);
    ITERATOR.MoveLast();

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR.IsEnd(EQIterationDirection::E_Backward);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the iterator points to the first position when the list is not empty.
/// </summary>
QTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenListIsNotEmpty_Test )
{
    // [Preparation]
    QList<int> SOURCE_LIST(10);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ++ORIGINAL_ITERATOR;
    ++ORIGINAL_ITERATOR;
    ++ORIGINAL_ITERATOR;
    QList<int>::QConstListIterator ITERATOR_FIRST(&SOURCE_LIST, 0);

	// [Execution]
    QList<int>::QConstListIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveFirst();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_FIRST);
}

/// <summary>
/// Checks that the iterator points to the first position even when it was pointing to the position before the first.
/// </summary>
QTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenListIsNotEmptyAndIteratorWasPointingToPositionBeforeFirst_Test )
{
    // [Preparation]
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ORIGINAL_ITERATOR--;

    QList<int>::QConstListIterator ITERATOR_FIRST(&SOURCE_LIST, 0);

	// [Execution]
    QList<int>::QConstListIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveFirst();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_FIRST);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator points to the end position when the list is empty.
/// </summary>
QTEST_CASE ( MoveFirst_IteratorPointsToEndPositionWhenListIsEmpty_Test )
{
    // [Preparation]
    QList<int> EMPTY_ARRAY;
    QList<int>::QConstListIterator END_ITERATOR(&EMPTY_ARRAY, 0);
    END_ITERATOR.MoveLast();
    ++END_ITERATOR;
    QList<int>::QConstListIterator ITERATOR(&EMPTY_ARRAY, 0);

	// [Execution]
    ITERATOR.MoveFirst();

    // [Verification]
    BOOST_CHECK(ITERATOR == END_ITERATOR);
}

#endif

/// <summary>
/// Checks that the iterator points to the last position when the list is not empty.
/// </summary>
QTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenListIsNotEmpty_Test )
{
    // [Preparation]
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    QList<int>::QConstListIterator ITERATOR_LAST(&SOURCE_LIST, 0);
    ++ITERATOR_LAST;
    ++ITERATOR_LAST;

	// [Execution]
    QList<int>::QConstListIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveLast();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_LAST);
}

/// <summary>
/// Checks that the iterator points to the last position even when it was pointing to the position before the first.
/// </summary>
QTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenListIsNotEmptyAndIteratorWasPointingToPositionBeforeFirst_Test )
{
    // [Preparation]
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    --ORIGINAL_ITERATOR;

    QList<int>::QConstListIterator ITERATOR_LAST(&SOURCE_LIST, 0);
    ++ITERATOR_LAST;
    ++ITERATOR_LAST;

	// [Execution]
    QList<int>::QConstListIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveLast();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_LAST);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator points to the end position when the list is empty.
/// </summary>
QTEST_CASE ( MoveLast_IteratorPointsToEndPositionWhenListIsEmpty_Test )
{
    // [Preparation]
    QList<int> EMPTY_ARRAY;
    QList<int>::QConstListIterator END_ITERATOR(&EMPTY_ARRAY, 0);
    END_ITERATOR.MoveLast();
    ++END_ITERATOR;
    QList<int>::QConstListIterator ITERATOR(&EMPTY_ARRAY, 0);

	// [Execution]
    ITERATOR.MoveLast();

    // [Verification]
    BOOST_CHECK(ITERATOR == END_ITERATOR);
}

#endif

/// <summary>
/// Checks that it returns True when iterator points to a common position.
/// </summary>
QTEST_CASE ( IsValid_ReturnsTrueWhenIteratorPointsToCommonPosition_Test )
{
    // [Preparation]
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QConstListIterator ITERATOR(&SOURCE_LIST, 0);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR.IsValid();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

// End - Test Suite: QConstListIterator
QTEST_SUITE_END()
