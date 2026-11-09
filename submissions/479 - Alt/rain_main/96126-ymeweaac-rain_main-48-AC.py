import sys

def main():
    # input read
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    data_iterator = iter(input_data)
    
    # test cases 
    number_of_test_cases = int(next(data_iterator))
    
    for _ in range(number_of_test_cases):
        number_of_drones = int(next(data_iterator))
        number_of_nights = int(next(data_iterator))
        
        diagonal_groups = {}
        
        for drone_index in range(number_of_drones):
            start_x = int(next(data_iterator))
            start_y = int(next(data_iterator))
            height_z = int(next(data_iterator))
            direction = next(data_iterator)
            
            diagonal_sum = start_x + start_y
            if diagonal_sum not in diagonal_groups:
                diagonal_groups[diagonal_sum] = []
                
            diagonal_groups[diagonal_sum].append({
                'id': drone_index,
                'x': start_x,
                'y': start_y,
                'z': height_z,
                'direction': direction
            })
            
        max_possible_rain = number_of_drones * number_of_nights
        
        blocking_events = set()
        
        for diagonal_sum, drones_on_diagonal in diagonal_groups.items():
            east_drones = [drone for drone in drones_on_diagonal if drone['direction'] == 'E']
            north_drones = [drone for drone in drones_on_diagonal if drone['direction'] == 'N']
            
            for east_drone in east_drones:
                for north_drone in north_drones:
                    intersection_time = north_drone['x'] - east_drone['x']
                    
                    if 0 <= intersection_time < number_of_nights:
                        if east_drone['z'] < north_drone['z']:
                            blocking_events.add((east_drone['id'], intersection_time))
                        elif north_drone['z'] < east_drone['z']:
                            blocking_events.add((north_drone['id'], intersection_time))
                            
        # Total rainwater collected
        total_rainwater_collected = max_possible_rain - len(blocking_events)
        print(total_rainwater_collected)

if __name__ == '__main__':
    main()
