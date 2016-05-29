#ifndef __OBJ_COMBO_H__
#define __OBJ_COMBO_H__

#include "obj_common.h"

typedef unsigned short* combo_text;

typedef struct {
	int data;
	combo_text text;
} combo_item;

typedef struct _obj_combo {
    int id;
    object_style style;
    object_status status;
    MarfRect area;
    state_struct *parent;
    void (*draw)(struct _obj_combo*, bool blit);
    void (*erase)(struct _obj_combo*, bool blit);
    void (*focus)(struct _obj_common*, bool enable);
    void (*select)(struct _obj_common*, bool enable);
    void (*func)(struct _obj_combo*);

    MarfFontType font;
    unsigned int color;
    unsigned int align;

	combo_item *items;
	int selected;
	int count;

	bool (*attach)(struct _obj_combo*, combo_item *items, int count);
	void (*detach)(struct _obj_combo*);
	int (*get_data_nth)(struct _obj_combo*, int index);
	combo_text (*get_text_nth)(struct _obj_combo*, int index);
	int (*get_data)(struct _obj_combo*);
	combo_text (*get_text)(struct _obj_combo*);
	int (*get_count)(struct _obj_combo*);
	void (*select_item)(struct _obj_combo*, int index);
	int (*get_selected)(struct _obj_combo*);
} obj_combo;

void combo_draw(obj_combo *combo, bool blit);

bool combo_attach(obj_combo *combo, combo_item *items, int count);
void combo_detach(obj_combo *combo);
int combo_get_data_nth(obj_combo *combo, int index);
combo_text combo_get_text_nth(obj_combo *combo, int index);
int combo_get_data(obj_combo *combo);
combo_text combo_get_text(obj_combo *combo);
int combo_get_count(obj_combo *combo);
void combo_select_item(obj_combo *combo, int index);
int combo_get_selected(obj_combo *combo);


#endif // __OBJ_COMBO_H__

