#include <stdio.h>
#include <stdlib.h>

#define STX 0x02
#define ETX 0x03

static int parsing_ETX(char *pBuf, int len)
{
	int i;
	for(i=0; i<len; i++)
	{
	if (*(pBuf+i) == ETX)
		return i;
	}
	return -1;
}

int main(int argc,char * argv[])
{

    char FullOBDBuf[]="F002400AA79C6";
    char inputsize[5]={0,};
    char * ptrchar;
    int  intsize;
    ptrchar = &(inputsize);

    FullOBDBuf[3+1]=ETX;

    intsize = parsing_ETX(FullOBDBuf, strlen(FullOBDBuf));
    printf("%d ", intsize);

    printf("%d ", argc );



    return 0;
}



