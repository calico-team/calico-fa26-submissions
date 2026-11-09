import sys


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
    input = sys.stdin.readline

    T = int(input())

    for _ in range(T):
        N, M, Q = map(int, input().split())
        grid = [input().strip() for _ in range(N)]

        total = N * M
        dsu = DSU(2 * total)

        # State IDs:
        # 2 * cell     = Blue mode
        # 2 * cell + 1 = Red mode

        def blue_active(ch):
            return ch == '.' or ch == 'B'

        def red_active(ch):
            return ch == '.' or ch == 'R'

        for r in range(N):
            for c in range(M):
                cell = r * M + c
                ch = grid[r][c]

                blue = 2 * cell
                red = 2 * cell + 1

                # Switch modes on normal tiles.
                if ch == '.':
                    dsu.union(blue, red)

                # Connect with the cell above.
                if r > 0:
                    up = (r - 1) * M + c
                    up_ch = grid[r - 1][c]

                    if blue_active(ch) and blue_active(up_ch):
                        dsu.union(blue, 2 * up)

                    if red_active(ch) and red_active(up_ch):
                        dsu.union(red, 2 * up + 1)

                # Connect with the cell on the left.
                if c > 0:
                    left = r * M + c - 1
                    left_ch = grid[r][c - 1]

                    if blue_active(ch) and blue_active(left_ch):
                        dsu.union(blue, 2 * left)

                    if red_active(ch) and red_active(left_ch):
                        dsu.union(red, 2 * left + 1)

        # Process queries.
        for _ in range(Q):
            rs, cs, re, ce = map(int, input().split())

            start = rs * M + cs
            end = re * M + ce

            # Starting mode is always blue.
            start_root = dsu.find(2 * start)

            destination = grid[re][ce]
            possible = False

            # Check blue mode.
            if blue_active(destination):
                if dsu.find(2 * end) == start_root:
                    possible = True

            # Check red mode.
            if red_active(destination):
                if dsu.find(2 * end + 1) == start_root:
                    possible = True

            print("YES" if possible else "NO")


if __name__ == "__main__":
    solve()