class DSU:
    def __init__(self, n):
        self.parent = list(range(n))
        
    def find(self, i):
        if self.parent[i] == i:
            return i
        self.parent[i] = self.find(self.parent[i])
        return self.parent[i]
        
    def unite(self, i, j):
        root_i = self.find(i)
        root_j = self.find(j)
        if root_i != root_j:
            self.parent[root_i] = root_j

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
    layerkasize = N * M
    dsu = DSU(2 * layerkasize)
    
    def getnode(r, c, mode):
        return mode * layerkasize + r * M + c
    for r in range(N):
        for c in range(M):
            if G[r][c] == '.':
                dsu.unite(getnode(r, c, 0), getnode(r, c, 1))
            if c + 1 < M:
                if G[r][c] in 'B.' and G[r][c+1] in 'B.':
                    dsu.unite(getnode(r, c, 0), getnode(r, c+1, 0))
                if G[r][c] in 'R.' and G[r][c+1] in 'R.':
                    dsu.unite(getnode(r, c, 1), getnode(r, c+1, 1))
            if r + 1 < N:
                if G[r][c] in 'B.' and G[r+1][c] in 'B.':
                    dsu.unite(getnode(r, c, 0), getnode(r+1, c, 0))
                if G[r][c] in 'R.' and G[r+1][c] in 'R.':
                    dsu.unite(getnode(r, c, 1), getnode(r+1, c, 1))   
    results = []
    for i in range(Q):
        rs, cs = start[i]
        re, ce = end[i]
        startnode = getnode(rs, cs, 0)
        flg = False
        if G[re][ce] in '.B':
            if dsu.find(startnode) == dsu.find(getnode(re, ce, 0)):
                flg = True
        if G[re][ce] in '.R':
            if dsu.find(startnode) == dsu.find(getnode(re, ce, 1)):
                flg = True
                
        if flg:
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
