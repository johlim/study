# List
fruit =["사과","바나나","사과","딸기","키위","복숭아"]
# Dictionary
d = {}

for f in fruit:
    if f in d:
        d[f] = d[f]+1
    else:
        d[f] = 1
    print (d)

print ("**",d)