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
        s = x+y
        if s not in groups:
            groups[s] = ([],[])
        if d == "E":
            groups[s][0].append((x))
        else:
            groups[s][1].append((x))
    collisions = 0
    for east, north in groups.values():
        if not east or not north:
            continue
        east.sort()
        north.sort()
        p1 = 0
        p2 = 0
        le = len(east)
        for xb in north:
            while p1<le and east[p1]<=xb:
                p1+=1
            while p2<le and east[p2]<=xb -K:
                p2+=1
            collisions+= p1-p2
        return N*K-collisions

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