cases = int(input())
for i in range(cases):
    n, k = map(int, input().split())
    drones = []
    groups = {}
    for j in range(n):
        inp = input().split()
        x = int(inp[0])
        y = int(inp[1])
        z = int(inp[2])
        d = inp[3]
        drones.append([x, y, z, d])
        s = x + y
        if s not in groups:
            groups[s] = []
        groups[s].append([x, y, z, d, j])
    dm = []
    for _ in range(n):
        dm.append(set())
    for s in groups:
        l = groups[s]
        m = len(l)
        for ind in range(m):
            a = l[ind][0]
            b = l[ind][1]
            c = l[ind][2]
            d = l[ind][3]
            e = l[ind][4]
            for j in range(m):
                if ind == j:
                    continue
                xj = l[j][0]
                yj = l[j][1]
                zj = l[j][2]
                dj = l[j][3]
                idx_j = l[j][4]
                if zj > c and d != dj:
                    if d == "E":
                        t = xj - a
                    else:
                        t = a - xj
                    if 0 <= t and t < k:
                        dm[e].add(t)
                        
    rain = 0
    for j in range(n):
        rain += (k - len(dm[j]))
    print(rain)