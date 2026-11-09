import sys
from collections import deque


def can_fulfill_all(requests, recharge_time):
    charges = 2
    recharging = deque()

    for request_time in requests:
        # Recharges are processed before requests at the same timestamp.
        while recharging and recharging[0] <= request_time:
            recharging.popleft()
            charges += 1

        if charges == 0:
            return False

        charges -= 1
        if recharging:
            # Recharges happen sequentially.
            recharging.append(recharging[-1] + recharge_time)
        else:
            recharging.append(request_time + recharge_time)

    return True


def solve():
    input = sys.stdin.buffer.readline
    test_cases = int(input())
    answers = []

    for _ in range(test_cases):
        n, recharge_time = map(int, input().split())
        requests = list(map(int, input().split()))
        answers.append("YES" if can_fulfill_all(requests, recharge_time) else "NO")

    sys.stdout.write("\n".join(answers))


if __name__ == "__main__":
    solve()
