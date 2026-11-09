import sys
from collections import deque


def main():
    data = sys.stdin.buffer.read().split()
    idx = 0
    t = int(data[idx])
    idx += 1
    out = []
    for _ in range(t):
        n = int(data[idx])
        r = int(data[idx + 1])
        idx += 2
        charges = 2
        q = deque()  # finish times of pending recharges, in order
        ok = True
        for i in range(n):
            x = int(data[idx + i])
            # recharges finishing at or before x are processed first
            while q and q[0] <= x:
                q.popleft()
                charges += 1
            if charges == 0:
                ok = False
                break
            charges -= 1
            start = q[-1] if q else x
            q.append(start + r)
        idx += n
        out.append("YES" if ok else "NO")
    print("\n".join(out))


main()
