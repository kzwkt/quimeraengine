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

#include <wx/filefn.h>

#include "TestConfiguration/TATTestAutomationToolConfiguration.h"
#include "TestConfiguration/ITATConfigLoader.h"
#include "TATTestAutomationToolConfigurationWhiteBox.h"
#include "TestConfiguration/TATKeyValueNode.h"
#include "TestConfiguration/ETATConfigNodeType.h"

using Kinesis::TestAutomationTool::Backend::TATTestAutomationToolConfiguration;
using Kinesis::TestAutomationTool::Backend::Test::TATTestAutomationToolConfigurationWhiteBox;
using Kinesis::TestAutomationTool::Backend::ITATConfigLoader;

QTEST_SUITE_BEGIN( TATTestAutomationToolConfiguration_TestSuite )

/// <summary>
/// Checks if the values set in the default constructor have changed.
/// </summary>
QTEST_CASE ( Constructor_DefaultValuesHaveNotChanged_Test )
{
    // Preparation
    ITATConfigLoader* CONFIGURATION_LOADER_NULL = null_t;
    const wxString CONFIGURATION_LOADER_SOURCE = wxT("config.ini");
    std::list<wxString> EXPECTED_COMPILER_CONFIGURATIONS;
    std::list<wxString> EXPECTED_COMPILER_CONFIGURATION_SELECTION;
    TATTestAutomationToolConfiguration::TFlagCombinationCollection EXPECTED_FLAG_COMBINATIONS;
    std::list<wxString> EXPECTED_FLAG_COMBINATION_SELECTION;

	// Execution
    TATTestAutomationToolConfiguration testAutomationToolConfigurationUT;

    // Verification
    BOOST_CHECK_NE(testAutomationToolConfigurationUT.GetConfigLoader(), CONFIGURATION_LOADER_NULL);
    BOOST_CHECK_EQUAL(testAutomationToolConfigurationUT.GetConfigLoader()->GetSource(), CONFIGURATION_LOADER_SOURCE);
    BOOST_CHECK(testAutomationToolConfigurationUT.GetCompilerConfigurations() == EXPECTED_COMPILER_CONFIGURATIONS);
    BOOST_CHECK(testAutomationToolConfigurationUT.GetCompilerConfigurationSelection() == EXPECTED_COMPILER_CONFIGURATION_SELECTION);
    BOOST_CHECK(testAutomationToolConfigurationUT.GetFlagCombinations() == EXPECTED_FLAG_COMBINATIONS);
    BOOST_CHECK(testAutomationToolConfigurationUT.GetFlagCombinationSelection() == EXPECTED_FLAG_COMBINATION_SELECTION);
}

/// <summary>
/// Checks that no exceptions are thrown when the configuration source exists and is completely valid.
/// </summary>
QTEST_CASE ( LoadConfiguration_NoExceptionIsThrownWhenUsingExistingAndValidSource_Test )
{
    // Preparation
    TATTestAutomationToolConfiguration TESTAUTOMATIONTOOL_CONFIGURATION;
    const wxString EXISTING_VALID_SOURCE = wxString(TAT_ARTIFACTS_DIRECTORY) + wxT("/ConfigFileMock.ini");
    const bool NO_EXCEPTIONS_THROWN_VALUE = false;

	// Execution
    bool bExceptionThrown = false;

    try
    {
        TESTAUTOMATIONTOOL_CONFIGURATION.LoadConfiguration(EXISTING_VALID_SOURCE);
    }
    catch(...)
    {
        bExceptionThrown = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bExceptionThrown, NO_EXCEPTIONS_THROWN_VALUE);
}

