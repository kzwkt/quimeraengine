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

#include "QStopwatchEnclosed.h"

#include "SQFloat.h"
#include "QAssertException.h"

using Kinesis::QuimeraEngine::System::Timing::QStopwatchEnclosed;
using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;
using Kinesis::QuimeraEngine::System::Timing::EQStopwatchEnclosedBehavior;
using Kinesis::QuimeraEngine::Common::DataTypes::float_q;
using Kinesis::QuimeraEngine::Common::DataTypes::SQFloat;


QTEST_SUITE_BEGIN( QStopwatchEnclosed_TestSuite )

/// <summary>
/// Method used in some tests to wait for a given amount of time.
/// </summary>
/// <param name="uMilliseconds">Number of milliseconds to stay waiting.</param>
void Wait_TestMethod(const unsigned int uMilliseconds)
{
    QStopwatchEnclosed stopwatch;
    stopwatch.Set();

    while(stopwatch.GetElapsedTimeAsInteger() / 10000ULL < uMilliseconds)
        ;
}

/// <summary>
/// Checks that the default values set by the default constructor have not changed since the last time the test was executed.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const QTimeSpan EXPECTED_TIMELAPSE(0);
    const EQStopwatchEnclosedBehavior EXPECTED_BEHAVIOR(EQStopwatchEnclosedBehavior::E_Clamped);

    // [Execution]
    QStopwatchEnclosed stopwatch;
    
    // [Verification]
    EQStopwatchEnclosedBehavior eBehavior = stopwatch.GetBehavior();
    QTimeSpan timeLapse = stopwatch.GetTimeLapseLength();
    BOOST_CHECK(eBehavior == EXPECTED_BEHAVIOR);
    BOOST_CHECK(timeLapse == EXPECTED_TIMELAPSE);
}

/// <summary>
/// Checks that the input values are stored correctly.
/// </summary>
QTEST_CASE ( Constructor2_InputValuesAreCorrectlyStored_Test )
{
    // [Preparation]
    const QTimeSpan EXPECTED_TIMELAPSE(0, 0, 0, 0, 123, 0, 0);
    const EQStopwatchEnclosedBehavior EXPECTED_BEHAVIOR(EQStopwatchEnclosedBehavior::E_Cyclic);

    // [Execution]
    QStopwatchEnclosed stopwatch(EXPECTED_TIMELAPSE, EXPECTED_BEHAVIOR);
    
    // [Verification]
    EQStopwatchEnclosedBehavior eBehavior = stopwatch.GetBehavior();
    QTimeSpan timeLapse = stopwatch.GetTimeLapseLength();
    BOOST_CHECK(eBehavior == EXPECTED_BEHAVIOR);
    BOOST_CHECK(timeLapse == EXPECTED_TIMELAPSE);
}

