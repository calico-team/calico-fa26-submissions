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
    for i in range(N):
        x,y,z,d = L[i]
        s = x+y

        if s in groups:
            groups[s] = []
        groups[s].append((x,z,d))

    blocked = 0

    for s in groups:
        drones = groups[s]

        for a in drones:
            xa, za, da = a

            for b in drones:
                xb, zb, db = b
                if zb < za:
                    pass

                if da == 'E' and db == 'N':
                    t = xb - xa
                elif da == 'N' and db == 'E':
                    t = xa - xb
                else:
                    continue

                if t>= 0 and t <= K - 1:
                    blocked += 1

    return N * K - blocked

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