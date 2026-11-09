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
    from collections import deque
    def bfs(s_r, s_c, e_r, e_c):
        if G[s_r][s_c] != '.' :
            return False
        
        SEEN = set()
        q = deque([(s_r, s_c, 0)])
        SEEN.add((s_r, s_c, 0))

        moves = [(0,1), (0,-1), (1,0), (-1,0)]
        
        while q:
            r, c, mode = q.popleft()
            if (r, c) == (e_r, e_c):
                return True

            if G[r][c] == '.':
                next_state = (r,c,1-mode)
                if next_state not in SEEN:
                    SEEN.add(next_state)
                    q.append(next_state)
                    
            for dr, dc in moves:
                nr, nc = r + dr, c + dc

                if 0 <= nr < N and 0 <= nc < M :
                    cell= G[nr][nc]
                    if cell == '.' or (mode == 0 and cell == 'B') or (mode == 1 and cell == 'R'):
                        next_state = (nr, nc, mode)

                        if next_state not in SEEN:
                            SEEN.add(next_state)
                            q.append(next_state)      
        return False
    results = []
    for i in range(Q):
        s_r, s_c = start[i]
        e_r, e_c = end[i]
        if bfs(s_r, s_c, e_r, e_c):
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
