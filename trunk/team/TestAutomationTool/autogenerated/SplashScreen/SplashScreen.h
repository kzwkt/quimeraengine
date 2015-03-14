///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec  2 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __SPLASHSCREEN_H__
#define __SPLASHSCREEN_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/sizer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

namespace Kinesis
{
	namespace TestAutomationTool
	{
		namespace UI
		{
			#define ID_SPLASH_SCREEN_FRAME 1000
			
			///////////////////////////////////////////////////////////////////////////////
			/// Class SplashScreenBase
			///////////////////////////////////////////////////////////////////////////////
			class SplashScreenBase : public wxFrame 
			{
				private:
				
				protected:
					wxStaticText* m_staticText1;
					wxStaticBitmap* m_bitmap3;
					wxStaticBitmap* m_bitmap4;
					wxStaticBitmap* m_bitmap41;
					wxStaticText* m_lblLicense;
					
					// Virtual event handlers, overide them in your derived class
					virtual void OnFrameClose( wxCloseEvent& event ) { event.Skip(); }
					
				
				public:
					
					SplashScreenBase( wxWindow* parent, wxWindowID id = ID_SPLASH_SCREEN_FRAME, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = 0|wxTAB_TRAVERSAL );
					
					~SplashScreenBase();
				
			};
			
		} // namespace UI
	} // namespace TestAutomationTool
} // namespace Kinesis

#endif //__SPLASHSCREEN_H__
