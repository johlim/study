/* Header file include --------------------------------------------------*/
#include <stdbool.h>
#include <glib.h>
#include <glib/gprintf.h> //g_printf
#include <glib/gstdio.h> // g_remove
#include <memory.h>
#include <math.h>

#include "obj_common.h"

/* Function implementation  ---------------------------------------------*/

/*******************************************************************************
*	Description		:
*	Arguments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/

/*******************************************************************************
*	Description		:
*	Arguments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
void line_draw(obj_line *obj)
{
        if(obj->status & DISABLED
        || obj->parent->status != S_STAT_ACTIVE) {
                return;
        }
				//TODO PORTING
        //ui_draw_line(obj->start.x, obj->start.y, obj->end.x, obj->end.y, obj->color, obj->thick);
}


/*******************************************************************************
*	Description		:
*	Arguments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
void rect_draw(obj_rect *obj)
{
        if(obj->status & DISABLED
        || obj->parent->status != S_STAT_ACTIVE) {
                return;
        }
		//TODO PORTING
        //ui_draw_rect(obj->area.x, obj->area.y, obj->area.w, obj->area.h, obj->color, obj->fill, obj->thick);
        printf("%s %d %d %d %d / %d %d %d\n",__func__, obj->area.x, obj->area.y, obj->area.w, obj->area.h, obj->color, obj->fill, obj->thick);
}


/*******************************************************************************
*	Description		:
*	Arguments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
void button_draw(obj_button *obj)
{
	bool sel;
	int img_x = 0, img_y = 0;
	int text_x, text_y, text_w, text_h;
	int text_wid;	// temporary
	int text_hei;	// temporary
	unsigned int txt_color;
	unsigned short *text_ptr = NULL;


	if(obj->status & DISABLED
	|| obj->parent->status != S_STAT_ACTIVE) {
		return;
	}
	//TODO PORTING
	printf("%s %d %d %d %d / %s %s \n",__func__, obj->area.x, obj->area.y, obj->area.w, obj->area.h, obj->image, obj->image_focus);
}

void scen_draw(state_struct * state)
{
	//TODO PORTING
	printf("%s %d %d %d %d / %s %d \n",__func__, state->area.x, state->area.y, state->area.w, state->area.h, state->image.image, state->bg_color);

}

void obj_erase(obj_common *obj)
{
	//TODO PORTING
	
}
