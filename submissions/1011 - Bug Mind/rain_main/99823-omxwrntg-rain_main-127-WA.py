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
    drops = 0
    drops = N * K # max
    xydata = {}
    for i in range(N): 
        x, y, z, d = L[i]
        xydata[(y, x)] = i # x y in reverse for contrst comprson

    for i in range(N):
        thisxy = (L[i][0], L[i][1]) # x y in forward for comparison
        dist = max(L[i][0], L[i][1]) - min(L[i][0], L[i][1]) # max of x and y - min of x and y
        if thisxy in xydata and dist < K:
            drops -= 1 # remove the duplicate

    return drops

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