/*********************************************************************
  Copyright(C) 2012 by CoreLogic, Incorporated. All Rights Reserved.

  File           : obj_button.c
  Date           : 2012.07.03
  Author         : djlee (dukjae.lee@bokwang.com)
  Description    : button object definition
  
  ----------------------------------------------------------------------
  Revision history
  ----------------------------------------------------------------------
  20120703       djlee       Create new file
 **********************************************************************/

#include "obj_button.h"

#define OBJ_GAP 10

void button_draw(obj_button *obj, bool blit)
{
	bool sel;
	int img_x, img_y, align;
	unsigned long text_x, text_y, text_w, text_h;
	int img;
	unsigned int txt_color;

	if(obj->status & (FOCUS | SELECT)) {
		img = obj->image_focus;
		txt_color = obj->color_focus;
		sel = true;
	}
	else {
		if(obj->status & DISABLED) {
			img = obj->image_disabled;
		}
		else {
			img = obj->image;
		}
		txt_color = obj->color_normal;
		sel = false;
	}

	if(img >= 0)
	{
		// icon style
		if(obj->text)
		{
			unsigned long text_len;
			unsigned long text_hei;
			if(obj->text_pos == BTN_TXT_POS_RIGHT)
			{
				text_len = mfGraphic_measureTextWidth(obj->text, obj->font);
				text_x = obj->area.x + obj->area.w + OBJ_GAP;
				text_y = obj->area.y;
				text_w = text_len;
				text_h = obj->area.h;
				align = TEXT_ALIGN_LEFT | TEXT_ALIGN_MIDDLE;
			}
			else if(obj->text_pos == BTN_TXT_POS_BOTTOM)
			{
				text_len = mfGraphic_measureTextWidth(obj->text, obj->font);
				text_hei = mfGraphic_measureTextHeight(obj->text, obj->font);
				if(text_len > obj->area.w) {
					text_x = obj->area.x - ((text_len - obj->area.w) / 2);
					text_w = text_len;
				}
				else {
					text_x = obj->area.x;
					text_w = obj->area.w;
				}
				text_y = obj->area.y + obj->area.h + OBJ_GAP;
				text_h = text_hei;
				align = TEXT_ALIGN_CENTER | TEXT_ALIGN_MIDDLE;
			}
			else if(obj->text_pos == BTN_TXT_POS_CENTER) 
			{
				text_x = obj->area.x;
				text_y = obj->area.y-1;
				text_w = obj->area.w;
				text_h = obj->area.h;
				align = TEXT_ALIGN_CENTER | TEXT_ALIGN_MIDDLE;
			}
			else
			{
				text_x = obj->text_area.x ;
				text_y = obj->text_area.y;
				text_w = obj->text_area.w;
				text_h = obj->text_area.h;
				align = TEXT_ALIGN_CENTER | TEXT_ALIGN_MIDDLE;
			}
		}
		img_x = obj->area.x;
		img_y = obj->area.y;
	}
	else
	{
		// box style
		if(obj->text)
		{
			text_x = obj->area.x;
			text_y = obj->area.y;
			text_w = obj->area.w;
			text_h = obj->area.h;
			align = TEXT_ALIGN_CENTER | TEXT_ALIGN_MIDDLE;
		}
		if(sel) {
			Marf_DrawRect(obj->area.x, obj->area.y, obj->area.w, obj->area.h, RGB(70,70,70), 0, true);
			txt_color = RGB(255,255,0);
		}
		else {
			Marf_DrawRect(obj->area.x, obj->area.y, obj->area.w, obj->area.h, RGB(0,0,0), 0, true);
			Marf_DrawRect(obj->area.x, obj->area.y, obj->area.w, obj->area.h, RGB(70,70,70), 1, false);
			txt_color = RGB(255,255,255);
		}
	}

	if(obj->text) {
		obj->text_area.x = text_x;
		obj->text_area.y = text_y;
		obj->text_area.w = text_w;
		obj->text_area.h = text_h;
	}
	else {
		memset(&obj->text_area, 0, sizeof(MarfRect));
	}

	if(img >= 0) {
		Marf_ImageDrawID(img, img_x, img_y);
	}
	if(obj->text) {
		Marf_DrawTextAlignW(text_x, text_y, text_w, text_h, obj->text, obj->font, txt_color, align);
	}
	if(blit) {
		Marf_RefreshOSD();
	}
}

