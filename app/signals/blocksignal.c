#include <stdio.h>
#include <signal.h>

int main(int argc, char ** argv[])
{
	sigset_t set1, set2;

	sigfillset(&set1);
	sigemptyset(&set2);
	sigaddset(&set2, SIGINT);

	printf("Critial\n");
	sigprocmask(SIG_BLOCK, &set1, NULL);

	sleep(5);
	printf("Less   \n");
	sigprocmask(SIG_UNBLOCK, &set2, NULL);

	sleep(5);
	printf("Non    \n");
	sigprocmask(SIG_UNBLOCK, &set1, NULL);

	sleep(1);
}
