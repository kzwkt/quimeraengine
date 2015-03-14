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

#include "TestExecution/TATTestAutomationToolExecution.h"

#include <algorithm>
#include <boost/property_tree/detail/xml_parser_error.hpp>

#include "TestExecution/TATwxWidgetsControlLogger.h"
#include "TestExecution/TATFormattedMessage.h"
#include "TestExecution/ETATColor.h"
#include "TestExecution/TATMessageFormat.h"
#include "ExternalDefinitions.h"
#include "STATFileSystemHelper.h"
#include "TestResults/TATTestResultInfo.h"

// Defines the events related to multithread test execution
wxDEFINE_EVENT(wxEVT_COMMAND_EXECUTIONTHREAD_COMPLETED, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_EXECUTIONTHREAD_LOG_UPDATE, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_EXECUTIONTHREAD_NOTIFICATION, wxThreadEvent);
// Defines the events related to the test execution process
wxDEFINE_EVENT(wxEVT_COMMAND_TESTEXECUTION_FINISHED, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_TESTEXECUTION_PARSE_TESTRESULTS, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_TESTEXECUTION_NOTIFICATION, wxCommandEvent);

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

const wxString TATTestAutomationToolExecution::BACKUP_SUFFIX = wxT(".bak");


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATTestAutomationToolExecution::TATTestAutomationToolExecution() : m_pExecutionThread(NULL),
                                                                   m_pLogger(NULL),
                                                                   m_pTestExecutionEventListener(NULL)
{
    // Subscribes to thread events
    this->Connect( wxEVT_COMMAND_EXECUTIONTHREAD_LOG_UPDATE, wxThreadEventHandler(TATTestAutomationToolExecution::OnTestExecutionThreadLogUpdate) );
    this->Connect( wxEVT_COMMAND_EXECUTIONTHREAD_COMPLETED, wxThreadEventHandler(TATTestAutomationToolExecution::OnTestExecutionThreadCompletion) );
    this->Connect( wxEVT_COMMAND_EXECUTIONTHREAD_NOTIFICATION, wxThreadEventHandler(TATTestAutomationToolExecution::OnTestExecutionThreadNotification) );
}

