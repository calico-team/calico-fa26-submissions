
import sys
from collections import defaultdict
from bisect import bisect_left, bisect_right

def solve(N, K, L):
    groups = defaultdict(lambda: ([], []))

    for x, y, z, d in L:
        east, north = groups[x + y]
        if d == 'E':
            east.append(x)
        else:
            north.append(x)

    blocked = 0

    for east, north in groups.values():
        if not east or not north:
            continue

        east.sort()

        for x in north:
            blocked += bisect_right(east, x) - bisect_left(east, x - K + 1)

    return N * K - blocked


def main():
    data = sys.stdin.buffer
    T = int(data.readline())

    for _ in range(T):
        N, K = map(int, data.readline().split())
        L = []

        for _ in range(N):
            x, y, z, d = data.readline().split()
            L.append((int(x), int(y), int(z), d.decode()))

        print(solve(N, K, L))


if __name__ == '__main__':
    main()
