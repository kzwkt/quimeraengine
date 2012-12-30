// [TERMS&CONDITIONS]

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../../testsystem/TestingExternalDefinitions.h"

#include "TestExecution/TATTestResultNode.h"

using Kinesis::TestAutomationTool::Backend::TATTestResultNode;

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
    
	// [Execution]
    TATTestResultNode nodeUT;
    
    ETATResult eResult = nodeUT.GetResult();
    int nTime = nodeUT.GetTime();
    wxString strMessage = nodeUT.GetMessage();
    wxString strName = nodeUT.GetName();
    
    // [Verification]
    BOOST_CHECK_EQUAL(eResult.ToString(), EXPECTED_RESULT.ToString());
    BOOST_CHECK_EQUAL(nTime, EXPECTED_TIME);
    BOOST_CHECK_EQUAL(strMessage, EXPECTED_MESSAGE);
    BOOST_CHECK_EQUAL(strName, EXPECTED_NAME);
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
    
	// [Execution]
    TATTestResultNode nodeUT(EXPECTED_NAME);
    
    ETATResult eResult = nodeUT.GetResult();
    int nTime = nodeUT.GetTime();
    wxString strMessage = nodeUT.GetMessage();
    wxString strName = nodeUT.GetName();
    
    // [Verification]
    BOOST_CHECK_EQUAL(eResult.ToString(), EXPECTED_RESULT.ToString());
    BOOST_CHECK_EQUAL(nTime, EXPECTED_TIME);
    BOOST_CHECK_EQUAL(strMessage, EXPECTED_MESSAGE);
    BOOST_CHECK_EQUAL(strName, EXPECTED_NAME);
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
    
	// [Execution]
    TATTestResultNode nodeUT(EXPECTED_NAME, EXPECTED_RESULT, EXPECTED_MESSAGE, EXPECTED_TIME);
    
    ETATResult eResult = nodeUT.GetResult();
    int nTime = nodeUT.GetTime();
    wxString strMessage = nodeUT.GetMessage();
    wxString strName = nodeUT.GetName();
    
    // [Verification]
    BOOST_CHECK_EQUAL(eResult.ToString(), EXPECTED_RESULT.ToString());
    BOOST_CHECK_EQUAL(nTime, EXPECTED_TIME);
    BOOST_CHECK_EQUAL(strMessage, EXPECTED_MESSAGE);
    BOOST_CHECK_EQUAL(strName, EXPECTED_NAME);
}

/// <summary>
/// Checks that the result is correctly retrieved.
/// </summary>
QTEST_CASE ( GetResult_ResultIsCorrectlyRetrieved_Test )
{
    using Kinesis::TestAutomationTool::Backend::ETATResult;

    // [Preparation]
    const ETATResult EXPECTED_RESULT = ETATResult::E_Success;
    TATTestResultNode nodeUT(wxT(""), EXPECTED_RESULT, wxT(""), 0);

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
    TATTestResultNode nodeUT(wxT(""), ETATResult::E_NoResult, EXPECTED_MESSAGE, 0);

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
    TATTestResultNode nodeUT(wxT(""), ETATResult::E_NoResult, wxT(""), EXPECTED_TIME);

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

// End - Test Suite: TATTestResultNode
QTEST_SUITE_END()
