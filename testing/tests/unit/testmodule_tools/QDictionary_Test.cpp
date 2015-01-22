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

#include "QDictionary.h"

#include "DataTypesDefinitions.h"
#include "CallCounter.h"

using Kinesis::QuimeraEngine::Tools::Containers::QDictionary;
using Kinesis::QuimeraEngine::Common::DataTypes::string_q;


QTEST_SUITE_BEGIN( QDictionary_TestSuite )

/// <summary>
/// Checks that the default values have not changed since the last time this test was executed.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    // [TODO] Thund: Add more checks to this tests when more properties exist

    // [Execution]
    QDictionary<string_q, int> dictionary;

    // [Verification]
    bool bAllocatorIsNotNull = dictionary.GetAllocator() != null_q;
    BOOST_CHECK(bAllocatorIsNotNull);
}

/// <summary>
/// Checks that the default values have not changed since the last time this test was executed.
/// </summary>
QTEST_CASE ( Constructor2_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    // [TODO] Thund: Add more checks to this tests when more properties exist

    // [Execution]
    QDictionary<string_q, int> dictionary(1);

    // [Verification]
    bool bAllocatorIsNotNull = dictionary.GetAllocator() != null_q;
    BOOST_CHECK(bAllocatorIsNotNull);
}

/// <summary>
/// Checks that the initial capacity is correctly stored.
/// </summary>
QTEST_CASE ( Constructor2_CapacityIsCorrectlyStored_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECPTED_CAPACITY = 6;

    // [Execution]
    QDictionary<string_q, int> dictionary(EXPECPTED_CAPACITY);

    // [Verification]
    // [TODO] Thund: Uncomment when GetCapacity exists
    //pointer_uint_q uCapacity = dictionary.GetCapacity();
    //BOOST_CHECK_EQUAL(uCapacity, EXPECPTED_CAPACITY);
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
        QDictionary<string_q, int> dictionary(INPUT_ZERO);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // #if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

// [TODO] Thund: Uncomment when Add and Iterator exists
//
///// <summary>
///// Checks that the tree is correctly copied when it has elements.
///// </summary>
//QTEST_CASE ( Constructor3_TreeIsCorrectlyCopiedWhenItHasElements_Test )
//{
//    // [Preparation]
//    const int EXPECTED_VALUES[] = {1, 3, 5, 6, 8};
//    QBinarySearchTree<int> TREE(5);
//    TREE.Add(5, EQTreeTraversalOrder::E_DepthFirstInOrder);
//    TREE.Add(3, EQTreeTraversalOrder::E_DepthFirstInOrder);
//    TREE.Add(6, EQTreeTraversalOrder::E_DepthFirstInOrder);
//    TREE.Add(1, EQTreeTraversalOrder::E_DepthFirstInOrder);
//    TREE.Add(8, EQTreeTraversalOrder::E_DepthFirstInOrder);
//
//    const pointer_uint_q EXPECTED_COUNT = TREE.GetCount();
//
//    // [Execution]
//    QBinarySearchTree<int> copiedTree(TREE);
//
//    // [Verification]
//    bool bResultIsWhatEspected = true;
//
//    QBinarySearchTree<int>::QConstBinarySearchTreeIterator it = copiedTree.GetIterator(0, EQTreeTraversalOrder::E_DepthFirstInOrder);
//    int i = 0;
//
//    for(; !it.IsEnd(); ++it, ++i)
//        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];
//
//    pointer_uint_q uCount = copiedTree.GetCount();
//    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
//    BOOST_CHECK(bResultIsWhatEspected);
//}
//
///// <summary>
///// Checks that the tree is correctly copied when it is empty.
///// </summary>
//QTEST_CASE ( Constructor3_TreeIsCorrectlyCopiedWhenItIsEmpty_Test )
//{
//    // [Preparation]
//    QBinarySearchTree<int> TREE(3);
//
//    // [Execution]
//    QBinarySearchTree<int> copiedTree(TREE);
//
//    // [Verification]
//    bool bTreeIsEmpty = copiedTree.IsEmpty();
//    BOOST_CHECK(bTreeIsEmpty);
//}
//
///// <summary>
///// Checks that the copy constructors are called for each element.
///// </summary>
//QTEST_CASE ( Constructor3_CopyConstructorsAreCalledForAllElements_Test )
//{
//    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;
//
//    // [Preparation]
//    QBinarySearchTree<CallCounter> TREE(5);
//    TREE.Add(CallCounter(), EQTreeTraversalOrder::E_DepthFirstInOrder);
//    TREE.Add(CallCounter(), EQTreeTraversalOrder::E_DepthFirstInOrder);
//    TREE.Add(CallCounter(), EQTreeTraversalOrder::E_DepthFirstInOrder);
//    TREE.Add(CallCounter(), EQTreeTraversalOrder::E_DepthFirstInOrder);
//    TREE.Add(CallCounter(), EQTreeTraversalOrder::E_DepthFirstInOrder);
//
//    const unsigned int EXPECTED_VALUE = TREE.GetCount();
//    CallCounter::ResetCounters();
//
//    // [Execution]
//    QBinarySearchTree<CallCounter> copiedTree(TREE);
//
//    // [Verification]
//    unsigned int uNumberOfCalls = CallCounter::GetCopyConstructorCallsCount();
//    BOOST_CHECK_EQUAL(uNumberOfCalls, EXPECTED_VALUE);
//}

/// <summary>
/// Checks that the destructor of every key and every value is called.
/// </summary>
QTEST_CASE ( Destructor_DestructorOfEveryKeyAndValueIsCalled_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    // const pointer_uint_q EXPECTED_DESTRUCTOR_CALLS = 6;

    //// [TODO] Thund: Uncommend when Add method exists
    //{
    //    QDictionary<CallCounter, CallCounter> dictionary;
    //    dictionary.Add(CallCounter(), CallCounter());
    //    dictionary.Add(CallCounter(), CallCounter());
    //    dictionary.Add(CallCounter(), CallCounter());
    //    CallCounter::ResetCounters();

    //// [Execution]
    //} // Destructor called

    //// [Verification]
    //pointer_uint_q uDestructorCalls = CallCounter::GetDestructorCallsCount();
    //BOOST_CHECK_EQUAL(uDestructorCalls, EXPECTED_DESTRUCTOR_CALLS);
}

// [TODO] Thund: Uncomment when Add and Iterator exists
///// <summary>
///// Checks that the tree is correctly copied when it has elements and the destination tree is empty.
///// </summary>
//QTEST_CASE ( OperatorAssignment_DictionaryIsCorrectlyCopiedWhenItHasElementsAndDestinationIsEmpty_Test )
//{
//    // [Preparation]
//    const int EXPECTED_VALUES[] = {1, 3, 5, 6, 8};
//    QDictionary<string_q, int> DICTIONARY(5);
//    DICTIONARY.Add("key1", 1);
//    DICTIONARY.Add("key2", 2);
//    DICTIONARY.Add("key3", 3);
//    DICTIONARY.Add("key4", 4);
//    DICTIONARY.Add("key5", 5);
//
//    const pointer_uint_q EXPECTED_COUNT = DICTIONARY.GetCount();
//    QDictionary<string_q, int> copiedDictionary(8);
//
//    // [Execution]
//    copiedDictionary = DICTIONARY;
//
//    // [Verification]
//    bool bResultIsWhatEspected = true;
//
//    QDictionary<int>::QConstDictionaryIterator it = copiedDictionary.GetIterator(0, EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    int i = 0;
//
//    for(; !it.IsEnd(); ++it, ++i)
//        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];
//
//    pointer_uint_q uCount = copiedDictionary.GetCount();
//    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
//    BOOST_CHECK(bResultIsWhatEspected);
//}
//
///// <summary>
///// Checks that the tree is correctly copied when there are more elements in the source tree than in the destination.
///// </summary>
//QTEST_CASE ( OperatorAssignment_DictionaryIsCorrectlyCopiedWhenThereAreMoreElementsInSourceThanInDestination_Test )
//{
//    // [Preparation]
//    const int EXPECTED_VALUES[] = {1, 3, 5, 6, 8};
//    QDictionary<int> DICTIONARY(8);
//    DICTIONARY.Add(5, EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    DICTIONARY.Add(3, EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    DICTIONARY.Add(6, EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    DICTIONARY.Add(1, EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    DICTIONARY.Add(8, EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    const pointer_uint_q EXPECTED_COUNT = DICTIONARY.GetCount();
//
//    QDictionary<int> copiedDictionary(3);
//    copiedDictionary.Add(9, EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    copiedDictionary.Add(0, EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    copiedDictionary.Add(2, EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//
//    // [Execution]
//    copiedDictionary = DICTIONARY;
//
//    // [Verification]
//    bool bResultIsWhatEspected = true;
//
//    QDictionary<int>::QConstBinarySearchDictionaryIterator it = copiedDictionary.GetIterator(0, EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    int i = 0;
//
//    for(; !it.IsEnd(); ++it, ++i)
//        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];
//
//    pointer_uint_q uCount = copiedDictionary.GetCount();
//    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
//    BOOST_CHECK(bResultIsWhatEspected);
//}
//
///// <summary>
///// Checks that the tree is correctly copied when there are less elements in the source tree than in the destination.
///// </summary>
//QTEST_CASE ( OperatorAssignment_DictionaryIsCorrectlyCopiedWhenThereAreLessElementsInSourceThanInDestination_Test )
//{
//    // [Preparation]
//    const int EXPECTED_VALUES[] = {3, 5};
//    QDictionary<int> DICTIONARY(3);
//    DICTIONARY.Add(5, EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    DICTIONARY.Add(3, EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    const pointer_uint_q EXPECTED_COUNT = DICTIONARY.GetCount();
//
//    QDictionary<int> copiedDictionary(3);
//    copiedDictionary.Add(9, EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    copiedDictionary.Add(0, EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    copiedDictionary.Add(2, EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//
//    // [Execution]
//    copiedDictionary = DICTIONARY;
//
//    // [Verification]
//    bool bResultIsWhatEspected = true;
//
//    QDictionary<int>::QConstBinarySearchDictionaryIterator it = copiedDictionary.GetIterator(0, EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    int i = 0;
//
//    for(; !it.IsEnd(); ++it, ++i)
//        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];
//
//    pointer_uint_q uCount = copiedDictionary.GetCount();
//    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
//    BOOST_CHECK(bResultIsWhatEspected);
//}
//
///// <summary>
///// Checks that the tree is correctly copied when there are the same number of elements in the source tree than in the destination.
///// </summary>
//QTEST_CASE ( OperatorAssignment_DictionaryIsCorrectlyCopiedWhenThereAreSameNumberOfElementsInSourceThanInDestination_Test )
//{
//    // [Preparation]
//    const int EXPECTED_VALUES[] = {3, 5, 6};
//    QDictionary<int> DICTIONARY(3);
//    DICTIONARY.Add(5, EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    DICTIONARY.Add(3, EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    DICTIONARY.Add(6, EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    const pointer_uint_q EXPECTED_COUNT = DICTIONARY.GetCount();
//
//    QDictionary<int> copiedDictionary(3);
//    copiedDictionary.Add(9, EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    copiedDictionary.Add(0, EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    copiedDictionary.Add(2, EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//
//    // [Execution]
//    copiedDictionary = DICTIONARY;
//
//    // [Verification]
//    bool bResultIsWhatEspected = true;
//
//    QDictionary<int>::QConstBinarySearchDictionaryIterator it = copiedDictionary.GetIterator(0, EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    int i = 0;
//
//    for(; !it.IsEnd(); ++it, ++i)
//        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];
//
//    pointer_uint_q uCount = copiedDictionary.GetCount();
//    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
//    BOOST_CHECK(bResultIsWhatEspected);
//}
//
///// <summary>
///// Checks that the tree is correctly copied when it is empty and the destination tree has elements.
///// </summary>
//QTEST_CASE ( OperatorAssignment_DictionaryIsCorrectlyCopiedWhenItIsEmptyAndDestinationHasElements_Test )
//{
//    // [Preparation]
//    QDictionary<int> DICTIONARY(3);
//    QDictionary<int> copiedDictionary(3);
//    copiedDictionary.Add(5, EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    copiedDictionary.Add(3, EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    copiedDictionary.Add(6, EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//
//    // [Execution]
//    copiedDictionary = DICTIONARY;
//
//    // [Verification]
//    bool bDictionaryIsEmpty = copiedDictionary.IsEmpty();
//    BOOST_CHECK(bDictionaryIsEmpty);
//}
//
///// <summary>
///// Checks that the copy constructors are called for each element.
///// </summary>
//QTEST_CASE ( OperatorAssignment_CopyConstructorsAreCalledForAllElements_Test )
//{
//    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;
//
//    // [Preparation]
//    QDictionary<CallCounter> DICTIONARY(8);
//    DICTIONARY.Add(CallCounter(), EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    DICTIONARY.Add(CallCounter(), EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    DICTIONARY.Add(CallCounter(), EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    DICTIONARY.Add(CallCounter(), EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    DICTIONARY.Add(CallCounter(), EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//
//    QDictionary<CallCounter> copiedDictionary(3);
//    copiedDictionary.Add(CallCounter(), EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    copiedDictionary.Add(CallCounter(), EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    copiedDictionary.Add(CallCounter(), EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//
//    const unsigned int EXPECTED_COPY_CONSTRUCTORS_VALUE = DICTIONARY.GetCount();
//    CallCounter::ResetCounters();
//
//    // [Execution]
//    copiedDictionary = DICTIONARY;
//
//    // [Verification]
//    unsigned int uNumberOfCalls = CallCounter::GetCopyConstructorCallsCount();
//    BOOST_CHECK_EQUAL(uNumberOfCalls, EXPECTED_COPY_CONSTRUCTORS_VALUE);
//}
//
///// <summary>
///// Checks that the destructors are called for each element.
///// </summary>
//QTEST_CASE ( OperatorAssignment_DestructorsAreCalledForAllElements_Test )
//{
//    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;
//    
//    // [Preparation]
//    QDictionary<CallCounter> DICTIONARY(8);
//    DICTIONARY.Add(CallCounter(), EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    DICTIONARY.Add(CallCounter(), EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    DICTIONARY.Add(CallCounter(), EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    DICTIONARY.Add(CallCounter(), EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    DICTIONARY.Add(CallCounter(), EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//
//    QDictionary<CallCounter> copiedDictionary(3);
//    copiedDictionary.Add(CallCounter(), EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    copiedDictionary.Add(CallCounter(), EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//    copiedDictionary.Add(CallCounter(), EQDictionaryTraversalOrder::E_DepthFirstInOrder);
//
//    const unsigned int EXPECTED_DESTRUCTORS_VALUE = copiedDictionary.GetCount();
//    CallCounter::ResetCounters();
//
//    // [Execution]
//    copiedDictionary = DICTIONARY;
//
//    // [Verification]
//    unsigned int uNumberOfCalls = CallCounter::GetDestructorCallsCount();
//    BOOST_CHECK_EQUAL(uNumberOfCalls, EXPECTED_DESTRUCTORS_VALUE);
//}


// End - Test Suite: QDictionary
QTEST_SUITE_END()
