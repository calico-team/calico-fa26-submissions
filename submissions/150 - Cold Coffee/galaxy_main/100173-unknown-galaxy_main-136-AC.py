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
    total_cells = N*M*2
    par = list(range(total_cells))
    size = [1]*total_cells

    def find(x):
        if par[x] != x:
            par[x] = find(par[x])
        return par[x]
    def union(a,b):
        a = find(a)
        b = find(b)
        if a == b:
            return
        if size[a] < size[b]:
            a,b = b,a
        par[b] = a
        size[a] += size[b]
    def get_id(r,c,mode):
        return mode*(N*M) + r*M + c

    def can_walk(r,c,mode):
        if G[r][c] == '.':
            return True
        if mode == 0:
            return G[r][c] == 'B'
        return G[r][c] == 'R'
    for r in range(N):
        for c in range(M):
            if G[r][c] == '.':
                union(get_id(r,c,0),get_id(r,c,1))
            for dr,dc in [(1,0),(0,1)]:
                nr = r + dr
                nc = c + dc
                if nr < N and nc < M:
                    for mode in range(2):
                        if can_walk(r,c,mode) and can_walk(nr,nc,mode):
                            union(get_id(r,c,mode),get_id(nr,nc,mode))
    results = []
    for i in range(Q):
        s_r, s_c = start[i]
        e_r, e_c = end[i]

        if G[s_r][s_c] != '.':
            results.append("NO")
            continue
        source = find(get_id(s_r,s_c,0))
        possible = False
        for mode in range(2):
            if can_walk(e_r,e_c,mode):
                if source == find(get_id(e_r,e_c,mode)):
                    possible = True
                    break
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
        start, end = [], []
        for _ in range(Q):
            start_row, start_col, end_row, end_col = map(int, input().split())
            start.append((start_row, start_col))
            end.append((end_row, end_col))
        for s in solve(N, M, Q, G, start, end):
            print(s)

if __name__ == '__main__':
    main()
