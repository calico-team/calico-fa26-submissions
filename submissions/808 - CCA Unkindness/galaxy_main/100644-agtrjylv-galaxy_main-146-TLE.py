# Source: https://usaco.guide/general/io
from collections import deque

def cool_func():
    N, M, Q = map(int, input().split())
    
    map_gal = []
    for i in range(N):
        map_gal.append(input())
        
    for x in range(Q):
        starting_row, starting_column, ending_row, ending_column = map(int, input().split())
        
        cool_state = (starting_row, starting_column, "B")
        queue = deque([cool_state])
        visits = {cool_state}
        cool_dirs = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        isThere = False
        
        while queue:
            row, column, mode = queue.popleft()
            
            if row == ending_row and column == ending_column:
                print("YES")
                isThere = True
                break
                
            if map_gal[row][column] == '.':
                if mode == "B":
                    next_mode = "R"
                else:
                    next_mode = "B"
                spin_state = (row, column, next_mode)
                if spin_state not in visits:
                    visits.add(spin_state)
                    queue.append(spin_state)
                    
            for d_row, d_column in cool_dirs:
                next_row, next_column = row+d_row, column+d_column
                if 0 <= next_row < N and 0 <= next_column < M:
                    tile = map_gal[next_row][next_column]
                    is_active = (tile == '.') or (tile == mode)
                    
                    if is_active:
                        next_state = (next_row, next_column, mode)
                        if next_state not in visits:
                            visits.add(next_state)
                            queue.append(next_state)
        if not isThere:
            print("NO")

test_cases = int(input())
for i in range(test_cases):
    cool_func()
