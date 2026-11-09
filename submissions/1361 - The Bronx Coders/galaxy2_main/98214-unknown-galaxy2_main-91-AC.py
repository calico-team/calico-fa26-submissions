import sys
from collections import deque

sys.setrecursionlimit(20000)

def build_network(height, width, board):
    col_step = 2 * height
    total = width * col_step
    graph = [[] for _ in range(total)]
    active_node = [False] * total
    
    for x in range(width):
        offset = x * col_step
        for y in range(height):
            tile = board[y][x]
            blue_id = offset + 2 * y
            red_id = blue_id + 1
            
            if tile != 'R':
                active_node[blue_id] = True
            if tile != 'B':
                active_node[red_id] = True
            if tile == '.':
                graph[blue_id].append(red_id)
                graph[red_id].append(blue_id)
                
            if y + 1 < height:
                down_tile = board[y + 1][x]
                if tile != 'R' and down_tile != 'R':
                    graph[blue_id].append(blue_id + 2)
                    graph[blue_id + 2].append(blue_id)
                if tile != 'B' and down_tile != 'B':
                    graph[red_id].append(red_id + 2)
                    graph[red_id + 2].append(red_id)
                    
            if x + 1 < width:
                right_tile = board[y][x + 1]
                if tile != 'R' and right_tile != 'R':
                    graph[blue_id].append(blue_id + col_step)
                    graph[blue_id + col_step].append(blue_id)
                if tile != 'B' and right_tile != 'B':
                    graph[red_id].append(red_id + col_step)
                    graph[red_id + col_step].append(red_id)
                    
    return graph, active_node

def run_galaxy2():
    tokens = sys.stdin.read().split()
    if not tokens:
        return
    
    pos = 0
    test_count = int(tokens[pos])
    pos += 1
    UNREACHABLE = 10**15
    final_output = []
    
    for _ in range(test_count):
        height = int(tokens[pos])
        width = int(tokens[pos + 1])
        q_count = int(tokens[pos + 2])
        pos += 3
        
        board = tokens[pos : pos + height]
        pos += height
        
        col_step = 2 * height
        graph, active_node = build_network(height, width, board)
        
        best_dist = [UNREACHABLE] * q_count
        time_limits = [0] * q_count
        tasks = []
        
        for idx in range(q_count):
            sy = int(tokens[pos])
            sx = int(tokens[pos + 1])
            ey = int(tokens[pos + 2])
            ex = int(tokens[pos + 3])
            limit = int(tokens[pos + 4])
            pos += 5
            
            time_limits[idx] = limit
            src = sx * col_step + 2 * sy
            dst_base = ex * col_step + 2 * ey
            target_ch = board[ey][ex]
            
            if target_ch == 'B':
                dst_a, dst_b = dst_base, dst_base
            elif target_ch == 'R':
                dst_a, dst_b = dst_base + 1, dst_base + 1
            else:
                dst_a, dst_b = dst_base, dst_base + 1
                
            if sy == ey and sx == ex:
                best_dist[idx] = 0
            else:
                tasks.append((idx, src, dst_a, dst_b, sx, ex))
                
        layer_dist = [0] * (width * col_step)
        
        def divide_columns(low_x, high_x, sub_tasks):
            if low_x > high_x or not sub_tasks:
                return
                
            mid_x = (low_x + high_x) // 2
            start_cell = low_x * col_step
            end_cell = (high_x + 1) * col_step
            span = end_cell - start_cell
            
            if low_x > 0:
                layer_dist[(low_x - 1) * col_step : start_cell] = [0] * col_step
            if high_x + 1 < width:
                layer_dist[end_cell : (high_x + 2) * col_step] = [0] * col_step
                
            mid_base = mid_x * col_step
            for root in range(mid_base, mid_base + col_step):
                if not active_node[root]:
                    continue
                    
                layer_dist[start_cell : end_cell] = [UNREACHABLE] * span
                layer_dist[root] = 0
                dq = deque([root])
                
                while dq:
                    u = dq.popleft()
                    step_cost = layer_dist[u] + 1
                    for v in graph[u]:
                        if layer_dist[v] == UNREACHABLE:
                            layer_dist[v] = step_cost
                            dq.append(v)
                            
                for idx, src, dst_a, dst_b, sx, ex in sub_tasks:
                    da = layer_dist[dst_a]
                    db = layer_dist[dst_b]
                    total_d = layer_dist[src] + (da if da < db else db)
                    if total_d < best_dist[idx]:
                        best_dist[idx] = total_d
                        
            if low_x < high_x:
                left_sub = []
                right_sub = []
                for item in sub_tasks:
                    idx, src, dst_a, dst_b, sx, ex = item
                    if best_dist[idx] <= time_limits[idx]:
                        continue
                    if sx < mid_x and ex < mid_x:
                        left_sub.append(item)
                    elif sx > mid_x and ex > mid_x:
                        right_sub.append(item)
                divide_columns(low_x, mid_x - 1, left_sub)
                divide_columns(mid_x + 1, high_x, right_sub)
                
        divide_columns(0, width - 1, tasks)
        
        for idx in range(q_count):
            if best_dist[idx] <= time_limits[idx]:
                final_output.append("YES")
            else:
                final_output.append("NO")
                
    print("\n".join(final_output))

if __name__ == "__main__":
    run_galaxy2()