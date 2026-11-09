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
    directions = [(1,0), (-1,0),(0,1),(0,-1)]
    component = [[[-1,-1] for _ in range(M)] for _ in range(N)]
    
    componentID = 0
    for row in range(N):
        for col in range(M):
            for mode in range(2):
                tile = G[row][col]
                valid = (tile == "." or (tile == "B" and mode == 0) or (tile == "R" and mode == 1))
                if not valid:
                    continue
                if component[row][col][mode] != -1:
                    continue
                
                queue = deque([(row, col, mode)])
                component[row][col][mode] = componentID
                
                while queue:
                    cr, cc, cmode = queue.popleft()

                    if G[cr][cc] == ".":
                        other = 1 - cmode

                        if component[cr][cc][other] == -1:
                            component[cr][cc][other] = componentID
                            queue.append((cr, cc, other))

                    for directionR, directionC in directions:
                        nr = cr + directionR
                        nc = cc + directionC

                        if not (0 <= nr < N and 0 <= nc < M):
                            continue

                        tile = G[nr][nc]

                        canMove = (tile == "." or (tile == "R" and cmode == 1) or (tile == "B" and cmode == 0))

                        if canMove and component[nr][nc][cmode] == -1:
                            component[nr][nc][cmode] = componentID
                            queue.append((nr, nc, cmode))

                componentID += 1
    
    answers = []
    
    for i in range(Q):
        sourceR, sourceC = start[i]
        endR, endC = end[i]
        startID = component[sourceR][sourceC][0]
        
        if (startID == component[endR][endC][0] or startID == component[endR][endC][1]):
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
