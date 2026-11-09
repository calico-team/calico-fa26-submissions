import sys
from collections import deque


def int_stream():
    # yield the input's integers one at a time without ever holding
    # the whole token list in memory (the bonus input can be huge)
    read = sys.stdin.buffer.read
    leftover = b""
    while True:
        chunk = read(1 << 16)
        if not chunk:
            if leftover:
                yield int(leftover)
            return
        data = leftover + chunk
        parts = data.split()
        if data[-1:] not in b" \t\r\n":
            # last token may continue into the next chunk
            leftover = parts.pop() if parts else b""
        else:
            leftover = b""
        yield from map(int, parts)


def solve() -> None:
    nums = int_stream()
    t = next(nums, None)
    if t is None:
        return
    out = []
    for _ in range(t):
        n = next(nums)
        r = next(nums)

        # finish times of charges currently recharging, in order.
        # recharges happen one at a time, so a newly used charge only
        # starts recharging once every charge ahead of it is restored.
        recharging = deque()
        ok = True
        left = n
        while left > 0:
            time = next(nums)
            left -= 1
            if not ok:
                continue
            while recharging and recharging[0] <= time:
                recharging.popleft()
            if len(recharging) >= 2:
                ok = False
                continue
            start = recharging[-1] if recharging else time
            recharging.append(start + r)
        out.append("YES" if ok else "NO")
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
