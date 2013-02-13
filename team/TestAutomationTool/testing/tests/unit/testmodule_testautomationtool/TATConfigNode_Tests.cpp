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

#include "TestConfiguration/TATConfigNode.h"
#include "TestConfiguration/ETATConfigNodeType.h"

using Kinesis::TestAutomationTool::Backend::TATConfigNode;
using Kinesis::TestAutomationTool::Backend::ETATConfigNodeType;

QTEST_SUITE_BEGIN( TATConfigNode_TestSuite )

/// <summary>
/// Checks whether the values assigned to class members by default have not changed.
/// </summary>
QTEST_CASE ( Constructor_DefaultValuesHasNotChanged_Test )
{
    // Preparation
    const wxString EXPECTED_NAME_VALUE = wxT("");
    const ETATConfigNodeType EXPECTED_TYPE_VALUE = ETATConfigNodeType::E_ROOT;

	// Execution
    TATConfigNode configNodeUT;
    ETATConfigNodeType defaultType = configNodeUT.GetType();
    wxString strDefaultName = configNodeUT.GetName();
    
    // Verification
    BOOST_CHECK(defaultType == EXPECTED_TYPE_VALUE);
    BOOST_CHECK_EQUAL(strDefaultName, EXPECTED_NAME_VALUE);
}

/// <summary>
/// Checks that an empty list is returned when the node hasn't got children.
/// </summary>
QTEST_CASE ( GetChildrenByType_NoChildIsReturnedWhenChildListIsEmpty_Test )
{
    // Preparation
    const TATConfigNode PARENT_NODE;
    const ETATConfigNodeType NODE_TYPE = ETATConfigNodeType::E_ROOT;
    const bool HAS_RETURNED_ZERO_NODES = true;

	// Execution
    TATConfigNode::TNodeCollection childrenReturnedUT = PARENT_NODE.GetChildrenByType(NODE_TYPE);

    // Verification
    bool bHasReturnedZeroNodes = childrenReturnedUT.empty();
    BOOST_CHECK_EQUAL(bHasReturnedZeroNodes, HAS_RETURNED_ZERO_NODES);
}

/// <summary>
/// Checks that an empty list is returned when the type of any node's child matches the type being searched.
/// </summary>
QTEST_CASE ( GetChildrenByType_NoChildrenIsReturnedWhenThereIsNoChildOfSearchedType_Test )
{
    // Preparation
    TATConfigNode PARENT_NODE;
    TATConfigNode* CHILD_NODE1 = new TATConfigNode();
    CHILD_NODE1->SetType(ETATConfigNodeType::E_VALUE);
    PARENT_NODE.AddChild(CHILD_NODE1);
    TATConfigNode* CHILD_NODE2 = new TATConfigNode();
    CHILD_NODE2->SetType(ETATConfigNodeType::E_VALUE);
    PARENT_NODE.AddChild(CHILD_NODE2);
    TATConfigNode* CHILD_NODE3 = new TATConfigNode();
    CHILD_NODE3->SetType(ETATConfigNodeType::E_HEADER);
    PARENT_NODE.AddChild(CHILD_NODE3);
    TATConfigNode* CHILD_NODE4 = new TATConfigNode();
    CHILD_NODE4->SetType(ETATConfigNodeType::E_HEADER);
    PARENT_NODE.AddChild(CHILD_NODE4);

    const ETATConfigNodeType NODE_TYPE = ETATConfigNodeType::E_ROOT;
    const bool HAS_RETURNED_ZERO_NODES = true;

	// Execution
    TATConfigNode::TNodeCollection childrenReturnedUT = PARENT_NODE.GetChildrenByType(NODE_TYPE);

    // Verification
    bool bHasReturnedZeroNodes = childrenReturnedUT.empty();
    BOOST_CHECK_EQUAL(bHasReturnedZeroNodes, HAS_RETURNED_ZERO_NODES);
}

/// <summary>
/// Checks that the node's children whose type matches the one being searched are returned, and only them.
/// </summary>
QTEST_CASE ( GetChildrenByType_ChildrenWhoseTypeMatchesTheSearchedOneAreReturned_Test )
{
    // Preparation
    TATConfigNode PARENT_NODE;
    TATConfigNode* CHILD_NODE1 = new TATConfigNode();
    CHILD_NODE1->SetType(ETATConfigNodeType::E_ROOT);
    PARENT_NODE.AddChild(CHILD_NODE1);
    TATConfigNode* CHILD_NODE2 = new TATConfigNode();
    CHILD_NODE2->SetType(ETATConfigNodeType::E_VALUE);
    PARENT_NODE.AddChild(CHILD_NODE2);
    TATConfigNode* CHILD_NODE3 = new TATConfigNode();
    CHILD_NODE3->SetType(ETATConfigNodeType::E_HEADER);
    PARENT_NODE.AddChild(CHILD_NODE3);
    TATConfigNode* CHILD_NODE4 = new TATConfigNode();
    CHILD_NODE4->SetType(ETATConfigNodeType::E_HEADER);
    PARENT_NODE.AddChild(CHILD_NODE4);
    TATConfigNode* CHILD_NODE5 = new TATConfigNode();
    CHILD_NODE5->SetType(ETATConfigNodeType::E_VALUE);
    PARENT_NODE.AddChild(CHILD_NODE5);
    TATConfigNode* CHILD_NODE6 = new TATConfigNode();
    CHILD_NODE6->SetType(ETATConfigNodeType::E_ROOT);
    PARENT_NODE.AddChild(CHILD_NODE6);

    const ETATConfigNodeType NODE_TYPE = ETATConfigNodeType::E_ROOT;
    const size_t EXPECTED_AMMOUNT_OF_FOUND_NODES = 2;

	// Execution
    TATConfigNode::TNodeCollection childrenReturned = PARENT_NODE.GetChildrenByType(NODE_TYPE);

    // Verification
    // - Correct ammount of child nodes found
    size_t nAmmountOfNodes = childrenReturned.size();
    BOOST_CHECK_EQUAL(nAmmountOfNodes, EXPECTED_AMMOUNT_OF_FOUND_NODES);

    // - All the child nodes' type are correct
    TATConfigNode::TNodeCollection::const_iterator it = childrenReturned.begin();

    for(; it != childrenReturned.end(); ++it)
    {
        ETATConfigNodeType type = dynamic_cast<TATConfigNode*>(it->second)->GetType();
        BOOST_CHECK(type == NODE_TYPE);
    }
}

/// <summary>
/// Checks that the type is correctly retrieved.
/// </summary>
QTEST_CASE ( GetType_TypeIsCorrectlyRetrieved_Test )
{
    // Preparation
    const ETATConfigNodeType NODE_TYPE = ETATConfigNodeType::E_VALUE;
    TATConfigNode NODE;
    NODE.SetType(NODE_TYPE);

	// Execution
    ETATConfigNodeType nodeTypeUT = NODE.GetType();
    
    // Verification
    BOOST_CHECK(nodeTypeUT == NODE_TYPE);
}

/// <summary>
/// Checks that the type is correctly stored.
/// </summary>
QTEST_CASE ( SetType_TypeIsCorrectlyStored_Test )
{
    // Preparation
    const ETATConfigNodeType NODE_TYPE = ETATConfigNodeType::E_VALUE;

	// Execution
    TATConfigNode nodeUT;
    nodeUT.SetType(NODE_TYPE);
    
    // Verification
    BOOST_CHECK(nodeUT.GetType() == NODE_TYPE);
}

// End - Test Suite: TATConfigNode
QTEST_SUITE_END()
