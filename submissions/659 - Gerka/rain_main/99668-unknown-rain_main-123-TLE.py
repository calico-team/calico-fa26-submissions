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
    drones = {}
    totalRainfall = 0
    for i in range(N):
        drones[i] = {"x":L[i][0], "y":L[i][1],"z":L[i][2],"d": 1 if L[i][3] == "N" else -1}
    for i in range(K):
        usedX = set()
        for i in range(N):
            usedX.add((drones[i]["x"],drones[i]["y"]))
            if drones[i]["d"] == 1:
                drones[i]["y"] += 1
            else:
                drones[i]["x"] += 1
        totalRainfall += len(usedX)
        
    return totalRainfall

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