#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define DBG(fmt,args...)	\
	{	\
	fprintf(stderr, "[%s] %d " fmt,  __FUNCTION__, __LINE__, ##args); \
	}

typedef struct
{
		int32_t buf_id;	
} MSG_BUFFER_INFO;

enum __MSG_TYPE_BUFF__
{
	MSG_TYPE_PD		= 100,
	MSG_TYPE_MAIN = 200,
};

static pthread_t	s_tid_rearprocess=0;

void * rear_process( void * inptr)
{
	
		
	while(1)	
	{
		MSG_BUFFER_INFO send_msg={0,};
		MSG_BUFFER_INFO recv_msg={0,};
		
		if ( ReciveMsg(MSG_TYPE_PD, &recv_msg) > 0 )
		{
			DBG("MSG_TYPE_PD recv_msg->buf_id %d \n",recv_msg.buf_id);			
		}
		else
		{
			DBG("empty\n");
		}
		
		// processs
		
		// send sink
#if 1/// HOLD TEST
		memcpy(&send_msg, &recv_msg, sizeof(MSG_BUFFER_INFO));
		send_msg.buf_id+=100;
		DBG("SendToMain\n");
		if ( SendToAdasMain(&send_msg) < 0)
		{
			DBG("message queue full\n");
		}
#endif
		
	}
}

int main(int argc, char ** argv[], char ** envp[])
{
	int i=1;
	CreatePDMsg(0);
	ResetPDMsg(0);
	

	if (s_tid_rearprocess == 0)
	{
		int ret = 0;
		ret = pthread_create(&s_tid_rearprocess, NULL, rear_process,
				(void*) &i);
		if (ret != 0) {
			DBG("rear process create error");
		} else {
			DBG("create ok\n");
		}
	}	
	
	while(i<10000000)
	{
		MSG_BUFFER_INFO send_msg={0,};
		MSG_BUFFER_INFO recv_msg={0,};



		send_msg.buf_id = i++;		
		DBG("SendToPD\n");
		if ( SendToPD(&send_msg) <0 )
		{
			DBG("message queue full\n");
		}
		// process		
		if ( ReciveMsg(MSG_TYPE_MAIN, &recv_msg) > 0 )
		{
			DBG("MSG_TYPE_MAIN recv_msg->buf_id %d \n",recv_msg.buf_id);			
		}
		else
		{
			DBG("empty\n");
		}
		sleep(1);
	}
	DestoryPDMsg(0);
}
