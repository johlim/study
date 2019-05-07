# -*- coding: cp949 -*-

# fridge.py

class Fridge:
    isOpened = 0
    foods = []

    def open(self):
        self.isOpened = 1
        print '냉장고 문을 열었어요...'

    def put(self, thing):
        if self.isOpened:
            self.foods.append(thing)
            print '냉장고 속에 음식이 들어갔네...'
        else:
            print '냉장고 문이 닫혀있어서 못넣겠어요...'

    def close(self):
        self.isOpened = 0
        print '냉장고 문을 닫았어요...'

class Food:
    pass