/// <summary>
/// Checks that it returns the expected value when the time passed is lower than the time lapse, using Clamp behavior.
/// </summary>
QTEST_CASE ( GetProgression_ReturnsExpectedValueWhenTimePassedIsLowerThanTimeLapseAndUsingClampBehavior_Test )
{
    // [Preparation]
    const float_q EXPECTED_VALUE = SQFloat::_1;
    const QTimeSpan TIMELAPSE(0, 0, 0, 0, 200, 0, 0);
    const EQStopwatchEnclosedBehavior BEHAVIOR(EQStopwatchEnclosedBehavior::E_Clamped);
    QStopwatchEnclosed stopwatch(TIMELAPSE, BEHAVIOR);
    stopwatch.Set();
    Wait_TestMethod(100);

    // [Execution]
    float_q fResult = stopwatch.GetProgression();
    
    // [Verification]
    BOOST_CHECK(fResult > SQFloat::_0);
    BOOST_CHECK(fResult < EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when the time passed is greater than the time lapse, using Clamp behavior.
/// </summary>
QTEST_CASE ( GetProgression_ReturnsExpectedValueWhenTimePassedIsGreaterThanTimeLapseAndUsingClampBehavior_Test )
{
    // [Preparation]
    const float_q MAXIMUM_VALUE = SQFloat::_1;
    const QTimeSpan TIMELAPSE(0, 0, 0, 0, 50, 0, 0);
    const EQStopwatchEnclosedBehavior BEHAVIOR(EQStopwatchEnclosedBehavior::E_Clamped);
    QStopwatchEnclosed stopwatch(TIMELAPSE, BEHAVIOR);
    stopwatch.Set();
    Wait_TestMethod(100);

    // [Execution]
    float_q fResult = stopwatch.GetProgression();
    
    // [Verification]
    BOOST_CHECK(fResult == MAXIMUM_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when the time passed is lower than the time lapse, using Proportional behavior.
/// </summary>
QTEST_CASE ( GetProgression_ReturnsExpectedValueWhenTimePassedIsLowerThanTimeLapseAndUsingProportionalBehavior_Test )
{
    // [Preparation]
    const float_q EXPECTED_VALUE = SQFloat::_1;
    const QTimeSpan TIMELAPSE(0, 0, 0, 0, 200, 0, 0);
    const EQStopwatchEnclosedBehavior BEHAVIOR(EQStopwatchEnclosedBehavior::E_Proportional);
    QStopwatchEnclosed stopwatch(TIMELAPSE, BEHAVIOR);
    stopwatch.Set();
    Wait_TestMethod(100);

    // [Execution]
    float_q fResult = stopwatch.GetProgression();
    
    // [Verification]
    BOOST_CHECK(fResult > SQFloat::_0);
    BOOST_CHECK(fResult < EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when the time passed is greater than the time lapse, using Proportional behavior.
/// </summary>
QTEST_CASE ( GetProgression_ReturnsExpectedValueWhenTimePassedIsGreaterThanTimeLapseAndUsingProportionalBehavior_Test )
{
    // [Preparation]
    const float_q EXPECTED_VALUE = SQFloat::_2;
    const QTimeSpan TIMELAPSE(0, 0, 0, 0, 50, 0, 0);
    const EQStopwatchEnclosedBehavior BEHAVIOR(EQStopwatchEnclosedBehavior::E_Proportional);
    QStopwatchEnclosed stopwatch(TIMELAPSE, BEHAVIOR);
    stopwatch.Set();
    Wait_TestMethod(100);

    // [Execution]
    float_q fResult = stopwatch.GetProgression();
    
    // [Verification]
    BOOST_CHECK(fResult >= EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when the time passed is lower than the time lapse, using Cyclic behavior.
/// </summary>
QTEST_CASE ( GetProgression_ReturnsExpectedValueWhenTimePassedIsLowerThanTimeLapseAndUsingCyclicBehavior_Test )
{
    // [Preparation]
    const float_q EXPECTED_VALUE = SQFloat::_1;
    const QTimeSpan TIMELAPSE(0, 0, 0, 0, 200, 0, 0);
    const EQStopwatchEnclosedBehavior BEHAVIOR(EQStopwatchEnclosedBehavior::E_Cyclic);
    QStopwatchEnclosed stopwatch(TIMELAPSE, BEHAVIOR);
    stopwatch.Set();
    Wait_TestMethod(100);

    // [Execution]
    float_q fResult = stopwatch.GetProgression();
    
    // [Verification]
    BOOST_CHECK(fResult > SQFloat::_0);
    BOOST_CHECK(fResult < EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when the time passed is greater than the time lapse, using Cyclic behavior.
/// </summary>
QTEST_CASE ( GetProgression_ReturnsExpectedValueWhenTimePassedIsGreaterThanTimeLapseAndUsingCyclicBehavior_Test )
{
    // [Preparation]
    const float_q MAXIMUM_VALUE = SQFloat::_1;
    const QTimeSpan TIMELAPSE(0, 0, 0, 0, 50, 0, 0);
    const EQStopwatchEnclosedBehavior BEHAVIOR(EQStopwatchEnclosedBehavior::E_Cyclic);
    QStopwatchEnclosed stopwatch(TIMELAPSE, BEHAVIOR);
    stopwatch.Set();
    Wait_TestMethod(100);

    // [Execution]
    float_q fResult = stopwatch.GetProgression();
    
    // [Verification]
    BOOST_CHECK(fResult < MAXIMUM_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when the time passed is lower than the time lapse, using Clamp behavior.
/// </summary>
QTEST_CASE ( GetPercentage_ReturnsExpectedValueWhenTimePassedIsLowerThanTimeLapseAndUsingClampBehavior_Test )
{
    // [Preparation]
    const float_q EXPECTED_VALUE = 100.0;
    const QTimeSpan TIMELAPSE(0, 0, 0, 0, 200, 0, 0);
    const EQStopwatchEnclosedBehavior BEHAVIOR(EQStopwatchEnclosedBehavior::E_Clamped);
    QStopwatchEnclosed stopwatch(TIMELAPSE, BEHAVIOR);
    stopwatch.Set();
    Wait_TestMethod(100);

    // [Execution]
    float_q fResult = stopwatch.GetPercentage();
    
    // [Verification]
    BOOST_CHECK(fResult > SQFloat::_0);
    BOOST_CHECK(fResult < EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when the time passed is greater than the time lapse, using Clamp behavior.
/// </summary>
QTEST_CASE ( GetPercentage_ReturnsExpectedValueWhenTimePassedIsGreaterThanTimeLapseAndUsingClampBehavior_Test )
{
    // [Preparation]
    const float_q MAXIMUM_VALUE = 100.0;
    const QTimeSpan TIMELAPSE(0, 0, 0, 0, 50, 0, 0);
    const EQStopwatchEnclosedBehavior BEHAVIOR(EQStopwatchEnclosedBehavior::E_Clamped);
    QStopwatchEnclosed stopwatch(TIMELAPSE, BEHAVIOR);
    stopwatch.Set();
    Wait_TestMethod(100);

    // [Execution]
    float_q fResult = stopwatch.GetPercentage();
    
    // [Verification]
    BOOST_CHECK(fResult == MAXIMUM_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when the time passed is lower than the time lapse, using Proportional behavior.
/// </summary>
QTEST_CASE ( GetPercentage_ReturnsExpectedValueWhenTimePassedIsLowerThanTimeLapseAndUsingProportionalBehavior_Test )
{
    // [Preparation]
    const float_q EXPECTED_VALUE = 100.0;
    const QTimeSpan TIMELAPSE(0, 0, 0, 0, 200, 0, 0);
    const EQStopwatchEnclosedBehavior BEHAVIOR(EQStopwatchEnclosedBehavior::E_Proportional);
    QStopwatchEnclosed stopwatch(TIMELAPSE, BEHAVIOR);
    stopwatch.Set();
    Wait_TestMethod(100);

    // [Execution]
    float_q fResult = stopwatch.GetPercentage();
    
    // [Verification]
    BOOST_CHECK(fResult > SQFloat::_0);
    BOOST_CHECK(fResult < EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when the time passed is greater than the time lapse, using Proportional behavior.
/// </summary>
QTEST_CASE ( GetPercentage_ReturnsExpectedValueWhenTimePassedIsGreaterThanTimeLapseAndUsingProportionalBehavior_Test )
{
    // [Preparation]
    const float_q EXPECTED_VALUE = 200.0;
    const QTimeSpan TIMELAPSE(0, 0, 0, 0, 50, 0, 0);
    const EQStopwatchEnclosedBehavior BEHAVIOR(EQStopwatchEnclosedBehavior::E_Proportional);
    QStopwatchEnclosed stopwatch(TIMELAPSE, BEHAVIOR);
    stopwatch.Set();
    Wait_TestMethod(100);

    // [Execution]
    float_q fResult = stopwatch.GetPercentage();
    
    // [Verification]
    BOOST_CHECK(fResult >= EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when the time passed is lower than the time lapse, using Cyclic behavior.
/// </summary>
QTEST_CASE ( GetPercentage_ReturnsExpectedValueWhenTimePassedIsLowerThanTimeLapseAndUsingCyclicBehavior_Test )
{
    // [Preparation]
    const float_q EXPECTED_VALUE = 100.0;
    const QTimeSpan TIMELAPSE(0, 0, 0, 0, 200, 0, 0);
    const EQStopwatchEnclosedBehavior BEHAVIOR(EQStopwatchEnclosedBehavior::E_Cyclic);
    QStopwatchEnclosed stopwatch(TIMELAPSE, BEHAVIOR);
    stopwatch.Set();
    Wait_TestMethod(100);

    // [Execution]
    float_q fResult = stopwatch.GetPercentage();
    
    // [Verification]
    BOOST_CHECK(fResult > SQFloat::_0);
    BOOST_CHECK(fResult < EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when the time passed is greater than the time lapse, using Cyclic behavior.
/// </summary>
QTEST_CASE ( GetPercentage_ReturnsExpectedValueWhenTimePassedIsGreaterThanTimeLapseAndUsingCyclicBehavior_Test )
{
    // [Preparation]
    const float_q MAXIMUM_VALUE = 100.0;
    const QTimeSpan TIMELAPSE(0, 0, 0, 0, 50, 0, 0);
    const EQStopwatchEnclosedBehavior BEHAVIOR(EQStopwatchEnclosedBehavior::E_Cyclic);
    QStopwatchEnclosed stopwatch(TIMELAPSE, BEHAVIOR);
    stopwatch.Set();
    Wait_TestMethod(100);

    // [Execution]
    float_q fResult = stopwatch.GetPercentage();
    
    // [Verification]
    BOOST_CHECK(fResult < MAXIMUM_VALUE);
}

/// <summary>
/// Checks that the time lapse is correctly stored.
/// </summary>
QTEST_CASE ( SetTimeLapseLength_TimeLapseIsCorrectlyStored_Test )
{
    // [Preparation]
    const QTimeSpan TIMELAPSE(0, 0, 0, 0, 50, 0, 0);
    const EQStopwatchEnclosedBehavior BEHAVIOR(EQStopwatchEnclosedBehavior::E_Cyclic);
    QStopwatchEnclosed stopwatch;
    
    // [Execution]
    stopwatch.SetTimeLapseLength(TIMELAPSE);
    
    // [Verification]
    QTimeSpan timeLapse = stopwatch.GetTimeLapseLength();
    BOOST_CHECK(timeLapse == TIMELAPSE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input time lapse equals zero.
/// </summary>
QTEST_CASE ( SetTimeLapseLength_AssertionFailsWhenInputIsZero_Test )
{
    // [Preparation]
    const QTimeSpan TIMELAPSE(0);
    QStopwatchEnclosed stopwatch;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        QTimeSpan timeLapse = stopwatch.SetTimeLapseLength(TIMELAPSE);
    }
    catch(const Kinesis::QuimeraEngine::Common::Exceptions::QAssertException&)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

// End - Test Suite: QStopwatchEnclosed
QTEST_SUITE_END()
