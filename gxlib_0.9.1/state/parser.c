/* Header file include --------------------------------------------------*/
#include <memory.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <glib.h>

#include "parser.h"
#include "obj_common.h"


#define DBGOUT(x, ... ) // printf

/* Define  --------------------------------------------------------------*/
typedef enum {
	TAG_LINE,
	TAG_RECT,
	TAG_TAB,
	TAG_BUTTON,
	TAG_LIST,
	TAG_ICON,
	TAG_TEXT,
	TAG_PROGRESS,
	TAG_TOGGLE,
	TAG_UNKNOWN
} TagType;

typedef struct _obj_all {
	unsigned int id;
	Obj_area area;
	int focusable;
	unsigned int group;
	void (*draw)(struct _obj_common*);
	void (*func)(struct _obj_common*);
	void (*free)(struct _obj_common*);

	unsigned int bg_color;
	char image[64];
	char image_focus[64];

	unsigned int color_normal;
	unsigned int color_focus;
} obj_all; // using in parser only

ListHandle state_list = {NULL,};

typedef void (*obj_handler)(struct _obj_button*);
typedef void (*state_handler)(struct _state_struct*, int, int, int);

typedef struct _obj_handler_arr_type {
	char *name;
	obj_handler func;
} ObjHandlerArrType;

void dummy_handler(struct _obj_button *);
void Draw_Install_Type(struct _obj_button * dummy);
void dummy_state_handler(state_struct *state);
static const unsigned char *obj_tag_arr[] =
{
	"line",
	"rect",
	"tab",
	"button",
	"list",
	"icon",
	"text",
	"progress",
	"toggle",
	NULL
};

static const ObjHandlerArrType obj_handler_arr[] =
{
	{ "Draw_Install_Type", (obj_handler)Draw_Install_Type },
	{ "Draw_Install_Position", (obj_handler)dummy_handler },
	{ "Draw_Install_Dimension", (obj_handler)dummy_handler },
	{ "Draw_Install_Reset", (obj_handler)dummy_handler },
	{ "Click_Install_carType",(obj_handler) dummy_handler },
	{ "Click_Install_Position_Atta", (obj_handler)dummy_handler },
	{ "Click_Install_Position_Len", (obj_handler)dummy_handler },
	{ "Click_Install_Dimension_Cam", (obj_handler)dummy_handler },
	{ "Click_Install_Dimension_Vehicle", (obj_handler)dummy_handler },
	{ "Click_Install_Dimension_Blinker", (obj_handler)dummy_handler },
	{ "Click_Install_Rst_Step1", (obj_handler)dummy_handler },
	{ "Click_Install_Rst_Step2", (obj_handler)dummy_handler },
	{ "Click_Install_Rst_Popup", (obj_handler)dummy_handler },
	{ "OnClickEnterPb_parking", (obj_handler)dummy_handler },
	{ "OnClickEnterPb_event", (obj_handler)dummy_handler },
	{ "OnClickEnterPb_cctv", (obj_handler)dummy_handler },
	{ "Draw_Pb_TOP", (obj_handler)dummy_handler },
	{ "Draw_Pb_BOTTOM", (obj_handler)dummy_handler },
	{ "Draw_PlayWait", (obj_handler)dummy_handler },

	{ "OnClickEnterPbPlay_exit", (obj_handler)dummy_handler },
	{ "Draw_Pb_Playback_Prev", (obj_handler)dummy_handler },
	{ "Draw_Pb_Playback_Pause", (obj_handler)dummy_handler },
	{ "Draw_Pb_Playback_Next", (obj_handler)dummy_handler },

	{ "s_password_input_ok", (obj_handler)dummy_handler },
	{ "s_password_input_x", (obj_handler)dummy_handler },
	{ "OnClickEnterPb_download", (obj_handler)dummy_handler },
	{ NULL, NULL }
};

