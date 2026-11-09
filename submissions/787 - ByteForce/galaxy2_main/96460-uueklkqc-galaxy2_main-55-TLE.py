from collections import deque

def can_reach(grid, n, m, sr, sc, er, ec, k):

    dist = [[[-1] * 2 for _ in range(m)] for _ in range(n)]

    queue = deque()
    queue.append((sr, sc, 0))
    dist[sr][sc][0] = 0

    directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]

    while queue:
        r, c, mode = queue.popleft()
        time = dist[r][c][mode]

        if time > k:
            continue

        if r == er and c == ec:
            return True

        for dr, dc in directions:
            nr = r + dr
            nc = c + dc

            if 0 <= nr < n and 0 <= nc < m:
                tile = grid[nr][nc]

                # Check whether the tile is active
                can_move = (
                    tile == "." or
                    (tile == "B" and mode == 0) or
                    (tile == "R" and mode == 1)
                )

                if can_move and dist[nr][nc][mode] == -1:
                    dist[nr][nc][mode] = time + 1
                    queue.append((nr, nc, mode))

        if grid[r][c] == ".":
            new_mode = 1 - mode

            if dist[r][c][new_mode] == -1:
                dist[r][c][new_mode] = time + 1
                queue.append((r, c, new_mode))

    return False


def solve():
    T = int(input())

    for _ in range(T):
        n, m, q = map(int, input().split())
        grid = [input().strip() for _ in range(n)]

        for _ in range(q):
            sr, sc, er, ec, k = map(int, input().split())

            if can_reach(grid, n, m, sr, sc, er, ec, k):
                print("YES")
            else:
                print("NO")


if __name__ == "__main__":
    solve()
