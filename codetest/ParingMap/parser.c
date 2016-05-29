/*********************************************************************
  Copyright(C) 2012 by CoreLogic, Incorporated. All Rights Reserved.

File           : parser.c
Date           : 2012.07.05
Author         : djlee (dukjae.lee@bokwang.com)
Description    : do script parsing and create object

----------------------------------------------------------------------
Revision history
----------------------------------------------------------------------
20120705       djlee       Create new file
 **********************************************************************/
#include "obj_radio.h"//#include "conflict.h"
//#include "parser.h"
//#include "obj_common.h"
//#include "obj_button.h"
//#include "obj_radio.h"
//#include "obj_list.h"
//#include "obj_icon.h"
//#include "obj_text.h"
//#include "obj_combo.h"
//#include "obj_progress.h"
//#include "obj_toggle.h"
//#include "ui_text.h"



#include "script/ui_script.c"
#include "script/ui_script_tv.c"
extern const unsigned char ui_script_buf[];
extern const unsigned char ui_script_tv_buf[];

extern unsigned int g_BBDispDevice;
extern state_struct *curr_state;

typedef int (*obj_handler_type)(struct _obj_common*);
typedef int (*state_handler_type)(struct _state_struct*, UI_Event, U32, U32, U32);
typedef struct {
	unsigned char *name;
	obj_handler_type func;
} ObjHandlerArrType;

typedef enum {
	TAG_BUTTON,
	TAG_RADIO,
	TAG_TOGGLE,
	TAG_TEXT,
	TAG_COMBO,
	TAG_PROGRESS,
	TAG_LIST,
	TAG_ICON,
	TAG_UNKNOWN
} TagType;

static const unsigned char *obj_tag_strings[] =
{
	"button",
	"radio",
	"toggle",
	"text",
	"combo",
	"progress",
	"list",
	"icon",
	NULL
};

static const state_handler_type state_handlers[APP_MAX] =
{
	blackbox_handler,
	NULL,
	folder_selection_handler,
	filebrowser_handler,
	play_handler,
	setup_main_handler,
	setup_sensor_handler,
	setup_time_handler,
	setup_voice_handler,
	setup_etc_handler,
	setup_format_handler,
	setup_formatting_handler,
	setup_version_handler,
	update_confirm_handler,
	NULL,
	updating_handler,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	rear_cam_err_handler,
	sd_check_handler,
	sd_err_handler,
	gps_check_handler,
	NULL,
	NULL, //ldws_select_car_handler,
	NULL, //ldws_setup_handler,
	calibration_handler,
	boot_handler,
	mode_change_handler,
	test_menu_handler,
	test_adc_handler,
	test_lcd_handler,
	NULL,
};

static const ObjHandlerArrType obj_handlers[] =
{
	{ NULL, NULL }
};

typedef struct _obj_all {
	unsigned int id;
	object_style style;
	object_status status;
	MarfRect area;
	state_struct *parent;
	void (*draw)(struct _obj_common*, bool blit);
	void (*erase)(struct _obj_common*, bool blit);
	void (*focus)(struct _obj_common*, bool enable);
	void (*select)(struct _obj_common*, bool enable);
	int  (*func)(struct _obj_common*);

	unsigned int color;
	unsigned int thick;
	unsigned int bg_color;
	unsigned int bar_color;

	int image;
	int image_focus;
	int image_disabled;
	btn_style button_style;
	unsigned short *text;
	MarfFontType font;
	unsigned int align;
	btn_txt_pos text_pos;
	unsigned int color_normal;
	unsigned int color_focus;

	unsigned int group;

} obj_all; // using in parser only


static void ascii_to_unistr(char *astr, unsigned short *ustr)
{
	while(*astr) {
		*(ustr++) = *(astr++);
	}
}

static void unistr_copy(unsigned short *dst, unsigned short *src)
{
	while(*src) {
		*(dst++) = *(src++);
	}
}

static unsigned char* pass_white_space(unsigned char *buf)
{
	while(*buf == ' ' || *buf == '\n' || *buf == '\r' || *buf == '\t') {
		buf++;
	}
	return buf;
}

TagType get_tag(const unsigned char *buf)
{
	TagType tag = TAG_BUTTON;

	while(obj_tag_strings[tag]) {
		if(memcmp(buf, obj_tag_strings[tag], 3) == 0) {
			break;
		}
		tag++;
	}
	return tag;
}

