import sys

def solve():
    input = sys.stdin.readline
    T = int(input())

    for _ in range(T):
        N, M, Q = map(int, input().split())
        grid = [input().strip() for _ in range(N)]

        for _ in range(Q):
            rs, cs, re, ce, K = map(int, input().split())

            start = (rs * M + cs) * 2 + 1

            dist = [-1] * (N * M * 2)
            dist[start] = 0

            q = deque([start])
            answer = False

            while q:
                u = q.popleft()
                d = dist[u]

                cell, mode = divmod(u, 2)
                r, c = divmod(cell, M)

                if r == re and c == ce:
                    answer = True
                    break

                if d == K:
                    continue

                ch = grid[r][c]

                # Spin on normal tile
                if ch == '.':
                    v = u ^ 1
                    if dist[v] == -1:
                        dist[v] = d + 1
                        q.append(v)

                # Move to adjacent tiles
                for nr, nc in (
                    (r - 1, c),
                    (r + 1, c),
                    (r, c - 1),
                    (r, c + 1)
                ):
                    if 0 <= nr < N and 0 <= nc < M:
                        tile = grid[nr][nc]

                        if tile == '.' or \
                           (tile == 'B' and mode == 1) or \
                           (tile == 'R' and mode == 0):

                            v = (nr * M + nc) * 2 + mode

                            if dist[v] == -1:
                                dist[v] = d + 1
                                q.append(v)

            print("YES" if answer else "NO")


if __name__ == "__main__":
    solve()