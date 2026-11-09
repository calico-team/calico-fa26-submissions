for times in range(int(input())):
    a,aa=map(int, input().split())
    b=[int(i) for i in input().split()]
    c=2
    d=0 #time
    e=0 #regen time
    f=0 #index
    while True:
        d+=1
        if c < 2:
            e+=1
        if e == aa:
            c+=1
            e=0
        if f == len(b):
            print('YES')
            break
        if b[f] == d:
            if c==0:
                print('NO')
                break
            else:
                c-=1
                f+=1
        
    
    
