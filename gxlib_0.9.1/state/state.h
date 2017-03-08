#ifndef __STATE_H__
#define __STATE_H__

typedef enum
{
	SID_INST_MAIN =0,
	SID_INST_TYPE,
	SID_INST_POSITION,
	SID_INST_DIMENSION,
	SID_INST_RESET,
	SID_PLAY_FB_MENU,
	SID_PLAY_FB_LIST,
	SID_PLAY_PLAYER,
	SID_PASSWORD_INPUT,
	SID_PLAY_FB_MENU_3WIFI,
	SID_PLAY_FB_MENU_4WIFI,
	SID_MAX
} StateID ;

typedef enum {
	S_STAT_READY,
	S_STAT_ACTIVE,
	S_STAT_SLEEP,
	S_STAT_QUIT
} state_status;

void * ui_get_state(StateID sid);
#endif // __STATE_H__
