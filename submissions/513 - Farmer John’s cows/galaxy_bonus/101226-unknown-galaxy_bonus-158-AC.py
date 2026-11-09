import sys
input = sys.stdin.readline

t = int(input())
for i in range(t):
    n, m, q = map(int, input().split())  
    grid = [input().strip() for j in range(n)]
    visited = {}
    for r in range(n):
        for c in range(m):
            for start_mode in range(2):
                if (r, c, start_mode) not in visited:
                    if start_mode == 0 and grid[r][c] == 'R': 
                        continue
                    if start_mode == 1 and grid[r][c] == 'B': 
                        continue
                    visited[(r, c, start_mode)] = (r, c, start_mode)
                    current = [(r, c, start_mode)]    
                        
                    while len(current) > 0:
                        next_b = []
                        for x, y, mode in current:
                            if grid[x][y] == '.':
                                new_mode = 0 if mode == 1 else 1
                                if (x, y, new_mode) not in visited:
                                    visited[(x, y, new_mode)] = (r, c, start_mode)
                                    next_b.append((x, y, new_mode))
             #check                
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
                                            visited[(neighbor_x, neighbor_y, mode)] = (r, c, start_mode)
                                            next_b.append((neighbor_x, neighbor_y, mode))
                                        
                        current = next_b
    for i in range(q):
        query = input().split()
        start_x = int(query[0])
        start_y = int(query[1])
        end_x = int(query[2])
        end_y = int(query[3])


        #checdk logic
        if (start_x, start_y, 0) in visited:
            start_room = visited[(start_x, start_y, 0)]     
            can_reach = False
            if (end_x, end_y, 0) in visited and visited[(end_x, end_y, 0)] == start_room:
                can_reach = True
            elif (end_x, end_y, 1) in visited and visited[(end_x, end_y, 1)] == start_room:
                can_reach = True            
            if can_reach:
                sys.stdout.write("YES\n")
            else:
                sys.stdout.write("NO\n")
        else:
            sys.stdout.write("NO\n")
