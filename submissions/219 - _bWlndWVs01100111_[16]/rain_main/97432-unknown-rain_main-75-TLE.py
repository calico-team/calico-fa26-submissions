super_miguel = int(input())
for i in range(super_miguel):
    total = 0
    b = input().split()
    n = int(b[0])
    k = int(b[1])
    x = []
    y = []
    h = []
    d = []
    for i in range(n):
        c = input().split()
        x.append(c[0])
        y.append(c[1])
        h.append(c[2])
        d.append(c[3])

    count = 0
    coords = {}
    for i in range(n):
        a = int(x[i] + y[i])
        coords[i] = a
    total += len(set(coords.values()))

    
    for _ in range(k-1):
        count = 0
        coords = {}
        for i in range(n):
            if d[i] ==  "N":
                y[i] = str(int(y[i]) + 1)
            else:
                x[i] = str(int(x[i]) + 1)
        for i in range(n):
            a = int(x[i] + y[i])
            coords[i] = a
        total += len(set(coords.values()))
    print(total)
            
    
        
    