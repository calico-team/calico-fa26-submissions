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
    drops = 0
    for _ in range(K):
        positions = set()
        for i in range(N):
            X,Y,Z,D = L[i]
            if (X,Y) not in positions:
                positions.add((X,Y))
                drops += 1
            if D == 'E':
                X += 1
            else:
                Y += 1
            L[i] = (X,Y,Z,D)
                
            

    
    return drops

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