#include <stdlib.h>

int main(int argc, char ** argv[])
{
	int iflag=0;

	for(;iflag<100;iflag=iflag+2)
	SampleFunction1();

	printf("call return(%d)",	SampleAddInt(iflag,2));
	return 0;
}
