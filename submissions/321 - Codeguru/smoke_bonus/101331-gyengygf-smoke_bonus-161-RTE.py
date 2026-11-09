import sys
from collections import deque

def solve(n, r, a):
    # restore_times[i] = the time when the i-th busy charger becomes free again
    # They come back in the order they were used, so a deque works nicely.
    restore_times = deque()

    for t in a:
        # First, free up any chargers that finished recharging by now.
        while restore_times and restore_times[0] <= t:
            restore_times.popleft()

        # If both chargers are still busy, we're stuck.
        if len(restore_times) == 2:
            return "NO"

        if not restore_times:
            # Both chargers are free: use one, it comes back at t + r.
            restore_times.append(t + r)
        else:
            # One charger is free, one is busy. Use the free one,
            # but it can't start recharging until the busy one is done.
            restore_times.append(restore_times[0] + r)

    return "YES"


def main():
    data = sys.stdin.read().split()
    idx = 0
    T = int(data[idx]); idx += 1

    answers = []
    for _ in range(T):
        n = int(data[idx])
        r = int(data[idx + 1])
        idx += 2
        a = list(map(int, data[idx:idx + n]))
        idx += n

        answers.append(solve(n, r, a))

    sys.stdout.write("\n".join(answers) + "\n")


main()