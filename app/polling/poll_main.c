#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/poll.h> 

#include <stdlib.h>
#include <fcntl.h>

#define 	OPEN_MAX	(3)
struct pollfd client[OPEN_MAX];
int fd=0;
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
	
	//printf("write to socket %d \n", fd);
	//write(fd,"", 1);
}

int main_exam (int argc, char *argv)
{
	struct sigaction Sa;
	struct itimerval timer;

	memset(&Sa, 0, sizeof(Sa));
	Sa.sa_handler = &timer_callback;
	Sa.sa_handler = &timer_prn_callback;
	//sigaction(SIGPROF, &Sa, NULL);
	sigaction(SIGALRM, &Sa, NULL);

	timer.it_value.tv_sec=5;
	timer.it_value.tv_usec = 0;
	timer.it_interval.tv_sec=10;
	timer.it_interval.tv_usec=0;

	//setitimer(ITIMER_PROF, &timer, NULL);
	setitimer(ITIMER_REAL, &timer, NULL);

	timer_prn_callback(0);

	return 0;
}


int main (int argc, char *argv)
{

	int maxi = 0;
	int i = 0;
	int poll_state=0;
	int sockfd;
	char buf[255];
  	int    timeout;
  	struct pollfd fds[200];
	int    nfds = 1, current_size = 0, j;
	int    len, rc, on = 1;

	timeout = -1;//(3 * 60 * 1000);

    // 반응하도록 세팅한다. 
	fd=open("./ld_req.bin",O_RDWR , 0644);
	if (fd < 0)
		perror("open error");
	fcntl(fd, F_SETFL, FNDELAY);
	printf("fd %d\n", fd);

	if( 0 < read( fd, buf, 250))
	{
		// 수신 자료를 처리
	}
	memset(fds,0x00, sizeof(fds))	;
	
	fds[0].fd = fd;
	fds[0].events = POLLIN;
	fds[0].revents = 0;

	//main_exam(0,0);

	while(1)
	{
		time_t curtime, mktime;
		struct tm tmpbuf;
		struct tm * tmbuf;
		int nread;

		rc = poll(fds, nfds, timeout);
		/***********************************************************/
		/* Check to see if the poll call failed.                   */
		/***********************************************************/
		if (rc < 0)
		{
		perror("  poll() failed");
		break;
		}

		/***********************************************************/
		/* Check to see if the 3 minute time out expired.          */
		/***********************************************************/
		if (rc == 0)
		{
		printf("  poll() timed out.  End program.\n");
		break;
		}
			
		if (rc > 0)
		{
			current_size = nfds;
			for (i = 0; i < current_size; i++)
			{
				/*********************************************************/
				/* Loop through to find the descriptors that returned    */
				/* POLLIN and determine whether it's the listening       */
				/* or the active connection.                             */
				/*********************************************************/
				if(fds[i].revents == 0)
					continue;

				/*********************************************************/
				/* If revents is not POLLIN, it's an unexpected result,  */
				/* log and end the server.                               */
				/*********************************************************/
				if(fds[i].revents != POLLIN)
				{
					printf("  Error! revents = %d\n", fds[i].revents);
				
					break;

				}
				if((fds[i].fd == fd) && (fds[i].revents & POLLIN))
				{
					/*******************************************************/
					/* Listening descriptor is readable.                   */
					/*******************************************************/
					printf("  Listening socket is readable rc(%d) \n",rc);			

					rc = read(fds[i].fd, buf, sizeof(buf));
					if (rc < 0)
					{
						perror("  read() failed");	
						break;
					}
					if (rc == 0)	
					{
						perror("empty");
					}
				}
			}
		}
		printf("idle \n");
	}
	return 0;
}
