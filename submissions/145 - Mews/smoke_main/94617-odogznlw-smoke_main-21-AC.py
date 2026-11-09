
from collections import deque

def solve():
    t = int(input())

    for _ in range(t):
        n, r = map(int, input().split())
        a = list(map(int, input().split()))

        recharge = deque()
        available = 2

        possible = True

        for time in a:
            while recharge and recharge[0] <= time:
                recharge.popleft()
                available += 1

            if available == 0:
                possible = False
                break

            available -= 1

            start = max(time, recharge[-1] if recharge else time)
            recharge.append(start + r)

        print("YES" if possible else "NO")


def read_your_input():
    solve()


if __name__ == "__main__":
    read_your_input()
