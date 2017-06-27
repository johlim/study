#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS	(1)
struct thread_data {
	int thread_id;
	char * message;
};

typedef struct _coordinate_line
{
	int x1;
	int y1;
	int x2;
	int y2;
} coordinate_line;

struct thread_data thread_data_array[NUM_THREADS];
coordinate_line draw_line_xy[4];
void * PrintHello(void * arg)
{
	int myidx=0;
	struct thread_data * my_data;
	my_data = (struct thread_data*)arg;
	coordinate_line * ptr;
	printf("Thread_id = %d , message = %s\n", my_data->thread_id, my_data->message);

	while(1)
	{
		//ptr = draw_line_xy[myidx];
		ptr = &draw_line_xy[myidx];
		printf("%d (%d) \n", ptr->x1, ptr->y1);
		sleep(1);
		myidx = ++myidx & 3;
	}

	pthread_exit(NULL);
}

int main(int argc, char * argv[])
{
	int idx=0;
	pthread_t threads[NUM_THREADS];
	int rc, t;

	for (t=0; t < NUM_THREADS; ++t)
	{
		thread_data_array[t].thread_id = t;
		thread_data_array[t].message = "Arg, Msg";
		rc = pthread_create(&threads[t], NULL, PrintHello, (void *)&thread_data_array[t]);	

	}

	for(t=50;t>0;)
	{
		t--;
		draw_line_xy[idx].x1 = idx;
		draw_line_xy[idx].y1 = t;
		idx = ++idx & 3;
		sleep(2);
	}

	pthread_exit(NULL);
}
