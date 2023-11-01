# -*- coding: utf-8 -*-
"""
Created on Thu Jul 16 00:22:09 2020

@author: jhlim
"""


from tkinter import *



    
root = Tk()
root.title("My Gui")
root.geometry("640x480")
root.resizable(False,False)

label1 = Label(root,text="Hi")
label1.pack()

photo = PhotoImage(file="img.png")
label2 = Button(root,image=photo)
label2.pack()

def btncmd():
    print("button clicked")
    label1.config(text="again")
    global photo2
    photo2 = PhotoImage(file="img2.png")
    label2.config(image=photo2)

btn = Button(root,text="click", command=btncmd)
btn.pack()


root.mainloop()