import sys
from collections import deque

def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    it = iter(data)
    t = next(it, 0)
    out = []
    for _ in range(t):
        n = next(it)
        R = next(it)
        A = [next(it) for _ in range(n)]
        charges = 2
        q = deque()
        ok = True
        for a in A:
            while q and q[0] <= a:
                q.popleft()
                charges += 1
            if charges == 0:
                ok = False
                break
            charges -= 1
            if not q:
                finish = a + R
            else:
                finish = q[-1] + R
            q.append(finish)
        out.append("YES" if ok else "NO")
    sys.stdout.write("\n".join(out))

if __name__ == "__main__":
    solve()