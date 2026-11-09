import sys
import math

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    iterator = iter(input_data)
    num_test_cases = int(next(iterator))
    
    out = []
    for _ in range(num_test_cases):
        N = int(next(iterator))
        M = int(next(iterator))
        Q = int(next(iterator))
        
        earthquakes = [None] * Q
        for i in range(Q):
            earthquakes[i] = (int(next(iterator)), int(next(iterator)), int(next(iterator)))
            
        grid = [0] * (N * M)
        unvisited_count = N * M
        
        
        row_nxt = [list(range(M + 1)) for _ in range(N)]
        
        def find_root(nxt_arr, i):
            root = i
            while nxt_arr[root] != root:
                root = nxt_arr[root]
            curr = i
            while curr != root:
                nxt_arr[curr], curr = root, nxt_arr[curr]
            return root

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
                nxt_arr = row_nxt[r]
                
                c = find_root(nxt_arr, c_start)
                while c <= c_end:
                    idx = row_offset + c
                    unvisited_count -= 1
                    c_diff = c - c_eq
                    grid[idx] = p_sq - (r_diff_sq + c_diff * c_diff) + 1
                    
                    nxt_arr[c] = find_root(nxt_arr, c + 1)
                    c = nxt_arr[c]
                        
        for r in range(N):
            row_offset = r * M
            out.append(" ".join(str(grid[row_offset + c]) for c in range(M)))
            
    sys.stdout.write("\n".join(out) + "\n")

if __name__ == '__main__':
    solve()