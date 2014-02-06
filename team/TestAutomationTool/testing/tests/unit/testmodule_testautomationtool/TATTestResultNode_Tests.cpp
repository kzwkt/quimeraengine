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

#include "TestResults/TATTestResultNode.h"

using Kinesis::TestAutomationTool::Backend::TATTestResultNode;
using Kinesis::TestAutomationTool::Backend::ETATTestResultNodeType;

QTEST_SUITE_BEGIN( TATTestResultNode_TestSuite )

/// <summary>
/// Checks that the default values have not changed since last execution.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    using Kinesis::TestAutomationTool::Backend::ETATResult;

    // [Preparation]
    const wxString EXPECTED_NAME = wxT("");
    const ETATResult EXPECTED_RESULT = ETATResult::E_NoResult;
    const wxString EXPECTED_MESSAGE = wxT("");
    const int EXPECTED_TIME = 0;
    const ETATTestResultNodeType EXPECTED_TYPE = ETATTestResultNodeType::E_Root;
    
	// [Execution]
    TATTestResultNode nodeUT;
    
    ETATResult eResult = nodeUT.GetResult();
    int nTime = nodeUT.GetTime();
    wxString strMessage = nodeUT.GetMessage();
    wxString strName = nodeUT.GetName();
    ETATTestResultNodeType eType = nodeUT.GetNodeType();
    
    // [Verification]
    BOOST_CHECK_EQUAL(eResult.ToString(), EXPECTED_RESULT.ToString());
    BOOST_CHECK_EQUAL(nTime, EXPECTED_TIME);
    BOOST_CHECK_EQUAL(strMessage, EXPECTED_MESSAGE);
    BOOST_CHECK_EQUAL(strName, EXPECTED_NAME);
    BOOST_CHECK_EQUAL(eType.ToString(), EXPECTED_TYPE.ToString());
}

/// <summary>
/// Checks that the passed values are correctly stored.
/// </summary>
QTEST_CASE ( Constructor2_ValuesAreCorrectlyStored_Test )
{
    using Kinesis::TestAutomationTool::Backend::ETATResult;

    // [Preparation]
    const wxString EXPECTED_NAME = wxT("NAME");
    const ETATResult EXPECTED_RESULT = ETATResult::E_NoResult;
    const wxString EXPECTED_MESSAGE = wxT("");
    const int EXPECTED_TIME = 0;
    const ETATTestResultNodeType EXPECTED_TYPE = ETATTestResultNodeType::E_Root;

	// [Execution]
    TATTestResultNode nodeUT(EXPECTED_NAME);
    
    ETATResult eResult = nodeUT.GetResult();
    int nTime = nodeUT.GetTime();
    wxString strMessage = nodeUT.GetMessage();
    wxString strName = nodeUT.GetName();
    ETATTestResultNodeType eType = nodeUT.GetNodeType();

    // [Verification]
    BOOST_CHECK_EQUAL(eResult.ToString(), EXPECTED_RESULT.ToString());
    BOOST_CHECK_EQUAL(nTime, EXPECTED_TIME);
    BOOST_CHECK_EQUAL(strMessage, EXPECTED_MESSAGE);
    BOOST_CHECK_EQUAL(strName, EXPECTED_NAME);
    BOOST_CHECK_EQUAL(eType.ToString(), EXPECTED_TYPE.ToString());
}

/// <summary>
/// Checks that the passed values are correctly stored.
/// </summary>
QTEST_CASE ( Constructor3_ValuesAreCorrectlyStored_Test )
{
    using Kinesis::TestAutomationTool::Backend::ETATResult;

    // [Preparation]
    const wxString EXPECTED_NAME = wxT("NAME");
    const ETATResult EXPECTED_RESULT = ETATResult::E_Success;
    const wxString EXPECTED_MESSAGE = wxT("MESSAGE");
    const int EXPECTED_TIME = 999;
    const ETATTestResultNodeType EXPECTED_TYPE = ETATTestResultNodeType::E_Suite;

	// [Execution]
    TATTestResultNode nodeUT(EXPECTED_NAME, EXPECTED_RESULT, EXPECTED_MESSAGE, EXPECTED_TIME, EXPECTED_TYPE);
    
    ETATResult eResult = nodeUT.GetResult();
    int nTime = nodeUT.GetTime();
    wxString strMessage = nodeUT.GetMessage();
    wxString strName = nodeUT.GetName();
    ETATTestResultNodeType eType = nodeUT.GetNodeType();
    
    // [Verification]
    BOOST_CHECK_EQUAL(eResult.ToString(), EXPECTED_RESULT.ToString());
    BOOST_CHECK_EQUAL(nTime, EXPECTED_TIME);
    BOOST_CHECK_EQUAL(strMessage, EXPECTED_MESSAGE);
    BOOST_CHECK_EQUAL(strName, EXPECTED_NAME);
    BOOST_CHECK_EQUAL(eType.ToString(), EXPECTED_TYPE.ToString());
}

/// <summary>
/// Checks that the result is correctly retrieved.
/// </summary>
QTEST_CASE ( GetResult_ResultIsCorrectlyRetrieved_Test )
{
    using Kinesis::TestAutomationTool::Backend::ETATResult;

    // [Preparation]
    const ETATResult EXPECTED_RESULT = ETATResult::E_Success;
    TATTestResultNode nodeUT(wxT(""), EXPECTED_RESULT, wxT(""), 0, ETATTestResultNodeType::E_Root);

	// [Execution]
    ETATResult eResult = nodeUT.GetResult();
    
    // [Verification]
    BOOST_CHECK_EQUAL(eResult.ToString(), EXPECTED_RESULT.ToString());
}

/// <summary>
/// Checks that the result is correctly stored.
/// </summary>
QTEST_CASE ( SetResult_ResultIsCorrectlyStored_Test )
{
    using Kinesis::TestAutomationTool::Backend::ETATResult;

    // [Preparation]
    const ETATResult EXPECTED_RESULT = ETATResult::E_Success;

	// [Execution]
    TATTestResultNode nodeUT;
    nodeUT.SetResult(EXPECTED_RESULT);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nodeUT.GetResult().ToString(), EXPECTED_RESULT.ToString());
}

/// <summary>
/// Checks that the message is correctly retrieved.
/// </summary>
QTEST_CASE ( GetMessage_MessageIsCorrectlyRetrieved_Test )
{
    using Kinesis::TestAutomationTool::Backend::ETATResult;

    // [Preparation]
    const wxString EXPECTED_MESSAGE = wxT("MESSAGE");
    TATTestResultNode nodeUT(wxT(""), ETATResult::E_NoResult, EXPECTED_MESSAGE, 0, ETATTestResultNodeType::E_Root);

	// [Execution]
    wxString strMessage = nodeUT.GetMessage();
    
    // [Verification]
    BOOST_CHECK_EQUAL(strMessage, EXPECTED_MESSAGE);
}

/// <summary>
/// Checks that the message is correctly stored.
/// </summary>
QTEST_CASE ( SetMessage_MessageIsCorrectlyStored_Test )
{
    // [Preparation]
    const wxString EXPECTED_MESSAGE = wxT("MESSAGE");

	// [Execution]
    TATTestResultNode nodeUT;
    nodeUT.SetMessage(EXPECTED_MESSAGE);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nodeUT.GetMessage(), EXPECTED_MESSAGE);
}

/// <summary>
/// Checks that the testing time is correctly retrieved.
/// </summary>
QTEST_CASE ( GetTime_TimeIsCorrectlyRetrieved_Test )
{
    using Kinesis::TestAutomationTool::Backend::ETATResult;

    // [Preparation]
    const int EXPECTED_TIME = 999;
    TATTestResultNode nodeUT(wxT(""), ETATResult::E_NoResult, wxT(""), EXPECTED_TIME, ETATTestResultNodeType::E_Root);

	// [Execution]
    int nTime = nodeUT.GetTime();
    
    // [Verification]
    BOOST_CHECK_EQUAL(nTime, EXPECTED_TIME);
}

