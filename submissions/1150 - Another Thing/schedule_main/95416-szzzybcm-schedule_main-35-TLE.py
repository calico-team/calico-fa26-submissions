for times in range(int(input())):
    a=[int(i) for i in input().split()]
    b=[int(i) for i in input().split()]
    c=['n' for i in range(a[0])]
    cc=c[0:]
    d=0
    for i in range(len(b)):
        if b[i] == 0:
            d+=1
            c[i] = 'y'
    for i in range(a[1]):
        e=a[2]
        for j in range(len(b)):
            if cc[b[j]-1] == 'y' and c[j] != 'y':
                if e > 0:
                    d+=1
                    e-=1
                    c[j] = 'y'
        cc=c[0:]
                    
    print(d)
