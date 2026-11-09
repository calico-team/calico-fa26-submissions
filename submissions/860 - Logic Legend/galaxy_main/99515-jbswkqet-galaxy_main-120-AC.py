import sys


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
        grid = [next(it) for _ in range(n)]
        total = 2 * n * m
        parent = list(range(total))
        size = [1] * total

        def active(ch, mode):
            return ch == 46 or (ch == 66 and mode == 0) or (ch == 82 and mode == 1)

        def find(x):
            while parent[x] != x:
                parent[x] = parent[parent[x]]
                x = parent[x]
            return x

        def union(a, b):
            ra = find(a)
            rb = find(b)
            if ra == rb:
                return
            if size[ra] < size[rb]:
                ra, rb = rb, ra
            parent[rb] = ra
            size[ra] += size[rb]

        for r in range(n):
            row = grid[r]
            for c in range(m):
                ch = row[c]
                cell = r * m + c
                if ch == 46:
                    union(2 * cell, 2 * cell + 1)

                for mode in (0, 1):
                    if not active(ch, mode):
                        continue
                    here = 2 * cell + mode
                    if c + 1 < m and active(row[c + 1], mode):
                        union(here, 2 * (cell + 1) + mode)
                    if r + 1 < n and active(grid[r + 1][c], mode):
                        union(here, 2 * (cell + m) + mode)

        for _ in range(q):
            rs = int(next(it))
            cs = int(next(it))
            re = int(next(it))
            ce = int(next(it))
            start = 2 * (rs * m + cs)
            dest_cell = re * m + ce
            dest = grid[re][ce]
            start_root = find(start)

            if dest == 46:
                possible = find(2 * dest_cell) == start_root or find(2 * dest_cell + 1) == start_root
            elif dest == 66:
                possible = find(2 * dest_cell) == start_root
            else:
                possible = find(2 * dest_cell + 1) == start_root
            answers.append("YES" if possible else "NO")

    sys.stdout.write("\n".join(answers))


if __name__ == "__main__":
    solve()
