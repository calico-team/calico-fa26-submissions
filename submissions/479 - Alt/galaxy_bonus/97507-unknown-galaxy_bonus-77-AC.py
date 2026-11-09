import sys

sys.setrecursionlimit(300000)

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    iterator = iter(input_data)
    
    try:
        num_test_cases = int(next(iterator))
    except StopIteration:
        return

    output = []
    
    for _ in range(num_test_cases):
        N = int(next(iterator))
        M = int(next(iterator))
        Q = int(next(iterator))
        
        grid = [next(iterator) for _ in range(N)]
        
        parent = list(range(2 * N * M))
        
        def find(i):
            root = i
            while parent[root] != root:
                root = parent[root]
            
            curr = i
            while curr != root:
                nxt = parent[curr]
                parent[curr] = root
                curr = nxt
            return root
            
        def union(i, j):
            root_i = find(i)
            root_j = find(j)
            if root_i != root_j:
                parent[root_i] = root_j

        for r in range(N):
            for c in range(M):
                cell = grid[r][c]
                u_blue = (r * M + c) * 2
                u_red = u_blue + 1
                
                if cell == '.':
                    union(u_blue, u_red)
                    
                if r + 1 < N:
                    v_blue = ((r + 1) * M + c) * 2
                    v_red = v_blue + 1
                    next_cell = grid[r + 1][c]
                    
                    if cell in ('.', 'B') and next_cell in ('.', 'B'):
                        union(u_blue, v_blue)
                    if cell in ('.', 'R') and next_cell in ('.', 'R'):
                        union(u_red, v_red)
                        
                if c + 1 < M:
                    v_blue = (r * M + (c + 1)) * 2
                    v_red = v_blue + 1
                    next_cell = grid[r][c + 1]
                    
                    if cell in ('.', 'B') and next_cell in ('.', 'B'):
                        union(u_blue, v_blue)
                    if cell in ('.', 'R') and next_cell in ('.', 'R'):
                        union(u_red, v_red)
        
        for _ in range(Q):
            r1, c1 = int(next(iterator)), int(next(iterator))
            r2, c2 = int(next(iterator)), int(next(iterator))
            
            start_node = (r1 * M + c1) * 2
            dest_blue = (r2 * M + c2) * 2
            dest_red = dest_blue + 1
            
            root_start = find(start_node)
            dest_cell = grid[r2][c2]
            

            possible = False
            if dest_cell in ('.', 'B') and root_start == find(dest_blue):
                possible = True
            elif dest_cell in ('.', 'R') and root_start == find(dest_red):
                possible = True
                
            output.append("YES" if possible else "NO")
            
    sys.stdout.write('\n'.join(output) + '\n')

if __name__ == '__main__':
    solve()
