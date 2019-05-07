words=['AAAAAAAAAAB ', 
'BBBBBBBBBBB', 
'AAAAAAAAAAB', 
'BBBBBBBBBBB', 
'AAAAAAAAAAA', 
'BBBBBBBBBBB', 
'AAAAAAAAAAA', 
'CCCCCCCCCCC', 
'CCCCCCCCCCC', 
'CCCCCCCCCCA', 
'CCCCCCCCCCA'] 
count={} 
for string in words: 
    count[string] = count.get(string,0)+1 
for string in count: 
    print string,count[string] 
