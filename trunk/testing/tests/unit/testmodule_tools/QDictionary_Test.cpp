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
#include "QAssertException.h"

using Kinesis::QuimeraEngine::Tools::Containers::QDictionary;
using Kinesis::QuimeraEngine::Common::DataTypes::string_q;


QTEST_SUITE_BEGIN( QDictionary_TestSuite )

/// <summary>
/// Checks that the default values have not changed since the last time this test was executed.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]

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
    pointer_uint_q uCapacity = dictionary.GetCapacity();
    BOOST_CHECK_EQUAL(uCapacity, EXPECPTED_CAPACITY);
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

/// <summary>
/// Checks that the dictionary is correctly copied when it has elements.
/// </summary>
QTEST_CASE ( Constructor3_DictionaryIsCorrectlyCopiedWhenItHasElements_Test )
{
    // [Preparation]
    const string_q EXPECTED_KEYS[] = {"key1", "key2", "key3", "key4", "key5"};
    const int EXPECTED_VALUES[] = {1, 3, 5, 6, 8};
    QDictionary<string_q, int> DICTIONARY(5);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add("key2", 3);
    DICTIONARY.Add("key3", 5);
    DICTIONARY.Add("key4", 6);
    DICTIONARY.Add("key5", 8);

    const pointer_uint_q EXPECTED_COUNT = DICTIONARY.GetCount();

    // [Execution]
    QDictionary<string_q, int> copiedDictionary(DICTIONARY);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QDictionary<string_q, int>::QConstDictionaryIterator it = copiedDictionary.GetFirst();
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetKey() == EXPECTED_KEYS[i];
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetValue() == EXPECTED_VALUES[i];
    }

    pointer_uint_q uCount = copiedDictionary.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the dictionary is correctly copied when it is empty.
/// </summary>
QTEST_CASE ( Constructor3_DictionaryIsCorrectlyCopiedWhenItIsEmpty_Test )
{
    // [Preparation]
    QDictionary<string_q, int> DICTIONARY(3);

    // [Execution]
    QDictionary<string_q, int> copiedDictionary(DICTIONARY);

    // [Verification]
    bool bDictionaryIsEmpty = copiedDictionary.IsEmpty();
    BOOST_CHECK(bDictionaryIsEmpty);
}

/// <summary>
/// Checks that the copy constructors are called for each element.
/// </summary>
QTEST_CASE ( Constructor3_CopyConstructorsAreCalledForAllElements_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    QDictionary<CallCounter, CallCounter> DICTIONARY(5);
    DICTIONARY.Add(CallCounter(), CallCounter());
    DICTIONARY.Add(CallCounter(), CallCounter());
    DICTIONARY.Add(CallCounter(), CallCounter());
    DICTIONARY.Add(CallCounter(), CallCounter());
    DICTIONARY.Add(CallCounter(), CallCounter());

    const unsigned int EXPECTED_VALUE = DICTIONARY.GetCount() * 2U;
    CallCounter::ResetCounters();

    // [Execution]
    QDictionary<CallCounter, CallCounter> copiedDictionary(DICTIONARY);

    // [Verification]
    unsigned int uNumberOfCalls = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uNumberOfCalls, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the destructor of every key and every value is called.
/// </summary>
QTEST_CASE ( Destructor_DestructorOfEveryKeyAndValueIsCalled_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    const pointer_uint_q EXPECTED_DESTRUCTOR_CALLS = 6;

    {
        QDictionary<CallCounter, CallCounter> dictionary;
        dictionary.Add(CallCounter(), CallCounter());
        dictionary.Add(CallCounter(), CallCounter());
        dictionary.Add(CallCounter(), CallCounter());
        CallCounter::ResetCounters();

    // [Execution]
    } // Destructor called

    // [Verification]
    pointer_uint_q uDestructorCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorCalls, EXPECTED_DESTRUCTOR_CALLS);
}

