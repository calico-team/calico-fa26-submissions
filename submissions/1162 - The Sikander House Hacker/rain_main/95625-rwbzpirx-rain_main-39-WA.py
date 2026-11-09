import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    T = int(input_data[0])
    idx = 1
    
    out = []
    for _ in range(T):
        N = int(input_data[idx])
        K = int(input_data[idx+1])
        idx += 2
        
        e_drones = []
        n_drones = []
        
        for _ in range(N):
            x = int(input_data[idx])
            y = int(input_data[idx+1])
            z = int(input_data[idx+2])
            d = input_data[idx+3]
            idx += 4
            
            if d == 'E':
                e_drones.append((x, y, z))
            else:
                n_drones.append((x, y, z))
                
        total_water = N * K
        blocked = 0
        
        group_e = {}
        for x, y, z in e_drones:
            s = x + y
            if s not in group_e:
                group_e[s] = []
            group_e[s].append((x, y, z))
            
        group_n = {}
        for x, y, z in n_drones:
            s = x + y
            if s not in group_n:
                group_n[s] = []
            group_n[s].append((x, y, z))
            
        common_s = set(group_e.keys()).intersection(group_n.keys())
        for s in common_s:
            blockers = [(nx, nz) for nx, ny, nz in group_n[s]]
            targets = []
            for ex, ey, ez in group_e[s]:
                xmin = ex + 1
                xmax = ex + K - 1
                if xmin <= xmax:
                    targets.append((ez, xmin, xmax))
            
            if blockers and targets:
                coords = []
                for bx, bz in blockers:
                    coords.append(bx)
                for tz, tmin, tmax in targets:
                    coords.append(tmin)
                    coords.append(tmax)
                coords = sorted(list(set(coords)))
                coord_map = {c: i + 1 for i, c in enumerate(coords)}
                
                events = []
                for bx, bz in blockers:
                    events.append((bz, 1, coord_map[bx]))
                for tz, tmin, tmax in targets:
                    events.append((tz, 0, coord_map[tmin], coord_map[tmax]))
                
                events.sort(key=lambda e: (-e[0], e[1]))
                
                tree = [0] * (len(coords) + 2)
                def add(i, delta):
                    while i < len(tree):
                        tree[i] += delta
                        i += i & (-i)
                def query(i):
                    s_val = 0
                    while i > 0:
                        s_val += tree[i]
                        i -= i & (-i)
                    return s_val
                
                for ev in events:
                    if ev[1] == 0:
                        _, _, l_idx, r_idx = ev
                        blocked += query(r_idx) - query(l_idx - 1)
                    else:
                        _, _, idx_val = ev
                        add(idx_val, 1)
                        
        group_e_diff = {}
        for x, y, z in e_drones:
            d_val = x - y
            if d_val not in group_e_diff:
                group_e_diff[d_val] = []
            group_e_diff[d_val].append((x, y, z))
            
        group_n_diff = {}
        for x, y, z in n_drones:
            d_val = x - y
            if d_val not in group_n_diff:
                group_n_diff[d_val] = []
            group_n_diff[d_val].append((x, y, z))
            
        common_d = set(group_n_diff.keys()).intersection(group_e_diff.keys())
        for d_val in common_d:
            blockers = [(ex, ez) for ex, ey, ez in group_e_diff[d_val]]
            targets = []
            for nx, ny, nz in group_n_diff[d_val]:
                xmin = nx - K + 1
                xmax = nx - 1
                if xmin <= xmax:
                    targets.append((nz, xmin, xmax))
            
            if blockers and targets:
                coords = []
                for bx, bz in blockers:
                    coords.append(bx)
                for tz, tmin, tmax in targets:
                    coords.append(tmin)
                    coords.append(tmax)
                coords = sorted(list(set(coords)))
                coord_map = {c: i + 1 for i, c in enumerate(coords)}
                
                events = []
                for bx, bz in blockers:
                    events.append((bz, 1, coord_map[bx]))
                for tz, tmin, tmax in targets:
                    events.append((tz, 0, coord_map[tmin], coord_map[tmax]))
                
                events.sort(key=lambda e: (-e[0], e[1]))
                
                tree = [0] * (len(coords) + 2)
                def add(i, delta):
                    while i < len(tree):
                        tree[i] += delta
                        i += i & (-i)
                def query(i):
                    s_val = 0
                    while i > 0:
                        s_val += tree[i]
                        i -= i & (-i)
                    return s_val
                
                for ev in events:
                    if ev[1] == 0:
                        _, _, l_idx, r_idx = ev
                        blocked += query(r_idx) - query(l_idx - 1)
                    else:
                        _, _, idx_val = ev
                        add(idx_val, 1)
                        
        out.append(str(total_water - blocked))
        
    print('\n'.join(out))

if __name__ == '__main__':
    solve()