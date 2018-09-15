import socket, traceback

def Time_date():           
     utcnow = datetime.datetime.utcnow()
     time_gap = datetime.timedelta(hours=9)
     kor_time = utcnow + time_gap
     year = kor_time.year
     month= kor_time.month
     day = kor_time.day
     hour = kor_time.hour
     minute=kor_time.minute
     second = kor_time.second
     return year, month,day, hour,minute,second

backlog = 5
size = 1024
server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server.bind(('0.0.0.0',12345))

while 1:
    try:
        message, address = server.recvfrom(1024)
        year, month,day, hour,minute,second = message.split(',')
        msg = "Got data from" + str( address ) 
        print (msg )
        print (year, month,day, hour,minute,second)
        #s.sendto(message, address)
    except (KeyboardInterrupt, SystemExit):
        raise
    except:
        traceback.print_exec()
