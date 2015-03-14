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

#include "TestResults/TATTestResultInfo.h"
#include "TestResults/TATTestResultNode.h"

using Kinesis::TestAutomationTool::Backend::TATTestResultInfo;

QTEST_SUITE_BEGIN( TATTestResultInfo_TestSuite )

/// <summary>
/// Checks that the default values have not changed since last execution.
/// </summary>
QTEST_CASE ( Constructor_DefaultValuesHaveNotChanged_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATTestResultNode;

    // [Preparation]
    wxString EXPECTED_FLAGCOMBINATIONNAME = wxT("");
    wxString EXPECTED_FLAGCOMBINATIONVALUES = wxT("");
    wxString EXPECTED_COMPILATIONCONFIGURATION = wxT("");
    wxString EXPECTED_COMPILERNAME = wxT("");
    TATTestResultNode* EXPECTED_TESTRESULTTREE = NULL;

	// [Execution]
    TATTestResultInfo resultInfoUT;

    wxString strFlagCombinationName = resultInfoUT.GetFlagCombinationName();
    wxString strFlagCombinationValues = resultInfoUT.GetFlagCombinationValues();
    wxString strCompilationConfiguration = resultInfoUT.GetCompilationConfiguration();
    wxString strCompilerName = resultInfoUT.GetCompilerName();
    TATTestResultNode* pTestResultTree = resultInfoUT.GetResultTree();

    // [Verification]
    BOOST_CHECK_EQUAL(strFlagCombinationName, EXPECTED_FLAGCOMBINATIONNAME);
    BOOST_CHECK_EQUAL(strFlagCombinationValues, EXPECTED_FLAGCOMBINATIONVALUES);
    BOOST_CHECK_EQUAL(strCompilationConfiguration, EXPECTED_COMPILATIONCONFIGURATION);
    BOOST_CHECK_EQUAL(strCompilerName, EXPECTED_COMPILERNAME);
    BOOST_CHECK_EQUAL(pTestResultTree, EXPECTED_TESTRESULTTREE);
}

/// <summary>
/// Checks that the flag combination name is correctly retrieved.
/// </summary>
QTEST_CASE ( GetFlagCombinationName_FlagCombinationNameIsCorrectlyRetrieved_Test )
{
    // [Preparation]
    const wxString EXPECTED_FLAGCOMBINATIONNAME = wxT("FLAGCOMBINATIONNAME");
    TATTestResultInfo infoUT;
    infoUT.SetFlagCombinationName(EXPECTED_FLAGCOMBINATIONNAME);

	// [Execution]
    wxString strFlagCombinationName = infoUT.GetFlagCombinationName();
    
    // [Verification]
    BOOST_CHECK_EQUAL(strFlagCombinationName, EXPECTED_FLAGCOMBINATIONNAME);
}

/// <summary>
/// Checks that the flag combination name is correctly stored.
/// </summary>
QTEST_CASE ( SetFlagCombinationName_FlagCombinationNameIsCorrectlyStored_Test )
{
    // [Preparation]
    const wxString EXPECTED_FLAGCOMBINATIONNAME = wxT("FLAGCOMBINATIONNAME");

	// [Execution]
    TATTestResultInfo infoUT;
    infoUT.SetFlagCombinationName(EXPECTED_FLAGCOMBINATIONNAME);
    
    // [Verification]
    BOOST_CHECK_EQUAL(infoUT.GetFlagCombinationName(), EXPECTED_FLAGCOMBINATIONNAME);
}

/// <summary>
/// Checks that the flag combination values are correctly retrieved.
/// </summary>
QTEST_CASE ( GetFlagCombinationValues_FlagCombinationValuesAreCorrectlyRetrieved_Test )
{
    // [Preparation]
    const wxString EXPECTED_FLAGCOMBINATIONVALUES = wxT("FLAGCOMBINATIONVALUES");
    TATTestResultInfo infoUT;
    infoUT.SetFlagCombinationValues(EXPECTED_FLAGCOMBINATIONVALUES);

	// [Execution]
    wxString strFlagCombinationValues = infoUT.GetFlagCombinationValues();
    
    // [Verification]
    BOOST_CHECK_EQUAL(strFlagCombinationValues, EXPECTED_FLAGCOMBINATIONVALUES);
}

