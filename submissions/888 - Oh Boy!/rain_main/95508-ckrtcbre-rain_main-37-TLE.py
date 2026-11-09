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
    water = N
    for i in range(K-1):
        sky = {}
        for drone in range(N):
            X, Y, Z, D = L[drone]
            if D == 'N':
                Y += 1
            elif D == 'E':
                X += 1
            if (X,Y) in sky:
                water -= 1
            sky[(X,Y)] = 1
            water += 1
            L[drone] = (X, Y, Z, D)
        
    return water

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