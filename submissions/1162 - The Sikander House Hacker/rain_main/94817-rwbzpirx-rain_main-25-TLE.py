import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    iterator = iter(input_data)
    T = int(next(iterator))
    
    output = []
    
    for _ in range(T):
        N = int(next(iterator))
        K = int(next(iterator))
        
        drones = []
        for i in range(N):
            x = int(next(iterator))
            y = int(next(iterator))
            z = int(next(iterator))
            d = next(iterator)
            drones.append((x, y, z, d, i))
            
        all_z = sorted(list(set(d[2] for d in drones)))
        z_map = {val: idx + 1 for idx, val in enumerate(all_z)}
        num_z = len(all_z)
        
        groups = {}
        for d in drones:
            x, y, z, dir_val, idx = d
            s = x + y
            if s not in groups:
                groups[s] = ([], [])
            if dir_val == 'E':
                groups[s][0].append((y, z, idx))
            else:
                groups[s][1].append((x, z, idx))
                
        blocked_count = [0] * N
        
        for s, (e_list, n_list) in groups.items():
            if e_list and n_list:
                events = []
                for x, z, idx in n_list:
                    events.append((x, 0, z_map[z], 0, 0))
                for y, z, idx in e_list:
                    l = s - y
                    r = s - y + K - 1
                    events.append((r, 1, z_map[z], 1, idx))
                    events.append((l - 1, 1, z_map[z], -1, idx))
                
                events.sort(key=lambda item: (item[0], item[1]))
                
                bit = [0] * (num_z + 2)
                def add(idx, val):
                    while idx < len(bit):
                        bit[idx] += val
                        idx += idx & (-idx)
                        
                def query(idx):
                    s_val = 0
                    while idx > 0:
                        s_val += bit[idx]
                        idx -= idx & (-idx)
                    return s_val
                
                total_points = 0
                for ev in events:
                    if ev[1] == 0:
                        add(ev[2], 1)
                        total_points += 1
                    else:
                        z_c = ev[2]
                        sign = ev[3]
                        idx = ev[4]
                        count_leq = query(z_c)
                        count_greater = total_points - count_leq
                        blocked_count[idx] += sign * count_greater
                        
                events = []
                for y, z, idx in e_list:
                    events.append((y, 0, z_map[z], 0, 0))
                for x, z, idx in n_list:
                    l = s - x
                    r = s - x + K - 1
                    events.append((r, 1, z_map[z], 1, idx))
                    events.append((l - 1, 1, z_map[z], -1, idx))
                    
                events.sort(key=lambda item: (item[0], item[1]))
                
                bit = [0] * (num_z + 2)
                total_points = 0
                for ev in events:
                    if ev[1] == 0:
                        add(ev[2], 1)
                        total_points += 1
                    else:
                        z_c = ev[2]
                        sign = ev[3]
                        idx = ev[4]
                        count_leq = query(z_c)
                        count_greater = total_points - count_leq
                        blocked_count[idx] += sign * count_greater
                        
        total_blocked = sum(blocked_count)
        total_water = N * K - total_blocked
        output.append(str(total_water))
        
    print('\n'.join(output))

if __name__ == '__main__':
    solve()