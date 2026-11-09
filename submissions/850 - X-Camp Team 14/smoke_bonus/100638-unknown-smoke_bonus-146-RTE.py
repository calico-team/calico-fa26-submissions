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
import sys
from collections import deque

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    idx = 0
    try:
        T = int(input_data[idx])
        idx += 1
    except (IndexError, ValueError):
        return
    
    out = []
    for _ in range(T):
        if idx >= len(input_data):
            break
        try:
            N = int(input_data[idx])
            R = int(input_data[idx+1])
            idx += 2
            
            A = []
            for _ in range(N):
                A.append(int(input_data[idx]))
                idx += 1
        except (IndexError, ValueError):
            break
        
        # Sort arrival/start times chronologically
        A.sort()
        
        q = deque([0, 0])
        possible = True
        
        for t in A:
            while q and q[0] <= t:
                q.popleft()
                
            if len(q) >= 2:
                possible = False
                
            if q:
                next_finish = q[-1] + R
            else:
                next_finish = t + R
                
            q.append(next_finish)
            
        out.append("YES" if possible else "NO")
        
    print('\n'.join(out))

if __name__ == '__main__':
    solve()
    
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
# import sys
# 
# def solve():
#     input_data = sys.stdin.read().split()
#     if not input_data:
#         return
#     
#     iterator = iter(input_data)
#     try:
#         T_str = next(iterator, None)
#         if T_str is None:
#             return
#         T = int(T_str)
#     except (ValueError, StopIteration):
#         return
#     
#     for _ in range(T):
#         try:
#             N = int(next(iterator))
#             K = int(next(iterator))
#         except (ValueError, StopIteration):
#             break
#         
#         groups = {}
#         for _ in range(N):
#             try:
#                 x = int(next(iterator))
#                 y = int(next(iterator))
#                 z = int(next(iterator))
#                 d = next(iterator)
#             except (ValueError, StopIteration):
#                 break
#             
#             s_val = x + y
#             if s_val not in groups:
#                 groups[s_val] = ([], [])
#             
#             if d == 'S':
#                 groups[s_val][0].append(x)
#             else:
#                 groups[s_val][1].append(x)
#                 
#         total_water = N * K
#         loss = 0
#         
#         for s_val, (s_xs, n_xs) in groups.items():
#             if not s_xs or not n_xs:
#                 continue
#             
#             n_xs.sort()
#             
#             for x_s in s_xs:
#                 L = x_s
#                 R = x_s + K - 1
#                 
#                 # Manual binary search (bisect_left and bisect_right)
#                 # bisect_left
#                 low, high = 0, len(n_xs)
#                 while low < high:
#                     mid = (low + high) // 2
#                     if n_xs[mid] < L:
#                         low = mid + 1
#                     else:
#                         high = mid
#                 idx_l = low
#                 
#                 # bisect_right
#                 low, high = 0, len(n_xs)
#                 while low < high:
#                     mid = (low + high) // 2
#                     if n_xs[mid] <= R:
#                         low = mid + 1
#                     else:
#                         high = mid
#                 idx_r = low
#                 
#                 loss += (idx_r - idx_l)
#                 
#         print(total_water - loss)
# 
# if __name__ == '__main__':
#     solve()