void assign_state_handler(state_struct *state)
{
	state->handler = state_handlers[state->id];
}

obj_handler_type assign_object_handler(const unsigned char *func_str)
{
	int i = 0;
	obj_handler_type handler = NULL;

	while(obj_handlers[i].name) {
		if(!strcmp(func_str, obj_handlers[i].name)) {
			break;
		}
		i++;
	}
	return obj_handlers[i].func;
}

unsigned char* assign_state_elem(unsigned char *buf, state_struct *state, bool *child)
{
	unsigned char r, g, b;
	unsigned char *temp;
	unsigned char item[16] = {0};
	unsigned char data[64] = {0};

	buf += strlen("<state ");
	state->image = -1; // set no-image as default

	while(*buf != '>' && *buf != '/')
	{
		memset(item, 0, sizeof(item));
		memset(data, 0, sizeof(data));

		buf = pass_white_space(buf);

		temp = strchr(buf, '=');
		strncpy(item, buf, (unsigned int)(temp - buf));

		buf = strchr(temp, '\'') + 1;
		temp = strchr(buf, '\'');
		strncpy(data, buf, (unsigned int)(temp - buf));

		if(!memcmp(item, "id", 1)) {
			state->id = atoi(data);
		}
		else if(!memcmp(item, "x", 1)) {
			state->area.x = atoi(data);
		}
		else if(!memcmp(item, "y", 1)) {
			state->area.y = atoi(data);
		}
		else if(!memcmp(item, "w", 1)) {
			if(data[0] == 'F') {
				state->area.w = FB_WIDTH - state->area.x;
			}
			else {
				state->area.w = atoi(data);
			}
		}
		else if(!memcmp(item, "h", 1)) {
			if(data[0] == 'F') {
				state->area.h = FB_HEIGHT - state->area.y;
			}
			else {
				state->area.h = atoi(data);
			}
		}
		else if(!memcmp(item, "bg", 1))
		{
			if(data[0] == '#') {		// color
				state->bg_color = strtoul(&data[1], NULL, 16);
				r = RGB_RED(state->bg_color);
				g = RGB_GREEN(state->bg_color);
				b = RGB_BLUE(state->bg_color);
				state->bg_color = RGB(r, g, b);
			}
			else {	// image id
				state->image = atoi(data); // set image index (see. ui_image.h)
			}
		}
		buf = ++temp;
		buf = pass_white_space(buf);
	}

	// does this state have child object?
	*child = *buf == '/' ? false : true;

	state->draw = state_draw;
	state->draw_bg = state_draw_bg;
	state->erase = state_erase;
	assign_state_handler(state);

	return ++buf;
}

