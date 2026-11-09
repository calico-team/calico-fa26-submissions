import sys
from math import isqrt


def main():
    data = sys.stdin.buffer.read().split()
    t = int(data[0])
    pos = 1
    out = []
    width_cache = {}

    for _ in range(t):
        n, m, q = int(data[pos]), int(data[pos + 1]), int(data[pos + 2])
        pos += 3
        quakes = []
        for _ in range(q):
            quakes.append((int(data[pos]), int(data[pos + 1]), int(data[pos + 2])))
            pos += 3

        stride = m + 1                     # one sentinel column per row
        nxt = list(range(n * stride))      # next unassigned cell in the same row
        owner = [-1] * (n * stride)

        def find(i):
            root = i
            while nxt[root] != root:
                root = nxt[root]
            while nxt[i] != root:          # path compression
                nxt[i], i = root, nxt[i]
            return root

        seen = set()
        # Last earthquake wins, so paint in reverse and never repaint a cell.
        for qi in range(q - 1, -1, -1):
            r0, c0, p = quakes[qi]
            if (r0, c0, p) in seen:        # an identical later quake already covers it
                continue
            seen.add((r0, c0, p))
            widths = width_cache.get(p)
            if widths is None:
                pp = p * p
                widths = [isqrt(pp - d * d) for d in range(p + 1)]
                width_cache[p] = widths
            for dr in range(-p, p + 1):
                w = widths[dr if dr >= 0 else -dr]
                base = (r0 + dr) * stride
                end = base + c0 + w
                c = find(base + c0 - w)
                while c <= end:
                    owner[c] = qi
                    nxt[c] = c + 1
                    c = find(c + 1)

        for r in range(n):
            base = r * stride
            row = []
            for c in range(m):
                qi = owner[base + c]
                if qi < 0:
                    row.append("0")
                else:
                    r0, c0, p = quakes[qi]
                    row.append(str(p * p - ((r - r0) ** 2 + (c - c0) ** 2) + 1))
            out.append(" ".join(row))

    sys.stdout.write("\n".join(out) + "\n")


main()