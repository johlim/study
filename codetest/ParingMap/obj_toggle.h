/*********************************************************************
 Copyright(C) 2012 by CoreLogic, Incorporated. All Rights Reserved.
 
 File           : obj_toggle.h
 Date           : 2012.07.03
 Author         : djlee (dukjae.lee@bokwang.com)
 Description    : toggle object definition
 
----------------------------------------------------------------------
 Revision history
----------------------------------------------------------------------
 20120703       djlee       Create new file
**********************************************************************/

#ifndef __OBJ_TOGGLE_H__
#define __OBJ_TOGGLE_H__

#include "obj_common.h"

typedef struct _obj_toggle {
    int id;
    object_style style;
    object_status status;
    MarfRect area;
    state_struct *parent;
    void (*draw)(struct _obj_toggle*, bool blit);
    void (*erase)(struct _obj_toggle*, bool blit);
    void (*focus)(struct _obj_common*, bool enable);
    void (*select)(struct _obj_common*, bool enable);
    void (*func)(struct _obj_toggle*);

    int image;			// OFF
    int image_focus;	// ON
    int image_disabled;	// DISABLED

} obj_toggle;

void toggle_draw(obj_toggle *obj, bool blit);

#endif // __OBJ_TOGGLE_H__

