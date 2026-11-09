def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    available_smokes = 2
    recharge = []
    for timestamp in A:
        while len(recharge) > 0 and recharge[0] <= timestamp:
            available_smokes += 1
            recharge.pop(0)
        if available_smokes > 0:
            available_smokes -= 1
            
        else:
            return "NO"
        if len(recharge) == 0 :
           start = timestamp
        else:
            start = recharge[-1]
        if start < timestamp:
            start = timestamp
        recharge.append(start + R)

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