static const state_handler state_handler_arr[SID_MAX] =
{
	dummy_state_handler, 								// 0
};
/* Define variable  -----------------------------------------------------*/
/* Define extern variable & function  -----------------------------------*/
/* Function prototype  --------------------------------------------------*/
/* Function implementation  ---------------------------------------------*/
void dummy_handler(struct _obj_button * dummy)
{
}
void Draw_Install_Type(struct _obj_button * dummy)
{
}
void dummy_state_handler(state_struct *state)
{
}
/*******************************************************************************
*	Description		:
*	Arguments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static char* pass_white_space(char *buf)
{
	while(*buf == ' ' || *buf == '\n' || *buf == '\r' || *buf == '\t') {
		buf++;
	}
	return buf;
}
static TagType get_object_tag(const unsigned char *buf)
{
	TagType tag = TAG_LINE;

	while(obj_tag_arr[tag]) {
		if(!strcmp(buf, obj_tag_arr[tag])) {
			break;
		}
		tag++;
	}
	return tag;
}

static void assign_state_handler(state_struct *state)
{
	state->handler = state_handler_arr[state->index];
}

/*******************************************************************************
*	Description		:
*	Arguments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static obj_handler assign_object_handler(const char *func_str)
{
	int i = 0;

	while(obj_handler_arr[i].name) {
		if(!strcmp(func_str, obj_handler_arr[i].name)) {
			break;
		}
		i++;
	}
	return obj_handler_arr[i].func;
}

/*******************************************************************************
*	Description		:
*	Arguments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static char* assign_state_elem(char *buf, state_struct *state)
{
	char r, g, b;
	char *temp;
	char item[15] = {0};
	char data[100] = {0};
	char fullpath[200] = {0};
	state_struct parserState = {};
	static int scen_count=0;
	
	printf("%s(%d)\n", __func__,  scen_count++);//debug
	
	buf += strlen("<state ");

	while(*buf != '>')
	{
		memset(item, 0, sizeof(item));
		memset(data, 0, sizeof(data));
		memset(&parserState, 0, sizeof(state_struct));
		
		buf = pass_white_space(buf);

		temp = strchr(buf, '=');
		strncpy(item, buf, (unsigned int)(temp - buf));

		buf = strchr(temp, '"') + 1;
		temp = strchr(buf, '"');
		strncpy(data, buf, (unsigned int)(temp - buf));

		if(!strcmp(item, "name")) {
			goto PASS;
		}
		else if(!strcmp(item, "x")) {
			state->area.x = atoi(data);
		}
		else if(!strcmp(item, "y")) {
			state->area.y = atoi(data);
		}
		else if(!strcmp(item, "w")) {
			state->area.w = atoi(data);
		}
		else if(!strcmp(item, "h")) {
			state->area.h = atoi(data);
		}
		else if(!strcmp(item, "id")) {
			state->index = (StateID)atoi(data);
		}
		else if(!strcmp(item, "img")) {
			strcpy(state->image.image, data);
		}

PASS:
		buf = ++temp;
		buf = pass_white_space(buf);
	}

	return ++buf;
}

/*******************************************************************************
*	Description		:
*	Arguments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static char* assign_object_elem(char *buf, state_struct *state)
{
	char *temp;
	char item[20] = {0};
	char data[50] = {0};
	char fullpath[200] = {0};
	char r, g, b;
	obj_button all = {0};
	obj_button *obj;
	ListNodePtr node;
	TagType tag;
	int i, len;
	static int obj_count=0;

	

	while(strncmp(buf, "</state>", 8))
	{
		buf = pass_white_space(buf);

		buf = strchr(buf, '<') + 1;
		temp = strchr(buf, ' ');
		strncpy(item, buf, (unsigned int)(temp - buf));
		buf = temp + 1;
		tag = get_object_tag(item);

		memset(&all, 0, sizeof(obj_button));
		all.id = 0;
		all.group = 0;

		// save all elements
		while(*buf != '>')
		{
			memset(item, 0, sizeof(item));
			memset(data, 0, sizeof(data));

			temp = strchr(buf, '=');
			strncpy(item, buf, (unsigned int)(temp - buf));

			buf = strchr(temp, '"') + 1;
			temp = strchr(buf, '"');
			strncpy(data, buf, (unsigned int)(temp - buf));

			if(!strcmp(item, "x") || !strcmp(item, "x1")) {
				all.area.x = atoi(data);
			}
			else if(!strcmp(item, "y") || !strcmp(item, "y1")) {
				all.area.y = atoi(data);
			}
			else if(!strcmp(item, "w") || !strcmp(item, "x2")) {
				all.area.w = atoi(data);
			}
			else if(!strcmp(item, "h") || !strcmp(item, "y2")) {
				all.area.h = atoi(data);
			}
			else if(!strcmp(item, "id")) {
				all.id = atoi(data);
			}
			else if(!strcmp(item, "img")) {
				strcpy(all.image, data);
			}
			else if(!strcmp(item, "img_f")) {
				strcpy(all.image_focus, data);
			}
			else if(!strcmp(item, "focusable")) {
				all.focusable = (int)atoi(data);
			}
			else if(!strcmp(item, "group")) {
				all.group = strtoul(data, NULL, 10);
			}
			else if(!strcmp(item, "func")) {
				all.func = assign_object_handler(data);
			}
			buf = ++temp;
			buf = pass_white_space(buf);
		}
		buf++;
		memset(item, 0, sizeof(item));

		switch(TAG_BUTTON)
		{
			case TAG_BUTTON:
			{
				obj_button common = {0};
				memcpy(&common, &all, sizeof(obj_button));
				memcpy(&common.image, &all.image, sizeof(common.image));
				memcpy(&common.image_focus, &all.image_focus, sizeof(common.image_focus));
				common.group = all.group;

				node = ListIF.add(state->object_list, (void*)&common, sizeof(obj_button));
				buf += strlen("</button>");
				printf("add button %s(%d)\n", __func__,  obj_count++);//debug
			}
			break;
			default:
			{
				printf("not support tag\n");
			}
		}

		obj = (obj_button*)node->data;
		obj->parent = state;
		buf = pass_white_space(buf);
	}
	buf += strlen("</state>");
	return buf;
}


/*******************************************************************************
*	Description		:
*	Arguments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
int script_open_parsing(char *script_path)
{
	int size;
	ListNode *node;
	obj_common *child;
	state_struct state, *parent;
	FILE *file = NULL;
	char *buf, *buf_org;

	if(state_list) {
		DBGOUT("[script_open_parsing] already done.\n");
		return 0;
	}

	printf("%s\n", script_path);
	file = fopen(script_path, "r");
	if(!file) {
		printf("error %s\n", script_path);
		return false;
	}

	// get file size and alloc buffer
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);

	buf = (char*)malloc(size);
	memset(buf, 0, size);
	fread(buf, 1, size, file);
	fclose(file);
	buf_org = buf;

	InitListIF(&ListIF);
	if(!state_list) {
		state_list = ListIF.create(false);
	}

	while(1)
	{
		buf = strstr(buf, "<state ");
		if(buf)
		{
			memset(&state, 0, sizeof(state_struct));
			buf = assign_state_elem(buf, &state);
			node = ListIF.add(state_list, (void*)&state, sizeof(state_struct));
			parent = (state_struct *)node->data;
			parent->object_list = ListIF.create(false);
			buf = assign_object_elem(buf, parent);
		}
		else {
			break; // end of element
		}
	}

	//printf("%s\n", buf_org);
	
	if(buf_org) {
		free(buf_org);
	}
	
	printf("ok %s\n", script_path);
	return true;
}

/*******************************************************************************
*	Description		:
*	Arguments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
void script_close_parsing(void)
{
	int i;
	obj_button *obj;
	state_struct *state;
	ListNode *node_s, *node_o;

	if(state_list == NULL) {
		return;
	}

	node_s = ListIF.get_node_head(state_list);
	while(node_s)
	{
		state = (state_struct*) node_s->data;
		if(state)
		{
			node_o = ListIF.get_node_head(state->object_list);
			while(node_o)
			{
				obj = (obj_button*)node_o->data;
				if(obj && obj->free) {
					obj->free(obj);
				}
				node_o = node_o->next;
			}
			ListIF.destroy(state->object_list);
			state->object_list = NULL;
			state->free(state);
		}
		node_s = node_s->next;
	}
	ListIF.destroy(state_list);
	state_list = NULL;
}

/*******************************************************************************
*	Description		:
*	Arguments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
void script_update(void)
{
//
}

