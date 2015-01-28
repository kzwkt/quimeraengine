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

using Kinesis::QuimeraEngine::Tools::Containers::QHashtable;
using Kinesis::QuimeraEngine::Common::Exceptions::QAssertException;


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
    QHashtable<string_q, int> hashtable(NUMBER_OF_BUCKETS, NUMBER_OF_SLOTS);

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

// [TODO] Thund: Implement when Add exists
/*
/// <summary>
/// Checks that .
/// </summary>
QTEST_CASE ( Constructor2_EveryKeyValuePairIsCopied_Test )
{
    // [Preparation]

    // [Execution]

    // [Verification]
}

/// <summary>
/// Checks that .
/// </summary>
QTEST_CASE ( Constructor2_CopyConstructorOfEveryKeyAndValueIsCalled_Test )
{
    // [Preparation]

    // [Execution]

    // [Verification]
}

/// <summary>
/// Checks that .
/// </summary>
QTEST_CASE ( Constructor2_ItIsCorrectlyCopiedWhenItIsEmpty_Test )
{
    // [Preparation]

    // [Execution]

    // [Verification]
}

/// <summary>
/// Checks that the destructor of every key and value is called.
/// </summary>
QTEST_CASE ( Destructor_TheDestructorOfEveryKeyAndValueIsCalled_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::Test::CallCounter;
    
    // [Preparation]
    const unsigned int EXPECTED_CALLS = 3;

    {
        QHashtable<CallCounter, CallCounter> HASTABLE(3);
        HASTABLE.Add(CallCounter(), CallCounter());
        HASTABLE.Add(CallCounter(), CallCounter());
        HASTABLE.Add(CallCounter(), CallCounter());
        CallCounter::ResetCounters();

    // [Execution]
    // Destructor is called when the execution flow leaves this block
    }

    // [Verification]
    unsigned int uDestructorCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorCalls, EXPECTED_CALLS);
}
*/
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
/* [TODO] Thund: Uncomment when Add exists
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
*/

// End - Test Suite: QHashtable
QTEST_SUITE_END()
