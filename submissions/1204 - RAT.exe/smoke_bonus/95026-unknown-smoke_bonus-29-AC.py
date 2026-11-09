from collections import deque


def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    charges = 2
    pending = deque()  

    for t in A:
        
        while pending and pending[0] <= t:
            pending.popleft()
            charges += 1

        if charges == 0:
            return "NO"

        charges -= 1
        
        start = max(t, pending[-1]) if pending else t
        pending.append(start + R)

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
        
