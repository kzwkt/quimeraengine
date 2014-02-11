///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec  2 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "SplashScreen.h"

#include "../../resources/embedded/KinesisLogoTiny.bmp.h"
#include "../../resources/embedded/TATLogo.png.h"
#include "../../resources/embedded/TATSplashTitle.png.h"

///////////////////////////////////////////////////////////////////////////
using namespace Kinesis::TestAutomationTool::UI;

SplashScreenBase::SplashScreenBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxColour( 255, 255, 255 ) );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("v0.2"), wxDefaultPosition, wxSize( -1,40 ), 0 );
	m_staticText1->Wrap( -1 );
	bSizer3->Add( m_staticText1, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	m_bitmap3 = new wxStaticBitmap( this, wxID_ANY, TATLogo_png_to_wx_bitmap(), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_bitmap3, 0, wxALL, 5 );
	
	m_bitmap4 = new wxStaticBitmap( this, wxID_ANY, TATSplashTitle_png_to_wx_bitmap(), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_bitmap4, 0, wxALL, 5 );
	
	bSizer3->Add( bSizer2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	mainSizer->Add( bSizer3, 0, wxEXPAND|wxBOTTOM, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	m_bitmap41 = new wxStaticBitmap( this, wxID_ANY, KinesisLogoTiny_bmp_to_wx_bitmap(), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_bitmap41, 0, wxALL, 5 );
	
	m_lblLicense = new wxStaticText( this, wxID_ANY, _("\nThis tool is distributed under GPL license. It's intended to be used by Kinesis Team for product testing purposes."), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblLicense->Wrap( -1 );
	m_lblLicense->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 93, 90, false, wxEmptyString ) );
	
	bSizer4->Add( m_lblLicense, 1, wxALL|wxEXPAND, 5 );
	
	mainSizer->Add( bSizer4, 1, wxEXPAND, 5 );
	
	this->SetSizer( mainSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( SplashScreenBase::OnFrameClose ) );
}

SplashScreenBase::~SplashScreenBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( SplashScreenBase::OnFrameClose ) );
	
}
