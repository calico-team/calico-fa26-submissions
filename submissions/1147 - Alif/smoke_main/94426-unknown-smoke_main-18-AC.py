import sys
from collections import deque

def ok(n, r, a):
    have = 2
    q = deque()  

    for t in a:
        while q and q[0] <= t:
            q.popleft()
            have += 1

        if not have:
            return False

        have -= 1
        
        st = q[-1] if q else t
        q.append(st + r)

    return True

def main():
    d = sys.stdin.buffer.read().split()
    p = 0
    T = int(d[p]); p += 1
    res = []
    for _ in range(T):
        N = int(d[p]); R = int(d[p+1]); p += 2
        A = list(map(int, d[p:p+N])); p += N
        res.append("YES" if ok(N, R, A) else "NO")
    sys.stdout.write("\n".join(res))

if __name__ == "__main__":
    main()