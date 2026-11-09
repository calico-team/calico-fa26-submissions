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

    for i in range(Q):
        vu=[[[0,0] for i in range(M)] for j in range(N)]
        er,ec=end[i]
        m=1 if G[er][ec]=="R" else 0
        q=[(er,ec,m)]
        h=0
        vu[er][ec][m]= 1
        diddy=[(1,0),(-1,0),(0,1),(0,-1)]
        while h < len(q):
            r,c,m = q[h]
            h+=1
            if G[r][c] == ".":
                other = 1-m
                if not vu[r][c][other]:
                    vu[r][c][other] = vu[r][c][m] + 1
                    q.append((r,c,other))
            for dr, dc in diddy:
                nr = r + dr
                nc = c +dc
                if 0 <= nr < N and 0 <= nc < M:
                    tile = G[nr][nc]
                    if m == 0 and tile == "R":continue
                    if m == 1 and tile == 'B':continue
                    if not vu[nr][nc][m]:
                        vu[nr][nc][m]=vu[r][c][m]+1
                        q.append((nr,nc,m))
        sr,sc = start[i]
        ret = []

        if vu[sr][sc][0] and vu[sr][sc][0] - 1 <= K[i]:ret.append("YES")        
        else:ret.append("NO")
    return ret
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
