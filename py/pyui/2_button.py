# -*- coding: utf-8 -*-
"""
Created on Wed Jul 15 08:15:36 2020

@author: jhlim
"""


from tkinter import *


def btncmd():
    print("button clicked")
    
root = Tk()
root.title("My Gui")
root.geometry("640x480")
root.resizable(False,False)

btn1 = Button(root,text="Button1자동조절 ")
btn1.pack()

btn2 = Button(root, padx=5, pady=10, text="Button2")
btn2.pack()

btn3 = Button(root, padx=10, pady=5, text="Button3여백")
btn3.pack()

btn4 = Button(root, width=10, height=5, text="고정크기버")
btn4.pack()

btn5 = Button(root, fg="red", bg="black", text="ColorButton")
btn5.pack()


photo = PhotoImage(file="img.png")
btn6 = Button(root,image=photo)
btn6.pack()

btn7 = Button(root, text="Cmd Button", command=btncmd)
btn7.pack()

root.mainloop()