import sys
import numpy as np

try:
    from numba import njit
except ImportError:  # pragma: no cover
    # Fallback: numba is expected on the judge.
    # Without it the same algorithm is still correct, just slower.
    def njit(f):
        return f

@njit
def solve_one(N, M, Rs, Cs, Ps, ans):
    # parent[r, c] = next candidate >= c in row r, M = sentinel
    parent = np.empty((N, M + 1), dtype=np.int64)
    for r in range(N):
        for c in range(M + 1):
            parent[r, c] = c

    Q = Rs.shape[0]
    for qi in range(Q - 1, -1, -1):
        R = Rs[qi]
        C = Cs[qi]
        P = Ps[qi]
        P2 = P * P
        r0 = R - P
        r1 = R + P
        for r in range(r0, r1 + 1):
            dx = r - R
            rem = P2 - dx * dx
            # integer sqrt
            d = int(np.sqrt(float(rem)))
            while (d + 1) * (d + 1) <= rem:
                d += 1
            while d * d > rem:
                d -= 1
            L = C - d
            Rr = C + d

            # find(L) with path compression, inline
            c = L
            # find
            while parent[r, c] != c:
                parent[r, c] = parent[r, parent[r, c]]
                c = parent[r, c]

            while c <= Rr:
                dc = c - C
                ans[r, c] = P2 - dx * dx - dc * dc + 1

                # delete c: union to c+1
                nxt = c + 1
                # find(nxt)
                while parent[r, nxt] != nxt:
                    parent[r, nxt] = parent[r, parent[r, nxt]]
                    nxt = parent[r, nxt]
                parent[r, c] = nxt
                c = nxt  # already the representative

def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return
    it = iter(data)
    t = next(it)
    out_parts = []

    for _ in range(t):
        n = next(it)
        m = next(it)
        q = next(it)
        Rs = np.empty(q, dtype=np.int64)
        Cs = np.empty(q, dtype=np.int64)
        Ps = np.empty(q, dtype=np.int64)
        for i in range(q):
            Rs[i] = next(it)
            Cs[i] = next(it)
            Ps[i] = next(it)

        ans = np.zeros((n, m), dtype=np.int64)
        if q:
            solve_one(n, m, Rs, Cs, Ps, ans)

        # build output
        lines = [' '.join(map(str, ans[r])) for r in range(n)]
        out_parts.append('\n'.join(lines))

    sys.stdout.write('\n'.join(out_parts))

if __name__ == "__main__":
    solve()