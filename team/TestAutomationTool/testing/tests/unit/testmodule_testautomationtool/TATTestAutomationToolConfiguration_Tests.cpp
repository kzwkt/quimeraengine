// [TERMS&CONDITIONS]

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../../testsystem/TestingExternalDefinitions.h"

#include "TestConfiguration/TATTestAutomationToolConfiguration.h"
#include "TestConfiguration/ITATConfigLoader.h"
#include "TATTestAutomationToolConfigurationWhiteBox.h"

using Kinesis::TestAutomationTool::Backend::TATTestAutomationToolConfiguration;
using Kinesis::TestAutomationTool::Backend::Test::TATTestAutomationToolConfigurationWhiteBox;
using Kinesis::TestAutomationTool::Backend::ITATConfigLoader;

QTEST_SUITE_BEGIN( TATTestAutomationToolConfiguration_TestSuite )

/// <summary>
/// Checks if the values set in the default constructor have changed.
/// </summary>
QTEST_CASE ( Constructor_DefaultValuesHaveNotChanged_Test )
{
    // TODO [Thund]: This test has to be completed when more properties are initialized in future tasks.

    // Preparation
    ITATConfigLoader* CONFIGURATION_LOADER_NULL = NULL;
    const wxString CONFIGURATION_LOADER_SOURCE = wxT("config.ini");
    
	// Execution
    TATTestAutomationToolConfiguration testAutomationToolConfigurationUT;
    
    // Verification
    BOOST_CHECK_NE(testAutomationToolConfigurationUT.GetConfigLoader(), CONFIGURATION_LOADER_NULL);
    BOOST_CHECK_EQUAL(testAutomationToolConfigurationUT.GetConfigLoader()->GetSource(), CONFIGURATION_LOADER_SOURCE);
}

/// <summary>
/// Checks that no exceptions are thrown when the configuration source exists and is completely valid.
/// </summary>
QTEST_CASE ( LoadConfiguration_NoExceptionIsThrownWhenUsingExistingAndValidSource_Test )
{
    // Preparation
    TATTestAutomationToolConfiguration TESTAUTOMATIONTOOL_CONFIGURATION;
    const wxString EXISTING_VALID_SOURCE = wxT("ConfigFileMock.ini");
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
    const wxString SOURCE = wxT("ConfigFileMock.ini");
    TESTAUTOMATIONTOOL_CONFIGURATION.LoadConfiguration(SOURCE);

	// Execution
    TESTAUTOMATIONTOOL_CONFIGURATION.SelectCompilerConfiguration(wxT("CompilerConfigurationValue2"), true);

    // Verification
    std::list<wxString> compilerConfigurationNames = TESTAUTOMATIONTOOL_CONFIGURATION.GetCompilerConfigurationSelection();
    BOOST_CHECK_EQUAL(compilerConfigurationNames.size(), EXPECTED_NUMBER_OF_COMPILER_CONFIGS);
    BOOST_CHECK_EQUAL(*compilerConfigurationNames.begin(), EXPECTED_CONFIGURATION_NAME2);
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
    ITATConfigLoader* CONFIGURATION_LOADER_NULL = NULL;
    TATTestAutomationToolConfigurationWhiteBox TESTAUTOMATIONTOOL_CONFIGURATION;

	// Execution
    TESTAUTOMATIONTOOL_CONFIGURATION.Destroy();

    // Verification
    BOOST_CHECK_EQUAL(TESTAUTOMATIONTOOL_CONFIGURATION.GetConfigLoader(), CONFIGURATION_LOADER_NULL);
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
    const wxString SOURCE = wxT("ConfigFileMock.ini");
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
    const wxString SOURCE = wxT("ConfigFileMock.ini");
    TESTAUTOMATIONTOOL_CONFIGURATION.LoadConfiguration(SOURCE);
    TESTAUTOMATIONTOOL_CONFIGURATION.SelectCompilerConfiguration(wxT("CompilerConfigurationValue2"), true);

	// Execution
    std::list<wxString> compilerConfigurationNames = TESTAUTOMATIONTOOL_CONFIGURATION.GetCompilerConfigurationSelection();

    // Verification
    BOOST_CHECK_EQUAL(compilerConfigurationNames.size(), EXPECTED_NUMBER_OF_COMPILER_CONFIGS);
    BOOST_CHECK_EQUAL(*compilerConfigurationNames.begin(), EXPECTED_CONFIGURATION_NAME2);
}

// End - Test Suite: TATTestAutomationToolConfiguration
QTEST_SUITE_END()
