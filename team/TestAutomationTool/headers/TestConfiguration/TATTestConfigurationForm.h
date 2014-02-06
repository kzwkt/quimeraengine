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

#ifndef __TATTESTCONFIGURATIONFORM__
#define __TATTESTCONFIGURATIONFORM__

#include "TestConfiguration/TestConfiguration.h"
#include "TestConfiguration/TATTestAutomationToolConfiguration.h"

using Kinesis::TestAutomationTool::Backend::TATTestAutomationToolConfiguration;

namespace Kinesis
{
    namespace TestAutomationTool
    {
        namespace Backend
        {
            class TATKeyValueNode;
            class TATCompilerInfo;
        }
    }
}

using Kinesis::TestAutomationTool::Backend::TATKeyValueNode;
using Kinesis::TestAutomationTool::Backend::TATCompilerInfo;

namespace Kinesis
{
namespace TestAutomationTool
{
namespace UI
{

// Forward declarations
class TestExecutionBaseForm;
class TestResultsBaseForm;
class EditorBaseForm;

/// <summary>
/// Dialog that lets the user configure the testing process before executing it.
/// </summary>
class TATTestConfigurationForm : public TestConfigurationBaseForm
{
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	TATTestConfigurationForm();


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>
	virtual ~TATTestConfigurationForm();


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Loads the test configuration file and fills the UI.
    /// </summary>
    /// <remarks>
    /// It calls ResetConfiguration internally.
    /// </remarks>
    void LoadConfiguration();

    /// <summary>
    /// Clears the UI controls and re-initializes the backend.
    /// </summary>
    void ResetConfiguration();

protected:

    /// <summary>
	/// Shows the test execution window.
	/// </summary>
    void ShowExecutionWindow();

    /// <summary>
	/// Shows the editor window.
	/// </summary>
    void ShowEditorWindow();

    /// <summary>
	/// Shows the test results window.
	/// </summary>
    void ShowResultsWindow();

    /// <summary>
    /// Checks that there are, at least, one compilation configuration and one flag combination selected and,
    /// if so, enables the Launch button. Otherwise, it's disabled.
    /// </summary>
    void EnableLaunchButtonDependingOnSelection();

    /// <summary>
    /// Removes all the cells in a grid.
    /// </summary>
    /// <param name="pGrid">The grid to be cleared.</param>
    void ClearGrid(wxGrid* pGrid) const;
    
    /// <summary>
	/// Initializes the backend components.
	/// </summary>
    void InitializeBackend();

    /// <summary>
    /// Builds compiler information structures using the data stored in a value tree.
    /// </summary>
    /// <param name="pValueTree">The value true that provides the compiler data.</param>
    /// <param name="compilerInfos">The output list that holds the compiler information structures.</param>
    void ExtractCompilerInfosFromValueTree(TATKeyValueNode* pValueTree, std::map<wxString, TATCompilerInfo>& compilerInfos) const;

    /// <summary>
    /// Obtains a subset of a flag combination list, filtering by their name.
    /// </summary>
    /// <param name="flagsCombination">The flag combination list with the full set.</param>
    /// <param name="flagsSelection">The list of flag combination names to filter by.</param>
    /// <param name="filteredFlagCombinations">The output subset of flag combinations.</param>
    void FilterFlagCombinationListBySelection(const TATTestAutomationToolConfiguration::TFlagCombinationCollection& flagsCombination, 
                                              const std::list<wxString>& flagsSelection, 
                                              TATTestAutomationToolConfiguration::TFlagCombinationCollection& filteredFlagCombinations) const;


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
	/// Event handler called when the user checks one of the items in the compilation configuration list.
	/// </summary>
    /// <param name="event">The event argument.</param>
	virtual void OnCompilationConfigurationCheckListBoxToggled( wxCommandEvent& event );

    /// <summary>
	/// Event handler called when the user selects one of the items in the flag combination list.
	/// </summary>
    /// <param name="event">The event argument.</param>
	virtual void OnFlagCombinationsCheckListBoxSelected( wxCommandEvent& event );

    /// <summary>
	/// Event handler called when the user checks one of the items in the flag combination list.
	/// </summary>
    /// <param name="event">The event argument.</param>
	virtual void OnFlagCombinationsCheckListBoxToggled( wxCommandEvent& event );

    /// <summary>
	/// Event handler called when the user clicks on the button that navigates to the Editor.
	/// </summary>
    /// <param name="event">The event argument.</param>
	virtual void OnEditorButtonClick( wxCommandEvent& event );

    /// <summary>
	/// Event handler called when the user clicks on the button that navigates to the Test Execution dialog.
	/// </summary>
    /// <param name="event">The event argument.</param>
	virtual void OnLaunchButtonClick( wxCommandEvent& event );
    
    /// <summary>
	/// Event handler called when the user clicks on the button that navigates to the Test Results dialog.
	/// </summary>
    /// <param name="event">The event argument.</param>
	virtual void OnViewResultsButtonClick( wxCommandEvent& event );


	// PROPERTIES
	// ---------------
public:


	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
	/// Backend objects. Manages the business logic behind the user interface.
	/// </summary>	
    TATTestAutomationToolConfiguration m_backend;

    /// <summary>
	/// The form created when navigating to the test execution functional group.
	/// </summary>
    TestExecutionBaseForm* m_pExecutionForm;
    
    /// <summary>
	/// The form created when navigating to the test results functional group.
	/// </summary>
    TestResultsBaseForm* m_pTestResultsForm;

    /// <summary>
    /// The form created when navigating to the editor functional group.
    /// </summary>
    EditorBaseForm* m_pEditorForm;
};

} //namespace UI
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATTESTCONFIGURATIONFORM__
