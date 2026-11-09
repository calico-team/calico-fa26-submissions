import sys
from math import isqrt


def main():
    data = sys.stdin.buffer.read().split()
    t = int(data[0])
    pos = 1
    out = []
    for _ in range(t):
        n, m, q = int(data[pos]), int(data[pos + 1]), int(data[pos + 2])
        pos += 3
        quakes = [int(x) for x in data[pos:pos + 3 * q]]
        pos += 3 * q
        maxp = max(quakes[2::3])
        root = [isqrt(x) for x in range(maxp * maxp + 1)]
        squares = [d * d for d in range(-maxp, maxp + 1)]
        cells = n * m
        val = [0] * cells
        done = bytearray(cells)
        ones = b"\x01" * (2 * maxp + 1)
        free = (1 << cells) - 1
        masks = {}
        for i in range(3 * q - 3, -1, -3):
            r0, c0, p = quakes[i], quakes[i + 1], quakes[i + 2]
            p2 = p * p
            if p < 40:
                first, last = -p, p
            else:
                disk = masks.get(p)
                if disk is None:
                    parts = []
                    for dr in range(p, -p - 1, -1):
                        h = root[p2 - dr * dr]
                        parts.append("0" * (m - p - h - 1) + "1" * (2 * h + 1) + "0" * (p - h))
                    disk = int("".join(parts), 2)
                    masks[p] = disk
                shift = (r0 - p) * m + c0 - p
                hit = (free >> shift) & disk
                if not hit:
                    continue
                free ^= hit << shift
                first = ((hit & -hit).bit_length() - 1) // m - p
                last = (hit.bit_length() - 1) // m - p
            for dr in range(first, last + 1):
                d2 = dr * dr
                h = root[p2 - d2]
                center = (r0 + dr) * m + c0
                hi = center + h + 1
                s = done.find(0, center - h, hi)
                if s < 0:
                    continue
                top = p2 - d2 + 1
                off = maxp - center
                while s >= 0:
                    e = done.find(1, s, hi)
                    if e < 0:
                        e = hi
                    val[s:e] = [top - v for v in squares[s + off:e + off]]
                    done[s:e] = ones[:e - s]
                    s = done.find(0, e, hi)
        for r in range(n):
            out.append(" ".join(map(str, val[r * m:r * m + m])))
    sys.stdout.write("\n".join(out) + "\n")


main()
