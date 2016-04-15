#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int global_int = 5;
int main(int argc, char * argv[])
{
	pid_t pid;
	int stat_lock;

	pid = fork();

	if (pid == 0) {
		// child
		global_int++;
		printf("child global int : %d \n", global_int);
		exit(0);
	}
	else
	{
		global_int++;
		printf("parent global int : %d \n", global_int);
		wait(&stat_lock);
	}

	printf("parent global int : %d \n", global_int);
	return 0;

}
