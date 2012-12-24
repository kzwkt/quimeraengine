// [TERMS&CONDITIONS]

#ifndef __TATTESTEXECUTIONFORM__
#define __TATTESTEXECUTIONFORM__

#include <list>
#include <map>

#include "TestExecution/TestExecution.h"
#include "TestExecution/TATTestAutomationToolExecution.h"

using Kinesis::TestAutomationTool::Backend::TATTestAutomationToolExecution;
using Kinesis::TestAutomationTool::Backend::TATCompilerInfo;

namespace Kinesis
{
    namespace TestAutomationTool
    {
        namespace Backend
        {
            class TATKeyValueNode;
        }
    }
}

using Kinesis::TestAutomationTool::Backend::TATKeyValueNode;

namespace Kinesis
{
namespace TestAutomationTool
{
namespace UI
{

/// <summary>
/// Dialog that lets the user control the execution of the tests.
/// </summary>
class TATTestExecutionForm : public TestExecutionBaseForm
{
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

};

} //namespace UI
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATTESTEXECUTIONFORM__
