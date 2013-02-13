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

#include "TestingExternalDefinitions.h"

#include "TATNode.h"
#include "TATNodeMock.h"

using Kinesis::TestAutomationTool::Backend::TATNode;
using Kinesis::TestAutomationTool::Backend::Test::TATNodeMock;

QTEST_SUITE_BEGIN( TATNode_TestSuite )
    
/// <summary>
/// Checks that all node's members are initialized as empty, by default.
/// </summary>
QTEST_CASE ( Constructor1_MembersAreEmpty_Test )
{
    // Preparation
    const wxString EMPTY_STRING;
    const size_t ELEMENTS_IN_COLLECTION = 0;

	// Execution
    TATNode nodeUT;
    
    // Verification
    BOOST_CHECK_EQUAL(nodeUT.GetName(), EMPTY_STRING);
    BOOST_CHECK_EQUAL(nodeUT.GetChildren().size(), ELEMENTS_IN_COLLECTION);
}

/// <summary>
/// Checks that the node name is correctly set.
/// </summary>
QTEST_CASE ( Constructor2_NameIsCorrectlySet_Test )
{
    // Preparation
    const wxString NODE_NAME = "NODE_NAME";

	// Execution
    TATNode nodeUT(NODE_NAME);
    
    // Verification
    BOOST_CHECK_EQUAL(nodeUT.GetName(), NODE_NAME);
}

/// <summary>
/// Checks that the children collection is initialized as empty.
/// </summary>
QTEST_CASE ( Constructor2_ChildrenIsEmpty_Test )
{
    // Preparation
    const wxString NODE_NAME = "NODE_NAME";
    const size_t ELEMENTS_IN_COLLECTION = 0;

	// Execution
    TATNode nodeUT(NODE_NAME);
    
    // Verification
    BOOST_CHECK_EQUAL(nodeUT.GetChildren().size(), ELEMENTS_IN_COLLECTION);
}

/// <summary>
/// Checks that all the child nodes are also destroyed.
/// </summary>
QTEST_CASE ( Destructor_ChildrenAreDestroyed_Test )
{
    // Preparation
    const int DESTROYED_NODES = 3;
    TATNodeMock* PARENT_NODE = new TATNodeMock();
    PARENT_NODE->AddChild(new TATNodeMock());
    PARENT_NODE->AddChild(new TATNodeMock());

	// Execution
    delete PARENT_NODE;
    
    // Verification
    BOOST_CHECK_EQUAL(TATNodeMock::sm_nDestructorCallCounter, DESTROYED_NODES);

    // Cleaning
    TATNodeMock::sm_nDestructorCallCounter = 0;
}

/// <summary>
/// Checks that the child node is added successfully.
/// </summary>
QTEST_CASE ( AddChild_ChildIsAdded_Test )
{
    // Preparation
    const size_t ELEMENTS_IN_COLLECTION = 1;
    TATNode* NODE_TO_ADD = new TATNode();

	// Execution
    TATNode nodeUT;
    nodeUT.AddChild(NODE_TO_ADD);
    
    // Verification
    BOOST_CHECK_EQUAL(nodeUT.GetChildren().size(), ELEMENTS_IN_COLLECTION);
    BOOST_CHECK_EQUAL(nodeUT.GetChildren().begin()->second, NODE_TO_ADD);
}

/// <summary>
/// Checks that more than one child node with the same name can be added with no errors nor replacements.
/// </summary>
QTEST_CASE ( AddChild_MoreThanOneChildWithSameNameCanBeAdded_Test )
{
    // Preparation
    const size_t ELEMENTS_IN_COLLECTION = 2;
    TATNode* NODE_TO_ADD1 = new TATNode(wxT("RepeatedName"));
    TATNode* NODE_TO_ADD2 = new TATNode(wxT("RepeatedName"));

	// Execution
    TATNode nodeUT;
    nodeUT.AddChild(NODE_TO_ADD1);
    nodeUT.AddChild(NODE_TO_ADD2);
    
    // Verification
    BOOST_CHECK_EQUAL(nodeUT.GetChildren().size(), ELEMENTS_IN_COLLECTION);
}

