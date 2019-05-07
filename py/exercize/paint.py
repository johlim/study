# -*- coding: cp949 -*- 
# filename : paint.pyw 
# ������ �̹��� ���μ��� ���α׷� 

from Tkinter import * 
import tkFileDialog, tkMessageBox 
import Image, ImageTk 
from numpy import *
import os

class App: 
        def __init__(self): 
                self.root=Tk() 
                self.menu=Menu(self.root) 
                self.root.config(menu=self.menu); 
                self.label=Label(self.root, text="", width=50, height=20) 
                self.label.pack() 

                self.filemenu=Menu(self.menu) 
                self.menu.add_cascade(label=u"����", menu=self.filemenu)
                self.filemenu.add_command(label=u"����", command=self.Create, accelerator="Ctrl+N")
                self.filemenu.add_command(label=u"����", command=self.OpenFile, accelerator="Ctrl+O") 
                self.filemenu.add_separator() 
                self.filemenu.add_command(label=u"����", command=self.Quit, accelerator="Ctrl+Q") 

                self.editmenu=Menu(self.menu) 
                self.menu.add_cascade(label=u"����", menu=self.editmenu) 
                self.editmenu.add_command(label=u"�� ����", command=self.Inverse, accelerator="Ctrl+I") 

                self.root.bind("<Control-o>",self.OpenFile) 
                self.root.bind("<Control-q>",self.Quit) 
                self.root.bind("<Control-i>",self.Inverse) 
                self.root.bind("<Escape>",self.Quit)
                self.Create()
                self.root.mainloop() 

        def OpenFile(self,event=None): 
                self.filename=tkFileDialog.askopenfilename() 
                if(self.filename==""): 
                        return 
                try: 
                        self.image=Image.open(self.filename) 
                except: 
                        tkMessageBox.showerror(u"���� !","���� ���⿡ �����߽��ϴ�") 
                else: 
                        self.pixel=self.image.load() 
                        self.label.image=ImageTk.PhotoImage(self.image) 
                        Label.__init__(self.label,self.root,image=self.label.image,bd=0) 
                        self.label.pack() 

        def Quit(self,event=None): 
                self.root.destroy() 

        def Inverse(self,event=None): 
                if(self.filename==""): 
                        return 
                self.image=Image.eval(self.image,lambda x:256-x) 
                self.label.image=ImageTk.PhotoImage(self.image) 
                Label.__init__(self.label,self.root,image=self.label.image,bd=0) 
                self.label.pack()
                
        def readmyfile(filename,bytes=4,endian='<h'):
                totalBytes = os.path.getsize(filename)
                values = empty(totalBytes/bytes)
                with open(filename,'rb') as f:
                    for i in range(len(values)):
                        values[i] = struct.unpack(endian,f.read(bytes))[0]
                return values
            
        def Create(self,event=None):
                self.filename=tkFileDialog.askopenfilename() 
                if(self.filename==""): 
                        return 
                try: 
                        self.readmyfile(self.filename) 
                except: 
                        tkMessageBox.showerror(u"���� !","���� ���⿡ �����߽��ϴ�") 
                else: 
                         return
App();
