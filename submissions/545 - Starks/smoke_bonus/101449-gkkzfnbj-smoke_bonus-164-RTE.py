
import sys

def solve():
    data = iter(sys.stdin.buffer.read().split())
    t = int(next(data))
    answers = []

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

    for _ in range(t):
        n = int(next(data))
        m = int(next(data))
        q = int(next(data))

        grid = [
            next(data).decode()
            for _ in range(n)
        ]

        total = n * m
        dsu = DSU(2 * total)

        def get_id(r, c, mode):
            return mode * total + r * m + c

        def active(r, c, mode):
            tile = grid[r][c]

            if tile == '.':
                return True

            if mode == 0 and tile == 'B':
                return True

            if mode == 1 and tile == 'R':
                return True

            return False

        directions = [(0, 1), (1, 0)]

        for r in range(n):
            for c in range(m):

                for mode in range(2):
                    if not active(r, c, mode):
                        continue

                    current = get_id(r, c, mode)

                    for dr, dc in directions:
                        nr = r + dr
                        nc = c + dc

                        if nr < n and nc < m:
                            if active(nr, nc, mode):
                                neighbor = get_id(nr, nc, mode)
                                dsu.union(current, neighbor)

                if grid[r][c] == '.':
                    blue = get_id(r, c, 0)
                    red = get_id(r, c, 1)
                    dsu.union(blue, red)

        for _ in range(q):
            rs = int(next(data)) - 1
            cs = int(next(data)) - 1
            re = int(next(data)) - 1
            ce = int(next(data)) - 1

            possible = False

            for start_mode in range(2):
                if not active(rs, cs, start_mode):
                    continue

                start = get_id(rs, cs, start_mode)

                for end_mode in range(2):
                    if not active(re, ce, end_mode):
                        continue

                    end = get_id(re, ce, end_mode)

                    if dsu.find(start) == dsu.find(end):
                        possible = True
                        break

                if possible:
                    break

            answers.append("YES" if possible else "NO")

    sys.stdout.write("\n".join(answers))


solve()
