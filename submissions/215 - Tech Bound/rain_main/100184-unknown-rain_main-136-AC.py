"""
* Return an integer denoting the amount of rain collected after the Kth nights 
*
* N: Number of drones
* K: Number of nights
* L: a list in this order [X, Y, Z, D] for each drone
*   X: Starting X location of Drone
*   Y: Starting Y location of Drone
*   Z: Starting Z location of Drone
*   D: Starting direction of Drone
"""
from collections import defaultdict
from bisect import bisect_left, bisect_right




def solve(N: int, K: int, L: list):
    groups = defaultdict(list)

    for x, y, z, d in L:
        groups[x + y].append((x, z, d))

    blocked = 0

    for drones in groups.values():
        xs = sorted(x for x, _, _ in drones)
        m = len(xs)
        index = {x: i + 1 for i, x in enumerate(xs)}

        bit_e = [0] * (m + 1)
        bit_n = [0] * (m + 1)

        def prefix_sum(bit, i):
            total = 0
            while i > 0:
                total += bit[i]
                i -= i & -i
            return total

        def add(bit, i):
            while i <= m:
                bit[i] += 1
                i += i & -i

        drones.sort(key=lambda item: -item[1])

        p = 0
        while p < len(drones):
            q = p
            height = drones[p][1]

            while q < len(drones) and drones[q][1] == height:
                q += 1

            for x, _, direction in drones[p:q]:
                if direction == 'E':
                    left = bisect_left(xs, x)
                    right = bisect_right(xs, x + K - 1)

                    blocked += (
                        prefix_sum(bit_n, right)
                        - prefix_sum(bit_n, left)
                    )
                else:
                    left = bisect_left(xs, x - K + 1)
                    right = bisect_right(xs, x)

                    blocked += (
                        prefix_sum(bit_e, right)
                        - prefix_sum(bit_e, left)
                    )

            for x, _, direction in drones[p:q]:
                add(
                    bit_e if direction == 'E' else bit_n,
                    index[x]
                )

            p = q

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