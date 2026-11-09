import sys


def solve():
    data = sys.stdin.buffer.read().split()
    if not data:
        return

    ptr = 0
    test_cases = int(data[ptr])
    ptr += 1

    answers = []

    for _ in range(test_cases):
        rows = int(data[ptr])
        cols = int(data[ptr + 1])
        queries = int(data[ptr + 2])
        ptr += 3

        grid = []
        for _ in range(rows):
            grid.append(data[ptr].decode())
            ptr += 1

        total_cells = rows * cols
        total_states = total_cells * 2

        parent = list(range(total_states))
        rank = [0] * total_states

        def find(node):
            while parent[node] != node:
                parent[node] = parent[parent[node]]
                node = parent[node]
            return node

        def union(first, second):
            root_first = find(first)
            root_second = find(second)

            if root_first == root_second:
                return

            if rank[root_first] < rank[root_second]:
                root_first, root_second = root_second, root_first

            parent[root_second] = root_first

            if rank[root_first] == rank[root_second]:
                rank[root_first] += 1

        # On a normal tile, Ben can spin to switch between blue and red mode.
        for row in range(rows):
            for col in range(cols):
                if grid[row][col] == '.':
                    cell = row * cols + col
                    blue_state = cell * 2
                    red_state = blue_state + 1
                    union(blue_state, red_state)

        # Connect adjacent cells that are both active in the same mode.
        # Checking only down and right is enough because edges are undirected.
        for row in range(rows):
            for col in range(cols):
                cell = row * cols + col
                blue_state = cell * 2
                red_state = blue_state + 1
                current_tile = grid[row][col]

                # Move down
                if row + 1 < rows:
                    next_cell = (row + 1) * cols + col
                    next_tile = grid[row + 1][col]

                    if current_tile != 'R' and next_tile != 'R':
                        union(blue_state, next_cell * 2)

                    if current_tile != 'B' and next_tile != 'B':
                        union(red_state, next_cell * 2 + 1)

                # Move right
                if col + 1 < cols:
                    next_cell = row * cols + (col + 1)
                    next_tile = grid[row][col + 1]

                    if current_tile != 'R' and next_tile != 'R':
                        union(blue_state, next_cell * 2)

                    if current_tile != 'B' and next_tile != 'B':
                        union(red_state, next_cell * 2 + 1)

        for _ in range(queries):
            start_row = int(data[ptr])
            start_col = int(data[ptr + 1])
            end_row = int(data[ptr + 2])
            end_col = int(data[ptr + 3])
            ptr += 4

            start_cell = start_row * cols + start_col
            start_state = start_cell * 2  # Always start in blue mode
            start_root = find(start_state)

            end_cell = end_row * cols + end_col
            end_tile = grid[end_row][end_col]

            reachable = False

            if end_tile == 'B':
                if find(end_cell * 2) == start_root:
                    reachable = True

            elif end_tile == 'R':
                if find(end_cell * 2 + 1) == start_root:
                    reachable = True

            else:  # Normal tile: either mode is acceptable
                if (find(end_cell * 2) == start_root or
                        find(end_cell * 2 + 1) == start_root):
                    reachable = True

            answers.append("YES" if reachable else "NO")

    sys.stdout.write("\n".join(answers))


if __name__ == "__main__":
    solve()