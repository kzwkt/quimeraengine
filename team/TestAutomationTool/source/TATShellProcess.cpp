// [TERMS&CONDITIONS]

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
