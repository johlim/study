#include <stdio.h>
#include <jpeglib.h>
JSAMPLE * image_buffer;
int image_height;
int image_width;
int main(int argc, char * argv[])
{
	image_height=480;
	image_width=720;
	image_buffer = malloc(1024*1024);
	FILE * fp;
	fp = fopen("00_menu_bg.bmp","r");	
	fread(image_buffer,1,1024*1000, fp);
	fclose(fp);
	write_JPEG_file("test.jpg", 99);
	return 0;
}
