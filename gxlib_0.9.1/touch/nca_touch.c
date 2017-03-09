/*-------------------------- [ Comment ] -------------------------------------*\
	File name	: 
	Project		: 
	Description :

	Copyright(c)
  ----------------------------------------------------------------------------
	C0000 - 
	C0001 -
\*----------------------------------------------------------------------------*/

/* Header file include -------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>
#include <sys/timerfd.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "nca_touch.h"
#include "tslib.h"

/* Define  -------------------------------------------------------------------*/
#define TRUE		1
#define FALSE	0

#define	SWAP(a, b)				do { a ^= b ^= a ^= b; } while(0)


#define _240320_TO_320240(x,y) do { 											\
									 SWAP( x, y ); 								\
									 x = (int)((float)((float)VIEW_WIDTH  / (float)LCD_WIDTH)  * (float)x); \
									 y = (int)((float)((float)VIEW_HEIGHT / (float)LCD_HEIGHT) * (float)y); \
								} while(0)

struct NCA_TOUCH_CTX
{
	int					(*callback)(int, int);

	pthread_t			pthread;
	int					monitoring_start;
	int					intaval;
	int					thread_start;

	struct tsdev 			*dev;
};

typedef	struct	tagRECT
{
	unsigned short	x;	//	start x
	unsigned short	y;	//	start y
	unsigned short	w;	//	width
	unsigned short	h;	//	height
} NC_RECT, *PNC_RECT;

typedef struct
{
	int x[5], xfb[5];
	int y[5], yfb[5];
	int a[7];
} calibration;

/* Define variable  ----------------------------------------------------------*/

/* Define extern variable & function  ----------------------------------------*/

