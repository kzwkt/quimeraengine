// [TERMS&CONDITIONS]

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
