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


T = int(input())

for i in range(T):
    n, m, q = map(int, input().split())

    grid = []

    for i in range(n):
        grid.append(input().strip())

    total = n * m
    dsu = DSU(2 * total)

    for r in range(n):
        for c in range(m):
            cell = grid[r][c]

            current = r * m + c
            red_current = current + total

            if cell == ".":
                dsu.union(current, red_current)

            if c + 1 < m:
                next_cell = grid[r][c + 1]
                next_id = current + 1

                if cell != "R" and next_cell != "R":
                    dsu.union(current, next_id)

                if cell != "B" and next_cell != "B":
                    dsu.union(red_current, next_id + total)

            if r + 1 < n:
                next_cell = grid[r + 1][c]
                next_id = current + m

                if cell != "R" and next_cell != "R":
                    dsu.union(current, next_id)

                if cell != "B" and next_cell != "B":
                    dsu.union(red_current, next_id + total)

    for i in range(q):
        rs, cs, re, ce = map(int, input().split())

        start = rs * m + cs
        end = re * m + ce

        possible = False

        if grid[re][ce] != "R":
            if dsu.find(start) == dsu.find(end):
                possible = True

        if grid[re][ce] != "B":
            if dsu.find(start) == dsu.find(end + total):
                possible = True

        if possible:
            print("YES")
        else:
            print("NO")