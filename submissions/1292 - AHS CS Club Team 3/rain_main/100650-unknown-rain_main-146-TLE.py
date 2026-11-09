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
    rainCount = 0
    for i in range(K):
        for j in range(N):
            rainCatch = True
            for k in range(N):
                if ((L[j][0] == L[k][0] and L[j][1] == L[k][1]) and L[j][2] < L[k][2]):
                    rainCatch = False
            if rainCatch:
                rainCount += 1
        for l in range(N):
            if (L[l][3] == "N"):
                L[l] = (L[l][0], L[l][1] + 1, L[l][2], L[l][3])
            else:
                L[l] = (L[l][0] + 1, L[l][1], L[l][2], L[l][3])

    return rainCount

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