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

    total = N * K

    if(N == 1):
        return K

    Elist = []
    Nlist = []

    for i in range(N):
        if(L[i][3] == "N"):
            Nlist.append(L[i])
        else:
            Elist.append(L[i])

    for i in Elist:
        for j in Nlist:
            total -= intersect(i,j,K)

    return total

def intersect(right,up,K):
    if(right[1] - up[1] == up[0] - right[0] and right[1] - up[1] < K and right[1] - up[1] > 0):
        return 1
    else:
        return 0

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