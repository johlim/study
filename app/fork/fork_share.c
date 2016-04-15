#include <sys/mman.h>
#include <stdio.h>
#include <fcntl.h>

#include <stdlib.h> // malloc
int fd;

void memopen(void)
{
	fd = open("./maptest.txt", O_RDWR| O_CREAT);
	if(fd <0)
	{
		perror("FAIL \n");
		exit(1);
	}
	//return 0;
}
void memrelease(void)
{
	close(fd);
}


#define CS3_BASE	(0x04000000)
int main(int argc, char ** argv[])
{
	char * cs3_base;

	cs3_base = malloc(4096);
	memopen();



	*(cs3_base + 1) = 'A';

	pid_t pid;
	pid_t ppid;

	pid = fork();

	if (pid == 0)
	{
		*(cs3_base + 1) = 'B';
	}
	else if (pid > 0)
	{
		*(cs3_base + 2) = 'C';
	}


	write(fd, cs3_base, 10);

EXIT2:	

	memrelease();
	free(cs3_base);
	return 0;
}
