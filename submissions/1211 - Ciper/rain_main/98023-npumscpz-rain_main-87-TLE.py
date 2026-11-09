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
    rain = 0

    for day in range(K):
        max_z = {}

        current = []

        for X, Y, Z, D in L:
            c_x = X + day if D == 'E' else X
            c_y = Y + day if D == 'N' else Y
            
            current.append((c_x, c_y, Z))
            
            pos = (c_x, c_y)
            if pos not in max_z or Z > max_z[pos]:
                max_z[pos] = Z

        for c_x, c_y, Z in current:
            if max_z[(c_x, c_y)] == Z:
                rain += 1

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