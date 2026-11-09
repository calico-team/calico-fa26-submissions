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

from bisect import bisect_left, bisect_right

def solve(N: int, K: int, L: list):
    diagonals = {}
    for X, Y, Z, D in L:
        east, north = diagonals.setdefault(X + Y, ([], []))
        if D == 'E':
            east.append(X)
        else:
            north.append(X)

    blocked = 0
    for east, north in diagonals.values():
        north.sort()
        for x in east:
            left = bisect_left(north, x)
            right = bisect_right(north, x + K - 1)
            blocked += right - left

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