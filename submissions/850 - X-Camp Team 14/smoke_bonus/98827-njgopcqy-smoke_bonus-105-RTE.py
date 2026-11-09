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

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    idx = 0
    T = int(input_data[idx])
    idx += 1
    
    for _ in range(T):
        N = int(input_data[idx])
        R = int(input_data[idx+1])
        idx += 2
        
        A = []
        for _ in range(N):
            A.append(int(input_data[idx]))
            idx += 1
            
        finish_times = []
        possible = True
        
        for t in A:
            # Remove charges that have finished recharging by time t
            while finish_times and finish_times[0] <= t:
                finish_times.pop(0)
                
            # If both charges are currently recharging, we don't have an available charge
            if len(finish_times) >= 2:
                possible = False
                
            # Sequential recharge: next charge starts when the previous one finishes
            if finish_times:
                next_finish = finish_times[-1] + R
            else:
                next_finish = t + R
                
            finish_times.append(next_finish)
            
        print("YES" if possible else "NO")

if __name__ == '__main__':
    solve()

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