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

# from collections import Counter
from bisect import bisect_left
from collections import defaultdict


def solve(N: int, K: int, L: list):
    # total = 0
    # for night in range(K):
    #     c = Counter()  # count amount rainwater collected by (x,y position)
    #     for drone in L:
    #         x, y, z, d = drone
    #         c[(x, y)] = 1  # ignore z, if there is one drone at z then all other drones dont matter
    #         # we dont care which drone collects water if multiple at a single x,y coord
    #         if d == "E":
    #             drone[0] += 1
    #         if d == "N":
    #             drone[1] += 1
    #     total += len(c)

    # drone n/e overlaps once max so we find drone overlaps then it will be
    # drone * time - overlaps
    # but overlaps calculated with x1+y1=x2+y2    1 (e) and 2 (n) diff drones

    nd = set()  # north drones
    ed = set()

    for drone in L:
        x, y, z, d = drone
        if d == "E":  # no z cuz it doesnt matter just one drone at x,y means 1 water colelcted
            ed.add((x, y))
        else:
            nd.add((x, y))

    # binary search or some shit until eq??
    groupings = defaultdict(list)  # see collisionss
    for x, y in ed:
        groupings[x + y].append(y)  # multiple y vals to check if eq the sum is the important part that can equal
    for x in groupings.values():
        x.sort()  # so binary search works
    # binary search helps find # of colliding sums per drone, do it n times per drone going east
    # then sum together = total collsions then subtract
    # holy shit im a genius
    c = 0
    for x, y in nd:
        a = groupings.get(x + y, [])
        if len(a) == 0:
            continue
        c += bisect_left(a, y + K) - bisect_left(a, y)
    return K * (len(nd) + len(ed)) - c  # not N bc overlapping same row fails


def main():
    T = int(input())
    for _ in range(T):
        N, K = map(int, input().split())
        L = []
        for _ in range(N):
            X, Y, Z, D = input().split()
            L.append([int(X), int(Y), int(Z), D])

        print(solve(N, K, L))


if __name__ == "__main__":
    main()
