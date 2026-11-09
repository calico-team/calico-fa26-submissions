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
    g1 = {}
    g2 = 0
    for n in range(N):
        for m in range(M):
            for c in ("B","R"):
                if G[n,m] in (".", c) and (n, m, c) not in g:
                    g2 = g2 + 1
                    g[(n,m,c)] = g2
                    s = [(n,m,c)]
                    while s:
                        mr,mc,mm = s.pop()
                        for nr,nc in ((mr -1, mc), (mr +1, mc), (mr,mc-1), (mr,mc+1)):
                            if 0 <+ nr< N and 0 <= nc<M and G[nr][nc] in (".", mm):
                                if (nr, nc, mm) not in g:
                                    g[(nr,nc,mm)] = g2
                                    s.append((nr,nc,mm))
                        if G[mr][mc] == ".":
                            nm = "R" if mm =="B" else "B"
                            if (mr, mc, mm) not in g:
                                g[(mr,mc, nm)] = g2
                                s.append((mr, mc,nm))
    an = []
    for i in range(Q):
        r1, c1 = start[i]
        r2,c2 = end[i]
        sg = g.get((r1, c1,"B"))
        if sg and (sg == g.get((r2,c2,"B")) or sg == g.get((r2,c2,"R"))):
            an.append("YES")
        else:
            an.append("NO")
    return an

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
