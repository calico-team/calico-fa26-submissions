import sys
from collections import deque

BLUE_MODE = 0
RED_MODE = 1
NOT_REACHABLE = -1

test_cases = int(input())
output_lines = []

for test_case in range(test_cases):
    row_count, column_count, query_count = map(int, input().split())

    grid = []
    for row in range(row_count):
        grid.append(input().strip())

    # standing on a tile is fine or if its color matches our mode
    def can_stand_on(row, column, mode):
        tile = grid[row][column]
        if tile == ".":
            return True
        if mode == BLUE_MODE and tile == "B":
            return True
        if mode == RED_MODE and tile == "R":
            return True
        return False

    # region[mode][row][column] tells us which group "standing on this tile in this mode" belongs to. two spots in the same group can reach each other,
    # cause every step and every spin can be undone by repeating
    region = []
    for mode in range(2):
        mode_grid = []
        for row in range(row_count):
            mode_grid.append([NOT_REACHABLE] * column_count)
        region.append(mode_grid)

    region_count = 0

    # the four directions we can walk: down, up, right, left
    row_steps = [1, -1, 0, 0]
    column_steps = [0, 0, 1, -1]

    for mode in range(2):
        for row in range(row_count):
            for column in range(column_count):
                # skip tiles we already grouped, or can't stand on in this mode
                if region[mode][row][column] != NOT_REACHABLE:
                    continue
                if not can_stand_on(row, column, mode):
                    continue
                # start a new group here and flood out from it
                region[mode][row][column] = region_count
                queue = deque()
                queue.append((mode, row, column))

                while queue:
                    current_mode, current_row, current_column = queue.popleft()
                    # spin: 
                    other_mode = 1 - current_mode
                    if grid[current_row][current_column] == ".":
                        if region[other_mode][current_row][current_column] == NOT_REACHABLE:
                            region[other_mode][current_row][current_column] = region_count
                            queue.append((other_mode, current_row, current_column))
                    # walk
                    for direction in range(4):
                        next_row = current_row + row_steps[direction]
                        next_column = current_column + column_steps[direction]

                        # don't walk off the grid
                        if next_row < 0 or next_row >= row_count:
                            continue
                        if next_column < 0 or next_column >= column_count:
                            continue
                        # dont revisit, and dont step on inactive tiles
                        if region[current_mode][next_row][next_column] != NOT_REACHABLE:
                            continue
                        if not can_stand_on(next_row, next_column, current_mode):
                            continue

                        region[current_mode][next_row][next_column] = region_count
                        queue.append((current_mode, next_row, next_column))

                region_count += 1

    for query in range(query_count):
        start_row, start_column, end_row, end_column = map(int, input().split())
        # the start tile is normal, so both of its modes are in the same group
        start_region = region[BLUE_MODE][start_row][start_column]
        # we made it if we can reach the destination in either mode
        end_region_blue = region[BLUE_MODE][end_row][end_column]
        end_region_red = region[RED_MODE][end_row][end_column]

        if start_region == end_region_blue or start_region == end_region_red:
            output_lines.append("YES")
        else:
            output_lines.append("NO")

print("\n".join(output_lines))