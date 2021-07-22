all: zmq czmq

zmq:
	gcc client.c -o client -lzmq
	gcc server.c -o server -lzmq
czmq:

	gcc cmq_client.c -o cmq_server -lczmq

clean:
	rm client server cmq_server
