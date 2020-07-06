# -*- coding: utf-8 -*-
"""
Created on Thu Jul  2 16:23:20 2020

@author: jhlim
"""
import time
import requests 
import logging

from datetime import datetime

now = datetime.now() # current date and time

year = now.strftime("%Y")
print("year:", year)

month = now.strftime("%m")
print("month:", month)

day = now.strftime("%d")
print("day:", day)

date_time = now.strftime("%Y%m%d%H%M%S")
logfilename = "munic_"+date_time+".log"

print (logfilename)

#logging.basicConfig(filename='./munic.log',level=logging.INFO)
logger = logging.getLogger()
logger.setLevel(logging.INFO)


formatter = logging.Formatter('%(asctime)s \n %(message)s')
file_handler = logging.FileHandler(logfilename)
file_handler.setFormatter(formatter)
logger.addHandler(file_handler)


#URL = 'http://192.168.225.254:8080/aimatics/gps' 

ListQuery=[]

ListQuery.append('http://192.168.225.254:8080/aimatics/gps')
ListQuery.append('http://192.168.225.254:8080/aimatics/vehicle')
ListQuery.append('http://192.168.225.254:8080/aimatics/device')
ListQuery.append('http://192.168.225.254:8080/aimatics/driving')


onGo=True
count=0
while onGo:
    for URL in ListQuery:
        
        response = requests.get(URL) 
        #response.status_code 
        #response.text
        
        logger.info(URL)
        print(URL)
        #print ("response :"+response.text )
        logger.info(response.text)
        print (response.text)
        time.sleep (0.25)
    count +=1
    if count > 10:
        onGo=False