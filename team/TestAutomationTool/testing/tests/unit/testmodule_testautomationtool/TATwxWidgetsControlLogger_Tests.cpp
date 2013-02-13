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

#include "TestExecution/TATwxWidgetsControlLogger.h"
#include "TATwxWidgetsControlLoggerWhiteBox.h"
#include "TATRichTextCtrlMock.h"

using Kinesis::TestAutomationTool::Backend::TATwxWidgetsControlLogger;
using Kinesis::TestAutomationTool::Backend::Test::TATwxWidgetsControlLoggerWhiteBox;

QTEST_SUITE_BEGIN( TATwxWidgetsControlLogger_TestSuite )

/// <summary>
/// Checks that default values have not changed since last test execution.
/// </summary>
QTEST_CASE ( Constructor_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const bool EXPECTED_AUTONEWLINEPRINT = true;
    const bool EXPECTED_AUTOTIMEPRINT = true;

	// [Execution]
    TATwxWidgetsControlLogger logger(null_t);

    bool bAutoNewLinePrint = logger.GetAutoNewLinePrint();
    bool bAutoTimePrint = logger.GetAutoTimePrint();

    // [Verification]
    BOOST_CHECK_EQUAL(bAutoNewLinePrint, EXPECTED_AUTONEWLINEPRINT);
    BOOST_CHECK_EQUAL(bAutoTimePrint, EXPECTED_AUTOTIMEPRINT);
}

/// <summary>
/// Checks that the messages are written in the control immediately, when the auto-flush mechanism is enabled.
/// </summary>
QTEST_CASE ( Log_MessageIsWrittenInControlInstantlyWhenAutoFlushIsEnabled_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATFormattedMessage;
    using Kinesis::TestAutomationTool::Backend::Test::TATRichTextCtrlMock;

    // [Preparation]
    TATRichTextCtrlMock CONTROL;
    const wxString EXPECTED_LOGGED_TEXT = wxT("LOGGEDTEXT");
    const bool AUTO_FLUSH_ENABLED = true;

    TATwxWidgetsControlLogger logger(&CONTROL, AUTO_FLUSH_ENABLED);
    // Sets some properties to simplify the test
    logger.SetAutoTimePrint(false);
    logger.SetAutoNewLinePrint(false);

	// [Execution]
    logger.Log(TATFormattedMessage(EXPECTED_LOGGED_TEXT));
    wxString strLoggedText = CONTROL.GetValue();

    // [Verification]
    BOOST_CHECK_EQUAL(strLoggedText, EXPECTED_LOGGED_TEXT);
}

/// <summary>
/// Checks that the messages are not written in the control immediately, when the auto-flush mechanism is disabled.
/// </summary>
QTEST_CASE ( Log_MessageIsNotWrittenInControlInstantlyWhenAutoFlushIsDisabled_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATFormattedMessage;
    using Kinesis::TestAutomationTool::Backend::Test::TATRichTextCtrlMock;

    // [Preparation]
    TATRichTextCtrlMock CONTROL;
    const wxString LOGGED_TEXT = wxT("LOGGEDTEXT");
    const wxString EXPECTED_TEXT = wxT("");
    const bool AUTO_FLUSH_ENABLED = false;

    TATwxWidgetsControlLogger logger(&CONTROL, AUTO_FLUSH_ENABLED);
    // Sets some properties to simplify the test
    logger.SetAutoTimePrint(false);
    logger.SetAutoNewLinePrint(false);

	// [Execution]
    logger.Log(TATFormattedMessage(LOGGED_TEXT));
    wxString strLoggedText = CONTROL.GetValue();

    // [Verification]
    BOOST_CHECK_EQUAL(strLoggedText, EXPECTED_TEXT);
}

