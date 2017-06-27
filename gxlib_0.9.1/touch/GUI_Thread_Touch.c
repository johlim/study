#include <pthread.h>        //pthread_create
#include <stdio.h>          //printf
#include <unistd.h>         //perror
#include <linux/input.h>    //input_event
#include <fcntl.h>          //O_RDONLY

#include "GUI_Thread.h"
#include "GUI_Thread_Touch.h"
#include "GUI_Obj_Class.h"

///////////////////////////////////////////////////////////////////////
// define
///////////////////////////////////////////////////////////////////////
#define DBGOUT(x,...)

#define DEV_TOUCHSCREEN			"/dev/input/event1"

// Physical
#define DEF_TS_IN_Y_MIN (158)
#define DEF_TS_IN_Y_MAX (3964)

#define DEF_TS_IN_X_MIN (149)
#define DEF_TS_IN_X_MAX (3893)

#define DEF_TS_OUT_WIDTH (320)
#define DEF_TS_OUT_HEIGHT (240)

#define screen_width DEF_TS_OUT_WIDTH
#define screen_height DEF_TS_OUT_HEIGHT
enum _TOUCH_STATUS
{
    TOUCH_NONE = 0,
    TOUCH_UP,
    TOUCH_DOWN,
    TOUCH_MOVE,
    TOUCH_SLIDE_RIGHT,
    TOUCH_SLIDE_LEFT,
    TOUCH_SLIDE_UP,
    TOUCH_SLIDE_DOWN,
    TOUCH_MAX
};

typedef struct _TOUCH_MSG
{
    int status; // down or up
    int x;
    int y;
} TOUCH_MSG;

typedef int				( *CALLBACK_FUNCTION)		( void *buffer );

///////////////////////////////////////////////////////////////////////
// static variable
///////////////////////////////////////////////////////////////////////
static GUI_THREAD_t thrTouch;

static int fd_touch = -1;
static struct input_event ev[64];
static int lastx=0;
static int lasty=0;
static int vx=0;
static int vy=0;

static int ableSlide = 1;
static int ableFirstDown = 1;
CALLBACK_FUNCTION callback_func;
///////////////////////////////////////////////////////////////////////
// static function
///////////////////////////////////////////////////////////////////////
static int Conv_X( int x, int outScl )
{
	int effw = DEF_TS_IN_X_MAX - DEF_TS_IN_X_MIN;

	if( x>= DEF_TS_IN_X_MIN )
		x -= DEF_TS_IN_X_MIN;
	else if( x < DEF_TS_IN_X_MIN )
		x = 0;

	if( x> effw )
	 x = effw;

	return 	(outScl-1) * x / effw;
}

static int Conv_Y( int y, int outScl )
{
	int effh = DEF_TS_IN_Y_MAX - DEF_TS_IN_Y_MIN;

	if( y>= DEF_TS_IN_Y_MIN )
		y -= DEF_TS_IN_Y_MIN;
	else if( y < DEF_TS_IN_Y_MIN )
		y = 0;

	if( y > effh )
	 y = effh;

	return 	(outScl-1) * y / effh;
}

static void ConvXY(int *pDstX, int *pDstY, int inX, int inY )
{
	// Logical
    int FlipX = 0;
    int FlipY = 1;
    int Rotate90 = 0;
	int dstx;
	int dsty;

	if(Rotate90)
	{
		dstx = Conv_Y( inY, DEF_TS_OUT_WIDTH );
		dsty = Conv_X( inX, DEF_TS_OUT_HEIGHT );
	}
	else
	{
		dstx = Conv_X( inX, DEF_TS_OUT_WIDTH );
		dsty = Conv_Y( inY, DEF_TS_OUT_HEIGHT );
	}

	if(FlipX)
	{
		dstx = (DEF_TS_OUT_WIDTH-1) - dstx;
	}
	else
	{

	}

	if(FlipY)
	{
		dsty = (DEF_TS_OUT_HEIGHT-1) - dsty;
	}
	else
	{

	}

	*pDstX = dstx;
	*pDstY = dsty;
}


static void setAbleSlide(int value)
{
    ableSlide = value;
}
static int isSlide(int x, int y)
{
    static int last_x, last_y, dx, dy;
    int dx_range, dy_range;
    int touchStatus = TOUCH_NONE;

    if (ableSlide == 0 )
    {
        return touchStatus;
    }
    else if ( ableSlide == 1 )
    {
        dx = 0;
        dy = 0;
        last_x = x;
        last_y = y;
        ableSlide = 2;
    }
    else if ( ableSlide ==  2 )
    {
        dx += (x - last_x);
        dy += (y - last_y);

        dx_range = (screen_width)>>2;
        dy_range = (screen_height)>>2;

        if ( dx > dx_range )
        {
            touchStatus = TOUCH_SLIDE_RIGHT;
            ableSlide = 0;
        }
        else if ( dx < (dx_range * -1) )
        {
            touchStatus = TOUCH_SLIDE_LEFT;
            ableSlide = 0;
        }
        if ( dy > dy_range )
        {
            touchStatus = TOUCH_SLIDE_DOWN;
            ableSlide = 0;
        }
        else if ( dy < (dy_range * -1) )
        {
            touchStatus = TOUCH_SLIDE_UP;
            ableSlide = 0;
        }

        last_x = x;
        last_y = y;
    }

    return touchStatus;
}

