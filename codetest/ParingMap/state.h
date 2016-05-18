/*********************************************************************
 Copyright(C) 2012 by CoreLogic, Incorporated. All Rights Reserved.

 File           : state.h
 Date           : 2012.07.03
 Author         : djlee (dukjae.lee@bokwang.com)
 Description    : state definition for ui scheme

----------------------------------------------------------------------
 Revision history
----------------------------------------------------------------------
 20120703       djlee       Create new file
**********************************************************************/

#ifndef __STATE_H__
#define __STATE_H__


typedef enum {
    S_STAT_READY,
    S_STAT_ACTIVE,
    S_STAT_SLEEP,
    S_STAT_QUIT
} state_status;

typedef struct _state_struct {
    int id;
    state_status status;
    MarfRect area;
    ListNode *object_list;
    unsigned int object_count;
    int image;
    unsigned int bg_color;
    void (*draw)(struct _state_struct*, bool blit);
    void (*draw_bg)(struct _state_struct*, bool blit);
    void (*erase)(struct _state_struct*, bool blit);
    void (*handler)(struct _state_struct*, UI_Event event,
                        unsigned int arg1, unsigned int arg2, unsigned int arg3);
} state_struct;

void state_draw(state_struct *state, bool blit);
void state_draw_bg(state_struct *state, bool blit);
void state_erase(state_struct *state, bool blit);
bool is_intersection(MarfRect *base, MarfRect *area);


#endif // __STATE_H__
