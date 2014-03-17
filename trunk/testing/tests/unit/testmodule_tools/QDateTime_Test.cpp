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
    // [TODO] Thund: Uncomment when operator== is implemented
    /*// [Preparation]

	// [Execution]
    QDateTime dateTime;

    // [Verification]
    BOOST_CHECK(dateTime == QDateTime::GetUndefinedDate());*/
}

/// <summary>
/// Checks that the date and time is copied correctly.
/// </summary>
QTEST_CASE ( Constructor2_DateTimeIsCorrectlyCopied_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit and time zones can be created
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = 2013;
    const u64_q EXPECTED_MONTH       = 5;
    const u64_q EXPECTED_DAY         = 2;
    const u64_q EXPECTED_HOUR        = 3;
    const u64_q EXPECTED_MINUTE      = 4;
    const u64_q EXPECTED_SECOND      = 5;
    const u64_q EXPECTED_MILLISECOND = 666;
    const u64_q EXPECTED_MICROSECOND = 777;
    const u64_q EXPECTED_HNS         = 8;
    const QTimeZone* EXPECTED_TIMEZONE = SQTimeZoneFactory::GetTimeZoneById("");
    const QDateTime ORIGINAL_DATETIME(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                                      EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                                      EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                                      EXPECTED_TIMEZONE);

	// [Execution]
    QDateTime dateTime(ORIGINAL_DATETIME);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the undefined date and time is copied.
/// </summary>
QTEST_CASE ( Constructor2_UndefinedDateTimeIsCopied_Test )
{
    // [TODO] Thund: Uncomment when operator== is implemented
    /*// [Preparation]
    const QDateTime EXPECTED_VALUE = QDateTime::GetUndefinedDate();

	// [Execution]
    QDateTime dateTime(EXPECTED_VALUE);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_VALUE);*/
}

/// <summary>
/// Checks that the instance is correctly constructed from a common date and time.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingCommonDateAndTime_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit and time zones can be created
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = 2013;
    const u64_q EXPECTED_MONTH       = 11;
    const u64_q EXPECTED_DAY         = 13;
    const u64_q EXPECTED_HOUR        = 10;
    const u64_q EXPECTED_MINUTE      = 32;
    const u64_q EXPECTED_SECOND      = 23;
    const u64_q EXPECTED_MILLISECOND = 654;
    const u64_q EXPECTED_MICROSECOND = 489;
    const u64_q EXPECTED_HNS         = 5;
    const QTimeZone* EXPECTED_TIMEZONE = SQTimeZoneFactory::GetTimeZoneById("Atlantic/Canary");

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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/

}

/// <summary>
/// Checks that the instance is correctly constructed from a common date and time and the time zone is null.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingCommonDateAndTimeAndNullTimeZone_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit and time zones can be created
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = 2013;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);*/
}

/// <summary>
/// Checks that the instance is correctly constructed from a common date and time and the offset of the time zone is positive.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingCommonDateAndTimeAndTimeZoneOffsetIsPositive_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit and time zones can be created
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = 2013;
    const u64_q EXPECTED_MONTH       = 11;
    const u64_q EXPECTED_DAY         = 13;
    const u64_q EXPECTED_HOUR        = 10;
    const u64_q EXPECTED_MINUTE      = 32;
    const u64_q EXPECTED_SECOND      = 23;
    const u64_q EXPECTED_MILLISECOND = 654;
    const u64_q EXPECTED_MICROSECOND = 489;
    const u64_q EXPECTED_HNS         = 5;
    const QTimeZone* POSITIVE_TIMEZONE = SQTimeZoneFactory::GetTimeZoneById("Europe/Madrid");

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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);*/
}

/// <summary>
/// Checks that the instance is correctly constructed from a common date and time and the offset of the time zone is negative.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingCommonDateAndTimeAndTimeZoneOffsetIsNegative_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit and time zones can be created
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = 2013;
    const u64_q EXPECTED_MONTH       = 11;
    const u64_q EXPECTED_DAY         = 13;
    const u64_q EXPECTED_HOUR        = 10;
    const u64_q EXPECTED_MINUTE      = 32;
    const u64_q EXPECTED_SECOND      = 23;
    const u64_q EXPECTED_MILLISECOND = 654;
    const u64_q EXPECTED_MICROSECOND = 489;
    const u64_q EXPECTED_HNS         = 5;
    const QTimeZone* NEGATIVE_TIMEZONE = SQTimeZoneFactory::GetTimeZoneById("America/New_York");

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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);*/
}

