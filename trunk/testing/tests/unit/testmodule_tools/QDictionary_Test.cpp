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


// End - Test Suite: QDictionary
QTEST_SUITE_END()
