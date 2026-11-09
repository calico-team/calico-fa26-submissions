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
    visited = [[[False, False] for _ in range(M)] for _ in range(N)]
    queue = deque()

    # destination is always (N - 1, M - 1)
    er, ec = N - 1, M - 1
    if G[er][ec] in ('.', 'B'):
        visited[er][ec][0] = True
        queue.append((er, ec, 0))
    if G[er][ec] in ('.', 'R'):
        visited[er][ec][1] = True
        queue.append((er, ec, 1))

    while queue:
        r, c, mode = queue.popleft()

        # spin action
        if G[r][c] == '.' and not visited[r][c][1 - mode]:
            visited[r][c][1 - mode] = True
            queue.append((r, c, 1 - mode))

        active_color = 'B' if mode == 0 else 'R'
        for dr, dc in ((-1, 0), (1, 0), (0, -1), (0, 1)):
            nr, nc = r + dr, c + dc
            if 0 <= nr < N and 0 <= nc < M and not visited[nr][nc][mode]:
                if G[nr][nc] == '.' or G[nr][nc] == active_color:
                    visited[nr][nc][mode] = True
                    queue.append((nr, nc, mode))

    ans = []
    for sr, sc in start:
        ans.append("YES" if visited[sr][sc][0] else "NO")
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
