"""
*Return an N by M grid displaying the reading of the block seismometers after all earthquakes occur.
*
*N: number of rows in the grid
*M: number of columns in the grid
*Q: number of earthquakes
*earthquakes: a list of tuples (X, Y, P), where:
*    X: column of the epicenter
*    Y: row of the epicenter
*    P: power of the earthquake
"""
def solve(N, M, Q, earthquakes):
    # YOUR CODE HERE
    readings = [0] * (N * M)
    next_unset_col = list(range(M + 1)) * N
    finished_cells = 0
    cell_count = N * M
    processed_disks = set()

    for i in range(Q - 1, -1, -1):
        if finished_cells == cell_count:
            break

        epicenter_row, epicenter_col, power = earthquakes[i]
        disk_key = (epicenter_row, epicenter_col, power)
        if disk_key in processed_disks:
            continue
        processed_disks.add(disk_key)

        power_squared = power * power
        horizontal_reach = power

        for row_offset in range(power + 1):
            horizontal_reach_squared = power_squared - row_offset * row_offset
            while horizontal_reach * horizontal_reach > horizontal_reach_squared:
                horizontal_reach -= 1

            left_col = epicenter_col - horizontal_reach
            right_col = epicenter_col + horizontal_reach

            row = epicenter_row - row_offset
            dsu_row_start = row * (M + 1)
            next_col = left_col
            while next_unset_col[dsu_row_start + next_col] != next_col:
                next_unset_col[dsu_row_start + next_col] = next_unset_col[dsu_row_start + next_unset_col[dsu_row_start + next_col]]
                next_col = next_unset_col[dsu_row_start + next_col]

            if next_col <= right_col:
                after_interval = right_col + 1
                while next_unset_col[dsu_row_start + after_interval] != after_interval:
                    next_unset_col[dsu_row_start + after_interval] = next_unset_col[dsu_row_start + next_unset_col[dsu_row_start + after_interval]]
                    after_interval = next_unset_col[dsu_row_start + after_interval]

                new_columns = []
                col = next_col
                while col <= right_col:
                    new_columns.append(col)
                    next_free = col + 1
                    while next_unset_col[dsu_row_start + next_free] != next_free:
                        next_unset_col[dsu_row_start + next_free] = next_unset_col[dsu_row_start + next_unset_col[dsu_row_start + next_free]]
                        next_free = next_unset_col[dsu_row_start + next_free]
                    col = next_free

                reading_row_start = row * M
                for col in new_columns:
                    col_offset = col - epicenter_col
                    shock_level = power_squared - (row_offset * row_offset + col_offset * col_offset) + 1
                    readings[reading_row_start + col] = shock_level
                    next_unset_col[dsu_row_start + col] = after_interval
                finished_cells += len(new_columns)

            if row_offset != 0:
                row = epicenter_row + row_offset
                dsu_row_start = row * (M + 1)
                next_col = left_col
                while next_unset_col[dsu_row_start + next_col] != next_col:
                    next_unset_col[dsu_row_start + next_col] = next_unset_col[dsu_row_start + next_unset_col[dsu_row_start + next_col]]
                    next_col = next_unset_col[dsu_row_start + next_col]

                if next_col <= right_col:
                    after_interval = right_col + 1
                    while next_unset_col[dsu_row_start + after_interval] != after_interval:
                        next_unset_col[dsu_row_start + after_interval] = next_unset_col[dsu_row_start + next_unset_col[dsu_row_start + after_interval]]
                        after_interval = next_unset_col[dsu_row_start + after_interval]

                    new_columns = []
                    col = next_col
                    while col <= right_col:
                        new_columns.append(col)
                        next_free = col + 1
                        while next_unset_col[dsu_row_start + next_free] != next_free:
                            next_unset_col[dsu_row_start + next_free] = next_unset_col[dsu_row_start + next_unset_col[dsu_row_start + next_free]]
                            next_free = next_unset_col[dsu_row_start + next_free]
                        col = next_free

                    reading_row_start = row * M
                    for col in new_columns:
                        col_offset = col - epicenter_col
                        shock_level = power_squared - (row_offset * row_offset + col_offset * col_offset) + 1
                        readings[reading_row_start + col] = shock_level
                        next_unset_col[dsu_row_start + col] = after_interval
                    finished_cells += len(new_columns)

    readings_by_row = []
    for row in range(N):
        readings_by_row.append(readings[row * M:(row + 1) * M])
    return readings_by_row

def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        earthquakes = []
        for i in range(Q):
            X, Y, P = map(int, input().split())
            earthquakes.append((X, Y, P))
        answer = solve(N, M, Q, earthquakes)
        for row in answer:
            print(' '.join(map(str, row)))

if __name__ == '__main__':
    main()