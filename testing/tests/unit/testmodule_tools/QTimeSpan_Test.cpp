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

#include "QTimeSpan.h"

using Kinesis::QuimeraEngine::Common::DataTypes::u64_q;
using Kinesis::QuimeraEngine::Common::DataTypes::u32_q;
using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

QTEST_SUITE_BEGIN( QTimeSpan_TestSuite )

/// <summary>
/// Checks constructor with no parameters.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const u64_q EXPECTED_VALUE_FOR_TIMESPAN = 0;

	// [Execution]
    QTimeSpan timeSpan;
    
    // [Verification]
    // [TODO] [raul] To uncomment this line the getter must be implemented in class QTimeSpan
    // BOOST_CHECK(timeSpan.getTimeSpan() == EXPECTED_VALUE_FOR_TIMESPAN);
    BOOST_CHECK(true);
}

/// <summary>
/// Checks constructor with one parameter. Checks if the class member is set correctly
/// </summary>
QTEST_CASE ( Constructor2_ParameterIsProperlyAssigned_Test )
{
    // [Preparation]
    const u64_q EXPECTED_VALUE_FOR_TIMESPAN = 15;

	// [Execution]
    QTimeSpan timeSpan(EXPECTED_VALUE_FOR_TIMESPAN);
    
    // [Verification]
    // [TODO] [raul] To uncomment this line the getter must be implemented in class QTimeSpan
    // BOOST_CHECK(timeSpan.getTimeSpan() == EXPECTED_VALUE_FOR_TIMESPAN);
    BOOST_CHECK(true);
}

