import socket

def find_service_name ():
    protocolname = 'tcp'
    for port in [80,25]:
        print "Port : %s => service name: %s" %(port, socket.getservbyport(port, protocolname))

    port = 53
    protocolname = 'udp'
    print "Port: %s => service name : %s" %(port, socket.getservbyport(port, protocolname))

if __name__ == '__main__':
    find_service_name()

