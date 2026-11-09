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

def solve(N: int, K: int, L: list):
    groups = defaultdict(lambda: [[], []])

    for x, y, z, d in L:
        s = x + y

        if d == 'E':
            groups[s][0].append(x)
        else:
            groups[s][1].append(x)

    collisions = 0

    for east, north in groups.values():
        east.sort()
        north.sort()

        left = 0
        right = 0

        for x in north:
            # Remove east drones that meet too early
            while left < len(east) and east[left] < x - K + 1:
                left += 1

            # Count east drones strictly to the left
            while right < len(east) and east[right] < x:
                right += 1

            collisions += right - left

    return N * K - collisions


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