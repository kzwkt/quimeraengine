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

#include "QCharUnicode.h"

using Kinesis::QuimeraEngine::Common::DataTypes::QCharUnicode;

QTEST_SUITE_BEGIN( QCharUnicode_TestSuite )

/// <summary>
/// Checks that the character is properly initialized using a common code point.
/// </summary>
QTEST_CASE ( Constructor1_CharacterIsProperlyInitialized_Test )
{
    // [TODO] Thund: Uncomment when the operator== is implemented

    /*using Kinesis::QuimeraEngine::Common::DataTypes::codepoint_q;

    // [Preparation]
    codepoint_q INPUT_CODEPOINT = 159; // arbitrary value
    QCharUnicode EXPECTED_RESULT(INPUT_CODEPOINT); 

	// [Execution]
    QCharUnicode character(INPUT_CODEPOINT);
    
    // [Verification]
    BOOST_CHECK(character == EXPECTED_RESULT);*/
}

/// <summary>
/// Checks that the copy of a character is equal to the original.
/// </summary>
QTEST_CASE ( Constructor2_CopiedCharacterIsEqualToOriginal_Test )
{
    // [TODO] Thund: Uncomment when the operator== is implemented

    /*using Kinesis::QuimeraEngine::Common::DataTypes::codepoint_q;

    // [Preparation]
    codepoint_q INPUT_CODEPOINT = 159; // arbitrary value
    QCharUnicode EXPECTED_RESULT(INPUT_CODEPOINT);

	// [Execution]
    QCharUnicode character(EXPECTED_RESULT);
    
    // [Verification]
    BOOST_CHECK(character == EXPECTED_RESULT);*/
}

/// <summary>
/// Checks that the assigned character is equal to the copied character.
/// </summary>
QTEST_CASE ( OperatorAssignation_CopiedCharacterIsEqualToOriginal_Test )
{
    // [TODO] Thund: Uncomment when the operator== is implemented

    /*using Kinesis::QuimeraEngine::Common::DataTypes::codepoint_q;

    // [Preparation]
    codepoint_q INPUT_CODEPOINT = 159; // arbitrary value
    QCharUnicode EXPECTED_RESULT(INPUT_CODEPOINT);

	// [Execution]
    QCharUnicode character;
    character = EXPECTED_RESULT;
    
    // [Verification]
    BOOST_CHECK(character == EXPECTED_RESULT);*/
}


// End - Test Suite: QCharUnicode
QTEST_SUITE_END()
