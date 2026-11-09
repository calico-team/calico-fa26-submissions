
class DSU:
    def __init__(self, n):
        self.parent = list(range(n))
        self.size = [1] * n

    def find(self, x):
        while self.parent[x] != x:
            self.parent[x] = self.parent[self.parent[x]]
            x = self.parent[x]
        return x

    def union(self, a, b):
        a = self.find(a)
        b = self.find(b)

        if a == b:
            return

        if self.size[a] < self.size[b]:
            a, b = b, a

        self.parent[b] = a
        self.size[a] += self.size[b]

    def same(self, a, b):
        return self.find(a) == self.find(b)


t = int(input())

for _ in range(t):
    n, m, q = map(int, input().split())
    g = [input().strip() for _ in range(n)]

    total = n * m
    dsu = DSU(2 * total)

    def active(ch, mode):
        if ch == '.':
            return True
        if mode == 0:
            return ch == 'B'
        return ch == 'R'

    for i in range(n):
        for j in range(m):
            u = i * m + j
            ch = g[i][j]

            # Spin on normal tiles
            if ch == '.':
                dsu.union(u, u + total)

            for di, dj in [(0, 1), (1, 0)]:
                ni = i + di
                nj = j + dj

                if ni >= n or nj >= m:
                    continue

                v = ni * m + nj

                # Connect accessible cells in both modes
                for mode in range(2):
                    if active(ch, mode) and active(g[ni][nj], mode):
                        dsu.union(u + mode * total,
                                  v + mode * total)

    for _ in range(q):
        rs, cs, re, ce = map(int, input().split())

        start = rs * m + cs
        end = re * m + ce

        if g[re][ce] == 'B':
            target = end
            ans = dsu.same(start, target)

        elif g[re][ce] == 'R':
            target = end + total
            ans = dsu.same(start, target)

        else:
            ans = (dsu.same(start, end) or
                   dsu.same(start, end + total))

        print("YES" if ans else "NO")
