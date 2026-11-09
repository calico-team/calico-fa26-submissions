
import sys
from collections import deque

def solve():
    input = sys.stdin.readline
    t = int(input())

    for _ in range(t):
        n, m, q = map(int, input().split())
        grid = [input().strip() for _ in range(n)]

        # Two states for every cell:
        # 0 = Blue mode
        # 1 = Red mode

        size = n * m
        total = 2 * size

        comp = [-1] * total
        cid = 0

        for mode in range(2):
            for r in range(n):
                for c in range(m):
                    start = mode * size + r * m + c

                    if comp[start] != -1:
                        continue

                    ch = grid[r][c]

                    # Skip inactive colored tiles
                    if ch == 'R' and mode == 0:
                        continue
                    if ch == 'B' and mode == 1:
                        continue

                    comp[start] = cid
                    queue = deque([start])

                    while queue:
                        u = queue.popleft()

                        current_mode = u // size
                        pos = u % size
                        x = pos // m
                        y = pos % m

                        # Four directions
                        for dx, dy in ((1, 0), (-1, 0),
                                       (0, 1), (0, -1)):
                            nx = x + dx
                            ny = y + dy

                            if 0 <= nx < n and 0 <= ny < m:
                                tile = grid[nx][ny]

                                if tile == 'R' and current_mode == 0:
                                    continue
                                if tile == 'B' and current_mode == 1:
                                    continue

                                v = current_mode * size + nx * m + ny

                                if comp[v] == -1:
                                    comp[v] = cid
                                    queue.append(v)

                        # Spin on normal tiles
                        if grid[x][y] == '.':
                            v = (1 - current_mode) * size + pos

                            if comp[v] == -1:
                                comp[v] = cid
                                queue.append(v)

                    cid += 1

        # Answer queries
        for _ in range(q):
            rs, cs, re, ce = map(int, input().split())

            start = rs * m + cs

            # Starting cell is always normal and starts in blue mode
            start_comp = comp[start]

            if grid[re][ce] == '.':
                end_blue = comp[re * m + ce]
                end_red = comp[size + re * m + ce]

                if start_comp == end_blue or start_comp == end_red:
                    print("YES")
                else:
                    print("NO")

            elif grid[re][ce] == 'B':
                end = comp[re * m + ce]
                print("YES" if start_comp == end else "NO")

            else:
                end = comp[size + re * m + ce]
                print("YES" if start_comp == end else "NO")


if __name__ == "__main__":
    solve()
