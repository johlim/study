/*********************************************************************
 Copyright(C) 2012 by CoreLogic, Incorporated. All Rights Reserved.
 
 File           : obj_tab.h
 Date           : 2012.07.18
 Author         : djlee (dukjae.lee@bokwang.com)
 Description    : tab object definition
 
----------------------------------------------------------------------
 Revision history
----------------------------------------------------------------------
 20120718       djlee       Create new file
**********************************************************************/

#ifndef __OBJ_TAB_H__
#define __OBJ_TAB_H__

#include "obj_common.h"

typedef enum {
    TAB_OPEN_LEFT,
    TAB_OPEN_TOP,
    TAB_OPEN_RIGHT,
    TAB_OPEN_BOTTOM
} tab_open_side;

typedef struct _obj_tab {
    int id;
    object_style style;
    object_status status;
    MarfRect area;
    state_struct *parent;
    void (*draw)(struct _obj_tab*, bool blit);
    void (*erase)(struct _obj_tab*, bool blit);
    void (*focus)(struct _obj_common*, bool enable);
    void (*select)(struct _obj_common*, bool enable);
    void (*func)(struct _obj_tab*);

    tab_open_side open_side;
    int image;
    int image_focus;
    unsigned int bg_color_normal;
    unsigned int bg_color_focus;
    unsigned short *text;
    MarfFontType font;
    unsigned int color_normal;
    unsigned int color_focus;
} obj_tab;

void tab_draw(obj_tab *obj, bool blit);

#endif // __OBJ_TAB_H__

