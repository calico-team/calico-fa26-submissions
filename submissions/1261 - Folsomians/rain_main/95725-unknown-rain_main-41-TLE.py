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
    water_counter = 0
    L = [list(i) for i in L[-N:]]
    for i in range(K):
        taken_coords = set()
        for j in L:
            x, y, z, d = j
            coord = (x,y)
            if coord not in taken_coords:
                taken_coords.add(coord)
                water_counter += 1
            if d == "E":
                j[0] += 1
            else:
                j[1] += 1
    return water_counter


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