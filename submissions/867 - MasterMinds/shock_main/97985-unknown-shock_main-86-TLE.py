import sys
import math

def solve():
    # Read all inputs from standard input efficiently
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
        
        earthquakes = []
        for _ in range(Q):
            r = int(next(repeat))
            c = int(next(repeat))
            p = int(next(repeat))
            earthquakes.append((r, c, p))
            
        grid = [[0] * M for _ in range(N)]
        visited = [[False] * M for _ in range(N)]
        unvisited_count = N * M
        
        # Process earthquakes in reverse order
        for r_eq, c_eq, p_eq in reversed(earthquakes):
            if unvisited_count == 0:
                break
                
            p_sq = p_eq * p_eq
            r_start = max(0, r_eq - p_eq)
            r_end = min(N - 1, r_eq + p_eq)
            
            for r in range(r_start, r_end + 1):
                r_diff = r - r_eq
                r_diff_sq = r_diff * r_diff
                rem = p_sq - r_diff_sq
                if rem < 0:
                    continue
                # Calculate valid column range using integer square root
                dc = math.isqrt(rem)
                c_start = max(0, c_eq - dc)
                c_end = min(M - 1, c_eq + dc)
                
                for c in range(c_start, c_end + 1):
                    if not visited[r][c]:
                        visited[r][c] = True
                        unvisited_count -= 1
                        c_diff = c - c_eq
                        dist2 = r_diff_sq + c_diff * c_diff
                        grid[r][c] = p_sq - dist2 + 1
                        
        for r in range(N):
            out.append(" ".join(map(str, grid[r])))
            
    print("\n".join(out))

if __name__ == '__main__':
    solve()