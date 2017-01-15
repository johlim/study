from time import sleep
import sys, os
import datetime
import time

relay1=1
turnon=0
turnoff=1
print ("turn off")

sleep(1); print ("loop")
pwr_on = 0
pwr_off = 0

while True:
	now =time.localtime()
	s = "%04d-%02d-%02d %02d:%02d:%02d" % (now.tm_year, now.tm_mon, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec)
	print("\n %s power on %d power off %d" % (s, pwr_on , pwr_off))
	pwr_on=pwr_on+1
	ontime =0
	while(ontime< 120 ):                
		sys.stdout.write("%d " % ontime)
		sleep(1)
		ontime=ontime+1

	pwr_off=pwr_off+1
	sleep(20)