import sys
from collections import deque


def main():
    data = sys.stdin.buffer.read().split()
    idx = 0
    T = int(data[idx]); idx += 1
    out = []

    for _ in range(T):
        n = int(data[idx]); r = int(data[idx + 1]); idx += 2
        times = data[idx:idx + n]
        idx += n

        pending = deque()
        ok = True

        for tok in times:
            t = int(tok)

            while pending and pending[0] <= t:
                pending.popleft()

            if len(pending) == 2:
                ok = False
                break

            if not pending:
                pending.append(t + r)
            else:
                pending.append(pending[0] + r)

        out.append("YES" if ok else "NO")

    sys.stdout.write("\n".join(out) + "\n")


main()