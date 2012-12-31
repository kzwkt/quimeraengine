// [TERMS&CONDITIONS]

#include "TestExecution/TATTestResultNode.h"


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
                                         m_nTime(0)
{
}

TATTestResultNode::TATTestResultNode(const wxString &strName) : TATNode(strName),
                                                                m_eResult(ETATResult::E_NoResult),
                                                                m_strMessage(wxT("")),
                                                                m_nTime(0)
{
}

TATTestResultNode::TATTestResultNode(const wxString &strName, const ETATResult &eResult, const wxString &strMessage, const int &nTime) :
                                                                TATNode(strName),
                                                                m_eResult(eResult),
                                                                m_strMessage(strMessage),
                                                                m_nTime(nTime)
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

int TATTestResultNode::GetTime() const
{
    return m_nTime;
}

void TATTestResultNode::SetTime(const int &nTime)
{
    m_nTime = nTime;
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
