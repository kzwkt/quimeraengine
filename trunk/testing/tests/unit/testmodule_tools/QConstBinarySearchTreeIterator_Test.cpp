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

#include "QBinarySearchTree.h"

#include "QConstBinarySearchTreeIteratorMock.h"

using Kinesis::QuimeraEngine::Tools::Containers::QBinarySearchTree;
using Kinesis::QuimeraEngine::Tools::Containers::EQTreeTraversalOrder;
using Kinesis::QuimeraEngine::Tools::Containers::Test::QConstBinarySearchTreeIteratorMock;

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

QTEST_SUITE_BEGIN( QConstBinarySearchTreeIterator_TestSuite )

/// <summary>
/// Gets a sample tree with which to perform some tests.
/// </summary>
/// <returns>
/// A sample tree with a variety of nodes.
/// </returns>
static const QBinarySearchTree<int>* GetSampleTree()
{
    static QBinarySearchTree<int> sampleTree(7);
    static bool bInitialized = false;

    if(!bInitialized)
    {
        //         4
        //       /   \
        //      /     \
        //     2       6
        //    / \     / \
        //   /   \   /   \
        //  1     3 5     7
        sampleTree.Add(4, EQTreeTraversalOrder::E_DepthFirstInOrder);
        sampleTree.Add(2, EQTreeTraversalOrder::E_DepthFirstInOrder);
        sampleTree.Add(1, EQTreeTraversalOrder::E_DepthFirstInOrder);
        sampleTree.Add(3, EQTreeTraversalOrder::E_DepthFirstInOrder);
        sampleTree.Add(6, EQTreeTraversalOrder::E_DepthFirstInOrder);
        sampleTree.Add(5, EQTreeTraversalOrder::E_DepthFirstInOrder);
        sampleTree.Add(7, EQTreeTraversalOrder::E_DepthFirstInOrder);

        bInitialized = true;
    }

    return &sampleTree;
}

/// <summary>
/// Creates a sample tree using an external tree.
/// </summary>
/// <param name="inputTree">An empty tree.</param>
static void BuildSampleTree(QBinarySearchTree<int> &inputTree)
{
    //         4
    //       /   \
    //      /     \
    //     2       6
    //    / \     / \
    //   /   \   /   \
    //  1     3 5     7
    inputTree.Add(4, EQTreeTraversalOrder::E_DepthFirstInOrder);
    inputTree.Add(2, EQTreeTraversalOrder::E_DepthFirstInOrder);
    inputTree.Add(1, EQTreeTraversalOrder::E_DepthFirstInOrder);
    inputTree.Add(3, EQTreeTraversalOrder::E_DepthFirstInOrder);
    inputTree.Add(6, EQTreeTraversalOrder::E_DepthFirstInOrder);
    inputTree.Add(5, EQTreeTraversalOrder::E_DepthFirstInOrder);
    inputTree.Add(7, EQTreeTraversalOrder::E_DepthFirstInOrder);
}


/// <summary>
/// Checks that the iterator points to the given position when using a common tree and depth-first in-order traversal order.
/// </summary>
QTEST_CASE ( Constructor_IteratorPointsToGivenPositionWhenUsingCommonTreeAndDepthFirstInOrder_Test )
{/* [TODO] Thund: Uncomment when the method AddChild exists
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();
    const pointer_uint_q POSITION = 2;
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator EXPECTED_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    EXPECTED_ITERATOR.MoveFirst();
    ++EXPECTED_ITERATOR;

	// [Execution]
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(SAMPLE_TREE, POSITION, EQTreeTraversalOrder::E_DepthFirstInOrder);
    
    // [Verification]
    BOOST_CHECK(iterator == EXPECTED_ITERATOR);*/
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when input tree is null.
/// </summary>
QTEST_CASE ( Constructor_AssertionFailsWhenInputTreeIsNull_Test )
{
    // [Preparation]
    QBinarySearchTree<int>* SOURCE_TREE = null_q;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QBinarySearchTree<int>::QConstBinarySearchTreeIterator INVALID_ITERATOR(SOURCE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
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
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    const pointer_uint_q CAPACITY = SAMPLE_TREE->GetCapacity();
    const unsigned int INVALID_POSITION = CAPACITY;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QBinarySearchTree<int>::QConstBinarySearchTreeIterator INVALID_ITERATOR(SAMPLE_TREE, INVALID_POSITION, EQTreeTraversalOrder::E_DepthFirstInOrder);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when input traversal order is not supported.
/// </summary>
QTEST_CASE ( Constructor_AssertionFailsWhenInputTraversalOrderIsNotSupported_Test )
{
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();
    const EQTreeTraversalOrder UNSUPPORTED_TRAVERSAL_ORDER = EQTreeTraversalOrder::_NotEnumValue;
    const unsigned int INPUT_POSITION = 0;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QBinarySearchTree<int>::QConstBinarySearchTreeIterator INVALID_ITERATOR(SAMPLE_TREE, INPUT_POSITION, UNSUPPORTED_TRAVERSAL_ORDER);
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
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    const pointer_uint_q NUMBER_OF_ELEMENTS = SAMPLE_TREE->GetCount();

    const unsigned int INVALID_POSITION = NUMBER_OF_ELEMENTS;
    const bool IS_END = true;

	// [Execution]
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator INVALID_ITERATOR(SAMPLE_TREE, INVALID_POSITION, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    bool bIsEndIterationForward = INVALID_ITERATOR.IsEnd(EQIterationDirection::E_Forward);
    BOOST_CHECK_EQUAL(bIsEndIterationForward, IS_END);
}

/// <summary>
/// Checks that the iterator points to the end position (forward iteration) when using an empty tree.
/// </summary>
QTEST_CASE ( Constructor_IteratorPointsToForwardEndPositionWhenUsingEmptyTree_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const QBinarySearchTree<int> SOURCE_TREE(3);
    const bool IS_END = true;

	// [Execution]
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(&SOURCE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

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
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    const int EXPECTED_VALUE = 1;
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ITERATOR.MoveFirst();

	// [Execution]
    int value = *ITERATOR;

    // [Verification]
    BOOST_CHECK_EQUAL(value, EXPECTED_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorIndirection_AssertionFailsWhenIteratorIsInvalid_Test )
{
    // [Preparation]
    QBinarySearchTree<int> SAMPLE_TREE(8);
    BuildSampleTree(SAMPLE_TREE);

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator FIRST_POSITION(&SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder); 
    QConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(&SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE.GetCapacity());
    
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
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
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
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
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
    QBinarySearchTree<TestStructure> SAMPLE_TREE(7);
    SAMPLE_TREE.Add(TestStructure(4), EQTreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(2), EQTreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(1), EQTreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(3), EQTreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(6), EQTreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(5), EQTreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(7), EQTreeTraversalOrder::E_DepthFirstInOrder);

    const int EXPECTED_VALUE = 2;
    QBinarySearchTree<TestStructure>::QConstBinarySearchTreeIterator ITERATOR = SAMPLE_TREE.GetFirst(EQTreeTraversalOrder::E_DepthFirstInOrder);
    ++ITERATOR;

	// [Execution]
    int value = ITERATOR->m_field;

    // [Verification]
    BOOST_CHECK_EQUAL(value, EXPECTED_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorDereferencing_AssertionFailsWhenIteratorIsInvalid_Test )
{
    // [Preparation]
    QBinarySearchTree<TestStructure> SAMPLE_TREE(7);
    SAMPLE_TREE.Add(TestStructure(4), EQTreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(2), EQTreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(1), EQTreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(3), EQTreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(6), EQTreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(5), EQTreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(7), EQTreeTraversalOrder::E_DepthFirstInOrder);

    QBinarySearchTree<TestStructure>::QConstBinarySearchTreeIterator FIRST_POSITION(&SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder); 
    QConstBinarySearchTreeIteratorMock<TestStructure> INVALID_ITERATOR(&SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE.GetCapacity());
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        INVALID_ITERATOR->m_field;
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
    QBinarySearchTree<TestStructure> SAMPLE_TREE(7);
    SAMPLE_TREE.Add(TestStructure(4), EQTreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(2), EQTreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(1), EQTreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(3), EQTreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(6), EQTreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(5), EQTreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(7), EQTreeTraversalOrder::E_DepthFirstInOrder);

    QBinarySearchTree<TestStructure>::QConstBinarySearchTreeIterator ITERATOR(&SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ITERATOR.MoveLast();
    ++ITERATOR;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ITERATOR->m_field;
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
    QBinarySearchTree<TestStructure> SAMPLE_TREE(7);
    SAMPLE_TREE.Add(TestStructure(4), EQTreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(2), EQTreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(1), EQTreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(3), EQTreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(6), EQTreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(5), EQTreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(7), EQTreeTraversalOrder::E_DepthFirstInOrder);

    QBinarySearchTree<TestStructure>::QConstBinarySearchTreeIterator ITERATOR(&SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ITERATOR.MoveFirst();
    --ITERATOR;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ITERATOR->m_field;
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
/// Checks that the iterator steps forward properly and returns the previous state when using depth-first in-order.
/// </summary>
QTEST_CASE ( OperatorPostIncrement_CommonIteratorStepsForwardProperlyAndReturnsPreviousStateWhenUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const int SECOND_ELEMENT_VALUE = 2;
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ORIGINAL_ITERATOR.MoveFirst();

	// [Execution]
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(ORIGINAL_ITERATOR);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iteratorPreviousState = iterator++;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(*iterator == SECOND_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the tree is traversed in the correct order when using depth-first in-order.
/// </summary>
QTEST_CASE ( OperatorPostIncrement_TreeIsTraversedInCorrectOrderWhenUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5, 6, 7};
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    iterator.MoveFirst();
    bool bIsCorrect = true;
    unsigned int i = 0;

	// [Execution]
    while(bIsCorrect && !iterator.IsEnd())
    {
        bIsCorrect = bIsCorrect && ELEMENT_VALUES[i] == *iterator;
        iterator++;
        i++;
    }

    // [Verification]
    BOOST_CHECK(bIsCorrect);
}

/// <summary>
/// Checks that the iterator points to the first position and returns the previous state when it was pointing to the end position before the first one, using depth-first in-order.
/// </summary>
QTEST_CASE ( OperatorPostIncrement_IteratorPointsToFirstPositionAndReturnsPreviousStateWhenItWasPointingToPositionBeforeFirstUsingDepthFirstInOrder_Test )
{/* [TODO] Thund: Uncomment when the method AddChild exists
    // [Preparation]
    const int FIRST_ELEMENT_VALUE = 1;
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ORIGINAL_ITERATOR.MoveFirst();
    --ORIGINAL_ITERATOR;

	// [Execution]
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(ORIGINAL_ITERATOR);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iteratorPreviousState = iterator++;
    int nCurrentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(nCurrentElement == FIRST_ELEMENT_VALUE);*/
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorPostIncrement_AssertionFailsWhenIteratorIsNotValid_Test )
{/* [TODO] Thund: Uncomment when the method AddChild exists
    // [Preparation]
    QBinarySearchTree<int> SAMPLE_TREE(7);
    BuildSampleTree(SAMPLE_TREE);

    QConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(&SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE.GetCapacity());
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
{/* [TODO] Thund: Uncomment when the method AddChild exists
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_END(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
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
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);*/
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator does not change when it already points to the end position.
/// </summary>
QTEST_CASE ( OperatorPostIncrement_IteratorDoesNotChangeWhenItAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_END(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ITERATOR_END.MoveLast();
    ++ITERATOR_END;

	// [Execution]
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(ITERATOR_END);
    iterator++;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_END);
}

#endif

/// <summary>
/// Checks that the iterator steps backward properly and returns the previous state, when using depth-first in-order.
/// </summary>
QTEST_CASE ( OperatorPostDecrement_CommonIteratorStepsBackwardProperlyAndReturnsPreviousStateWhenUsingDepthFirstInOrder_Test )
{/* [TODO] Thund: Uncomment when the method AddChild exists
    // [Preparation]
    const int SECOND_ELEMENT_VALUE = 6;
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ORIGINAL_ITERATOR.MoveLast();

	// [Execution]
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(ORIGINAL_ITERATOR);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iteratorPreviousState = iterator--;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(*iterator == SECOND_ELEMENT_VALUE);*/
}

/// <summary>
/// Checks that the tree is traversed in the correct order when using depth-first in-order.
/// </summary>
QTEST_CASE ( OperatorPostDecrement_TreeIsTraversedInCorrectOrderWhenUsingDepthFirstInOrder_Test )
{/* [TODO] Thund: Uncomment when the method AddChild exists
    // [Preparation]
    const int ELEMENT_VALUES[] = {7, 6, 5, 4, 3, 2, 1};
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    iterator.MoveLast();
    bool bIsCorrect = true;
    unsigned int i = 0;

	// [Execution]
    while(bIsCorrect && !iterator.IsEnd())
    {
        bIsCorrect = bIsCorrect && ELEMENT_VALUES[i] == *iterator;
        iterator--;
        i++;
    }

    // [Verification]
    BOOST_CHECK(bIsCorrect);*/
}

/// <summary>
/// Checks that the iterator points to the last position and returns the previous state when it was pointing to the end position after the last one, when using depth-first in-order.
/// </summary>
QTEST_CASE ( OperatorPostDecrement_IteratorPointsToLastPositionAndReturnsPreviousStateWhenItWasPointingToLastEndPositionUsingDepthFirstInOrder_Test )
{/* [TODO] Thund: Uncomment when the method AddChild exists
    // [Preparation]
    const int LAST_ELEMENT_VALUE = 7;
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ORIGINAL_ITERATOR.MoveLast();
    ++ORIGINAL_ITERATOR;

	// [Execution]
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(ORIGINAL_ITERATOR);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iteratorPreviousState = iterator--;
    int nCurrentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(nCurrentElement == LAST_ELEMENT_VALUE);*/
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS
/* [TODO] Thund: Uncomment when the method AddChild exists
/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorPostDecrement_AssertionFailsWhenIteratorIsNotValid_Test )
{
    // [Preparation]
    QBinarySearchTree<int> SAMPLE_TREE(7);
    BuildSampleTree(SAMPLE_TREE);

    QConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(&SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE.GetCapacity());
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
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_END(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
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
}*/

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator does not change when it already points to the end position.
/// </summary>
QTEST_CASE ( OperatorPostDecrement_IteratorDoesNotChangeWhenItAlreadyPointsToEndPositionBeforeFirst_Test )
{/* [TODO] Thund: Uncomment when the method AddChild exists
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_END(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ITERATOR_END.MoveFirst();
    --ITERATOR_END;

	// [Execution]
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(ITERATOR_END);
    iterator--;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_END);*/
}

#endif
/* [TODO] Thund: Uncomment when the method AddChild exists
/// <summary>
/// Checks that the iterator steps forward properly and returns the current state, when using depth-first in-order.
/// </summary>
QTEST_CASE ( OperatorPreIncrement_CommonIteratorStepsForwardProperlyAndReturnsCurrentStateWhenUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const int SECOND_ELEMENT_VALUE = 2;
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ORIGINAL_ITERATOR.MoveFirst();

	// [Execution]
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(ORIGINAL_ITERATOR);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iteratorPreviousState = ++iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState != iterator);
    BOOST_CHECK(*iterator == SECOND_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the tree is traversed in the correct order when using depth-first in-order.
/// </summary>
QTEST_CASE ( OperatorPreIncrement_TreeIsTraversedInCorrectOrderWhenUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5, 6, 7};
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    iterator.MoveFirst();
    bool bIsCorrect = true;
    unsigned int i = 0;

	// [Execution]
    while(bIsCorrect && !iterator.IsEnd())
    {
        bIsCorrect = bIsCorrect && ELEMENT_VALUES[i] == *iterator;
        ++iterator;
        ++i;
    }

    // [Verification]
    BOOST_CHECK(bIsCorrect);
}

/// <summary>
/// Checks that the iterator points to the first position and returns the current state when it was pointing to the end position before the first one, when using depth-first in-order.
/// </summary>
QTEST_CASE ( OperatorPreIncrement_IteratorPointsToFirstPositionAndReturnsCurrentStateWhenItWasPointingToPositionBeforeFirstUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const int FIRST_ELEMENT_VALUE = 1;
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ORIGINAL_ITERATOR.MoveFirst();
    --ORIGINAL_ITERATOR;

	// [Execution]
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(ORIGINAL_ITERATOR);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iteratorPreviousState = ++iterator;
    int nCurrentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState != iterator);
    BOOST_CHECK(nCurrentElement == FIRST_ELEMENT_VALUE);
}*/

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS
/* [TODO] Thund: Uncomment when the method AddChild exists
/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorPreIncrement_AssertionFailsWhenIteratorIsNotValid_Test )
{
    // [Preparation]
    QBinarySearchTree<int> SAMPLE_TREE(7);
    BuildSampleTree(SAMPLE_TREE);

    QConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(&SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE.GetCapacity());
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
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_END(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ITERATOR_END.MoveLast();
    ITERATOR_END++;

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
*/
#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator does not change when it already points to the end position.
/// </summary>
QTEST_CASE ( OperatorPreIncrement_IteratorDoesNotChangeWhenItAlreadyPointsToLastEndPosition_Test )
{/* [TODO] Thund: Uncomment when the method AddChild exists
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_END(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ITERATOR_END.MoveLast();
    ITERATOR_END++;

	// [Execution]
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(ITERATOR_END);
    ++iterator;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_END);*/
}

#endif
/* [TODO] Thund: Uncomment when the method AddChild exists
/// <summary>
/// Checks that the iterator steps backward properly and returns the current state, when using depth-first in-order.
/// </summary>
QTEST_CASE ( OperatorPreDecrement_CommonIteratorStepsBackwardProperlyAndReturnsCurrentStateWhenUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const int SECOND_ELEMENT_VALUE = 6;
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ORIGINAL_ITERATOR.MoveLast();

	// [Execution]
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(ORIGINAL_ITERATOR);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iteratorPreviousState = --iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState != iterator);
    BOOST_CHECK(*iterator == SECOND_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the iterator points to the last position and returns the current state when it was pointing to the end position after the last one, when using depth-first in-order.
/// </summary>
QTEST_CASE ( OperatorPreDecrement_IteratorPointsToLastPositionAndReturnsCurrentStateWhenItWasPointingToLastEndPositionUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const int LAST_ELEMENT_VALUE = 7;
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ORIGINAL_ITERATOR.MoveLast();
    ORIGINAL_ITERATOR++;

	// [Execution]
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(ORIGINAL_ITERATOR);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iteratorPreviousState = --iterator;
    int nCurrentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState != iterator);
    BOOST_CHECK(nCurrentElement == LAST_ELEMENT_VALUE);
}*/

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS
/* [TODO] Thund: Uncomment when the method AddChild exists
/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorPreDecrement_AssertionFailsWhenIteratorIsNotValid_Test )
{
    // [Preparation]
    QBinarySearchTree<int> SAMPLE_TREE(7);
    BuildSampleTree(SAMPLE_TREE);

    QConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(&SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE.GetCapacity());
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
/// Checks that the tree is traversed in the correct order when using depth-first in-order.
/// </summary>
QTEST_CASE ( OperatorPreDecrement_TreeIsTraversedInCorrectOrderWhenUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const int ELEMENT_VALUES[] = {7, 6, 5, 4, 3, 2, 1};
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    iterator.MoveLast();
    bool bIsCorrect = true;
    unsigned int i = 0;

	// [Execution]
    while(bIsCorrect && !iterator.IsEnd())
    {
        bIsCorrect = bIsCorrect && ELEMENT_VALUES[i] == *iterator;
        --iterator;
        ++i;
    }

    // [Verification]
    BOOST_CHECK(bIsCorrect);
}

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position before the first one.
/// </summary>
QTEST_CASE ( OperatorPreDecrement_AssertionFailsWhenIteratorAlreadyPointsToEndPositionBeforeFirst_Test )
{
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_END(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ITERATOR_END.MoveFirst();
    ITERATOR_END--;

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
}*/

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator does not change when it already points to the end position.
/// </summary>
QTEST_CASE ( OperatorPreDecrement_IteratorDoesNotChangeWhenItAlreadyPointsToEndPositionBeforeFirst_Test )
{/* [TODO] Thund: Uncomment when the method AddChild exists
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_END(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ITERATOR_END.MoveFirst();
    ITERATOR_END--;

	// [Execution]
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(ITERATOR_END);
    --iterator;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_END);*/
}

#endif
/* [TODO] Thund: Uncomment when the method AddChild exists
/// <summary>
/// Checks that a common iterator is copied.
/// </summary>
QTEST_CASE ( OperatorAssignment_CommonIteratorIsCorrectlyCopied_Test )
{
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ++ITERATOR_A;

	// [Execution]
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator = ITERATOR_B;
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
    QBinarySearchTree<int> SAMPLE_TREE(7);
    BuildSampleTree(SAMPLE_TREE);

    QConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(&SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE.GetCapacity());
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator VALID_ITERATOR(&SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

	// [Execution]
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator = INVALID_ITERATOR;
    iterator = VALID_ITERATOR;

    // [Verification]
    BOOST_CHECK(iterator.IsValid());
    BOOST_CHECK(iterator == VALID_ITERATOR);
}*/

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS
/* [TODO] Thund: Uncomment when the method AddChild exists
/// <summary>
/// Checks that an assertion fails when the input iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorAssignment_AssertionFailsWhenInputIteratorIsNotValid_Test )
{
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
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
/// Checks that an assertion fails when the input iterator points to a different tree.
/// </summary>
QTEST_CASE ( OperatorAssignment_AssertionFailsWhenInputIteratorPointsToDifferentTree_Test )
{
    // [Preparation]
    QBinarySearchTree<int> TREE_A(3);
    const QBinarySearchTree<int>* TREE_B = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_A(&TREE_A, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(TREE_B, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
        iterator = ITERATOR_A;
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}*/

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator is copied when it is not valid.
/// </summary>
QTEST_CASE ( OperatorAssignment_IteratorIsCopiedWhenInputIteratorIsNotValid_Test )
{/* [TODO] Thund: Uncomment when the method AddChild and Remove exist
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());

	// [Execution]
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    iterator = INVALID_ITERATOR;

    // [Verification]
    BOOST_CHECK(iterator == INVALID_ITERATOR);*/
}

/// <summary>
/// Checks that the iterator is not copied when it points to a different tree.
/// </summary>
QTEST_CASE ( OperatorAssignment_IteratorDoesNotChangeIfInputIteratorPointsToDifferentTree_Test )
{/* [TODO] Thund: Uncomment when the method AddChild exists
    QBinarySearchTree<int> TREE_A(3);
    const QBinarySearchTree<int>* TREE_B = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_A(&TREE_A, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_B(TREE_B, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

	// [Execution]
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator = ITERATOR_B;
    iterator = ITERATOR_A;

    // [Verification]
    BOOST_CHECK(iterator != ITERATOR_A);
    BOOST_CHECK(iterator == ITERATOR_B);*/
}

#endif
/* [TODO] Thund: Uncomment when the method Add exists
/// <summary>
/// Checks that it returns True when iterators are equal.
/// </summary>
QTEST_CASE ( OperatorEquality_ReturnsTrueWhenIteratorsAreEqual_Test )
{
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
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
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
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
{
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
        iterator == INVALID_ITERATOR;
    }
    catch(...)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
        INVALID_ITERATOR == iterator;
    }
    catch(...)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different tree.
/// </summary>
QTEST_CASE ( OperatorEquality_AssertionFailsWhenIteratorsPointToDifferentTrees_Test )
{
    // [Preparation]
    QBinarySearchTree<int> TREE_A(3);
    const QBinarySearchTree<int>* TREE_B = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_A(&TREE_A, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(TREE_B, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
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
/// Checks that it returns False when iterators point to a different tree.
/// </summary>
QTEST_CASE ( OperatorEquality_ReturnsFalseWhenIteratorsPointToDifferentTrees_Test )
{
    // [Preparation]
    QBinarySearchTree<int> TREE_A(3);
    const QBinarySearchTree<int>* TREE_B = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_A(&TREE_A, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_B(TREE_B, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
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
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
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
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
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
{
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
        iterator != INVALID_ITERATOR;
    }
    catch(...)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
        INVALID_ITERATOR != iterator;
    }
    catch(...)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different tree.
/// </summary>
QTEST_CASE ( OperatorInequality_AssertionFailsWhenIteratorsPointToDifferentTrees_Test )
{
    // [Preparation]
    QBinarySearchTree<int> TREE_A(3);
    const QBinarySearchTree<int>* TREE_B = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_A(&TREE_A, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(TREE_B, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
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
/// Checks that it returns True when iterators point to a different tree.
/// </summary>
QTEST_CASE ( OperatorInequality_ReturnsTrueWhenIteratorsPointToDifferentTrees_Test )
{
    // [Preparation]
    QBinarySearchTree<int> TREE_A(3);
    const QBinarySearchTree<int>* TREE_B = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_A(&TREE_A, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_B(TREE_B, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_A != ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when the resident iterator is greater than the input iterator, using depth-first in-order.
/// </summary>
QTEST_CASE ( OperatorGreaterThan_ReturnsTrueWhenResidentIteratorIsGreaterThanInputIteratorUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
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
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A > ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}
*/

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when either the input or the resident iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorGreaterThan_AssertionFailsWhenIteratorsAreNotValid_Test )
{/* [TODO] Thund: Uncomment when the methods AddChild and Remove exist
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
        iterator > INVALID_ITERATOR;
    }
    catch(...)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
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
/// Checks that an assertion fails when the input iterator points to a different tree.
/// </summary>
QTEST_CASE ( OperatorGreaterThan_AssertionFailsWhenIteratorsPointToDifferentTrees_Test )
{/* [TODO] Thund: Uncomment when the method AddChild exists
    // [Preparation]
    QBinarySearchTree<int> TREE_A(3);
    const QBinarySearchTree<int>* TREE_B = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_A(&TREE_A, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(TREE_B, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
        iterator > ITERATOR_A;
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
/// Checks that it returns False when iterators point to a different tree.
/// </summary>
QTEST_CASE ( OperatorGreaterThan_ReturnsFalseWhenIteratorsPointToDifferentTrees_Test )
{/* [TODO] Thund: Uncomment when the method AddChild exists
    // [Preparation]
    QBinarySearchTree<int> TREE_A(3);
    const QBinarySearchTree<int>* TREE_B = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_A(&TREE_A, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ++ITERATOR_A;
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_B(&TREE_B, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A > ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);*/
}

#endif
/* [TODO] Thund: Uncomment when the method AddChild exists
/// <summary>
/// Checks that it returns True when the resident iterator is lower than the input iterator, using depth-first in-order.
/// </summary>
QTEST_CASE ( OperatorLowerThan_ReturnsTrueWhenResidentIteratorIsLowerThanInputIteratorUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_A < ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident iterator is not lower than the input iterator, using depth-first in-order.
/// </summary>
QTEST_CASE ( OperatorLowerThan_ReturnsFalseWhenResidentIteratorIsNotLowerThanInputIteratorUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_B < ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}*/

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when either the input or the resident iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorLowerThan_AssertionFailsWhenIteratorsAreNotValid_Test )
{/* [TODO] Thund: Uncomment when the methods AddChild and Remove exist
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
        iterator < INVALID_ITERATOR;
    }
    catch(...)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
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
/// Checks that an assertion fails when the input iterator points to a different tree.
/// </summary>
QTEST_CASE ( OperatorLowerThan_AssertionFailsWhenIteratorsPointToDifferentTrees_Test )
{/* [TODO] Thund: Uncomment when the method AddChild exists
    // [Preparation]
    QBinarySearchTree<int> TREE_A(3);
    const QBinarySearchTree<int>* TREE_B = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_A(&TREE_A, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ++ITERATOR_A;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(&TREE_B, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
        iterator < ITERATOR_A;
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
/// Checks that it returns False when iterators point to a different tree.
/// </summary>
QTEST_CASE ( OperatorLowerThan_ReturnsFalseWhenIteratorsPointToDifferentTrees_Test )
{/* [TODO] Thund: Uncomment when the method AddChild exists
    // [Preparation]
    QBinarySearchTree<int> TREE_A(3);
    const QBinarySearchTree<int>* TREE_B = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_A(&TREE_A, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_B(&TREE_B, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A < ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);*/
}

#endif
/* [TODO] Thund: Uncomment when the method AddChild exists

/// <summary>
/// Checks that it returns True when the resident iterator is greater than the input iterator, using depth-first in-order.
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsTrueWhenResidentIteratorIsGreaterThanInputIteratorUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B >= ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the resident iterator is equal to the input iterator, using depth-first in-order.
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsTrueWhenResidentIteratorEqualsInputIteratorUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B >= ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident iterator is neither greater than nor equals to the input iterator, using depth-first in-order.
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsFalseWhenResidentIteratorIsNotGreaterThanAndDoNotEqualsInputIteratorUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A >= ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}
*/
#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when either the input or the resident iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_AssertionFailsWhenIteratorsAreNotValid_Test )
{/* [TODO] Thund: Uncomment when the methods AddChild and Remove exist
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
        iterator >= INVALID_ITERATOR;
    }
    catch(...)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
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
/// Checks that an assertion fails when the input iterator points to a different tree.
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_AssertionFailsWhenIteratorsPointToDifferentTrees_Test )
{/* [TODO] Thund: Uncomment when the method AddChild exists
    // [Preparation]
    QBinarySearchTree<int> TREE_A(3);
    const QBinarySearchTree<int>* TREE_B = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_A(&TREE_A, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(&TREE_B, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
        iterator >= ITERATOR_A;
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
/// Checks that it returns False when iterators point to a different tree.
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsFalseWhenIteratorsPointToDifferentTrees_Test )
{/* [TODO] Thund: Uncomment when the method AddChild exists
    // [Preparation]
    QBinarySearchTree<int> TREE_A(3);
    const QBinarySearchTree<int>* TREE_B = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_A(&TREE_A, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_B(&TREE_B, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A >= ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);*/
}

#endif
/* [TODO] Thund: Uncomment when the method AddChild exists
/// <summary>
/// Checks that it returns True when the resident iterator is lower than the input iterator, using depth-first in-order.
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_ReturnsTrueWhenResidentIteratorIsLowerThanInputIteratorUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ++ITERATOR_A;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B <= ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the resident iterator is equal to the input iterator, using depth-first in-order.
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_ReturnsTrueWhenResidentIteratorEqualsInputIteratorUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B <= ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident iterator is neither lower than nor equals to the input iterator, using depth-first in-order.
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_ReturnsFalseWhenResidentIteratorIsNotLowerThanAndDoNotEqualsInputIteratorUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
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
{
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(&SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
        iterator <= INVALID_ITERATOR;
    }
    catch(...)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(&SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
        INVALID_ITERATOR <= iterator;
    }
    catch(...)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different tree.
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_AssertionFailsWhenIteratorsPointToDifferentTrees_Test )
{
    // [Preparation]
    QBinarySearchTree<int> TREE_A(3);
    const QBinarySearchTree<int>* TREE_B = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_A(&TREE_A, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(TREE_B, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
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
/// Checks that it returns False when iterators point to a different tree.
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_ReturnsFalseWhenIteratorsPointToDifferentTrees_Test )
{
    // [Preparation]
    QBinarySearchTree<int> TREE_A(3);
    const QBinarySearchTree<int>* TREE_B = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_A(&TREE_A, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_B(&TREE_B, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
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
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
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
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
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
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ITERATOR.MoveLast();

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR.IsEnd();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}*/

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
QTEST_CASE ( IsEnd1_AssertionFailsWhenIteratorIsNotValid_Test )
{/* [TODO] Thund: Uncomment when the methods AddChild and Remove exist
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());

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
{/* [TODO] Thund: Uncomment when the method AddChild exists
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
    
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = INVALID_ITERATOR.IsEnd();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);*/
}

#endif
/* [TODO] Thund: Uncomment when the method AddChild exists
/// <summary>
/// Checks that it returns True when the iterator points to the position before the first.
/// </summary>
QTEST_CASE ( IsEnd2_ReturnsTrueWhenIteratorPointsToPositionBeforeFirst_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
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
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
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
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ITERATOR.MoveLast();

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR.IsEnd(EQIterationDirection::E_Backward);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}*/

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
QTEST_CASE ( IsEnd2_AssertionFailsWhenIteratorIsNotValid_Test )
{/* [TODO] Thund: Uncomment when the methods AddChild and Remove exist
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
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
{/* [TODO] Thund: Uncomment when the method AddChild exists
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
    
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = INVALID_ITERATOR.IsEnd(EQIterationDirection::E_Backward);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);*/
}

#endif

/// <summary>
/// Checks that the iterator points to the first position when the tree is not empty, using depth-first in-order.
/// </summary>
QTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenTreeIsNotEmptyUsingDepthFirstInOrder_Test )
{/* [TODO] Thund: Uncomment when the method Add exists
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ++ORIGINAL_ITERATOR;
    ++ORIGINAL_ITERATOR;
    ++ORIGINAL_ITERATOR;
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_FIRST(SAMPLE_TREE, 2, EQTreeTraversalOrder::E_DepthFirstInOrder);

	// [Execution]
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveFirst();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_FIRST);*/
}

/// <summary>
/// Checks that the iterator points to the first position even when it was not valid, using depth-first in-order.
/// </summary>
QTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenTreeIsNotEmptyAndIteratorWasNotValidUsingDepthFirstInOrder_Test )
{/* [TODO] Thund: Uncomment when the methods Add and Remove exist
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_FIRST(SAMPLE_TREE, 2, EQTreeTraversalOrder::E_DepthFirstInOrder);

	// [Execution]
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(INVALID_ITERATOR);
    iterator.MoveFirst();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_FIRST);*/
}

/// <summary>
/// Checks that the iterator points to the first position even when it was pointing to the position before the first, using depth-first in-order.
/// </summary>
QTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenTreeIsNotEmptyAndIteratorWasPointingToPositionBeforeFirstUsingDepthFirstInOrder_Test )
{/* [TODO] Thund: Uncomment when the method AddChild exists
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    --ORIGINAL_ITERATOR;

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_FIRST(SAMPLE_TREE, 2, EQTreeTraversalOrder::E_DepthFirstInOrder);

	// [Execution]
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveFirst();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_FIRST);*/
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator points to the end position when the tree is empty.
/// </summary>
QTEST_CASE ( MoveFirst_IteratorPointsToEndPositionWhenTreeIsEmpty_Test )
{
    // [Preparation]
    QBinarySearchTree<int> EMPTY_TREE(1);
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator END_ITERATOR(&EMPTY_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    END_ITERATOR.MoveLast();
    ++END_ITERATOR;
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR(&EMPTY_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

	// [Execution]
    ITERATOR.MoveFirst();

    // [Verification]
    BOOST_CHECK(ITERATOR == END_ITERATOR);
}

#endif

/// <summary>
/// Checks that the iterator points to the last position when the tree is not empty, using depth-first in-order.
/// </summary>
QTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenTreeIsNotEmptyUsingDepthFirstInOrder_Test )
{/* [TODO] Thund: Uncomment when the method AddChild exists
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_LAST(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    while(!ITERATOR_LAST.IsEnd())
        ++ITERATOR_LAST;
    --ITERATOR_LAST;

	// [Execution]
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveLast();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_LAST);*/
}

/// <summary>
/// Checks that the iterator points to the last position even when it was not valid, using depth-first in-order.
/// </summary>
QTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenTreeIsNotEmptyAndIteratorWasNotValidUsingDepthFirstInOrder_Test )
{/* [TODO] Thund: Uncomment when the methods AddChild and Remove exist
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_LAST(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    while(!ITERATOR_LAST.IsEnd())
        ++ITERATOR_LAST;
    --ITERATOR_LAST;

    QConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());

	// [Execution]
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(INVALID_ITERATOR);
    iterator.MoveLast();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_LAST);*/
}

/// <summary>
/// Checks that the iterator points to the last position even when it was pointing to the position before the first, using depth-first in-order.
/// </summary>
QTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenTreeIsNotEmptyAndIteratorWasPointingToPositionBeforeFirstUsingDepthFirstInOrder_Test )
{/* [TODO] Thund: Uncomment when the method AddChild exists
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    --ORIGINAL_ITERATOR;

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR_LAST(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    while(!ITERATOR_LAST.IsEnd())
        ++ITERATOR_LAST;
    --ITERATOR_LAST;

	// [Execution]
    QBinarySearchTree<int>::QConstBinarySearchTreeIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveLast();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_LAST);*/
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator points to the end position when the tree is empty.
/// </summary>
QTEST_CASE ( MoveLast_IteratorPointsToEndPositionWhenTreeIsEmpty_Test )
{
    // [Preparation]
    QBinarySearchTree<int> EMPTY_ARRAY(1);

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator END_ITERATOR(&EMPTY_ARRAY, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    END_ITERATOR.MoveLast();
    ++END_ITERATOR;

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR(&EMPTY_ARRAY, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

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
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QBinarySearchTree<int>::QConstBinarySearchTreeIterator ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
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
{
    // [Preparation]
    const QBinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    QConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = INVALID_ITERATOR.IsValid();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

// End - Test Suite: QConstBinarySearchTreeIterator
QTEST_SUITE_END()
