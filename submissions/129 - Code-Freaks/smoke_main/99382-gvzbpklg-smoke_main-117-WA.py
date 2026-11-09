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
        
    for t_stamp in A:
        if a==0 and t_stamp>=recharge_A:
            a=1
            recharge_A=-1
        if b==0 and t_stamp>=recharge_B:
            b=1
            recharge_B=-1    
        if a & b ==0:
            return "NO"
        curr_recharge=max(recharge_A,recharge_B)
        starting_time=max(t_stamp,curr_recharge)
        finishingTime=starting_time+R

        if a==1:
            a=0
            startTime=recharge_B if b==0 else t_stamp
            recharge_A=finishingTime
        elif b==1:
            b=0
            startTime=recharge_A if a ==0 else t_stamp
            recharge_B=finishingTime
    # YOUR CODE HERE
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
