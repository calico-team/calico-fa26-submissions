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

        total = N * M
        dsu = DSU(2 * total)

        def get_id(r, c, mode):
            return mode * total + r * M + c

        def active(ch, mode):
            if ch == '.':
                return True
            if mode == 0:
                return ch == 'B'
            return ch == 'R'

        directions = [(0, 1), (1, 0)]

        for r in range(N):
            for c in range(M):
                ch = grid[r][c]

                # Spin action on normal tiles
                if ch == '.':
                    dsu.union(
                        get_id(r, c, 0),
                        get_id(r, c, 1)
                    )

                # Connect adjacent cells in each mode
                for dr, dc in directions:
                    nr, nc = r + dr, c + dc

                    if nr >= N or nc >= M:
                        continue

                    nch = grid[nr][nc]

                    for mode in range(2):
                        if active(ch, mode) and active(nch, mode):
                            dsu.union(
                                get_id(r, c, mode),
                                get_id(nr, nc, mode)
                            )

        for _ in range(Q):
            rs, cs, re, ce = map(int, input().split())

            # Starting position is always normal,
            # and Ben starts in blue mode.
            start = get_id(rs, cs, 0)
            start_root = dsu.find(start)

            dest = grid[re][ce]

            if dest == '.':
                possible = (
                    dsu.find(get_id(re, ce, 0)) == start_root
                    or dsu.find(get_id(re, ce, 1)) == start_root
                )

            elif dest == 'B':
                possible = (
                    dsu.find(get_id(re, ce, 0)) == start_root
                )

            else:  # Red tile
                possible = (
                    dsu.find(get_id(re, ce, 1)) == start_root
                )

            print("YES" if possible else "NO")


if __name__ == "__main__":
    solve()
