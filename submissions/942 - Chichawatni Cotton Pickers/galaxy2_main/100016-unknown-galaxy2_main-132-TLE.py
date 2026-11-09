import sys
import heapq

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    idx = 0
    num_test_cases = int(input_data[idx])
    idx += 1
    
    out = []
    for _ in range(num_test_cases):
        N = int(input_data[idx])
        M = int(input_data[idx+1])
        Q = int(input_data[idx+2])
        idx += 3
        
        grid = []
        for _ in range(N):
            grid.append(input_data[idx])
            idx += 1
            
        for _ in range(Q):
            r_start = int(input_data[idx])
            c_start = int(input_data[idx+1])
            r_end = int(input_data[idx+2])
            c_end = int(input_data[idx+3])
            K = int(input_data[idx+4])
            idx += 5
            
            # Manhattan distance lower bound check
            manhattan = abs(r_start - r_end) + abs(c_start - c_end)
            if manhattan > K:
                out.append("NO")
                continue
            
            # Dijkstra / Priority Queue: (dist, r, c, mode)
            # mode: 0 for blue, 1 for red
            pq = [(0, r_start, c_start, 0)]
            best = {}
            best[(r_start, c_start, 0)] = 0
            
            possible = False
            
            while pq:
                dist, r, c, mode = heapq.heappop(pq)
                
                if dist > K:
                    break
                    
                if r == r_end and c == c_end:
                    possible = True
                    break
                    
                if dist > best.get((r, c, mode), float('inf')):
                    continue
                
                # 1. Try moving to adjacent cells (cost = 1)
                for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                    nr, nc = r + dr, c + dc
                    if 0 <= nr < N and 0 <= nc < M:
                        cell = grid[nr][nc]
                        is_active = (cell == '.') or (cell == 'B' and mode == 0) or (cell == 'R' and mode == 1)
                        if is_active:
                            nd = dist + 1
                            if nd <= K and nd < best.get((nr, nc, mode), float('inf')):
                                best[(nr, nc, mode)] = nd
                                heapq.heappush(pq, (nd, nr, nc, mode))
                                
                # 2. Try spin action if normal tile (cost = 1)
                if grid[r][c] == '.':
                    nmode = 1 - mode
                    nd = dist + 1
                    if nd <= K and nd < best.get((r, c, nmode), float('inf')):
                        best[(r, c, nmode)] = nd
                        heapq.heappush(pq, (nd, r, c, nmode))
                        
            out.append("YES" if possible else "NO")
            
    print('\n'.join(out))

if __name__ == '__main__':
    solve()
