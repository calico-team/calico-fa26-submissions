
from collections import deque

def shortest_time(grid, rs, cs, re, ce):
    n = len(grid)
    m = len(grid[0])

    queue = deque([(rs, cs, 0, 0)])
    visited = {(rs, cs, 0)}

    directions = [(1, 0), (-1, 0),
                  (0, 1), (0, -1)]

    while queue:
        r, c, mode, time = queue.popleft()

        if r == re and c == ce:
            return time

        if grid[r][c] == '.':
            state = (r, c, 1 - mode)

            if state not in visited:
                visited.add(state)
                queue.append((r, c, 1 - mode, time + 1))

        for dr, dc in directions:
            nr = r + dr
            nc = c + dc

            if not (0 <= nr < n and 0 <= nc < m):
                continue

            tile = grid[nr][nc]

            if tile == 'R' and mode != 1:
                continue

            if tile == 'B' and mode != 0:
                continue

            state = (nr, nc, mode)

            if state not in visited:
                visited.add(state)
                queue.append((nr, nc, mode, time + 1))

    return -1


def solve():
    T = int(input())

    for _ in range(T):
        N, M, Q = map(int, input().split())
        grid = [input().strip() for _ in range(N)]

        for _ in range(Q):
            rs, cs, re, ce, K = map(int, input().split())

            distance = shortest_time(
                grid, rs, cs, re, ce
            )

            if distance != -1 and distance <= K:
                print("YES")
            else:
                print("NO")


if __name__ == "__main__":
    solve()
