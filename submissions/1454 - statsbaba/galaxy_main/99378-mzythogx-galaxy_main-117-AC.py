import sys


def find_root(parent, node):
    while parent[node] != node:
        parent[node] = parent[parent[node]]
        node = parent[node]
    return node


def join_sets(parent, size, first, second):
    root_first = find_root(parent, first)
    root_second = find_root(parent, second)

    if root_first == root_second:
        return

    if size[root_first] < size[root_second]:
        root_first, root_second = root_second, root_first

    parent[root_second] = root_first
    size[root_first] += size[root_second]


def solve():
    data = sys.stdin.buffer.read().split()
    if not data:
        return

    token_index = 0
    test_cases = int(data[token_index])
    token_index += 1

    final_answers = []

    for _ in range(test_cases):
        rows = int(data[token_index])
        cols = int(data[token_index + 1])
        query_count = int(data[token_index + 2])
        token_index += 3

        grid = []
        for _ in range(rows):
            row_string = data[token_index].decode()
            token_index += 1
            grid.append(row_string)

        total_cells = rows * cols
        total_states = total_cells * 2

        parent = list(range(total_states))
        size = [1] * total_states

        # A normal tile allows switching between blue and red mode.
        for row in range(rows):
            for col in range(cols):
                if grid[row][col] == '.':
                    cell = row * cols + col
                    blue_state = cell * 2
                    red_state = blue_state + 1
                    join_sets(parent, size, blue_state, red_state)

        # Add movement edges for blue mode and red mode.
        for row in range(rows):
            for col in range(cols):
                cell = row * cols + col
                blue_state = cell * 2
                red_state = blue_state + 1
                current_tile = grid[row][col]

                # Blue mode: normal and blue tiles are active.
                if current_tile != 'R':
                    if row + 1 < rows and grid[row + 1][col] != 'R':
                        next_cell = (row + 1) * cols + col
                        join_sets(parent, size, blue_state, next_cell * 2)

                    if col + 1 < cols and grid[row][col + 1] != 'R':
                        next_cell = row * cols + (col + 1)
                        join_sets(parent, size, blue_state, next_cell * 2)

                # Red mode: normal and red tiles are active.
                if current_tile != 'B':
                    if row + 1 < rows and grid[row + 1][col] != 'B':
                        next_cell = (row + 1) * cols + col
                        join_sets(parent, size, red_state, next_cell * 2 + 1)

                    if col + 1 < cols and grid[row][col + 1] != 'B':
                        next_cell = row * cols + (col + 1)
                        join_sets(parent, size, red_state, next_cell * 2 + 1)

        for _ in range(query_count):
            start_row = int(data[token_index])
            start_col = int(data[token_index + 1])
            end_row = int(data[token_index + 2])
            end_col = int(data[token_index + 3])
            token_index += 4

            start_cell = start_row * cols + start_col
            start_state = start_cell * 2  # Start in blue mode.

            start_root = find_root(parent, start_state)

            end_cell = end_row * cols + end_col
            end_tile = grid[end_row][end_col]

            possible_end_states = []

            if end_tile == 'B':
                possible_end_states.append(end_cell * 2)
            elif end_tile == 'R':
                possible_end_states.append(end_cell * 2 + 1)
            else:
                possible_end_states.append(end_cell * 2)
                possible_end_states.append(end_cell * 2 + 1)

            reachable = False
            for end_state in possible_end_states:
                if find_root(parent, end_state) == start_root:
                    reachable = True
                    break

            final_answers.append("YES" if reachable else "NO")

    sys.stdout.write("\n".join(final_answers))


if __name__ == "__main__":
    solve()