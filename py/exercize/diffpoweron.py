import re
imagePattern = "[02/17 12:43:52] POWER: ON"
m = re.search('\[02/17 (.*?)\] POWER: ON', imagePattern)
#print m.group(1)
imagePattern = "[02/17 12:43:52] POWER: ON"
m = re.search('\[02/17 (..):(..):(..)\] POWER: ON', imagePattern)
#print m.group(1)+ m.group(2)+ m.group(3)

if __name__ == '__main__':
    fname = "E:\\SYSTEM_ONOFF_LOG_5.txt"    
    #fp = open('./test.txt')
    #fp = open('./SYSTEM_ONOFF_LOG_1.txt')
    fp = open(fname)
    
    


prem=0
curm=0
count=0
while 1:
    line = fp.readline()
    if not line:
        break
    m = re.search('\[02/.. (..):(..):(..)\] POWER: ON', line)
    n = re.search('\[(..)/(..) (..):(..):(..)\] POWER: ON', line)
    if n:
        month = int(n.group(1))
        day = int(n.group(2))     
        
                
    if m:        
        curm = int(m.group(2))
        curh = int(m.group(1))        
        if (prem):            
            if (curm-prem)>9:
                print str(month)+"/"+str(day)+" "+str(preh)+":"+str(prem)+" " + m.group(2) 
                print " diff " +str(curm-prem+(60*(curh - preh)))
                count=count+1
        prem = curm
        preh = curh
    
	

print("10minute over is (" + str(count)  + ") happen! ")
