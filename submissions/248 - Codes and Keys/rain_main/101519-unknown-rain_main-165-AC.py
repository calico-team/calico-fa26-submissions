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
    total_rainwater = 0
    east_drones = {}
    north_drones = {}
    for X, Y, Z, D in L:
        coordinates = X + Y
        if D == 'E':
            if coordinates not in east_drones:
                east_drones[coordinates] = set()
            east_drones[coordinates].add(X)
        else:
            if coordinates not in north_drones:
                north_drones[coordinates] = set()
            north_drones[coordinates].add(X)

    total_rainwater = N * K

    for coordinates in east_drones:
        if coordinates not in north_drones:
            continue
        for east_X in east_drones[coordinates]:
            for north_X in north_drones[coordinates]:
                if east_X >= north_X:
                    continue

                moves_needed = north_X - east_X
                if moves_needed < K:
                    total_rainwater -= 1
    return total_rainwater

    

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