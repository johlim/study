#include "obj_radio.h"

void radio_draw(obj_radio *obj, bool blit)
{
	if(obj->status & SELECT) {
		if(obj->image_focus > 0) {
			Marf_ImageDrawID(obj->image_focus, obj->area.x, obj->area.y);
		}
	}
	else if(obj->status & DISABLED) {
		if(obj->image_disabled > 0) {
			Marf_ImageDrawID(obj->image_disabled, obj->area.x, obj->area.y);
		}
	}
	else {
		if(obj->image_focus > 0) {
			Marf_ImageDrawID(obj->image, obj->area.x, obj->area.y);
		}
	}
	if(blit) {
		Marf_RefreshOSD();
	}
}

