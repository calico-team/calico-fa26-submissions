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
    count_rain = 0
    for x in range(K):
        for i in range(N):
            found = False
            for j in range(N):
                if i != j:
                    if L[i][0] == L[j][0] and L[i][1] == L[j][1] and L[j][2] > L[i][2]:
                        found = True
                        break
            if not found:
                count_rain += 1
        new_L = []
        for x, y, z, d in L:
            if d == "E":
                new_L.append((x + 1, y, z, d))
            else:
                new_L.append((x, y + 1, z, d))
        L = new_L                
    return count_rain

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