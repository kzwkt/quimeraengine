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

#ifndef __TATTESTAUTOMATIONTOOLEXECUTION__
#define __TATTESTAUTOMATIONTOOLEXECUTION__

#include <map>
#include <wx/thread.h>
#include <wx/event.h>

#include "TestExecution/TATCompilerInfo.h"
#include "TestExecution/TATFormattedMessage.h"
#include "TATShellProcess.h"

// Events for multithreading tasks
wxDECLARE_EVENT(wxEVT_COMMAND_EXECUTIONTHREAD_COMPLETED, wxThreadEvent);
wxDECLARE_EVENT(wxEVT_COMMAND_EXECUTIONTHREAD_LOG_UPDATE, wxThreadEvent);
wxDECLARE_EVENT(wxEVT_COMMAND_EXECUTIONTHREAD_NOTIFICATION, wxThreadEvent);
// Events for test execution process
wxDECLARE_EVENT(wxEVT_COMMAND_TESTEXECUTION_FINISHED, wxCommandEvent);
wxDECLARE_EVENT(wxEVT_COMMAND_TESTEXECUTION_PARSE_TESTRESULTS, wxCommandEvent);
wxDECLARE_EVENT(wxEVT_COMMAND_TESTEXECUTION_NOTIFICATION, wxCommandEvent);


namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

class ITATLogger;

/// <summary>
/// Manages the business logic of a functional sector of the application in a UI-independent way.
/// Provides functionality related to the execution of the tests.
/// </summary>
class TATTestAutomationToolExecution : public wxEvtHandler
{
    // INTERNAL CLASSES
    // ----------------
protected:

    /// <summary>
    /// Encapsulates a thread that will execute the tests and which is able to listen to process events.
    /// It's intended for internal use only in order to not hang up the UI layer.
    /// </summary>
    class TATTestExecutionThread : public wxThread, public TATShellProcess::ITATShellProcessListener
    {
    public:

        /// <summary>
        /// Constructor that receives a pointer to the component that handles the thread. 
        /// </summary>
        /// <param name="pHandler">The handler of the thread.</param>
        TATTestExecutionThread(TATTestAutomationToolExecution* pHandler);

        /// <summary>
        /// Default destructor.
        /// </summary>
        ~TATTestExecutionThread();

        //! @copydoc TATShellProcess::ITATShellProcessListener::ProcessCompletedHandler()
        virtual void ProcessCompletedHandler(const int &nResult);

        //! @copydoc TATShellProcess::ITATShellProcessListener::ProcessOutputHandler()
        virtual void ProcessOutputHandler(const wxString &strOutput);

    protected:

        //! @copydoc wxThread::Entry()
        virtual ExitCode Entry();

        /// <summary>
        /// Creates a back-up copy of the configuration file of the SUT.
        /// </summary>
        /// <param name="strConfigurationFilePath">The path to the configuration file.</param>
        /// <returns>
        /// True when the file was created, false otherwise.
        /// </returns>
        bool CreateConfigurationFileBackup(const wxString& strConfigurationFilePath) const;

        /// <summary>
        /// Overwrites the current configuration file of the SUT with the previously created back-up copy. The copy is then removed.
        /// </summary>
        /// <param name="strConfigurationFilePath">The path to the configuration file.</param>
        /// <returns>
        /// True when the file was restored, false otherwise.
        /// </returns>
        bool RestoreConfigurationFileBackup(const wxString& strConfigurationFilePath) const;

        /// <summary>
        /// Replaces the value of every flag in the configuration file of the SUT with the given value for each flag.
        /// </summary>
        /// <param name="strConfigurationFilePath">The path to the configuration file.</param>
        /// <param name="replacements">A list of pairs compound of the flag's name and its new value.</param>
        /// <returns>
        /// True if all the values were replaced, false otherwise.
        /// </returns>
        bool ReplaceFlagValuesInConfigurationFile(const wxString& strConfigurationFilePath, const std::map<wxString, wxString>& replacements) const;

        /// <summary>
        /// Replaces the value of every flag in a string with the given value for each flag.
        /// </summary>
        /// <param name="strSource">The source string.</param>
        /// <param name="replacements">A list of pairs compound of the flag's name and its new value.</param>
        /// <returns>
        /// A copy of the source string with all the replacements applied.
        /// </returns>
        wxString ReplaceFlagValues(const wxString& strSource, const std::map<wxString, wxString>& replacements) const;

