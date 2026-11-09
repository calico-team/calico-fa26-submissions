import sys


class DSU:
    def __init__(self, n):
        self.parent = list(range(n))
        self.size = [1] * n

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


def main():
    data = sys.stdin.buffer.read().split()
    test_cases = int(data[0])
    pos = 1
    answers = []

    for _ in range(test_cases):
        rows, cols, query_count = map(int, data[pos:pos + 3])
        pos += 3

        grid = data[pos:pos + rows]
        pos += rows

        cells = rows * cols
        dsu = DSU(cells * 2)

        for r in range(rows):
            for c in range(cols):
                tile = grid[r][c]
                cell = r * cols + c

                if tile == ord('.'):
                    dsu.union(cell, cells + cell)

                for nr, nc in ((r + 1, c), (r, c + 1)):
                    if nr >= rows or nc >= cols:
                        continue

                    neighbor = grid[nr][nc]
                    other = nr * cols + nc

                    if tile != ord('R') and neighbor != ord('R'):
                        dsu.union(cell, other)

                    if tile != ord('B') and neighbor != ord('B'):
                        dsu.union(cells + cell, cells + other)

        for _ in range(query_count):
            start_row, start_col, end_row, end_col = map(
                int, data[pos:pos + 4]
            )
            pos += 4

            start = start_row * cols + start_col
            end = end_row * cols + end_col
            start_component = dsu.find(start)

            tile = grid[end_row][end_col]

            if tile == ord('.'):
                possible = (
                    start_component == dsu.find(end)
                    or start_component == dsu.find(cells + end)
                )
            elif tile == ord('B'):
                possible = start_component == dsu.find(end)
            else:
                possible = start_component == dsu.find(cells + end)

            answers.append("YES" if possible else "NO")

    sys.stdout.write("\n".join(answers))


if __name__ == "__main__":
    main()