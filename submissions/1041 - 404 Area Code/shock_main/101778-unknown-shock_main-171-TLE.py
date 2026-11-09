import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    iterator = iter(input_data)
    T = int(next(iterator))
    
    out = []
    for _ in range(T):
        N = int(next(iterator))
        M = int(next(iterator))
        Q = int(next(iterator))
        
        grid = [0] * (N * M)
        
        for _ in range(Q):
            R_i = int(next(iterator))
            C_i = int(next(iterator))
            P_i = int(next(iterator))
            
            P_sq = P_i * P_i
            
            for r in range(R_i - P_i, R_i + P_i + 1):
                r_diff_sq = (r - R_i) * (r - R_i)
                row_offset = r * M
                
                for c in range(C_i - P_i, C_i + P_i + 1):
                    c_diff_sq = (c - C_i) * (c - C_i)
                    dist_sq = r_diff_sq + c_diff_sq
                    
                    if dist_sq <= P_sq:
                        shock_level = P_sq - dist_sq + 1
                        grid[row_offset + c] = shock_level
                        
        for r in range(N):
            row_vals = [str(grid[r * M + c]) for c in range(M)]
            out.append(" ".join(row_vals))
            
    print("\n".join(out))

if __name__ == "__main__":
    solve()
