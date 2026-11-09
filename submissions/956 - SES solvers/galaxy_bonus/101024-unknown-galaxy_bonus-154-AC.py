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
    tot=N*M*2
    prnt=list(range(tot))
    size=[1]*tot

    def find(x):
        while prnt[x]!=x:
            prnt[x]=prnt[prnt[x]]
            x=prnt[x]
        return x

    def union(a,b):
        a=find(a)
        b=find(b)
        if a==b:
            return
        if size[a]<size[b]:
            a,b=b,a
        prnt[b]=a
        size[a]+=size[b]

    def get_id(r,c, mode):
        return (r*M+c)*2+mode

    def active(r,c,mode):
        if G[r][c]=='.':
            return True
        if mode==0 and G[r][c]=='B':
            return True
        if mode==1 and G[r][c]=='R':
            return True
        return False
    for r in range(N):
        for c in range(M):
            if G[r][c]=='.':
                union(get_id(r,c,0),get_id(r,c,1))

            for mode in range(2):
                if not active(r,c,mode):
                    continue
                if c+1<M and active(r,c+1,mode):
                    union(
                        get_id(r,c,mode),
                        get_id(r,c+1,mode)
                    )
                if r+1<N and active(r+1,c,mode):
                    union(
                        get_id(r,c,mode),
                        get_id(r+1,c,mode)
                    )
    answer=[]
    for i in range(Q):
        sr,sc=start[i]
        er,ec=end[i]

        source= find(get_id(sr,sc,0))
        blue_destination=get_id(er,ec,0)
        red_destination=get_id(er,ec,1)

        if (active(er,ec,0) and source==find(blue_destination)) or (active(er,ec,1) and source==find(red_destination)):
            answer.append("YES")
        else:
            answer.append("NO")
    return answer


                

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
