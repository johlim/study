#include <stdio.h>
#include <unistd.h>
#include <time.h> // ctime, difftime
#include <sys/types.h>
#include <sys/time.h> //gettimeofday
#include <sys/times.h> //times

int global_int = 5;
int main(int argc, char * argv[])
{
	time_t curtime;
	time_t oldtime;

	time(&oldtime);
	printf("current : %s \n",  ctime(&oldtime));
	sleep(2);
	time(&curtime);
	printf("current : %s \n",  ctime(&curtime));

	printf("elapsed : %d sec\n",  (int)difftime(curtime, oldtime));

	struct timeval tv;
	struct timezone tz;

	gettimeofday(&tv, &tz);

	printf("%u.%06u, %d, %d \n", (int)tv.tv_sec, (int)tv.tv_usec, 
				(int)tz.tz_minuteswest, (int)tz.tz_dsttime);

	double cticks;
	clock_t tcstart, tcend;
	struct tms tmstart, tmend;

	if ((tcstart = times(&tmstart)) == -1)
	{
		perror("time");
		exit(1);
	}

	printf("Fraction of CPU time used is %d \n", tcstart);
	printf("CPU time spent executing process is %d\n", tmstart.tms_utime);
	printf("CPU time spent in system is %d\n", tmstart.tms_stime);

	sleep(2);

	if ((tcend = times(&tmend)) == -1)
	{
		perror ("get error");
		exit(1);
	}
	printf("Fraction of CPU time used is %d \n", tcstart);
	printf("CPU time spent executing process is %d\n", tmstart.tms_utime);
	printf("CPU time spent in system is %d\n", tmstart.tms_stime);

	cticks = tmend.tms_utime + tmend.tms_stime - tmstart.tms_utime - tmstart.tms_stime;

	printf("Total CPU time is %f seconds. \n", cticks/100);
	printf("Fraction CPU time used is %f \n", cticks/(tcend - tcstart));
	

	return 0;
}
