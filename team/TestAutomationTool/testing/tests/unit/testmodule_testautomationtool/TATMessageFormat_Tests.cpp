//-------------------------------------------------------------------------------//
//                   TEST AUTOMATION TOOL : LICENSE                              //
//-------------------------------------------------------------------------------//
// This file is part of Test Automation Tool.                                    //
// Test Automation Tool is free software: you can redistribute it and/or modify  //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation, either version 3 of the License, or             //
// (at your option) any later version.                                           //
//                                                                               //
// Test Automation Tool is distributed in the hope that it will be useful,       //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License for more details.                                  //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with Test Automation Tool. If not, see <http://www.gnu.org/licenses/>.  //
//                                                                               //
// This license doesn't force you to put any kind of banner or logo telling      //
// that you are using Test Automation Tool in your project but we would          //
// appreciate if you do so or, at least, if you let us know about that.          //
//                                                                               //
// Enjoy!                                                                        //
//                                                                               //
// Kinesis Team                                                                  //
//-------------------------------------------------------------------------------//

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../../testsystem/TestingExternalDefinitions.h"

#include "TestExecution/TATMessageFormat.h"

using Kinesis::TestAutomationTool::Backend::TATMessageFormat;
using Kinesis::TestAutomationTool::Backend::ETATColor;

QTEST_SUITE_BEGIN( TATMessageFormat_TestSuite )

/// <summary>
/// Checks that the default values have not changed since the last test execution.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const ETATColor EXPECTED_COLOR = ETATColor::E_Black;
    const std::map<wxString, wxString> EXPECTED_REPLACEMENTS;
    const unsigned int EXPECTED_TEXTSTYLE = 0;

	// [Execution]
    TATMessageFormat messageFormatUT;
    
    ETATColor eColor = messageFormatUT.GetColor();
    unsigned int uTextStyle = messageFormatUT.GetTextStyle();

    // [Verification]
    BOOST_CHECK_EQUAL(eColor.ToString(), EXPECTED_COLOR.ToString());
    BOOST_CHECK_EQUAL(uTextStyle, EXPECTED_TEXTSTYLE);
}

/// <summary>
/// Checks that the value is correctly stored.
/// </summary>
QTEST_CASE ( Constructor2_ValueIsCorrectlyStored_Test )
{
    // [Preparation]
    const ETATColor EXPECTED_COLOR = ETATColor::E_Red;
    const std::map<wxString, wxString> EXPECTED_DEFAULT_REPLACEMENTS;
    const unsigned int EXPECTED_DEFAULT_TEXTSTYLE = 0;

	// [Execution]
    TATMessageFormat messageFormatUT(EXPECTED_COLOR);
    
    ETATColor eColor = messageFormatUT.GetColor();
    unsigned int uTextStyle = messageFormatUT.GetTextStyle();

    // [Verification]
    BOOST_CHECK_EQUAL(eColor.ToString(), EXPECTED_COLOR.ToString());
    BOOST_CHECK_EQUAL(uTextStyle, EXPECTED_DEFAULT_TEXTSTYLE);
}

/// <summary>
/// Checks that the values are correctly stored.
/// </summary>
QTEST_CASE ( Constructor3_ValuesAreCorrectlyStored_Test )
{
    // [Preparation]
    const ETATColor EXPECTED_COLOR = ETATColor::E_Red;
    const std::map<wxString, wxString> EXPECTED_DEFAULT_REPLACEMENTS;
    const unsigned int EXPECTED_TEXTSTYLE = 0;

	// [Execution]
    TATMessageFormat messageFormatUT(EXPECTED_COLOR, EXPECTED_TEXTSTYLE);
    
    ETATColor eColor = messageFormatUT.GetColor();
    unsigned int uTextStyle = messageFormatUT.GetTextStyle();

    // [Verification]
    BOOST_CHECK_EQUAL(eColor.ToString(), EXPECTED_COLOR.ToString());
    BOOST_CHECK_EQUAL(uTextStyle, EXPECTED_TEXTSTYLE);
}

/// <summary>
/// Checks that the color is correctly retrieved.
/// </summary>
QTEST_CASE ( GetColor_ColorIsCorrectlyRetrieved_Test )
{
    // Preparation
    TATMessageFormat messageFormatUT;
    const ETATColor EXPECTED_COLOR = ETATColor::E_Red;
    messageFormatUT.SetColor(EXPECTED_COLOR);

	// Execution
    ETATColor eColor = messageFormatUT.GetColor();
    
    // Verification
    BOOST_CHECK_EQUAL(eColor.ToString(), EXPECTED_COLOR.ToString());
}

/// <summary>
/// Checks that the color is correctly stored.
/// </summary>
QTEST_CASE ( SetColor_ColorIsCorrectlyStored_Test )
{
    // Preparation
    const ETATColor EXPECTED_COLOR = ETATColor::E_Red;

	// Execution
    TATMessageFormat messageFormatUT;
    messageFormatUT.SetColor(EXPECTED_COLOR);
    
    // Verification
    BOOST_CHECK_EQUAL(messageFormatUT.GetColor().ToString(), EXPECTED_COLOR.ToString());
}

/// <summary>
/// Checks that the text style is correctly retrieved.
/// </summary>
QTEST_CASE ( GetTextStyle_TextStyleIsCorrectlyRetrieved_Test )
{
    // Preparation
    TATMessageFormat messageFormatUT;
    const unsigned int EXPECTED_TEXTSTYLE = 1;
    messageFormatUT.SetTextStyle(EXPECTED_TEXTSTYLE);

	// Execution
    unsigned int uTextStyle = messageFormatUT.GetTextStyle();
    
    // Verification
    BOOST_CHECK_EQUAL(uTextStyle, EXPECTED_TEXTSTYLE);
}

/// <summary>
/// Checks that the text style is correctly stored.
/// </summary>
QTEST_CASE ( SetTextStyle_TextStyleIsCorrectlyStored_Test )
{
    // Preparation
    const unsigned int EXPECTED_TEXTSTYLE = 1;

	// Execution
    TATMessageFormat messageFormatUT;
    messageFormatUT.SetTextStyle(EXPECTED_TEXTSTYLE);
    
    // Verification
    BOOST_CHECK_EQUAL(messageFormatUT.GetTextStyle(), EXPECTED_TEXTSTYLE);
}

// End - Test Suite: TATMessageFormat
QTEST_SUITE_END()