/// <summary>
/// Checks that the default value of the time zone is null.
/// </summary>
QTEST_CASE ( Constructor3_TimeZoneDefaultValueIsNull_Test )
{
    // [Preparation]
    const i32_q EXPECTED_YEAR        = 2013;
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
    const i32_q NOT_ALLOWED_YEAR   = 30000;
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
/// Checks that an assertion fails when the month is greater than the top limit.
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
    /*
    // [TODO] Thund: Uncomment when it is possible to get the maximum date and time
    // [Preparation]
    const i32_q MAX_YEAR        = QDateTime::GetMaxDate().GetYear();
    const u64_q MAX_MONTH       = QDateTime::GetMaxDate().GetMonth();
    const u64_q MAX_DAY         = QDateTime::GetMaxDate().GetDay();
    const u64_q MAX_HOUR        = QDateTime::GetMaxDate().GetHour();
    const u64_q MAX_MINUTE      = QDateTime::GetMaxDate().GetMinute();
    const u64_q MAX_SECOND      = QDateTime::GetMaxDate().GetSecond();
    const u64_q MAX_MILLISECOND = QDateTime::GetMaxDate().GetMillisecond();
    const u64_q MAX_MICROSECOND = QDateTime::GetMaxDate().GetMicrosecond();
    const u64_q MAX_HNS         = QDateTime::GetMaxDate().GetHundredsOfNanoseconds();
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
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);*/
}

