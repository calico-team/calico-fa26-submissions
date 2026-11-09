
import sys
from collections import deque

def can_use_all_smokes(n, r, requests):

    recharge = deque()

    for current_time in requests:

        # Restore all charges that have completed recharging
        while recharge and recharge[0] <= current_time:
            recharge.popleft()

        # Both smoke charges are unavailable
        if len(recharge) == 2:
            return False

        # Start the next recharge after the previous one finishes
        if recharge:
            finish_time = max(current_time, recharge[-1]) + r
        else:
            finish_time = current_time + r

        recharge.append(finish_time)

    return True


def main():
    t = int(sys.stdin.readline())

    for _ in range(t):
        n, r = map(int, sys.stdin.readline().split())
        requests = list(map(int, sys.stdin.readline().split()))

        if can_use_all_smokes(n, r, requests):
            print("YES")
        else:
            print("NO")


if __name__ == "__main__":
    main()
