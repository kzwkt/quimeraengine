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
#include "QBinarySearchTreeWhiteBox.h"
#include "CallCounter.h"

using Kinesis::QuimeraEngine::Tools::Containers::QBinarySearchTree;
using Kinesis::QuimeraEngine::Tools::Containers::Test::QBinarySearchTreeWhiteBox;


QTEST_SUITE_BEGIN( QBinarySearchTree_TestSuite )

/// <summary>
/// Checks that all the default values have not changed since the last time this test was executed.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_ROOT = QBinarySearchTreeWhiteBox<int>::GetEndPositionForward();
    const pointer_uint_q EXPECTED_CAPACITY = 1;
    const pointer_uint_q EXPECTED_NODE_CAPACITY = EXPECTED_CAPACITY;

    // [Execution]
    QBinarySearchTreeWhiteBox<int> tree;

    // [Verification]
    pointer_uint_q uStoredRoot = tree.GetRootPosition();
    pointer_uint_q uStoredCapacity = tree.GetCapacity();
    pointer_uint_q uStoredNodeCapacity = tree.GetNodeAllocator().GetPoolSize() / sizeof(QBinarySearchTreeWhiteBox<int>::QBinaryNode);

    BOOST_CHECK_EQUAL(uStoredRoot, EXPECTED_ROOT);
    BOOST_CHECK_EQUAL(uStoredCapacity, EXPECTED_CAPACITY);
    BOOST_CHECK_EQUAL(uStoredNodeCapacity, EXPECTED_NODE_CAPACITY);
}

/// <summary>
/// Checks that the value of input parameters are correctly stored.
/// </summary>
QTEST_CASE ( Constructor2_InputParametersAreCorrectlySet_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_CAPACITY = 5;

    // [Execution]
    QBinarySearchTreeWhiteBox<int> tree(EXPECTED_CAPACITY);

    // [Verification]
    pointer_uint_q uStoredCapacity = tree.GetCapacity();

    BOOST_CHECK_EQUAL(uStoredCapacity, EXPECTED_CAPACITY);
}

/// <summary>
/// Checks that all the default values have not changed since the last time this test was executed.
/// </summary>
QTEST_CASE ( Constructor2_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_CAPACITY = 5;
    const pointer_uint_q EXPECTED_ROOT = QBinarySearchTreeWhiteBox<int>::GetEndPositionForward();
    const pointer_uint_q EXPECTED_NODE_CAPACITY = INPUT_CAPACITY;

    // [Execution]
    QBinarySearchTreeWhiteBox<int> tree(INPUT_CAPACITY);

    // [Verification]
    const pointer_uint_q uStoredRoot = tree.GetRootPosition();
    const pointer_uint_q uStoredNodeCapacity = tree.GetNodeAllocator().GetPoolSize() / sizeof(QBinarySearchTreeWhiteBox<int>::QBinaryNode);

    BOOST_CHECK_EQUAL(uStoredRoot, EXPECTED_ROOT);
    BOOST_CHECK_EQUAL(uStoredNodeCapacity, EXPECTED_NODE_CAPACITY);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input capacity equals zero.
/// </summary>
QTEST_CASE ( Constructor2_AssertionFailsWhenCapacityEqualsZero_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_ZERO = 0;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        QBinarySearchTree<int> tree(INPUT_ZERO);
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
    
    // [Preparation]
    const unsigned int EXPECTED_CALLS = 3;

    {
        QBinarySearchTree<CallCounter> TREE(3);
        TREE.Add(CallCounter(), EQTreeTraversalOrder::E_DepthFirstInOrder);
        TREE.Add(CallCounter(), EQTreeTraversalOrder::E_DepthFirstInOrder);
        TREE.Add(CallCounter(), EQTreeTraversalOrder::E_DepthFirstInOrder);
        CallCounter::ResetCounters();

    // [Execution]
    // Destructor is called when the execution flow leaves this block
    }

    // [Verification]
    unsigned int uDestructorCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorCalls, EXPECTED_CALLS);
}

