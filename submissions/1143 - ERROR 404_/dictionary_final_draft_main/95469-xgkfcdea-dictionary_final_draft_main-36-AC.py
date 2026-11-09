import sys
from collections import deque
from array import array

input = sys.stdin.readline

class Trie:
    def __init__(self):
        self.l = array('i', [0])
        self.r = array('i', [0])
        self.c = array('i', [0])

    def add(self, x, delta):
        node = 0
        self.c[node] += delta

        for b in range(29, -1, -1):
            bit = (x >> b) & 1

            if bit:
                nxt = self.r[node]
                if nxt == 0:
                    nxt = len(self.c)
                    self.r[node] = nxt
                    self.l.append(0)
                    self.r.append(0)
                    self.c.append(0)
            else:
                nxt = self.l[node]
                if nxt == 0:
                    nxt = len(self.c)
                    self.l[node] = nxt
                    self.l.append(0)
                    self.r.append(0)
                    self.c.append(0)

            node = nxt
            self.c[node] += delta

    def query(self, x):
        node = 0
        ans = 0

        for b in range(29, -1, -1):
            bit = (x >> b) & 1

            if bit:
                a = self.l[node]
                z = self.r[node]
            else:
                a = self.r[node]
                z = self.l[node]

            if a != 0 and self.c[a] > 0:
                ans |= (1 << b)
                node = a
            else:
                node = z

        return ans


t = int(input())

for _ in range(t):
    n = int(input())

    f = [x - 1 for x in map(int, input().split())]
    v = list(map(int, input().split()))

    rev = [[] for _ in range(n)]
    deg = [0] * n

    for i in range(n):
        rev[f[i]].append(i)
        deg[f[i]] += 1

    q = deque(i for i in range(n) if deg[i] == 0)

    while q:
        u = q.popleft()
        w = f[u]
        deg[w] -= 1

        if deg[w] == 0:
            q.append(w)

    ans = [0] * n
    seen = [False] * n

    for start in range(n):
        if deg[start] == 0 or seen[start]:
            continue

        cycle = []
        u = start

        while not seen[u]:
            seen[u] = True
            cycle.append(u)
            u = f[u]

        m = len(cycle)

        p = [0] * (2 * m + 1)

        for i in range(2 * m):
            p[i + 1] = p[i] ^ v[cycle[i % m]]

        total = p[m]

        ct = Trie()

        for i in range(1, m + 1):
            ct.add(p[i], 1)

        for j in range(m):
            root = cycle[j]

            def cycle_query(x):
                res = ct.query(x)

                if total:
                    res = max(res, ct.query(x ^ total))

                return res

            ans[root] = cycle_query(p[j])

            children = [
                x for x in rev[root]
                if deg[x] == 0
            ]

            if children:
                pt = Trie()
                pt.add(0, 1)

                stack = [(x, 0, False) for x in children]

                while stack:
                    x, parent_dist, exiting = stack.pop()

                    if exiting:
                        pt.add(parent_dist, -1)
                        continue

                    d = v[x] ^ parent_dist

                    best1 = pt.query(d)
                    best2 = cycle_query(d ^ p[j])

                    ans[x] = max(best1, best2)

                    pt.add(d, 1)

                    stack.append((x, d, True))

                    for child in rev[x]:
                        if deg[child] == 0:
                            stack.append((child, d, False))

            if j + 1 < m:
                ct.add(p[j + 1], -1)
                ct.add(p[j + m + 1], 1)

    print(*ans)