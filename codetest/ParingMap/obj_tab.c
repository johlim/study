/*********************************************************************
 Copyright(C) 2012 by CoreLogic, Incorporated. All Rights Reserved.
 
 File           : obj_tab.c
 Date           : 2012.07.18
 Author         : djlee (dukjae.lee@bokwang.com)
 Description    : tab object definition
 
----------------------------------------------------------------------
 Revision history
----------------------------------------------------------------------
 20120718       djlee       Create new file
**********************************************************************/

#include "obj_tab.h"

void tab_draw(obj_tab *obj, bool blit)
{
	bool ret, sel;
	int img;
	unsigned int bg_color, txt_color;

	if(obj->status & (FOCUS | SELECT))
	{
		img = obj->image_focus;
		txt_color = obj->color_focus;
		sel = true;
	}
	else
	{
		img = obj->image;
		txt_color = obj->color_normal;
		sel = false;
	}
	Marf_ImageDrawID(img, obj->area.x, obj->area.y);

	if(obj->text) {
		Marf_DrawTextAlignW(obj->area.x, obj->area.y, obj->area.w, obj->area.h, 
				obj->text, obj->font, txt_color, TEXT_ALIGN_CENTER | TEXT_ALIGN_MIDDLE);
	}
	if(blit) {
		Marf_RefreshOSD();
	}
}

