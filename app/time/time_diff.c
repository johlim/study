#include <time.h>
#include <stdio.h>

int print_time(int argc, char * argv[])
{
	time_t the_time;
	struct tm* timeinfo;
	unsigned int iReadTimeInterval;
	unsigned int uAccTimer;
	uAccTimer = time(NULL);
	time(&the_time);
	timeinfo = localtime(&the_time);
	iReadTimeInterval = uAccTimer + 900;
	printf("%lld \n", iReadTimeInterval);	

}	
int main(int argc, char * argv[])
{
	int i=0;
	for(i=0; i<10; i++)
		print_time(0,NULL);
	return 0;
}