/// <summary>
/// Checks that the nodes are added successfully.
/// </summary>
QTEST_CASE ( AddChildren_ChildIsAdded_Test )
{
    // Preparation
    const size_t ELEMENTS_IN_COLLECTION = 2;
    TATNode::TNodeCollection NODE_COLLECTION;
    NODE_COLLECTION.insert(TATNode::TNodeNamePair(wxString("NODE1"), new TATNode("NODE1")));
    NODE_COLLECTION.insert(TATNode::TNodeNamePair(wxString("NODE2"), new TATNode("NODE2")));

	// Execution
    TATNode nodeUT;
    nodeUT.AddChildren(NODE_COLLECTION);
    
    // Verification
    BOOST_CHECK_EQUAL(nodeUT.GetChildren().size(), ELEMENTS_IN_COLLECTION);
}

/// <summary>
/// Checks that all the nodes whose names match the given one are retrieved.
/// </summary>
QTEST_CASE ( GetChild_GetsTheCorrectNodes_Test )
{
    // Preparation
    const size_t ELEMENTS_IN_COLLECTION = 2;
    const wxString NODE_NAME1 = "NODE1";
    const wxString NODE_NAME2 = "NODE2";

    TATNode NODE;
    TATNode* NODE1_INSTANCE_1 = new TATNode(NODE_NAME1);
    TATNode* NODE1_INSTANCE_2 = new TATNode(NODE_NAME1);
    TATNode* NODE2_INSTANCE = new TATNode(NODE_NAME2);
    NODE.AddChild(NODE1_INSTANCE_1);
    NODE.AddChild(NODE1_INSTANCE_2);
    NODE.AddChild(NODE2_INSTANCE);

	// Execution
    TATNode::TNodeCollection range = NODE.GetChild(NODE_NAME1);
    
    // Verification
    TATNode::TNodeCollection::iterator node = range.begin();

    BOOST_CHECK_EQUAL(range.size(), ELEMENTS_IN_COLLECTION);
    BOOST_CHECK((node++)->second == NODE1_INSTANCE_1);
    BOOST_CHECK(node->second == NODE1_INSTANCE_2);
}

/// <summary>
/// Checks that all the nodes whose names coincide with the given one are correctly removed.
/// </summary>
QTEST_CASE ( RemoveChild_AllNodesWhoseNameCoincidesAreRemoved_Test )
{
    // Preparation
    const size_t ELEMENTS_IN_COLLECTION = 1;
    const wxString NODE_NAME1 = "NODE1";
    const wxString NODE_NAME2 = "NODE2";

    TATNode PARENT_NODE;
    TATNode* NODE1_INSTANCE_1 = new TATNode(NODE_NAME1);
    TATNode* NODE1_INSTANCE_2 = new TATNode(NODE_NAME1);
    TATNode* NODE2_INSTANCE = new TATNode(NODE_NAME2);
    PARENT_NODE.AddChild(NODE1_INSTANCE_1);
    PARENT_NODE.AddChild(NODE1_INSTANCE_2);
    PARENT_NODE.AddChild(NODE2_INSTANCE);

	// Execution
    PARENT_NODE.RemoveChild(NODE_NAME1);
    
    // Verification
    TATNode::TNodeCollection::const_iterator node = PARENT_NODE.GetChildren().begin();

    BOOST_CHECK_EQUAL(PARENT_NODE.GetChildren().size(), ELEMENTS_IN_COLLECTION);
    BOOST_CHECK(node->second == NODE2_INSTANCE);
}

