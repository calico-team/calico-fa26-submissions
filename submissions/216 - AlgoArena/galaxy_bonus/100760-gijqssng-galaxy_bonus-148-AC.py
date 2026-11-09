import sys
from collections import deque


def solve(N: int, M: int, Q: int, G: list[str], start: list[tuple[int, int]], end: list[tuple[int, int]]) -> list[str]:
    def active(r, c, mode):
        return G[r][c] == '.' or G[r][c] == 'BR'[mode]

    comp = [[-1, -1] for _ in range(N * M)]  # component id of (cell, mode)
    count = 0
    for s in range(N * M):
        for mode in (0, 1):
            if comp[s][mode] != -1 or not active(s // M, s % M, mode):
                continue
            comp[s][mode] = count
            queue = deque([(s, mode)])
            while queue:
                cell, m = queue.popleft()
                r, c = divmod(cell, M)
                nxt = [(cell, 1 - m)] if G[r][c] == '.' else []
                for nr, nc in ((r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)):
                    if 0 <= nr < N and 0 <= nc < M and active(nr, nc, m):
                        nxt.append((nr * M + nc, m))
                for ncell, nm in nxt:
                    if comp[ncell][nm] == -1:
                        comp[ncell][nm] = count
                        queue.append((ncell, nm))
            count += 1

    return ["YES" if comp[sr * M + sc][0] in comp[er * M + ec] else "NO"
            for (sr, sc), (er, ec) in zip(start, end)]


def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    iterator = iter(input_data)
    T = int(next(iterator))
    for _ in range(T):
        N = int(next(iterator))
        M = int(next(iterator))
        Q = int(next(iterator))
        G = []
        for _ in range(N):
            G.append(next(iterator))
        start, end = [], []
        for _ in range(Q):
            start_row = int(next(iterator))
            start_col = int(next(iterator))
            end_row = int(next(iterator))
            end_col = int(next(iterator))
            start.append((start_row, start_col))
            end.append((end_row, end_col))

        for s in solve(N, M, Q, G, start, end):
            print(s)


if __name__ == '__main__':
    main()