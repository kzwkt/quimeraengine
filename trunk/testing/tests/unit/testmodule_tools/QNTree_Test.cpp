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
#include "QNTreeWhiteBox.h"
#include "CallCounter.h"
#include "QAssertException.h"

using Kinesis::QuimeraEngine::Common::Exceptions::QAssertException;
using Kinesis::QuimeraEngine::Tools::Containers::QNTree;
using Kinesis::QuimeraEngine::Tools::Containers::Test::QNTreeWhiteBox;
using Kinesis::QuimeraEngine::Tools::Containers::EQTreeTraversalOrder;


QTEST_SUITE_BEGIN( QNTree_TestSuite )

/// <summary>
/// Checks that the maximum number of child nodes has been correctly set.
/// </summary>
QTEST_CASE ( Constructor1_MaximumChildrenIsCorrectlySet_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_VALUE = 3;

    // [Execution]
    QNTreeWhiteBox<int> tree(EXPECTED_VALUE);

    // [Verification]
    pointer_uint_q uStoredValue = tree.GetMaximumChildren();
    BOOST_CHECK_EQUAL(uStoredValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that all the default values have not changed since the last time this test was executed.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_MAXIMUM_CHILDREN = 3;
    const pointer_uint_q EXPECTED_ROOT = QNTreeWhiteBox<int>::GetEndPositionForward();
    const pointer_uint_q EXPECTED_CAPACITY = 1;
    const pointer_uint_q EXPECTED_NODE_CAPACITY = EXPECTED_CAPACITY;

    // [Execution]
    QNTreeWhiteBox<int> tree(INPUT_MAXIMUM_CHILDREN);

    // [Verification]
    pointer_uint_q uStoredRoot = tree.GetRootPosition();
    pointer_uint_q uStoredCapacity = tree.GetCapacity();
    pointer_uint_q uStoredNodeCapacity = tree.GetNodeAllocator().GetPoolSize() / sizeof(QNTreeWhiteBox<int>::QNode);

    BOOST_CHECK_EQUAL(uStoredRoot, EXPECTED_ROOT);
    BOOST_CHECK_EQUAL(uStoredCapacity, EXPECTED_CAPACITY);
    BOOST_CHECK_EQUAL(uStoredNodeCapacity, EXPECTED_NODE_CAPACITY);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the maximum children equals zero.
/// </summary>
QTEST_CASE ( Constructor1_AssertionFailsWhenMaximumChildrenEqualsZero_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_ZERO = 0;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        QNTree<int> tree(INPUT_ZERO);
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
/// Checks that the value of input parameters are correctly stored.
/// </summary>
QTEST_CASE ( Constructor2_InputParametersAreCorrectlySet_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_MAXIMUM_CHILDREN = 3;
    const pointer_uint_q EXPECTED_CAPACITY = 5;

    // [Execution]
    QNTreeWhiteBox<int> tree(EXPECTED_MAXIMUM_CHILDREN, EXPECTED_CAPACITY);

    // [Verification]
    pointer_uint_q uStoredMaximumChildren = tree.GetMaximumChildren();
    pointer_uint_q uStoredCapacity = tree.GetCapacity();

    BOOST_CHECK_EQUAL(uStoredMaximumChildren, EXPECTED_MAXIMUM_CHILDREN);
    BOOST_CHECK_EQUAL(uStoredCapacity, EXPECTED_CAPACITY);
}

/// <summary>
/// Checks that all the default values have not changed since the last time this test was executed.
/// </summary>
QTEST_CASE ( Constructor2_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_MAXIMUM_CHILDREN = 3;
    const pointer_uint_q INPUT_CAPACITY = 5;
    const pointer_uint_q EXPECTED_ROOT = QNTreeWhiteBox<int>::GetEndPositionForward();
    const pointer_uint_q EXPECTED_NODE_CAPACITY = INPUT_CAPACITY;

    // [Execution]
    QNTreeWhiteBox<int> tree(INPUT_MAXIMUM_CHILDREN, INPUT_CAPACITY);

    // [Verification]
    const pointer_uint_q uStoredRoot = tree.GetRootPosition();
    const pointer_uint_q uStoredNodeCapacity = tree.GetNodeAllocator().GetPoolSize() / sizeof(QNTreeWhiteBox<int>::QNode);

    BOOST_CHECK_EQUAL(uStoredRoot, EXPECTED_ROOT);
    BOOST_CHECK_EQUAL(uStoredNodeCapacity, EXPECTED_NODE_CAPACITY);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the maximum children equals zero.
/// </summary>
QTEST_CASE ( Constructor2_AssertionFailsWhenMaximumChildrenEqualsZero_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_ZERO = 0;
    const pointer_uint_q CAPACITY = 3;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        QNTree<int> tree(INPUT_ZERO, CAPACITY);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the input capacity equals zero.
/// </summary>
QTEST_CASE ( Constructor2_AssertionFailsWhenCapacityEqualsZero_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_ZERO = 0;
    const pointer_uint_q MAXIMUM_CHILDREN = 3;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        QNTree<int> tree(MAXIMUM_CHILDREN, INPUT_ZERO);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // #if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the tree is correctly copied when it has elements.
/// </summary>
QTEST_CASE ( Constructor3_TreeIsCorrectlyCopiedWhenItHasElements_Test )
{
    // [Preparation]
    const char EXPECTED_VALUES[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    QNTree<char> TREE(3, 8);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParent2 = TREE.AddChild(itParent, 'B');
    TREE.AddChild(itParent2, 'C');
    TREE.AddChild(itParent2, 'D');
    TREE.AddChild(itParent2, 'E');
    TREE.AddChild(itParent, 'F');
    const pointer_uint_q EXPECTED_COUNT = TREE.GetCount();

    // [Execution]
    QNTree<char> copiedTree(TREE);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QNTree<char>::QNTreeIterator it = copiedTree.GetFirst(EQTreeTraversalOrder::E_DepthFirstPreOrder);
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    pointer_uint_q uCount = copiedTree.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the tree is correctly copied when it is empty.
/// </summary>
QTEST_CASE ( Constructor3_TreeIsCorrectlyCopiedWhenItIsEmpty_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 5);

    // [Execution]
    QNTree<char> copiedTree(TREE);

    // [Verification]
    bool bTreeIsEmpty = copiedTree.IsEmpty();
    BOOST_CHECK(bTreeIsEmpty);
}

/// <summary>
/// Checks that the copy constructors are called for each element.
/// </summary>
QTEST_CASE ( Constructor3_CopyConstructorsAreCalledForAllElements_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    QNTree<CallCounter> TREE(3, 5);
    TREE.SetRootValue(CallCounter());
    QNTree<CallCounter>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<CallCounter>::QNTreeIterator itParent2 = TREE.AddChild(itParent, CallCounter());
    TREE.AddChild(itParent2, CallCounter());
    TREE.AddChild(itParent2, CallCounter());
    TREE.AddChild(itParent2, CallCounter());
    TREE.AddChild(itParent, CallCounter());
    const unsigned int EXPECTED_VALUE = TREE.GetCount();
    CallCounter::ResetCounters();

    // [Execution]
    QNTree<CallCounter> copiedTree(TREE);

    // [Verification]
    unsigned int uNumberOfCalls = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uNumberOfCalls, EXPECTED_VALUE);
}

/// <summary>
/// Checks that all the default values have not changed since the last time this test was executed.
/// </summary>
QTEST_CASE ( Destructor_TheDestructorOfEveryElementIsCalled_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    const unsigned int EXPECTED_CALLS = 3;

    {
        QNTree<CallCounter> TREE(3, 5);
        TREE.SetRootValue(CallCounter());
        TREE.AddChild(TREE.GetRoot(EQTreeTraversalOrder::E_DepthFirstPreOrder), CallCounter());
        TREE.AddChild(TREE.GetRoot(EQTreeTraversalOrder::E_DepthFirstPreOrder), CallCounter());
        CallCounter::ResetCounters();

    // [Execution]
    // Destructor is called when the execution flow leaves this block
    }

    // [Verification]
    unsigned int uDestructorCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorCalls, EXPECTED_CALLS);
}

/// <summary>
/// Checks that the tree is correctly copied when it has elements and the destination tree is empty.
/// </summary>
QTEST_CASE ( OperatorAssignment_TreeIsCorrectlyCopiedWhenItHasElementsAndDestinationIsEmpty_Test )
{
    // [Preparation]
    const char EXPECTED_VALUES[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    QNTree<char> TREE(3, 8);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParent2 = TREE.AddChild(itParent, 'B');
    TREE.AddChild(itParent2, 'C');
    TREE.AddChild(itParent2, 'D');
    TREE.AddChild(itParent2, 'E');
    TREE.AddChild(itParent, 'F');
    const pointer_uint_q EXPECTED_COUNT = TREE.GetCount();
    QNTree<char> copiedTree(3, 8);

    // [Execution]
    copiedTree = TREE;

    // [Verification]
    bool bResultIsWhatEspected = true;

    QNTree<char>::QNTreeIterator it = copiedTree.GetFirst(EQTreeTraversalOrder::E_DepthFirstPreOrder);
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    pointer_uint_q uCount = copiedTree.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the tree is correctly copied when there are more elements in the source tree than in the destination.
/// </summary>
QTEST_CASE ( OperatorAssignment_TreeIsCorrectlyCopiedWhenThereAreMoreElementsInSourceThanInDestination_Test )
{
    // [Preparation]
    const char EXPECTED_VALUES[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    QNTree<char> TREE(3, 8);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParent2 = TREE.AddChild(itParent, 'B');
    TREE.AddChild(itParent2, 'C');
    TREE.AddChild(itParent2, 'D');
    TREE.AddChild(itParent2, 'E');
    TREE.AddChild(itParent, 'F');
    const pointer_uint_q EXPECTED_COUNT = TREE.GetCount();

    QNTree<char> copiedTree(3, 8);
    copiedTree.SetRootValue('G');
    QNTree<char>::QNTreeIterator itParent3 = copiedTree.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParent4 = copiedTree.AddChild(itParent3, 'H');
    copiedTree.AddChild(itParent4, 'I');

    // [Execution]
    copiedTree = TREE;

    // [Verification]
    bool bResultIsWhatEspected = true;

    QNTree<char>::QNTreeIterator it = copiedTree.GetFirst(EQTreeTraversalOrder::E_DepthFirstPreOrder);
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    pointer_uint_q uCount = copiedTree.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the tree is correctly copied when there are less elements in the source tree than in the destination.
/// </summary>
QTEST_CASE ( OperatorAssignment_TreeIsCorrectlyCopiedWhenThereAreLessElementsInSourceThanInDestination_Test )
{
    // [Preparation]
    const char EXPECTED_VALUES[] = {'A', 'B', 'C'};
    QNTree<char> TREE(3, 8);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParent2 = TREE.AddChild(itParent, 'B');
    TREE.AddChild(itParent2, 'C');
    const pointer_uint_q EXPECTED_COUNT = TREE.GetCount();

    QNTree<char> copiedTree(3, 8);
    copiedTree.SetRootValue('G');
    QNTree<char>::QNTreeIterator itParent3 = copiedTree.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParent4 = copiedTree.AddChild(itParent3, 'H');
    copiedTree.AddChild(itParent4, 'I');
    copiedTree.AddChild(itParent4, 'J');

    // [Execution]
    copiedTree = TREE;

    // [Verification]
    bool bResultIsWhatEspected = true;

    QNTree<char>::QNTreeIterator it = copiedTree.GetFirst(EQTreeTraversalOrder::E_DepthFirstPreOrder);
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    pointer_uint_q uCount = copiedTree.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the tree is correctly copied when there are the same number of elements in the source tree than in the destination.
/// </summary>
QTEST_CASE ( OperatorAssignment_TreeIsCorrectlyCopiedWhenThereAreSameNumberOfElementsInSourceThanInDestination_Test )
{
    // [Preparation]
    const char EXPECTED_VALUES[] = {'A', 'B', 'C'};
    QNTree<char> TREE(3, 8);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParent2 = TREE.AddChild(itParent, 'B');
    TREE.AddChild(itParent2, 'C');
    const pointer_uint_q EXPECTED_COUNT = TREE.GetCount();

    QNTree<char> copiedTree(3, 8);
    copiedTree.SetRootValue('G');
    QNTree<char>::QNTreeIterator itParent3 = copiedTree.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParent4 = copiedTree.AddChild(itParent3, 'H');
    copiedTree.AddChild(itParent4, 'I');

    // [Execution]
    copiedTree = TREE;

    // [Verification]
    bool bResultIsWhatEspected = true;

    QNTree<char>::QNTreeIterator it = copiedTree.GetFirst(EQTreeTraversalOrder::E_DepthFirstPreOrder);
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    pointer_uint_q uCount = copiedTree.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the tree is correctly copied when it is empty and the destination tree has elements.
/// </summary>
QTEST_CASE ( OperatorAssignment_TreeIsCorrectlyCopiedWhenItIsEmptyAndDestinationHasElements_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 8);
    QNTree<char> copiedTree(3, 8);
    copiedTree.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = copiedTree.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParent2 = copiedTree.AddChild(itParent, 'B');
    copiedTree.AddChild(itParent2, 'C');
    copiedTree.AddChild(itParent2, 'D');
    copiedTree.AddChild(itParent2, 'E');
    copiedTree.AddChild(itParent, 'F');

    // [Execution]
    copiedTree = TREE;

    // [Verification]
    bool bTreeIsEmpty = copiedTree.IsEmpty();
    BOOST_CHECK(bTreeIsEmpty);
}

/// <summary>
/// Checks that the copy constructors are called for each element.
/// </summary>
QTEST_CASE ( OperatorAssignment_CopyConstructorsAreCalledForAllElements_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    QNTree<CallCounter> TREE(3, 8);
    TREE.SetRootValue(CallCounter());
    QNTree<CallCounter>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<CallCounter>::QNTreeIterator itParent2 = TREE.AddChild(itParent, CallCounter());
    TREE.AddChild(itParent2, CallCounter());
    TREE.AddChild(itParent2, CallCounter());
    TREE.AddChild(itParent2, CallCounter());
    TREE.AddChild(itParent, CallCounter());

    QNTree<CallCounter> copiedTree(3, 8);
    copiedTree.SetRootValue(CallCounter());
    QNTree<CallCounter>::QNTreeIterator itParent3 = copiedTree.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<CallCounter>::QNTreeIterator itParent4 = copiedTree.AddChild(itParent3, CallCounter());
    copiedTree.AddChild(itParent4, CallCounter());

    const unsigned int EXPECTED_COPY_CONSTRUCTORS_VALUE = TREE.GetCount();
    CallCounter::ResetCounters();

    // [Execution]
    copiedTree = TREE;

    // [Verification]
    unsigned int uNumberOfCalls = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uNumberOfCalls, EXPECTED_COPY_CONSTRUCTORS_VALUE);
}

/// <summary>
/// Checks that the destructors are called for each element.
/// </summary>
QTEST_CASE ( OperatorAssignment_DestructorsAreCalledForAllElements_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    QNTree<CallCounter> TREE(3, 8);
    TREE.SetRootValue(CallCounter());
    QNTree<CallCounter>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<CallCounter>::QNTreeIterator itParent2 = TREE.AddChild(itParent, CallCounter());
    TREE.AddChild(itParent2, CallCounter());
    TREE.AddChild(itParent2, CallCounter());
    TREE.AddChild(itParent2, CallCounter());
    TREE.AddChild(itParent, CallCounter());

    QNTree<CallCounter> copiedTree(3, 8);
    copiedTree.SetRootValue(CallCounter());
    QNTree<CallCounter>::QNTreeIterator itParent3 = copiedTree.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<CallCounter>::QNTreeIterator itParent4 = copiedTree.AddChild(itParent3, CallCounter());
    copiedTree.AddChild(itParent4, CallCounter());

    const unsigned int EXPECTED_DESTRUCTORS_VALUE = copiedTree.GetCount();
    CallCounter::ResetCounters();

    // [Execution]
    copiedTree = TREE;

    // [Verification]
    unsigned int uNumberOfCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uNumberOfCalls, EXPECTED_DESTRUCTORS_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when trees have different maximum children values.
/// </summary>
QTEST_CASE ( OperatorAssignment_AssertionFailsWhenTreesHaveDifferentMaximumChildrenValues_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 2);
    QNTree<char> copiedTree(1, 2);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        copiedTree = TREE;
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <sumary>
/// Checks that it returns True when trees are exactly equal.
/// </sumary>
QTEST_CASE( OperatorEquality_ReturnsTrueWhenTreesAreExactlyEqual_Test )
{
    // [Preparation]
    QNTree<char> TREE1(3, 8);
    TREE1.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE1.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParent2 = TREE1.AddChild(itParent, 'B');
    TREE1.AddChild(itParent2, 'C');
    TREE1.AddChild(itParent2, 'D');
    TREE1.AddChild(itParent2, 'E');
    TREE1.AddChild(itParent, 'F');

    QNTree<char> TREE2 = TREE1;

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = TREE1 == TREE2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when trees are the same instance.
/// </sumary>
QTEST_CASE( OperatorEquality_ReturnsTrueWhenTreesAreSameInstance_Test )
{
    // [Preparation]
    QNTree<char> TREE1(3, 8);
    TREE1.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE1.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParent2 = TREE1.AddChild(itParent, 'B');
    TREE1.AddChild(itParent2, 'C');
    TREE1.AddChild(itParent2, 'D');
    TREE1.AddChild(itParent2, 'E');
    TREE1.AddChild(itParent, 'F');
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = TREE1 == TREE1;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when trees have the same structure but elements are not equal.
/// </sumary>
QTEST_CASE( OperatorEquality_ReturnsFalseWhenTreesHaveSameStructureButElementsAreNotEqual_Test )
{
    // [Preparation]
    QNTree<char> TREE1(3, 8);
    TREE1.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE1.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParent2 = TREE1.AddChild(itParent, 'B');
    TREE1.AddChild(itParent2, 'C');
    TREE1.AddChild(itParent2, 'D');
    TREE1.AddChild(itParent2, 'E');
    TREE1.AddChild(itParent, 'F');

    QNTree<char> TREE2(3, 8);
    TREE2.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent3 = TREE2.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParent4 = TREE2.AddChild(itParent3, 'B');
    TREE2.AddChild(itParent4, 'C');
    TREE2.AddChild(itParent4, 'X');
    TREE2.AddChild(itParent4, 'E');
    TREE2.AddChild(itParent3, 'F');

    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = TREE1 == TREE2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when trees have the same values but with a different structure.
/// </sumary>
QTEST_CASE( OperatorEquality_ReturnsFalseWhenTreesAreHaveSameValuesButDifferentStructure_Test )
{
    // [Preparation]
    QNTree<char> TREE1(8, 8);
    TREE1.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE1.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParent2 = TREE1.AddChild(itParent, 'B');
    TREE1.AddChild(itParent2, 'C');
    TREE1.AddChild(itParent2, 'D');
    TREE1.AddChild(itParent2, 'E');
    TREE1.AddChild(itParent, 'F');

    QNTree<char> TREE2(8, 8);
    TREE2.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent3 = TREE2.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE2.AddChild(itParent3, 'B');
    TREE2.AddChild(itParent3, 'C');
    TREE2.AddChild(itParent3, 'D');
    TREE2.AddChild(itParent3, 'E');
    TREE2.AddChild(itParent3, 'F');

    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = TREE1 == TREE2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when trees have different number of elements although elements are equal.
/// </sumary>
QTEST_CASE( OperatorEquality_ReturnsFalseWhenTreesHaveDifferentNumberOfElementsAlthoughElementsAreEqual_Test )
{
    // [Preparation]
    QNTree<char> TREE1(3, 8);
    TREE1.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE1.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParent2 = TREE1.AddChild(itParent, 'B');
    TREE1.AddChild(itParent2, 'C');
    TREE1.AddChild(itParent2, 'D');
    TREE1.AddChild(itParent2, 'E');
    TREE1.AddChild(itParent, 'F');

    QNTree<char> TREE2(3, 8);
    TREE2.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent3 = TREE2.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE2.AddChild(itParent3, 'B');

    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = TREE1 == TREE2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when trees are exactly equal.
/// </sumary>
QTEST_CASE( OperatorInequality_ReturnsFalseWhenTreesAreExactlyEqual_Test )
{
    // [Preparation]
    QNTree<char> TREE1(3, 8);
    TREE1.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE1.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParent2 = TREE1.AddChild(itParent, 'B');
    TREE1.AddChild(itParent2, 'C');
    TREE1.AddChild(itParent2, 'D');
    TREE1.AddChild(itParent2, 'E');
    TREE1.AddChild(itParent, 'F');

    QNTree<char> TREE2 = TREE1;

    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = TREE1 != TREE2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when trees are the same instance.
/// </sumary>
QTEST_CASE( OperatorInequality_ReturnsFalseWhenTreesAreSameInstance_Test )
{
    // [Preparation]
    QNTree<char> TREE1(3, 8);
    TREE1.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE1.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParent2 = TREE1.AddChild(itParent, 'B');
    TREE1.AddChild(itParent2, 'C');
    TREE1.AddChild(itParent2, 'D');
    TREE1.AddChild(itParent2, 'E');
    TREE1.AddChild(itParent, 'F');
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = TREE1 != TREE1;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when trees have the same structure but elements are not equal.
/// </sumary>
QTEST_CASE( OperatorInequality_ReturnsTrueWhenTreesHaveSameStructureButElementsAreNotEqual_Test )
{
    // [Preparation]
    QNTree<char> TREE1(3, 8);
    TREE1.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE1.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParent2 = TREE1.AddChild(itParent, 'B');
    TREE1.AddChild(itParent2, 'C');
    TREE1.AddChild(itParent2, 'D');
    TREE1.AddChild(itParent2, 'E');
    TREE1.AddChild(itParent, 'F');

    QNTree<char> TREE2(3, 8);
    TREE2.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent3 = TREE2.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParent4 = TREE2.AddChild(itParent3, 'B');
    TREE2.AddChild(itParent4, 'C');
    TREE2.AddChild(itParent4, 'X');
    TREE2.AddChild(itParent4, 'E');
    TREE2.AddChild(itParent3, 'F');

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = TREE1 != TREE2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when trees have the same values but with a different structure.
/// </sumary>
QTEST_CASE( OperatorInequality_ReturnsTrueWhenTreesAreHaveSameValuesButDifferentStructure_Test )
{
    // [Preparation]
    QNTree<char> TREE1(8, 8);
    TREE1.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE1.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParent2 = TREE1.AddChild(itParent, 'B');
    TREE1.AddChild(itParent2, 'C');
    TREE1.AddChild(itParent2, 'D');
    TREE1.AddChild(itParent2, 'E');
    TREE1.AddChild(itParent, 'F');

    QNTree<char> TREE2(8, 8);
    TREE2.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent3 = TREE2.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE2.AddChild(itParent3, 'B');
    TREE2.AddChild(itParent3, 'C');
    TREE2.AddChild(itParent3, 'D');
    TREE2.AddChild(itParent3, 'E');
    TREE2.AddChild(itParent3, 'F');

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = TREE1 != TREE2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when trees have different number of elements although elements are equal.
/// </sumary>
QTEST_CASE( OperatorInequality_ReturnsTrueWhenTreesHaveDifferentNumberOfElementsAlthoughElementsAreEqual_Test )
{
    // [Preparation]
    QNTree<char> TREE1(3, 8);
    TREE1.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE1.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParent2 = TREE1.AddChild(itParent, 'B');
    TREE1.AddChild(itParent2, 'C');
    TREE1.AddChild(itParent2, 'D');
    TREE1.AddChild(itParent2, 'E');
    TREE1.AddChild(itParent, 'F');

    QNTree<char> TREE2(3, 8);
    TREE2.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent3 = TREE2.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE2.AddChild(itParent3, 'B');

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = TREE1 != TREE2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the capacity is correctly increased.
/// </summary>
QTEST_CASE ( Reserve_CapacityIsCorrectlyIncreased_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_CAPACITY = 4;
    QNTree<int> TREE(2, 2);

    // [Execution]
    TREE.Reserve(EXPECTED_CAPACITY);

    // [Verification]
    pointer_uint_q uStoredCapacity = TREE.GetCapacity();

    BOOST_CHECK_EQUAL(uStoredCapacity, EXPECTED_CAPACITY);
}

/// <summary>
/// Checks that elements are correctly reallocated.
/// </summary>
QTEST_CASE ( Reserve_ElementsAreCorrectlyReallocated_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_CAPACITY = 4;
    const int EXPECTED_FIRST_ELEMENT = 1;
    const int EXPECTED_SECOND_ELEMENT = 2;
    QNTree<int> TREE(2, 2);
    TREE.SetRootValue(EXPECTED_FIRST_ELEMENT);
    TREE.AddChild(TREE.GetRoot(EQTreeTraversalOrder::E_DepthFirstPreOrder), EXPECTED_SECOND_ELEMENT);

    // [Execution]
    TREE.Reserve(INPUT_CAPACITY); // A reallocation occurs

    // [Verification]
    QNTree<int>::QNTreeIterator it = TREE.GetRoot(EQTreeTraversalOrder::E_DepthFirstPreOrder);
    BOOST_CHECK_EQUAL(*it, EXPECTED_FIRST_ELEMENT);
    ++it;
    BOOST_CHECK_EQUAL(*it, EXPECTED_SECOND_ELEMENT);
}

/// <summary>
/// Checks that elements are not reallocated and capacity does not change when attempting to reserve less memory than current reserved.
/// </summary>
QTEST_CASE ( Reserve_NothingHappensWhenTheAmountToReserveIsNoGreaterThanCurrentCapacity_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_CAPACITY = 1;
    const pointer_uint_q EXPECTED_CAPACITY = 4;
    QNTree<int> TREE(4, 4);
    TREE.SetRootValue(1);
    int* EXPECTED_LOCATION_OF_ELEMENT = &(*TREE.GetRoot(EQTreeTraversalOrder::E_DepthFirstPreOrder));

    // [Execution]
    TREE.Reserve(INPUT_CAPACITY); // A reallocation occurs

    // [Verification]
    pointer_uint_q uCapacity = TREE.GetCapacity();
    TREE.SetRootValue(1);
    int* pLocationOfElement = &(*TREE.GetRoot(EQTreeTraversalOrder::E_DepthFirstPreOrder));

    BOOST_CHECK_EQUAL(uCapacity, EXPECTED_CAPACITY);
    BOOST_CHECK_EQUAL(pLocationOfElement, EXPECTED_LOCATION_OF_ELEMENT);
}

/// <summary>
/// Checks that the element is correctly copied when the tree is empty.
/// </summary>
QTEST_CASE ( SetRootValue_RootNodeIsCorrectlyCopiedWhenTreeIsEmpty_Test )
{
    // [Preparation]
    const int EXPECTED_ELEMENT = 1;
    QNTree<int> TREE(2, 2);

    // [Execution]
    TREE.SetRootValue(EXPECTED_ELEMENT);

    // [Verification]
    int nElementValue = *TREE.GetRoot(EQTreeTraversalOrder::E_DepthFirstPreOrder);

    BOOST_CHECK_EQUAL(nElementValue, EXPECTED_ELEMENT);
}

/// <summary>
/// Checks that the element is correctly copied when the tree is not empty.
/// </summary>
QTEST_CASE ( SetRootValue_RootNodeIsCorrectlyCopiedWhenTreeIsNotEmpty_Test )
{
    // [Preparation]
    const int EXPECTED_ELEMENT = 1;
    const int ORIGINAL_ELEMENT = 2;
    QNTree<int> TREE(2, 2);
    TREE.SetRootValue(ORIGINAL_ELEMENT);

    // [Execution]
    TREE.SetRootValue(EXPECTED_ELEMENT);

    // [Verification]
    int nElementValue = *TREE.GetRoot(EQTreeTraversalOrder::E_DepthFirstPreOrder);

    BOOST_CHECK_EQUAL(nElementValue, EXPECTED_ELEMENT);
}

/// <summary>
/// Checks that the copy constructor of the element is called when the tree is empty.
/// </summary>
QTEST_CASE ( SetRootValue_CopyConstructorOfElementIsCalledWhenTreeIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    CallCounter::ResetCounters();
    const unsigned int EXPECTED_CALLS_TO_COPY_CONSTRUCTOR = 1;
    QNTree<CallCounter> TREE(2, 2);

    // [Execution]
    TREE.SetRootValue(CallCounter());

    // [Verification]
    unsigned int uCopyConstructorCalls = CallCounter::GetCopyConstructorCallsCount();

    BOOST_CHECK_EQUAL(uCopyConstructorCalls, EXPECTED_CALLS_TO_COPY_CONSTRUCTOR);
}

/// <summary>
/// Checks that the assignment operator of the element is called when the tree is not empty.
/// </summary>
QTEST_CASE ( SetRootValue_AssignmentOperatorOfElementIsCalledWhenTreeIsNotEmpty_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    CallCounter::ResetCounters();
    const unsigned int EXPECTED_CALLS_TO_ASSIGNMENT_OPERATOR = 1;
    QNTree<CallCounter> TREE(2, 2);
    TREE.SetRootValue(CallCounter());

    // [Execution]
    TREE.SetRootValue(CallCounter());

    // [Verification]
    unsigned int uAssignmentOperatorCalls = CallCounter::GetAssignmentCallsCount();

    BOOST_CHECK_EQUAL(uAssignmentOperatorCalls, EXPECTED_CALLS_TO_ASSIGNMENT_OPERATOR);
}

/// <summary>
/// Checks that the element is added when the parent node has no children.
/// </summary>
QTEST_CASE ( AddChild_ElementIsAddedWhenNodeHasNoChildren_Test )
{
    // [Preparation]
    const char EXPECTED_VALUES[] = {'A', 'B'};
    QNTree<char> TREE(3, 3);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);

    // [Execution]
    TREE.AddChild(itParent, 'B');

    // [Verification]
    bool bResultIsWhatEspected = true;

    QNTree<char>::QNTreeIterator it = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is added when the parent node has one child node only.
/// </summary>
QTEST_CASE ( AddChild_ElementIsAddedWhenNodeHasOnlyOneChild_Test )
{
    // [Preparation]
    const char EXPECTED_VALUES[] = {'A', 'B', 'C'};
    QNTree<char> TREE(3, 3);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itParent, 'B');

    // [Execution]
    TREE.AddChild(itParent, 'C');

    // [Verification]
    bool bResultIsWhatEspected = true;

    QNTree<char>::QNTreeIterator it = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is added when the parent node has more than one child node.
/// </summary>
QTEST_CASE ( AddChild_ElementIsAddedWhenNodeHasMoreThanOneChild_Test )
{
    // [Preparation]
    const char EXPECTED_VALUES[] = {'A', 'B', 'C', 'D'};
    QNTree<char> TREE(3, 4);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itParent, 'B');
    TREE.AddChild(itParent, 'C');
    
    // [Execution]
    TREE.AddChild(itParent, 'D');
    
    // [Verification]
    bool bResultIsWhatEspected = true;

    QNTree<char>::QNTreeIterator it = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];
        
    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element count is incremented when an element is added.
/// </summary>
QTEST_CASE ( AddChild_CountIsIncrementedWhenElementIsAdded_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 3);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    const pointer_uint_q ORIGINAL_COUNT = TREE.GetCount();

    // [Execution]
    TREE.AddChild(itParent, 'B');

    // [Verification]
    pointer_uint_q uCount = TREE.GetCount();
    BOOST_CHECK(uCount > ORIGINAL_COUNT);
}

/// <summary>
/// Checks that the capacity is incremented when an element is added and the capacity was full.
/// </summary>
QTEST_CASE ( AddChild_CapacityIsIncrementedWhenElementIsAddedAndCapacityWasFull_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 1);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    const pointer_uint_q ORIGINAL_CAPACITY = TREE.GetCapacity();

    // [Execution]
    TREE.AddChild(itParent, 'B');

    // [Verification]
    pointer_uint_q uCapacity = TREE.GetCapacity();
    BOOST_CHECK(uCapacity > ORIGINAL_CAPACITY);
}

/// <summary>
/// Checks that the returned iterator points to the added node.
/// </summary>
QTEST_CASE ( AddChild_ReturnedIteratorPointsToAddedNode_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 3);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    const char EXPECTED_NODE_VALUE = 'B';

    // [Execution]
    QNTree<char>::QNTreeIterator itResult = TREE.AddChild(itParent, EXPECTED_NODE_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(*itResult, EXPECTED_NODE_VALUE);
}

/// <summary>
/// Checks that the copy constructor of the added element is called.
/// </summary>
QTEST_CASE ( AddChild_CopyConstructorIsCalled_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    QNTree<CallCounter> TREE(3, 5);
    TREE.SetRootValue(CallCounter());
    QNTree<CallCounter>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    const unsigned int EXPECTED_CALLS = 1;
    CallCounter::ResetCounters();

    // [Execution]
    TREE.AddChild(itParent, CallCounter());

    // [Verification]
    unsigned int uCopyConstructorCalls = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uCopyConstructorCalls, EXPECTED_CALLS);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when adding more nodes than the maximum allowed.
/// </summary>
QTEST_CASE ( AddChild_AssertionFailsWhenExceedingMaximumNodes_Test )
{
    // [Preparation]
    QNTree<char> TREE(2, 4);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itParent, 'B');
    TREE.AddChild(itParent, 'C');

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        TREE.AddChild(itParent, 'D');
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the input node points to an end position.
/// </summary>
QTEST_CASE ( AddChild_AssertionFailsWhenInputNodePointsToEndPosition_Test )
{
    // [Preparation]
    QNTree<char> TREE(2, 4);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    ++itParent;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        TREE.AddChild(itParent, 'B');
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the node is not added when the maximum has been reached.
/// </summary>
QTEST_CASE ( AddChild_NothingHappensWhenExceedingMaximumNodes_Test )
{
    // [Preparation]
    const char EXPECTED_VALUES[] = {'A', 'B', 'C'};
    QNTree<char> TREE(2, 1);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itParent, 'B');
    TREE.AddChild(itParent, 'C');

    // [Execution]
    TREE.AddChild(itParent, 'D');

    // [Verification]
    bool bResultIsWhatEspected = true;

    QNTree<char>::QNTreeIterator it = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the result iterator points to an end position when the maximum has been reached.
/// </summary>
QTEST_CASE ( AddChild_ResultIteratorPointsToEndWhenExceedingMaximumNodes_Test )
{
    // [Preparation]
    QNTree<char> TREE(2, 1);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itParent, 'B');
    TREE.AddChild(itParent, 'C');
    const bool RESULT_IS_END = true;

    // [Execution]
    QNTree<char>::QNTreeIterator itResult = TREE.AddChild(itParent, 'D');

    // [Verification]
    BOOST_CHECK_EQUAL(itResult.IsEnd(), RESULT_IS_END);
}

#endif

/// <summary>
/// Checks that the element is correctly removed when it is the last child and it has no children.
/// </summary>
QTEST_CASE ( Remove_ElementIsRemovedWhenItIsLastChildAndHasNoChildren_Test )
{
    // [Preparation]
    const char EXPECTED_VALUES[] = {'A', 'B'};
    QNTree<char> TREE(3, 3);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParentNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itParentNode, 'B');
    QNTree<char>::QNTreeIterator itNode = TREE.AddChild(itParentNode, 'C');

    // [Execution]
    TREE.Remove(itNode);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QNTree<char>::QNTreeIterator it = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the entire tree is removed when removing the root node.
/// </summary>
QTEST_CASE ( Remove_TheEntireTreeIsRemovedWhenRemovingRootNode_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 8);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParentNode1 = TREE.AddChild(itRootNode, 'B');
    QNTree<char>::QNTreeIterator itParentNode2 = TREE.AddChild(itRootNode, 'F');
    TREE.AddChild(itParentNode1, 'C');
    TREE.AddChild(itParentNode1, 'D');
    TREE.AddChild(itParentNode1, 'E');
    TREE.AddChild(itParentNode2, 'G');

    const bool TREE_IS_EMPTY = true;

    // [Execution]
    TREE.Remove(itRootNode);

    // [Verification]
    bool bIsEmpty = TREE.IsEmpty();
    BOOST_CHECK_EQUAL(bIsEmpty, TREE_IS_EMPTY);
}

/// <summary>
/// Checks that the element is correctly removed when it is the root node and there are no more elements in the tree.
/// </summary>
QTEST_CASE ( Remove_ElementIsRemovedWhenItIsTheRootAndThereAreNoMoreElements_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    const bool TREE_IS_EMPTY = true;

    // [Execution]
    TREE.Remove(itRootNode);

    // [Verification]
    bool bIsEmpty = TREE.IsEmpty();
    BOOST_CHECK_EQUAL(bIsEmpty, TREE_IS_EMPTY);
}

/// <summary>
/// Checks that the element is correctly removed when it has parent.
/// </summary>
QTEST_CASE ( Remove_ElementIsRemovedWhenItHasParent_Test )
{
    // [Preparation]
    const char EXPECTED_VALUES[] = {'A'};
    QNTree<char> TREE(3, 3);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParentNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itNode = TREE.AddChild(itParentNode, 'B');

    // [Execution]
    TREE.Remove(itNode);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QNTree<char>::QNTreeIterator it = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly removed when it has parent and children.
/// </summary>
QTEST_CASE ( Remove_ElementIsRemovedWhenItHasParentAndChildren_Test )
{
    // [Preparation]
    const char EXPECTED_VALUES[] = {'A'};
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParentNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itNode = TREE.AddChild(itParentNode, 'B');
    TREE.AddChild(itNode, 'C');
    TREE.AddChild(itNode, 'D');
    TREE.AddChild(itNode, 'E');

    // [Execution]
    TREE.Remove(itNode);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QNTree<char>::QNTreeIterator it = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly removed when it has parent and one child.
/// </summary>
QTEST_CASE ( Remove_ElementIsRemovedWhenItHasParentAndOneChild_Test )
{
    // [Preparation]
    const char EXPECTED_VALUES[] = {'A'};
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParentNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itNode = TREE.AddChild(itParentNode, 'B');
    TREE.AddChild(itNode, 'C');

    // [Execution]
    TREE.Remove(itNode);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QNTree<char>::QNTreeIterator it = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly removed when it has parent and brother.
/// </summary>
QTEST_CASE ( Remove_ElementIsRemovedWhenItHasParentAndBrother_Test )
{
    // [Preparation]
    const char EXPECTED_VALUES[] = {'A', 'C'};
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParentNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itNode = TREE.AddChild(itParentNode, 'B');
    TREE.AddChild(itParentNode, 'C');

    // [Execution]
    TREE.Remove(itNode);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QNTree<char>::QNTreeIterator it = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the returned iterator points to the next node.
/// </summary>
QTEST_CASE ( Remove_ReturnsIteratorThatPointsToNextNode_Test )
{
    // [Preparation]
    const char EXPECTED_VALUE = 'C';
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParentNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itNode = TREE.AddChild(itParentNode, 'B');
    TREE.AddChild(itParentNode, EXPECTED_VALUE);

    // [Execution]
    QNTree<char>::QNTreeIterator itResult = TREE.Remove(itNode);

    // [Verification]
    BOOST_CHECK_EQUAL(*itResult, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the returned iterator points to an end position.
/// </summary>
QTEST_CASE ( Remove_ReturnsIteratorThatPointsToEndPosition_Test )
{
    // [Preparation]
    const bool POINTS_TO_END_POSITION = true;
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParentNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itNode = TREE.AddChild(itParentNode, 'B');

    // [Execution]
    QNTree<char>::QNTreeIterator itResult = TREE.Remove(itNode);

    // [Verification]
    bool bIsEnd = itResult.IsEnd();
    BOOST_CHECK_EQUAL(bIsEnd, POINTS_TO_END_POSITION);
}

/// <summary>
/// Checks that the destructor of all the removed elements is called.
/// </summary>
QTEST_CASE ( Remove_DestructorsAreCalled_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    QNTree<CallCounter> TREE(3, 5);
    TREE.SetRootValue(CallCounter());
    QNTree<CallCounter>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itParent, CallCounter());
    TREE.AddChild(itParent, CallCounter());
    const unsigned int EXPECTED_CALLS = 3;
    CallCounter::ResetCounters();

    // [Execution]
    TREE.Remove(itParent);

    // [Verification]
    unsigned int uDestructorCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorCalls, EXPECTED_CALLS);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to an end position.
/// </summary>
QTEST_CASE ( Remove_AssertionFailsWhenInputIteratorPointsToEndPosition_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    ++itRootNode;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        TREE.Remove(itRootNode);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the tree is empty.
/// </summary>
QTEST_CASE ( Remove_AssertionFailsWhenTreeIsEmpty_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.Remove(itRootNode);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        TREE.Remove(itRootNode);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that the element is correctly removed when it is the last child and it has no children.
/// </summary>
QTEST_CASE ( RemoveChild_ElementIsRemoveChilddWhenItIsLastChildAndHasNoChildren_Test )
{
    // [Preparation]
    const char EXPECTED_VALUES[] = {'A', 'B'};
    QNTree<char> TREE(3, 3);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParentNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itParentNode, 'B');
    TREE.AddChild(itParentNode, 'C');
    const pointer_uint_q POSITION = 1;

    // [Execution]
    TREE.RemoveChild(itParentNode, POSITION);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QNTree<char>::QNTreeIterator it = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly removed when it is in the middle and it has no children.
/// </summary>
QTEST_CASE ( RemoveChild_ElementIsRemoveChilddWhenItIsInTheMiddleAndHasNoChildren_Test )
{
    // [Preparation]
    const char EXPECTED_VALUES[] = {'A', 'B', 'D'};
    QNTree<char> TREE(3, 4);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParentNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itParentNode, 'B');
    TREE.AddChild(itParentNode, 'C');
    TREE.AddChild(itParentNode, 'D');
    const pointer_uint_q POSITION = 1;

    // [Execution]
    TREE.RemoveChild(itParentNode, POSITION);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QNTree<char>::QNTreeIterator it = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly removed when it is the first and it has no children.
/// </summary>
QTEST_CASE ( RemoveChild_ElementIsRemoveChilddWhenItIsTheFirstAndHasNoChildren_Test )
{
    // [Preparation]
    const char EXPECTED_VALUES[] = {'A', 'C', 'D'};
    QNTree<char> TREE(3, 4);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParentNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itParentNode, 'B');
    TREE.AddChild(itParentNode, 'C');
    TREE.AddChild(itParentNode, 'D');
    const pointer_uint_q POSITION = 0;

    // [Execution]
    TREE.RemoveChild(itParentNode, POSITION);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QNTree<char>::QNTreeIterator it = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the entire subtree is removed when removing the a node.
/// </summary>
QTEST_CASE ( RemoveChild_TheEntireSubtreeIsRemovedWhenRemovingNode_Test )
{
    // [Preparation]
    const char EXPECTED_VALUES[] = {'A', 'F', 'G'};

    QNTree<char> TREE(3, 8);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParentNode1 = TREE.AddChild(itRootNode, 'B');
    QNTree<char>::QNTreeIterator itParentNode2 = TREE.AddChild(itRootNode, 'F');
    TREE.AddChild(itParentNode1, 'C');
    TREE.AddChild(itParentNode1, 'D');
    TREE.AddChild(itParentNode1, 'E');
    TREE.AddChild(itParentNode2, 'G');
    const pointer_uint_q POSITION = 0;

    // [Execution]
    TREE.RemoveChild(itRootNode, POSITION);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QNTree<char>::QNTreeIterator it = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly removed when it has one child.
/// </summary>
QTEST_CASE ( RemoveChild_ElementIsRemovedWhenItHasOneChild_Test )
{
    // [Preparation]
    const char EXPECTED_VALUES[] = {'A'};
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParentNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itParentNode, 'B');
    const pointer_uint_q POSITION = 0;

    // [Execution]
    TREE.RemoveChild(itParentNode, POSITION);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QNTree<char>::QNTreeIterator it = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the destructor of all the removed elements is called.
/// </summary>
QTEST_CASE ( RemoveChild_DestructorsAreCalled_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    QNTree<CallCounter> TREE(3, 5);
    TREE.SetRootValue(CallCounter());
    QNTree<CallCounter>::QNTreeIterator itRoot = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<CallCounter>::QNTreeIterator itParent = TREE.AddChild(itRoot, CallCounter());
    TREE.AddChild(itParent, CallCounter());
    TREE.AddChild(itParent, CallCounter());
    const unsigned int EXPECTED_CALLS = 3;
    const pointer_uint_q POSITION = 0;
    CallCounter::ResetCounters();

    // [Execution]
    TREE.RemoveChild(itRoot, POSITION);

    // [Verification]
    unsigned int uDestructorCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorCalls, EXPECTED_CALLS);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to an end position.
/// </summary>
QTEST_CASE ( RemoveChild_AssertionFailsWhenInputIteratorPointsToEndPosition_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    ++itRootNode;
    const pointer_uint_q POSITION = 0;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        TREE.RemoveChild(itRootNode, POSITION);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the tree is empty.
/// </summary>
QTEST_CASE ( RemoveChild_AssertionFailsWhenTreeIsEmpty_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.Remove(itRootNode);
    const pointer_uint_q POSITION = 0;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        TREE.RemoveChild(itRootNode, POSITION);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the child position does not exist.
/// </summary>
QTEST_CASE ( RemoveChild_AssertionFailsWhenPositionDoesNotExist_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itRootNode, 'B');
    TREE.AddChild(itRootNode, 'C');
    const pointer_uint_q POSITION = 2;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        TREE.RemoveChild(itRootNode, POSITION);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the node has no children.
/// </summary>
QTEST_CASE ( RemoveChild_AssertionFailsWhenNodeHasNoChildren_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    const pointer_uint_q POSITION = 0;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        TREE.RemoveChild(itRootNode, POSITION);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that the element is correctly inserted at the first position when the parent node has only one child.
/// </summary>
QTEST_CASE ( InsertChild_ElementIsInsertedAtFirstPositionWhenNodeHasOnlyOneChild_Test )
{
    // [Preparation]
    const char EXPECTED_VALUES[] = {'A', 'C', 'B'};
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itParent, 'B');
    const pointer_uint_q POSITION = 0;

    // [Execution]
    TREE.InsertChild(itParent, 'C', POSITION);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QNTree<char>::QNTreeIterator it = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly inserted at the first position when the parent node has more than one child.
/// </summary>
QTEST_CASE ( InsertChild_ElementIsInsertedAtFirstPositionWhenNodeHasMoreThanOneChild_Test )
{
    // [Preparation]
    const char EXPECTED_VALUES[] = {'A', 'D', 'B', 'C'};
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itParent, 'B');
    TREE.AddChild(itParent, 'C');
    const pointer_uint_q POSITION = 0;

    // [Execution]
    TREE.InsertChild(itParent, 'D', POSITION);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QNTree<char>::QNTreeIterator it = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly inserted in the middle.
/// </summary>
QTEST_CASE ( InsertChild_ElementIsInsertedInTheMiddle_Test )
{
    // [Preparation]
    const char EXPECTED_VALUES[] = {'A', 'B', 'D', 'C'};
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itParent, 'B');
    TREE.AddChild(itParent, 'C');
    const pointer_uint_q POSITION = 1;

    // [Execution]
    TREE.InsertChild(itParent, 'D', POSITION);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QNTree<char>::QNTreeIterator it = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the copy constructor of the inserted element is called.
/// </summary>
QTEST_CASE ( InsertChild_CopyConstructorIsCalled_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    QNTree<CallCounter> TREE(3, 5);
    TREE.SetRootValue(CallCounter());
    QNTree<CallCounter>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itParent, CallCounter());
    TREE.AddChild(itParent, CallCounter());
    const pointer_uint_q POSITION = 1;
    const unsigned int EXPECTED_CALLS = 1;
    CallCounter::ResetCounters();

    // [Execution]
    TREE.InsertChild(itParent, CallCounter(), POSITION);

    // [Verification]
    unsigned int uCopyConstructorCalls = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uCopyConstructorCalls, EXPECTED_CALLS);
}

/// <summary>
/// Checks that the element count is incremented when an element is added.
/// </summary>
QTEST_CASE ( InsertChild_CountIsIncrementedWhenElementIsAdded_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 3);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itParent, 'B');
    const pointer_uint_q ORIGINAL_COUNT = TREE.GetCount();
    const pointer_uint_q POSITION = 0;

    // [Execution]
    TREE.InsertChild(itParent, 'C', POSITION);

    // [Verification]
    pointer_uint_q uCount = TREE.GetCount();
    BOOST_CHECK(uCount > ORIGINAL_COUNT);
}

/// <summary>
/// Checks that the capacity is incremented when an element is added and the capacity was full.
/// </summary>
QTEST_CASE ( InsertChild_CapacityIsIncrementedWhenElementIsAddedAndCapacityWasFull_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 2);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itParent, 'B');
    const pointer_uint_q ORIGINAL_CAPACITY = TREE.GetCapacity();
    const pointer_uint_q POSITION = 0;

    // [Execution]
    TREE.InsertChild(itParent, 'C', POSITION);

    // [Verification]
    pointer_uint_q uCapacity = TREE.GetCapacity();
    BOOST_CHECK(uCapacity > ORIGINAL_CAPACITY);
}

/// <summary>
/// Checks that the returned iterator points to the added node.
/// </summary>
QTEST_CASE ( InsertChild_ReturnedIteratorPointsToAddedNode_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 1);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itParent, 'B');
    const char EXPECTED_NODE_VALUE = 'C';
    const pointer_uint_q POSITION = 0;

    // [Execution]
    QNTree<char>::QNTreeIterator itResult = TREE.InsertChild(itParent, EXPECTED_NODE_VALUE, POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(*itResult, EXPECTED_NODE_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when adding more nodes than the maximum allowed.
/// </summary>
QTEST_CASE ( InsertChild_AssertionFailsWhenExceedingMaximumNodes_Test )
{
    // [Preparation]
    QNTree<char> TREE(2, 1);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itParent, 'B');
    const pointer_uint_q POSITION = 1;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        TREE.InsertChild(itParent, 'C', POSITION);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the input node points to an end position.
/// </summary>
QTEST_CASE ( InsertChild_AssertionFailsWhenInputNodePointsToEndPosition_Test )
{
    // [Preparation]
    QNTree<char> TREE(2, 1);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itParent, 'B');
    ++itParent;
    const pointer_uint_q POSITION = 0;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        TREE.InsertChild(itParent, 'C', POSITION);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the node is not added when the maximum has been reached.
/// </summary>
QTEST_CASE ( InsertChild_NothingHappensWhenExceedingMaximumNodes_Test )
{
    // [Preparation]
    const char EXPECTED_VALUES[] = {'A', 'B', 'C'};
    QNTree<char> TREE(2, 1);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itParent, 'B');
    TREE.AddChild(itParent, 'C');
    const pointer_uint_q POSITION = 0;

    // [Execution]
    TREE.InsertChild(itParent, 'D', POSITION);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QNTree<char>::QNTreeIterator it = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the result iterator points to an end position when the maximum has been reached.
/// </summary>
QTEST_CASE ( InsertChild_ResultIteratorPointsToEndWhenExceedingMaximumNodes_Test )
{
    // [Preparation]
    QNTree<char> TREE(2, 1);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itParent, 'B');
    TREE.AddChild(itParent, 'C');
    const bool RESULT_IS_END = true;
    const pointer_uint_q POSITION = 0;

    // [Execution]
    QNTree<char>::QNTreeIterator itResult = TREE.InsertChild(itParent, 'D', POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(itResult.IsEnd(), RESULT_IS_END);
}

#endif

/// <sumary>
/// Checks that the expected iterator is returned when using a common tree and a common index and using the depth-first pre-order.
/// </sumary>
QTEST_CASE( GetIterator_ReturnsTheExpectedIteratorWhenUsingCommonTreeAndPositionAndDepthFirstPreOrder_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_INDEX = 1;
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = QNTree<char>::QNTreeIterator(&TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itRootNode, 'B');
    TREE.AddChild(itRootNode, 'C');

    QNTree<char>::QNTreeIterator EXPECTED_ITERATOR = QNTree<char>::QNTreeIterator(&TREE, 1, EQTreeTraversalOrder::E_DepthFirstPreOrder);

    // [Execution]
    QNTree<char>::QNTreeIterator it = TREE.GetIterator(INPUT_INDEX, EQTreeTraversalOrder::E_DepthFirstPreOrder);

    // [Verification]
    BOOST_CHECK(it == EXPECTED_ITERATOR);
}

/// <sumary>
/// Checks that the first position is returned when using a common tree and the index equals zero and using the depth-first pre-order.
/// </sumary>
QTEST_CASE( GetIterator_ReturnsTheFirstPositionWhenUsingCommonTreeAndZeroIndexAndDepthFirstPreOrder_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_INDEX = 0;
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = QNTree<char>::QNTreeIterator(&TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itRootNode, 'B');
    TREE.AddChild(itRootNode, 'C');

    QNTree<char>::QNTreeIterator EXPECTED_ITERATOR = QNTree<char>::QNTreeIterator(&TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);

    // [Execution]
    QNTree<char>::QNTreeIterator it = TREE.GetIterator(INPUT_INDEX, EQTreeTraversalOrder::E_DepthFirstPreOrder);

    // [Verification]
    BOOST_CHECK(it == EXPECTED_ITERATOR);
}

/// <sumary>
/// Checks that the last position is returned when using a common tree and the last index and using the depth-first pre-order.
/// </sumary>
QTEST_CASE( GetIterator_ReturnsTheLastPositionWhenUsingCommonTreeAndLastIndexAndDepthFirstPreOrder_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = QNTree<char>::QNTreeIterator(&TREE, 0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itRootNode, 'B');
    TREE.AddChild(itRootNode, 'C');
    const pointer_uint_q INPUT_INDEX = TREE.GetCount() - 1U;

    QNTree<char>::QNTreeIterator EXPECTED_ITERATOR = QNTree<char>::QNTreeIterator(&TREE, 2, EQTreeTraversalOrder::E_DepthFirstPreOrder);

    // [Execution]
    QNTree<char>::QNTreeIterator it = TREE.GetIterator(INPUT_INDEX, EQTreeTraversalOrder::E_DepthFirstPreOrder);

    // [Verification]
    BOOST_CHECK(it == EXPECTED_ITERATOR);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the tree is empty.
/// </sumary>
QTEST_CASE( GetIterator_AssertionFailsWhenTreeIsEmpty_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_INDEX = 0;
    QNTree<char> TREE(3, 3);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        TREE.GetIterator(INPUT_INDEX, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    }
    catch(const QAssertException&)
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
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itRootNode, 'B');
    TREE.AddChild(itRootNode, 'C');
    const pointer_uint_q OUT_OF_BOUNDS_INDEX = TREE.GetCount() + 1U;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        TREE.GetIterator(OUT_OF_BOUNDS_INDEX, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    }
    catch(const QAssertException&)
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
QTEST_CASE( GetIterator_IteratorPointsToEndPositionWhenTreeIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const pointer_uint_q INPUT_INDEX = 0;
    QNTree<char> TREE(3, 3);
    const bool ITERATOR_POINTS_END_POSITION = true;

    // [Execution]
    QNTree<char>::QNTreeIterator it = TREE.GetIterator(INPUT_INDEX, EQTreeTraversalOrder::E_DepthFirstPreOrder);

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
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itRootNode, 'B');
    TREE.AddChild(itRootNode, 'C');
    const pointer_uint_q OUT_OF_BOUNDS_INDEX = TREE.GetCount() + 1U;

    // [Execution]
    QNTree<char>::QNTreeIterator it = TREE.GetIterator(OUT_OF_BOUNDS_INDEX, EQTreeTraversalOrder::E_DepthFirstPreOrder);

    // [Verification]
    bool bIsEnd = it.IsEnd(EQIterationDirection::E_Forward);
    BOOST_CHECK_EQUAL(bIsEnd, ITERATOR_POINTS_END_POSITION);
}

#endif

/// <sumary>
/// Checks that the tree is emptied.
/// </sumary>
QTEST_CASE( Clear_TheTreeIsEmptied_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itRootNode, 'B');
    TREE.AddChild(itRootNode, 'C');

    // [Execution]
    TREE.Clear();

    // [Verification]
    bool bIsEmpty = TREE.IsEmpty();
    BOOST_CHECK(bIsEmpty);
}

/// <sumary>
/// Checks that nothing is done when the tree is already empty.
/// </sumary>
QTEST_CASE( Clear_NothingHappensWhenTreeIsAlreadyEmpty_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 5);

    // [Execution]
    TREE.Clear();

    // [Verification]
    bool bIsEmpty = TREE.IsEmpty();
    BOOST_CHECK(bIsEmpty);
}

/// <sumary>
/// Checks that the node is obtained when the child is the first in the list.
/// </sumary>
QTEST_CASE( GetChild_NodeIsObtainedWhenItIsFirstChild_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const char EXPECTED_ELEMENT = 'B';
    const pointer_uint_q POSITION = 0;
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itRootNode, EXPECTED_ELEMENT);
    TREE.AddChild(itRootNode, 'C');
    TREE.AddChild(itRootNode, 'D');

    // [Execution]
    QNTree<char>::QNTreeIterator itChild = TREE.GetChild(itRootNode, POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(*itChild, EXPECTED_ELEMENT);
}

/// <sumary>
/// Checks that the node is obtained when the child is in the middle of the list.
/// </sumary>
QTEST_CASE( GetChild_NodeIsObtainedWhenItIsInTheMiddleOfChildList_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const char EXPECTED_ELEMENT = 'C';
    const pointer_uint_q POSITION = 1U;
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itRootNode, 'B');
    TREE.AddChild(itRootNode, EXPECTED_ELEMENT);
    TREE.AddChild(itRootNode, 'D');

    // [Execution]
    QNTree<char>::QNTreeIterator itChild = TREE.GetChild(itRootNode, POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(*itChild, EXPECTED_ELEMENT);
}

/// <sumary>
/// Checks that the node is obtained when the child is the last in the list.
/// </sumary>
QTEST_CASE( GetChild_NodeIsObtainedWhenItIsTheLastChild_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const char EXPECTED_ELEMENT = 'D';
    const pointer_uint_q POSITION = 2U;
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itRootNode, 'B');
    TREE.AddChild(itRootNode, 'C');
    TREE.AddChild(itRootNode, EXPECTED_ELEMENT);

    // [Execution]
    QNTree<char>::QNTreeIterator itChild = TREE.GetChild(itRootNode, POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(*itChild, EXPECTED_ELEMENT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the input index is not lower than the number of children.
/// </sumary>
QTEST_CASE( GetChild_AssertionFailsWhenIndexIsNotLowerThanCount_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itRootNode, 'B');
    TREE.AddChild(itRootNode, 'C');
    TREE.AddChild(itRootNode, 'D');

    const pointer_uint_q POSITION = 3U;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        TREE.GetChild(itRootNode, POSITION);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <sumary>
/// Checks that an assertion fails when the input iterator points to the end position.
/// </sumary>
QTEST_CASE( GetChild_AssertionFailsWhenIteratorPointsToEnd_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itRootNode, 'B');
    TREE.AddChild(itRootNode, 'C');
    TREE.AddChild(itRootNode, 'D');
    itRootNode.MoveLast();
    ++itRootNode;

    const pointer_uint_q POSITION = 0;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        TREE.GetChild(itRootNode, POSITION);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <sumary>
/// Checks that the returned iterator points to the end position when the input index is not lower than the number of children.
/// </sumary>
QTEST_CASE( GetChild_ObtainedIteratorPointsToEndPositionWhenIndexIsOutOfBounds_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const pointer_uint_q POSITION = 3U;
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itRootNode, 'B');
    TREE.AddChild(itRootNode, 'C');
    TREE.AddChild(itRootNode, 'D');

    // [Execution]
    QNTree<char>::QNTreeIterator itChild = TREE.GetChild(itRootNode, POSITION);

    // [Verification]
    bool bIteratorPointsToEnd = itChild.IsEnd();
    BOOST_CHECK(bIteratorPointsToEnd);
}

#endif

/// <sumary>
/// Checks that the parent node is correctly obtained.
/// </sumary>
QTEST_CASE( GetParent_ParentNodeIsCorrectlyObtained_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const char EXPECTED_ELEMENT = 'A';
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue(EXPECTED_ELEMENT);
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itRootNode, 'B');
    TREE.AddChild(itRootNode, 'C');
    QNTree<char>::QNTreeIterator itChild = TREE.AddChild(itRootNode, 'D');

    // [Execution]
    QNTree<char>::QNTreeIterator itParent = TREE.GetParent(itChild);

    // [Verification]
    BOOST_CHECK_EQUAL(*itParent, EXPECTED_ELEMENT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the iterator points to the end position.
/// </sumary>
QTEST_CASE( GetParent_AssertionFailsWhenIteratorPointsToEndPosition_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itRootNode, 'B');
    itRootNode.MoveLast();
    ++itRootNode;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        TREE.GetParent(itRootNode);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <sumary>
/// Checks that the obtained iterator points to end position when node has no parent.
/// </sumary>
QTEST_CASE( GetParent_ReturnedIteratorPointsToEndWhenNodeHasNoParent_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itRootNode, 'B');

    // [Execution]
    QNTree<char>::QNTreeIterator itParent = TREE.GetParent(itRootNode);

    // [Verification]
    bool bIteratorPointstoEnd = itParent.IsEnd();
    BOOST_CHECK(bIteratorPointstoEnd);
}

/// <sumary>
/// Checks that the node is obtained when using the depth-first pre-order.
/// </sumary>
QTEST_CASE( GetFirst_NodeIsObtainedWhenUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const char EXPECTED_ELEMENT = 'A';
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue(EXPECTED_ELEMENT);
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itRootNode, 'B');
    TREE.AddChild(itRootNode, 'C');
    TREE.AddChild(itRootNode, 'D');

    // [Execution]
    QNTree<char>::QNTreeIterator itFirst = TREE.GetFirst(EQTreeTraversalOrder::E_DepthFirstPreOrder);

    // [Verification]
    BOOST_CHECK_EQUAL(*itFirst, EXPECTED_ELEMENT);
}

/// <sumary>
/// Checks that the obtained iterator points to end position when the tree is empty.
/// </sumary>
QTEST_CASE( GetFirst_ReturnedIteratorPointsToEndWhenTreeIsEmpty_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 5);

    // [Execution]
    QNTree<char>::QNTreeIterator itFirst = TREE.GetFirst(EQTreeTraversalOrder::E_DepthFirstPreOrder);

    // [Verification]
    bool bIteratorPointstoEnd = itFirst.IsEnd();
    BOOST_CHECK(bIteratorPointstoEnd);
}

/// <sumary>
/// Checks that it returns the correct number of children when the node has several child nodes.
/// </sumary>
QTEST_CASE( GetChildrenCount_TheNumberOfChildreIsCorrectWhenNodeHasSeveralChildNodes_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const pointer_uint_q EXPECTED_VALUE = 3U;
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itRootNode, 'B');
    TREE.AddChild(itRootNode, 'C');
    TREE.AddChild(itRootNode, 'D');

    // [Execution]
    pointer_uint_q uCount = TREE.GetChildrenCount(itRootNode);

    // [Verification]
    BOOST_CHECK_EQUAL(uCount, EXPECTED_VALUE);
}

/// <sumary>
/// Checks that it returns zero when the node does not have children.
/// </sumary>
QTEST_CASE( GetChildrenCount_ReturnsZeroWhenNodeHasNoChildren_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const pointer_uint_q EXPECTED_VALUE = 0;
    QNTree<char> TREE(3, 3);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);

    // [Execution]
    pointer_uint_q uCount = TREE.GetChildrenCount(itRootNode);

    // [Verification]
    BOOST_CHECK_EQUAL(uCount, EXPECTED_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the iterator points to the end position.
/// </sumary>
QTEST_CASE( GetChildrenCount_AssertionFailsWhenIteratorPointsToEndPosition_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 3);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    itRootNode.MoveLast();
    ++itRootNode;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        TREE.GetChildrenCount(itRootNode);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <sumary>
/// Checks that it returns True when the node has several child nodes.
/// </sumary>
QTEST_CASE( HasChildren_ReturnsTrueWhenNodeHasChildren_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const bool EXPECTED_VALUE = true;
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itRootNode, 'B');
    TREE.AddChild(itRootNode, 'C');
    TREE.AddChild(itRootNode, 'D');

    // [Execution]
    bool bResult = TREE.HasChildren(itRootNode);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);
}

/// <sumary>
/// Checks that it returns False when the node does not have children.
/// </sumary>
QTEST_CASE( HasChildren_ReturnsFalseWhenNodeHasNoChildren_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const bool EXPECTED_VALUE = false;
    QNTree<char> TREE(3, 3);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);

    // [Execution]
    bool bResult = TREE.HasChildren(itRootNode);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the iterator points to the end position.
/// </sumary>
QTEST_CASE( HasChildren_AssertionFailsWhenIteratorPointsToEndPosition_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 3);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    itRootNode.MoveLast();
    ++itRootNode;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        TREE.HasChildren(itRootNode);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <sumary>
/// Checks that it returns True when the node has a parent.
/// </sumary>
QTEST_CASE( HasParent_ReturnsTrueWhenNodeHasParent_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const bool EXPECTED_VALUE = true;
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itChild = TREE.AddChild(itRootNode, 'B');
    TREE.AddChild(itRootNode, 'C');
    TREE.AddChild(itRootNode, 'D');

    // [Execution]
    bool bResult = TREE.HasParent(itChild);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);
}

/// <sumary>
/// Checks that it returns False when the node does not have a parent.
/// </sumary>
QTEST_CASE( HasParent_ReturnsFalseWhenNodeHasNoParent_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const bool EXPECTED_VALUE = false;
    QNTree<char> TREE(3, 3);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);

    // [Execution]
    bool bResult = TREE.HasParent(itRootNode);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the iterator points to the end position.
/// </sumary>
QTEST_CASE( HasParent_AssertionFailsWhenIteratorPointsToEndPosition_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 3);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    itRootNode.MoveLast();
    ++itRootNode;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        TREE.HasParent(itRootNode);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <sumary>
/// Checks that the node is obtained when using the depth-first pre-order.
/// </sumary>
QTEST_CASE( GetRoot_NodeIsObtainedWhenUsingDepthFirstPreOrder_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const char EXPECTED_ELEMENT = 'A';
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue(EXPECTED_ELEMENT);
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itRootNode, 'B');
    TREE.AddChild(itRootNode, 'C');
    TREE.AddChild(itRootNode, 'D');

    // [Execution]
    QNTree<char>::QNTreeIterator itFirst = TREE.GetRoot(EQTreeTraversalOrder::E_DepthFirstPreOrder);

    // [Verification]
    BOOST_CHECK_EQUAL(*itFirst, EXPECTED_ELEMENT);
}

/// <sumary>
/// Checks that the obtained iterator points to end position when the tree is empty.
/// </sumary>
QTEST_CASE( GetRoot_ReturnedIteratorPointsToEndWhenTreeIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    QNTree<char> TREE(3, 5);

    // [Execution]
    QNTree<char>::QNTreeIterator itFirst = TREE.GetRoot(EQTreeTraversalOrder::E_DepthFirstPreOrder);

    // [Verification]
    bool bIteratorPointstoEnd = itFirst.IsEnd();
    BOOST_CHECK(bIteratorPointstoEnd);
}


/// <summary>
/// Checks that it returns True when the tree contains the element.
/// </summary>
QTEST_CASE ( Contains_ReturnsTrueWhenTreeContainsTheElement_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 8);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParentNode1 = TREE.AddChild(itRootNode, 'B');
    QNTree<char>::QNTreeIterator itParentNode2 = TREE.AddChild(itRootNode, 'F');
    TREE.AddChild(itParentNode1, 'C');
    TREE.AddChild(itParentNode1, 'D');
    TREE.AddChild(itParentNode1, 'E');
    TREE.AddChild(itParentNode2, 'G');
    const char INPUT_VALUE = 'E';
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = TREE.Contains(INPUT_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the tree does not contain the element.
/// </summary>
QTEST_CASE ( Contains_ReturnsFalseWhenTreeDoesNotContainTheElement_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 8);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParentNode1 = TREE.AddChild(itRootNode, 'B');
    QNTree<char>::QNTreeIterator itParentNode2 = TREE.AddChild(itRootNode, 'F');
    TREE.AddChild(itParentNode1, 'C');
    TREE.AddChild(itParentNode1, 'D');
    TREE.AddChild(itParentNode1, 'E');
    TREE.AddChild(itParentNode2, 'G');
    const char INPUT_VALUE = 'X';
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = TREE.Contains(INPUT_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the tree is empty.
/// </summary>
QTEST_CASE ( Contains_ReturnsFalseWhenTreeIsEmpty_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 8);
    const char INPUT_VALUE = 'X';
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = TREE.Contains(INPUT_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected position when the tree contains the element and using depth-first pre-order.
/// </summary>
QTEST_CASE ( PositionOf1_ReturnsExpectedPositionWhenTreeContainsTheElementAndUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const char INPUT_VALUE = 'E';
    QNTree<char> TREE(3, 8);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParentNode1 = TREE.AddChild(itRootNode, 'B');
    QNTree<char>::QNTreeIterator itParentNode2 = TREE.AddChild(itRootNode, 'F');
    TREE.AddChild(itParentNode1, 'C');
    TREE.AddChild(itParentNode1, 'D');
    TREE.AddChild(itParentNode1, INPUT_VALUE);
    TREE.AddChild(itParentNode2, 'G');

    // [Execution]
    QNTree<char>::QNTreeIterator itPosition = TREE.PositionOf(INPUT_VALUE, EQTreeTraversalOrder::E_DepthFirstPreOrder);

    // [Verification]
    BOOST_CHECK_EQUAL(*itPosition, INPUT_VALUE);
}

/// <summary>
/// Checks that it returns the first occurrence, when there is more than one, using depth-first pre-order.
/// </summary>
QTEST_CASE ( PositionOf1_ReturnsFirstOccurrenceWhenUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const char INPUT_VALUE = 'E';
    QNTree<char> TREE(3, 8);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParentNode1 = TREE.AddChild(itRootNode, 'B');
    QNTree<char>::QNTreeIterator itParentNode2 = TREE.AddChild(itRootNode, 'F');
    QNTree<char>::QNTreeIterator itFirst = TREE.AddChild(itParentNode1, INPUT_VALUE);
    TREE.AddChild(itParentNode1, 'D');
    TREE.AddChild(itParentNode1, INPUT_VALUE);
    TREE.AddChild(itParentNode2, 'G');

    // [Execution]
    QNTree<char>::QNTreeIterator itPosition = TREE.PositionOf(INPUT_VALUE, EQTreeTraversalOrder::E_DepthFirstPreOrder);

    // [Verification]
    BOOST_CHECK(itPosition == itFirst);
}

/// <summary>
/// Checks that it returns an iterator that points to the end position when the tree does not contain the element and using depth-first pre-order.
/// </summary>
QTEST_CASE ( PositionOf1_ReturnsEndPositionWhenTreeDoesNotContainTheElementAndUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 8);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParentNode1 = TREE.AddChild(itRootNode, 'B');
    QNTree<char>::QNTreeIterator itParentNode2 = TREE.AddChild(itRootNode, 'F');
    TREE.AddChild(itParentNode1, 'C');
    TREE.AddChild(itParentNode1, 'D');
    TREE.AddChild(itParentNode1, 'E');
    TREE.AddChild(itParentNode2, 'G');
    const char INPUT_VALUE = 'X';

    // [Execution]
    QNTree<char>::QNTreeIterator itPosition = TREE.PositionOf(INPUT_VALUE, EQTreeTraversalOrder::E_DepthFirstPreOrder);

    // [Verification]
    bool bIteratorIsEnd = itPosition.IsEnd();
    BOOST_CHECK(bIteratorIsEnd);
}

/// <summary>
/// Checks that it returns an iterator that points to the end position when the tree is empty and using depth-first pre-order.
/// </summary>
QTEST_CASE ( PositionOf1_ReturnsEndPositionWhenTreeIsEmptyAndUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 8);
    const char INPUT_VALUE = 'X';

    // [Execution]
    QNTree<char>::QNTreeIterator itPosition = TREE.PositionOf(INPUT_VALUE, EQTreeTraversalOrder::E_DepthFirstPreOrder);

    // [Verification]
    bool bIteratorIsEnd = itPosition.IsEnd();
    BOOST_CHECK(bIteratorIsEnd);
}

/// <summary>
/// Checks that it returns the expected position when the tree contains the element and using depth-first pre-order.
/// </summary>
QTEST_CASE ( PositionOf2_ReturnsExpectedPositionWhenTreeContainsTheElementAndUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const char INPUT_VALUE = 'E';
    QNTree<char> TREE(3, 8);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParentNode1 = TREE.AddChild(itRootNode, 'B');
    QNTree<char>::QNTreeIterator itParentNode2 = TREE.AddChild(itRootNode, 'F');
    TREE.AddChild(itParentNode1, 'C');
    TREE.AddChild(itParentNode1, 'D');
    QNTree<char>::QNTreeIterator startPosition = TREE.AddChild(itParentNode1, INPUT_VALUE);
    TREE.AddChild(itParentNode2, 'G');

    // [Execution]
    QNTree<char>::QNTreeIterator itPosition = TREE.PositionOf(INPUT_VALUE, EQTreeTraversalOrder::E_DepthFirstPreOrder, startPosition);

    // [Verification]
    BOOST_CHECK_EQUAL(*itPosition, INPUT_VALUE);
}

/// <summary>
/// Checks that it returns the first occurrence, when there is more than one, using depth-first pre-order.
/// </summary>
QTEST_CASE ( PositionOf2_ReturnsFirstOccurrenceWhenUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const char INPUT_VALUE = 'E';
    QNTree<char> TREE(3, 8);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParentNode1 = TREE.AddChild(itRootNode, 'B');
    QNTree<char>::QNTreeIterator itParentNode2 = TREE.AddChild(itRootNode, 'F');
    QNTree<char>::QNTreeIterator itFirst = TREE.AddChild(itParentNode1, INPUT_VALUE);
    TREE.AddChild(itParentNode1, 'D');
    TREE.AddChild(itParentNode1, INPUT_VALUE);
    TREE.AddChild(itParentNode2, 'G');
    QNTree<char>::QNTreeIterator startPosition = itFirst;

    // [Execution]
    QNTree<char>::QNTreeIterator itPosition = TREE.PositionOf(INPUT_VALUE, EQTreeTraversalOrder::E_DepthFirstPreOrder, startPosition);

    // [Verification]
    BOOST_CHECK(itPosition == itFirst);
}

/// <summary>
/// Checks that it returns the first occurrence from the start point, when there is more than one, using depth-first pre-order.
/// </summary>
QTEST_CASE ( PositionOf2_ReturnsFirstOccurrenceFromStartPositionWhenUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const char INPUT_VALUE = 'E';
    QNTree<char> TREE(3, 8);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParentNode1 = TREE.AddChild(itRootNode, 'B');
    QNTree<char>::QNTreeIterator itParentNode2 = TREE.AddChild(itRootNode, 'F');
    TREE.AddChild(itParentNode1, 'D');
    QNTree<char>::QNTreeIterator startPosition = TREE.AddChild(itParentNode1, INPUT_VALUE);
    TREE.AddChild(itParentNode2, 'G');
    QNTree<char>::QNTreeIterator EXPECTED_POSITION = startPosition;

    // [Execution]
    QNTree<char>::QNTreeIterator itPosition = TREE.PositionOf(INPUT_VALUE, EQTreeTraversalOrder::E_DepthFirstPreOrder, startPosition);

    // [Verification]
    BOOST_CHECK(itPosition == EXPECTED_POSITION);
}

/// <summary>
/// Checks that it returns an iterator that points to the end position when the tree does not contain the element and using depth-first pre-order.
/// </summary>
QTEST_CASE ( PositionOf2_ReturnsEndPositionWhenTreeDoesNotContainTheElementAndUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 8);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParentNode1 = TREE.AddChild(itRootNode, 'B');
    QNTree<char>::QNTreeIterator itParentNode2 = TREE.AddChild(itRootNode, 'F');
    TREE.AddChild(itParentNode1, 'C');
    TREE.AddChild(itParentNode1, 'D');
    TREE.AddChild(itParentNode1, 'E');
    TREE.AddChild(itParentNode2, 'G');
    const char INPUT_VALUE = 'X';
    QNTree<char>::QNTreeIterator startPosition = itRootNode;

    // [Execution]
    QNTree<char>::QNTreeIterator itPosition = TREE.PositionOf(INPUT_VALUE, EQTreeTraversalOrder::E_DepthFirstPreOrder, startPosition);

    // [Verification]
    bool bIteratorIsEnd = itPosition.IsEnd();
    BOOST_CHECK(bIteratorIsEnd);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the start position points to the end position.
/// </summary>
QTEST_CASE ( PositionOf2_AssertionFailsWhenStartPositionPointsToEnd_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 8);
    QNTree<char>::QNTreeIterator startPosition = TREE.GetFirst(EQTreeTraversalOrder::E_DepthFirstPreOrder);
    const char INPUT_VALUE = 'X';

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        TREE.PositionOf(INPUT_VALUE, EQTreeTraversalOrder::E_DepthFirstPreOrder, startPosition);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <sumary>
/// Checks that the first child node is correctly obtained.
/// </sumary>
QTEST_CASE( GetFirstChild_ChildNodeIsCorrectlyObtained_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 5);
    const char EXPECTED_ELEMENT = 'B';
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetRoot(EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itRootNode, EXPECTED_ELEMENT);
    TREE.AddChild(itRootNode, 'C');
    TREE.AddChild(itRootNode, 'D');

    // [Execution]
    QNTree<char>::QNTreeIterator itChild = TREE.GetFirstChild(itRootNode);

    // [Verification]
    BOOST_CHECK_EQUAL(*itChild, EXPECTED_ELEMENT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the iterator points to the end position.
/// </sumary>
QTEST_CASE( GetFirstChild_AssertionFailsWhenIteratorPointsToEndPosition_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetRoot(EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itRootNode, 'B');
    itRootNode.MoveLast();
    ++itRootNode;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        TREE.GetFirstChild(itRootNode);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <sumary>
/// Checks that the obtained iterator points to end position when node has no children.
/// </sumary>
QTEST_CASE( GetFirstChild_ReturnedIteratorPointsToEndWhenNodeHasNoChildren_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetRoot(EQTreeTraversalOrder::E_DepthFirstPreOrder);

    // [Execution]
    QNTree<char>::QNTreeIterator itChild = TREE.GetFirstChild(itRootNode);

    // [Verification]
    bool bIteratorPointstoEnd = itChild.IsEnd();
    BOOST_CHECK(bIteratorPointstoEnd);
}

/// <sumary>
/// Checks that the last child node is correctly obtained.
/// </sumary>
QTEST_CASE( GetLastChild_ChildNodeIsCorrectlyObtained_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const char EXPECTED_ELEMENT = 'D';
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetRoot(EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itRootNode, 'B');
    TREE.AddChild(itRootNode, 'C');
    TREE.AddChild(itRootNode, EXPECTED_ELEMENT);

    // [Execution]
    QNTree<char>::QNTreeIterator itChild = TREE.GetLastChild(itRootNode);

    // [Verification]
    BOOST_CHECK_EQUAL(*itChild, EXPECTED_ELEMENT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the iterator points to the end position.
/// </sumary>
QTEST_CASE( GetLastChild_AssertionFailsWhenIteratorPointsToEndPosition_Test )
{
    // [Preparation]
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetRoot(EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itRootNode, 'B');
    itRootNode.MoveLast();
    ++itRootNode;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        TREE.GetLastChild(itRootNode);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <sumary>
/// Checks that the obtained iterator points to end position when node has no children.
/// </sumary>
QTEST_CASE( GetLastChild_ReturnedIteratorPointsToEndWhenNodeHasNoChildren_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetRoot(EQTreeTraversalOrder::E_DepthFirstPreOrder);

    // [Execution]
    QNTree<char>::QNTreeIterator itChild = TREE.GetLastChild(itRootNode);

    // [Verification]
    bool bIteratorPointstoEnd = itChild.IsEnd();
    BOOST_CHECK(bIteratorPointstoEnd);
}

/// <sumary>
/// Checks that the node is obtained when using the depth-first pre-order.
/// </sumary>
QTEST_CASE( GetLast_NodeIsObtainedWhenUsingDepthFirstPreOrder_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    const char EXPECTED_ELEMENT = 'E';
    QNTree<char> TREE(3, 5);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = TREE.GetRoot(EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itRootNode, 'B');
    TREE.AddChild(itRootNode, 'C');
    QNTree<char>::QNTreeIterator itChild = TREE.AddChild(itRootNode, 'D');
    TREE.AddChild(itChild, EXPECTED_ELEMENT);

    // [Execution]
    QNTree<char>::QNTreeIterator itLast = TREE.GetLast(EQTreeTraversalOrder::E_DepthFirstPreOrder);

    // [Verification]
    BOOST_CHECK_EQUAL(*itLast, EXPECTED_ELEMENT);
}

/// <sumary>
/// Checks that the obtained iterator points to end position when the tree is empty.
/// </sumary>
QTEST_CASE( GetLast_ReturnedIteratorPointsToEndWhenTreeIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

    // [Preparation]
    QNTree<char> TREE(3, 5);

    // [Execution]
    QNTree<char>::QNTreeIterator itLast = TREE.GetLast(EQTreeTraversalOrder::E_DepthFirstPreOrder);

    // [Verification]
    bool bIteratorPointstoEnd = itLast.IsEnd();
    BOOST_CHECK(bIteratorPointstoEnd);
}

/// <summary>
/// Checks if it the clone method works properly.
/// </summary>
QTEST_CASE ( Clone_ClonedTreeHasSameValuesThanTheOriginalTree_Test )
{
    // [Preparation]
    QNTree<char> sourceTree(3, 8);
    sourceTree.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = sourceTree.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParentNode1 = sourceTree.AddChild(itRootNode, 'B');
    QNTree<char>::QNTreeIterator itParentNode2 = sourceTree.AddChild(itRootNode, 'F');
    sourceTree.AddChild(itParentNode1, 'C');
    sourceTree.AddChild(itParentNode1, 'D');
    sourceTree.AddChild(itParentNode1, 'E');
    sourceTree.AddChild(itParentNode2, 'G');
    QNTree<char> destinationTree(3, 8);

    // [Execution]
    sourceTree.Clone(destinationTree);

    // [Verification]
    BOOST_CHECK(sourceTree == destinationTree);
}

/// <summary>
/// Checks if it the clone method works properly when the destination tree has more capacity and elements.
/// </summary>
QTEST_CASE ( Clone_ClonedTreeHasSameValuesThanTheOriginalTreeWhenInputTreeHasMoreCapacityAndElements_Test )
{
    // [Preparation]
    QNTree<char> sourceTree(3, 4);
    sourceTree.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = sourceTree.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParentNode1 = sourceTree.AddChild(itRootNode, 'B');
    sourceTree.AddChild(itParentNode1, 'C');

    QNTree<char> destinationTree(3, 8);
    destinationTree.SetRootValue('X');
    QNTree<char>::QNTreeIterator itRootNode2 = destinationTree.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParentNode3 = destinationTree.AddChild(itRootNode2, 'Z');
    QNTree<char>::QNTreeIterator itParentNode4 = destinationTree.AddChild(itRootNode2, 'U');
    destinationTree.AddChild(itParentNode3, 'T');
    destinationTree.AddChild(itParentNode3, 'R');
    destinationTree.AddChild(itParentNode4, 'S');
    destinationTree.AddChild(itParentNode4, 'M');

    // [Execution]
    sourceTree.Clone(destinationTree);

    // [Verification]
    BOOST_CHECK(sourceTree == destinationTree);
}

/// <summary>
/// Checks if it the clone method works properly when the destination tree has less capacity and elements.
/// </summary>
QTEST_CASE ( Clone_ClonedTreeHasSameValuesThanTheOriginalTreeWhenInputTreeHasLessCapacityAndElements_Test )
{
    // [Preparation]
    QNTree<char> sourceTree(3, 8);
    sourceTree.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = sourceTree.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator itParentNode1 = sourceTree.AddChild(itRootNode, 'B');
    QNTree<char>::QNTreeIterator itParentNode2 = sourceTree.AddChild(itRootNode, 'F');
    sourceTree.AddChild(itParentNode1, 'C');
    sourceTree.AddChild(itParentNode1, 'D');
    sourceTree.AddChild(itParentNode1, 'E');
    sourceTree.AddChild(itParentNode2, 'G');

    QNTree<char> destinationTree(3, 3);
    destinationTree.SetRootValue('X');
    QNTree<char>::QNTreeIterator itRootNode2 = destinationTree.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    destinationTree.AddChild(itRootNode2, 'Z');
    destinationTree.AddChild(itRootNode2, 'U');

    // [Execution]
    sourceTree.Clone(destinationTree);

    // [Verification]
    BOOST_CHECK(sourceTree == destinationTree);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the maximum number of elements in the destination tree is lower than in the source tree.
/// </summary>
QTEST_CASE ( Clone_AssertionFailsWhenTheMaximumNumberOfElementsInDestinationIsLowerThanInSource_Test )
{
    // [Preparation]
    QNTree<char> sourceTree(5, 3);
    sourceTree.SetRootValue('A');
    QNTree<char>::QNTreeIterator itRootNode = sourceTree.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    sourceTree.AddChild(itRootNode, 'B');
    sourceTree.AddChild(itRootNode, 'F');

    QNTree<char> destinationTree(3, 3);
    destinationTree.SetRootValue('X');
    QNTree<char>::QNTreeIterator itRootNode2 = destinationTree.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    destinationTree.AddChild(itRootNode2, 'Z');
    destinationTree.AddChild(itRootNode2, 'U');

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        sourceTree.Clone(destinationTree);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <sumary>
/// Checks that elements are correctly swapped when selecting any position.
/// </sumary>
QTEST_CASE( Swap_ElementsAreCorrectlySwappedWhenSelectingAnyPosition_Test )
{
    // [Preparation]
    const char EXPECTED_VALUE_A = 'B';
    const char EXPECTED_VALUE_B = 'C';
    QNTree<char> tree(3, 4);
    tree.SetRootValue('A');
    const QNTree<char>::QNTreeIterator ROOT = tree.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    const QNTree<char>::QNTreeIterator POSITION_A = tree.AddChild(ROOT, EXPECTED_VALUE_B);
    const QNTree<char>::QNTreeIterator POSITION_B = tree.AddChild(ROOT, EXPECTED_VALUE_A);
    tree.AddChild(ROOT, 'D');

    // [Execution]
    tree.Swap(POSITION_A, POSITION_B);

    // [Verification]
    BOOST_CHECK_EQUAL(*POSITION_A, EXPECTED_VALUE_A);
    BOOST_CHECK_EQUAL(*POSITION_B, EXPECTED_VALUE_B);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the first position provided is an end position.
/// </sumary>
QTEST_CASE( Swap_AssertionFailsWhenFirstPositionIsEndPosition_Test )
{
    // [Preparation]
    QNTree<char> tree(3, 4);
    tree.SetRootValue('A');
    QNTree<char>::QNTreeIterator POSITION_A = tree.GetLast(EQTreeTraversalOrder::E_DepthFirstPreOrder);
    ++POSITION_A;
    const QNTree<char>::QNTreeIterator POSITION_B = tree.GetFirst(EQTreeTraversalOrder::E_DepthFirstPreOrder);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        tree.Swap(POSITION_A, POSITION_B);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

/// <sumary>
/// Checks that an assertion fails when the second position provided is an end position.
/// </sumary>
QTEST_CASE( Swap_AssertionFailsWhenSecondPositionIsEndPosition_Test )
{
    // [Preparation]
    QNTree<char> tree(3, 4);
    tree.SetRootValue('A');
    QNTree<char>::QNTreeIterator POSITION_A = tree.GetFirst(EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator POSITION_B = tree.GetLast(EQTreeTraversalOrder::E_DepthFirstPreOrder);
    ++POSITION_B;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        tree.Swap(POSITION_A, POSITION_B);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

/// <sumary>
/// Checks that an assertion fails when swapping the same element.
/// </sumary>
QTEST_CASE( Swap_AssertionFailsWhenSwappingTheSameElement_Test )
{
    // [Preparation]
    QNTree<char> tree(3, 4);
    tree.SetRootValue('A');
    QNTree<char>::QNTreeIterator POSITION_A = tree.GetFirst(EQTreeTraversalOrder::E_DepthFirstPreOrder);
    QNTree<char>::QNTreeIterator POSITION_B = POSITION_A;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        tree.Swap(POSITION_A, POSITION_B);
    }
    catch(const QAssertException&)
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
QTEST_CASE( Swap_NothingHappensWhenSwappingTheSameElement_Test )
{
    // [Preparation]
    const char EXPECTED_VALUE_A = 'B';
    QNTree<char> tree(3, 4);
    tree.SetRootValue('A');
    const QNTree<char>::QNTreeIterator ROOT = tree.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    const QNTree<char>::QNTreeIterator POSITION_A = tree.AddChild(ROOT, EXPECTED_VALUE_A);
    const QNTree<char>::QNTreeIterator POSITION_B = POSITION_A;
    tree.AddChild(ROOT, 'D');

    // [Execution]
    tree.Swap(POSITION_A, POSITION_B);

    // [Verification]
    BOOST_CHECK_EQUAL(*POSITION_A, EXPECTED_VALUE_A);
    BOOST_CHECK_EQUAL(*POSITION_B, EXPECTED_VALUE_A);
}

#endif

/// <summary>
/// Checks that the capacity is correctly calculated.
/// </summary>
QTEST_CASE ( GetCapacity_IsCorrectlyCalculated_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    const unsigned int EXPECTED_CAPACITY = 3;
    QNTree<CallCounter> TREE(3, 3);

    // [Execution]
    pointer_uint_q uCapacity = TREE.GetCapacity();

    // [Verification]
    BOOST_CHECK_EQUAL(uCapacity, EXPECTED_CAPACITY);
}

/// <summary>
/// Checks that the capacity is correctly calculated when it equals zero.
/// </summary>
QTEST_CASE ( GetCapacity_IsCorrectlyCalculatedWhenItEqualsZero_Test )
{
//    [TODO] Thund: Uncomment when Shrink is implemented
//    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;
//
//    // [Preparation]
//    const unsigned int EXPECTED_CAPACITY = 0;
//    QNTree<CallCounter> TREE(3, 3);
//    TREE.Shrink();
//
//    // [Execution]
//    pointer_uint_q uCapacity = TREE.GetCapacity();
//
//    // [Verification]
//    BOOST_CHECK_EQUAL(uCapacity, EXPECTED_CAPACITY);
}

/// <summary>
/// Checks that the number of elements is correctly counted.
/// </summary>
QTEST_CASE ( GetCount_IsCorrectlyCalculated_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_COUNT = 3;
    QNTree<int> TREE(3, 3);
    TREE.SetRootValue(1);                                                       // [ 1 |   |   ]
    TREE.AddChild(TREE.GetRoot(EQTreeTraversalOrder::E_DepthFirstPreOrder), 2); // [ 1 | 2 |   ]
    TREE.AddChild(TREE.GetRoot(EQTreeTraversalOrder::E_DepthFirstPreOrder), 3); // [ 1 | 2 | 3 ]

    // [Execution]
    pointer_uint_q uCount = TREE.GetCount();

    // [Verification]
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that it returns zero when the tree is empty.
/// </summary>
QTEST_CASE ( GetCount_ReturnsZeroWhenTreeIsEmpty_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_COUNT = 0;
    QNTree<int> TREE(3, 3);

    // [Execution]
    pointer_uint_q uCount = TREE.GetCount();

    // [Verification]
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that it returns True when the tree is empty.
/// </summary>
QTEST_CASE ( IsEmpty_ReturnsTrueWhenTreeIsEmpty_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    QNTree<int> TREE(3, 3);

    // [Execution]
    bool bResult = TREE.IsEmpty();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the tree is not empty.
/// </summary>
QTEST_CASE ( IsEmpty_ReturnsFalseWhenTreeIsNotEmpty_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    QNTree<int> TREE(3, 3);
    TREE.SetRootValue(1);

    // [Execution]
    bool bResult = TREE.IsEmpty();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

// End - Test Suite: QNTree

QTEST_SUITE_END()
