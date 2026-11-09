import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    idx = 0
    num_test_cases = int(input_data[idx])
    idx += 1
    
    out = []
    for _ in range(num_test_cases):
        N = int(input_data[idx])
        M = int(input_data[idx+1])
        Q = int(input_data[idx+2])
        idx += 3
        
        grid = [[0] * M for _ in range(N)]
        
        for _ in range(Q):
            r_epicenter = int(input_data[idx])
            c_epicenter = int(input_data[idx+1])
            power = int(input_data[idx+2])
            idx += 3
            
            r_min = max(0, r_epicenter - power)
            r_max = min(N - 1, r_epicenter + power)
            c_min = max(0, c_epicenter - power)
            c_max = min(M - 1, c_epicenter + power)
            
            p_sq = power * power
            
            for r in range(r_min, r_max + 1):
                dr_sq = (r - r_epicenter) ** 2
                row = grid[r]
                for c in range(c_min, c_max + 1):
                    dist_sq = dr_sq + (c - c_epicenter) ** 2
                    if dist_sq <= p_sq:
                        row[c] = p_sq - dist_sq + 1
                            
        for row in grid:
            out.append(' '.join(map(str, row)))
            
    print('\n'.join(out))

if __name__ == '__main__':
    solve()
