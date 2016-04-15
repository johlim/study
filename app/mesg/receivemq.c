#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 16
#define QKEY (key_t)0x0111

struct msgq_data {
	long type;
	char text[BUFSIZE];
};

struct msgq_data recv_data;

int main(int argc, char ** argv[], char ** envp[])
{
	int qid , len;
	char buf[BUFSIZE];

	if ((qid = msgget(QKEY, IPC_CREAT | 0666)) == -1 )
	{
		perror ("msgget failed");
		exit(1);
	}

	if (len = msgrcv(qid, &recv_data, BUFSIZE, 0, 0) == -1)
	{
		perror("msgsnd failed");
		exit(1);
	}

	printf("received from message queue : %s \n", recv_data.text);

	if(msgctl(qid,IPC_RMID,0) == -1)
	{
		perror("msgctl failed");
		exit(1);
	}

}
