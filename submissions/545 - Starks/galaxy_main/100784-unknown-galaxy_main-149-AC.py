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

        if a == b:
            return

        if self.size[a] < self.size[b]:
            a, b = b, a

        self.parent[b] = a
        self.size[a] += self.size[b]


def solve():
    t = int(input())

    for _ in range(t):
        n, m, o = map(int, input().split())

        grid = [input().strip() for _ in range(n)]

        total = n * m
        dsu = DSU(2 * total)

        def get_id(r, c, mode):
            return mode * total + r * m + c

        def active(tile, mode):
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

                    if not active(grid[r][c], mode):
                        continue

                    current = get_id(r, c, mode)

                    for dr, dc in directions:
                        nr = r + dr
                        nc = c + dc

                        if 0 <= nr < n and 0 <= nc < m:
                            if active(grid[nr][nc], mode):
                                neighbor = get_id(nr, nc, mode)
                                dsu.union(current, neighbor)

                if grid[r][c] == '.':
                    blue = get_id(r, c, 0)
                    red = get_id(r, c, 1)
                    dsu.union(blue, red)

        for _ in range(o):
            rs, cs, re, ce = map(int, input().split())

            start = get_id(rs, cs, 0)

            possible = False

            for mode in range(2):
                if active(grid[re][ce], mode):
                    destination = get_id(re, ce, mode)

                    if dsu.find(start) == dsu.find(destination):
                        possible = True

            print("YES" if possible else "NO")


solve()