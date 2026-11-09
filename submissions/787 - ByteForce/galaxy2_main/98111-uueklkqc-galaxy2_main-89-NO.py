from collections import deque

def solve(N, M, Q, G, start, end, K):
    answers = []
    directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]

    for query in range(Q):
        sr, sc = start[query]
        er, ec = end[query]
        limit = K[query]

        dist = [[[-1, -1] for _ in range(M)] for _ in range(N)]

        q = deque()
        q.append((sr, sc, 0))
        dist[sr][sc][0] = 0

        found = False

        while q:
            r, c, mode = q.popleft()
            d = dist[r][c][mode]

            if d > limit:
                continue

            if r == er and c == ec:
                found = True
                break

            for dr, dc in directions:
                nr, nc = r + dr, c + dc

                if 0 <= nr < N and 0 <= nc < M:
                    tile = G[nr][nc]

                    if (tile == '.' or
                        (tile == 'B' and mode == 0) or
                        (tile == 'R' and mode == 1)):

                        if dist[nr][nc][mode] == -1:
                            dist[nr][nc][mode] = d + 1
                            q.append((nr, nc, mode))

          
            if G[r][c] == '.':
                new_mode = 1 - mode

                if dist[r][c][new_mode] == -1:
                    dist[r][c][new_mode] = d + 1
                    q.append((r, c, new_mode))

        answers.append("YES" if found else "NO")

    return answers
