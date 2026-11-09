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

    for i in range(N):
        for j in range(i,N):
            if(intersect(L[i],L[j],K)):
                total -= 1

    return total

def intersect(pos1,pos2,K):
    if(pos1[3] == pos2[3]):
        return False

    up = None
    right = None

    if(pos1[3] == "E"):
        up = pos2
        right = pos1
    else:
        up = pos1
        right = pos2

    if(right[1] - up[1] == up[0] - right[0] and right[1] - up[1] < K):
        return True
    else:
        return False

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