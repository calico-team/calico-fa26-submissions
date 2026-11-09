def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE

    A.sort()
    charges = 2
    next_recharge = float('inf') 

    for time in A:
        while charges < 2 and next_recharge <= time:
            charges += 1
            if charges < 2:
                next_recharge += R
            else:
                next_recharge = float('inf')
        if charges == 0:
            return "NO"
        charges -= 1
        if next_recharge == float('inf'):
            next_recharge = time + R

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
