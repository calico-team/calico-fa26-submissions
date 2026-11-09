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


def findNextPos(X, Y, Z, D):
    Zout = Z

    if D == "N":
        Yout = Y + 1
        Xout = X

    if D == "E":
        Yout = Y
        Xout = X + 1

    return Xout, Yout, Zout, D


def solve(N: int, K: int, L: list):

    score = 0


    for night in range(K):
        xCollected = [
        ]
        yCollected = [
        ]


        for drone in range(N):
            if L[drone][0] not in xCollected:
                if L[drone][1] not in yCollected:
                    score += 1
                    xCollected.append(L[drone][0])
                    yCollected.append(L[drone][1])



        for drone in range(N):
            L[drone] = findNextPos(L[drone][0],L[drone][1],L[drone][2],L[drone][3])



    return score

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