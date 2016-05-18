/*********************************************************************
 Copyright(C) 2012 by CoreLogic, Incorporated. All Rights Reserved.
 
 File           : obj_list.h
 Date           : 2012.07.03
 Author         : djlee (dukjae.lee@bokwang.com)
 Description    : list object definition
 
----------------------------------------------------------------------
 Revision history
----------------------------------------------------------------------
 20120703       djlee       Create new file
**********************************************************************/

#ifndef __OBJ_LIST_H__
#define __OBJ_LIST_H__

#include "obj_common.h"

typedef unsigned short* ItemData;

typedef struct _obj_list {
	int id;
	object_style style;
	object_status status;
	MarfRect area;
	state_struct *parent;
	void (*draw)(struct _obj_list*, bool blit);
	void (*erase)(struct _obj_list*, bool blit);
	void (*focus)(struct _obj_common*, bool enable);
	void (*select)(struct _obj_common*, bool enable);
	void (*func)(struct _obj_list*);

	int selected;
	int selected_prev;
	int indent;
	int font_size;
	int item_count;
	int item_max_in_page;
	int item_height;
	int page_count;
	int page_index;
	ImageID fg;
	bool renew_all;
	ListNodePtr list_shallow;

	void (*attach)(struct _obj_list*, ListNodePtr source, int count);
	void (*set_attr)(struct _obj_list*, int item_height, int max_in_page, int indent, int font_size);
	void (*set_fg_image)(struct _obj_list*, ImageID fg);
	void (*select_item)(struct _obj_list*, int index);
	void (*select_page)(struct _obj_list*, int page);
	int (*select_position)(struct _obj_list*, int y);	
	int (*get_selected)(struct _obj_list*);
	ItemData (*get_data)(struct _obj_list*, int index);
	int (*get_page_index)(struct _obj_list*);
	int (*get_page_count)(struct _obj_list*);
	int (*count)(struct _obj_list*);
	void (*detach)(struct _obj_list*);
} obj_list;

void list_draw(obj_list *list, bool blit);
void list_attach(obj_list *list, ListNodePtr source, int count);
void list_set_attr(obj_list *list, int item_height, int max_in_page, int indent, int font_size);
void list_set_fg_image(obj_list *list, ImageID fg);
void list_select_item(obj_list *list, int index);
void list_select_page(obj_list *list, int page);
int list_select_position(obj_list *list, int y);
int list_get_selected(obj_list *list);
ItemData list_get_data(obj_list *list, int index);
int list_get_page_index(obj_list *list);
int list_get_page_count(obj_list *list);
int list_count(obj_list *list);
void list_detach(obj_list *list);

#endif // __OBJ_LIST_H__

