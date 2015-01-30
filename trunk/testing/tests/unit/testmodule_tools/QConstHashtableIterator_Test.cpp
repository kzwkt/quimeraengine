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

#include "QHashtable.h"
#include "SQStringHashProvider.h"

using Kinesis::QuimeraEngine::Tools::Containers::QHashtable;
using Kinesis::QuimeraEngine::Tools::Containers::SQStringHashProvider;

/// <summary>
/// Small structure used in operator* and operator-> tests.
/// </summary>
struct TestStructure
{
    TestStructure(const int field) : m_field(field)
    {
    }

    bool operator==(const TestStructure& ts) const
    {
        return m_field == ts.m_field;
    }
    
    bool operator<(const TestStructure& ts) const
    {
        return m_field < ts.m_field;
    }

    int m_field;
};

QTEST_SUITE_BEGIN( QConstHashtableIterator_TestSuite )
    /* [TODO] Thund: Uncomment when GetFirst exists
/// <summary>
/// Checks that the iterator points to the given position when using a common hashtable.
/// </summary>
QTEST_CASE ( Constructor_IteratorPointsToGivenPositionWhenUsingCommonHashtable_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);
    const pointer_uint_q POSITION = 1;
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator EXPECTED_ITERATOR = HASHTABLE.GetFirst();
    ++EXPECTED_ITERATOR;

	// [Execution]
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iterator(&HASHTABLE, POSITION);
    
    // [Verification]
    BOOST_CHECK(iterator == EXPECTED_ITERATOR);
}*/

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when input position is not lower than the capacity.
/// </summary>
QTEST_CASE ( Constructor_AssertionFailsWhenInputPositionIsNotLowerThanCapacity_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    const pointer_uint_q CAPACITY = HASHTABLE.GetCapacity();
    const unsigned int INVALID_POSITION = CAPACITY;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator INVALID_ITERATOR(&HASHTABLE, INVALID_POSITION);
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
/// Checks that the iterator points to the end position (forward iteration) when using an invalid position.
/// </summary>
QTEST_CASE ( Constructor_IteratorPointsToForwardEndPositionWhenUsingInvalidPosition_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    const pointer_uint_q NUMBER_OF_ELEMENTS = HASHTABLE.GetCount();

    const unsigned int INVALID_POSITION = NUMBER_OF_ELEMENTS;
    const bool IS_END = true;

	// [Execution]
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator INVALID_ITERATOR(&HASHTABLE, INVALID_POSITION);

    // [Verification]
    bool bIsEndIterationForward = INVALID_ITERATOR.IsEnd(EQIterationDirection::E_Forward);
    BOOST_CHECK_EQUAL(bIsEndIterationForward, IS_END);
}

/// <summary>
/// Checks that the iterator points to the end position (forward iteration) when using an empty hashtable.
/// </summary>
QTEST_CASE ( Constructor_IteratorPointsToForwardEndPositionWhenUsingEmptyHashtable_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(3);
    const bool IS_END = true;

	// [Execution]
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iterator(&HASHTABLE, 0);

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
    using Kinesis::QuimeraEngine::Tools::Containers::QKeyValuePair;

    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    const string_q EXPECTED_KEY("key1");
    const int EXPECTED_VALUE = 1;
    HASHTABLE.Add(EXPECTED_KEY, EXPECTED_VALUE);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);
    
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR(&HASHTABLE, 0);
    ITERATOR.MoveFirst();

	// [Execution]
    QKeyValuePair<string_q, int> value = *ITERATOR;

    // [Verification]
    BOOST_CHECK(value.GetKey() == EXPECTED_KEY);
    BOOST_CHECK(value.GetValue() == EXPECTED_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is pointing to the end position (forward iteration).
/// </summary>
QTEST_CASE ( OperatorIndirection_AssertionFailsWhenIteratorPointsToForwardEndPosition_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR(&HASHTABLE, 0);
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
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR(&HASHTABLE, 0);
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
/* [TODO] Thund: Uncomment when GetFirst exists
/// <summary>
/// Checks that the element pointed to by the iterator is returned.
/// </summary>
QTEST_CASE ( OperatorDereferencing_ReturnsTheCorrespondingElement_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(7);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    const string_q EXPECTED_KEY("key1");
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR = HASHTABLE.GetFirst();
    ++ITERATOR;

	// [Execution]
    string_q strKey = ITERATOR->GetKey();

    // [Verification]
    BOOST_CHECK(strKey == EXPECTED_KEY);
}*/

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is pointing to the end position (forward iteration).
/// </summary>
QTEST_CASE ( OperatorDereferencing_AssertionFailsWhenIteratorPointsToForwardEndPosition_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR(&HASHTABLE, 0);
    ITERATOR.MoveLast();
    ++ITERATOR;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ITERATOR->GetKey();
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
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR(&HASHTABLE, 0);
    ITERATOR.MoveFirst();
    --ITERATOR;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ITERATOR->GetKey();
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
    const string_q SECOND_ELEMENT_KEY("key2");
    const int SECOND_ELEMENT_VALUE = 2;
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add(SECOND_ELEMENT_KEY, SECOND_ELEMENT_VALUE);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ORIGINAL_ITERATOR(&HASHTABLE, 0);
    ORIGINAL_ITERATOR.MoveFirst();

	// [Execution]
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iterator(ORIGINAL_ITERATOR);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iteratorPreviousState = iterator++;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(iterator->GetKey() == SECOND_ELEMENT_KEY);
    BOOST_CHECK(iterator->GetValue() == SECOND_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the iterator points to the first position and returns the previous state when it was pointing to the end position before the first one.
/// </summary>
QTEST_CASE ( OperatorPostIncrement_IteratorPointsToFirstPositionAndReturnsPreviousStateWhenItWasPointingToPositionBeforeFirst_Test )
{
    // [Preparation]
    const string_q FIRST_ELEMENT_KEY("key1");
    const int FIRST_ELEMENT_VALUE = 1;
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ORIGINAL_ITERATOR(&HASHTABLE, 0);
    ORIGINAL_ITERATOR.MoveFirst();
    --ORIGINAL_ITERATOR;

	// [Execution]
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iterator(ORIGINAL_ITERATOR);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iteratorPreviousState = iterator++;
    string_q strCurrentElementKey = iterator->GetKey();
    int nCurrentElementValue = iterator->GetValue();

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(strCurrentElementKey == FIRST_ELEMENT_KEY);
    BOOST_CHECK(nCurrentElementValue == FIRST_ELEMENT_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position.
/// </summary>
QTEST_CASE ( OperatorPostIncrement_AssertionFailsWhenIteratorAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_END(&HASHTABLE, 0);
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
/// Checks that the iterator does not change when it already points to the end position.
/// </summary>
QTEST_CASE ( OperatorPostIncrement_IteratorDoesNotChangeWhenItAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE ;
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_END(&HASHTABLE, 0);
    ITERATOR_END.MoveLast();
    ++ITERATOR_END;

	// [Execution]
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iterator(ITERATOR_END);
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
    const string_q SECOND_ELEMENT_KEY("key2");
    const int SECOND_ELEMENT_VALUE = 2;
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add(SECOND_ELEMENT_KEY, SECOND_ELEMENT_VALUE);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ORIGINAL_ITERATOR(&HASHTABLE, 0);
    ORIGINAL_ITERATOR.MoveLast();

	// [Execution]
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iterator(ORIGINAL_ITERATOR);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iteratorPreviousState = iterator--;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(iterator->GetKey() == SECOND_ELEMENT_KEY);
    BOOST_CHECK(iterator->GetValue() == SECOND_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the iterator points to the last position and returns the previous state when it was pointing to the end position after the last one, when using depth-first in-order.
/// </summary>
QTEST_CASE ( OperatorPostDecrement_IteratorPointsToLastPositionAndReturnsPreviousStateWhenItWasPointingToLastEndPositionUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const string_q LAST_ELEMENT_KEY("key3");
    const int LAST_ELEMENT_VALUE = 3;
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ORIGINAL_ITERATOR(&HASHTABLE, 0);
    ORIGINAL_ITERATOR.MoveLast();
    ++ORIGINAL_ITERATOR;

	// [Execution]
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iterator(ORIGINAL_ITERATOR);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iteratorPreviousState = iterator--;
    string_q strCurrentElementKey = iterator->GetKey();
    int nCurrentElementValue = iterator->GetValue();

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(strCurrentElementKey == LAST_ELEMENT_KEY);
    BOOST_CHECK(nCurrentElementValue == LAST_ELEMENT_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position before the first one.
/// </summary>
QTEST_CASE ( OperatorPostDecrement_AssertionFailsWhenIteratorAlreadyPointsToEndPositionBeforeFirst_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_END(&HASHTABLE, 0);
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
/// Checks that the iterator does not change when it already points to the end position.
/// </summary>
QTEST_CASE ( OperatorPostDecrement_IteratorDoesNotChangeWhenItAlreadyPointsToEndPositionBeforeFirst_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE = GetSampleHashtable();
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_END(&HASHTABLE, 0);
    ITERATOR_END.MoveFirst();
    --ITERATOR_END;

	// [Execution]
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iterator(ITERATOR_END);
    iterator--;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_END);
}

#endif
/* [TODO] Thund: Uncomment when GetFirst exists
/// <summary>
/// Checks that the iterator steps forward properly and returns the current state, when using depth-first in-order.
/// </summary>
QTEST_CASE ( OperatorPreIncrement_CommonIteratorStepsForwardProperlyAndReturnsCurrentStateWhenUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const string_q SECOND_ELEMENT_KEY("key2");
    const int SECOND_ELEMENT_VALUE = 2;
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ORIGINAL_ITERATOR = HASHTABLE.GetFirst();

	// [Execution]
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iterator(ORIGINAL_ITERATOR);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iteratorPreviousState = ++iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == iterator);
    BOOST_CHECK(iterator->GetKey() == SECOND_ELEMENT_KEY);
    BOOST_CHECK(iterator->GetValue() == SECOND_ELEMENT_VALUE);
}
*/

/// <summary>
/// Checks that the iterator points to the first position and returns the current state when it was pointing to the end position before the first one.
/// </summary>
QTEST_CASE ( OperatorPreIncrement_IteratorPointsToFirstPositionAndReturnsCurrentStateWhenItWasPointingToPositionBeforeFirstU_Test )
{
    // [Preparation]
    const string_q FIRST_ELEMENT_KEY("key1");
    const int FIRST_ELEMENT_VALUE = 1;
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add(FIRST_ELEMENT_KEY, FIRST_ELEMENT_VALUE);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ORIGINAL_ITERATOR(&HASHTABLE, 0);
    ORIGINAL_ITERATOR.MoveFirst();
    --ORIGINAL_ITERATOR;

	// [Execution]
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iterator(ORIGINAL_ITERATOR);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iteratorPreviousState = ++iterator;
    string_q strCurrentElementValue = iterator->GetKey();
    string_q strCurrentElementKey = iterator->GetKey();
    int nCurrentElementValue = iterator->GetValue();

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == iterator);
    BOOST_CHECK(strCurrentElementKey == FIRST_ELEMENT_KEY);
    BOOST_CHECK(nCurrentElementValue == FIRST_ELEMENT_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position.
/// </summary>
QTEST_CASE ( OperatorPreIncrement_AssertionFailsWhenIteratorAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_END(&HASHTABLE, 0);
    ITERATOR_END.MoveLast();
    ITERATOR_END++;

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
/// Checks that the iterator does not change when it already points to the end position.
/// </summary>
QTEST_CASE ( OperatorPreIncrement_IteratorDoesNotChangeWhenItAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_END(&HASHTABLE, 0);
    ITERATOR_END.MoveLast();
    ITERATOR_END++;

	// [Execution]
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iterator(ITERATOR_END);
    ++iterator;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_END);
}

#endif
/* [TODO] Thund: Uncomment when GetFirst exists
/// <summary>
/// Checks that the iterator steps backward properly and returns the current state.
/// </summary>
QTEST_CASE ( OperatorPreDecrement_CommonIteratorStepsBackwardProperlyAndReturnsCurrentState_Test )
{
    // [Preparation]
    const string_q SECOND_ELEMENT_KEY("key2");
    const int SECOND_ELEMENT_VALUE = 2;
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add(SECOND_ELEMENT_KEY, SECOND_ELEMENT_VALUE);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ORIGINAL_ITERATOR = HASHTABLE.GetLast();

	// [Execution]
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iterator(ORIGINAL_ITERATOR);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iteratorPreviousState = --iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == iterator);
    BOOST_CHECK(iterator->GetKey() == SECOND_ELEMENT_KEY);
    BOOST_CHECK(iterator->GetValue() == SECOND_ELEMENT_VALUE);
}
*//* [TODO] Thund: Uncomment when GetFirst exists
/// <summary>
/// Checks that the iterator points to the last position and returns the current state when it was pointing to the end position after the last one.
/// </summary>
QTEST_CASE ( OperatorPreDecrement_IteratorPointsToLastPositionAndReturnsCurrentStateWhenItWasPointingToLastEndPosition_Test )
{
    // [Preparation]
    const string_q LAST_ELEMENT_KEY("key3");
    const int LAST_ELEMENT_VALUE = 3;
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ORIGINAL_ITERATOR = HASHTABLE.GetLast();
    ORIGINAL_ITERATOR++;

	// [Execution]
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iterator(ORIGINAL_ITERATOR);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iteratorPreviousState = --iterator;
    string_q strCurrentElementKey = iterator->GetKey();
    int nCurrentElementValue = iterator->GetValue();

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == iterator);
    BOOST_CHECK(strCurrentElementKey == LAST_ELEMENT_KEY);
    BOOST_CHECK(nCurrentElementValue == LAST_ELEMENT_VALUE);
}
*/

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position before the first one.
/// </summary>
QTEST_CASE ( OperatorPreDecrement_AssertionFailsWhenIteratorAlreadyPointsToEndPositionBeforeFirst_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_END(&HASHTABLE, 0);
    ITERATOR_END.MoveFirst();
    ITERATOR_END--;

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
/// Checks that the iterator does not change when it already points to the end position.
/// </summary>
QTEST_CASE ( OperatorPreDecrement_IteratorDoesNotChangeWhenItAlreadyPointsToEndPositionBeforeFirst_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_END(&HASHTABLE, 0);
    ITERATOR_END.MoveFirst();
    ITERATOR_END--;

	// [Execution]
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iterator(ITERATOR_END);
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
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_A(&HASHTABLE, 0);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_B(&HASHTABLE, 0);
    ++ITERATOR_A;

	// [Execution]
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iterator = ITERATOR_B;
    iterator = ITERATOR_A;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_A);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different hashtable.
/// </summary>
QTEST_CASE ( OperatorAssignment_AssertionFailsWhenInputIteratorPointsToDifferentHashtable_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE_A(10, 2);
    HASHTABLE_A.Add("key1", 1);
    HASHTABLE_A.Add("key2", 2);
    HASHTABLE_A.Add("key3", 3);
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE_B(10, 2);
    HASHTABLE_B.Add("key1", 1);
    HASHTABLE_B.Add("key2", 2);
    HASHTABLE_B.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_A(&HASHTABLE_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iterator(&HASHTABLE_B, 0);
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
/// Checks that the iterator is not copied when it points to a different hashtable.
/// </summary>
QTEST_CASE ( OperatorAssignment_IteratorDoesNotChangeIfInputIteratorPointsToDifferentHashtable_Test )
{
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE_A(3);
    HASHTABLE_A.Add("key1", 1);
    HASHTABLE_A.Add("key2", 2);
    HASHTABLE_A.Add("key3", 3);
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE_B(10, 2);
    HASHTABLE_B.Add("key1", 1);
    HASHTABLE_B.Add("key2", 2);
    HASHTABLE_B.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_A(&HASHTABLE_A, 0);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_B(&HASHTABLE_B, 0);

	// [Execution]
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iterator = ITERATOR_B;
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
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_A(&HASHTABLE, 0);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_B(&HASHTABLE, 0);
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
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_A(&HASHTABLE, 0);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_B(&HASHTABLE, 0);
    ++ITERATOR_B;

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A == ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different hashtable.
/// </summary>
QTEST_CASE ( OperatorEquality_AssertionFailsWhenIteratorsPointToDifferentDictionaries_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE_A(10, 2);
    HASHTABLE_A.Add("key1", 1);
    HASHTABLE_A.Add("key2", 2);
    HASHTABLE_A.Add("key3", 3);
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE_B(10, 2);
    HASHTABLE_B.Add("key1", 1);
    HASHTABLE_B.Add("key2", 2);
    HASHTABLE_B.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_A(&HASHTABLE_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iterator(&HASHTABLE_B, 0);
        iterator == ITERATOR_A;
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
/// Checks that it returns False when iterators point to a different hashtable.
/// </summary>
QTEST_CASE ( OperatorEquality_ReturnsFalseWhenIteratorsPointToDifferentDictionaries_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE_A(3);
    HASHTABLE_A.Add("key1", 1);
    HASHTABLE_A.Add("key2", 2);
    HASHTABLE_A.Add("key3", 3);
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE_B(10, 2);
    HASHTABLE_B.Add("key1", 1);
    HASHTABLE_B.Add("key2", 2);
    HASHTABLE_B.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_A(&HASHTABLE_A, 0);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_B(&HASHTABLE_B, 0);
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
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_A(&HASHTABLE, 0);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_B(&HASHTABLE, 0);
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
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_A(&HASHTABLE, 0);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_B(&HASHTABLE, 0);
    ++ITERATOR_B;

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_A != ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different hashtable.
/// </summary>
QTEST_CASE ( OperatorInequality_AssertionFailsWhenIteratorsPointToDifferentDictionaries_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE_A(10, 2);
    HASHTABLE_A.Add("key1", 1);
    HASHTABLE_A.Add("key2", 2);
    HASHTABLE_A.Add("key3", 3);
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE_B(10, 2);
    HASHTABLE_B.Add("key1", 1);
    HASHTABLE_B.Add("key2", 2);
    HASHTABLE_B.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_A(&HASHTABLE_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iterator(&HASHTABLE_B, 0);
        iterator != ITERATOR_A;
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
/// Checks that it returns True when iterators point to a different hashtable.
/// </summary>
QTEST_CASE ( OperatorInequality_ReturnsTrueWhenIteratorsPointToDifferentDictionaries_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE_A(3);
    HASHTABLE_A.Add("key1", 1);
    HASHTABLE_A.Add("key2", 2);
    HASHTABLE_A.Add("key3", 3);
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE_B(10, 2);
    HASHTABLE_B.Add("key1", 1);
    HASHTABLE_B.Add("key2", 2);
    HASHTABLE_B.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_A(&HASHTABLE_A, 0);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_B(&HASHTABLE_B, 0);
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
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_A(&HASHTABLE, 0);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_B(&HASHTABLE, 0);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B > ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident iterator is not greater than the input iterator, using depth-first in-order.
/// </summary>
QTEST_CASE ( OperatorGreaterThan_ReturnsFalseWhenResidentIteratorIsNotGreaterThanInputIteratorUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_A(&HASHTABLE, 0);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_B(&HASHTABLE, 0);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A > ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different hashtable.
/// </summary>
QTEST_CASE ( OperatorGreaterThan_AssertionFailsWhenIteratorsPointToDifferentDictionaries_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE_A(10, 2);
    HASHTABLE_A.Add("key1", 1);
    HASHTABLE_A.Add("key2", 2);
    HASHTABLE_A.Add("key3", 3);
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE_B(10, 2);
    HASHTABLE_B.Add("key1", 1);
    HASHTABLE_B.Add("key2", 2);
    HASHTABLE_B.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_A(&HASHTABLE_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iterator(&HASHTABLE_B, 0);
        iterator > ITERATOR_A;
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
/// Checks that it returns False when iterators point to a different hashtable.
/// </summary>
QTEST_CASE ( OperatorGreaterThan_ReturnsFalseWhenIteratorsPointToDifferentDictionaries_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE_A(10, 2);
    HASHTABLE_A.Add("key1", 1);
    HASHTABLE_A.Add("key2", 2);
    HASHTABLE_A.Add("key3", 3);
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE_B(10, 2);
    HASHTABLE_B.Add("key1", 1);
    HASHTABLE_B.Add("key2", 2);
    HASHTABLE_B.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_A(&HASHTABLE_A, 0);
    ++ITERATOR_A;
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_B(&HASHTABLE_B, 0);
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
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_A(&HASHTABLE, 0);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_B(&HASHTABLE, 0);
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
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_A(&HASHTABLE, 0);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_B(&HASHTABLE, 0);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_B < ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different hashtable.
/// </summary>
QTEST_CASE ( OperatorLowerThan_AssertionFailsWhenIteratorsPointToDifferentDictionaries_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE_A(10, 2);
    HASHTABLE_A.Add("key1", 1);
    HASHTABLE_A.Add("key2", 2);
    HASHTABLE_A.Add("key3", 3);
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE_B(10, 2);
    HASHTABLE_B.Add("key1", 1);
    HASHTABLE_B.Add("key2", 2);
    HASHTABLE_B.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_A(&HASHTABLE_A, 0);
    ++ITERATOR_A;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iterator(&HASHTABLE_B, 0);
        iterator < ITERATOR_A;
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
/// Checks that it returns False when iterators point to a different hashtable.
/// </summary>
QTEST_CASE ( OperatorLowerThan_ReturnsFalseWhenIteratorsPointToDifferentDictionaries_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE_A(10, 2);
    HASHTABLE_A.Add("key1", 1);
    HASHTABLE_A.Add("key2", 2);
    HASHTABLE_A.Add("key3", 3);
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE_B(10, 2);
    HASHTABLE_B.Add("key1", 1);
    HASHTABLE_B.Add("key2", 2);
    HASHTABLE_B.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_A(&HASHTABLE_A, 0);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_B(&HASHTABLE_B, 0);
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
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_A(&HASHTABLE, 0);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_B(&HASHTABLE, 0);
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
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_A(&HASHTABLE, 0);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_B(&HASHTABLE, 0);
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
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_A(&HASHTABLE, 0);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_B(&HASHTABLE, 0);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A >= ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different hashtable.
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_AssertionFailsWhenIteratorsPointToDifferentDictionaries_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE_A(10, 2);
    HASHTABLE_A.Add("key1", 1);
    HASHTABLE_A.Add("key2", 2);
    HASHTABLE_A.Add("key3", 3);
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE_B(10, 2);
    HASHTABLE_B.Add("key1", 1);
    HASHTABLE_B.Add("key2", 2);
    HASHTABLE_B.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_A(&HASHTABLE_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iterator(&HASHTABLE_B, 0);
        iterator >= ITERATOR_A;
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
/// Checks that it returns False when iterators point to a different hashtable.
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsFalseWhenIteratorsPointToDifferentDictionaries_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE_A(10, 2);
    HASHTABLE_A.Add("key1", 1);
    HASHTABLE_A.Add("key2", 2);
    HASHTABLE_A.Add("key3", 3);
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE_B(10, 2);
    HASHTABLE_B.Add("key1", 1);
    HASHTABLE_B.Add("key2", 2);
    HASHTABLE_B.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_A(&HASHTABLE_A, 0);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_B(&HASHTABLE_B, 0);
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
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_A(&HASHTABLE, 0);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_B(&HASHTABLE, 0);
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
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_A(&HASHTABLE, 0);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_B(&HASHTABLE, 0);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B <= ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident iterator is neither lower than nor equals to the input iterator.
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_ReturnsFalseWhenResidentIteratorIsNotLowerThanAndDoNotEqualsInputIterator_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_A(&HASHTABLE, 0);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_B(&HASHTABLE, 0);
    ++ITERATOR_A;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A <= ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different hashtable.
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_AssertionFailsWhenIteratorsPointToDifferentDictionaries_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE_A(10, 2);
    HASHTABLE_A.Add("key1", 1);
    HASHTABLE_A.Add("key2", 2);
    HASHTABLE_A.Add("key3", 3);
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE_B(10, 2);
    HASHTABLE_B.Add("key1", 1);
    HASHTABLE_B.Add("key2", 2);
    HASHTABLE_B.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_A(&HASHTABLE_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iterator(&HASHTABLE_B, 0);
        iterator <= ITERATOR_A;
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
/// Checks that it returns False when iterators point to a different hashtable.
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_ReturnsFalseWhenIteratorsPointToDifferentDictionaries_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE_A(10, 2);
    HASHTABLE_A.Add("key1", 1);
    HASHTABLE_A.Add("key2", 2);
    HASHTABLE_A.Add("key3", 3);
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE_B(10, 2);
    HASHTABLE_B.Add("key1", 1);
    HASHTABLE_B.Add("key2", 2);
    HASHTABLE_B.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_A(&HASHTABLE_A, 0);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_B(&HASHTABLE_B, 0);
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
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR(&HASHTABLE, 0);
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
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR(&HASHTABLE, 0);
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
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR(&HASHTABLE, 0);
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
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR(&HASHTABLE, 0);
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
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR(&HASHTABLE, 0);
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
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR(&HASHTABLE, 0);
    ITERATOR.MoveLast();

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR.IsEnd(EQIterationDirection::E_Backward);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the iterator points to the first position when the hashtable is not empty.
/// </summary>
QTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenHashtableIsNotEmpty_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ORIGINAL_ITERATOR(&HASHTABLE, 0);
    ++ORIGINAL_ITERATOR;
    ++ORIGINAL_ITERATOR;
    ++ORIGINAL_ITERATOR;
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_FIRST(&HASHTABLE, 0);

	// [Execution]
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveFirst();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_FIRST);
}

/// <summary>
/// Checks that the iterator points to the first position even when it was pointing to the position before the first.
/// </summary>
QTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenHashtableIsNotEmptyAndIteratorWasPointingToPositionBeforeFirst_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ORIGINAL_ITERATOR(&HASHTABLE, 0);
    --ORIGINAL_ITERATOR;

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_FIRST(&HASHTABLE, 0);

	// [Execution]
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveFirst();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_FIRST);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator points to the end position when the hashtable is empty.
/// </summary>
QTEST_CASE ( MoveFirst_IteratorPointsToEndPositionWhenHashtableIsEmpty_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> EMPTY_HASHTABLE(1);
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator END_ITERATOR(&EMPTY_HASHTABLE, 0);
    END_ITERATOR.MoveLast();
    ++END_ITERATOR;
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR(&EMPTY_HASHTABLE, 0);

	// [Execution]
    ITERATOR.MoveFirst();

    // [Verification]
    BOOST_CHECK(ITERATOR == END_ITERATOR);
}

#endif

/// <summary>
/// Checks that the iterator points to the last position when the hashtable is not empty.
/// </summary>
QTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenHashtableIsNotEmpty_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ORIGINAL_ITERATOR(&HASHTABLE, 0);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_LAST(&HASHTABLE, 0);
    while(!ITERATOR_LAST.IsEnd())
        ++ITERATOR_LAST;
    --ITERATOR_LAST;

	// [Execution]
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveLast();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_LAST);
}

/// <summary>
/// Checks that the iterator points to the last position even when it was pointing to the position before the first.
/// </summary>
QTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenHashtableIsNotEmptyAndIteratorWasPointingToPositionBeforeFirst_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ORIGINAL_ITERATOR(&HASHTABLE, 0);
    --ORIGINAL_ITERATOR;

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR_LAST(&HASHTABLE, 0);
    while(!ITERATOR_LAST.IsEnd())
        ++ITERATOR_LAST;
    --ITERATOR_LAST;

	// [Execution]
    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveLast();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_LAST);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator points to the end position when the hashtable is empty.
/// </summary>
QTEST_CASE ( MoveLast_IteratorPointsToEndPositionWhenHashtableIsEmpty_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> EMPTY_HASHTABLE(1);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator END_ITERATOR(&EMPTY_HASHTABLE, 0);
    END_ITERATOR.MoveLast();
    ++END_ITERATOR;

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR(&EMPTY_HASHTABLE, 0);

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
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(10, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator ITERATOR(&HASHTABLE, 0);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR.IsValid();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

// End - Test Suite: QConstHashtableIterator
QTEST_SUITE_END()
