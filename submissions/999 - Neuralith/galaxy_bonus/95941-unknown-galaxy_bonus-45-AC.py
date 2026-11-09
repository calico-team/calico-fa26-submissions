
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

        total = N * M * 2
        dsu = DSU(total)

        # State IDs:
        # Blue mode = cell * 2
        # Red mode  = cell * 2 + 1

        def active(ch, mode):
            if ch == '.':
                return True
            if mode == 0 and ch == 'B':
                return True
            if mode == 1 and ch == 'R':
                return True
            return False

        # Build connected components
        for r in range(N):
            for c in range(M):

                cell = r * M + c

                # Connect both modes on normal tiles
                if grid[r][c] == '.':
                    dsu.union(cell * 2, cell * 2 + 1)

                # Check right and down neighbors
                for dr, dc in ((0, 1), (1, 0)):
                    nr = r + dr
                    nc = c + dc

                    if nr >= N or nc >= M:
                        continue

                    neighbor = nr * M + nc

                    for mode in range(2):
                        if (active(grid[r][c], mode) and
                            active(grid[nr][nc], mode)):

                            dsu.union(
                                cell * 2 + mode,
                                neighbor * 2 + mode
                            )

        # Answer queries
        for _ in range(Q):
            rs, cs, re, ce = map(int, input().split())

            start = (rs * M + cs) * 2
            destination = (re * M + ce) * 2

            # Starting state is always blue
            start_root = dsu.find(start)

            # Destination reachable in blue mode?
            blue_possible = (
                active(grid[re][ce], 0) and
                start_root == dsu.find(destination)
            )

            # Destination reachable in red mode?
            red_possible = (
                active(grid[re][ce], 1) and
                start_root == dsu.find(destination + 1)
            )

            if blue_possible or red_possible:
                print("YES")
            else:
                print("NO")


if __name__ == "__main__":
    solve()
