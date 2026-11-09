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
        M = int(input_data[idx+1])
        Q = int(input_data[idx+2])
        idx += 3
        
        grid = []
        for _ in range(N):
            grid.append(input_data[idx])
            idx += 1
            
    
        total_nodes = N * M * 2
        parent = list(range(total_nodes))
        rank = [1] * total_nodes
        
       
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
                if rank[root_i] > rank[root_j]:
                    parent[root_j] = root_i
                elif rank[root_i] < rank[root_j]:
                    parent[root_i] = root_j
                else:
                    parent[root_j] = root_i
                    rank[root_i] += 1
                    
        def get_node(r, c, mode):
            return (r * M + c) * 2 + mode
            
       
        for r in range(N):
            for c in range(M):
                cell = grid[r][c]
                
             
                if cell == '.':
                    union(get_node(r, c, 0), get_node(r, c, 1))
                    
             
                if c + 1 < M:
                    right_cell = grid[r][c+1]
                  
                    if cell in ('.', 'B') and right_cell in ('.', 'B'):
                        union(get_node(r, c, 0), get_node(r, c+1, 0))
              
                    if cell in ('.', 'R') and right_cell in ('.', 'R'):
                        union(get_node(r, c, 1), get_node(r, c+1, 1))
              
                if r + 1 < N:
                    bottom_cell = grid[r+1][c]
                 
                    if cell in ('.', 'B') and bottom_cell in ('.', 'B'):
                        union(get_node(r, c, 0), get_node(r+1, c, 0))
               
                    if cell in ('.', 'R') and bottom_cell in ('.', 'R'):
                        union(get_node(r, c, 1), get_node(r+1, c, 1))
                        
   
        for _ in range(Q):
            rs = int(input_data[idx])
            cs = int(input_data[idx+1])
            re = int(input_data[idx+2])
            ce = int(input_data[idx+3])
            idx += 4
          
            start_node = get_node(rs, cs, 0)
            end_cell = grid[re][ce]
            
            possible = False
            
        
            if end_cell in ('.', 'B'):
                if find(start_node) == find(get_node(re, ce, 0)):
                    possible = True
                    
          
            if end_cell in ('.', 'R'):
                if find(start_node) == find(get_node(re, ce, 1)):
                    possible = True
                    
            if possible:
                out.append("YES")
            else:
                out.append("NO")
 
    print('\n'.join(out))

if __name__ == '__main__':
    solve()