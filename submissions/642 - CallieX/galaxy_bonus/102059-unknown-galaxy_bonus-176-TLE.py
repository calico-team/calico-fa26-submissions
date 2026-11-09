testC = int(input())

for t in range(testC):
    firstLine = input().split()
    while len(firstLine) == 0:
        firstLine = input().split()
        
    n = int(firstLine[0])
    m = int(firstLine[1])
    q = int(firstLine[2])
    
    grid = []
    for i in range(n):
        row_str = input().strip()
        while len(row_str) == 0:
            row_str = input().strip()
        grid.append(row_str)
        
    for query_idx in range(q):
        qLine = input().split()
        while len(qLine) == 0:
            qLine = input().split()
            
        r_start = int(qLine[0])
        c_start = int(qLine[1])
        r_end = int(qLine[2])
        c_end = int(qLine[3])
        
        queue = [(r_start, c_start, 0)]
        visited = set()
        visited.add((r_start, c_start, 0))
        
        possible = "NO"
        head = 0
        
        while head < len(queue):
            curr_r, curr_c, curr_mode = queue[head]
            head = head + 1
            
            if curr_r == r_end and curr_c == c_end:
                possible = "YES"
                break
                
            dc = [0, 0, -1, 1]
            dr = [-1, 1, 0, 0]
            for i in range(4):
                nr = curr_r + dr[i]
                nc = curr_c + dc[i]
                
                if 0 <= nr < n and 0 <= nc < m:
                    tile = grid[nr][nc]
                    
                    can_walk = False
                    if tile == '.':
                        can_walk = True
                    elif tile == 'B' and curr_mode == 0:
                        can_walk = True
                    elif tile == 'R' and curr_mode == 1:
                        can_walk = True
                        
                    if can_walk == True:
                        next_state = (nr, nc, curr_mode)
                        if next_state not in visited:
                            visited.add(next_state)
                            queue.append(next_state)
                            
            if grid[curr_r][curr_c] == '.':
                next_mode = 1 - curr_mode
                next_state = (curr_r, curr_c, next_mode)
                if next_state not in visited:
                    visited.add(next_state)
                    queue.append(next_state)
                    
        print(possible)
