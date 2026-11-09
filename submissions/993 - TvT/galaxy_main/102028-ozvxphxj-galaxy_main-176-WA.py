parent = []
size = []

def find(i):
    if parent[i] == i:
        return i
    parent[i] = find(parent[i])
    return parent[i]

def union(i, j):
    i = find(i)
    j = find(j)
    if i != j:
       if size[i] < size[j]:
           i,j = j,i
    parent[j] = i
    size[i] += size[j]

def solve(N: int, M: int, Q: int, G: list[str], start: list[tuple[int, int]], end: list[tuple[int, int]]) -> list[str]:
    global parent, size

    T_Nodes = 2*N*M
    parent=list(range(T_Nodes))
    size=[1]*T_Nodes

    def getid(r,c,mode):
        return(r*M+c)*2+mode

    for r in range(N):
        for c in range(M):
            tile = G[r][c]

            if tile in '.B':

                if tile == '.':
                    union(getid(r,c,0),getid(r,c,1))
                if c + 1 < M and G[r] [c+1] in '.B':
                    union(getid(r,c,0),getid(r,c,0))
                if r + 1 < N and G[r+1] [c] in '.B':
                    union(getid(r,c,0),getid(r+1,c,1))

            if tile in '.R':

                if c + 1 < M and G[r][c + 1] in '.R':
                    union(getid(r, c, 0), getid(r, c, 0))
                if r + 1 < N and G[r + 1][c] in '.R':
                    union(getid(r, c, 0), getid(r + 1, c, 1))

    ans = []
    for i in range (Q):
        rs,cs = start[i]
        re,ce = end[i]

        start_root = find(getid(rs,cs,0))
        dest_tile = G[re][ce]

        if dest_tile == '.':
            if find(getid(re,ce,0)) == start_root or find(getid(rs,cs,0)) == start_root:
                ans.append("YES")
            else:
                ans.append("NO")
        elif dest_tile == 'B':
            if find(getid(re,ce,0)) == start_root:
                ans.append("YES")
            else:
                ans.append("NO")
        else:
            if find(getid(re,ce,1)) == start_root:
                ans.append("YES")
            else:
                ans.append("NO")

    return ans

def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        G = []
        L = []
        for _ in range(N):
            G.append(input())
        start, end = [], []
        for _ in range(Q):
            start_row, start_col, end_row, end_col = map(int, input().split())
            start.append((start_row, start_col))
            end.append((end_row, end_col))
        for s in solve(N, M, Q, G, start, end):
            L.append(s)
            print(s)

if __name__ == '__main__':
    main()