static TOUCH_MSG GetTouchInfo( void )
{
    TOUCH_MSG touchMsg;
    int rd;

    touchMsg.status = TOUCH_NONE;
    touchMsg.x = 0;
    touchMsg.y = 0;

    rd = read( fd_touch, ev, sizeof(ev) );

    if( rd < (int)sizeof(struct input_event) )
	{
		perror("\nevtest: error reading");
	}

    int i, ev_count;
    ev_count = rd / sizeof(struct input_event);
	for( i=0; i<ev_count; i++ )
	{
		if(ev[i].type!=3)
			continue;
		//printf("type:%x, code:%x, value:%d \n",ev[i].type,ev[i].code,ev[i].value);
		if( ev[i].type==3 && ev[i].code==0 )
		{
			lastx = ev[i].value;//DEF_TS_OUT_WIDTH * ev[i].value / 4095;
			vx=1;
		}

		if( ev[i].type==3 && ev[i].code==1 )
		{
			lasty = ev[i].value; //DEF_TS_OUT_HEIGHT * ev[i].value / 4095;
			vy=1;
		}

		if( ev[i].type==3 && ev[i].code==0x18 && ev[i].value==0)
		{
			int x,y;
			ConvXY( &x,&y, lastx, lasty );
			//printf(" UP - X:%d, Y:%d \n ",x,y);
			touchMsg.status = TOUCH_UP;
			touchMsg.x = x;
            touchMsg.y = y;

			vx =0;
			vy =0;

			// First Down Flag
			ableFirstDown = 1;
            // Slide Flag
			setAbleSlide(1);
		}
		else
		{
			if(vx && vy)
			{
				int x,y;
				ConvXY( &x,&y, lastx, lasty );
				//printf(" DOWN - X:%d, Y:%d \n ",x,y);
				touchMsg.status = TOUCH_MOVE;
    			touchMsg.x = x;
                touchMsg.y = y;

				vx =0;
				vy =0;
                // Check First Down
                if ( ableFirstDown == 1 )
                {
                    ableFirstDown = 0;
                    touchMsg.status = TOUCH_DOWN;
                }
                // Check Slide
				int slideStatus = isSlide(x,y);
				if ( slideStatus != TOUCH_NONE )
				{
				    touchMsg.status = slideStatus;
				}
			}
		}
	}

    return touchMsg;
}

static int OpenTouchScreen( void )
{
	int	ret = 0;

	if( (fd_touch = open(DEV_TOUCHSCREEN, O_RDONLY)) < 0 )
	{
		printf("Can't open touch device...\n" );
		ret = -1;
	}

	return ret;
}

static void *GUI_Thread_Touch(void *arg)
{
    TOUCH_MSG touchMsg;
		callback_func = (CALLBACK_FUNCTION)arg;
    OpenTouchScreen();
    while( thrTouch.running == 1 )
    {
        touchMsg = GetTouchInfo();

				
        switch (touchMsg.status)
        {
            case TOUCH_UP :
                DBGOUT("[TOUCH_UP] (%d, %d)\n", touchMsg.x, touchMsg.y);

                break;
            case TOUCH_DOWN :
                DBGOUT("[TOUCH_DOWN] (%d, %d)\n", touchMsg.x, touchMsg.y);

								//printf("%p\n", callback_func);
								//callback_func(&touchMsg);
								
                break;
            case TOUCH_MOVE :               
								DBGOUT("[TOUCH_MOVE] (%d, %d)\n", touchMsg.x, touchMsg.y);
                break;
            case TOUCH_SLIDE_RIGHT :
                DBGOUT("[TOUCH_SLIDE_RIGHT] (%d, %d)\n", touchMsg.x, touchMsg.y);
								callback_func(&touchMsg);
                break;
            case TOUCH_SLIDE_LEFT :
                DBGOUT("[TOUCH_SLIDE_LEFT] (%d, %d)\n", touchMsg.x, touchMsg.y);
								callback_func(&touchMsg);

                break;
            case TOUCH_SLIDE_UP :
                DBGOUT("[TOUCH_SLIDE_UP] (%d, %d)\n", touchMsg.x, touchMsg.y);
								callback_func(&touchMsg);
                break;
            case TOUCH_SLIDE_DOWN :
                DBGOUT("[TOUCH_SLIDE_DOWN] (%d, %d)\n", touchMsg.x, touchMsg.y);
								callback_func(&touchMsg);
                break;
            default :

                break;
        }
    }

    return (void *)1;
}

///////////////////////////////////////////////////////////////////////
// external variable
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
// external function
///////////////////////////////////////////////////////////////////////
int GUI_ThreadTouch_Start(int arg)
{
    thrTouch.argument = arg;
    thrTouch.running = 1;

    thrTouch.id = pthread_create(&thrTouch.p_thread, NULL, GUI_Thread_Touch, (void *)thrTouch.argument);
    if (thrTouch.id < 0)
    {
        perror("Thread Touch");
        return -1;
    }
    // Create thread
    printf("** Thread Touch Start arg[%p]\n", thrTouch.argument);

    return 1;
}

int GUI_ThreadTouch_End(void)
{
    int ret;

    thrTouch.running = 0;
    pthread_join(thrTouch.p_thread, (void **)&ret);   // Wait untill thread is end
    printf("** Thread Touch End ret[%d]\n", thrTouch.ret);

    return ret;
}
