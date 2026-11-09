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
    # YOUR CODE HERE
    group = []
    for r in range(N):
        row=[]
        for c in range(M):
            row.append([-1,-1])
        group.append(row)

    def can_stand(r,c,mode):
        title=G[r][c]
        if title=='.':
            return True
        if title=='B' and mode ==0:
            return True
        if title=='R' and mode==1:
            return True
        return False

    directions=[(1,0), (-1,0), (0,1), (0,-1)]
    group_count=0
    for r in range(N):
        for c in range(M):
            for mode in range(2):
                if not can_stand(r, c, mode):
                    continue
                if group[r][c][mode]!=-1:
                    continue

                queue = deque()
                queue.append((r,c,mode))
                group[r][c][mode]=group_count

                while queue:
                    cr, cc, cm=queue.popleft()
                    for dr, dc in directions:
                        nr=cr+dr
                        nc=cc+dc
                        if nr<0 or nr>=N:
                            continue
                        if nc<0 or nc>=M:
                            continue
                        if can_stand(nr,nc,cm) and group[nr][nc][cm]==-1:
                            group[nr][nc][cm] = group_count
                            queue.append((nr,nc,cm))
                    
                    if G[cr][cc] == ".":
                        other = 1-cm

                        if group[cr][cc][other] == -1:
                            group[cr][cc][other] = group_count
                            queue.append((cr,cc,other))
                    
                group_count+=1
    answers=[]
    for i in range(Q):
        sr, sc = start[i]
        er, ec = end[i]

        start_group = group[sr][sc][0]
        if group[er][ec][0] == start_group:
            answers.append("YES")
        elif group[er][ec][1] == start_group:
            answers.append("YES")
        else:
            answers.append("NO")

    return answers
    

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
