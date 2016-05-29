/*********************************************************************
  Copyright(C) 2012 by CoreLogic, Incorporated. All Rights Reserved.

File           : state.c
Date           : 2012.07.03
Author         : djlee (dukjae.lee@bokwang.com)
Description    : state definition for ui scheme

----------------------------------------------------------------------
Revision history
----------------------------------------------------------------------
20120703       djlee       Create new file
 **********************************************************************/

#include "state.h"
#include "obj_common.h"

void state_draw(state_struct *state, bool blit)
{
	int i;
	obj_common *obj;
	ListNodePtr node;

	if(state->status == S_STAT_SLEEP
	|| state->status == S_STAT_QUIT) {
		return;
	}

	if(state->image >= 0) {
		Marf_ImageDrawID(state->image, state->area.x, state->area.y);
	}
	else {
		Marf_DrawRect(state->area.x, state->area.y, state->area.w, state->area.h, state->bg_color, 0, true);
	}

	node = ListIF.get_node(state->object_list, 0);
	while(node) {
		obj = node->pData;
		if(obj->status != DISABLED && obj->draw) {
			obj->draw(obj, false);
		}
		node = node->pNext;
	}

	if(blit) {
		Marf_RefreshOSD();
	}
}

void state_draw_bg(state_struct *state, bool blit)
{
	if(state->status == S_STAT_SLEEP
	|| state->status == S_STAT_QUIT) {
		return;
	}

	if(state->image >= 0) {
		Marf_ImageDrawID(state->image, state->area.x, state->area.y);
	}
	else {
		Marf_DrawRect(state->area.x, state->area.y, state->area.w, state->area.h, state->bg_color, 0, true);
	}
	if(blit) {
		Marf_RefreshOSD();
	}
}

void state_erase(state_struct *state, bool blit)
{
	if(state->status == S_STAT_SLEEP
	|| state->status == S_STAT_QUIT) {
		return;
	}

	Marf_EraseArea(state->area.x, state->area.y, state->area.w, state->area.h);
	if(blit) {
		Marf_RefreshOSD();
	}
}

bool is_intersection(MarfRect *base, MarfRect *area)
{
	int x1, x2, x3, x4, y1, y2, y3, y4;

	x1 = area->x;
	y1 = area->y;
	x2 = area->x + area->w;
	y2 = y1;
	x3 = x1;
	y3 = area->y + area->h;
	x4 = x2;
	y4 = y3;

	if((x1 >= base->x && x1 < base->x + base->w
	&&  y1 >= base->y && y1 < base->y + base->h)
	|| (x2 >= base->x && x2 < base->x + base->w
	&&  y2 >= base->y && y2 < base->y + base->h)
	|| (x3 >= base->x && x3 < base->x + base->w
	&&  y3 >= base->y && y3 < base->y + base->h)
	|| (x4 >= base->x && x4 < base->x + base->w
	&&  y4 >= base->y && y4 < base->y + base->h))
	{
		return true;
	}
	return false;
}

