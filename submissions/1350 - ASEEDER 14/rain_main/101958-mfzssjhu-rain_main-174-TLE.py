import sys

def solve(N: int, K: int, L: list):
    same_pos_groups = {}
    for i, (x, y, z, d) in enumerate(L):
        key = (x, y, d)
        if key not in same_pos_groups:
            same_pos_groups[key] = []
        same_pos_groups[key].append((z, i))
        
    blocked_total = 0
    active_drones = []
    
    for key, drones in same_pos_groups.items():
        drones.sort(key=lambda item: item[0], reverse=True)
        max_z, best_idx = drones[0]
        active_drones.append((key[0], key[1], max_z, key[2], best_idx))
        for z, idx in drones[1:]:
            blocked_total += K
            
    east_drones = [d for d in active_drones if d[3] == 'E']
    north_drones = [d for d in active_drones if d[3] != 'E']
    
    events = {}
    for x_e, y_e, z_e, _, idx_e in east_drones:
        for x_n, y_n, z_n, _, idx_n in north_drones:
            s = x_n - x_e
            if s == y_e - y_n and 0 <= s < K:
                event_key = (s, x_n, y_e)
                if event_key not in events:
                    events[event_key] = []
                events[event_key].append((z_e, idx_e))
                events[event_key].append((z_n, idx_n))
                
    blocked_nights = set()
    for event_key, drone_list in events.items():
        s = event_key[0]
        t = s + 1
        unique_drones = {}
        for z, idx in drone_list:
            unique_drones[idx] = z
            
        max_z = max(unique_drones.values())
        for idx, z in unique_drones.items():
            if z < max_z:
                blocked_nights.add((t, idx))
                
    return K * N - (blocked_total + len(blocked_nights))

def main():
    try:
        T = int(sys.stdin.readline())
    except (IOError, ValueError):
        return
        
    for _ in range(T):
        line = sys.stdin.readline()
        if not line:
            break
        N, K = map(int, line.split())
        L = []
        for _ in range(N):
            x, y, z, d = sys.stdin.readline().split()
            L.append((int(x), int(y), int(z), d))
        print(solve(N, K, L))

if __name__ == '__main__':
    main()
