// [TERMS&CONDITIONS]

#include "TestExecution/TATFormattedMessage.h"

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

typedef TATFormattedMessage::TMessagePart TMessagePart;
typedef TATFormattedMessage::TMessagePartCollection TMessagePartCollection;

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

TATFormattedMessage::TATFormattedMessage()
{
    m_partPointer = m_messageParts.begin();
}
	
TATFormattedMessage::TATFormattedMessage(const wxString& strMessage, const TATMessageFormat& format)
{
    this->Append(strMessage, format);
    m_partPointer = m_messageParts.begin();
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		  DESTRUCTOR		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATFormattedMessage::~TATFormattedMessage()
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

TATFormattedMessage& TATFormattedMessage::Append(const wxString& strMessage, const TATMessageFormat& format)
{
    m_messageParts.push_back(TATFormattedMessage::TMessagePart(strMessage, format));
    return *this;
}

void TATFormattedMessage::Clear()
{
    m_messageParts.clear();
}

wxString TATFormattedMessage::GetFullMessage() const
{
    wxString strFullMessage;

    for(TATFormattedMessage::TMessagePartCollection::const_iterator iPart = m_messageParts.begin(); iPart != m_messageParts.end(); ++iPart)
    {
        strFullMessage.Append(iPart->first);
    }

    return strFullMessage;
}

const TATFormattedMessage::TMessagePart* TATFormattedMessage::GetFirstAndResetPointer()
{
    m_partPointer = m_messageParts.begin();

    if(m_partPointer == m_messageParts.end())
    {
        return NULL;
    }
    else
    {
        return &(*m_partPointer);
    }
}

const TATFormattedMessage::TMessagePart* TATFormattedMessage::GetNext()
{
    if(m_messageParts.size() > 0 && m_partPointer != m_messageParts.end())
    {
        ++m_partPointer;

        if(m_partPointer == m_messageParts.end())
        {
            return NULL;
        }
        else
        {
            return &(*m_partPointer);
        }
    }
    else
    {
        return NULL;
    }
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
