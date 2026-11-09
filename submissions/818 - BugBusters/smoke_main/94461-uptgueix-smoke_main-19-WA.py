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
        q = deque()  # Scheduled recharge times
        possible = True

        for time in a:
            # Process recharges before handling this request.
            while q and q[0] <= time:
                q.popleft()
                charges += 1

            if charges == 0:
                possible = False
                break

            # Use one charge and schedule its sequential recharge.
            charges -= 1
            if not q:
                q.append(time + r)
            else:
                q.append(q[-1] + r)

        out.append("YES" if possible else "NO")

    sys.stdout.write("\\n".join(out))

if __name__ == "__main__":
    solve()
