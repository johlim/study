#include <time.h>

int main(int argc, char * argv[])
{
	time_t the_time;
	struct tm* timeinfo;
	unsigned int iReadTimeInterval;
	unsigned int uAccTimer;
	uAccTimer = time(NULL);
	time(&the_time);
	timeinfo = localtime(&the_time);
	iReadTimeInterval = uAccTimer + 900;

}	
