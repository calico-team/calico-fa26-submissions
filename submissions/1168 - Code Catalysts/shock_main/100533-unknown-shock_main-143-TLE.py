import sys
from math import isqrt


def solve(N, M, Q, earthquakes):
    size = N * M
    res = [0] * size
    filled = bytearray(size)
    find = filled.find
    remaining = size
    profiles = {}

    for R, C, P in reversed(earthquakes):
        if remaining == 0:
            break
        prof = profiles.get(P)
        if prof is None:
            pp = P * P
            prof = []
            for d in range(-P, P + 1):
                rem = pp - d * d
                prof.append((isqrt(rem), rem))
            profiles[P] = prof
        start = (R - P) * M + C
        for w, rem in prof:
            i = find(0, start - w, start + w + 1)
            while i >= 0:
                dc = i - start
                res[i] = rem - dc * dc + 1
                filled[i] = 1
                remaining -= 1
                i = find(0, i + 1, start + w + 1)
            start += M

    return [res[r * M:(r + 1) * M] for r in range(N)]


def main():
    data = sys.stdin.buffer.read().split()
    p = 0
    T = int(data[p])
    p += 1
    out = []
    for _ in range(T):
        N = int(data[p])
        M = int(data[p + 1])
        Q = int(data[p + 2])
        p += 3
        earthquakes = []
        for _ in range(Q):
            earthquakes.append((int(data[p]), int(data[p + 1]), int(data[p + 2])))
            p += 3
        answer = solve(N, M, Q, earthquakes)
        for row in answer:
            out.append(' '.join(map(str, row)))
    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == '__main__':
    main()