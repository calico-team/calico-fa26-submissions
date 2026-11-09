import sys


def solve():
    data = sys.stdin.read().split()
    pos = 0

    def next_token():
        nonlocal pos
        tok = data[pos]
        pos += 1
        return tok

    out = []
    t = int(next_token())
    for _ in range(t):
        n = int(next_token())
        m = int(next_token())
        q = int(next_token())
        grid = [next_token() for _ in range(n)]

        # Label connected regions of tiles Ben can walk on in one fixed mode.
        # In blue mode he can use '.' and 'B' tiles; in red mode '.' and 'R'.
        def label(allowed):
            comp = [[-1] * m for _ in range(n)]
            count = 0
            for r in range(n):
                for c in range(m):
                    if grid[r][c] in allowed and comp[r][c] == -1:
                        stack = [(r, c)]
                        comp[r][c] = count
                        while stack:
                            x, y = stack.pop()
                            for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                                nx, ny = x + dx, y + dy
                                if 0 <= nx < n and 0 <= ny < m:
                                    if comp[nx][ny] == -1 and grid[nx][ny] in allowed:
                                        comp[nx][ny] = count
                                        stack.append((nx, ny))
                        count += 1
            return comp, count

        blue, num_blue = label({'.', 'B'})
        red, num_red = label({'.', 'R'})

        # Union-Find over all regions of both modes. A normal tile belongs to
        # one blue region and one red region, and Ben can spin on it, so those
        # two regions are linked. Reachability = being in one linked group.
        parent = list(range(num_blue + num_red))

        def find(x):
            while parent[x] != x:
                parent[x] = parent[parent[x]]
                x = parent[x]
            return x

        def union(a, b):
            ra, rb = find(a), find(b)
            if ra != rb:
                parent[ra] = rb

        for r in range(n):
            for c in range(m):
                if grid[r][c] == '.':
                    union(blue[r][c], num_blue + red[r][c])

        for _ in range(q):
            rs = int(next_token())
            cs = int(next_token())
            re_ = int(next_token())
            ce = int(next_token())

            # Ben starts in blue mode on a normal tile.
            start_group = find(blue[rs][cs])
            tile = grid[re_][ce]
            if tile == 'B':
                ok = find(blue[re_][ce]) == start_group
            elif tile == 'R':
                ok = find(num_blue + red[re_][ce]) == start_group
            else:  # normal tile: standable in either mode
                ok = find(blue[re_][ce]) == start_group
            out.append('YES' if ok else 'NO')

    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == '__main__':
    solve()
