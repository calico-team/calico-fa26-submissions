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
    drones = list(L)
    liters = 0
    for _ in range(K):
        xy_positions = [item[:2] for item in drones]
        unique = set(xy_positions)
        if len(unique) == len(xy_positions):
            liters += N
        else:
            liters += len(unique)

        for i in range(len(drones)):
            X, Y, Z, D = drones[i]
            if D == "N":
                drones[i] = X, Y + 1, Z, D
            else:
                drones[i] = X + 1, Y, Z, D
        
    return liters

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