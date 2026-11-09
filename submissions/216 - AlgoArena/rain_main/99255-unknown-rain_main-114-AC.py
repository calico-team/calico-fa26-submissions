import sys
from bisect import bisect_left, bisect_right
from collections import defaultdict
input = sys.stdin.readline

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
    east = defaultdict(list)   # diagonal (x + y) -> x of east drones
    north = defaultdict(list)  # diagonal (x + y) -> x of north drones
    for X, Y, Z, D in L:
        if D == 'E':
            east[X + Y].append(X)
        else:
            north[X + Y].append(X)

    blocked = 0
    for diagonal, east_xs in east.items():
        north_xs = sorted(north[diagonal]) if diagonal in north else []
        for x in east_xs:
            blocked += bisect_right(north_xs, x + K - 1) - bisect_left(north_xs, x)
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