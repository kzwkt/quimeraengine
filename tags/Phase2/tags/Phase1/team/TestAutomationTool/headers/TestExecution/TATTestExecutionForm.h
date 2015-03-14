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

#ifndef __TATTESTEXECUTIONFORM__
#define __TATTESTEXECUTIONFORM__

#include <list>
#include <map>

#include "TestExecution/TestExecution.h"
#include "TestExecution/TATTestAutomationToolExecution.h"
#include "wx/treectrl.h"

using Kinesis::TestAutomationTool::Backend::TATTestAutomationToolExecution;
using Kinesis::TestAutomationTool::Backend::TATCompilerInfo;


class wxImageList;


namespace Kinesis
{
namespace TestAutomationTool
{
namespace UI
{

// Forward declaration
class TATTestResultsForm;


/// <summary>
/// Dialog that lets the user control the execution of the tests.
/// </summary>
class TATTestExecutionForm : public TestExecutionBaseForm
{
    // CONSTANTS
	// ---------------
protected:

    /// <summary>
    /// The index of the image used to represent a passed test, in the internal image list.
    /// </summary>
    static const int IMAGE_INDEX_FOR_SUCCESSFULL_TREE_ITEM;

    /// <summary>
    /// The index of the image used to represent a failed test, in the internal image list.
    /// </summary>
    static const int IMAGE_INDEX_FOR_FAILED_TREE_ITEM;

    /// <summary>
    /// An index to represent that no image is defined.
    /// </summary>
    static const int IMAGE_INDEX_FOR_UNDEFINED_TREE_ITEM;


	// CONSTRUCTORS
	// ---------------
public:

    /// <summary>
    /// Constructor that receives the parent window and some data to be processed later during the tests execution.
    /// </summary>
    /// <param name="parent">The parent window.</param>
    /// <param name="strConfigurationFilePath">The path of the configuration file used by the SUT.</param>
    /// <param name="flagCombinations">Flag combinations to apply replacements to the configuration file.</param>
    /// <param name="compilationConfigurations">Compilation configurations that will be compiled.</param>
    /// <param name="compilerInfos">Information about compilers to be used for building the SUT and the test modules.</param>
	TATTestExecutionForm(wxWindow* parent,
                         const wxString& strConfigurationFilePath,
                         const std::map< wxString, std::map<wxString, wxString> >& flagCombinations,
                         const std::list<wxString>& compilationConfigurations,
                         const std::map<wxString, TATCompilerInfo>& compilerInfos);


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>
	virtual ~TATTestExecutionForm();


	// METHODS
	// ---------------
protected:

    /// <summary>
	/// Initializes the backend components.
	/// </summary>
    void InitializeBackend(const wxString& strConfigurationFilePath,
                           const std::map< wxString, std::map<wxString, wxString> >& flagCombinations,
                           const std::list<wxString>& compilationConfigurations,
                           const std::map<wxString, TATCompilerInfo>& compilerInfos);

    /// <summary>
    /// Prepares the UI for starting the execution of the tests and instructs the backend to start the test execution process.
    /// </summary>
    void StartTestExecution();

    /// <summary>
    /// Stops the test execution as soon as possible, this means, it's not an immediate operation, the
    /// application may wait until the current pirece of work is done.
    /// </summary>
    /// <remarks>
    /// The event wxEVT_COMMAND_TESTEXECUTION_FINISHED will inform about when the process has really stopped.
    /// </remarks>
    void StopTestExecution();

    /// <summary>
    /// Shows or hides a set of buttons (Restart / Stop) depending on the status of the execution. When
    /// the execution is running, the Stop button will be shown and not the Restart button, and when the
    /// process is stopped, the opposite will occur.
    /// </summary>
    /// <param name="bExecuting">Indicates whether the execution is running (true) or not (false).</param>
    void ShowButtonsDependingOnExecutionStatus(const bool &bExecuting);

    /// <summary>
    /// Since the execution process cannot stop immediately, a message is shown inside the Stop button telling
    /// the user that the application is trying to stop. This message has to dissapear after the operation stops.
    /// </summary>
    /// <param name="bStopped">Indicates whether the operation has been stopped (true) or not (false).</param>
    void SwitchStopButtonText(const bool &bStopped);

    /// <summary>
    /// Adds a new item to the log event list.
    /// </summary>
    /// <remarks>
    /// It's expected that the messages start with "[i]" and "[E]" prefixes, which will affect to the item appearance.
    /// </remarks>
    /// <param name="strMessage">The text of the item.</param>
    void AddLogEvent(const wxString &strMessage);

    /// <summary>
    /// Enables and disables the log event list depending on whether the tests are being executed or not.
    /// The list has to be disabled during execution.
    /// </summary>
    /// <param name="bExecuting">True when the tests are being executed, false if they are not.</param>
    void EnableLogEventListDependingOnExecution(bool bExecuting);


    // EVENT HANDLERS
	// ---------------
public:

    /// <summary>
	/// Event handler called when the dialog is initialized.
	/// </summary>
    /// <param name="event">The event argument. Not used.</param>
    virtual void OnInitDialog( wxInitDialogEvent& event );

    /// <summary>
	/// Event handler called when the dialog is about to be closed.
	/// </summary>
    /// <param name="event">The event argument. Not used.</param>
    virtual void OnDialogClose( wxCloseEvent& event );

    /// <summary>
    /// Event handler called when the Stop button is pushed.
    /// </summary>
    /// <param name="event">The event argument.</param>
    virtual void OnStopButtonClick( wxCommandEvent& event );

    /// <summary>
    /// Event handler called when the Restart button is pushed.
    /// </summary>
    /// <param name="event">The event argument.</param>
	virtual void OnRestartButtonClick( wxCommandEvent& event );

    /// <summary>
    /// Event handler called when the backend notifies about the necessity of parsing new test result files.
    /// </summary>
    /// <param name="event">The event argument that contains the new tree.</param>
    virtual void OnParseTestResults(wxCommandEvent& event);

    /// <summary>
    /// Event handler called when the backend notifies about the end of the execution process.
    /// </summary>
    /// <param name="event">The event argument.</param>
    virtual void OnTestExecutionFinished(wxCommandEvent& event);

    /// <summary>
    /// Event handler called when a notification of the backend regarding the test execution "events" are received.
    /// </summary>
    /// <param name="event">The event argument that holds the message.</param>
    virtual void OnTestExecutionNotificationReceived(wxCommandEvent& event);

    /// <summary>
    /// Event handler called when an item of the log event list is selected.
    /// </summary>
    /// <param name="event">The event argument.</param>
    virtual void OnLogEventItemSelected( wxListEvent& event );


	// PROPERTIES
	// ---------------
public:


	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
    /// Backend objects. Manages the business logic behind the user interface.
    /// </summary>
    TATTestAutomationToolExecution m_backend;

    /// <summary>
    /// A image list control to be used by the tree control.
    /// </summary>
    wxImageList* m_imgList;

    /// <summary>
    /// Flag that indicates whether the execution process was stopped by the user or not.
    /// </summary>
    bool m_bStoppedByUser;

    /// <summary>
    /// The from where the test results are shown.
    /// </summary>
    TATTestResultsForm* m_pTestResultsForm;
};

} //namespace UI
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATTESTEXECUTIONFORM__
