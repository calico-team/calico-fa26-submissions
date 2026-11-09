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

# def solve(N, R, A):
#     smoke=2
#     for i in range(N):    
#         if A[i]<=R and smoke<2:
#             smoke+=1
#     return 'YES' if smoke<=3 else 'NO'


# def main():
#     T = int(input())
#     for _ in range(T):
#         temp = input().split()
#         N = int(temp[0])
#         R = int(temp[1])
#         A = list(map(int, input().split()))
#         print(solve(N, R, A))


# if __name__ == '__main__':
#     main()
def find(values, target):
    left=0
    right=len(values)
    while left<right:
        middle=(left+right)//2
        if values[middle]<target:
            left=middle+1
        else:
            right=middle
    return left
def solve(N:int, K:int, drones):
    east={}
    north=[]
    for x,y,z,direction in drones:
        line=x+y
        if direction=='E':
            if line not in east:
                east[line]=[]
            east[line].append(x)
        else:
            north.append((line, x))
    for xs in east.values():
        xs.sort()

    blocked=0
    for line,x in north:
        xs=east.get(line,[])
        blocked+=(
            find(xs,x)
            -find(xs,x-K+1)
        )
    return N*K-blocked

def main():
    T=int(input())
    for _ in range(T):
        N,K=map(int,input().split())
        L=[]
        for _ in range(N):
            X,Y,Z,D=input().split()
            L.append((int(X),int(Y),int(Z),D))

        print(solve(N,K,L))

if __name__=='__main__':
    main()