/// <summary>
/// Checks that an assertion fails when the date and time is prior to minimum.
/// </summary>
QTEST_CASE ( Constructor3_AssertionFailsWhenDateIsAnteriorToMinimum_Test )
{
    /*
    // [TODO] Thund: Uncomment when it is possible to get the minimum date and time
    // [Preparation]
    const i32_q MIN_YEAR        = QDateTime::GetMinDate().GetYear();
    const u64_q MIN_MONTH       = QDateTime::GetMinDate().GetMonth();
    const u64_q MIN_DAY         = QDateTime::GetMinDate().GetDay();
    const u64_q MIN_HOUR        = QDateTime::GetMinDate().GetHour();
    const u64_q MIN_MINUTE      = QDateTime::GetMinDate().GetMinute();
    const u64_q MIN_SECOND      = QDateTime::GetMinDate().GetSecond();
    const u64_q MIN_MILLISECOND = QDateTime::GetMinDate().GetMillisecond();
    const u64_q MIN_MICROSECOND = QDateTime::GetMinDate().GetMicrosecond();
    const u64_q MIN_HNS         = QDateTime::GetMinDate().GetHundredsOfNanoseconds();
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
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);*/
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the constructed instance has the maximum value when the input date and time is greater than maximum.
/// </summary>
QTEST_CASE ( Constructor3_MaximumDateIsConstructedWhenDateIsPosteriorToMaximum_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get the maximum date and time
    /*// [Preparation]
    const i32_q MAX_YEAR        = QDateTime::GetMaxDate().GetYear();
    const u64_q MAX_MONTH       = QDateTime::GetMaxDate().GetMonth();
    const u64_q MAX_DAY         = QDateTime::GetMaxDate().GetDay();
    const u64_q MAX_HOUR        = QDateTime::GetMaxDate().GetHour();
    const u64_q MAX_MINUTE      = QDateTime::GetMaxDate().GetMinute();
    const u64_q MAX_SECOND      = QDateTime::GetMaxDate().GetSecond();
    const u64_q MAX_MILLISECOND = QDateTime::GetMaxDate().GetMillisecond();
    const u64_q MAX_MICROSECOND = QDateTime::GetMaxDate().GetMicrosecond();
    const u64_q MAX_HNS         = QDateTime::GetMaxDate().GetHundredsOfNanoseconds();
    const QTimeZone* NULL_TIMEZONE = null_q;
    const u64_q MAX_HNS_PLUS_ONE = MAX_HNS + 1;
    const QDateTime MAX_DATETIME = QDateTime::GetMaxDate();

	// [Execution]
    QDateTime dateTime(MAX_YEAR, MAX_MONTH, MAX_DAY,
                       MAX_HOUR, MAX_MINUTE, MAX_SECOND,
                       MAX_MILLISECOND, MAX_MICROSECOND, MAX_HNS_PLUS_ONE,
                       NULL_TIMEZONE);

    // [Verification]
    BOOST_CHECK_(dateTime == MAX_DATETIME);*/
}

/// <summary>
/// Checks that the constructed instance has the minimum value when the input date and time is lower than minimum.
/// </summary>
QTEST_CASE ( Constructor3_MinimumDateIsConstructedWhenDateIsAnteriorToMinimum_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get the minimum date and time
    /*// [Preparation]
    const i32_q MIN_YEAR        = QDateTime::GetMinDate().GetYear();
    const u64_q MIN_MONTH       = QDateTime::GetMinDate().GetMonth();
    const u64_q MIN_DAY         = QDateTime::GetMinDate().GetDay();
    const u64_q MIN_HOUR        = QDateTime::GetMinDate().GetHour();
    const u64_q MIN_MINUTE      = QDateTime::GetMinDate().GetMinute();
    const u64_q MIN_SECOND      = QDateTime::GetMinDate().GetSecond();
    const u64_q MIN_MILLISECOND = QDateTime::GetMinDate().GetMillisecond();
    const u64_q MIN_MICROSECOND = QDateTime::GetMinDate().GetMicrosecond();
    const u64_q MIN_HNS         = QDateTime::GetMinDate().GetHundredsOfNanoseconds();
    const QTimeZone* MIN_TIMEZONE = null_q;
    const u64_q MIN_HNS_MINUS_ONE = MIN_HNS - 1;
    const QDateTime MIN_DATETIME = QDateTime::GetMinDate();

	// [Execution]
    QDateTime dateTime(MIN_YEAR, MIN_MONTH, MIN_DAY,
                       MIN_HOUR, MIN_MINUTE, MIN_SECOND,
                       MIN_MILLISECOND, MIN_MICROSECOND, MIN_HNS_MINUS_ONE,
                       MIN_TIMEZONE);

    // [Verification]
    BOOST_CHECK(dateTime == MIN_DATETIME);*/
}

#endif

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is 0004-05-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstPositiveLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = 4;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is -0004-05-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstNegativeLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = -4;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is 0004-02-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstPositiveLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = 4;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is -0004-02-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstNegativeLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = -4;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is 0001-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstPositiveDateAndTime_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = 1;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is -0001-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstInstantOfFirstNegativeYear_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = -1;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input year is multiple of 5.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenYearIsPositiveAndMultipleOfFive_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = 25;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input year is multiple of 5.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenYearIsNegativeAndMultipleOfFive_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = -25;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when using a positive leap year and the day 29th of February.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingPositiveLeapYearAndDayIs29February_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = 20;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when using a negative leap year and the day 29th of February.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingNegativeLeapYearAndDayIs29February_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = -20;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when using a positive leap year and the day 28th of February.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingPositiveLeapYearAndDayIs28February_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = 20;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when using a negative leap year and the day 28th of February.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingNegativeLeapYearAndDayIs28February_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = -20;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input is -0001-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingLastNegativeInstant_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = -1;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input is 0001-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingLastInstantOfFirstPositiveYear_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = 1;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input is 0012-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstInstantOfPositiveLeapYear_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = 12;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input is -0012-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstInstantOfNegativeLeapYear_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = -12;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input is 004-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstInstantOfFirstPositiveLeapYear_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = 4;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input is -004-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstInstantOfFirstNegativeLeapYear_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = -4;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input is 004-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingLastInstantOfFirstPositiveLeapYear_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = 4;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input is -004-12-31 23:59:59.999.999.9.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingLastInstantOfFirstNegativeLeapYear_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = -4;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input is the maximum date and time allowed.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingMaximumDateAndTime_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q MAX_YEAR        = QDateTime::GetMaxDate().GetYear();
    const u64_q MAX_MONTH       = QDateTime::GetMaxDate().GetMonth();
    const u64_q MAX_DAY         = QDateTime::GetMaxDate().GetDay();
    const u64_q MAX_HOUR        = QDateTime::GetMaxDate().GetHour();
    const u64_q MAX_MAXUTE      = QDateTime::GetMaxDate().GetMaxute();
    const u64_q MAX_SECOND      = QDateTime::GetMaxDate().GetSecond();
    const u64_q MAX_MILLISECOND = QDateTime::GetMaxDate().GetMillisecond();
    const u64_q MAX_MICROSECOND = QDateTime::GetMaxDate().GetMicrosecond();
    const u64_q MAX_HNS         = QDateTime::GetMaxDate().GetHundredsOfNanoseconds();
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(MAX_YEAR, MAX_MONTH, MAX_DAY,
                       MAX_HOUR, MAX_MAXUTE, MAX_SECOND,
                       MAX_MILLISECOND, MAX_MICROSECOND, MAX_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), MAX_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), MAX_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), MAX_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), MAX_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMaxute(), MAX_MAXUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), MAX_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), MAX_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), MAX_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), MAX_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), MAX_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input is the minimum date and time allowed.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingMinimumDateAndTime_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q MIN_YEAR        = QDateTime::GetMinDate().GetYear();
    const u64_q MIN_MONTH       = QDateTime::GetMinDate().GetMonth();
    const u64_q MIN_DAY         = QDateTime::GetMinDate().GetDay();
    const u64_q MIN_HOUR        = QDateTime::GetMinDate().GetHour();
    const u64_q MIN_MINUTE      = QDateTime::GetMinDate().GetMinute();
    const u64_q MIN_SECOND      = QDateTime::GetMinDate().GetSecond();
    const u64_q MIN_MILLISECOND = QDateTime::GetMinDate().GetMillisecond();
    const u64_q MIN_MICROSECOND = QDateTime::GetMinDate().GetMicrosecond();
    const u64_q MIN_HNS         = QDateTime::GetMinDate().GetHundredsOfNanoseconds();
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(MIN_YEAR, MIN_MONTH, MIN_DAY,
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), MIN_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), MIN_TIMEZONE)*/
}


