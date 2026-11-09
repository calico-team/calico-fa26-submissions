# t=int(input())
# def case(i):
#     if 'write_me' in i:
#         i+='make_it_sound_human'
#     elif 'what_is' in i:
#             i+='do_not_hallucinate'
#     elif 'solve' in i:
#             i+='make_no_mistakes'
#     else:
#           i+='thank_you'
#     return i
# for _ in range(t):
#     print(case(input()))

def solve(N, R, A):
    smoke=2
    for i in range(N):    
        if A[i]<=R:
            smoke+=1
    return 'YES' if smoke <= 3 else 'NO'


def main():
    T = int(input())
    for _ in range(T):
        temp = input().split()
        N = int(temp[0])
        R = int(temp[1])
        A = list(map(int, input().split()))
        print(solve(N, R, A))


if __name__ == '__main__':
    main()
