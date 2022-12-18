# -*- coding: utf-8 -*-
"""
Created on Thu Jul 16 00:41:26 2020

@author: jhlim
"""
from tkinter import *

root = Tk()
root.title("My Gui")
root.geometry("640x480")
root.resizable(False,False)

listbox = Listbox(root,selectmode="extended", height=3)
listbox.insert(0,"사과")
listbox.insert(1,"딸기")
listbox.insert(2,"바나나")
listbox.insert(END,"수박")
listbox.insert(END,"포도")
listbox.pack()

def btncmd():
    #listbox.delete(0)
    #print("list size", listbox.size(),"exist")
    #print("",listbox.get(0,2))
    print ( listbox.curselection())
    print(listbox.get(listbox.curselection()))
    
btn = Button(root,text="click",command=btncmd)
btn.pack()

root.mainloop()