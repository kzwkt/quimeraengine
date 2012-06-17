///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 30 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif //WX_PRECOMP

#include "MainDialog.h"

#include "res/KinesisLogoTiny.bmp.h"

///////////////////////////////////////////////////////////////////////////

MainDialog::MainDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 0, 2, 0, 0 );
	
	m_bitmap1 = new wxStaticBitmap( this, wxID_ANY, KinesisLogoTiny_bmp_to_wx_bitmap(), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_bitmap1, 1, wxALL, 5 );
	
	this->SetSizer( gSizer1 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainDialog::OnClose ) );
}

MainDialog::~MainDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainDialog::OnClose ) );
	
}
