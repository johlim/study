#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
	long ret = sysconf(_SC_PAGESIZE);
	printf("sysconf(_SC_PAGESIZE) %ld)\n", ret);

}
