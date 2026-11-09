import sys
def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE

    charges = 2
    recharge_end = None
    
    for t in A:
        while charges < 2 and recharge_end is not None and recharge_end <= t:
            charges += 1
            if charges < 2:
                recharge_end += R
            else:
                recharge_end = None
    
        if charges == 0:
            return "NO"
    
        if charges == 2:
            recharge_end = t + R
        charges -= 1
    return "YES"
    


def main():
    data = sys.stdin.read().split()
    p = 0
    T = int(data[p])
    p += 1
    out = []
    for _ in range(T):
        N = int(data[p])
        R = int(data[p + 1])
        p += 2
        A = list(map(int, data[p:p + N]))
        p += N
        out.append(solve(N, R, A))
    print("\n".join(out))


if __name__ == '__main__':
    main()
