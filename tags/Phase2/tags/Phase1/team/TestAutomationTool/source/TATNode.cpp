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

#include "TATNode.h"

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATNode::TATNode()
{
    m_children.clear();
    m_strName.Clear();
}

TATNode::TATNode(const wxString strName)
{
    m_strName = strName;
    m_children.clear();
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		  DESTRUCTOR		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATNode::~TATNode()
{
    for(TNodeCollection::iterator i = m_children.begin(); i != m_children.end(); ++i)
    {
        delete i->second;
        i->second = NULL;
    }

    m_children.clear();
    m_strName.Clear();
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

void TATNode::AddChild(TATNode* pChildNode)
{
    if(pChildNode != NULL)
        m_children.insert(TNodeNamePair(pChildNode->GetName(), pChildNode));
}

void TATNode::AddChildren(const TNodeCollection& children)
{
    if(children.size() > 0)
        for(TNodeCollection::const_iterator i = children.begin(); i != children.end(); ++i)
            if(i->second != NULL)
                m_children.insert(TNodeNamePair(i->first, i->second));
}

TATNode::TNodeCollection TATNode::GetChild(const wxString& strChildName) const
{
    // Gets all nodes for the given name
    TNodeRange range = m_children.equal_range(strChildName);

    // Copies them into a result set
    TNodeCollection result;

    for(TNodeCollection::const_iterator i = range.first; i != range.second; ++i)
        result.insert(*i);

    return result;
}

void TATNode::RemoveChild(const wxString& strChildName)
{
    m_children.erase(strChildName);
}

void TATNode::RemoveChildren(const TNodeNameList& childrenNames)
{
    for(TNodeNameList::const_iterator i = childrenNames.begin(); i != childrenNames.end(); ++i)
        m_children.erase(*i);
}

bool TATNode::HasChild(const wxString& strChildName) const
{
    TNodeCollection::const_iterator foundNode = m_children.find(strChildName);

    return foundNode != m_children.end();
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

wxString TATNode::GetName() const
{
    return m_strName;
}

void TATNode::SetName(const wxString& strName)
{
    m_strName = strName;
}

const TATNode::TNodeCollection& TATNode::GetChildren() const
{
    return m_children;
}

bool TATNode::HasChildren() const
{
    return m_children.size() > 0;
}

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis
