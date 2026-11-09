# def solve(num_row: int, num_col: int, Q: int, G: list[str], start: list[tuple[int, int]], end: list[tuple[int, int]]) -> list[str]:
#     """
#     Return an array of Q strings, the i-th of which is "YES"
#     if Big Ben can travel from start[i] to end[i], and "NO"
#     otherwise.

#     N: the number of rows in the grid
#     M: the number of columns in the grid
#     Q: the number of queries
#     G: the grid, where each tile is 'R', 'B', or '.'
#     start: the (row, column) of the starting tile of each query
#     end: the (row, column) of the ending tile of each query
#     """
#     answers = []

#     for i in range(Q):
#         start_pos = start[i]
#         end_pos = end[i]

#         # if is_possible(G, start_pos, end_pos, True, start_pos) or is_possible(G, start_pos, end_pos, False, start_pos):
#         #     answers.append("YES")
#         # else:
#         #     answers.append("NO")
        
#         possible = False
#         for dir in directions:
#             new_pos = (start_pos[0] + dir[0], start_pos[1] + dir[1])
#             if 0 <= new_pos[0] < num_row and 0 <= new_pos[1] < num_col:
#                 if G[new_pos[0]][new_pos[1]] == "R":
#                     if is_possible(G, new_pos, end_pos, False, {start_pos}, num_row, num_col):
#                         # answers.append("YES")
#                         possible = True
#                         break
#                 elif is_possible(G, new_pos, end_pos, True, {start_pos}, num_row, num_col):
#                     # answers.append("YES")
#                     possible = True
#                     break

#         if possible:
#             answers.append("YES")
#         else:
#             answers.append("NO")


#     return answers

def solve(num_row, num_col, G, start, end):
    components = {}
    component_id = 0

    for r in range(num_row):
        for c in range(num_col):
            for is_blue in (True, False):
                state = (r, c, is_blue)

                if state in components:
                    continue

                tile = G[r][c]

                if tile == "R" and is_blue:
                    continue
                if tile == "B" and not is_blue:
                    continue

                stack = [state]
                components[state] = component_id

                while stack:
                    cr, cc, mode = stack.pop()

                    # Toggle modes on normal tiles
                    if G[cr][cc] == ".":
                        next_state = (cr, cc, not mode)

                        if next_state not in components:
                            components[next_state] = component_id
                            stack.append(next_state)

                    # Move to adjacent active tiles
                    for dr, dc in directions:
                        nr, nc = cr + dr, cc + dc

                        if not (0 <= nr < num_row and 0 <= nc < num_col):
                            continue

                        neighbor = G[nr][nc]

                        if neighbor == "R" and mode:
                            continue
                        if neighbor == "B" and not mode:
                            continue

                        next_state = (nr, nc, mode)

                        if next_state not in components:
                            components[next_state] = component_id
                            stack.append(next_state)

                component_id += 1

    answers = []

    for s, e in zip(start, end):
        start_state = (s[0], s[1], True)

        end_blue = (e[0], e[1], True)
        end_red = (e[0], e[1], False)

        start_component = components[start_state]

        if (components.get(end_blue) == start_component or
                components.get(end_red) == start_component):
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
        for s in solve(N, M, G, start, end):
            print(s)

if __name__ == '__main__':
    main()
