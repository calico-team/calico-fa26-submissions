
import sys
from collections import defaultdict
from bisect import bisect_left, bisect_right


def solve(N: int, K: int, L: list):
    east = defaultdict(list)
    north = defaultdict(list)

    for x, y, z, d in L:
        key = x + y

        if d == 'E':
            east[key].append(x)
        else:
            north[key].append(x)

    total = N * K

    for key, east_positions in east.items():
        if key not in north:
            continue

        north_positions = sorted(north[key])

        for x in east_positions:
            left = bisect_left(north_positions, x)
            right = bisect_right(north_positions, x + K - 1)

            total -= right - left

    return total


def main():
    input = sys.stdin.readline

    T = int(input())

    for _ in range(T):
        N, K = map(int, input().split())
        L = []

        for _ in range(N):
            X, Y, Z, D = input().split()
            L.append((int(X), int(Y), int(Z), D))

        print(solve(N, K, L))


if __name__ == '__main__':
    main()
