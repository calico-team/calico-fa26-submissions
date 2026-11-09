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
    
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    
    # initialize array
    array = []
    for i in range(0, N):
        row = []
        for j in range(0, M):
            row.append(-1)
        array.append(row)
    
    # assign labels
    currentLabel = 0
    for x in range(0, N):
        for y in range(0, M):
            if(array[x][y] == -1):
                array[x][y] = currentLabel
                pending = [(x, y)]
                
                while len(pending) > 0:
                    item = pending.pop()
                    
                    for direction in directions:
                        neighbor = (item[0] + direction[0], item[1] + direction[1])
                        nx = neighbor[0]
                        ny = neighbor[1]
                        
                        if not (nx < 0 or nx >= N or ny < 0 or ny >= M):
                            if array[nx][ny] == -1:
                                itemcolor = G[item[0]][item[1]]
                                neighborcolor = G[nx][ny]
                                if itemcolor == neighborcolor or itemcolor == "." or neighborcolor == ".":
                                    array[nx][ny] = currentLabel
                                    pending.append(neighbor)
                
                currentLabel += 1
                
                
    # solve queries?
    answers = []
    for i in range(0, Q):
        if array[start[i][0]][start[i][1]] == array[end[i][0]][end[i][1]]:
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
