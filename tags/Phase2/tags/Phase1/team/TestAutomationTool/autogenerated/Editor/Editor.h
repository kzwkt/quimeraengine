///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec  2 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __EDITOR_H__
#define __EDITOR_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/string.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

namespace Kinesis
{
	namespace TestAutomationTool
	{
		namespace UI
		{
			
			///////////////////////////////////////////////////////////////////////////////
			/// Class EditorBaseForm
			///////////////////////////////////////////////////////////////////////////////
			class EditorBaseForm : public wxDialog 
			{
				private:
				
				protected:
					wxRichTextCtrl* m_rtbConfigurationFile;
					wxStaticText* m_lblReminder;
					wxStaticText* m_lblMessages;
					wxButton* m_btnSave;
					wxButton* m_btnClose;
					
					// Virtual event handlers, overide them in your derived class
					virtual void OnDialogClose( wxCloseEvent& event ) { event.Skip(); }
					virtual void OnInitDialog( wxInitDialogEvent& event ) { event.Skip(); }
					virtual void OnConfigurationFileTextChanged( wxCommandEvent& event ) { event.Skip(); }
					virtual void OnSaveButtonClick( wxCommandEvent& event ) { event.Skip(); }
					virtual void OnCloseButtonClick( wxCommandEvent& event ) { event.Skip(); }
					
				
				public:
					
					EditorBaseForm( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("EditorTitle"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 560,721 ), long style = wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxDIALOG_NO_PARENT|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU ); 
					~EditorBaseForm();
				
			};
			
		} // namespace UI
	} // namespace TestAutomationTool
} // namespace Kinesis

#endif //__EDITOR_H__
