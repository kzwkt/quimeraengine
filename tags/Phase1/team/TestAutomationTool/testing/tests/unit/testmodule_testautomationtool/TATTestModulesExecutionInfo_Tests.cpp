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
/// Checks that it returns true when objects are equal.
/// </summary>
QTEST_CASE ( OperatorEquality_ReturnsTrueWhenObjectsAreEqual_Test )
{
    // Preparation
    const wxString EXPECTED_TESTMODULESPATH = wxT("A");
    const wxString EXPECTED_RESULTSPATH = wxT("B");
    const wxString EXPECTED_TESTPROJECTPATH = wxT("C");

    TATTestModulesExecutionInfo executionInfoA;
    executionInfoA.SetResultsPath(EXPECTED_TESTMODULESPATH);
    executionInfoA.SetTestModulesPath(EXPECTED_RESULTSPATH);
    executionInfoA.SetTestProjectPath(EXPECTED_TESTPROJECTPATH);

    TATTestModulesExecutionInfo executionInfoB;
    executionInfoB.SetResultsPath(EXPECTED_TESTMODULESPATH);
    executionInfoB.SetTestModulesPath(EXPECTED_RESULTSPATH);
    executionInfoB.SetTestProjectPath(EXPECTED_TESTPROJECTPATH);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = executionInfoA == executionInfoB;
    
    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns false when objects are not equal.
/// </summary>
QTEST_CASE ( OperatorEquality_ReturnsFalseWhenObjectsAreNotEqual_Test )
{
    // Preparation
    const wxString EXPECTED_TESTMODULESPATH = wxT("A");
    const wxString EXPECTED_RESULTSPATH = wxT("DIFFERENT");
    const wxString EXPECTED_TESTPROJECTPATH = wxT("C");
    
    const wxString DIFFERENT_VALUE("X");

    TATTestModulesExecutionInfo executionInfoA;
    executionInfoA.SetResultsPath(DIFFERENT_VALUE);
    executionInfoA.SetTestModulesPath(EXPECTED_RESULTSPATH);
    executionInfoA.SetTestProjectPath(EXPECTED_TESTPROJECTPATH);

    TATTestModulesExecutionInfo executionInfoB;
    executionInfoB.SetResultsPath(EXPECTED_TESTMODULESPATH);
    executionInfoB.SetTestModulesPath(EXPECTED_RESULTSPATH);
    executionInfoB.SetTestProjectPath(EXPECTED_TESTPROJECTPATH);

    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult = executionInfoA == executionInfoB;
    
    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns false when objects are equal.
/// </summary>
QTEST_CASE ( OperatorInequality_ReturnsFalseWhenObjectsAreEqual_Test )
{
    // Preparation
    const wxString EXPECTED_TESTMODULESPATH = wxT("A");
    const wxString EXPECTED_RESULTSPATH = wxT("B");
    const wxString EXPECTED_TESTPROJECTPATH = wxT("C");

    TATTestModulesExecutionInfo executionInfoA;
    executionInfoA.SetResultsPath(EXPECTED_TESTMODULESPATH);
    executionInfoA.SetTestModulesPath(EXPECTED_RESULTSPATH);
    executionInfoA.SetTestProjectPath(EXPECTED_TESTPROJECTPATH);

    TATTestModulesExecutionInfo executionInfoB;
    executionInfoB.SetResultsPath(EXPECTED_TESTMODULESPATH);
    executionInfoB.SetTestModulesPath(EXPECTED_RESULTSPATH);
    executionInfoB.SetTestProjectPath(EXPECTED_TESTPROJECTPATH);

    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult = executionInfoA != executionInfoB;
    
    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns true when objects are not equal.
/// </summary>
QTEST_CASE ( OperatorInequality_ReturnsTrueWhenObjectsAreNotEqual_Test )
{
    // Preparation
    const wxString EXPECTED_TESTMODULESPATH = wxT("A");
    const wxString EXPECTED_RESULTSPATH = wxT("B");
    const wxString EXPECTED_TESTPROJECTPATH = wxT("C");
    
    const wxString DIFFERENT_VALUE("X");

    TATTestModulesExecutionInfo executionInfoA;
    executionInfoA.SetResultsPath(DIFFERENT_VALUE);
    executionInfoA.SetTestModulesPath(EXPECTED_RESULTSPATH);
    executionInfoA.SetTestProjectPath(EXPECTED_TESTPROJECTPATH);

    TATTestModulesExecutionInfo executionInfoB;
    executionInfoB.SetResultsPath(EXPECTED_TESTMODULESPATH);
    executionInfoB.SetTestModulesPath(EXPECTED_RESULTSPATH);
    executionInfoB.SetTestProjectPath(EXPECTED_TESTPROJECTPATH);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = executionInfoA != executionInfoB;
    
    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
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
