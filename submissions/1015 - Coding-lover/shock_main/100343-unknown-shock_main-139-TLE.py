from math import isqrt
t = int(input())
for _ in range(t):
    n, m, q = map(int, input().split())
    qs = []
    i = 0
    while i < q:
        qs.append(list(map(int, input().split())))
        i = i + 1
    ans = [[0] * m for _ in range(n)]
    nxt = []
    r = 0
    while r < n:
        nxt.append(list(range(m + 1)))
        r = r + 1
    rem = [m] * n
    rpar = list(range(n + 1))
    def find_c(r, x):
        p = nxt[r]
        while p[x] != x:
            p[x] = p[p[x]]
            x = p[x]
        return x
    def find_r(x):
        while rpar[x] != x:
            rpar[x] = rpar[rpar[x]]
            x = rpar[x]
        return x
    qi = q - 1
    while qi >= 0:
        ri, ci, pi = qs[qi]
        r = find_r(ri - pi)
        r2 = ri + pi
        while r <= r2:
            dr = r - ri
            if dr < 0:
                dr = -dr
            dx = isqrt(pi * pi - dr * dr)
            left = ci - dx
            right = ci + dx
            c = find_c(r, left)
            while c <= right:
                ans[r][c] = pi * pi - dr * dr - (c - ci) * (c - ci) + 1
                nxt[r][c] = find_c(r, c + 1)
                rem[r] = rem[r] - 1
                if rem[r] == 0:
                    rpar[r] = find_r(r + 1)
                    break
                c = nxt[r][c]
            r = find_r(r + 1)
        qi = qi - 1
    for row in ans:
        print(" ".join(map(str, row)))
