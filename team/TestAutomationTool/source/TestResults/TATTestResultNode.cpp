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

#include "TestResults/TATTestResultNode.h"


namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |  ATTRIBUTES INITIALIZATION |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################



//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATTestResultNode::TATTestResultNode() : m_eResult(ETATResult::E_NoResult),
                                         m_strMessage(wxT("")),
                                         m_nTime(0),
                                         m_eType(ETATTestResultNodeType::E_Root)
{
}

TATTestResultNode::TATTestResultNode(const wxString &strName) : TATNode(strName),
                                                                m_eResult(ETATResult::E_NoResult),
                                                                m_strMessage(wxT("")),
                                                                m_nTime(0),
                                                                m_eType(ETATTestResultNodeType::E_Root)
{
}

TATTestResultNode::TATTestResultNode(const wxString &strName, 
                                     const ETATResult &eResult, 
                                     const wxString &strMessage, 
                                     const int &nTime, 
                                     const ETATTestResultNodeType &eType) :
                                                                TATNode(strName),
                                                                m_eResult(eResult),
                                                                m_strMessage(strMessage),
                                                                m_nTime(nTime),
                                                                m_eType(eType)
{
}

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

ETATResult TATTestResultNode::GetResult() const
{
    return m_eResult;
}

void TATTestResultNode::SetResult(const ETATResult &eResult)
{
    m_eResult = eResult;
}

wxString TATTestResultNode::GetMessage() const
{
    return m_strMessage;
}

void TATTestResultNode::SetMessage(const wxString &strMessage)
{
    m_strMessage = strMessage;
}

unsigned int TATTestResultNode::GetTime() const
{
    return m_nTime;
}

void TATTestResultNode::SetTime(const unsigned int &nTime)
{
    m_nTime = nTime;
}

ETATTestResultNodeType TATTestResultNode::GetNodeType() const
{
    return m_eType;
}

void TATTestResultNode::SetNodeType(const ETATTestResultNodeType &eType)
{
    m_eType = eType;
}

bool TATTestResultNode::HasErrors() const
{
    bool bHasErrors = (m_eResult == ETATResult::E_Fail || m_eResult == ETATResult::E_Error);

    if(!bHasErrors)
    {
        TNodeCollection::const_iterator iNode = m_children.begin();

        while(iNode != m_children.end() && !bHasErrors)
        {
            bHasErrors = dynamic_cast<TATTestResultNode*>(iNode->second)->HasErrors();
            ++iNode;
        }
    }

    return bHasErrors;
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################



} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis
