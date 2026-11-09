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
        
        diags = {}
        for _ in range(N):
            x = int(next(iterator))
            y = int(next(iterator))
            z = int(next(iterator))
            d = next(iterator)
            c = x + y
            if c not in diags:
                diags[c] = ([], [])
            if d == 'E':
                diags[c][0].append((x, z))
            else:
                diags[c][1].append((x, z))
                
        total_water = N * K
        
        for c, (es, ns) in diags.items():
            if not es or not ns:
                continue
                
            z_vals = sorted(list(set([z for _, z in es] + [z for _, z in ns])))
            z_map = {val: idx + 1 for idx, val in enumerate(z_vals)}
            m = len(z_vals)
            
            bit = [0] * (m + 1)
            
            def add(idx, val):
                while idx <= m:
                    bit[idx] += val
                    idx += idx & (-idx)
                    
            def query(idx):
                s = 0
                while idx > 0:
                    s += bit[idx]
                    idx -= idx & (-idx)
                return s
                
            e_dict = {}
            for x, z in es:
                if x not in e_dict:
                    e_dict[x] = []
                e_dict[x].append(z)
                
            n_dict = {}
            for x, z in ns:
                if x not in n_dict:
                    n_dict[x] = []
                n_dict[x].append(z)
                
            all_x = sorted(list(set(list(e_dict.keys()) + list(n_dict.keys()) + [x + K for x in n_dict.keys()] + [x - K for x in n_dict.keys()])))
            
            for x in all_x:
                if x in n_dict:
                    for z in n_dict[x]:
                        add(z_map[z], 1)
                leave_x = x - K
                if leave_x in n_dict:
                    for z in n_dict[leave_x]:
                        add(z_map[z], -1)
                if x in e_dict:
                    for z in e_dict[x]:
                        total_water -= (query(m) - query(z_map[z]))
                        
        out.append(str(total_water))
        
    print('\n'.join(out))

if __name__ == '__main__':
    solve()