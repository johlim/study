#include "obj_combo.h"

void combo_draw(obj_combo *combo, bool blit)
{
	combo_item *item;

	if(combo->items == NULL) {
		return;
	}

	item = &combo->items[combo->selected];
	if(item && item->text)
	{
		Marf_DrawTextAlignW(combo->area.x, combo->area.y, combo->area.w, combo->area.h, 
							item->text, combo->font, combo->color, combo->align);
		if(blit) {
			Marf_RefreshOSD();
		}
	}
}

bool combo_attach(obj_combo *combo, combo_item *items, int count)
{
	if(combo->items) {
		mfHeap_free(combo->items);
	}
	combo->items = mfHeap_alloc(sizeof(combo_item) * count);
	if(combo->items == NULL) {
		ASAL_OS_Printf("%s() : not enough memory (%d byes)\n", sizeof(combo_item) * count);
		return false;
	}
	memcpy(combo->items, items, sizeof(combo_item) * count);
	combo->count = count;
	combo->selected = 0;

	return true;
}

void combo_detach(obj_combo *combo)
{
	if(combo->items) {
		mfHeap_free(combo->items);
	}
	combo->items = NULL;
	combo->count = 0;
	combo->selected = 0;
}

int combo_get_data_nth(obj_combo *combo, int index)
{
	combo_item *item;

	if(combo->items == NULL || index >= combo->count) {
		return -1;
	}
	item = &combo->items[index];

	return item->data;
}

combo_text combo_get_text_nth(obj_combo *combo, int index)
{
	combo_item *item;

	if(combo->items == NULL || index >= combo->count) {
		return -1;
	}
	item = &combo->items[index];

	return item->text;
}

int combo_get_data(obj_combo *combo)
{
	return combo_get_data_nth(combo, combo->selected);
}

combo_text combo_get_text(obj_combo *combo)
{
	return combo_get_text_nth(combo, combo->selected);
}

int combo_get_count(obj_combo *combo)
{
	return combo->count;
}

void combo_select_item(obj_combo *combo, int index)
{
	if(index < 0 || index >= combo->count) {
		return;
	}
	combo->selected = index;
}

int combo_get_selected(obj_combo *combo)
{
	return combo->selected;
}


