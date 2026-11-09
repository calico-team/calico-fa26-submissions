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
    return 0

    for night in range(K):

        positions = {}

        # Move all drones
        for i in range(N):
            if L[i][3] == 'E':
                L[i][0] += 1
            else:
                L[i][1] += 1

        # Find the highest drone at each coordinate
        for x, y, z, d in L:
            if (x, y) not in positions:
                positions[(x, y)] = z
            else:
                positions[(x, y)] = max(positions[(x, y)], z)

        # Count drones at the highest position
        for x, y, z, d in L:
            if z == positions[(x, y)]:
                total += 1

    return total

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