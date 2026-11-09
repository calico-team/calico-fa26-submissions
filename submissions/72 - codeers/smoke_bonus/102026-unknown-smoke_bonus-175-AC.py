from collections import deque
def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    q = []
    head = 0
    for t in A:
        while head < len(q) and q[head] <= t:
            head += 1
        if len(q) - head == 2:
            return "NO"
        start = max(t, q[-1] if head < len(q) else t)
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
