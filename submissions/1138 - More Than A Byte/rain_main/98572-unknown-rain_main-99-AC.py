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
    groups = defaultdict(list)

    for x, y, z, d in L:
        groups[x + y].append((x, d))

    lostRain = 0

    for drones in groups.values():
        drones.sort()

        eastDrones = []
        start = 0

        for x, direction in drones:
            while start < len(eastDrones) and eastDrones[start] < x - K + 1:
                start += 1

            if direction == 'N':
                lostRain += len(eastDrones) - start
            else:
                eastDrones.append(x)
    return N * K - lostRain

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