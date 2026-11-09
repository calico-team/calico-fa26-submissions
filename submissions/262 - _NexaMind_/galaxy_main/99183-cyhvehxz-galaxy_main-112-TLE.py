from collections import deque, defaultdict
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
    start_to_queries = defaultdict(list)
    for i, (s, e) in enumerate(zip(start, end)):
        start_to_queries[s].append((e, i))
        
    answers = [None] * Q
    visited = [[[0] * 2 for _ in range(M)] for _ in range(N)]
    run_id = 0
    for s, queries in start_to_queries.items():
        r1, c1 = s
        run_id += 1
        queue = deque()
        
        queue.append((r1, c1, 0))
        visited[r1][c1][0] = run_id
        
        while queue:
            r, c, mode = queue.popleft()
            if G[r][c] == '.':
                nxt_mode = 1 - mode
                if visited[r][c][nxt_mode] != run_id:
                    visited[r][c][nxt_mode] = run_id
                    queue.append((r, c, nxt_mode))
            for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                nr, nc = r + dr, c + dc
                if 0 <= nr < N and 0 <= nc < M:
                    tile = G[nr][nc]
                    active = False
                    if tile == '.':
                        active = True
                    elif tile == 'B' and mode == 0:
                        active = True
                    elif tile == 'R' and mode == 1:
                        active = True
                    if active and visited[nr][nc][mode] != run_id:
                        visited[nr][nc][mode] = run_id
                        queue.append((nr, nc, mode))
        for (r2, c2), idx in queries:
            if r1 == r2 and c1 == c2:
                answers[idx] = "YES"
            elif visited[r2][c2][0] == run_id or visited[r2][c2][1] == run_id:
                answers[idx] = "YES"
            else:
                answers[idx] = "NO"
    return answers

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
