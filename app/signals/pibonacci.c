#include <stdio.h>
#include <signal.h>
#include <setjmp.h>


sigjmp_buf jbuf;

void handler1(int sig)
{
	printf("1\n");
	siglongjmp(jbuf,1);
}


int main(int argc, char ** argv[])
{
	struct sigaction act={0,};
	int cur_i, past_i, tmp_i;

	if(sigsetjmp(jbuf,1) == 0)
	{
		//
		// TRAP SIGUSR1
		act.sa_handler = handler1;
		sigaction(SIGINT, &act, NULL);
	}

	cur_i = past_i =1;

	while(1) 
	{
		printf("%d\n", cur_i);
		tmp_i = cur_i;
		cur_i += past_i;
		past_i = tmp_i;
		sleep(1);
	}
}
