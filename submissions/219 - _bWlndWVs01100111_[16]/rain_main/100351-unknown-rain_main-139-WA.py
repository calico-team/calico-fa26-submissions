super_miguel = int(input())
for i in range(super_miguel):
    b = input().split()
    n = int(b[0])
    k = int(b[1])
    total = n*k
    xn = []
    yn = []
    xe = []
    ye = []
    for i in range(n):
        c = input().split()
        if c[3] == 'N':
            xn.append(int(c[0]))
            yn.append(int(c[1]))
        else:
            xe.append(int(c[0]))
            ye.append(int(c[1]))
    for x in range(len(xn)):
        for i in range(len(xe)):
            if xn[x] - xe[i] > 0:
                if xn[x]-xe[i] == ye[i]-yn[x]:
                    if xn[x]-xe[i] <= k-1:
                        total -= 1
                else: break
            else: break
                        

    print(total)
            
    
    