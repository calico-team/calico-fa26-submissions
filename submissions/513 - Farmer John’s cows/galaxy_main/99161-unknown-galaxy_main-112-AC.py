t = int(input())

for i in range(t):
    n, m, q = map(int, input().split())  
    grid = [input().strip() for j in range(n)]
    visited = set()
    current = []    
    end_x = n - 1
    end_y = m - 1 
    if grid[end_x][end_y] != 'R':
        visited.add((end_x, end_y, 0))
        current.append((end_x, end_y, 0))
    if grid[end_x][end_y] != 'B':
        visited.add((end_x, end_y, 1))
        current.append((end_x, end_y, 1))
        
    while len(current) > 0:
        next_b = []
        for x, y, mode in current:
            if grid[x][y] == '.':
                new_mode = 0 if mode == 1 else 1
                if (x, y, new_mode) not in visited:
                    visited.add((x, y, new_mode))
                    next_b.append((x, y, new_mode))
            
            directions = [(0, -1), (0, 1), (-1, 0), (1, 0)]
            for k in range(4):
                move = directions[k]
                change_y = move[0]
                change_x = move[1]       
                neighbor_x = x + change_x
                neighbor_y = y + change_y
                
                if 0 <= neighbor_x < n and 0 <= neighbor_y < m:
                    tile = grid[neighbor_x][neighbor_y]                  
                    if tile == '.' or (mode == 0 and tile == 'B') or (mode == 1 and tile == 'R'):
                        if (neighbor_x, neighbor_y, mode) not in visited:
                            visited.add((neighbor_x, neighbor_y, mode))
                            next_b.append((neighbor_x, neighbor_y, mode))
                        
        current = next_b
    for i in range(q):
        query = input().split()
        start_x = int(query[0])
        start_y = int(query[1])
        
        if (start_x, start_y, 0) in visited:
            print("YES")
        else:
            print("NO")