/// <summary>
/// Checks that the capacity is correctly increased.
/// </summary>
QTEST_CASE ( Reserve_CapacityIsCorrectlyIncreased_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_CAPACITY = 4;
    QBinarySearchTree<int> TREE(2);

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
{/* [TODO] Thund: Uncomment when Add, GetRoot and QBinarySearchTreeIterator are implemented
    // [Preparation]
    const pointer_uint_q INPUT_CAPACITY = 4;
    const int EXPECTED_FIRST_ELEMENT = 1;
    const int EXPECTED_SECOND_ELEMENT = 2;
    QBinarySearchTree<int> TREE(2);
    TREE.Add(EXPECTED_FIRST_ELEMENT);
    TREE.Add(EXPECTED_SECOND_ELEMENT);

    // [Execution]
    TREE.Reserve(INPUT_CAPACITY); // A reallocation occurs

    // [Verification]
    QBinarySearchTree<int>::QBinarySearchTreeIterator it = TREE.GetRoot();
    BOOST_CHECK_EQUAL(*it, EXPECTED_FIRST_ELEMENT);
    ++it;
    BOOST_CHECK_EQUAL(*it, EXPECTED_SECOND_ELEMENT);*/
}

/// <summary>
/// Checks that elements are not reallocated and capacity does not change when attempting to reserve less memory than current reserved.
/// </summary>
QTEST_CASE ( Reserve_NothingHappensWhenTheAmountToReserveIsNoGreaterThanCurrentCapacity_Test )
{/* [TODO] Thund: Uncomment when Reserve, GetRoot and QBinarySearchTree::QBinarySearchTreeIterator is implemented
    // [Preparation]
    const pointer_uint_q INPUT_CAPACITY = 1;
    const pointer_uint_q EXPECTED_CAPACITY = 4;
    QBinarySearchTree<int> TREE(4);
    TREE.Add(1);
    int* EXPECTED_LOCATION_OF_ELEMENT = &(*TREE.GetRoot());

    // [Execution]
    TREE.Reserve(INPUT_CAPACITY); // A reallocation occurs

    // [Verification]
    pointer_uint_q uCapacity = TREE.GetCapacity();
    *TREE.GetFirst() = 1;
    int* pLocationOfElement = &(*TREE.GetRoot());

    BOOST_CHECK_EQUAL(uCapacity, EXPECTED_CAPACITY);
    BOOST_CHECK_EQUAL(pLocationOfElement, EXPECTED_LOCATION_OF_ELEMENT);*/
}

/// <summary>
/// Checks that the element is correctly added when the tree is empty.
/// </summary>
QTEST_CASE ( Add_ElementIsCorrectlyAddedWhenTreeIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    const int INPUT_ELEMENT = 0;
    const int EXPECTED_VALUES[] = {INPUT_ELEMENT};
    
    QBinarySearchTree<int> TREE(3);

    // [Execution]
    TREE.Add(INPUT_ELEMENT, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QBinarySearchTree<int>::QBinarySearchTreeIterator it = QBinarySearchTree<int>::QBinarySearchTreeIterator(&TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly added when it is lower than the root and the tree only contains one element.
/// </summary>
QTEST_CASE ( Add_ElementIsCorrectlyAddedWhenItIsLowerThanRootAndTreeOnlyContainsOneElement_Test )
{
    // [Preparation]
    const int INPUT_ELEMENT = 3;
    const int EXPECTED_VALUES[] = {INPUT_ELEMENT, 5};
    
    QBinarySearchTree<int> TREE(3);
    TREE.Add(5, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Add(INPUT_ELEMENT, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QBinarySearchTree<int>::QBinarySearchTreeIterator it = QBinarySearchTree<int>::QBinarySearchTreeIterator(&TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly added when it is greater than the root and the tree only contains one element.
/// </summary>
QTEST_CASE ( Add_ElementIsCorrectlyAddedWhenItIsGreaterThanRootAndTreeOnlyContainsOneElement_Test )
{
    // [Preparation]
    const int INPUT_ELEMENT = 7;
    const int EXPECTED_VALUES[] = {5, INPUT_ELEMENT};
    
    QBinarySearchTree<int> TREE(3);
    TREE.Add(5, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Add(INPUT_ELEMENT, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QBinarySearchTree<int>::QBinarySearchTreeIterator it = QBinarySearchTree<int>::QBinarySearchTreeIterator(&TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly added when it is lower than the root and greater than its left child.
/// </summary>
QTEST_CASE ( Add_ElementIsCorrectlyAddedWhenItIsLowerThanRootAndGreaterThanItsLeftChild_Test )
{
    // [Preparation]
    const int INPUT_ELEMENT = 4;
    const int EXPECTED_VALUES[] = {3, INPUT_ELEMENT, 5};
    
    QBinarySearchTree<int> TREE(3);
    TREE.Add(5, EQTreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(3, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Add(INPUT_ELEMENT, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QBinarySearchTree<int>::QBinarySearchTreeIterator it = QBinarySearchTree<int>::QBinarySearchTreeIterator(&TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly added when it is lower than the root and lower than its left child.
/// </summary>
QTEST_CASE ( Add_ElementIsCorrectlyAddedWhenItIsLowerThanRootAndLowerThanItsLeftChild_Test )
{
    // [Preparation]
    const int INPUT_ELEMENT = 2;
    const int EXPECTED_VALUES[] = {INPUT_ELEMENT, 3, 5};
    
    QBinarySearchTree<int> TREE(3);
    TREE.Add(5, EQTreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(3, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Add(INPUT_ELEMENT, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QBinarySearchTree<int>::QBinarySearchTreeIterator it = QBinarySearchTree<int>::QBinarySearchTreeIterator(&TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly added when it is greater than the root and lower than its right child.
/// </summary>
QTEST_CASE ( Add_ElementIsCorrectlyAddedWhenItIsGreaterThanRootAndLowerThanItsRightChild_Test )
{
    // [Preparation]
    const int INPUT_ELEMENT = 6;
    const int EXPECTED_VALUES[] = {5, INPUT_ELEMENT, 7};
    
    QBinarySearchTree<int> TREE(3);
    TREE.Add(5, EQTreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(7, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Add(INPUT_ELEMENT, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QBinarySearchTree<int>::QBinarySearchTreeIterator it = QBinarySearchTree<int>::QBinarySearchTreeIterator(&TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly added when it is greater than the root and greater than its right child.
/// </summary>
QTEST_CASE ( Add_ElementIsCorrectlyAddedWhenItIsGreaterThanRootAndGreaterThanItsRightChild_Test )
{
    // [Preparation]
    const int INPUT_ELEMENT = 8;
    const int EXPECTED_VALUES[] = {5, 7, INPUT_ELEMENT};
    
    QBinarySearchTree<int> TREE(3);
    TREE.Add(5, EQTreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(7, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Add(INPUT_ELEMENT, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QBinarySearchTree<int>::QBinarySearchTreeIterator it = QBinarySearchTree<int>::QBinarySearchTreeIterator(&TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the iterator points to the added element.
/// </summary>
QTEST_CASE ( Add_ReturnedIteratorPointsToAddedElement_Test )
{
    // [Preparation]
    const int INPUT_ELEMENT = 8;
    
    QBinarySearchTree<int> TREE(3);
    TREE.Add(5, EQTreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(3, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    QBinarySearchTree<int>::QBinarySearchTreeIterator itResult = TREE.Add(INPUT_ELEMENT, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    BOOST_CHECK_EQUAL(*itResult, INPUT_ELEMENT);
}

/// <summary>
/// Checks that the number of elements is incremented after adding.
/// </summary>
QTEST_CASE ( Add_CountIsIncremented_Test )
{
    // [Preparation]
    const int INPUT_ELEMENT = 8;
    
    QBinarySearchTree<int> TREE(3);
    TREE.Add(5, EQTreeTraversalOrder::E_DepthFirstInOrder);
    const pointer_uint_q COUNT_BEFORE_ADDING = TREE.GetCount();

    // [Execution]
    TREE.Add(INPUT_ELEMENT, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    pointer_uint_q uCountAfterAdding = TREE.GetCount();
    BOOST_CHECK(uCountAfterAdding > COUNT_BEFORE_ADDING);
}

/// <summary>
/// Checks that the capacity is incremented after exceeding its value.
/// </summary>
QTEST_CASE ( Add_CapacityIsIncrementedWhenNecessary_Test )
{
    // [Preparation]
    const int INPUT_ELEMENT = 8;
    
    QBinarySearchTree<int> TREE(1);
    TREE.Add(5, EQTreeTraversalOrder::E_DepthFirstInOrder);
    const pointer_uint_q CAPACITY_BEFORE_ADDING = TREE.GetCapacity();

    // [Execution]
    TREE.Add(INPUT_ELEMENT, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    pointer_uint_q uCapacityAfterAdding = TREE.GetCapacity();
    BOOST_CHECK(uCapacityAfterAdding > CAPACITY_BEFORE_ADDING);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the element already exists.
/// </summary>
QTEST_CASE ( Add_AssertionFailsWhenTheElementAlreadyExists_Test )
{
    // [Preparation]
    const int ELEMENT = 0;
    
    QBinarySearchTree<int> TREE(1);
    TREE.Add(ELEMENT, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        TREE.Add(ELEMENT, EQTreeTraversalOrder::E_DepthFirstInOrder);
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
/// Checks that the element is not added when it already exists in the tree.
/// </summary>
QTEST_CASE ( Add_ElementIsNotAddedWhenItAlreadyExists_Test )
{
    // [Preparation]
    const int INPUT_ELEMENT = 1;
    const int EXPECTED_VALUES[] = {INPUT_ELEMENT};
    
    QBinarySearchTree<int> TREE(3);
    TREE.Add(INPUT_ELEMENT, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Add(INPUT_ELEMENT, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QBinarySearchTree<int>::QBinarySearchTreeIterator it = QBinarySearchTree<int>::QBinarySearchTreeIterator(&TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the iterator points to the end position when it is not added.
/// </summary>
QTEST_CASE ( Add_ReturnedIteratorPointsToEndPositionWhenElementIsNotAdded_Test )
{
    // [Preparation]
    const int INPUT_ELEMENT = 1;
    
    QBinarySearchTree<int> TREE(3);
    TREE.Add(INPUT_ELEMENT, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    QBinarySearchTree<int>::QBinarySearchTreeIterator itResult = TREE.Add(INPUT_ELEMENT, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    bool bIteratorPointsToEndPosition = itResult.IsEnd();
    BOOST_CHECK_EQUAL(bIteratorPointsToEndPosition);
}

#endif

/// <summary>
/// Checks that the tree is empty when removing the only element in it.
/// </summary>
QTEST_CASE ( Remove_TreeIsEmptyWhenRemovingTheOnlyElementInTheTree_Test )
{
    // [Preparation]
    QBinarySearchTree<int> TREE(3);
    QBinarySearchTree<int>::QBinarySearchTreeIterator itElementPosition = TREE.Add(5, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Remove(itElementPosition);

    // [Verification]
    bool bTreeIsEmpty = TREE.IsEmpty();
    BOOST_CHECK(bTreeIsEmpty);
}

/// <summary>
/// Checks that the element is correctly removed when it has both left and right children, which do not have descendants.
/// </summary>
QTEST_CASE ( Remove_ElementIsCorrectlyRemovedWhenItHasLeftAndRightChildrenWhichDoNotHaveDescendants_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {1, 4, 5};
    QBinarySearchTree<int> TREE(5);
    TREE.Add(5, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QBinarySearchTreeIterator itElementPosition = TREE.Add(3, EQTreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(1, EQTreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(4, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Remove(itElementPosition);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QBinarySearchTree<int>::QBinarySearchTreeIterator it = QBinarySearchTree<int>::QBinarySearchTreeIterator(&TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly removed when it has both left and right children and it is the left child of its parent.
/// </summary>
QTEST_CASE ( Remove_ElementIsCorrectlyRemovedWhenItHasLeftAndRightChildrenAndIsLeftChildOfItsParent_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {1, 4, 5};
    QBinarySearchTree<int> TREE(5);
    TREE.Add(5, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QBinarySearchTreeIterator itElementPosition = TREE.Add(3, EQTreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(1, EQTreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(4, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Remove(itElementPosition);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QBinarySearchTree<int>::QBinarySearchTreeIterator it = QBinarySearchTree<int>::QBinarySearchTreeIterator(&TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly removed when it has both left and right children and it is the right child of its parent.
/// </summary>
QTEST_CASE ( Remove_ElementIsCorrectlyRemovedWhenItHasLeftAndRightChildrenAndIsRightChildOfItsParent_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {5, 6, 8};
    QBinarySearchTree<int> TREE(5);
    TREE.Add(5, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QBinarySearchTreeIterator itElementPosition = TREE.Add(7, EQTreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(6, EQTreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(8, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Remove(itElementPosition);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QBinarySearchTree<int>::QBinarySearchTreeIterator it = QBinarySearchTree<int>::QBinarySearchTreeIterator(&TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly removed when it has both left and right children and the left child has a right child.
/// </summary>
QTEST_CASE ( Remove_ElementIsCorrectlyRemovedWhenItHasLeftAndRightChildrenAndTheLeftChildHasRightChild_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {1, 2, 4, 5};
    QBinarySearchTree<int> TREE(5);
    TREE.Add(5, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QBinarySearchTreeIterator itElementPosition = TREE.Add(3, EQTreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(1, EQTreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(2, EQTreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(4, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Remove(itElementPosition);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QBinarySearchTree<int>::QBinarySearchTreeIterator it = QBinarySearchTree<int>::QBinarySearchTreeIterator(&TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly removed when it has both left and right children and the left child has a left child.
/// </summary>
QTEST_CASE ( Remove_ElementIsCorrectlyRemovedWhenItHasLeftAndRightChildrenAndTheLeftChildHasLeftChild_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {0, 1, 4, 5};
    QBinarySearchTree<int> TREE(5);
    TREE.Add(5, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QBinarySearchTreeIterator itElementPosition = TREE.Add(3, EQTreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(1, EQTreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(4, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Remove(itElementPosition);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QBinarySearchTree<int>::QBinarySearchTreeIterator it = QBinarySearchTree<int>::QBinarySearchTreeIterator(&TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly removed when it has a left child only.
/// </summary>
QTEST_CASE ( Remove_ElementIsCorrectlyRemovedWhenItHasLeftChildOnly_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {1, 5};
    QBinarySearchTree<int> TREE(3);
    TREE.Add(5, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QBinarySearchTreeIterator itElementPosition = TREE.Add(3, EQTreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(1, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Remove(itElementPosition);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QBinarySearchTree<int>::QBinarySearchTreeIterator it = QBinarySearchTree<int>::QBinarySearchTreeIterator(&TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly removed when it has a right child only.
/// </summary>
QTEST_CASE ( Remove_ElementIsCorrectlyRemovedWhenItHasRightChildOnly_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {4, 5};
    QBinarySearchTree<int> TREE(3);
    TREE.Add(5, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QBinarySearchTreeIterator itElementPosition = TREE.Add(3, EQTreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(4, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Remove(itElementPosition);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QBinarySearchTree<int>::QBinarySearchTreeIterator it = QBinarySearchTree<int>::QBinarySearchTreeIterator(&TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly removed when it has no children.
/// </summary>
QTEST_CASE ( Remove_ElementIsCorrectlyRemovedWhenHasNoChildren_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {5};
    QBinarySearchTree<int> TREE(3);
    TREE.Add(5, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QBinarySearchTreeIterator itElementPosition = TREE.Add(3, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Remove(itElementPosition);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QBinarySearchTree<int>::QBinarySearchTreeIterator it = QBinarySearchTree<int>::QBinarySearchTreeIterator(&TREE, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the root is updated when it is removed.
/// </summary>
QTEST_CASE ( Remove_RootElementIsUpdatedWhenItIsRemoved_Test )
{
    // [Preparation]
    QBinarySearchTree<int> TREE(3);
    const QBinarySearchTree<int>::QBinarySearchTreeIterator ROOT_ITERATOR = TREE.Add(5, EQTreeTraversalOrder::E_DepthFirstInOrder);
    const QBinarySearchTree<int>::QBinarySearchTreeIterator EXPECTED_ITERATOR = TREE.Add(3, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Remove(ROOT_ITERATOR);

    // [Verification]
    //QBinarySearchTree<int>::QBinarySearchTreeIterator itRoot = TREE.GetRoot();
    //BOOST_CHECK(itRoot == EXPECTED_ITERATOR);
}

/// <summary>
/// Checks that the returned iterator points to the end position when there is not next element in the tree.
/// </summary>
QTEST_CASE ( Remove_ReturnedIteratorPointsToEndPositionWhenThereIsNoNextElementInTree_Test )
{
    // [Preparation]
    QBinarySearchTree<int> TREE(3);
    TREE.Add(5, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QBinarySearchTreeIterator itLastElement = TREE.Add(6, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    QBinarySearchTree<int>::QBinarySearchTreeIterator itResult = TREE.Remove(itLastElement);

    // [Verification]
    bool bIteratorPointsToEndPosition = itResult.IsEnd();
    BOOST_CHECK(bIteratorPointsToEndPosition);
}

/// <summary>
/// Checks that the returned iterator points to the next element.
/// </summary>
QTEST_CASE ( Remove_ReturnedIteratorPointsToNextElement_Test )
{
    // [Preparation]
    QBinarySearchTree<int> TREE(4);
    TREE.Add(5, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QBinarySearchTreeIterator itElementToRemove = TREE.Add(3, EQTreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(4, EQTreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(6, EQTreeTraversalOrder::E_DepthFirstInOrder);
    QBinarySearchTree<int>::QBinarySearchTreeIterator EXPECTED_ITERATOR = itElementToRemove;
    ++EXPECTED_ITERATOR;

    // [Execution]
    QBinarySearchTree<int>::QBinarySearchTreeIterator itResult = TREE.Remove(itElementToRemove);

    // [Verification]
    BOOST_CHECK(itResult == EXPECTED_ITERATOR);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to end position.
/// </summary>
QTEST_CASE ( Remove_AssertionFailsWhenTheInputIteratorPointsToEndPosition_Test )
{
    // [Preparation]
    QBinarySearchTree<int> TREE(1);
    QBinarySearchTree<int>::QBinarySearchTreeIterator itEnd = TREE.Add(0, EQTreeTraversalOrder::E_DepthFirstInOrder);
    ++itEnd;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        TREE.Remove(itEnd);
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
/// Checks that the capacity is correctly calculated.
/// </summary>
QTEST_CASE ( GetCapacity_IsCorrectlyCalculated_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_CAPACITY = 3;
    QBinarySearchTree<int> TREE(3);

    // [Execution]
    pointer_uint_q uCapacity = TREE.GetCapacity();

    // [Verification]
    BOOST_CHECK_EQUAL(uCapacity, EXPECTED_CAPACITY);
}

/// <summary>
/// Checks that the number of elements is correctly counted.
/// </summary>
QTEST_CASE ( GetCount_IsCorrectlyCalculated_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_COUNT = 3;
    QBinarySearchTree<int> TREE(3);
    TREE.Add(1, EQTreeTraversalOrder::E_DepthFirstInOrder); // [ 1 |   |   ]
    TREE.Add(2, EQTreeTraversalOrder::E_DepthFirstInOrder); // [ 1 | 2 |   ]
    TREE.Add(3, EQTreeTraversalOrder::E_DepthFirstInOrder); // [ 1 | 2 | 3 ]

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
    QBinarySearchTree<int> TREE(3);

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
    QBinarySearchTree<int> TREE(3);

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
    QBinarySearchTree<int> TREE(3);
    TREE.Add(1, EQTreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    bool bResult = TREE.IsEmpty();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

// End - Test Suite: QBinarySearchTree

QTEST_SUITE_END()