/// <summary>
/// Checks that the instance is correctly constructed from a common date and time.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingCommonDateAndTime_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit and time zones can be created
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR  = 2013;
    const u64_q EXPECTED_MONTH = 11;
    const u64_q EXPECTED_DAY   = 13;
    const QTimeZone* EXPECTED_TIMEZONE = SQTimeZoneFactory::GetTimeZoneById("");

	// [Execution]
    QDateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the default value of the time zone is null.
/// </summary>
QTEST_CASE ( Constructor4_TimeZoneDefaultValueIsNull_Test )
{
    // [Preparation]
    const i32_q EXPECTED_YEAR  = 2013;
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
/// Checks that an assertion fails when the month is greater than the top limit.
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
    /*
    // [TODO] Thund: Uncomment when it is possible to get the maximum date and time
    // [Preparation]
    const i32_q MAX_YEAR  = QDateTime::GetMaxDate().GetYear();
    const u64_q MAX_MONTH = QDateTime::GetMaxDate().GetMonth();
    const u64_q MAX_DAY   = QDateTime::GetMaxDate().GetDay();
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
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);*/
}

/// <summary>
/// Checks that an assertion fails when the date and time is prior to minimum.
/// </summary>
QTEST_CASE ( Constructor4_AssertionFailsWhenDateIsAnteriorToMinimum_Test )
{
    /*
    // [TODO] Thund: Uncomment when it is possible to get the minimum date and time
    // [Preparation]
    const i32_q MIN_YEAR  = QDateTime::GetMinDate().GetYear();
    const u64_q MIN_MONTH = QDateTime::GetMinDate().GetMonth();
    const u64_q MIN_DAY   = QDateTime::GetMinDate().GetDay() + 1; // (time is 00:00:00, which would be prior to minimum, so next day is used)
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
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);*/
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the constructed instance has the maximum value when the input date and time is greater than maximum.
/// </summary>
QTEST_CASE ( Constructor4_MaximumDateIsConstructedWhenDateIsPosteriorToMaximum_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get the maximum date and time
    /*// [Preparation]
    const i32_q MAX_YEAR  = QDateTime::GetMaxDate().GetYear();
    const u64_q MAX_MONTH = QDateTime::GetMaxDate().GetMonth();
    const u64_q MAX_DAY   = QDateTime::GetMaxDate().GetDay();
    const QTimeZone* NULL_TIMEZONE = null_q;
    const u64_q MAX_DAY_PLUS_ONE = MAX_DAY + 1;
    const QDateTime MAX_DATETIME = QDateTime::GetMaxDate();

	// [Execution]
    QDateTime dateTime(MAX_YEAR, MAX_MONTH, MAX_DAY_PLUS_ONE,
                       NULL_TIMEZONE);

    // [Verification]
    BOOST_CHECK_(dateTime == MAX_DATETIME);*/
}

/// <summary>
/// Checks that the constructed instance has the minimum value when the input date and time is lower than minimum.
/// </summary>
QTEST_CASE ( Constructor4_MinimumDateIsConstructedWhenDateIsAnteriorToMinimum_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get the minimum date and time
    /*// [Preparation]
    const i32_q MIN_YEAR  = QDateTime::GetMinDate().GetYear();
    const u64_q MIN_MONTH = QDateTime::GetMinDate().GetMonth();
    const u64_q MIN_DAY   = QDateTime::GetMinDate().GetDay() + 1; // (time is 00:00:00, which would be prior to minimum, so next day is used)
    const QTimeZone* NULL_TIMEZONE = null_q;
    const u64_q MIN_DAY_MINUS_ONE = MIN_DAY - 1;
    const QDateTime MIN_DATETIME = QDateTime::GetMinDate();

	// [Execution]
    QDateTime dateTime(MIN_YEAR, MIN_MONTH, MIN_DAY_MINUS_ONE,
                       MIN_TIMEZONE);

    // [Verification]
    BOOST_CHECK(dateTime == MIN_DATETIME);*/
}

#endif

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is 0004-05-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstPositiveLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = 4;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is -0004-05-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstNegativeLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = -4;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is 0004-02-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstPositiveLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = 4;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is -0004-02-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstNegativeLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = -4;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is 0001-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstPositiveDateAndTime_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = 1;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is -0001-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstInstantOfFirstNegativeYear_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = -1;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input year is multiple of 5.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenYearIsPositiveAndMultipleOfFive_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = 25;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input year is multiple of 5.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenYearIsNegativeAndMultipleOfFive_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = -25;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when using a positive leap year and the day 29th of February.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingPositiveLeapYearAndDayIs29February_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = 20;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when using a negative leap year and the day 29th of February.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingNegativeLeapYearAndDayIs29February_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = -20;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when using a positive leap year and the day 28th of February.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingPositiveLeapYearAndDayIs28February_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = 20;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when using a negative leap year and the day 28th of February.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingNegativeLeapYearAndDayIs28February_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = -20;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input is 0012-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstInstantOfPositiveLeapYear_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = 12;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input is -0012-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstInstantOfNegativeLeapYear_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = -12;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input is 004-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstInstantOfFirstPositiveLeapYear_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = 4;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input is -004-01-01 00:00:00.000.000.0.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstInstantOfFirstNegativeLeapYear_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = -4;
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input is the maximum date and time allowed.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingMaximumDateAndTime_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q MAX_YEAR        = QDateTime::GetMaxDate().GetYear();
    const u64_q MAX_MONTH       = QDateTime::GetMaxDate().GetMonth();
    const u64_q MAX_DAY         = QDateTime::GetMaxDate().GetDay();
    const u64_q MAX_HOUR        = 0;
    const u64_q MAX_MAXUTE      = 0;
    const u64_q MAX_SECOND      = 0;
    const u64_q MAX_MILLISECOND = 0;
    const u64_q MAX_MICROSECOND = 0;
    const u64_q MAX_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(MAX_YEAR, MAX_MONTH, MAX_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), MAX_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), MAX_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), MAX_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), MAX_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMaxute(), MAX_MAXUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), MAX_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), MAX_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), MAX_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), MAX_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), MAX_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed when input is the minimum date and time allowed.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingMinimumDateAndTime_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit
    /*
    // [Preparation]
    const i32_q MIN_YEAR        = QDateTime::GetMinDate().GetYear();
    const u64_q MIN_MONTH       = QDateTime::GetMinDate().GetMonth();
    const u64_q MIN_DAY         = QDateTime::GetMinDate().GetDay() + 1;
    const u64_q MIN_HOUR        = 0;
    const u64_q MIN_MINUTE      = 0;
    const u64_q MIN_SECOND      = 0;
    const u64_q MIN_MILLISECOND = 0;
    const u64_q MIN_MICROSECOND = 0;
    const u64_q MIN_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = null_q;

	// [Execution]
    QDateTime dateTime(MIN_YEAR, MIN_MONTH, MIN_DAY,
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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), MIN_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), MIN_TIMEZONE)*/
}

