def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    NEG = -(10 ** 18)
    # Availability time of the two charges (both ready at round start).
    c1 = NEG
    c2 = NEG
    # Time the single sequential recharger becomes free.
    free = NEG
    for t in A:
        # Use the charge that becomes available earliest.
        if c1 > c2:
            c1, c2 = c2, c1
        if c1 > t:          # earliest charge not yet available -> cannot fulfill
            return "NO"
        # Consume c1 at time t; its recharge runs on the sequential recharger.
        start = t if t > free else free
        done = start + R
        free = done
        c1 = done
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
