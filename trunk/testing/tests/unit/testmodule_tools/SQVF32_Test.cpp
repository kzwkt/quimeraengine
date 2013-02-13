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

#include "SQVF32.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::SQVF32;
using Kinesis::QuimeraEngine::Tools::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::DataTypes::float_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::vf32_q;

QTEST_SUITE_BEGIN( SQVF32_TestSuite )

/// <summary>
/// Checks if every floating point value is set in the correct place into the vector.
/// </summary>
QTEST_CASE ( Pack_EveryValueIsSetInTheRightPlace_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_FLOAT1 = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_FLOAT2 = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_FLOAT3 = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_FLOAT4 = SQFloat::_4;

	// Execution
    vf32_q vectorUT;
    SQVF32::Pack(EXPECTED_VALUE_FOR_FLOAT1,
                 EXPECTED_VALUE_FOR_FLOAT2,
                 EXPECTED_VALUE_FOR_FLOAT3,
                 EXPECTED_VALUE_FOR_FLOAT4,
                 vectorUT);

    // Verification
    float_q fFloatValueInPosition1;
    float_q fFloatValueInPosition2;
    float_q fFloatValueInPosition3;
    float_q fFloatValueInPosition4;
    SQVF32::Unpack(vectorUT,
                   fFloatValueInPosition1,
                   fFloatValueInPosition2,
                   fFloatValueInPosition3,
                   fFloatValueInPosition4);

    BOOST_CHECK_EQUAL(fFloatValueInPosition1, EXPECTED_VALUE_FOR_FLOAT1);
    BOOST_CHECK_EQUAL(fFloatValueInPosition2, EXPECTED_VALUE_FOR_FLOAT2);
    BOOST_CHECK_EQUAL(fFloatValueInPosition3, EXPECTED_VALUE_FOR_FLOAT3);
    BOOST_CHECK_EQUAL(fFloatValueInPosition4, EXPECTED_VALUE_FOR_FLOAT4);
}

/// <summary>
/// Not tested. It's the same as Pack so it's not repeated.
/// </summary>
QTEST_CASE ( Unpack_NotTested_Test )
{
    BOOST_MESSAGE(QE_L("It's not a testable method: no inputs, no outputs, just executes a method of a component."));
}

// End - Test Suite: SQVF32
QTEST_SUITE_END()
