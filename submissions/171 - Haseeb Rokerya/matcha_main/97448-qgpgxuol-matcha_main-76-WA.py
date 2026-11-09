# cook your dish here
import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    iterator = iter(input_data)
    num_test_cases = int(next(iterator))
    
    out = []
    for _ in range(num_test_cases):
        n = int(next(iterator))
        l_bounds = [int(next(iterator)) for _ in range(n)]
        r_bounds = [int(next(iterator)) for _ in range(n)]
        
        current_intervals = [(l_bounds[i], r_bounds[i]) for i in range(n)]
        max_enjoyment = 0
        
        for bit in range(29, -1, -1):
            mask = 1 << bit
            forced_parity = 0
            flexible_intervals = []
            next_intervals = []
            
            for l, r in current_intervals:
                if (l >> bit) == (r >> bit):
                    forced_parity ^= (l >> bit) & 1
                    next_intervals.append((l, r))
                else:
                    mid_zero_end = (l | mask) - 1
                    mid_one_start = (l & ~mask) | mask
                    
                    flexible_intervals.append({
                        'range0': (l, mid_zero_end),
                        'range1': (mid_one_start, r)
                    })
            
            if flexible_intervals:
                max_enjoyment |= mask
                target_bit = 1
                current_parity = forced_parity ^ len(flexible_intervals)
                
                chosen = []
                for i, f in enumerate(flexible_intervals):
                    if i == 0 and current_parity != target_bit:
                        chosen.append(f['range0'])
                    else:
                        chosen.append(f['range1'])
                
                current_intervals = next_intervals + chosen
            else:
                if forced_parity == 1:
                    max_enjoyment |= mask
                current_intervals = next_intervals
                
        out.append(str(max_enjoyment))
        
    print('\n'.join(out))

if __name__ == '__main__':
    solve()