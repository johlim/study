#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <stdio.h>

#define DBG(fmt,args...)	\
	{	\
	fprintf(stderr, "[%s] %d " fmt,  __FUNCTION__, __LINE__, ##args); \
	}
#define BUFSIZE 16
#define QKEY (key_t)0x0111
typedef struct _msgq_data {
	long msg_type;
	int		msg_id;			// message id
	int		size;			// contents size	
	char contents[BUFSIZE];
} BUF_MESSAGE;

enum __MSG_TYPE_BUFF__
{
	MSG_TYPE_PD		= 100,
	MSG_TYPE_MAIN = 200,
};
typedef struct
{
	int32_t buf_id;	
} MSG_BUFFER_INFO;
static key_t qid;

void CreatePDMsg(MSG_BUFFER_INFO *msg)
{

	if ((qid = msgget(QKEY, IPC_CREAT | 0666)) == -1 )
	{
		perror ("msgget create failed");	
	}

}

void DestoryPDMsg(MSG_BUFFER_INFO *msg)
{
	if(msgctl(qid,IPC_RMID,0) == -1)
	{
		perror("msgctl failed");	
	}
}

int ResetPDMsg( int msgType )
{
	BUF_MESSAGE msg;
	DBG("++ %s\n",__func__);
	while ( msgrcv( qid, (void *)&msg, sizeof(BUF_MESSAGE)-sizeof(long), msgType, IPC_NOWAIT) > 0);
	DBG("-- %s\n",__func__);
	return 1;
}

int ReciveMsg(int msgType, MSG_BUFFER_INFO * output)
{
	int len;
	long msg_type=0;
	BUF_MESSAGE recv_data;
	DBG("++ %s\n",__func__);
	DBG("recv qid %x\n", qid);
	if (len = msgrcv(qid, &recv_data, sizeof(BUF_MESSAGE), msg_type, 0) == -1)
	{
		perror("msgsnd failed");
		return 0;
	}
	else
	{
		memcpy(output, &(recv_data.contents), sizeof(MSG_BUFFER_INFO));
		DBG("(%d) (%d) (%d) \n", recv_data.msg_type , recv_data.msg_id, recv_data.size);	
		DBG("-- %s len(%d)\n",__func__, len );	
	}

	
	return 1;
}

int SendToPD(MSG_BUFFER_INFO *msg)
{
	BUF_MESSAGE snd_msg;
	int type=MSG_TYPE_PD;
	int id=0;
	int ret;
	
	DBG("++ %s\n",__func__);
	
	snd_msg.msg_type=type;		// message type
	snd_msg.msg_id=id;			// message id
	snd_msg.size = sizeof(MSG_BUFFER_INFO);

	DBG("%d\n",msg->buf_id);
	DBG("send qid %x\n", qid);	
	DBG("send size %x\n", snd_msg.size);	
	memcpy(&snd_msg.contents, msg, snd_msg.size);	
	ret = msgsnd(qid , (void *)&snd_msg, sizeof(BUF_MESSAGE), IPC_NOWAIT);
	DBG("-- %s\n",__func__);
	return ret;
}

int SendToAdasMain(MSG_BUFFER_INFO *msg)
{
	BUF_MESSAGE snd_msg;
	int type=MSG_TYPE_PD;
	int id=0;
	int ret;
	snd_msg.msg_type=type;		// message type
	snd_msg.msg_id=id;			// message id
	snd_msg.size = sizeof(MSG_BUFFER_INFO);

	memcpy(&snd_msg.contents, msg, snd_msg.size);	
	ret = msgsnd( qid, (void *)&snd_msg, sizeof(BUF_MESSAGE), IPC_NOWAIT);
	return ret;
}

