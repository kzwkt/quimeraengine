///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec  2 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __TESTRESULTS_H__
#define __TESTRESULTS_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/filepicker.h>
#include <wx/treectrl.h>
#include <wx/sizer.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

namespace Kinesis
{
	namespace TestAutomationTool
	{
		namespace UI
		{
			#define ID_DIRPICKER_DIRSELECTED 1000
			#define ID_BUTTON_REFRESH 1001
			
			///////////////////////////////////////////////////////////////////////////////
			/// Class TestResultsBaseForm
			///////////////////////////////////////////////////////////////////////////////
			class TestResultsBaseForm : public wxDialog 
			{
				private:
				
				protected:
					wxStaticText* m_txtResults;
					wxDirPickerCtrl* m_dirPickerTestResults;
					wxTreeCtrl* m_treeResults;
					wxStaticText* m_txtResultInfo;
					wxRichTextCtrl* m_rtbResultInfo;
					wxButton* m_btnRefresh;
					
					// Virtual event handlers, overide them in your derived class
					virtual void OnDialogClose( wxCloseEvent& event ) { event.Skip(); }
					virtual void OnInitDialog( wxInitDialogEvent& event ) { event.Skip(); }
					virtual void OnTestResultsDirChanged( wxFileDirPickerEvent& event ) { event.Skip(); }
					virtual void OnRefreshButtonClick( wxCommandEvent& event ) { event.Skip(); }
					
				
				public:
					
					TestResultsBaseForm( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("TestResultsTitle"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 560,721 ), long style = wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxDIALOG_NO_PARENT|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU ); 
					~TestResultsBaseForm();
				
			};
			
		} // namespace UI
	} // namespace TestAutomationTool
} // namespace Kinesis

#endif //__TESTRESULTS_H__
