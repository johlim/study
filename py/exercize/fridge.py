# -*- coding: cp949 -*-

# fridge.py

class Fridge:
    isOpened = 0
    foods = []

    def open(self):
        self.isOpened = 1
        print '����� ���� �������...'

    def put(self, thing):
        if self.isOpened:
            self.foods.append(thing)
            print '����� �ӿ� ������ ����...'
        else:
            print '����� ���� �����־ ���ְھ��...'

    def close(self):
        self.isOpened = 0
        print '����� ���� �ݾҾ��...'

class Food:
    pass