import sys
import re
from math import isqrt


def main():
    data = sys.stdin.buffer.read().split()
    pos = 0
    test_cases = int(data[pos]); pos += 1

    BITS = [[k for k in range(8) if (b >> k) & 1] for b in range(256)]
    nonzero = re.compile(b'[^\x00]')

    out = []
    for _ in range(test_cases):
        N = int(data[pos]); M = int(data[pos + 1]); Q = int(data[pos + 2])
        pos += 3
        quakes = data[pos:pos + 3 * Q]
        pos += 3 * Q

        size = N * M
        res = [0] * size
        unpainted = (1 << size) - 1
        masks = {}

        for q in range(Q - 1, -1, -1):
            if not unpainted:
                break
            R = int(quakes[3 * q]); C = int(quakes[3 * q + 1]); P = int(quakes[3 * q + 2])

            D = masks.get(P)
            if D is None:
                pp = P * P
                strs = []
                for d in range(P + 1):
                    w = isqrt(pp - d * d)
                    strs.append('0' * (M - 1 - P - w) + '1' * (2 * w + 1) + '0' * (P - w))
                D = int(''.join(strs[::-1] + strs[1:]), 2)
                masks[P] = D

            shift = (R - P) * M + (C - P)
            new = (unpainted >> shift) & D
            if new:
                unpainted ^= new << shift
                nb = new.to_bytes((new.bit_length() + 7) >> 3, 'little')
                base = P * P + 1
                for m in nonzero.finditer(nb):
                    i = m.start()
                    off = i * 8
                    for k in BITS[nb[i]]:
                        p = off + k
                        a, j = divmod(p, M)
                        a -= P
                        j -= P
                        res[shift + p] = base - a * a - j * j

        for r in range(N):
            out.append(" ".join(map(str, res[r * M:(r + 1) * M])))

    sys.stdout.write("\n".join(out) + "\n")


main()