/// <summary>
/// Checks that all the nodes whose names coincide with the given one are correctly removed.
/// </summary>
QTEST_CASE ( RemoveChildren_AllNodesWhoseNameCoincidesAreRemoved_Test )
{
    // Preparation
    const size_t ELEMENTS_IN_COLLECTION = 1;
    const wxString NODE_NAME1 = "NODE1";
    const wxString NODE_NAME2 = "NODE2";
    const wxString NODE_NAME3 = "NODE3";

    TATNode PARENT_NODE;
    TATNode* NODE1_INSTANCE_1 = new TATNode(NODE_NAME1);
    TATNode* NODE1_INSTANCE_2 = new TATNode(NODE_NAME1);
    TATNode* NODE2_INSTANCE = new TATNode(NODE_NAME2);
    TATNode* NODE3_INSTANCE = new TATNode(NODE_NAME3);
    PARENT_NODE.AddChild(NODE1_INSTANCE_1);
    PARENT_NODE.AddChild(NODE1_INSTANCE_2);
    PARENT_NODE.AddChild(NODE2_INSTANCE);
    PARENT_NODE.AddChild(NODE3_INSTANCE);

    TATNode::TNodeNameList NODE_NAME_LIST;
    NODE_NAME_LIST.push_back(NODE_NAME1);
    NODE_NAME_LIST.push_back(NODE_NAME2);

	// Execution
    PARENT_NODE.RemoveChildren(NODE_NAME_LIST);
    
    // Verification
    TATNode::TNodeCollection::const_iterator node = PARENT_NODE.GetChildren().begin();

    BOOST_CHECK_EQUAL(PARENT_NODE.GetChildren().size(), ELEMENTS_IN_COLLECTION);
    BOOST_CHECK(node->second == NODE3_INSTANCE);
}

/// <summary>
/// Checks whether the result is True when a child is found.
/// </summary>
QTEST_CASE ( HasChild_ReturnsTrueWhenTheChildIsThere_Test )
{
    // Preparation
    const wxString NODE_NAME1 = "NODE1";
    const wxString NODE_NAME2 = "NODE2";

    TATNode PARENT_NODE;
    TATNode* NODE1_INSTANCE_1 = new TATNode(NODE_NAME1);
    TATNode* NODE1_INSTANCE_2 = new TATNode(NODE_NAME1);
    TATNode* NODE2_INSTANCE = new TATNode(NODE_NAME2);
    PARENT_NODE.AddChild(NODE1_INSTANCE_1);
    PARENT_NODE.AddChild(NODE1_INSTANCE_2);
    PARENT_NODE.AddChild(NODE2_INSTANCE);

    const bool THE_COLLECTION_HAS_THE_CHILD = true;

	// Execution
    bool bHasChildUT = PARENT_NODE.HasChild(NODE_NAME1);
    
    // Verification
    BOOST_CHECK_EQUAL(bHasChildUT, THE_COLLECTION_HAS_THE_CHILD);
}

/// <summary>
/// Checks whether the result is False when a child is not found.
/// </summary>
QTEST_CASE ( HasChild_ReturnsFalseWhenTheChildIsNotThere_Test )
{
    // Preparation
    const wxString NODE_NAME1 = "NODE1";
    const wxString NODE_NAME2 = "NODE2";
    const wxString NODE_NAME_NOT_ADDED = "NODE3";

    TATNode PARENT_NODE;
    TATNode* NODE1_INSTANCE_1 = new TATNode(NODE_NAME1);
    TATNode* NODE1_INSTANCE_2 = new TATNode(NODE_NAME1);
    TATNode* NODE2_INSTANCE = new TATNode(NODE_NAME2);
    PARENT_NODE.AddChild(NODE1_INSTANCE_1);
    PARENT_NODE.AddChild(NODE1_INSTANCE_2);
    PARENT_NODE.AddChild(NODE2_INSTANCE);

    const bool THE_COLLECTION_HAS_NOT_THE_CHILD = false;

	// Execution
    bool bHasChildUT = PARENT_NODE.HasChild(NODE_NAME_NOT_ADDED);
    
    // Verification
    BOOST_CHECK_EQUAL(bHasChildUT, THE_COLLECTION_HAS_NOT_THE_CHILD);
}

