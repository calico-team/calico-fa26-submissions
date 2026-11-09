import sys
import heapq

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    iterator = iter(input_data)
    T = int(next(iterator))
    
    out = []
    for _ in range(T):
        N = int(next(iterator))
        M = int(next(iterator))
        Q = int(next(iterator))
        
        grid = []
        for _ in range(N):
            grid.append(next(iterator))
            
        queries = []
        for _ in range(Q):
            sr = int(next(iterator))
            sc = int(next(iterator))
            er = int(next(iterator))
            ec = int(next(iterator))
            k = int(next(iterator))
            queries.append((sr, sc, er, ec, k))
            
        memo = {}
        
        for sr, sc, er, ec, k in queries:
            start_key = (sr, sc)
            if start_key not in memo:
                dist = {}
                for r in range(N):
                    for c in range(M):
                        dist[(r, c, 0)] = float('inf')
                        dist[(r, c, 1)] = float('inf')
                        
                dist[(sr, sc, 0)] = 0
                pq = [(0, sr, sc, 0)]
                
                while pq:
                    d, r, c, mode = heapq.heappop(pq)
                    
                    if d > dist[(r, c, mode)]:
                        continue
                        
                    for nr, nc in ((r-1, c), (r+1, c), (r, c-1), (r, c+1)):
                        if 0 <= nr < N and 0 <= nc < M:
                            cell = grid[nr][nc]
                            active = False
                            if cell == '.':
                                active = True
                            elif cell == 'B' and mode == 0:
                                active = True
                            elif cell == 'R' and mode == 1:
                                active = True
                                
                            if active:
                                nd = d + 1
                                if nd < dist[(nr, nc, mode)]:
                                    dist[(nr, nc, mode)] = nd
                                    heapq.heappush(pq, (nd, nr, nc, mode))
                                    
                    if grid[r][c] == '.':
                        new_mode = 1 - mode
                        nd = d + 1
                        if nd < dist[(r, c, new_mode)]:
                            dist[(r, c, new_mode)] = nd
                            heapq.heappush(pq, (nd, r, c, new_mode))
                            
                memo[start_key] = dist
            else:
                dist = memo[start_key]
                
            ans_d = min(dist[(er, ec, 0)], dist[(er, ec, 1)])
            if ans_d <= k:
                out.append("YES")
            else:
                out.append("NO")
                
    sys.stdout.write('\n'.join(out) + '\n')

if __name__ == '__main__':
    solve()