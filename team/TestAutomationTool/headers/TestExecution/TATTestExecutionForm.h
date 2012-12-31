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
            class TATTestResultNode;
        }
    }
}

class wxImageList;

using Kinesis::TestAutomationTool::Backend::TATKeyValueNode;
using Kinesis::TestAutomationTool::Backend::TATTestResultNode;

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
    // INTERNAL CLASSES
	// ----------------
protected:

    /// <summary>
    /// Data associated to every item in the test result tree.
    /// </summary>
    class TATResultTreeItemData : public wxTreeItemData
    {
    public:

        /// <summary>
        /// Constructor that receives the test result node associated to the item.
        /// </summary>
        /// <param name="pNode">A node of a test result tree.</param>
        TATResultTreeItemData(TATTestResultNode* pNode) : m_pTestResultNode(pNode)
        {
        }

        /// <summary>
        /// Gets the test result node associated to the item.
        /// </summary>
        /// <returns>
        /// A test result node.
        /// </returns>
        TATTestResultNode* GetTestResultNode()
        {
            return m_pTestResultNode;
        }

        /// <summary>
        /// The test result node associated to the item.
        /// </summary>
        TATTestResultNode* m_pTestResultNode;
    };


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
    /// Creates the visual representation of the test result tree on a tree control.
    /// </summary>
    /// <param name="pTreeControl">The tree control that will represent the test results.</param>
    /// <param name="pResultTree">The test results to be painted.</param>
    virtual void BuildResultTree(wxTreeCtrl* pTreeControl, TATTestResultNode* pResultTree);


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
    /// Event handler called when the backend notifies about a new available test result tree.
    /// </summary>
    /// <param name="event">The event argument that contains the new tree.</param>
    virtual void OnResultUpdate(wxCommandEvent& event);

    /// <summary>
    /// Event handler called when the backend notifies about the end of the execution process.
    /// </summary>
    /// <param name="event">The event argument.</param>
    virtual void OnTestExecutionFinished(wxCommandEvent& event);

    /// <summary>
    /// Event handler called when an item of the tree control is selected.
    /// </summary>
    /// <param name="event">The event argument that holds the ID of the selected item.</param>
    virtual void OnTreeItemSelected(wxTreeEvent& event);

    /// <summary>
    /// Selects the index of an image that represents the status of a test result (has errors or not).
    /// </summary>
    /// <param name="pNode">The test result node to be evaluated.</param>
    /// <returns>
    /// The index of the image in the internal image list.
    /// </returns>
    int SelectImageIndexForResult(TATTestResultNode* pNode);

    /// <summary>
    /// Shows a tooltip over a tree control and fills it with information about a test result.
    /// </summary>
    /// <param name="pTreeControl">The tree control where the tooltip will be placed on.</param>
    /// <param name="itemId">The ID of the item that holds the data about the test result.</param>
    void ShowToolTipWithAdditionalInfo(wxTreeCtrl* pTreeControl, const wxTreeItemId& itemId);


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

};

} //namespace UI
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATTESTEXECUTIONFORM__
