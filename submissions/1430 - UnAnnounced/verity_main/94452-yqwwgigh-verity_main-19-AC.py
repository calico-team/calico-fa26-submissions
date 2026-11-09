# Source: https://usaco.guide/general/io
import sys

t = int(input())
for i in range(t):
    n, k = map(int, input().split())
    a = list(input().split())
    ans = ['_'] * n
    ok = False
    for i in range(k):
        print(a[i] * n)
        sys.stdout.flush()
        x = input()
        if x == 'CORRECT':
            ok = True
            break
        for j in range(n):
            if x[j] != '_':
                ans[j] = x[j]
    if not ok:
        print(''.join(ans))
        x = input()