unsigned char* assign_object_elem(unsigned char *buf, state_struct *state)
{
	unsigned char *temp;
	unsigned char item[15] = {0};
	unsigned char data[50] = {0};
	unsigned char r, g, b;
	unsigned int object_count = 0;
	obj_all all = {0};
	obj_common *obj;
	TagType tag;

	while(memcmp(buf, "</s", 3) != 0)
	{
		buf = pass_white_space(buf);

		buf = strchr(buf, '<') + 1;
		temp = strchr(buf, ' ');
		strncpy(item, buf, (unsigned int)(temp - buf));
		buf = temp + 1;
		tag = get_tag(item);

		all.id = all.image = all.image_focus = -1; // set no-image as default
		all.text = 0;
		all.status = 0;
		all.align = 0;

		// save all elements
		while(*buf != '/')
		{
			memset(item, 0, sizeof(item));
			memset(data, 0, sizeof(data));

			temp = strchr(buf, '=');
			strncpy(item, buf, (unsigned int)(temp - buf));

			buf = strchr(temp, '\'') + 1;
			temp = strchr(buf, '\'');
			strncpy(data, buf, (unsigned int)(temp - buf));

			if(!memcmp(item, "x", 1)) {
				all.area.x = atoi(data);
			}
			else if(!memcmp(item, "y", 1)) {
				all.area.y = atoi(data);
			}
			else if(!memcmp(item, "w", 1)) {
				if(data[0] == 'F') {
					all.area.w = FB_WIDTH - all.area.x;
				}
				else {
					all.area.w = atoi(data);
				}
			}
			else if(!memcmp(item, "h", 1)) {
				if(data[0] == 'F') {
					all.area.h = FB_HEIGHT - all.area.y;
				}
				else {
					all.area.h = atoi(data);
				}
			}
			else if(!memcmp(item, "id", 2)) {
				all.id = atoi(data);
			}
			else if(!memcmp(item, "gr", 1)) {
				all.group = atoi(data);
			}
			else if(!memcmp(item, "img", 2))
			{
				if(item[3] == '_')
				{
					if(item[4] == 'f') {
						all.image_focus = atoi(data); // ImageID
					}
					else {
						all.image_disabled = atoi(data); // ImageID
					}
				}
				else {
					all.image = atoi(data); // ImageID
				}
			}
			else if(!memcmp(item, "text", 2)) {
				all.text = (unsigned short*)text_array[atoi(data)];
			}
			else if(!memcmp(item, "font", 2)) {
				all.font = (MarfFontType)atoi(data);
			}
			else if(!memcmp(item, "align", 2))
			{
				// horizontal
				switch(data[0])
				{
					case 'L':
						all.align |= TEXT_ALIGN_LEFT;
						break;
					case 'C':
						all.align |= TEXT_ALIGN_CENTER;
						break;
					case 'R':
						all.align |= TEXT_ALIGN_RIGHT;
						break;
				}

				// vertical
				switch(data[1])
				{
					case 'T':
						all.align |= TEXT_ALIGN_TOP;
						break;
					case 'M':
						all.align |= TEXT_ALIGN_MIDDLE;
						break;
					case 'B':
						all.align |= TEXT_ALIGN_BOTTOM;
						break;
				}
			}
			else if(!memcmp(item, "color", 2)) {
				all.color = strtoul(&data[1], NULL, 16);
				r = RGB_RED(all.bg_color);
				g = RGB_GREEN(all.bg_color);
				b = RGB_BLUE(all.bg_color);
				all.bg_color = RGB(r, g, b);
			}
			else if(!memcmp(item, "func", 2)) {
				all.func = assign_object_handler(data);
			}
			else if(!memcmp(item, "enable", 2)) {
				if(!atoi(data)) {
					all.status = DISABLED;
				}
			}
			buf = ++temp;
			buf = pass_white_space(buf);
		}
		buf += 2;

		all.style = tag;
		all.draw = obj_draw;
		all.erase = obj_erase;
		all.focus = obj_set_focus;
		all.select = obj_set_select;

		switch(tag)
		{
			case TAG_BUTTON:
				{
					obj_button button = {0};
					memcpy(&button, &all, sizeof(obj_common));
					button.button_style = all.button_style;
					button.image = all.image;
					button.image_focus = all.image_focus;
					button.image_disabled = all.image_disabled;
					button.text = all.text;
					button.font = all.font;
					button.text_pos = all.text_pos;
					button.color_normal = all.color_normal;
					button.color_focus = all.color_focus;
					obj = ListIF.add(state->object_list, (void*)&button, sizeof(obj_button));
				}
				break;
			case TAG_RADIO:
				{
					obj_radio radio = {0};
					memcpy(&radio, &all, sizeof(obj_common));
					radio.group = all.group;
					radio.image = all.image;
					radio.image_focus = all.image_focus;
					radio.image_disabled = all.image_disabled;
					obj = ListIF.add(state->object_list, (void*)&radio, sizeof(obj_radio));
				}
				break;
			case TAG_TOGGLE:
				{
					obj_toggle toggle = {0};
					memcpy(&toggle, &all, sizeof(obj_common));
					toggle.image = all.image;
					toggle.image_focus = all.image_focus;
					toggle.image_disabled = all.image_disabled;
					obj = ListIF.add(state->object_list, (void*)&toggle, sizeof(obj_toggle));
				}
				break;
			case TAG_TEXT:
				{
					obj_text text = {0};
					memcpy(&text, &all, sizeof(obj_common));
					text.text = all.text;
					text.font = all.font;
					text.color = all.color;
					text.align = all.align;
					obj = ListIF.add(state->object_list, (void*)&text, sizeof(obj_text));
				}
				break;
			case TAG_COMBO:
				{
					obj_combo combo = {0};
					memcpy(&combo, &all, sizeof(obj_common));
					combo.font = all.font;
					combo.color = all.color;
					combo.align = all.align;
					combo.attach = combo_attach;
					combo.detach = combo_detach;
					combo.get_data = combo_get_data;
					combo.get_text = combo_get_text;
					combo.get_data_nth = combo_get_data_nth;
					combo.get_text_nth = combo_get_text_nth;
					combo.get_count = combo_get_count;
					combo.select_item = combo_select_item;
					combo.get_selected = combo_get_selected;
					obj = ListIF.add(state->object_list, (void*)&combo, sizeof(obj_combo));
				}
				break;
			case TAG_PROGRESS:
				{
					obj_progress progress = {0};
					memcpy(&progress, &all, sizeof(obj_common));
					progress.image_bg = all.image;
					progress.image_bar = all.image_focus;
					progress.value = 0;
					obj = ListIF.add(state->object_list, (void*)&progress, sizeof(obj_progress));
				}
				break;
			case TAG_LIST:
				{
					obj_list list = {0};
					memcpy(&list, &all, sizeof(obj_common));
					list.attach = list_attach;
					list.set_attr = list_set_attr;
					list.set_fg_image = list_set_fg_image;
					list.select_item = list_select_item;
					list.select_page = list_select_page;
					list.select_position = list_select_position;
					list.get_selected = list_get_selected;
					list.get_data = list_get_data;
					list.get_page_index = list_get_page_index;
					list.get_page_count = list_get_page_count;
					list.count = list_count;
					list.detach = list_detach;
					obj = ListIF.add(state->object_list, (void*)&list, sizeof(obj_list));
				}
				break;
			case TAG_ICON:
				{
					obj_icon icon = {0};
					memcpy(&icon, &all, sizeof(obj_common));
					icon.image = all.image;
					obj = ListIF.add(state->object_list, (void*)&icon, sizeof(obj_icon));
				}
				break;
		}
		object_count++;
		obj->parent = state;
		buf = pass_white_space(buf);
	}
	state->object_count = object_count;
	buf += strlen("</state>");
	return buf;
}

