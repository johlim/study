/*********************************************************************
 Copyright(C) 2012 by CoreLogic, Incorporated. All Rights Reserved.
 
 File           : obj_icon.h
 Date           : 2012.07.03
 Author         : djlee (dukjae.lee@bokwang.com)
 Description    : icon object definition
 
----------------------------------------------------------------------
 Revision history
----------------------------------------------------------------------
 20120703       djlee       Create new file
**********************************************************************/

#ifndef __OBJ_ICON_H__
#define __OBJ_ICON_H__

#include "obj_common.h"

typedef struct _obj_icon {
    int id;
    object_style style;
    object_status status;
    MarfRect area;
    state_struct *parent;
    void (*draw)(struct _obj_icon*, bool blit);
    void (*erase)(struct _obj_icon*, bool blit);
    void (*focus)(struct _obj_common*, bool enable);
    void (*select)(struct _obj_common*, bool enable);
    void (*func)(struct _obj_icon*);

    int image;
} obj_icon;

void icon_draw(obj_icon *obj, bool blit);

#endif // __OBJ_ICON_H__

