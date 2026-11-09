
import sys
from collections import deque

def solve():
    input = sys.stdin.readline
    T = int(input())

    for _ in range(T):
        N, R = map(int, input().split())
        A = list(map(int, input().split()))

        available = 2
        recharge = deque()
        possible = True

        for t in A:
            # Restore all charges whose recharge is complete
            while recharge and recharge[0] <= t:
                recharge.popleft()
                available += 1

            if available == 0:
                possible = False
                break

            # Use one charge
            available -= 1

            # Schedule its recharge sequentially
            if recharge:
                recharge.append(recharge[-1] + R)
            else:
                recharge.append(t + R)

        print("YES" if possible else "NO")


if __name__ == "__main__":
    solve()
