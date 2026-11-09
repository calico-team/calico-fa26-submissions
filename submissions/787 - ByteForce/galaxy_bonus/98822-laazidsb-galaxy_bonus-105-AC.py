
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

    def connected(self, a, b):
        return self.find(a) == self.find(b)


def solve():
    import sys
    input = sys.stdin.readline

    T = int(input())

    for _ in range(T):
        N, M, Q = map(int, input().split())
        grid = [input().strip() for _ in range(N)]

        total = N * M
        dsu = DSU(2 * total)

        def get_id(r, c, mode):
            return mode * total + r * M + c

        # Build connections for both modes
        for r in range(N):
            for c in range(M):
                tile = grid[r][c]

                # Normal tiles allow switching modes
                if tile == '.':
                    dsu.union(
                        get_id(r, c, 0),
                        get_id(r, c, 1)
                    )

                for dr, dc in [(0, 1), (1, 0)]:
                    nr, nc = r + dr, c + dc

                    if nr >= N or nc >= M:
                        continue

                    other = grid[nr][nc]

                    # Blue mode
                    if tile in '.B' and other in '.B':
                        dsu.union(
                            get_id(r, c, 0),
                            get_id(nr, nc, 0)
                        )

                    # Red mode
                    if tile in '.R' and other in '.R':
                        dsu.union(
                            get_id(r, c, 1),
                            get_id(nr, nc, 1)
                        )

        # Answer queries
        for _ in range(Q):
            rs, cs, re, ce = map(int, input().split())

            start = get_id(rs, cs, 0)

            blue = get_id(re, ce, 0)
            red = get_id(re, ce, 1)

            if (dsu.connected(start, blue) or
                    dsu.connected(start, red)):
                print("YES")
            else:
                print("NO")


if __name__ == "__main__":
    solve()