/// <summary>
/// Checks if all the selected compiler configuration names are returned, and only them.
/// </summary>
QTEST_CASE ( SelectCompilerConfiguration_OnlySelectedCompilerCondigurationAreReturned_Test )
{
    // Preparation
    const wxString EXPECTED_CONFIGURATION_NAME2 = wxT("CompilerConfigurationValue2");
    const int EXPECTED_NUMBER_OF_COMPILER_CONFIGS = 1;

    TATTestAutomationToolConfiguration TESTAUTOMATIONTOOL_CONFIGURATION;
    const wxString SOURCE = wxGetCwd() + wxT("/") + TAT_ARTIFACTS_DIRECTORY + wxT("/ConfigFileMock.ini");
    TESTAUTOMATIONTOOL_CONFIGURATION.LoadConfiguration(SOURCE);

	// Execution
    TESTAUTOMATIONTOOL_CONFIGURATION.SelectCompilerConfiguration(EXPECTED_CONFIGURATION_NAME2, true);

    // Verification
    std::list<wxString> compilerConfigurationNames = TESTAUTOMATIONTOOL_CONFIGURATION.GetCompilerConfigurationSelection();
    BOOST_CHECK_EQUAL(compilerConfigurationNames.size(), EXPECTED_NUMBER_OF_COMPILER_CONFIGS);
    BOOST_CHECK_EQUAL(*compilerConfigurationNames.begin(), EXPECTED_CONFIGURATION_NAME2);
}

/// <summary>
/// Checks if all the selected flag combination names are returned, and only them.
/// </summary>
QTEST_CASE ( SelectFlagCombination_OnlySelectedFlagCombinationsAreReturned_Test )
{
    // Preparation
    const wxString EXPECTED_COMBINATION_NAME2 = wxT("FlagCombination2");
    const int EXPECTED_NUMBER_OF_FLAG_COMBINATIONS = 1;

    TATTestAutomationToolConfiguration testAutomationToolConfigUT;
    const wxString SOURCE = wxGetCwd() + wxT("/") + TAT_ARTIFACTS_DIRECTORY + wxT("/ConfigFileMock.ini");
    testAutomationToolConfigUT.LoadConfiguration(SOURCE);

	// Execution
    testAutomationToolConfigUT.SelectFlagCombination(EXPECTED_COMBINATION_NAME2, true);

    // Verification
    std::list<wxString> flagCombinationNames = testAutomationToolConfigUT.GetFlagCombinationSelection();
    BOOST_CHECK_EQUAL(flagCombinationNames.size(), EXPECTED_NUMBER_OF_FLAG_COMBINATIONS);
    BOOST_CHECK_EQUAL(*flagCombinationNames.begin(), EXPECTED_COMBINATION_NAME2);
}

