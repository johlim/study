#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS	(5)
struct thread_data {
	int thread_id;
	char * message;
};

struct thread_data thread_data_array[NUM_THREADS];
void *send_error_thread(void * system_cmdstr)
{
    	char * cmd_pipe = (char *)system_cmdstr;
	printf("message = %s\n", cmd_pipe);
	pthread_exit(NULL);
}

void * PrintHello(void * arg)
{
	struct thread_data * my_data;
	my_data = (struct thread_data*)arg;
	printf("Thread_id = %d , message = %s\n", my_data->thread_id, my_data->message);

	pthread_exit(NULL);
}

int main(int argc, char * argv[])
{
	pthread_t threads[NUM_THREADS];
	int rc, t;
	char cmd_pipe[128]={0,};
	sprintf(cmd_pipe, "%s %s %s", "/usr/local/share/script/send_errorlog.sh", "serial", "LOG");

	for (t=0; t < NUM_THREADS; ++t)
	{
		thread_data_array[t].thread_id = t;
		thread_data_array[t].message = "Arg, Msg";
		rc = pthread_create(&threads[t], NULL, send_error_thread, (void *)cmd_pipe);
		//rc = pthread_create(&threads[t], NULL, PrintHello, (void *)&thread_data_array[t]);	

	}

	for(t=10;t>0;)
	{
		sleep(1);
		t--;
	}

	pthread_exit(NULL);
}
