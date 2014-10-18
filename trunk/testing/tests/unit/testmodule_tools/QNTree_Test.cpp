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
    catch(...) // [TODO] Thund: Replace with the appropiate exception type when exists
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
    catch(...) // [TODO] Thund: Replace with the appropiate exception type when exists
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
    catch(...) // [TODO] Thund: Replace with the appropiate exception type when exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // #if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that all the default values have not changed since the last time this test was executed.
/// </summary>
QTEST_CASE ( Destructor_TheDestructorOfEveryElementIsCalled_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;
    /* [TODO] Thund: Uncomment when the destructor is fully implemented
    // [Preparation]
    CallCounter::ResetCounters();
    const unsigned int EXPECTED_CALLS = 3;

    {
        QNTree<CallCounter> TREE(3, 5);
        TREE.SetRootValue(CallCounter());
        TREE.AddChild(TREE.GetRoot(), CallCounter());
        TREE.AddChild(TREE.GetRoot(), CallCounter());


    // [Execution]
    // Destructor is called when the execution flow leaves this block
    }

    // [Verification]
    unsigned int uDestructorCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorCalls, EXPECTED_CALLS);*/
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
{/* [TODO] Thund: Uncomment when AddChild, GetRoot and QNTreeIterator are implemented
    // [Preparation]
    const pointer_uint_q INPUT_CAPACITY = 4;
    const int EXPECTED_FIRST_ELEMENT = 1;
    const int EXPECTED_SECOND_ELEMENT = 2;
    QNTree<int> TREE(2, 2);
    TREE.SetRootValue(EXPECTED_FIRST_ELEMENT);
    TREE.AddChild(TREE.GetRoot(), EXPECTED_SECOND_ELEMENT);

    // [Execution]
    TREE.Reserve(INPUT_CAPACITY); // A reallocation occurs

    // [Verification]
    QNTree<int>::QNTreeIterator it = TREE.GetRoot();
    BOOST_CHECK_EQUAL(*it, EXPECTED_FIRST_ELEMENT);
    ++it;
    BOOST_CHECK_EQUAL(*it, EXPECTED_SECOND_ELEMENT);*/
}

/// <summary>
/// Checks that elements are not reallocated and capacity does not change when attempting to reserve less memory than current reserved.
/// </summary>
QTEST_CASE ( Reserve_NothingHappensWhenTheAmountToReserveIsNoGreaterThanCurrentCapacity_Test )
{/* [TODO] Thund: Uncomment when Reserve, GetRoot and QNTree::QNTreeIterator is implemented
    // [Preparation]
    const pointer_uint_q INPUT_CAPACITY = 1;
    const pointer_uint_q EXPECTED_CAPACITY = 4;
    QNTree<int> TREE(4, 4);
    TREE.SetRootValue(1);
    int* EXPECTED_LOCATION_OF_ELEMENT = &(*TREE.GetRoot());

    // [Execution]
    TREE.Reserve(INPUT_CAPACITY); // A reallocation occurs

    // [Verification]
    pointer_uint_q uCapacity = TREE.GetCapacity();
    TREE.SetRootValue(1);
    int* pLocationOfElement = &(*TREE.GetRoot());

    BOOST_CHECK_EQUAL(uCapacity, EXPECTED_CAPACITY);
    BOOST_CHECK_EQUAL(pLocationOfElement, EXPECTED_LOCATION_OF_ELEMENT);*/
}

/// <summary>
/// Checks that the element is correctly copied when the tree is empty.
/// </summary>
QTEST_CASE ( SetRootValue_RootNodeIsCorrectlyCopiedWhenTreeIsEmpty_Test )
{/* [TODO] Thund: Uncomment when GetRoot is implemented
    // [Preparation]
    const int EXPECTED_ELEMENT = 1;
    QNTree<int> TREE(2, 2);

    // [Execution]
    TREE.SetRootValue(EXPECTED_ELEMENT);

    // [Verification]
    int nElementValue = *TREE.GetRoot();

    BOOST_CHECK_EQUAL(nElementValue, EXPECTED_ELEMENT);*/
}

/// <summary>
/// Checks that the element is correctly copied when the tree is not empty.
/// </summary>
QTEST_CASE ( SetRootValue_RootNodeIsCorrectlyCopiedWhenTreeIsNotEmpty_Test )
{/* [TODO] Thund: Uncomment when GetRoot is implemented
    // [Preparation]
    const int EXPECTED_ELEMENT = 1;
    const int ORIGINAL_ELEMENT = 2;
    QNTree<int> TREE(2, 2);
    TREE.SetRootValue(ORIGINAL_ELEMENT);

    // [Execution]
    TREE.SetRootValue(EXPECTED_ELEMENT);

    // [Verification]
    int nElementValue = *TREE.GetRoot();

    BOOST_CHECK_EQUAL(nElementValue, EXPECTED_ELEMENT);
    */
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
    catch(...)
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
    catch(...)
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
    const char EXPECTED_VALUES[] = {'A', 'B'};
    QNTree<char> TREE(2, 1);
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
/// Checks that the result iterator points to an end position when the maximum has been reached.
/// </summary>
QTEST_CASE ( AddChild_ResultIteratorPointsToEndWhenExceedingMaximumNodes_Test )
{
    // [Preparation]
    QNTree<char> TREE(2, 1);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itParent, 'B');
    const bool RESULT_IS_END = true;

    // [Execution]
    QNTree<char>::QNTreeIterator itResult = TREE.AddChild(itParent, 'C');

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
    catch(...)
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
    catch(...)
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
    catch(...)
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
    catch(...)
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
    catch(...)
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
    catch(...)
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
    catch(...)
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
    catch(...)
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
    const char EXPECTED_VALUES[] = {'A', 'B'};
    QNTree<char> TREE(2, 1);
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
/// Checks that the result iterator points to an end position when the maximum has been reached.
/// </summary>
QTEST_CASE ( InsertChild_ResultIteratorPointsToEndWhenExceedingMaximumNodes_Test )
{
    // [Preparation]
    QNTree<char> TREE(2, 1);
    TREE.SetRootValue('A');
    QNTree<char>::QNTreeIterator itParent = TREE.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstPreOrder);
    TREE.AddChild(itParent, 'B');
    const bool RESULT_IS_END = true;
    const pointer_uint_q POSITION = 0;

    // [Execution]
    QNTree<char>::QNTreeIterator itResult = TREE.InsertChild(itParent, 'C', POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(itResult.IsEnd(), RESULT_IS_END);
}

#endif

/// <sumary>
/// Checks that the expected iterator is returned when using a common tree and a common index.
/// </sumary>
QTEST_CASE( GetIterator_ReturnsTheExpectedIteratorWhenUsingCommonTreeAndPosition_Test )
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
/// Checks that the first position is returned when using a common tree and the index equals zero.
/// </sumary>
QTEST_CASE( GetIterator_ReturnsTheFirstPositionWhenUsingCommonTreeAndZeroIndex_Test )
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
/// Checks that the last position is returned when using a common tree and the last index.
/// </sumary>
QTEST_CASE( GetIterator_ReturnsTheLastPositionWhenUsingCommonTreeAndLastIndex_Test )
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
{/* [TODO] Thund: Uncomment when Shrink is implemented
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    const unsigned int EXPECTED_CAPACITY = 0;
    QNTree<CallCounter> TREE(3, 3);
    TREE.Shrink();

    // [Execution]
    pointer_uint_q uCapacity = TREE.GetCapacity();

    // [Verification]
    BOOST_CHECK_EQUAL(uCapacity, EXPECTED_CAPACITY);*/
}

/// <summary>
/// Checks that the number of elements is correctly counted.
/// </summary>
QTEST_CASE ( GetCount_IsCorrectlyCalculated_Test )
{/* [TODO] Thund: Uncomment when AddChild is implemented
    // [Preparation]
    const pointer_uint_q EXPECTED_COUNT = 3;
    QNTree<int> TREE(3, 3);
    TREE.SetRootValue(1);             // [ 1 |   |   ]
    TREE.AddChild(TREE.GetRoot(), 2); // [ 1 | 2 |   ]
    TREE.AddChild(TREE.GetRoot(), 3); // [ 1 | 2 | 3 ]

    // [Execution]
    pointer_uint_q uCount = TREE.GetCount();

    // [Verification]
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);*/
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