void UI_ParsingRun(void)
{
	int index = 0, i = 0;
	unsigned char *buf;
	unsigned long time[2];
	bool has_child;
	obj_common *obj;
	state_struct state_dummy = {0};
	state_struct *state;

#if (USE_FILESYSTEM)
	CLFS_handle file;
	unsigned char *buf_org;

	if(g_BBDispDevice == DISPLAY_OUTPUT_PATH_LCD) {
		file = ClFs_fopen(UI_SCRIPT_PATH, "r");
	}
	else {
		file = ClFs_fopen(UI_SCRIPT_TV_PATH, "r");
	}
	if(file) {
		CLFS_fstat_t stat = {0};
		ClFs_hstat(file, &stat);
		buf = (unsigned char*)ASAL_OS_AllocateMem(stat.st_size);
		ClFs_fread(buf, 1, stat.st_size, file);
		buf_org = buf;
	}
#else
	if(g_BBDispDevice == DISPLAY_OUTPUT_PATH_LCD) {
		buf = ui_script_buf;
	}
	else {
		buf = ui_script_tv_buf;
	}
#endif

	Marf_InitListIF(&ListIF);
	if(state_list) {
		ListIF.destroy(state_list);
	}
	state_list = ListIF.create();

	// start time checking
	time[0] = sys_clock_gettick();

	while(1)
	{
		buf = strstr(buf, "<state ");
		if(buf)
		{
			memset(&state_dummy, 0, sizeof(state_struct));
			state = ListIF.add(state_list, (void*)&state_dummy, sizeof(state_struct));
			state->object_list = ListIF.create();
			buf = assign_state_elem(buf, state, &has_child);
			if(has_child) {
				buf = assign_object_elem(buf, state);
			}
		}
		else {
			break; // end of element
		}
	}

	// finish time checking
	time[1] = sys_clock_gettick();
	ASAL_OS_Printf("UI parsing elapsed : %d msec\n", time[1] - time[0]);

#if (USE_FILESYSTEM)
	if(buf_org) {
		ASAL_OS_FreeMem(buf_org);
	}
	ClFs_fclose(file);
#endif
}

void UI_ParsingDestroy(void)
{
	int i, state_cnt;
	state_struct *state;
	ListNodePtr node;

	if(curr_state && curr_state->handler) {
		curr_state->handler(curr_state, UI_EVENT_EXIT, 0, 0, 0);
	}

	node = ListIF.get_node(state_list, 0);
	while(node)
	{
		state = node->pData;
		ListIF.remove_all(state->object_list);
		ListIF.destroy(state->object_list);
		node = node->pNext;
	}
	ListIF.remove_all(state_list);
	ListIF.destroy(state_list);
	curr_state = state_list = NULL;
}


