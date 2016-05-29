/*********************************************************************
 Copyright(C) 2012 by CoreLogic, Incorporated. All Rights Reserved.
 
 File           : obj_text.h
 Date           : 2012.07.03
 Author         : djlee (dukjae.lee@bokwang.com)
 Description    : text object definition
 
----------------------------------------------------------------------
 Revision history
----------------------------------------------------------------------
 20120703       djlee       Create new file
**********************************************************************/

#ifndef __OBJ_TEXT_H__
#define __OBJ_TEXT_H__

#include "obj_common.h"

typedef struct _obj_text {
    int id;
    object_style style;
    object_status status;
    MarfRect area;
    state_struct *parent;
    void (*draw)(struct _obj_text*, bool blit);
    void (*erase)(struct _obj_text*, bool blit);
    void (*focus)(struct _obj_common*, bool enable);
    void (*select)(struct _obj_common*, bool enable);
    void (*func)(struct _obj_text*);

    unsigned short *text;
    MarfFontType font;
    unsigned int color;
    unsigned int align;
} obj_text;

void text_draw(obj_text *obj, bool blit);


#endif // __OBJ_TEXT_H__

