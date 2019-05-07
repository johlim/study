# -*- coding: cp949 -*-
#----------------------------------------------------------

# Ÿ�Ӽ��� v0.1

#

#----------------------------------------------------------

import time

from socket import *

 

PORT    = 13

HOST    = ''                                            # localhost�� �ǹ�

 

def timeserver_calculation():

    return time.asctime( time.gmtime() )

 

def daytimeserver(host=HOST, port=PORT, backlog=5):

    serversock = socket(AF_INET, SOCK_STREAM)

    serversock.bind( (host,port) )                      # Ʃ���̶�!

    serversock.listen(backlog)

    print 'Listening on Port %s (%s, %s)' % (port, 'host', backlog)

    while 1:

        conn, addr = serversock.accept()

        daytime = timeserver_calculation()

        print 'Connected for %s Client: %s, Port: %s' % (daytime, addr, port)

        conn.send(daytime)

        conn.close()

 

if __name__ == '__main__':

    daytimeserver()

