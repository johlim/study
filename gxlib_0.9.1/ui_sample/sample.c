#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <gx.h>
#include <gxjpg.h>
#include <gxpng.h>

#include <fcntl.h>
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

#define	VIEW_LEFT	    5
#define	VIEW_TOP	    10
#define	VIEW_RIGHT	    319
#define VIEW_BOTTOM	    239
#define	VIEW_WIDTH	    ( VIEW_RIGHT  	- VIEW_LEFT)
#define VIEW_HEIGHT	    ( VIEW_BOTTOM	- VIEW_TOP )

static  int ndx_counter = 0;

static dump(void * src, int len)
{
	int ret;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	int fd= open("buffer.yuv", O_RDWR | O_CREAT | O_TRUNC , mode );
	if(fd <0)
	{
		perror("file error\n");
		return;
	}
	ret=write(fd, src, len);
	close(fd);
	printf("write %d \n", ret);
}

static void display_text( void){

    // Ư�� ���� Ư�� ������ ä��
	// gx_clear_area( dc_buffer, VIEW_LEFT, VIEW_TOP, VIEW_RIGHT, VIEW_BOTTOM, gx_color( 0xff, 0, 0, 255));

	// counter ���
    dc_buffer->font = hfont_2;
    dc_buffer->font_color   = gx_color(  255, 0, 0, 0);
    gx_text_out( dc_buffer, VIEW_LEFT, VIEW_TOP+50, "255,0,0,0");
    dc_buffer->font_color   = gx_color(  0, 255, 0, 0);
    gx_text_out( dc_buffer, VIEW_LEFT, VIEW_TOP+90, "0,255,0,0");
    dc_buffer->font_color   = gx_color(  0, 0, 255, 0);
    gx_text_out( dc_buffer, VIEW_LEFT, VIEW_TOP+130, "0,0,255,0");
    dc_buffer->font_color   = gx_color(  0, 0, 0, 255);
    gx_text_out( dc_buffer, VIEW_LEFT, VIEW_TOP+170, "0,0,0,255");
    dc_buffer->font_color   = gx_color(  0, 0, 0, 0);
    gx_text_out( dc_buffer, VIEW_LEFT, VIEW_TOP+210, "0,0,0,0");




//    gx_bitblt( dc_screen, VIEW_LEFT, VIEW_TOP, dc_buffer, VIEW_LEFT, VIEW_TOP, VIEW_WIDTH, VIEW_HEIGHT);
//		gx_bitblt_rotation(dc_screen, dc_buffer);
    dump(dc_buffer->mapped, dc_buffer->bytes);
}


/** ----------------------------------------------------------------------------
@brief  main()
@remark -
@param  -
@return -
 -----------------------------------------------------------------------------*/
int   main  ( int argc, char *argv[]){

#if defined(GLIB)
	script_open_parsing("../script.xml");
#endif
	
    if( 2 > argc){                                                      //  �μ��� ���ٸ� Frame Buffer�� �⺻ Device Name�� /dev/fb
        strcpy( fb_dev_name, "/dev/fb");
    } else {
        strcpy( fb_dev_name, argv[1]);
    }

	if  ( GX_SUCCESS != gx_open( fb_dev_name)  )  
   	{ 
		perror("fb access");
		return 1;   // gxLib �ʱ�ȭ
	}

	if  ( NULL == ( dc_screen = gx_get_screen_dc() ))
	{ 
		perror("fb access");
		return 1;   // ȭ�� ����� ���� screen DC ����
	}

	printf( "running....%s\n", fb_dev_name);
	printf( "screen widht= %d\n"      , dc_screen->width);              // ȭ�� ���� ���̸� ���
	printf( "screen height= %d\n"      , dc_screen->height);              // ȭ�� ���� ���̸� ���
	printf( "screen color depth= %d\n", dc_screen->colors);

	if  ( NULL == ( dc_buffer = gx_get_buffer_dc( 320, 240) ))   
	{ 
		perror("fb access");
		return 1;   // ȭ�� �������� ���ֱ� ���� ���� DC, width swap
	}
	printf( "buffer widht= %d\n"      , dc_buffer->width);              // ȭ�� ���� ���̸� ���
	printf( "buffer height= %d\n"      , dc_buffer->height);              // ȭ�� ���� ���̸� ���
	printf( "buffer color depth= %d\n", dc_buffer->colors);

    gx_clear( dc_screen, gx_color( 0xf, 0xf, 0xf, 0xf0));
	
	gx_clear( dc_buffer, gx_color( 0x0, 0x0, 0x0, 0x0));

    if ( NULL == ( hfont_1 = gx_open_font( "gulim12.bdf")) ) 
	{  
		perror("font file access");
		return 1;
	}
    if ( NULL == ( hfont_2 = gx_open_font( "nbold32.bdf")) )
	{  
		perror("font file access");
		return 1;
	}

		display_text();

    while( 1){
		usleep( 100 * 1000);                                            // 200 msec ���
		//sleep(3);
    }

    gx_release_dc( dc_screen);
    gx_close();

    return   0;
}
