def tipinput(amount):
    print """ What is tip rate(percent)  """
    try:
        tiprate_10 = input()
    except:
        print """ wrong input """
        print """ reenter rate """
    tip = tiprate_10 / 100.0    
    return round(amount * tip,2)

print """-----------------------------"""
print """ What is the bill amount ?"""
amount = input()
tip = tipinput(amount)
print """ ***** total ***** """
print """ tip %0.2f $ """ % tip
print """ sum %0.2f $ """ % (tip + amount)
