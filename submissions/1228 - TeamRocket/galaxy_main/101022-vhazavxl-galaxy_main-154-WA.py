from collections import deque
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
    results=[]
    for i in range(Q):
        solved=False
        q=deque([(start[i][0],start[i][1])])
        visited=[[False]*M for _ in range(N)]
        directions=[(0,1),(0,-1),(1,0),(-1,0)]
        while q:
            x,y=q.popleft()
            if (x,y)==(end[i][0],end[i][1]):
                results.append("YES")
                solved=True
                break
            if G[x][y]==".":
                for mode in ["R","B"]:
                    for dir in directions:
                        newx,newy=x+dir[0],y+dir[1]
                        if 0<=newx<N and 0<=newy<M and visited[newx][newy]==False and (G[newx][newy]=="." or G[newx][newy]==mode):
                            q.append((newx,newy))
                            visited[newx][newy]=True
            else:
                for dir in directions:
                    newx,newy=x+dir[0],y+dir[1]
                    if 0<=newx<N and 0<=newy<M and visited[newx][newy]==False and (G[newx][newy]=="." or G[newx][newy]==mode):
                        q.append((newx,newy))
                        visited[newx][newy]=True
        if not solved:
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
