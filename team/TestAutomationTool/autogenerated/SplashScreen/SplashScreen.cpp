///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 30 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "SplashScreen.h"

#include "../../resources/embedded/KinesisLogoTiny.bmp.h"

///////////////////////////////////////////////////////////////////////////
using namespace Kinesis::TestAutomationTool::UI;

SplashScreenBase::SplashScreenBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	m_imgLogo = new wxStaticBitmap( this, wxID_ANY, KinesisLogoTiny_bmp_to_wx_bitmap(), wxDefaultPosition, wxDefaultSize, 0 );
	mainSizer->Add( m_imgLogo, 0, wxALL, 5 );
	
	this->SetSizer( mainSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
}

SplashScreenBase::~SplashScreenBase()
{
}
