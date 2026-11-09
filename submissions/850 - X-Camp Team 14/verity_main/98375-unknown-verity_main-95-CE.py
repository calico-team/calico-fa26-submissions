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

t = int(input())
for _ in range(t):
    length_string, distinct_char = map(int, input().split())
    chars = input().split()
    
    hint = ['_'] * length_string
    
    for j in chars:
        ans = list(hint)
        # Fill remaining underscores with the current character
        for k in range(length_string):
            if ans[k] == '_':
                ans[k] = j
                
        print(*ans, sep='')
        
        feedback = input()
        if feedback == "CORRECT":
            break
        hint = list(feedback)
                break
                
        print(*ans, sep='')
        
        # Read the feedback from the judge
        feedback = input()
        if feedback == "CORRECT":
            break
        hint = list(feedback)