from collections import deque
import sys

# Increase recursion/input speed for large Q (up to 10^5)
input = lambda: sys.stdin.readline().rstrip('\r\n')

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

    comp = [[[-1, -1] for _ in range(M)] for _ in range(N)]
    comp_id = 0
    queue = deque()

    for r0 in range(N):
        for c0 in range(M):
            for mode0 in (0, 1):
                if comp[r0][c0][mode0] != -1:
                    continue
                active_color0 = 'B' if mode0 == 0 else 'R'
                if G[r0][c0] != '.' and G[r0][c0] != active_color0:
                    continue

                comp[r0][c0][mode0] = comp_id
                queue.append((r0, c0, mode0))

                while queue:
                    r, c, mode = queue.popleft()

                    # spin action
                    if G[r][c] == '.' and comp[r][c][1 - mode] == -1:
                        comp[r][c][1 - mode] = comp_id
                        queue.append((r, c, 1 - mode))

                    # move to adjacent active tiles in active mode
                    active_color = 'B' if mode == 0 else 'R'
                    for dr, dc in ((-1, 0), (1, 0), (0, -1), (0, 1)):
                        nr, nc = r + dr, c + dc
                        if 0 <= nr < N and 0 <= nc < M and comp[nr][nc][mode] == -1:
                            if G[nr][nc] == '.' or G[nr][nc] == active_color:
                                comp[nr][nc][mode] = comp_id
                                queue.append((nr, nc, mode))

                comp_id += 1

    ans = []
    for (sr, sc), (er, ec) in zip(start, end):
        c_start = comp[sr][sc][0]
        if c_start != -1 and (comp[er][ec][0] == c_start or comp[er][ec][1] == c_start):
            ans.append("YES")
        else:
            ans.append("NO")
    return ans

def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        G = []
        for _ in range(N):
            G.append(input())
        start, end = [], []
        for _ in range(Q):
            start_row, start_col, end_row, end_col = map(int, input().split())
            start.append((start_row, start_col))
            end.append((end_row, end_col))
        for s in solve(N, M, Q, G, start, end):
            print(s)

if __name__ == '__main__':
    main()
