import sys
import numpy as np

def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return

    idx = 0
    t = data[idx]
    idx += 1
    out = []

    for _ in range(t):
        n = data[idx]
        m = data[idx + 1]
        q = data[idx + 2]
        idx += 3

        quakes = []
        for _ in range(q):
            r = data[idx]
            c = data[idx + 1]
            p = data[idx + 2]
            idx += 3
            quakes.append((r, c, p))

        ans = np.zeros((n, m), dtype=np.int64)
        filled = np.zeros((n, m), dtype=bool)
        filled_cnt = 0
        total = n * m

        # Reverse: last earthquake covering a cell wins.
        for r0, c0, p in reversed(quakes):
            if filled_cnt == total:
                break
            if p < 0:
                continue

            r1 = r0 - p
            r2 = r0 + p
            c1 = c0 - p
            c2 = c0 + p

            # Clamp just in case (constraints guarantee it is inside).
            r1 = max(r1, 0)
            r2 = min(r2, n - 1)
            c1 = max(c1, 0)
            c2 = min(c2, m - 1)

            sub_filled = filled[r1:r2 + 1, c1:c2 + 1]
            if sub_filled.all():
                continue

            # Distance squared for the whole bounding box, in C.
            rows = np.arange(r1, r2 + 1, dtype=np.int64)[:, None] - r0
            cols = np.arange(c1, c2 + 1, dtype=np.int64)[None, :] - c0
            dist2 = rows * rows + cols * cols

            # Inside the disk and not yet filled.
            mask = (dist2 <= p * p) & (~sub_filled)
            if not mask.any():
                continue

            sub_ans = ans[r1:r2 + 1, c1:c2 + 1]
            # value = p^2 - dist^2 + 1
            sub_ans[mask] = p * p - dist2[mask] + 1
            sub_filled[mask] = True
            filled_cnt += int(mask.sum())

        for r in range(n):
            out.append(' '.join(map(str, ans[r].tolist())))

    sys.stdout.write('\n'.join(out))

if __name__ == "__main__":
    solve()