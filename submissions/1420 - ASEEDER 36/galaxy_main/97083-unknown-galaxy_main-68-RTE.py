test_cases = int(input())
direction = [(-1, 0), (1, 0), (0, -1), (0, 1)]

for case in range(test_cases):
    n, m, q = map(int, input().split())

    grid = []
    groups = []
    for row in range(n):
        grid.append(input().split())
        groups.append([-1] * m)

    group_number = 0

    for start_row in range(n):
        for start_col in range(m):
            if groups[start_row][start_col] != -1:
                continue
            waiting = [(start_row, start_col)]
            groups[start_row][start_col] = group_number

            while waiting:
                row, col = waiting.pop()

                for row_change, col_change in direction:
                    next_row, next_col = row + row_change, col + col_change

                    if not (0 <= next_row < n and 0 <= next_col < m):
                        continue

                    if groups[next_row][next_col] != -1:
                        continue

                    current_tile = grid[row][col]
                    next_tile = grid[next_row][next_col]

                    if current_tile == "R" and next_tile == "B":
                        continue
                    if current_tile == "B" and next_tile == "R":
                        continue

                    groups[next_row][next_col] = group_number
                    waiting.append((next_row, next_col))

            group_number += 1

    for query in range(q):
        start_row, start_col, end_row, end_col = map(int, input().split())

        if groups[start_row][start_col] == groups[end_row][end_col]:
            print("YES")
        else:
            print("NO")
