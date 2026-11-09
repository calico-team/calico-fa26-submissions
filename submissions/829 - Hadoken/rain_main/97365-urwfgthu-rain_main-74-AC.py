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
    north_dir = {} 

    for X, Y, Z, D in L:
        if D == 'N':
            if X + Y not in north_dir:
                north_dir[X + Y] = []
            north_dir[X + Y].append(X)

    for i in north_dir:
        north_dir[i].sort()

    meets = 0
    for X, Y, Z, D in L:
        if D == 'E':
            if (X + Y) in north_dir:

                north_xs = north_dir[X + Y]
                meets += bisect_right(north_xs, X + K - 1) - bisect_left(north_xs, X)

    return N * K - meets


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