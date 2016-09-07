// working pc, not work board
#include <stdio.h>
//#include <jpeglib.h>
#include <turbojpeg.h>
static void YUV_lookup_table(void);
static void convert_yuv420_to_rgb(unsigned char * out, unsigned char * in, const int w, const int h);

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
	fp = fopen("/mnt/nfs/fcw/ldws_stream.yuv","r");
	size = fread(yuv_buffer,1,image_width*image_height*3/2, fp);
	printf("size : %d", size);
	fclose(fp);



	YUV_lookup_table();
	convert_yuv420_to_rgb(image_buffer, yuv_buffer, 320, 240);
	write_JPEG_file("test.jpg", 99);

	return 0;
}

static double YY[256], BU[256], GV[256], GU[256], RV[256];
static unsigned char YUV_B[256][256];
static unsigned char YUV_R[256][256];
static unsigned char YUV_G[256][256][256];

static void YUV_lookup_table(void)
{
	int i, j, k;
	double i_value;
	for( i=255; i>=0; i-- )
	{
		YY[i] = (1.164*(i-16.0));
		BU[i] = (2.018*(i-128.0));
		GV[i] = (0.831*(i-128.0));
		GU[i] = (0.391*(i-128.0));
		RV[i] = (1.596*(i-128.0));
	}

	for( i=255; i>=0; i-- ){
		for( j=255; j>=0; j-- )
		{
			i_value = YY[i] + BU[j];
			if ( i_value > 255 ) i_value=255;
			else if ( i_value < 0 ) i_value=0;
			YUV_B[i][j]=(int)i_value;

			i_value = YY[i] + RV[j];
			if ( i_value > 255 ) i_value=255;
			else if ( i_value < 0 ) i_value=0;
			YUV_R[i][j]=(int)i_value;
			for( k=0; k<256; k++ )
			{
				i_value = YY[i] - (GU[j] + GV[k]);
				if ( i_value > 255 ) i_value=255;
				else if ( i_value < 0 ) i_value=0;
				YUV_G[i][j][k] =(int)i_value;
			}
		}
	}
}

static void convert_yuv420_to_rgb(unsigned char * out, unsigned char * in, const int w, const int h)
{
	int x,y;
	double imgsize = w*h;
	int w3 = w*3;
	double uvsize = imgsize/4.0;


	unsigned char *pY = in;
	unsigned char *pV = in + (int)imgsize;
	unsigned char *pU = in + (int)imgsize + (int)uvsize;

	int y00, y01, y10, y11;
	int u,v;    
	unsigned char *p;	
	
	for( y=0; y<=h-2; y+=2 )
	{
			for( x=0; x<=w-2; x+=2 )
			{
					p = out + w3*y + x*3;
					u = *pU;
					v = *pV;

					y00 = *pY;
					y01 = *(pY+1);
					y10 = *(pY+w);
					y11 = *(pY+w+1);

					*(p)        = YUV_B[y00][u];
					*(p+1)      = YUV_G[y00][u][v];
					*(p+2)      = YUV_R[y00][v];

					*(p+3)      = YUV_B[y01][u];
					*(p+3+1)    = YUV_G[y01][u][v];
					*(p+3+2)    = YUV_R[y01][v];

					*(p+w3)     = YUV_B[y10][u];
					*(p+w3+1)   = YUV_G[y10][u][v];
					*(p+w3+2)   = YUV_R[y10][v];

					*(p+w3+3)   = YUV_B[y11][u];
					*(p+w3+3+1) = YUV_G[y11][u][v];
					*(p+w3+3+2) = YUV_R[y11][v];
					
					pU++;
					pV++;
					pY = pY + 2;
			}
			pY = pY + w;
	}
	return;	
}

