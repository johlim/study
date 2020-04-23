TARGET=

all: server client

server:
	${CC} -g sum_server.c -o sum_server

client:
	${CC} -g sum_client.c  -o sum_client

clean:
	rm -rf *.o
	rm -rf sum_server sum_client
