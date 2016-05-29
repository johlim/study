/*********************************************************************
 Copyright(C) 2012 by CoreLogic, Incorporated. All Rights Reserved.

 File           : obj_common.h
 Date           : 2012.07.03
 Author         : djlee (dukjae.lee@bokwang.com)
 Description    : definition of common ui object

----------------------------------------------------------------------
 Revision history
----------------------------------------------------------------------
 20120703       djlee       Create new file
**********************************************************************/

#ifndef __OBJ_COMMON_H__
#define __OBJ_COMMON_H__


//#include "state.h"
#include "conflict.h"

#define BLACK   ((unsigned int)RGB(0,0,0))
#define WHITE   ((unsigned int)RGB(255,255,255))
#define GRAY_D  ((unsigned int)RGB(25,25,25))
#define GRAY_L  ((unsigned int)RGB(85,85,85))
#define YELLOW  ((unsigned int)RGB(255,255,0))
#define ORANGE  ((unsigned int)RGB(255,50,0))
#define BG_COLOR DEFAULT_BG_COLOR

typedef enum {
	BUTTON,
	RADIO,
	TOGGLE,
	TEXT,
	COMBO,
	PROGRESS,
	LIST,
	ICONS
} object_style;

typedef enum {
    NORMAL		= 0,
    FOCUS		= 1 << 0,
    SELECT		= 1 << 1,
    DISABLED	= 1 << 2,
    INVISIBLE	= 1 << 3,
    UNFOCUSABLE	= 1 << 4
} object_status;

typedef struct _obj_common {
    int id;
    object_style style;
    object_status status;
    MarfRect area;
    state_struct *parent;
    void (*draw)(struct _obj_common*, bool blit);
    void (*erase)(struct _obj_common*, bool blit);
    void (*focus)(struct _obj_common*, bool enable);
    void (*select)(struct _obj_common*, bool enable);
    int  (*func)(struct _obj_common*);
} obj_common;


void obj_draw(obj_common *obj, bool blit);
void obj_erase(obj_common *obj, bool blit);
void obj_set_focus(obj_common *obj, bool enable);
void obj_set_select(obj_common *obj, bool enable);

#endif // __OBJ_COMMON_H__

