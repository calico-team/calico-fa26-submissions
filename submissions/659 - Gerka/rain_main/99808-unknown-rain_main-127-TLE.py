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
    north = set()
    east = set()
    totalRainfall = 0
    for x,y,z,d in L:
        if d == "N":
            north.add((x,y))
        else:
            east.add((x,y))
    totalRainfall = (len(north) + len(east)) * K
    
    for xNorth, yNorth in north:
        for xEast, yEast in east:
            t = xNorth - xEast
            if t == yEast - yNorth and 0 <= t < K:
                totalRainfall -= 1
        
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