/// <summary>
/// Checks that the instance is correctly constructed from a common time.
/// </summary>
QTEST_CASE ( Constructor5_IsCorrectlyConstructedWhenUsingCommonTime_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit and time zones can be created
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = 1;
    const u64_q EXPECTED_MONTH       = 1;
    const u64_q EXPECTED_DAY         = 1;
    const u64_q EXPECTED_HOUR        = 10;
    const u64_q EXPECTED_MINUTE      = 32;
    const u64_q EXPECTED_SECOND      = 23;
    const u64_q EXPECTED_MILLISECOND = 654;
    const u64_q EXPECTED_MICROSECOND = 489;
    const u64_q EXPECTED_HNS         = 5;
    const QTimeZone* EXPECTED_TIMEZONE = SQTimeZoneFactory::GetTimeZoneById("");

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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/

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
    // [TODO] Thund: Uncomment when it is possible to get every time unit and time zones can be created
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = 1;
    const u64_q EXPECTED_MONTH       = 1;
    const u64_q EXPECTED_DAY         = 1;
    const u64_q EXPECTED_HOUR        = 10;
    const u64_q EXPECTED_MINUTE      = 32;
    const u64_q EXPECTED_SECOND      = 23;
    const u64_q EXPECTED_MILLISECOND = 654;
    const u64_q EXPECTED_MICROSECOND = 0;
    const u64_q EXPECTED_HNS         = 0;
    const QTimeZone* EXPECTED_TIMEZONE = SQTimeZoneFactory::GetTimeZoneById("");

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
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/

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
/// Checks that the input date and time are correctly copied.
/// </summary>
QTEST_CASE ( OperatorAssignation_InputDateTimeIsCorrectlyCopied_Test )
{
    // [TODO] Thund: Uncomment when it is possible to get every time unit and time zones can be created
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR        = 2013;
    const u64_q EXPECTED_MONTH       = 5;
    const u64_q EXPECTED_DAY         = 2;
    const u64_q EXPECTED_HOUR        = 3;
    const u64_q EXPECTED_MINUTE      = 4;
    const u64_q EXPECTED_SECOND      = 5;
    const u64_q EXPECTED_MILLISECOND = 666;
    const u64_q EXPECTED_MICROSECOND = 777;
    const u64_q EXPECTED_HNS         = 8;
    const QTimeZone* EXPECTED_TIMEZONE = SQTimeZoneFactory::GetTimeZoneById("");
    const QDateTime EXPECTED_DATETIME(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                                      EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                                      EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                                      EXPECTED_TIMEZONE);

	// [Execution]
    QDateTime dateTime;
    dateTime = EXPECTED_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE)*/
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that undefined dates are copied.
/// </summary>
QTEST_CASE ( OperatorAssignation_UndefinedDateIsCopied_Test )
{
    // [TODO] Thund: Uncomment when operator== is implemented
    /*
    // [Preparation]
    const i32_q EXPECTED_YEAR  = 2013;
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
    BOOST_CHECK(dateTime == EXPECTED_YEAR);*/
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
    const i32_q NONLEAP_YEAR = 2;
    const u64_q COMMON_MONTH = 1;
    const u64_q COMMON_DAY   = 2;
    const QDateTime ORIGINAL_DATETIME(NONLEAP_YEAR, COMMON_MONTH, COMMON_DAY);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ORIGINAL_DATETIME.IsLeapYear();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the date is undefined.
/// </summary>
QTEST_CASE ( IsLeapYear_AssertionFailsWhenDateIsUndefined_Test )
{
    // [TODO] Thund: Uncomment when the operator QDateTime::operator== exists
    /*// [Preparation]
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
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);*/
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
/// It is not necessary to test this method since it is just a getter.
/// </summary>
QTEST_CASE ( GetUndefinedDate_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

// End - Test Suite: QDateTime
QTEST_SUITE_END()
