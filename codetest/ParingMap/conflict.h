

#define APP_MAX 100
#define FB_HEIGHT   240;
#define FB_WIDTH    320;
#ifndef bool
typedef int    bool;
#endif

#define false   0
#define true    1

typedef unsigned int U32;
#define NULL    0


typedef int UI_Event;

//typedef enum {
//    S_STAT_READY,
//    S_STAT_ACTIVE,
//    S_STAT_SLEEP,
//    S_STAT_QUIT
//} state_status;

typedef struct _ListNode
{
    unsigned int id;
    struct _ListNode * prev;
    struct _ListNode * next;
} ListNode;

#define BLACK   ((unsigned int)RGB(0,0,0))
#define WHITE   ((unsigned int)RGB(255,255,255))
#define GRAY_D  ((unsigned int)RGB(25,25,25))
#define GRAY_L  ((unsigned int)RGB(85,85,85))
#define YELLOW  ((unsigned int)RGB(255,255,0))
#define ORANGE  ((unsigned int)RGB(255,50,0))
#define BG_COLOR DEFAULT_BG_COLOR

//typedef enum {
//    BUTTON,
//    RADIO,
//    TOGGLE,
//    TEXT,
//    COMBO,
//    PROGRESS,
//    LIST,
//    ICONS
//} object_style;

//typedef enum {
//    NORMAL      = 0,
//    FOCUS       = 1 << 0,
//    SELECT      = 1 << 1,
//    DISABLED    = 1 << 2,
//    INVISIBLE   = 1 << 3,
//    UNFOCUSABLE = 1 << 4
//} object_status;

typedef struct _drawRec
{
    //int sx,sy,ex,ey;
    int x,y,w,h;

} MarfRect;

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




	typedef btn_style;

	typedef MarfFontType;

	typedef btn_txt_pos;
extern const unsigned int text_array[];
