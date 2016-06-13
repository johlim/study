#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

int main(int argc, char *argv[])
{
	/* variable */
	int listenfd = 0, connfd = 0;
	struct sockaddr_in serv_addr; 

	char sendBuff[1025];
	char recvBuff[1025];
	time_t ticks; 

	int rval;

	/* create scoket */
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serv_addr, '0', sizeof(serv_addr));
	memset(sendBuff, '0', sizeof(sendBuff)); 

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(5000); 

	/* call bind */
	if (bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)))
	{
		perror("bind faild");
		exit(1);
	}

	/* listen for 10 connection */
	listen(listenfd, 10); 

	while(1)
	{
		connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 

		if (connfd == -1)
		{
			perror("accept failed");
			close(connfd);
		}
		else
		{
#if 0 // Write 
			ticks = time(NULL);
			snprintf(sendBuff, sizeof(sendBuff), "Hi Now is %.24s\r\n", ctime(&ticks));
			write(connfd, sendBuff, strlen(sendBuff)); 
#endif
			memset(recvBuff,0,sizeof(recvBuff));
			if ((rval = recv(connfd, recvBuff, sizeof(recvBuff), 0)) <0)
				perror("reading stream message error");
			else
			{
				// ok 
				fprintf(stderr, "%s", recvBuff);
			}
			close(connfd);
		}
		sleep(1);
	}
}
