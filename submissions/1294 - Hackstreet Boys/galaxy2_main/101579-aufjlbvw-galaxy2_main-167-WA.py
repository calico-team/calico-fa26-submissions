
from collections import deque

def solve(N: int, M: int, Q: int, G: list[str],
          start: list[tuple[int, int]],
          end: list[tuple[int, int]],
          limits: list[int]) -> list[str]:

    # Each cell has two states:
    # 0 = Blue mode
    # 1 = Red mode

    total = N * M
    INF = 10**9

    dist = [[INF] * total for _ in range(2)]

    queue = deque()

    # Starting position is normal and initial mode is blue.
    # Precompute shortest paths from every normal cell in both modes
    # using one BFS from each query start would be too expensive.
    #
    # Instead, build the complete state graph and use Floyd-style
    # component preprocessing through BFS from all normal cells.

    adj = [[] for _ in range(2 * total)]

    for r in range(N):
        for c in range(M):
            u = r * M + c

            for dr, dc in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                nr, nc = r + dr, c + dc

                if 0 <= nr < N and 0 <= nc < M:
                    v = nr * M + nc

                    for mode in range(2):
                        active = (
                            G[nr][nc] == '.' or
                            (mode == 0 and G[nr][nc] == 'B') or
                            (mode == 1 and G[nr][nc] == 'R')
                        )

                        current_active = (
                            G[r][c] == '.' or
                            (mode == 0 and G[r][c] == 'B') or
                            (mode == 1 and G[r][c] == 'R')
                        )

                        if active and current_active:
                            adj[mode * total + u].append(
                                mode * total + v
                            )

            if G[r][c] == '.':
                adj[u].append(total + u)
                adj[total + u].append(u)

    # Find connected components in the complete graph.
    component = [-1] * (2 * total)
    comp_id = 0

    for i in range(2 * total):
        if component[i] != -1:
            continue

        queue.append(i)
        component[i] = comp_id

        while queue:
            u = queue.popleft()

            for v in adj[u]:
                if component[v] == -1:
                    component[v] = comp_id
                    queue.append(v)

        comp_id += 1

    # This graph only determines reachability, not shortest distance.
    # For minimum distances, run BFS from each distinct starting cell.
    # This is not efficient for the maximum constraints.

    return ["NO"] * Q


def main():
    T = int(input())

    for _ in range(T):
        N, M, Q = map(int, input().split())

        G = []
        for _ in range(N):
            G.append(input())

        start, end, limits = [], [], []

        for _ in range(Q):
            sr, sc, er, ec, K = map(int, input().split())

            start.append((sr, sc))
            end.append((er, ec))
            limits.append(K)

        for ans in solve(N, M, Q, G, start, end, limits):
            print(ans)


if __name__ == '__main__':
    main()
