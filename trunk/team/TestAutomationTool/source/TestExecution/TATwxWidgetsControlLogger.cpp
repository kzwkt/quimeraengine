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

#include "TestExecution/TATwxWidgetsControlLogger.h"

#include <wx/richtext/richtextctrl.h>


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
	
TATwxWidgetsControlLogger::TATwxWidgetsControlLogger(wxRichTextCtrl* pControl, const bool& bAutoFlush) : 
                                                                            m_pControl(pControl),
                                                                            m_bAutoFlush(bAutoFlush),
                                                                            m_bAutoNewLinePrintEnabled(true),
                                                                            m_bAutoTimePrintEnabled(true)
{
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		  DESTRUCTOR		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATwxWidgetsControlLogger::~TATwxWidgetsControlLogger()
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

void TATwxWidgetsControlLogger::Log(TATFormattedMessage message)
{
    wxCriticalSectionLocker lock(m_criticalSection);

    if(m_bAutoFlush)
    {
        if(m_pControl)
        {
            this->WriteMessage(message);
        }
    }
    else
    {
        m_buffer.push(message);
    }
}

void TATwxWidgetsControlLogger::Flush()
{
    wxCriticalSectionLocker lock(m_criticalSection);

    if(m_pControl)
    {
        while(m_buffer.size() > 0)
        {
            std::queue<TATFormattedMessage>::reference iMessage = m_buffer.front();

            this->WriteMessage(iMessage);

            m_buffer.pop();
        } 
    }
}

void TATwxWidgetsControlLogger::WriteMessagePart(const TATFormattedMessage::TMessagePart& messagePart)
{
    wxString strMessage = messagePart.first;
    const TATMessageFormat& format = messagePart.second;

    // Text color
    m_pControl->BeginTextColour(this->TranslateColor(format.GetColor()));

    // Text styles
    if(format.GetTextStyle() & TATMessageFormat::TEXT_STYLE_BOLD)
    {
        m_pControl->BeginBold();
    }

    if(format.GetTextStyle() & TATMessageFormat::TEXT_STYLE_ITALIC)
    {
        m_pControl->BeginItalic();
    }

    if(format.GetTextStyle() & TATMessageFormat::TEXT_STYLE_UNDERLINE)
    {
        m_pControl->BeginUnderline();
    }

    // Prints the message part
    m_pControl->WriteText(strMessage);

    if(format.GetTextStyle() & TATMessageFormat::TEXT_STYLE_UNDERLINE)
    {
        m_pControl->EndUnderline();
    }

    if(format.GetTextStyle() & TATMessageFormat::TEXT_STYLE_ITALIC)
    {
        m_pControl->EndItalic();
    }

    if(format.GetTextStyle() & TATMessageFormat::TEXT_STYLE_BOLD)
    {
        m_pControl->EndBold();
    }

    m_pControl->EndTextColour();
}

void TATwxWidgetsControlLogger::WriteMessage(TATFormattedMessage& message)
{
    const TATFormattedMessage::TMessagePart* pCurrentMessagePart = message.GetFirstAndResetPointer();

    // Prints the time
    if(m_bAutoTimePrintEnabled)
    {
        WriteMessagePart(TATFormattedMessage::TMessagePart(wxT("[") + wxDateTime::Now().FormatTime() + wxT("] "), TATMessageFormat(ETATColor::E_White)));
    }

    while(pCurrentMessagePart)
    {
        // Prints the message part
        WriteMessagePart(*pCurrentMessagePart);

        pCurrentMessagePart = message.GetNext();
    }

    if(m_bAutoNewLinePrintEnabled)
    {
        m_pControl->SetCaretPosition(m_pControl->GetLastPosition());
    }
    m_pControl->ShowPosition(m_pControl->GetLastPosition());
    m_pControl->UpdateWindowUI();
}

wxColor TATwxWidgetsControlLogger::TranslateColor(const ETATColor& color) const
{
    wxColor result;

    switch(color)
    {
        case ETATColor::E_Black:
            result = *wxBLACK;
            break;
        case ETATColor::E_White:
            result = *wxWHITE;
            break;
        case ETATColor::E_Red:
            result = *wxRED;
            break;
        case ETATColor::E_Yellow:
            result = *wxYELLOW;
            break;
        case ETATColor::E_Blue:
            result = *wxBLUE;
            break;
        case ETATColor::E_Green:
            result = *wxGREEN;
            break;
        case ETATColor::E_Purple:
            result = wxColor("Purple");
            break;
        case ETATColor::E_Grey:
            result = *wxLIGHT_GREY;
            break;
    }

    return result;
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

void TATwxWidgetsControlLogger::SetAutoNewLinePrint(const bool &bEnable)
{
    m_bAutoNewLinePrintEnabled = bEnable;
}

bool TATwxWidgetsControlLogger::GetAutoNewLinePrint() const
{
    return m_bAutoNewLinePrintEnabled;
}

void TATwxWidgetsControlLogger::SetAutoTimePrint(const bool &bEnable)
{
    m_bAutoTimePrintEnabled = bEnable;
}

bool TATwxWidgetsControlLogger::GetAutoTimePrint() const
{
    return m_bAutoTimePrintEnabled;
}


} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis
