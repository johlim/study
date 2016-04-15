#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS	(5)
struct thread_data {
	int thread_id;
	char * message;
};

struct thread_data thread_data_array[NUM_THREADS];
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

	for (t=0; t < NUM_THREADS; ++t)
	{
		thread_data_array[t].thread_id = t;
		thread_data_array[t].message = "Arg, Msg";
		rc = pthread_create(&threads[t], NULL, PrintHello, (void *)&thread_data_array[t]);	

	}

	for(t=10;t>0;)
	{
		sleep(1);
		t--;
	}

	pthread_exit(NULL);
}
