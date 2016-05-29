/*********************************************************************
 Copyright(C) 2012 by CoreLogic, Incorporated. All Rights Reserved.
 
 File           : obj_text.c
 Date           : 2012.07.03
 Author         : djlee (dukjae.lee@bokwang.com)
 Description    : text object definition
 
----------------------------------------------------------------------
 Revision history
----------------------------------------------------------------------
 20120703       djlee       Create new file
**********************************************************************/

#include "obj_text.h"

void text_draw(obj_text *obj, bool blit)
{
	if(obj->text)
	{
		Marf_DrawTextAlignW(obj->area.x, obj->area.y, obj->area.w, obj->area.h, 
				obj->text, obj->font, obj->color, obj->align);
		if(blit) {
			Marf_RefreshOSD();
		}
	}
}

