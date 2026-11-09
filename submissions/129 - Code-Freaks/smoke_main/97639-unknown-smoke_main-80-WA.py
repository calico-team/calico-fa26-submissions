def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    a,b=1,1
    recharge_A=float("-inf")
    recharge_B=float("-inf")
        
    for t in A:
        if a==0 and t>=recharge_A:
            a=1
        if b==0 and t>=recharge_B:
            b=1    
        if a & b ==0:
            return "No"
        if a==1:
            a=0
            time=max(t,recharge_B)
            recharge_A=time+R
        elif b==1:
            b=0
            time=max(t,recharge_A)
            recharge_B=time+R
    # YOUR CODE HERE
    return "Yes"


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
