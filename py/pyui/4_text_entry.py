# -*- coding: utf-8 -*-
"""
Created on Thu Jul 16 00:30:24 2020

@author: jhlim
"""
from tkinter import *

root = Tk()
root.title("My Gui")
root.geometry("640x480")
root.resizable(False,False)

txt = Text(root,width=30,height=5)
txt.pack()
txt.insert(END,"Enter char") # 글자삽

e = Entry(root,width=30) #one line input
e.pack()
e.insert(0,"write one line")

def btncmd():
    print(txt.get("1.0",END)) # txt에서 col 1 row 0 에서 끝까지 
    print(e.get())
    # 삭제
    txt.delete("1.0",END)
    e.delete(0,END)

btn = Button(root,text="click",command=btncmd)
btn.pack()

root.mainloop()

