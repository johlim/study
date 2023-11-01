99# -*- coding: utf-8 -*-
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

#progressbar = ttk.Progressbar(root, maximum=100, mode="indeterminate")
progressbar = ttk.Progressbar(root, maximum=100, mode="determinate")
progressbar.start(10)
progressbar.pack()

def btncmd():
    progressbar.stop()
    print(progressbar.get())

btn = Button(root,text="click",command=btncmd)
btn.pack()

root.mainloop()

