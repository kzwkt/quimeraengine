// [TERMS&CONDITIONS]

#ifndef __TATTESTEXECUTIONFORM__
#define __TATTESTEXECUTIONFORM__

#include <list>
#include <map>

#include "TestExecution/TestExecution.h"
#include "TestExecution/TATTestAutomationToolExecution.h"

using Kinesis::TestAutomationTool::Backend::TATTestAutomationToolExecution;

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
	/// Constructor that receives a parent window.
	/// </summary>
    /// <param name="parent">The parent window.</param>
	TATTestExecutionForm(wxWindow* parent, 
                         TATKeyValueNode* pValueTree, 
                         std::map< wxString, std::map<wxString, wxString> > flagCombinations,
                         std::list<wxString> selectedCompilerConfigurations, 
                         std::list<wxString> selectedFlagCombinations);


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>		
	virtual ~TATTestExecutionForm();


	// METHODS
	// ---------------
public:

    /// <summary>
	/// Initializes the backend components.
	/// </summary>
    void InitializeBackend();


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