/// <summary>
/// Checks that the tree is correctly copied when it has elements and the destination tree is empty.
/// </summary>
QTEST_CASE ( OperatorAssignment_DictionaryIsCorrectlyCopiedWhenItHasElementsAndDestinationIsEmpty_Test )
{
    // [Preparation]
    const string_q EXPECTED_KEYS[] = {"key1", "key2", "key3", "key4", "key5"};
    const int EXPECTED_VALUES[] = {1, 3, 5, 6, 8};
    QDictionary<string_q, int> DICTIONARY(5);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add("key2", 3);
    DICTIONARY.Add("key3", 5);
    DICTIONARY.Add("key4", 6);
    DICTIONARY.Add("key5", 8);

    const pointer_uint_q EXPECTED_COUNT = DICTIONARY.GetCount();
    QDictionary<string_q, int> copiedDictionary(8);

    // [Execution]
    copiedDictionary = DICTIONARY;

    // [Verification]
    bool bResultIsWhatEspected = true;

    QDictionary<string_q, int>::QConstDictionaryIterator it = copiedDictionary.GetFirst();
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetKey() == EXPECTED_KEYS[i];
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetValue() == EXPECTED_VALUES[i];
    }

    pointer_uint_q uCount = copiedDictionary.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the tree is correctly copied when there are more elements in the source tree than in the destination.
/// </summary>
QTEST_CASE ( OperatorAssignment_DictionaryIsCorrectlyCopiedWhenThereAreMoreElementsInSourceThanInDestination_Test )
{
    // [Preparation]
    const string_q EXPECTED_KEYS[] = {"key1", "key2", "key3", "key4", "key5"};
    const int EXPECTED_VALUES[] = {1, 3, 5, 6, 8};
    QDictionary<string_q, int> DICTIONARY(5);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add("key2", 3);
    DICTIONARY.Add("key3", 5);
    DICTIONARY.Add("key4", 6);
    DICTIONARY.Add("key5", 8);
    const pointer_uint_q EXPECTED_COUNT = DICTIONARY.GetCount();

    QDictionary<string_q, int> copiedDictionary(3);
    copiedDictionary.Add("key5", 10);
    copiedDictionary.Add("key6", 11);
    copiedDictionary.Add("key7", 12);

    // [Execution]
    copiedDictionary = DICTIONARY;

    // [Verification]
    bool bResultIsWhatEspected = true;

    QDictionary<string_q, int>::QConstDictionaryIterator it = copiedDictionary.GetFirst();
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetKey() == EXPECTED_KEYS[i];
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetValue() == EXPECTED_VALUES[i];
    }

    pointer_uint_q uCount = copiedDictionary.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the tree is correctly copied when there are less elements in the source tree than in the destination.
/// </summary>
QTEST_CASE ( OperatorAssignment_DictionaryIsCorrectlyCopiedWhenThereAreLessElementsInSourceThanInDestination_Test )
{
    // [Preparation]
    const string_q EXPECTED_KEYS[] = {"key1", "key2"};
    const int EXPECTED_VALUES[] = {1, 3};
    QDictionary<string_q, int> DICTIONARY(5);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add("key2", 3);
    const pointer_uint_q EXPECTED_COUNT = DICTIONARY.GetCount();

    QDictionary<string_q, int> copiedDictionary(3);
    copiedDictionary.Add("key5", 10);
    copiedDictionary.Add("key6", 11);
    copiedDictionary.Add("key7", 12);

    // [Execution]
    copiedDictionary = DICTIONARY;

    // [Verification]
    bool bResultIsWhatEspected = true;

    QDictionary<string_q, int>::QConstDictionaryIterator it = copiedDictionary.GetFirst();
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetKey() == EXPECTED_KEYS[i];
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetValue() == EXPECTED_VALUES[i];
    }

    pointer_uint_q uCount = copiedDictionary.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the tree is correctly copied when there are the same number of elements in the source tree than in the destination.
/// </summary>
QTEST_CASE ( OperatorAssignment_DictionaryIsCorrectlyCopiedWhenThereAreSameNumberOfElementsInSourceThanInDestination_Test )
{
    // [Preparation]
    const string_q EXPECTED_KEYS[] = {"key1", "key2", "key3"};
    const int EXPECTED_VALUES[] = {1, 3, 5};
    QDictionary<string_q, int> DICTIONARY(5);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add("key2", 3);
    DICTIONARY.Add("key3", 5);
    const pointer_uint_q EXPECTED_COUNT = DICTIONARY.GetCount();

    QDictionary<string_q, int> copiedDictionary(3);
    copiedDictionary.Add("key5", 10);
    copiedDictionary.Add("key6", 11);
    copiedDictionary.Add("key7", 12);

    // [Execution]
    copiedDictionary = DICTIONARY;

    // [Verification]
    bool bResultIsWhatEspected = true;

    QDictionary<string_q, int>::QConstDictionaryIterator it = copiedDictionary.GetFirst();
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetKey() == EXPECTED_KEYS[i];
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetValue() == EXPECTED_VALUES[i];
    }

    pointer_uint_q uCount = copiedDictionary.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the tree is correctly copied when it is empty and the destination tree has elements.
/// </summary>
QTEST_CASE ( OperatorAssignment_DictionaryIsCorrectlyCopiedWhenItIsEmptyAndDestinationHasElements_Test )
{
    // [Preparation]
    QDictionary<string_q, int> DICTIONARY(3);
    QDictionary<string_q, int> copiedDictionary(3);
    copiedDictionary.Add("key5", 10);
    copiedDictionary.Add("key6", 11);
    copiedDictionary.Add("key7", 12);

    // [Execution]
    copiedDictionary = DICTIONARY;

    // [Verification]
    bool bDictionaryIsEmpty = copiedDictionary.IsEmpty();
    BOOST_CHECK(bDictionaryIsEmpty);
}

/// <summary>
/// Checks that the copy constructors are called for each key and value.
/// </summary>
QTEST_CASE ( OperatorAssignment_CopyConstructorsAreCalledForAllKeysAndValues_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    QDictionary<CallCounter, CallCounter> DICTIONARY(5);
    DICTIONARY.Add(CallCounter(), CallCounter());
    DICTIONARY.Add(CallCounter(), CallCounter());
    DICTIONARY.Add(CallCounter(), CallCounter());
    DICTIONARY.Add(CallCounter(), CallCounter());
    DICTIONARY.Add(CallCounter(), CallCounter());

    QDictionary<CallCounter, CallCounter> copiedDictionary(3);
    copiedDictionary.Add(CallCounter(), CallCounter());
    copiedDictionary.Add(CallCounter(), CallCounter());
    copiedDictionary.Add(CallCounter(), CallCounter());

    const unsigned int EXPECTED_COPY_CONSTRUCTORS_VALUE = DICTIONARY.GetCount() * 2U;
    CallCounter::ResetCounters();

    // [Execution]
    copiedDictionary = DICTIONARY;

    // [Verification]
    unsigned int uNumberOfCalls = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uNumberOfCalls, EXPECTED_COPY_CONSTRUCTORS_VALUE);
}

/// <summary>
/// Checks that the destructors are called for each key and value.
/// </summary>
QTEST_CASE ( OperatorAssignment_DestructorsAreCalledForAllKeysAndValues_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;
    
    // [Preparation]
    QDictionary<CallCounter, CallCounter> DICTIONARY(5);
    DICTIONARY.Add(CallCounter(), CallCounter());
    DICTIONARY.Add(CallCounter(), CallCounter());
    DICTIONARY.Add(CallCounter(), CallCounter());
    DICTIONARY.Add(CallCounter(), CallCounter());
    DICTIONARY.Add(CallCounter(), CallCounter());

    QDictionary<CallCounter, CallCounter> copiedDictionary(3);
    copiedDictionary.Add(CallCounter(), CallCounter());
    copiedDictionary.Add(CallCounter(), CallCounter());
    copiedDictionary.Add(CallCounter(), CallCounter());

    const unsigned int EXPECTED_DESTRUCTORS_VALUE = copiedDictionary.GetCount() * 2U;
    CallCounter::ResetCounters();

    // [Execution]
    copiedDictionary = DICTIONARY;

    // [Verification]
    unsigned int uNumberOfCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uNumberOfCalls, EXPECTED_DESTRUCTORS_VALUE);
}

