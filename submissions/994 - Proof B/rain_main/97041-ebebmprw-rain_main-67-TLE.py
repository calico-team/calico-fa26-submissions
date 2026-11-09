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
    L = [[j for j in l] for l in L]
    t = 0
    for _ in range(K):
        t += rain(L)
        for i in range(N):
            if L[i][3] == "E":
                L[i][0] += 1
            else:
                L[i][1] += 1
    return t

def rain(L):
    t = 0
    for l in L:
        for l2 in L:
            if l[0] == l2[0]:
                if l[1] == l2[1]:
                    if l[2] < l2[2]:
                        t -= 1
                        break
        t += 1
    return t

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