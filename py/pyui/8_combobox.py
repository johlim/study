# -*- coding: utf-8 -*-
"""
Created on Thu Jul 16 08:56:12 2020

@author: jhlim
"""
import tkinter.ttk# as ttk
from tkinter import *

root = Tk()
root.title("My Gui")
root.geometry("640x480")
root.resizable(False,False)

values = [str(i) + "일" for i in range(1,32)] # string list
combobox = tkinter.ttk.Combobox(root,height=5,values=values)
combobox.pack()
combobox.set("Card payment date ")

readonly_combobox = ttk.Combobox(root, height=10, values=values, state="readonly")
readonly_combobox.current(0)
readonly_combobox.pack()

def btncmd():
    print(combobox.get())
    print(readonly_combobox.get())

btn = Button(root,text="click",command=btncmd)
btn.pack()

root.mainloop()

