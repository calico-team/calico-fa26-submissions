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
    poss = []
    for X, Y, Z, D in L:
        diag = X + Y
        if D == "E":
            poss.append((diag, X, -1))
            poss.append((diag, X + (K - 1), 1))
        else:
            poss.append((diag, X, 0))
    zone = 0
    conc = 0
    for diag, X, kind in sorted(poss):
        zone -= kind
        if kind == 0:
            conc += zone
    return N * K - conc

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