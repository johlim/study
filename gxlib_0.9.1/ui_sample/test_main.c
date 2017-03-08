#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#include "state.h"
#include "obj_common.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main_loop=1;
void ui_scen_draw(state_struct *state, int event)
{
	int i=0,j;
	printf("\t=====(%p) (%d) ==\t",state,event);
	if(state)
	{
		scen_draw(state);
	}
	
	if (state->status)	
	{
		obj_button *obj;
	    do
	    {
		obj = ListIF.get_data_nth(state->object_list, i++);
		
		if (obj)
			button_draw(obj);	 // element
		}while(obj);
	}
	
}
void do_handle_draw(int sid, int event)
{
	printf("=====(%d) (%d) =================\n",sid,event);
	ui_run_state(sid,event);// SID, event
	ui_scen_draw(ui_get_curr_state(),event);

}

int cur_scen=0;
int cur_event=0;

int main(int argc, char *argv[]) {

	g_print("hello world\n");

	script_open_parsing("script.xml");

	// main message loop
	main_loop = 5; // test 
	do
	{
		// get event(touch, key)
		cur_event++;

		// draw scen
		switch(cur_event%4) // TODO
		{
		  case 0 : // UP slide
			// scen select
			cur_scen++;
			break;
		  case 1 : // DOWN slide
			// scen select
			cur_scen++;
			break;
		  case 2 : // LEFT slide
			// scen select
			cur_scen++;
		  	break;
		  case 3 : // RIGHT slide
			// scen select
			cur_scen--;
			break;	  	
		}
		
		do_handle_draw(cur_scen,cur_event);// SID			
	
	}while(main_loop--);
	return 0;
}
