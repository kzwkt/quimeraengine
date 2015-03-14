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
