def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    available_rechrages  = 2
    recharging_time = []
    for i in range (N):
        current_time = A[i]
        while recharging_time and recharging_time[0] <= current_time:
            available_rechrages += 1 
            recharging_time.pop(0)
        if (available_rechrages == 0):    
            return "NO"

        if recharging_time:
            next_recharging  = recharging_time[-1] + R
        else:
            next_recharging = current_time + R
        recharging_time.append(next_recharging)
        
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
