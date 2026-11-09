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

def solve(N: int, K: int, L):
    intersections = 0
    for s in L.keys():
        drones = list(L[s])
        l1 = [0] * (s + 1)
        l2 = [0] * (s + 1)
        for drone in drones:
            if drone[2] == "E":
                l1[int(s / 2 + (drone[0] - drone[1]) / 2)] += 1
            else:
                l2[int(s / 2 + (drone[0] - drone[1]) / 2)] += 1
        l3 = [sum(l2[i + 1: min(i + K, s + 2)]) for i in range(s + 1)]
        for i in range(s + 1):
            intersections += l1[i] * l3[i]
    return intersections

def main():
    T = int(input())
    for _ in range(T):
        N, K = map(int, input().split())
        L = {}
        for _ in range(N):
            X, Y, Z, D = input().split()
            X = int(X)
            Y = int(Y)
            Z = int(Z)
            if (X + Y) in L.keys():
                L[X + Y].add((X, Y, D))
            else:
                L[X + Y] = {(X, Y, D)}
        print(N * K - solve(N, K, L))

if __name__ == '__main__':
    main()
