/***************************************************************
 * Name:      wxWidgetsApp.h
 * Purpose:   Defines Application Class
 * Author:    limjh (johlim@daum.net)
 * Created:   2015-04-16
 * Copyright: limjh (ohappylife.blogshot.com)
 * License:
 **************************************************************/

#ifndef WXWIDGETSAPP_H
#define WXWIDGETSAPP_H

#include <wx/app.h>

class wxWidgetsApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // WXWIDGETSAPP_H
