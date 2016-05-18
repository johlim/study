#ifndef __OBJ_RADIO_H__
#define __OBJ_RADIO_H__

#include "obj_common.h"

typedef struct _obj_radio {
	int id;
	object_style style;
	object_status status;
	MarfRect area;
	state_struct *parent;
	void (*draw)(struct _obj_radio*, bool blit);
	void (*erase)(struct _obj_radio*, bool blit);
	void (*focus)(struct _obj_common*, bool enable);
	void (*select)(struct _obj_common*, bool enable);
	void (*func)(struct _obj_radio*);

	int image;
	int image_focus;
	int image_disabled;
	unsigned int group;
} obj_radio;

void radio_draw(obj_radio *obj, bool blit);

#endif // __OBJ_RADIO_H__

