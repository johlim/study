/*
@file     main.c
@date     2012/01/09
@author   ��漮 jks@falinux.com  FALinux.Co.,Ltd.
@brief    ./images�� �ִ� ��� �̹��� ������ ȭ�鿡 ���
@todo
@bug
@remark
@warning

���۱�    �������̸�����(��)
          �ܺΰ��� ����

 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <gx.h>
#include <gxjpg.h>
#include <gxpng.h>

/** ----------------------------------------------------------------------------
@brief  ���� ũ�� ����
@remark
 -----------------------------------------------------------------------------*/
#define MAX_BUFF_SIZE   1024
#define MAX_DEV_NANE    100

/** ----------------------------------------------------------------------------
@brief  ���� ���� ����
@remark
 -----------------------------------------------------------------------------*/
static dc_t         *dc_screen;                                         // ȭ�� Device Context
static dc_t         *dc_buffer;                                         // ȭ�� �������� ���ϱ� ���� ���� DC
static font_t 		*hfont_1;
static font_t 		*hfont_2;

static char  buff[MAX_BUFF_SIZE];                                       // 1�� �Լ������� ����� �� �ִ� ����
static char  fb_dev_name[MAX_DEV_NANE];

#define	VIEW_LEFT	    10
#define	VIEW_TOP	    10
#define	VIEW_RIGHT	    300
#define VIEW_BOTTOM	    200
#define	VIEW_WIDTH	    ( VIEW_RIGHT  	- VIEW_LEFT)
#define VIEW_HEIGHT	    ( VIEW_BOTTOM	- VIEW_TOP )

static  int ndx_counter = 0;

static void display_text( void){

    // Ư�� ���� Ư�� ������ ä��
	gx_clear_area( dc_buffer, VIEW_LEFT, VIEW_TOP, VIEW_RIGHT, VIEW_BOTTOM, gx_color( 0xff, 0, 0, 255));

	// counter ���
    dc_buffer->font = hfont_2;
    dc_buffer->font_color   = gx_color(    0, 255, 255, 60);

    gx_text_out( dc_buffer, VIEW_LEFT, VIEW_TOP+50, "TEST");
    sprintf( buff, "%d", ndx_counter++);
	dc_buffer->font	= hfont_1;
	dc_buffer->font_color	= gx_color( 100,    255, 100, 255);
	gx_text_out( dc_buffer, VIEW_LEFT+190, VIEW_TOP+40, buff);

	// �ѱ� ���ڿ� ���

    if ( ndx_counter % 5){
        dc_buffer->font = hfont_2;
        dc_buffer->font_color   = gx_color( 0, 0, 0, 255);
        gx_text_out( dc_buffer, VIEW_LEFT, VIEW_TOP+120, "������");
    }
    else {
        dc_buffer->font = hfont_1;
        dc_buffer->font_color   = gx_color( 0, 255, 0  , 255);
        gx_text_out( dc_buffer, VIEW_LEFT, VIEW_TOP+120, "black-");
    }

//    gx_bitblt( dc_screen, VIEW_LEFT, VIEW_TOP, dc_buffer, VIEW_LEFT, VIEW_TOP, VIEW_WIDTH, VIEW_HEIGHT);
		gx_bitblt_rotation(dc_screen, dc_buffer);
}


/** ----------------------------------------------------------------------------
@brief  main()
@remark -
@param  -
@return -
 -----------------------------------------------------------------------------*/
int   main  ( int argc, char *argv[]){

int alpha=0;

	script_open_parsing("../script.xml");
	
    if( 2 > argc){                                                      //  �μ��� ���ٸ� Frame Buffer�� �⺻ Device Name�� /dev/fb
        strcpy( fb_dev_name, "/dev/fb");
    } else {
        strcpy( fb_dev_name, argv[1]);
    }

    if  ( GX_SUCCESS != gx_open( fb_dev_name)           )   return 1;   // gxLib �ʱ�ȭ
    if  ( NULL == ( dc_screen = gx_get_screen_dc() ) 	)   return 1;   // ȭ�� ����� ���� screen DC ����
    if  ( NULL == ( dc_buffer
                    = gx_get_buffer_dc( 320, 240) ))   return 1;   // ȭ�� �������� ���ֱ� ���� ���� DC, width swap

		dc_buffer->dc_type = DCTYPE_SCREEN;

    gx_clear( dc_screen, gx_color( 0xf, 0xf, 0xf, 0xf0));
		gx_clear( dc_buffer, gx_color( 0xf, 0xf, 0xf, 0xf0));

    printf( "font loading\n");
    if ( NULL == ( hfont_1 = gx_open_font( "gulim12.bdf")) )   return 1;
    if ( NULL == ( hfont_2 = gx_open_font( "nago28.bdf")) )   return 1;

    printf( "running....%s\n", fb_dev_name);
    printf( "screen widht= %d\n"      , dc_screen->width);              // ȭ�� ���� ���̸� ���
		printf( "screen height= %d\n"      , dc_screen->height);              // ȭ�� ���� ���̸� ���
    printf( "screen color depth= %d\n", dc_screen->colors);

    while( 1){
		//		gx_clear( dc_screen, gx_color( 0x0, 0xf, 0xff, alpha++%255));
		    display_text();
        usleep( 100 * 1000);                                            // 200 msec ���
				//sleep(3);
    }

    gx_release_dc( dc_screen);
    gx_close();

    return   0;
}
