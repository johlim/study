#include <sys/mman.h>
#include <stdio.h>
#include <fcntl.h>

#include <stdlib.h> // malloc
int fd;

void memopen(void)
{
	fd = open("./maptest.txt", O_RDWR);
	if(fd <0)
	{
		perror("FAIL \n");
		exit(1);
	}
	return 0;
}
void memrelease(void)
{
	close(fd);
}


#define CS3_BASE	(0x04000000)
int main(int argc, char ** argv[])
{
	char * cs3_base;
	char * bufptr;

	bufptr = malloc(4096);
	memopen();

	//cs3_base = mmap(NULL, 1024, PROT_READ | PROT_WRITE , MAP_SHARED, fd, CS3_BASE);
	cs3_base = mmap(NULL, 1024, PROT_READ | PROT_WRITE , MAP_SHARED, fd, &bufptr);

	if((int)cs3_base == -1) {
		perror("mmap fail");
		goto EXIT2;
	}

	*(cs3_base + 1) = 'A';

	pid_t pid;
	pid_t ppid;

	pid = fork();

	if (pid == 0)
	{
		*(cs3_base + 1) = 'C';
	}
	else if (pid > 0)
	{
		*(cs3_base + 2) = 'A';
	}



EXIT2:	

	memrelease();
	free(bufptr);
}
