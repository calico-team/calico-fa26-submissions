def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    smoke1 = True
    smoke2 = True
    smoke1end = 0
    smoke2end = 0
    for i in range(N):
        if not smoke1 and A[i] >= smoke1end:
            smoke1 = True
            smoke1end = 0
        if not smoke2 and A[i] >= smoke2end:
            smoke2 = True
            smoke2end = 0
        if not smoke1 and not smoke2:
            return "NO"

        if i == 0:
            smoke1 = False
            smoke1end = A[i] + R
            continue

        if smoke1:
            smoke1 = False
            smoke1end = A[i] + R
        elif smoke2:
            smoke2 = False
            smoke2end = max(smoke1end, A[i]) + R

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
