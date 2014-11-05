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

#include "QTimeSpan.h"

using Kinesis::QuimeraEngine::Tools::Time::QTimeZone;
using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;


QTEST_SUITE_BEGIN( QDstInformation_TestSuite )

/// <summary>
/// Checks that instances are correctly constructed when using common input data.
/// </summary>
QTEST_CASE ( Constructor_InstanceIsCorrectlyBuiltWhenUsingCommonInputData_Test )
{
    // [Preparation]
    const QTimeSpan EXPECTED_OFFSET = QTimeSpan(36000000000);
    const bool EXPECTED_OFFSET_SIGN = false;
    boost::local_time::tz_database TIMEZONE_DATABASE;
    std::istringstream streamDbSource;
    streamDbSource.str("\"Europe/Madrid\",\"CET\",\"CET\",\"CEST\",\"CEST\",\"+01:00:00\",\"+01:00:00\",\"-1;0;3\",\"+02:00:00\",\"-1;0;10\",\"+03:00:00\"");
    TIMEZONE_DATABASE.load_from_stream(streamDbSource);
    boost::local_time::time_zone_ptr timeZoneFromDB = TIMEZONE_DATABASE.time_zone_from_region("Europe/Madrid");

	// [Execution]
    QTimeZone::QDstInformation dstInfo(timeZoneFromDB);

    // [Verification]
    BOOST_CHECK(dstInfo.GetOffset() == EXPECTED_OFFSET);
    BOOST_CHECK_EQUAL(dstInfo.IsOffsetNegative(), EXPECTED_OFFSET_SIGN);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when passing a null time zone.
/// </summary>
QTEST_CASE ( Constructor_AssertionFailsWhenUsingNullInputData_Test )
{
    // [Preparation]
    boost::local_time::time_zone_ptr timeZoneFromDB = boost::local_time::time_zone_ptr((boost::local_time::time_zone_ptr::element_type*) null_q);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QTimeZone::QDstInformation dstInfo(timeZoneFromDB);
    }
    catch(...) // [TODO] Thund: Use appropiate exception type when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that returned date and time are what expected.
/// </summary>
QTEST_CASE ( GetStartInYear_ReturnsExpectedDateTimeForCommonYear_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QDateTime;

    // [Preparation]
    boost::local_time::tz_database TIMEZONE_DATABASE;
    std::istringstream streamDbSource;
    streamDbSource.str("\"Europe/Madrid\",\"CET\",\"CET\",\"CEST\",\"CEST\",\"+01:00:00\",\"+01:00:00\",\"-1;0;3\",\"+02:00:00\",\"-1;0;10\",\"+03:00:00\"");
    TIMEZONE_DATABASE.load_from_stream(streamDbSource);

    const int COMMON_YEAR = 2014;
    boost::local_time::time_zone_ptr timeZoneFromDB = TIMEZONE_DATABASE.time_zone_from_region("Europe/Madrid");
    QTimeZone::QDstInformation dstInfo(timeZoneFromDB);
    const QDateTime EXPECTED_DATETIME(2014, 3ULL, 30ULL, 2ULL, 0, 0, 0, 0, 0, null_q); // UTC

	// [Execution]
    QDateTime start = dstInfo.GetStartInYear(COMMON_YEAR);

    // [Verification]
    BOOST_CHECK(start == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that returned date and time are what expected.
/// </summary>
QTEST_CASE ( GetEndInYear_ReturnsExpectedDateTimeForCommonYear_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QDateTime;

    // [Preparation]
    boost::local_time::tz_database TIMEZONE_DATABASE;
    std::istringstream streamDbSource;
    streamDbSource.str("\"Europe/Madrid\",\"CET\",\"CET\",\"CEST\",\"CEST\",\"+01:00:00\",\"+01:00:00\",\"-1;0;3\",\"+02:00:00\",\"-1;0;10\",\"+03:00:00\"");
    TIMEZONE_DATABASE.load_from_stream(streamDbSource);

    const int COMMON_YEAR = 2014;
    boost::local_time::time_zone_ptr timeZoneFromDB = TIMEZONE_DATABASE.time_zone_from_region("Europe/Madrid");
    QTimeZone::QDstInformation dstInfo(timeZoneFromDB);
    const QDateTime EXPECTED_DATETIME(2014, 10ULL, 26ULL, 3ULL, 0, 0, 0, 0, 0, null_q); // UTC

	// [Execution]
    QDateTime end = dstInfo.GetEndInYear(COMMON_YEAR);

    // [Verification]
    BOOST_CHECK(end == EXPECTED_DATETIME);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when input year equals zero.
/// </summary>
QTEST_CASE ( GetStartInYear_AssertionFailsWhenYearEqualsZero_Test )
{
    // [Preparation]
    boost::local_time::tz_database TIMEZONE_DATABASE;
    std::istringstream streamDbSource;
    streamDbSource.str("\"Europe/Madrid\",\"CET\",\"CET\",\"CEST\",\"CEST\",\"+01:00:00\",\"+01:00:00\",\"-1;0;3\",\"+02:00:00\",\"-1;0;10\",\"+03:00:00\"");
    TIMEZONE_DATABASE.load_from_stream(streamDbSource);
    boost::local_time::time_zone_ptr timeZoneFromDB = TIMEZONE_DATABASE.time_zone_from_region("Europe/Madrid");
    QTimeZone::QDstInformation dstInfo(timeZoneFromDB);

    const int YEAR_ZERO = 0;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        dstInfo.GetStartInYear(YEAR_ZERO);
    }
    catch(...) // [TODO] Thund: Use appropiate exception type when it exists
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when input year equals zero.
/// </summary>
QTEST_CASE ( GetEndInYear_AssertionFailsWhenYearEqualsZero_Test )
{
    // [Preparation]
    boost::local_time::tz_database TIMEZONE_DATABASE;
    std::istringstream streamDbSource;
    streamDbSource.str("\"Europe/Madrid\",\"CET\",\"CET\",\"CEST\",\"CEST\",\"+01:00:00\",\"+01:00:00\",\"-1;0;3\",\"+02:00:00\",\"-1;0;10\",\"+03:00:00\"");
    TIMEZONE_DATABASE.load_from_stream(streamDbSource);
    boost::local_time::time_zone_ptr timeZoneFromDB = TIMEZONE_DATABASE.time_zone_from_region("Europe/Madrid");
    QTimeZone::QDstInformation dstInfo(timeZoneFromDB);

    const int YEAR_ZERO = 0;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        dstInfo.GetEndInYear(YEAR_ZERO);
    }
    catch(...) // [TODO] Thund: Use appropiate exception type when it exists
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
QTEST_CASE ( GetOffset_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
QTEST_CASE ( GetIsOffsetNegative_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

// End - Test Suite: QDstInformation
QTEST_SUITE_END()
