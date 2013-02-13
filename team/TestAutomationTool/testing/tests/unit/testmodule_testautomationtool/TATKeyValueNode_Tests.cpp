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

#include "TestConfiguration/TATKeyValueNode.h"
#include "TestConfiguration/ETATConfigNodeType.h"

using Kinesis::TestAutomationTool::Backend::TATKeyValueNode;
using Kinesis::TestAutomationTool::Backend::ETATConfigNodeType;

QTEST_SUITE_BEGIN( TATKeyValueNode_TestSuite )

/// <summary>
/// Checks that default values has not changed.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHasNotChanged_Test )
{
    // Preparation
    const wxString EXPECTED_VALUE_VALUE = wxT("");
    const wxString EXPECTED_NAME_VALUE = wxT("");
    const ETATConfigNodeType EXPECTED_TYPE_VALUE = ETATConfigNodeType::E_ROOT;

	// Execution
    TATKeyValueNode nodeUT;
    wxString strDefaultValue = nodeUT.GetValue();
    wxString strDefaultName = nodeUT.GetName();
    ETATConfigNodeType eDefaultType = nodeUT.GetType();
    
    // Verification
    BOOST_CHECK_EQUAL(strDefaultValue, EXPECTED_VALUE_VALUE);
    BOOST_CHECK_EQUAL(strDefaultName, EXPECTED_NAME_VALUE);
    BOOST_CHECK(eDefaultType.ToString() == EXPECTED_TYPE_VALUE.ToString());
}

/// <summary>
/// Checks that every parameter of is correctly stored.
/// </summary>
QTEST_CASE ( Constructor2_AllValuesAreCorrectlySet_Test )
{
    // Preparation
    const wxString EXPECTED_VALUE_VALUE = wxT("VALUE");
    const wxString EXPECTED_NAME_VALUE = wxT("NAME");
    const ETATConfigNodeType EXPECTED_TYPE_VALUE = ETATConfigNodeType::E_VALUE;

	// Execution
    TATKeyValueNode nodeUT(EXPECTED_NAME_VALUE, EXPECTED_TYPE_VALUE, EXPECTED_VALUE_VALUE);
    wxString strValue = nodeUT.GetValue();
    wxString strName = nodeUT.GetName();
    ETATConfigNodeType eType = nodeUT.GetType();
    
    // Verification
    BOOST_CHECK_EQUAL(strValue, EXPECTED_VALUE_VALUE);
    BOOST_CHECK_EQUAL(strName, EXPECTED_NAME_VALUE);
    BOOST_CHECK(eType.ToString() == EXPECTED_TYPE_VALUE.ToString());
}

/// <summary>
/// Checks that the value is correctly retrieved.
/// </summary>
QTEST_CASE ( GetValue_ValueIsCorrectlyRetrieved_Test )
{
    // Preparation
    const wxString EXPECTED_VALUE_VALUE = wxT("VALUE");
    TATKeyValueNode NODE;
    NODE.SetValue(EXPECTED_VALUE_VALUE);

	// Execution
    wxString strValueUT = NODE.GetValue();
    
    // Verification
    BOOST_CHECK_EQUAL(strValueUT, EXPECTED_VALUE_VALUE);
}

/// <summary>
/// Checks that the value is correctly stored.
/// </summary>
QTEST_CASE ( SetValue_ValueIsCorrectlyStored_Test )
{
    // Preparation
    const wxString EXPECTED_VALUE_VALUE = wxT("VALUE");

	// Execution
    TATKeyValueNode nodeUT;
    nodeUT.SetValue(EXPECTED_VALUE_VALUE);

    // Verification
    BOOST_CHECK_EQUAL(nodeUT.GetValue(), EXPECTED_VALUE_VALUE);
}


// End - Test Suite: TATKeyValueNode
QTEST_SUITE_END()
