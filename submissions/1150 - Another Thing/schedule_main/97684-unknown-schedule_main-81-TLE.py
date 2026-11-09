for times in range(int(input())):
    a,aa,aaa=map(int, input().split())
    b=[int(i) for i in input().split()]
    c=['n' for i in range(a)]
    cc=c[0:]
    d=0
    f=True
    g=aa
    h=len(b)
    for i in range(len(b)):
        if b[i] == 0:
            d+=1
            c[i] = 'y'
    e=aaa
    while f:
        if h > 0:
            j=len(b)-h
            if cc[b[j]-1] == 'y' and cc[j] != 'y' and e > 0:
                d+=1
                e-=1
                c[j] = 'y'
            h-=1
        else:
            if cc == c:
                break
            h=len(b)
            g-=1
            e=aaa
            cc=c[0:]
        if g == 0:
            f=False               
    print(d)
