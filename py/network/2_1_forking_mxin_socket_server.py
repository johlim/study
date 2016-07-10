import os
import socket
import threading
import SocketServer

SERVER_HOST='localhost'
SERVER_PORT=0 #dynamic
BUF_SIZE=1024
ECHO_MSG = 'Hello echo server!'

class ForkedClient():
    def __init__(self, ip, port):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((ip, port))

    def run(self):
        current_process_id = os.getpid()
        print 'PID %s Sending echo message to the server : %s' % (current_process_id, ECHO_MSG)
        send_data_length = self.sock.send(ECHO_MSG)
        print 'Client Sent : %d char , so far ..' % send_data_length
        response = self.sock.recv(BUF_SIZE)
        print 'PID : %s received %s ' % (current_process_id, response[5:])

    def shutdown(self):
        self.sock.close()
    

class ForkingServerRequestHandler(SocketServer.BaseRequestHandler):
    def handle(self):
        data =self.request.recv(BUF_SIZE)
        current_process_id = os.getpid()
        response = '%s: %s' % (current_process_id, data)
        print "Server sending response [current_process_id: data] = [%s]" %response
        self.request.send(response)
        return

class ForkingServer(SocketServer.ForkingMixIn, SocketServer.TCPServer,):
    """Nothing"""
    pass

def main():
    server = ForkingServer((SERVER_HOST, SERVER_PORT), ForkingServerRequestHandler)
    ip, port = server.server_address
    server_thread = threading.Thread(target=server.serve_forever)
    server_thread.setDaemon(True)
    server_thread.start()
    print 'Server loop running PID : %s' % os.getpid()

    client1 = ForkedClient(ip, port)
    client1.run()
    
    client2 = ForkedClient(ip, port)
    client2.run()
    
    server.shutdown()
    client1.shutdown()
    client2.shutdown()
    server.socket.close()
    
if __name__ == '__main__':
   main()
    
