# -*- coding: utf-8 -*-
"""
Created on Thu Jul 16 01:01:59 2020

@author: jhlim
"""

from tkinter import *

root = Tk()
root.title("My Gui")
root.geometry("640x480")
root.resizable(False,False)

label1 = Label(root, text="select food").pack()

menu_var = IntVar()
btn_menu1 = Radiobutton(root, text="Ham burger",value=1,variable=menu_var)
btn_menu1.select()
btn_menu2 = Radiobutton(root, text="Cheese burger",value=2,variable=menu_var)
btn_menu3 = Radiobutton(root, text="Chikeen burger",value=3,variable=menu_var)

btn_menu1.pack()
btn_menu2.pack()
btn_menu3.pack()



drink_var=StringVar()
btn_drink1 = Radiobutton(root,text="cola", value="cola",variable=drink_var)
btn_drink1.select()
btn_drink2 = Radiobutton(root,text="cider", value="cider",variable=drink_var)

label1 = Label(root, text="select drink").pack()

btn_drink1.pack()
btn_drink2.pack()

def btncmd():
    print(menu_var.get())
    print(drink_var.get())

btn = Button(root,text="click",command=btncmd)
btn.pack()

root.mainloop()
