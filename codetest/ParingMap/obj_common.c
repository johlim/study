/*********************************************************************
 Copyright(C) 2012 by CoreLogic, Incorporated. All Rights Reserved.
 
 File           : obj_common.c
 Date           : 2012.07.03
 Author         : djlee (dukjae.lee@bokwang.com)
 Description    : definition of common ui object
 
----------------------------------------------------------------------
 Revision history
----------------------------------------------------------------------
 20120703       djlee       Create new file
**********************************************************************/

#include "obj_common.h"

void obj_draw(obj_common *obj, bool blit)
{
	if(obj->status & INVISIBLE) {
		return;
	}	
	switch(obj->style)
	{
		case BUTTON:
			button_draw(obj, blit);
			break;
		case RADIO:
			radio_draw(obj, blit);
			break;
		case TOGGLE:
			toggle_draw(obj, blit);
			break;
		case TEXT:
			text_draw(obj, blit);
			break;
		case COMBO:
			combo_draw(obj, blit);
			break;
		case PROGRESS:
			progress_draw(obj, blit);
			break;
		case LIST:
			list_draw(obj, blit);
			break;
		case ICONS:
			icon_draw(obj, blit);
			break;
	}
}

void obj_erase(obj_common *obj, bool blit)
{
	MarfRect clip;
	state_struct *parent;

	parent = obj->parent;
	clip.x = parent->area.x + obj->area.x;
	clip.y = parent->area.y + obj->area.y;
	clip.w = obj->area.w;
	clip.h = obj->area.h;
	
	mfGraphic_setClipRect(clip.x, clip.y, clip.x + clip.w, clip.y + clip.h, false);
	obj->status |= INVISIBLE;
	parent->draw_bg(parent, blit);
	obj->status &= ~INVISIBLE;
	mfGraphic_resetClipRect();
}

void obj_set_focus(obj_common *obj, bool enable)
{
	if(enable) {
		obj->status |= FOCUS;
	}
	else {
		obj->status &= ~FOCUS;
	}
}

void obj_set_select(obj_common *obj, bool enable)
{
	if(enable) {
		obj->status |= SELECT;
	}
	else {
		obj->status &= ~SELECT;
	}
}

