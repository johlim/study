from Tkinter import *
import RPi.GPIO as GPIO
import time
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.OUT)

class App:
    def __init__(self, master):
        frame = Frame(master)
        frame.pack()
        self.check_Var = BooleanVar()
        check = Checkbutton(frame, text='What',
        command=self.update,
        variable=self.check_Var,onvalue=True, offvalue=False)
        check.grid(row=1)
        
    def update(self):
        print('update')
        GPIO.output(18,self.check_Var.get())

root=Tk()
root.wm_title('On Off')
app = App(root)
root.geometry("200x50+0+0")
root.mainloop()