/// <summary>
/// Checks if the generated combinations are what expected when there are more than one flag.
/// </summary>
QTEST_CASE ( CombineFlags_FlasgAreCombinedAsExpectedWhenThereAreMoreThanOne_Test )
{
    using Kinesis::TestAutomationTool::Backend::Test::TATTestAutomationToolConfigurationWhiteBox;
    using Kinesis::TestAutomationTool::Backend::TATKeyValueNode;
    using Kinesis::TestAutomationTool::Backend::ETATConfigNodeType;

    // Preparation
    const int EXPECTED_NUMBER_OF_COMBINATIONS = 4;
    TATTestAutomationToolConfiguration::TFlagCombinationCollection EXPECTED_FLAG_COMBINATIONS;

    std::map<wxString, wxString> COMBINATION1;
    COMBINATION1.insert(std::pair<wxString, wxString>(wxT("Flag1"), wxT("Value1_1")));
    COMBINATION1.insert(std::pair<wxString, wxString>(wxT("Flag2"), wxT("Value2_1")));
    EXPECTED_FLAG_COMBINATIONS.insert(std::pair<wxString, std::map<wxString, wxString> >(wxT("C0"), COMBINATION1));

    std::map<wxString, wxString> COMBINATION2;
    COMBINATION2.insert(std::pair<wxString, wxString>(wxT("Flag1"), wxT("Value1_1")));
    COMBINATION2.insert(std::pair<wxString, wxString>(wxT("Flag2"), wxT("Value2_2")));
    EXPECTED_FLAG_COMBINATIONS.insert(std::pair<wxString, std::map<wxString, wxString> >(wxT("C1"), COMBINATION2));

    std::map<wxString, wxString> COMBINATION3;
    COMBINATION3.insert(std::pair<wxString, wxString>(wxT("Flag1"), wxT("Value1_2")));
    COMBINATION3.insert(std::pair<wxString, wxString>(wxT("Flag2"), wxT("Value2_1")));
    EXPECTED_FLAG_COMBINATIONS.insert(std::pair<wxString, std::map<wxString, wxString> >(wxT("C2"), COMBINATION3));

    std::map<wxString, wxString> COMBINATION4;
    COMBINATION4.insert(std::pair<wxString, wxString>(wxT("Flag1"), wxT("Value1_2")));
    COMBINATION4.insert(std::pair<wxString, wxString>(wxT("Flag2"), wxT("Value2_2")));
    EXPECTED_FLAG_COMBINATIONS.insert(std::pair<wxString, std::map<wxString, wxString> >(wxT("C3"), COMBINATION4));

    std::list<TATKeyValueNode*> INPUT_FLAGS;

    TATKeyValueNode* pFlag1 = new TATKeyValueNode(wxT("F"), ETATConfigNodeType::E_HEADER, wxT("Flag1"));
    pFlag1->AddChild(new TATKeyValueNode(wxT("Option1"), ETATConfigNodeType::E_VALUE, wxT("Value1_1")));
    pFlag1->AddChild(new TATKeyValueNode(wxT("Option2"), ETATConfigNodeType::E_VALUE, wxT("Value1_2")));
    INPUT_FLAGS.push_back(pFlag1);

    TATKeyValueNode* pFlag2 = new TATKeyValueNode(wxT("F"), ETATConfigNodeType::E_HEADER, wxT("Flag2"));
    pFlag2->AddChild(new TATKeyValueNode(wxT("Option1"), ETATConfigNodeType::E_VALUE, wxT("Value2_1")));
    pFlag2->AddChild(new TATKeyValueNode(wxT("Option2"), ETATConfigNodeType::E_VALUE, wxT("Value2_2")));
    INPUT_FLAGS.push_back(pFlag2);

    TATTestAutomationToolConfigurationWhiteBox TESTAUTOMATIONTOOL_CONFIGURATION;

	// Execution
    TESTAUTOMATIONTOOL_CONFIGURATION.CombineFlags(INPUT_FLAGS);

    // Verification
    TATTestAutomationToolConfiguration::TFlagCombinationCollection flagCombinationsGenerated = TESTAUTOMATIONTOOL_CONFIGURATION.GetExpectedFlagCombinations();
    BOOST_CHECK_EQUAL(flagCombinationsGenerated.size(), EXPECTED_NUMBER_OF_COMBINATIONS);

    TATTestAutomationToolConfiguration::TFlagCombinationCollection::iterator iCombination = flagCombinationsGenerated.begin();
    TATTestAutomationToolConfiguration::TFlagCombinationCollection::iterator iExpected = EXPECTED_FLAG_COMBINATIONS.begin();

    for(; iCombination != flagCombinationsGenerated.end(); ++iCombination, ++iExpected)
    {
        BOOST_CHECK_EQUAL(iCombination->first, iExpected->first);

        std::map<wxString, wxString>::iterator iFlagValue = iCombination->second.begin();
        std::map<wxString, wxString>::iterator iExpectedFlagValue = iExpected->second.begin();

        for(; iFlagValue != iCombination->second.end(); ++iFlagValue, ++iExpectedFlagValue)
        {
            BOOST_CHECK_EQUAL(iFlagValue->first, iExpectedFlagValue->first);
            BOOST_CHECK_EQUAL(iFlagValue->second, iExpectedFlagValue->second);
        }
    }

    // Cleaning
    delete pFlag1;
    delete pFlag2;
}

