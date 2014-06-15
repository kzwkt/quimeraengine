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
/// Checks that a common tree is correctly shrunk.
/// </summary>
QTEST_CASE ( Shrink_CommonTreeIsCorrectlyShrunk_Test )
{/* [TODO] Thund: Uncomment when AddChild is implemented
    // [Preparation]
    const pointer_uint_q EXPECTED_CAPACITY = 3;
    QNTree<int> TREE(4, 5);
    TREE.SetRootValue(1);
    TREE.AddChild(TREE.GetRoot(), 2);
    TREE.AddChild(TREE.GetRoot(), 3);

    // [Execution]
    TREE.Shrink();

    // [Verification]
    pointer_uint_q uStoredCapacity = TREE.GetCapacity();

    BOOST_CHECK_EQUAL(uStoredCapacity, EXPECTED_CAPACITY);*/
}

/// <summary>
/// Checks that the capacity of an empty tree equals zero after it has been shrunk.
/// </summary>
QTEST_CASE ( Shrink_EmptyTreeIsShrunkSoCapacityEqualsZero_Test )
{/* [TODO] Thund: Uncomment when Shrink is implemented
    // [Preparation]
    const pointer_uint_q EXPECTED_CAPACITY = 0;
    QNTree<int> TREE(4, 5);

    // [Execution]
    TREE.Shrink();

    // [Verification]
    pointer_uint_q uStoredCapacity = TREE.GetCapacity();

    BOOST_CHECK_EQUAL(uStoredCapacity, EXPECTED_CAPACITY);*/
}

/// <summary>
/// Checks that the capacity does not vary when it equals the number of elements in the tree.
/// </summary>
QTEST_CASE ( Shrink_NothingHappensWhenCountEqualsCapacity_Test )
{/* [TODO] Thund: Uncomment when AddChild is implemented
    // [Preparation]
    const pointer_uint_q EXPECTED_CAPACITY = 3;
    QNTree<int> TREE(3, 3);
    TREE.SetRootValue(1);
    TREE.AddChild(TREE.GetRoot(), 2);
    TREE.AddChild(TREE.GetRoot(), 3);

    // [Execution]
    TREE.Shrink();

    // [Verification]
    pointer_uint_q uStoredCapacity = TREE.GetCapacity();

    BOOST_CHECK_EQUAL(uStoredCapacity, EXPECTED_CAPACITY);*/
}

/// <summary>
/// Checks that it works correctly when the elements in the internal buffer has gaps.
/// </summary>
QTEST_CASE ( Shrink_ItWorksCorrectlyWhenInternalBufferHasEmptySlotsInTheMiddle_Test )
{/* [TODO] Thund: Uncomment when AddChild, RemoveChild, GetRoot and QNTreeIterator are implemented
    // [Preparation]
    const int EXPECTED_FIRST_ELEMENT = 1;
    const int EXPECTED_SECOND_ELEMENT = 3;
    const pointer_uint_q EXPECTED_CAPACITY = 2;
    QNTree<int> TREE(3, 3);
    TREE.SetRootValue(EXPECTED_FIRST_ELEMENT);              // [ 1 |   |   ]
    TREE.AddChild(TREE.GetRoot(), 2);                       // [ 1 | 2 |   ]
    TREE.AddChild(TREE.GetRoot(), EXPECTED_SECOND_ELEMENT); // [ 1 | 2 | 3 ]
    TREE.RemoveChild(TREE.GetRoot().GetFistChild(), 0);     // [ 1 | X | 3 ]

    // [Execution]
    TREE.Shrink();                                          // [ 1 | 3 ]

    // [Verification]
    pointer_uint_q uStoredCapacity = TREE.GetCapacity();
    QNTree<int>::QNTreeIterator it = TREE.GetRoot();

    BOOST_CHECK_EQUAL(uStoredCapacity, EXPECTED_CAPACITY);
    BOOST_CHECK_EQUAL(*it, EXPECTED_FIRST_ELEMENT);
    ++it;
    BOOST_CHECK_EQUAL(*it, EXPECTED_SECOND_ELEMENT);*/
}

/// <summary>
/// Checks that the capacity is correctly increased.
/// </summary>
QTEST_CASE ( Reserve_CapacityIsCorrectlyIncreased_Test )
{/* [TODO] Thund: Uncomment when Reserve is implemented
    // [Preparation]
    const pointer_uint_q EXPECTED_CAPACITY = 4;
    QNTree<int> TREE(2, 2);

    // [Execution]
    TREE.Reserve(EXPECTED_CAPACITY);

    // [Verification]
    pointer_uint_q uStoredCapacity = TREE.GetCapacity();

    BOOST_CHECK_EQUAL(uStoredCapacity, EXPECTED_CAPACITY);*/
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
