import sys
from bisect import bisect_left, bisect_right


def solve(N, K, L):
    east = []
    north = []
    for X, Y, D in L:
        if D == b"E":
            east.append((X + Y) * 1e10 + X)
        else:
            north.append((X + Y) * 1e10 + X)
    east.sort()
    return N * K - sum(bisect_right(east, key) - bisect_left(east, key - K + 1) for key in north)


def main():
    data = sys.stdin.buffer.read().split()
    p = 1
    for _ in range(int(data[0])):
        N, K = int(data[p]), int(data[p + 1])
        p += 2
        q = p + 4 * N
        L = zip(map(float, data[p:q:4]), map(float, data[p + 1:q:4]), data[p + 3:q:4])
        p = q
        print(solve(N, K, L))


main()
