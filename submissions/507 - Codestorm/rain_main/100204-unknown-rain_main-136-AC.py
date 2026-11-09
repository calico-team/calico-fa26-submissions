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
    groups = {}
    for x, y, z, d in L:
        key = x+y
        if key not in groups:
            groups[key] = {"E": [], "N": []}
        groups[key][d].append((x, z))
    def countblock(p, q):
        if not p or not q:
            return 0
        p.sort(key=lambda p:p[1], reverse=True)
        q.sort(key=lambda q:q[2], reverse=True)
        axs = sorted(set(x for x, z in p))
        b = [0] * (len(axs)+1)
        def update(i):
            i = i+1
            while i < len(b):
                b[i] += 1
                i += i & -i
        def prefix(i):
            res = 0
            while i > 0:
                res += b[i]
                i -= i & -i
            return res
        block = 0
        P = 0
        from bisect import bisect_left, bisect_right
        for l, r, h in q:
            while P < len(p) and p[P][1] > h:
                x = p[P][0]
                pos = bisect_left(axs, x)
                update(pos)
                P += 1
            ls = bisect_left(axs, l)
            rs = bisect_right(axs, r)
            block += prefix(rs) - prefix(ls)
        return block
    total = N * K
    for group in groups.values():
        east = group['E']
        north = group['N']
        east_q = []
        north_q = []
        for x, z in east:
            east_q.append((x, x + K - 1, z))
        for x, z in north:
            north_q.append((x - K + 1, x, z))
        total -= countblock(north, east_q)
        total -= countblock(east, north_q)
    return total

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