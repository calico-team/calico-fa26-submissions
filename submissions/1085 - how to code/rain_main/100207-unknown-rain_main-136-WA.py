
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
    s = {}
    for x,y,_,d in data:
        x = int(x)
        y = int(y)
        v = (d=='N', x)
        if x+y in s:
            s[x+y].add(v)
        else:
            s[x+y] = {v}
    keys = s.keys()
    for k in keys:
        s[k] = sorted(s[k])
    tot = 0
    for k in keys:
        tot += len(s[k])*K
        if s[k][0][0] != s[k][-1][0]:
            brk = bs(s[k], (True, -1), True)
            left = [v for _,v in s[k][:brk]]
            right = [v for _,v in s[k][brk:]]
            for x in left:
                lo = bs(right, x, False)
                hi = bs(right, x+K-1, True)
                if right[lo] >= x-K+1:
                    lo -= 1
                tot -= (hi - lo - 1)
    print(tot)


