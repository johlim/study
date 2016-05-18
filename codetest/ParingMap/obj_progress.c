/*********************************************************************
 Copyright(C) 2012 by CoreLogic, Incorporated. All Rights Reserved.
 
 File           : obj_progress.c
 Date           : 2012.07.03
 Author         : djlee (dukjae.lee@bokwang.com)
 Description    : progress object definition
 
----------------------------------------------------------------------
 Revision history
----------------------------------------------------------------------
 20120703       djlee       Create new file
**********************************************************************/

#include "obj_progress.h"

#define BAR_OFFSET			22

void progress_draw(obj_progress *obj, bool blit)
{
	int i;

	if(obj->value > PROGRESS_MAX_VAL) {
		obj->value = PROGRESS_MAX_VAL;
	}

	if(obj->value == 0)
	{
		for(i = 0; i < PROGRESS_MAX_VAL; i++) {
			Marf_ImageDrawID(obj->image_bg, obj->area.x + (i * BAR_OFFSET), obj->area.y);
		}
		obj->count = 0;
	}
	else
	{
		if((obj->count + 1) < obj->value) 
		{
			// continous bar
			for(i = obj->count; i < obj->value; i++) {
				Marf_ImageDrawID(obj->image_bar, obj->area.x + (i * BAR_OFFSET), obj->area.y);
			}			
		}
		else
		{
			// single bar
			Marf_ImageDrawID(obj->image_bar, obj->area.x + ((obj->value - 1) * BAR_OFFSET), obj->area.y);
		}

		obj->count = obj->value;
	}

	if(blit) {
		Marf_RefreshOSD();
	}
}

