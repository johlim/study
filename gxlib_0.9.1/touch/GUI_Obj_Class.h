#ifndef __GUI_OBJ_CLASS_H__
#define __GUI_OBJ_CLASS_H__


#pragma pack(1)
///////////////////////////////////////////////////////////////////////
// define
///////////////////////////////////////////////////////////////////////
#define GUI_OBJ_ID_MAX  (1024)
#define GUI_ROOT_ID     (0)

#define ROOT_NUM_MAX    (2) //for triple buffering
#define GUI_ROOT1_ID    GUI_OBJ_ID_MAX
#define GUI_ROOT2_ID    GUI_OBJ_ID_MAX+1

#define SCREEN_WIDTH    320
#define SCREEN_HEIGHT   240

#define OBJ_WIDTH_CENTER  (-1)
#define OBJ_HEIGHT_CENTER (-1)
#define OBJ_WIDTH         (-2)
#define OBJ_HEIGHT        (-2)

enum _OBJ_TYPE
{
    OBJ_TYPE_NULL = 0,
    OBJ_TYPE_ROOT,
    OBJ_TYPE_BITMAP,
    OBJ_TYPE_BUTTON,
    OBJ_TYPE_CHECKBOX,
    OBJ_TYPE_COMBOBOX,
    OBJ_TYPE_TEXT,
    OBJ_TYPE_MAX
};

typedef int GUI_OBJ_ID;

typedef void(*GUI_CALLBACK_FUNC)(int *);

typedef struct _GUI_OBJ
{
    GUI_OBJ_ID  pId;    // paranet object id

    int     type;       // root1, root2, bitmap, button, check box, combo box, list box, text
    int     value;      // value for each type

    int     x;          // x coordinate on parent object
    int     y;          // y coordinate on parent object
    int     width;      // width
    int     height;     // height

    char    **mem;      // memory coordinate : mem(height, width)
    int     mem_size;   // memory size (width * height * fb->bits_per_pixel/8)
    int     line_length;// bytes per line (width * fb->bits_per_pixel/8)

    int     isVisable;  // visable default : 1
    int     isDisabled; // disable default : 0

    char    **objId_mem;// object id on root : objId_mem(height, width) = obj_id

    GUI_CALLBACK_FUNC   callbackFunc_TouchMove;         // touch move callback
    GUI_CALLBACK_FUNC   callbackFunc_TouchDown;         // touch down callback
    GUI_CALLBACK_FUNC   callbackFunc_TouchUp;           // touch up callback

    GUI_CALLBACK_FUNC   callbackFunc_TouchSlideLeft;    // slide left callback
    GUI_CALLBACK_FUNC   callbackFunc_TouchSlideRight;   // slide right callback
    GUI_CALLBACK_FUNC   callbackFunc_TouchSlideUp;      // slide up callback
    GUI_CALLBACK_FUNC   callbackFunc_TouchSlideDown;    // slide down callback

} GUI_OBJ_t;

///////////////////////////////////////////////////////////////////////
// external variable
///////////////////////////////////////////////////////////////////////
extern GUI_OBJ_t *guiObj[GUI_OBJ_ID_MAX+ROOT_NUM_MAX];   // object buffer * (GUI_OBJ_ID_MAX+ROOT_NUM_MAX)

///////////////////////////////////////////////////////////////////////
// external function
///////////////////////////////////////////////////////////////////////
extern int GUI_OBJ_Open(void);
extern int GUI_OBJ_Close(void);
extern int GUI_CheckValidId(GUI_OBJ_ID id);    // check if obj id is valid
// object
extern GUI_OBJ_ID GUI_CreateObj(GUI_OBJ_ID pId, int x, int y, int width, int height);
extern int GUI_DestroyObj(GUI_OBJ_ID id);   // del obj to display list
extern int GUI_UpdateObj(GUI_OBJ_ID id);    // add obj to display list
extern void GUI_DelAllObj(void);
extern int GUI_CopyObj(GUI_OBJ_ID idSrc, int nXSrc, int nYSrc, GUI_OBJ_ID idDest, int nXDest, int nYDest, int nWidth, int nHeight);
// root
extern void GUI_RootClear(GUI_OBJ_ID rootId);               // clear root
extern int GUI_ObjToRoot(GUI_OBJ_ID id, GUI_OBJ_ID rootId); // copy obj to root
extern void GUI_RootToFB(GUI_OBJ_ID rootId);                // copy root to fb


#endif