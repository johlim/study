import time
import sys

S_SCK=3.6864
CPSDVSR=2
SCR=2 

def sample():
    S_SCK_OUT = float(S_SCK) / (CPSDVSR * (1+SCR))
    print ' S_SCK_OUT = S_SCK / (CPSDVSR * (1+SCR))'
    return S_SCK_OUT

 

def calc(s_sck=S_SCK, cpsdvsr=CPSDVSR, scr=SCR):
    print 'input  clock %s ps %s, scr %s)' % (s_sck, cpsdvsr, scr)
    s_sck_out = float(s_sck) / (cpsdvsr * (1+scr))
    return s_sck_out
 
def main():
    if len(sys.argv)<2:
        sample()
        sys.exit(1) 
    calc() 
    return None 
  
if __name__=='__main__':
  main()
  sys.exit(0)