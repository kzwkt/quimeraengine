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

#include "QDateTime.h"

#include "SQTimeZoneFactory.h"

using Kinesis::QuimeraEngine::Tools::Time::QDateTime;
using Kinesis::QuimeraEngine::Tools::Time::QTimeZone;
using Kinesis::QuimeraEngine::Common::DataTypes::i32_q;
using Kinesis::QuimeraEngine::Common::DataTypes::u64_q;

QTEST_SUITE_BEGIN( QDateTime_TestSuite )

/// <summary>
/// Checks that the default value is an undefined date.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValueIsUndefined_Test )
{
    // [Preparation]

	// [Execution]
    QDateTime dateTime;

    // [Verification]
    BOOST_CHECK(dateTime == QDateTime::GetUndefinedDate());
}

/// <summary>
/// Checks that the date and time is copied correctly.
/// </summary>
QTEST_CASE ( Constructor2_DateTimeIsCorrectlyCopied_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;

    // [Preparation]
    const u64_q EXPECTED_YEAR        = 2013;
    const u64_q EXPECTED_MONTH       = 5;
    const u64_q EXPECTED_DAY         = 2;
    const u64_q EXPECTED_HOUR        = 3;
    const u64_q EXPECTED_MINUTE      = 4;
    const u64_q EXPECTED_SECOND      = 5;
    const u64_q EXPECTED_MILLISECOND = 666;
    const u64_q EXPECTED_MICROSECOND = 777;
    const u64_q EXPECTED_HNS         = 8;
    const QTimeZone* EXPECTED_TIMEZONE = SQTimeZoneFactory::GetTimeZoneById(QE_L("Europe/Madrid"));
    const QDateTime ORIGINAL_DATETIME(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                                      EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                                      EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                                      EXPECTED_TIMEZONE);

	// [Execution]
    QDateTime dateTime(ORIGINAL_DATETIME);

    // [Verification]
    BOOST_CHECK(dateTime == ORIGINAL_DATETIME);
    BOOST_CHECK(dateTime.GetTimeZone() == EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the undefined date and time is copied.
/// </summary>
QTEST_CASE ( Constructor2_UndefinedDateTimeIsCopied_Test )
{
    // [Preparation]
    const QDateTime EXPECTED_VALUE = QDateTime::GetUndefinedDate();

	// [Execution]
    QDateTime dateTime(EXPECTED_VALUE);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the instance is correctly constructed from a common date and time.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingCommonDateAndTime_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;

    // [Preparation]
    const u64_q EXPECTED_YEAR        = 2013;
    const u64_q EXPECTED_MONTH       = 11;
    const u64_q EXPECTED_DAY         = 13;
    const u64_q EXPECTED_HOUR        = 10;
    const u64_q EXPECTED_MINUTE      = 32;
    const u64_q EXPECTED_SECOND      = 23;
    const u64_q EXPECTED_MILLISECOND = 654;
    const u64_q EXPECTED_MICROSECOND = 489;
    const u64_q EXPECTED_HNS         = 5;
    const QTimeZone* EXPECTED_TIMEZONE = SQTimeZoneFactory::GetTimeZoneById(QE_L("Atlantic/Canary"));

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed from a common date and time and the time zone is null.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingCommonDateAndTimeAndNullTimeZone_Test )
{
    // [Preparation]
    const u64_q EXPECTED_YEAR        = 2013;
    const u64_q EXPECTED_MONTH       = 11;
    const u64_q EXPECTED_DAY         = 13;
    const u64_q EXPECTED_HOUR        = 10;
    const u64_q EXPECTED_MINUTE      = 32;
    const u64_q EXPECTED_SECOND      = 23;
    const u64_q EXPECTED_MILLISECOND = 654;
    const u64_q EXPECTED_MICROSECOND = 489;
    const u64_q EXPECTED_HNS         = 5;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed from a common date and time and the offset of the time zone is positive.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingCommonDateAndTimeAndTimeZoneOffsetIsPositive_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;

    // [Preparation]
    const u64_q EXPECTED_YEAR        = 2013;
    const u64_q EXPECTED_MONTH       = 11;
    const u64_q EXPECTED_DAY         = 13;
    const u64_q EXPECTED_HOUR        = 10;
    const u64_q EXPECTED_MINUTE      = 32;
    const u64_q EXPECTED_SECOND      = 23;
    const u64_q EXPECTED_MILLISECOND = 654;
    const u64_q EXPECTED_MICROSECOND = 489;
    const u64_q EXPECTED_HNS         = 5;
    const QTimeZone* POSITIVE_TIMEZONE = SQTimeZoneFactory::GetTimeZoneById(QE_L("Europe/Madrid"));

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       POSITIVE_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), POSITIVE_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed from a common date and time and the offset of the time zone is negative.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingCommonDateAndTimeAndTimeZoneOffsetIsNegative_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;

    // [Preparation]
    const u64_q EXPECTED_YEAR        = 2013;
    const u64_q EXPECTED_MONTH       = 11;
    const u64_q EXPECTED_DAY         = 13;
    const u64_q EXPECTED_HOUR        = 10;
    const u64_q EXPECTED_MINUTE      = 32;
    const u64_q EXPECTED_SECOND      = 23;
    const u64_q EXPECTED_MILLISECOND = 654;
    const u64_q EXPECTED_MICROSECOND = 489;
    const u64_q EXPECTED_HNS         = 5;
    const QTimeZone* NEGATIVE_TIMEZONE = SQTimeZoneFactory::GetTimeZoneById(QE_L("America/New_York"));

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       NEGATIVE_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), NEGATIVE_TIMEZONE);
}

