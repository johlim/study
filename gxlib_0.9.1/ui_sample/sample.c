#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <gx.h>
#include <gxjpg.h>
#include <gxpng.h>


/** ----------------------------------------------------------------------------
@brief  버퍼 크기 정의
@remark
 -----------------------------------------------------------------------------*/
#define MAX_BUFF_SIZE   1024
#define MAX_DEV_NANE    100

/** ----------------------------------------------------------------------------
@brief  지역 변수 정의
@remark
 -----------------------------------------------------------------------------*/
static dc_t         *dc_screen;                                         // 화면 Device Context
static dc_t         *dc_buffer;                                         // 화면 깜빡임을 피하기 위한 버퍼 DC
static font_t 		*hfont_1;
static font_t 		*hfont_2;

static char  buff[MAX_BUFF_SIZE];                                       // 1차 함수에서만 사용할 수 있는 버퍼
static char  fb_dev_name[MAX_DEV_NANE];

#define	VIEW_LEFT	    0
#define	VIEW_TOP	    0
#define	VIEW_RIGHT	    319
#define VIEW_BOTTOM	    239
#define	VIEW_WIDTH	    ( VIEW_RIGHT  	- VIEW_LEFT)
#define VIEW_HEIGHT	    ( VIEW_BOTTOM	- VIEW_TOP )

static  int ndx_counter = 0;

static void intro_text( void){

	// 특정 지역 특정 색으로 채움
	gx_clear_area( dc_buffer, VIEW_LEFT, VIEW_TOP, VIEW_RIGHT, VIEW_BOTTOM, gx_color( 0x00,0x00, 0, 255));

	// counter 출력
	dc_buffer->font = hfont_2;
	dc_buffer->font_color   = gx_color( 0, 255, 0  , 255);
	gx_text_out( dc_buffer, VIEW_LEFT+50, VIEW_TOP+50, "Firmware ");
	gx_text_out( dc_buffer, VIEW_LEFT+50, VIEW_TOP+90, "Update ?");
	dc_buffer->font = hfont_1;
	gx_text_out( dc_buffer, VIEW_LEFT+50, VIEW_TOP+140, "NO , touch left(<-) ");
	gx_text_out( dc_buffer, VIEW_LEFT+150, VIEW_TOP+160, "YES touch right(->)");

//    gx_bitblt( dc_screen, VIEW_LEFT, VIEW_TOP, dc_buffer, VIEW_LEFT, VIEW_TOP, VIEW_WIDTH, VIEW_HEIGHT);
	gx_bitblt_rotation(dc_screen, dc_buffer);
	printf("%s %d \n", __func__, __LINE__);
}

static void display_text( void){
  // 특정 지역 특정 색으로 채움
	gx_clear_area( dc_buffer, VIEW_LEFT, VIEW_TOP, VIEW_RIGHT, VIEW_BOTTOM, gx_color( 0xff, 0, 0, 255));

	// counter 출력
    dc_buffer->font = hfont_2;
    dc_buffer->font_color   = gx_color(    0, 255, 255, 60);

    gx_text_out( dc_buffer, VIEW_LEFT, VIEW_TOP+50, "TEST");
    sprintf( buff, "%d", ndx_counter++);
	dc_buffer->font	= hfont_1;
	dc_buffer->font_color	= gx_color( 100,    255, 100, 255);
	gx_text_out( dc_buffer, VIEW_LEFT+190, VIEW_TOP+40, buff);

	// 한글 문자열 출력

    if ( ndx_counter % 5){
        dc_buffer->font = hfont_2;
        dc_buffer->font_color   = gx_color( 0, 0, 0, 255);
        gx_text_out( dc_buffer, VIEW_LEFT, VIEW_TOP+120, "검정색");
    }
    else {
        dc_buffer->font = hfont_1;
        dc_buffer->font_color   = gx_color( 0, 255, 0  , 255);
        gx_text_out( dc_buffer, VIEW_LEFT, VIEW_TOP+120, "black-");
    }

//    gx_bitblt( dc_screen, VIEW_LEFT, VIEW_TOP, dc_buffer, VIEW_LEFT, VIEW_TOP, VIEW_WIDTH, VIEW_HEIGHT);
		gx_bitblt_rotation(dc_screen, dc_buffer);

		printf("%s %d \n", __func__, __LINE__);
}