/// <summary>
/// Checks that dumps the buffered messages in the control.
/// </summary>
QTEST_CASE ( Flush_DumpsTheBufferedMessagesInControl_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATFormattedMessage;
    using Kinesis::TestAutomationTool::Backend::Test::TATRichTextCtrlMock;

    // [Preparation]
    TATRichTextCtrlMock CONTROL;
    const wxString FIRST_LOGGED_TEXT = wxT("LOGGED");
    const wxString SECOND_LOGGED_TEXT = wxT("TEXT");
    const wxString EXPECTED_LOGGED_TEXT = wxT("LOGGEDTEXT");
    const bool AUTO_FLUSH_ENABLED = false;

    TATwxWidgetsControlLogger logger(&CONTROL, AUTO_FLUSH_ENABLED);
    // Sets some properties to simplify the test
    logger.SetAutoTimePrint(false);
    logger.SetAutoNewLinePrint(false);

    logger.Log(TATFormattedMessage(FIRST_LOGGED_TEXT));
    logger.Log(TATFormattedMessage(SECOND_LOGGED_TEXT));

	// [Execution]
    logger.Flush();
    wxString strLoggedText = CONTROL.GetValue();

    // [Verification]
    BOOST_CHECK_EQUAL(strLoggedText, EXPECTED_LOGGED_TEXT);
}

/// <summary>
/// Checks that writes the message part in the control.
/// </summary>
QTEST_CASE ( WriteMessagePart_WritesMessagePartInControl_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATFormattedMessage;
    using Kinesis::TestAutomationTool::Backend::Test::TATRichTextCtrlMock;
    using Kinesis::TestAutomationTool::Backend::TATMessageFormat;

    // [Preparation]
    TATRichTextCtrlMock CONTROL;
    const wxString EXPECTED_LOGGED_TEXT = wxT("LOGGEDTEXT");;
    const bool AUTO_FLUSH_ENABLED = true;

    TATwxWidgetsControlLoggerWhiteBox logger(&CONTROL, AUTO_FLUSH_ENABLED);
    // Sets some properties to simplify the test
    logger.SetAutoTimePrint(false);
    logger.SetAutoNewLinePrint(false);

	// [Execution]
    logger.WriteMessagePart(std::pair<wxString, TATMessageFormat>(EXPECTED_LOGGED_TEXT, TATMessageFormat()));
    wxString strLoggedText = CONTROL.GetValue();

    // [Verification]
    BOOST_CHECK_EQUAL(strLoggedText, EXPECTED_LOGGED_TEXT);
}

/// <summary>
/// Checks that writes the message in the control.
/// </summary>
QTEST_CASE ( WriteMessage_WritesMessageInControl_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATFormattedMessage;
    using Kinesis::TestAutomationTool::Backend::Test::TATRichTextCtrlMock;

    // [Preparation]
    TATRichTextCtrlMock CONTROL;
    const wxString FIRST_LOGGED_TEXT = wxT("LOGGED");
    const wxString SECOND_LOGGED_TEXT = wxT("TEXT");
    const wxString EXPECTED_LOGGED_TEXT = wxT("LOGGEDTEXT");
    const bool AUTO_FLUSH_ENABLED = true;

    TATwxWidgetsControlLoggerWhiteBox logger(&CONTROL, AUTO_FLUSH_ENABLED);
    // Sets some properties to simplify the test
    logger.SetAutoTimePrint(false);
    logger.SetAutoNewLinePrint(false);

    TATFormattedMessage MESSAGE = TATFormattedMessage(FIRST_LOGGED_TEXT);
    MESSAGE.Append(SECOND_LOGGED_TEXT);

	// [Execution]
    logger.WriteMessage(MESSAGE);
    wxString strLoggedText = CONTROL.GetValue();

    // [Verification]
    BOOST_CHECK_EQUAL(strLoggedText, EXPECTED_LOGGED_TEXT);
}

