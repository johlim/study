# -*- coding: cp949 -*-

class Person:
    # �� �� ��, �� �ϳ�, �� �ϳ�...
    eyes = 2
    nose = 1
    mouth = 1
    ears = 2
    arms = 2
    legs = 2

    # �԰� �ڰ� �̾߱��ϰ�...
    def eat(self):
        print '���...'

    def sleep(self):
        print '����...'

    def talk(self):
        print '��������...'
        
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