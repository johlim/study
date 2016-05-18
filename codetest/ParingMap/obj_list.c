/*********************************************************************
 Copyright(C) 2012 by CoreLogic, Incorporated. All Rights Reserved.
 
 File           : obj_list.c
 Date           : 2012.07.03
 Author         : djlee (dukjae.lee@bokwang.com)
 Description    : list object definition
 
----------------------------------------------------------------------
 Revision history
----------------------------------------------------------------------
 20120703       djlee       Create new file
**********************************************************************/

#include "obj_list.h"

void list_draw(obj_list *list, bool blit)
{
	int i;
	int item_x, item_y, item_w, item_h;
	int top_index_of_page;
	int selected, selected_prev;
	unsigned short *item, *text;
	ListNodePtr node;
	state_struct *parent = list->parent;

	if(list->list_shallow == NULL || list->item_count == 0) {
		return;
	}

	if(list->page_index > 0) {
		selected = list->selected % (list->page_index * list->item_max_in_page);
		selected_prev = list->selected_prev % (list->page_index * list->item_max_in_page);
	}
	else {
		selected = list->selected;
		selected_prev = list->selected_prev;
	}

	if(list->renew_all)
	{
		// draw all items
		list->erase(list, false);
		
		item_x = list->area.x + list->indent;
		item_y = list->area.y;
		item_w = list->area.w;
		item_h = list->item_height;

		// get top index of this (new) page
		top_index_of_page = list->page_index * list->item_max_in_page;
	
		node = ListIF.get_node(list->list_shallow, top_index_of_page);
		for(i = 0 ; i < list->item_max_in_page && node ; i++)
		{
			item = node->pData;
			text = mfStr_findRightChar((MT_CTSTR)item, (MT_TCHAR)'\\');
			text++;
			if(selected >= 0 && selected == i) 
			{
				if(list->fg > 0)
					Marf_ImageDrawID(list->fg, list->area.x, item_y);
				else
					Marf_DrawRect(list->area.x, item_y, item_w, item_h, RGB(150,150,150), 1, true);
			}
			Marf_DrawTextAlignW(item_x, item_y, item_w, item_h, text, list->font_size, RGB(255,255,255), TEXT_ALIGN_LEFT | TEXT_ALIGN_MIDDLE);
			item_y += item_h;
			node = node->pNext;
		}
	}
	else 
	{
		if(selected != selected_prev)
		{
			// renew previous selected item without bg
			if(selected_prev >= 0) {
				item_x = list->area.x + list->indent;
				item_y = list->area.y + selected_prev * list->item_height;
				item_w = list->area.w;
				item_h = list->item_height;

				item = ListIF.get_item(list->list_shallow, list->selected_prev);
				text = mfStr_findRightChar((MT_CTSTR)item, (MT_TCHAR)'\\');
				text++;

				mfGraphic_setClipRect(list->area.x, item_y, list->area.x + item_w, item_y + item_h, false);
				list->status |= INVISIBLE;
				parent->draw_bg(parent, false);
				list->status &= ~INVISIBLE;
				Marf_DrawTextAlignW(item_x, item_y, item_w, item_h, text, list->font_size, RGB(255,255,255), TEXT_ALIGN_LEFT | TEXT_ALIGN_MIDDLE);
				mfGraphic_resetClipRect();
			}

			// renew new selected item with bg
			if(selected >= 0) {
				item_x = list->area.x + list->indent;
				item_y = list->area.y + selected * list->item_height;
				item_w = list->area.w;
				item_h = list->item_height;

				item = ListIF.get_item(list->list_shallow, list->selected);
				text = mfStr_findRightChar((MT_CTSTR)item, (MT_TCHAR)'\\');
				text++;

				if(list->fg > 0)
					Marf_ImageDrawID(list->fg, list->area.x, item_y);
				else
					Marf_DrawRect(list->area.x, item_y, item_w, item_h, RGB(150,150,150), 1, true);

				Marf_DrawTextAlignW(item_x, item_y, item_w, item_h, text, list->font_size, RGB(255,255,255), TEXT_ALIGN_LEFT | TEXT_ALIGN_MIDDLE);
			}
		}
		else {
			blit = false;
		}
	}

	if(blit) {
		Marf_RefreshOSD();
	}
	list->renew_all = true;
}

void list_attach(obj_list *list, ListNodePtr source, int count)
{
	list->list_shallow = source;
	list->item_count = count;
	list->page_index = 0;
	list->selected = -1;
	list->selected_prev = -1;
	list->renew_all = true;

	list->page_count = list->item_count / list->item_max_in_page;
	if(list->item_count % list->item_max_in_page > 0) {
		list->page_count++;
	}
}

void list_set_attr(obj_list *list, int item_height, int max_in_page, int indent, int font_size)
{
	list->item_height = item_height;
	list->item_max_in_page = max_in_page;
	list->indent = indent;
	list->font_size = font_size;
}

void list_set_fg_image(obj_list *list, ImageID fg)
{
	list->fg = fg;
}

void list_select_item(obj_list *list, int index)
{
	int page_curr, page_new;

	if(index < 0 || index >= list->item_count) {
		return;
	}

	list->selected_prev = list->selected;
	list->selected = index;
	page_curr = list->page_index;
	page_new = list->selected >= 0 ? (list->selected / list->item_max_in_page) : 0;
	
	if(page_curr != page_new) {
		list->renew_all = true;
	}
	list->page_index = page_new;
}

void list_select_page(obj_list *list, int page)
{
	if(page != list->page_index && page < list->page_count) {
		list->page_index = page;
		list->selected = -1;
		list->selected_prev = -1;
		list->renew_all = true;
	}
}

int list_select_position(obj_list *list, int y)
{
	int y_pos, index;

	y_pos = y - list->area.y;
	if(y_pos < 0 || y_pos > list->area.h) { // out of range
		return -1;
	}

	index = y_pos / list->item_height;
	if(list->page_index > 0) {
		index = index + (list->page_index * list->item_max_in_page);
	}

	if(index >= list->item_count) {
		return -1;
	}
	list->selected_prev = list->selected;
	list->selected = index;
	list->renew_all = false;

	return list->selected;
}

int list_get_selected(obj_list *list)
{
	return list->selected;
}

ItemData list_get_data(obj_list *list, int index)
{
	return (ItemData)ListIF.get_item(list->list_shallow, index);
}

int list_get_page_index(obj_list *list)
{
	return list->page_index;
}

int list_get_page_count(obj_list *list)
{
	return list->page_count;
}

int list_count(obj_list *list)
{
	return list->item_count;
}

void list_detach(obj_list *list)
{
	list->list_shallow = NULL;
	list->item_count = 0;
	list->page_index = 0;
	list->page_count = 1;
	list->selected = -1;
	list->selected_prev = -1;
	list->renew_all = true;
}

