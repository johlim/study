#python 2
import socket
import time
import traceback
import json
import datetime

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

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
#client.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
# firewall check
server = ('192.168.2.200',12345)

while 1:
    try:
        year, month,day, hour,minute,second = Time_date()
        message="%d, %d, %d, %d, %d, %d" % (year , month , day , hour , minute , second )
        client.sendto(message, server)
        print message
        time.sleep(5)
    except (KeyboardInterrupt, SystemExit):
        raise


