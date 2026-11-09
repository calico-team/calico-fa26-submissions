import sys
from collections import deque

def solve():
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return

    idx = 0
    t = data[idx]
    idx += 1
    answers = []

    for _ in range(t):
        n = data[idx]
        r = data[idx + 1]
        idx += 2

        times = data[idx:idx + n]
        idx += n

        charges = 2
        recharge_times = deque()
        possible = True

        for current_time in times:
            # Complete all recharges due at or before this request.
            while recharge_times and recharge_times[0] <= current_time:
                recharge_times.popleft()
                charges += 1

            # No available charge means this request cannot be fulfilled.
            if charges == 0:
                possible = False
                break

            # Use one charge. Its recharge is scheduled after all
            # previously queued recharges, because recharging is sequential.
            charges -= 1
            if recharge_times:
                recharge_times.append(recharge_times[-1] + r)
            else:
                recharge_times.append(current_time + r)

        answers.append("YES" if possible else "NO")

    sys.stdout.write("\n".join(answers))


if __name__ == "__main__":
    solve()
