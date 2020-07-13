class Person:
    def __init__(self,name):
        self.name = name
    
    def say_hello(self,to_name):
        print("Hello "+to_name + "! I am "+ self.name)

class Police(Person):
    def arress(self,to_arrest):
        print(to_arrest+" You are under arrest")

wonie = Police("워니")
hslim = Person("현서")
hhlim = Person("현호")

wonie.say_hello("종환")
wonie.arress("종환")
hslim.say_hello("종환")
hhlim.say_hello("종환")