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
    for drone in L:
        for d in L:
            if (drone[0] == d[0]) and (drone[1]==d[1]) and (drone[2]< d[2]):
                pass
            else:
                valid_drones.append(drone)
    for drone in L:
        if drone[3] == 'N':
            drone[1] += 1
        elif drone[3] == 'S':
            drone[1] -= 1
        elif drone[3] == 'E':
            drone[0] += 1
        elif drone[3] == 'W':
            drone[0] -= 1
    return len(valid_drones) * K

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