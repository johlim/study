/***************************************************************
 * Name:      wxWidgetsMain.h
 * Purpose:   Defines Application Frame
 * Author:    limjh (johlim@daum.net)
 * Created:   2015-04-16
 * Copyright: limjh (ohappylife.blogshot.com)
 * License:
 **************************************************************/

#ifndef WXWIDGETSMAIN_H
#define WXWIDGETSMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "wxWidgetsApp.h"


#include <wx/button.h>
#include <wx/statline.h>
class wxWidgetsDialog: public wxDialog
{
    public:
        wxWidgetsDialog(wxDialog *dlg, const wxString& title);
        ~wxWidgetsDialog();

    protected:
        enum
        {
            idBtnQuit = 1000,
            idBtnAbout
        };
        wxStaticText* m_staticText1;
        wxButton* BtnAbout;
        wxStaticLine* m_staticline1;
        wxButton* BtnQuit;

    private:
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
};

#endif // WXWIDGETSMAIN_H
