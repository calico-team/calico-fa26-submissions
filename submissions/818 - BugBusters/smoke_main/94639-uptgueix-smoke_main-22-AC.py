import sys
from collections import deque

def solve():
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return

    idx = 0
    t = data[idx]
    idx += 1
    out = []

    for _ in range(t):
        n = data[idx]
        r = data[idx + 1]
        idx += 2
        a = data[idx:idx + n]
        idx += n

        charges = 2
        recharge_times = deque()
        possible = True

        for time in a:
            # Recharge completed charges before processing this request.
            while recharge_times and recharge_times[0] <= time:
                recharge_times.popleft()
                charges += 1

            if charges == 0:
                possible = False
                break

            # Use one charge. Recharges happen one after another.
            charges -= 1
            if recharge_times:
                recharge_times.append(recharge_times[-1] + r)
            else:
                recharge_times.append(time + r)

        out.append("YES" if possible else "NO")

    sys.stdout.write("\n".join(out))

if __name__ == "__main__":
    solve()
