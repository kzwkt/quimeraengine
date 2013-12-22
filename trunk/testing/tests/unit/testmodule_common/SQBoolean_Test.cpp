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

#include "SQBoolean.h"

using Kinesis::QuimeraEngine::Common::DataTypes::SQBoolean;

QTEST_SUITE_BEGIN( SQBoolean_TestSuite )

/// <summary>
/// Checks if the string returned for the TRUE value meets the expectations.
/// </summary>
QTEST_CASE ( ToString_TrueValueIsConvertedToStringAsExpected_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::string_q;

    // [Preparation]
    const bool BOOLEAN_VALUE_TRUE = true;
    string_q EXPECTED_RESULT = QE_L("true");

	// [Execution]
    string_q strResultUT = SQBoolean::ToString(BOOLEAN_VALUE_TRUE);

    // [Verification]
    BOOST_CHECK(strResultUT == EXPECTED_RESULT);
}

/// <summary>
/// Checks if the string returned for the FALSE value meets the expectations.
/// </summary>
QTEST_CASE ( ToString_FalseValueIsConvertedToStringAsExpected_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::string_q;

    // [Preparation]
    const bool BOOLEAN_VALUE_FALSE = false;
    string_q EXPECTED_RESULT = QE_L("false");

	// [Execution]
    string_q strResultUT = SQBoolean::ToString(BOOLEAN_VALUE_FALSE);

    // [Verification]
    BOOST_CHECK(strResultUT == EXPECTED_RESULT);
}

// End - Test Suite: SQBoolean
QTEST_SUITE_END()
