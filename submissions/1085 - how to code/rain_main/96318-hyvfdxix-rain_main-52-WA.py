
def bs(ls, n, side):
    l = 0
    h = len(ls)
    pvlh = (l,h)
    while l<h:
        m = (l+h)//2
        if ls[m] > n:
            h = m
        elif ls[m] <= n:
            l = m
        if (l,h)==pvlh:
            break
        pvlh = (l,h)
    if side:
        return h
    return l

for _ in range(int(input())):
    N, K = map(int, input().split())
    data = [input().split() for _ in range(N)]
    s1 = {}
    s2 = {}
    k1 = []
    k2 = []
    for x,y,_,d in data:
        x = int(x)
        y = int(y)
        s = s2
        k = k2
        if d=='N':
            s = s1
            k = k1
        if x+y in s:
            s[x+y].add(x)
        else:
            s[x+y] = {x}
            k.append(x+y)
    for k in k2:
        s2[k] = sorted(s2[k])
    co = set(k1).intersection(set(k2))
    tot = 0
    for k in k1:
        tot += len(s1[k])*K
        if k in co:
            for x1 in s1[k]:
                lo = bs(s2[k], x1-K, False)
                hi = bs(s2[k], x1+K-1, True)
                if s2[k][lo] >= x1-K+1:
                    lo -= 1
                tot -= (hi - lo - 1)
    for k in k2:
        tot += len(s2[k])*K
    print(tot)

