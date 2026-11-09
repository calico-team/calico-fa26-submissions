
import sys
from math import isqrt

def solve(N, M, Q, earthquakes):
    size = N * M
    parent = list(range(size + 1))
    ans = [0] * size
    remaining = [M] * N
    radii = {}
    seen = set()

    def find(x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    for r, c, p in reversed(earthquakes):
        if (r, c, p) in seen:
            continue
        seen.add((r, c, p))

        if p not in radii:
            pp = p * p
            radii[p] = [isqrt(pp - d * d) for d in range(p + 1)]

        rad = radii[p]
        pp = p * p + 1

        for row in range(r - p, r + p + 1):
            if not remaining[row]:
                continue

            dy = abs(row - r)
            dx = rad[dy]
            left = row * M + c - dx
            right = row * M + c + dx

            idx = find(left)
            while idx <= right:
                x = idx - row * M - c
                ans[idx] = pp - dy * dy - x * x
                remaining[row] -= 1
                parent[idx] = find(idx + 1)
                idx = parent[idx]

    return [ans[i:i + M] for i in range(0, size, M)]


def main():
    data = iter(map(int, sys.stdin.buffer.read().split()))
    T = next(data)
    out = []

    for _ in range(T):
        N = next(data)
        M = next(data)
        Q = next(data)
        earthquakes = [
            (next(data), next(data), next(data))
            for _ in range(Q)
        ]

        for row in solve(N, M, Q, earthquakes):
            out.append(' '.join(map(str, row)))

    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == '__main__':
    main()
