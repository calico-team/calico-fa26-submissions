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
            
        Zs = []
        Xs = []
        Ys = []
        DXs = []
        DYs = []
        
        for _ in range(N):
            x = int(next(iterator))
            y = int(next(iterator))
            z = int(next(iterator))
            d = next(iterator)
            dx, dy = dir_map[d]
            
            Zs.append(z)
            Xs.append(x)
            Ys.append(y)
            DXs.append(dx)
            DYs.append(dy)
            
        water_counts = [0] * N
        
        # Simulate each of the K nights
        for t in range(K):
            max_z_at = {}
            
            # First pass: find the maximum Z at each (x, y) for time t
            for i in range(N):
                cx = Xs[i] + t * DXs[i]
                cy = Ys[i] + t * DYs[i]
                pos = (cx, cy)
                z = Zs[i]
                if pos not in max_z_at or z > max_z_at[pos]:
                    max_z_at[pos] = z
            
            # Second pass: collect water if the drone is the highest at its position
            for i in range(N):
                cx = Xs[i] + t * DXs[i]
                cy = Ys[i] + t * DYs[i]
                if max_z_at[(cx, cy)] == Zs[i]:
                    water_counts[i] += 1
                    
        out.append(str(sum(water_counts)))
        
    sys.stdout.write('\n'.join(out) + '\n')

if __name__ == '__main__':
    solve()