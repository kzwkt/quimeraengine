// [TERMS&CONDITIONS]

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../../testsystem/TestingExternalDefinitions.h"

#include "TestConfiguration/STATAppSettings.h"

using Kinesis::TestAutomationTool::Backend::STATAppSettings;

QTEST_SUITE_BEGIN( STATAppSettings_TestSuite )

/// <summary>
/// Checks whether the returned value has changed. This tests prevents from unintended changes.
/// </summary>
QTEST_CASE ( GetConfigurationFilePath_ReturnValueHasNotChanged_Test )
{
    // Preparation
    const wxString EXPECTED_VALUE = "config.ini";

	// Execution
    wxString strReturnedValueUT = STATAppSettings::GetConfigurationFilePath();
    
    // Verification
    BOOST_CHECK_EQUAL(strReturnedValueUT, EXPECTED_VALUE);
}

// End - Test Suite: STATAppSettings
QTEST_SUITE_END()
