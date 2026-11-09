def solve(N: int, M: int, Q: int, G: list[str], start: list[tuple[int, int]], end: list[tuple[int, int]]):
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
    ans = []
    for trial in range(Q):
        sx = start[trial][0]
        sy = start[trial][1]
        ex = end[trial][0]
        ey = end[trial][1]
        latest = ()
        toAns = "YES"
        while True:
          cur = (G[sx])[sy]
          if (sx,sy) == (ex,ey):
            break
          right = int(sy+1<M and(cur != (G[sx])[sy+1] or (G[sx])[sy+1]==".") and (G[sx])[sy+1]!="X")
          left = int(sy-1<M and(cur != (G[sx])[sy-1] or (G[sx])[sy-1]==".") and (G[sx])[sy-1]!="X" )
          up = int(sx+1<N and(cur != (G[sx+1])[sy] or (G[sx+1])[sy]==".") and (G[sx+1])[sy]!="X")
          down = int(sx-1<N and(cur != (G[sx-1])[sy] or (G[sx-1])[sy]==".") and (G[sx-1])[sy]!="X" ) 
          
          if sum(right,left,up,down) > 1:
            if right and (sx,sy+1) != latest:
              latest = (sx,sy)
              sy+=1
              continue
            elif left and ((sx,sy-1) != latest):
              latest = (sx,sy)
              sy-=1
              continue
            elif up and (sx+1,sy) != latest:
              latest = (sx,sy)
              sx+=1
              continue
            elif down and not ((sx-1,sy) == latest):
              latest = (sx,sy)
              sx-=1
              continue
          if sum(right,left,up,down) >= 1:
              if right and (sx,sy+1) != latest:
                if((sx,sy+1) == latest):
                  G[sx] = (G[sx])[:sy]+"X"+(G[sx])[sy+1:]
                latest = (sx,sy)
                sy+=1
              elif left and ((sx,sy-1) != latest):
                if((sx,sy-1) == latest):
                  G[sx] = (G[sx])[:sy]+"X"+(G[sx])[sy+1:]
                latest = (sx,sy)
                sy-=1
              elif up and (sx+1,sy) != latest:
                if((sx+1,sy) == latest):
                  G[sx] = (G[sx])[:sy]+"X"+(G[sx])[sy+1:]
                latest = (sx,sy)
                sx+=1
              elif down and not ((sx-1,sy) == latest):
                if((sx-1,sy) == latest):
                  G[sx] = (G[sx])[:sy]+"X"+(G[sx])[sy+1:]
                  latest = (sx,sy)
                sx-=1
          else:
            toAns="NO"
            break
             
        ans.append(toAns)
    return ans

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
