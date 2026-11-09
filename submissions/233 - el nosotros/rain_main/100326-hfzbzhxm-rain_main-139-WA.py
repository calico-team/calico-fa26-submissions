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

    for i in range(N-1):
        for j in range(i+1,N):
            total -= intersect(L[i],L[j],K)

    return total

def intersect(pos1,pos2,K):
    if(pos1[3] == pos2[3]):
        return 0

    up = None
    right = None

    if(pos1[3] == "E"):
        up = pos2
        right = pos1
    else:
        up = pos1
        right = pos2

    if(right[1] - up[1] == up[0] - right[0] and right[1] - up[1] < K):
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