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
    optimalWater = K * N
    lostWater = 0
    for i in range(K):
        for drone in L:
            if drone[D] == "E":
                drone[X] += 1
            elif drone[D] == "N":
                drone[Y] += 1
        for droneC in L:
            for droneCB in L:
                if droneC[X] == droneCB[X] and droneC[Y] == droneCB[Y]:
                    lostWater += 1
    return optimalWater - lostWater

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