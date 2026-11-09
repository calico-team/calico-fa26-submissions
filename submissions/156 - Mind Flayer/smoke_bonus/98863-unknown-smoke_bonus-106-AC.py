from collections import deque

def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    c = 2
    q = deque()
    for t in A:
        while q and q[0] <= t:
            q.popleft()
            c += 1
        if c == 0:
            return "NO"
        c -= 1
        start = max(t, q[-1]) if q else t
        q.append(start + R)
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
