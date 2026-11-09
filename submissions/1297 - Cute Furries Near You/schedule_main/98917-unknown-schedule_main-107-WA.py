for _ in range(int(input())):
    n, m, k = tuple(int(x) for x in input().split())
    p = [int(x) for x in input().split()]
    c = 0
    tc = []
    for _ in range(m):
        tb = []
        sc = []
        for i, x in enumerate(p):
            if x is None: continue
            if x == 0 or x in tc:
                tb.append(i)
        # print(f"tb is {tb}, tc is {tc}")
        tbc = tb[:]
        for x in tb:
            if x in p:
                sc.append(x + 1)
                tbc.remove(x)
        sc.extend(tbc)
        sc = sc[:k]
        tc.extend(sc)
        for x in sc:
            p[x] = None
        c += len(sc)
    print(c)