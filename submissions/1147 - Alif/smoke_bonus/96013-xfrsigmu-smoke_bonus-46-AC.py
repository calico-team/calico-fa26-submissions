import sys
from collections import deque

def go(n, r, ts):
    q = deque()

    for t in ts:
        while q and q[0] <= t:
            q.popleft()

        if len(q) == 2:
            return "NO"

        if q:
            nt = max(t, q[-1]) + r
        else:
            nt = t + r

        q.append(nt)

    return "YES"

def main():
    inp = sys.stdin.readline
    T = int(inp())

    for _ in range(T):
        n, r = map(int, inp().split())
        ts = list(map(int, inp().split()))
        print(go(n, r, ts))

if __name__ == "__main__":
    main()