# -*- coding: utf-8 -*-
"""
Created on Thu Jul  2 16:23:20 2020

@author: jhlim
"""
import time
import requests 
import logging

#logging.basicConfig(filename='./munic.log',level=logging.INFO)
logger = logging.getLogger()
logger.setLevel(logging.INFO)

formatter = logging.Formatter('%(asctime)s \n %(message)s')
file_handler = logging.FileHandler('./munic.log')
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