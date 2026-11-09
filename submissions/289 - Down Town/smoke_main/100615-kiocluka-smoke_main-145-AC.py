from collections import deque
import sys


def main():
    data = sys.stdin.read().split()
    idx = 0
    t = int(data[idx])
    idx += 1
    out = []
    for _ in range(t):
        n = int(data[idx])
        r = int(data[idx + 1])
        idx += 2
        a = list(map(int, data[idx : idx + n]))
        idx += n

        charges = 2
        q = deque()
        ok = True
        for x in a:

            while q and q[0] <= x:
                q.popleft()
                charges += 1
            if charges == 0:
                ok = False
                break
            charges -= 1
            start = q[-1] if q else x
            q.append(start + r)
        out.append("YES" if ok else "NO")
    print("\n".join(out))


main()
