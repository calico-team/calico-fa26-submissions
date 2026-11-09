from collections import deque
def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    recharges = deque()

    for timestamp in A: 
        while recharges and recharges[0] <=timestamp:
            recharges.popleft()

        available_charges = 2-len(recharges)
        if available_charges > 0:
            if not recharges:
                recharges.append(timestamp + R)
            else:
                recharges.append(recharges[-1] + R)
        else:
            return "NO"
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
