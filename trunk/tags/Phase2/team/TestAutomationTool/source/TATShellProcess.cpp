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

#include "TATShellProcess.h"

#include <iostream>

#include "ExternalDefinitions.h"

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

TATShellProcess::TATShellProcess() : m_strCommand(wxT("")),
                                     m_pListener(NULL)
{
}

TATShellProcess::TATShellProcess(const wxString& strCommand, 
                                 TATShellProcess::ITATShellProcessListener* pListener) : 
                                                                m_strCommand(strCommand),
                                                                m_pListener(pListener)
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

TATShellProcess::~TATShellProcess()
{
    m_pListener = NULL;
    m_strCommand.clear();
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

void TATShellProcess::Execute(const bool &bSynchronous)
{

#ifdef TAT_OS_WINDOWS
    #define OPEN_PROCESS(strCommand, strMode) _popen(strCommand, strMode)
    #define CLOSE_PROCESS(pOutputStream) _pclose(pOutputStream)
#elif defined (TAT_OS_LINUX)
    #define OPEN_PROCESS(strCommand, strMode) popen(strCommand, strMode)
    #define CLOSE_PROCESS(pOutputStream) pclose(pOutputStream)
#endif

    const unsigned int BUFFER_SIZE = 128;

    // TODO Change to wide char
    FILE* pProcessOutput = OPEN_PROCESS(m_strCommand.c_str(), "r");

    char buffer[BUFFER_SIZE];

    while( !feof( pProcessOutput ) )
    {
        if( fgets( buffer, BUFFER_SIZE, pProcessOutput ) != NULL )
        {
            this->OnOutputArrived(buffer, BUFFER_SIZE);
        }
    }

    int nProcessResult = CLOSE_PROCESS( pProcessOutput );

    this->OnProcessCompleted(nProcessResult);
}

void TATShellProcess::OnOutputArrived(const char* outputBuffer, const unsigned int& uBufferSize)
{
    if(m_pListener != NULL)
    {
        m_pListener->ProcessOutputHandler(wxString(outputBuffer));
    }
}

void TATShellProcess::OnProcessCompleted(const int& nProcessResult)
{
    if(m_pListener != NULL)
    {
        m_pListener->ProcessCompletedHandler(nProcessResult);
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

void TATShellProcess::SetCommand(const wxString& strCommand)
{
    m_strCommand = strCommand;
}

wxString TATShellProcess::GetCommand() const
{
    return m_strCommand;
}

void TATShellProcess::SetListener(TATShellProcess::ITATShellProcessListener* pListener)
{
    m_pListener = pListener;
}

TATShellProcess::ITATShellProcessListener* TATShellProcess::GetListener() const
{
    return m_pListener;
}


} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis
