
import sys

input = sys.stdin.readline

class DSU:
    def __init__(self, n):
        self.parent = list(range(n))
        self.size = [1] * n

    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, a, b):
        a = self.find(a)
        b = self.find(b)

        if a != b:
            if self.size[a] < self.size[b]:
                a, b = b, a
            self.parent[b] = a
            self.size[a] += self.size[b]


def solve():
    t = int(input())

    for _ in range(t):
        n, m, q = map(int, input().split())
        grid = [input().strip() for _ in range(n)]

        dsu = DSU(2 * n * m)

        def node(r, c, mode):
            return mode * n * m + r * m + c

        for r in range(n):
            for c in range(m):
                ch = grid[r][c]

                if ch == '.':
                    dsu.union(node(r, c, 0),
                              node(r, c, 1))

                for dr, dc in [(0, 1), (1, 0)]:
                    nr, nc = r + dr, c + dc

                    if nr < n and nc < m:
                        nxt = grid[nr][nc]

                        for mode in range(2):
                            active1 = (
                                ch == '.' or
                                (mode == 0 and ch == 'B') or
                                (mode == 1 and ch == 'R')
                            )

                            active2 = (
                                nxt == '.' or
                                (mode == 0 and nxt == 'B') or
                                (mode == 1 and nxt == 'R')
                            )

                            if active1 and active2:
                                dsu.union(
                                    node(r, c, mode),
                                    node(nr, nc, mode)
                                )

        for _ in range(q):
            rs, cs, re, ce = map(int, input().split())

            start = node(rs, cs, 0)
            possible = False

            if grid[re][ce] != 'R':
                if dsu.find(start) == dsu.find(node(re, ce, 0)):
                    possible = True

            if grid[re][ce] != 'B':
                if dsu.find(start) == dsu.find(node(re, ce, 1)):
                    possible = True

            print("YES" if possible else "NO")


if __name__ == "__main__":
    solve()
