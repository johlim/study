#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#define BUFSIZE	(256)

#define FIFONAME "mfifo"
void sig_handler(int signum)
{
	printf("get sig PIPE");
}

int main(int argc, char ** argv[], char **envp[])
{
	int fifo ;
	char buf[BUFSIZE];
	char ch;
	struct sigaction act;


	if((fifo = open(FIFONAME, O_RDONLY)) < 0)
	{
		perror("open()");
		exit(0);
	}

	printf("open fifo success");

	while(1)
	{
		if ( read(fifo, &ch, 1)==1)
		write(1,&ch,1);
	}

	close(fifo);
}
