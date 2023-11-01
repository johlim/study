#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

/** 
* @brief timer_callback(int signum)
* @return 
*/
void timer_callback(int signum)
{
	static int count = 0;
	printf("timer expired %d times\n", ++count);
}

/** 
* @brief timer_prn_callback(int signum)
* @return 
*/
void timer_prn_callback(int signum)
{
	time_t curtime, mktime;
	struct tm tmpbuf;
	struct tm * tmbuf;

	if (time(&curtime) < 0) {
		perror("timer error");
	}
	printf("The time is %s", ctime(&curtime));
//	tmbuf = (struct tm *)localtime(&curtime);
//	printf("The time is %s", asctime(tmbuf));
//	memcpy(&tmpbuf, tmbuf, sizeof(tmpbuf));
//	printf("The time is %d\n", tmpbuf.tm_sec);

}

int main (int argc, char *argv)
{
	struct sigaction Sa;
	struct itimerval timer;

	memset(&Sa, 0, sizeof(Sa));
	Sa.sa_handler = &timer_callback;
	Sa.sa_handler = &timer_prn_callback;
	//sigaction(SIGPROF, &Sa, NULL);
	sigaction(SIGALRM, &Sa, NULL);

	timer.it_value.tv_sec=3;
	timer.it_value.tv_usec = 0;
	timer.it_interval.tv_sec=5;
	timer.it_interval.tv_usec=0;

	//setitimer(ITIMER_PROF, &timer, NULL);
	setitimer(ITIMER_REAL, &timer, NULL);

	timer_prn_callback(0);
	while(1)
	{
		sleep(1);
	}
	return 0;
}
