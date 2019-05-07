# -*- coding: cp949 -*-
from Tkinter import * 
import tkFileDialog, tkMessageBox 
import sys

args = sys.argv[1:]
print args
if (args[0]==""):
    exit
try:    
    f = open(args[0],'r')
except:
    tkMessageBox.showerror("Err"," open fail") 
else:
    f.seek(0)
    lines = f.readlines()
    for line in lines:
#        print line
        print "\t{"+line[5:19]+"},"+line[20:100]
    f.close()
    
