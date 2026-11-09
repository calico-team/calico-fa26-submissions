from collections import deque

def solve(N, M, Q, G, start, end, K):
    answers = []

    for query in range(Q):
        sr, sc = start[query]
        er, ec = end[query]
        limit = K[query]

        dist = [[[-1, -1] for _ in range(M)] for _ in range(N)]

        queue = deque()
        queue.append((sr, sc, 0))
        dist[sr][sc][0] = 0

        found = False

        while queue:
            r, c, mode = queue.popleft()
            time = dist[r][c][mode]

            if time > limit:
                continue

            if r == er and c == ec:
                found = True
                break

            for dr, dc in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
                nr = r + dr
                nc = c + dc

                if 0 <= nr < N and 0 <= nc < M:
                    tile = G[nr][nc]

                    if tile == ".":
                        allowed = True
                    elif tile == "B" and mode == 0:
                        allowed = True
                    elif tile == "R" and mode == 1:
                        allowed = True
                    else:
                        allowed = False

                    if allowed and dist[nr][nc][mode] == -1:
                        dist[nr][nc][mode] = time + 1
                        queue.append((nr, nc, mode))

            if G[r][c] == ".":
                new_mode = 1 - mode

                if dist[r][c][new_mode] == -1:
                    dist[r][c][new_mode] = time + 1
                    queue.append((r, c, new_mode))

        answers.append("YES" if found else "NO")

    return answers


def main():
    T = int(input())

    for _ in range(T):
        N, M, Q = map(int, input().split())

        G = []
        for _ in range(N):
            G.append(input().strip())

        start = []
        end = []
        K = []

        for _ in range(Q):
            start_row, start_col, end_row, end_col, k = map(int, input().split())

            start.append((start_row, start_col))
            end.append((end_row, end_col))
            K.append(k)

        results = solve(N, M, Q, G, start, end, K)

        for result in results:
            print(result)


if __name__ == "__main__":
    main()
