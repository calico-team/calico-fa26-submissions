import sys


class DSU:
    def __init__(self, size):
        self.parent = list(range(size))
        self.rank = [0] * size

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
        if self.rank[a] < self.rank[b]:
            a, b = b, a
        self.parent[b] = a
        if self.rank[a] == self.rank[b]:
            self.rank[a] += 1


def solve():
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    it = iter(data)
    t = int(next(it))
    answers = []

    for _ in range(t):
        n = int(next(it))
        m = int(next(it))
        q = int(next(it))

        grid = [next(it).decode() for _ in range(n)]

        cells = n * m
        dsu = DSU(2 * cells)

        def node(mode, r, c):
            return mode * cells + r * m + c

        for r in range(n):
            for c in range(m):
                current = grid[r][c]

                if current == '.':
                    dsu.union(node(0, r, c), node(1, r, c))

                for dr, dc in ((0, 1), (1, 0)):
                    nr = r + dr
                    nc = c + dc
                    if nr >= n or nc >= m:
                        continue
                    neighbor = grid[nr][nc]

                    if current in ('.', 'B') and neighbor in ('.', 'B'):
                        dsu.union(node(0, r, c), node(0, nr, nc))

                    if current in ('.', 'R') and neighbor in ('.', 'R'):
                        dsu.union(node(1, r, c), node(1, nr, nc))

        for _ in range(q):
            rs = int(next(it))
            cs = int(next(it))
            re = int(next(it))
            ce = int(next(it))

            start_component = dsu.find(node(0, rs, cs))
            destination = grid[re][ce]

            if destination == 'R':
                destination_component = dsu.find(node(1, re, ce))
            else:
                destination_component = dsu.find(node(0, re, ce))

            answers.append("YES" if start_component == destination_component else "NO")

    sys.stdout.write("\n".join(answers))


if __name__ == "__main__":
    solve()
