#ifndef __OBJ_COMMON_H__
#define __OBJ_COMMON_H__
#include "list_if.h"
#include "state.h"
/* Define  --------------------------------------------------------------*/

typedef enum {
        LINE,
        RECT,
        TAB,
        BUTTON,
        LIST,
        ICONS,
        TEXT,
        PROGRESS,
        TOGGLE
} object_style;

typedef enum {
        NORMAL = 0x00,
        FOCUS = 0x01,
        SELECT = 0x02,
        DISABLED = 0x04 // == FIXED (no focus, no selection)
} object_status;


/* Define  --------------------------------------------------------------*/

typedef struct _Obj_area
{
	unsigned int x;
	unsigned int y;
	unsigned int w;
	unsigned int h;
} Obj_area;

typedef struct _position {
        int x;
        int y;
} Position;

typedef struct _state_img
{
	char image[64];
	char image_focus[64];
}state_img;

typedef struct _state_struct
{
	StateID index; // state id (== sid), ref. script
	state_status status;
	Obj_area area;
	unsigned int bg_color;
	struct _obj_common *focus_obj; // current focus obj

	ListHandle object_list;
	unsigned int object_count;

	state_img image;
	void (*handler)(struct _state_struct*, int p1, int p2, int p3);
	void (*free)(struct _state_struct*);
}state_struct;

typedef struct _obj_common 
{
	unsigned int id;
	Obj_area area;
	int focusable;
	unsigned int group;	// group number (1, 2, 3, ...)
	void (*draw)(struct _obj_common*);
	void (*func)(struct _obj_common*);
	void (*free)(struct _obj_common*);
} obj_common;

typedef struct _obj_button {
	unsigned int id;
	Obj_area area;
	int focusable;
	unsigned int group;	// group number (1, 2, 3, ...)
	void (*draw)(struct _obj_common*);
	void (*func)(struct _obj_common*);
	void (*free)(struct _obj_common*);
	//-----------------
	object_status status;
	state_struct *parent;
	//-----------------
	char image[64];
	char image_focus[64];
	unsigned int color_normal;
	unsigned int color_focus;
} obj_button;

typedef struct _obj_line {
	unsigned int id;
	Obj_area area;
	int focusable;
	unsigned int group;	// group number (1, 2, 3, ...)
	void (*draw)(struct _obj_common*);
	void (*func)(struct _obj_common*);
	void (*free)(struct _obj_common*);
	//-----------------
	object_status status;
	state_struct *parent;
	//-----------------
	Position start;
	Position end;
	unsigned int color;
	unsigned int thick;
} obj_line;

typedef struct _obj_rect {
	unsigned int id;
	Obj_area area;
	int focusable;
	unsigned int group;	// group number (1, 2, 3, ...)
	void (*draw)(struct _obj_common*);
	void (*func)(struct _obj_common*);
	void (*free)(struct _obj_common*);
	//-----------------
	object_status status;
	state_struct *parent;
	//-----------------
	unsigned int color;
	unsigned int fill;	
	unsigned int thick;
} obj_rect;

typedef struct _ObjGroup
{
	unsigned int Obj[32];
	int	Total_Obj;
	int obj_status;		//0::show view	1::hide view
} _ObjGroup;


#endif // __OBJ_COMMON_H__
