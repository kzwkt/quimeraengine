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

#ifndef __TATTESTRESULTSFORM__
#define __TATTESTRESULTSFORM__

#include <list>
#include <map>

#include "TestResults/TestResults.h"
#include "TestResults/TATTestAutomationToolResults.h"
#include "TestResults/ETATResult.h"
#include "TestResults/ETATTestResultNodeType.h"

using Kinesis::TestAutomationTool::Backend::TATTestAutomationToolResults;
using Kinesis::TestAutomationTool::Backend::ETATResult;

namespace Kinesis
{
    namespace TestAutomationTool
    {
        namespace Backend
        {
            class TATKeyValueNode;
            class TATTestResultNode;
            class TATTestResultInfo;
        }
    }
}

class wxImageList;

using Kinesis::TestAutomationTool::Backend::TATKeyValueNode;
using Kinesis::TestAutomationTool::Backend::TATTestResultNode;
using Kinesis::TestAutomationTool::Backend::TATTestResultInfo;
using Kinesis::TestAutomationTool::Backend::ETATTestResultNodeType;

namespace Kinesis
{
namespace TestAutomationTool
{
namespace UI
{

/// <summary>
/// Dialog that lets the user control the execution of the tests.
/// </summary>
class TATTestResultsForm : public TestResultsBaseForm
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
        /// Constructor that receives the test result associated to the item.
        /// </summary>
        /// <remarks>
        /// The test result will be deleted when this object is destroyed.
        /// </remarks>
        /// <param name="result">Test result information structure.</param>
        /// <param name="pNode">A node of a test result tree.</param>
        /// <param name="bIsMethod">Optional. Indicates whether the item represents a method (true) or a use case of a method (false).</param>
        TATResultTreeItemData(const TATTestResultInfo result, TATTestResultNode* pNode, const bool &bIsMethod=true);

        /// <summary>
        /// Gets the test result associated to the item.
        /// </summary>
        /// <returns>
        /// A test result information structure.
        /// </returns>
        TATTestResultInfo GetTestResult() const;

        /// <summary>
        /// Gets the test result node associated to the item.
        /// </summary>
        /// <returns>
        /// A test result node.
        /// </returns>
        TATTestResultNode* GetTestResultNode() const;

        /// <summary>
        /// Indicates whether the item represents a method (true) or a use case of a method (false).
        /// </summary>
        /// <returns>
        /// True if the item is a method, flse otherwise.
        /// </returns>
        bool IsMethod() const;

        /// <summary>
        /// The test result associated to the item.
        /// </summary>
        TATTestResultInfo m_testResult;

        /// <summary>
        /// The test result node associated to the item.
        /// </summary>
        TATTestResultNode* m_pTestResultNode;

        /// <summary>
        /// Flag that indicates whether the item represents a method (true) or a use case of a method (false).
        /// </summary>
        bool m_bIsMethod;
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
    /// <param name="strTestResultsPath">The path of the configuration file used by the SUT.</param>
	TATTestResultsForm(wxWindow* parent,
                       const wxString& strTestResultsPath,
                       const bool& bParseTestResultsAutomatically);


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>
	virtual ~TATTestResultsForm();


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Parses a test result file and shows the results as a tree.
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
    
    /// <summary>
    /// Empties the result tree and reset the internal result data.
    /// </summary>
    void ClearTestResultTree();

protected:

    /// <summary>
	/// Initializes the backend components.
	/// </summary>
    void InitializeBackend(const wxString& strTestResultsPath);
    
    /// <summary>
    /// Parses all the result files at a given directory and shows the results as a tree.
    /// </summary>
    /// <param name="strTestResultFilePath">The path to the test result files.</param>
    void ParseAllTestResultFiles(const wxString& strTestResultFilesPath);

    /// <summary>
    /// Creates the visual representation of the test result tree on a tree control.
    /// </summary>
    /// <param name="pTreeControl">The tree control that will represent the test results.</param>
    /// <param name="pResult">The test results to be painted.</param>
    virtual void BuildResultTree(wxTreeCtrl* pTreeControl, TATTestResultInfo* pResult);
    
    /// <summary>
    /// Selects the index of an image that represents the status of a test result (has errors or not).
    /// </summary>
    /// <param name="pNode">The test result node to be evaluated.</param>
    /// <returns>
    /// The index of the image in the internal image list.
    /// </returns>
    int SelectImageIndexForResult(TATTestResultNode* pNode);

    /// <summary>
    /// Shows information about a test result into a rich text control.
    /// </summary>
    /// <param name="pTreeControl">The tree control that will represent the test results.</param>
    /// <param name="itemId">The ID of the item that holds the data about the test result.</param>
    /// <param name="pInformationPanel">The control where the information will be displayed.</param>
    void ShowAdditionalInformation(wxTreeCtrl* pTreeControl, const wxTreeItemId& itemId, wxRichTextCtrl* pInformationPanel);
    
    /// <summary>
    /// Obtains the corresponding title for a test result to be displayed in the result tree.
    /// </summary>
    /// <param name="eResult">The result represented by the tree node.</param>
    /// <returns>
    /// A title for the result node.
    /// </returns>
    wxString GetLocalizedTitleForResult(const ETATResult &eResult) const;

    /// <summary>
    /// Generates a more friendly or readable name for an item. The way to transform the input name
    /// depends on the type of the test result node.
    /// </summary>
    /// <param name="strNodeName">Original name of the test result node.</param>
    /// <param name="eType">The type of the test result node.</param>
    /// <param name="bMethodOrCase">Optional. Indicates whether the item represents a method (true) or a use case of 
    /// a method (false). Should be used for test cases only.</param>
    /// <returns>
    /// The transformed name that is intended to be more friendly.
    /// </returns>
    wxString GetCleanTestNodeName(const wxString &strNodeName, const ETATTestResultNodeType &eType, const bool &bMethodOrCase=true) const;


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
    /// Event handler called when an item of the tree control is selected.
    /// </summary>
    /// <param name="event">The event argument that holds the ID of the selected item.</param>
    virtual void OnTreeItemSelected(wxTreeEvent& event);

    /// <summary>
    /// Event handler called when the Refresh button is pressed.
    /// </summary>
    /// <param name="event">The event argument. Not used.</param>  
    virtual void OnRefreshButtonClick(wxCommandEvent& event);

    /// <summary>
    /// Event handler called when a new test result files directory is selected.
    /// </summary>
    /// <param name="event">The event argument that contains the new path.</param>  
    virtual void OnTestResultsDirChanged(wxFileDirPickerEvent& event);


	// PROPERTIES
	// ---------------
public:


	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
    /// Backend objects. Manages the business logic behind the user interface.
    /// </summary>
    TATTestAutomationToolResults m_backend;

    /// <summary>
    /// A image list control to be used by the tree control.
    /// </summary>
    wxImageList* m_imgList;

    /// <summary>
    /// This flag is set when the form is created and is used to whether the test result files have
    /// to be parsed as the window is shown or will be parsed later.
    /// </summary>
    bool m_bParseTestResultsAutomatically;
};

} //namespace UI
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATTESTRESULTSFORM__
