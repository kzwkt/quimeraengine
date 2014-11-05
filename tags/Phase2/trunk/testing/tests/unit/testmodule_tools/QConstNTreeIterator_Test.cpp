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

#include "QNTree.h"

#include "QNTreeIteratorMock.h"

using Kinesis::QuimeraEngine::Tools::Containers::QNTree;
using Kinesis::QuimeraEngine::Tools::Containers::EQTreeTraversalOrder;
using Kinesis::QuimeraEngine::Tools::Containers::Test::QNTreeIteratorMock;

/// <summary>
/// Small structure used in operator* and operator-> tests.
/// </summary>
struct TestStructure
{
    TestStructure(const char field) : m_field(field)
    {
    }

    char m_field;
};

QTEST_SUITE_BEGIN( QConstNTreeIterator_TestSuite )

/// <summary>
/// Gets a sample tree with which to perform some tests.
/// </summary>
/// <returns>
/// A sample tree with a variety of nodes.
/// </returns>
static const QNTree<char>* GetSampleTree()
{
    static QNTree<char> sampleTree(3, 7);
    static bool bInitialized = false;

    if(!bInitialized)
    {
        //          A
        //         /|\
        //        / | \
        //       B  C  D
        //      / \     \
        //     /   \     \
        //    E     F     G
        sampleTree.SetRootValue('A');
        QNTree<char>::QConstNTreeIterator iteratorA = sampleTree.GetRoot(EQTreeTraversalOrder::E_DepthFirstPreOrder);
        sampleTree.AddChild(iteratorA, 'B');
        sampleTree.AddChild(iteratorA, 'C');
        sampleTree.AddChild(iteratorA, 'D');
        QNTree<char>::QConstNTreeIterator iteratorB = sampleTree.GetFirstChild(iteratorA);
        sampleTree.AddChild(iteratorB, 'E');
        sampleTree.AddChild(iteratorB, 'F');
        QNTree<char>::QConstNTreeIterator iteratorD = sampleTree.GetLastChild(iteratorA);
        sampleTree.AddChild(iteratorD, 'G');

        bInitialized = true;
    }

    return &sampleTree;
}

/// <summary>
/// Creates a sample tree using an external tree.
/// </summary>
/// <param name="inputTree">An empty tree.</param>
static void BuildSampleTree(QNTree<char> &inputTree)
{
    //          A
    //         /|\
    //        / | \
    //       B  C  D
    //      / \     \
    //     /   \     \
    //    E     F     G
    inputTree.SetRootValue('A');
    QNTree<char>::QConstNTreeIterator iteratorA = inputTree.GetRoot(EQTreeTraversalOrder::E_DepthFirstPreOrder);
    inputTree.AddChild(iteratorA, 'B');
    inputTree.AddChild(iteratorA, 'C');
    inputTree.AddChild(iteratorA, 'D');
    QNTree<char>::QConstNTreeIterator iteratorB = inputTree.GetFirstChild(iteratorA);
    inputTree.AddChild(iteratorB, 'E');
    inputTree.AddChild(iteratorB, 'F');
    QNTree<char>::QConstNTreeIterator iteratorD = inputTree.GetLastChild(iteratorA);
    inputTree.AddChild(iteratorD, 'G');
}


/// <summary>
/// Checks that the iterator points to the given position when using a common tree and depth-first pre-order traversal order.
/// </summary>
QTEST_CASE ( Constructor_IteratorPointsToGivenPositionWhenUsingCommonTreeAndDepthFirstPreOrder_Test )
{
    // [Preparation]
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();
    const pointer_uint_q POSITION = 1;
    QNTree<char>::QConstNTreeIterator EXPECTED_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    EXPECTED_ITERATOR.MoveFirst();
    ++EXPECTED_ITERATOR;

	// [Execution]
    QNTree<char>::QConstNTreeIterator iterator(SAMPLE_TREE, POSITION, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    
    // [Verification]
    BOOST_CHECK(iterator == EXPECTED_ITERATOR);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when input tree is null.
/// </summary>
QTEST_CASE ( Constructor_AssertionFailsWhenInputTreeIsNull_Test )
{
    // [Preparation]
    QNTree<char>* SOURCE_TREE = null_q;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QNTree<char>::QConstNTreeIterator INVALID_ITERATOR(SOURCE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    const pointer_uint_q CAPACITY = SAMPLE_TREE->GetCapacity();
    const unsigned int INVALID_POSITION = CAPACITY;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QNTree<char>::QConstNTreeIterator INVALID_ITERATOR(SAMPLE_TREE, INVALID_POSITION, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();
    const EQTreeTraversalOrder UNSUPPORTED_TRAVERSAL_ORDER = EQTreeTraversalOrder::_NotEnumValue;
    const unsigned int INPUT_POSITION = 0;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QNTree<char>::QConstNTreeIterator INVALID_ITERATOR(SAMPLE_TREE, INPUT_POSITION, UNSUPPORTED_TRAVERSAL_ORDER);
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
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    const pointer_uint_q NUMBER_OF_ELEMENTS = SAMPLE_TREE->GetCount();

    const unsigned int INVALID_POSITION = NUMBER_OF_ELEMENTS;
    const bool IS_END = true;

	// [Execution]
    QNTree<char>::QConstNTreeIterator INVALID_ITERATOR(SAMPLE_TREE, INVALID_POSITION, EQTreeTraversalOrder::E_DepthFirstPreOrder);

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
    const QNTree<char> SOURCE_TREE(3);
    const bool IS_END = true;

	// [Execution]
    QNTree<char>::QConstNTreeIterator iterator(&SOURCE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);

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
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    const char EXPECTED_VALUE = 'B';
    QNTree<char>::QConstNTreeIterator ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    ++ITERATOR;

	// [Execution]
    char value = *ITERATOR;

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
    QNTree<char> SAMPLE_TREE(3, 7);
    BuildSampleTree(SAMPLE_TREE);

    QNTree<char>::QConstNTreeIterator FIRST_POSITION(&SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder); 
    QNTreeIteratorMock<char> INVALID_ITERATOR(&SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder); 
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
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
    QNTree<TestStructure> SAMPLE_TREE(3, 7);
    SAMPLE_TREE.SetRootValue(TestStructure('A'));
    QNTree<TestStructure>::QConstNTreeIterator iteratorA = SAMPLE_TREE.GetRoot(EQTreeTraversalOrder::E_DepthFirstPreOrder);
    SAMPLE_TREE.AddChild(iteratorA, TestStructure('B'));
    SAMPLE_TREE.AddChild(iteratorA, TestStructure('C'));
    SAMPLE_TREE.AddChild(iteratorA, TestStructure('D'));
    QNTree<TestStructure>::QConstNTreeIterator iteratorB = SAMPLE_TREE.GetFirstChild(iteratorA);
    SAMPLE_TREE.AddChild(iteratorB, TestStructure('E'));
    SAMPLE_TREE.AddChild(iteratorB, TestStructure('F'));
    QNTree<TestStructure>::QConstNTreeIterator iteratorD = SAMPLE_TREE.GetLastChild(iteratorA);
    SAMPLE_TREE.AddChild(iteratorD, TestStructure('G'));

    const char EXPECTED_VALUE = 'B';
    QNTree<TestStructure>::QConstNTreeIterator ITERATOR(&SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    ++ITERATOR;

	// [Execution]
    char value = ITERATOR->m_field;

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
    QNTree<TestStructure> SAMPLE_TREE(3, 7);
    SAMPLE_TREE.SetRootValue(TestStructure('A'));
    QNTree<TestStructure>::QConstNTreeIterator iteratorA = SAMPLE_TREE.GetRoot(EQTreeTraversalOrder::E_DepthFirstPreOrder);
    SAMPLE_TREE.AddChild(iteratorA, TestStructure('B'));
    SAMPLE_TREE.AddChild(iteratorA, TestStructure('C'));
    SAMPLE_TREE.AddChild(iteratorA, TestStructure('D'));
    QNTree<TestStructure>::QConstNTreeIterator iteratorB = SAMPLE_TREE.GetFirstChild(iteratorA);
    SAMPLE_TREE.AddChild(iteratorB, TestStructure('E'));
    SAMPLE_TREE.AddChild(iteratorB, TestStructure('F'));
    QNTree<TestStructure>::QConstNTreeIterator iteratorD = SAMPLE_TREE.GetLastChild(iteratorA);
    SAMPLE_TREE.AddChild(iteratorD, TestStructure('G'));

    QNTree<TestStructure>::QConstNTreeIterator FIRST_POSITION(&SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder); 
    QNTreeIteratorMock<TestStructure> INVALID_ITERATOR(&SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder); 
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
    QNTree<TestStructure> SAMPLE_TREE(3, 7);
    SAMPLE_TREE.SetRootValue(TestStructure('A'));
    QNTree<TestStructure>::QConstNTreeIterator iteratorA = SAMPLE_TREE.GetRoot(EQTreeTraversalOrder::E_DepthFirstPreOrder);
    SAMPLE_TREE.AddChild(iteratorA, TestStructure('B'));
    SAMPLE_TREE.AddChild(iteratorA, TestStructure('C'));
    SAMPLE_TREE.AddChild(iteratorA, TestStructure('D'));
    QNTree<TestStructure>::QConstNTreeIterator iteratorB = SAMPLE_TREE.GetFirstChild(iteratorA);
    SAMPLE_TREE.AddChild(iteratorB, TestStructure('E'));
    SAMPLE_TREE.AddChild(iteratorB, TestStructure('F'));
    QNTree<TestStructure>::QConstNTreeIterator iteratorD = SAMPLE_TREE.GetLastChild(iteratorA);
    SAMPLE_TREE.AddChild(iteratorD, TestStructure('G'));

    QNTree<TestStructure>::QConstNTreeIterator ITERATOR(&SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
    QNTree<TestStructure> SAMPLE_TREE(3, 7);
    SAMPLE_TREE.SetRootValue(TestStructure('A'));
    QNTree<TestStructure>::QConstNTreeIterator iteratorA = SAMPLE_TREE.GetRoot(EQTreeTraversalOrder::E_DepthFirstPreOrder);
    SAMPLE_TREE.AddChild(iteratorA, TestStructure('B'));
    SAMPLE_TREE.AddChild(iteratorA, TestStructure('C'));
    SAMPLE_TREE.AddChild(iteratorA, TestStructure('D'));
    QNTree<TestStructure>::QConstNTreeIterator iteratorB = SAMPLE_TREE.GetFirstChild(iteratorA);
    SAMPLE_TREE.AddChild(iteratorB, TestStructure('E'));
    SAMPLE_TREE.AddChild(iteratorB, TestStructure('F'));
    QNTree<TestStructure>::QConstNTreeIterator iteratorD = SAMPLE_TREE.GetLastChild(iteratorA);
    SAMPLE_TREE.AddChild(iteratorD, TestStructure('G'));

    QNTree<TestStructure>::QConstNTreeIterator ITERATOR(&SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
/// Checks that the iterator steps forward properly and returns the previous state when using depth-first pre-order.
/// </summary>
QTEST_CASE ( OperatorPostIncrement_CommonIteratorStepsForwardProperlyAndReturnsPreviousStateWhenUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const char SECOND_ELEMENT_VALUE = 'B';
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    ORIGINAL_ITERATOR.MoveFirst();

	// [Execution]
    QNTree<char>::QConstNTreeIterator iterator(ORIGINAL_ITERATOR);
    QNTree<char>::QConstNTreeIterator iteratorPreviousState = iterator++;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(*iterator == SECOND_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the tree is traversed in the correct order when using depth-first pre-order.
/// </summary>
QTEST_CASE ( OperatorPostIncrement_TreeIsTraversedInCorrectOrderWhenUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const char ELEMENT_VALUES[] = {'A', 'B', 'E', 'F', 'C', 'D', 'G'};
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    iterator.MoveFirst();
    bool bIsCorrect = true;
    unsigned int i = 0;

	// [Execution]
    while(bIsCorrect && !iterator.IsEnd())
    {
        bIsCorrect = bIsCorrect && ELEMENT_VALUES[i] == *iterator;
        iterator++;
        ++i;
    }

    // [Verification]
    BOOST_CHECK(bIsCorrect);
}

/// <summary>
/// Checks that the iterator points to the first position and returns the previous state when it was pointing to the end position before the first one, using depth-first pre-order.
/// </summary>
QTEST_CASE ( OperatorPostIncrement_IteratorPointsToFirstPositionAndReturnsPreviousStateWhenItWasPointingToPositionBeforeFirstUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const char FIRST_ELEMENT_VALUE = 'A';
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    ORIGINAL_ITERATOR.MoveFirst();
    --ORIGINAL_ITERATOR;

	// [Execution]
    QNTree<char>::QConstNTreeIterator iterator(ORIGINAL_ITERATOR);
    QNTree<char>::QConstNTreeIterator iteratorPreviousState = iterator++;
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
    QNTree<char> SAMPLE_TREE(3, 7);
    BuildSampleTree(SAMPLE_TREE);

    QNTreeIteratorMock<char> INVALID_ITERATOR(&SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder); 
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
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position.
/// </summary>
QTEST_CASE ( OperatorPostIncrement_AssertionFailsWhenIteratorAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_END(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_END(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    ITERATOR_END.MoveLast();
    ++ITERATOR_END;

	// [Execution]
    QNTree<char>::QConstNTreeIterator iterator(ITERATOR_END);
    iterator++;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_END);
}

#endif

/// <summary>
/// Checks that the iterator steps backward properly and returns the previous state, when using depth-first pre-order.
/// </summary>
QTEST_CASE ( OperatorPostDecrement_CommonIteratorStepsBackwardProperlyAndReturnsPreviousStateWhenUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const char SECOND_ELEMENT_VALUE = 'D';
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    ORIGINAL_ITERATOR.MoveLast();

	// [Execution]
    QNTree<char>::QConstNTreeIterator iterator(ORIGINAL_ITERATOR);
    QNTree<char>::QConstNTreeIterator iteratorPreviousState = iterator--;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(*iterator == SECOND_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the tree is traversed in the correct order when using depth-first pre-order.
/// </summary>
QTEST_CASE ( OperatorPostDecrement_TreeIsTraversedInCorrectOrderWhenUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const char ELEMENT_VALUES[] = {'G', 'D', 'C', 'F', 'E', 'B', 'A'};
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    iterator.MoveLast();
    bool bIsCorrect = true;
    unsigned int i = 0;

	// [Execution]
    while(bIsCorrect && !iterator.IsEnd())
    {
        bIsCorrect = bIsCorrect && ELEMENT_VALUES[i] == *iterator;
        iterator--;
        ++i;
    }

    // [Verification]
    BOOST_CHECK(bIsCorrect);
}

/// <summary>
/// Checks that the iterator points to the last position and returns the previous state when it was pointing to the end position after the last one, when using depth-first pre-order.
/// </summary>
QTEST_CASE ( OperatorPostDecrement_IteratorPointsToLastPositionAndReturnsPreviousStateWhenItWasPointingToLastEndPositionUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const char LAST_ELEMENT_VALUE = 'G';
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    ORIGINAL_ITERATOR.MoveLast();
    ++ORIGINAL_ITERATOR;

	// [Execution]
    QNTree<char>::QConstNTreeIterator iterator(ORIGINAL_ITERATOR);
    QNTree<char>::QConstNTreeIterator iteratorPreviousState = iterator--;
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
    QNTree<char> SAMPLE_TREE(3, 7);
    BuildSampleTree(SAMPLE_TREE);

    QNTreeIteratorMock<char> INVALID_ITERATOR(&SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder); 
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
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_END(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_END(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    ITERATOR_END.MoveFirst();
    --ITERATOR_END;

	// [Execution]
    QNTree<char>::QConstNTreeIterator iterator(ITERATOR_END);
    iterator--;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_END);
}

#endif

/// <summary>
/// Checks that the iterator steps forward properly and returns the current state, when using depth-first pre-order.
/// </summary>
QTEST_CASE ( OperatorPreIncrement_CommonIteratorStepsForwardProperlyAndReturnsCurrentStateWhenUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const char SECOND_ELEMENT_VALUE = 'B';
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    ORIGINAL_ITERATOR.MoveFirst();

	// [Execution]
    QNTree<char>::QConstNTreeIterator iterator(ORIGINAL_ITERATOR);
    QNTree<char>::QConstNTreeIterator iteratorPreviousState = ++iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == iterator);
    BOOST_CHECK(*iterator == SECOND_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the tree is traversed in the correct order when using depth-first pre-order.
/// </summary>
QTEST_CASE ( OperatorPreIncrement_TreeIsTraversedInCorrectOrderWhenUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const char ELEMENT_VALUES[] = {'A', 'B', 'E', 'F', 'C', 'D', 'G'};
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
/// Checks that the iterator points to the first position and returns the current state when it was pointing to the end position before the first one, when using depth-first pre-order.
/// </summary>
QTEST_CASE ( OperatorPreIncrement_IteratorPointsToFirstPositionAndReturnsCurrentStateWhenItWasPointingToPositionBeforeFirstUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const char FIRST_ELEMENT_VALUE = 'A';
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    ORIGINAL_ITERATOR.MoveFirst();
    --ORIGINAL_ITERATOR;

	// [Execution]
    QNTree<char>::QConstNTreeIterator iterator(ORIGINAL_ITERATOR);
    QNTree<char>::QConstNTreeIterator iteratorPreviousState = ++iterator;
    char currentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == iterator);
    BOOST_CHECK(currentElement == FIRST_ELEMENT_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorPreIncrement_AssertionFailsWhenIteratorIsNotValid_Test )
{
    // [Preparation]
    QNTree<char> SAMPLE_TREE(3, 7);
    BuildSampleTree(SAMPLE_TREE);

    QNTreeIteratorMock<char> INVALID_ITERATOR(&SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder); 
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
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_END(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator does not change when it already points to the end position.
/// </summary>
QTEST_CASE ( OperatorPreIncrement_IteratorDoesNotChangeWhenItAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_END(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    ITERATOR_END.MoveLast();
    ITERATOR_END++;

	// [Execution]
    QNTree<char>::QConstNTreeIterator iterator(ITERATOR_END);
    ++iterator;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_END);
}

#endif

/// <summary>
/// Checks that the iterator steps backward properly and returns the current state, when using depth-first pre-order.
/// </summary>
QTEST_CASE ( OperatorPreDecrement_CommonIteratorStepsBackwardProperlyAndReturnsCurrentStateWhenUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const char SECOND_ELEMENT_VALUE = 'D';
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    ORIGINAL_ITERATOR.MoveLast();

	// [Execution]
    QNTree<char>::QConstNTreeIterator iterator(ORIGINAL_ITERATOR);
    QNTree<char>::QConstNTreeIterator iteratorPreviousState = --iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == iterator);
    BOOST_CHECK(*iterator == SECOND_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the tree is traversed in the correct order when using depth-first pre-order.
/// </summary>
QTEST_CASE ( OperatorPreDecrement_TreeIsTraversedInCorrectOrderWhenUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const char ELEMENT_VALUES[] = {'G', 'D', 'C', 'F', 'E', 'B', 'A'};
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
/// Checks that the iterator points to the last position and returns the current state when it was pointing to the end position after the last one, when using depth-first pre-order.
/// </summary>
QTEST_CASE ( OperatorPreDecrement_IteratorPointsToLastPositionAndReturnsCurrentStateWhenItWasPointingToLastEndPositionUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const char LAST_ELEMENT_VALUE = 'G';
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    ORIGINAL_ITERATOR.MoveLast();
    ORIGINAL_ITERATOR++;

	// [Execution]
    QNTree<char>::QConstNTreeIterator iterator(ORIGINAL_ITERATOR);
    QNTree<char>::QConstNTreeIterator iteratorPreviousState = --iterator;
    int nCurrentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == iterator);
    BOOST_CHECK(nCurrentElement == LAST_ELEMENT_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
QTEST_CASE ( OperatorPreDecrement_AssertionFailsWhenIteratorIsNotValid_Test )
{
    // [Preparation]
    QNTree<char> SAMPLE_TREE(3, 7);
    BuildSampleTree(SAMPLE_TREE);

    QNTreeIteratorMock<char> INVALID_ITERATOR(&SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder); 
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
/// Checks that an assertion fails when the iterator already points to the end position before the first one.
/// </summary>
QTEST_CASE ( OperatorPreDecrement_AssertionFailsWhenIteratorAlreadyPointsToEndPositionBeforeFirst_Test )
{
    // [Preparation]
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_END(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator does not change when it already points to the end position.
/// </summary>
QTEST_CASE ( OperatorPreDecrement_IteratorDoesNotChangeWhenItAlreadyPointsToEndPositionBeforeFirst_Test )
{
    // [Preparation]
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_END(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    ITERATOR_END.MoveFirst();
    ITERATOR_END--;

	// [Execution]
    QNTree<char>::QConstNTreeIterator iterator(ITERATOR_END);
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
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QConstNTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    ++ITERATOR_A;

	// [Execution]
    QNTree<char>::QConstNTreeIterator iterator = ITERATOR_B;
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
    QNTree<char> SAMPLE_TREE(3, 7);
    BuildSampleTree(SAMPLE_TREE);

    QNTreeIteratorMock<char> INVALID_ITERATOR(&SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE.GetCapacity());
    QNTree<char>::QConstNTreeIterator VALID_ITERATOR(&SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);

	// [Execution]
    QNTree<char>::QConstNTreeIterator iterator = INVALID_ITERATOR;
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
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTreeIteratorMock<char> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QNTree<char>::QConstNTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
    QNTree<char> TREE_A(3);
    const QNTree<char>* TREE_B = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_A(&TREE_A, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QNTree<char>::QConstNTreeIterator iterator(TREE_B, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTreeIteratorMock<char> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());

	// [Execution]
    QNTree<char>::QConstNTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    iterator = INVALID_ITERATOR;

    // [Verification]
    BOOST_CHECK(iterator == INVALID_ITERATOR);
}

/// <summary>
/// Checks that the iterator is not copied when it points to a different tree.
/// </summary>
QTEST_CASE ( OperatorAssignment_IteratorDoesNotChangeIfInputIteratorPointsToDifferentTree_Test )
{
    QNTree<char> TREE_A(3);
    const QNTree<char>* TREE_B = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_A(&TREE_A, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QConstNTreeIterator ITERATOR_B(TREE_B, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);

	// [Execution]
    QNTree<char>::QConstNTreeIterator iterator = ITERATOR_B;
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
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QConstNTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QConstNTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTreeIteratorMock<char> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        QNTree<char>::QConstNTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
        iterator == INVALID_ITERATOR;
    }
    catch(...)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QNTree<char>::QConstNTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
    QNTree<char> TREE_A(3);
    const QNTree<char>* TREE_B = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_A(&TREE_A, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QNTree<char>::QConstNTreeIterator iterator(TREE_B, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
    QNTree<char> TREE_A(3);
    const QNTree<char>* TREE_B = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_A(&TREE_A, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QConstNTreeIterator ITERATOR_B(TREE_B, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QConstNTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QConstNTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTreeIteratorMock<char> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        QNTree<char>::QConstNTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
        iterator != INVALID_ITERATOR;
    }
    catch(...)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QNTree<char>::QConstNTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
    QNTree<char> TREE_A(3);
    const QNTree<char>* TREE_B = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_A(&TREE_A, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QNTree<char>::QConstNTreeIterator iterator(TREE_B, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
    QNTree<char> TREE_A(3);
    const QNTree<char>* TREE_B = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_A(&TREE_A, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QConstNTreeIterator ITERATOR_B(TREE_B, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_A != ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when the resident iterator is greater than the input iterator, using depth-first pre-order.
/// </summary>
QTEST_CASE ( OperatorGreaterThan_ReturnsTrueWhenResidentIteratorIsGreaterThanInputIteratorUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QConstNTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B > ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident iterator is not greater than the input iterator, using depth-first pre-order.
/// </summary>
QTEST_CASE ( OperatorGreaterThan_ReturnsFalseWhenResidentIteratorIsNotGreaterThanInputIteratorUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QConstNTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
{
    // [Preparation]
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTreeIteratorMock<char> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        QNTree<char>::QConstNTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
        iterator > INVALID_ITERATOR;
    }
    catch(...)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QNTree<char>::QConstNTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
        INVALID_ITERATOR > iterator;
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
QTEST_CASE ( OperatorGreaterThan_AssertionFailsWhenIteratorsPointToDifferentTrees_Test )
{
    // [Preparation]
    QNTree<char> TREE_A(3);
    const QNTree<char>* TREE_B = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_A(&TREE_A, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QNTree<char>::QConstNTreeIterator iterator(TREE_B, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
/// Checks that it returns False when iterators point to a different tree.
/// </summary>
QTEST_CASE ( OperatorGreaterThan_ReturnsFalseWhenIteratorsPointToDifferentTrees_Test )
{
    // [Preparation]
    QNTree<char> TREE_A(3);
    const QNTree<char>* TREE_B = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_A(&TREE_A, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    ++ITERATOR_A;
    QNTree<char>::QConstNTreeIterator ITERATOR_B(TREE_B, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A > ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when the resident iterator is lower than the input iterator, using depth-first pre-order.
/// </summary>
QTEST_CASE ( OperatorLowerThan_ReturnsTrueWhenResidentIteratorIsLowerThanInputIteratorUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QConstNTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_A < ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident iterator is not lower than the input iterator, using depth-first pre-order.
/// </summary>
QTEST_CASE ( OperatorLowerThan_ReturnsFalseWhenResidentIteratorIsNotLowerThanInputIteratorUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QConstNTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
{
    // [Preparation]
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTreeIteratorMock<char> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        QNTree<char>::QConstNTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
        iterator < INVALID_ITERATOR;
    }
    catch(...)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QNTree<char>::QConstNTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
        INVALID_ITERATOR < iterator;
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
QTEST_CASE ( OperatorLowerThan_AssertionFailsWhenIteratorsPointToDifferentTrees_Test )
{
    // [Preparation]
    QNTree<char> TREE_A(3);
    TREE_A.SetRootValue('A');
    const QNTree<char>* TREE_B = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_A(&TREE_A, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    ++ITERATOR_A;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QNTree<char>::QConstNTreeIterator iterator(TREE_B, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
/// Checks that it returns False when iterators point to a different tree.
/// </summary>
QTEST_CASE ( OperatorLowerThan_ReturnsFalseWhenIteratorsPointToDifferentTrees_Test )
{
    // [Preparation]
    QNTree<char> TREE_A(3);
    const QNTree<char>* TREE_B = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_A(&TREE_A, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QConstNTreeIterator ITERATOR_B(TREE_B, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A < ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when the resident iterator is greater than the input iterator, using depth-first pre-order.
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsTrueWhenResidentIteratorIsGreaterThanInputIteratorUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QConstNTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B >= ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the resident iterator is equal to the input iterator, using depth-first pre-order.
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsTrueWhenResidentIteratorEqualsInputIteratorUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QConstNTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B >= ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident iterator is neither greater than nor equals to the input iterator, using depth-first pre-order.
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsFalseWhenResidentIteratorIsNotGreaterThanAndDoNotEqualsInputIteratorUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QConstNTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
{
    // [Preparation]
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTreeIteratorMock<char> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        QNTree<char>::QConstNTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
        iterator >= INVALID_ITERATOR;
    }
    catch(...)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QNTree<char>::QConstNTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
        INVALID_ITERATOR >= iterator;
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
QTEST_CASE ( OperatorGreaterThanOrEquals_AssertionFailsWhenIteratorsPointToDifferentTrees_Test )
{
    // [Preparation]
    QNTree<char> TREE_A(3);
    const QNTree<char>* TREE_B = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_A(&TREE_A, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QNTree<char>::QConstNTreeIterator iterator(TREE_B, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
/// Checks that it returns False when iterators point to a different tree.
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsFalseWhenIteratorsPointToDifferentTrees_Test )
{
    // [Preparation]
    QNTree<char> TREE_A(3, 3);
    const QNTree<char>* TREE_B = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_A(&TREE_A, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QConstNTreeIterator ITERATOR_B(TREE_B, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A >= ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when the resident iterator is lower than the input iterator, using depth-first pre-order.
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_ReturnsTrueWhenResidentIteratorIsLowerThanInputIteratorUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QConstNTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    ++ITERATOR_A;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B <= ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the resident iterator is equal to the input iterator, using depth-first pre-order.
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_ReturnsTrueWhenResidentIteratorEqualsInputIteratorUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QConstNTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B <= ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident iterator is neither lower than nor equals to the input iterator, using depth-first pre-order.
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_ReturnsFalseWhenResidentIteratorIsNotLowerThanAndDoNotEqualsInputIteratorUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_A(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QConstNTreeIterator ITERATOR_B(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTreeIteratorMock<char> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        QNTree<char>::QConstNTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
        iterator <= INVALID_ITERATOR;
    }
    catch(...)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QNTree<char>::QConstNTreeIterator iterator(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
    QNTree<char> TREE_A(3);
    const QNTree<char>* TREE_B = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_A(&TREE_A, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QNTree<char>::QConstNTreeIterator iterator(TREE_B, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
    QNTree<char> TREE_A(3);
    const QNTree<char>* TREE_B = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR_A(&TREE_A, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QConstNTreeIterator ITERATOR_B(TREE_B, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
{
    // [Preparation]
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTreeIteratorMock<char> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder); 
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
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns False when the iterator is not valid.
/// </summary>
QTEST_CASE ( IsEnd1_ReturnsFalseWhenIteratorIsNotValid_Test )
{
    // [Preparation]
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTreeIteratorMock<char> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
    
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = INVALID_ITERATOR.IsEnd();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when the iterator points to the position before the first.
/// </summary>
QTEST_CASE ( IsEnd2_ReturnsTrueWhenIteratorPointsToPositionBeforeFirst_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTreeIteratorMock<char> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder); 
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
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns False when the iterator is not valid.
/// </summary>
QTEST_CASE ( IsEnd2_ReturnsFalseWhenIteratorIsNotValid_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTreeIteratorMock<char> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
    
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = INVALID_ITERATOR.IsEnd(EQIterationDirection::E_Backward);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that the iterator points to the first position when the tree is not empty, using depth-first pre-order.
/// </summary>
QTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenTreeIsNotEmptyUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    ++ORIGINAL_ITERATOR;
    ++ORIGINAL_ITERATOR;
    ++ORIGINAL_ITERATOR;
    QNTree<char>::QConstNTreeIterator ITERATOR_FIRST(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);

	// [Execution]
    QNTree<char>::QConstNTreeIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveFirst();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_FIRST);
}

/// <summary>
/// Checks that the iterator points to the first position even when it was not valid, using depth-first pre-order.
/// </summary>
QTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenTreeIsNotEmptyAndIteratorWasNotValidUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTreeIteratorMock<char> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());

    QNTree<char>::QConstNTreeIterator ITERATOR_FIRST(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);

	// [Execution]
    QNTree<char>::QConstNTreeIterator iterator(INVALID_ITERATOR);
    iterator.MoveFirst();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_FIRST);
}

/// <summary>
/// Checks that the iterator points to the first position even when it was pointing to the position before the first, using depth-first pre-order.
/// </summary>
QTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenTreeIsNotEmptyAndIteratorWasPointingToPositionBeforeFirstUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    --ORIGINAL_ITERATOR;

    QNTree<char>::QConstNTreeIterator ITERATOR_FIRST(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);

	// [Execution]
    QNTree<char>::QConstNTreeIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveFirst();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_FIRST);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator points to the end position when the tree is empty.
/// </summary>
QTEST_CASE ( MoveFirst_IteratorPointsToEndPositionWhenTreeIsEmpty_Test )
{
    // [Preparation]
    QNTree<char> EMPTY_ARRAY(3, 1);
    QNTree<char>::QConstNTreeIterator END_ITERATOR(&EMPTY_ARRAY, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    END_ITERATOR.MoveLast();
    ++END_ITERATOR;
    QNTree<char>::QConstNTreeIterator ITERATOR(&EMPTY_ARRAY, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);

	// [Execution]
    ITERATOR.MoveFirst();

    // [Verification]
    BOOST_CHECK(ITERATOR == END_ITERATOR);
}

#endif

/// <summary>
/// Checks that the iterator points to the last position when the tree is not empty, using depth-first pre-order.
/// </summary>
QTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenTreeIsNotEmptyUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);

    QNTree<char>::QConstNTreeIterator ITERATOR_LAST(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    while(!ITERATOR_LAST.IsEnd())
        ++ITERATOR_LAST;
    --ITERATOR_LAST;

	// [Execution]
    QNTree<char>::QConstNTreeIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveLast();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_LAST);
}

/// <summary>
/// Checks that the iterator points to the last position even when it was not valid, using depth-first pre-order.
/// </summary>
QTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenTreeIsNotEmptyAndIteratorWasNotValidUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);

    QNTree<char>::QConstNTreeIterator ITERATOR_LAST(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    while(!ITERATOR_LAST.IsEnd())
        ++ITERATOR_LAST;
    --ITERATOR_LAST;

    QNTreeIteratorMock<char> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());

	// [Execution]
    QNTree<char>::QConstNTreeIterator iterator(INVALID_ITERATOR);
    iterator.MoveLast();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_LAST);
}

/// <summary>
/// Checks that the iterator points to the last position even when it was pointing to the position before the first, using depth-first pre-order.
/// </summary>
QTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenTreeIsNotEmptyAndIteratorWasPointingToPositionBeforeFirstUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    --ORIGINAL_ITERATOR;

    QNTree<char>::QConstNTreeIterator ITERATOR_LAST(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    while(!ITERATOR_LAST.IsEnd())
        ++ITERATOR_LAST;
    --ITERATOR_LAST;

	// [Execution]
    QNTree<char>::QConstNTreeIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveLast();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_LAST);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator points to the end position when the tree is empty.
/// </summary>
QTEST_CASE ( MoveLast_IteratorPointsToEndPositionWhenTreeIsEmpty_Test )
{
    // [Preparation]
    QNTree<char> EMPTY_ARRAY(3, 1);

    QNTree<char>::QConstNTreeIterator END_ITERATOR(&EMPTY_ARRAY, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    END_ITERATOR.MoveLast();
    ++END_ITERATOR;

    QNTree<char>::QConstNTreeIterator ITERATOR(&EMPTY_ARRAY, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);

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
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTree<char>::QConstNTreeIterator ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
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
    const QNTree<char>* SAMPLE_TREE = GetSampleTree();

    QNTreeIteratorMock<char> INVALID_ITERATOR(SAMPLE_TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = INVALID_ITERATOR.IsValid();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

// End - Test Suite: QConstNTreeIterator
QTEST_SUITE_END()
