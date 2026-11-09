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
            blocked = set()
            b_add = blocked.add
            
            for i in range(N):
                if i == j:
                    continue
                zi, xi, yi, dxi, dyi = drones[i]
                
                if zi > zj:
                    if dxi != dxj:
                        num = xj - xi
                        den = dxi - dxj
                        if num % den == 0:
                            cand = num // den
                            if 0 <= cand < K:
                                if yi + cand * dyi == yj + cand * dyj:
                                    b_add(cand)
                    else:
                        if xi == xj:
                            if dyi != dyj:
                                num = yj - yi
                                den = dyi - dyj
                                if num % den == 0:
                                    cand = num // den
                                    if 0 <= cand < K:
                                        b_add(cand)
                            else:
                                if yi == yj:
                                    for t_step in range(K):
                                        b_add(t_step)
            
            total_water += (K - len(blocked))
            
        out.append(str(total_water))
        
    sys.stdout.write('\n'.join(out) + '\n')

if __name__ == '__main__':
    solve()