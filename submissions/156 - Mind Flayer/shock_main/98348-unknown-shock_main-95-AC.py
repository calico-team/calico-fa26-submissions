import sys
from math import isqrt


# Process the earthquakes from last to first. The first time (in this
# reversed order) that a quake covers a cell, that quake is the most
# recent one the cell felt, so it fixes the cell's final reading and
# the cell never needs to be touched again. A disjoint-set "next free
# column" structure per row lets us skip cells that are already fixed.

def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    pos = 0
    t = data[pos]
    pos += 1
    out_lines = []

    for _ in range(t):
        n, m, q = data[pos], data[pos + 1], data[pos + 2]
        pos += 3
        quakes = []
        for _ in range(q):
            quakes.append((data[pos], data[pos + 1], data[pos + 2]))
            pos += 3

        ans = [[0] * m for _ in range(n)]
        parent = [list(range(m + 1)) for _ in range(n)]

        def find(par, x):
            while par[x] != x:
                par[x] = par[par[x]]
                x = par[x]
            return x

        total = n * m
        filled = 0
        seen = set()

        for (r0, c0, p) in reversed(quakes):
            if filled == total:
                break
            key = (r0, c0, p)
            if key in seen:
                # an identical later quake already fixed this whole disk
                continue
            seen.add(key)
            p2 = p * p
            for dr in range(-p, p + 1):
                r = r0 + dr
                rest = p2 - dr * dr
                w = isqrt(rest)
                lo = c0 - w
                hi = c0 + w
                base = rest + 1  # value at column c0 in this row
                par = parent[r]
                row = ans[r]
                c = find(par, lo)
                while c <= hi:
                    dc = c - c0
                    row[c] = base - dc * dc
                    par[c] = find(par, c + 1)
                    filled += 1
                    c = par[c]

        for row in ans:
            out_lines.append(" ".join(map(str, row)))

    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    solve()
