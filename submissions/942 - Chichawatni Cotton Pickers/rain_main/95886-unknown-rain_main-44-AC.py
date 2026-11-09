import sys

def solve(N: int, K: int, drones: list) -> int:
    total_water = N * K
    
    sum_map_east = {}
    for x, y, z, idx in [(d[0], d[1], d[2], i) for i, d in enumerate(drones) if d[3] == 'E']:
        s = x + y
        if s not in sum_map_east:
            sum_map_east[s] = []
        sum_map_east[s].append((x, y, z, idx))
        
    intersect_events = {}
    for x_n, y_n, z_n, idx_n in [(d[0], d[1], d[2], i) for i, d in enumerate(drones) if d[3] == 'N']:
        s = x_n + y_n
        if s in sum_map_east:
            for x_e, y_e, z_e, idx_e in sum_map_east[s]:
                t = x_n - x_e
                if 0 <= t < K:
                    if t not in intersect_events:
                        intersect_events[t] = []
                    intersect_events[t].append((z_e, z_n))
                    
    lost_water = 0
    for t in intersect_events:
        for z_e, z_n in intersect_events[t]:
            if z_e < z_n:
                lost_water += 1
            else:
                lost_water += 1
                
    return total_water - lost_water

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    T = int(input_data[0])
    idx = 1
    for _ in range(T):
        N = int(input_data[idx])
        K = int(input_data[idx+1])
        idx += 2
        
        drones = []
        for _ in range(N):
            x = int(input_data[idx])
            y = int(input_data[idx+1])
            z = int(input_data[idx+2])
            d = input_data[idx+3]
            drones.append((x, y, z, d))
            idx += 4
            
        print(solve(N, K, drones))

if __name__ == '__main__':
    main()
