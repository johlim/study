#include <stdio.h>

typedef struct _coordinate_line
{
	int x1;
	int y1;
	int x2;
	int y2;
} coordinate_line;
coordinate_line teststruct={1,2,3,4};

void PrintHello(char * pbuf, coordinate_line input)
{
	if(pbuf)
		sprintf(pbuf, "hello hi");
	else
		printf("what");
		
}

int main(int argc, char * argv[])
{
	int idx=4;
	int rc, t;
	char buf[120]={0,};

	while(idx>0)
	{
		idx -= 1;
		PrintHello(&buf,teststruct);
		printf("%s\n", buf);
	}
}
