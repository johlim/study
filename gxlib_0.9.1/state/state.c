/* Header file include --------------------------------------------------*/
#include <stdbool.h>
#include <glib.h>

#include "state.h"
#include "obj_common.h"

#define RUN_STATE_ARG_MAX 1
static state_struct *curr_state = NULL;
/* Function implementation  ---------------------------------------------*/

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
void * ui_get_state(StateID sid)
{
	ListNode *node;
	state_struct *state;
	extern ListHandle state_list;
	
	node = ListIF.get_node_head(state_list);
	while(node) {
		state = (state_struct *)node->data;
		if(state) {
			if(state->index == sid) {
				return state;
			}
		}
		node = node->next;
	}
	return NULL;
}

void ui_run_state(StateID sid, ...)
{
	state_struct *new_state;

	va_list arg_list;
	long i, arg[RUN_STATE_ARG_MAX + 1] = {0};

	{
		new_state = ui_get_state(sid);
		new_state->status = S_STAT_ACTIVE;
		curr_state = new_state;

		// get argument if exist...
		// if argument is used, the last one must be NULL
		va_start(arg_list, sid);
		for(i=0 ; i<(RUN_STATE_ARG_MAX + 1/*NULL*/); i++) {
			arg[i] = va_arg(arg_list, long);
			if(arg[i] == NULL) {
				break;
			}
		}
		va_end(arg_list);
		
	}
}

state_struct* ui_get_curr_state(void)
{
	return curr_state;
}

