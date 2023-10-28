#include <stdio.h>
//#include <jpeglib.h>
#include <turbojpeg.h>
#include <stdlib.h>
unsigned char * image_buffer;
int image_height;
int image_width;
unsigned char * yuv_buffer=NULL;

int main(int argc, char * argv[])
{
	int size=0;
	unsigned char *addr[3];
	int strides[3];

	image_height=480;
	image_width=640;
	image_buffer = malloc(1024*1024);
	yuv_buffer = malloc(1024*1024);
	FILE * fp;
  	FILE * outfile;               /* target file */
	//fp = fopen("00_menu_bg.bmp","r");	
	fp = fopen("/media/jhlim/sdb1_ghost/study/use_turbojpeg/output640480.yuv","r");
    if (fp != NULL)
    {

	size = fread(yuv_buffer,1,image_width*image_height*3/2, fp);
	printf("in size : %d \n", size);
	fclose(fp);


		const int JPEG_QUALITY = 75;
		const int COLOR_COMPONENTS = 3;
		long unsigned int _jpegSize = 0;		

		addr[0] = yuv_buffer;
		addr[1] = yuv_buffer+((image_height*image_width));
		addr[2] = addr[1]+((image_height*image_width)>>2);


	strides[0] = image_width;
	strides[1] = image_width/2;
	strides[2] = image_width/2;

	tjhandle _jpegCompressor = tjInitCompress();
/*
	tjCompress2(_jpegCompressor, yuv_buffer, image_width, 0, image_height, TJPF_RGB,
			          &image_buffer, &_jpegSize, TJSAMP_444, JPEG_QUALITY,
				            TJFLAG_FASTDCT);
*/

	tjCompressFromYUVPlanes(_jpegCompressor,&addr, image_width, &strides, image_height, TJSAMP_420,
			          &image_buffer, &_jpegSize, JPEG_QUALITY,
				            TJFLAG_FASTDCT);
 


	tjDestroy(_jpegCompressor);
	outfile = fopen("./test.jpg","w");
	fwrite(image_buffer, 1, _jpegSize, outfile);
	fclose(outfile);
	printf("out size : %ld \n", _jpegSize);
	}


	return 0;
}
