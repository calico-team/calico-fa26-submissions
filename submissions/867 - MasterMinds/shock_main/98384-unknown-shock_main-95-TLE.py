import sys
import math

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    repeat = iter(input_data)
    num_test_cases = int(next(repeat))
    
    out = []
    for _ in range(num_test_cases):
        N = int(next(repeat))
        M = int(next(repeat))
        Q = int(next(repeat))
        
        earthquakes = [None] * Q
        for i in range(Q):
            earthquakes[i] = (int(next(repeat)), int(next(repeat)), int(next(repeat)))
            
       
        grid = [0] * (N * M)
        visited = [False] * (N * M)
        unvisited_count = N * M
        
        
        for r_eq, c_eq, p_eq in reversed(earthquakes):
            if unvisited_count == 0:
                break
                
            p_sq = p_eq * p_eq
            r_start = 0 if r_eq < p_eq else r_eq - p_eq
            r_end = N - 1 if r_eq + p_eq >= N else r_eq + p_eq
            
            for r in range(r_start, r_end + 1):
                r_diff = r - r_eq
                r_diff_sq = r_diff * r_diff
                rem = p_sq - r_diff_sq
                if rem < 0:
                    continue
                
                dc = math.isqrt(rem)
                c_start = 0 if c_eq < dc else c_eq - dc
                c_end = M - 1 if c_eq + dc >= M else c_eq + dc
                
                row_offset = r * M
                for c in range(c_start, c_end + 1):
                    idx = row_offset + c
                    if not visited[idx]:
                        visited[idx] = True
                        unvisited_count -= 1
                        grid[idx] = p_sq - (r_diff_sq + (c - c_eq) * (c - c_eq)) + 1
                        
        for r in range(N):
            row_offset = r * M
            out.append(" ".join(str(grid[row_offset + c]) for c in range(M)))
            
    sys.stdout.write("\n".join(out) + "\n")

if __name__ == '__main__':
    solve()