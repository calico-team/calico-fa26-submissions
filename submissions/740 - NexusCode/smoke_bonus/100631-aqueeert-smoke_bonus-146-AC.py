
from collections import deque

def solve(N, R, A):
    max_charges = 2
    last_finish = 0
    recharge_queue = deque()

    for t in A:

        # Process completed recharges first
        while recharge_queue and recharge_queue[0] <= t:
            recharge_queue.popleft()
            max_charges += 1

        # No charge available
        if max_charges == 0:
            return "NO"

        # Use one smoke charge
        max_charges -= 1

        # Schedule its recharge
        finish = max(t, last_finish) + R
        recharge_queue.append(finish)
        last_finish = finish

    return "YES"


def main():
    T = int(input())

    for _ in range(T):
        N, R = map(int, input().split())
        A = list(map(int, input().split()))

        print(solve(N, R, A))


if __name__ == '__main__':
    main()
