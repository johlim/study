# -*- coding: utf-8 -*-
# -*- coding: cp949 -*-
from future.utils import isint


def isNumber(s):
  try:
    float(s)
    return True
  except ValueError:
    print "invaild value"
    return False

def isPositive(s):
    if int(s) >= 0 :
        return True
    else:
        print "negative value"
        return False

def calc_tip(amount,tiprate_10):
    tip = tiprate_10 / 100.0
    return round(amount * tip,2)

def con_input_value():
    while True:
        amount = raw_input()
        if isNumber(amount) and isPositive(amount):
            break
    return amount

if __name__=="__main__":
    print """-----------------------------"""
    print """ What is the bill amount ?"""

    amount=con_input_value()

    print """ What is tip rate(percent)  """
    try:
        tiprate_10 = input()
    except:
        print """ wrong input """
        print """ reenter rate """

    tip = calc_tip(float(amount),float(tiprate_10))

    print """ ***** total ***** """
    print """ tip %-0.2f $ """ % tip
    print """ sum %-0.2f $ """ % (tip + float(amount))
