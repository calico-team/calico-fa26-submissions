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

from bisect import bisect_left

def solve(N: int, K: int, L: list):

    drone_groups = {}

    
    for X, Y, Z, path in L:
        label = X + Y

        if label not in drone_groups:
            drone_groups[label] = []

        drone_groups[label].append((X, Y, Z, path))

    meet_point = 0

    
    for label in drone_groups:
        drones = drone_groups[label]

        
        e_x = []

        for d in drones:
            if d[3] == "E":
                e_x.append(d[0])

        e_x.sort()

        
        for d in drones:
            if d[3] == "N":
                n_x = d[0]

                left = bisect_left(e_x, n_x - K + 1)
                right = bisect_left(e_x, n_x)

                meet_point += right - left

    return N * K - meet_point


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