
import sys

input = sys.stdin.readline


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


def solve():
    T = int(input())

    for _ in range(T):
        N, M, Q = map(int, input().split())
        grid = [input().strip() for _ in range(N)]

        dsu = DSU(2 * N * M)

        def node(r, c, mode):
            return 2 * (r * M + c) + mode

        def active(r, c, mode):
            ch = grid[r][c]
            if ch == '.':
                return True
            if mode == 0:
                return ch == 'B'
            return ch == 'R'

        # Build connected components.
        for r in range(N):
            for c in range(M):
                # Spin action on normal tiles.
                if grid[r][c] == '.':
                    dsu.union(node(r, c, 0), node(r, c, 1))

                # Connect neighboring cells in each mode.
                for mode in range(2):
                    if not active(r, c, mode):
                        continue

                    if c + 1 < M and active(r, c + 1, mode):
                        dsu.union(
                            node(r, c, mode),
                            node(r, c + 1, mode)
                        )

                    if r + 1 < N and active(r + 1, c, mode):
                        dsu.union(
                            node(r, c, mode),
                            node(r + 1, c, mode)
                        )

        # Answer queries.
        for _ in range(Q):
            rs, cs, re, ce = map(int, input().split())

            start = node(rs, cs, 0)  # Initially blue mode

            if active(re, ce, 0):
                if dsu.find(start) == dsu.find(node(re, ce, 0)):
                    print("YES")
                    continue

            if active(re, ce, 1):
                if dsu.find(start) == dsu.find(node(re, ce, 1)):
                    print("YES")
                    continue

            print("NO")


if __name__ == "__main__":
    solve()
