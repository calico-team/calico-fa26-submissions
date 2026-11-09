import sys

def solve():
    data = sys.stdin.read().split()
    if not data:
        return
        
    num_test_cases = int(data[0])
    pointer = 1
    
    results = []
    
    for _ in range(num_test_cases):
        rows = int(data[pointer])
        cols = int(data[pointer+1])
        queries = int(data[pointer+2])
        pointer += 3
        
        grid = []
        for _ in range(rows):
            grid.append(data[pointer])
            pointer += 1
            
     
        total_states = rows * cols * 2
        parent = list(range(total_states))
        
      
        def find(node):
            path = []
            while parent[node] != node:
                path.append(node)
                node = parent[node]
     
            for n in path:
                parent[n] = node
            return node
            
    
        def union(node1, node2):
            root1 = find(node1)
            root2 = find(node2)
            if root1 != root2:
                parent[root1] = root2
                
      
        def get_id(r, c, is_red):
            return (r * cols + c) * 2 + is_red
            
    
        for r in range(rows):
            for c in range(cols):
                current_tile = grid[r][c]
                
           
                if current_tile == '.':
                    union(get_id(r, c, 0), get_id(r, c, 1))
                    
             
                if c + 1 < cols:
                    right_tile = grid[r][c+1]
                    if current_tile in ['.', 'B'] and right_tile in ['.', 'B']:
                        union(get_id(r, c, 0), get_id(r, c+1, 0))
                    if current_tile in ['.', 'R'] and right_tile in ['.', 'R']:
                        union(get_id(r, c, 1), get_id(r, c+1, 1))
                        
       
                if r + 1 < rows:
                    down_tile = grid[r+1][c]
                    if current_tile in ['.', 'B'] and down_tile in ['.', 'B']:
                        union(get_id(r, c, 0), get_id(r+1, c, 0))
                    if current_tile in ['.', 'R'] and down_tile in ['.', 'R']:
                        union(get_id(r, c, 1), get_id(r+1, c, 1))
                        
       
        for _ in range(queries):
            start_r = int(data[pointer])
            start_c = int(data[pointer+1])
            end_r = int(data[pointer+2])
            end_c = int(data[pointer+3])
            pointer += 4
            
            start_state = get_id(start_r, start_c, 0) # Always start in Blue Mode
            end_tile = grid[end_r][end_c]
            
            can_reach = False
            
        
            if end_tile in ['.', 'B']:
                if find(start_state) == find(get_id(end_r, end_c, 0)):
                    can_reach = True
                    
           
            if end_tile in ['.', 'R']:
                if find(start_state) == find(get_id(end_r, end_c, 1)):
                    can_reach = True
                    
            if can_reach:
                results.append("YES")
            else:
                results.append("NO")
                
    
    print('\n'.join(results))

if __name__ == '__main__':
    solve()