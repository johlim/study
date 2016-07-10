#-----------------------------------------------------------------------------
# Name:        1_13a_echo_client.py
# Purpose:     
#
# Author:      <your name>
#
# Created:     2016/06/23
# RCS-ID:      $Id: 1_13a_echo_client.py $
# Copyright:   (c) 2006
# Licence:     <your licence>
#-----------------------------------------------------------------------------
import socket
import sys
import argparse

host = 'localhost'
data_payload = 2048
backlog = 5


def echo_client(port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
 
    server_address = (host,port)
    print "Connecting to echo server on %s port %s" %server_address
    sock.connect(server_address)
    
    
    try:
        
        message = "Test message. This will echoed"
        print "Sending %s" % message
        sock.sendall(message)
        
        amount_received = 0
        amount_expected = len(message)
        while amount_received < amount_expected:
            data = sock.recv(16)
            amount_received += len(data)
            print "Received: %s" % data
    except socket.errno, e:
        print "Socket error: %s" % str(e)
    except Exception, e:
        print "Other error: %s" % str(e)
    finally:
        print "Closing connection to the server"
        sock.close()
            
    
if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Socket Client Exampole')
    parser.add_argument('--port', action="store", dest="port", type=int, required=True)
    given_args = parser.parse_args()
    port = given_args.port
    echo_client(port)
    