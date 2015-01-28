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

#include "DataTypesDefinitions.h"
#include "SQIntegerHashProvider.h"
#include "QAssertException.h"

using Kinesis::QuimeraEngine::Tools::Containers::SQIntegerHashProvider;
using Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q;
using Kinesis::QuimeraEngine::Common::Exceptions::QAssertException;


QTEST_SUITE_BEGIN( SQIntegerHashProvider_TestSuite )

/// <summary>
/// Checks that it returns zero when the input value is zero.
/// </summary>
QTEST_CASE ( GenerateHashKey_ItReturnsZeroWhenInputIsZero_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_VALUE = 0;
    const pointer_uint_q NUMBER_OF_BUCKETS = 4;
    const pointer_uint_q EXPECTED_VALUE = 0;

    // [Execution]
    pointer_uint_q uHashKey = SQIntegerHashProvider::GenerateHashKey(INPUT_VALUE, NUMBER_OF_BUCKETS);
    
    // [Verification]
    BOOST_CHECK_EQUAL(uHashKey, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected result when using common input values.
/// </summary>
QTEST_CASE ( GenerateHashKey_ItReturnsExpectedValueWhenUsingCommonInputValues_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_VALUE = 10;
    const pointer_uint_q NUMBER_OF_BUCKETS = 4;
    const pointer_uint_q EXPECTED_VALUE = 2;

    // [Execution]
    pointer_uint_q uHashKey = SQIntegerHashProvider::GenerateHashKey(INPUT_VALUE, NUMBER_OF_BUCKETS);
    
    // [Verification]
    BOOST_CHECK_EQUAL(uHashKey, EXPECTED_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the number of buckets is zero.
/// </summary>
QTEST_CASE ( GenerateHashKey_AssertionFailsWhenNumberOfBucketsIsZero_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_VALUE = 0;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQIntegerHashProvider::GenerateHashKey(INPUT_VALUE, 0);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

// End - Test Suite: SQIntegerHashProvider
QTEST_SUITE_END()
