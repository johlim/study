# -*- coding: cp949 -*-
#Vsync 주기와 width, height로 PCLK 추산
def SensorPCLK(w,h,vsyncms):
    dw_cycle =  2.0 * w * h
# cycle : vsync ms == ? : 1000ms
# vsync ms * ? == cycle * 1000ms
# ? = (cycle * 1000ms)/vsync ms
    ret = dw_cycle * 1000 / vsyncms
    a = ret/(1000*1000)
    b = ret%(1000*1000)
    print "%0.4f Mhz" % a
    
    
if __name__ == "__main__": 
    SensorPCLK(640,480,16)
