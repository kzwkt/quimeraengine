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

#ifndef __TATEDITORFORM__
#define __TATEDITORFORM__

#include "Editor/Editor.h"


namespace Kinesis
{
namespace TestAutomationTool
{
namespace UI
{

/// <summary>
/// Dialog that lets the user edit the test configuration file.
/// </summary>
class TATEditorForm : public EditorBaseForm
{
	// CONSTRUCTORS
	// ---------------
public:

    /// <summary>
    /// Constructor that receives the parent window and the path of the test configuration file.
    /// </summary>
    /// <param name="pParent">The parent window.</param>
    /// <param name="strConfigurationFilePath">The path of the test configuration file to be edited.</param>
	TATEditorForm(wxWindow* pParent, const wxString &strConfigurationFilePath);


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>
	virtual ~TATEditorForm();


	// METHODS
	// ---------------
protected:

    /// <summary>
    /// Saves the text of the editor into the test configuration file.
    /// </summary>
    /// <param name="strFilePath">The path of the test configuration file.</param>
    /// <returns>
    /// True if the file was saved, false otherwise.
    /// </returns>
    bool SaveConfigurationFile(const wxString &strFilePath);

    /// <summary>
    /// Loads the test configuration file into the text editor.
    /// </summary>
    /// <param name="strFilePath">The file of the test configuration file.</param>
    /// <returns>
    /// True if the file was loaded, false otherwise.
    /// </returns>
    bool LoadConfigurationFile(const wxString &strFilePath);

    /// <summary>
    /// Forces the parent window, which is assumed to be a test configuration form, to reload its content
    /// due to a change of the test configuration file's contents.
    /// </summary>
    void ForceConfigurationFormToReload();


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
    /// Event handler called when the text of the editor is changed.
    /// </summary>
    /// <param name="event">The event argument. Not used.</param>
    virtual void OnConfigurationFileTextChanged( wxCommandEvent& event );

    /// <summary>
    /// Event handler called when the "Save" button is pressed.
    /// </summary>
    /// <param name="event">The event argument. Not used.</param>
	virtual void OnSaveButtonClick( wxCommandEvent& event );

    /// <summary>
    /// Event handler called when the "Close" button is pressed.
    /// </summary>
    /// <param name="event">The event argument. Not used.</param>
	virtual void OnCloseButtonClick( wxCommandEvent& event );


	// PROPERTIES
	// ---------------
public:


	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
    /// Flag that indicates whether the text of the editor has been modified or not since it 
    /// was saved or loaded.
    /// </summary>
    bool m_bIsModified;

    /// <summary>
    /// Flag that indicates whether the text of the editor has been modified or not since it
    /// was loaded.
    /// </summary>
    bool m_bWasModified;

    /// <summary>
    /// The path of the test configuration file.
    /// </summary>
    wxString m_strConfigurationFilePath;

    /// <summary>
    /// Flag that indicates whether the test configuration file has been loaded or not.
    /// </summary>
    bool m_bFileLoaded;
};

} //namespace UI
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATEDITORFORM__
