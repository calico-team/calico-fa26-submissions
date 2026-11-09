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
    from bisect import bisect_left,bisect_right
    total=N*K
    group={}
    for X,Y,Z,D in L:
        keyy=X+Y
        if keyy not in group:
            group[keyy]=[[],[]]
        if D=='E':
            group[keyy][0].append(X)
        else:
            group[keyy][1].append(X)
    for east,north in group.values():
        if not east or not north:
            continue
        north.sort()
        for X in east:
            left=bisect_right(north,X)
            right=bisect_right(north,X+K-1)
            total-=right-left
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