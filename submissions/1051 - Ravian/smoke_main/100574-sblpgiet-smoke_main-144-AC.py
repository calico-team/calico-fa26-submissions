def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    

    current_charges = 2
    wait = 0

    for i in range(N):
        if current_charges == 0:
            return "NO"
        current_charges = current_charges - 1
        if wait == 0:
            wait = R

        if i == N - 1:
            break

        t = A[i+1] - A[i]
        while t > 0 and current_charges < 2:
            if t >= wait:
                t = t - wait
                current_charges = min(current_charges + 1, 2)
                wait = R if current_charges < 2 else 0
            else:
                wait = wait - t
                t = 0

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
