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
    total = 0
    for i in range(0,K):
        num_overlap = 0

        for j in range(0,N-1):
            for k in range(j+1,N):
                if(L[j][0] == L[k][0] and L[j][1] == L[k][1]):
                    num_overlap += 1

        total += N - num_overlap

        for j in range(0,N):
            if(L[j][3] == "N"):
                L[j][1] += 1
            elif(L[j][3] == "E"):
                L[j][0] += 1

    return total

def main():
    T = int(input())
    for _ in range(T):
        N, K = map(int, input().split())
        L = []
        for _ in range(N):
            X, Y, Z, D = input().split()
            L.append([int(X), int(Y), int(Z), D])

        print(solve(N, K, L))

if __name__ == '__main__':
    main()