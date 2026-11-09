from collections import deque


def solve(N: int, M: int, Q: int, G: list[str], start: list[tuple[int, int]], end: list[tuple[int, int]], K: list[int]) -> list[str]:
    """
    Return an array of Q strings, the i-th of which is "YES"
    if Big Ben can travel from start[i] to end[i] within K[i]
    seconds, and "NO" otherwise.

    N: the number of rows in the grid
    M: the number of columns in the grid
    Q: the number of queries
    G: the grid, where each tile is 'R', 'B', or '.'
    start: the (row, column) of the starting tile of each query
    end: the (row, column) of the ending tile of each query
    K: the maximum number of seconds allowed for each query
    """
    total = N * M
    INF = 10**15


    def bfs(sr, sc):
        dist = [-1] * (2 * total)
        source = sr * M + sc

        dist[source] = 0
        queue = deque([source])

        while queue:
            state = queue.popleft()
            d = dist[state] + 1

            mode = state // total
            pos = state % total

            r, c = divmod(pos, M)
            tile = G[r][c]

            if tile == ".":
                other = pos + (1 - mode) * total

                if dist[other] == -1:
                    dist[other] = d
                    queue.append(other)

            for nr, nc in (
                (r - 1, c),
                (r + 1, c),
                (r, c - 1),
                (r, c + 1)
            ):
                if not (0 <= nr < N and 0 <= nc < M):
                    continue

                next_tile = G[nr][nc]

                if mode == 0 and next_tile == "R":
                    continue

                if mode == 1 and next_tile == "B":
                    continue

                next_state = mode * total + nr * M + nc

                if dist[next_state] == -1:
                    dist[next_state] = d
                    queue.append(next_state)

        return dist

    results = ["NO"] * Q

    groups = {}

    for i in range(Q):
        groups.setdefault(start[i], []).append(i)

    for (sr, sc), indices in groups.items():
        distances = bfs(sr, sc)

        for i in indices:
            er, ec = end[i]
            target = er * M + ec

            blue_distance = distances[target]
            red_distance = distances[target + total]

            possible = (
                (blue_distance != -1 and blue_distance <= K[i])
                or
                (red_distance != -1 and red_distance <= K[i])
            )

            if possible:
                results[i] = "YES"

    return results

def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        G = []
        for _ in range(N):
            G.append(input())
        start, end, K = [], [], []
        for _ in range(Q):
            start_row, start_col, end_row, end_col, k = map(int, input().split())
            start.append((start_row, start_col))
            end.append((end_row, end_col))
            K.append(k)
        for s in solve(N, M, Q, G, start, end, K):
            print(s)

if __name__ == '__main__':
    main()
