// [TERMS&CONDITIONS]

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../../testsystem/TestingExternalDefinitions.h"

#include "TestExecution/TATTestModulesExecutionInfo.h"

using Kinesis::TestAutomationTool::Backend::TATTestModulesExecutionInfo;

QTEST_SUITE_BEGIN( TATTestModulesExecutionInfo_TestSuite )

/// <summary>
/// Checks that the default values have not changed since the last test execution.
/// </summary>
QTEST_CASE ( Constructor_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const wxString EXPECTED_TESTMODULESPATH = wxT("");
    const wxString EXPECTED_RESULTSPATH = wxT("");
    const wxString EXPECTED_TESTPROJECTPATH = wxT("");

	// [Execution]
    TATTestModulesExecutionInfo testModulesExecutionInfoUT;
    
    wxString strTestModulesPath = testModulesExecutionInfoUT.GetTestModulesPath();
    wxString strResultsPath = testModulesExecutionInfoUT.GetResultsPath();
    wxString strTestProjectPath = testModulesExecutionInfoUT.GetTestProjectPath();

    // [Verification]
    BOOST_CHECK_EQUAL(strTestModulesPath, EXPECTED_TESTMODULESPATH);
    BOOST_CHECK_EQUAL(strResultsPath, EXPECTED_RESULTSPATH);
    BOOST_CHECK_EQUAL(strTestProjectPath, EXPECTED_TESTPROJECTPATH);
}

/// <summary>
/// Checks that the test modules' path is correctly retrieved.
/// </summary>
QTEST_CASE ( GetTestModulesPath_TestModulesPathIsCorrectlyRetrieved_Test )
{
    // Preparation
    const wxString EXPECTED_TESTMODULESPATH = "TESTMODULESPATH";
    TATTestModulesExecutionInfo testModulesExecutionInfoUT;
    testModulesExecutionInfoUT.SetTestModulesPath(EXPECTED_TESTMODULESPATH);

	// Execution
    wxString strTestModulesPath = testModulesExecutionInfoUT.GetTestModulesPath();
    
    // Verification
    BOOST_CHECK_EQUAL(strTestModulesPath, EXPECTED_TESTMODULESPATH);
}

/// <summary>
/// Checks that the test modules' path is correctly stored.
/// </summary>
QTEST_CASE ( SetTestModulesPath_TestModulesPathIsCorrectlyStored_Test )
{
    // Preparation
    const wxString EXPECTED_TESTMODULESPATH = "TESTMODULESPATH";

	// Execution
    TATTestModulesExecutionInfo testModulesExecutionInfoUT;
    testModulesExecutionInfoUT.SetTestModulesPath(EXPECTED_TESTMODULESPATH);
    
    // Verification
    BOOST_CHECK_EQUAL(testModulesExecutionInfoUT.GetTestModulesPath(), EXPECTED_TESTMODULESPATH);
}

/// <summary>
/// Checks that the result files' path is correctly retrieved.
/// </summary>
QTEST_CASE ( GetResultsPath_ResultsPathIsCorrectlyRetrieved_Test )
{
    // Preparation
    const wxString EXPECTED_RESULTSPATH = "RESULTSPATH";
    TATTestModulesExecutionInfo testModulesExecutionInfoUT;
    testModulesExecutionInfoUT.SetResultsPath(EXPECTED_RESULTSPATH);

	// Execution
    wxString strResultsPath = testModulesExecutionInfoUT.GetResultsPath();
    
    // Verification
    BOOST_CHECK_EQUAL(strResultsPath, EXPECTED_RESULTSPATH);
}

/// <summary>
/// Checks that the test modules' path is correctly stored.
/// </summary>
QTEST_CASE ( SetResultsPath_ResultsPathIsCorrectlyStored_Test )
{
    // Preparation
    const wxString EXPECTED_RESULTSPATH = "RESULTSPATH";

	// Execution
    TATTestModulesExecutionInfo testModulesExecutionInfoUT;
    testModulesExecutionInfoUT.SetResultsPath(EXPECTED_RESULTSPATH);
    
    // Verification
    BOOST_CHECK_EQUAL(testModulesExecutionInfoUT.GetResultsPath(), EXPECTED_RESULTSPATH);
}

/// <summary>
/// Checks that the test project's path is correctly retrieved.
/// </summary>
QTEST_CASE ( GetTestProjectPath_TestProjectPathIsCorrectlyRetrieved_Test )
{
    // Preparation
    const wxString EXPECTED_TESTPROJECTPATH = "TESTPROJECTPATH";
    TATTestModulesExecutionInfo testModulesExecutionInfoUT;
    testModulesExecutionInfoUT.SetTestProjectPath(EXPECTED_TESTPROJECTPATH);

	// Execution
    wxString strTestProjectPath = testModulesExecutionInfoUT.GetTestProjectPath();
    
    // Verification
    BOOST_CHECK_EQUAL(strTestProjectPath, EXPECTED_TESTPROJECTPATH);
}

/// <summary>
/// Checks that the test project's path is correctly stored.
/// </summary>
QTEST_CASE ( SetTestProjectPath_TestProjectPathIsCorrectlyStored_Test )
{
    // Preparation
    const wxString EXPECTED_TESTPROJECTPATH = "TESTPROJECTPATH";

	// Execution
    TATTestModulesExecutionInfo testModulesExecutionInfoUT;
    testModulesExecutionInfoUT.SetTestProjectPath(EXPECTED_TESTPROJECTPATH);
    
    // Verification
    BOOST_CHECK_EQUAL(testModulesExecutionInfoUT.GetTestProjectPath(), EXPECTED_TESTPROJECTPATH);
}

// End - Test Suite: TATTestModulesExecutionInfo
QTEST_SUITE_END()
