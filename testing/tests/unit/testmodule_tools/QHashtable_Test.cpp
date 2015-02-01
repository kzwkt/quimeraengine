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

#include "QAssertException.h"
#include "CallCounter.h"
#include "SQStringHashProvider.h"

using Kinesis::QuimeraEngine::Tools::Containers::QHashtable;
using Kinesis::QuimeraEngine::Common::Exceptions::QAssertException;
using Kinesis::QuimeraEngine::Tools::Containers::SQStringHashProvider;


QTEST_SUITE_BEGIN( QHashtable_TestSuite )

/// <summary>
/// Checks that the capacity of the container is correctly set when using common values.
/// </summary>
QTEST_CASE ( Constructor1_CapacityOfContainerIsCorrect_Test )
{
    // [Preparation]
    const pointer_uint_q NUMBER_OF_BUCKETS = 10;
    const pointer_uint_q NUMBER_OF_SLOTS = 5;
    const pointer_uint_q EXPECTED_CAPACITY = 50;

    // [Execution]
    QHashtable<int, int> hashtable(NUMBER_OF_BUCKETS, NUMBER_OF_SLOTS);

    // [Verification]
    pointer_uint_q uCapacity = hashtable.GetCapacity();
    BOOST_CHECK_EQUAL(uCapacity, EXPECTED_CAPACITY);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the number of buckets equals zero.
/// </summary>
QTEST_CASE ( Constructor1_AssertionFailsWhenNumberOfBucketsEqualsZero_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_ZERO = 0;
    const pointer_uint_q NUMBER_OF_SLOTS = 5;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        QHashtable<string_q, int> hashtable(INPUT_ZERO, NUMBER_OF_SLOTS);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when slots per buckets equals zero.
/// </summary>
QTEST_CASE ( Constructor1_AssertionFailsWhenSlotsPerBucketsEqualsZero_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_ZERO = 0;
    const pointer_uint_q NUMBER_OF_BUCKETS = 5;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        QHashtable<string_q, int> hashtable(NUMBER_OF_BUCKETS, INPUT_ZERO);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // #if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS
/* [TODO] Thund: Uncomment when GetFirst exists
/// <summary>
/// Checks that every key-value pair is copied.
/// </summary>
QTEST_CASE ( Constructor2_EveryKeyValuePairIsCopied_Test )
{
    // [Preparation]
    const int EXPECTED_KEYS[] = {0, 2, 1};
    const int EXPECTED_VALUES[] = {0, 2, 1};
    
    QHashtable<int, int> HASHTABLE(10, 2);
    HASHTABLE.Add(0, 0);
    HASHTABLE.Add(2, 2);
    HASHTABLE.Add(1, 1);

    // [Execution]
    QHashtable<int, int> hashtableCopy = HASHTABLE;

    // [Verification]
    bool bResultIsWhatEspected = true;

    for(int i = 0; i < sizeof(EXPECTED_KEYS) / sizeof(int); ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && hashtableCopy[EXPECTED_KEYS[i]] == EXPECTED_VALUES[i];
    }

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the copy constructor of every key and value is called.
/// </summary>
QTEST_CASE ( Constructor2_CopyConstructorOfEveryKeyAndValueIsCalled_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;
    
    // [Preparation]
    const unsigned int EXPECTED_CALLS = 6;
    QHashtable<CallCounter, CallCounter> HASHTABLE(10, 2);
    HASHTABLE.Add(CallCounter(), CallCounter());
    HASHTABLE.Add(CallCounter(), CallCounter());
    HASHTABLE.Add(CallCounter(), CallCounter());
    CallCounter::ResetCounters();

    // [Execution]
    QHashtable<CallCounter, CallCounter> hashtableCopy = HASHTABLE;

    // [Verification]
    unsigned int uCopyConstructorCalls = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uCopyConstructorCalls, EXPECTED_CALLS);
}

/// <summary>
/// Checks that an empty hashtable is correctly copied.
/// </summary>
QTEST_CASE ( Constructor2_ItIsCorrectlyCopiedWhenItIsEmpty_Test )
{
    // [Preparation]
    QHashtable<int, int> HASHTABLE(10, 2);

    // [Execution]
    QHashtable<int, int> hashtableCopy = HASHTABLE;

    // [Verification]
    bool bCopyIsEmpty = hashtableCopy.IsEmpty();
    BOOST_CHECK(bCopyIsEmpty);
}
*/
/// <summary>
/// Checks that the destructor of every key and value is called.
/// </summary>
QTEST_CASE ( Destructor_TheDestructorOfEveryKeyAndValueIsCalled_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;
    
    // [Preparation]
    const unsigned int EXPECTED_CALLS = 6;

    {
        QHashtable<CallCounter, CallCounter> HASHTABLE(10, 2);
        HASHTABLE.Add(CallCounter(), CallCounter());
        HASHTABLE.Add(CallCounter(), CallCounter());
        HASHTABLE.Add(CallCounter(), CallCounter());
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
    const pointer_uint_q EXPECTED_CAPACITY = 4U;
    QHashtable<int, int> hashtable(1, 1);

    // [Execution]
    hashtable.Reserve(EXPECTED_CAPACITY);

    // [Verification]
    pointer_uint_q uStoredCapacity = hashtable.GetCapacity();

    BOOST_CHECK_EQUAL(uStoredCapacity, EXPECTED_CAPACITY);
}

/// <summary>
/// Checks that elements are correctly reallocated.
/// </summary>
QTEST_CASE ( Reserve_ElementsAreCorrectlyReallocated_Test )
{
    // [Preparation]
    const bool ELEMENTS_ARE_THE_SAME = true;
    const pointer_uint_q INPUT_CAPACITY = 20U;
    QHashtable<int, int> hashtable(1, 3);
    const int NUMBER_OF_ELEMENTS = 3;
    
    for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
        hashtable.Add(i, i);

    // [Execution]
    hashtable.Reserve(INPUT_CAPACITY); // A reallocation occurs

    // [Verification]
    bool bElementsAreTheSame = true;

    for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
        bElementsAreTheSame = bElementsAreTheSame && (hashtable[i] == i);

    BOOST_CHECK_EQUAL(bElementsAreTheSame, ELEMENTS_ARE_THE_SAME);
}

/// <summary>
/// Checks that elements are not reallocated and capacity does not change when attempting to reserve less memory than currently reserved.
/// </summary>
QTEST_CASE ( Reserve_NothingHappensWhenTheAmountToReserveIsNoGreaterThanCurrentCapacity_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_CAPACITY = 1U;
    const pointer_uint_q EXPECTED_CAPACITY = 3U;
    QHashtable<int, int> hashtable(1, EXPECTED_CAPACITY);
    
    for(pointer_uint_q i = 0; i < EXPECTED_CAPACITY; ++i)
        hashtable.Add(i, i);

    const int* ORIGINAL_FIRST_ELEMENT_ADDRESS = &hashtable[0];

    // [Execution]
    hashtable.Reserve(INPUT_CAPACITY);

    // [Verification]
    pointer_uint_q uCapacity = hashtable.GetCapacity();
    int* pFirstElementAddress = &hashtable[0];

    BOOST_CHECK_EQUAL(pFirstElementAddress, ORIGINAL_FIRST_ELEMENT_ADDRESS);
    BOOST_CHECK_EQUAL(uCapacity, EXPECTED_CAPACITY);
}

/// <summary>
/// Checks that the element is correctly added when the hashtable is empty.
/// </summary>
QTEST_CASE ( Add_ElementIsCorrectlyAddedWhenHashtableIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    const int INPUT_KEY = 1;
    const int INPUT_VALUE = 0;
    const int EXPECTED_KEYS[] = {INPUT_KEY};
    const int EXPECTED_VALUES[] = {INPUT_VALUE};
    
    QHashtable<int, int> HASHTABLE(1, 1);

    // [Execution]
    HASHTABLE.Add(INPUT_KEY, INPUT_VALUE);

    // [Verification]
    bool bResultIsWhatEspected = true;

    for(int i = 0; i < sizeof(EXPECTED_KEYS) / sizeof(int); ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && HASHTABLE[EXPECTED_KEYS[i]] == EXPECTED_VALUES[i];
    }

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly added when the hashtable only contains one element.
/// </summary>
QTEST_CASE ( Add_ElementIsCorrectlyAddedWhenHashtableOnlyContainsOneElement_Test )
{
    // [Preparation]
    const int INPUT_KEY = 15;
    const int INPUT_VALUE = 0;
    const int EXPECTED_KEYS[] = {INPUT_KEY, 1};
    const int EXPECTED_VALUES[] = {INPUT_VALUE, 1};
    
    QHashtable<int, int> HASHTABLE(10, 2);
    HASHTABLE.Add(1, 1);

    // [Execution]
    HASHTABLE.Add(INPUT_KEY, INPUT_VALUE);

    // [Verification]
    bool bResultIsWhatEspected = true;

    for(int i = 0; i < sizeof(EXPECTED_KEYS) / sizeof(int); ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && HASHTABLE[EXPECTED_KEYS[i]] == EXPECTED_VALUES[i];
    }

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly added when its hash key collides with an existing element's.
/// </summary>
QTEST_CASE ( Add_ElementIsCorrectlyAddedWhenHashKeyCollidesWithExistingElements_Test )
{
    // [Preparation]
    const int INPUT_KEY = 11;
    const int INPUT_VALUE = 0;
    const int EXPECTED_KEYS[] = {INPUT_KEY, 1};
    const int EXPECTED_VALUES[] = {INPUT_VALUE, 1};
    
    QHashtable<int, int> HASHTABLE(10, 2);
    HASHTABLE.Add(1, 1);

    // [Execution]
    HASHTABLE.Add(INPUT_KEY, INPUT_VALUE);

    // [Verification]
    bool bResultIsWhatEspected = true;

    for(int i = 0; i < sizeof(EXPECTED_KEYS) / sizeof(int); ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && HASHTABLE[EXPECTED_KEYS[i]] == EXPECTED_VALUES[i];
    }

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the iterator points to the added element.
/// </summary>
QTEST_CASE ( Add_ReturnedIteratorPointsToAddedElement_Test )
{
    // [Preparation]
    const int INPUT_KEY = 2;
    const int INPUT_VALUE = 1;
    
    QHashtable<int, int> HASHTABLE(10, 2);
    HASHTABLE.Add(4, 2);
    HASHTABLE.Add(6, 3);

    // [Execution]
    QHashtable<int, int>::QConstHashtableIterator itResult = HASHTABLE.Add(INPUT_KEY, INPUT_VALUE);

    // [Verification]
    BOOST_CHECK(itResult->GetKey() == INPUT_KEY);
    BOOST_CHECK(itResult->GetValue() == INPUT_VALUE);
}

/// <summary>
/// Checks that the number of elements is incremented after adding.
/// </summary>
QTEST_CASE ( Add_CountIsIncremented_Test )
{
    // [Preparation]
    const int INPUT_KEY = 5;
    const int INPUT_VALUE = 1;
    
    QHashtable<int, int> HASHTABLE(10, 1);
    HASHTABLE.Add(6, 2);
    const pointer_uint_q COUNT_BEFORE_ADDING = HASHTABLE.GetCount();

    // [Execution]
    HASHTABLE.Add(INPUT_KEY, INPUT_VALUE);

    // [Verification]
    pointer_uint_q uCountAfterAdding = HASHTABLE.GetCount();
    BOOST_CHECK(uCountAfterAdding > COUNT_BEFORE_ADDING);
}

/// <summary>
/// Checks that the capacity is incremented after exceeding its value.
/// </summary>
QTEST_CASE ( Add_CapacityIsIncrementedWhenNecessary_Test )
{
    // [Preparation]
    const int INPUT_KEY = 6;
    const int INPUT_VALUE = 6;
    
    QHashtable<int, int> HASHTABLE(5, 1);
    HASHTABLE.Add(1, 1);
    HASHTABLE.Add(2, 2);
    HASHTABLE.Add(3, 3);
    HASHTABLE.Add(4, 4);
    HASHTABLE.Add(5, 5);
    const pointer_uint_q CAPACITY_BEFORE_ADDING = HASHTABLE.GetCapacity();

    // [Execution]
    HASHTABLE.Add(INPUT_KEY, INPUT_VALUE);

    // [Verification]
    pointer_uint_q uCapacityAfterAdding = HASHTABLE.GetCapacity();
    BOOST_CHECK(uCapacityAfterAdding > CAPACITY_BEFORE_ADDING);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the key already exists.
/// </summary>
QTEST_CASE ( Add_AssertionFailsWhenTheKeyAlreadyExists_Test )
{
    using Kinesis::QuimeraEngine::Common::Exceptions::QAssertException;

    // [Preparation]
    const int INPUT_KEY = 1;
    const int INPUT_VALUE = 1;
    
    QHashtable<int, int> HASHTABLE(10, 2);
    HASHTABLE.Add(INPUT_KEY, INPUT_VALUE);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        HASHTABLE.Add(INPUT_KEY, 0);
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
/// Checks that the correct value is returned when the key exists in the hashtable.
/// </sumary>
QTEST_CASE( OperatorArraySubscript_CorrectValueIsReturnedWhenKeyExists_Test )
{
    // [Preparation]
    const int INPUT_KEY = 2;
    const int EXPECTED_VALUE = 2;
    QHashtable<int, int> HASHTABLE(10, 2);
    HASHTABLE.Add(1, 1);
    HASHTABLE.Add(INPUT_KEY, EXPECTED_VALUE);
    HASHTABLE.Add(3, 3);

    // [Execution]
    int nValue = HASHTABLE[INPUT_KEY];

    // [Verification]
    BOOST_CHECK_EQUAL(nValue, EXPECTED_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the key does not exist in the hashtable.
/// </sumary>
QTEST_CASE( OperatorArraySubscript_AssertionFailsWhenKeyDoesNotExist_Test )
{
    using Kinesis::QuimeraEngine::Common::Exceptions::QAssertException;

    // [Preparation]
    const int INPUT_KEY = 2;
    QHashtable<int, int> HASHTABLE(10, 2);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        HASHTABLE[INPUT_KEY];
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
/// Checks that the correct value is returned when the key exists in the hashtable.
/// </sumary>
QTEST_CASE( GetValue_CorrectValueIsReturnedWhenKeyExists_Test )
{
    // [Preparation]
    const int INPUT_KEY = 2;
    const int EXPECTED_VALUE = 2;
    QHashtable<int, int> HASHTABLE(10, 2);
    HASHTABLE.Add(1, 1);
    HASHTABLE.Add(INPUT_KEY, EXPECTED_VALUE);
    HASHTABLE.Add(3, 3);

    // [Execution]
    int nValue = HASHTABLE.GetValue(INPUT_KEY);

    // [Verification]
    BOOST_CHECK_EQUAL(nValue, EXPECTED_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the key does not exist in the hashtable.
/// </sumary>
QTEST_CASE( GetValue_AssertionFailsWhenKeyDoesNotExist_Test )
{
    using Kinesis::QuimeraEngine::Common::Exceptions::QAssertException;

    // [Preparation]
    const int INPUT_KEY = 2;
    QHashtable<int, int> HASHTABLE(5, 2);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        HASHTABLE.GetValue(INPUT_KEY);
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
/// Checks that the value is set when the key exists in the HASHTABLE.
/// </sumary>
QTEST_CASE( SetValue_ValueIsSetWhenKeyExists_Test )
{
    // [Preparation]
    const int INPUT_KEY = 2;
    const int EXPECTED_VALUE = 2;
    QHashtable<int, int> HASHTABLE(10, 2);
    HASHTABLE.Add(1, 1);
    HASHTABLE.Add(INPUT_KEY, 10);
    HASHTABLE.Add(3, 3);

    // [Execution]
    HASHTABLE.SetValue(INPUT_KEY, EXPECTED_VALUE);

    // [Verification]
    int nValue = HASHTABLE.GetValue(INPUT_KEY);
    BOOST_CHECK_EQUAL(nValue, EXPECTED_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the key does not exist in the HASHTABLE.
/// </sumary>
QTEST_CASE( SetValue_AssertionFailsWhenKeyDoesNotExist_Test )
{
    using Kinesis::QuimeraEngine::Common::Exceptions::QAssertException;

    // [Preparation]
    const int INPUT_KEY = 2;
    QHashtable<int, int> HASHTABLE(10, 2);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        HASHTABLE.SetValue(INPUT_KEY, 0);
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
/// Checks that it returns True when the hashtable contains the key.
/// </summary>
QTEST_CASE ( ContainsKey_ReturnsTrueWhenHashtableContainsTheKey_Test )
{
    // [Preparation]
    const string_q INPUT_KEY("key3");
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(5, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 4);
    HASHTABLE.Add(INPUT_KEY, 5);
    HASHTABLE.Add("key4", 6);

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = HASHTABLE.ContainsKey(INPUT_KEY);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the hashtable does not contain the key.
/// </summary>
QTEST_CASE ( ContainsKey_ReturnsFalseWhenHashtableDoesNotContainTheKey_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(5, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 4);
    HASHTABLE.Add("key3", 5);
    HASHTABLE.Add("key4", 6);
    const string_q INPUT_KEY("key5");
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = HASHTABLE.ContainsKey(INPUT_KEY);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the hashtable is empty.
/// </summary>
QTEST_CASE ( ContainsKey_ReturnsFalseWhenHashtableIsEmpty_Test )
{
    // [Preparation]
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(3, 2);
    const string_q INPUT_KEY("key1");
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = HASHTABLE.ContainsKey(INPUT_KEY);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the hashtable is empty when removing the only element in it.
/// </summary>
QTEST_CASE ( Remove_HashtableIsEmptyWhenRemovingTheOnlyElementInTheHashtable_Test )
{
    // [Preparation]
    const string_q EXISTING_KEY("key1");
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(3, 2);
    HASHTABLE.Add(EXISTING_KEY, 0);

    // [Execution]
    HASHTABLE.Remove(EXISTING_KEY);

    // [Verification]
    bool bHashtableIsEmpty = HASHTABLE.IsEmpty();
    BOOST_CHECK(bHashtableIsEmpty);
}

/// <summary>
/// Checks that the key-value pair is removed when there are many pairs in the hashtable and the key exists.
/// </summary>
QTEST_CASE ( Remove_PairIsCorrectlyRemovedWhenThereAreManyAndKeyExists_Test )
{
    // [Preparation]
    const string_q EXISTING_KEY("key2");
    const string_q EXPECTED_KEYS[] = {"key1", "key3", "key4"};
    const int EXPECTED_VALUES[] = {1, 3, 4};
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(5, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add(EXISTING_KEY, 2);
    HASHTABLE.Add("key3", 3);
    HASHTABLE.Add("key4", 4);

    // [Execution]
    HASHTABLE.Remove(EXISTING_KEY);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator it = QHashtable<string_q, int, SQStringHashProvider>::QConstHashtableIterator(&HASHTABLE, 0);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetKey() == EXPECTED_KEYS[i];
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetValue() == EXPECTED_VALUES[i];
    }

    BOOST_CHECK(bResultIsWhatEspected);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input key does not exist in the hashtable.
/// </summary>
QTEST_CASE ( Remove_AssertionFailsWhenTheInputKeyDoesNotExist_Test )
{
    using Kinesis::QuimeraEngine::Common::Exceptions::QAssertException;

    // [Preparation]
    const string_q NON_EXISTING_KEY("key2");
    QHashtable<string_q, int, SQStringHashProvider> HASHTABLE(2, 2);
    HASHTABLE.Add("key1", 1);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        HASHTABLE.Remove(NON_EXISTING_KEY);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

// End - Test Suite: QHashtable
QTEST_SUITE_END()
