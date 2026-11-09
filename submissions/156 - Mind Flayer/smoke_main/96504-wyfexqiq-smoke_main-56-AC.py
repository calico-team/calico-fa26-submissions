from collections import deque

def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    charges = 2
    pending = deque()   # completion times of charges currently recharging
    last = 0            # completion time of the last scheduled recharge
    for a in A:
        while pending and pending[0] <= a:
            pending.popleft()
            charges += 1
        if charges == 0:
            return "NO"
        charges -= 1
        done = max(a, last) + R
        pending.append(done)
        last = done
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