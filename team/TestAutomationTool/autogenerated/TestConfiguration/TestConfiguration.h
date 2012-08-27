///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 30 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __TESTCONFIGURATION_H__
#define __TESTCONFIGURATION_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/checklst.h>
#include <wx/grid.h>
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
			#define ID_TEST_CONFIGURATION_DIALOG 1000
			#define ID_CHECKLIST_COMPILATION_CONFIG 1001
			#define ID_CHECKLIST_FLAG_COMBINATION 1002
			#define ID_BUTTON_EDITOR 1003
			#define ID_BUTTON_LAUNCH 1004
			
			///////////////////////////////////////////////////////////////////////////////
			/// Class TestConfigurationBaseForm
			///////////////////////////////////////////////////////////////////////////////
			class TestConfigurationBaseForm : public wxDialog 
			{
				private:
				
				protected:
					wxStaticText* m_txtSelectCompilationConfiguration;
					wxCheckListBox* m_clCompilationConfiguration;
					wxStaticText* m_txtFlagCombinationsTitle;
					wxStaticText* m_txtFlagCombinationSelectionTitle;
					wxCheckListBox* m_clFlagCombinations;
					wxStaticText* m_txtFlagValuesTitle;
					wxGrid* m_gridFlagValues;
					wxButton* m_btnEditor;
					wxButton* m_btnLaunch;
				
				public:
					
					TestConfigurationBaseForm( wxWindow* parent, wxWindowID id = ID_TEST_CONFIGURATION_DIALOG, const wxString& title = _("TestConfigurationTitle"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 546,682 ), long style = wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxDIALOG_NO_PARENT|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU ); 
					~TestConfigurationBaseForm();
				
			};
			
		} // namespace UI
	} // namespace TestAutomationTool
} // namespace Kinesis

#endif //__TESTCONFIGURATION_H__
