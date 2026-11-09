def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    chrg1, chrg2 = 0, 0
    
    for t in A:
        if min(chrg1, chrg2) <= t:
            if chrg1 <= chrg2:
                chrg1 = max(t, chrg2) + R
            else:
                chrg2 = max(t, chrg1) + R
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
