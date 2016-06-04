/*********************************************************************
 Copyright(C) 2012 by CoreLogic, Incorporated. All Rights Reserved.
 
 File           : obj_button.h
 Date           : 2012.07.03
 Author         : djlee (dukjae.lee@bokwang.com)
 Description    : button object definition
 
----------------------------------------------------------------------
 Revision history
----------------------------------------------------------------------
 20120703       djlee       Create new file
**********************************************************************/

#ifndef __OBJ_BUTTON_H__
#define __OBJ_BUTTON_H__

#include "obj_common.h"

typedef enum {
	BTN_STY_ICON,
	BTN_STY_STATIC
} btn_style;

typedef enum {
	BTN_TXT_POS_CENTER,
	BTN_TXT_POS_RIGHT,
	BTN_TXT_POS_BOTTOM,
	BTN_TXT_POS_CUSTOM
} btn_txt_pos;

typedef struct _obj_button {
	int id;
	object_style style;
	object_status status;
	MarfRect area;
	state_struct *parent;
	void (*draw)(struct _obj_button*, bool blit);
	void (*erase)(struct _obj_button*, bool blit);
	void (*focus)(struct _obj_common*, bool enable);
	void (*select)(struct _obj_common*, bool enable);
	void (*func)(struct _obj_button*);

	int image;
	int image_focus;
	int image_disabled;
	btn_style button_style;
	unsigned short *text;
	MarfFontType font;
	btn_txt_pos text_pos;
	MarfRect text_area;
	unsigned int color_normal;
	unsigned int color_focus;
} obj_button;

void button_draw(obj_button *obj, bool blit);

#endif // __OBJ_BUTTON_H__

