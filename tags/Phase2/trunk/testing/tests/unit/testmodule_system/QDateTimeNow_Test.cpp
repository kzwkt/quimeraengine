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

#include "QDateTimeNow.h"

#include "QTimeZone.h"
#include "SQTimeZoneFactory.h"

using Kinesis::QuimeraEngine::System::Timing::QDateTimeNow;
using Kinesis::QuimeraEngine::Tools::Time::QTimeZone;


QTEST_SUITE_BEGIN( QDateTimeNow_TestSuite )
    
/// <summary>
/// Checks that it creates a valid date and time.
/// </summary>
QTEST_CASE ( Constructor1_CreatesValidDateTime_Test )
{
    // [Preparation]
    const bool IS_NOT_UNDEFINED = true;

	// [Execution]
    QDateTimeNow now;
    
    // [Verification]
    bool IsNotUndefined = !now.IsUndefined();

    BOOST_CHECK_EQUAL(IsNotUndefined, IS_NOT_UNDEFINED);
}

/// <summary>
/// Checks that it creates a valid date and time when the input time zone is null.
/// </summary>
QTEST_CASE ( Constructor2_CreatesValidDateTimeWhenTimeZoneIsNull_Test )
{
    // [Preparation]
    const bool IS_NOT_UNDEFINED = true;
    const QTimeZone* NULL_TIMEZONE = null_q;

	// [Execution]
    QDateTimeNow now(NULL_TIMEZONE);
    
    // [Verification]
    bool IsNotUndefined = !now.IsUndefined();
    const QTimeZone* pTimeZone = now.GetTimeZone();

    BOOST_CHECK_EQUAL(IsNotUndefined, IS_NOT_UNDEFINED);
    BOOST_CHECK_EQUAL(pTimeZone, NULL_TIMEZONE);
}

/// <summary>
/// Checks that it creates a valid date and time when the input time is not null.
/// </summary>
QTEST_CASE ( Constructor2_CreatesValidDateTimeWhenTimeZoneIsNotNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;

    // [Preparation]
    const bool IS_NOT_UNDEFINED = true;
    const QTimeZone* TIMEZONE = SQTimeZoneFactory::GetTimeZoneById("Europe/London");

	// [Execution]
    QDateTimeNow now(TIMEZONE);
    
    // [Verification]
    bool IsNotUndefined = !now.IsUndefined();
    const QTimeZone* pTimeZone = now.GetTimeZone();

    BOOST_CHECK_EQUAL(IsNotUndefined, IS_NOT_UNDEFINED);
    BOOST_CHECK_EQUAL(pTimeZone, TIMEZONE);
}

// End - Test Suite: QDateTimeNow
QTEST_SUITE_END()
