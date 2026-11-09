for times in range(int(input())):
    a=input().split()
    b=input().split()
    c=['n' for i in range(int(a[0]))]
    cc=c[0:]
    d=0
    f=True
    g=int(a[1])
    h=len(b)
    for i in range(len(b)):
        if int(b[i]) == 0:
            d+=1
            c[i] = 'y'
    e=int(a[2])
    while f:
        if h > 0:
            j=len(b)-h
            if cc[int(b[j])-1] == 'y' and cc[j] != 'y' and e > 0:
                d+=1
                e-=1
                c[j] = 'y'
            h-=1
        else:
            h=len(b)
            g-=1
            e=int(a[2])
            cc=c[0:]
        if g == 0:
            f=False
                    
    print(d)