/// <summary>
/// Checks that .
/// </summary>
QTEST_CASE ( TranslateColor_TranslationHasNotChanged_Test )
{
    using Kinesis::TestAutomationTool::Backend::ETATColor;

    // [Preparation]
    const wxColor EXPECTED_COLOR_FOR_BLACK  = *wxBLACK;
    const wxColor EXPECTED_COLOR_FOR_WHITE  = *wxWHITE;
    const wxColor EXPECTED_COLOR_FOR_RED    = *wxRED;
    const wxColor EXPECTED_COLOR_FOR_YELLOW = *wxYELLOW;
    const wxColor EXPECTED_COLOR_FOR_BLUE   = *wxBLUE;
    const wxColor EXPECTED_COLOR_FOR_GREEN  = *wxGREEN;
    const wxColor EXPECTED_COLOR_FOR_PURPLE = wxColor("Purple");
    const wxColor EXPECTED_COLOR_FOR_GREY   = *wxLIGHT_GREY;

    const ETATColor INPUT_COLOR_BLACK  = ETATColor::E_Black;
    const ETATColor INPUT_COLOR_WHITE  = ETATColor::E_White;
    const ETATColor INPUT_COLOR_RED    = ETATColor::E_Red;
    const ETATColor INPUT_COLOR_YELLOW = ETATColor::E_Yellow;
    const ETATColor INPUT_COLOR_BLUE   = ETATColor::E_Blue;
    const ETATColor INPUT_COLOR_GREEN  = ETATColor::E_Green;
    const ETATColor INPUT_COLOR_PURPLE = ETATColor::E_Purple;
    const ETATColor INPUT_COLOR_GREY   = ETATColor::E_Grey;

    TATwxWidgetsControlLoggerWhiteBox logger(null_t);

	// [Execution]
    wxColor returnedBlack  = logger.TranslateColor(INPUT_COLOR_BLACK);
    wxColor returnedWhite  = logger.TranslateColor(INPUT_COLOR_WHITE);
    wxColor returnedRed    = logger.TranslateColor(INPUT_COLOR_RED);
    wxColor returnedYellow = logger.TranslateColor(INPUT_COLOR_YELLOW);
    wxColor returnedBlue   = logger.TranslateColor(INPUT_COLOR_BLUE);
    wxColor returnedGreen  = logger.TranslateColor(INPUT_COLOR_GREEN);
    wxColor returnedPurple = logger.TranslateColor(INPUT_COLOR_PURPLE);
    wxColor returnedGrey   = logger.TranslateColor(INPUT_COLOR_GREY);

    // [Verification]
    BOOST_CHECK_EQUAL(returnedBlack.GetRGBA(),  EXPECTED_COLOR_FOR_BLACK.GetRGBA());
    BOOST_CHECK_EQUAL(returnedWhite.GetRGBA(),  EXPECTED_COLOR_FOR_WHITE.GetRGBA());
    BOOST_CHECK_EQUAL(returnedRed.GetRGBA(),    EXPECTED_COLOR_FOR_RED.GetRGBA());
    BOOST_CHECK_EQUAL(returnedYellow.GetRGBA(), EXPECTED_COLOR_FOR_YELLOW.GetRGBA());
    BOOST_CHECK_EQUAL(returnedBlue.GetRGBA(),   EXPECTED_COLOR_FOR_BLUE.GetRGBA());
    BOOST_CHECK_EQUAL(returnedGreen.GetRGBA(),  EXPECTED_COLOR_FOR_GREEN.GetRGBA());
    BOOST_CHECK_EQUAL(returnedPurple.GetRGBA(), EXPECTED_COLOR_FOR_PURPLE.GetRGBA());
    BOOST_CHECK_EQUAL(returnedGrey.GetRGBA(),   EXPECTED_COLOR_FOR_GREY.GetRGBA());
}

// End - Test Suite: TATwxWidgetsControlLogger
QTEST_SUITE_END()

/*
    wxColor TranslateColor(const ETATColor& color) const;

    virtual void SetAutoNewLinePrint(const bool &bEnable);

    virtual bool GetAutoNewLinePrint() const;

    virtual void SetAutoTimePrint(const bool &bEnable);

    virtual bool GetAutoTimePrint() const;
    */