        /// <summary>
        /// Executes a compiler using a specific command and a list of parameters.
        /// </summary>
        /// <remarks>
        /// The strings are concatenated following the pattern: "strProjectFilePath"+ +strCommandstr+Configuration+ +strParams.
        /// Note that the command and the configuration are not separated.
        /// </remarks>
        /// <param name="strCompilerPath">The path to the physical compiler file.</param>
        /// <param name="strCommand">A command the compiler expects.</param>
        /// <param name="strConfiguration">The compilation configuration.</param>
        /// <param name="strProjectFilePath">Optional. The project file to operate with.</param>
        /// <param name="strParams">Optional. A list of parameters expected by the compiler for the given command.</param>
        /// <param name="strParams">Optional. The token used by the compiler to specify the project file path.</param>
        /// <returns>
        /// True if the command was executed successfully, false otherwise.
        /// </returns>
        bool ExecuteCompilerCommand(const wxString& strCompilerPath, const wxString& strCommand, const wxString& strConfiguration,
                                    const wxString& strProjectFilePath=wxT(""), const wxString& strParams=wxT(""),
                                    const wxString& strFileSpecifier=wxT(""));

        /// <summary>
        /// Executes a test module.
        /// </summary>
        /// <param name="strTestModulePath">The path to the executable file.</param>
        /// <returns>
        /// True if the execution was successfull, false otherwise.
        /// </returns>
        bool ExecuteTestModule(const wxString& strTestModulePath);

        /// <summary>
        /// Makes a list of all the test module files inside a given directory.
        /// </summary>
        /// <param name="strFolderPath">The path to the folder to search in.</param>
        /// <returns>
        /// A list of the paths to every test module.
        /// </returns>
        std::list<wxString> ReadTestModuleFiles(const wxString& strFolderPath) const;
        
        /// <summary>
        /// Makes a list of all the test result files inside a given directory.
        /// </summary>
        /// <param name="strFolderPath">The path to the folder to search in.</param>
        /// <returns>
        /// A list of the paths to every test result file.
        /// </returns>
        std::list<wxString> ReadTestResultFiles(const wxString& strFolderPath) const;

        /// <summary>
        /// Sends a message to be written by the logger.
        /// </summary>
        /// <remarks>
        /// There are no guarantees that the message is written immediately.
        /// </remarks>
        /// <param name="message">The message to send.</param>
        void Log(TATFormattedMessage message);

        /// <summary>
        /// Deletes the test result files allocated into a given folder.
        /// </summary>
        /// <param name="strTestResultFilePath">The path to the test result files.</param>
        /// <returns>
        /// True if the files were deleted, false otherwise.
        /// </returns>
        bool DeletePreviousResultFiles(const wxString &strTestResultFilePath);

        /// <summary>
        /// Sends a notification regarding test process events.
        /// </summary>
        /// <param name="strMessage">Notification message.</param>
        void NotifyEvent(const wxString &strMessage);

    protected:

        /// <summary>
        /// The handler of the thread.
        /// </summary>
        TATTestAutomationToolExecution* m_pHandler;

        /// <summary>
        /// The last exit code an executed process returned.
        /// </summary>
        int m_nLastProcessResult;
    };


    // TYPEDEFS
    // ---------------
protected:

    typedef std::map< wxString, std::map<wxString, wxString> > TFlagCombinationCollection;
    typedef std::map< wxString, wxString > TFlagCombinationValues;


    // CONSTANTS
    // ---------------
protected:

    /// <summary>
    /// The suffix to append to the back-up copy of the configuration file.
    /// </summary>
    static const wxString BACKUP_SUFFIX;


	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	TATTestAutomationToolExecution();


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>
	virtual ~TATTestAutomationToolExecution();


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Releases all the resources.
    /// </summary>
    void Destroy();

    /// <summary>
    /// Starts the execution of the tests in a separated thread.
    /// </summary>
    void ExecuteTests();

    /// <summary>
    /// Stops the execution of the tests as soon as possible.
    /// </summary>
    /// <remarks>
    /// It depends on how often the execution thread checks for destruction requests.
    /// </remarks>
    void StopTestExecution();

    /// <summary>
    /// Raises an event to notify that new test result files have to be parsed.
    /// </summary>
    /// <param name="strTestResultFilePath">The path to the test result files.</param>
    /// <param name="strCompilationConfig">The name of the compilation configuration.</param>
    /// <param name="strCompilerName">The name of the compiler.</param>
    /// <param name="strFlagCombinationName">The flag combination name.</param>
    /// <param name="strFlagCombinationValues">The values of the flag combination.</param>
    void ParseTestResultFile(const wxString& strTestResultFilePath, 
                             const wxString& strCompilationConfig,
                             const wxString& strCompilerName,
                             const wxString& strFlagCombinationName,
                             const wxString& strFlagCombinationValues);

