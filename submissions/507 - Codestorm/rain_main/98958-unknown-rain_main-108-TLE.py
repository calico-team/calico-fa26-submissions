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
    Total = N * K
    block = [set() for _ in range(N)]
    for i in range(N):
        for j in range(i+1, N):
            x1, y1, z1, d1 = L[i]
            x2, y2, z2, d2 = L[j]
            if d1 == d2:
                continue
            if d1=="N":
                north = L[i]
                east = L[j]
                n = i
                e = j
            else:
                north = L[j]
                east = L[i]
                n = j
                e = i
            merge_x = north[0] - east[0]
            merge_y = east[1] - north[1]
            if merge_x == merge_y and 0 <= merge_x < K:
                if north[2] > east[2]:
                    block[e].add(merge_x)
                elif east[2] > north[2]:
                    block[n].add(merge_x)
    for i in range(N):
        Total = Total - len(block[i])                      
    return Total

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