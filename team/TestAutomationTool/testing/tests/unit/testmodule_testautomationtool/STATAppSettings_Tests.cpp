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
