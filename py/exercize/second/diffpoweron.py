# filename : diffpoweron.pyw 
# 간단한 log 검사

from Tkinter import * 
import tkFileDialog, tkMessageBox 
import os
import re

class App: 
        def __init__(self): 
                self.root=Tk() 
                self.menu=Menu(self.root) 
                self.root.config(menu=self.menu); 
                self.label=Label(self.root, text="", width=50, height=20) 
                self.label.pack() 

                self.filemenu=Menu(self.menu) 
                self.menu.add_cascade(label=u"파일", menu=self.filemenu)
                self.filemenu.add_command(label=u"열기", command=self.OpenFile, accelerator="Ctrl+O") 
                self.filemenu.add_separator() 
                self.filemenu.add_command(label=u"종료", command=self.Quit, accelerator="Ctrl+Q") 

                self.editmenu=Menu(self.menu) 
                self.menu.add_cascade(label=u"Action", menu=self.editmenu) 
                self.editmenu.add_command(label=u"Count", command=self.readmyfile, accelerator="Ctrl+I") 

                self.root.bind("<Control-o>",self.OpenFile) 
                self.root.bind("<Control-q>",self.Quit) 
                self.root.bind("<Control-i>",self.readmyfile) 
                self.root.bind("<Escape>",self.Quit)
                self.Create()
                self.root.mainloop() 

        def OpenFile(self,event=None): 
                self.filename=tkFileDialog.askopenfilename() 
                if(self.filename==""): 
                        return 
                try: 
                        self.readmyfile(self.filename) 
                except: 
                        #tkMessageBox.showerror(u"오류 !","파일 열기에 실패했습니다")
                        tkMessageBox.showerror(u"ERROR !","open error") 
                else: 
                        self.label.pack() 

        def Quit(self,event=None): 
                self.root.destroy() 
                
        def readmyfile(self,event=None):
                print self.filename
                totalBytes = os.path.getsize(self.filename)               
   
   
                prem=0
                curm=0
                count=0
                fp = open(self.filename)
                while 1:
                        line = fp.readline()
                        if not line:
                                break                        
                        n = re.search('\[(..)/(..) (..):(..):(..)\] POWER: ON', line)
                        if n:
                                month = int(n.group(1))
                                day = int(n.group(2))     
                                curh = int(n.group(3))        
                                curm = int(n.group(4))
                                
                        if (prem):            
                                if (curm-prem)>9:
                                        print str(premonth)+"/"+str(preday)+" "+str(preh)+":"+str(prem)+" <-> "
                                        print str(month)+"/"+str(day)+" "+str(curh)+":"+str(curm)
                                        print " diff " +str(curm-prem+(60*(curh - preh)))
                                        count=count+1
                        prem = curm
                        preh = curh
                        premonth = month
                        preday = day

                print("10minute over is (" + str(count)  + ") happen! ")
                #close(self.filename)
                return
            
        def Create(self,event=None):
                self.filename=tkFileDialog.askopenfilename() 
                if(self.filename==""): 
                        return 
                try:
                        self.readmyfile(self.filename) 
                except: 
                        tkMessageBox.showerror(u"ERROR !","Create Error") 
                else: 
                         return
App();
