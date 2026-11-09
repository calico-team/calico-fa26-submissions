import sys


class DSU:
    def __init__(self, size):
        self.parent = list(range(size))
        self.size = [1] * size

    def find(self, x):
        parent = self.parent
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
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


def is_active(tile, mode):
    # Mode 0 is blue; mode 1 is red.
    return tile == "." or (mode == 0 and tile == "B") or (mode == 1 and tile == "R")


def build_components(grid, n, m):
    cell_count = n * m
    dsu = DSU(2 * cell_count)

    # A spin connects the two modes at every normal tile.
    for cell, tile in enumerate(grid):
        if tile == ".":
            dsu.union(2 * cell, 2 * cell + 1)

    # Add walkable edges independently in each mode.
    for r in range(n):
        for c in range(m):
            cell = r * m + c
            for mode in range(2):
                if not is_active(grid[cell], mode):
                    continue

                state = 2 * cell + mode
                if c + 1 < m:
                    right = cell + 1
                    if is_active(grid[right], mode):
                        dsu.union(state, 2 * right + mode)
                if r + 1 < n:
                    down = cell + m
                    if is_active(grid[down], mode):
                        dsu.union(state, 2 * down + mode)

    return dsu


def solve():
    input = sys.stdin.buffer.readline
    test_cases = int(input())
    answers = []

    for _ in range(test_cases):
        n, m, q = map(int, input().split())
        rows = [input().strip().decode() for _ in range(n)]
        grid = "".join(rows)
        dsu = build_components(grid, n, m)

        for _ in range(q):
            rs, cs, re, ce = map(int, input().split())
            start = 2 * (rs * m + cs)  # Every query starts in blue mode.
            destination = 2 * (re * m + ce)
            start_component = dsu.find(start)
            tile = grid[re * m + ce]

            reachable = False
            if tile == "." or tile == "B":
                reachable |= dsu.find(destination) == start_component
            if tile == "." or tile == "R":
                reachable |= dsu.find(destination + 1) == start_component

            answers.append("YES" if reachable else "NO")

    sys.stdout.write("\n".join(answers))


if __name__ == "__main__":
    solve()
