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
    north = {}
    for X, Y, Z, D in L:
        if D == "N":
            s = X + Y
            if s not in north:
                north[s] = []
            north[s].append(X)
    for s in north:
        north[s].sort()

    overlaps = 0

    for X, Y, Z, D in L:
        if D == "E":
            s = X + Y
            if s in north:
                positions = north[s]
                left = bisect_left(positions, X)
                right = bisect_right(positions, X + K - 1)
                overlaps += right - left
    return N*K - overlaps

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