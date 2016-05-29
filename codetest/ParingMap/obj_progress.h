/*********************************************************************
 Copyright(C) 2012 by CoreLogic, Incorporated. All Rights Reserved.
 
 File           : obj_progress.h
 Date           : 2012.07.03
 Author         : djlee (dukjae.lee@bokwang.com)
 Description    : progress object definition
 
----------------------------------------------------------------------
 Revision history
----------------------------------------------------------------------
 20120703       djlee       Create new file
**********************************************************************/

#ifndef __OBJ_PROGRESS_H__
#define __OBJ_PROGRESS_H__

#include "obj_common.h"

#define PROGRESS_MAX_VAL	15	// step

typedef struct _obj_progress {
    int id;
    object_style style;
    object_status status;
    MarfRect area;
    state_struct *parent;
    void (*draw)(struct _obj_progress*, bool blit);
    void (*erase)(struct _obj_progress*, bool blit);
    void (*focus)(struct _obj_common*, bool enable);
    void (*select)(struct _obj_common*, bool enable);
    void (*func)(struct _obj_progress*);

	int image_bg;
    int image_bar;
	unsigned int count;
    unsigned int value;

} obj_progress;

void progress_draw(obj_progress *obj, bool blit);

#endif // __OBJ_PROGRESS_H__

