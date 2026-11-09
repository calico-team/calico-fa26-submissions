import sys
from bisect import bisect_left, bisect_right
from collections import defaultdict


def solve(N: int, K: int, L: list):
    east = defaultdict(list)
    north = defaultdict(list)

    for X, Y, Z, D in L:
        if D == 'E':
            east[X + Y].append(X)
        else:
            north[X + Y].append(X)

    meetings = 0
    for s, nxs in north.items():
        exs = east.get(s)
        if not exs:
            continue
        exs.sort()
        for x2 in nxs:
            # E drones with x2-K+1 <= X1 <= x2
            meetings += bisect_right(exs, x2) - bisect_left(exs, x2 - K + 1)

    return N * K - meetings


def main():
    data = sys.stdin.read().split()
    pos = 0
    T = int(data[pos]); pos += 1
    out = []
    for _ in range(T):
        N = int(data[pos]); K = int(data[pos + 1]); pos += 2
        L = []
        for _ in range(N):
            X = int(data[pos]); Y = int(data[pos + 1])
            Z = int(data[pos + 2]); D = data[pos + 3]
            pos += 4
            L.append((X, Y, Z, D))
        out.append(str(solve(N, K, L)))
    print("\n".join(out))


if __name__ == '__main__':
    main()