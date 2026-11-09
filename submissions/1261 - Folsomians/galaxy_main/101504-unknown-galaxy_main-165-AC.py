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
    grid = [list(i) for i in G]
    results = []
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    r_end, c_end = N - 1, M - 1

    visited = [[[False, False] for m in range(M)] for n in range(N)]
    queue = deque()
    if grid[r_end][c_end] == ".":
        visited[r_end][c_end][0] = True
        visited[r_end][c_end][1] = True
        queue.append((r_end, c_end, 0))
        queue.append((r_end, c_end, 1))
    if grid[r_end][c_end] == "B":
        visited[r_end][c_end][0] = True
        queue.append((r_end, c_end, 0))
    if grid[r_end][c_end] == "R":
        visited[r_end][c_end][1] = True
        queue.append((r_end, c_end, 1))

    while queue:
        r, c, mode = queue.popleft()
        if grid[r][c] == ".":
            new_mode = 1 - mode
            if not visited[r][c][new_mode]:
                visited[r][c][new_mode] = True
                queue.append((r, c, new_mode))
        for dr, dc in directions:
            nr, nc = r - dr, c - dc
            if 0 <= nr < N and 0 <= nc < M:
                target = grid[nr][nc]
                active = False
                if target == ".":
                    active = True
                elif target == "B" and mode == 0:
                    active = True
                elif target == "R" and mode == 1:
                    active = True

                if active and not visited[nr][nc][mode]:
                    visited[nr][nc][mode] = True
                    queue.append((nr, nc, mode))
    for i in range(Q):
        r_start, c_start = start[i]
        if visited[r_start][c_start][0]:
            results.append("YES")
        else:
            results.append("NO")
    return results

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
