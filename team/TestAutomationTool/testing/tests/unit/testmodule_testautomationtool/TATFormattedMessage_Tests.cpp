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

#include "TestExecution/TATFormattedMessage.h"

using Kinesis::TestAutomationTool::Backend::TATFormattedMessage;

QTEST_SUITE_BEGIN( TATFormattedMessage_TestSuite )


/// <summary>
/// Checks that default values have not changed.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // Preparation
    const TATFormattedMessage::TMessagePart* EXPECTED_MESSAGE = null_t;

    // Execution
    TATFormattedMessage formattedMessageUT;

    const TATFormattedMessage::TMessagePart* pMessage = formattedMessageUT.GetFirstAndResetPointer();
    
    // Verification
    BOOST_CHECK_EQUAL(pMessage, EXPECTED_MESSAGE);
}

/// <summary>
/// Checks that received values are stored properly.
/// </summary>
QTEST_CASE ( Constructor2_ValuesAreSetProperly_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATMessageFormat;
    using Kinesis::TestAutomationTool::Backend::ETATColor;

    // Preparation
    const wxString EXPECTED_MESSAGE_TEXT = wxT("MESSAGETEXT");
    const TATMessageFormat EXPECTED_MESSAGE_FORMAT = TATMessageFormat(ETATColor::E_Purple);

    // Execution
    TATFormattedMessage formattedMessageUT(EXPECTED_MESSAGE_TEXT, TATMessageFormat(ETATColor::E_Purple));

    const TATFormattedMessage::TMessagePart* pMessagePart = formattedMessageUT.GetFirstAndResetPointer();
    
    // Verification
    BOOST_CHECK_EQUAL(pMessagePart->first, EXPECTED_MESSAGE_TEXT);
    BOOST_CHECK_EQUAL(pMessagePart->second.GetColor().ToString(), EXPECTED_MESSAGE_FORMAT.GetColor().ToString());
}

/// <summary>
/// Checks that the message part is added at the end.
/// </summary>
QTEST_CASE ( Append_MessagePartIsCorrectlyAppendedAtTheEnd_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATMessageFormat;
    using Kinesis::TestAutomationTool::Backend::ETATColor;

    // Preparation
    const wxString EXPECTED_MESSAGE_TEXT = wxT("MESSAGETEXT");
    const TATMessageFormat EXPECTED_MESSAGE_FORMAT = TATMessageFormat(ETATColor::E_Purple);

    // Execution
    TATFormattedMessage formattedMessageUT(wxT("FirstMessage"));
    formattedMessageUT.Append(EXPECTED_MESSAGE_TEXT, TATMessageFormat(ETATColor::E_Purple));

    formattedMessageUT.GetFirstAndResetPointer();
    const TATFormattedMessage::TMessagePart* pMessagePart = formattedMessageUT.GetNext();
    
    // Verification
    BOOST_CHECK_EQUAL(pMessagePart->first, EXPECTED_MESSAGE_TEXT);
    BOOST_CHECK_EQUAL(pMessagePart->second.GetColor().ToString(), EXPECTED_MESSAGE_FORMAT.GetColor().ToString());
}

/// <summary>
/// Checks that returned message is the same instance that is being modified.
/// </summary>
QTEST_CASE ( Append_ReturnedMessageIsTheSameInstance_Test )
{
    // Preparation
    TATFormattedMessage formattedMessageUT;
    TATFormattedMessage* EXPECTED_MESSAGE = &formattedMessageUT;

    // Execution
    TATFormattedMessage* pMessage = &formattedMessageUT.Append(wxT("MESSAGE"));
    
    // Verification
    BOOST_CHECK_EQUAL(pMessage, EXPECTED_MESSAGE);
}

/// <summary>
/// Checks that message is emptied.
/// </summary>
QTEST_CASE ( Clear_MessageIsEmptyAfterClear_Test )
{
    // Preparation
    const TATFormattedMessage::TMessagePart* EXPECTED_CONTENT = null_t;
    TATFormattedMessage formattedMessageUT(wxT("FirstMessage"));

    // Execution
    formattedMessageUT.Clear();
    
    const TATFormattedMessage::TMessagePart* pMessagePart = formattedMessageUT.GetFirstAndResetPointer();
    
    // Verification
    BOOST_CHECK_EQUAL(pMessagePart, EXPECTED_CONTENT);
}

/// <summary>
/// Checks that the message contains all the parts previously added.
/// </summary>
QTEST_CASE ( GetFullMessage_MessageContainsAllParts_Test )
{
    // Preparation
    const wxString MESSAGE_TEXTPART1 = wxT("TEXT1");
    const wxString MESSAGE_TEXTPART2 = wxT("TEXT2");
    const wxString EXPECTED_MESSAGE_TEXT = MESSAGE_TEXTPART1 + MESSAGE_TEXTPART2;

    TATFormattedMessage formattedMessageUT(MESSAGE_TEXTPART1);
    formattedMessageUT.Append(MESSAGE_TEXTPART2);

    // Execution
    wxString strFullMessage = formattedMessageUT.GetFullMessage();
    
    // Verification
    BOOST_CHECK_EQUAL(strFullMessage, EXPECTED_MESSAGE_TEXT);
}

