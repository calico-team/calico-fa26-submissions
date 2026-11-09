# Source: https://usaco.guide/general/io

t = int(input())
for i in range(t):
    n, r = map(int, input().split())
    a = list(map(int, input().split()))
    ok = True
    d = 0
    for i in range(n):
        d = max(d, a[i])
        if d > a[i] + r:
            ok = False
        d += r
    print('YES' if ok else 'NO')