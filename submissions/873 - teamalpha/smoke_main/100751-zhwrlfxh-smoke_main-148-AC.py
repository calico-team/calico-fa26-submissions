def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    available_charges=2
    recharge_time=[]

    # to process each request  
    for t in A:
            while recharge_time and recharge_time[0] <= t:
                recharge_time.pop(0)
                available_charges+=1

            # to check if charges are available or not
            if available_charges==0:
                return "NO"    

            available_charges -=1

            if recharge_time:
                 completeion_timme=recharge_time[-1] + R
            else:
                 completeion_timme=R+t    
            
            recharge_time.append(completeion_timme)    


    



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
