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
    groups = {}

    for x,y,z,d in L:
        s=x+y
        if s not in groups:
            groups[s]=[[], []]

        if d =="E":
            groups[s][0].append(x)
        else:
            groups[s][1].append(x)

    intersec = 0
    for east,north in groups.values():
        north.sort()
        for ex in east:
            left=bisect_left(north,ex)
            right=bisect_right(north,ex +K-1)
            intersec += right - left

    return N*K-intersec

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