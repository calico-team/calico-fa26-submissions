def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    charges = 2
    waiting_charges = 0
    next_recharge_time= 0

    for t in A:
        while waiting_charges > 0 and next_recharge_time <= t:
            charges += 1
            waiting_charges -= 1

            if waiting_charges > 0:
                next_recharge_time += R
        if charges == 0:
            return "NO"
        charges -= 1
        waiting_charges += 1
        if waiting_charges == 1:
            next_recharge_time = t + R

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