    // EVENT HANDLERS
    // ---------------
public:

    /// <summary>
    /// Event handler for catching thread update signals when the log can be updated.
    /// </summary>
    /// <param name="wxThreadEvent">The event arguments.</param>
    virtual void OnTestExecutionThreadLogUpdate( wxThreadEvent& event );

    /// <summary>
    /// Event handler for catching the thread completed signal.
    /// </summary>
    /// <param name="wxThreadEvent">The event arguments.</param>
    virtual void OnTestExecutionThreadCompletion( wxThreadEvent& event );

    /// <summary>
    /// Event handler for catching notification messages.
    /// </summary>
    /// <param name="event">The event argument that holds the notification message.</param>
    virtual void OnTestExecutionThreadNotification( wxThreadEvent& event );


	// PROPERTIES
	// ---------------
public:

    /// <summary>
    /// Gets the path to the configuration file of the SUT.
    /// </summary>
    /// <returns>
    /// The path to the configuration file of the SUT.
    /// </returns>
    wxString GetConfigurationFilePath() const;

    /// <summary>
    /// Sets the path to the configuration file of the SUT.
    /// </summary>
    /// <param name="strCompilerFilePath">The path to the configuration file of the SUT.</param>
    void SetConfigurationFilePath(const wxString& strCompilerFilePath);

    /// <summary>
    /// Gets the list of flag combinations to be used in the test execution process.
    /// </summary>
    /// <returns>
    /// A list of flag combinations
    /// </returns>
    std::map< wxString, std::map<wxString, wxString> > GetFlagCombinations() const;

    /// <summary>
    /// Sets the list of flag combinations to be used in the test execution process.
    /// </summary>
    /// <param name="flagCombinations">A list of flag combinations</param>
    void SetFlagCombinations(const std::map< wxString, std::map<wxString, wxString> >& flagCombinations);

    /// <summary>
    /// Gets the information about the compilers to be used during the test execution process.
    /// </summary>
    /// <returns>
    /// A list of compiler information structures.
    /// </returns>
    std::map<wxString, TATCompilerInfo> GetCompilerInfos() const;

    /// <summary>
    /// Sets the information about the compilers to be used during the test execution process.
    /// </summary>
    /// <param name="compilerInfos">A list of compiler information structures.</param>
    void SetCompilerInfos(const std::map<wxString, TATCompilerInfo>& compilerInfos);

    /// <summary>
    /// Gets the compilation configurations to be considered during the test execution process.
    /// </summary>
    /// <returns>
    /// A list with the name of the compilation configurations.
    /// </returns>
    std::list<wxString> GetCompilationConfigurations() const;

    /// <summary>
    /// Sets the compilation configurations to be considered during the test execution process.
    /// </summary>
    /// <param name="compilationConfigurations">A list with the name of the compilation configurations.</param>
    void SetCompilationConfigurations(const std::list<wxString>& compilationConfigurations);

    /// <summary>
    /// Gets the logger that will receive the traces during the test execution process.
    /// </summary>
    /// <returns>
    /// A logger to send messages to.
    /// </returns>
    ITATLogger* GetLogger() const;

    /// <summary>
    /// Sets the logger that will receive the traces during the test execution process.
    /// </summary>
    /// <param name="pLogger">A logger to send messages to.</param>
    void SetLogger(ITATLogger* pLogger);
    
    /// <summary>
    /// Sets the component that will react to some events.
    /// </summary>
    /// <param name="pListener">A component that will react to some events.</param>
    void SetTestExecutionEventListener(wxEvtHandler* pListener);


	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
    /// The path to the configuration file of the SUT.
    /// </summary>
    wxString m_strConfigurationFilePath;

    /// <summary>
    /// The list of flag combinations to be used in the test execution process.
    /// </summary>
    std::map< wxString, std::map<wxString, wxString> > m_flagCombinations;

    /// <summary>
    /// The compilation configurations to be considered during the test execution process.
    /// </summary>
    std::list<wxString> m_compilationConfigurations;

    /// <summary>
    /// The information about the compilers to be used during the test execution process.
    /// </summary>
    std::map<wxString, TATCompilerInfo> m_compilerInfos;

	/// <summary>
    /// The logger that will receive the traces during the test execution process.
    /// </summary>
	ITATLogger* m_pLogger;

    /// <summary>
    /// The thread which will execute the tests.
    /// </summary>
    TATTestExecutionThread* m_pExecutionThread;

    /// <summary>
    /// A component that will react to some events.
    /// </summary>
    wxEvtHandler* m_pTestExecutionEventListener;

};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATTESTAUTOMATIONTOOLEXECUTION__
