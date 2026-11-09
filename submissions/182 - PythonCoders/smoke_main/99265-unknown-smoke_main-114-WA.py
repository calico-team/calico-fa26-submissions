def solve(N, R, A):
    b=0
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
"""
    for e in range(0,N-2):
        if not A[e+1]-A[e]>=R:
            b+=1
    
    s=A[-1]/R+2-b
    for q in range(0,N-1):
##            s-=1
##            b+=1
        s-=1
    if s>=0:
        return "YES"
    else:
        return'NO'


def main():
    T = int(input())
    for z in range(T):
        temp = input().split()
        N = int(temp[0])
        R = int(temp[1])
        A = list(map(int, input().split()))
        print(solve(N, R, A))

if __name__ == '__main__':
    main()