/// <summary>
/// Checks that the testing time is correctly stored.
/// </summary>
QTEST_CASE ( SetTime_TimeIsCorrectlyStored_Test )
{
    // [Preparation]
    const int EXPECTED_TIME = 999;

	// [Execution]
    TATTestResultNode nodeUT;
    nodeUT.SetTime(EXPECTED_TIME);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nodeUT.GetTime(), EXPECTED_TIME);
}

/// <summary>
/// Checks that the test node type is correctly retrieved.
/// </summary>
QTEST_CASE ( GetNodeType_TypeIsCorrectlyRetrieved_Test )
{
    using Kinesis::TestAutomationTool::Backend::ETATResult;

    // [Preparation]
    const ETATTestResultNodeType EXPECTED_TYPE = ETATTestResultNodeType::E_Suite;
    TATTestResultNode nodeUT(wxT(""), ETATResult::E_NoResult, wxT(""), 0, EXPECTED_TYPE);

	// [Execution]
    ETATTestResultNodeType eType = nodeUT.GetNodeType();
    
    // [Verification]
    BOOST_CHECK_EQUAL(eType.ToString(), EXPECTED_TYPE.ToString());
}

/// <summary>
/// Checks that the test node type is correctly stored.
/// </summary>
QTEST_CASE ( SetNodeType_TypeIsCorrectlyStored_Test )
{
    // [Preparation]
    const ETATTestResultNodeType EXPECTED_TYPE = ETATTestResultNodeType::E_Suite;

	// [Execution]
    TATTestResultNode nodeUT;
    nodeUT.SetNodeType(EXPECTED_TYPE);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nodeUT.GetNodeType().ToString(), EXPECTED_TYPE.ToString());
}

/// <summary>
/// Checks that it returns true when the result is a fail.
/// </summary>
QTEST_CASE ( HasErrors_ReturnsTrueWhenTheResultIsAFail_Test )
{
    using Kinesis::TestAutomationTool::Backend::ETATResult;

    // [Preparation]
    TATTestResultNode nodeUT(wxT(""), ETATResult::E_Fail, wxT(""), 0, ETATTestResultNodeType::E_Root);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = nodeUT.HasErrors();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns true when the result is not a fail but one of its children is.
/// </summary>
QTEST_CASE ( HasErrors_ReturnsTrueWhenOneChildIsAFail_Test )
{
    using Kinesis::TestAutomationTool::Backend::ETATResult;

    // [Preparation]
    TATTestResultNode nodeUT(wxT(""), ETATResult::E_NoResult, wxT(""), 0, ETATTestResultNodeType::E_Root);
    nodeUT.AddChild(new TATTestResultNode(wxT(""), ETATResult::E_Fail, wxT(""), 0, ETATTestResultNodeType::E_Module));
    nodeUT.AddChild(new TATTestResultNode(wxT(""), ETATResult::E_NoResult, wxT(""), 0, ETATTestResultNodeType::E_Module));
    nodeUT.AddChild(new TATTestResultNode(wxT(""), ETATResult::E_Success, wxT(""), 0, ETATTestResultNodeType::E_Module));
    nodeUT.AddChild(new TATTestResultNode(wxT(""), ETATResult::E_Error, wxT(""), 0, ETATTestResultNodeType::E_Module));

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = nodeUT.HasErrors();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns false when the result and its children are not fails.
/// </summary>
QTEST_CASE ( HasErrors_ReturnsFalseWhenNeitherTheResultNorItsChildrenAreFails_Test )
{
    using Kinesis::TestAutomationTool::Backend::ETATResult;

    // [Preparation]
    TATTestResultNode nodeUT(wxT(""), ETATResult::E_NoResult, wxT(""), 0, ETATTestResultNodeType::E_Root);
    nodeUT.AddChild(new TATTestResultNode(wxT(""), ETATResult::E_NoResult, wxT(""), 0, ETATTestResultNodeType::E_Module));
    nodeUT.AddChild(new TATTestResultNode(wxT(""), ETATResult::E_Success, wxT(""), 0, ETATTestResultNodeType::E_Module));

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = nodeUT.HasErrors();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

// End - Test Suite: TATTestResultNode
QTEST_SUITE_END()
