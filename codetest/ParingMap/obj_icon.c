/*********************************************************************
 Copyright(C) 2012 by CoreLogic, Incorporated. All Rights Reserved.
 
 File           : obj_icon.c
 Date           : 2012.07.03
 Author         : djlee (dukjae.lee@bokwang.com)
 Description    : icon object definition
 
----------------------------------------------------------------------
 Revision history
----------------------------------------------------------------------
 20120703       djlee       Create new file
**********************************************************************/

#include "obj_icon.h"

void icon_draw(obj_icon *obj, bool blit)
{
	Marf_ImageDrawID(obj->image, obj->area.x, obj->area.y);
	if(blit) {
		Marf_RefreshOSD();
	}
}

