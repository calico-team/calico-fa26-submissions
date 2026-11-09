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

import bisect

def solve(N: int, K: int, L: list) -> int:
    east, north = {}, {}
    lost = 0

    for X, Y, Z, D in L:
        s = X + Y
        if D == 'E': east.setdefault(s, []).append(X)
        else: north.setdefault(s, []).append(X)

    for s, ns in north.items():
        es = east.get(s)
        if not es: continue
        es.sort()
        for xn in ns: lost += bisect.bisect_right(es, xn) - bisect.bisect_left(es, xn-K+1)

    return (N*K)-lost

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