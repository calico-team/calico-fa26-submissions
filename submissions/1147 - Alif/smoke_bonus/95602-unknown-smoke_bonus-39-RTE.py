import sys
from collections import deque

def ok(N, R, A):
    have = 2
    q = deque()

    for t in A:
        # refund anything that came back by now
        while q and q[0] <= t:
            q.popleft()
            have += 1

        if not have:
            return False

        have -= 1
        # recharges are sequential, so this one starts after the last queued
        st = q[-1] if q else t
        q.append(st + R)

    return True

def main():
    d = sys.stdin.read().split()
    p = 0
    T = int(d[p]); p += 1
    res = []
    for _ in range(T):
        N = int(d[p]); R = int(d[p+1]); p += 2
        A = [int(x) for x in d[p:p+N]]
        p += N
        res.append("YES" if ok(N, R, A) else "NO")
    sys.stdout.write("\n".join(res))

if __name__ == "__main__":
    main()