/// <summary>
/// Checks that the name is correctly retrieved.
/// </summary>
QTEST_CASE ( GetName_NameIsCorrectlyRetrieved_Test )
{
    // Preparation
    const wxString NODE_NAME = "NODE";
    TATNode NODE(NODE_NAME);

	// Execution
    wxString nodeNameUT = NODE.GetName();
    
    // Verification
    BOOST_CHECK_EQUAL(nodeNameUT, NODE_NAME);
}

/// <summary>
/// Checks that the name is correctly stored.
/// </summary>
QTEST_CASE ( SetName_NameIsCorrectlyStored_Test )
{
    // Preparation
    const wxString NODE_NAME = "NODE";

	// Execution
    TATNode nodeUT;
    nodeUT.SetName(NODE_NAME);
    
    // Verification
    BOOST_CHECK_EQUAL(nodeUT.GetName(), NODE_NAME);
}

/// <summary>
/// Checks that all the child nodes are retrieved.
/// </summary>
QTEST_CASE ( GetChildren_AllChildNodesAreRetrieved_Test )
{
    // Preparation
    const size_t ELEMENTS_IN_COLLECTION = 3;
    const wxString NODE_NAME1 = "NODE1";
    const wxString NODE_NAME2 = "NODE2";

    TATNode NODE;
    TATNode* NODE1_INSTANCE_1 = new TATNode(NODE_NAME1);
    TATNode* NODE1_INSTANCE_2 = new TATNode(NODE_NAME1);
    TATNode* NODE2_INSTANCE = new TATNode(NODE_NAME2);
    NODE.AddChild(NODE1_INSTANCE_1);
    NODE.AddChild(NODE1_INSTANCE_2);
    NODE.AddChild(NODE2_INSTANCE);

	// Execution
    TATNode::TNodeCollection childrenUT = NODE.GetChildren();
    
    // Verification
    TATNode::TNodeCollection::iterator node = childrenUT.begin();

    BOOST_CHECK_EQUAL(childrenUT.size(), ELEMENTS_IN_COLLECTION);
    BOOST_CHECK((node++)->second == NODE1_INSTANCE_1);
    BOOST_CHECK((node++)->second == NODE1_INSTANCE_2);
    BOOST_CHECK(node->second == NODE2_INSTANCE);
}

/// <summary>
/// Checks whether the result is True when the parent node has, at least, one child.
/// </summary>
QTEST_CASE ( HasChildren_ReturnsTrueWhenThereAreChildNodes_Test )
{
    // Preparation
    TATNode PARENT_NODE;
    TATNode* NODE_INSTANCE = new TATNode();
    PARENT_NODE.AddChild(NODE_INSTANCE);

    const bool THE_COLLECTION_HAS_CHILDREN = true;

	// Execution
    bool bHasChildUT = PARENT_NODE.HasChildren();
    
    // Verification
    BOOST_CHECK_EQUAL(bHasChildUT, THE_COLLECTION_HAS_CHILDREN);
}

/// <summary>
/// Checks whether the result is False when the parent node has not children.
/// </summary>
QTEST_CASE ( HasChildren_ReturnsFalseWhenThereAreNotChildNodes_Test )
{
    // Preparation
    TATNode PARENT_NODE;

    const bool THE_COLLECTION_HAS_NOT_CHILDREN = false;

	// Execution
    bool bHasChildUT = PARENT_NODE.HasChildren();
    
    // Verification
    BOOST_CHECK_EQUAL(bHasChildUT, THE_COLLECTION_HAS_NOT_CHILDREN);
}

// End - Test Suite: TATNode
QTEST_SUITE_END()
