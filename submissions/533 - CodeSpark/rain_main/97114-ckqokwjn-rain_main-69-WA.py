import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    iterator = iter(input_data)
    try:
        T = int(next(iterator))
    except StopIteration:
        return
    
    out = []
    for _ in range(T):
        N = int(next(iterator))
        K = int(next(iterator))
        
        drones = []
        for _ in range(N):
            x = int(next(iterator))
            y = int(next(iterator))
            z = int(next(iterator))
            d = next(iterator)
            drones.append((x, y, z, d))
            
        events = {}
        for x, y, z, d in drones:
            if d == 'E':
                t = 100000 - x
            else:
                t = 100000 - y
            if t < 0:
                t = 0
            if t not in events:
                events[t] = []
            events[t].append((x, y, z, d))
            
        current_drones = sorted(drones, key=lambda item: (item[0] if item[3]=='E' else item[1]))
        
        total_water = 0
        current_time = 0
        
        for night in range(K):
            if night >= K:
                break
            
            x_coords = {}
            y_coords = {}
            for x, y, z, d in drones:
                if d == 'E':
                    cx = x + night
                    cy = y
                else:
                    cx = x
                    cy = y + night
                if (cx, cy) not in x_coords:
                    x_coords[(cx, cy)] = []
                x_coords[(cx, cy)].append(z)
                
            night_collected = 0
            for pos, heights in x_coords.items():
                min_z = min(heights)
                count_min = heights.count(min_z)
                night_collected += (len(heights) - count_min)
                
            total_water += night_collected
            
        out.append(str(total_water))
        
    print("\n".join(out))

if __name__ == '__main__':
    solve()