# -*- coding: utf-8 -*-
"""
Created on Thu Jul 16 00:56:40 2020

@author: jhlim
"""
from tkinter import *

root = Tk()
root.title("My Gui")
root.geometry("640x480")
root.resizable(False,False)

label1 = Label(root, text="select please").pack()


check_var = IntVar()
chkbox = Checkbutton(root,text="today no see",variable=check_var)
#chkbox.select()
chkbox.pack()


check_var2 = IntVar()
chkbox2 = Checkbutton(root,text="today no see",variable=check_var2)
#chkbox2.select()
chkbox2.pack()

def btncmd():
    print(check_var.get()) # 0 no 1 : yes
    #chkbox.deselect()
    print(check_var2.get()) # 0 no 1 : yes
    
btn = Button(root,text="click",command=btncmd)
btn.pack()

root.mainloop()

