// [TERMS&CONDITIONS]

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
