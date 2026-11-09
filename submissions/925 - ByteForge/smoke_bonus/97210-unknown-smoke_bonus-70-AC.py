from collections import deque


def solve(N, R, A):
    pending = deque()
    for t in A:
        while pending and pending[0] <= t:
            pending.popleft()
        if len(pending) == 2:
            return 'NO'
        pending.append(max(t, pending[-1] if pending else t) + R)
    return 'YES'


def main():
    T = int(input())
    for _ in range(T):
        N, R = map(int, input().split())
        A = list(map(int, input().split()))
        print(solve(N, R, A))


if __name__ == '__main__':
    main()
