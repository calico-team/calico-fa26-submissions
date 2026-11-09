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
    e_drones = defaultdict(list)   # key: x+y, value: x of E drones
    n_drones = defaultdict(list)   # key: x+y, value: x of N drones

    for X, Y, Z, D in L:
        s = X + Y
        if D == "E":
            e_drones[s].append(X)
        else:
            n_drones[s].append(X)

    covered = 0

    for s in e_drones:
        if s not in n_drones:
            continue

        n_drones[s].sort()
        lst = n_drones[s]

        for xe in e_drones[s]:
            covered += bisect_right(lst, xe + K - 1) - bisect_left(lst, xe)

    return N * K - covered

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