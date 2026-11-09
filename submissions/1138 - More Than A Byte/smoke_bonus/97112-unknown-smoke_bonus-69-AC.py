from collections import deque
def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    availableCharges = 2
    rechargingTime = deque()

    for currentTime in A:
        while rechargingTime and rechargingTime[0] <= currentTime:
            rechargingTime.popleft()
            availableCharges += 1
        if availableCharges == 0:
            return "NO"
        availableCharges -= 1

        if rechargingTime:
            nextRecharge = rechargingTime[-1] + R
        else:
            nextRecharge = currentTime + R
        rechargingTime.append(nextRecharge)
    
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
