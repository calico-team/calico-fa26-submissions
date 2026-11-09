def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    available_charge = 2
    next_recharge = []
    for t in A:
        while next_recharge and next_recharge[0] <= t:
            next_recharge.pop(0)
            available_charge += 1
        
        if available_charge == 0:
            return "NO"

        available_charge -=1

        if next_recharge:
            recharge_time = next_recharge[-1] + R
        else:
            recharge_time = t + R
        next_recharge.append(recharge_time)

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
