from collections import defaultdict
from bisect import bisect_left, bisect_right
"""
* Return an integer denoting the amount of rain collected after the Kth nights

* N: Number of drones
* K: Number of nights
* L: a list in this order [X, Y, Z, D] for each drone
*   X: Starting X location of Drone
*   Y: Starting Y location of Drone
*   Z: Starting Z location of Drone
*   D: Starting direction of Drone
"""

def solve(N: int, K: int, L: list):
    groups = defaultdict(list)

    for X, Y, Z, D in L:
        groups[X + Y].append((X, Z, D))

    blocked = 0

    for points in groups.values():
        points.sort(key=lambda p: p[0])

        xs = [p[0] for p in points]
        m = len(points)

        bit_e = [0] * (m + 1)
        bit_n = [0] * (m + 1)

        def update(bit, i):
            i += 1
            while i <= m:
                bit[i] += 1
                i += i & -i

        def query(bit, i):
            result = 0
            while i > 0:
                result += bit[i]
                i -= i & -i
            return result

        points.sort(key=lambda p: -p[1])

        i = 0

        while i < m:
            j = i

            while j < m and points[j][1] == points[i][1]:
                j += 1

            for x, z, d in points[i:j]:
                if d == 'E':
                    left = bisect_left(xs, x)
                    right = bisect_right(xs, x + K - 1)

                    blocked += (
                        query(bit_n, right) -
                        query(bit_n, left)
                    )

                else:
                    left = bisect_left(xs, x - K + 1)
                    right = bisect_right(xs, x)

                    blocked += (
                        query(bit_e, right) -
                        query(bit_e, left)
                    )

            for x, z, d in points[i:j]:
                pos = bisect_left(xs, x)

                if d == 'E':
                    update(bit_e, pos)
                else:
                    update(bit_n, pos)

            i = j

    return N * K - blocked


def main():
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
