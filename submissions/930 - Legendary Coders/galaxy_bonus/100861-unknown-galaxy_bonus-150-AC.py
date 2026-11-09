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
    blue=0
    red=1
    def is_active(row, col, mode):
        tile=G[row][col]
        if tile=='.':
            return True
        if tile=='B' and mode==0:
            return True
        if tile=='R' and mode==1:
            return True
        else:
            return False
    component = [[[-1, -1] for _ in range(M)] for _ in range(N)]
    directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]
    next_component_id = 0
    for row in range(N):
        for col in range(M):
            for mode in [blue, red]:
                if is_active(row, col, mode) and component[row][col][mode] == -1:
                    queue=[(row, col, mode)]
                    component[row][col][mode] = next_component_id
                    x=0
                    while x<len(queue):
                        roww, coll, modee = queue[x]
                        x += 1

                        for dr, dc in directions:
                            nroww = roww + dr
                            ncoll = coll + dc

                            if 0 <= nroww < N and 0 <= ncoll < M:
                                if is_active(nroww, ncoll, modee):
                                    if component[nroww][ncoll][modee] == -1:
                                        component[nroww][ncoll][modee] = next_component_id
                                        queue.append((nroww, ncoll, modee))

                        # Spin on a normal tile to switch modes.
                        if G[roww][coll] == ".":
                            other_mode = 1 - modee

                            if component[roww][coll][other_mode] == -1:
                                component[roww][coll][other_mode] = next_component_id
                                queue.append((roww, coll, other_mode))

                    next_component_id += 1
                    
    answers = []

    for i in range(Q):
        initial_row, initial_col = start[i]
        end_row, end_col = end[i]

        start_component = component[initial_row][initial_col][blue]

        can_reach = False

        for mode in [blue, red]:
            if is_active(end_row, end_col, mode):
                if component[end_row][end_col][mode] == start_component:
                    can_reach = True

        answers.append("YES" if can_reach else "NO")

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