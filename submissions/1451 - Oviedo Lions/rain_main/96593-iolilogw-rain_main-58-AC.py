from collections import defaultdict
from bisect import bisect_left

for i in range(int(input())):
    n, k = map(int, input().split())

    e = []
    a = defaultdict(list)

    for i in range(n):
        x, y, z, d = input().split()
        x, y = int(x), int(y)
        s = x + y
        if d == "N":
            a[s].append(x)
        else:
            e.append((s, x))
    for v in a.values():
        v.sort()
    ans = n * k
    for s, x in e:
        v = a[s]

        ans -= bisect_left(v, x + k)-bisect_left(v, x)
    print(ans)
