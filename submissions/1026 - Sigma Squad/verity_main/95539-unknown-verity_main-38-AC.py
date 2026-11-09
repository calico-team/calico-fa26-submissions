import sys

t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    a = input().split()
    res = ['_'] * n
    j = 0
    while True:
        g = ''.join(res[i] if res[i] != '_' else a[j] for i in range(n))
        print(g)
        sys.stdout.flush()
        r = input().strip()
        if r == "CORRECT":
            break
        for i in range(n):
            if r[i] != '_':
                res[i] = r[i]
        j += 1
