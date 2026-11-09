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
    master = list(range(N * M * 2))

    def root(node):
        while master[node] != node:
            master[node] = master[master[node]]
            node = master[node]
        return node

    def join(p, q):
        rp, rq = root(p), root(q)
        if rp != rq:
            master[rp] = rq

    def usable(tile, phase):
        return tile == '.' or (tile =='B' and phase == 0) or (tile == 'R' and phase == 1)

    for y in range(N):
        
        straightline = G[y]

        for x in range(M):

            headstart = straightline[x]
            point = y * M + x
            if headstart == '.':
                join(point * 2, point * 2 + 1)
            for space in (0, 1):
                if not usable(headstart, space):
                    continue
                if x + 1 < M and usable(straightline[x + 1], space):
                    join(point * 2 + space, (point + 1) * 2 + space)
                if y + 1 < N and usable(G[y + 1][x], space):
                    join(point * 2 + space, (point + M) * 2 + space )

    endsolution =[]
    for (oy, ox), (ty, tx) in zip(start,end):

        house = (oy * M + ox) * 2

        target = ty * M + tx

        goal_target = 1 if G[ty][tx] == 'R' else 0

        combined = root(house) == root(target * 2 + goal_target)

        endsolution.append("YES" if combined else "NO")
    return endsolution  
    

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
