# -*- coding: cp949 -*-
#----------------------------------------------------------

# 타임클라이언트 v0.1

#

#----------------------------------------------------------

import sys

from socket import *

 

BUFSIZE = 1024

HOST    = 'localhost'

#HOST   = '203.254.163.74'                              # time.kriss.re.kr

PORT    = 13                                            # daytime

 

def daytimeclient(host=HOST, port=PORT):

    clientsock = socket(AF_INET, SOCK_STREAM)

    try:

        clientsock.connect( (host, port) )

    except:

        print 'connect: Connection retused'

        return

    svr_time = clientsock.recv(BUFSIZE)

    print svr_time

    clientsock.close()

 

if __name__ == '__main__':

    daytimeclient()

