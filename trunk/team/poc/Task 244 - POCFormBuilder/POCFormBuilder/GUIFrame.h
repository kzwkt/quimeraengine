///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 30 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!

// Clases generadas por wxFormBuilder. Son dos clases, la clase de la ventana principal y la clase del diálogo.
// Este comentario se autodestruirá en el momento que modifiquéis algo con FormBuilder.

///////////////////////////////////////////////////////////////////////////

#ifndef __GUIFRAME_H__
#define __GUIFRAME_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statusbr.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/checklst.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

#define idMenuQuit 1000
#define idMenuAbout 1001

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrame
///////////////////////////////////////////////////////////////////////////////
class GUIFrame : public wxFrame
{
	private:

	protected:
		wxMenuBar* mbar;
		wxMenu* fileMenu;
		wxMenu* helpMenu;
		wxStatusBar* statusBar;
		wxStaticText* m_staticText1;
		wxTextCtrl* m_textCtrl1;
		wxButton* m_button5;
		wxButton* m_button6;

		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void DialogOpen( wxCommandEvent& event ) { event.Skip(); }
		virtual void AppExit( wxCommandEvent& event ) { event.Skip(); }


	public:

		GUIFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("wxWidgets Application Template"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 481,181 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~GUIFrame();

};

///////////////////////////////////////////////////////////////////////////////
/// Class MyDialog1
///////////////////////////////////////////////////////////////////////////////
class MyDialog1 : public wxDialog
{
	private:

	protected:
		wxCheckListBox* m_checkList2;
		wxButton* m_button7;

		// Virtual event handlers, overide them in your derived class
		virtual void DialogClose( wxCommandEvent& event ) { event.Skip(); }


	public:

		MyDialog1( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Dialogo de opciones"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 344,270 ), long style = wxDEFAULT_DIALOG_STYLE );
		~MyDialog1();

};

#endif //__GUIFRAME_H__
