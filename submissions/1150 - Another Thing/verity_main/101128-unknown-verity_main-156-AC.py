for times in range(int(input())):
    a=[int(i) for i in input().split()]
    b=input().split()
    d=0
    c='_'*a[0]
    while True:
        if c=='CORRECT':
            break
        else:
            print(c.replace('_', b[d]))
            c=input()
        d+=1
    
