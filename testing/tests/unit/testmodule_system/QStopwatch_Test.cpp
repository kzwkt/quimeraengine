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

#include "QStopwatch.h"

#include "QStopwatchWhiteBox.h"
#include "QAssertException.h"

using Kinesis::QuimeraEngine::Common::Exceptions::QAssertException;
using Kinesis::QuimeraEngine::System::Timing::QStopwatch;



QTEST_SUITE_BEGIN( QStopwatch_TestSuite )

/// <summary>
/// Checks that attributes are correctly initialized.
/// </summary>
QTEST_CASE ( Constructor_ItIsCorrectlyInitialized_Test )
{
    using Kinesis::QuimeraEngine::System::Timing::Test::QStopwatchWhiteBox;

    // [Preparation]
    const u64_q EXPECTED_VALUE = 0;

    // [Execution]
    QStopwatchWhiteBox stopWatch;
    
    // [Verification]
    BOOST_CHECK_EQUAL(stopWatch.GetReferenceInstantForTest(), EXPECTED_VALUE);
}

/// <summary>
/// Checks that the returned value is greater than zero when the stopwatch is set.
/// </summary>
QTEST_CASE ( GetElapsedTimeAsFloat_ReturnedValueIsGreaterThanZeroWhenStopWatchIsSet_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::float_q;

    // [Preparation]
    const float_q ZERO = 0.0;
    QStopwatch stopWatch;
    stopWatch.Set();
    
    // Delay
    for(int i = 0; i < 10000; ++i)
        i = i;

    // [Execution]
    float_q fValue = stopWatch.GetElapsedTimeAsFloat();
    
    // [Verification]
    BOOST_CHECK(fValue > ZERO);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the stopwatch as not been set.
/// </summary>
QTEST_CASE ( GetElapsedTimeAsFloat_AssertionFailsWhenStopWatchHasNotBeenSet_Test )
{
    // [Preparation]
    QStopwatch stopWatch;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        stopWatch.GetElapsedTimeAsFloat();
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
/// Checks that the returned value is greater than zero when the stopwatch is set.
/// </summary>
QTEST_CASE ( GetElapsedTimeAsInteger_ReturnedValueIsGreaterThanZeroWhenStopWatchIsSet_Test )
{
    // [Preparation]
    const u64_q ZERO = 0;
    QStopwatch stopWatch;
    stopWatch.Set();
    
    // Delay
    for(int i = 0; i < 10000; ++i)
        i = i;

    // [Execution]
    u64_q uValue = stopWatch.GetElapsedTimeAsInteger();
    
    // [Verification]
    BOOST_CHECK(uValue > ZERO);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the stopwatch as not been set.
/// </summary>
QTEST_CASE ( GetElapsedTimeAsInteger_AssertionFailsWhenStopWatchHasNotBeenSet_Test )
{
    // [Preparation]
    QStopwatch stopWatch;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        stopWatch.GetElapsedTimeAsInteger();
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
/// Checks that the returned value is greater than zero when the stopwatch is set.
/// </summary>
QTEST_CASE ( GetElapsedTimeAsTimeSpan_ReturnedValueIsGreaterThanZeroWhenStopWatchIsSet_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QTimeSpan ZERO = QTimeSpan(0);
    QStopwatch stopWatch;
    stopWatch.Set();

    // Delay
    for(int i = 0; i < 10000; ++i)
        i = i;

    // [Execution]
    QTimeSpan value = stopWatch.GetElapsedTimeAsTimeSpan();
    
    // [Verification]
    BOOST_CHECK(value > ZERO);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the stopwatch as not been set.
/// </summary>
QTEST_CASE ( GetElapsedTimeAsTimeSpan_AssertionFailsWhenStopWatchHasNotBeenSet_Test )
{
    // [Preparation]
    QStopwatch stopWatch;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        stopWatch.GetElapsedTimeAsTimeSpan();
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

// End - Test Suite: QStopwatch
QTEST_SUITE_END()
