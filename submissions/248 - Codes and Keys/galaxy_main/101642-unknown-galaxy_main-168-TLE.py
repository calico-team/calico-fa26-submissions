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
    def area(row, column, mode):
        next_steps = []
        
        up    = (row - 1, column)
        down  = (row + 1, column)
        left  = (row, column - 1)
        right = (row, column + 1)
        
        for move in [up, down, left, right]:
            next_row, next_column = move
            if 0 <= next_row < N and 0 <= next_column < M:
                tile = G[next_row][next_column]
                if tile == '.' or (mode == 0 and tile == 'B') or (mode == 1 and tile == 'R'):
                    next_steps.append((next_row, next_column, mode))
                    
        # Spin on normal tile
        if G[row][column] == '.':
            if mode == 0:
                next_steps.append((row, column, 1))
            else:
                next_steps.append((row, column, 0))
                
        return next_steps

    results = []
    max_steps = 2 * N * M

    for i in range(Q):
        S = start[i]
        start_row = S[0]
        start_column = S[1]
        
        goal = end[i]
        goal_row = goal[0]
        goal_column = goal[1]
        
        next_steps = [(start_row, start_column, 0)]
        visited = set([(start_row, start_column, 0)])
        step_taken = 0
        found = False

        while len(next_steps) > 0 and step_taken < max_steps:
            row, column, mode = next_steps.pop(0)
            step_taken += 1

            if row == goal_row and column == goal_column:
                found = True
                break

            for move in area(row, column, mode):
                if move not in visited:
                    visited.add(move)
                    next_steps.append(move)

        if found:
            results.append("YES")
        else:
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