TATTestAutomationToolExecution::TATTestExecutionThread::TATTestExecutionThread(TATTestAutomationToolExecution* pHandler)
{
    m_pHandler = pHandler;
    m_nLastProcessResult = 0;
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		  DESTRUCTOR		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATTestAutomationToolExecution::~TATTestAutomationToolExecution()
{
    this->Destroy();
}

TATTestAutomationToolExecution::TATTestExecutionThread::~TATTestExecutionThread()
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

void TATTestAutomationToolExecution::Destroy()
{
    if(m_pExecutionThread != NULL)
    {
        m_pExecutionThread->Delete();
        delete m_pExecutionThread;
        m_pExecutionThread = NULL;
    }

    if(m_pLogger != NULL)
    {
        delete m_pLogger;
        m_pLogger = NULL;
    }
}

void TATTestAutomationToolExecution::ExecuteTests()
{
    // Creates a new thread
    m_pExecutionThread = new TATTestExecutionThread(this);

    if ( m_pExecutionThread->Create() != wxTHREAD_NO_ERROR )
    {
        delete m_pExecutionThread;
        m_pExecutionThread = NULL;
    }
    else
    {
        m_pExecutionThread->SetPriority(WXTHREAD_MIN_PRIORITY);

        // Starts the execution of the tests in the new thread
        if (m_pExecutionThread->Run() != wxTHREAD_NO_ERROR )
        {
            delete m_pExecutionThread;
            m_pExecutionThread = NULL;
        }
    }
}

void TATTestAutomationToolExecution::StopTestExecution()
{
    m_pExecutionThread->Delete();
}

void TATTestAutomationToolExecution::ParseTestResultFile(const wxString& strTestResultFilePath, 
                                                         const wxString& strCompilationConfig,
                                                         const wxString& strCompilerName,
                                                         const wxString& strFlagCombinationName,
                                                         const wxString& strFlagCombinationValues)
{
    TATTestResultInfo* info = new TATTestResultInfo();
    info->SetCompilationConfiguration(strCompilationConfig);
    info->SetCompilerName(strCompilerName);
    info->SetFlagCombinationName(strFlagCombinationName);
    info->SetFlagCombinationValues(strFlagCombinationValues);

    wxCommandEvent* pEventData = new wxCommandEvent(wxEVT_COMMAND_TESTEXECUTION_PARSE_TESTRESULTS);
    pEventData->SetClientData((void*)(info));
    pEventData->SetString(strTestResultFilePath);

    // Raises the event
    wxQueueEvent(m_pTestExecutionEventListener, pEventData);
}

bool TATTestAutomationToolExecution::TATTestExecutionThread::CreateConfigurationFileBackup(const wxString& strConfigurationFilePath) const
{
    // Makes a copy with a suffix
    return STATFileSystemHelper::Copy(strConfigurationFilePath, strConfigurationFilePath + BACKUP_SUFFIX);
}

bool TATTestAutomationToolExecution::TATTestExecutionThread::RestoreConfigurationFileBackup(const wxString& strConfigurationFilePath) const
{
    // Copies back the back-up file to the original path
    if(STATFileSystemHelper::Copy(strConfigurationFilePath + BACKUP_SUFFIX, strConfigurationFilePath))
    {
        // Deletes the back-up file
        return(STATFileSystemHelper::Delete(strConfigurationFilePath + BACKUP_SUFFIX));
    }
    else
    {
        return false;
    }
}

bool TATTestAutomationToolExecution::TATTestExecutionThread::ReplaceFlagValuesInConfigurationFile(
                                                                    const wxString& strConfigurationFilePath,
                                                                    const std::map<wxString, wxString>& replacements) const
{
    bool bResult = false;
    wxString strFileContent;

    bResult = STATFileSystemHelper::Read(strConfigurationFilePath, strFileContent);

    if(bResult)
    {
        wxString strReplacedFileContent = ReplaceFlagValues(strFileContent, replacements);

        bResult = STATFileSystemHelper::Write(strConfigurationFilePath, strReplacedFileContent);
    }

    return bResult;
}

wxString TATTestAutomationToolExecution::TATTestExecutionThread::ReplaceFlagValues(const wxString& strSource,
                                                                                   const std::map<wxString, wxString>& replacements) const
{
    wxString strResult = strSource;

    for(std::map<wxString, wxString>::const_iterator iReplacement = replacements.begin(); iReplacement != replacements.end(); ++iReplacement)
    {
        // Gets the position just after the flag
        size_t nFlagPos = strResult.Find(iReplacement->first);

        // If found...
        if(nFlagPos != wxString::npos)
        {
            nFlagPos += iReplacement->first.size();

            // Gets the position of the end of the line where the flag is defined
            size_t nEOLPos = strResult.find_first_of(TAT_NEWLINE_TOKEN, nFlagPos);

            // If found...
            if(nEOLPos != wxString::npos)
            {
                strResult = strResult.replace(nFlagPos, nEOLPos - nFlagPos, wxT(" ") + iReplacement->second);
            }
            else // EOF
            {
                strResult = strResult.replace(nFlagPos, strResult.size() - nFlagPos, wxT(" ") + iReplacement->second);
            }
        }
    }

    return strResult;
}

bool TATTestAutomationToolExecution::TATTestExecutionThread::ExecuteCompilerCommand(const wxString& strCompilerPath,
                                                                                    const wxString& strCommand,
                                                                                    const wxString& strConfiguration,
                                                                                    const wxString& strProjectFilePath,
                                                                                    const wxString& strParams,
                                                                                    const wxString& strFileSpecifier)
{
    bool bResult = false;

    try
    {
        // The output of the process has to be a continuous string, so new lines and time must not be printed
        m_pHandler->GetLogger()->SetAutoNewLinePrint(false);
        m_pHandler->GetLogger()->SetAutoTimePrint(false);

        bResult = STATFileSystemHelper::Execute(strCompilerPath, strFileSpecifier + wxT(" ") + wxT(" \"") + strProjectFilePath + wxT("\" ") + strCommand + strConfiguration + wxT(" ") + strParams, this);

        m_pHandler->GetLogger()->SetAutoNewLinePrint(true);
        m_pHandler->GetLogger()->SetAutoTimePrint(true);
    }
    catch(...)
    {
        bResult = false;
    }

    return bResult;
}

bool TATTestAutomationToolExecution::TATTestExecutionThread::ExecuteTestModule(const wxString& strTestModulePath)
{
    bool bResult = false;

    try
    {
        // The output of the process has to be a continuous string, so new lines and time must not be printed
        m_pHandler->GetLogger()->SetAutoNewLinePrint(false);
        m_pHandler->GetLogger()->SetAutoTimePrint(false);

        bResult = STATFileSystemHelper::Execute(strTestModulePath, wxT(""), this);

        m_pHandler->GetLogger()->SetAutoNewLinePrint(true);
        m_pHandler->GetLogger()->SetAutoTimePrint(true);
    }
    catch(...)
    {
        bResult = false;
    }

    return bResult;
}

std::list<wxString> TATTestAutomationToolExecution::TATTestExecutionThread::ReadTestModuleFiles(const wxString& strFolderPath) const
{
    return STATFileSystemHelper::ListFolderContent(strFolderPath, STATFileSystemHelper::GetExecutableFileExtension());
}

std::list<wxString> TATTestAutomationToolExecution::TATTestExecutionThread::ReadTestResultFiles(const wxString& strFolderPath) const
{
    return STATFileSystemHelper::ListFolderContent(strFolderPath, wxT("xml"));
}

wxThread::ExitCode TATTestAutomationToolExecution::TATTestExecutionThread::Entry()
{
    // [TODO] Thund: This method has to be split and refactored, there is no time to do it at the moment
    // [TODO] Thund: It would be good to localize all the literals of this method

    const int SUCCESS = 0;

    // Logger formats
    const TATMessageFormat LOG_FORMAT_NORMAL(ETATColor::E_White);
    const TATMessageFormat LOG_FORMAT_ERROR(ETATColor::E_Red, TATMessageFormat::TEXT_STYLE_BOLD);
    const TATMessageFormat LOG_FORMAT_PROCESS_TITLE(ETATColor::E_White, TATMessageFormat::TEXT_STYLE_UNDERLINE);
    const TATMessageFormat LOG_FORMAT_DATA_HIGHLIGHT(ETATColor::E_Yellow, TATMessageFormat::TEXT_STYLE_ITALIC);

    const wxString INFO_NOTIFICATION = wxT("[i] ");
    const wxString ERROR_NOTIFICATION = wxT("[E] ");

    try
    {
        std::list<wxString> parsedResultFiles;
        wxString strConfigurationFilePath = m_pHandler->GetConfigurationFilePath();
        TFlagCombinationCollection flagCombinations = m_pHandler->GetFlagCombinations();
        std::list<wxString> compilationConfigurations = m_pHandler->GetCompilationConfigurations();
        std::map<wxString, TATCompilerInfo> compilerInfos = m_pHandler->GetCompilerInfos();

        this->Log(TATFormattedMessage(wxT("Test execution process starts."), LOG_FORMAT_PROCESS_TITLE));
        this->NotifyEvent(INFO_NOTIFICATION + wxT("START"));
        this->Log(TATFormattedMessage(wxT("Current working directory: '"), LOG_FORMAT_NORMAL).
                               Append(wxGetCwd(), LOG_FORMAT_DATA_HIGHLIGHT).
                               Append(wxT("'."), LOG_FORMAT_NORMAL));

        // 1. Creates a backup of the configuration file
        this->Log(TATFormattedMessage(wxT("Creating a back-up copy of the configuration file at '"), LOG_FORMAT_NORMAL).
                               Append(strConfigurationFilePath + BACKUP_SUFFIX, LOG_FORMAT_DATA_HIGHLIGHT).
                               Append(wxT("'..."), LOG_FORMAT_NORMAL));

        if(this->CreateConfigurationFileBackup(strConfigurationFilePath))
        {
            this->Log(TATFormattedMessage(wxT("Back-up copy created."), LOG_FORMAT_NORMAL));

            // 2. For each flag combination...
            for(TFlagCombinationCollection::const_iterator iFlagCombination = flagCombinations.begin(); iFlagCombination != flagCombinations.end(); ++iFlagCombination)
            {
                if(this->TestDestroy()) throw std::exception();

                // 2.1 Replaces the flag values in the configuration file
                this->Log(TATFormattedMessage(wxT("Setting flag values of the combination '"), LOG_FORMAT_NORMAL).
                                       Append(iFlagCombination->first, LOG_FORMAT_DATA_HIGHLIGHT).
                                       Append(wxT("' in the configuration file..."), LOG_FORMAT_NORMAL));
                this->NotifyEvent(INFO_NOTIFICATION + iFlagCombination->first + wxT(" flag values"));

                const TFlagCombinationValues& flagCombinationValues = iFlagCombination->second;

                wxString strFlagValues;

                for(std::map<wxString, wxString>::const_iterator iFlagValue = flagCombinationValues.begin(); iFlagValue != flagCombinationValues.end(); ++iFlagValue)
                {
                    strFlagValues += iFlagValue->first + wxT(" = ") + iFlagValue->second + TAT_NEWLINE_TOKEN;
                    this->Log(TATFormattedMessage(iFlagValue->first + wxT(" = ") + iFlagValue->second, LOG_FORMAT_NORMAL));
                }

                if(this->ReplaceFlagValuesInConfigurationFile(strConfigurationFilePath, flagCombinationValues))
                {
                    this->Log(TATFormattedMessage(wxT("Flag values set."), LOG_FORMAT_NORMAL));
                }
                else
                {
                    this->Log(TATFormattedMessage(wxT("Flag values couldn't be set. The file may not be accessible."), LOG_FORMAT_ERROR));
                }

                // 2.2 For each compiler configuration...
                for(std::list<wxString>::const_iterator iCompilationConfig = compilationConfigurations.begin(); iCompilationConfig != compilationConfigurations.end(); ++iCompilationConfig)
                {
                    if(this->TestDestroy()) throw std::exception();

                    this->Log(TATFormattedMessage(wxT("Preparing to compile with configuration '"), LOG_FORMAT_NORMAL).
                                           Append(*iCompilationConfig, LOG_FORMAT_DATA_HIGHLIGHT).
                                           Append(wxT("'..."), LOG_FORMAT_NORMAL));
                    this->NotifyEvent(INFO_NOTIFICATION + *iCompilationConfig + wxT(" configuration"));

                    // 2.2.1 For each compiler...
                    for(std::map<wxString, TATCompilerInfo>::const_iterator iCompilerInfo = compilerInfos.begin(); iCompilerInfo != compilerInfos.end(); ++iCompilerInfo)
                    {
                        if(this->TestDestroy()) throw std::exception();

                        const TATCompilerInfo& compilerInfo = iCompilerInfo->second;

                        this->Log(TATFormattedMessage(wxT("Using compiler '"), LOG_FORMAT_NORMAL).
                                               Append(compilerInfo.GetName(), LOG_FORMAT_DATA_HIGHLIGHT).
                                               Append(wxT("' located at '"), LOG_FORMAT_NORMAL).
                                               Append(compilerInfo.GetCompilerPath(), LOG_FORMAT_DATA_HIGHLIGHT).
                                               Append(wxT("'."), LOG_FORMAT_NORMAL));
                        this->NotifyEvent(INFO_NOTIFICATION + compilerInfo.GetName() + wxT(" compiler"));

                        // 2.2.1.1 Rebuilds every project of the SUT...
                        const std::list<wxString>& sutProjects = compilerInfo.GetSUTProjects();

                        bool bExecSucceeded;

                        for(std::list<wxString>::const_iterator iProject = sutProjects.begin(); iProject != sutProjects.end(); ++iProject)
                        {
                            if(this->TestDestroy()) throw std::exception();

                            this->Log(TATFormattedMessage(wxT("Compiling SUT project: '"), LOG_FORMAT_NORMAL).
                                                   Append(*iProject, LOG_FORMAT_DATA_HIGHLIGHT).
                                                   Append(wxT("'..."), LOG_FORMAT_NORMAL));
                            this->NotifyEvent(INFO_NOTIFICATION + *iProject + wxT(" project"));

                            this->Log(TATFormattedMessage(wxT("Cleaning..."), LOG_FORMAT_NORMAL));
                            this->Log(TATFormattedMessage(compilerInfo.GetCompilerPath() + wxT(" ") + compilerInfo.GetFileSpecifier() + wxT(" \"") + *iProject + wxT("\" ") + compilerInfo.GetCleanCommand() + *iCompilationConfig + wxT(" ") + compilerInfo.GetCleanParams(), LOG_FORMAT_DATA_HIGHLIGHT));

                            bExecSucceeded = this->ExecuteCompilerCommand(compilerInfo.GetCompilerPath(), compilerInfo.GetCleanCommand(), *iCompilationConfig, *iProject, compilerInfo.GetCleanParams(), compilerInfo.GetFileSpecifier());

                            if(m_nLastProcessResult < SUCCESS || !bExecSucceeded)
                            {
                                this->Log(TATFormattedMessage(wxT("The execution of the command failed."), LOG_FORMAT_ERROR));
                                this->NotifyEvent(ERROR_NOTIFICATION + wxT("Clean command failed"));
                            }

                            if(this->TestDestroy()) throw std::exception();

                            this->Log(TATFormattedMessage(wxT("Building..."), LOG_FORMAT_NORMAL));
                            this->Log(TATFormattedMessage(compilerInfo.GetCompilerPath() + wxT(" ") + compilerInfo.GetFileSpecifier() + wxT(" \"") + *iProject + wxT("\" ") + compilerInfo.GetBuildCommand() + *iCompilationConfig + wxT(" ") + compilerInfo.GetBuildParams(), LOG_FORMAT_DATA_HIGHLIGHT));

                            bExecSucceeded = this->ExecuteCompilerCommand(compilerInfo.GetCompilerPath(), compilerInfo.GetBuildCommand(), *iCompilationConfig, *iProject, compilerInfo.GetBuildParams(), compilerInfo.GetFileSpecifier());

                            if(m_nLastProcessResult < SUCCESS || !bExecSucceeded)
                            {
                                this->Log(TATFormattedMessage(wxT("The execution of the command failed."), LOG_FORMAT_ERROR));
                                this->NotifyEvent(ERROR_NOTIFICATION + wxT("Build command failed"));
                            }

                            if(this->TestDestroy()) throw std::exception();
                        }

                        // 2.2.1.2 Rebuilds every test project...
                        const std::list<TATTestModulesExecutionInfo>& testModuleInfos = compilerInfo.GetTestModulesExecutionInfo();

                        for(std::list<TATTestModulesExecutionInfo>::const_iterator iTestModuleInfo = testModuleInfos.begin(); iTestModuleInfo !=  testModuleInfos.end(); ++iTestModuleInfo)
                        {
                            if(this->TestDestroy()) throw std::exception();

                            this->Log(TATFormattedMessage(wxT("Compiling test project: '"), LOG_FORMAT_NORMAL).
                                                   Append(iTestModuleInfo->GetTestProjectPath(), LOG_FORMAT_DATA_HIGHLIGHT).
                                                   Append(wxT("'..."), LOG_FORMAT_NORMAL));
                            this->NotifyEvent(INFO_NOTIFICATION + iTestModuleInfo->GetTestProjectPath() + wxT(" test project"));

                            this->Log(TATFormattedMessage(wxT("Cleaning..."), LOG_FORMAT_NORMAL));
                            this->Log(TATFormattedMessage(compilerInfo.GetCompilerPath() + wxT(" ") + compilerInfo.GetFileSpecifier() + wxT(" \"") + iTestModuleInfo->GetTestProjectPath() + wxT("\" ") + compilerInfo.GetCleanCommand() + *iCompilationConfig + wxT(" ") + compilerInfo.GetCleanParams(), LOG_FORMAT_DATA_HIGHLIGHT));

                            bExecSucceeded = this->ExecuteCompilerCommand(compilerInfo.GetCompilerPath(), compilerInfo.GetCleanCommand(), *iCompilationConfig, iTestModuleInfo->GetTestProjectPath(), compilerInfo.GetCleanParams(), compilerInfo.GetFileSpecifier());

                            if(m_nLastProcessResult < SUCCESS || !bExecSucceeded)
                            {
                                this->Log(TATFormattedMessage(wxT("The execution of the command failed."), LOG_FORMAT_ERROR));
                                this->NotifyEvent(ERROR_NOTIFICATION + wxT("Clean command failed"));
                            }

                            if(this->TestDestroy()) throw std::exception();

                            this->Log(TATFormattedMessage(wxT("Building..."), LOG_FORMAT_NORMAL));
                            this->Log(TATFormattedMessage(compilerInfo.GetCompilerPath() + wxT(" ") + compilerInfo.GetFileSpecifier() + wxT(" \"") + iTestModuleInfo->GetTestProjectPath() + wxT("\" ") + compilerInfo.GetBuildCommand() + *iCompilationConfig + wxT(" ") + compilerInfo.GetBuildParams(), LOG_FORMAT_DATA_HIGHLIGHT));

                            bExecSucceeded = this->ExecuteCompilerCommand(compilerInfo.GetCompilerPath(), compilerInfo.GetBuildCommand(), *iCompilationConfig, iTestModuleInfo->GetTestProjectPath(), compilerInfo.GetBuildParams(), compilerInfo.GetFileSpecifier());

                            if(m_nLastProcessResult < SUCCESS || !bExecSucceeded)
                            {
                                this->Log(TATFormattedMessage(wxT("The execution of the command failed."), LOG_FORMAT_ERROR));
                                this->NotifyEvent(ERROR_NOTIFICATION + wxT("Build command failed"));
                            }

                            if(this->TestDestroy()) throw std::exception();

                            // 2.2.1.2.1 Removes test result files of previous executions

                            // If this is the first test result file to write for this execution...
                            if(parsedResultFiles.size() == 0)
                            {
                                this->Log(TATFormattedMessage(wxT("Removing previous test result files from '"), LOG_FORMAT_NORMAL).
                                                    Append(iTestModuleInfo->GetResultsPath(), LOG_FORMAT_DATA_HIGHLIGHT).
                                                    Append(wxT("'..."), LOG_FORMAT_NORMAL));

                                if(this->DeletePreviousResultFiles(iTestModuleInfo->GetResultsPath()))
                                {
                                    this->Log(TATFormattedMessage(wxT("Result files removed."), LOG_FORMAT_NORMAL));
                                }
                            }

                            // 2.2.1.2.2 Execute every test module...

                            // Obtains the paths of all the test modules
                            std::list<wxString> testModulePaths = this->ReadTestModuleFiles(iTestModuleInfo->GetTestModulesPath() + *iCompilationConfig);

                            if(testModulePaths.empty())
                            {
                                this->Log(TATFormattedMessage(wxT("No modules were found at '"), LOG_FORMAT_ERROR).
                                                       Append(iTestModuleInfo->GetTestModulesPath() + *iCompilationConfig, LOG_FORMAT_DATA_HIGHLIGHT).
                                                       Append(wxT("'."), LOG_FORMAT_ERROR));
                                this->NotifyEvent(ERROR_NOTIFICATION + iTestModuleInfo->GetTestModulesPath() + *iCompilationConfig + wxT(" modules folder"));
                            }

                            for(std::list<wxString>::const_iterator iTestModulePath = testModulePaths.begin(); iTestModulePath != testModulePaths.end(); ++iTestModulePath)
                            {
                                if(this->TestDestroy()) throw std::exception();

                                this->Log(TATFormattedMessage(wxT("Executing test module '"), LOG_FORMAT_NORMAL).
                                                       Append(*iTestModulePath, LOG_FORMAT_DATA_HIGHLIGHT).
                                                       Append(wxT("'..."), LOG_FORMAT_NORMAL));
                                this->NotifyEvent(INFO_NOTIFICATION + *iTestModulePath + wxT(" test module"));

                                // Sets the working directory. Many modules needs to read configuration files refered to by relative paths
                                wxString strPreviousWorkingDirectory = wxGetCwd();
                                wxSetWorkingDirectory(iTestModuleInfo->GetTestModulesPath() + *iCompilationConfig);

                                wxString strTestModulePath;
#ifdef TAT_OS_WINDOWS
                                strTestModulePath = *iTestModulePath;
#elif defined(TAT_OS_LINUX)
                                // Linux needs to specify the folder of the executable file, since it's not registered as a command
                                strTestModulePath = wxT("./") + *iTestModulePath;
#else
    #error Test module path not defined!
#endif

                                bExecSucceeded = this->ExecuteTestModule(strTestModulePath);

                                if(m_nLastProcessResult < SUCCESS || !bExecSucceeded)
                                {
                                    this->Log(TATFormattedMessage(wxT("The execution of the test module failed."), LOG_FORMAT_ERROR));
                                    this->NotifyEvent(ERROR_NOTIFICATION + wxT("Test module failed"));
                                }

                                // Restores the working directory
                                wxSetWorkingDirectory(strPreviousWorkingDirectory);

                                // 2.2.1.2.1.1 Parses the test result files

                                // Obtains a list with all the existent result files
                                std::list<wxString> testResultFiles = this->ReadTestResultFiles(iTestModuleInfo->GetResultsPath());

                                if(testResultFiles.empty())
                                {
                                    this->Log(TATFormattedMessage(wxT("No result files were found at '"), LOG_FORMAT_ERROR).
                                                           Append(iTestModuleInfo->GetResultsPath(), LOG_FORMAT_DATA_HIGHLIGHT).
                                                           Append(wxT("'."), LOG_FORMAT_ERROR));
                                    this->NotifyEvent(ERROR_NOTIFICATION + iTestModuleInfo->GetResultsPath() + wxT(" result files folder"));
                                }

                                // Checks if there are new files to parse
                                for(std::list<wxString>::const_iterator iResultFilePath = testResultFiles.begin(); iResultFilePath != testResultFiles.end(); ++iResultFilePath)
                                {
                                    if(this->TestDestroy()) throw std::exception();

                                    if(std::find(parsedResultFiles.begin(), parsedResultFiles.end(), iTestModuleInfo->GetResultsPath() + *iResultFilePath) == parsedResultFiles.end())
                                    {
                                        // If the file was not already parsed, parse it now
                                        this->Log(TATFormattedMessage(wxT("Parsing test result file '"), LOG_FORMAT_NORMAL).
                                                               Append(*iResultFilePath, LOG_FORMAT_DATA_HIGHLIGHT).
                                                               Append(wxT("'..."), LOG_FORMAT_NORMAL));
                                        this->NotifyEvent(INFO_NOTIFICATION + *iResultFilePath + wxT(" result file"));

                                        bool bResultFileParsingFailed = false;

                                        try
                                        {
                                            m_pHandler->ParseTestResultFile(iTestModuleInfo->GetResultsPath() + *iResultFilePath, 
                                                                            *iCompilationConfig, 
                                                                            iCompilerInfo->second.GetName(), 
                                                                            iFlagCombination->first, 
                                                                            strFlagValues);
                                        }
                                        catch(const boost::property_tree::xml_parser::xml_parser_error &ex)
                                        {
                                            bResultFileParsingFailed = true;
                                            this->Log(TATFormattedMessage(wxString(wxT("Failed to parse the result file:")) + ex.what(), LOG_FORMAT_ERROR));
                                            this->NotifyEvent(ERROR_NOTIFICATION + wxT("Parsing test result failed"));
                                        }

                                        if(!bResultFileParsingFailed)
                                        {
                                            this->Log(TATFormattedMessage(wxT("Test result file parsed."), LOG_FORMAT_NORMAL));
                                        }

                                        // Saves the path of the file in the list of parsed files
                                        parsedResultFiles.push_back(iTestModuleInfo->GetResultsPath() + *iResultFilePath);
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // Restores the configuration file at the end of the process
            this->Log(TATFormattedMessage(wxT("Restoring the configuration file..."), LOG_FORMAT_NORMAL));

            if(this->RestoreConfigurationFileBackup(strConfigurationFilePath))
            {
                this->Log(TATFormattedMessage(wxT("Configuration file restored."), LOG_FORMAT_NORMAL));
            }
            else
            {
                this->Log(TATFormattedMessage(wxT("The configuration file or the back-up copy were not accessible. Configuration file couldn't be restored."), LOG_FORMAT_ERROR));
                this->NotifyEvent(ERROR_NOTIFICATION + wxT("Configuration file couldn't be restored"));
            }
        }
        else
        {
            this->Log(TATFormattedMessage(wxT("The configuration file was not accessible. Back-up copy couldn't be created. Please, verify that the path is correct: '"), LOG_FORMAT_ERROR).
                                   Append(strConfigurationFilePath, LOG_FORMAT_DATA_HIGHLIGHT).
                                   Append(wxT("'."), LOG_FORMAT_ERROR));
            this->NotifyEvent(ERROR_NOTIFICATION + wxT("Configuration file was not accessible"));
        }

        this->Log(TATFormattedMessage(wxT("Finalizing test execution process."), LOG_FORMAT_NORMAL));
    }
    catch(const std::exception& ex)
    {
        this->Log(TATFormattedMessage(wxT("Abnormal termination: ") + wxString(ex.what()), LOG_FORMAT_ERROR));
        this->NotifyEvent(ERROR_NOTIFICATION + wxT("Abnormal termination"));
    }
    catch(...)
    {
        this->Log(TATFormattedMessage(wxT("Abnormal termination. Unknown reason."), LOG_FORMAT_ERROR));
        this->NotifyEvent(ERROR_NOTIFICATION + wxT("Abnormal termination"));
    }

    this->NotifyEvent(INFO_NOTIFICATION + wxT("FINISH"));

    wxQueueEvent(m_pHandler, new wxThreadEvent(wxEVT_COMMAND_EXECUTIONTHREAD_COMPLETED));

    return static_cast<wxThread::ExitCode>(0);
}

void TATTestAutomationToolExecution::TATTestExecutionThread::Log(TATFormattedMessage message)
{
    m_pHandler->GetLogger()->Log(message);
    wxQueueEvent(m_pHandler, new wxThreadEvent(wxEVT_COMMAND_EXECUTIONTHREAD_LOG_UPDATE));
    this->Sleep(10); // To let the UI refresh
}

bool TATTestAutomationToolExecution::TATTestExecutionThread::DeletePreviousResultFiles(const wxString &strTestResultFilePath)
{
    bool bResult = false;

    std::list<wxString> filesToDelete = this->ReadTestResultFiles(strTestResultFilePath);

    for(std::list<wxString>::const_iterator iResultFile = filesToDelete.begin(); iResultFile != filesToDelete.end(); ++iResultFile)
    {
        bResult |= STATFileSystemHelper::Delete(strTestResultFilePath + *iResultFile);
    }

    return bResult;
}

void TATTestAutomationToolExecution::TATTestExecutionThread::NotifyEvent(const wxString &strMessage)
{
    wxThreadEvent* pEventData = new wxThreadEvent(wxEVT_COMMAND_EXECUTIONTHREAD_NOTIFICATION);
    pEventData->SetString(strMessage);

    // Raises the event
    wxQueueEvent(m_pHandler, pEventData);
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		EVENT HANDLERS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

void TATTestAutomationToolExecution::OnTestExecutionThreadLogUpdate(wxThreadEvent& event)
{
    m_pLogger->Flush();
}

void TATTestAutomationToolExecution::OnTestExecutionThreadCompletion(wxThreadEvent& event)
{
    m_pExecutionThread = NULL;

    // Raises the event
    wxQueueEvent(m_pTestExecutionEventListener, new wxCommandEvent(wxEVT_COMMAND_TESTEXECUTION_FINISHED));
}

void TATTestAutomationToolExecution::OnTestExecutionThreadNotification(wxThreadEvent& event)
{
    wxCommandEvent* pEventData = new wxCommandEvent(wxEVT_COMMAND_TESTEXECUTION_NOTIFICATION);
    pEventData->SetString(event.GetString());

    // Raises the event
    wxQueueEvent(m_pTestExecutionEventListener, pEventData);
}

void TATTestAutomationToolExecution::TATTestExecutionThread::ProcessOutputHandler(const wxString& strOutput)
{
    this->Log(TATFormattedMessage(strOutput, TATMessageFormat(ETATColor::E_Grey)));
}

void TATTestAutomationToolExecution::TATTestExecutionThread::ProcessCompletedHandler(const int& nResult)
{
    m_nLastProcessResult = nResult;
}

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

wxString TATTestAutomationToolExecution::GetConfigurationFilePath() const
{
    return m_strConfigurationFilePath;
}

void TATTestAutomationToolExecution::SetConfigurationFilePath(const wxString& strCompilerFilePath)
{
    m_strConfigurationFilePath = strCompilerFilePath;
}

std::map< wxString, std::map<wxString, wxString> > TATTestAutomationToolExecution::GetFlagCombinations() const
{
    return m_flagCombinations;
}

void TATTestAutomationToolExecution::SetFlagCombinations(const std::map< wxString, std::map<wxString, wxString> >& flagCombinations)
{
    m_flagCombinations = flagCombinations;
}

std::list<wxString> TATTestAutomationToolExecution::GetCompilationConfigurations() const
{
    return m_compilationConfigurations;
}

void TATTestAutomationToolExecution::SetCompilationConfigurations(const std::list<wxString>& compilationConfigurations)
{
    m_compilationConfigurations = compilationConfigurations;
}

std::map<wxString, TATCompilerInfo> TATTestAutomationToolExecution::GetCompilerInfos() const
{
    return m_compilerInfos;
}

void TATTestAutomationToolExecution::SetCompilerInfos(const std::map<wxString, TATCompilerInfo>& compilerInfos)
{
    m_compilerInfos = compilerInfos;
}

ITATLogger* TATTestAutomationToolExecution::GetLogger() const
{
    return m_pLogger;
}

void TATTestAutomationToolExecution::SetLogger(ITATLogger* pLogger)
{
    m_pLogger = pLogger;
}

void TATTestAutomationToolExecution::SetTestExecutionEventListener(wxEvtHandler* pListener)
{
    m_pTestExecutionEventListener = pListener;
}

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis
