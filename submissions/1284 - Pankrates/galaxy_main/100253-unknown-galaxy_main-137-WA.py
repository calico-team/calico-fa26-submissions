def solve(num_row: int, num_col: int, Q: int, G: list[str], start: list[tuple[int, int]], end: list[tuple[int, int]]) -> list[str]:
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
    answers = []

    for i in range(Q):
        start_pos = start[i]
        end_pos = end[i]

        # if is_possible(G, start_pos, end_pos, True, start_pos) or is_possible(G, start_pos, end_pos, False, start_pos):
        #     answers.append("YES")
        # else:
        #     answers.append("NO")
        
        possible = False
        for dir in directions:
            new_pos = (start_pos[0] + dir[0], start_pos[1] + dir[1])
            if 0 <= new_pos[0] < num_row and 0 <= new_pos[1] < num_col:
                if G[new_pos[0]][new_pos[1]] == "R":
                    if is_possible(G, new_pos, end_pos, False, {start_pos}, num_row, num_col):
                        # answers.append("YES")
                        possible = True
                        break
                elif is_possible(G, new_pos, end_pos, True, {start_pos}, num_row, num_col):
                    # answers.append("YES")
                    possible = True
                    break

        if possible:
            answers.append("YES")
        else:
            answers.append("NO")


    return answers

directions = (
    (0, 1),
    (0, -1),
    (1, 0),
    (-1, 0)
)

def is_possible(grid: list[str], current: tuple[int, int], end: tuple[int, int], is_blue: bool, seen: set[tuple[int, int]], width: int, height: int) -> bool:
    # print(f"At: {current} - {"B" if is_blue else "R"}")

    if current == end:
        return True


    for dir in directions:
        new_pos = (current[0] + dir[0], current[1] + dir[1])
        if new_pos not in seen:

            if 0 <= new_pos[0] < width and 0 <= new_pos[1] < height:

                if grid[new_pos[0]][new_pos[1]] == ".":
                    if is_possible(grid, new_pos, end, True, seen | {new_pos}, width, height) or is_possible(grid, new_pos, end, False, seen | {new_pos}, width, height):
                        return True
                elif (is_blue and grid[new_pos[0]][new_pos[1]] == "B") or (not is_blue and grid[new_pos[0]][new_pos[1]] == "R"):
                    if is_possible(grid, new_pos, end, is_blue, seen | {new_pos}, width, height):
                        return True

    return False


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
