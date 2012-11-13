// [TERMS&CONDITIONS]

#include "TestConfiguration/TATRuleNode.h"


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

TATRuleNode::TATRuleNode() : m_bCanBeEmpty(false),
                             m_bIsObligatory(false),
                             m_nMaxCount(false)
{
}

TATRuleNode::TATRuleNode(const wxString& strName, const int nMaxCount, const bool& bCanBeEmpty,
                         const bool& bIsObligatory, const ETATConfigNodeType& type) :
                            m_bCanBeEmpty(bCanBeEmpty),
                            m_bIsObligatory(bIsObligatory),
                            m_nMaxCount(nMaxCount)
{
    m_strName = strName;
    m_type = type;
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################



//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

int TATRuleNode::GetMaxCount() const
{
    return m_nMaxCount;
}

void TATRuleNode::SetMaxCount(const int& nMaxCount)
{
    m_nMaxCount = nMaxCount;
}

bool TATRuleNode::GetIsObligatory() const
{
    return m_bIsObligatory;
}

void TATRuleNode::SetIsObligatory(const bool& bIsObligatory)
{
    m_bIsObligatory = bIsObligatory;
}

bool TATRuleNode::GetCanBeEmpty() const
{
    return m_bCanBeEmpty;
}

void TATRuleNode::SetCanBeEmpty(const bool& bCanBeEmpty)
{
    m_bCanBeEmpty = bCanBeEmpty;
}


} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis
