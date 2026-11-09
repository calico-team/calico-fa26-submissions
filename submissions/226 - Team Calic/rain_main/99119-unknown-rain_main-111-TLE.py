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
    L.sort(key=lambda p: p[0] + p[1])
    blocked = 0

    def lower(a, v):
        l, r = 0, len(a)
        while l < r:
            m = (l + r) // 2
            if a[m] < v:
                l = m + 1
            else:
                r = m
        return l

    def count(arr, queries, lo, hi):
        nonlocal blocked

        coords = sorted(set(x for x, z in arr))
        bit = [0] * (len(coords) + 1)

        arr.sort(key=lambda p: -p[1])
        queries.sort(key=lambda p: -p[1])

        def update(i):
            while i < len(bit):
                bit[i] += 1
                i += i & -i

        def prefix(i):
            s = 0
            while i:
                s += bit[i]
                i -= i & -i
            return s

        j = 0

        for x, z in queries:
            while j < len(arr) and arr[j][1] > z:
                update(lower(coords, arr[j][0]) + 1)
                j += 1

            left = lower(coords, lo(x))
            right = lower(coords, hi(x))
            blocked += prefix(right) - prefix(left)

    i = 0

    while i < N:
        s = L[i][0] + L[i][1]
        e, n = [], []

        while i < N and L[i][0] + L[i][1] == s:
            x, y, z, d = L[i]
            if d == "E":
                e.append((x, z))
            else:
                n.append((x, z))
            i += 1

        if e and n:
            count(n, e, lambda x: x + 1, lambda x: x + K)
            count(e, n, lambda x: x - K + 1, lambda x: x)

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