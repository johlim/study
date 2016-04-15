#include <stdio.h>
#include <signal.h>

void handler1(int sig)
{
printf("1\n");
}
void handler2(int sig)
{
printf("2\n");
}

sigset_t set1={0,};

int main(int argc, char ** argv[])
{
	struct sigaction act={0,};

	sigemptyset(&set1);
	sigaddset(&set1, SIGUSR1);

	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	//
	// TRAP SIGUSR1
	act.sa_handler = handler1;
	sigaction(SIGUSR1, &act, NULL);

	// TRAP SIGUSR2
	act.sa_handler = handler2;
	sigaction(SIGUSR2, &act, NULL);

	// BLOCK SIG1
	sigprocmask(SIG_SETMASK, &set1, NULL);

	while(1) 
	{
	pause();
	sigprocmask(SIG_UNBLOCK, &set1, NULL);
	}
}
