
import sys
from collections import deque

def solve():
    data = iter(map(int, sys.stdin.buffer.read().split()))
    T = next(data)
    results = []

    for _ in range(T):
        N = next(data)
        R = next(data)
        A = [next(data) for _ in range(N)]

        available = 2
        recharge = deque()
        possible = True

        for t in A:
            # Recharge all charges ready at time t
            while recharge and recharge[0] <= t:
                recharge.popleft()
                available += 1

            if available == 0:
                possible = False
                break

            # Consume one charge
            available -= 1

            # Schedule its recharge
            if recharge:
                recharge.append(recharge[-1] + R)
            else:
                recharge.append(t + R)

        results.append("YES" if possible else "NO")

    print("\n".join(results))


if __name__ == "__main__":
    solve()
