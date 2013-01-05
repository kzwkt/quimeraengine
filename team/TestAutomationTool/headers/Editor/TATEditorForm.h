// [TERMS&CONDITIONS]

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
    /// [DOC]
    /// </summary>
    /// <param name="pParent">[DOC]</param>
    /// <returns>
    /// [DOC]
    /// </returns>
	TATEditorForm(wxWindow* pParent);


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>
	virtual ~TATEditorForm();


	// METHODS
	// ---------------
public:



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
    /// [DOC]
    /// </summary>
    /// <param name="event">[DOC]</param>
    virtual void OnConfigurationFileTextChanged( wxCommandEvent& event );

    /// <summary>
    /// [DOC]
    /// </summary>
    /// <param name="event">[DOC]</param>
	virtual void OnSaveButtonClick( wxCommandEvent& event );

    /// <summary>
    /// [DOC]
    /// </summary>
    /// <param name="event">[DOC]</param>
	virtual void OnCloseButtonClick( wxCommandEvent& event );


	// PROPERTIES
	// ---------------
public:


	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
    /// [DOC]
    /// </summary>
    bool m_bIsModified;

    /// <summary>
    /// [DOC]
    /// </summary>
    bool m_bWasModified;
};

} //namespace UI
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATEDITORFORM__
