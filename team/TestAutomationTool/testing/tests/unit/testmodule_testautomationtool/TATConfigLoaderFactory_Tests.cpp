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

#include "TestConfiguration/TATConfigLoaderFactory.h"
#include "TestConfiguration/ETATConfigNodeType.h"
#include "TestConfiguration/TATRuleNode.h"
#include "TATConfigLoaderFactoryWhiteBox.h"


using Kinesis::TestAutomationTool::Backend::TATConfigLoaderFactory;
using Kinesis::TestAutomationTool::Backend::Test::TATConfigLoaderFactoryWhiteBox;
using Kinesis::TestAutomationTool::Backend::ETATConfigurationSource;
using Kinesis::TestAutomationTool::Backend::ETATConfigNodeType;
using Kinesis::TestAutomationTool::Backend::TATRuleNode;
using Kinesis::TestAutomationTool::Backend::ITATConfigLoader;

QTEST_SUITE_BEGIN( TATConfigLoaderFactory_TestSuite )

/// <summary>
/// Checks that a configuration loader implementation is returned for every source available.
/// </summary>
QTEST_CASE ( CreateConfigLoader_ThereIsAConfigLoaderForEverySource_Test )
{
    // Preparation
    const TATConfigLoaderFactory FACTORY_UT = TATConfigLoaderFactory();

    ETATConfigurationSource INI_FILE_SOURCE = ETATConfigurationSource::E_INI_FILE;
    ITATConfigLoader* NON_EXISTENT_IMPLEMENTATION = null_t;

	// Execution
    ITATConfigLoader* pConfigLoaderFromIniFile = FACTORY_UT.CreateConfigLoader(INI_FILE_SOURCE);

    // Verification
    BOOST_CHECK_NE(pConfigLoaderFromIniFile, NON_EXISTENT_IMPLEMENTATION);

	// Cleaning
    delete pConfigLoaderFromIniFile;
}

/// <summary>
/// Checks if null is returned when there is not implementation for a given source.
/// </summary>
QTEST_CASE ( CreateConfigLoader_ReturnsNullWhenTheSourceIsNotAvailable_Test )
{
    // Preparation
    const TATConfigLoaderFactory FACTORY_UT = TATConfigLoaderFactory();

    ETATConfigurationSource NON_EXISTENT_SOURCE = ETATConfigurationSource::_NotEnumValue;
    ITATConfigLoader* NON_EXISTENT_IMPLEMENTATION = null_t;

	// Execution
    ITATConfigLoader* pConfigLoaderFromIniFile = FACTORY_UT.CreateConfigLoader(NON_EXISTENT_SOURCE);

    // Verification
    BOOST_CHECK_EQUAL(pConfigLoaderFromIniFile, NON_EXISTENT_IMPLEMENTATION);

	// Cleaning
    delete pConfigLoaderFromIniFile;
}

/// <summary>
/// Checks that a configuration loader implementation is returned.
/// </summary>
QTEST_CASE ( CreateConfigLoaderFromIniFile_AnImplementationIsReturned_Test )
{
    // Preparation
    const TATConfigLoaderFactoryWhiteBox FACTORY_UT = TATConfigLoaderFactoryWhiteBox();
    ITATConfigLoader* NON_EXISTENT_IMPLEMENTATION = null_t;

	// Execution
    ITATConfigLoader* pConfigLoaderFromIniFile = FACTORY_UT.CreateConfigLoaderFromIniFile();

    // Verification
    BOOST_CHECK_NE(pConfigLoaderFromIniFile, NON_EXISTENT_IMPLEMENTATION);

	// Cleaning
    delete pConfigLoaderFromIniFile;
}

/// <summary>
/// Checks that returned configuration loader's properties are intialized as expected.
/// </summary>
QTEST_CASE ( CreateConfigLoaderFromIniFile_ObjectIsInitializedAsExpected_Test )
{
    // Preparation
    const TATConfigLoaderFactoryWhiteBox FACTORY_UT = TATConfigLoaderFactoryWhiteBox();
    const TATRuleNode* null_t_VALUE = null_t;
    const ETATConfigNodeType ROOT_NODE_TYPE = ETATConfigNodeType::E_ROOT;
    const wxString EXPECTED_SOURCE = wxT("");

	// Execution
    ITATConfigLoader* pConfigLoaderFromIniFile = FACTORY_UT.CreateConfigLoaderFromIniFile();
    wxString source = pConfigLoaderFromIniFile->GetSource();
    TATRuleNode* pRuleTree = pConfigLoaderFromIniFile->GetRuleTree();

    // Verification
    BOOST_CHECK_EQUAL(source, EXPECTED_SOURCE);
    BOOST_CHECK_NE(pRuleTree, null_t_VALUE);

    if(pRuleTree)
    {
        BOOST_CHECK_EQUAL(pRuleTree->GetType().ToString(), ROOT_NODE_TYPE.ToString());
    }

	// Cleaning
    delete pConfigLoaderFromIniFile;
}


