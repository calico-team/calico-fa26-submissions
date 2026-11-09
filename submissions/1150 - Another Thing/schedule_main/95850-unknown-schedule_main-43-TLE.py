for times in range(int(input())):
    a=input().split()
    b=input().split()
    c=['n' for i in range(int(a[0]))]
    cc=c[0:]
    d=0
    for i in range(len(b)):
        if int(b[i]) == 0:
            d+=1
            c[i] = 'y'
    for i in range(int(a[1])):
        e=int(a[2])
        for j in range(len(b)):
            if cc[int(b[j])-1] == 'y' and cc[j] != 'y':
                if e > 0:
                    d+=1
                    e-=1
                    c[j] = 'y'
        cc=c[0:]
                    
    print(d)
