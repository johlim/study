#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int signo);

int main(int argc, char **argv[])
{
	struct sigaction act={0,};
	int i=0;
	act.sa_handler = handler;
	sigfillset(&(act.sa_mask));
	sigaction(SIGINT, &act, NULL);

	printf("SIGINT on");
	while(1)
	{
		sleep(1);
		printf("sleep for %d sec(s).\n", ++i);
	}
}

void handler(int signo)
{
	printf("%s : %d \n", __func__, signo);
}
