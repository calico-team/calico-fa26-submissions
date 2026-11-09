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

def lower(arr, v):
    lo, hi = 0, len(arr)
    while lo < hi:
        mid = (lo + hi) // 2
        if arr[mid] < v:
            lo = mid + 1
        else:
            hi = mid
    return lo

def upper(arr, v):
    lo, hi = 0, len(arr)
    while lo < hi:
        mid = (lo + hi) // 2
        if arr[mid] <= v:
            lo = mid + 1
        else:
            hi = mid
    return lo


def solve(N: int, K: int, L: list):
    east = {}
    north = {}

    for X, Y, Z, D in L:
        d = east if D == "E" else north
        s = X + Y
        if s in d:
            d[s].append(X)
        else:
            d[s] = [X]

    covered = 0

    for s, north_xs in north.items():
        east_xs = east.get(s)
        if not east_xs:
            continue
        east_xs.sort()
        for a in north_xs:
            covered += upper(east_xs, a) - lower(east_xs, a - K+1)
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