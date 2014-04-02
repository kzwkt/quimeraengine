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

#include "QTimeZone.h"

#include <sstream>
#include "QTimeSpan.h"
#include "SQTimeZoneFactory.h"

using Kinesis::QuimeraEngine::Tools::Time::QTimeZone;
using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

QTEST_SUITE_BEGIN( QTimeZone_TestSuite )

/// <summary>
/// Checks that the instance is correctly constructed when using common input values.
/// </summary>
QTEST_CASE ( Constructor_InstanceIsCorrectlyConstructedWhenUsingCommonInputs_Test )
{
    // [Preparation]
    const string_q COMMON_TIMEZONE_ID = QE_L("Europe/Madrid");
    const string_q COMMON_TIMEZONE_NAME = QE_L("CET");
    const QTimeSpan COMMON_TIMEZONE_OFFSET = QTimeSpan(123456789);
    const bool IS_NEGATIVE = false;
    const bool HAS_DST = true;

    // Creates the DST from Boost data
    boost::local_time::tz_database TIMEZONE_DATABASE;
    std::istringstream streamDbSource;
    streamDbSource.str("\"Europe/Madrid\",\"CET\",\"CET\",\"CEST\",\"CEST\",\"+01:00:00\",\"+01:00:00\",\"-1;0;3\",\"+02:00:00\",\"-1;0;10\",\"+03:00:00\"");
    TIMEZONE_DATABASE.load_from_stream(streamDbSource);

    boost::local_time::time_zone_ptr timeZoneFromDB = TIMEZONE_DATABASE.time_zone_from_region("Europe/Madrid");
    const QTimeZone::QDstInformation DST_INFO(timeZoneFromDB);

	// [Execution]
    QTimeZone timeZone(COMMON_TIMEZONE_ID, COMMON_TIMEZONE_NAME, COMMON_TIMEZONE_OFFSET, IS_NEGATIVE, DST_INFO, HAS_DST);

    // [Verification]
    BOOST_CHECK(timeZone.GetId() == COMMON_TIMEZONE_ID);
    BOOST_CHECK(timeZone.GetName() == COMMON_TIMEZONE_NAME);
    BOOST_CHECK(timeZone.GetTimeZoneOffset() == COMMON_TIMEZONE_OFFSET);
    BOOST_CHECK_EQUAL(timeZone.IsTimeZoneOffsetNegative(), IS_NEGATIVE);
    BOOST_CHECK_EQUAL(timeZone.HasDstOffset(), HAS_DST);
    BOOST_CHECK(timeZone.GetDstInfo().IsOffsetNegative() == DST_INFO.IsOffsetNegative());
    BOOST_CHECK(timeZone.GetDstInfo().GetOffset() == DST_INFO.GetOffset());
}

/// <summary>
/// Checks that it returns the expected result when the DST offset is active.
/// </summary>
QTEST_CASE ( CalculateOffset_ReturnsExpectedOffsetWhenDstIsActive_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;
    using Kinesis::QuimeraEngine::Tools::Time::QDateTime;

    // [Preparation]
    const string_q COMMON_TIMEZONE_ID = QE_L("Europe/Madrid");
    const QTimeZone* TIME_ZONE = SQTimeZoneFactory::GetTimeZoneById(COMMON_TIMEZONE_ID);
    const QDateTime DST_START_TIME = TIME_ZONE->GetDstInfo().GetStartInYear(2020);
    const QTimeSpan EXPECTED_OFFSET = QTimeSpan(72000000000); // +2 hours
    const bool EXPECTED_OFFSET_SIGN = false;

	// [Execution]
    QTimeSpan offset(0);
    bool bOffsetIsNegative = true;
    TIME_ZONE->CalculateOffset(DST_START_TIME, offset, bOffsetIsNegative);

    // [Verification]
    BOOST_CHECK(offset == EXPECTED_OFFSET);
    BOOST_CHECK_EQUAL(bOffsetIsNegative, EXPECTED_OFFSET_SIGN);
}

/// <summary>
/// Checks that it returns the expected result when the DST offset is NOT active.
/// </summary>
QTEST_CASE ( CalculateOffset_ReturnsExpectedOffsetWhenDstIsNotActive_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;
    using Kinesis::QuimeraEngine::Tools::Time::QDateTime;

    // [Preparation]
    const string_q COMMON_TIMEZONE_ID = QE_L("Europe/Madrid");
    const QTimeZone* TIME_ZONE = SQTimeZoneFactory::GetTimeZoneById(COMMON_TIMEZONE_ID);
    const QDateTime BEFORE_DST_START_TIME = TIME_ZONE->GetDstInfo().GetStartInYear(2020) - QTimeSpan(1);
    const QTimeSpan EXPECTED_OFFSET = QTimeSpan(36000000000); // +1 hour
    const bool EXPECTED_OFFSET_SIGN = false;

	// [Execution]
    QTimeSpan offset(0);
    bool bOffsetIsNegative = true;
    TIME_ZONE->CalculateOffset(BEFORE_DST_START_TIME, offset, bOffsetIsNegative);

    // [Verification]
    BOOST_CHECK(offset == EXPECTED_OFFSET);
    BOOST_CHECK_EQUAL(bOffsetIsNegative, EXPECTED_OFFSET_SIGN);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input date and time is undefined.
/// </summary>
QTEST_CASE ( CalculateOffset_AssertionFailsWhenInputDateIsUndefined_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;
    using Kinesis::QuimeraEngine::Tools::Time::QDateTime;

    // [Preparation]
    const string_q COMMON_TIMEZONE_ID = QE_L("Europe/Madrid");
    const QTimeZone* TIME_ZONE = SQTimeZoneFactory::GetTimeZoneById(COMMON_TIMEZONE_ID);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    
    try
    {
        QTimeSpan offset(0);
        bool bOffsetIsNegative = true;
        TIME_ZONE->CalculateOffset(QDateTime::GetUndefinedDate(), offset, bOffsetIsNegative);
    }
    catch(...) // [TODO] Thund: Use the appropiate exception type when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
QTEST_CASE ( GetId_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
QTEST_CASE ( GetName_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
QTEST_CASE ( GetTimeZoneOffset_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
QTEST_CASE ( GetDstInfo_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
QTEST_CASE ( IsTimeZoneOffsetNegative_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
QTEST_CASE ( HasDstOffset_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

// End - Test Suite: QTimeZone
QTEST_SUITE_END()