/// <summary>
/// Checks that the default value of the time zone is null.
/// </summary>
QTEST_CASE ( Constructor3_TimeZoneDefaultValueIsNull_Test )
{
    // [Preparation]
    const u64_q EXPECTED_YEAR        = 2013;
    const u64_q EXPECTED_MONTH       = 11;
    const u64_q EXPECTED_DAY         = 13;
    const u64_q EXPECTED_HOUR        = 10;
    const u64_q EXPECTED_MINUTE      = 32;
    const u64_q EXPECTED_SECOND      = 23;
    const u64_q EXPECTED_MILLISECOND = 654;
    const u64_q EXPECTED_MICROSECOND = 489;
    const u64_q EXPECTED_HNS         = 5;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the year is greater than the top limit.
/// </summary>
QTEST_CASE ( Constructor3_AssertionFailsWhenYearIsTooHigh_Test )
{
    // [Preparation]
    const u64_q NOT_ALLOWED_YEAR   = 30000;
    const u64_q COMMON_MONTH       = 11;
    const u64_q COMMON_DAY         = 13;
    const u64_q COMMON_HOUR        = 10;
    const u64_q COMMON_MINUTE      = 32;
    const u64_q COMMON_SECOND      = 23;
    const u64_q COMMON_MILLISECOND = 654;
    const u64_q COMMON_MICROSECOND = 489;
    const u64_q COMMON_HNS         = 5;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(NOT_ALLOWED_YEAR, COMMON_MONTH, COMMON_DAY,
                           COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the year is lower than the minimum allowed.
/// </summary>
QTEST_CASE ( Constructor3_AssertionFailsWhenYearIsTooLow_Test )
{
    // [Preparation]
    const i32_q NOT_ALLOWED_YEAR   = -30000;
    const u64_q COMMON_MONTH       = 11;
    const u64_q COMMON_DAY         = 13;
    const u64_q COMMON_HOUR        = 10;
    const u64_q COMMON_MINUTE      = 32;
    const u64_q COMMON_SECOND      = 23;
    const u64_q COMMON_MILLISECOND = 654;
    const u64_q COMMON_MICROSECOND = 489;
    const u64_q COMMON_HNS         = 5;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(NOT_ALLOWED_YEAR, COMMON_MONTH, COMMON_DAY,
                           COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the year equals zero.
/// </summary>
QTEST_CASE ( Constructor3_AssertionFailsWhenYearEqualsZero_Test )
{
    // [Preparation]
    const i32_q YEAR_ZERO          = 0;
    const u64_q COMMON_MONTH       = 11;
    const u64_q COMMON_DAY         = 13;
    const u64_q COMMON_HOUR        = 10;
    const u64_q COMMON_MINUTE      = 32;
    const u64_q COMMON_SECOND      = 23;
    const u64_q COMMON_MILLISECOND = 654;
    const u64_q COMMON_MICROSECOND = 489;
    const u64_q COMMON_HNS         = 5;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(YEAR_ZERO, COMMON_MONTH, COMMON_DAY,
                           COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the month is greater than the top limit.
/// </summary>
QTEST_CASE ( Constructor3_AssertionFailsWhenMonthIsTooHigh_Test )
{
    // [Preparation]
    const i32_q COMMON_YEAR        = 2013;
    const u64_q NOT_ALLOWED_MONTH  = 13;
    const u64_q COMMON_DAY         = 13;
    const u64_q COMMON_HOUR        = 10;
    const u64_q COMMON_MINUTE      = 32;
    const u64_q COMMON_SECOND      = 23;
    const u64_q COMMON_MILLISECOND = 654;
    const u64_q COMMON_MICROSECOND = 489;
    const u64_q COMMON_HNS         = 5;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(COMMON_YEAR, NOT_ALLOWED_MONTH, COMMON_DAY,
                           COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the month equals zero.
/// </summary>
QTEST_CASE ( Constructor3_AssertionFailsWhenMonthEqualsZero_Test )
{
    // [Preparation]
    const i32_q COMMON_YEAR        = 2013;
    const u64_q MONTH_ZERO         = 0;
    const u64_q COMMON_DAY         = 13;
    const u64_q COMMON_HOUR        = 10;
    const u64_q COMMON_MINUTE      = 32;
    const u64_q COMMON_SECOND      = 23;
    const u64_q COMMON_MILLISECOND = 654;
    const u64_q COMMON_MICROSECOND = 489;
    const u64_q COMMON_HNS         = 5;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(COMMON_YEAR, MONTH_ZERO, COMMON_DAY,
                           COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the day is greater than the top limit.
/// </summary>
QTEST_CASE ( Constructor3_AssertionFailsWhenDayIsTooHigh_Test )
{
    // [Preparation]
    const i32_q COMMON_YEAR        = 2013;
    const u64_q COMMON_MONTH       = 11;
    const u64_q NOT_ALLOWED_DAY    = 32;
    const u64_q COMMON_HOUR        = 10;
    const u64_q COMMON_MINUTE      = 32;
    const u64_q COMMON_SECOND      = 23;
    const u64_q COMMON_MILLISECOND = 654;
    const u64_q COMMON_MICROSECOND = 489;
    const u64_q COMMON_HNS         = 5;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(COMMON_YEAR, COMMON_MONTH, NOT_ALLOWED_DAY,
                           COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the day equals zero.
/// </summary>
QTEST_CASE ( Constructor3_AssertionFailsWhenDayEqualsZero_Test )
{
    // [Preparation]
    const i32_q COMMON_YEAR        = 2013;
    const u64_q COMMON_MONTH       = 11;
    const u64_q DAY_ZERO           = 0;
    const u64_q COMMON_HOUR        = 10;
    const u64_q COMMON_MINUTE      = 32;
    const u64_q COMMON_SECOND      = 23;
    const u64_q COMMON_MILLISECOND = 654;
    const u64_q COMMON_MICROSECOND = 489;
    const u64_q COMMON_HNS         = 5;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(COMMON_YEAR, COMMON_MONTH, DAY_ZERO,
                           COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when input day is not valid for the provided input month and year.
/// </summary>
QTEST_CASE ( Constructor3_AssertionFailsWhenDayIsNotValidForTheGivenMonthAndYear_Test )
{
    // [Preparation]
    const i32_q COMMON_YEAR        = 2013;
    const u64_q COMMON_MONTH       = 2;
    const u64_q NOT_ALLOWED_DAY    = 30;
    const u64_q COMMON_HOUR        = 10;
    const u64_q COMMON_MINUTE      = 32;
    const u64_q COMMON_SECOND      = 23;
    const u64_q COMMON_MILLISECOND = 654;
    const u64_q COMMON_MICROSECOND = 489;
    const u64_q COMMON_HNS         = 5;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(COMMON_YEAR, COMMON_MONTH, NOT_ALLOWED_DAY,
                           COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the hour is greater than the top limit.
/// </summary>
QTEST_CASE ( Constructor3_AssertionFailsWhenHourIsTooHigh_Test )
{
    // [Preparation]
    const i32_q COMMON_YEAR        = 2013;
    const u64_q COMMON_MONTH       = 11;
    const u64_q COMMON_DAY         = 13;
    const u64_q NOT_ALLOWED_HOUR   = 24;
    const u64_q COMMON_MINUTE      = 32;
    const u64_q COMMON_SECOND      = 23;
    const u64_q COMMON_MILLISECOND = 654;
    const u64_q COMMON_MICROSECOND = 489;
    const u64_q COMMON_HNS         = 5;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(COMMON_YEAR, COMMON_MONTH, COMMON_DAY,
                           NOT_ALLOWED_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the minute is greater than the top limit.
/// </summary>
QTEST_CASE ( Constructor3_AssertionFailsWhenMinuteIsTooHigh_Test )
{
    // [Preparation]
    const i32_q COMMON_YEAR        = 2013;
    const u64_q COMMON_MONTH       = 11;
    const u64_q COMMON_DAY         = 13;
    const u64_q COMMON_HOUR        = 12;
    const u64_q NOT_ALLOWED_MINUTE = 60;
    const u64_q COMMON_SECOND      = 23;
    const u64_q COMMON_MILLISECOND = 654;
    const u64_q COMMON_MICROSECOND = 489;
    const u64_q COMMON_HNS         = 5;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(COMMON_YEAR, COMMON_MONTH, COMMON_DAY,
                           COMMON_HOUR, NOT_ALLOWED_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the second is greater than the top limit.
/// </summary>
QTEST_CASE ( Constructor3_AssertionFailsWhenSecondIsTooHigh_Test )
{
    // [Preparation]
    const i32_q COMMON_YEAR        = 2013;
    const u64_q COMMON_MONTH       = 11;
    const u64_q COMMON_DAY         = 13;
    const u64_q COMMON_HOUR        = 12;
    const u64_q COMMON_MINUTE      = 50;
    const u64_q NOT_ALLOWED_SECOND = 60;
    const u64_q COMMON_MILLISECOND = 654;
    const u64_q COMMON_MICROSECOND = 489;
    const u64_q COMMON_HNS         = 5;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(COMMON_YEAR, COMMON_MONTH, COMMON_DAY,
                           COMMON_HOUR, COMMON_MINUTE, NOT_ALLOWED_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the millisecond is greater than the top limit.
/// </summary>
QTEST_CASE ( Constructor3_AssertionFailsWhenMillisecondIsTooHigh_Test )
{
    // [Preparation]
    const i32_q COMMON_YEAR             = 2013;
    const u64_q COMMON_MONTH            = 11;
    const u64_q COMMON_DAY              = 13;
    const u64_q COMMON_HOUR             = 12;
    const u64_q COMMON_MINUTE           = 50;
    const u64_q COMMON_SECOND           = 52;
    const u64_q NOT_ALLOWED_MILLISECOND = 1000;
    const u64_q COMMON_MICROSECOND      = 489;
    const u64_q COMMON_HNS              = 5;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(COMMON_YEAR, COMMON_MONTH, COMMON_DAY,
                           COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           NOT_ALLOWED_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the microsecond is greater than the top limit.
/// </summary>
QTEST_CASE ( Constructor3_AssertionFailsWhenMicrosecondIsTooHigh_Test )
{
    // [Preparation]
    const i32_q COMMON_YEAR             = 2013;
    const u64_q COMMON_MONTH            = 11;
    const u64_q COMMON_DAY              = 13;
    const u64_q COMMON_HOUR             = 12;
    const u64_q COMMON_MINUTE           = 50;
    const u64_q COMMON_SECOND           = 52;
    const u64_q COMMON_MILLISECOND      = 546;
    const u64_q NOT_ALLOWED_MICROSECOND = 1000;
    const u64_q COMMON_HNS              = 5;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(COMMON_YEAR, COMMON_MONTH, COMMON_DAY,
                           COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, NOT_ALLOWED_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the hundred of nanoseconds is greater than the top limit.
/// </summary>
QTEST_CASE ( Constructor3_AssertionFailsWhenHundredsOfNanosecondsIsTooHigh_Test )
{
    // [Preparation]
    const i32_q COMMON_YEAR        = 2013;
    const u64_q COMMON_MONTH       = 11;
    const u64_q COMMON_DAY         = 13;
    const u64_q COMMON_HOUR        = 12;
    const u64_q COMMON_MINUTE      = 50;
    const u64_q COMMON_SECOND      = 52;
    const u64_q COMMON_MILLISECOND = 546;
    const u64_q COMMON_MICROSECOND = 256;
    const u64_q NOT_ALLOWED_HNS    = 10;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(COMMON_YEAR, COMMON_MONTH, COMMON_DAY,
                           COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, NOT_ALLOWED_HNS,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the date and time is posterior to maximum.
/// </summary>
QTEST_CASE ( Constructor3_AssertionFailsWhenDateIsPosteriorToMaximum_Test )
{
    // [Preparation]
    const i32_q MAX_YEAR        = QDateTime::GetMaxDateTime().GetYear();
    const u64_q MAX_MONTH       = QDateTime::GetMaxDateTime().GetMonth();
    const u64_q MAX_DAY         = QDateTime::GetMaxDateTime().GetDay();
    const u64_q MAX_HOUR        = QDateTime::GetMaxDateTime().GetHour();
    const u64_q MAX_MINUTE      = QDateTime::GetMaxDateTime().GetMinute();
    const u64_q MAX_SECOND      = QDateTime::GetMaxDateTime().GetSecond();
    const u64_q MAX_MILLISECOND = QDateTime::GetMaxDateTime().GetMillisecond();
    const u64_q MAX_MICROSECOND = QDateTime::GetMaxDateTime().GetMicrosecond();
    const u64_q MAX_HNS         = QDateTime::GetMaxDateTime().GetHundredOfNanosecond();
    const QTimeZone* NULL_TIMEZONE = null_q;
    const u64_q MAX_HNS_PLUS_ONE = MAX_HNS + 1;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(MAX_YEAR, MAX_MONTH, MAX_DAY,
                           MAX_HOUR, MAX_MINUTE, MAX_SECOND,
                           MAX_MILLISECOND, MAX_MICROSECOND, MAX_HNS_PLUS_ONE,
                           NULL_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the date and time is prior to minimum.
/// </summary>
QTEST_CASE ( Constructor3_AssertionFailsWhenDateIsAnteriorToMinimum_Test )
{
    // [Preparation]
    const i32_q MIN_YEAR        = QDateTime::GetMinDateTime().GetYear();
    const u64_q MIN_MONTH       = QDateTime::GetMinDateTime().GetMonth();
    const u64_q MIN_DAY         = QDateTime::GetMinDateTime().GetDay();
    const u64_q MIN_HOUR        = QDateTime::GetMinDateTime().GetHour();
    const u64_q MIN_MINUTE      = QDateTime::GetMinDateTime().GetMinute();
    const u64_q MIN_SECOND      = QDateTime::GetMinDateTime().GetSecond();
    const u64_q MIN_MILLISECOND = QDateTime::GetMinDateTime().GetMillisecond();
    const u64_q MIN_MICROSECOND = QDateTime::GetMinDateTime().GetMicrosecond();
    const u64_q MIN_HNS         = QDateTime::GetMinDateTime().GetHundredOfNanosecond();
    const QTimeZone* NULL_TIMEZONE = null_q;
    const u64_q MIN_HNS_MINUS_ONE = MIN_HNS - 1;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(MIN_YEAR, MIN_MONTH, MIN_DAY,
                           MIN_HOUR, MIN_MINUTE, MIN_SECOND,
                           MIN_MILLISECOND, MIN_MICROSECOND, MIN_HNS_MINUS_ONE,
                           NULL_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the constructed instance has the maximum value when the input date and time is greater than maximum.
/// </summary>
QTEST_CASE ( Constructor3_MaximumDateIsConstructedWhenDateIsPosteriorToMaximum_Test )
{
    // [Preparation]
    const i32_q MAX_YEAR        = QDateTime::GetMaxDateTime().GetYear();
    const u64_q MAX_MONTH       = QDateTime::GetMaxDateTime().GetMonth();
    const u64_q MAX_DAY         = QDateTime::GetMaxDateTime().GetDay();
    const u64_q MAX_HOUR        = QDateTime::GetMaxDateTime().GetHour();
    const u64_q MAX_MINUTE      = QDateTime::GetMaxDateTime().GetMinute();
    const u64_q MAX_SECOND      = QDateTime::GetMaxDateTime().GetSecond();
    const u64_q MAX_MILLISECOND = QDateTime::GetMaxDateTime().GetMillisecond();
    const u64_q MAX_MICROSECOND = QDateTime::GetMaxDateTime().GetMicrosecond();
    const u64_q MAX_HNS         = QDateTime::GetMaxDateTime().GetHundredOfNanosecond();
    const QTimeZone* NULL_TIMEZONE = null_q;
    const u64_q MAX_HNS_PLUS_ONE = MAX_HNS + 1;
    const QDateTime MAX_DATETIME = QDateTime::GetMaxDateTime();

	// [Execution]
    QDateTime dateTime(MAX_YEAR, MAX_MONTH, MAX_DAY,
                       MAX_HOUR, MAX_MINUTE, MAX_SECOND,
                       MAX_MILLISECOND, MAX_MICROSECOND, MAX_HNS_PLUS_ONE,
                       NULL_TIMEZONE);

    // [Verification]
    BOOST_CHECK(dateTime == MAX_DATETIME);
}

/// <summary>
/// Checks that the constructed instance has the minimum value when the input date and time is lower than minimum.
/// </summary>
QTEST_CASE ( Constructor3_MinimumDateIsConstructedWhenDateIsAnteriorToMinimum_Test )
{
    // [Preparation]
    const i32_q MIN_YEAR        = QDateTime::GetMinDateTime().GetYear();
    const u64_q MIN_MONTH       = QDateTime::GetMinDateTime().GetMonth();
    const u64_q MIN_DAY         = QDateTime::GetMinDateTime().GetDay();
    const u64_q MIN_HOUR        = QDateTime::GetMinDateTime().GetHour();
    const u64_q MIN_MINUTE      = QDateTime::GetMinDateTime().GetMinute();
    const u64_q MIN_SECOND      = QDateTime::GetMinDateTime().GetSecond();
    const u64_q MIN_MILLISECOND = QDateTime::GetMinDateTime().GetMillisecond();
    const u64_q MIN_MICROSECOND = QDateTime::GetMinDateTime().GetMicrosecond();
    const u64_q MIN_HNS         = QDateTime::GetMinDateTime().GetHundredOfNanosecond();
    const QTimeZone* MIN_TIMEZONE = null_q;
    const u64_q MIN_HNS_MINUS_ONE = MIN_HNS - 1;
    const QDateTime MIN_DATETIME = QDateTime::GetMinDateTime();

	// [Execution]
    QDateTime dateTime(-scast_q(MIN_YEAR, i32_q), MIN_MONTH, MIN_DAY,
                       MIN_HOUR, MIN_MINUTE, MIN_SECOND,
                       MIN_MILLISECOND, MIN_MICROSECOND, MIN_HNS_MINUS_ONE,
                       MIN_TIMEZONE);

    // [Verification]
    BOOST_CHECK(dateTime == MIN_DATETIME);
}

#endif

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is 0004-05-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstPositiveLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const u64_q EXPECTED_YEAR        = 4;
    const u64_q EXPECTED_MONTH       = 5;
    const u64_q EXPECTED_DAY         = 1;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is -0004-05-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstNegativeLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const i32_q NEGATIVE_YEAR        = -4;
    const u64_q EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_q EXPECTED_MONTH       = 5;
    const u64_q EXPECTED_DAY         = 1;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is 0004-02-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstPositiveLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const u64_q EXPECTED_YEAR        = 4;
    const u64_q EXPECTED_MONTH       = 2;
    const u64_q EXPECTED_DAY         = 1;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is -0004-02-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstNegativeLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const i32_q NEGATIVE_YEAR        = -4;
    const u64_q EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_q EXPECTED_MONTH       = 2;
    const u64_q EXPECTED_DAY         = 1;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is 0001-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstPositiveDateAndTime_Test )
{
    // [Preparation]
    const u64_q EXPECTED_YEAR        = 1;
    const u64_q EXPECTED_MONTH       = 1;
    const u64_q EXPECTED_DAY         = 1;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is -0001-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstInstantOfFirstNegativeYear_Test )
{
    // [Preparation]
    const i32_q NEGATIVE_YEAR        = -1;
    const u64_q EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_q EXPECTED_MONTH       = 1;
    const u64_q EXPECTED_DAY         = 1;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input year is multiple of 5.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenYearIsPositiveAndMultipleOfFive_Test )
{
    // [Preparation]
    const u64_q EXPECTED_YEAR        = 25;
    const u64_q EXPECTED_MONTH       = 1;
    const u64_q EXPECTED_DAY         = 1;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input year is multiple of 5.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenYearIsNegativeAndMultipleOfFive_Test )
{
    // [Preparation]
    const i32_q NEGATIVE_YEAR        = -25;
    const u64_q EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_q EXPECTED_MONTH       = 1;
    const u64_q EXPECTED_DAY         = 1;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when using a positive leap year and the day 29th of February.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingPositiveLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const u64_q EXPECTED_YEAR        = 20;
    const u64_q EXPECTED_MONTH       = 2;
    const u64_q EXPECTED_DAY         = 29;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when using a negative leap year and the day 29th of February.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingNegativeLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const i32_q NEGATIVE_YEAR        = -20;
    const u64_q EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_q EXPECTED_MONTH       = 2;
    const u64_q EXPECTED_DAY         = 29;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when using a positive leap year and the day 28th of February.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingPositiveLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const u64_q EXPECTED_YEAR        = 20;
    const u64_q EXPECTED_MONTH       = 2;
    const u64_q EXPECTED_DAY         = 28;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when using a negative leap year and the day 28th of February.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingNegativeLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const i32_q NEGATIVE_YEAR        = -20;
    const u64_q EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_q EXPECTED_MONTH       = 2;
    const u64_q EXPECTED_DAY         = 28;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is -0001-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingLastNegativeInstant_Test )
{
    // [Preparation]
    const i32_q NEGATIVE_YEAR        = -1;
    const u64_q EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_q EXPECTED_MONTH       = 12;
    const u64_q EXPECTED_DAY         = 31;
    const u64_q EXPECTED_HOUR        = 23;
    const u64_q EXPECTED_MINUTE      = 59;
    const u64_q EXPECTED_SECOND      = 59;
    const u64_q EXPECTED_MILLISECOND = 999;
    const u64_q EXPECTED_MICROSECOND = 999;
    const u64_q EXPECTED_HNS         = 9;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is 0001-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingLastInstantOfFirstPositiveYear_Test )
{
    // [Preparation]
    const u64_q EXPECTED_YEAR        = 1;
    const u64_q EXPECTED_MONTH       = 12;
    const u64_q EXPECTED_DAY         = 31;
    const u64_q EXPECTED_HOUR        = 23;
    const u64_q EXPECTED_MINUTE      = 59;
    const u64_q EXPECTED_SECOND      = 59;
    const u64_q EXPECTED_MILLISECOND = 999;
    const u64_q EXPECTED_MICROSECOND = 999;
    const u64_q EXPECTED_HNS         = 9;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is 0012-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstInstantOfPositiveLeapYear_Test )
{
    // [Preparation]
    const u64_q EXPECTED_YEAR        = 12;
    const u64_q EXPECTED_MONTH       = 1;
    const u64_q EXPECTED_DAY         = 1;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is -0012-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstInstantOfNegativeLeapYear_Test )
{
    // [Preparation]
    const i32_q NEGATIVE_YEAR        = -12;
    const unsigned int EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_q EXPECTED_MONTH       = 1;
    const u64_q EXPECTED_DAY         = 1;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(NEGATIVE_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is 004-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const u64_q EXPECTED_YEAR        = 4;
    const u64_q EXPECTED_MONTH       = 1;
    const u64_q EXPECTED_DAY         = 1;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is -004-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const i32_q NEGATIVE_YEAR        = -4;
    const u64_q EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_q EXPECTED_MONTH       = 1;
    const u64_q EXPECTED_DAY         = 1;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(NEGATIVE_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is 004-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingLastInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const u64_q EXPECTED_YEAR        = 4;
    const u64_q EXPECTED_MONTH       = 1;
    const u64_q EXPECTED_DAY         = 1;
    const u64_q EXPECTED_HOUR        = 23;
    const u64_q EXPECTED_MINUTE      = 59;
    const u64_q EXPECTED_SECOND      = 59;
    const u64_q EXPECTED_MILLISECOND = 999;
    const u64_q EXPECTED_MICROSECOND = 999;
    const u64_q EXPECTED_HNS         = 9;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is -004-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingLastInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const i32_q NEGATIVE_YEAR        = -4;
    const unsigned int EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_q EXPECTED_MONTH       = 12;
    const u64_q EXPECTED_DAY         = 31;
    const u64_q EXPECTED_HOUR        = 23;
    const u64_q EXPECTED_MINUTE      = 59;
    const u64_q EXPECTED_SECOND      = 59;
    const u64_q EXPECTED_MILLISECOND = 999;
    const u64_q EXPECTED_MICROSECOND = 999;
    const u64_q EXPECTED_HNS         = 9;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is the maximum date and time allowed.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingMaximumDateAndTime_Test )
{
    // [Preparation]
    const u64_q MAX_YEAR        = QDateTime::GetMaxDateTime().GetYear();
    const u64_q MAX_MONTH       = QDateTime::GetMaxDateTime().GetMonth();
    const u64_q MAX_DAY         = QDateTime::GetMaxDateTime().GetDay();
    const u64_q MAX_HOUR        = QDateTime::GetMaxDateTime().GetHour();
    const u64_q MAX_MINUTE      = QDateTime::GetMaxDateTime().GetMinute();
    const u64_q MAX_SECOND      = QDateTime::GetMaxDateTime().GetSecond();
    const u64_q MAX_MILLISECOND = QDateTime::GetMaxDateTime().GetMillisecond();
    const u64_q MAX_MICROSECOND = QDateTime::GetMaxDateTime().GetMicrosecond();
    const u64_q MAX_HNS         = QDateTime::GetMaxDateTime().GetHundredOfNanosecond();
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(scast_q(MAX_YEAR, i32_q), MAX_MONTH, MAX_DAY,
                       MAX_HOUR, MAX_MINUTE, MAX_SECOND,
                       MAX_MILLISECOND, MAX_MICROSECOND, MAX_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), MAX_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), MAX_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), MAX_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), MAX_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), MAX_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), MAX_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), MAX_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), MAX_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), MAX_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is the minimum date and time allowed.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingMinimumDateAndTime_Test )
{
    // [Preparation]
    const u64_q MIN_YEAR        = QDateTime::GetMinDateTime().GetYear();
    const u64_q MIN_MONTH       = QDateTime::GetMinDateTime().GetMonth();
    const u64_q MIN_DAY         = QDateTime::GetMinDateTime().GetDay();
    const u64_q MIN_HOUR        = QDateTime::GetMinDateTime().GetHour();
    const u64_q MIN_MINUTE      = QDateTime::GetMinDateTime().GetMinute();
    const u64_q MIN_SECOND      = QDateTime::GetMinDateTime().GetSecond();
    const u64_q MIN_MILLISECOND = QDateTime::GetMinDateTime().GetMillisecond();
    const u64_q MIN_MICROSECOND = QDateTime::GetMinDateTime().GetMicrosecond();
    const u64_q MIN_HNS         = QDateTime::GetMinDateTime().GetHundredOfNanosecond();
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(-scast_q(MIN_YEAR, i32_q), MIN_MONTH, MIN_DAY,
                       MIN_HOUR, MIN_MINUTE, MIN_SECOND,
                       MIN_MILLISECOND, MIN_MICROSECOND, MIN_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), MIN_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), MIN_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), MIN_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), MIN_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), MIN_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), MIN_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), MIN_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), MIN_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), MIN_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}


/// <summary>
/// Checks that the instance is correctly constructed from a common date and time.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingCommonDateAndTime_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;

    // [Preparation]
    const u64_q EXPECTED_YEAR  = 2013;
    const u64_q EXPECTED_MONTH = 11;
    const u64_q EXPECTED_DAY   = 13;
    const QTimeZone* EXPECTED_TIMEZONE = SQTimeZoneFactory::GetTimeZoneById(QE_L("America/Antigua"));

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the default value of the time zone is null.
/// </summary>
QTEST_CASE ( Constructor4_TimeZoneDefaultValueIsNull_Test )
{
    // [Preparation]
    const u64_q EXPECTED_YEAR  = 2013;
    const u64_q EXPECTED_MONTH = 11;
    const u64_q EXPECTED_DAY   = 13;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the year is greater than the top limit.
/// </summary>
QTEST_CASE ( Constructor4_AssertionFailsWhenYearIsTooHigh_Test )
{
    // [Preparation]
    const i32_q NOT_ALLOWED_YEAR = 30000;
    const u64_q COMMON_MONTH     = 11;
    const u64_q COMMON_DAY       = 13;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(NOT_ALLOWED_YEAR, COMMON_MONTH, COMMON_DAY,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the year is lower than the minimum allowed.
/// </summary>
QTEST_CASE ( Constructor4_AssertionFailsWhenYearIsTooLow_Test )
{
    // [Preparation]
    const i32_q NOT_ALLOWED_YEAR = -30000;
    const u64_q COMMON_MONTH     = 11;
    const u64_q COMMON_DAY       = 13;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(NOT_ALLOWED_YEAR, COMMON_MONTH, COMMON_DAY,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the year equals zero.
/// </summary>
QTEST_CASE ( Constructor4_AssertionFailsWhenYearEqualsZero_Test )
{
    // [Preparation]
    const i32_q YEAR_ZERO    = 0;
    const u64_q COMMON_MONTH = 11;
    const u64_q COMMON_DAY   = 13;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(YEAR_ZERO, COMMON_MONTH, COMMON_DAY,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the month is greater than the top limit.
/// </summary>
QTEST_CASE ( Constructor4_AssertionFailsWhenMonthIsTooHigh_Test )
{
    // [Preparation]
    const i32_q COMMON_YEAR       = 2013;
    const u64_q NOT_ALLOWED_MONTH = 13;
    const u64_q COMMON_DAY        = 13;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(COMMON_YEAR, NOT_ALLOWED_MONTH, COMMON_DAY,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the month equals zero.
/// </summary>
QTEST_CASE ( Constructor4_AssertionFailsWhenMonthEqualsZero_Test )
{
    // [Preparation]
    const i32_q COMMON_YEAR = 2013;
    const u64_q MONTH_ZERO  = 0;
    const u64_q COMMON_DAY  = 13;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(COMMON_YEAR, MONTH_ZERO, COMMON_DAY,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the day is greater than the top limit.
/// </summary>
QTEST_CASE ( Constructor4_AssertionFailsWhenDayIsTooHigh_Test )
{
    // [Preparation]
    const i32_q COMMON_YEAR     = 2013;
    const u64_q COMMON_MONTH    = 11;
    const u64_q NOT_ALLOWED_DAY = 32;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(COMMON_YEAR, COMMON_MONTH, NOT_ALLOWED_DAY,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the day equals zero.
/// </summary>
QTEST_CASE ( Constructor4_AssertionFailsWhenDayEqualsZero_Test )
{
    // [Preparation]
    const i32_q COMMON_YEAR  = 2013;
    const u64_q COMMON_MONTH = 11;
    const u64_q DAY_ZERO     = 0;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(COMMON_YEAR, COMMON_MONTH, DAY_ZERO,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when input day is not valid for the provided input month and year.
/// </summary>
QTEST_CASE ( Constructor4_AssertionFailsWhenDayIsNotValidForTheGivenMonthAndYear_Test )
{
    // [Preparation]
    const i32_q COMMON_YEAR     = 2013;
    const u64_q COMMON_MONTH    = 2;
    const u64_q NOT_ALLOWED_DAY = 30;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(COMMON_YEAR, COMMON_MONTH, NOT_ALLOWED_DAY,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the date and time is posterior to maximum.
/// </summary>
QTEST_CASE ( Constructor4_AssertionFailsWhenDateIsPosteriorToMaximum_Test )
{
    // [Preparation]
    const i32_q MAX_YEAR  = QDateTime::GetMaxDateTime().GetYear();
    const u64_q MAX_MONTH = QDateTime::GetMaxDateTime().GetMonth();
    const u64_q MAX_DAY   = QDateTime::GetMaxDateTime().GetDay();
    const QTimeZone* NULL_TIMEZONE = null_q;
    const u64_q MAX_DAY_PLUS_ONE = MAX_DAY + 1;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(MAX_YEAR, MAX_MONTH, MAX_DAY_PLUS_ONE,
                           NULL_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the date and time is prior to minimum.
/// </summary>
QTEST_CASE ( Constructor4_AssertionFailsWhenDateIsAnteriorToMinimum_Test )
{
    // [Preparation]
    const i32_q MIN_YEAR  = QDateTime::GetMinDateTime().GetYear();
    const u64_q MIN_MONTH = QDateTime::GetMinDateTime().GetMonth();
    const u64_q MIN_DAY   = QDateTime::GetMinDateTime().GetDay() + 1; // (time is 00:00:00, which would be prior to minimum, so next day is used)
    const QTimeZone* NULL_TIMEZONE = null_q;
    const u64_q MIN_DAY_MINUS_ONE = MIN_DAY - 1;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(MIN_YEAR, MIN_MONTH, MIN_DAY_MINUS_ONE,
                           NULL_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the constructed instance has the maximum value when the input date and time is greater than maximum.
/// </summary>
QTEST_CASE ( Constructor4_MaximumDateIsConstructedWhenDateIsPosteriorToMaximum_Test )
{
    // [Preparation]
    const i32_q MAX_YEAR  = QDateTime::GetMaxDateTime().GetYear();
    const u64_q MAX_MONTH = QDateTime::GetMaxDateTime().GetMonth();
    const u64_q MAX_DAY   = QDateTime::GetMaxDateTime().GetDay();
    const QTimeZone* NULL_TIMEZONE = null_q;
    const u64_q MAX_DAY_PLUS_ONE = MAX_DAY + 1;
    const QDateTime MAX_DATETIME = QDateTime::GetMaxDateTime();

	// [Execution]
    QDateTime dateTime(MAX_YEAR, MAX_MONTH, MAX_DAY_PLUS_ONE,
                       NULL_TIMEZONE);

    // [Verification]
    BOOST_CHECK(dateTime == MAX_DATETIME);
}

/// <summary>
/// Checks that the constructed instance has the minimum value when the input date and time is lower than minimum.
/// </summary>
QTEST_CASE ( Constructor4_MinimumDateIsConstructedWhenDateIsAnteriorToMinimum_Test )
{
    // [Preparation]
    const i32_q MIN_YEAR  = QDateTime::GetMinDateTime().GetYear();
    const u64_q MIN_MONTH = QDateTime::GetMinDateTime().GetMonth();
    const u64_q MIN_DAY   = QDateTime::GetMinDateTime().GetDay() + 1; // (time is 00:00:00, which would be prior to minimum, so next day is used)
    const QTimeZone* NULL_TIMEZONE = null_q;
    const u64_q MIN_DAY_MINUS_ONE = MIN_DAY - 1;
    const QDateTime MIN_DATETIME = QDateTime::GetMinDateTime();

	// [Execution]
    QDateTime dateTime(-scast_q(MIN_YEAR, i32_q), MIN_MONTH, MIN_DAY_MINUS_ONE,
                       NULL_TIMEZONE);

    // [Verification]
    BOOST_CHECK(dateTime == MIN_DATETIME);
}

#endif

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is 0004-05-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstPositiveLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const u64_q EXPECTED_YEAR        = 4;
    const u64_q EXPECTED_MONTH       = 5;
    const u64_q EXPECTED_DAY         = 1;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is -0004-05-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstNegativeLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const i32_q NEGATIVE_YEAR        = -4;
    const unsigned int EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_q EXPECTED_MONTH       = 5;
    const u64_q EXPECTED_DAY         = 1;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is 0004-02-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstPositiveLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const u64_q EXPECTED_YEAR        = 4;
    const u64_q EXPECTED_MONTH       = 2;
    const u64_q EXPECTED_DAY         = 1;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is -0004-02-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstNegativeLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const i32_q NEGATIVE_YEAR        = -4;
    const unsigned int EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_q EXPECTED_MONTH       = 2;
    const u64_q EXPECTED_DAY         = 1;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is 0001-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstPositiveDateAndTime_Test )
{
    // [Preparation]
    const u64_q EXPECTED_YEAR        = 1;
    const u64_q EXPECTED_MONTH       = 1;
    const u64_q EXPECTED_DAY         = 1;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is -0001-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstInstantOfFirstNegativeYear_Test )
{
    // [Preparation]
    const i32_q NEGATIVE_YEAR        = -1;
    const unsigned int EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_q EXPECTED_MONTH       = 1;
    const u64_q EXPECTED_DAY         = 1;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input year is multiple of 5.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenYearIsPositiveAndMultipleOfFive_Test )
{
    // [Preparation]
    const u64_q EXPECTED_YEAR        = 25;
    const u64_q EXPECTED_MONTH       = 1;
    const u64_q EXPECTED_DAY         = 1;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input year is multiple of 5.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenYearIsNegativeAndMultipleOfFive_Test )
{
    // [Preparation]
    const i32_q NEGATIVE_YEAR        = -25;
    const unsigned int EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_q EXPECTED_MONTH       = 1;
    const u64_q EXPECTED_DAY         = 1;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when using a positive leap year and the day 29th of February.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingPositiveLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const u64_q EXPECTED_YEAR        = 20;
    const u64_q EXPECTED_MONTH       = 2;
    const u64_q EXPECTED_DAY         = 29;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when using a negative leap year and the day 29th of February.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingNegativeLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const i32_q NEGATIVE_YEAR        = -20;
    const unsigned int EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_q EXPECTED_MONTH       = 2;
    const u64_q EXPECTED_DAY         = 29;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when using a positive leap year and the day 28th of February.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingPositiveLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const u64_q EXPECTED_YEAR        = 20;
    const u64_q EXPECTED_MONTH       = 2;
    const u64_q EXPECTED_DAY         = 28;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when using a negative leap year and the day 28th of February.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingNegativeLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const i32_q NEGATIVE_YEAR        = -20;
    const unsigned int EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_q EXPECTED_MONTH       = 2;
    const u64_q EXPECTED_DAY         = 28;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is 0012-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstInstantOfPositiveLeapYear_Test )
{
    // [Preparation]
    const u64_q EXPECTED_YEAR        = 12;
    const u64_q EXPECTED_MONTH       = 1;
    const u64_q EXPECTED_DAY         = 1;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is -0012-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstInstantOfNegativeLeapYear_Test )
{
    // [Preparation]
    const i32_q NEGATIVE_YEAR        = -12;
    const unsigned int EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_q EXPECTED_MONTH       = 1;
    const u64_q EXPECTED_DAY         = 1;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is 004-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const u64_q EXPECTED_YEAR        = 4;
    const u64_q EXPECTED_MONTH       = 1;
    const u64_q EXPECTED_DAY         = 1;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is -004-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const i32_q NEGATIVE_YEAR        = -4;
    const unsigned int EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_q EXPECTED_MONTH       = 1;
    const u64_q EXPECTED_DAY         = 1;
    const u64_q EXPECTED_HOUR        = 0;
    const u64_q EXPECTED_MINUTE      = 0;
    const u64_q EXPECTED_SECOND      = 0;
    const u64_q EXPECTED_MILLISECOND = 0;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is the maximum date and time allowed.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingMaximumDateAndTime_Test )
{
    // [Preparation]
    const u64_q MAX_YEAR        = QDateTime::GetMaxDateTime().GetYear();
    const u64_q MAX_MONTH       = QDateTime::GetMaxDateTime().GetMonth();
    const u64_q MAX_DAY         = QDateTime::GetMaxDateTime().GetDay();
    const u64_q MAX_HOUR        = 0;
    const u64_q MAX_MINUTE      = 0;
    const u64_q MAX_SECOND      = 0;
    const u64_q MAX_MILLISECOND = 0;
    const u64_q MAX_MICROSECOND = 0;
    const u64_q MAX_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(scast_q(MAX_YEAR, i32_q), MAX_MONTH, MAX_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), MAX_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), MAX_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), MAX_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), MAX_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), MAX_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), MAX_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), MAX_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), MAX_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), MAX_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is the minimum date and time allowed.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingMinimumDateAndTime_Test )
{
    // [Preparation]
    const u64_q MIN_YEAR        = QDateTime::GetMinDateTime().GetYear();
    const u64_q MIN_MONTH       = QDateTime::GetMinDateTime().GetMonth();
    const u64_q MIN_DAY         = QDateTime::GetMinDateTime().GetDay() + 1;
    const u64_q MIN_HOUR        = 0;
    const u64_q MIN_MINUTE      = 0;
    const u64_q MIN_SECOND      = 0;
    const u64_q MIN_MILLISECOND = 0;
    const u64_q MIN_MICROSECOND = 0;
    const u64_q MIN_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(-scast_q(MIN_YEAR, i32_q), MIN_MONTH, MIN_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), MIN_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), MIN_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), MIN_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), MIN_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), MIN_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), MIN_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), MIN_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), MIN_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), MIN_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed from a common time.
/// </summary>
QTEST_CASE ( Constructor5_IsCorrectlyConstructedWhenUsingCommonTime_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;

    // [Preparation]
    const u64_q EXPECTED_YEAR        = 1;
    const u64_q EXPECTED_MONTH       = 1;
    const u64_q EXPECTED_DAY         = 1;
    const u64_q EXPECTED_HOUR        = 10;
    const u64_q EXPECTED_MINUTE      = 32;
    const u64_q EXPECTED_SECOND      = 23;
    const u64_q EXPECTED_MILLISECOND = 654;
    const u64_q EXPECTED_MICROSECOND = 489;
    const u64_q EXPECTED_HNS         = 5;
    const QTimeZone* EXPECTED_TIMEZONE = SQTimeZoneFactory::GetTimeZoneById(QE_L("America/Antigua"));

	// [Execution]
    QDateTime dateTime(EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the default value of the time zone is null.
/// </summary>
QTEST_CASE ( Constructor5_TimeZoneDefaultValueIsNull_Test )
{
    // [Preparation]
    const u64_q EXPECTED_HOUR        = 10;
    const u64_q EXPECTED_MINUTE      = 32;
    const u64_q EXPECTED_SECOND      = 23;
    const u64_q EXPECTED_MILLISECOND = 654;
    const u64_q EXPECTED_MICROSECOND = 489;
    const u64_q EXPECTED_HNS         = 5;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the hour is greater than the top limit.
/// </summary>
QTEST_CASE ( Constructor5_AssertionFailsWhenHourTooHigh_Test )
{
    // [Preparation]
    const u64_q NOT_ALLOWED_HOUR   = 24;
    const u64_q COMMON_MINUTE      = 32;
    const u64_q COMMON_SECOND      = 23;
    const u64_q COMMON_MILLISECOND = 654;
    const u64_q COMMON_MICROSECOND = 489;
    const u64_q COMMON_HNS         = 5;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(NOT_ALLOWED_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the minute is greater than the top limit.
/// </summary>
QTEST_CASE ( Constructor5_AssertionFailsWhenMinuteTooHigh_Test )
{
    // [Preparation]
    const u64_q COMMON_HOUR        = 12;
    const u64_q NOT_ALLOWED_MINUTE = 60;
    const u64_q COMMON_SECOND      = 23;
    const u64_q COMMON_MILLISECOND = 654;
    const u64_q COMMON_MICROSECOND = 489;
    const u64_q COMMON_HNS         = 5;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(COMMON_HOUR, NOT_ALLOWED_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the second is greater than the top limit.
/// </summary>
QTEST_CASE ( Constructor5_AssertionFailsWhenSecondTooHigh_Test )
{
    // [Preparation]
    const u64_q COMMON_HOUR        = 12;
    const u64_q COMMON_MINUTE      = 50;
    const u64_q NOT_ALLOWED_SECOND = 60;
    const u64_q COMMON_MILLISECOND = 654;
    const u64_q COMMON_MICROSECOND = 489;
    const u64_q COMMON_HNS         = 5;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(COMMON_HOUR, COMMON_MINUTE, NOT_ALLOWED_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the millisecond is greater than the top limit.
/// </summary>
QTEST_CASE ( Constructor5_AssertionFailsWhenMillisecondTooHigh_Test )
{
    // [Preparation]
    const u64_q COMMON_HOUR             = 12;
    const u64_q COMMON_MINUTE           = 50;
    const u64_q COMMON_SECOND           = 52;
    const u64_q NOT_ALLOWED_MILLISECOND = 1000;
    const u64_q COMMON_MICROSECOND      = 489;
    const u64_q COMMON_HNS              = 5;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           NOT_ALLOWED_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the microsecond is greater than the top limit.
/// </summary>
QTEST_CASE ( Constructor5_AssertionFailsWhenMicrosecondTooHigh_Test )
{
    // [Preparation]
    const u64_q COMMON_HOUR             = 12;
    const u64_q COMMON_MINUTE           = 50;
    const u64_q COMMON_SECOND           = 52;
    const u64_q COMMON_MILLISECOND      = 546;
    const u64_q NOT_ALLOWED_MICROSECOND = 1000;
    const u64_q COMMON_HNS              = 5;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, NOT_ALLOWED_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the hundred of nanoseconds is greater than the top limit.
/// </summary>
QTEST_CASE ( Constructor5_AssertionFailsWhenHundredsOfNanosecondsTooHigh_Test )
{
    // [Preparation]
    const u64_q COMMON_HOUR        = 12;
    const u64_q COMMON_MINUTE      = 50;
    const u64_q COMMON_SECOND      = 52;
    const u64_q COMMON_MILLISECOND = 546;
    const u64_q COMMON_MICROSECOND = 256;
    const u64_q NOT_ALLOWED_HNS    = 10;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, NOT_ALLOWED_HNS,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that the instance is correctly constructed from a common time.
/// </summary>
QTEST_CASE ( Constructor6_IsCorrectlyConstructedWhenUsingCommonTime_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;

    // [Preparation]
    const u64_q EXPECTED_YEAR        = 1;
    const u64_q EXPECTED_MONTH       = 1;
    const u64_q EXPECTED_DAY         = 1;
    const u64_q EXPECTED_HOUR        = 10;
    const u64_q EXPECTED_MINUTE      = 32;
    const u64_q EXPECTED_SECOND      = 23;
    const u64_q EXPECTED_MILLISECOND = 654;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = SQTimeZoneFactory::GetTimeZoneById(QE_L("America/Antigua"));

	// [Execution]
    QDateTime dateTime(EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the default value of the time zone is null.
/// </summary>
QTEST_CASE ( Constructor6_TimeZoneDefaultValueIsNull_Test )
{
    // [Preparation]
    const u64_q EXPECTED_HOUR        = 10;
    const u64_q EXPECTED_MINUTE      = 32;
    const u64_q EXPECTED_SECOND      = 23;
    const u64_q EXPECTED_MILLISECOND = 654;
    const u64_q EXPECTED_MICROSECOND = 489;
    const u64_q EXPECTED_HNS         = 5;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the hour is greater than the top limit.
/// </summary>
QTEST_CASE ( Constructor6_AssertionFailsWhenHourIsTooHigh_Test )
{
    // [Preparation]
    const u64_q NOT_ALLOWED_HOUR   = 24;
    const u64_q COMMON_MINUTE      = 32;
    const u64_q COMMON_SECOND      = 23;
    const u64_q COMMON_MILLISECOND = 654;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(NOT_ALLOWED_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the minute is greater than the top limit.
/// </summary>
QTEST_CASE ( Constructor6_AssertionFailsWhenMinuteIsTooHigh_Test )
{
    // [Preparation]
    const u64_q COMMON_HOUR        = 12;
    const u64_q NOT_ALLOWED_MINUTE = 60;
    const u64_q COMMON_SECOND      = 23;
    const u64_q COMMON_MILLISECOND = 654;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(COMMON_HOUR, NOT_ALLOWED_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the second is greater than the top limit.
/// </summary>
QTEST_CASE ( Constructor6_AssertionFailsWhenSecondIsTooHigh_Test )
{
    // [Preparation]
    const u64_q COMMON_HOUR        = 12;
    const u64_q COMMON_MINUTE      = 50;
    const u64_q NOT_ALLOWED_SECOND = 60;
    const u64_q COMMON_MILLISECOND = 654;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(COMMON_HOUR, COMMON_MINUTE, NOT_ALLOWED_SECOND,
                           COMMON_MILLISECOND,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the millisecond is greater than the top limit.
/// </summary>
QTEST_CASE ( Constructor6_AssertionFailsWhenMillisecondIsTooHigh_Test )
{
    // [Preparation]
    const u64_q COMMON_HOUR             = 12;
    const u64_q COMMON_MINUTE           = 50;
    const u64_q COMMON_SECOND           = 52;
    const u64_q NOT_ALLOWED_MILLISECOND = 1000;
    const QTimeZone* COMMON_TIMEZONE = null_q;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           NOT_ALLOWED_MILLISECOND,
                           COMMON_TIMEZONE);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that the instance is correctly constructed.
/// </summary>
QTEST_CASE ( Constructor7_InstanceIsCorrectlyConstructed_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;

    // [Preparation]
    const QTimeZone* EXPECTED_TIMEZONE = SQTimeZoneFactory::GetTimeZoneById(QE_L("Europe/Madrid"));
    const QDateTime EXPECTED_DATETIME(1, 2, 3, 4, 5, 6, 7, 8, 9, null_q);

	// [Execution]
    QDateTime dateTime(EXPECTED_DATETIME, EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, without year sign, time fraction or time zone offset.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithNoYearSignAndNoFractionAndNoTimeZone_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("1234-12-23T12:34:56");
    const QDateTime EXPECTED_DATETIME(1234, 12, 23, 12, 34, 56, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with year positive sign but without time fraction or time zone offset.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithYearPositiveSignAndNoFractionAndNoTimeZone_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("+1234-12-23T12:34:56");
    const QDateTime EXPECTED_DATETIME(1234, 12, 23, 12, 34, 56, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with year negative sign but without time fraction or time zone offset.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithYearNegativeSignAndNoFractionAndNoTimeZone_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("-1234-12-23T12:34:56");
    const QDateTime EXPECTED_DATETIME(-1235, 12, 23, 12, 34, 56, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with a year of 5 numbers, and without year sign or time fraction or time zone offset.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithYearOfFiveNumbersAndNoYearSignAndNoFractionAndNoTimeZone_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("12345-12-23T12:34:56");
    const QDateTime EXPECTED_DATETIME(12345, 12, 23, 12, 34, 56, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with a year of 5 numbers and with year positive sign but without time fraction or time zone offset.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithYearOfFiveNumbersAndYearPositiveSignAndNoFractionAndNoTimeZone_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("+12345-12-23T12:34:56");
    const QDateTime EXPECTED_DATETIME(12345, 12, 23, 12, 34, 56, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with a year of 5 numbers and with year negative sign but without time fraction or time zone offset.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithYearOfFiveNumbersAndYearNegativeSignAndNoFractionAndNoTimeZone_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("-12345-12-23T12:34:56");
    const QDateTime EXPECTED_DATETIME(-12346, 12, 23, 12, 34, 56, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, using basic format.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeUsingBasicFormat_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("123451223T123456");
    const QDateTime EXPECTED_DATETIME(12345, 12, 23, 12, 34, 56, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, using extended format.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeUsingExtendedFormat_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("12345-12-23T12:34:56");
    const QDateTime EXPECTED_DATETIME(12345, 12, 23, 12, 34, 56, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with a positive time offset, using basic format.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithPositiveTimeOffsetUsingBasicFormat_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("123451223T235657+1122");
    const QDateTime EXPECTED_DATETIME(12345, 12, 23, 12, 34, 57, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with a positive time offset, using extended format.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithPositiveTimeOffsetUsingExtendedFormat_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("12345-12-23T23:56:57+11:22");
    const QDateTime EXPECTED_DATETIME(12345, 12, 23, 12, 34, 57, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with a negative time offset, using basic format.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithNegativeTimeOffsetUsingBasicFormat_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("123451223T123457-1122");
    const QDateTime EXPECTED_DATETIME(12345, 12, 23, 23, 56, 57, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with a negative time offset, using extended format.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithNegativeTimeOffsetUsingExtendedFormat_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("12345-12-23T12:34:57-11:22");
    const QDateTime EXPECTED_DATETIME(12345, 12, 23, 23, 56, 57, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with a time offset and a time fraction, using basic format.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithTimeOffsetAndFractionUsingBasicFormat_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("123451223T123457.1234567-1122");
    const QDateTime EXPECTED_DATETIME(12345, 12, 23, 23, 56, 57, 123, 456, 7, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with a time offset and a time fraction, using extended format.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithTimeOffsetAndFractionUsingExtendedFormat_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("12345-12-23T12:34:57.1234567-11:22");
    const QDateTime EXPECTED_DATETIME(12345, 12, 23, 23, 56, 57, 123, 456, 7, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with fraction of 8 numbers.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithFractionOfEightNumbers_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("12345-12-23T12:34:57.12345678");
    const QDateTime EXPECTED_DATETIME(12345, 12, 23, 12, 34, 57, 123, 456, 7, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with fraction of 7 numbers.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithFractionOfSevenNumbers_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("12345-12-23T12:34:57.1234567");
    const QDateTime EXPECTED_DATETIME(12345, 12, 23, 12, 34, 57, 123, 456, 7, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with fraction of 1 number.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithFractionOfOneNumber_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("12345-12-23T12:34:57.1");
    const QDateTime EXPECTED_DATETIME(12345, 12, 23, 12, 34, 57, 100, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with fraction with format "0000001".
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithFractionWithFormat0000001_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("12345-12-23T12:34:57.0000001");
    const QDateTime EXPECTED_DATETIME(12345, 12, 23, 12, 34, 57, 0, 0, 1, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with fraction with format "0010023".
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithFractionWithFormat0010023_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("12345-12-23T12:34:57.0010023");
    const QDateTime EXPECTED_DATETIME(12345, 12, 23, 12, 34, 57, 1, 2, 3, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with fraction with format "1002003".
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithFractionWithFormat1002003_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("12345-12-23T12:34:57.1002003");
    const QDateTime EXPECTED_DATETIME(12345, 12, 23, 12, 34, 57, 100, 200, 3, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with Zulu time.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithZuluTime_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("12345-12-23T12:34:57.1234567Z");
    const QDateTime EXPECTED_DATETIME(12345, 12, 23, 12, 34, 57, 123, 456, 7, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the year +0000 means 1 BC.
/// </summary>
QTEST_CASE ( Constructor8_PositiveYear0000Means1BC_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("-0000-12-23T12:34:57");
    const QDateTime EXPECTED_DATETIME(-1, 12, 23, 12, 34, 57, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the year -0000 means 1 BC.
/// </summary>
QTEST_CASE ( Constructor8_NegativeYear0000Means1BC_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("-0000-12-23T12:34:57");
    const QDateTime EXPECTED_DATETIME(-1, 12, 23, 12, 34, 57, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the hour 24 means 00.
/// </summary>
QTEST_CASE ( Constructor8_Hour24Means00_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("1234-12-23T24:00:00");
    const QDateTime EXPECTED_DATETIME(1234, 12, 23, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the negative time offset affects the date.
/// </summary>
QTEST_CASE ( Constructor8_NegativeTimeOffsetAffectsTheDate_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("1234-12-23T23:00:00-03:00");
    const QDateTime EXPECTED_DATETIME(1234, 12, 24, 2, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the positive time offset affects the date.
/// </summary>
QTEST_CASE ( Constructor8_PositiveTimeOffsetAffectsTheDate_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("1234-12-23T01:00:00+03:00");
    const QDateTime EXPECTED_DATETIME(1234, 12, 22, 22, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of a year of 4 numbers with a positive sign.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfYearOfFourNumbersWithPositiveSign_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("+1234");
    const QDateTime EXPECTED_DATETIME(1234, 1, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of a year of 4 numbers with a negative sign.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfYearOfFourNumbersWithNegativeSign_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("-1234");
    const QDateTime EXPECTED_DATETIME(-1235, 1, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of a year of 5 numbers with a positive sign.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfYearOfFiveNumbersWithPositiveSign_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("+12345");
    const QDateTime EXPECTED_DATETIME(12345, 1, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of a year of 5 numbers with a negative sign.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfYearOfFiveNumbersWithNegativeSign_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("-12345");
    const QDateTime EXPECTED_DATETIME(-12346, 1, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of a date with a year of 5 numbers without sign.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfDateWithYearOfFiveNumbersWithoutSignUsingExtendedFormat_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("12345-09-15");
    const QDateTime EXPECTED_DATETIME(12345, 9, 15, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of a date with a year of 4 numbers without sign.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfDateWithYearOfFourNumbersWithoutSignUsingExtendedFormat_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("1234-09-15");
    const QDateTime EXPECTED_DATETIME(1234, 9, 15, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of a date with a year of 4 numbers with positive sign and month and day, using basic format.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfYearOfFourNumbersWithPositiveSignAndMonthAndDayUsingBasicFormat_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("+12341223");
    const QDateTime EXPECTED_DATETIME(1234, 12, 23, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of a date with a year of 4 numbers with negative sign and month and day, using basic format.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfYearOfFourNumbersWithNegativeSignAndMonthAndDayUsingBasicFormat_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("-12341223");
    const QDateTime EXPECTED_DATETIME(-1235, 12, 23, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the year +0000 is the year 1 BC.
/// </summary>
QTEST_CASE ( Constructor8_PositiveYear0000Means1BCWhenTimestampIsCompoundOfDateOnly_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("+00001223");
    const QDateTime EXPECTED_DATETIME(-1, 12, 23, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the year -0000 is the year 1 BC.
/// </summary>
QTEST_CASE ( Constructor8_NegativeYear0000Means1BCWhenTimestampIsCompoundOfDateOnly_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("-00001223");
    const QDateTime EXPECTED_DATETIME(-1, 12, 23, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of hour only.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfHourOnly_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("13");
    const QDateTime EXPECTED_DATETIME(1, 1, 1, 13, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of hour and minute only, using basic format.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfHourAndMinuteOnlyUsingBasicFormat_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("1357");
    const QDateTime EXPECTED_DATETIME(1, 1, 1, 13, 57, 0, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of hour and minute and second only, using basic format.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfHourAndMinuteAndSecondOnlyUsingBasicFormat_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("135748");
    const QDateTime EXPECTED_DATETIME(1, 1, 1, 13, 57, 48, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of hour and minute only, using extended format.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfHourAndMinuteOnlyUsingExtendedFormat_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("13:57");
    const QDateTime EXPECTED_DATETIME(1, 1, 1, 13, 57, 0, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of hour and minute and second only, using extended format.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfHourAndMinuteAndSecondOnlyUsingExtendedFormat_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("13:57:48");
    const QDateTime EXPECTED_DATETIME(1, 1, 1, 13, 57, 48, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of hour only with time offset.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfHourOnlyWithTimeOffset_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("13+0130");
    const QDateTime EXPECTED_DATETIME(1, 1, 1, 11, 30, 0, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of hour and minute only with time offset, using basic format.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfHourAndMinuteOnlyWithTimeOffsetUsingBasicFormat_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("1357+0130");
    const QDateTime EXPECTED_DATETIME(1, 1, 1, 12, 27, 0, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of hour and minute and second only with time offset, using basic format.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfHourAndMinuteAndSecondOnlyWithTimeOffsetUsingBasicFormat_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("135748+0130");
    const QDateTime EXPECTED_DATETIME(1, 1, 1, 12, 27, 48, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of hour and minute only with time offset, using extended format.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfHourAndMinuteOnlyWithTimeOffsetUsingExtendedFormat_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("13:57+01:30");
    const QDateTime EXPECTED_DATETIME(1, 1, 1, 12, 27, 0, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of hour and minute and second only with time offset, using extended format.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfHourAndMinuteAndSecondOnlyWithTimeOffsetUsingExtendedFormat_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("13:57:48+01:30");
    const QDateTime EXPECTED_DATETIME(1, 1, 1, 12, 27, 48, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of time with time offset composed of hour only.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfTimeWithTimeOffsetCompoundOfHourOnly_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("13:57:48+01");
    const QDateTime EXPECTED_DATETIME(1, 1, 1, 12, 57, 48, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of time with negative time offset.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfTimeWithNegativeTimeOffset_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("13:57:48-01:30");
    const QDateTime EXPECTED_DATETIME(1, 1, 1, 15, 27, 48, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of time with fraction but without time offset.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfTimeWithFractionWithoutTimeOffset_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("13:57:48.1234567");
    const QDateTime EXPECTED_DATETIME(1, 1, 1, 13, 57, 48, 123, 456, 7, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of time with time offset and fraction of 7 numbers.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfTimeWithTimeOffsetAndFractionOfSevenNumbers_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("13:57:48.1234567-01:30");
    const QDateTime EXPECTED_DATETIME(1, 1, 1, 15, 27, 48, 123, 456, 7, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of time with time offset and fraction of 8 numbers.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfTimeWithTimeOffsetAndFractionOfEightNumbers_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("13:57:48.12345678-01:30");
    const QDateTime EXPECTED_DATETIME(1, 1, 1, 15, 27, 48, 123, 456, 7, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of time with time offset and fraction of 1 number.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfTimeWithTimeOffsetAndFractionOfOneNumber_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("13:57:48.1-01:30");
    const QDateTime EXPECTED_DATETIME(1, 1, 1, 15, 27, 48, 100, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of time with time offset and fraction like "0000001".
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfTimeWithTimeOffsetAndFractionLike0000001_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("13:57:48.0000001-01:30");
    const QDateTime EXPECTED_DATETIME(1, 1, 1, 15, 27, 48, 0, 0, 1, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of time with time offset and fraction like "1002003".
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfTimeWithTimeOffsetAndFractionLike0010023_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("13:57:48.1002003-01:30");
    const QDateTime EXPECTED_DATETIME(1, 1, 1, 15, 27, 48, 100, 200, 3, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of time with fraction and Zulu Time.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfTimeWithFractionAndZuluTime_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("13:57:48.1234Z");
    const QDateTime EXPECTED_DATETIME(1, 1, 1, 13, 57, 48, 123, 400, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of time with Zulu Time.
/// </summary>
QTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfTimeWithZuluTime_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("13:57:48Z");
    const QDateTime EXPECTED_DATETIME(1, 1, 1, 13, 57, 48, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the hour 24 means 00 when the timestamp is composed of the hour only.
/// </summary>
QTEST_CASE ( Constructor8_Hour24Means00WhenTimeIsCompoundOfHourOnly_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("24");
    const QDateTime EXPECTED_DATETIME(1, 1, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the hour 24 means 00 when the timestamp is composed of the hour and the minute only.
/// </summary>
QTEST_CASE ( Constructor8_Hour24Means00WhenTimeIsCompoundOfHourAndMinuteOnly_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("24:00");
    const QDateTime EXPECTED_DATETIME(1, 1, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the hour 24 means 00 when the timestamp is composed of the hour, the minute and the second.
/// </summary>
QTEST_CASE ( Constructor8_Hour24Means00WhenTimeIsCompoundOfHourAndMinuteAndSecond_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("240000");
    const QDateTime EXPECTED_DATETIME(1, 1, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the negative time offset does not affect the date when the timestamp is composed of time only.
/// </summary>
QTEST_CASE ( Constructor8_NegativeTimeOffsetDoesNotAffectTheDateWhenTimestampIsCompoundOfTimeOnly_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("23:00:00-03:00");
    const QDateTime EXPECTED_DATETIME(1, 1, 1, 2, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the positive time offset does not affect the date when the timestamp is composed of time only.
/// </summary>
QTEST_CASE ( Constructor8_PositiveTimeOffsetDoesNotAffectTheDateWhenTimestampIsCompoundOfTimeOnly_Test )
{
    // [Preparation]
    const string_q TIMESTAMP("01:00:00+03:00");
    const QDateTime EXPECTED_DATETIME(1, 1, 1, 22, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    QDateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input string is empty.
/// </summary>
QTEST_CASE ( Constructor8_AssertionFailsWhenInputStringIsEmpty_Test )
{
    // [Preparation]
    const string_q EMPTY_TIMESTAMP;
    const bool ASSERTION_FAILED = true;


	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(EMPTY_TIMESTAMP);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the input string contains whitespaces.
/// </summary>
QTEST_CASE ( Constructor8_AssertionFailsWhenInputStringContainsWhitesSpaces_Test )
{
    // [Preparation]
    const string_q TIMESTAMP = "2000-12-13 10:20:33";
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(TIMESTAMP);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that the input date and time are correctly copied.
/// </summary>
QTEST_CASE ( OperatorAssignation_InputDateTimeIsCorrectlyCopied_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;

    // [Preparation]
    const u64_q EXPECTED_YEAR        = 2013;
    const u64_q EXPECTED_MONTH       = 5;
    const u64_q EXPECTED_DAY         = 2;
    const u64_q EXPECTED_HOUR        = 3;
    const u64_q EXPECTED_MINUTE      = 4;
    const u64_q EXPECTED_SECOND      = 5;
    const u64_q EXPECTED_MILLISECOND = 666;
    const u64_q EXPECTED_MICROSECOND = 777;
    const u64_q EXPECTED_HNS         = 8;
    const QTimeZone* EXPECTED_TIMEZONE = SQTimeZoneFactory::GetTimeZoneById(QE_L("Europe/Madrid"));
    const QDateTime EXPECTED_DATETIME(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                                      EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                                      EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                                      EXPECTED_TIMEZONE);

	// [Execution]
    QDateTime dateTime;
    dateTime = EXPECTED_DATETIME;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
    BOOST_CHECK(dateTime.GetTimeZone() == EXPECTED_DATETIME.GetTimeZone());
}

/// <summary>
/// Checks that undefined dates are copied.
/// </summary>
QTEST_CASE ( OperatorAssignment_UndefinedDateIsCopied_Test )
{
    // [Preparation]
    const u64_q EXPECTED_YEAR  = 2013;
    const u64_q EXPECTED_MONTH = 5;
    const u64_q EXPECTED_DAY   = 2;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;
    const QDateTime ORIGINAL_DATETIME(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                                      EXPECTED_TIMEZONE);
    const QDateTime UNDEFINED_DATETIME(QDateTime::GetUndefinedDate());

	// [Execution]
    QDateTime dateTime(ORIGINAL_DATETIME);
    dateTime = UNDEFINED_DATETIME;

    // [Verification]
    BOOST_CHECK(dateTime == UNDEFINED_DATETIME);
}

/// <summary>
/// Checks that a common time span is correctly added to a positive date.
/// </summary>
QTEST_CASE ( OperatorAdditionAssignment_CommonTimeSpanIsCorrectlyAddedToPositiveDate_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime ORIGINAL_DATETIME(100, 1, 3, 4, 6, 10, 100, 200, 5, null_q);
    const QTimeSpan INPUT_TIMESPAN(           2, 2, 2,  2,   2,   2, 2);
    const QDateTime EXPECTED_DATETIME(100, 1, 5, 6, 8, 12, 102, 202, 7, null_q);

	// [Execution]
    QDateTime dateTime(ORIGINAL_DATETIME);
    dateTime += INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that a common time span is correctly added to a negative date.
/// </summary>
QTEST_CASE ( OperatorAdditionAssignment_CommonTimeSpanIsCorrectlyAddedToNegativeDate_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime ORIGINAL_DATETIME(-100, 1, 3, 4, 6, 10, 100, 200, 5, null_q);
    const QTimeSpan INPUT_TIMESPAN(            2, 2, 2,  2,   2,   2, 2);
    const QDateTime EXPECTED_DATETIME(-100, 1, 5, 6, 8, 12, 102, 202, 7, null_q);

	// [Execution]
    QDateTime dateTime(ORIGINAL_DATETIME);
    dateTime += INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the operator returns the resident value.
/// </summary>
QTEST_CASE ( OperatorAdditionAssignment_ReturnsResidentValue_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime ORIGINAL_DATETIME(100, 1, 3, 4, 6, 10, 100, 200, 5, null_q);
    const QTimeSpan INPUT_TIMESPAN(           2, 2, 2,  2,   2,   2, 2);

	// [Execution]
    QDateTime dateTime(ORIGINAL_DATETIME);
    QDateTime& returnedValue = (dateTime += INPUT_TIMESPAN);

    // [Verification]
    BOOST_CHECK(&dateTime == &returnedValue);
}

/// <summary>
/// Checks that a time span is correctly added when passing through the year zero.
/// </summary>
QTEST_CASE ( OperatorAdditionAssignment_CommonTimeSpanIsCorrectlyAddedWhenPassingThroughYearZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime ORIGINAL_DATETIME(-1, 12, 30, 4, 6, 10, 100, 200, 5, null_q);
    const QTimeSpan INPUT_TIMESPAN(            2, 2, 2,  2,   2,   2, 2);
    const QDateTime EXPECTED_DATETIME( 1,  1,  1, 6, 8, 12, 102, 202, 7, null_q);

	// [Execution]
    QDateTime dateTime(ORIGINAL_DATETIME);
    dateTime += INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that a time span is correctly added when passing through the year zero (time span greater than 1 year).
/// </summary>
QTEST_CASE ( OperatorAdditionAssignment_CommonTimeSpanIsCorrectlyAddedWhenPassingThroughYearZeroMoreThanOneYear_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime ORIGINAL_DATETIME(-2, 12, 30, 4, 6, 10, 100, 200, 5, null_q);
    const QTimeSpan INPUT_TIMESPAN(          740, 2, 2,  2,   2,   2, 2); // +2 years
    const QDateTime EXPECTED_DATETIME( 2, 1,   9, 6, 8, 12, 102, 202, 7, null_q);

	// [Execution]
    QDateTime dateTime(ORIGINAL_DATETIME);
    dateTime += INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the resident date is undefined.
/// </summary>
QTEST_CASE ( OperatorAdditionAssignment_AssertionFailsWhenDateIsUndefined_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const QTimeSpan ANY_TIMESPAN(1);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(UNDEFINED_DATETIME);
        dateTime += ANY_TIMESPAN;
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the result of the sum exceeds the maximum date.
/// </summary>
QTEST_CASE ( OperatorAdditionAssignment_AssertionFailsWhenAdditionOverflowsAllowedMaximumValue_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime MAXIMUM_DATETIME = QDateTime::GetMaxDateTime();
    const QTimeSpan INPUT_TIMESPAN(1);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(MAXIMUM_DATETIME);
        dateTime += INPUT_TIMESPAN;
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that undefined dates do not change.
/// </summary>
QTEST_CASE ( OperatorAdditionAssignment_UndefinedDatesDoNotChange_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const QTimeSpan ANY_TIMESPAN(1);

	// [Execution]
    QDateTime dateTime(UNDEFINED_DATETIME);
    dateTime += ANY_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == UNDEFINED_DATETIME);
}

/// <summary>
/// Checks that the result is the maximum value when the result of the sum is greater than the maximum.
/// </summary>
QTEST_CASE ( OperatorAdditionAssignment_MaximumValueIsSetWhenAdditionOverflowsAllowedMaximumValue_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime MAXIMUM_DATETIME = QDateTime::GetMaxDateTime();
    const QTimeSpan INPUT_TIMESPAN(1);

	// [Execution]
    QDateTime dateTime(MAXIMUM_DATETIME);
    dateTime += INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == MAXIMUM_DATETIME);
}

#endif

/// <summary>
/// Checks that a common time span is correctly subtracted to a positive date.
/// </summary>
QTEST_CASE ( OperatorSubtractionAssignment_CommonTimeSpanIsCorrectlySubtractedToPositiveDate_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime ORIGINAL_DATETIME(100, 1, 5, 6, 8, 12, 102, 202, 7, null_q);
    const QTimeSpan INPUT_TIMESPAN(           2, 2, 2,  2,   2,   2, 2);
    const QDateTime EXPECTED_DATETIME(100, 1, 3, 4, 6, 10, 100, 200, 5, null_q);

	// [Execution]
    QDateTime dateTime(ORIGINAL_DATETIME);
    dateTime -= INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that a common time span is correctly subtracted to a negative date.
/// </summary>
QTEST_CASE ( OperatorSubtractionAssignment_CommonTimeSpanIsCorrectlySubtractedToNegativeDate_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime ORIGINAL_DATETIME(-100, 1, 5, 6, 8, 12, 102, 202, 7, null_q);
    const QTimeSpan INPUT_TIMESPAN(            2, 2, 2,  2,   2,   2, 2);
    const QDateTime EXPECTED_DATETIME(-100, 1, 3, 4, 6, 10, 100, 200, 5, null_q);

	// [Execution]
    QDateTime dateTime(ORIGINAL_DATETIME);
    dateTime -= INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the operator returns the resident value.
/// </summary>
QTEST_CASE ( OperatorSubtractionAssignment_ReturnsResidentValue_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime ORIGINAL_DATETIME(100, 1, 3, 4, 6, 10, 100, 200, 5, null_q);
    const QTimeSpan INPUT_TIMESPAN(           2, 2, 2,  2,   2,   2, 2);

	// [Execution]
    QDateTime dateTime(ORIGINAL_DATETIME);
    QDateTime& returnedValue = (dateTime -= INPUT_TIMESPAN);

    // [Verification]
    BOOST_CHECK(&dateTime == &returnedValue);
}

/// <summary>
/// Checks that a time span is correctly subtracted when passing through the year zero.
/// </summary>
QTEST_CASE ( OperatorSubtractionAssignment_CommonTimeSpanIsCorrectlySubtractedWhenPassingThroughYearZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime ORIGINAL_DATETIME( 1,  1,  1, 6, 8, 12, 102, 202, 7, null_q);
    const QTimeSpan INPUT_TIMESPAN(            2, 2, 2,  2,   2,   2, 2);
    const QDateTime EXPECTED_DATETIME(-1, 12, 30, 4, 6, 10, 100, 200, 5, null_q);

	// [Execution]
    QDateTime dateTime(ORIGINAL_DATETIME);
    dateTime -= INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that a time span is correctly subtracted when passing through the year zero (time span greater than 1 year).
/// </summary>
QTEST_CASE ( OperatorSubtractionAssignment_CommonTimeSpanIsCorrectlySubtractedWhenPassingThroughYearZeroMoreThanOneYear_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime ORIGINAL_DATETIME( 2, 1,   9, 6, 8, 12, 102, 202, 7, null_q);
    const QTimeSpan INPUT_TIMESPAN(          740, 2, 2,  2,   2,   2, 2); // +2 years
    const QDateTime EXPECTED_DATETIME(-2, 12, 30, 4, 6, 10, 100, 200, 5, null_q);

	// [Execution]
    QDateTime dateTime(ORIGINAL_DATETIME);
    dateTime -= INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the resident date is undefined.
/// </summary>
QTEST_CASE ( OperatorSubtractionAssignment_AssertionFailsWhenDateIsUndefined_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const QTimeSpan ANY_TIMESPAN(1);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(UNDEFINED_DATETIME);
        dateTime -= ANY_TIMESPAN;
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the result of the subtraction exceeds the minimum date.
/// </summary>
QTEST_CASE ( OperatorSubtractionAssignment_AssertionFailsWhenSubtractionOverflowsAllowedMinimumValue_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime MINIMUM_DATETIME = QDateTime::GetMinDateTime();
    const QTimeSpan INPUT_TIMESPAN(1);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime(MINIMUM_DATETIME);
        dateTime -= INPUT_TIMESPAN;
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that undefined dates do not change.
/// </summary>
QTEST_CASE ( OperatorSubtractionAssignment_UndefinedDatesDoNotChange_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const QTimeSpan ANY_TIMESPAN(1);

	// [Execution]
    QDateTime dateTime(UNDEFINED_DATETIME);
    dateTime -= ANY_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == UNDEFINED_DATETIME);
}

/// <summary>
/// Checks that the result is the minimum value when the result of the subtraction is lower than the minimum.
/// </summary>
QTEST_CASE ( OperatorSubtractionAssignment_MinimumValueIsSetWhenSubtractionOverflowsAllowedMinimumValue_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime MINIMUM_DATETIME = QDateTime::GetMinDateTime();
    const QTimeSpan INPUT_TIMESPAN(1);

	// [Execution]
    QDateTime dateTime(MINIMUM_DATETIME);
    dateTime -= INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == MINIMUM_DATETIME);
}

#endif

/// <summary>
/// Checks that a common time span is correctly added to a positive date.
/// </summary>
QTEST_CASE ( OperatorAddition_CommonTimeSpanIsCorrectlyAddedToPositiveDate_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime ORIGINAL_DATETIME(100, 1, 3, 4, 6, 10, 100, 200, 5, null_q);
    const QTimeSpan INPUT_TIMESPAN(           2, 2, 2,  2,   2,   2, 2);
    const QDateTime EXPECTED_DATETIME(100, 1, 5, 6, 8, 12, 102, 202, 7, null_q);

	// [Execution]
    QDateTime dateTime = ORIGINAL_DATETIME + INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that a common time span is correctly added to a negative date.
/// </summary>
QTEST_CASE ( OperatorAddition_CommonTimeSpanIsCorrectlyAddedToNegativeDate_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime ORIGINAL_DATETIME(-100, 1, 3, 4, 6, 10, 100, 200, 5, null_q);
    const QTimeSpan INPUT_TIMESPAN(            2, 2, 2,  2,   2,   2, 2);
    const QDateTime EXPECTED_DATETIME(-100, 1, 5, 6, 8, 12, 102, 202, 7, null_q);

	// [Execution]
    QDateTime dateTime = ORIGINAL_DATETIME + INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that a time span is correctly added when passing through the year zero.
/// </summary>
QTEST_CASE ( OperatorAddition_CommonTimeSpanIsCorrectlyAddedWhenPassingThroughYearZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime ORIGINAL_DATETIME(-1, 12, 30, 4, 6, 10, 100, 200, 5, null_q);
    const QTimeSpan INPUT_TIMESPAN(            2, 2, 2,  2,   2,   2, 2);
    const QDateTime EXPECTED_DATETIME( 1,  1,  1, 6, 8, 12, 102, 202, 7, null_q);

	// [Execution]
    QDateTime dateTime = ORIGINAL_DATETIME + INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that a time span is correctly added when passing through the year zero (time span greater than 1 year).
/// </summary>
QTEST_CASE ( OperatorAddition_CommonTimeSpanIsCorrectlyAddedWhenPassingThroughYearZeroMoreThanOneYear_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime ORIGINAL_DATETIME(-2, 12, 30, 4, 6, 10, 100, 200, 5, null_q);
    const QTimeSpan INPUT_TIMESPAN(          740, 2, 2,  2,   2,   2, 2); // +2 years
    const QDateTime EXPECTED_DATETIME( 2, 1,   9, 6, 8, 12, 102, 202, 7, null_q);

	// [Execution]
    QDateTime dateTime = ORIGINAL_DATETIME + INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the resident date is undefined.
/// </summary>
QTEST_CASE ( OperatorAddition_AssertionFailsWhenDateIsUndefined_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const QTimeSpan ANY_TIMESPAN(1);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime = UNDEFINED_DATETIME + ANY_TIMESPAN;
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the result of the sum exceeds the maximum date.
/// </summary>
QTEST_CASE ( OperatorAddition_AssertionFailsWhenAdditionOverflowsAllowedMaximumValue_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime MAXIMUM_DATETIME = QDateTime::GetMaxDateTime();
    const QTimeSpan INPUT_TIMESPAN(1);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime = MAXIMUM_DATETIME + INPUT_TIMESPAN;
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that undefined dates do not change.
/// </summary>
QTEST_CASE ( OperatorAddition_UndefinedDatesDoNotChange_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const QTimeSpan ANY_TIMESPAN(1);

	// [Execution]
    QDateTime dateTime = UNDEFINED_DATETIME + ANY_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == UNDEFINED_DATETIME);
}

/// <summary>
/// Checks that the result is the maximum value when the result of the sum is greater than the maximum.
/// </summary>
QTEST_CASE ( OperatorAddition_MaximumValueIsSetWhenAdditionOverflowsAllowedMaximumValue_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime MAXIMUM_DATETIME = QDateTime::GetMaxDateTime();
    const QTimeSpan INPUT_TIMESPAN(1);

	// [Execution]
    QDateTime dateTime = MAXIMUM_DATETIME + INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == MAXIMUM_DATETIME);
}

#endif

/// <summary>
/// Checks that a common time span is correctly subtracted to a positive date.
/// </summary>
QTEST_CASE ( OperatorSubtraction1_CommonTimeSpanIsCorrectlySubtractedToPositiveDate_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime ORIGINAL_DATETIME(100, 1, 5, 6, 8, 12, 102, 202, 7, null_q);
    const QTimeSpan INPUT_TIMESPAN(           2, 2, 2,  2,   2,   2, 2);
    const QDateTime EXPECTED_DATETIME(100, 1, 3, 4, 6, 10, 100, 200, 5, null_q);

	// [Execution]
    QDateTime dateTime = ORIGINAL_DATETIME - INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that a common time span is correctly subtracted to a negative date.
/// </summary>
QTEST_CASE ( OperatorSubtraction1_CommonTimeSpanIsCorrectlySubtractedToNegativeDate_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime ORIGINAL_DATETIME(-100, 1, 5, 6, 8, 12, 102, 202, 7, null_q);
    const QTimeSpan INPUT_TIMESPAN(            2, 2, 2,  2,   2,   2, 2);
    const QDateTime EXPECTED_DATETIME(-100, 1, 3, 4, 6, 10, 100, 200, 5, null_q);

	// [Execution]
    QDateTime dateTime = ORIGINAL_DATETIME - INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that a time span is correctly subtracted when passing through the year zero.
/// </summary>
QTEST_CASE ( OperatorSubtraction1_CommonTimeSpanIsCorrectlySubtractedWhenPassingThroughYearZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime ORIGINAL_DATETIME( 1,  1,  1, 6, 8, 12, 102, 202, 7, null_q);
    const QTimeSpan INPUT_TIMESPAN(            2, 2, 2,  2,   2,   2, 2);
    const QDateTime EXPECTED_DATETIME(-1, 12, 30, 4, 6, 10, 100, 200, 5, null_q);

	// [Execution]
    QDateTime dateTime = ORIGINAL_DATETIME - INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that a time span is correctly subtracted when passing through the year zero (time span greater than 1 year).
/// </summary>
QTEST_CASE ( OperatorSubtraction1_CommonTimeSpanIsCorrectlySubtractedWhenPassingThroughYearZeroMoreThanOneYear_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime ORIGINAL_DATETIME( 2, 1,   9, 6, 8, 12, 102, 202, 7, null_q);
    const QTimeSpan INPUT_TIMESPAN(          740, 2, 2,  2,   2,   2, 2); // +2 years
    const QDateTime EXPECTED_DATETIME(-2, 12, 30, 4, 6, 10, 100, 200, 5, null_q);

	// [Execution]
    QDateTime dateTime = ORIGINAL_DATETIME - INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the resident date is undefined.
/// </summary>
QTEST_CASE ( OperatorSubtraction1_AssertionFailsWhenDateIsUndefined_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const QTimeSpan ANY_TIMESPAN(1);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime = UNDEFINED_DATETIME - ANY_TIMESPAN;
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the result of the subtraction exceeds the minimum date.
/// </summary>
QTEST_CASE ( OperatorSubtraction1_AssertionFailsWhenSubtractionOverflowsAllowedMinimumValue_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime MINIMUM_DATETIME = QDateTime::GetMinDateTime();
    const QTimeSpan INPUT_TIMESPAN(1);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime dateTime = MINIMUM_DATETIME - INPUT_TIMESPAN;
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that undefined dates do not change.
/// </summary>
QTEST_CASE ( OperatorSubtraction1_UndefinedDatesDoNotChange_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const QTimeSpan ANY_TIMESPAN(1);

	// [Execution]
    QDateTime dateTime = UNDEFINED_DATETIME - ANY_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == UNDEFINED_DATETIME);
}

/// <summary>
/// Checks that the result is the minimum value when the result of the subtraction is lower than the minimum.
/// </summary>
QTEST_CASE ( OperatorSubtraction1_MinimumValueIsSetWhenSubtractionOverflowsAllowedMinimumValue_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime MINIMUM_DATETIME = QDateTime::GetMinDateTime();
    const QTimeSpan INPUT_TIMESPAN(1);

	// [Execution]
    QDateTime dateTime = MINIMUM_DATETIME - INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == MINIMUM_DATETIME);
}

#endif

/// <summary>
/// Checks that it returns the expected result when subtracting a negative date to a positive date. 
/// </summary>
QTEST_CASE ( OperatorSubtraction2_ReturnsExpectedTimeSpanWhenSubtractingNegativeDateToPositiveDate_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime LEFT_DATETIME(  2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime RIGHT_DATETIME(-2, 12, 30, 4, 6, 10, 100, 200, 5, null_q);
    const QTimeSpan EXPECTED_TIMESPAN(    740, 2, 2,  2,   2,   2, 2); // +2 years

	// [Execution]
    QTimeSpan result = LEFT_DATETIME - RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK(result == EXPECTED_TIMESPAN);
}

/// <summary>
/// Checks that it returns the expected result when subtracting a positive date to a negative date. 
/// </summary>
QTEST_CASE ( OperatorSubtraction2_ReturnsExpectedTimeSpanWhenSubtractingPositiveDateToNegativeDate_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME(2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME(-2, 12, 30, 4, 6, 10, 100, 200, 5, null_q);
    const QTimeSpan EXPECTED_TIMESPAN(   740, 2, 2,  2,   2,   2, 2); // +2 years

	// [Execution]
    QTimeSpan result = LEFT_DATETIME - RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK(result == EXPECTED_TIMESPAN);
}

/// <summary>
/// Checks that it returns zero when operands are equal. 
/// </summary>
QTEST_CASE ( OperatorSubtraction2_ReturnsZeroWhenOperandsAreEqual_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME(2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME(RIGHT_DATETIME);
    const QTimeSpan EXPECTED_TIMESPAN(0);

	// [Execution]
    QTimeSpan result = LEFT_DATETIME - RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK(result == EXPECTED_TIMESPAN);
}

/// <summary>
/// Checks that it returns the expected result when subtracting positive dates. 
/// </summary>
QTEST_CASE ( OperatorSubtraction2_ReturnsExpectedTimeSpanWhenSubtractingPositiveDates_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME(2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME( 2,  1,  9, 7, 9, 16, 102, 202, 7, null_q);
    const QTimeSpan EXPECTED_TIMESPAN(     0, 1, 1,  4,   0,   0, 0);

	// [Execution]
    QTimeSpan result = LEFT_DATETIME - RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK(result == EXPECTED_TIMESPAN);
}

/// <summary>
/// Checks that it returns the expected result when subtracting negative dates. 
/// </summary>
QTEST_CASE ( OperatorSubtraction2_ReturnsExpectedTimeSpanWhenSubtractingNegativeDates_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME(-2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME( -2,  1,  9, 7, 9, 16, 102, 202, 7, null_q);
    const QTimeSpan EXPECTED_TIMESPAN(      0, 1, 1,  4,   0,   0, 0);

	// [Execution]
    QTimeSpan result = LEFT_DATETIME - RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK(result == EXPECTED_TIMESPAN);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when dates are undefined.
/// </summary>
QTEST_CASE ( OperatorSubtraction2_AssertionFailsWhenDatesAreUndefined_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const QDateTime ANY_DATETIME(1, 1, 1);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        UNDEFINED_DATETIME - ANY_DATETIME;
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed1 = true;
    }
    
    bool bAssertionFailed2 = false;

    try
    {
        ANY_DATETIME - UNDEFINED_DATETIME;
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns zero when dates are undefined.
/// </summary>
QTEST_CASE ( OperatorSubtraction2_ReturnsZeroWhenDatesAreUndefined_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const QDateTime ANY_DATETIME(1, 1, 1);
    const QTimeSpan ZERO_TIMESPAN(0);

	// [Execution]
    QTimeSpan result1 = UNDEFINED_DATETIME - ANY_DATETIME;
    QTimeSpan result2 = ANY_DATETIME - UNDEFINED_DATETIME;

    // [Verification]
    BOOST_CHECK(result1 == ZERO_TIMESPAN);
    BOOST_CHECK(result2 == ZERO_TIMESPAN);
}

#endif

/// <summary>
/// Checks that time zones do not affect the result. 
/// </summary>
QTEST_CASE ( OperatorSubtraction2_TimeZoneDoesNotAffectTheResult_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME_UTC(2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME_UTC( 2,  1,  9, 7, 9, 16, 102, 202, 7, null_q);
    const QTimeSpan EXPECTED_TIMESPAN(         0, 1, 1,  4,   0,   0, 0);

    const QTimeZone* pTimeZone1 = SQTimeZoneFactory::GetTimeZoneById(QE_L("Europe/Madrid"));
    const QTimeZone* pTimeZone2 = SQTimeZoneFactory::GetTimeZoneById(QE_L("America/New_York"));

    const QDateTime RIGHT_DATETIME_WITH_TIMEZONE(RIGHT_DATETIME_UTC, pTimeZone1);
    const QDateTime LEFT_DATETIME_WITH_TIMEZONE(LEFT_DATETIME_UTC, pTimeZone2);

	// [Execution]
    QTimeSpan resultUTC = LEFT_DATETIME_WITH_TIMEZONE - RIGHT_DATETIME_WITH_TIMEZONE;
    QTimeSpan resultWithTimeZones = LEFT_DATETIME_WITH_TIMEZONE - RIGHT_DATETIME_WITH_TIMEZONE;

    // [Verification]
    BOOST_CHECK(resultUTC == EXPECTED_TIMESPAN);
    BOOST_CHECK(resultUTC == resultWithTimeZones);
}

/// <summary>
/// Checks that it returns True when operands are equal. 
/// </summary>
QTEST_CASE ( OperatorEquality_ReturnsTrueWhenOperandsAreEqual_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME(-2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME( -2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME == RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when operands are not equal. 
/// </summary>
QTEST_CASE ( OperatorEquality_ReturnsFalseWhenOperandsAreNotEqual_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME( 2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME( -2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_DATETIME == RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that time zones do not affect the result. 
/// </summary>
QTEST_CASE ( OperatorEquality_TimeZonesAreIgnored_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME_UTC(2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME_UTC( 2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);

    const QTimeZone* pTimeZone1 = SQTimeZoneFactory::GetTimeZoneById(QE_L("Europe/Madrid"));
    const QTimeZone* pTimeZone2 = SQTimeZoneFactory::GetTimeZoneById(QE_L("America/New_York"));

    const QDateTime RIGHT_DATETIME_WITH_TIMEZONE(RIGHT_DATETIME_UTC, pTimeZone1);
    const QDateTime LEFT_DATETIME_WITH_TIMEZONE(LEFT_DATETIME_UTC, pTimeZone2);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME_WITH_TIMEZONE == RIGHT_DATETIME_WITH_TIMEZONE;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when operands are equal. 
/// </summary>
QTEST_CASE ( OperatorInequality_ReturnsFalseWhenOperandsAreEqual_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME(-2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME( -2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_DATETIME != RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when operands are not equal. 
/// </summary>
QTEST_CASE ( OperatorInequality_ReturnsTrueWhenOperandsAreNotEqual_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME( 2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME( -2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME != RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that time zones do not affect the result. 
/// </summary>
QTEST_CASE ( OperatorInequality_TimeZonesAreIgnored_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME_UTC(2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME_UTC( 2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);

    const QTimeZone* pTimeZone1 = SQTimeZoneFactory::GetTimeZoneById(QE_L("Europe/Madrid"));
    const QTimeZone* pTimeZone2 = SQTimeZoneFactory::GetTimeZoneById(QE_L("America/New_York"));

    const QDateTime RIGHT_DATETIME_WITH_TIMEZONE(RIGHT_DATETIME_UTC, pTimeZone1);
    const QDateTime LEFT_DATETIME_WITH_TIMEZONE(LEFT_DATETIME_UTC, pTimeZone2);

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_DATETIME_WITH_TIMEZONE != RIGHT_DATETIME_WITH_TIMEZONE;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when input operand is less than or equal to resident operand when comparing negative dates. 
/// </summary>
QTEST_CASE ( OperatorLowerThan_ReturnsFalseWhenInputIsNotLesserThanResidentWhenComparingNegativeDates_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME(-2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME( -1,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_DATETIME < RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when input operand is less than or equal to resident operand when comparing positive dates. 
/// </summary>
QTEST_CASE ( OperatorLowerThan_ReturnsFalseWhenInputIsNotLesserThanResidentWhenComparingPositiveDates_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME(1,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME( 2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_DATETIME < RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when input operand is lower than resident operand when comparing negative dates. 
/// </summary>
QTEST_CASE ( OperatorLowerThan_ReturnsTrueWhenInputIsLesserThanResidentWhenComparingNegativeDates_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME(-2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME( -3,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME < RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when input operand is lower than resident operand when comparing positive dates. 
/// </summary>
QTEST_CASE ( OperatorLowerThan_ReturnsTrueWhenInputIsLesserThanResidentWhenComparingPositiveDates_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME(3,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME( 2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME < RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that time zones do not affect the result. 
/// </summary>
QTEST_CASE ( OperatorLowerThan_TimeZonesAreIgnored_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME_UTC(2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME_UTC( 2,  1,  9, 7, 8, 12, 102, 202, 7, null_q);

    const QTimeZone* pTimeZone1 = SQTimeZoneFactory::GetTimeZoneById(QE_L("Europe/Madrid"));
    const QTimeZone* pTimeZone2 = SQTimeZoneFactory::GetTimeZoneById(QE_L("America/New_York"));

    const QDateTime RIGHT_DATETIME_WITH_TIMEZONE(RIGHT_DATETIME_UTC, pTimeZone1);
    const QDateTime LEFT_DATETIME_WITH_TIMEZONE(LEFT_DATETIME_UTC, pTimeZone2);

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_DATETIME_WITH_TIMEZONE < RIGHT_DATETIME_WITH_TIMEZONE;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when dates are undefined.
/// </summary>
QTEST_CASE ( OperatorLowerThan_AssertionFailsWhenDatesAreUndefined_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const QDateTime ANY_DATETIME(1, 1, 1);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        UNDEFINED_DATETIME < ANY_DATETIME;
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed1 = true;
    }
    
    bool bAssertionFailed2 = false;

    try
    {
        ANY_DATETIME < UNDEFINED_DATETIME;
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that an it returns false when dates are undefined.
/// </summary>
QTEST_CASE ( OperatorLowerThan_ReturnsFalseWhenDatesAreUndefined_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const QDateTime ANY_DATETIME(1, 1, 1);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult1 = UNDEFINED_DATETIME < ANY_DATETIME;
    bool bResult2 = ANY_DATETIME < UNDEFINED_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns False when input operand is greater than or equal to resident operand when comparing negative dates. 
/// </summary>
QTEST_CASE ( OperatorGreaterThan_ReturnsFalseWhenInputIsNotGreaterThanResidentWhenComparingNegativeDates_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME(-2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME( -3,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_DATETIME > RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when input operand is greater than or equal to resident operand when comparing positive dates. 
/// </summary>
QTEST_CASE ( OperatorGreaterThan_ReturnsFalseWhenInputIsNotGreaterThanResidentWhenComparingPositiveDates_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME(2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME( 1,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_DATETIME > RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when input operand is greater than resident operand when comparing negative dates. 
/// </summary>
QTEST_CASE ( OperatorGreaterThan_ReturnsTrueWhenInputIsGreaterThanResidentWhenComparingNegativeDates_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME(-3,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME( -2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME > RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when input operand is greater than resident operand when comparing positive dates. 
/// </summary>
QTEST_CASE ( OperatorGreaterThan_ReturnsTrueWhenInputIsGreaterThanResidentWhenComparingPositiveDates_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME(2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME( 3,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME > RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that time zones do not affect the result. 
/// </summary>
QTEST_CASE ( OperatorGreaterThan_TimeZonesAreIgnored_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME_UTC(2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME_UTC( 2,  1,  9, 7, 8, 12, 102, 202, 7, null_q);

    const QTimeZone* pTimeZone1 = SQTimeZoneFactory::GetTimeZoneById(QE_L("Europe/Madrid"));
    const QTimeZone* pTimeZone2 = SQTimeZoneFactory::GetTimeZoneById(QE_L("America/New_York"));

    const QDateTime RIGHT_DATETIME_WITH_TIMEZONE(RIGHT_DATETIME_UTC, pTimeZone1);
    const QDateTime LEFT_DATETIME_WITH_TIMEZONE(LEFT_DATETIME_UTC, pTimeZone2);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME_WITH_TIMEZONE > RIGHT_DATETIME_WITH_TIMEZONE;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when dates are undefined.
/// </summary>
QTEST_CASE ( OperatorGreaterThan_AssertionFailsWhenDatesAreUndefined_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const QDateTime ANY_DATETIME(1, 1, 1);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        UNDEFINED_DATETIME > ANY_DATETIME;
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed1 = true;
    }
    
    bool bAssertionFailed2 = false;

    try
    {
        ANY_DATETIME > UNDEFINED_DATETIME;
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that an it returns false when dates are undefined.
/// </summary>
QTEST_CASE ( OperatorGreaterThan_ReturnsFalseWhenDatesAreUndefined_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const QDateTime ANY_DATETIME(1, 1, 1);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult1 = UNDEFINED_DATETIME > ANY_DATETIME;
    bool bResult2 = ANY_DATETIME > UNDEFINED_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns False when input operand is less than the resident operand when comparing negative dates. 
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_ReturnsFalseWhenInputIsNotLesserThanOrEqualToResidentWhenComparingNegativeDates_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME(-2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME( -1,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_DATETIME <= RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when input operand is less than the resident operand when comparing positive dates. 
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_ReturnsFalseWhenInputIsNotLesserThanOrEqualToResidentWhenComparingPositiveDates_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME(1,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME( 2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_DATETIME <= RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when input operand is lower than resident operand when comparing negative dates. 
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_ReturnsTrueWhenInputIsLesserThanResidentWhenComparingNegativeDates_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME(-2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME( -3,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME <= RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when input operand is lower than resident operand when comparing positive dates. 
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_ReturnsTrueWhenInputIsLesserThanResidentWhenComparingPositiveDates_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME(3,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME( 2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME <= RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when dates are equal. 
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_ReturnsTrueWhenDatesAreEqual_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME(2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME(RIGHT_DATETIME);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME <= RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when both dates are undefined. 
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_ReturnsTrueWhenBothDatesAreUndefined_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = UNDEFINED_DATETIME <= UNDEFINED_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that time zones do not affect the result. 
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_TimeZonesAreIgnored_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME_UTC(2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME_UTC( 2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);

    const QTimeZone* pTimeZone1 = SQTimeZoneFactory::GetTimeZoneById(QE_L("Europe/Madrid"));
    const QTimeZone* pTimeZone2 = SQTimeZoneFactory::GetTimeZoneById(QE_L("America/New_York"));

    const QDateTime RIGHT_DATETIME_WITH_TIMEZONE(RIGHT_DATETIME_UTC, pTimeZone1);
    const QDateTime LEFT_DATETIME_WITH_TIMEZONE(LEFT_DATETIME_UTC, pTimeZone2);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME_WITH_TIMEZONE <= RIGHT_DATETIME_WITH_TIMEZONE;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when only one of the dates is undefined.
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_AssertionFailsWhenOnlyOneDateIsUndefined_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const QDateTime ANY_DATETIME(1, 1, 1);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        UNDEFINED_DATETIME <= ANY_DATETIME;
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed1 = true;
    }
    
    bool bAssertionFailed2 = false;

    try
    {
        ANY_DATETIME <= UNDEFINED_DATETIME;
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that an it returns false when dates are undefined.
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_ReturnsFalseWhenDatesAreUndefined_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const QDateTime ANY_DATETIME(1, 1, 1);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult1 = UNDEFINED_DATETIME <= ANY_DATETIME;
    bool bResult2 = ANY_DATETIME <= UNDEFINED_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns False when input operand is greater than or equal to resident operand when comparing negative dates. 
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsFalseWhenInputIsNotGreaterThanResidentWhenComparingNegativeDates_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME(-2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME( -3,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_DATETIME >= RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when input operand is less than or equal to resident operand when comparing positive dates. 
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsFalseWhenInputIsNotGreaterThanResidentWhenComparingPositiveDates_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME(2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME( 1,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_DATETIME >= RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when input operand is greater than resident operand when comparing negative dates. 
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsTrueWhenInputIsGreaterThanResidentWhenComparingNegativeDates_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME(-3,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME( -2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME >= RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when input operand is greater than resident operand when comparing positive dates. 
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsTrueWhenInputIsGreaterThanResidentWhenComparingPositiveDates_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME(2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME( 3,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME >= RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when dates are equal. 
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsTrueWhenDatesAreEqual_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME(2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME(RIGHT_DATETIME);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME >= RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when both dates are undefined. 
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsTrueWhenBothDatesAreUndefined_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = UNDEFINED_DATETIME >= UNDEFINED_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that time zones do not affect the result. 
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_TimeZonesAreIgnored_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime RIGHT_DATETIME_UTC(2,  1,  9, 6, 8, 12, 102, 202, 7, null_q);
    const QDateTime LEFT_DATETIME_UTC( 2,  1,  9, 7, 8, 12, 102, 202, 7, null_q);

    const QTimeZone* pTimeZone1 = SQTimeZoneFactory::GetTimeZoneById(QE_L("Europe/Madrid"));
    const QTimeZone* pTimeZone2 = SQTimeZoneFactory::GetTimeZoneById(QE_L("America/New_York"));

    const QDateTime RIGHT_DATETIME_WITH_TIMEZONE(RIGHT_DATETIME_UTC, pTimeZone1);
    const QDateTime LEFT_DATETIME_WITH_TIMEZONE(LEFT_DATETIME_UTC, pTimeZone2);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME_WITH_TIMEZONE >= RIGHT_DATETIME_WITH_TIMEZONE;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when only one of the dates is undefined.
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_AssertionFailsWhenOnlyOneDateIsUndefined_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const QDateTime ANY_DATETIME(1, 1, 1);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        UNDEFINED_DATETIME >= ANY_DATETIME;
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed1 = true;
    }
    
    bool bAssertionFailed2 = false;

    try
    {
        ANY_DATETIME >= UNDEFINED_DATETIME;
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that an it returns false when dates are undefined.
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsFalseWhenDatesAreUndefined_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // [Preparation]
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const QDateTime ANY_DATETIME(1, 1, 1);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult1 = UNDEFINED_DATETIME >= ANY_DATETIME;
    bool bResult2 = ANY_DATETIME >= UNDEFINED_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns the expected number of days for the first month.
/// </summary>
QTEST_CASE ( GetDaysInMonth_ReturnsExpectedDaysForFirstMonth_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAYS = 31;
    const u64_q INPUT_MONTH          = 1;
    const i32_q INPUT_YEAR           = 1;

	// [Execution]
    unsigned int uDays = QDateTime::GetDaysInMonth(INPUT_MONTH, INPUT_YEAR);

    // [Verification]
    BOOST_CHECK_EQUAL(uDays, EXPECTED_DAYS);
}

/// <summary>
/// Checks that it returns the expected number of days for the last month.
/// </summary>
QTEST_CASE ( GetDaysInMonth_ReturnsExpectedDaysForLastMonth_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAYS = 31;
    const u64_q LAST_MONTH           = 12;
    const i32_q INPUT_YEAR           = 1;

	// [Execution]
    unsigned int uDays = QDateTime::GetDaysInMonth(LAST_MONTH, INPUT_YEAR);

    // [Verification]
    BOOST_CHECK_EQUAL(uDays, EXPECTED_DAYS);
}

/// <summary>
/// Checks that it returns 29 days when month is February and year is a leap year.
/// </summary>
QTEST_CASE ( GetDaysInMonth_Returns29DaysWhenMonthIsFebruaryAndYearIsLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAYS = 29;
    const u64_q FEBRUARY_MONTH       = 2;
    const i32_q LEAP_YEAR            = 4;

	// [Execution]
    unsigned int uDays = QDateTime::GetDaysInMonth(FEBRUARY_MONTH, LEAP_YEAR);

    // [Verification]
    BOOST_CHECK_EQUAL(uDays, EXPECTED_DAYS);
}

/// <summary>
/// Checks that it returns 28 days when month is February and year is not a leap year.
/// </summary>
QTEST_CASE ( GetDaysInMonth_Returns28DaysWhenMonthIsFebruaryAndYearIsNotLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAYS = 28;
    const u64_q FEBRUARY_MONTH       = 2;
    const i32_q NONLEAP_YEAR         = 1;

	// [Execution]
    unsigned int uDays = QDateTime::GetDaysInMonth(FEBRUARY_MONTH, NONLEAP_YEAR);

    // [Verification]
    BOOST_CHECK_EQUAL(uDays, EXPECTED_DAYS);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input month is not valid.
/// </summary>
QTEST_CASE ( GetDaysInMonth_AssertionFailsWhenMonthIsNotValid_Test )
{
    // [Preparation]
    const u64_q NOT_VALID_MONTH = 13;
    const i32_q INPUT_YEAR      = 1;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime::GetDaysInMonth(NOT_VALID_MONTH, INPUT_YEAR);
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that negative years start at menis zero (1 BC).
/// </summary>
QTEST_CASE ( ToString_NegativeYearsStartAtMinusZero_Test )
{
    // [Preparation]
    const QDateTime DATETIME(-1, 1, 1, 0, 0, 0, 0, 0, 0, null_q);
    const string_q EXPECTED_RESULT = "-0000-01-01T00:00:00Z";

	// [Execution]
    string_q strTimestamp = DATETIME.ToString();

    // [Verification]
    BOOST_CHECK(strTimestamp == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the timestamp is preceded by a negative sign when the date is negative.
/// </summary>
QTEST_CASE ( ToString_NegativeSignWhenYearIsNegative_Test )
{
    // [Preparation]
    const QDateTime DATETIME(-1234, 1, 1, 0, 0, 0, 0, 0, 0, null_q);
    const string_q EXPECTED_RESULT = "-1233-01-01T00:00:00Z";

	// [Execution]
    string_q strTimestamp = DATETIME.ToString();

    // [Verification]
    BOOST_CHECK(strTimestamp == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the timestamp is preceded by a positive sign when the date is positive.
/// </summary>
QTEST_CASE ( ToString_PositiveSignWhenYearIsPositive_Test )
{
    // [Preparation]
    const QDateTime DATETIME(1234, 1, 1, 0, 0, 0, 0, 0, 0, null_q);
    const string_q EXPECTED_RESULT = "+1234-01-01T00:00:00Z";

	// [Execution]
    string_q strTimestamp = DATETIME.ToString();

    // [Verification]
    BOOST_CHECK(strTimestamp == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the timestamp ends with a Z when the time is UTC.
/// </summary>
QTEST_CASE ( ToString_TimestampEndsWithZWhenTimeIsUtc_Test )
{
    // [Preparation]
    const QTimeZone* UTC_TZ = null_q;
    const QDateTime DATETIME(1234, 2, 11, 13, 14, 25, 0, 0, 0, UTC_TZ);
    const string_q EXPECTED_RESULT = "+1234-02-11T13:14:25Z";

	// [Execution]
    string_q strTimestamp = DATETIME.ToString();

    // [Verification]
    BOOST_CHECK(strTimestamp == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the date and time parts are correctly padded when they are formed by one number.
/// </summary>
QTEST_CASE ( ToString_DateAndTimePartsAreCorrectlyPaddedWhenTheyAreFormedByOneNumber_Test )
{
    // [Preparation]
    const QDateTime DATETIME(3, 2, 1, 4, 5, 6, 0, 0, 0, null_q);
    const string_q EXPECTED_RESULT = "+0003-02-01T04:05:06Z";

	// [Execution]
    string_q strTimestamp = DATETIME.ToString();

    // [Verification]
    BOOST_CHECK(strTimestamp == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the years formed of five numbers are correctly created.
/// </summary>
QTEST_CASE ( ToString_YearsOfFiveNumbersAreCorrectlyCreated_Test )
{
    // [Preparation]
    const QDateTime DATETIME(12345, 2, 1, 4, 5, 6, 0, 0, 0, null_q);
    const string_q EXPECTED_RESULT = "+12345-02-01T04:05:06Z";

	// [Execution]
    string_q strTimestamp = DATETIME.ToString();

    // [Verification]
    BOOST_CHECK(strTimestamp == EXPECTED_RESULT);
}

/// <summary>
/// Checks that only the necessary numbers of the time fraction are added to the timestamp.
/// </summary>
QTEST_CASE ( ToString_OnlyNecessaryFractionNumbersAreAddedToTimestamp_Test )
{
    // [Preparation]
    const QDateTime DATETIME(1, 1, 1, 0, 0, 0, 123, 400, 0, null_q);
    const string_q EXPECTED_RESULT = "+0001-01-01T00:00:00.1234Z";

	// [Execution]
    string_q strTimestamp = DATETIME.ToString();

    // [Verification]
    BOOST_CHECK(strTimestamp == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the fraction with maximum length is correctly created.
/// </summary>
QTEST_CASE ( ToString_TheMaximumFractionLengthIsCorrectlyCreated_Test )
{
    // [Preparation]
    const QDateTime DATETIME(1, 1, 1, 0, 0, 0, 123, 456, 7, null_q);
    const string_q EXPECTED_RESULT = "+0001-01-01T00:00:00.1234567Z";

	// [Execution]
    string_q strTimestamp = DATETIME.ToString();

    // [Verification]
    BOOST_CHECK(strTimestamp == EXPECTED_RESULT);
}

/// <summary>
/// Checks that no fraction is added when millisecond, microsecond and hundred of nanosecond equal zero.
/// </summary>
QTEST_CASE ( ToString_NoFractionIsAddedWhenMillisecondMicrosecondAndHundredOfNanosecondEqualZero_Test )
{
    // [Preparation]
    const QDateTime DATETIME(1, 1, 1, 0, 0, 0, 0, 0, 0, null_q);
    const string_q EXPECTED_RESULT = "+0001-01-01T00:00:00Z";

	// [Execution]
    string_q strTimestamp = DATETIME.ToString();

    // [Verification]
    BOOST_CHECK(strTimestamp == EXPECTED_RESULT);
}

/// <summary>
/// Checks that positive time offsets are correctly appended.
/// </summary>
QTEST_CASE ( ToString_PositiveOffsetAreCorrectlyAppended_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;

    // [Preparation]
    const QTimeZone* POSITIVE_TIMEZONE = SQTimeZoneFactory::GetTimeZoneById(QE_L("Asia/Calcutta")); // IST+5:30
    const QDateTime DATETIME(1, 1, 1, 0, 0, 0, 0, 0, 0, POSITIVE_TIMEZONE);
    const string_q EXPECTED_RESULT = "+0001-01-01T00:00:00+05:30";

	// [Execution]
    string_q strTimestamp = DATETIME.ToString();

    // [Verification]
    BOOST_CHECK(strTimestamp == EXPECTED_RESULT);
}

/// <summary>
/// Checks that negative time offsets are correctly appended.
/// </summary>
QTEST_CASE ( ToString_NegativeOffsetAreCorrectlyAppended_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;

    // [Preparation]
    const QTimeZone* NEGATIVE_TIMEZONE = SQTimeZoneFactory::GetTimeZoneById(QE_L("Pacific/Marquesas")); // MART-9:30
    const QDateTime DATETIME(1, 1, 1, 0, 0, 0, 0, 0, 0, NEGATIVE_TIMEZONE);
    const string_q EXPECTED_RESULT = "+0001-01-01T00:00:00-09:30";

	// [Execution]
    string_q strTimestamp = DATETIME.ToString();

    // [Verification]
    BOOST_CHECK(strTimestamp == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the year is a leap year.
/// </summary>
QTEST_CASE ( IsLeapYear_ReturnsTrueWhenYearIsLeapYear_Test )
{
    // [Preparation]
    const i32_q LEAP_YEAR    = 4;
    const u64_q COMMON_MONTH = 1;
    const u64_q COMMON_DAY   = 2;
    const QDateTime ORIGINAL_DATETIME(LEAP_YEAR, COMMON_MONTH, COMMON_DAY);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ORIGINAL_DATETIME.IsLeapYear();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the year is not a leap year.
/// </summary>
QTEST_CASE ( IsLeapYear_ReturnsFalseWhenYearIsNotLeapYear_Test )
{
    // [Preparation]
    const i32_q NONLEAP_YEAR = 100;
    const u64_q COMMON_MONTH = 1;
    const u64_q COMMON_DAY   = 2;
    const QDateTime ORIGINAL_DATETIME(NONLEAP_YEAR, COMMON_MONTH, COMMON_DAY);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ORIGINAL_DATETIME.IsLeapYear();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it is calculated using the local time.
/// </summary>
QTEST_CASE ( IsLeapYear_IsLocalTime_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;

    const bool EXPECTED_RESULT = false;
    const QTimeZone* EXPECTED_TIMEZONE = SQTimeZoneFactory::GetTimeZoneById(QE_L("America/Santiago")); // CLT-4
    const QDateTime SOURCE_DATETIME(1999, 12, 31, 23, 59, 59, 999, 999, 9, EXPECTED_TIMEZONE);
    const QDateTime SOURCE_DATETIME_UTC(SOURCE_DATETIME, null_q);

	// [Execution]
    bool bIsLeapLocal = SOURCE_DATETIME.IsLeapYear();
    bool bIsLeapUtc   = SOURCE_DATETIME_UTC.IsLeapYear();

    // [Verification]
    BOOST_CHECK_EQUAL(bIsLeapLocal, EXPECTED_RESULT);
    BOOST_CHECK_NE(bIsLeapLocal, bIsLeapUtc);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the date is undefined.
/// </summary>
QTEST_CASE ( IsLeapYear_AssertionFailsWhenDateIsUndefined_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QDateTime::GetUndefinedDate().IsLeapYear();
    }
    catch(...) // [TODO] Thund: Use the corresponding exception when it exists
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
QTEST_CASE ( GetTimeZone_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-05-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 4;
    const QDateTime SOURCE_DATETIME(EXPECTED_YEAR, 5, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-05-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 4;
    const QDateTime SOURCE_DATETIME(-scast_q(EXPECTED_YEAR, int), 5, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-02-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 4;
    const QDateTime SOURCE_DATETIME(EXPECTED_YEAR, 2, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-02-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 4;
    const QDateTime SOURCE_DATETIME(-scast_q(EXPECTED_YEAR, int), 2, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0001-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingFirstPositiveDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 1;
    const QDateTime SOURCE_DATETIME(EXPECTED_YEAR, 1, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0001-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 1;
    const QDateTime SOURCE_DATETIME(-scast_q(EXPECTED_YEAR, int), 1, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input year is multiple of 5.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenYearIsPositiveAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 25;
    const QDateTime SOURCE_DATETIME(EXPECTED_YEAR, 1, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input year is multiple of 5.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenYearIsNegativeAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 25;
    const QDateTime SOURCE_DATETIME(-scast_q(EXPECTED_YEAR, int), 1, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 29th of February.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 20;
    const QDateTime SOURCE_DATETIME(EXPECTED_YEAR, 2, 29, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 29th of February.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 20;
    const QDateTime SOURCE_DATETIME(-scast_q(EXPECTED_YEAR, int), 2, 29, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 28th of February.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 20;
    const QDateTime SOURCE_DATETIME(EXPECTED_YEAR, 2, 28, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 28th of February.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 20;
    const QDateTime SOURCE_DATETIME(-scast_q(EXPECTED_YEAR, int), 2, 28, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingLastNegativeInstant_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 1;
    const QDateTime SOURCE_DATETIME(-scast_q(EXPECTED_YEAR, int), 12, 31, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is 0001-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 1;
    const QDateTime SOURCE_DATETIME(EXPECTED_YEAR, 12, 31, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is 0012-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingFirstInstantOfPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 12;
    const QDateTime SOURCE_DATETIME(EXPECTED_YEAR, 1, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0012-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingFirstInstantOfNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 12;
    const QDateTime SOURCE_DATETIME(-scast_q(EXPECTED_YEAR, int), 1, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingFirstInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 4;
    const QDateTime SOURCE_DATETIME(EXPECTED_YEAR, 1, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 4;
    const QDateTime SOURCE_DATETIME(-scast_q(EXPECTED_YEAR, int), 1, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 4;
    const QDateTime SOURCE_DATETIME(EXPECTED_YEAR, 12, 31, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingLastInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 4;
    const QDateTime SOURCE_DATETIME(-scast_q(EXPECTED_YEAR, int), 12, 31, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is the maximum date and time allowed.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingMaximumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 29228;
    const QDateTime MAXIMUM_POSITIVE_DATETIME = QDateTime::GetMaxDateTime();

	// [Execution]
    unsigned int uYear = MAXIMUM_POSITIVE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is the minimum date and time allowed.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingMinimumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 29228;
    const QDateTime MAXIMUM_NEGATIVE_DATETIME = QDateTime::GetMinDateTime();

	// [Execution]
    unsigned int uYear = MAXIMUM_NEGATIVE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCase19960101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 1996;
    const QDateTime SOURCE_DATETIME(EXPECTED_YEAR, 1, 1, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCase19961231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 1996;
    const QDateTime SOURCE_DATETIME(EXPECTED_YEAR, 12, 31, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCase20001231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 2000;
    const QDateTime SOURCE_DATETIME(EXPECTED_YEAR, 12, 31, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCase20000101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 2000;
    const QDateTime SOURCE_DATETIME(EXPECTED_YEAR, 1, 1, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 00:00:00.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCase20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 2000;
    const QDateTime SOURCE_DATETIME(EXPECTED_YEAR, 1, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 12:00:00.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCase20000101T120000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 2000;
    const QDateTime SOURCE_DATETIME(EXPECTED_YEAR, 1, 1, 12, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCase19991231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 1999;
    const QDateTime SOURCE_DATETIME(EXPECTED_YEAR, 12, 31, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCase19991231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 1999;
    const QDateTime SOURCE_DATETIME(EXPECTED_YEAR, 12, 31, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 4;
    const QDateTime SOURCE_DATETIME(-scast_q(EXPECTED_YEAR, int), 1, 1, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-02 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCaseNegative00040102T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 4;
    const QDateTime SOURCE_DATETIME(-scast_q(EXPECTED_YEAR, int), 1, 2, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0003-01-01 00:00:00.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCaseNegative00030101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 3;
    const QDateTime SOURCE_DATETIME(-scast_q(EXPECTED_YEAR, int), 1, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.1.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 4;
    const QDateTime SOURCE_DATETIME(-scast_q(EXPECTED_YEAR, int), 1, 1, 0, 0, 0, 0, 0, 1, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0005-12-31 23:59:59.999.999.9..
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCaseNegative00051231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 5;
    const QDateTime SOURCE_DATETIME(-scast_q(EXPECTED_YEAR, int), 12, 31, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 23:59:59.999.999.9..
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 2000;
    const QDateTime SOURCE_DATETIME(-scast_q(EXPECTED_YEAR, int), 12, 31, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 00:00:00.000.000.1.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 2000;
    const QDateTime SOURCE_DATETIME(-scast_q(EXPECTED_YEAR, int), 12, 31, 0, 0, 0, 0, 0, 1, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-01-01 00:00:00.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCaseNegative20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 2000;
    const QDateTime SOURCE_DATETIME(-scast_q(EXPECTED_YEAR, int), 1, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCaseNegative00010101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 1;
    const QDateTime SOURCE_DATETIME(-scast_q(EXPECTED_YEAR, int), 1, 1, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-02 00:00:00.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCaseNegative00010102T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 1;
    const QDateTime SOURCE_DATETIME(-scast_q(EXPECTED_YEAR, int), 1, 2, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-30 00:00:00.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCaseNegative00011230T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 1;
    const QDateTime SOURCE_DATETIME(-scast_q(EXPECTED_YEAR, int), 12, 30, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCaseNegative00011231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 1;
    const QDateTime SOURCE_DATETIME(-scast_q(EXPECTED_YEAR, int), 12, 31, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it is local time.
/// </summary>
QTEST_CASE ( GetYear_IsLocalTime_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;

    const unsigned int EXPECTED_YEAR = 13;
    const QTimeZone* EXPECTED_TIMEZONE = SQTimeZoneFactory::GetTimeZoneById(QE_L("Atlantic/Azores")); // AZOT-1
    const QDateTime SOURCE_DATETIME(    EXPECTED_YEAR, 12, 31, 23, 59, 59, 999, 999, 9, EXPECTED_TIMEZONE);
    const QDateTime SOURCE_DATETIME_UTC(SOURCE_DATETIME, null_q);

	// [Execution]
    unsigned int uYearLocal = SOURCE_DATETIME.GetYear();
    unsigned int uYearUtc   = SOURCE_DATETIME_UTC.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYearLocal, EXPECTED_YEAR);
    BOOST_CHECK_NE(uYearLocal, uYearUtc);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the date/time is undefined
/// </summary>
QTEST_CASE ( GetYear_AssertionFailsWhenDateIsUndefined_Test )
{
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        UNDEFINED_DATETIME.GetYear();
    }
    catch(...) // [TODO] Thund: Use the concrete exception type when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-05-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 5;
    const QDateTime SOURCE_DATETIME(4, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-05-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 5;
    const QDateTime SOURCE_DATETIME(-4, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-02-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 2;
    const QDateTime SOURCE_DATETIME(4, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-02-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 2;
    const QDateTime SOURCE_DATETIME(-4, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0001-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingFirstPositiveDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const QDateTime SOURCE_DATETIME(1, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0001-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const QDateTime SOURCE_DATETIME(-1, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input year is multiple of 5.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenYearIsPositiveAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const QDateTime SOURCE_DATETIME(25, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input year is multiple of 5.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenYearIsNegativeAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const QDateTime SOURCE_DATETIME(-25, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 29th of February.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 2;
    const QDateTime SOURCE_DATETIME(20, EXPECTED_MONTH, 29, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 29th of February.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 2;
    const QDateTime SOURCE_DATETIME(-20, EXPECTED_MONTH, 29, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 28th of February.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 2;
    const QDateTime SOURCE_DATETIME(20, EXPECTED_MONTH, 28, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 28th of February.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 2;
    const QDateTime SOURCE_DATETIME(-20, EXPECTED_MONTH, 28, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingLastNegativeInstant_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 12;
    const QDateTime SOURCE_DATETIME(-1, EXPECTED_MONTH, 31, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is 0001-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 12;
    const QDateTime SOURCE_DATETIME(1, EXPECTED_MONTH, 31, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is 0012-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingFirstInstantOfPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const QDateTime SOURCE_DATETIME(12, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -0012-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingFirstInstantOfNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const QDateTime SOURCE_DATETIME(-12, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingFirstInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const QDateTime SOURCE_DATETIME(4, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const QDateTime SOURCE_DATETIME(-4, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 12;
    const QDateTime SOURCE_DATETIME(4, EXPECTED_MONTH, 31, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingLastInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 12;
    const QDateTime SOURCE_DATETIME(-4, EXPECTED_MONTH, 31, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is the maximum date and time allowed.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingMaximumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 9;
    const QDateTime MAXIMUM_POSITIVE_DATETIME = QDateTime::GetMaxDateTime();

	// [Execution]
    unsigned int uMonth = MAXIMUM_POSITIVE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is the minimum date and time allowed.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingMinimumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 4;
    const QDateTime MAXIMUM_NEGATIVE_DATETIME = QDateTime::GetMinDateTime();

	// [Execution]
    unsigned int uMonth = MAXIMUM_NEGATIVE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCase19960101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const QDateTime SOURCE_DATETIME(1996, EXPECTED_MONTH, 1, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCase19961231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 12;
    const QDateTime SOURCE_DATETIME(1996, EXPECTED_MONTH, 31, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCase20001231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 12;
    const QDateTime SOURCE_DATETIME(2000, EXPECTED_MONTH, 31, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCase20000101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const QDateTime SOURCE_DATETIME(2000, EXPECTED_MONTH, 1, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 00:00:00.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCase20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const QDateTime SOURCE_DATETIME(2000, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 12:00:00.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCase20000101T120000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const QDateTime SOURCE_DATETIME(2000, EXPECTED_MONTH, 1, 12, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCase19991231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 12;
    const QDateTime SOURCE_DATETIME(1999, EXPECTED_MONTH, 31, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCase19991231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 12;
    const QDateTime SOURCE_DATETIME(1999, EXPECTED_MONTH, 31, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const QDateTime SOURCE_DATETIME(-4, EXPECTED_MONTH, 1, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-02 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCaseNegative00040102T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const QDateTime SOURCE_DATETIME(-4, EXPECTED_MONTH, 2, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -0003-01-01 00:00:00.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCaseNegative00030101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const QDateTime SOURCE_DATETIME(-3, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.1.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const QDateTime SOURCE_DATETIME(-4, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 1, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -0005-12-31 23:59:59.999.999.9..
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCaseNegative00051231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 12;
    const QDateTime SOURCE_DATETIME(-5, EXPECTED_MONTH, 31, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 23:59:59.999.999.9..
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 12;
    const QDateTime SOURCE_DATETIME(-2000, EXPECTED_MONTH, 31, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 00:00:00.000.000.1.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 12;
    const QDateTime SOURCE_DATETIME(-2000, EXPECTED_MONTH, 31, 0, 0, 0, 0, 0, 1, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-01-01 00:00:00.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCaseNegative20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const QDateTime SOURCE_DATETIME(-2000, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCaseNegative00010101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const QDateTime SOURCE_DATETIME(-1, EXPECTED_MONTH, 1, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-02 00:00:00.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCaseNegative00010102T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const QDateTime SOURCE_DATETIME(-1, EXPECTED_MONTH, 2, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-30 00:00:00.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCaseNegative00011230T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 12;
    const QDateTime SOURCE_DATETIME(-1, EXPECTED_MONTH, 30, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCaseNegative00011231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 12;
    const QDateTime SOURCE_DATETIME(-1, EXPECTED_MONTH, 31, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it is local time.
/// </summary>
QTEST_CASE ( GetMonth_IsLocalTime_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;

    // [Preparation]
    const unsigned int EXPECTED_MONTH = 12;
    const QTimeZone* EXPECTED_TIMEZONE = SQTimeZoneFactory::GetTimeZoneById(QE_L("Atlantic/Azores")); // AZOT-1
    const QDateTime SOURCE_DATETIME(    12, EXPECTED_MONTH, 31, 23, 59, 59, 999, 999, 9, EXPECTED_TIMEZONE);
    const QDateTime SOURCE_DATETIME_UTC(SOURCE_DATETIME, null_q);

	// [Execution]
    unsigned int uMonthLocal = SOURCE_DATETIME.GetMonth();
    unsigned int uMonthUtc   = SOURCE_DATETIME_UTC.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonthLocal, EXPECTED_MONTH);
    BOOST_CHECK_NE(uMonthLocal, uMonthUtc);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the date/time is undefined.
/// </summary>
QTEST_CASE ( GetMonth_AssertionFailsWhenDateIsUndefined_Test )
{
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        UNDEFINED_DATETIME.GetMonth();
    }
    catch(...) // [TODO] Thund: Use the concrete exception type when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-05-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const QDateTime SOURCE_DATETIME(4, 5, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-05-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const QDateTime SOURCE_DATETIME(-4, 5, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-02-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const QDateTime SOURCE_DATETIME(4, 2, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-02-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const QDateTime SOURCE_DATETIME(-4, 2, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0001-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingFirstPositiveDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const QDateTime SOURCE_DATETIME(1, 1, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0001-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const QDateTime SOURCE_DATETIME(-1, 1, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input year is positive and multiple of 5.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenYearIsPositiveAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const QDateTime SOURCE_DATETIME(25, 1, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input year is negative and multiple of 5.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenYearIsNegativeAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const QDateTime SOURCE_DATETIME(-25, 1, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 29th of February.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 29;
    const QDateTime SOURCE_DATETIME(20, 2, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 29th of February.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 29;
    const QDateTime SOURCE_DATETIME(-20, 2, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 28th of February.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 28;
    const QDateTime SOURCE_DATETIME(20, 2, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 28th of February.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 28;
    const QDateTime SOURCE_DATETIME(-20, 2, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingLastNegativeInstant_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 31;
    const QDateTime SOURCE_DATETIME(-1, 12, EXPECTED_DAY, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is 0001-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 31;
    const QDateTime SOURCE_DATETIME(1, 12, EXPECTED_DAY, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is 0012-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingFirstInstantOfPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const QDateTime SOURCE_DATETIME(12, 1, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -0012-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingFirstInstantOfNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const QDateTime SOURCE_DATETIME(-12, 1, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingFirstInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const QDateTime SOURCE_DATETIME(4, 1, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const QDateTime SOURCE_DATETIME(-4, 1, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 31;
    const QDateTime SOURCE_DATETIME(4, 12, EXPECTED_DAY, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingLastInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 31;
    const QDateTime SOURCE_DATETIME(-4, 12, EXPECTED_DAY, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is the maximum date and time allowed.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingMaximumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 14;
    const QDateTime MAXIMUM_POSITIVE_DATETIME = QDateTime::GetMaxDateTime();

	// [Execution]
    unsigned int uDay = MAXIMUM_POSITIVE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is the minimum date and time allowed.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingMinimumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 18;
    const QDateTime MAXIMUM_NEGATIVE_DATETIME = QDateTime::GetMinDateTime();

	// [Execution]
    unsigned int uDay = MAXIMUM_NEGATIVE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCase19960101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const QDateTime SOURCE_DATETIME(1996, 1, EXPECTED_DAY, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCase19961231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 31;
    const QDateTime SOURCE_DATETIME(1996, 12, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCase20001231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 31;
    const QDateTime SOURCE_DATETIME(2000, 12, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCase20000101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const QDateTime SOURCE_DATETIME(2000, 1, EXPECTED_DAY, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 00:00:00.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCase20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const QDateTime SOURCE_DATETIME(2000, 1, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 12:00:00.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCase20000101T120000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const QDateTime SOURCE_DATETIME(2000, 1, EXPECTED_DAY, 12, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCase19991231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 31;
    const QDateTime SOURCE_DATETIME(1999, 12, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCase19991231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 31;
    const QDateTime SOURCE_DATETIME(1999, 12, EXPECTED_DAY, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const QDateTime SOURCE_DATETIME(-4, 1, EXPECTED_DAY, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-02 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCaseNegative00040102T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 2;
    const QDateTime SOURCE_DATETIME(-4, 1, EXPECTED_DAY, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -0003-01-01 00:00:00.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCaseNegative00030101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const QDateTime SOURCE_DATETIME(-3, 1, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.1.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const QDateTime SOURCE_DATETIME(-4, 1, EXPECTED_DAY, 0, 0, 0, 0, 0, 1, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -0005-12-31 23:59:59.999.999.9..
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCaseNegative00051231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 31;
    const QDateTime SOURCE_DATETIME(-5, 12, EXPECTED_DAY, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 23:59:59.999.999.9..
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 31;
    const QDateTime SOURCE_DATETIME(-2000, 12, EXPECTED_DAY, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 00:00:00.000.000.1.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 31;
    const QDateTime SOURCE_DATETIME(-2000, 12,EXPECTED_DAY, 0, 0, 0, 0, 0, 1, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-01-01 00:00:00.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCaseNegative20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const QDateTime SOURCE_DATETIME(-2000, 1, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCaseNegative00010101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const QDateTime SOURCE_DATETIME(-1, 1, EXPECTED_DAY, 23, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-02 00:00:00.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCaseNegative00010102T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 2;
    const QDateTime SOURCE_DATETIME(-1, 1, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-30 00:00:00.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCaseNegative00011230T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 30;
    const QDateTime SOURCE_DATETIME(-1, 12, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCaseNegative00011231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 31;
    const QDateTime SOURCE_DATETIME(-1, 12, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it is local time.
/// </summary>
QTEST_CASE ( GetDay_IsLocalTime_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;

    // [Preparation]
    const unsigned int EXPECTED_DAY = 31;
    const QTimeZone* EXPECTED_TIMEZONE = SQTimeZoneFactory::GetTimeZoneById(QE_L("Atlantic/Azores")); // AZOT-1
    const QDateTime SOURCE_DATETIME(    12, 12, 31, 23, 59, 59, 999, 999, 9, EXPECTED_TIMEZONE);
    const QDateTime SOURCE_DATETIME_UTC(SOURCE_DATETIME, null_q);

	// [Execution]
    unsigned int uDayLocal = SOURCE_DATETIME.GetDay();
    unsigned int uDayUtc   = SOURCE_DATETIME_UTC.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDayLocal, EXPECTED_DAY);
    BOOST_CHECK_NE(uDayLocal, uDayUtc);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the date/time is undefined.
/// </summary>
QTEST_CASE ( GetDay_AssertionFailsWhenDateIsUndefined_Test )
{
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        UNDEFINED_DATETIME.GetDay();
    }
    catch(...) // [TODO] Thund: Use the concrete exception type when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-05-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const QDateTime SOURCE_DATETIME(4, 5, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-05-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const QDateTime SOURCE_DATETIME(-4, 5, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-02-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const QDateTime SOURCE_DATETIME(4, 2, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-02-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const QDateTime SOURCE_DATETIME(-4, 2, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0001-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingFirstPositiveDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const QDateTime SOURCE_DATETIME(1, 1, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0001-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const QDateTime SOURCE_DATETIME(-1, 1, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input year is multiple of 5.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenYearIsPositiveAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const QDateTime SOURCE_DATETIME(25, 1, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input year is multiple of 5.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenYearIsNegativeAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const QDateTime SOURCE_DATETIME(-25, 1, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 29th of February.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const QDateTime SOURCE_DATETIME(20, 2, 29, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 29th of February.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const QDateTime SOURCE_DATETIME(-20, 2, 29, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 28th of February.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const QDateTime SOURCE_DATETIME(20, 2, 28, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 28th of February.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const QDateTime SOURCE_DATETIME(-20, 2, 28, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingLastNegativeInstant_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 23;
    const QDateTime SOURCE_DATETIME(-1, 12, 31, EXPECTED_HOUR, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is 0001-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 23;
    const QDateTime SOURCE_DATETIME(1, 12, 31, EXPECTED_HOUR, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is 0012-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingFirstInstantOfPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const QDateTime SOURCE_DATETIME(12, 1, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0012-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingFirstInstantOfNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const QDateTime SOURCE_DATETIME(-12, 1, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingFirstInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const QDateTime SOURCE_DATETIME(4, 1, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const QDateTime SOURCE_DATETIME(-4, 1, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 23;
    const QDateTime SOURCE_DATETIME(4, 12, 31, EXPECTED_HOUR, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingLastInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 23;
    const QDateTime SOURCE_DATETIME(-4, 12, 31, EXPECTED_HOUR, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is the maximum date and time allowed.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingMaximumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 2;
    const QDateTime MAXIMUM_POSITIVE_DATETIME = QDateTime::GetMaxDateTime();

	// [Execution]
    unsigned int uHour = MAXIMUM_POSITIVE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is the minimum date and time allowed.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingMinimumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 21;
    const QDateTime MAXIMUM_NEGATIVE_DATETIME = QDateTime::GetMinDateTime();

	// [Execution]
    unsigned int uHour = MAXIMUM_NEGATIVE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCase19960101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 23;
    const QDateTime SOURCE_DATETIME(1996, 1, 1, EXPECTED_HOUR, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCase19961231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const QDateTime SOURCE_DATETIME(1996, 12, 31, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCase20001231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const QDateTime SOURCE_DATETIME(2000, 12, 31, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCase20000101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 23;
    const QDateTime SOURCE_DATETIME(2000, 1, 1, EXPECTED_HOUR, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 00:00:00.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCase20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const QDateTime SOURCE_DATETIME(2000, 1, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 12:00:00.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCase20000101T120000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 12;
    const QDateTime SOURCE_DATETIME(2000, 1, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCase19991231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const QDateTime SOURCE_DATETIME(1999, 12, 31, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCase19991231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 23;
    const QDateTime SOURCE_DATETIME(1999, 12, 31, EXPECTED_HOUR, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 23;
    const QDateTime SOURCE_DATETIME(-4, 1, 1, EXPECTED_HOUR, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-02 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCaseNegative00040102T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 23;
    const QDateTime SOURCE_DATETIME(-4, 1, 2, EXPECTED_HOUR, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0003-01-01 00:00:00.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCaseNegative00030101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const QDateTime SOURCE_DATETIME(-3, 1, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.1.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const QDateTime SOURCE_DATETIME(-4, 1, 1, EXPECTED_HOUR, 0, 0, 0, 0, 1, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0005-12-31 23:59:59.999.999.9..
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCaseNegative00051231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 23;
    const QDateTime SOURCE_DATETIME(-5, 12, 31, EXPECTED_HOUR, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 23:59:59.999.999.9..
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 23;
    const QDateTime SOURCE_DATETIME(-2000, 12, 31, EXPECTED_HOUR, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 00:00:00.000.000.1.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const QDateTime SOURCE_DATETIME(-2000, 12, 31, EXPECTED_HOUR, 0, 0, 0, 0, 1, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-01-01 00:00:00.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCaseNegative20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const QDateTime SOURCE_DATETIME(-2000, 1, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCaseNegative00010101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 23;
    const QDateTime SOURCE_DATETIME(-1, 1, 1, EXPECTED_HOUR, 59, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-02 00:00:00.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCaseNegative00010102T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const QDateTime SOURCE_DATETIME(-1, 1, 2, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-30 00:00:00.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCaseNegative00011230T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const QDateTime SOURCE_DATETIME(-1, 12, 30, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCaseNegative00011231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const QDateTime SOURCE_DATETIME(-1, 12, 31, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it is local time.
/// </summary>
QTEST_CASE ( GetHour_IsLocalTime_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;

    // [Preparation]
    const unsigned int EXPECTED_HOUR = 1;
    const QTimeZone* EXPECTED_TIMEZONE = SQTimeZoneFactory::GetTimeZoneById(QE_L("Atlantic/Azores")); // AZOT-1
    const QDateTime SOURCE_DATETIME(    12, 12, 31, EXPECTED_HOUR, 59, 59, 999, 999, 9, EXPECTED_TIMEZONE);
    const QDateTime SOURCE_DATETIME_UTC(SOURCE_DATETIME, null_q);

	// [Execution]
    unsigned int uHourLocal = SOURCE_DATETIME.GetHour();
    unsigned int uHourUtc   = SOURCE_DATETIME_UTC.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHourLocal, EXPECTED_HOUR);
    BOOST_CHECK_NE(uHourLocal, uHourUtc);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the date/time is undefined.
/// </summary>
QTEST_CASE ( GetHour_AssertionFailsWhenDateIsUndefined_Test )
{
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        UNDEFINED_DATETIME.GetHour();
    }
    catch(...) // [TODO] Thund: Use the concrete exception type when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-05-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const QDateTime SOURCE_DATETIME(4, 5, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-05-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const QDateTime SOURCE_DATETIME(-4, 5, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-02-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const QDateTime SOURCE_DATETIME(4, 2, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-02-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const QDateTime SOURCE_DATETIME(-4, 2, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0001-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingFirstPositiveDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const QDateTime SOURCE_DATETIME(1, 1, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0001-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const QDateTime SOURCE_DATETIME(-1, 1, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input year is multiple of 5.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenYearIsPositiveAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const QDateTime SOURCE_DATETIME(25, 1, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input year is multiple of 5.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenYearIsNegativeAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const QDateTime SOURCE_DATETIME(-25, 1, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 29th of February.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const QDateTime SOURCE_DATETIME(20, 2, 29, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 29th of February.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const QDateTime SOURCE_DATETIME(-20, 2, 29, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 28th of February.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const QDateTime SOURCE_DATETIME(20, 2, 28, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 28th of February.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const QDateTime SOURCE_DATETIME(-20, 2, 28, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingLastNegativeInstant_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 59;
    const QDateTime SOURCE_DATETIME(-1, 12, 31, 23, EXPECTED_MINUTE, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is 0001-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 59;
    const QDateTime SOURCE_DATETIME(1, 12, 31, 23, EXPECTED_MINUTE, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is 0012-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingFirstInstantOfPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const QDateTime SOURCE_DATETIME(12, 1, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -0012-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingFirstInstantOfNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const QDateTime SOURCE_DATETIME(-12, 1, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingFirstInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const QDateTime SOURCE_DATETIME(4, 1, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const QDateTime SOURCE_DATETIME(-4, 1, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 59;
    const QDateTime SOURCE_DATETIME(4, 12, 31, 23, EXPECTED_MINUTE, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingLastInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 59;
    const QDateTime SOURCE_DATETIME(-4, 12, 31, 23, EXPECTED_MINUTE, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is the maximum date and time allowed.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingMaximumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 48;
    const QDateTime MAXIMUM_POSITIVE_DATETIME = QDateTime::GetMaxDateTime();

	// [Execution]
    unsigned int uMinute = MAXIMUM_POSITIVE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is the minimum date and time allowed.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingMinimumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 11;
    const QDateTime MAXIMUM_NEGATIVE_DATETIME = QDateTime::GetMinDateTime();

	// [Execution]
    unsigned int uMinute = MAXIMUM_NEGATIVE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCase19960101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 59;
    const QDateTime SOURCE_DATETIME(1996, 1, 1, 23, EXPECTED_MINUTE, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCase19961231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const QDateTime SOURCE_DATETIME(1996, 12, 31, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCase20001231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const QDateTime SOURCE_DATETIME(2000, 12, 31, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCase20000101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 59;
    const QDateTime SOURCE_DATETIME(2000, 1, 1, 23, EXPECTED_MINUTE, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 00:00:00.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCase20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const QDateTime SOURCE_DATETIME(2000, 1, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 12:00:00.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCase20000101T120000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const QDateTime SOURCE_DATETIME(2000, 1, 1, 12, EXPECTED_MINUTE, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCase19991231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const QDateTime SOURCE_DATETIME(1999, 12, 31, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCase19991231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 59;
    const QDateTime SOURCE_DATETIME(1999, 12, 31, 23, EXPECTED_MINUTE, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 59;
    const QDateTime SOURCE_DATETIME(-4, 1, 1, 23, EXPECTED_MINUTE, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-02 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCaseNegative00040102T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 59;
    const QDateTime SOURCE_DATETIME(-4, 1, 2, 23, EXPECTED_MINUTE, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -0003-01-01 00:00:00.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCaseNegative00030101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const QDateTime SOURCE_DATETIME(-3, 1, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.1.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const QDateTime SOURCE_DATETIME(-4, 1, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 1, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -0005-12-31 23:59:59.999.999.9..
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCaseNegative00051231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 59;
    const QDateTime SOURCE_DATETIME(-5, 12, 31, 23, EXPECTED_MINUTE, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 23:59:59.999.999.9..
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 59;
    const QDateTime SOURCE_DATETIME(-2000, 12, 31, 23, EXPECTED_MINUTE, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 00:00:00.000.000.1.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const QDateTime SOURCE_DATETIME(-2000, 12, 31, 0, EXPECTED_MINUTE, 0, 0, 0, 1, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-01-01 00:00:00.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCaseNegative20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const QDateTime SOURCE_DATETIME(-2000, 1, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCaseNegative00010101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 59;
    const QDateTime SOURCE_DATETIME(-1, 1, 1, 23, EXPECTED_MINUTE, 59, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-02 00:00:00.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCaseNegative00010102T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const QDateTime SOURCE_DATETIME(-1, 1, 2, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-30 00:00:00.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCaseNegative00011230T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const QDateTime SOURCE_DATETIME(-1, 12, 30, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCaseNegative00011231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const QDateTime SOURCE_DATETIME(-1, 12, 31, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it is local time.
/// </summary>
QTEST_CASE ( GetMinute_IsLocalTime_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;

    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 59;
    const QTimeZone* EXPECTED_TIMEZONE = SQTimeZoneFactory::GetTimeZoneById(QE_L("Pacific/Marquesas")); // MART-9:30
    const QDateTime SOURCE_DATETIME(    12, 12, 31, 10, EXPECTED_MINUTE, 59, 999, 999, 9, EXPECTED_TIMEZONE);
    const QDateTime SOURCE_DATETIME_UTC(SOURCE_DATETIME, null_q);

	// [Execution]
    unsigned int uMinuteLocal = SOURCE_DATETIME.GetMinute();
    unsigned int uMinuteUtc   = SOURCE_DATETIME_UTC.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinuteLocal, EXPECTED_MINUTE);
    BOOST_CHECK_NE(uMinuteLocal, uMinuteUtc);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the date/time is undefined.
/// </summary>
QTEST_CASE ( GetMinute_AssertionFailsWhenDateIsUndefined_Test )
{
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        UNDEFINED_DATETIME.GetMinute();
    }
    catch(...) // [TODO] Thund: Use the concrete exception type when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-05-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const QDateTime SOURCE_DATETIME(4, 5, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-05-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const QDateTime SOURCE_DATETIME(-4, 5, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-02-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const QDateTime SOURCE_DATETIME(4, 2, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-02-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const QDateTime SOURCE_DATETIME(-4, 2, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0001-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingFirstPositiveDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const QDateTime SOURCE_DATETIME(1, 1, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0001-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const QDateTime SOURCE_DATETIME(-1, 1, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input year is multiple of 5.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenYearIsPositiveAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const QDateTime SOURCE_DATETIME(25, 1, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input year is multiple of 5.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenYearIsNegativeAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const QDateTime SOURCE_DATETIME(-25, 1, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 29th of February.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const QDateTime SOURCE_DATETIME(20, 2, 29, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 29th of February.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const QDateTime SOURCE_DATETIME(-20, 2, 29, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 28th of February.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const QDateTime SOURCE_DATETIME(20, 2, 28, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 28th of February.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const QDateTime SOURCE_DATETIME(-20, 2, 28, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingLastNegativeInstant_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 59;
    const QDateTime SOURCE_DATETIME(-1, 12, 31, 23, 59, EXPECTED_SECOND, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0001-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 59;
    const QDateTime SOURCE_DATETIME(1, 12, 31, 23, 59, EXPECTED_SECOND, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0012-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingFirstInstantOfPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const QDateTime SOURCE_DATETIME(12, 1, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0012-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingFirstInstantOfNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const QDateTime SOURCE_DATETIME(-12, 1, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingFirstInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const QDateTime SOURCE_DATETIME(4, 1, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const QDateTime SOURCE_DATETIME(-4, 1, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 59;
    const QDateTime SOURCE_DATETIME(4, 12, 31, 23, 59, EXPECTED_SECOND, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingLastInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 59;
    const QDateTime SOURCE_DATETIME(-4, 12, 31, 23, 59, EXPECTED_SECOND, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is the maximum date and time allowed.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingMaximumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 5;
    const QDateTime MAXIMUM_POSITIVE_DATETIME = QDateTime::GetMaxDateTime();

	// [Execution]
    unsigned int uSecond = MAXIMUM_POSITIVE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is the minimum date and time allowed.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingMinimumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 54;
    const QDateTime MAXIMUM_NEGATIVE_DATETIME = QDateTime::GetMinDateTime();

	// [Execution]
    unsigned int uSecond = MAXIMUM_NEGATIVE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCase19960101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 59;
    const QDateTime SOURCE_DATETIME(1996, 1, 1, 23, 59, EXPECTED_SECOND, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCase19961231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const QDateTime SOURCE_DATETIME(1996, 12, 31, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCase20001231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const QDateTime SOURCE_DATETIME(2000, 12, 31, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCase20000101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 59;
    const QDateTime SOURCE_DATETIME(2000, 1, 1, 23, 59, EXPECTED_SECOND, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 00:00:00.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCase20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const QDateTime SOURCE_DATETIME(2000, 1, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 12:00:00.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCase20000101T120000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const QDateTime SOURCE_DATETIME(2000, 1, 1, 12, 0, EXPECTED_SECOND, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCase19991231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const QDateTime SOURCE_DATETIME(1999, 12, 31, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCase19991231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 59;
    const QDateTime SOURCE_DATETIME(1999, 12, 31, 23, 59, EXPECTED_SECOND, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 59;
    const QDateTime SOURCE_DATETIME(-4, 1, 1, 23, 59, EXPECTED_SECOND, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-02 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00040102T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 59;
    const QDateTime SOURCE_DATETIME(-4, 1, 2, 23, 59, EXPECTED_SECOND, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0003-01-01 00:00:00.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00030101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const QDateTime SOURCE_DATETIME(-3, 1, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.1.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const QDateTime SOURCE_DATETIME(-4, 1, 1, 0, 0, EXPECTED_SECOND, 0, 0, 1, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0005-12-31 23:59:59.999.999.9..
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00051231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 59;
    const QDateTime SOURCE_DATETIME(-5, 12, 31, 23, 59, EXPECTED_SECOND, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 23:59:59.999.999.9..
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 59;
    const QDateTime SOURCE_DATETIME(-2000, 12, 31, 23, 59, EXPECTED_SECOND, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 00:00:00.000.000.1.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const QDateTime SOURCE_DATETIME(-2000, 12, 31, 0, 0, EXPECTED_SECOND, 0, 0, 1, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-01-01 00:00:00.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCaseNegative20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const QDateTime SOURCE_DATETIME(-2000, 1, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00010101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 59;
    const QDateTime SOURCE_DATETIME(-1, 1, 1, 23, 59, EXPECTED_SECOND, 999, 999, 9, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-02 00:00:00.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00010102T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const QDateTime SOURCE_DATETIME(-1, 1, 2, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-30 00:00:00.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00011230T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const QDateTime SOURCE_DATETIME(-1, 12, 30, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00011231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const QDateTime SOURCE_DATETIME(-1, 12, 31, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_q);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the date/time is undefined.
/// </summary>
QTEST_CASE ( GetSecond_AssertionFailsWhenDateIsUndefined_Test )
{
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        UNDEFINED_DATETIME.GetSecond();
    }
    catch(...) // [TODO] Thund: Use the concrete exception type when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-05-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const QDateTime SOURCE_DATETIME(4, 5, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-05-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const QDateTime SOURCE_DATETIME(-4, 5, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-02-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const QDateTime SOURCE_DATETIME(4, 2, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-02-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const QDateTime SOURCE_DATETIME(-4, 2, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0001-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingFirstPositiveDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const QDateTime SOURCE_DATETIME(1, 1, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0001-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const QDateTime SOURCE_DATETIME(-1, 1, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input year is positive and multiple of 5.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenYearIsPositiveAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const QDateTime SOURCE_DATETIME(25, 1, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input year is negative and multiple of 5.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenYearIsNegativeAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const QDateTime SOURCE_DATETIME(-25, 1, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 29th of February.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const QDateTime SOURCE_DATETIME(20, 2, 29, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 29th of February.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const QDateTime SOURCE_DATETIME(-20, 2, 29, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 28th of February.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const QDateTime SOURCE_DATETIME(20, 2, 28, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 28th of February.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const QDateTime SOURCE_DATETIME(-20, 2, 28, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingLastNegativeInstant_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 999;
    const QDateTime SOURCE_DATETIME(-1, 12, 31, 23, 59, 59, EXPECTED_MILLISECOND, 999, 9, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0001-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 999;
    const QDateTime SOURCE_DATETIME(1, 12, 31, 23, 59, 59, EXPECTED_MILLISECOND, 999, 9, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0012-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingFirstInstantOfPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const QDateTime SOURCE_DATETIME(12, 1, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0012-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingFirstInstantOfNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const QDateTime SOURCE_DATETIME(-12, 1, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingFirstInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const QDateTime SOURCE_DATETIME(4, 1, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const QDateTime SOURCE_DATETIME(-4, 1, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 999;
    const QDateTime SOURCE_DATETIME(4, 12, 31, 23, 59, 59, EXPECTED_MILLISECOND, 999, 9, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingLastInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 999;
    const QDateTime SOURCE_DATETIME(-4, 12, 31, 23, 59, 59, EXPECTED_MILLISECOND, 999, 9, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is the maximum date and time allowed.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingMaximumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 477;
    const QDateTime MAXIMUM_POSITIVE_DATETIME = QDateTime::GetMaxDateTime();

	// [Execution]
    unsigned int uMillisecond = MAXIMUM_POSITIVE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is the minimum date and time allowed.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingMinimumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 522;
    const QDateTime MAXIMUM_NEGATIVE_DATETIME = QDateTime::GetMinDateTime();

	// [Execution]
    unsigned int uMillisecond = MAXIMUM_NEGATIVE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCase19960101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 999;
    const QDateTime SOURCE_DATETIME(1996, 1, 1, 23, 59, 59, EXPECTED_MILLISECOND, 999, 9, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCase19961231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const QDateTime SOURCE_DATETIME(1996, 12, 31, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCase20001231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const QDateTime SOURCE_DATETIME(2000, 12, 31, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCase20000101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 999;
    const QDateTime SOURCE_DATETIME(2000, 1, 1, 23, 59, 59, EXPECTED_MILLISECOND, 999, 9, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 00:00:00.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCase20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const QDateTime SOURCE_DATETIME(2000, 1, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 12:00:00.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCase20000101T120000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const QDateTime SOURCE_DATETIME(2000, 1, 1, 12, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCase19991231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const QDateTime SOURCE_DATETIME(1999, 12, 31, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCase19991231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 999;
    const QDateTime SOURCE_DATETIME(1999, 12, 31, 23, 59, 59, EXPECTED_MILLISECOND, 999, 9, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 999;
    const QDateTime SOURCE_DATETIME(-4, 1, 1, 23, 59, 59, EXPECTED_MILLISECOND, 999, 9, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-02 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00040102T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 999;
    const QDateTime SOURCE_DATETIME(-4, 1, 2, 23, 59, 59, EXPECTED_MILLISECOND, 999, 9, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0003-01-01 00:00:00.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00030101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const QDateTime SOURCE_DATETIME(-3, 1, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.1.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const QDateTime SOURCE_DATETIME(-4, 1, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 1, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0005-12-31 23:59:59.999.999.9..
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00051231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 999;
    const QDateTime SOURCE_DATETIME(-5, 12, 31, 23, 59, 59, EXPECTED_MILLISECOND, 999, 9, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 23:59:59.999.999.9..
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 999;
    const QDateTime SOURCE_DATETIME(-2000, 12, 31, 23, 59, 59, EXPECTED_MILLISECOND, 999, 9, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 00:00:00.000.000.1.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const QDateTime SOURCE_DATETIME(-2000, 12, 31, 0, 0, 0, EXPECTED_MILLISECOND, 0, 1, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-01-01 00:00:00.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCaseNegative20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const QDateTime SOURCE_DATETIME(-2000, 1, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00010101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 999;
    const QDateTime SOURCE_DATETIME(-1, 1, 1, 23, 59, 59, EXPECTED_MILLISECOND, 999, 9, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-02 00:00:00.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00010102T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const QDateTime SOURCE_DATETIME(-1, 1, 2, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-30 00:00:00.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00011230T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const QDateTime SOURCE_DATETIME(-1, 12, 30, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00011231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const QDateTime SOURCE_DATETIME(-1, 12, 31, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_q);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the date/time is undefined.
/// </summary>
QTEST_CASE ( GetMillisecond_AssertionFailsWhenDateIsUndefined_Test )
{
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        UNDEFINED_DATETIME.GetMillisecond();
    }
    catch(...) // [TODO] Thund: Use the concrete exception type when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-05-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const QDateTime SOURCE_DATETIME(4, 5, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-05-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const QDateTime SOURCE_DATETIME(-4, 5, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-02-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const QDateTime SOURCE_DATETIME(4, 2, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-02-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const QDateTime SOURCE_DATETIME(-4, 2, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0001-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingFirstPositiveDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const QDateTime SOURCE_DATETIME(1, 1, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0001-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const QDateTime SOURCE_DATETIME(-1, 1, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input year is positive and multiple of 5.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenYearIsPositiveAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const QDateTime SOURCE_DATETIME(25, 1, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input year is negative and multiple of 5.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenYearIsNegativeAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const QDateTime SOURCE_DATETIME(-25, 1, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 29th of February.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const QDateTime SOURCE_DATETIME(20, 2, 29, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 29th of February.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const QDateTime SOURCE_DATETIME(-20, 2, 29, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 28th of February.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const QDateTime SOURCE_DATETIME(20, 2, 28, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 28th of February.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const QDateTime SOURCE_DATETIME(-20, 2, 28, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingLastNegativeInstant_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 999;
    const QDateTime SOURCE_DATETIME(-1, 12, 31, 23, 59, 59, 999, EXPECTED_MICROSECOND, 9, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0001-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 999;
    const QDateTime SOURCE_DATETIME(1, 12, 31, 23, 59, 59, 999, EXPECTED_MICROSECOND, 9, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0012-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingFirstInstantOfPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const QDateTime SOURCE_DATETIME(12, 1, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0012-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingFirstInstantOfNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const QDateTime SOURCE_DATETIME(-12, 1, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingFirstInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const QDateTime SOURCE_DATETIME(4, 1, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const QDateTime SOURCE_DATETIME(-4, 1, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 999;
    const QDateTime SOURCE_DATETIME(4, 12, 31, 23, 59, 59, 999, EXPECTED_MICROSECOND, 9, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingLastInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 999;
    const QDateTime SOURCE_DATETIME(-4, 12, 31, 23, 59, 59, 999, EXPECTED_MICROSECOND, 9, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is the maximum date and time allowed.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingMaximumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 580;
    const QDateTime MAXIMUM_POSITIVE_DATETIME = QDateTime::GetMaxDateTime();

	// [Execution]
    unsigned int uMicrosecond = MAXIMUM_POSITIVE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is the minimum date and time allowed.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingMinimumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 419;
    const QDateTime MAXIMUM_NEGATIVE_DATETIME = QDateTime::GetMinDateTime();

	// [Execution]
    unsigned int uMicrosecond = MAXIMUM_NEGATIVE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCase19960101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 999;
    const QDateTime SOURCE_DATETIME(1996, 1, 1, 23, 59, 59, 999, EXPECTED_MICROSECOND, 9, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCase19961231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const QDateTime SOURCE_DATETIME(1996, 12, 31, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCase20001231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const QDateTime SOURCE_DATETIME(2000, 12, 31, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCase20000101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 999;
    const QDateTime SOURCE_DATETIME(2000, 1, 1, 23, 59, 59, 999, EXPECTED_MICROSECOND, 9, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 00:00:00.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCase20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const QDateTime SOURCE_DATETIME(2000, 1, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 12:00:00.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCase20000101T120000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const QDateTime SOURCE_DATETIME(2000, 1, 1, 12, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCase19991231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const QDateTime SOURCE_DATETIME(1999, 12, 31, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCase19991231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 999;
    const QDateTime SOURCE_DATETIME(1999, 12, 31, 23, 59, 59, 999, EXPECTED_MICROSECOND, 9, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 999;
    const QDateTime SOURCE_DATETIME(-4, 1, 1, 23, 59, 59, 999, EXPECTED_MICROSECOND, 9, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-02 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00040102T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 999;
    const QDateTime SOURCE_DATETIME(-4, 1, 2, 23, 59, 59, 999, EXPECTED_MICROSECOND, 9, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0003-01-01 00:00:00.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00030101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const QDateTime SOURCE_DATETIME(-3, 1, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.1.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const QDateTime SOURCE_DATETIME(-4, 1, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 1, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0005-12-31 23:59:59.999.999.9..
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00051231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 999;
    const QDateTime SOURCE_DATETIME(-5, 12, 31, 23, 59, 59, 999, EXPECTED_MICROSECOND, 9, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 23:59:59.999.999.9..
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 999;
    const QDateTime SOURCE_DATETIME(-2000, 12, 31, 23, 59, 59, 999, EXPECTED_MICROSECOND, 9, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 00:00:00.000.000.1.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const QDateTime SOURCE_DATETIME(-2000, 12, 31, 0, 0, 0, 0, EXPECTED_MICROSECOND, 1, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-01-01 00:00:00.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const QDateTime SOURCE_DATETIME(-2000, 1, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00010101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 999;
    const QDateTime SOURCE_DATETIME(-1, 1, 1, 23, 59, 59, 999, EXPECTED_MICROSECOND, 9, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-02 00:00:00.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00010102T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const QDateTime SOURCE_DATETIME(-1, 1, 2, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-30 00:00:00.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00011230T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const QDateTime SOURCE_DATETIME(-1, 12, 30, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00011231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const QDateTime SOURCE_DATETIME(-1, 12, 31, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_q);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the date/time is undefined.
/// </summary>
QTEST_CASE ( GetMicrosecond_AssertionFailsWhenDateIsUndefined_Test )
{
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        UNDEFINED_DATETIME.GetMicrosecond();
    }
    catch(...) // [TODO] Thund: Use the concrete exception type when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-05-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const QDateTime SOURCE_DATETIME(4, 5, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-05-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const QDateTime SOURCE_DATETIME(-4, 5, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-02-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const QDateTime SOURCE_DATETIME(4, 2, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-02-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const QDateTime SOURCE_DATETIME(-4, 2, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0001-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingFirstPositiveDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const QDateTime SOURCE_DATETIME(1, 1, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0001-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const QDateTime SOURCE_DATETIME(-1, 1, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input year is positive and multiple of 5.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenYearIsPositiveAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const QDateTime SOURCE_DATETIME(25, 1, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input year is negative and multiple of 5.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenYearIsNegativeAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const QDateTime SOURCE_DATETIME(-25, 1, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 29th of February.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const QDateTime SOURCE_DATETIME(20, 2, 29, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 29th of February.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const QDateTime SOURCE_DATETIME(-20, 2, 29, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 28th of February.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const QDateTime SOURCE_DATETIME(20, 2, 28, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 28th of February.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const QDateTime SOURCE_DATETIME(-20, 2, 28, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingLastNegativeInstant_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 9;
    const QDateTime SOURCE_DATETIME(-1, 12, 31, 23, 59, 59, 999, 999, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0001-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 9;
    const QDateTime SOURCE_DATETIME(1, 12, 31, 23, 59, 59, 999, 999, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0012-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingFirstInstantOfPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const QDateTime SOURCE_DATETIME(12, 1, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0012-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingFirstInstantOfNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const QDateTime SOURCE_DATETIME(-12, 1, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingFirstInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const QDateTime SOURCE_DATETIME(4, 1, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const QDateTime SOURCE_DATETIME(-4, 1, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 9;
    const QDateTime SOURCE_DATETIME(4, 12, 31, 23, 59, 59, 999, 999, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingLastInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 9;
    const QDateTime SOURCE_DATETIME(-4, 12, 31, 23, 59, 59, 999, 999, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is the maximum date and time allowed.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingMaximumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 7;
    const QDateTime MAXIMUM_POSITIVE_DATETIME = QDateTime::GetMaxDateTime();

	// [Execution]
    unsigned int uHundredOfNanosecond = MAXIMUM_POSITIVE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is the minimum date and time allowed.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingMinimumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 3;
    const QDateTime MAXIMUM_NEGATIVE_DATETIME = QDateTime::GetMinDateTime();

	// [Execution]
    unsigned int uHundredOfNanosecond = MAXIMUM_NEGATIVE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCase19960101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 9;
    const QDateTime SOURCE_DATETIME(1996, 1, 1, 23, 59, 59, 999, 999, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCase19961231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const QDateTime SOURCE_DATETIME(1996, 12, 31, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCase20001231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const QDateTime SOURCE_DATETIME(2000, 12, 31, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCase20000101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 9;
    const QDateTime SOURCE_DATETIME(2000, 1, 1, 23, 59, 59, 999, 999, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 00:00:00.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCase20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const QDateTime SOURCE_DATETIME(2000, 1, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 12:00:00.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCase20000101T120000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const QDateTime SOURCE_DATETIME(2000, 1, 1, 12, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCase19991231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const QDateTime SOURCE_DATETIME(1999, 12, 31, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCase19991231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 9;
    const QDateTime SOURCE_DATETIME(1999, 12, 31, 23, 59, 59, 999, 999, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 9;
    const QDateTime SOURCE_DATETIME(-4, 1, 1, 23, 59, 59, 999, 999, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-02 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00040102T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 9;
    const QDateTime SOURCE_DATETIME(-4, 1, 2, 23, 59, 59, 999, 999, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0003-01-01 00:00:00.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00030101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const QDateTime SOURCE_DATETIME(-3, 1, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.1.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 1;
    const QDateTime SOURCE_DATETIME(-4, 1, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0005-12-31 23:59:59.999.999.9..
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00051231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 9;
    const QDateTime SOURCE_DATETIME(-5, 12, 31, 23, 59, 59, 999, 999, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 23:59:59.999.999.9..
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 9;
    const QDateTime SOURCE_DATETIME(-2000, 12, 31, 23, 59, 59, 999, 999, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 00:00:00.000.000.1.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 1;
    const QDateTime SOURCE_DATETIME(-2000, 12, 31, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-01-01 00:00:00.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const QDateTime SOURCE_DATETIME(-2000, 1, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-01 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00010101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 9;
    const QDateTime SOURCE_DATETIME(-1, 1, 1, 23, 59, 59, 999, 999, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-02 00:00:00.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00010102T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const QDateTime SOURCE_DATETIME(-1, 1, 2, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-30 00:00:00.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00011230T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const QDateTime SOURCE_DATETIME(-1, 12, 30, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 00:00:00.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00011231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const QDateTime SOURCE_DATETIME(-1, 12, 31, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_q);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the date/time is undefined.
/// </summary>
QTEST_CASE ( GetHundredOfNanosecond_AssertionFailsWhenDateIsUndefined_Test )
{
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        UNDEFINED_DATETIME.GetHundredOfNanosecond();
    }
    catch(...) // [TODO] Thund: Use the concrete exception type when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that it returns the same date/time with different time zone.
/// </summary>
QTEST_CASE ( GetUtc_ReturnsSameDateTimeWithDifferentTimeZone_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;

    // [Preparation]
    const QTimeZone* EXPECTED_TIMEZONE = null_q;
    const QTimeZone* TIMEZONE = SQTimeZoneFactory::GetTimeZoneById(QE_L("Europe/Madrid")); // CET+1
    const QDateTime SOURCE_DATETIME(-4, 12, 31, 23, 59, 59, 999, 999, 9, EXPECTED_TIMEZONE);
    const QDateTime UTC_DATETIME(   SOURCE_DATETIME, null_q);

	// [Execution]
    QDateTime result = SOURCE_DATETIME.GetUtc();

    // [Verification]
    const QTimeZone* pResultTimeZone = result.GetTimeZone();
    BOOST_CHECK(result == UTC_DATETIME);
    BOOST_CHECK(pResultTimeZone == EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that it returns the expected value.
/// </summary>
QTEST_CASE ( GetMaxDateTime_ReturnsExpectedValue_Test )
{
    // [Preparation]
    const QDateTime EXPECTED_DATETIME(29228, 9, 14, 2, 48, 5, 477, 580, 7, null_q);
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime result = QDateTime::GetMaxDateTime();

    // [Verification]
    const QTimeZone* pResultTimeZone = result.GetTimeZone();
    BOOST_CHECK(result == EXPECTED_DATETIME);
    BOOST_CHECK(pResultTimeZone == EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that it returns the expected value.
/// </summary>
QTEST_CASE ( GetMinDateTime_ReturnsExpectedValue_Test )
{
    // [Preparation]
    const QDateTime EXPECTED_DATETIME(-29228, 4, 18, 21, 11, 54, 522, 419, 3, null_q);
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime result = QDateTime::GetMinDateTime();

    // [Verification]
    const QTimeZone* pResultTimeZone = result.GetTimeZone();
    BOOST_CHECK(result == EXPECTED_DATETIME);
    BOOST_CHECK(pResultTimeZone == EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that it returns True when the date is positive.
/// </summary>
QTEST_CASE ( IsPositive_ReturnsTrueWhenDateIsPositive_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    const QDateTime SOURCE_DATETIME(4, 3, 2);

	// [Execution]
    bool bResult = SOURCE_DATETIME.IsPositive();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the date is not positive.
/// </summary>
QTEST_CASE ( IsPositive_ReturnsFalseWhenDateIsNotPositive_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    const QDateTime SOURCE_DATETIME(-4, 3, 2);

	// [Execution]
    bool bResult = SOURCE_DATETIME.IsPositive();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the date is calculated based on local time in order to know whether it is positive or not.
/// </summary>
QTEST_CASE ( IsPositive_IsLocalTime_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;

    const bool EXPECTED_RESULT = false;
    const QTimeZone* EXPECTED_TIMEZONE = SQTimeZoneFactory::GetTimeZoneById(QE_L("Atlantic/Azores")); // AZOT-1
    const QDateTime SOURCE_DATETIME(-1, 12, 31, 23, 30, 0, 0, 0, 0, EXPECTED_TIMEZONE);
    const QDateTime SOURCE_DATETIME_UTC(SOURCE_DATETIME, null_q);

	// [Execution]
    bool bResultLocal = SOURCE_DATETIME.IsPositive();
    bool bResultUtc   = SOURCE_DATETIME_UTC.IsPositive();

    // [Verification]
    BOOST_CHECK_EQUAL(bResultLocal, EXPECTED_RESULT);
    BOOST_CHECK_NE(bResultLocal, bResultUtc);
}

/// <summary>
/// Checks that it returns True when the date / time represent the first positive instant 0001-01-01 00:00:00.000000000.
/// </summary>
QTEST_CASE ( IsPositive_FirstPositiveInstantIsConsideredPositive_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    const QDateTime FIRST_POSITIVE_INSTANT(1, 1, 1, 0, 0, 0, 0, 0, 0);

	// [Execution]
    bool bResult = FIRST_POSITIVE_INSTANT.IsPositive();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the date/time is undefined.
/// </summary>
QTEST_CASE ( IsPositive_AssertionFailsWhenDateIsUndefined_Test )
{
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        UNDEFINED_DATETIME.IsPositive();
    }
    catch(...) // [TODO] Thund: Use the concrete exception type when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns False when date / time is undefined.
/// </summary>
QTEST_CASE ( IsPositive_ReturnsFalseWhenDateIsUndefined_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();

	// [Execution]
    bool bResult = UNDEFINED_DATETIME.IsPositive();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns False when the date is not negative.
/// </summary>
QTEST_CASE ( IsNegative_ReturnsTrueWhenDateIsNegative_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    const QDateTime SOURCE_DATETIME(4, 3, 2);

	// [Execution]
    bool bResult = SOURCE_DATETIME.IsNegative();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the date is negative.
/// </summary>
QTEST_CASE ( IsNegative_ReturnsTrueWhenDateIsNotNegative_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    const QDateTime SOURCE_DATETIME(-4, 3, 2);

	// [Execution]
    bool bResult = SOURCE_DATETIME.IsNegative();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the date is calculated based on local time in order to know whether it is negative or not.
/// </summary>
QTEST_CASE ( IsNegative_IsLocalTime_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;

    const bool EXPECTED_RESULT = true;
    const QTimeZone* EXPECTED_TIMEZONE = SQTimeZoneFactory::GetTimeZoneById(QE_L("Atlantic/Azores")); // AZOT-1
    const QDateTime SOURCE_DATETIME(-1, 12, 31, 23, 30, 0, 0, 0, 0, EXPECTED_TIMEZONE);
    const QDateTime SOURCE_DATETIME_UTC(SOURCE_DATETIME, null_q);

	// [Execution]
    bool bResultLocal = SOURCE_DATETIME.IsNegative();
    bool bResultUtc   = SOURCE_DATETIME_UTC.IsNegative();

    // [Verification]
    BOOST_CHECK_EQUAL(bResultLocal, EXPECTED_RESULT);
    BOOST_CHECK_NE(bResultLocal, bResultUtc);
}

/// <summary>
/// Checks that it returns False when the date / time represent the first positive instant 0001-01-01 00:00:00.000000000.
/// </summary>
QTEST_CASE ( IsNegative_FirstNegativeInstantIsNotConsideredNegative_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    const QDateTime FIRST_POSITIVE_INSTANT(1, 1, 1, 0, 0, 0, 0, 0, 0);

	// [Execution]
    bool bResult = FIRST_POSITIVE_INSTANT.IsNegative();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the date/time is undefined.
/// </summary>
QTEST_CASE ( IsNegative_AssertionFailsWhenDateIsUndefined_Test )
{
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        UNDEFINED_DATETIME.IsNegative();
    }
    catch(...) // [TODO] Thund: Use the concrete exception type when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns False when date / time is undefined.
/// </summary>
QTEST_CASE ( IsNegative_ReturnsFalseWhenDateIsUndefined_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    const QDateTime UNDEFINED_DATETIME = QDateTime::GetUndefinedDate();

	// [Execution]
    bool bResult = UNDEFINED_DATETIME.IsNegative();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
QTEST_CASE ( GetUndefinedDate_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// Checks that IsUndefined method returns true with an undefined date.
/// </summary>
QTEST_CASE ( IsUndefined_ReturnsTrueWithUndefinedDate_Test )
{
    const QDateTime DATETIME = QDateTime::GetUndefinedDate();
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bCheckResult = DATETIME.IsUndefined();

    // [Verification]
    BOOST_CHECK_EQUAL(bCheckResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that IsUndefined method returns false with a valid date.
/// </summary>
QTEST_CASE ( IsUndefined_ReturnsFalseWithValidDate_Test )
{
    const QDateTime DATETIME(1, 1, 1, 0, 0, 0, 0, 0, 0);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bCheckResult = DATETIME.IsUndefined();

    // [Verification]
    BOOST_CHECK_EQUAL(bCheckResult, EXPECTED_RESULT);
}

// End - Test Suite: QDateTime
QTEST_SUITE_END()
