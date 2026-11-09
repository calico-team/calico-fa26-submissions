import sys
import math

def problem8():
    raw_input = sys.stdin.read().split()
    if not raw_input:
        return
    
    ptr = 0
    num_test_cases = int(raw_input[ptr])
    ptr += 1
    
    output_buffer = []
    
    for _ in range(num_test_cases):
        rows_count = int(raw_input[ptr])
        cols_count = int(raw_input[ptr+1])
        earthquakes_count = int(raw_input[ptr+2])
        ptr += 3
        
        earthquakes_stack = []
        for _ in range(earthquakes_count):
            earthquakes_stack.append((
                int(raw_input[ptr]),
                int(raw_input[ptr+1]),
                int(raw_input[ptr+2])
            ))
            ptr += 3
            
        seismometer_flat_grid = [0] * (rows_count * cols_count)
        filled_cells_count = 0
        total_cells_to_fill = rows_count * cols_count
        
        # Track filled ranges per row to entirely bypass written blocks
        for epicenter_row, epicenter_col, earthquake_power in reversed(earthquakes_stack):
            if filled_cells_count >= total_cells_to_fill:
                break
                
            power_squared = earthquake_power * earthquake_power
            min_affected_row = max(0, epicenter_row - earthquake_power)
            max_affected_row = min(rows_count - 1, epicenter_row + earthquake_power)
            
            for current_row in range(min_affected_row, max_affected_row + 1):
                row_distance_squared = (current_row - epicenter_row) ** 2
                max_col_offset = int(math.isqrt(power_squared - row_distance_squared))
                
                min_affected_col = max(0, epicenter_col - max_col_offset)
                max_affected_col = min(cols_count - 1, epicenter_col + max_col_offset)
                
                row_base_index = current_row * cols_count
                start_index = row_base_index + min_affected_col
                end_index = row_base_index + max_affected_col
                
                # Precompute the shock segments or write directly if cell is empty
                # Reducing nested loop interpreter overhead via clean flat index lookups
                c_offset = min_affected_col - epicenter_col
                base_shock = power_squared - row_distance_squared + 1
                
                for flat_index in range(start_index, end_index + 1):
                    if seismometer_flat_grid[flat_index] == 0:
                        seismometer_flat_grid[flat_index] = base_shock - c_offset * c_offset
                        filled_cells_count += 1
                    c_offset += 1
                    
        for r in range(rows_count):
            start = r * cols_count
            end = start + cols_count
            output_buffer.append(" ".join(map(str, seismometer_flat_grid[start:end])))
            
    sys.stdout.write("\n".join(output_buffer) + "\n")

if __name__ == '__main__':
    problem8()
