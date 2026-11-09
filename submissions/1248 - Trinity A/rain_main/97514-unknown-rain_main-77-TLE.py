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
    total = N*K
    for i in range(len(L)):
        for j in range(i+1, len(L)):
            drone = L[i]
            drone2 = L[j]
            if drone[3] == "E" and drone2[3] == "N":
                if (drone2[0]-drone[0]) == (drone[1]-drone2[1]) and 0 <= (drone2[0]-drone[0]) <= K-1:
                    total -= 1
            elif drone[3] == "N" and drone2[3] == "E":
                if (drone[0]-drone2[0]) == (drone2[1]-drone[1]) and 0 <= (drone[0]-drone2[0]) <= K-1:
                    total -= 1
    return int(total)

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