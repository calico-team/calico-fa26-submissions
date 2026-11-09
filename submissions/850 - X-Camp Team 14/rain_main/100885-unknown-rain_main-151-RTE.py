#problem1
# T = int(input())
# for _ in range(T):
#     S = input()
# 
#     if 'write_me' in S:
#         print(S + 'make_it_sound_human')
#     elif 'what_is' in S:
#         print(S + 'do_not_hallucinate')
#     elif 'solve' in S:
#         print(S + 'make_no_mistakes')
#     else:
#         print(S + 'thank_you')

#problem2
# for _ in range(int(input())):
#     tokens = input().split()
#     N, R = int(tokens[0]), int(tokens[1])
#     A = [int(x) for x in input().split()]
#     
#     charges = 2
#     recharge_times = []
#     possible = True
#     
#     for t in A:
#         while recharge_times and recharge_times[0] <= t:
#             recharge_times.pop(0)
#             charges += 1
#             
#         if charges > 0:
#             charges -= 1
#             end_time = (t + R) if not recharge_times else (recharge_times[-1] + R)
#             recharge_times.append(end_time)
#         else:
#             possible = False
#             break
#             
#     print("YES" if possible else "NO")

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

#problem 3
#     chars = input().split()
#     
#     hint = ['_'] * length_string
#     
#     for j in chars:
#         ans = list(hint)
#         for k in range(length_string):
#             if ans[k] == '_':
#                 ans[k] = j
#                 
#         # flush=True is required for interactive problems!
#         print(*ans, sep='', flush=True)
#         
#         feedback = input()
#         if feedback == "CORRECT":
#             break
#         hint = list(feedback)

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
        for i in range(N):
            x = int(next(iterator))
            y = int(next(iterator))
            z = int(next(iterator))
            d = next(iterator)
            dx, dy = dir_map[d]
            drones.append((z, x, y, dx, dy))
            
        # Sort drones by Z descending (highest Z first)
        drones.sort(key=lambda d: d[0], reverse=True)
        
        total_water = 0
        
        # To track occupied (x, y) at each time t for higher-Z drones
        # For efficient lookup, we can store time intervals or positions.
        # Below is the core logic structure for tracking coverage.
        
        occupied = [set() for _ in range(K)]
        
        for z, x, y, dx, dy in drones:
            drone_water = 0
            curr_x, curr_y = x, y
            for t in range(K):
                if (curr_x, curr_y) not in occupied[t]:
                    drone_water += 1
                    occupied[t].add((curr_x, curr_y))
                curr_x += dx
                curr_y += dy
            total_water += drone_water
            
        out.append(str(total_water))
        
    print('\n'.join(out))

if __name__ == '__main__':
    solve()