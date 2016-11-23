#include <stdio.h>
#include <signal.h>

int gQuit;

void c_handler(int signo)
{
	printf("main sent signal(SIGUSR1) \n");
}

void c_q_handler(int signo)
{
	printf("main sent signal(SIGUSR2) (%d)\n", signo);
	gQuit=1;
}

int main(int argc, char * argv[])
{
	int ret;	
	// wait signal
#if 1
	{
		struct sigaction act;
		act.sa_handler = c_handler;
		sigfillset(&(act.sa_mask));
		sigaction(SIGUSR1, &act, NULL);
		
	}	
#endif

#if 1
	{
		struct sigaction act;
		act.sa_handler = c_q_handler;
		sigfillset(&(act.sa_mask));
		sigaction(SIGUSR2, &act, NULL);
		
	}	
#endif

	while(!gQuit)
		sleep(1);

	return ret;
}
