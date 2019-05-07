#!/usr/bin/python
# -*- coding: cp949 -*-
# SD에  테스트할 파일을 생성하기 위한 용도
import sys
import os

def make_dirs(fullpath):
    if not os.path.exists(fullpath):
        os.makedirs(fullpath)
    if not os.path.exists(fullpath):
        return 0
    return 1
targetdrv=["G:\\"]
targetdir=["REC","EVT"]
#[MOT\MOT_20130805_000018_1.avi](18371)(15)
for h in range(len(targetdir)):
    hour = "%02d" % (h)
#    updir = "G:\\REC\\2012_03_21_20_"+hour+"_38"
    updir = targetdrv[0]+targetdir[h]
    print updir
    make_dirs(updir)
    for i in range(1,51):
        s = "%02d" % i
        fname =updir+"\\"+targetdir[h]+"_20120321_20"+s+"20_1.avi"
        FH = open(fname, 'wb')
        s = FH.write("test")
        FH.truncate(1000*1024)
        print fname
        FH.close()   
        print fname
