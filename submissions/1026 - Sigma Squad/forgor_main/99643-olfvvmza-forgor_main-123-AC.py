import sys
from collections import deque


def amnesiac():
    data = read_your_input()
    phase = data[0]
    n = int(data[1])

    if phase == "FIRST":
        adj = [[] for _ in range(n + 1)]
        p = 2
        for _ in range(n - 1):
            u, v = int(data[p]), int(data[p + 1])
            p += 2
            adj[u].append(v)
            adj[v].append(u)

        par = [0] * (n + 1)
        seen = [False] * (n + 1)
        seen[1] = True
        dq = deque([1])
        while dq:
            u = dq.popleft()
            for v in adj[u]:
                if not seen[v]:
                    seen[v] = True
                    par[v] = u
                    dq.append(v)

        a = [0] * (n + 1)
        for i in range(2, n + 1):
            a[i] = par[i]
        a[1] = (-sum(a[2:])) % (n + 1)
        print(" ".join(map(str, a[1:])))
    else:
        a = [0] + [int(x) for x in data[2:2 + n]]
        miss = a.index(-1, 1)
        if miss != 1:
            s = sum(a[i] for i in range(1, n + 1) if i != miss)
            a[miss] = (-s) % (n + 1)
        out = []
        for i in range(2, n + 1):
            out.append(f"{i} {a[i]}")
        print("\n".join(out))


def read_your_input():
    return sys.stdin.read().split()


amnesiac()
