/*********************************************************************
 Copyright(C) 2012 by CoreLogic, Incorporated. All Rights Reserved.
 
 File           : obj_toggle.c
 Date           : 2012.07.03
 Author         : djlee (dukjae.lee@bokwang.com)
 Description    : toggle object definition
 
----------------------------------------------------------------------
 Revision history
----------------------------------------------------------------------
 20120703       djlee       Create new file
**********************************************************************/

#include "obj_toggle.h"

void toggle_draw(obj_toggle *obj, bool blit)
{
	if(obj->status & SELECT) {
		Marf_ImageDrawID(obj->image_focus, obj->area.x, obj->area.y);
	}
	else if(obj->status & DISABLED) {
		Marf_ImageDrawID(obj->image_disabled, obj->area.x, obj->area.y);
	}
	else {
		Marf_ImageDrawID(obj->image, obj->area.x, obj->area.y);
	}
	if(blit) {
		Marf_RefreshOSD();
	}
}

