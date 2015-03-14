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

#include "SQTimeZoneFactory.h"

#include "QTimeZone.h"
#include "QAssertException.h"

using Kinesis::QuimeraEngine::Common::Exceptions::QAssertException;
using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;
using Kinesis::QuimeraEngine::Tools::Time::QTimeZone;


QTEST_SUITE_BEGIN( SQTimeZoneFactory_TestSuite )

/// <summary>
/// Checks that it returns the expected time zone instance when using a common valid Id.
/// </summary>
QTEST_CASE( GetTimeZoneById_ReturnsExpectedTimeZoneWhenUsingCommonId_Test )
{
    // [Preparation]
    const string_q COMMON_TIMEZONE_ID = QE_L("Europe/Madrid");
    const QTimeZone* NULL_TIMEZONE = null_q;

	// [Execution]
    const QTimeZone* pTimeZone = SQTimeZoneFactory::GetTimeZoneById(COMMON_TIMEZONE_ID);

    // [Verification]
    BOOST_CHECK_NE(pTimeZone, NULL_TIMEZONE);
    BOOST_CHECK(pTimeZone->GetId() == COMMON_TIMEZONE_ID);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when using an invalid Id.
/// </summary>
QTEST_CASE( GetTimeZoneById_AssertionFailsWhenIdIsNotValid_Test )
{
    // [Preparation]
    const string_q INVALID_TIMEZONE_ID = QE_L("Not valid ID");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQTimeZoneFactory::GetTimeZoneById(INVALID_TIMEZONE_ID);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns null when using an invalid Id.
/// </summary>
QTEST_CASE( GetTimeZoneById_ReturnsNullWhenIdIsNotValid_Test )
{
    // [Preparation]
    const string_q INVALID_TIMEZONE_ID = QE_L("Not valid ID");
    const QTimeZone* NULL_TIMEZONE = null_q;

	// [Execution]
    const QTimeZone* pTimeZone = SQTimeZoneFactory::GetTimeZoneById(INVALID_TIMEZONE_ID);

    // [Verification]
    BOOST_CHECK_EQUAL(pTimeZone, NULL_TIMEZONE);
}

#endif


// End - Test Suite: SQTimeZoneFactory
QTEST_SUITE_END()
