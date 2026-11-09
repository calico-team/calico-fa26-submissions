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
    east = {}
    north = {}
    for x, y, z, d in L:
        s = x + y
        if d == 'E':
            east.setdefault(s, []).append(x)
        else:
            north.setdefault(s, []).append(x)

    blocked = 0
    for s, ex in east.items():
        nx = north.get(s)
        if nx is None:
            continue
        ex.sort()
        nx.sort()
        lo = 0
        hi = 0
        m = len(nx)
        for a in ex:
            while lo < m and nx[lo] < a:
                lo += 1
            if hi < lo:
                hi = lo
            while hi < m and nx[hi] <= a + K - 1:
                hi += 1
            blocked += hi - lo

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