/// <summary>
/// Checks that when there is only one flag, one combination is generated per flag value.
/// </summary>
QTEST_CASE ( CombineFlags_WhenThereIsOnlyOneFlagThereIsOneCombinationPerValue_Test )
{
    using Kinesis::TestAutomationTool::Backend::Test::TATTestAutomationToolConfigurationWhiteBox;
    using Kinesis::TestAutomationTool::Backend::TATKeyValueNode;
    using Kinesis::TestAutomationTool::Backend::ETATConfigNodeType;

    // Preparation
    const int EXPECTED_NUMBER_OF_COMBINATIONS = 2;
    TATTestAutomationToolConfiguration::TFlagCombinationCollection EXPECTED_FLAG_COMBINATIONS;

    std::map<wxString, wxString> COMBINATION1 = std::map<wxString, wxString>();
    COMBINATION1.insert(std::pair<wxString, wxString>(wxT("Flag1"), wxT("Value1_1")));
    EXPECTED_FLAG_COMBINATIONS.insert(std::pair<wxString, std::map<wxString, wxString> >(wxT("C0"), COMBINATION1));

    std::map<wxString, wxString> COMBINATION2 = std::map<wxString, wxString>();
    COMBINATION2.insert(std::pair<wxString, wxString>(wxT("Flag1"), wxT("Value1_2")));
    EXPECTED_FLAG_COMBINATIONS.insert(std::pair<wxString, std::map<wxString, wxString> >(wxT("C1"), COMBINATION2));

    std::list<TATKeyValueNode*> INPUT_FLAGS;

    TATKeyValueNode* pFlag1 = new TATKeyValueNode(wxT("F"), ETATConfigNodeType::E_HEADER, wxT("Flag1"));
    pFlag1->AddChild(new TATKeyValueNode(wxT("Option1"), ETATConfigNodeType::E_VALUE, wxT("Value1_1")));
    pFlag1->AddChild(new TATKeyValueNode(wxT("Option2"), ETATConfigNodeType::E_VALUE, wxT("Value1_2")));
    INPUT_FLAGS.push_back(pFlag1);

    TATTestAutomationToolConfigurationWhiteBox TESTAUTOMATIONTOOL_CONFIGURATION;

	// Execution
    TESTAUTOMATIONTOOL_CONFIGURATION.CombineFlags(INPUT_FLAGS);

    // Verification
    TATTestAutomationToolConfiguration::TFlagCombinationCollection flagCombinationsGenerated = TESTAUTOMATIONTOOL_CONFIGURATION.GetExpectedFlagCombinations();
    BOOST_CHECK_EQUAL(flagCombinationsGenerated.size(), EXPECTED_NUMBER_OF_COMBINATIONS);

    TATTestAutomationToolConfiguration::TFlagCombinationCollection::iterator iCombination = flagCombinationsGenerated.begin();
    TATTestAutomationToolConfiguration::TFlagCombinationCollection::iterator iExpected = EXPECTED_FLAG_COMBINATIONS.begin();

    for(; iCombination != flagCombinationsGenerated.end(); ++iCombination, ++iExpected)
    {
        BOOST_CHECK_EQUAL(iCombination->first, iExpected->first);

        std::map<wxString, wxString>::iterator iFlagValue = iCombination->second.begin();
        std::map<wxString, wxString>::iterator iExpectedFlagValue = iExpected->second.begin();

        for(; iFlagValue != iCombination->second.end(); ++iFlagValue, ++iExpectedFlagValue)
        {
            BOOST_CHECK_EQUAL(iFlagValue->first, iExpectedFlagValue->first);
            BOOST_CHECK_EQUAL(iFlagValue->second, iExpectedFlagValue->second);
        }
    }

    // Cleaning
    delete pFlag1;
}

/// <summary>
/// Checks if any error occurs during destruction.
/// </summary>
QTEST_CASE ( Destroy_NoErrorOccurred_Test )
{
    // Preparation
    const bool NO_ERROR_OCURRED = true;

    TATTestAutomationToolConfigurationWhiteBox* TESTAUTOMATIONTOOL_CONFIGURATION = new TATTestAutomationToolConfigurationWhiteBox();

	// Execution
    bool bNoErrorOcurred = true;

    try
    {
        delete TESTAUTOMATIONTOOL_CONFIGURATION;
    }
    catch(...) // TODO [Thund]: A concrete exception type should be caught
    {
        bNoErrorOcurred = false;
    }

    // Verification
    BOOST_CHECK_EQUAL(bNoErrorOcurred, NO_ERROR_OCURRED);
}

