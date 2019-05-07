# -*- coding: cp949 -*-

class Person:
    # 눈 두 개, 코 하나, 입 하나...
    eyes = 2
    nose = 1
    mouth = 1
    ears = 2
    arms = 2
    legs = 2

    # 먹고 자고 이야기하고...
    def eat(self):
        print '얌냠...'

    def sleep(self):
        print '쿨쿨...'

    def talk(self):
        print '주절주절...'
        
class Amazon(Person):
    str = 20           
    dex = 25           
    vit = 20          
    eng = 15          

    def attack(self): 
        return 'Jab!!!'

    def exercise(self): 
        self.str +=2
        self.dex +=3
        self.vit +=1