static void display_line( void){

    // 특정 지역 특정 색으로 채움
	gx_clear_area( dc_buffer, VIEW_LEFT, VIEW_TOP, VIEW_RIGHT, VIEW_BOTTOM, gx_color( 0xff, 0, 0, 255));
			dc_buffer->pen_color    = gx_color( 255, 255, 255, 255);
			dc_buffer->brush_color  = gx_color( 255,   0, 255, 255);	
	gx_rectangle( dc_buffer, 10, 10, 200, 30);



//    gx_bitblt( dc_screen, VIEW_LEFT, VIEW_TOP, dc_buffer, VIEW_LEFT, VIEW_TOP, VIEW_WIDTH, VIEW_HEIGHT);
		gx_bitblt_rotation(dc_screen, dc_buffer);
		printf("%s %d \n", __func__, __LINE__);
}

static void display_rec(int pos)
{
	
		fprintf(stderr,"%s %d (%d)\n", __func__, __LINE__,pos);
		
		
		switch(pos)
		{
			case 0:
			gx_clear( dc_screen, gx_color( 0, 0, 0, 255));		
			dc_screen->pen_color    = gx_color( 255, 255, 255, 255);
			dc_screen->brush_color  = gx_color( 255,   0, 255, 255);
			gx_rectangle( dc_screen, 10, 10, 100, 100);
			break;

			case 1:
			gx_clear( dc_screen, gx_color( 0, 0, 0, 255));		
			dc_screen->pen_color    = gx_color( 255, 255, 255, 0);
			dc_screen->brush_color  = gx_color( 255,   0,   0, 255);
			gx_rectangle( dc_screen, 40, 40, 130, 130);
			break;

			case 2:
			// dc_screen->pen_color    = gx_color( 255, 255, 255, 0);
			// dc_screen->brush_color  = gx_color( 255,  255,   0, 100);
			// gx_rectangle( dc_screen, 10, 40, 100, 150);
			intro_text();
			break;

			case 3:		
			// dc_screen->pen_color    = gx_color( 255,   0, 255, 255);
			// dc_screen->brush_color  = gx_color(   0, 255,   0, 255);
			// gx_rectangle( dc_screen, 40, 10, 130, 100);
			
			//default:
			//display_text();
			gx_clear( dc_buffer, gx_color( 0xff, 0, 0, 255));
			gx_bitblt_rotation(dc_screen, dc_buffer);
		}
		//gx_release_dc( dc_screen);
}
static void callback_TouchHandler (void * param)
{
	callback_userinput(param);// touch , key etc
		//gx_clear_area( dc_screen, 100, 100, 200, 200, gx_color( 0xff, 0, 0, 255));
	{
		int * type= param;
		display_rec(type[0]%4);
		//display_line();
	}
}

/** ----------------------------------------------------------------------------
@brief  main()
@remark -
@param  -
@return -
 -----------------------------------------------------------------------------*/
int   main  ( int argc, char *argv[]){

	script_open_parsing("../script.xml");
	
    if( 2 > argc){                                                      //  인수가 없다면 Frame Buffer의 기본 Device Name은 /dev/fb
        strcpy( fb_dev_name, "/dev/fb");
    } else {
        strcpy( fb_dev_name, argv[1]);
    }

    if  ( GX_SUCCESS != gx_open( fb_dev_name)           )   return 1;   // gxLib 초기화
    if  ( NULL == ( dc_screen = gx_get_screen_dc() ) 	)   return 1;   // 화면 출력을 위한 screen DC 구함
    if  ( NULL == ( dc_buffer
                    = gx_get_buffer_dc( 320, 240) ))   return 1;   // 화면 깜빡임을 없애기 위한 버퍼 DC, width swap

		dc_buffer->dc_type = DCTYPE_SCREEN;

    gx_clear( dc_screen, gx_color( 0xf, 0xf, 0xf, 0xf0));
		gx_clear( dc_buffer, gx_color( 0xf, 0xf, 0xf, 0xf0));

    printf( "font loading\n");
    if ( NULL == ( hfont_1 = gx_open_font( "gulim12.bdf")) )   return 1;
    if ( NULL == ( hfont_2 = gx_open_font( "nbold32.bdf")) )   return 1;

    printf( "running....%s\n", fb_dev_name);
    printf( "screen widht= %d\n"      , dc_screen->width);              // 화면 폭과 넓이를 출력
		printf( "screen height= %d\n"      , dc_screen->height);              // 화면 폭과 넓이를 출력
    printf( "screen color depth= %d\n", dc_screen->colors);

		//////////////////////////
		open_userinput_handler();
		
		printf(" display_text %p \n", callback_TouchHandler);
		
		GUI_ThreadTouch_Start(callback_TouchHandler);
		
		
		////////////////////////////
		setRun_userinput(1); // userinput enable
		
		// touch cal require tslib
		// nca_touch_open(0);
		intro_text();
		//display_line();
		
		//display_text();
		
    while( 1){
       usleep( 100 * 1000);                                            // 200 msec 대기
    }

		gx_release_dc( dc_buffer);
    gx_release_dc( dc_screen);
    gx_close();

    return   0;
}
