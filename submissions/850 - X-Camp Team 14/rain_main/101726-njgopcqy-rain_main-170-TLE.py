#problem 2b1
# import sys
# from collections import deque
# 
# def solve():
#     # Read all input efficiently
#     input_data = sys.stdin.read().split()
#     if not input_data:
#         return
#     
#     iterator = iter(input_data)
#     
#     try:
#         T = int(next(iterator))
#     except (StopIteration, ValueError):
#         return
#     
#     out = []
#     for _ in range(T):
#         try:
#             N = int(next(iterator))
#             R = int(next(iterator))
#             A = [int(next(iterator)) for _ in range(N)]
#         except (StopIteration, ValueError):
#             break
#          
#         # Sort task/arrival times chronologically
#         A.sort()
#          
#         q = deque([0, 0])
#         possible = True
#          
#         for t in A:
#             while q and q[0] <= t:
#                 q.popleft()
#                  
#             if len(q) >= 2:
#                 possible = False
#                  
#             if q:
#                 next_finish = q[-1] + R
#             else:
#                 next_finish = t + R
#                  
#             q.append(next_finish)
#              
#         out.append("YES" if possible else "NO")
#          
#     # Fast output writing
#     sys.stdout.write('\n'.join(out) + '\n')
# 
# if __name__ == '__main__':
#     solve()

#problem 4
import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    iterator = iter(input_data)
    try:
        T = int(next(iterator))
    except (StopIteration, ValueError):
        return
    
    out = []
    dir_map = {
        'N': (0, 1),
        'S': (0, -1),
        'E': (1, 0),
        'W': (-1, 0)
    }
    
    for _ in range(T):
        try:
            N = int(next(iterator))
            K = int(next(iterator))
        except StopIteration:
            break
            
        drones = []
        for _ in range(N):
            x = int(next(iterator))
            y = int(next(iterator))
            z = int(next(iterator))
            d = next(iterator)
            dx, dy = dir_map[d]
            drones.append((z, x, y, dx, dy))
            
        total_water = 0
        
        for j in range(N):
            zj, xj, yj, dxj, dyj = drones[j]
            intervals = []
            
            for i in range(N):
                if i == j:
                    continue
                zi, xi, yi, dxi, dyi = drones[i]
                
                # Only higher-Z drones can block lower-Z drones
                if zi > zj:
                    # Check if paths are identical
                    if dxi == dxj and dyi == dyj:
                        if xi == xj and yi == yj:
                            intervals.append((0, K - 1))
                    else:
                        t = None
                        if dxi != dxj:
                            num = xj - xi
                            den = dxi - dxj
                            if num % den == 0:
                                cand = num // den
                                if 0 <= cand < K:
                                    if yi + cand * dyi == yj + cand * dyj:
                                        t = cand
                        else:
                            num = yj - yi
                            den = dyi - dyj
                            if num % den == 0:
                                cand = num // den
                                if 0 <= cand < K:
                                    if xi + cand * dxi == xj + cand * dxj:
                                        t = cand
                                        
                        if t is not None:
                            intervals.append((t, t))
            
            if not intervals:
                total_water += K
                continue
                
            # Merge overlapping intervals in O(N log N)
            intervals.sort()
            merged = []
            m_start, m_end = intervals[0]
            for start, end in intervals[1:]:
                if start <= m_end + 1:
                    m_end = max(m_end, end)
                else:
                    merged.append((m_start, m_end))
                    m_start, m_end = start, end
            merged.append((m_start, m_end))
            
            blocked_count = sum(end - start + 1 for start, end in merged)
            total_water += (K - blocked_count)
            
        out.append(str(total_water))
        
    sys.stdout.write('\n'.join(out) + '\n')

if __name__ == '__main__':
    solve()