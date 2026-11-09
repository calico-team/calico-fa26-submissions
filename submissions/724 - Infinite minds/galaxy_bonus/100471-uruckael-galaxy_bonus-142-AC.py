def solve(N: int, M: int, Q: int, G: list[str], start: list[tuple[int, int]], end: list[tuple[int, int]]) -> list[str]:
    NM = N*M
    parent = list(range(2*NM))
    def find(x):
        root = x
        while parent[root]!=root:
            root = parent[root]
        while parent[x]!= root:
            parent[x], x = root, parent[x]
        return root
    def union(a, b):
        a = find(a)
        b = find(b)
        if a!=b:
            parent[a] = b
    for r in range(N):
        for c in range(M):
            ch = G[r][c]
            i = r*M+c
            if ch=='.':
                union(i, NM+i)
            for nr, nc in ((r, c+1), (r+1, c)):
                if nr<N and nc<M:
                    ch2 = G[nr][nc]
                    j = nr*M+nc
                    if ch!= "R" and ch2!="R":
                        union(i, j)
                    if ch!="B" and ch2!="B":
                        union(NM+i, NM+j)
    def node(r,c):
        i = r*M+c
        return NM+i if G[r][c] =="R" else i
    res = []
    for k in range(Q):
        sr, sc = start[k]
        er, ec = end[k]
        res.append("YES" if find(node(sr, sc))==find(node(er, ec)) else "NO")
    return res

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
