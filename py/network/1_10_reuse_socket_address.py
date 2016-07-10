#-----------------------------------------------------------------------------
# Name:        1_10_reuse_socket_address.py
# Purpose:     
#
#
#
# Author:      <your name>
#
# Created:     2016/06/22
# RCS-ID:      $Id: 1_10_reuse_socket_address.py $
# Copyright:   (c) 2006
# Licence:     <your licence>
#-----------------------------------------------------------------------------
import socket
import sys

def reuse_socket_addr():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    old_state = sock.getsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR)
    print "Old sock sate : %s" % old_state
    
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
    new_state = sock.getsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR)
    print "New sock sate : %s" % new_state
    
    local_port = 8282
    
    srv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#socket.error: [Errno 98] Address already in use
    srv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
    srv.bind(('',local_port))
    
    srv.listen(1)
    
    print ("Listening on port: %s " %local_port)
    while True:
        try:
            connection, addr = srv.accept()
            print 'Connected by %s:%s' % (addr[0], addr[1])
        except KeyboardInterrupt:
            break
        except socket.error, msg:
            print '%s' % (msg,)

if __name__ == '__main__':
    reuse_socket_addr()
    
    