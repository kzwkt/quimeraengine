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

QTEST_SUITE_BEGIN( QListIterator_TestSuite )

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
    QList<int>::QListIterator EXPECTED_ITERATOR(&SOURCE_LIST, 0);
    EXPECTED_ITERATOR.MoveFirst();
    ++EXPECTED_ITERATOR;

	// [Execution]
    QList<int>::QListIterator iterator(&SOURCE_LIST, POSITION);
    
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
        QList<int>::QListIterator INVALID_ITERATOR(SOURCE_LIST, 0);
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
        QList<int>::QListIterator INVALID_ITERATOR(&SOURCE_LIST, INVALID_POSITION);
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
    QList<int>::QListIterator iterator(&SOURCE_LIST, INVALID_POSITION);

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
    QList<int>::QListIterator iterator(&SOURCE_LIST, 0);

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
    QList<int>::QListIterator ITERATOR(&SOURCE_LIST, 0);
    ++ITERATOR;

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
    // [Preparation]
    QList<int> SOURCE_LIST(10);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QListIterator INVALID_ITERATOR(&SOURCE_LIST, 0);
    INVALID_ITERATOR.MoveLast();
    SOURCE_LIST.Remove(SOURCE_LIST.GetCount()-1);
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
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

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

    QList<int>::QListIterator ITERATOR(&SOURCE_LIST, 0);
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

    QList<int>::QListIterator ITERATOR(&SOURCE_LIST, 0);
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
    QList<TestStructure>::QListIterator ITERATOR(&SOURCE_LIST, 0);
    ++ITERATOR;

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
    // [Preparation]
    QList<TestStructure> SOURCE_LIST(10);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(TestStructure(i));
    }

    QList<TestStructure>::QListIterator INVALID_ITERATOR(&SOURCE_LIST, 0);
    INVALID_ITERATOR.MoveLast();
    SOURCE_LIST.Remove(SOURCE_LIST.GetCount()-1);
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
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

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

    QList<TestStructure>::QListIterator ITERATOR(&SOURCE_LIST, 0);
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

    QList<TestStructure>::QListIterator ITERATOR(&SOURCE_LIST, 0);
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

    QList<int>::QListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ORIGINAL_ITERATOR.MoveFirst();

	// [Execution]
    QList<int>::QListIterator iterator(ORIGINAL_ITERATOR);
    QList<int>::QListIterator iteratorPreviousState = iterator++;

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

    QList<int>::QListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ORIGINAL_ITERATOR.MoveFirst();
    --ORIGINAL_ITERATOR;

	// [Execution]
    QList<int>::QListIterator iterator(ORIGINAL_ITERATOR);
    QList<int>::QListIterator iteratorPreviousState = iterator++;
    int nCurrentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(nCurrentElement == FIRST_ELEMENT_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorPostIncrement_AssertionFailsWhenIteratorIsNotValid_Test )
{
    // [Preparation]
    QList<int> SOURCE_LIST(10);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QListIterator INVALID_ITERATOR(&SOURCE_LIST, 0);
    INVALID_ITERATOR.MoveLast();
    SOURCE_LIST.Remove(SOURCE_LIST.GetCount()-1);
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
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

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

    QList<int>::QListIterator ITERATOR_END(&SOURCE_LIST, 0);
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

    QList<int>::QListIterator ITERATOR_END(&SOURCE_LIST, 0);
    ITERATOR_END.MoveLast();
    ++ITERATOR_END;

	// [Execution]
    QList<int>::QListIterator iterator(ITERATOR_END);
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

    QList<int>::QListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ORIGINAL_ITERATOR.MoveLast();

	// [Execution]
    QList<int>::QListIterator iterator(ORIGINAL_ITERATOR);
    QList<int>::QListIterator iteratorPreviousState = iterator--;

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

    QList<int>::QListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ORIGINAL_ITERATOR.MoveLast();
    ++ORIGINAL_ITERATOR;

	// [Execution]
    QList<int>::QListIterator iterator(ORIGINAL_ITERATOR);
    QList<int>::QListIterator iteratorPreviousState = iterator--;
    int nCurrentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(nCurrentElement == LAST_ELEMENT_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorPostDecrement_AssertionFailsWhenIteratorIsNotValid_Test )
{
    // [Preparation]
    QList<int> SOURCE_LIST(10);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QListIterator INVALID_ITERATOR(&SOURCE_LIST, 0);
    INVALID_ITERATOR.MoveLast();
    SOURCE_LIST.Remove(SOURCE_LIST.GetCount()-1);
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
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

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

    QList<int>::QListIterator ITERATOR_END(&SOURCE_LIST, 0);
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

    QList<int>::QListIterator ITERATOR_END(&SOURCE_LIST, 0);
    ITERATOR_END.MoveFirst();
    --ITERATOR_END;

	// [Execution]
    QList<int>::QListIterator iterator(ITERATOR_END);
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

    QList<int>::QListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ORIGINAL_ITERATOR.MoveFirst();

	// [Execution]
    QList<int>::QListIterator iterator(ORIGINAL_ITERATOR);
    QList<int>::QListIterator iteratorCurrentState = ++iterator;

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

    QList<int>::QListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ORIGINAL_ITERATOR.MoveFirst();
    --ORIGINAL_ITERATOR;

	// [Execution]
    QList<int>::QListIterator iterator(ORIGINAL_ITERATOR);
    QList<int>::QListIterator iteratorCurrentState = ++iterator;
    int nCurrentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorCurrentState == iterator);
    BOOST_CHECK(nCurrentElement == FIRST_ELEMENT_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorPreIncrement_AssertionFailsWhenIteratorIsNotValid_Test )
{
    // [Preparation]
    QList<int> SOURCE_LIST(10);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QListIterator INVALID_ITERATOR(&SOURCE_LIST, 0);
    INVALID_ITERATOR.MoveLast();
    SOURCE_LIST.Remove(SOURCE_LIST.GetCount()-1);
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
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

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

    QList<int>::QListIterator ITERATOR_END(&SOURCE_LIST, 0);
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

    QList<int>::QListIterator ITERATOR_END(&SOURCE_LIST, 0);
    ITERATOR_END.MoveLast();
    ++ITERATOR_END;

	// [Execution]
    QList<int>::QListIterator iterator(ITERATOR_END);
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

    QList<int>::QListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ORIGINAL_ITERATOR.MoveLast();

	// [Execution]
    QList<int>::QListIterator iterator(ORIGINAL_ITERATOR);
    QList<int>::QListIterator iteratorCurrentState = --iterator;

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

    QList<int>::QListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ORIGINAL_ITERATOR.MoveLast();
    ++ORIGINAL_ITERATOR;

	// [Execution]
    QList<int>::QListIterator iterator(ORIGINAL_ITERATOR);
    QList<int>::QListIterator iteratorCurrentState = --iterator;
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
{
    // [Preparation]
    QList<int> SOURCE_LIST(10);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QListIterator INVALID_ITERATOR(&SOURCE_LIST, 0);
    INVALID_ITERATOR.MoveLast();
    SOURCE_LIST.Remove(SOURCE_LIST.GetCount()-1);
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
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

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

    QList<int>::QListIterator ITERATOR_END(&SOURCE_LIST, 0);
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

    QList<int>::QListIterator ITERATOR_END(&SOURCE_LIST, 0);
    ITERATOR_END.MoveFirst();
    --ITERATOR_END;

	// [Execution]
    QList<int>::QListIterator iterator(ITERATOR_END);
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

    QList<int>::QListIterator ITERATOR_A(&SOURCE_LIST, 0);
    QList<int>::QListIterator ITERATOR_B(&SOURCE_LIST, 0);
    ++ITERATOR_A;

	// [Execution]
    QList<int>::QListIterator iterator = ITERATOR_B;
    iterator = ITERATOR_A;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_A);
}

/// <summary>
/// Checks that input iterator is copied when resident iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorAssignment_InputIteratorIsCorrectlyCopiedWhenResidentIteratorIsNotValid_Test )
{
    // [Preparation]
    QList<int> SOURCE_LIST(10);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QListIterator INVALID_ITERATOR(&SOURCE_LIST, 0);
    INVALID_ITERATOR.MoveLast();
    SOURCE_LIST.Remove(SOURCE_LIST.GetCount()-1);
    QList<int>::QListIterator VALID_ITERATOR(&SOURCE_LIST, 0);

	// [Execution]
    QList<int>::QListIterator iterator = INVALID_ITERATOR;
    iterator = VALID_ITERATOR;

    // [Verification]
    BOOST_CHECK(iterator.IsValid());
    BOOST_CHECK(iterator == VALID_ITERATOR);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorAssignment_AssertionFailsWhenInputIteratorIsNotValid_Test )
{
    // [Preparation]
    QList<int> SOURCE_LIST(10);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QListIterator INVALID_ITERATOR(&SOURCE_LIST, 0);
    INVALID_ITERATOR.MoveLast();
    SOURCE_LIST.Remove(SOURCE_LIST.GetCount()-1);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QList<int>::QListIterator iterator(SOURCE_LIST);
        iterator = INVALID_ITERATOR;
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

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

    QList<int>::QListIterator ITERATOR_A(&LIST_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QList<int>::QListIterator iterator(&LIST_B, 0);
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
{
    // [Preparation]
    QList<int> SOURCE_LIST(10);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QListIterator INVALID_ITERATOR(&SOURCE_LIST, 0);
    INVALID_ITERATOR.MoveLast();
    SOURCE_LIST.Remove(SOURCE_LIST.GetCount()-1);

	// [Execution]
    QList<int>::QListIterator iterator(&SOURCE_LIST, 0);
    iterator = INVALID_ITERATOR;

    // [Verification]
    BOOST_CHECK(iterator == INVALID_ITERATOR);
}

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

    QList<int>::QListIterator ITERATOR_A(&LIST_A, 0);
    QList<int>::QListIterator ITERATOR_B(&LIST_B, 0);

	// [Execution]
    QList<int>::QListIterator iterator = ITERATOR_B;
    iterator = ITERATOR_A;

    // [Verification]
    BOOST_CHECK(iterator != ITERATOR_A);
    BOOST_CHECK(iterator == ITERATOR_B);
}

#endif

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

    QList<int>::QListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ++ORIGINAL_ITERATOR;
    ++ORIGINAL_ITERATOR;
    ++ORIGINAL_ITERATOR;
    QList<int>::QListIterator ITERATOR_FIRST(&SOURCE_LIST, 0);

	// [Execution]
    QList<int>::QListIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveFirst();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_FIRST);
}

