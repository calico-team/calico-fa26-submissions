from collections import deque
import sys

def solve():
    input = sys.stdin.readline

    T = int(input())

    for _ in range(T):
        N, M, Q = map(int, input().split())
        grid = [input().strip() for _ in range(N)]

        directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]

        for _ in range(Q):
            rs, cs, re, ce, K = map(int, input().split())

            if (rs, cs) == (re, ce):
                print("YES")
                continue

            dist = [[[-1] * 2 for _ in range(M)] for _ in range(N)]

            queue = deque()
            queue.append((rs, cs, 0))
            dist[rs][cs][0] = 0

            answer = False

            while queue:
                r, c, mode = queue.popleft()
                d = dist[r][c][mode]

                if d > K:
                    continue

                if r == re and c == ce:
                    answer = True
                    break

                if d == K:
                    continue

                if grid[r][c] == '.':
                    nm = 1 - mode

                    if dist[r][c][nm] == -1:
                        dist[r][c][nm] = d + 1
                        queue.append((r, c, nm))

                for dr, dc in directions:
                    nr, nc = r + dr, c + dc

                    if not (0 <= nr < N and 0 <= nc < M):
                        continue

                    tile = grid[nr][nc]

                    if tile == '.':
                        pass
                    elif tile == 'R' and mode != 1:
                        continue
                    elif tile == 'B' and mode != 0:
                        continue

                    if dist[nr][nc][mode] == -1:
                        dist[nr][nc][mode] = d + 1
                        queue.append((nr, nc, mode))

            print("YES" if answer else "NO")


if __name__ == "__main__":
    solve()