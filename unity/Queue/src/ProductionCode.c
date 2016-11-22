#include <stdio.h>
#include "ProductionCode.h"

static char * BufferToFind[NODE_POOL_MAX];
static int widx;
static int ridx;
volatile int * dummy;	

int PushQueue(void * input)
{
	BufferToFind[widx]= (char *)input;
	//printf("%s %p\n", __func__, input);
// Critical Section
	ridx=widx;
// Critical Section

	widx++;
	if (widx > 8)
		widx = 0;
	return ridx;
}

int PopQueue(char ** outptr)
{
	// Critial Section
	int id = ridx;
    *outptr= BufferToFind[id];
	//printf("%s %p\n", __func__, (char *)*outptr);
	return id;
}

int ResetQueue(void)
{
	//printf("%s %d %d\n", __func__, ridx,widx);
	ridx=widx=0;
	return ridx;
}
