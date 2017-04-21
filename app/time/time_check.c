#include <stdio.h>
#include <unistd.h>
#include <time.h> // ctime, difftime
#include <sys/types.h>
#include <sys/time.h> //gettimeofday
#include <sys/times.h> //times

int global_int = 5;
int callbackmain(int argc, char * argv[])
{
	time_t curtime;
	static time_t oldtime;

	time(&curtime);
	int diff = (int)difftime(curtime, oldtime);

//	printf("elapsed : %d sec\n",  (int)difftime(curtime, oldtime));

	if (diff >= 15)
	{
		printf("elapsed : %d sec\n",  (int)difftime(curtime, oldtime));
		printf("per 15 , update oldtime\n");
		oldtime=curtime;
	}

}


int main(int argc, char * argv[])
{
	while(1)
	{
		callbackmain(0,0);
		sleep(1);
	}
}