/// <summary>
/// Checks if all the resources have been released. It's not a deep check but a "check for null" or "check for empty" test.
/// </summary>
QTEST_CASE ( Destroy_AllResourcesAreReleased_Test )
{
    // Preparation
    ITATConfigLoader* CONFIGURATION_LOADER_null_t = null_t;
    TATTestAutomationToolConfigurationWhiteBox TESTAUTOMATIONTOOL_CONFIGURATION;

	// Execution
    TESTAUTOMATIONTOOL_CONFIGURATION.Destroy();

    // Verification
    BOOST_CHECK_EQUAL(TESTAUTOMATIONTOOL_CONFIGURATION.GetConfigLoader(), CONFIGURATION_LOADER_null_t);
}

/// <summary>
/// Checks if the generated combinations are what expected.
/// </summary>
QTEST_CASE ( CombineFlagValue_FlasgAreCombinedAsExpected_Test )
{
    using Kinesis::TestAutomationTool::Backend::Test::TATTestAutomationToolConfigurationWhiteBox;
    using Kinesis::TestAutomationTool::Backend::TATKeyValueNode;
    using Kinesis::TestAutomationTool::Backend::ETATConfigNodeType;

    // Preparation
    const int EXPECTED_NUMBER_OF_COMBINATIONS = 4;
    std::list< std::map<wxString, wxString> > EXPECTED_FLAG_COMBINATIONS;

    std::map<wxString, wxString> COMBINATION1 = std::map<wxString, wxString>();
    COMBINATION1.insert(std::pair<wxString, wxString>(wxT("Flag1"), wxT("Value1_1")));
    COMBINATION1.insert(std::pair<wxString, wxString>(wxT("Flag2"), wxT("Value2_1")));
    EXPECTED_FLAG_COMBINATIONS.push_back(COMBINATION1);

    std::map<wxString, wxString> COMBINATION2 = std::map<wxString, wxString>();
    COMBINATION2.insert(std::pair<wxString, wxString>(wxT("Flag1"), wxT("Value1_1")));
    COMBINATION2.insert(std::pair<wxString, wxString>(wxT("Flag2"), wxT("Value2_2")));
    EXPECTED_FLAG_COMBINATIONS.push_back(COMBINATION2);

    std::map<wxString, wxString> COMBINATION3 = std::map<wxString, wxString>();
    COMBINATION3.insert(std::pair<wxString, wxString>(wxT("Flag1"), wxT("Value1_2")));
    COMBINATION3.insert(std::pair<wxString, wxString>(wxT("Flag2"), wxT("Value2_1")));
    EXPECTED_FLAG_COMBINATIONS.push_back(COMBINATION3);

    std::map<wxString, wxString> COMBINATION4 = std::map<wxString, wxString>();
    COMBINATION4.insert(std::pair<wxString, wxString>(wxT("Flag1"), wxT("Value1_2")));
    COMBINATION4.insert(std::pair<wxString, wxString>(wxT("Flag2"), wxT("Value2_2")));
    EXPECTED_FLAG_COMBINATIONS.push_back(COMBINATION4);

    std::list<TATKeyValueNode*> INPUT_FLAGS;

    TATKeyValueNode* pFlag1 = new TATKeyValueNode(wxT("F"), ETATConfigNodeType::E_HEADER, wxT("Flag1"));
    pFlag1->AddChild(new TATKeyValueNode(wxT("Option1"), ETATConfigNodeType::E_VALUE, wxT("Value1_1")));
    pFlag1->AddChild(new TATKeyValueNode(wxT("Option2"), ETATConfigNodeType::E_VALUE, wxT("Value1_2")));
    INPUT_FLAGS.push_back(pFlag1);

    TATKeyValueNode* pFlag2 = new TATKeyValueNode(wxT("F"), ETATConfigNodeType::E_HEADER, wxT("Flag2"));
    pFlag2->AddChild(new TATKeyValueNode(wxT("Option1"), ETATConfigNodeType::E_VALUE, wxT("Value2_1")));
    pFlag2->AddChild(new TATKeyValueNode(wxT("Option2"), ETATConfigNodeType::E_VALUE, wxT("Value2_2")));
    INPUT_FLAGS.push_back(pFlag2);

    TATTestAutomationToolConfigurationWhiteBox testAutomationToolConfigurationUT;

	// Execution
    std::map<wxString, wxString> flagCombination;
    std::list< std::map<wxString, wxString> > flagCombinations;
    testAutomationToolConfigurationUT.CombineFlagValue(INPUT_FLAGS.begin(), INPUT_FLAGS.end(), flagCombination, flagCombinations);

    // Verification
    BOOST_CHECK_EQUAL(flagCombinations.size(), EXPECTED_NUMBER_OF_COMBINATIONS);

    std::list< std::map<wxString, wxString> >::iterator iCombination = flagCombinations.begin();
    std::list< std::map<wxString, wxString> >::iterator iExpected = EXPECTED_FLAG_COMBINATIONS.begin();

    for(; iCombination != flagCombinations.end(); ++iCombination, ++iExpected)
    {
        std::map<wxString, wxString>::iterator iFlagValue = iCombination->begin();
        std::map<wxString, wxString>::iterator iExpectedFlagValue = iExpected->begin();

        for(; iFlagValue != iCombination->end(); ++iFlagValue, ++iExpectedFlagValue)
        {
            BOOST_CHECK_EQUAL(iFlagValue->first, iExpectedFlagValue->first);
            BOOST_CHECK_EQUAL(iFlagValue->second, iExpectedFlagValue->second);
        }
    }

    // Cleaning
    delete pFlag1;
    delete pFlag2;
}

