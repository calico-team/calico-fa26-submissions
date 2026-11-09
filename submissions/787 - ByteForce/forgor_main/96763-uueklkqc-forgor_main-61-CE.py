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
        m = int(next(iterator))
        q = int(next(iterator))
        
        grid = [[0] * m for _ in range(n)]
        
        for _ in range(q):
            r_epicenter = int(next(iterator))
            c_epicenter = int(next(iterator))
            p = int(next(iterator))
            
            p_sq = p * p
            
            row_min = max(0, r_epicenter - p)
            row_max = min(n - 1, r_epicenter + p)
            col_min = max(0, c_epicenter - p)
            col_max = min(m - 1, c_epicenter + p)
            
            for r in range(row_min, row_max + 1):
                dr = r - r_epicenter
                dr_sq = dr * dr
                for c in range(col_min, col_max + 1):
                    dc = c - c_epicenter
                    dist_sq = dr_sq + dc * dc
                    if dist_sq <= p_sq:
                        grid[r][c] = p_sq - dist_sq + 1
                        
        for r in range(n):
            out.append(" ".join(map(str, grid[r])))
            
    print("\n".join(out))

if __name__ == '__main__':
    solve()
```[cite: 2, 3, 4]
