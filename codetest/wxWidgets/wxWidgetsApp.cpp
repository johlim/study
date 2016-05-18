/***************************************************************
 * Name:      wxWidgetsApp.cpp
 * Purpose:   Code for Application Class
 * Author:    limjh (johlim@daum.net)
 * Created:   2015-04-16
 * Copyright: limjh (ohappylife.blogshot.com)
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "wxWidgetsApp.h"
#include "wxWidgetsMain.h"

IMPLEMENT_APP(wxWidgetsApp);

bool wxWidgetsApp::OnInit()
{
    
    wxWidgetsDialog* dlg = new wxWidgetsDialog(0L, _("wxWidgets Application Template"));
    
    dlg->Show();
    return true;
}