/// <summary>
/// Checks if all the expected compiler configuration names are returned.
/// </summary>
QTEST_CASE ( GetCompilerConfigurations_RetrievedCompilerConfigurationNamesAreWhatExpected_Test )
{
    // Preparation
    const wxString EXPECTED_CONFIGURATION_NAME1 = wxT("CompilerConfigurationValue");
    const wxString EXPECTED_CONFIGURATION_NAME2 = wxT("CompilerConfigurationValue2");

    TATTestAutomationToolConfiguration TESTAUTOMATIONTOOL_CONFIGURATION;
    const wxString SOURCE = wxGetCwd() + wxT("/") + TAT_ARTIFACTS_DIRECTORY + wxT("/ConfigFileMock.ini");
    TESTAUTOMATIONTOOL_CONFIGURATION.LoadConfiguration(SOURCE);

	// Execution
    std::list<wxString> compilerConfigurationNames = TESTAUTOMATIONTOOL_CONFIGURATION.GetCompilerConfigurations();

    // Verification
    BOOST_CHECK_EQUAL(*compilerConfigurationNames.begin(), EXPECTED_CONFIGURATION_NAME1);
    BOOST_CHECK_EQUAL(*compilerConfigurationNames.rbegin(), EXPECTED_CONFIGURATION_NAME2);
}

/// <summary>
/// Checks if the property returns what's expected.
/// </summary>
QTEST_CASE ( GetConfigLoader_ExpectedValueIsReturned_Test )
{
    // Preparation
    const TATTestAutomationToolConfigurationWhiteBox TESTAUTOMATIONTOOL_CONFIGURATION;
    ITATConfigLoader* EXPECTED_CONFIGLOADER = TESTAUTOMATIONTOOL_CONFIGURATION.GetExpectedConfigLoader();

	// Execution
    ITATConfigLoader* pReturnedValue = TESTAUTOMATIONTOOL_CONFIGURATION.GetConfigLoader();

    // Verification
    BOOST_CHECK_EQUAL(pReturnedValue, EXPECTED_CONFIGLOADER);
}

