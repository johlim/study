import sys

from PyQt4.QtGui import *
from PyQt4.QtCore import *

class SimpleWindow(QWidget):
    def __init__(self):
        QWidget.__init__(self) 

        self.setWindowTitle("Power off Log Counter")
        self.setGeometry(300, 500, 300, 400)

def countPowerOnOffLog():
    import re
    imagePattern = "[02/17 12:43:52] POWER: ON"
    m = re.search('\[02/17 (.*?)\] POWER: ON', imagePattern)
    #print m.group(1)
    imagePattern = "[02/17 12:43:52] POWER: ON"
    m = re.search('\[02/17 (..):(..):(..)\] POWER: ON', imagePattern)
    #print m.group(1)+ m.group(2)+ m.group(3)


    fname = "E:\\SYSTEM_ONOFF_LOG_5.txt"    
    fp = open(fname)

    prem=0
    curm=0
    count=0
    while fp:
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


if __name__ == "__main__":
    app = QApplication(sys.argv)
    myWindow = SimpleWindow()
    myWindow.show()

    countPowerOnOffLog()

    app.exec_()