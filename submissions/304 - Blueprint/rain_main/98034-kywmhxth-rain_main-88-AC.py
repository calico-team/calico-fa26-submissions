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

    drone_east = defaultdict(list)
    drone_north = defaultdict(list)

    for x, y, z, d in L:
        s = x + y
        if d == 'E':
            drone_east[s].append(x)
        else:
            drone_north[s].append(x)
    blocked = 0

    for s, positions in drone_east.items():
        if s not in drone_north:
            continue
        positions.sort()

        for x in drone_north[s]:
            left = bisect_left(positions, x - K + 1)
            right = bisect_right(positions, x)
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