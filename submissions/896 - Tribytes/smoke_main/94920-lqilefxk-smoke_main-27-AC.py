import sys
from collections import deque


def solve(n, r, a):
    # queue holds the times at which currently-recharging charges come back
    q = deque()
    last = 0  # completion time of the most recently scheduled recharge
    for t in a:
        # recharges are processed before requests at the same timestamp
        while q and q[0] <= t:
            q.popleft()
        if len(q) >= 2:  # both charges are in use -> none available
            return "NO"
        # recharges are sequential: a new one starts after the previous finishes
        last = max(t, last) + r
        q.append(last)
    return "YES"


def main():
    data = sys.stdin.read().split()
    idx = 0
    t = int(data[idx]); idx += 1
    out = []
    for _ in range(t):
        n = int(data[idx]); r = int(data[idx + 1]); idx += 2
        a = list(map(int, data[idx:idx + n])); idx += n
        out.append(solve(n, r, a))
    print("\n".join(out))


main()