/* Function prototype  -------------------------------------------------------*/
/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static void *t_touch_monitoring(void *ctx_t)
{	
	struct NCA_TOUCH_CTX *ctx;
	if( ctx_t == NULL )
		return 0;
	else
		ctx = ctx_t;

	unsigned short 	x, y;
	int ret = 1;
	ctx->thread_start = 1;
	while(ctx->thread_start)
	{
		while(!ctx->monitoring_start)
			sleep(1);

		struct ts_sample samp;
		
		ret = ts_read( ctx->dev, &samp, 1 );
		
		if( ret < 0 )
		{
			printf("[ERROR] ts_read \n");
			goto END;
		}
		else if( ret != 1 )
		{
			goto END;
		}

		x = samp.x;
		y = samp.y;

/*
*	if can read fb, don't need _240320_TO_320240( x, y );
*/
//		_240320_TO_320240( x, y );

		ctx->callback(x, y);
END:
		usleep(ctx->intaval);

	}
	return 0;
}
/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int nca_touch_monitoring_open(void *ctx_t)
{
	struct NCA_TOUCH_CTX *ctx;
	if( ctx_t == NULL )
		return -1;
	else
		ctx = ctx_t;
	
	if((pthread_create( &ctx->pthread, NULL, t_touch_monitoring, ctx)) < 0)
	{
		printf("[ERROR] gsensor thread create falie \n");
		return -1;
	}
	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
int touch_check_calibration_file( void )
{
	int ret = TRUE;
	char *calib_file = getenv("TSLIB_CALIBFILE" );
	if( access(calib_file, F_OK) != 0 )
	{
		ret = FALSE;
	}

	return ret;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
int touch_check_default_calibration_file( void )
{
	int ret = TRUE;
	char *calib_file = "/etc/pointercal";
	if( access(calib_file, F_OK) != 0 )
	{
		ret = FALSE;
	}

	return ret;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
int perform_calibration(calibration *cal)
{
	int j;
	float n, x, y, x2, y2, xy, z, zx, zy;
	float det, a, b, c, e, f, i;
	float scaling = 65536.0;

// Get sums for matrix
	n = x = y = x2 = y2 = xy = 0;
	for(j=0;j<5;j++)
	{
		n += 1.0;
		x += (float)cal->x[j];
		y += (float)cal->y[j];
		x2 += (float)(cal->x[j]*cal->x[j]);
		y2 += (float)(cal->y[j]*cal->y[j]);
		xy += (float)(cal->x[j]*cal->y[j]);
	}

// Get determinant of matrix -- check if determinant is too small
	det = n*(x2*y2 - xy*xy) + x*(xy*y - x*y2) + y*(x*xy - y*x2);
	if(det < 0.1 && det > -0.1)
	{
		printf("ts_calibrate: determinant is too small -- %f\n",det);
		return 0;
	}

// Get elements of inverse matrix
	a = (x2*y2 - xy*xy)/det;
	b = (xy*y - x*y2)/det;
	c = (x*xy - y*x2)/det;
	e = (n*y2 - y*y)/det;
	f = (x*y - n*xy)/det;
	i = (n*x2 - x*x)/det;

// Get sums for x calibration
	z = zx = zy = 0;
	for(j=0;j<5;j++)
	{
		z += (float)cal->xfb[j];
		zx += (float)(cal->xfb[j]*cal->x[j]);
		zy += (float)(cal->xfb[j]*cal->y[j]);
	}

// Now multiply out to get the calibration for framebuffer x coord
	cal->a[0] = (int)((a*z + b*zx + c*zy)*(scaling));
	cal->a[1] = (int)((b*z + e*zx + f*zy)*(scaling));
	cal->a[2] = (int)((c*z + f*zx + i*zy)*(scaling));

	printf("%f %f %f\n",(a*z + b*zx + c*zy),
				(b*z + e*zx + f*zy),
				(c*z + f*zx + i*zy));

// Get sums for y calibration
	z = zx = zy = 0;
	for(j=0;j<5;j++)
	{
		z += (float)cal->yfb[j];
		zx += (float)(cal->yfb[j]*cal->x[j]);
		zy += (float)(cal->yfb[j]*cal->y[j]);
	}

// Now multiply out to get the calibration for framebuffer y coord
	cal->a[3] = (int)((a*z + b*zx + c*zy)*(scaling));
	cal->a[4] = (int)((b*z + e*zx + f*zy)*(scaling));
	cal->a[5] = (int)((c*z + f*zx + i*zy)*(scaling));

	printf( "[%s:%d]%f %f %f\n", __FILE__, __LINE__,	\
				(a*z + b*zx + c*zy),	\
				(b*z + e*zx + f*zy),	\
				(c*z + f*zx + i*zy) );

// If we got here, we're OK, so assign scaling to a[6] and return
	cal->a[6] = (int)scaling;
	return 1;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int sort_by_x(const void* a, const void *b)
{
	return (((struct ts_sample *)a)->x - ((struct ts_sample *)b)->x);
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int sort_by_y(const void* a, const void *b)
{
	return (((struct ts_sample *)a)->y - ((struct ts_sample *)b)->y);
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
void getxy(struct tsdev *ts, int *x, int *y)
{
#define MAX_SAMPLES 128
	struct ts_sample samp[MAX_SAMPLES];
	int index, middle;

	int status = 0;
	do
	{
		if (ts_read_raw(ts, &samp[0], 1) < 0)
		{
			status = -1;
			fprintf( stdout, "[%s:%d] error. ts_read_raw\n", __FILE__, __LINE__ );
			perror("ts_read");
			break;
		}
	} while (samp[0].pressure == 0);

	if( status == -1 )
		return;

	/* Now collect up to MAX_SAMPLES touches into the samp array. */
	index = 0;
	do
	{
		if (index < MAX_SAMPLES-1)
			index++;
		
		if (ts_read_raw(ts, &samp[index], 1) < 0)
		{
			status = -1;
			fprintf( stdout, "[%s:%d] error. ts_read_raw\n", __FILE__, __LINE__ );
			perror("ts_read");
			break;
		}
	} while (samp[index].pressure > 0);
	printf("Took %d samples...\n",index);

	/*
	 * At this point, we have samples in indices zero to (index-1)
	 * which means that we have (index) number of samples.  We want
	 * to calculate the median of the samples so that wild outliers
	 * don't skew the result.  First off, let's assume that arrays
	 * are one-based instead of zero-based.  If this were the case
	 * and index was odd, we would need sample number ((index+1)/2)
	 * of a sorted array; if index was even, we would need the
	 * average of sample number (index/2) and sample number
	 * ((index/2)+1).  To turn this into something useful for the
	 * real world, we just need to subtract one off of the sample
	 * numbers.  So for when index is odd, we need sample number
	 * (((index+1)/2)-1).  Due to integer division truncation, we
	 * can simplify this to just (index/2).  When index is even, we
	 * need the average of sample number ((index/2)-1) and sample
	 * number (index/2).  Calculate (index/2) now and we'll handle
	 * the even odd stuff after we sort.
	 */
	middle = index/2;
	if (x)
	{
		qsort(samp, index, sizeof(struct ts_sample), sort_by_x);
		if (index & 1)
			*x = samp[middle].x;
		else
			*x = (samp[middle-1].x + samp[middle].x) / 2;
	}

	if (y)
	{
		qsort(samp, index, sizeof(struct ts_sample), sort_by_y);
		if (index & 1)
			*y = samp[middle].y;
		else
			*y = (samp[middle-1].y + samp[middle].y) / 2;
	}
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static void get_sample (struct tsdev *ts, calibration *cal, int index, int x, int y, char *name)
{
	static int last_x = -1, last_y;

	if (last_x != -1)
	{
		#define NR_STEPS 10
		
		int dx = ((x - last_x) << 16) / NR_STEPS;
		int dy = ((y - last_y) << 16) / NR_STEPS;
		int i;
		last_x <<= 16;
		last_y <<= 16;
		for (i = 0; i < NR_STEPS; i++)
		{
			usleep (1000);
			last_x += dx;
			last_y += dy;
		}
	}

	getxy (ts, &cal->x [index], &cal->y [index]);

	last_x = cal->xfb [index] = x;
	last_y = cal->yfb [index] = y;

	printf("%s : X = %4d Y = %4d\n", name, cal->x [index], cal->y [index]);
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
int running_touch_calibrarion( void* ctx_t )
{

	struct NCA_TOUCH_CTX *ctx;

	if( ctx_t == NULL )
		return -1;
	else
		ctx = ctx_t;
	
	struct tsdev *ts;
	calibration cal;
	int cal_fd;
	char cal_buffer[256];
	char *tsdevice = NULL;
	char *calfile = NULL;
	unsigned int i;

	unsigned int x_fb_res = LCD_HEIGHT;
	unsigned int y_fb_res = LCD_WIDTH;

	unsigned int x_scr_res = LCD_WIDTH;
	unsigned int y_scr_res = LCD_HEIGHT;

	unsigned int x_margin = 50;
	unsigned int y_margin = 50;

	ts = ctx->dev;
	if(ts)
	{
		NC_RECT r = (NC_RECT){ 0, 0, LCD_WIDTH, LCD_HEIGHT };
		
		///////////////////////////////////////////////////////////////////////////////////
		
		printf("start Top Left\n");
		do
		get_sample (ts, &cal, 1, x_fb_res - x_margin, y_margin, "Top Left");
		while( !(cal.x [1] < 800 && cal.y [1] > 3200) );
		///////////////////////////////////////////////////////////////////////////////////
		
		printf("start Top right\n");
		do
			get_sample (ts, &cal, 2, x_fb_res-x_margin, y_fb_res-y_margin, "Top right");
		while( !(cal.x [2] < 800 && cal.y [2] < 800) );
		///////////////////////////////////////////////////////////////////////////////////

		printf("start Bot left\n");
		do
			get_sample (ts, &cal, 0, 50, 50, "Bot left");
		while( !(cal.x [0] > 3200 && cal.y [0] > 3200) );
		///////////////////////////////////////////////////////////////////////////////////

		printf("start Bot Right\n");
		do
			get_sample (ts, &cal, 3, 50, y_fb_res - 50, "Bot Right");
		while( !(cal.x [3] > 3200 && cal.y [3] < 800) );
		///////////////////////////////////////////////////////////////////////////////////

		printf("start Center\n");
		do
			get_sample (ts, &cal, 4, x_fb_res / 2,  y_fb_res / 2, "Center");
		while( !((cal.x [4] > 1500 && cal.x [4] < 2500) && (cal.y [4] > 1500 && cal.y [4] < 2500)) );
		///////////////////////////////////////////////////////////////////////////////////

		if( perform_calibration(&cal) )
		{
			printf ("Calibration constants: ");
			for (i = 0; i < 7; i++) printf("%d ", cal.a [i]);
			printf("\n");
			if ((calfile = getenv("TSLIB_CALIBFILE")) != NULL)
			{
				cal_fd = open (calfile, O_CREAT | O_RDWR);
			}
			else
			{
				cal_fd = open ("/etc/pointercal", O_CREAT | O_RDWR);
			}
			sprintf (cal_buffer,"%d %d %d %d %d %d %d",
								 cal.a[1], cal.a[2], cal.a[0],
								 cal.a[4], cal.a[5], cal.a[3], cal.a[6]);
			
			int size = strlen(cal_buffer) + 1;
			int wt	 = write( cal_fd, cal_buffer, size );			
			fprintf( stdout, "[%s:%d] %s. create touch calibration file\n", __FILE__, __LINE__, wt==size ? "SUCCESS" : "FAIL" );
			close( cal_fd );

			system("sync");
		}
		else
		{
			printf("Calibration failed.\n");
			return -1;
		}
		
	}
	else
	{
		printf("not ts open \n");
		return -1;
	}
	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int nca_touch_device_open(void *ctx_t)
{
	struct NCA_TOUCH_CTX *ctx;

	if( ctx_t == NULL )
		return -1;
	else
		ctx = ctx_t;

	char *tsdevice;

	if( (tsdevice = getenv("TSLIB_TSDEVICE")) )
	{
		if( (ctx->dev=ts_open(tsdevice, 0)))
		{
			if (ts_config(ctx->dev) == 0 )
			{
				/*
				* serch Calibration Info
				*/
				if( touch_check_calibration_file() == FALSE )
				{
					/*
					* serch default Calibration file
					*/
					if( touch_check_default_calibration_file() == TRUE )
					{
						char *def_calibfile = "pointercal";
						char command[128];
						sprintf( command, "cp /etc/%s %s", def_calibfile, getenv("TSLIB_CALIBFILE") );
						system( command );
						system( "sync" );
					}
					else
					{
						printf("NO!! default calibration data!!! \n");
						running_touch_calibrarion(ctx);// add draw graphic
					}
					
				}
			}
			else
			{
				printf("[ERROR] ts_config error \n");
				return -1;
			}
		}
		else
		{
			printf("[ERROR] ts_open error \n");
			return -1;
		}
	}
	else
	{
		printf("[ERROR] getenv error  TSLIB_TSDEVICE \n");
		return -1;
	}

	return 0;

}
/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
int nca_touch_open( void *ctx_t )
{
	struct NCA_TOUCH_CTX *ctx;

	if( ctx_t == NULL )
		ctx = malloc(sizeof(struct NCA_TOUCH_CTX));
	else
		ctx = ctx_t;

	memset( ctx, 0, sizeof(struct NCA_TOUCH_CTX));

	ctx->thread_start = 0;
	
	nca_touch_device_open(ctx);
	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
int nca_touch_close( void *ctx_t )
{
	struct NCA_TOUCH_CTX *ctx;

	if( ctx_t == NULL )
		return -1;
	else
		ctx = ctx_t;
	
	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
unsigned int nca_touch_read( void *ctx_t, void *data,  int size)
{ 
	struct NCA_TOUCH_CTX *ctx;

	if( ctx_t == NULL)
		return -1;
	else
		ctx = ctx_t;
 
	return 0;
}
/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
unsigned int nca_touch_write( void *ctx_t, unsigned char *data, unsigned int size)
{
	struct NCA_TOUCH_CTX *ctx;

	if( ctx_t == NULL)
		return -1;
	else
		ctx = ctx_t;
	
	return 0;
}
/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
int nca_touch_control( void *ctx_t, NCA_CTRL_TOUCH type, ...)
{ 
	struct NCA_TOUCH_CTX *ctx;

	if( ctx_t == NULL )
		return -1;
	else
		ctx = ctx_t;

	/* check maxctrl */
	if (type >= NCA_CTRL_TOUCH_MAX)
		return -1;

	/* Parse multi param */
	va_list ctrl;
	int		cur_ctrl;

	va_start (ctrl, type );
	cur_ctrl = type;
	while( cur_ctrl != NCA_CTRL_TOUCH_END )
	{
		switch(cur_ctrl)
		{
			case NCA_CTRL_TOUCH_MONITORING:
				{
					int param = va_arg(ctrl, int);
					ctx->monitoring_start = param;
				}
				break;
			case NCA_CTRL_TOUCH_CALLBACK:
				{
					int (*cb)(int, int) = va_arg(ctrl, int (*)(int, int));
					ctx->callback = cb;					
				}
				break;
			case NCA_CTRL_TOUCH_INTERVAL:
				{
					ctx->intaval = va_arg(ctrl, int);
				}
				break;
			case NCA_CTRL_TOUCH_START:
				{
					int param = va_arg(ctrl, int);
					
					if(param)
					{
						nca_touch_monitoring_open(ctx);
					}
				}
				break;
			case NCA_CTRL_TOUCH_STOP:
				{
					ctx->thread_start = 0;
					if(ctx->pthread)
					{
						pthread_join(ctx->pthread, NULL);
						ctx->pthread = 0;
					}
						
				}
				break;
		}
		cur_ctrl = va_arg(ctrl, int);
	}
	va_end( ctrl );
 
	return 0;
}
struct NCA_TOUCH_OPERATION nca_touch = {

		.name			= "nca_touch",
		.ctxsize			= sizeof(struct NCA_TOUCH_CTX),
		.maxctrl			= NCA_CTRL_TOUCH_MAX,

		.open			= nca_touch_open,
		.close			= nca_touch_close,
//		.read			= nca_touch_read,
//		.write			= nca_touch_write,
		.control			= nca_touch_control,

		/* component dependent fuction */
};