/// <summary>
/// Checks if all the selected compiler configuration names are returned, and only them.
/// </summary>
QTEST_CASE ( GetCompilerConfigurationSelection_OnlySelectedCompilerCondigurationAreReturned_Test )
{
    // Preparation
    const wxString EXPECTED_CONFIGURATION_NAME2 = wxT("CompilerConfigurationValue2");
    const int EXPECTED_NUMBER_OF_COMPILER_CONFIGS = 1;

    TATTestAutomationToolConfiguration TESTAUTOMATIONTOOL_CONFIGURATION;
    const wxString SOURCE = wxGetCwd() + wxT("/") + TAT_ARTIFACTS_DIRECTORY + wxT("/ConfigFileMock.ini");
    TESTAUTOMATIONTOOL_CONFIGURATION.LoadConfiguration(SOURCE);
    TESTAUTOMATIONTOOL_CONFIGURATION.SelectCompilerConfiguration(wxT("CompilerConfigurationValue2"), true);

	// Execution
    std::list<wxString> compilerConfigurationNames = TESTAUTOMATIONTOOL_CONFIGURATION.GetCompilerConfigurationSelection();

    // Verification
    BOOST_CHECK_EQUAL(compilerConfigurationNames.size(), EXPECTED_NUMBER_OF_COMPILER_CONFIGS);
    BOOST_CHECK_EQUAL(*compilerConfigurationNames.begin(), EXPECTED_CONFIGURATION_NAME2);
}

/// <summary>
/// Checks if all the expected flag combination names are returned.
/// </summary>
QTEST_CASE ( GetFlagCombinations_RetrievedFlagCombinationNamesAreWhatExpected_Test )
{
    using Kinesis::TestAutomationTool::Backend::Test::TATTestAutomationToolConfigurationWhiteBox;
    using Kinesis::TestAutomationTool::Backend::TATKeyValueNode;
    using Kinesis::TestAutomationTool::Backend::ETATConfigNodeType;

    // Preparation
    const int EXPECTED_NUMBER_OF_COMBINATIONS = 2;
    TATTestAutomationToolConfiguration::TFlagCombinationCollection EXPECTED_FLAG_COMBINATIONS;

    std::map<wxString, wxString> COMBINATION1 = std::map<wxString, wxString>();
    COMBINATION1.insert(std::pair<wxString, wxString>(wxT("Flag1"), wxT("Value1_1")));
    EXPECTED_FLAG_COMBINATIONS.insert(std::pair<wxString, std::map<wxString, wxString> >(wxT("C0"), COMBINATION1));

    std::map<wxString, wxString> COMBINATION2 = std::map<wxString, wxString>();
    COMBINATION2.insert(std::pair<wxString, wxString>(wxT("Flag1"), wxT("Value1_2")));
    EXPECTED_FLAG_COMBINATIONS.insert(std::pair<wxString, std::map<wxString, wxString> >(wxT("C1"), COMBINATION2));

    TATTestAutomationToolConfigurationWhiteBox testAutomationToolConfigUT;
    testAutomationToolConfigUT.SetExpectedFlagCombinations(EXPECTED_FLAG_COMBINATIONS);

	// Execution
    TATTestAutomationToolConfiguration::TFlagCombinationCollection flagCombinations = testAutomationToolConfigUT.GetFlagCombinations();

    // Verification
    BOOST_CHECK_EQUAL(flagCombinations.size(), EXPECTED_NUMBER_OF_COMBINATIONS);

    TATTestAutomationToolConfiguration::TFlagCombinationCollection::iterator iCombination = flagCombinations.begin();
    TATTestAutomationToolConfiguration::TFlagCombinationCollection::iterator iExpected = EXPECTED_FLAG_COMBINATIONS.begin();

    for(; iCombination != flagCombinations.end(); ++iCombination, ++iExpected)
    {
        BOOST_CHECK_EQUAL(iCombination->first, iExpected->first);

        std::map<wxString, wxString>::iterator iFlagValue = iCombination->second.begin();
        std::map<wxString, wxString>::iterator iExpectedFlagValue = iExpected->second.begin();

        for(; iFlagValue != iCombination->second.end(); ++iFlagValue, ++iExpectedFlagValue)
        {
            BOOST_CHECK_EQUAL(iFlagValue->first, iExpectedFlagValue->first);
            BOOST_CHECK_EQUAL(iFlagValue->second, iExpectedFlagValue->second);
        }
    }
}

// End - Test Suite: TATTestAutomationToolConfiguration
QTEST_SUITE_END()