/// <summary>
/// Checks that the iterator points to the first position even when it was not valid.
/// </summary>
QTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenListIsNotEmptyAndIteratorWasNotValid_Test )
{
    // [Preparation]
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QListIterator ITERATOR_FIRST(&SOURCE_LIST, 0);
    QList<int>::QListIterator INVALID_ITERATOR(&SOURCE_LIST, 0);
    INVALID_ITERATOR.MoveLast();
    SOURCE_LIST.Remove(SOURCE_LIST.GetCount()-1);

	// [Execution]
    QList<int>::QListIterator iterator(INVALID_ITERATOR);
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

    QList<int>::QListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ORIGINAL_ITERATOR--;

    QList<int>::QListIterator ITERATOR_FIRST(&SOURCE_LIST, 0);

	// [Execution]
    QList<int>::QListIterator iterator(ORIGINAL_ITERATOR);
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
    QList<int>::QListIterator END_ITERATOR(&EMPTY_ARRAY, 0);
    END_ITERATOR.MoveLast();
    ++END_ITERATOR;
    QList<int>::QListIterator ITERATOR(&EMPTY_ARRAY, 0);

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

    QList<int>::QListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    QList<int>::QListIterator ITERATOR_LAST(&SOURCE_LIST, 0);
    ++ITERATOR_LAST;
    ++ITERATOR_LAST;

	// [Execution]
    QList<int>::QListIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveLast();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_LAST);
}

