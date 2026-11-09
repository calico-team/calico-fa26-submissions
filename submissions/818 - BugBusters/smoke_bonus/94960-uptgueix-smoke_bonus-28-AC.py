import sys
from collections import deque

def can_smoke(n, r, times):
    charges = 2
    recharge_times = deque()

    for current_time in times:
        # Recharges at this timestamp happen before the request.
        while recharge_times and recharge_times[0] <= current_time:
            recharge_times.popleft()
            charges += 1

        if charges == 0:
            return False

        # Use one charge. If another recharge is pending, this
        # charge starts recharging only after that one finishes.
        charges -= 1
        next_recharge = (
            recharge_times[-1] if recharge_times
            else current_time
        ) + r
        recharge_times.append(next_recharge)

    return True


def main():
    data = iter(map(int, sys.stdin.buffer.read().split()))

    try:
        t = next(data)
    except StopIteration:
        return

    answers = []

    for _ in range(t):
        n = next(data)
        r = next(data)
        times = [next(data) for _ in range(n)]

        answers.append("YES" if can_smoke(n, r, times) else "NO")

    sys.stdout.write("\n".join(answers))


if __name__ == "__main__":
    main()
