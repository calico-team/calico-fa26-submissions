def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    charge=1
    useP=[None,None]
    for i in range(1,N):
            for j in range(len(useP)):
                if(useP[j]!=None):
                    if A[i]-useP[j]>=R:
                        charge+=1
                        useP[j]=None
            if A[i] - A[i - 1] < R:
                if useP[0]!=None:
                    useP[1]=A[i]
                else:
                    useP[0]=A[i]
            charge-=1
            
    if charge<=0:
        return "NO"
    else:
        return "YES"
        


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
