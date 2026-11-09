import sys
from collections import deque


def solve() -> None:
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
        times = data[idx:idx + n]
        idx += n

        # finish times of charges currently recharging, in order.
        # recharges happen one at a time, so a newly used charge only
        # starts recharging once every charge ahead of it is restored.
        recharging = deque()
        ok = True
        for time in times:
            while recharging and recharging[0] <= time:
                recharging.popleft()
            if len(recharging) >= 2:
                ok = False
                break
            start = recharging[-1] if recharging else time
            recharging.append(start + r)
        out.append("YES" if ok else "NO")
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