/// <summary>
/// Checks that the flag combination values are correctly stored.
/// </summary>
QTEST_CASE ( SetFlagCombinationValues_FlagCombinationValuesAreCorrectlyStored_Test )
{
    // [Preparation]
    const wxString EXPECTED_FLAGCOMBINATIONVALUES = wxT("FLAGCOMBINATIONVALUES");

	// [Execution]
    TATTestResultInfo infoUT;
    infoUT.SetFlagCombinationValues(EXPECTED_FLAGCOMBINATIONVALUES);
    
    // [Verification]
    BOOST_CHECK_EQUAL(infoUT.GetFlagCombinationValues(), EXPECTED_FLAGCOMBINATIONVALUES);
}

/// <summary>
/// Checks that the compilation configuration is correctly retrieved.
/// </summary>
QTEST_CASE ( GetCompilationConfiguration_CompilationConfigurationIsCorrectlyRetrieved_Test )
{
    // [Preparation]
    const wxString EXPECTED_COMPILATIONCONFIGURATION = wxT("COMPILATIONCONFIGURATION");
    TATTestResultInfo infoUT;
    infoUT.SetCompilationConfiguration(EXPECTED_COMPILATIONCONFIGURATION);

	// [Execution]
    wxString strCompilationConfiguration = infoUT.GetCompilationConfiguration();
    
    // [Verification]
    BOOST_CHECK_EQUAL(strCompilationConfiguration, EXPECTED_COMPILATIONCONFIGURATION);
}

/// <summary>
/// Checks that the compilation configuration is correctly stored.
/// </summary>
QTEST_CASE ( SetCompilationConfiguration_CompilationConfigurationIsCorrectlyStored_Test )
{
    // [Preparation]
    const wxString EXPECTED_COMPILATIONCONFIGURATION = wxT("COMPILATIONCONFIGURATION");

	// [Execution]
    TATTestResultInfo infoUT;
    infoUT.SetCompilationConfiguration(EXPECTED_COMPILATIONCONFIGURATION);
    
    // [Verification]
    BOOST_CHECK_EQUAL(infoUT.GetCompilationConfiguration(), EXPECTED_COMPILATIONCONFIGURATION);
}

/// <summary>
/// Checks that the compiler name is correctly retrieved.
/// </summary>
QTEST_CASE ( GetCompilerName_CompilerNameIsCorrectlyRetrieved_Test )
{
    // [Preparation]
    const wxString EXPECTED_COMPILERNAME = wxT("COMPILERNAME");
    TATTestResultInfo infoUT;
    infoUT.SetCompilerName(EXPECTED_COMPILERNAME);

	// [Execution]
    wxString strCompilerName = infoUT.GetCompilerName();
    
    // [Verification]
    BOOST_CHECK_EQUAL(strCompilerName, EXPECTED_COMPILERNAME);
}

/// <summary>
/// Checks that the compiler name is correctly stored.
/// </summary>
QTEST_CASE ( SetCompilerName_CompilerNameIsCorrectlyStored_Test )
{
    // [Preparation]
    const wxString EXPECTED_COMPILERNAME = wxT("COMPILERNAME");

	// [Execution]
    TATTestResultInfo infoUT;
    infoUT.SetCompilerName(EXPECTED_COMPILERNAME);
    
    // [Verification]
    BOOST_CHECK_EQUAL(infoUT.GetCompilerName(), EXPECTED_COMPILERNAME);
}

/// <summary>
/// Checks that the test result tree is correctly retrieved.
/// </summary>
QTEST_CASE ( GetResultTree_ResultTreeIsCorrectlyRetrieved_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATTestResultNode;

    // [Preparation]
    TATTestResultNode EXPECTED_RESULTTREE;
    TATTestResultInfo infoUT;
    infoUT.SetResultTree(&EXPECTED_RESULTTREE);

	// [Execution]
    TATTestResultNode* pResultTree = infoUT.GetResultTree();
    
    // [Verification]
    BOOST_CHECK_EQUAL(pResultTree, &EXPECTED_RESULTTREE);
}

/// <summary>
/// Checks that the test result tree is correctly stored.
/// </summary>
QTEST_CASE ( SetResultTree_ResultTreeIsCorrectlyStored_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATTestResultNode;

    // [Preparation]
    TATTestResultNode EXPECTED_RESULTTREE;

	// [Execution]
    TATTestResultInfo infoUT;
    infoUT.SetResultTree(&EXPECTED_RESULTTREE);
    
    // [Verification]
    BOOST_CHECK_EQUAL(infoUT.GetResultTree(), &EXPECTED_RESULTTREE);
}


// End - Test Suite: TATTestResultInfo
QTEST_SUITE_END()