/// <summary>
/// Checks if it the clone method works properly.
/// </summary>
QTEST_CASE ( Clone_ClonedDictionaryHasSameValuesThanTheOriginalDictionary_Test )
{
    // [Preparation]
    const string_q EXPECTED_KEYS[] = {"key1", "key2", "key3"};
    const int EXPECTED_VALUES[] = {1, 3, 5};
    QDictionary<string_q, int> sourceDictionary(5);
    sourceDictionary.Add("key1", 1);
    sourceDictionary.Add("key2", 3);
    sourceDictionary.Add("key3", 5);

    QDictionary<string_q, int> destinationDictionary(3);

    // [Execution]
    sourceDictionary.Clone(destinationDictionary);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QDictionary<string_q, int>::QConstDictionaryIterator it = destinationDictionary.GetFirst();
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetKey() == EXPECTED_KEYS[i];
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetValue() == EXPECTED_VALUES[i];
    }

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks if it the clone method works properly when the destination dictionary has more capacity and elements.
/// </summary>
QTEST_CASE ( Clone_ClonedDictionaryHasSameValuesThanTheOriginalDictionaryWhenInputDictionaryHasMoreCapacityAndElements_Test )
{
    // [Preparation]
    const string_q EXPECTED_KEYS[] = {"key1", "key2", "key3"};
    const int EXPECTED_VALUES[] = {1, 2, 3};
    QDictionary<string_q, int> sourceDictionary(3);
    sourceDictionary.Add("key1", 1);
    sourceDictionary.Add("key2", 2);
    sourceDictionary.Add("key3", 3);

    QDictionary<string_q, int> destinationDictionary(5);
    destinationDictionary.Add("key4", 4);
    destinationDictionary.Add("key5", 5);
    destinationDictionary.Add("key6", 6);
    destinationDictionary.Add("key7", 7);
    destinationDictionary.Add("key8", 8);

    // [Execution]
    sourceDictionary.Clone(destinationDictionary);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QDictionary<string_q, int>::QConstDictionaryIterator it = destinationDictionary.GetFirst();
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetKey() == EXPECTED_KEYS[i];
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetValue() == EXPECTED_VALUES[i];
    }

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks if it the clone method works properly when the destination dictionary has less capacity and elements.
/// </summary>
QTEST_CASE ( Clone_ClonedDictionaryHasSameValuesThanTheOriginalListWhenInputDictionaryHasLessCapacityAndElements_Test )
{
    // [Preparation]
    const string_q EXPECTED_KEYS[] = {"key1", "key2", "key3", "key4",  "key5"};
    const int EXPECTED_VALUES[] = {1, 2, 3, 4, 5};
    QDictionary<string_q, int> sourceDictionary(5);
    sourceDictionary.Add("key1", 1);
    sourceDictionary.Add("key2", 2);
    sourceDictionary.Add("key3", 3);
    sourceDictionary.Add("key4", 4);
    sourceDictionary.Add("key5", 5);

    QDictionary<string_q, int> destinationDictionary(3);
    destinationDictionary.Add("key6", 6);
    destinationDictionary.Add("key7", 7);
    destinationDictionary.Add("key8", 8);

    // [Execution]
    sourceDictionary.Clone(destinationDictionary);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QDictionary<string_q, int>::QConstDictionaryIterator it = destinationDictionary.GetFirst();
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetKey() == EXPECTED_KEYS[i];
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetValue() == EXPECTED_VALUES[i];
    }

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the number of elements is correctly counted.
/// </summary>
QTEST_CASE ( GetCount_IsCorrectlyCalculated_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_COUNT = 3;
    QDictionary<string_q, int> DICTIONARY(3);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add("key2", 2);
    DICTIONARY.Add("key3", 3);

    // [Execution]
    pointer_uint_q uCount = DICTIONARY.GetCount();

    // [Verification]
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that it returns zero when the dictionary is empty.
/// </summary>
QTEST_CASE ( GetCount_ReturnsZeroWhenDictionaryIsEmpty_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_COUNT = 0;
    QDictionary<string_q, int> DICTIONARY(3);

    // [Execution]
    pointer_uint_q uCount = DICTIONARY.GetCount();

    // [Verification]
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that it returns True when the dictionary is empty.
/// </summary>
QTEST_CASE ( IsEmpty_ReturnsTrueWhenDictionaryIsEmpty_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    QDictionary<string_q, int> DICTIONARY(3);

    // [Execution]
    bool bResult = DICTIONARY.IsEmpty();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the dictionary is not empty.
/// </summary>
QTEST_CASE ( IsEmpty_ReturnsFalseWhenDictionaryIsNotEmpty_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    QDictionary<string_q, int> DICTIONARY(3);
    DICTIONARY.Add("key1", 1);

    // [Execution]
    bool bResult = DICTIONARY.IsEmpty();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that the correct value is returned when the key exists in the dictionary.
/// </sumary>
QTEST_CASE( OperatorArraySubscript_CorrectValueIsReturnedWhenKeyExists_Test )
{
    // [Preparation]
    const string_q INPUT_KEY("key2");
    const int EXPECTED_VALUE = 2;
    QDictionary<string_q, int> DICTIONARY(3);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add(INPUT_KEY, EXPECTED_VALUE);
    DICTIONARY.Add("key3", 3);

    // [Execution]
    int nValue = DICTIONARY[INPUT_KEY];

    // [Verification]
    BOOST_CHECK_EQUAL(nValue, EXPECTED_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the key does not exist in the dictionary.
/// </sumary>
QTEST_CASE( OperatorArraySubscript_AssertionFailsWhenKeyDoesNotExist_Test )
{
    using Kinesis::QuimeraEngine::Common::Exceptions::QAssertException;

    // [Preparation]
    const string_q INPUT_KEY("key2");
    QDictionary<string_q, int> DICTIONARY(3);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        DICTIONARY[INPUT_KEY];
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
/// Checks that the correct value is returned when the key exists in the dictionary.
/// </sumary>
QTEST_CASE( GetValue_CorrectValueIsReturnedWhenKeyExists_Test )
{
    // [Preparation]
    const string_q INPUT_KEY("key2");
    const int EXPECTED_VALUE = 2;
    QDictionary<string_q, int> DICTIONARY(3);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add(INPUT_KEY, EXPECTED_VALUE);
    DICTIONARY.Add("key3", 3);
    

    // [Execution]
    int nValue = DICTIONARY.GetValue(INPUT_KEY);

    // [Verification]
    BOOST_CHECK_EQUAL(nValue, EXPECTED_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the key does not exist in the dictionary.
/// </sumary>
QTEST_CASE( GetValue_AssertionFailsWhenKeyDoesNotExist_Test )
{
    using Kinesis::QuimeraEngine::Common::Exceptions::QAssertException;

    // [Preparation]
    const string_q INPUT_KEY("key2");
    QDictionary<string_q, int> DICTIONARY(3);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        DICTIONARY.GetValue(INPUT_KEY);
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
/// Checks that the value is set when the key exists in the dictionary.
/// </sumary>
QTEST_CASE( SetValue_ValueIsSetWhenKeyExists_Test )
{
    // [Preparation]
    const string_q INPUT_KEY("key2");
    const int EXPECTED_VALUE = 2;
    QDictionary<string_q, int> DICTIONARY(3);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add(INPUT_KEY, 10);
    DICTIONARY.Add("key3", 3);

    // [Execution]
    DICTIONARY.SetValue(INPUT_KEY, EXPECTED_VALUE);

    // [Verification]
    int nValue = DICTIONARY.GetValue(INPUT_KEY);
    BOOST_CHECK_EQUAL(nValue, EXPECTED_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the key does not exist in the dictionary.
/// </sumary>
QTEST_CASE( SetValue_AssertionFailsWhenKeyDoesNotExist_Test )
{
    using Kinesis::QuimeraEngine::Common::Exceptions::QAssertException;

    // [Preparation]
    const string_q INPUT_KEY("key2");
    QDictionary<string_q, int> DICTIONARY(3);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        DICTIONARY.SetValue(INPUT_KEY, 0);
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
/// Checks that the dictionary is emptied.
/// </sumary>
QTEST_CASE( Clear_TheDictinaryIsEmptied_Test )
{
    // [Preparation]
    QDictionary<string_q, int> DICTIONARY(3);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add("key2", 2);
    DICTIONARY.Add("key3", 3);

    // [Execution]
    DICTIONARY.Clear();

    // [Verification]
    bool bIsEmpty = DICTIONARY.IsEmpty();
    BOOST_CHECK(bIsEmpty);
}

/// <sumary>
/// Checks that nothing is done when the dictionary is already empty.
/// </sumary>
QTEST_CASE( Clear_NothingHappensWhenDictionaryIsAlreadyEmpty_Test )
{
    // [Preparation]
    QDictionary<string_q, int> DICTIONARY(3);

    // [Execution]
    DICTIONARY.Clear();

    // [Verification]
    bool bIsEmpty = DICTIONARY.IsEmpty();
    BOOST_CHECK(bIsEmpty);
}

/// <summary>
/// Checks that the capacity is correctly increased.
/// </summary>
QTEST_CASE ( Reserve_CapacityIsCorrectlyIncreased_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_CAPACITY = 4;
    QDictionary<string_q, int> DICTIONARY(2);

    // [Execution]
    DICTIONARY.Reserve(EXPECTED_CAPACITY);

    // [Verification]
    pointer_uint_q uStoredCapacity = DICTIONARY.GetCapacity();

    BOOST_CHECK_EQUAL(uStoredCapacity, EXPECTED_CAPACITY);
}

/// <summary>
/// Checks that elements are correctly reallocated.
/// </summary>
QTEST_CASE ( Reserve_ElementsAreCorrectlyReallocated_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_CAPACITY = 4;
    const string_q EXPECTED_FIRST_KEY("key1");
    const string_q EXPECTED_SECOND_KEY("key2");
    const int EXPECTED_FIRST_VALUE = 1;
    const int EXPECTED_SECOND_VALUE = 2;
    QDictionary<string_q, int> DICTIONARY(2);
    DICTIONARY.Add(EXPECTED_FIRST_KEY, EXPECTED_FIRST_VALUE);
    DICTIONARY.Add(EXPECTED_SECOND_KEY, EXPECTED_SECOND_VALUE);

    // [Execution]
    DICTIONARY.Reserve(INPUT_CAPACITY); // A reallocation occurs

    // [Verification]
    QDictionary<string_q, int>::QConstDictionaryIterator it = DICTIONARY.GetFirst();
    BOOST_CHECK(it->GetKey() == EXPECTED_FIRST_KEY);
    BOOST_CHECK(it->GetValue() == EXPECTED_FIRST_VALUE);
    ++it;
    BOOST_CHECK(it->GetKey() == EXPECTED_SECOND_KEY);
    BOOST_CHECK(it->GetValue() == EXPECTED_SECOND_VALUE);
}

/// <summary>
/// Checks that elements are not reallocated and capacity does not change when attempting to reserve less memory than current reserved.
/// </summary>
QTEST_CASE ( Reserve_NothingHappensWhenTheAmountToReserveIsNoGreaterThanCurrentCapacity_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_CAPACITY = 1;
    const pointer_uint_q EXPECTED_CAPACITY = 4;
    QDictionary<string_q, int> DICTIONARY(4);

    // [Execution]
    DICTIONARY.Reserve(INPUT_CAPACITY); // A reallocation occurs

    // [Verification]
    pointer_uint_q uCapacity = DICTIONARY.GetCapacity();
    BOOST_CHECK_EQUAL(uCapacity, EXPECTED_CAPACITY);
}

/// <summary>
/// Checks that the element is correctly added when the dictionary is empty.
/// </summary>
QTEST_CASE ( Add_ElementIsCorrectlyAddedWhenDictionaryIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;

    // [Preparation]
    const string_q INPUT_KEY("key1");
    const int INPUT_VALUE = 0;
    const string_q EXPECTED_KEYS[] = {INPUT_KEY};
    const int EXPECTED_VALUES[] = {INPUT_VALUE};
    
    QDictionary<string_q, int> DICTIONARY(3);

    // [Execution]
    DICTIONARY.Add(INPUT_KEY, INPUT_VALUE);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QDictionary<string_q, int>::QConstDictionaryIterator it = QDictionary<string_q, int>::QConstDictionaryIterator(&DICTIONARY, 0);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetKey() == EXPECTED_KEYS[i];
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetValue() == EXPECTED_VALUES[i];
    }

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly added when the dictionary only contains one element.
/// </summary>
QTEST_CASE ( Add_ElementIsCorrectlyAddedWhenDictionaryOnlyContainsOneElement_Test )
{
    // [Preparation]
    const string_q INPUT_KEY("key1");
    const int INPUT_VALUE = 0;
    const string_q EXPECTED_KEYS[] = {INPUT_KEY, "key2"};
    const int EXPECTED_VALUES[] = {INPUT_VALUE, 1};
    
    QDictionary<string_q, int> DICTIONARY(3);
    DICTIONARY.Add("key2", 1);

    // [Execution]
    DICTIONARY.Add(INPUT_KEY, INPUT_VALUE);

    // [Verification]
    bool bResultIsWhatEspected = true;

    QDictionary<string_q, int>::QConstDictionaryIterator it = QDictionary<string_q, int>::QConstDictionaryIterator(&DICTIONARY, 0);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetKey() == EXPECTED_KEYS[i];
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetValue() == EXPECTED_VALUES[i];
    }

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the iterator points to the added element.
/// </summary>
QTEST_CASE ( Add_ReturnedIteratorPointsToAddedElement_Test )
{
    // [Preparation]
    const string_q INPUT_KEY("key1");
    const int INPUT_VALUE = 1;
    
    QDictionary<string_q, int> DICTIONARY(3);
    DICTIONARY.Add("key2", 2);
    DICTIONARY.Add("key3", 3);

    // [Execution]
    QDictionary<string_q, int>::QConstDictionaryIterator itResult = DICTIONARY.Add(INPUT_KEY, INPUT_VALUE);

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
    const string_q INPUT_KEY("key1");
    const int INPUT_VALUE = 1;
    
    QDictionary<string_q, int> DICTIONARY(3);
    DICTIONARY.Add("key2", 2);
    const pointer_uint_q COUNT_BEFORE_ADDING = DICTIONARY.GetCount();

    // [Execution]
    DICTIONARY.Add(INPUT_KEY, INPUT_VALUE);

    // [Verification]
    pointer_uint_q uCountAfterAdding = DICTIONARY.GetCount();
    BOOST_CHECK(uCountAfterAdding > COUNT_BEFORE_ADDING);
}

/// <summary>
/// Checks that the capacity is incremented after exceeding its value.
/// </summary>
QTEST_CASE ( Add_CapacityIsIncrementedWhenNecessary_Test )
{
    // [Preparation]
    const string_q INPUT_KEY("key1");
    const int INPUT_VALUE = 1;
    
    QDictionary<string_q, int> DICTIONARY(1);
    DICTIONARY.Add("key2", 2);
    const pointer_uint_q CAPACITY_BEFORE_ADDING = DICTIONARY.GetCapacity();

    // [Execution]
    DICTIONARY.Add(INPUT_KEY, INPUT_VALUE);

    // [Verification]
    pointer_uint_q uCapacityAfterAdding = DICTIONARY.GetCapacity();
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
    const string_q INPUT_KEY("key1");
    const int INPUT_VALUE = 1;
    
    QDictionary<string_q, int> DICTIONARY(1);
    DICTIONARY.Add(INPUT_KEY, INPUT_VALUE);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        DICTIONARY.Add(INPUT_KEY, 0);
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
/// Checks that the node is obtained.
/// </sumary>
QTEST_CASE( GetFirst_NodeIsObtained_Test )
{
    // [Preparation]
    const string_q EXPECTED_ELEMENT_KEY("key1");
    const int EXPECTED_ELEMENT_VALUE = 1;
    QDictionary<string_q, int> DICTIONARY(5);
    DICTIONARY.Add(EXPECTED_ELEMENT_KEY, EXPECTED_ELEMENT_VALUE);
    DICTIONARY.Add("key2", 2);
    DICTIONARY.Add("key3", 3);

    // [Execution]
    QDictionary<string_q, int>::QConstDictionaryIterator itFirst = DICTIONARY.GetFirst();

    // [Verification]
    BOOST_CHECK(itFirst->GetKey() == EXPECTED_ELEMENT_KEY);
    BOOST_CHECK(itFirst->GetValue() == EXPECTED_ELEMENT_VALUE);
}

/// <sumary>
/// Checks that the obtained iterator points to end position when the dictionary is empty.
/// </sumary>
QTEST_CASE( GetFirst_ReturnedIteratorPointsToEndWhenDictionaryIsEmpty_Test )
{
    // [Preparation]
    QDictionary<string_q, int> DICTIONARY(5);

    // [Execution]
    QDictionary<string_q, int>::QConstDictionaryIterator itFirst = DICTIONARY.GetFirst();

    // [Verification]
    bool bIteratorPointstoEnd = itFirst.IsEnd();
    BOOST_CHECK(bIteratorPointstoEnd);
}

/// <sumary>
/// Checks that the node is obtained.
/// </sumary>
QTEST_CASE( GetLast_NodeIsObtained_Test )
{
    // [Preparation]
    const string_q EXPECTED_ELEMENT_KEY("key3");
    const int EXPECTED_ELEMENT_VALUE = 3;
    QDictionary<string_q, int> DICTIONARY(5);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add("key2", 2);
    DICTIONARY.Add(EXPECTED_ELEMENT_KEY, EXPECTED_ELEMENT_VALUE);

    // [Execution]
    QDictionary<string_q, int>::QConstDictionaryIterator itLast = DICTIONARY.GetLast();

    // [Verification]
    BOOST_CHECK(itLast->GetKey() == EXPECTED_ELEMENT_KEY);
    BOOST_CHECK(itLast->GetValue() == EXPECTED_ELEMENT_VALUE);
}

/// <sumary>
/// Checks that the obtained iterator points to end position when the dictionary is empty.
/// </sumary>
QTEST_CASE( GetLast_ReturnedIteratorPointsToEndWhenDictionaryIsEmpty_Test )
{
    // [Preparation]
    QDictionary<string_q, int> DICTIONARY(5);

    // [Execution]
    QDictionary<string_q, int>::QConstDictionaryIterator itLast = DICTIONARY.GetLast();

    // [Verification]
    bool bIteratorPointstoEnd = itLast.IsEnd();
    BOOST_CHECK(bIteratorPointstoEnd);
}

/// <summary>
/// Checks that the capacity is correctly calculated.
/// </summary>
QTEST_CASE ( GetCapacity_IsCorrectlyCalculated_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_CAPACITY = 3;
    QDictionary<string_q, int> DICTIONARY(EXPECTED_CAPACITY);

    // [Execution]
    pointer_uint_q uCapacity = DICTIONARY.GetCapacity();

    // [Verification]
    BOOST_CHECK_EQUAL(uCapacity, EXPECTED_CAPACITY);
}

// End - Test Suite: QDictionary
QTEST_SUITE_END()
