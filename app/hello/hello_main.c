#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int str_match_string( char* key, char* target )
{
	int srclen=strlen(target);
	int len=strlen(key);
	int iret=0;

	printf ("%s %s comp %s\n", __func__, key, target);

	if ((srclen-len) <= 0)
		return iret;
	for(int i=0; i < srclen-len; i++ )
	{
		iret= memcmp(key,target+i,len);
		printf ("%s %d %s comp %s\n", __func__, iret, key, target+i);
		if (iret == 0)
			break;
	}

	return iret;
}

struct ringbuf_t;
typedef struct ringbuf_t* ringbuf;

int print_tablesize(void);
void request_set_rtc(void);
int main(int argc, char * argv)
{
	print_tablesize();
	printf("hello world %d \n", str_match_string("20200611","/mnt/config/20200611_product.cfg"));
	request_set_rtc();
	return 0;
}
