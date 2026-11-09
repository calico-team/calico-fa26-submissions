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

from collections import Counter


def solve(N: int, K: int, L: list):
    total = 0
    for night in range(K):
        c = Counter()  # count amount rainwater collected by (x,y position)
        for drone in L:
            x, y, z, d = drone
            c[(x, y)] = 1  # ignore z, if there is one drone at z then all other drones dont matter
            # we dont care which drone collects water if multiple at a single x,y coord
            if d == "E":
                drone[0] += 1
            if d == "N":
                drone[1] += 1
        total += len(c)

    return total


def main():
    T = int(input())
    for _ in range(T):
        N, K = map(int, input().split())
        L = []
        for _ in range(N):
            X, Y, Z, D = input().split()
            L.append([int(X), int(Y), int(Z), D])

        print(solve(N, K, L))


if __name__ == "__main__":
    main()
