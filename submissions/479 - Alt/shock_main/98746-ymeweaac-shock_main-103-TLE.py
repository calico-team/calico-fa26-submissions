import sys
import math

def main():
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
        
        seismometer_grid = [[0] * cols_count for _ in range(rows_count)]
        
        for _ in range(earthquakes_count):
            epicenter_row = int(raw_input[ptr])
            epicenter_col = int(raw_input[ptr+1])
            earthquake_power = int(raw_input[ptr+2])
            ptr += 3
            
            power_squared = earthquake_power * earthquake_power
            
            min_affected_row = max(0, epicenter_row - earthquake_power)
            max_affected_row = min(rows_count - 1, epicenter_row + earthquake_power)
            
            for current_row in range(min_affected_row, max_affected_row + 1):
                row_distance_squared = (current_row - epicenter_row) ** 2
                max_col_offset = int(math.isqrt(power_squared - row_distance_squared))
                
                min_affected_col = max(0, epicenter_col - max_col_offset)
                max_affected_col = min(cols_count - 1, epicenter_col + max_col_offset)
                
                for current_col in range(min_affected_col, max_affected_col + 1):
                    col_distance_squared = (current_col - epicenter_col) ** 2
                    total_distance_squared = row_distance_squared + col_distance_squared
                    
                    calculated_shock_level = power_squared - total_distance_squared + 1
                    seismometer_grid[current_row][current_col] = calculated_shock_level
                    
        for r in range(rows_count):
            output_buffer.append(" ".join(map(str, seismometer_grid[r])))
            
    sys.stdout.write("\n".join(output_buffer) + "\n")

if __name__ == '__main__':
    main()
