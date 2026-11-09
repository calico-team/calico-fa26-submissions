from collections import defaultdict
from bisect import bisect_left, bisect_right

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

def solve(N: int, K: int, L: list):
    if K == 1:
        return N

    north_groups = defaultdict(list)
    same_height_groups = defaultdict(list)
    east_drones = []

    for x, y, z, direction in L:
        diagonal = x + y

        if direction == "N":
            north_groups[diagonal].append(x)
            same_height_groups[(diagonal, z)].append(x)
        else:
            east_drones.append((x, diagonal, z))

    for positions in north_groups.values():
        positions.sort()

    for positions in same_height_groups.values():
        positions.sort()

    blocked = 0

    for x, diagonal, z in east_drones:
        positions = north_groups.get(diagonal)

        if positions is None:
            continue

        low = x + 1
        high = x + K - 1

        total = (
            bisect_right(positions, high)
            - bisect_left(positions, low)
        )

        equal_positions = same_height_groups.get(
            (diagonal, z)
        )

        if equal_positions is not None:
            equal_count = (
                bisect_right(equal_positions, high)
                - bisect_left(equal_positions, low)
            )
            total -= equal_count

        blocked += total

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