/// <summary>
/// Checks that the iterator points to the last position even when it was not valid.
/// </summary>
QTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenListIsNotEmptyAndIteratorWasNotValid_Test )
{
    // [Preparation]
    QList<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    QList<int>::QListIterator ITERATOR_LAST(&SOURCE_LIST, 0);
    ++ITERATOR_LAST;
    QList<int>::QListIterator INVALID_ITERATOR(&SOURCE_LIST, 0);
    ++INVALID_ITERATOR;
    ++INVALID_ITERATOR;
    SOURCE_LIST.Remove(SOURCE_LIST.GetCount()-1);

	// [Execution]
    QList<int>::QListIterator iterator(INVALID_ITERATOR);
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

    QList<int>::QListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    --ORIGINAL_ITERATOR;

    QList<int>::QListIterator ITERATOR_LAST(&SOURCE_LIST, 0);
    ++ITERATOR_LAST;
    ++ITERATOR_LAST;

	// [Execution]
    QList<int>::QListIterator iterator(ORIGINAL_ITERATOR);
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
    QList<int>::QListIterator END_ITERATOR(&EMPTY_ARRAY, 0);
    END_ITERATOR.MoveLast();
    ++END_ITERATOR;
    QList<int>::QListIterator ITERATOR(&EMPTY_ARRAY, 0);

	// [Execution]
    ITERATOR.MoveLast();

    // [Verification]
    BOOST_CHECK(ITERATOR == END_ITERATOR);
}

#endif

// End - Test Suite: QListIterator
QTEST_SUITE_END()
