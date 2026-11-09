a=[int(i) for i in input().split()]
b=input().split()
d=0
while True:
    c=input()
    if c=='CORRECT':
        break
    else:
        print(c.replace('_', b[d]))
    d+=1
    
