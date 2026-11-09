import sys
import math

def solve():
    input_tokens = sys.stdin.buffer.read().split()
    if not input_tokens:
        return

    token_iterator = iter(input_tokens)
    test_case_count = int(next(token_iterator))
    output_lines = []

    for _ in range(test_case_count):
        num_rows = int(next(token_iterator))
        num_cols = int(next(token_iterator))
        num_queries = int(next(token_iterator))

        earthquakes = []
        for _ in range(num_queries):
            epicenter_row = int(next(token_iterator))
            epicenter_col = int(next(token_iterator))
            power = int(next(token_iterator))
            earthquakes.append((epicenter_row, epicenter_col, power))

        was_transposed = False
        if num_rows > num_cols:
            was_transposed = True
            num_rows, num_cols = num_cols, num_rows
            transposed_earthquakes = []
            for epicenter_row, epicenter_col, power in earthquakes:
                transposed_earthquakes.append((epicenter_col, epicenter_row, power))
            earthquakes = transposed_earthquakes

        total_cells = num_rows * num_cols
        final_readings = [-1] * total_cells

        unvisited_parent = [list(range(num_cols + 1)) for _ in range(num_rows)]
        remaining_cells_per_row = [num_cols] * num_rows

        for quake_index in range(num_queries - 1, -1, -1):
            epicenter_row, epicenter_col, power = earthquakes[quake_index]

            row_start = epicenter_row - power
            if row_start < 0:
                row_start = 0
            row_end = epicenter_row + power
            if row_end >= num_rows:
                row_end = num_rows - 1

            power_squared = power * power

            for current_row in range(row_start, row_end + 1):
                if remaining_cells_per_row[current_row] == 0:
                    continue

                row_offset = current_row - epicenter_row
                remaining_squared_distance = power_squared - row_offset * row_offset
                if remaining_squared_distance < 0:
                    continue

                max_col_offset = math.isqrt(remaining_squared_distance)
                left_col = epicenter_col - max_col_offset
                if left_col < 0:
                    left_col = 0
                right_col = epicenter_col + max_col_offset
                if right_col >= num_cols:
                    right_col = num_cols - 1

                if left_col > right_col:
                    continue

                row_parent = unvisited_parent[current_row]

                candidate_col = left_col
                while row_parent[candidate_col] != candidate_col:
                    row_parent[candidate_col] = row_parent[row_parent[candidate_col]]
                    candidate_col = row_parent[candidate_col]

                while candidate_col <= right_col:
                    distance_squared = (row_offset * row_offset +
                                        (candidate_col - epicenter_col) * (candidate_col - epicenter_col))
                    shock_level = power_squared - distance_squared + 1
                    final_readings[current_row * num_cols + candidate_col] = shock_level
                    remaining_cells_per_row[current_row] -= 1

                    next_unvisited = candidate_col + 1
                    while row_parent[next_unvisited] != next_unvisited:
                        row_parent[next_unvisited] = row_parent[row_parent[next_unvisited]]
                        next_unvisited = row_parent[next_unvisited]
                    row_parent[candidate_col] = next_unvisited
                    candidate_col = next_unvisited

        if not was_transposed:
            for row in range(num_rows):
                row_values = []
                row_base = row * num_cols
                for col in range(num_cols):
                    value = final_readings[row_base + col]
                    if value == -1:
                        value = 0
                    row_values.append(str(value))
                output_lines.append(" ".join(row_values))
        else:
            original_num_rows = num_cols
            original_num_cols = num_rows
            transposed_back_readings = [0] * (original_num_rows * original_num_cols)

            for row in range(num_rows):
                row_base = row * num_cols
                for col in range(num_cols):
                    value = final_readings[row_base + col]
                    if value == -1:
                        value = 0
                    transposed_back_readings[col * original_num_cols + row] = value

            for row in range(original_num_rows):
                row_values = []
                row_base = row * original_num_cols
                for col in range(original_num_cols):
                    row_values.append(str(transposed_back_readings[row_base + col]))
                output_lines.append(" ".join(row_values))

    sys.stdout.write("\n".join(output_lines))

if __name__ == "__main__":
    solve()