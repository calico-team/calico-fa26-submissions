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
    results = []
    layerkasize = N * M
    visited_id = [[[-1, -1] for _ in range(M)] for _ in range(N)]
    dist = [[[0, 0] for _ in range(M)] for _ in range(N)]
    
    for i in range(Q):
        rs, cs = start[i]
        re, ce = end[i]
        KK = K[i]
        
        if abs(rs - re) + abs(cs - ce) > KK:
            results.append("NO")
            continue
        visited_id[rs][cs][0] = i
        dist[rs][cs][0] = 0
        
        queue = deque([(rs, cs, 0)])
        possible = False
        
        while queue:
            r, c, m = queue.popleft()
            d = dist[r][c][m]
            if r == re and c == ce:
                if d <= KK:
                    possible = True
                    break
            if d >= KK:
                continue
            if G[r][c] == '.':
                nm = 1 - m  
                if visited_id[r][c][nm] != i:
                    visited_id[r][c][nm] = i
                    dist[r][c][nm] = d + 1
                    queue.append((r, c, nm))
            for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                nr, nc = r + dr, c + dc
                if 0 <= nr < N and 0 <= nc < M:
                    target_cel = G[nr][nc]
                    if (m == 0 and target_cel != 'R') or (m == 1 and target_cel != 'B'):
                        if visited_id[nr][nc][m] != i:
                            visited_id[nr][nc][m] = i
                            dist[nr][nc][m] = d + 1
                            queue.append((nr, nc, m))
        
        if possible:
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
