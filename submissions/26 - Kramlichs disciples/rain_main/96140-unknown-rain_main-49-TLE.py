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
    valid_drones = []
    rain=0
    for _ in range(K):
        for drone in L:
            blocked = any(
                drone[0] == d[0]
                and drone[1] == d[1]
                and drone[2] < d[2]
                for d in L
            )
            if not blocked:
                valid_drones.append(drone)
        for i, drone in enumerate(L):
            x, y, z, direction = drone
            if direction == 'N':
                L[i] = (x, y + 1, z, direction)
            elif direction == 'S':
                L[i] = (x, y - 1, z, direction)
            elif direction == 'E':
                L[i] = (x + 1, y, z, direction)
            elif direction == 'W':
                L[i] = (x - 1, y, z, direction)
        rain += len(valid_drones)
        valid_drones = []
    return rain

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