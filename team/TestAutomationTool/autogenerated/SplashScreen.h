///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 30 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __SPLASHSCREEN_H__
#define __SPLASHSCREEN_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/string.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

namespace Kinesis
{
	namespace TestAutomationTool
	{
		namespace UI
		{
			
			///////////////////////////////////////////////////////////////////////////////
			/// Class SplashScreenBase
			///////////////////////////////////////////////////////////////////////////////
			class SplashScreenBase : public wxFrame 
			{
				private:
				
				protected:
					wxStaticBitmap* m_imgLogo;
				
				public:
					
					SplashScreenBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = 0|wxTAB_TRAVERSAL );
					
					~SplashScreenBase();
				
			};
			
		} // namespace UI
	} // namespace TestAutomationTool
} // namespace Kinesis

#endif //__SPLASHSCREEN_H__
