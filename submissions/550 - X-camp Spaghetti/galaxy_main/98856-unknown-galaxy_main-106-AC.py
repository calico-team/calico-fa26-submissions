
from collections import deque

def solve(N: int, M: int, Q: int, G: list[str], start: list[tuple[int, int]], end: list[tuple[int, int]]) -> list[str]:
    """
    Return an array of Q strings, the i-th of which is "YES"
    if Big Ben can travel from start[i] to end[i], and "NO"
    otherwise.

    N: the number of rows in the grid
    M: the number of columns in the grid
    Q: the number of queries
    G: the grid, where each tile is 'R', 'B', or '.'
    start: the (row, column) of the starting tile of each query
    end: the (row, column) of the ending tile of each query
    """
    # YOUR CODE HERE

    moves = [(-1, 0), (1, 0), (0, -1), (0, 1)]

    reach = [[[False, False] for i in range(M)] for j in range(N)]

    for first in range(2):

        if G[N - 1][M - 1] == "R" and first == 0:
            continue

        if G[N - 1][M - 1] == "B" and first == 1:
            continue

        seen = [[[False, False] for i in range(M)] for j in range(N)]

        q = deque()
        q.append((N - 1, M - 1, first))
        seen[N - 1][M - 1][first] = True

        while q:
            r, c, mode = q.popleft()

            reach[r][c][mode] = True

            if G[r][c] == ".":
                other = 1 - mode

                if not seen[r][c][other]:
                    seen[r][c][other] = True
                    q.append((r, c, other))

            for dr, dc in moves:
                nr = r + dr
                nc = c + dc

                if nr < 0 or nr >= N or nc < 0 or nc >= M:
                    continue

                if seen[nr][nc][mode]:
                    continue

                tile = G[nr][nc]

                if tile == ".":
                    seen[nr][nc][mode] = True
                    q.append((nr, nc, mode))

                elif tile == "B" and mode == 0:
                    seen[nr][nc][mode] = True
                    q.append((nr, nc, mode))

                elif tile == "R" and mode == 1:
                    seen[nr][nc][mode] = True
                    q.append((nr, nc, mode))

    ans = []

    for i in range(Q):
        r, c = start[i]

        if reach[r][c][0]:
            ans.append("YES")
        else:
            ans.append("NO")

    return ans

def main():
    T = int(input())
    for i in range(T):
        N, M, Q = map(int, input().split())
        G = []
        for i in range(N):
            G.append(input())
        start, end = [], []
        for i in range(Q):
            sr, sc, er, ec = map(int, input().split())
            start.append((sr, sc))
            end.append((er, ec))
        for s in solve(N, M, Q, G, start, end):
            print(s)

if __name__ == '__main__':
    main()
