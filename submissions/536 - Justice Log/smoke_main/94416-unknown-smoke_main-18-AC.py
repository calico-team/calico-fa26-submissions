def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    t = 0
    i = 0
    stock = 2
    charge = 0
    while t <= A[-1] and i < len(A):
        # print(t,stock)
        if stock < 2:
            charge += 1
            if charge == R:
                stock += 1
                charge = 0
        if t == A[i]:
            if stock > 0:
                stock -= 1
                i += 1
            else:
                return "NO"
        t += 1
    return "YES" if i >= len(A) else "NO"


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
