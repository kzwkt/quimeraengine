/***************************************************************
 * Name:      POCFormBuilderApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2012-05-09
 * Copyright:  ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "POCFormBuilderApp.h"
#include "POCFormBuilderMain.h"

IMPLEMENT_APP(POCFormBuilderApp);

bool POCFormBuilderApp::OnInit()
{
    POCFormBuilderFrame* frame = new POCFormBuilderFrame(0L);
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
    frame->Show();

    return true;
}