/// <summary>
/// Checks that it returns null when the message is empty.
/// </summary>
QTEST_CASE ( GetFirstAndResetPointer_ReturnsNullWhenMessageIsEmpty_Test )
{
    // Preparation
    const TATFormattedMessage::TMessagePart* EXPECTED_CONTENT = null_t;

    // Execution
    TATFormattedMessage formattedMessageUT;
    const TATFormattedMessage::TMessagePart* pMessagePart = formattedMessageUT.GetFirstAndResetPointer();
    
    // Verification
    BOOST_CHECK_EQUAL(pMessagePart, EXPECTED_CONTENT);
}

/// <summary>
/// Checks that it returns the first part of the message.
/// </summary>
QTEST_CASE ( GetFirstAndResetPointer_ReturnsTheFirstMessagePart_Test )
{
    // Preparation
    const wxString EXPECTED_MESSAGE_TEXT = wxT("FIRST");
    TATFormattedMessage formattedMessageUT(EXPECTED_MESSAGE_TEXT);
    formattedMessageUT.Append(wxT("NOTFIRST"));

    // Execution
    const TATFormattedMessage::TMessagePart* pMessagePart = formattedMessageUT.GetFirstAndResetPointer();
    
    // Verification
    BOOST_CHECK_EQUAL(pMessagePart->first, EXPECTED_MESSAGE_TEXT);
}

/// <summary>
/// Checks that the pointer to the current message part is reset when calling this method.
/// </summary>
QTEST_CASE ( GetFirstAndResetPointer_ResetsPointerToCurrentMessagePart_Test )
{
    // Preparation
    const wxString EXPECTED_MESSAGE_TEXT_AFTER_RESET = wxT("SECOND");

    TATFormattedMessage formattedMessageUT(wxT("FIRST"));
    formattedMessageUT.Append(EXPECTED_MESSAGE_TEXT_AFTER_RESET);
    formattedMessageUT.Append(wxT("THIRD"));

    formattedMessageUT.GetFirstAndResetPointer();
    formattedMessageUT.GetNext();
    formattedMessageUT.GetNext();

    // Execution
    formattedMessageUT.GetFirstAndResetPointer();
    const TATFormattedMessage::TMessagePart* pMessagePart = formattedMessageUT.GetNext();
    
    // Verification
    BOOST_CHECK_EQUAL(pMessagePart->first, EXPECTED_MESSAGE_TEXT_AFTER_RESET);
}

/// <summary>
/// Checks that returns the next message part.
/// </summary>
QTEST_CASE ( GetNext_ReturnsNextMessagePart_Test )
{
    // Preparation
    const wxString EXPECTED_MESSAGE_TEXT = wxT("SECOND");

    TATFormattedMessage formattedMessageUT(wxT("FIRST"));
    formattedMessageUT.Append(EXPECTED_MESSAGE_TEXT);
    formattedMessageUT.Append(wxT("THIRD"));

    // Execution
    formattedMessageUT.GetFirstAndResetPointer();
    const TATFormattedMessage::TMessagePart* pMessagePart = formattedMessageUT.GetNext();
    
    // Verification
    BOOST_CHECK_EQUAL(pMessagePart->first, EXPECTED_MESSAGE_TEXT);
}

/// <summary>
/// Checks that the pointer to the current message part is moved forward.
/// </summary>
QTEST_CASE ( GetNext_MovesPointerToCurrentMessagePartForward_Test )
{
    // Preparation
    const wxString SECOND_MESSAGE_TEXT = wxT("SECOND");
    const wxString THIRD_MESSAGE_TEXT = wxT("THIRD");

    TATFormattedMessage formattedMessageUT(wxT("FIRST"));
    formattedMessageUT.Append(SECOND_MESSAGE_TEXT);
    formattedMessageUT.Append(THIRD_MESSAGE_TEXT);

    // Execution
    formattedMessageUT.GetFirstAndResetPointer();
    const TATFormattedMessage::TMessagePart* pSecondPart = formattedMessageUT.GetNext();
    const TATFormattedMessage::TMessagePart* pThirdPart = formattedMessageUT.GetNext();
    
    // Verification
    BOOST_CHECK_EQUAL(pSecondPart->first, SECOND_MESSAGE_TEXT);
    BOOST_CHECK_EQUAL(pThirdPart->first, THIRD_MESSAGE_TEXT);
}

/// <summary>
/// Checks that returns null when there is no "next" message part.
/// </summary>
QTEST_CASE ( GetNext_ReturnsNullWhenThereAreNoMoreParts_Test )
{
    // Preparation
    const TATFormattedMessage::TMessagePart* EXPECTED_RESULT = null_t;
    TATFormattedMessage formattedMessageUT(wxT(""));

    // Execution
    formattedMessageUT.GetFirstAndResetPointer();
    const TATFormattedMessage::TMessagePart* pMessagePart = formattedMessageUT.GetNext();
    
    // Verification
    BOOST_CHECK_EQUAL(pMessagePart, EXPECTED_RESULT);
}

/// <summary>
/// Checks that returns null when the message is empty.
/// </summary>
QTEST_CASE ( GetNext_ReturnsNullWhenMessageIsEmpty_Test )
{
    // Preparation
    const TATFormattedMessage::TMessagePart* EXPECTED_RESULT = null_t;
    TATFormattedMessage formattedMessageUT;

    // Execution
    const TATFormattedMessage::TMessagePart* pMessagePart = formattedMessageUT.GetNext();
    
    // Verification
    BOOST_CHECK_EQUAL(pMessagePart, EXPECTED_RESULT);
}

// End - Test Suite: TATFormattedMessage
QTEST_SUITE_END()