/// <summary>
/// Checks constructor with several values as parameters.
/// These values represent days, hours, minutes, seconds, mseconds, microseconds and hundreds of nanosecs
/// </summary>
QTEST_CASE ( Constructor3_InstanceIsCorrectlyConstructedWhenUsingCommonTimeValues_Test )
{
    // [Preparation]
    const u64_q VALUE_FOR_DAYS = 1;
    const u64_q VALUE_FOR_HOURS = 1;
    const u64_q VALUE_FOR_MINUTES = 1;
    const u64_q VALUE_FOR_SECONDS = 1;
    const u64_q VALUE_FOR_MSECONDS = 1;
    const u64_q VALUE_FOR_MICROSECONDS = 1;
    const u64_q VALUE_FOR_HUNDREDSNANOSECS = 1;
    //days * 24 = hours
    //hours * 60 = minutes
    //minutes * 60 = seconds
    //seconds * 1000 = mseconds
    //microseconds * 1000 = microsecs
    //microsecs * 10 = hundreds of nanosecs
    const u64_q EXPECTED_VALUE_FOR_TIMESPAN = 900610010011;

	// [Execution]
    QTimeSpan timeSpan(VALUE_FOR_DAYS, VALUE_FOR_HOURS, VALUE_FOR_MINUTES, VALUE_FOR_SECONDS, 
                       VALUE_FOR_MSECONDS, VALUE_FOR_MICROSECONDS, VALUE_FOR_HUNDREDSNANOSECS);


    // [Verification]
    // [TODO] [raul] To uncomment this line the getter must be implemented in class QTimeSpan
    // BOOST_CHECK(timeSpan.getTimeSpan() == EXPECTED_VALUE_FOR_TIMESPAN);
    BOOST_CHECK(true);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED
/// <summary>
/// Checks if the overflow when passing parameter bigger than the maximum allowed provokes the return of max value.
/// </summary>
QTEST_CASE ( Constructor3_MaximumValueIsAssignedWhenParametersProduceOverflow_Test )
{
    // [Preparation]
    const u64_q VALUE_FOR_DAYS = 100000000000;
    const u64_q VALUE_FOR_HOURS = 1;
    const u64_q VALUE_FOR_MINUTES = 1;
    const u64_q VALUE_FOR_SECONDS = 1;
    const u64_q VALUE_FOR_MSECONDS = 1;
    const u64_q VALUE_FOR_MICROSECONDS = 1;
    const u64_q VALUE_FOR_HUNDREDSNANOSECS = 1;
    const u64_q EXPECTED_VALUE_FOR_TIMESPAN = -1;

	// [Execution]
    QTimeSpan timeSpan(VALUE_FOR_DAYS, VALUE_FOR_HOURS, VALUE_FOR_MINUTES, VALUE_FOR_SECONDS, 
                       VALUE_FOR_MSECONDS, VALUE_FOR_MICROSECONDS, VALUE_FOR_HUNDREDSNANOSECS);

    // [Verification]
    // [TODO] [raul] To uncomment this line the getter must be implemented in class QTimeSpan
    // BOOST_CHECK(timeSpan.getTimeSpan() == EXPECTED_VALUE_FOR_TIMESPAN);
    BOOST_CHECK(true);
   
}

/// <summary>
/// Checks if the overflow when computing the sum of all parameters provokes the return of max value.
/// </summary>
/// <remarks>
/// The values used in the test are computed as follows: e.g std::numeric_limits<u64_q>::max() / HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND - 1: (max value allowed divided by amount of hundreds of nanosecond of every parameter ) minus one.
/// </remarks>
QTEST_CASE ( Constructor3_MaximumValueIsAssignedWhenAdditionOfParametersProduceOverflow_Test )
{
    // [Preparation]
    const u64_q VALUE_FOR_DAYS = 21350397;
    const u64_q VALUE_FOR_HOURS = 512409556;
    const u64_q VALUE_FOR_MINUTES = 30744573455;
    const u64_q VALUE_FOR_SECONDS = 1844674407369;
    const u64_q VALUE_FOR_MSECONDS = 1844674407370954;
    const u64_q VALUE_FOR_MICROSECONDS = 1844674407370955160;
    const u64_q VALUE_FOR_HUNDREDSNANOSECS = 1000000000000000000;
    const u64_q EXPECTED_VALUE_FOR_TIMESPAN = -1;

	// [Execution]
    QTimeSpan timeSpan(VALUE_FOR_DAYS, VALUE_FOR_HOURS, VALUE_FOR_MINUTES, VALUE_FOR_SECONDS, 
                       VALUE_FOR_MSECONDS, VALUE_FOR_MICROSECONDS, VALUE_FOR_HUNDREDSNANOSECS);

    // [Verification]
    // [TODO] [raul] To uncomment this line the getter must be implemented in class QTimeSpan
    // BOOST_CHECK(timeSpan.getTimeSpan() == EXPECTED_VALUE_FOR_TIMESPAN);
    BOOST_CHECK(true);
   
}

#endif

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if the assertion inside the constructor fails whith overflow when passing parameter bigger the the maximum allowed.
/// </summary>
QTEST_CASE ( Constructor3_AssertionFailsWhenOverflowWithParameterOccurs_Test )
{
    // [Preparation]
    const u64_q VALUE_FOR_DAYS = 100000000000;
    const u64_q VALUE_FOR_HOURS = 1;
    const u64_q VALUE_FOR_MINUTES = 1;
    const u64_q VALUE_FOR_SECONDS = 1;
    const u64_q VALUE_FOR_MSECONDS = 1;
    const u64_q VALUE_FOR_MICROSECONDS = 1;
    const u64_q VALUE_FOR_HUNDREDSNANOSECS = 1;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QTimeSpan timeSpan(VALUE_FOR_DAYS, VALUE_FOR_HOURS, VALUE_FOR_MINUTES, VALUE_FOR_SECONDS, 
                       VALUE_FOR_MSECONDS, VALUE_FOR_MICROSECONDS, VALUE_FOR_HUNDREDSNANOSECS);
    }
    catch(...) // [TODO] [raul]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks if the assertion inside the constructor fails whith overflow when computing the sum of all parameters.
/// </summary>
/// <remarks>
/// The values used in the test are computed as follows: e.g std::numeric_limits<u64_q>::max() / HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND - 1: (max value allowed divided by amount of hundreds of nanosecond of every parameter ) minus one.
/// </remarks>
QTEST_CASE ( Constructor3_AssertionFailsWhenOverflowWithAdditionOccurs_Test )
{
    // [Preparation]
    const u64_q VALUE_FOR_DAYS = 21350397;
    const u64_q VALUE_FOR_HOURS = 512409556;
    const u64_q VALUE_FOR_MINUTES = 30744573455;
    const u64_q VALUE_FOR_SECONDS = 1844674407369;
    const u64_q VALUE_FOR_MSECONDS = 1844674407370954;
    const u64_q VALUE_FOR_MICROSECONDS = 1844674407370955160;
    const u64_q VALUE_FOR_HUNDREDSNANOSECS = 1000000000000000000;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QTimeSpan timeSpan(VALUE_FOR_DAYS, VALUE_FOR_HOURS, VALUE_FOR_MINUTES, VALUE_FOR_SECONDS, 
                       VALUE_FOR_MSECONDS, VALUE_FOR_MICROSECONDS, VALUE_FOR_HUNDREDSNANOSECS);
    }
    catch(...) // [TODO] [raul]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if copy constructor works properly. 
/// </summary>
QTEST_CASE ( Constructor4_QTimeSpanIsCopiedCorrectly_Test )
{
    // [Preparation]
    const u64_q EXPECTED_VALUE_FOR_TIMESPAN = 150;
    QTimeSpan timeSpanOriginal(EXPECTED_VALUE_FOR_TIMESPAN);

	// [Execution]
    QTimeSpan timeSpanResult(timeSpanOriginal);
    
    // [Verification]
    // [TODO] [raul] To uncomment this line the getter must be implemented in class QTimeSpan
    // BOOST_CHECK(timeSpanResult.getTimeSpan() == EXPECTED_VALUE_FOR_TIMESPAN);
    BOOST_CHECK(true);
}

/// <summary>
/// Checks assignment operator. 
/// </summary>
QTEST_CASE ( AsignmentOperator_AssignmentOperationIsDoneCorrectly_Test )
{
    // [Preparation]
    const u64_q EXPECTED_VALUE_FOR_TIMESPAN = 150;
    QTimeSpan timeSpanOriginal(EXPECTED_VALUE_FOR_TIMESPAN);

	// [Execution]
    QTimeSpan timeSpanAssigned = timeSpanOriginal;
    
    // [Verification]
    // [TODO] [raul] To uncomment this line the getter must be implemented in class QTimeSpan
    // BOOST_CHECK(timeSpanOriginal.getTimeSpan() == timeSpanAssigned.getTimeSpan());
    BOOST_CHECK(true);
}



// End - Test Suite: QTimeSpan
QTEST_SUITE_END()