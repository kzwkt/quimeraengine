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

#include "TestConfiguration/TATRuleNode.h"

using Kinesis::TestAutomationTool::Backend::TATRuleNode;
using Kinesis::TestAutomationTool::Backend::ETATConfigNodeType;

QTEST_SUITE_BEGIN( TATRuleNode_TestSuite )

/// <summary>
/// Checks that default values have not changed.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // Preparation
    const int EXPECTED_MAXCOUNT_VALUE = 0;
    const bool EXPECTED_ISOBLIGATORY_VALUE = false;
    const bool EXPECTED_CANBEEMPTY_VALUE = false;
    const wxString EXPECTED_NAME_VALUE = wxT("");
    const ETATConfigNodeType EXPECTED_TYPE_VALUE = ETATConfigNodeType::E_ROOT;

	// Execution
    TATRuleNode nodeUT;
    int nDefaultMaxCount = nodeUT.GetMaxCount();
    bool bDefaultIsObligatory = nodeUT.GetIsObligatory();
    bool bDefaultCanBeEmpty = nodeUT.GetCanBeEmpty();
    wxString strDefaultName = nodeUT.GetName();
    ETATConfigNodeType defaultType = nodeUT.GetType();
    
    // Verification
    BOOST_CHECK_EQUAL(nDefaultMaxCount, EXPECTED_MAXCOUNT_VALUE);
    BOOST_CHECK_EQUAL(bDefaultIsObligatory, EXPECTED_ISOBLIGATORY_VALUE);
    BOOST_CHECK_EQUAL(bDefaultCanBeEmpty, EXPECTED_CANBEEMPTY_VALUE);
    BOOST_CHECK_EQUAL(strDefaultName, EXPECTED_NAME_VALUE);
    BOOST_CHECK(defaultType == EXPECTED_TYPE_VALUE);
}

/// <summary>
/// Checks that every parameter of is correctly stored.
/// </summary>
QTEST_CASE ( Constructor2_AllValuesAreCorrectlySet_Test )
{
    // Preparation
    const int EXPECTED_MAXCOUNT_VALUE = 1;
    const bool EXPECTED_ISOBLIGATORY_VALUE = true;
    const bool EXPECTED_CANBEEMPTY_VALUE = true;
    const wxString EXPECTED_NAME_VALUE = wxT("NAME");
    const ETATConfigNodeType EXPECTED_TYPE_VALUE = ETATConfigNodeType::E_VALUE;

	// Execution
    TATRuleNode nodeUT(EXPECTED_NAME_VALUE, EXPECTED_MAXCOUNT_VALUE, EXPECTED_CANBEEMPTY_VALUE, EXPECTED_ISOBLIGATORY_VALUE, EXPECTED_TYPE_VALUE);
    int nDefaultMaxCount = nodeUT.GetMaxCount();
    bool bDefaultIsObligatory = nodeUT.GetIsObligatory();
    bool bDefaultCanBeEmpty = nodeUT.GetCanBeEmpty();
    wxString strDefaultName = nodeUT.GetName();
    ETATConfigNodeType defaultType = nodeUT.GetType();
    
    // Verification
    BOOST_CHECK_EQUAL(nDefaultMaxCount, EXPECTED_MAXCOUNT_VALUE);
    BOOST_CHECK_EQUAL(bDefaultIsObligatory, EXPECTED_ISOBLIGATORY_VALUE);
    BOOST_CHECK_EQUAL(bDefaultCanBeEmpty, EXPECTED_CANBEEMPTY_VALUE);
    BOOST_CHECK_EQUAL(strDefaultName, EXPECTED_NAME_VALUE);
    BOOST_CHECK(defaultType == EXPECTED_TYPE_VALUE);
}

/// <summary>
/// Checks that the maximum count is correctly retrieved.
/// </summary>
QTEST_CASE ( GetMaxCount_MaxCountIsCorrectlyRetrieved_Test )
{
    // Preparation
    const int MAX_COUNT = 1;
    TATRuleNode NODE;
    NODE.SetMaxCount(MAX_COUNT);

	// Execution
    int nMaxCountUT = NODE.GetMaxCount();
    
    // Verification
    BOOST_CHECK_EQUAL(nMaxCountUT, MAX_COUNT);
}

/// <summary>
/// Checks that the maximum count is correctly stored.
/// </summary>
QTEST_CASE ( SetMaxCount_MaxCountIsCorrectlyStored_Test )
{
    // Preparation
    const int MAX_COUNT = 1;

	// Execution
    TATRuleNode nodeUT;
    nodeUT.SetMaxCount(MAX_COUNT);
    
    // Verification
    BOOST_CHECK_EQUAL(nodeUT.GetMaxCount(),  MAX_COUNT);
}

/// <summary>
/// Checks that the "is obligatory" flag is correctly retrieved.
/// </summary>
QTEST_CASE ( GetIsObligatory_IsCorrectlyRetrieved_Test )
{
    // Preparation
    const bool IS_OBLIGATORY = true;
    TATRuleNode NODE;
    NODE.SetIsObligatory(IS_OBLIGATORY);

	// Execution
    bool bIsObligatoryUT = NODE.GetIsObligatory();
    
    // Verification
    BOOST_CHECK_EQUAL(bIsObligatoryUT, IS_OBLIGATORY);
}

/// <summary>
/// Checks that the "is obligatory" flag is correctly stored.
/// </summary>
QTEST_CASE ( SetIsObligatory_IsCorrectlyStored_Test )
{
    // Preparation
    const bool IS_OBLIGATORY = true;

	// Execution
    TATRuleNode nodeUT;
    nodeUT.SetIsObligatory(IS_OBLIGATORY);
    
    // Verification
    BOOST_CHECK_EQUAL(nodeUT.GetIsObligatory(), IS_OBLIGATORY);
}

/// <summary>
/// Checks that the "can be empty" is correctly retrieved.
/// </summary>
QTEST_CASE ( GetCanBeEmpty_IsCorrectlyRetrieved_Test )
{
    // Preparation
    const bool CAN_BE_EMPTY = true;
    TATRuleNode NODE;
    NODE.SetCanBeEmpty(CAN_BE_EMPTY);

	// Execution
    bool bCanBeEmpty = NODE.GetCanBeEmpty();
    
    // Verification
    BOOST_CHECK_EQUAL(bCanBeEmpty, CAN_BE_EMPTY);
}

/// <summary>
/// Checks that the "can be empty" is correctly stored.
/// </summary>
QTEST_CASE ( SetCanBeEmpty_IsCorrectlyStored_Test )
{
    // Preparation
    const bool CAN_BE_EMPTY = true;

	// Execution
    TATRuleNode nodeUT;
    nodeUT.SetCanBeEmpty(CAN_BE_EMPTY);
    
    // Verification
    BOOST_CHECK_EQUAL(nodeUT.GetCanBeEmpty(), CAN_BE_EMPTY);
}


// End - Test Suite: TATRuleNode
QTEST_SUITE_END()