/// <summary>
/// Compares 2 rule nodes for equality, property by property.
/// </summary>
/// <param name="ruleNodeA">A rule node.</param>
/// <param name="ruleNodeB">A rule node.</param>
/// <returns>
/// True if the nodes are equal, false otherwise.
/// </returns>
bool RuleNodesAreEqual_Utility(const TATRuleNode& ruleNodeA, const TATRuleNode& ruleNodeB)
{
    return ruleNodeA.GetCanBeEmpty() == ruleNodeB.GetCanBeEmpty() &&
           ruleNodeA.GetIsObligatory() == ruleNodeB.GetIsObligatory() &&
           ruleNodeA.GetMaxCount() == ruleNodeB.GetMaxCount() &&
           ruleNodeA.GetName() == ruleNodeB.GetName() &&
           ruleNodeA.GetType() == ruleNodeB.GetType();
}

/// <summary>
/// Checks whether the created tree has changed or keeps the same.
/// </summary>
QTEST_CASE ( CreateRuleTree_HasNotChanged_Test )
{
    // Preparation
    const TATConfigLoaderFactoryWhiteBox FACTORY_UT = TATConfigLoaderFactoryWhiteBox();
    const TATRuleNode ROOT_NODE(wxT("ROOT"), 1, false, true, ETATConfigNodeType::E_ROOT);
    const TATRuleNode COMPILER_SETTINGS_NODE(wxT("C"), 0, false, true, ETATConfigNodeType::E_HEADER);
    const TATRuleNode COMPILER_PATH_NODE(wxT("CompilerPath"), 1, false, true, ETATConfigNodeType::E_VALUE);
    const TATRuleNode COMPILER_CLEAN_COMMAND_NODE(wxT("CompilerCleanCommand"), 1, false, true, ETATConfigNodeType::E_VALUE);
    const TATRuleNode COMPILER_BUILD_COMMAND_NODE(wxT("CompilerBuildCommand"), 1, false, true, ETATConfigNodeType::E_VALUE);
    const TATRuleNode COMPILER_BUILD_PARAMS_NODE(wxT("CompilerBuildParams"), 1, true, true, ETATConfigNodeType::E_VALUE);
    const TATRuleNode PROJECT_SETTINGS_NODE(wxT("P"), 0, false, true, ETATConfigNodeType::E_HEADER);
    const TATRuleNode COMPILATION_INFO_PATH_NODE(wxT("CompilationInfoPath"), 1, false, true, ETATConfigNodeType::E_VALUE);
    const TATRuleNode COMPILER_NODE(wxT("Compiler"), 1, false, true, ETATConfigNodeType::E_VALUE);
    const TATRuleNode FLAG_NODE(wxT("F"), 0, false, false, ETATConfigNodeType::E_HEADER);
    const TATRuleNode OPTION_NODE( wxT("Option"), 0, false, true, ETATConfigNodeType::E_VALUE);
    const TATRuleNode SUT_NODE(wxT("S"), 1, false, true, ETATConfigNodeType::E_HEADER);
    const TATRuleNode CONFIGURATION_FILE_PATH_NODE( wxT("ConfigurationFilePath"), 1, false, true, ETATConfigNodeType::E_VALUE);
    const TATRuleNode COMPILER_CONFIGURATION_NODE(wxT("CompilerConfiguration"), 0, false, true, ETATConfigNodeType::E_VALUE);
    const TATRuleNode TEST_SYSTEM_NODE(wxT("T"), 0, false, true, ETATConfigNodeType::E_HEADER);
    const TATRuleNode TEST_MODULES_PATH_NODE(wxT("TestModulesPath"), 1, false, true, ETATConfigNodeType::E_VALUE);
    const TATRuleNode RESULTS_PATH_NODE(wxT("ResultsPath"), 1, false, true, ETATConfigNodeType::E_VALUE);
    const TATRuleNode COMPILATION_INFO_PATH_NODE2(wxT("CompilationInfoPath"), 1, false, true, ETATConfigNodeType::E_VALUE);
    const TATRuleNode COMPILER_PATH_NODE2(wxT("Compiler"), 1, false, true, ETATConfigNodeType::E_VALUE);

	// Execution
    TATRuleNode* pRuleTreeUT = FACTORY_UT.CreateRuleTree();

    // Verification
    BOOST_CHECK(RuleNodesAreEqual_Utility(*pRuleTreeUT, ROOT_NODE));

    TATRuleNode* pCompilerSettingsNode = dynamic_cast<TATRuleNode*>(pRuleTreeUT->GetChild(COMPILER_SETTINGS_NODE.GetName()).begin()->second);
    BOOST_CHECK(RuleNodesAreEqual_Utility(*pCompilerSettingsNode, COMPILER_SETTINGS_NODE));
    BOOST_CHECK(RuleNodesAreEqual_Utility(*dynamic_cast<TATRuleNode*>(pCompilerSettingsNode->GetChild(COMPILER_PATH_NODE.GetName()).begin()->second), COMPILER_PATH_NODE));
    BOOST_CHECK(RuleNodesAreEqual_Utility(*dynamic_cast<TATRuleNode*>(pCompilerSettingsNode->GetChild(COMPILER_CLEAN_COMMAND_NODE.GetName()).begin()->second), COMPILER_CLEAN_COMMAND_NODE));
    BOOST_CHECK(RuleNodesAreEqual_Utility(*dynamic_cast<TATRuleNode*>(pCompilerSettingsNode->GetChild(COMPILER_BUILD_COMMAND_NODE.GetName()).begin()->second), COMPILER_BUILD_COMMAND_NODE));
    BOOST_CHECK(RuleNodesAreEqual_Utility(*dynamic_cast<TATRuleNode*>(pCompilerSettingsNode->GetChild(COMPILER_BUILD_PARAMS_NODE.GetName()).begin()->second), COMPILER_BUILD_PARAMS_NODE));

    TATRuleNode* pProjectSettingsNode = dynamic_cast<TATRuleNode*>(pRuleTreeUT->GetChild(PROJECT_SETTINGS_NODE.GetName()).begin()->second);
    BOOST_CHECK(RuleNodesAreEqual_Utility(*pProjectSettingsNode, PROJECT_SETTINGS_NODE));
    BOOST_CHECK(RuleNodesAreEqual_Utility(*dynamic_cast<TATRuleNode*>(pProjectSettingsNode->GetChild(COMPILATION_INFO_PATH_NODE.GetName()).begin()->second), COMPILATION_INFO_PATH_NODE));
    BOOST_CHECK(RuleNodesAreEqual_Utility(*dynamic_cast<TATRuleNode*>(pProjectSettingsNode->GetChild(COMPILER_NODE.GetName()).begin()->second), COMPILER_NODE));

    TATRuleNode* pFlagNode = dynamic_cast<TATRuleNode*>(pRuleTreeUT->GetChild(FLAG_NODE.GetName()).begin()->second);
    BOOST_CHECK(RuleNodesAreEqual_Utility(*pFlagNode, FLAG_NODE));
    BOOST_CHECK(RuleNodesAreEqual_Utility(*dynamic_cast<TATRuleNode*>(pFlagNode->GetChild(OPTION_NODE.GetName()).begin()->second), OPTION_NODE));

    TATRuleNode* pSUTNode = dynamic_cast<TATRuleNode*>(pRuleTreeUT->GetChild(SUT_NODE.GetName()).begin()->second);
    BOOST_CHECK(RuleNodesAreEqual_Utility(*pSUTNode, SUT_NODE));
    BOOST_CHECK(RuleNodesAreEqual_Utility(*dynamic_cast<TATRuleNode*>(pSUTNode->GetChild(CONFIGURATION_FILE_PATH_NODE.GetName()).begin()->second), CONFIGURATION_FILE_PATH_NODE));
    BOOST_CHECK(RuleNodesAreEqual_Utility(*dynamic_cast<TATRuleNode*>(pSUTNode->GetChild(COMPILER_CONFIGURATION_NODE.GetName()).begin()->second), COMPILER_CONFIGURATION_NODE));

    TATRuleNode* pTestSystemNode = dynamic_cast<TATRuleNode*>(pRuleTreeUT->GetChild(TEST_SYSTEM_NODE.GetName()).begin()->second);
    BOOST_CHECK(RuleNodesAreEqual_Utility(*pTestSystemNode, TEST_SYSTEM_NODE));
    BOOST_CHECK(RuleNodesAreEqual_Utility(*dynamic_cast<TATRuleNode*>(pTestSystemNode->GetChild(TEST_MODULES_PATH_NODE.GetName()).begin()->second), TEST_MODULES_PATH_NODE));
    BOOST_CHECK(RuleNodesAreEqual_Utility(*dynamic_cast<TATRuleNode*>(pTestSystemNode->GetChild(RESULTS_PATH_NODE.GetName()).begin()->second), RESULTS_PATH_NODE));
    BOOST_CHECK(RuleNodesAreEqual_Utility(*dynamic_cast<TATRuleNode*>(pTestSystemNode->GetChild(COMPILATION_INFO_PATH_NODE2.GetName()).begin()->second), COMPILATION_INFO_PATH_NODE2));
    BOOST_CHECK(RuleNodesAreEqual_Utility(*dynamic_cast<TATRuleNode*>(pTestSystemNode->GetChild(COMPILER_PATH_NODE2.GetName()).begin()->second), COMPILER_PATH_NODE2));

	// Cleaning
    delete pRuleTreeUT;
}


// End - Test Suite: TATConfigLoaderFactory
QTEST_SUITE_END()
