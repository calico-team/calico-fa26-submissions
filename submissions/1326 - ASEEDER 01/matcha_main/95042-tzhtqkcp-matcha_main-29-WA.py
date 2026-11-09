
# def check(P):
#     check_right = 0
#     for i in range(0,len(P)):
#         if P[i:i+8] == "write_me":
#             P+=" make_it_sound_human"
#         elif P[i:i+7] == "what_is":
#             P+="do_not_hallucinate"
#         elif P[i:i+5] == "solve":
#             P+="make_no_mistakes"
#         else:
#             check_right+=1
#     if check_right == len(P):
#         P+=" thank_you"
#     return P
# n = int(input())
# for i in range(n):
#     S = str(input())
#     print(check(S))


n = int(input())
for i in range(n):
    life = int(input())
    L = list(map(int,input().split(" ")))
    R = list(map(int,input().split(" ")))
    result = 0
    for j in range(0,len(L)):
        max_value = max(L[j],R[j])
        result+=max_value
    print(result)