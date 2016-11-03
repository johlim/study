#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#define BUFSIZE	(256)

#define FIFONAME "mfifo"
void sig_handler(int signum)
{
	printf("get sig PIPE\n");
}

int main(int argc, char ** argv[], char **envp[])
{
	int fifo ;
	char buf[BUFSIZE];
	char ch='a';
	struct sigaction act;
#if 1
	act.sa_handler = sig_handler;
	sigfillset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	sigaction(SIGPIPE, &act, NULL);
#endif
	if((fifo = open(FIFONAME, O_WRONLY)) < 0)
	{
		perror("open()");
		exit(0);
	}

	printf("open fifo success");

	while(1)
	{
		write(fifo, &ch, 1);
		sleep(1);
	}

	close(fifo);
}
